#include "config.h"
#include "logger.h"
#include "paths.h"
#include "utils.h"
#include <cmath.h>

__attribute__((constructor))
void mod_init() {
    logInfo("Cursor Indicator library loaded");

    logInfo("Base directory: %s", getBaseDirectory().c_str());
    logInfo("Config file path: %s", getConfigFilePath().c_str());

    loadConfig();

    const ModConfig& cfg = getConfig();
    if (!cfg.enabled) {
        logInfo("Mod is disabled in config, skipping feature setup");
        return;
    }

    logInfo("Mod is enabled, feature setup can continue");

    logInfo("Mod initialized:");
    logInfo("  enabled=%d", cfg.enabled);
    logInfo("  showText=%d", cfg.showText);
    logInfo("  indicatorSize=%d", cfg.indicatorSize);
    logInfo("  configPath=%s", cfg.configPath.c_str());
}
