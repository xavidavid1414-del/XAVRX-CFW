# XAVRX CFW — Architecture

## Current scope

The repository contains a user-mode diagnostic application and portable core components. It is not bootable custom firmware and does not replace the existing boot chain.

## Core modules

| Module | Responsibility | Current boundary |
|---|---|---|
| core | Startup state transitions | Explicit, one-way transitions |
| config | Small key/value configuration parser | Bounded input; known keys only |
| log | Fixed-size in-memory log ring | No filesystem writes |
| app | 3DS diagnostic screen | Runs as ordinary homebrew |
| tests | Host-side checks | No console or NAND access |

## Startup model

1. Start in COLD.
2. Enter VALIDATING.
3. Enter READY only after validation succeeds, or FAILED if validation fails.
4. Do not perform privileged operations or boot-chain modifications.

## Configuration

The parser currently recognizes wifi_enabled=0|1 and log_level=0|1|2. Defaults are Wi-Fi disabled and log level 1. Unknown keys are ignored. Invalid values for recognized keys reject the configuration. The parser operates on a caller-supplied byte range and does not allocate memory.

## Logging

The logger stores up to eight fixed-size messages in RAM. It does not write to SD or NAND. This keeps the first logging implementation bounded and easy to test.

## Storage goal

The goal remains under 10 MB for XAVRX-owned microSD files, where technically feasible. No size claim is made until a real release artifact is built and measured.

## Next milestones

- [x] Portable startup state machine
- [x] Bounded configuration parser
- [x] Fixed-size in-memory logger
- [x] Host-side unit tests added to CI
- [ ] Confirm CI test and 3DS build results
- [ ] Add read-only SD detection behind a separately reviewed interface
- [ ] Hardware launch test without changing boot-critical files
