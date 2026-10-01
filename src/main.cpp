#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

std::string shellQuote(const std::string& value){
  std::string quoted = "'";
  for(char c : value){
    if(c=='\'') quoted += "'\\''";
    else quoted += c;
  }
  return quoted + "'";
}

bool run(const std::string& command){
  std::cout << " > " << command << "\n";
  return std::system(command.c_str()) == 0;
}

std::string packageNameFromUrl(std::string url) {
    const std::string suffix = ".git";

    if (url.size() >= suffix.size() &&
        url.compare(url.size() - suffix.size(), suffix.size(), suffix) == 0) {
        url.resize(url.size() - suffix.size());
    }

    const auto slash = url.find_last_of('/');
    return slash == std::string::npos ? url : url.substr(slash + 1);
}

int summon(const std::string& url, const std::string& ref){
  const std::string name = packageNameFromUrl(url);
  const fs::path root = fs::path(std::getenv("HOME"));
  const fs::path sourceDir = root / "sources" / name;
  const fs::path buildDir = root / "build" / name;

  fs::create_directories(root / "sources");
  fs::create_directories(root / "build");
  
  if(!fs::exists(sourceDir / ".git")){
    std::cout<<"Summoning "<<name<<"...\n";
    if(!run("git clone " + shellQuote(url) + " " + shellQuote(sourceDir.string()))) {
      return 1;
    }
  } else {
    std::cout<<"Refreshing "<<name<<"...\n";
    if(!run("git -C " + shellQuote(sourceDir.string()) + " fetch --all --tags")){
      return 1;
    }
  }

  if(!ref.empty()){
    if(!run("git -C " + shellQuote(sourceDir.string()) + " checkout " + shellQuote(ref))){
      return 1;
    }
  }

  if (!fs::exists(sourceDir / "CMakeLists.txt")) {
        std::cerr << "This spell has no CMakeLists.txt yet.\n";
        return 1;
    }

  std::cout << "Conjuring build files...\n";
    if (!run("cmake -S " + shellQuote(sourceDir.string()) +
             " -B " + shellQuote(buildDir.string()) +
             " -DCMAKE_BUILD_TYPE=Release")) {
        return 1;
    }

    std::cout << "Casting build...\n";
    if (!run("cmake --build " + shellQuote(buildDir.string()) + " --parallel")) {
        return 1;
    }

    std::cout << "\nSummoned successfully.\n";
    std::cout << "Build output: " << buildDir << "\n";
    return 0;
}

int main(int argc, char* argv[]){
  if(argc < 3 || std::string(argv[1]) != "summon"){
    std::cout << "Usage: grimoire summon <git-url> [git-ref]\n";
    return 1;
  }

  return summon(argv[2], argc >= 4 ? argv[3] : "");
}
