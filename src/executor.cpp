#include "executor.h"
#include "builtins.h"
#include <iostream>
#include <string>

bool execute(const std::vector<std::string>& tokens) {

    std::string cmd = tokens[0];

    if (cmd == "help") {
        help();
    } else if (cmd == "pwd") {
        pwd();
    } else if (cmd == "ls") {
        ls();
    } else if (cmd == "cd") {
        if (tokens.size() > 1) {
            cd(tokens[1]);
        }
    } else if (cmd == "touch") {
        if (tokens.size() > 1) {
            touch(tokens[1]);
        }
    } else if (cmd == "mkdir") {
        if (tokens.size() > 1) {
            mkdir(tokens[1]);
        }
    } else if (cmd == "rm") {
        if (tokens.size() > 1) {
            rm(tokens[1]);
        }
    } else if (cmd == "mv") {
        if (tokens.size() > 2) {
            mv(tokens[1], tokens[2]);
        }
    } else if (cmd == "cp") {
        if (tokens.size() > 2) {
            cp(tokens[1], tokens[2]);
        }
    } else if ( cmd == "find") {
        if (tokens.size() > 2) {
            find(tokens[1], tokens[2]);
        }
    } else if (cmd == "exit") {
        return false;
    } else {
        std::cerr << cmd << ": command not found\n";
    }

    return true;
}