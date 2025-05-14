#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <locale.h>
#include "./modules/colors.h"
#include <conio.h>
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
  bool staticOpc = false;
  std::string nameOpc = "main.exe";
  std::string code = "gcc ";
  std::string filter = ".c";

  #ifdef _WIN32
  std::setlocale(LC_ALL, "Portuguese_Brazil.1252");
  system("@echo off");
  system("title @Beta");
  #else
  std::setlocale(LC_ALL, "pt_BR.UTF-8");
  #endif

  if (argc > 6 || argc < 2) {
    std::cout << Colors::RED << "* " << Colors::DEFAULT << "Bad use of params, use example:\n\n" << Colors::BLUE << "-l " << Colors:: DEFAULT << "= Viwer files (Logs)\n" << Colors::BLUE << "-gcc "<< Colors::DEFAULT << "or" << Colors::BLUE << " -g++" << Colors::DEFAULT << " = Build from C or C++ project application\n" << Colors::BLUE << "-static " << Colors::DEFAULT << "= Build files in static mode for the project\n" << Colors::BLUE << "-name " << Colors::DEFAULT << "Inside \"YourProgram.exe\" write the name for your program." << std::endl;
    return 1;
  }
  for (int c = 1; c < argc; c++) {
    std::string args(argv[c]);
    std::transform(args.begin(), args.end(), args.begin(), [](unsigned char ch) { return std::tolower(ch); });
    if (args == "-l") logsOpc = true;
    // if (args == "-gcc") {
    //   files = "gcc ";
    //   filter = ".c";
    // }
    if (args == "-g++") {
      code = "g++ ";
      filter = ".cpp";
    }
    if (args == "-static") staticOpc = true;
    if (args == "-name") {
      nameOpc = std::string(argv[c+1]);
      if (nameOpc.substr(nameOpc.length()-4) != ".exe") {
        std::cout << Colors::RED << "-name \"YourProgram.exe\"" << Colors::DEFAULT;
        return 1;
      }
    };
  }
  if (filter == ".c" && code != "gcc " || filter == ".cpp" && code != "g++ ") {
    std::cout << Colors::RED << "Parameter to filter wrongly used \"C\" and \"C++\" files" << Colors::DEFAULT;
    return 1;
  }
  if (staticOpc) code += "-static ";
  if (logsOpc) std::cout << Colors::YELLOW << "Loading Files\n" << Colors::DEFAULT << std::endl;
  std::filesystem::path path = std::filesystem::current_path(); // path atual
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
  system(code.c_str());
  std::cout << Colors::DEFAULT << "Build finished.";
  return 0;
}