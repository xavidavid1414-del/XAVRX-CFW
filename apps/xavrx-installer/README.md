# Xavrx Installer

Standalone Nintendo 3DS homebrew application for the Xavrx ecosystem.

## Current implementation

- Builds as a separate `.3dsx` application.
- Reads the installed-title list for SD media through libctru's AM service.
- Displays title IDs with simple UP/DOWN navigation.
- Does not write to SD or NAND, install CIA files, delete titles, or modify system data.

## Planned development

1. Read-only SD title browser (current first milestone).
2. SD file browser and CIA metadata preview.
3. CIA installation with explicit destination and confirmation, robust error handling, and cancellation.
4. Installed-title details and safe user-title management.

CIA installation and title deletion are not implemented. Do not treat this first build as a replacement for FBI yet.

## Build

From this directory, with devkitPro/devkitARM installed:

```sh
make
```

Output: `xavrx-installer.3dsx`
