# FIRM container validation

Xavrx now has a read-only host-side inspector at `tools/firm-inspect.py`.
It checks the FIRM magic, minimum header length, section count, section data
bounds, and overlapping section ranges. Unit tests use synthetic byte arrays.

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

The 32-bit value at descriptor offset `+0x0C` is the FIRM section
**copy method**, not a processor or section type. The inspector reports it as
`copy_method` and deliberately does not interpret or enforce its value.
The descriptor's SHA-256 field begins at offset `+0x10`; this basic inspector
does not verify section hashes. See the [3dbrew FIRM format reference](https://3dbrew.org/wiki/FIRM).

This correction improves report accuracy; it does not add bootability checks.
