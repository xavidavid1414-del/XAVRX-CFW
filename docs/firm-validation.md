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
