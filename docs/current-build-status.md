# Xavrx current build status

Last verified workflow: [run 46062960686](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46062960686)

Commit: `f5ab6a372a79a758123c3de69826fbf3a1e962ee`

## Verified jobs

- `core-tests`: passed.
  - Portable core compiled with C11, `-Wall -Wextra -Werror`.
  - Read-only FIRM container unit tests passed, including descriptor metadata and stored-hash reporting.
- `build-3ds-homebrew`: passed.
  - devkitARM toolchain check passed.
  - Diagnostic `.3dsx` build passed.
  - Xavrx Installer `.3dsx` build passed.
  - SD-card layout ZIP was created and uploaded.

## What these results mean

The current portable code, homebrew applications, and SD folder-layout archive build in CI. These checks do not execute on a New Nintendo 2DS XL and do not establish boot-stage compatibility.

## Artifacts

Open the workflow run above and download:
- `xavrx-diagnostic-3dsx`
- `xavrx-installer-3dsx`
- `xavrx-sd-layout`

## Explicitly not available

- No Xavrx `boot.firm`.
- No ARM9 boot-stage executable.
- No CIA package.
- No hardware boot test or recovery validation.

Keep the currently working Luma boot files unchanged. The SD-layout ZIP contains Xavrx data folders only; it is not a firmware installer.
