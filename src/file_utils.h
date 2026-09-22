#pragma once
#include <string>

bool fileExists(const std::string& path);
bool ensureDirectoryExists(const std::string& path);
bool writeTextFile(const std::string& path, const std::string& content);
