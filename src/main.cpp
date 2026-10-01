#include <cstdlib>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void printLogo(){
  std::cout << "\033[0;37m ▄█▀▀▀▀▀█  \033[0;90;47m░\033[0;37m█▀▀▀▀█▄   ▀\033[0;90;47m░\033[0;37m█▀ ██▄▀▀▀█▄▀▀▀█▄    ▄█▀▀▀█▄  ▀\033[0;90;47m░\033[0;37m█▀  \033[0;90;47m░\033[0;37m█▀▀▀▀█▄    ▄\033[0;90;47m░\033[0;37m▀▀▀▀█\033[0m\n";
  std::cout << "\033[0;37m██ \033[0;31m▄\033[0;91;41m▄ \033[0;31m█▄▄\033[0;37m  ██ \033[0;31m█\033[0;91;41m▄\033[0;31m▄\033[0;37m ██   ██   ██    █    ██  ██ \033[0;31m█\033[0;31;41m \033[0;31m▄\033[0;37m ██  ██   ██ \033[0;31m█\033[0;91;41m▄\033[0;31m▄\033[0;37m ██  \033[0;90;47m░ \033[0;37m \033[0;31m▄\033[0;91;41m▄▄\033[0;31m▄▄\033[0m\n";
  std::cout << "\033[0;97;47m░░\033[0;37m \033[0;31m██\033[0;37m \033[0;97m▄▄▄\033[0;37m  \033[0;97;47m░░\033[0;37m \033[0;97;41m \033[0;91;41m▓\033[0;31m█\033[0;37m \033[0;97;47m░░\033[0;37m   \033[0;97;47m░░\033[0;37m   \033[0;97;47m░░\033[0;37m    \033[0;97;47m░\033[0;37m    \033[0;97;47m░░\033[0;37m  \033[0;97;47m░░\033[0;37m \033[0;31m█\033[0;91;41m▓\033[0;31m█\033[0;37m \033[0;97;47m░░\033[0;37m  \033[0;97;47m░░\033[0;37m   \033[0;97;47m░░\033[0;37m \033[0;97;41m \033[0;91;41m▓\033[0;31m█\033[0;37m \033[0;97;47m░░\033[0;37m  \033[0;97;47m░░\033[0;37m \033[0;97;41m \033[0;91;41m▓▒░▒\033[0m\n";
  std::cout << "\033[0;97;47m▒▒\033[0;37m \033[0;31m█▀\033[0;37m  \033[0;97;47m▒▒\033[0;37m  \033[0;97;47m▒▒\033[0;37m \033[0;31m█\033[0;91;41m▀\033[0;31m▀\033[0;37m \033[0;97;47m▒▒\033[0;37m   \033[0;97;47m▒▒\033[0;37m   \033[0;97;47m▒▒\033[0;37m \033[0;31m░\033[0;37m  \033[0;97;47m▒\033[0;37m \033[0;31m░\033[0;37m  \033[0;97;47m▒▒\033[0;37m  \033[0;97;47m▒▒\033[0;37m \033[0;31m█▀\033[0;37m  \033[0;97;47m▒▒\033[0;37m  \033[0;97;47m▒▒\033[0;37m   \033[0;97;47m▒▒\033[0;37m \033[0;31m█\033[0;91;41m▀\033[0;31m▀\033[0;37m \033[0;97;47m▒▒\033[0;37m  \033[0;97;47m▒▒\033[0;37m▀▀ \033[0;91;41m▒░\033[0;31m█\033[0m\n";
  std::cout << "\033[0;97;47m▓▓\033[0;37m     \033[0;97;47m▓▓\033[0;37m  \033[0;97;47m▓▓\033[0;97m▄▄▄▄\033[0;97;47m▓\033[0;97m▀\033[0;37m    \033[0;97;47m▓▓\033[0;37m   \033[0;97;47m▓▓\033[0;37m \033[0;31m▒\033[0;37m  \033[0;97;47m▓\033[0;37m \033[0;31m▒\033[0;37m  \033[0;97;47m▓▓\033[0;37m  \033[0;97;47m▓▓\033[0;37m     \033[0;97;47m▓▓\033[0;37m  \033[0;97;47m▓▓\033[0;37m   \033[0;97;47m▓▓\033[0;97m▄▄▄▄\033[0;97;47m▓\033[0;97m▀\033[0;37m   \033[0;97;47m▓▓\033[0;37m \033[0;31m█\033[0;91;41m▓▒░\033[0;31m█\033[0m\n";
  std::cout << "\033[0;90m▄▄\033[0;37m     \033[0;90m▄▄\033[0;37m  \033[0;90m▄▄\033[0;37m \033[0;31m▄▄▄\033[0;37m \033[0;90m▄\033[0;37m    \033[0;90m▄▄\033[0;37m   \033[0;90m▄▄\033[0;37m \033[0;31m█▄\033[0;37m   \033[0;31m▓\033[0;37m  \033[0;90m▄▄\033[0;37m  \033[0;90m▄▄\033[0;37m     \033[0;90m▄▄\033[0;37m  \033[0;90m▄▄\033[0;37m   \033[0;90m▄▄\033[0;37m \033[0;31m▄▄▄\033[0;37m \033[0;90m▄\033[0;37m   \033[0;90m▄▄\033[0;37m \033[0;31m▀\033[0;91;41m▀▀\033[0;31m▀▀\033[0m\n";
  std::cout << "\033[0;90m▀\033[0;90;47m▓\033[0;90m▄▄▄▄▄\033[0;90;47m▓▓\033[0;37m \033[0;90m▄\033[0;90;47m▓▓\033[0;90m▄\033[0;37m   \033[0;90m▄\033[0;90;47m▓▓\033[0;90m▄\033[0;37m \033[0;90m▄\033[0;90;47m▓▓\033[0;90m▄\033[0;37m \033[0;90m▄██▄\033[0;31m▀\033[0;91;41m▄\033[0;31m▄▄██\033[0;37m \033[0;90m▄██▄\033[0;37m  \033[0;90m▀█▄▄▄\033[0;90;47m▓\033[0;90m▀\033[0;37m  \033[0;90m▄\033[0;90;47m▓▓\033[0;90m▄\033[0;37m \033[0;90m▄\033[0;90;47m▓▓\033[0;90m▄\033[0;37m   \033[0;90m▄\033[0;90;47m▓▓\033[0;90m▄\033[0;37m  \033[0;90m▀\033[0;90;47m▓\033[0;90m▄▄▄▄\033[0;90;47m▓\033[0m\n\n";
}

fs::path grimoireRoot(){
  return fs::path(std::getenv("HOME")) / ".grimoire";
}

bool isSafePackageName(const std::string& name){
  return !name.empty() && name != "." && name != ".." &&
    name.find('/') == std::string::npos && name.find('\\') == std::string::npos;
}

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

bool commandExists(const std::string& command){
  return std::system(("command -v " + command + " > /dev/null 2>&1").c_str()) == 0;
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

bool writeSpellState(const fs::path& stateFile, const std::string& name,
                     const std::string& url, const std::string& ref,
                     const fs::path& outputDir){
  std::ofstream state(stateFile);
  if(!state){
    std::cerr << "Could not record summoned package state.\n";
    return false;
  }

  state << "name=" << name << "\n";
  state << "source=" << url << "\n";
  state << "ref=" << (ref.empty() ? "default branch" : ref) << "\n";
  state << "output=" << outputDir << "\n";
  return true;
}

fs::path findReadme(const fs::path& sourceDir){
  for(const char* fileName : {"README.md", "README.markdown", "README"}){
    const fs::path readme = sourceDir / fileName;
    if(fs::exists(readme)) return readme;
  }
  return {};
}

int scryDetails(const std::string& name){
  if(!isSafePackageName(name)){
    std::cerr << "Invalid package name.\n";
    return 1;
  }

  const fs::path stateFile = grimoireRoot() / "packages" / name / "state.txt";
  std::ifstream state(stateFile);
  if(!state){
    std::cerr << "No summoned package named " << name << ".\n";
    return 1;
  }

  std::cout << "Scrying " << name << ":\n";
  std::string line;
  while(std::getline(state, line)){
    const auto separator = line.find('=');
    if(separator == std::string::npos) continue;

    std::string label = line.substr(0, separator);
    if(!label.empty()) {
      label[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(label[0])));
    }
    std::cout << label << ": " << line.substr(separator + 1) << "\n";
  }
  return 0;
}

int scry(const std::string& name){
  if(!isSafePackageName(name)){
    std::cerr << "Invalid package name.\n";
    return 1;
  }

  const fs::path packageDir = grimoireRoot() / "packages" / name;
  if(!fs::exists(packageDir)){
    std::cerr << "No summoned package named " << name << ".\n";
    return 1;
  }

  const fs::path readme = findReadme(packageDir / "source");
  if(readme.empty()){
    std::cerr << "No README found for " << name << ".\n";
    return 1;
  }

  if(commandExists("glow")){
    return run("glow -p " + shellQuote(readme.string())) ? 0 : 1;
  }

  std::cerr << "Glow is not installed; opening the raw README instead.\n";
  return run("less " + shellQuote(readme.string())) ? 0 : 1;
}

int banish(const std::string& name){
  if(!isSafePackageName(name)){
    std::cerr << "Invalid package name.\n";
    return 1;
  }

  const fs::path packageDir = grimoireRoot() / "packages" / name;
  std::error_code error;
  bool found = fs::exists(packageDir);

  fs::remove_all(packageDir, error);
  if(error){
    std::cerr << "Could not banish package: " << error.message() << "\n";
    return 1;
  }

  if(!found){
    std::cerr << "No summoned package named " << name << ".\n";
    return 1;
  }

  std::cout << "Banished " << name << ".\n";
  return 0;
}

int summon(const std::string& url, const std::string& ref){
  const std::string name = packageNameFromUrl(url);
  const fs::path root = grimoireRoot();
  const fs::path packageDir = root / "packages" / name;
  const fs::path sourceDir = packageDir / "source";
  const fs::path buildDir = packageDir / "build";
  const fs::path stateFile = packageDir / "state.txt";

  fs::create_directories(packageDir);
  
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

  if(!writeSpellState(stateFile, name, url, ref, outputDir)){
    return 1;
  }

  std::cout << "\nSummoned successfully.\n";
  std::cout << "Build output: " << outputDir << "\n";
  return 0;
}

int main(int argc, char* argv[]){
  if(argc < 2){
    printLogo();
    std::cout << "Usage:\n"
              << "  grimoire summon <git-url> [git-ref]\n"
              << "  grimoire scry <package>\n"
              << "  grimoire scry <package> --details\n"
              << "  grimoire banish <package>\n";
    return 1;
  }

  const std::string command = argv[1];
  if(command == "summon" && argc >= 3){
    return summon(argv[2], argc >= 4 ? argv[3] : "");
  }

  if(command == "scry" && argc == 3){
    return scry(argv[2]);
  }

  if(command == "scry" && argc == 4 && std::string(argv[3]) == "--details"){
    return scryDetails(argv[2]);
  }

  if(command == "banish" && argc == 3){
    return banish(argv[2]);
  }

  std::cerr << "Invalid command or arguments. Run grimoire with no arguments for help.\n";
  return 1;
}
