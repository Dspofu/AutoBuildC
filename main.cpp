#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <locale.h>
#include "./modules/colors.h"
#include <conio.h>
#include <vector>

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
  bool logs = false;
  std::string files = "g++ ";
  std::string filter = ".cpp";

  #ifdef _WIN32
  std::setlocale(LC_ALL, "Portuguese_Brazil.1252");
  system("@echo off");
  system("@Beta");
  #else
  std::setlocale(LC_ALL, "pt_BR.UTF-8");
  #endif

  if (argc > 4 || argc < 3) {
    std::cout << Colors::RED << "* " << Colors::DEFAULT << "Bad use of params, use example: " << Colors::BLUE << "-l " << Colors:: DEFAULT << "= Viwer files (Logs) | " << Colors::BLUE << "-gcc "<< Colors::DEFAULT << "or" << Colors::BLUE << " -g++" << Colors::DEFAULT << " = Build from C or C++ project application | " << Colors::BLUE << "-static " << Colors::DEFAULT << "= Build files in static mode for the project." << std::endl;
    return 0;
  }
  for (int c = 1; c < argc; c++) {
    // std::cout << argv[c] << std::endl;
    if (std::string(argv[c]) == "-l" || std::string(argv[c]) == "-L") logs = true;
    if (std::string(argv[c]) == "-gcc" || std::string(argv[c]) == "-GCC") files = "gcc ", filter = ".c";
    if (std::string(argv[c]) == "-g++" || std::string(argv[c]) == "-G++") files = "g++ ";
    if (std::string(argv[c]) == "-static" || std::string(argv[c]) == "-STATIC") files += "-static ";
  }
  if (logs) std::cout << "Loading" << std::endl;
  std::filesystem::path path = std::filesystem::current_path(); // path atual
  loopPath(path, filter, logs);

  if (filesDir.size() < 1) {
    if (logs) std::cout << Colors::RED << "Files not found." << Colors::DEFAULT;
    return 1;
  }
  for (auto i : filesDir) { files += (i+" ").c_str(); }
  files += "-o main.exe";
  if (logs) std::cout << Colors::PURPLE << "Code: " << Colors::GREEN << files;

  // std::cout << argc << "    " << argv << Colors::RED << std::endl; // Local memory
  // std::cout << "Index 0" << filesDir[0] << Colors::DEFAULT << std::endl;
  std::cout << Colors::DEFAULT;
  return 0;
}