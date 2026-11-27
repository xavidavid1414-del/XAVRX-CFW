# Xavrx boot-contract evidence

Status: research notes only. This file does not define an executable entry ABI,
hardware memory map, or bootable FIRM image.

## Confirmed from upstream references

| Topic | Evidence | What Xavrx may conclude |
|---|---|---|
| File lookup | [boot9strap README](https://github.com/SciresM/boot9strap#readme) says it launches `boot.firm` from SD or CTRNAND. | The active payload filename and fallback locations are known. |
| FIRM section validation | [Luma3DS ARM9 FIRM loader](https://github.com/LumaTeam/Luma3DS/blob/master/arm9/source/firm.c) checks the `FIRM` magic, ARM9 entry, section count/size bounds, alignment, address overflow, and allowed destination ranges. | A basic header parser is not enough; validation must include section semantics and target-specific constraints. |
| FIRM descriptor metadata | [3dbrew FIRM format](https://3dbrew.org/wiki/FIRM) describes descriptor offset `+0x0C` as a copy method; Luma3DS's `FirmSection` struct calls the same field `procType`, though its loader validation does not consume it. | Xavrx reports this field without enforcing its value; the naming discrepancy is documented rather than guessed away. |
| Boot-chain versioning | [boot9strap releases](https://github.com/SciresM/boot9strap/releases) document behavior changes across versions. | Any compatibility claim must name the boot9strap version being targeted. |

## Not yet established

The references above do **not** establish a complete, safe contract for a new
Xavrx entry point on the user's New Nintendo 2DS XL. The following remain open:

- exact register, stack, CPU mode, interrupt, and cache state at Xavrx entry;
- exact boot9strap version and behavior on the target console;
- supported hardware revision identifiers and model-specific memory ownership;
- complete FIRM section constraints for this target, including any version
  flags or special hand-off behavior;
- a reviewed recovery procedure and independent hardware test setup.

Do not infer these details from a single implementation. In particular, Luma's
checks are evidence of what Luma validates, not proof that every check is a
formal requirement of every boot9strap release.

## Work rules

1. Keep the existing Luma `boot.firm` untouched.
2. Keep the current libctru `.3dsx` build separate from any future FIRM target.
3. Keep host-side inspection read-only and clearly label synthetic test data.
4. Do not create or publish a placeholder `boot.firm`.
5. Do not claim bootability based on a parsed header or a successful linker run.
6. Do not start hardware boot experiments until the missing contract items are
   sourced, independently reviewed, and paired with a verified recovery plan.

## Next checkpoint

Identify the exact boot9strap version present on the target setup from reliable
user-provided system information, then review the matching tagged upstream
source and record the remaining entry-state requirements. Until then, the
ARM9 entry ABI stays explicitly unspecified.


## FIRM entry-point and section facts

The [3dbrew FIRM format reference](https://3dbrew.org/wiki/FIRM) documents
ARM11 and ARM9 entry-point fields at header offsets `0x08` and `0x0C`.
Each of the four section descriptors contains a file offset, a physical load
address, a byte size, a copy-method field, and a SHA-256 digest. The section
size determines whether a descriptor is present. The reference describes
copy-method values for NDMA, XDMA, and CPU copy, and notes that Process9
ignores this field.

This supports the inspector's structural reporting of entry-point/section
matches, section file bounds, load-range arithmetic, and stored section
digests. It does **not** establish that a match is sufficient for execution,
that overlapping load ranges are acceptable, or that any reported physical
address is safe for Xavrx to use.

The [3DS memory-layout reference](https://3dbrew.org/wiki/Memory_layout)
shows distinct ARM9 regions and differences between Old 3DS and New 3DS
hardware. Xavrx therefore must not treat a generic 32-bit address-range check
as a hardware memory map. A target-specific map and ownership rules remain
unapproved until verified against the exact New 2DS XL and boot environment.

The [boot9strap project](https://github.com/SciresM/boot9strap) is the
upstream source to pin for the installed loader version. The exact version
installed on the target console is still unknown, so no version-specific
entry-state or hand-off claim is made here.
