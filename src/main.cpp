#include "logger.h"
#include "config.h"
#include "paths.h"

__attribute__((constructor))
void mod_init() {
    logInfo("Cursor Indicator library loaded");

    logInfo("Base directory: %s", getBaseDirectory().c_str());
    logInfo("Config file path: %s", getConfigFilePath().c_str());

    loadConfig();

    const ModConfig& cfg = getConfig();
    logInfo("Mod initialized");
    logInfo("  enabled=%d", cfg.enabled);
    logInfo("  showText=%d", cfg.showText);
    logInfo("  indicatorSize=%d", cfg.indicatorSize);
    logInfo("  configPath=%s", cfg.configPath.c_str());
}
