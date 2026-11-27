# XAVRX CFW

A lightweight, independently developed custom-firmware project for the **New Nintendo 2DS XL**.

## Target device

- Console: New Nintendo 2DS XL
- Reference system version: 11.17.0-50U
- Development target: ARM11 / Nintendo 3DS family
- Storage goal: keep XAVRX-owned files under **10 MB**, where technically feasible

## Project status

**Version 0.1 — architecture and safe development foundation**

This repository starts with project documentation and a modular source layout. It is not yet bootable firmware.

## Important boot-chain note

XAVRX is intended to become an independent CFW environment, not a Luma3DS theme or fork. The project will initially rely on an already-installed, established boot chain such as boot9strap to launch development builds. Replacing the boot chain itself is a separate, high-risk task and will not be attempted until recovery and compatibility are proven.

Do not remove Luma3DS or alter boot-critical files while XAVRX is experimental. No NAND writing or installation is part of Version 0.1.

## Planned modules

- **boot/** — entry point and startup handoff
- **core/** — minimal runtime and system services
- **modules/** — independently loadable components
- **sd/** — read-only-first microSD access and storage checks
- **wifi/** — network service interface
- **recovery/** — diagnostics and safe fallback behavior
- **tests/** — host-side checks for portable code

## Development principles

1. Prefer small, auditable components.
2. Keep hardware access behind explicit interfaces.
3. Test portable logic on a host before using console hardware.
4. Never claim console compatibility without a real test.
5. Preserve a known-good recovery path throughout development.

## Build status

No firmware binary is produced yet. Build tooling and the first tested executable will be added in a later step.
