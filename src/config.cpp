#include "config.h"
#include "logger.h"

static ModConfig g_config{};

const ModConfig& getConfig() {
    return g_config;
}

void loadConfig() {
    g_config.enabled = true;
    g_config.showText = true;
    g_config.indicatorSize = 12;

    logInfo("Config loaded: enabled=%d, showText=%d, indicatorSize=%d",
            g_config.enabled,
            g_config.showText,
            g_config.indicatorSize);
}
