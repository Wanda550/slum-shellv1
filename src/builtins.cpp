#include "builtins.h"
#include <exception>
#include <iostream>
#include <string>
#include <filesystem> // filesystem library
#include <fstream>    // For file creation and writing

// help function
void help() {
  std::cout << "Available commands: \n";
  std::cout << "   help   - show available commands \n";
  std::cout << "   pwd    - print working directory \n";
  std::cout << "   ls     - list files and folders \n";
  std::cout << "   cd     - change directory \n";
  std::cout << "   touch  - create file \n";
  std::cout << "   mkdir  - create directory \n";
  std::cout << "   rm     - remove file or directory \n";
  std::cout << "   exit   - exit shell \n";
};

// current path function
std::string getCurrentPath() {
  return std::filesystem::current_path().string();
};

// print working directory function
void pwd() {
  try {
    std::cout << std::filesystem::current_path().string() << '\n';
  } catch (const std::exception& e)  {
    std::cerr << "pwd: " << e.what() << "\n";
  };
};

// list function
void ls() {
  try {
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
      std::cout << entry.path().string() << '\n';
    };
  } catch (const std::exception& e) {
    std::cerr << "ls: " << e.what() << "\n";
  };
};

// change directory function
void cd(const std::string& path) {
  try {
      std::filesystem::current_path(path);
  } catch(const std::filesystem::filesystem_error& e) {
      std::cerr << "cd: " << e.what() << '\n';
  };
}

// make a file function
void touch(const std::string& path) {
  try {
    // Check if file already exists
    if (std::filesystem::exists(path)) {
      std::cout << "touch: file already exists. \n";
      return;
    };
      
    // Create an empty file using ofstream
    std::ofstream file(path);

    if (!file) {
      std::cout << "touch: failed to create file.";
      return;
    };

    std::cout << "file created: " << path << "\n";

  } catch (const std::filesystem::filesystem_error& e) {
      std::cerr << "touch: " << e.what() << "\n";
  };
};

// make directory function
void mkdir(const std::string& path) {
  try {
    if(std::filesystem::exists(path)) {
      std::cout << "mkdir: " << path << "'already exits \n";
      return;
    };

    if (std::filesystem::create_directory(path)) {
        std::cout << "directory created: " << path << "\n";
    } else {
        std::cout << "mkdir: failed to create file. \n";
    };
  } catch (const std::exception& e) {
      std::cerr << "mkdir: " << e.what() << "\n";
  };
}

// remove function
void rm(const std::string& path) {
  try {
    if (!std::filesystem::exists(path)){
      std::cout << "rm: could not remove '" << path << "': no such file or directory \n";
      return;
    };

    if (std::filesystem::remove(path)) {
        std::cout << "removed: " << path << "\n";
    } else {
        std::cout << "rm: can not removed. \n";
    }
  } catch (const std::exception& e) {
      std::cerr << "rm: " << e.what() << "\n";
  }
}

// move file function
void mv(const std::string& from, const std::string& to) {
  try {
    if (!std::filesystem::exists(from)){
      std::cout << "mv: could not move '" << from << "': no such file or directory \n";
      return;
    };

    std::filesystem::rename(from, to);

    std::cout << "moved from: " << from << '\n';
    std::cout << "moved to: " << to << '\n';

  } catch (const std::exception& e) {
      std::cerr << "mv: " << e.what() << "\n";
  }
}

// copy file function
void cp(const std::string& from, const std::string& to) {
  try {
    if (!std::filesystem::exists(from)){
      std::cout << "cp: could not copy '" << from << "': no such file \n";
      return;
    };

    if (std::filesystem::copy_file(from, to)) {
        std::cout << "copied from: " << from << "\n";
        std::cout << "copied to: " << to << "\n";
    } else {
        std::cout << "cp: can not copy. \n";
    }
  } catch (const std::exception& e) {
      std::cerr << "cp: " << e.what() << "\n";
  }
}

// find file or directory function
void find(const std::filesystem::path& start_dir, const std::string& target) {
    if (!std::filesystem::exists(start_dir)) {
        std::cout << "find: '" << start_dir.string() << "' does not exist.\n";
        return;
    }

    if (!std::filesystem::is_directory(start_dir)) {
        std::cout << "find: '" << start_dir.string() << "' is not a directory.\n";
        return;
    }

    bool found = false;
    std::error_code ec;

    std::filesystem::recursive_directory_iterator it( start_dir, std::filesystem::directory_options::skip_permission_denied,ec);

    std::filesystem::recursive_directory_iterator end;

    while (it != end) {

        if (ec) {
            ec.clear();
            it.increment(ec);
            continue;
        }

        if (it->path().filename() == target) {
            std::cout << "Found: " << it->path().string() << '\n';
            found = true;
        }

        it.increment(ec);
    };

    if (!found) {
        std::cout << "find: '" << target << "' not found.\n";
    };
}