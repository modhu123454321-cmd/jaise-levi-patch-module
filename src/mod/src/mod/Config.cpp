#include "mod/Config.h"

namespace aim_cursor {

nlohmann::json makeDefaultConfigJson() {
    return pl::config::defaultJson(ModConfig{});
}

nlohmann::json makeConfigSchemaJson() {
    return pl::config::schema(ModConfig{});
}

} // namespace aim_cursor
