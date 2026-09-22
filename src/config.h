#pragma once

struct ModConfig {
    bool enabled = true;
    bool showText = true;
    int indicatorSize = 12;
};

const ModConfig& getConfig();
void loadConfig();
