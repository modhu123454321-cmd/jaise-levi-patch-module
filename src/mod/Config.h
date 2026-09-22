#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace aim_cursor {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    float x = 960.0f;
    float y = 540.0f;
    std::string color = "#FFFFFF";
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace aim_cursor

template <> struct pl::config::Schema<aim_cursor::ModConfig> {
    static constexpr std::string_view title = "Aim Cursor Config";
    static constexpr std::string_view description = "Visual-only HUD prototype.";
    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};
        if (name == "enabled")
            return {.title = "Enabled"};
        if (name == "x")
            return {.title = "HUD X"};
        if (name == "y")
            return {.title = "HUD Y"};
        if (name == "color")
            return {.title = "Color"};
        return {};
    }
};
