#pragma once
#include <string>

struct ModConfig {
    bool enabled = true;
    bool showText = true;
    int indicatorSize = 48;
    std::string configPath;
};

const ModConfig& getConfig();
std::string getDefaultConfigText();
void logDefaultConfigPreview();
void loadConfig();
