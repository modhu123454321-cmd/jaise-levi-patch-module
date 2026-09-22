#pragma once

#include <optional>

#include "mod/Config.h"

#include <pl/Mod.hpp>

namespace aim_cursor {

class AimCursorMod {
public:
    static AimCursorMod &instance();

    AimCursorMod();

    [[nodiscard]] ll::mod::NativeMod &getSelf() const { return mSelf; }

    bool load();
    bool enable();
    bool disable();
    bool unload();

private:
    ll::mod::NativeMod &mSelf;
    ModConfig mConfig{};
    std::optional<pl::config::ConfigFile<ModConfig>> mConfigFile;

    void submitOverlay();
};

} // namespace aim_cursor
