#include "file_utils.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>

std::string trim(const std::string& input) {
    size_t start = 0;
    while (start < input.size() &&
           std::isspace(static_cast<unsigned char>(input[start]))) {
        ++start;
    }

    size_t end = input.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(input[end - 1]))) {
        --end;
    }

    return input.substr(start, end - start);
}

bool fileExists(const std::string& path) {
    std::error_code ec;
    return std::filesystem::exists(path, ec) &&
           std::filesystem::is_regular_file(path, ec);
}

bool ensureDirectoriesExist(const std::string& path) {
    std::error_code ec;

    if (path.empty()) {
        return false;
    }

    if (std::filesystem::exists(path, ec)) {
        return std::filesystem::is_directory(path, ec);
    }

    return std::filesystem::create_directories(path, ec);
}

bool readTextFile(const std::string& path, std::string& outText, bool binary) {
    std::ios::openmode mode = std::ios::in;
    if (binary) {
        mode |= std::ios::binary;
    }

    std::ifstream file(path, mode);
    if (!file.is_open()) {
        outText.clear();
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    outText = buffer.str();
    return true;
}

bool writeTextFile(const std::string& path, const std::string& text, bool binary) {
    std::ios::openmode mode = std::ios::out | std::ios::trunc;
    if (binary) {
        mode |= std::ios::binary;
    }

    std::ofstream file(path, mode);
    if (!file.is_open()) {
        return false;
    }

    file << text;
    return file.good();
}
