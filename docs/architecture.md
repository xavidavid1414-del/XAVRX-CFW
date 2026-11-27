# XAVRX CFW — Initial Architecture

## Version 0.1 scope

Version 0.1 establishes a safe, testable project structure. It does not install to NAND, replace boot9strap, or claim to boot as a complete CFW.

## Startup model

1. An existing trusted boot chain launches an XAVRX development build.
2. XAVRX validates its own build metadata and runtime environment.
3. The core initializes only services that have been implemented and tested.
4. Optional modules are started independently.
5. If initialization fails, XAVRX exits or returns control through the documented launch path.

## Component boundaries

| Component | Responsibility | Initial safety boundary |
|---|---|---|
| boot | Entry point and handoff | No boot-chain writes |
| core | Runtime, logging, configuration | No direct hardware writes without reviewed APIs |
| modules | Optional features | Disabled unless implemented |
| sd | Storage discovery | Read-only first |
| wifi | Network abstraction | No credentials stored in source |
| recovery | Diagnostics and fallback | Never overwrites NAND |

## Storage budget

The 10 MB target applies to XAVRX-owned files on the microSD card, not Nintendo system files, boot9strap, or required external dependencies. Actual size will be measured from release artifacts; it is not yet verified.

## Milestones

- [x] Create repository and define scope
- [x] Establish architecture and safety boundaries
- [ ] Add toolchain detection and reproducible build
- [ ] Add minimal entry point
- [ ] Add host-side unit tests
- [ ] Produce first development artifact
- [ ] Verify launch on hardware without changing NAND
