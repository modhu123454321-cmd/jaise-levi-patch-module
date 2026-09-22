#include "file_utils.h"
#include "logger.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <vector>

bool fileExists(const std::string& path) {
    struct stat info {};
    return stat(path.c_str(), &info) == 0;
}

bool ensureDirectoryExists(const std::string& path) {
    struct stat info {};
    if (stat(path.c_str(), &info) == 0) {
        if (info.st_mode & S_IFDIR) {
            logInfo("Directory already exists: %s", path.c_str());
            return true;
        }

        logError("Path exists but is not a directory: %s", path.c_str());
        return false;
    }

    if (mkdir(path.c_str(), 0755) == 0) {
        logInfo("Directory created: %s", path.c_str());
        return true;
    }

    logError("Failed to create directory: %s (errno=%d, %s)",
             path.c_str(), errno, strerror(errno));
    return false;
}

bool writeTextFile(const std::string& path, const std::string& content) {
    std::ofstream out(path);
    if (!out.is_open()) {
        logError("Failed to open file for writing: %s", path.c_str());
        return false;
    }

    out << content;
    out.close();

    if (!out) {
        logError("Failed while writing file: %s", path.c_str());
        return false;
    }

    logInfo("Wrote text file: %s", path.c_str());
    return true;
}
