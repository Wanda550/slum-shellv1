#include "parser.h"
#include <sstream>

std::vector<std::string> parse(const std::string& command) {

    std::stringstream ss(command);
    std::string token;

    std::vector<std::string> tokens;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
};