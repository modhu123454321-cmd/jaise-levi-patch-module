#pragma once

#include <string>

std::string trim(const std::string& input);

bool fileExists(const std::string& path);
bool ensureDirectoriesExist(const std::string& path);

bool readTextFile(const std::string& path, std::string& outText, bool binary = false);
bool writeTextFile(const std::string& path, const std::string& text, bool binary = false);
