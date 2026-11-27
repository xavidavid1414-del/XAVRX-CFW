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
- `tests/` — host-side unit tests
- `docs/` — architecture, build process, and safety notes
- `.github/workflows/` — automated build and test workflow

## Build artifact

The current 3DS target is `xavrx-diagnostic.3dsx`. No CIA or installable CFW package is produced.

See [docs/build.md](docs/build.md) for build details and [docs/architecture.md](docs/architecture.md) for the development model.


## Customization roadmap

XAVRX is planned to support animated startup splashes with optional synchronized sound, static splash fallback, custom interface themes, and optional theme music and sound effects. These are requirements, not implemented features yet. See [docs/customization.md](docs/customization.md) for the proposed design and compatibility stages.
