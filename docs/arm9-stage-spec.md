# ARM9 boot-stage specification

Status: design only. This document does not implement an ARM9 payload and does
not produce a bootable boot.firm.

## Purpose

Define the first Xavrx-owned ARM9 stage that would eventually run after the
existing boot chain loads a valid FIRM. The first implementation target is
controlled initialization and diagnostics, not replacing Luma or changing
NAND.

## Responsibilities

1. Establish a documented entry point and preserve the bootloader-provided
   processor state until each required property is understood.
2. Record the FIRM entry parameters and memory map in a versioned internal
   structure.
3. Validate that every memory range Xavrx intends to use is within an approved
   region and does not overlap reserved or hardware-owned areas.
4. Initialize only the minimum hardware needed for a visible diagnostic
   result; defer ARM11 hand-off, filesystem writes, wireless, and user modules.
5. On any failed precondition, stop safely without writing NAND or changing
   persistent boot configuration.

## Interfaces to define before implementation

- ARM9 entry ABI: exact register inputs, stack requirements, interrupt state,
  and processor mode. Must be verified against authoritative boot-chain
  documentation and a known-good reference implementation.
- Memory map: named regions, ownership, alignment, and lifetime.
- Result channel: a bounded diagnostic record that does not depend on SD I/O.
- ARM11 hand-off: explicitly out of scope for the first milestone.
- Error states: invalid entry contract, invalid memory map, unsupported
  hardware revision, and initialization failure.

## Host-side validation foundation

The portable core now exposes three pure helpers:

- `xavrx_memory_range_valid`: rejects empty ranges and 32-bit end overflow.
- `xavrx_memory_range_contains`: checks full containment.
- `xavrx_memory_ranges_overlap`: detects overlap while treating adjacent
  ranges as non-overlapping.

These helpers use generic 32-bit ranges only. They do not define, assume, or
approve any Nintendo 3DS physical memory addresses. Their edge cases are
covered by host tests, including empty ranges, overflow, containment,
overlap, and adjacency.


## Generic memory map validation

The portable core also validates a caller-supplied list of up to 16 generic
memory regions. It rejects null lists, empty lists, excessive region counts,
empty or overflowing ranges, and any pair of overlapping regions. Adjacent
regions are allowed. This is a host-testable structural check only: it does
not establish which physical addresses are safe or available on 3DS hardware.
A hardware-specific map must be sourced and reviewed before any boot-stage
code can consume it.

## Implementation gates

- Pin the exact 3DS hardware and boot-chain assumptions with source references.
- Build a dedicated ARM9 target separately from the existing libctru .3dsx
  application.
- Add host-side tests for memory-range validation and state transitions.
- Inspect the produced FIRM container with the read-only inspector.
- Do not call a container bootable merely because its header parses.
- Require independent review, a tested recovery path, backups, and a separate
  test console before any hardware boot experiment.

## Explicit non-goals

This milestone does not implement signature handling, exploit code, boot-chain
patches, NAND writes, firmware installation, or a replacement for boot9strap.
It does not change the existing SD-card package's active boot.firm.

## Current project status

The repository still has no Xavrx ARM9 entry-point implementation and no valid
Xavrx bootable FIRM artifact. The existing diagnostic .3dsx is ordinary
homebrew and remains separate from this design.


## Typed generic memory regions

A second host-side layer describes each generic range with a region kind
(`AVAILABLE`, `RESERVED`, or `DEVICE`) and explicit READ/WRITE/EXEC
permissions. Validation rejects unknown kinds or permission bits, writable or
executable RESERVED regions, executable DEVICE regions, invalid ranges, and
overlapping typed regions. These are conservative software invariants for
Xavrx's internal model, not claims about 3DS hardware permissions or physical
memory layout. No addresses are assigned by this API.
