# Xavrx current build status

Latest verified workflow: [run 46063447754](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46063447754)

Commit: `144dc1bc3849d7227dc8d0456e4866a33ea6df7a`

## Verified jobs

The latest three workflow runs completed successfully:

- [Run 46063440855](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46063440855): `core-tests` and `build-3ds-homebrew` passed.
- [Run 46063444075](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46063444075): `core-tests` and `build-3ds-homebrew` passed.
- [Run 46063447754](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46063447754): `core-tests` and `build-3ds-homebrew` passed.

The verified checks include portable C11 core tests, read-only FIRM inspector tests, the diagnostic `.3dsx` build, the Xavrx Installer `.3dsx` build, and the SD-layout ZIP packaging job.

## What these results mean

The current portable code, homebrew applications, and SD folder-layout archive build in CI. These checks do not execute on a New Nintendo 2DS XL and do not establish boot-stage compatibility.

## Artifacts

Open [the latest workflow run](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46063447754) and download:
- `xavrx-diagnostic-3dsx`
- `xavrx-installer-3dsx`
- `xavrx-sd-layout`

## Explicitly not available

- No Xavrx `boot.firm`.
- No ARM9 boot-stage executable.
- No CIA package.
- No hardware boot test or recovery validation.

Keep the currently working Luma boot files unchanged. The SD-layout ZIP contains Xavrx data folders only; it is not a firmware installer.
