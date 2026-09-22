#include "paths.h"

std::string getBaseDirectory() {
    // Placeholder path for future runtime-specific storage.
    // This will likely need to be changed depending on loader/game environment.
    return "/sdcard/Android/data/com.mojang.minecraftpe/files/LeviMods/CursorIndicator";
}

std::string getConfigFilePath() {
    return getBaseDirectory() + "/config.json";
}
