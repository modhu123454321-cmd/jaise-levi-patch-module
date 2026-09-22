#include "mod/MyMod.h"

#include <filesystem>
#include <vector>

#include <pl/Mod.hpp>
#include <pl/ModMenu.hpp>

namespace aim_cursor {

AimCursorMod &AimCursorMod::instance() {
    static AimCursorMod value;
    return value;
}

AimCursorMod::AimCursorMod() : mSelf(*ll::mod::NativeMod::current()) {}

bool AimCursorMod::load() {
    auto &self = getSelf();
    std::error_code ec;

    std::filesystem::create_directories(self.getDataDir(), ec);
    std::filesystem::create_directories(self.getConfigDir(), ec);

    if (ec) {
        self.getLogger().error("Failed to create directories: {}", ec.message());
        return false;
    }

    mConfigFile.emplace();
    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load typed config");
        return false;
    }

    mConfig = mConfigFile->value();
    return true;
}

bool AimCursorMod::enable() {
    auto &self = getSelf();

    if (!mConfig.enabled) {
        self.getLogger().info("Aim Cursor disabled by config");
        return true;
    }

    const bool moduleOk = pl::modmenu::ModuleBuilder("aim_cursor.hud", "Aim Cursor HUD")
                              .modId(self.getId())
                              .description("Visual-only crosshair prototype; no targeting or movement.")
                              .defaultEnabled(true)
                              .registerModule();

    if (!moduleOk) {
        self.getLogger().error("Failed to register HUD module");
        return false;
    }

    submitOverlay();
    return true;
}

bool AimCursorMod::disable() {
    pl::modmenu::unregisterModule("aim_cursor.hud");
    return true;
}

bool AimCursorMod::unload() {
    pl::modmenu::unregisterModule("aim_cursor.hud");
    mConfigFile.reset();
    return true;
}

void AimCursorMod::submitOverlay() {
    std::vector<pl::modmenu::DrawCommand> commands = {
        {
            .type = pl::modmenu::DrawCommandType::Text,
            .x = mConfig.x,
            .y = mConfig.y,
            .w = 24.0f,
            .h = 24.0f,
            .fontId = "default",
            .text = "+",
        },
    };

    pl::modmenu::submitDrawCommands("aim_cursor.hud", commands);
}

} // namespace aim_cursor
