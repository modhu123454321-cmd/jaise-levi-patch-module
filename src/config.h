#pragma once
#include <string>

struct ModConfig {
    bool enabled = true;
    bool showText = true;
    int indicatorSize = 12;
    std::string configPath;
};

const ModConfig& getConfig();
void loadConfig();
