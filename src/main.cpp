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

bool hasMakefile(const fs::path& sourceDir){
  return fs::exists(sourceDir / "Makefile") ||
    fs::exists(sourceDir / "makefile") ||
    fs::exists(sourceDir / "GNUmakefile");
}

bool buildProject(const fs::path& sourceDir, const fs::path& buildDir, fs::path& outputDir){
  if(fs::exists(sourceDir / "CMakeLists.txt")){
    std::cout<<"Detected Cmake project.\n";

    if(!run("cmake -S " + shellQuote(sourceDir.string()) +
          " -B " + shellQuote(buildDir.string()) + 
          " -DCMAKE_BUILD_TYPE=Release")) {
      return false;
    }

    if (!run("cmake --build " + shellQuote(buildDir.string()) +
             " --parallel")) {
      return false;
    }

    outputDir = buildDir;
    return true;
  }

  if (fs::exists(sourceDir / "Cargo.toml")) {
    std::cout << "Detected Cargo project.\n";

    if (!run("cargo build --release --manifest-path " +
             shellQuote((sourceDir / "Cargo.toml").string()))) {
      return false;
    }

    outputDir = sourceDir / "target" / "release";
    return true;
  }

  if (hasMakefile(sourceDir)) {
    std::cout << "Detected Makefile project.\n";

    if (!run("make -C " + shellQuote(sourceDir.string()))) {
      return false;
    }

    outputDir = sourceDir;
    return true;
  }

  std::cerr << "No supported build file found.\n";
  return false;
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

  fs::path outputDir;

if (!buildProject(sourceDir, buildDir, outputDir)) {
  return 1;
}

std::cout << "\nSummoned successfully.\n";
std::cout << "Build output: " << outputDir << "\n";
return 0;
}

int main(int argc, char* argv[]){
  if(argc < 3 || std::string(argv[1]) != "summon"){
    std::cout << "Usage: grimoire summon <git-url> [git-ref]\n";
    return 1;
  }

  return summon(argv[2], argc >= 4 ? argv[3] : "");
}
