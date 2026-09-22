#include "config.h"
#include "logger.h"
#include "paths.h"
#include "file_utils.h"

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

    std::string baseDir = getBaseDirectory();

    logInfo("Preparing config system...");
    logInfo("Base directory: %s", baseDir.c_str());
    logInfo("Config path: %s", g_config.configPath.c_str());

        if (!fileExists(g_config.configPath)) {
            logInfo("Config file does not exist, writing default config...");
            if (!writeTextFile(g_config.configPath, getDefaultConfigText())) {
                logError("Failed to write default config file");
            }
        } else {
            logInfo("Config file already exists: %s", g_config.configPath.c_str());
        }

        std::string configText;
        if (readTextFile(g_config.configPath, configText)) {
            logInfo("Config file contents:");
            logInfo("%s", configText.c_str());
        } else {
            logError("Could not read config file after setup");
        }
    
    }

    logInfo("Config loaded");
    logInfo("  enabled=%d", g_config.enabled);
    logInfo("  showText=%d", g_config.showText);
    logInfo("  indicatorSize=%d", g_config.indicatorSize);
    logInfo("  configPath=%s", g_config.configPath.c_str());
}
