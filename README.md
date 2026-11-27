# XAVRX CFW

A lightweight, independently developed custom-firmware project targeting the **New Nintendo 2DS XL**.

## Current status

**Development foundation — not bootable CFW yet.**

The repository currently contains:
- A libctru-based diagnostic homebrew application that builds as `xavrx-diagnostic.3dsx`.
- A small portable core state machine with host-side unit tests.
- A GitHub Actions workflow for the 3DS application build and core tests.
- Architecture and build documentation.

The diagnostic application runs as ordinary homebrew under the existing system software. It is not an ARM9 payload, bootloader, CIA installer, or replacement for Luma3DS.

## Target and goals

- Console: New Nintendo 2DS XL
- Reference system version: 11.17.0-50U
- Development family: Nintendo 3DS / ARM11
- Storage goal: under **10 MB** for XAVRX-owned microSD files, where technically feasible. This is a target, not a measured result.

## Safety boundary

XAVRX is intended to become an independent CFW environment rather than a theme or fork. Early development uses the established boot chain already present on the console to launch ordinary test applications. Do not remove Luma3DS, modify boot-critical files, or write to NAND while XAVRX is experimental. A future boot-chain implementation requires separate research, a tested recovery path, and real hardware validation.

## Repository layout

- `include/xavrx/` — public core interfaces
- `source/` — 3DS application and portable core implementation
- `apps/xavrx-installer/` — standalone Xavrx Installer homebrew app
- `distribution/` — safe SD-card folder-layout package (not bootable firmware)
- `scripts/package-sd.sh` — creates the SD layout ZIP
- `tests/` — host-side unit tests
- `docs/` — architecture, build process, and safety notes
- `.github/workflows/` — automated build and test workflow

## Build artifact

The repository builds `xavrx-diagnostic.3dsx` and a separate `apps/xavrx-installer/xavrx-installer.3dsx`. The installer is currently a read-only SD title browser; CIA installation and title deletion are not implemented. No CIA or installable CFW package is produced. A separate SD-layout ZIP creates only Xavrx data folders and a settings template; it does not install boot firmware.

See [docs/build.md](docs/build.md) for build details and [docs/architecture.md](docs/architecture.md) for the development model.


## Customization roadmap

XAVRX is planned to support animated startup splashes with optional synchronized sound, static splash fallback, custom interface themes, and optional theme music and sound effects. These are requirements, not implemented features yet. See [docs/customization.md](docs/customization.md) for the proposed design and compatibility stages.
