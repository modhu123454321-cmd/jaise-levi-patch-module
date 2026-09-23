# Cursor Indicator LeviPack

A preload-native LeviPack mod prototype for Minecraft Bedrock.

## Goal
Create a simple visual cursor indicator style mod.

## Current Stage
Native Android `.so` packaging is working.

## Source Layout
- `main.cpp` - mod startup
- `logger` - Android log wrapper
- `config` - config skeleton

## Next Steps
- verify library loading in-game
- add config file reading
- research hook/render callback support

## Configuration

The mod creates a config file automatically on startup.

Config file path:
`/sdcard/Android/data/com.dts.freefireth/files/il2cpp_mods/cursor_indicator/config.json`

Example config:
```json
{
  "enabled": true,
  "showText": false,
  "indicatorSize": 99
}
