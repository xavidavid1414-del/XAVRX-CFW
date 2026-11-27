# Xavrx boot-stage roadmap

## Goal

Develop an original, independently maintained Nintendo 3DS custom-firmware
payload that can eventually be loaded by an already-installed boot9strap
environment. The target output is a genuine FIRM-format payload named
`boot.firm`; a ZIP containing folders or a renamed `.3dsx` is not one.

## Verified boot-chain facts

- On a boot9strap setup, boot9strap loads `boot.firm` from the SD card first
  and can fall back to CTRNAND.
- Luma3DS is currently the user's working `boot.firm`.
- A normal libctru ARM11 user-mode homebrew application is not a replacement
  for a boot-stage ARM9 FIRM payload.
- Luma's documented START-at-boot chainloader behavior is not proof that the
  proposed START + POWER shortcut already exists in Xavrx.

## Development stages

1. **Specification:** document supported console models, boot environment,
   FIRM entry requirements, memory ownership, exception handling, and recovery.
2. **Build environment:** establish a dedicated ARM9/ARM11 low-level toolchain
   and reproducible build separate from the libctru homebrew target.
3. **Non-destructive prototype:** build and inspect a research payload in CI;
   do not install it as the active boot file.
4. **Validation:** test structure, section bounds, entry points, and static
   analysis. A file extension or successful linker exit is not enough.
5. **Controlled hardware testing:** only after independent review, documented
   recovery path, verified backups, and a test device are available.
6. **Feature work:** configuration loading, button shortcut, splash playback,
   modules, and system patches only after stable initialization.

## START + POWER behavior

The intended UX is: hold START while pressing POWER to request Xavrx's
maintenance/installer mode. This is a design requirement, not implemented
behavior. It must be detected by an early boot component; a regular
Homebrew Launcher application cannot observe the power-on key combination
before it starts.

## Safety and release gates

- Never overwrite the existing working `boot.firm` during development.
- Never write to NAND or alter boot9strap as part of the SD package.
- Never publish a placeholder, test executable, or renamed `.3dsx` as
  `boot.firm`.
- Do not label Xavrx as bootable until the exact FIRM artifact passes automated
  validation and has been successfully tested on supported hardware with a
  documented recovery route.
- Keep the current Luma installation intact until all release gates pass.

## Current status

**Not bootable.** The repository currently contains portable core code,
libctru homebrew targets, and an SD folder-layout package. It does not yet
contain an ARM9 boot-stage implementation or a valid Xavrx FIRM artifact.

## Next active milestone: boot contract evidence

The next engineering task is to replace assumptions with a source-backed boot
contract before writing an ARM9 entry point. Record, with exact upstream source
locations and version/commit pins:

- the FIRM header and section descriptor rules accepted by the installed
  boot9strap version;
- the ARM9 entry-point calling convention and initial processor state;
- section load addresses, alignment, bounds, and memory ownership;
- the supported New 2DS XL hardware/revision scope;
- the documented recovery procedure for an invalid SD-card payload.

A host-side FIRM parser passing tests is necessary but is not proof that a
payload will execute. The project must not synthesize a boot.firm until the
contract is verified and a dedicated ARM9 target can produce a meaningful,
reviewable payload. CI must keep the homebrew .3dsx and any future FIRM target
as separate artifacts.

## Latest verified CI checkpoint

Workflow run 46062710228 completed successfully on commit
`9d17965ae65acbbc688de904cebe0b5dfa11a2f1`: core-tests and
build-3ds-homebrew both passed. The run built the diagnostic and installer
`.3dsx` applications and produced the SD-layout ZIP. This verifies the
portable tests and existing homebrew/package build only; it does not build,
validate, or test a bootable Xavrx `boot.firm`.

See [docs/current-build-status.md](current-build-status.md) for the exact
artifacts and limitations.

## Boot contract research checkpoint

A source-backed evidence note is now tracked at
[`docs/boot-contract-evidence.md`](boot-contract-evidence.md). It records
what upstream references establish and, just as importantly, what remains
unverified: the exact ARM9 entry register/stack/CPU state, the target's
boot9strap version, and model-specific memory ownership. The next step is to
match the target's actual boot9strap version to its tagged source before
specifying an entry ABI. No ARM9 payload or `boot.firm` was produced by this
research checkpoint.

Research references:
- https://github.com/SciresM/boot9strap
- https://github.com/LumaTeam/Luma3DS/blob/master/arm9/source/firm.c
- https://github.com/radareorg/radare2/blob/master/libr/bin/p/bin_nin3ds.c
