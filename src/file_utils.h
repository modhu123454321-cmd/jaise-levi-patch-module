#pragma once

#include <string>

std::string trim(const std::string& input);
bool readTextFile(const std::string& path, std::string& outText, bool binary = false);
