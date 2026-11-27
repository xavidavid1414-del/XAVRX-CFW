# Build environment

## What this build produces

The current build produces `xavrx-diagnostic.3dsx`, a user-mode Nintendo 3DS homebrew diagnostic application linked against libctru. It is a toolchain and application smoke test. **It is not a CFW, bootloader, ARM9 payload, CIA installer, or replacement for Luma3DS.**

## Toolchain

- devkitARM
- libctru
- devkitPro 3DS development packages
- GNU Make

The GitHub Actions workflow installs the `3ds-dev` package and invokes the repository Makefile.

## Local build

After installing devkitPro's 3DS development environment:

```sh
export DEVKITPRO=/opt/devkitpro
export DEVKITARM="$DEVKITPRO/devkitARM"
make
```

The output is `xavrx-diagnostic.3dsx`.

## Safety

Do not copy experimental files over boot-critical SD files, write to NAND, or remove the known-good CFW. This diagnostic app runs as ordinary homebrew under the existing system software. A future independent CFW requires separately researched boot-chain, ARM9/ARM11, privilege, recovery, and hardware compatibility work.
