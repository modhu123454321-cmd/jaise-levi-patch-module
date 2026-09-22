# Aim Cursor Mob Indicator

Visual-only HUD prototype for LeviLauncher.

This project packages a native mod that draws a crosshair-style `+` using LeviLauncher's public Mod Menu overlay API. It does not move the camera, target entities, or modify game state.

## Build

Use a PC with Android SDK/NDK, CMake, Ninja, and PowerShell:

```powershell
./scripts/package.ps1 -Abi arm64-v8a
