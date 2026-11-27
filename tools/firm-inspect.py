#!/usr/bin/env python3
"""Read-only structural inspector for Nintendo 3DS FIRM containers.

This tool does not create, patch, sign, install, or execute firmware.
It reports basic header and section-boundary information only.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import struct
from pathlib import Path

HEADER_SIZE = 0x200
SECTION_COUNT = 4
SECTION_ENTRY_SIZE = 0x30
SECTION_TABLE_OFFSET = 0x40
MAGIC = b"FIRM"


def inspect_firm(data: bytes) -> dict:
    if len(data) < HEADER_SIZE:
        raise ValueError(f"file too small: {len(data)} bytes (need at least {HEADER_SIZE})")
    if data[:4] != MAGIC:
        raise ValueError("missing FIRM magic")

    arm11_entry, arm9_entry = struct.unpack_from("<II", data, 0x08)
    sections = []
    ranges = []
    load_ranges = []
    load_range_overlaps = []
    for index in range(SECTION_COUNT):
        off = SECTION_TABLE_OFFSET + index * SECTION_ENTRY_SIZE
        file_offset, load_address, size = struct.unpack_from("<III", data, off)
        copy_method = struct.unpack_from("<I", data, off + 0x0C)[0]
        if size == 0:
            sections.append({
                "index": index, "present": False, "file_offset": file_offset,
                "load_address": load_address, "size": size, "copy_method": copy_method,
                "section_sha256": None, "section_sha256_valid": None
            })
            continue
        end = file_offset + size
        load_end = load_address + size
        if load_end > 0x100000000:
            raise ValueError(f"section {index}: load address range overflows 32-bit address space")
        if file_offset < HEADER_SIZE:
            raise ValueError(f"section {index}: data overlaps FIRM header")
        if end < file_offset or end > len(data):
            raise ValueError(f"section {index}: data range exceeds file")
        for other_start, other_end, other_index in ranges:
            if file_offset < other_end and other_start < end:
                raise ValueError(f"sections {other_index} and {index} overlap")
        ranges.append((file_offset, end, index))
        for other_start, other_end, other_index in load_ranges:
            if load_address < other_end and other_start < load_end:
                load_range_overlaps.append({
                    "section_a": other_index, "section_b": index,
                    "overlap_start": f"0x{max(load_address, other_start):08X}",
                    "overlap_end_exclusive": f"0x{min(load_end, other_end):08X}"
                })
        load_ranges.append((load_address, load_end, index))
        stored_hash = data[off + 0x10:off + 0x30]
        calculated_hash = hashlib.sha256(data[file_offset:end]).digest()
        sections.append({
            "index": index, "present": True, "file_offset": file_offset,
            "load_address": load_address, "load_end_exclusive": f"0x{load_end:08X}" if load_end < 0x100000000 else "0x100000000",
            "size": size, "copy_method": copy_method,
            "section_sha256": stored_hash.hex(),
            "section_sha256_valid": stored_hash == calculated_hash
        })

    if not any(section["present"] for section in sections):
        raise ValueError("FIRM contains no non-empty sections")

    def matching_sections(entry_point: int) -> list[int]:
        return [
            index for start, end, index in load_ranges
            if start <= entry_point < end
        ]

    return {
        "format": "FIRM",
        "file_size": len(data),
        "file_sha256": hashlib.sha256(data).hexdigest(),
        "arm11_entry": f"0x{arm11_entry:08X}",
        "arm9_entry": f"0x{arm9_entry:08X}",
        "entry_point_section_matches": {
            "arm11": matching_sections(arm11_entry),
            "arm9": matching_sections(arm9_entry)
        },
        "sections": sections,
        "load_range_overlaps": load_range_overlaps,
        "validation": "basic container bounds only; not proof of bootability"
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("firm", type=Path)
    args = parser.parse_args()
    try:
        report = inspect_firm(args.firm.read_bytes())
    except (OSError, ValueError) as exc:
        parser.error(str(exc))
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
