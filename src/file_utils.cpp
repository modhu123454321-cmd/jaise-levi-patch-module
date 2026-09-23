#include "file_utils.h"

#include <cctype>
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

std::string readTextFile(const std::string& path, bool binary) {
    std::ios::openmode mode = std::ios::in;
    if (binary) {
        mode |= std::ios::binary;
    }

    std::ifstream file(path, mode);
    if (!file.is_open()) {
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
