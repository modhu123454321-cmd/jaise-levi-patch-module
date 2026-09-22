#include "logger.h"
#include "config.h"

__attribute__((constructor))
void mod_init() {
    logInfo("Cursor Indicator library loaded");
    loadConfig();

    const ModConfig& cfg = getConfig();
    logInfo("Mod initialized. enabled=%d, showText=%d, indicatorSize=%d",
            cfg.enabled,
            cfg.showText,
            cfg.indicatorSize);
}
