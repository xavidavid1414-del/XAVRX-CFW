# FIRM container validation

Xavrx now has a read-only host-side inspector at `tools/firm-inspect.py`.
It checks the FIRM magic, minimum header length, four section descriptors,
section data bounds, and overlapping section ranges. Its JSON report includes
the whole-file SHA-256, each present section's stored SHA-256 field, and a
`section_sha256_valid` boolean comparing the stored digest with a freshly
calculated SHA-256 of that section's bytes. A mismatch is reported rather than
silently accepted or modified. Unit tests use synthetic data.

Run on a computer or Termux with Python 3:

```sh
python3 -m unittest discover -s tests -p 'test_firm_inspect.py' -v
python3 tools/firm-inspect.py path/to/candidate.firm
```

A successful report means only that basic container boundaries look consistent.
It does **not** validate cryptographic authenticity, processor-specific code,
memory safety, entry-point correctness, hardware compatibility, or bootability.
Do not install an inspected file as `boot.firm` based on this report.

The inspector is deliberately read-only. It does not generate or modify FIRM
payloads, access NAND, or interact with the console.


## Descriptor field naming correction

The 32-bit value at descriptor offset `+0x0C` is described by 3dbrew as the
FIRM section **copy method** (0 = NDMA, 1 = XDMA, 2 = CPU copy). The inspector
reports it as `copy_method` and deliberately does not interpret or enforce its
value. Luma3DS's `FirmSection` struct names the same field `procType`, but its
current FIRM validation path does not use that member. Xavrx documents this
naming difference rather than treating the field as a bootability check.
The descriptor's stored SHA-256 field begins at offset `+0x10`; the inspector
now verifies that digest against the corresponding section data. See the [3dbrew FIRM format reference](https://3dbrew.org/wiki/FIRM).

This correction improves report accuracy; it does not add bootability checks.
