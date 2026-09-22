#include "mod/Config.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace {

bool writeJson(
    const std::filesystem::path &path,
    const nlohmann::json &value
) {
    std::error_code error;

    std::filesystem::create_directories(
        path.parent_path(),
        error
    );

    if (error) {
        std::cerr << "Failed to create directory: "
                  << error.message() << '\n';
        return false;
    }

    std::ofstream stream(
        path,
        std::ios::binary | std::ios::trunc
    );

    if (!stream) {
        std::cerr << "Failed to open file: "
                  << path << '\n';
        return false;
    }

    stream << value.dump(2) << '\n';

    return stream.good();
}

} // namespace

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr
            << "Usage: levi_config_generator "
               "<output-config-dir>\n";
        return 2;
    }

    const std::filesystem::path outputDirectory = argv[1];

    if (!writeJson(
            outputDirectory / "config.json",
            aim_cursor::makeDefaultConfigJson()
        )) {
        return 1;
    }

    if (!writeJson(
            outputDirectory / "config.schema.json",
            aim_cursor::makeConfigSchemaJson()
        )) {
        return 1;
    }

    return 0;
}
