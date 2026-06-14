#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>
#include <filesystem>

void help();
std::string getCurrentPath();

void pwd();
void ls();
void cd(const std::string& path);
void touch(const std::string& path);
void cat();
void mkdir(const std::string& path);
void rm(const std::string& path);
void mv(const std::string& from, const std::string& to);
void cp(const std::string& from, const std::string& to);
void find(const std::filesystem::path& start_dir, const std::string& target);

#endif