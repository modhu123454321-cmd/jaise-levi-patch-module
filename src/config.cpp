#include "config.h"
#include "logger.h"
#include "paths.h"

static ModConfig g_config{};

const ModConfig& getConfig() {
    return g_config;
}

std::string getDefaultConfigText() {
    return R"({
  "enabled": true,
  "showText": true,
  "indicatorSize": 12
})";
}

void logDefaultConfigPreview() {
    std::string text = getDefaultConfigText();
    logInfo("Default config preview:");
    logInfo("%s", text.c_str());
}

void loadConfig() {
    g_config.enabled = true;
    g_config.showText = true;
    g_config.indicatorSize = 12;
    g_config.configPath = getConfigFilePath();

    logInfo("Config loaded");
    logInfo("  enabled=%d", g_config.enabled);
    logInfo("  showText=%d", g_config.showText);
    logInfo("  indicatorSize=%d", g_config.indicatorSize);
    logInfo("  configPath=%s", g_config.configPath.c_str());
}
