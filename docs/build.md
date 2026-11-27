# Build environment

## What this build produces

The 3DS target is xavrx-diagnostic.3dsx, a user-mode Nintendo 3DS homebrew application linked against libctru. It is not a CFW, bootloader, ARM9 payload, CIA installer, or replacement for Luma3DS.

## Toolchain

- devkitARM
- libctru
- devkitPro 3DS development packages
- GNU Make

libctru is the user-mode ARM11 library used for 3DS homebrew, with devkitARM as the officially supported toolchain. See the official libctru project: https://github.com/devkitPro/libctru

## Local build

After installing devkitPro's 3DS development environment:

    export DEVKITPRO=/opt/devkitpro
    export DEVKITARM="$DEVKITPRO/devkitARM"
    make

The output is xavrx-diagnostic.3dsx.

## Portable core tests

On a host with a C compiler:

    cc -std=c11 -Wall -Wextra -Werror -Iinclude source/core.c source/config.c source/log.c tests/test_core.c -o xavrx-core-tests
    ./xavrx-core-tests

GitHub Actions runs this test separately from the 3DS toolchain build.

## Safety

Do not copy experimental files over boot-critical SD files, write to NAND, or remove the known-good CFW. The diagnostic app runs as ordinary homebrew under the existing system software. A future independent CFW requires separately researched boot-chain, ARM9/ARM11, privilege, recovery, and hardware compatibility work.
