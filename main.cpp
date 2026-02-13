#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <locale.h>
#include "./modules/colors.h"
#include <vector>
#include <algorithm>
#include <cctype>

std::vector <std::string> filesDir;

void loopPath(const std::filesystem::path& path, std::string filter, bool& logs) {
  for (const auto &entry : std::filesystem::recursive_directory_iterator(path)) {
    if (std::filesystem::is_regular_file(entry) && entry.path().extension() == filter) {
      if (logs) std::cout << Colors::CYAN << "- " << entry.path().string() << std::endl;
      filesDir.push_back(entry.path().string());
    }
  }
}

int main(int argc, char* argv[]) {
  bool logsOpc = false;
  std::filesystem::path current_path = std::filesystem::current_path();
  std::string otherFlags = "";
  std::string nameOpc = "main.exe";
  std::string code = "gcc ";
  std::string filter = ".c";

  #ifdef _WIN32
  // std::setlocale(LC_ALL, "Portuguese_Brazil.1252");
  system("@echo off");
  system("title @Beta");
  #else
  // std::setlocale(LC_ALL, "pt_BR.UTF-8");
  #endif

  if (argc < 2) {
    std::cout << Colors::RED << "* " << Colors::DEFAULT << "Bad use of params, use example:\n\n"
    << Colors::BLUE << "-path " << Colors::DEFAULT << "= Project folder for your program\n"
    << Colors::BLUE << "-flags " << Colors::DEFAULT << "= Use other configuration flags\n"
    << Colors::BLUE << "-gcc "<< Colors::DEFAULT << "or" << Colors::BLUE << " -g++" << Colors::DEFAULT << " = Build from C or C++ project application\n"
    << Colors::BLUE << "-logs " << Colors:: DEFAULT << "= View the file search flow\n"
    << Colors::BLUE << "-name " << Colors::DEFAULT << "= Inside \"YourProgram\" write the name for your program." << std::endl;
    // << Colors::BLUE << "-cbignore " << Colors::DEFAULT << "= Create a file called "<< Colors::YELLOW << "\"cbignore\"" << Colors::DEFAULT << " which will contain everything that should not be read." << std::endl;
    return 1;
  }
  for (int c = 1; c < argc; c++) { // A ordem das condições para o "code +=" afetem como sera formado o "Running"
    std::string args(argv[c]);
    std::transform(args.begin(), args.end(), args.begin(), [](unsigned char ch) { return std::tolower(ch); });
    if (args == "-path") {
      try { current_path = std::string(argv[c+1]); }
      catch(const std::exception& e) {
        // std::cerr << e.what() << '\n';
        std::cout << Colors::RED << "-path \"C:\\your\\path\\project\"" << Colors::DEFAULT;
        return 1;
      }
    };
    if (args == "-logs") logsOpc = true;
    // if (args == "-gcc") {
    //   files = "gcc ";
    //   filter = ".c";
    // }
    if (args == "-g++") {
      code = "g++ ";
      filter = ".cpp";
    }
    if (args == "-flags") {
      try { otherFlags += std::string(argv[c+1])+" "; }
      catch(const std::exception& e) {
        // std::cerr << e.what() << '\n';
        std::cout << Colors::RED << "-flags \"-example -example2\"" << Colors::DEFAULT;
        return 1;
      }
    };
    if (args == "-name") {
      try { nameOpc = std::string(argv[c+1]); }
      catch(const std::exception& e) {
        // std::cerr << e.what() << '\n';
        std::cout << Colors::RED << "-name \"YourProgram\"" << Colors::DEFAULT;
        return 1;
      }
    };
  }

  // Ordenando a formação do Running "code +="
  if (filter == ".c" && code != "gcc " || filter == ".cpp" && code != "g++ ") {
    std::cout << Colors::RED << "Parameter to filter wrongly used \"C\" and \"C++\" files" << Colors::DEFAULT;
    return 1;
  }
  if (otherFlags.length() > 1) code += otherFlags;
  if (logsOpc) std::cout << Colors::YELLOW << "Loading Files\n" << Colors::DEFAULT << std::endl;
  std::filesystem::path path = current_path; // path atual
  loopPath(path, filter, logsOpc);

  if (filesDir.size() < 1) {
    std::cout << Colors::RED << "No \"" << Colors::GRAY << filter << Colors::RED << "\" files found" << Colors::DEFAULT;
    return 1;
  }
  for (auto i : filesDir) { code += (i+" ").c_str(); }
  code += "-o "+nameOpc;
  if (logsOpc) std::cout << Colors::PURPLE << "\nRunning: " << Colors::GREEN << code << std::endl;

  // std::cout << argc << "    " << argv << Colors::RED << std::endl; // Local memory
  // std::cout << "Index 0" << filesDir[0] << Colors::DEFAULT << std::endl;
  std::filesystem::current_path(current_path);
  try {
    int err = system(code.c_str());
    if (err == 0) std::cout << Colors::DEFAULT << "Build finished." << std::endl;
    else std::cout << Colors::RED << "\nCheck the compilation" << Colors::DEFAULT << std::endl;
  } catch(const std::exception& e) {
    std::cout << Colors::DEFAULT << "Check the compilation." << std::endl;
  }
  return 0;
}