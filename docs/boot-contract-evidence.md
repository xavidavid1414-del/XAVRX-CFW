# Xavrx boot-contract evidence

Status: research notes only. This file does not define an executable entry ABI,
hardware memory map, or bootable FIRM image.

## Confirmed from upstream references

| Topic | Evidence | What Xavrx may conclude |
|---|---|---|
| File lookup | [boot9strap README](https://github.com/SciresM/boot9strap#readme) says it launches `boot.firm` from SD or CTRNAND. | The active payload filename and fallback locations are known. |
| FIRM section validation | [Luma3DS ARM9 FIRM loader](https://github.com/LumaTeam/Luma3DS/blob/master/arm9/source/firm.c) checks the `FIRM` magic, ARM9 entry, section count/size bounds, alignment, address overflow, and allowed destination ranges. | A basic header parser is not enough; validation must include section semantics and target-specific constraints. |
| FIRM structure | [radare2 Nintendo 3DS FIRM parser](https://github.com/radareorg/radare2/blob/master/libr/bin/p/bin_nin3ds.c) recognizes four section descriptors and ARM9/ARM11 section types. | Four descriptors and processor type metadata are useful format facts, but this parser is not a bootloader specification. |
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
