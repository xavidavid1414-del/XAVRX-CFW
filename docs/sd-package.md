# SD-card package and first-boot plan

## Current deliverable

The SD layout package is a folder-layout preview. It creates the Xavrx-owned
directories and a starter `Config/settings.ini` file. It intentionally does
not include `boot.firm`, `boot.3dsx`, bootloader payloads, or NAND changes.

The package must coexist with the existing Luma3DS installation during
development. Users must not overwrite or remove Luma boot files.

## Planned layout

```text
SD:/
├── boot.firm                 # Existing boot chain; do not replace yet
├── boot.3dsx                 # Existing homebrew entry; do not replace yet
├── README-XAVRX.txt
└── xavrx/
    ├── DM/
    ├── Splash/
    ├── Apps/
    ├── Modules/
    ├── Data/
    ├── Saves/
    ├── Config/
    │   └── settings.ini
    └── CT/
```

## START + POWER proposal

START + POWER is a proposed shortcut for a future early-boot environment.
A normal libctru homebrew application cannot intercept POWER before the
console's boot chain starts. Implementing this requires a separately developed
and validated boot-stage component, correct hardware button handling, and a
recovery path. Until then, the shortcut is documentation only.

## Safe installation behavior

The future installer should:
1. Verify the console model and supported environment.
2. Verify package integrity and available SD space.
3. Create missing Xavrx directories without deleting unrelated files.
4. Preserve existing boot files and user data.
5. Write configuration through a temporary file and atomic rename.
6. Produce a clear report and never claim that CFW boot support is installed
   until a real boot-stage implementation has been validated on hardware.

No NAND writes, boot-file replacement, or automatic Luma removal are part of
this initial package.
