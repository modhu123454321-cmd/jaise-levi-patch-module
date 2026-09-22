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
    } else {
        logError("Could not read config file after setup");
    }
}
