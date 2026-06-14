#include <iostream>
#include <string>
#include <vector>

// header file includes
#include "builtins.h"
#include "parser.h"
#include "executor.h"

int main() {

    std::string command;
    std::vector<std::string> history;

    std::cout << "+----------------------(Message from slum shell developer)--------------------------+ \n";
    std::cout << "|                                                                                   | \n";
    std::cout << "| slum (Simple Linux Unix Machine) is a minimal Unix-like shell written in C++      | \n";
    std::cout << "| want to check out the source code:                                                | \n";
    std::cout << "| https://github.com/Wanda550/slumv1.sh                                             | \n";
    std::cout << "|                                                                                   | \n";
    std::cout << "| (Run: 'g++ main.cpp -o main')  with                                               | \n"; 
    std::cout << "|                                                                                   | \n";
    std::cout << "| -----> terminal: cd build                                                         | \n";
    std::cout << "| -----> terminal: cmake --build .                                                  | \n";
    std::cout << "| -----> terminal: './cpp_shell.exe'                                                | \n";
    std::cout << "|                                                                                   | \n";

    while (true) {

        std::cout << std::endl;
        std::cout << "+-- (user@machine) - " << "[ " << getCurrentPath() << " ] \n";
        std::cout << "+- $ ";
        
        std::getline(std::cin, command);

        history.push_back(command);

        auto tokens = parse(command);

        std::cout << std::endl;

        if (tokens.empty()) {
            continue;
        }

        if (!execute(tokens)) {
            break;
        }
    }

    return 0;
}