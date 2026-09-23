#include "config.h"
#include "file_utils.h"
#include "logger.h"
#include "paths.h"

#include <cctype>

static ModConfig g_config;

static int clampInt(int value, int minValue, int maxValue) {
    if (value < minValue) {
        return minValue;
    }
    if (value > maxValue) {
        return maxValue;
    }
    return value;
}

static bool parseBoolValue(const std::string& text, const std::string& key, bool currentValue) {
    const std::string pattern = "\"" + key + "\"";
    size_t pos = text.find(pattern);
    if (pos == std::string::npos) {
        return currentValue;
    }

    pos = text.find(':', pos);
    if (pos == std::string::npos) {
        return currentValue;
    }

    ++pos;
    while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos]))) {
        ++pos;
    }

    if (text.compare(pos, 4, "true") == 0) {
        return true;
    }
    if (text.compare(pos, 5, "false") == 0) {
        return false;
    }

    return currentValue;
}

static int parseIntValue(const std::string& text, const std::string& key, int currentValue) {
    const std::string pattern = "\"" + key + "\"";
    size_t pos = text.find(pattern);
    if (pos == std::string::npos) {
        return currentValue;
    }

    pos = text.find(':', pos);
    if (pos == std::string::npos) {
        return currentValue;
    }

    ++pos;
    while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos]))) {
        ++pos;
    }

    bool negative = false;
    if (pos < text.size() && text[pos] == '-') {
        negative = true;
        ++pos;
    }

    if (pos >= text.size() || !std::isdigit(static_cast<unsigned char>(text[pos]))) {
        return currentValue;
    }

    int value = 0;
    while (pos < text.size() && std::isdigit(static_cast<unsigned char>(text[pos]))) {
        value = value * 10 + (text[pos] - '0');
        ++pos;
    }

    return negative ? -value : value;
}

const ModConfig& getConfig() {
    return g_config;
}

std::string getDefaultConfigText() {
    return
        "{\n"
        "  \"enabled\": true,\n"
        "  \"showText\": true,\n"
        "  \"indicatorSize\": 48\n"
        "}\n";
}

void logDefaultConfigPreview() {
    logInfo("Default config preview:");
    logInfo("%s", getDefaultConfigText().c_str());
}

void loadConfig() {
    const std::string baseDir = getBaseDirectory();
    g_config.configPath = getConfigFilePath();

    logInfo("Loading config...");
    logInfo("Base dir: %s", baseDir.c_str());
    logInfo("Config path: %s", g_config.configPath.c_str());

    if (!ensureDirectoriesExist(baseDir)) {
        logError("Failed to ensure config directory exists: %s", baseDir.c_str());
        return;
    }

    if (!fileExists(g_config.configPath)) {
        logInfo("Config file does not exist, writing default config...");
        if (!writeTextFile(g_config.configPath, getDefaultConfigText())) {
            logError("Failed to write default config file");
            return;
        }
    } else {
        logInfo("Config file already exists: %s", g_config.configPath.c_str());
    }

    std::string configText;
    if (readTextFile(g_config.configPath, configText)) {
        logInfo("Config file contents:");
        logInfo("%s", configText.c_str());

        g_config.enabled = parseBoolValue(configText, "enabled", g_config.enabled);
        g_config.showText = parseBoolValue(configText, "showText", g_config.showText);

        int parsedIndicatorSize = parseIntValue(configText, "indicatorSize", g_config.indicatorSize);
        g_config.indicatorSize = clampInt(parsedIndicatorSize, 8, 256);

        if (g_config.indicatorSize != parsedIndicatorSize) {
            logInfo("indicatorSize out of range, clamped from %d to %d",
                    parsedIndicatorSize, g_config.indicatorSize);
        }

        logInfo("Parsed config values:");
        logInfo("  enabled=%d", g_config.enabled);
        logInfo("  showText=%d", g_config.showText);
        logInfo("  indicatorSize=%d", g_config.indicatorSize);
    } else {
        logError("Could not read config file after setup");
    }
}
