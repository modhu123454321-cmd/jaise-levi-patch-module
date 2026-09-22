#pragma once
#include <string>

bool fileExists(const std::string& path);
bool ensureDirectoryExists(const std::string& path);
bool writeTextFile(const std::string& path, const std::string& content);
bool ensureDirectoriesExist(const std::string& path);
bool readTextFile(const std::string& path, std::string& outContent);
