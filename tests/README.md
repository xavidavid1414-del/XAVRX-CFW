# Tests

Portable code will be tested on a host before console testing.

Planned checks:

- configuration parsing
- module metadata validation
- storage path validation
- startup state transitions
- recovery decision logic

Hardware tests will be clearly separated from host tests. No test in this directory should write to NAND.
