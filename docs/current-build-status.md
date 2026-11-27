# Xavrx current build status

Latest verified workflow: [run 46064393281](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46064393281)

Commit: `4165d4933a5235a08faf473c1196dd7b03d6f2c5`

## Verified jobs

Run 46064393281 completed successfully:

- `core-tests`: portable core tests and read-only FIRM inspector tests passed.
- `build-3ds-homebrew`: diagnostic `.3dsx`, Xavrx Installer `.3dsx`, and SD-layout ZIP packaging completed successfully.

The inspector tests now cover entry-point-to-section matching and the exclusive end boundary. The report also identifies overlapping load ranges for review without claiming those ranges are safe or invalid.

## What these results mean

The current portable code, homebrew applications, and SD folder-layout archive build in CI. These checks do not execute on a New Nintendo 2DS XL and do not establish boot-stage compatibility.

## Artifacts

Open [the latest workflow run](https://github.com/xavidavid1414-del/XAVRX-CFW/actions/runs/46064393281) and download:
- `xavrx-diagnostic-3dsx`
- `xavrx-installer-3dsx`
- `xavrx-sd-layout`

## Explicitly not available

- No Xavrx `boot.firm`.
- No ARM9 boot-stage executable.
- No CIA package.
- No hardware boot test or recovery validation.

Keep the currently working Luma boot files unchanged. The SD-layout ZIP contains Xavrx data folders only; it is not a firmware installer.
