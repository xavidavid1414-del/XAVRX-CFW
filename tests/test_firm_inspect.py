import hashlib
import importlib.util
import struct
import unittest
from pathlib import Path

MODULE_PATH = Path(__file__).parents[1] / "tools" / "firm-inspect.py"
spec = importlib.util.spec_from_file_location("firm_inspect", MODULE_PATH)
firm_inspect = importlib.util.module_from_spec(spec)
spec.loader.exec_module(firm_inspect)


def make_firm():
    data = bytearray(0x240)
    data[:4] = b"FIRM"
    struct.pack_into("<II", data, 0x08, 0x1FF80000, 0x08000000)
    struct.pack_into("<III", data, 0x40, 0x200, 0x1FF80000, 0x40)
    struct.pack_into("<I", data, 0x4C, 0)
    data[0x50:0x70] = hashlib.sha256(data[0x200:0x240]).digest()
    return bytes(data)


class FirmInspectTests(unittest.TestCase):
    def test_accepts_bounded_container(self):
        result = firm_inspect.inspect_firm(make_firm())
        self.assertEqual(result["format"], "FIRM")
        self.assertTrue(result["sections"][0]["present"])
        self.assertEqual(result["sections"][0]["copy_method"], 0)
        self.assertNotIn("type", result["sections"][0])
        self.assertEqual(result["file_sha256"], hashlib.sha256(make_firm()).hexdigest())
        self.assertEqual(result["sections"][0]["section_sha256"], hashlib.sha256(make_firm()[0x200:0x240]).hexdigest())
        self.assertTrue(result["sections"][0]["section_sha256_valid"])

    def test_reports_copy_method_and_section_hash(self):
        data = bytearray(make_firm())
        struct.pack_into("<I", data, 0x4C, 2)
        data[0x50:0x70] = bytes(range(32))
        result = firm_inspect.inspect_firm(bytes(data))
        self.assertEqual(result["sections"][0]["copy_method"], 2)
        self.assertEqual(result["sections"][0]["section_sha256"], bytes(range(32)).hex())
        self.assertFalse(result["sections"][0]["section_sha256_valid"])

    def test_detects_section_hash_mismatch(self):
        data = bytearray(make_firm())
        data[0x220] ^= 0xFF
        result = firm_inspect.inspect_firm(bytes(data))
        self.assertFalse(result["sections"][0]["section_sha256_valid"])

    def test_reports_exclusive_load_end(self):
        result = firm_inspect.inspect_firm(make_firm())
        self.assertEqual(result["sections"][0]["load_end_exclusive"], "0x1FF80040")

    def test_rejects_load_address_overflow(self):
        data = bytearray(make_firm())
        struct.pack_into("<I", data, 0x44, 0xFFFFFFF0)
        with self.assertRaisesRegex(ValueError, "load address range overflows"):
            firm_inspect.inspect_firm(bytes(data))

    def test_reports_overlapping_load_ranges_without_claiming_validity(self):
        data = bytearray(make_firm()) + bytearray(0x20)
        struct.pack_into("<III", data, 0x70, 0x240, 0x1FF80020, 0x20)
        data[0x240:0x260] = bytes(range(0x20))
        data[0x80:0xA0] = hashlib.sha256(data[0x240:0x260]).digest()
        result = firm_inspect.inspect_firm(bytes(data))
        self.assertEqual(result["load_range_overlaps"], [{
            "section_a": 0, "section_b": 1,
            "overlap_start": "0x1FF80020",
            "overlap_end_exclusive": "0x1FF80040"
        }])

    def test_rejects_wrong_magic(self):
        with self.assertRaisesRegex(ValueError, "magic"):
            firm_inspect.inspect_firm(b"NOPE" + bytes(0x300))

    def test_rejects_short_file(self):
        with self.assertRaisesRegex(ValueError, "too small"):
            firm_inspect.inspect_firm(b"FIRM")

    def test_rejects_section_outside_file(self):
        data = bytearray(make_firm())
        struct.pack_into("<I", data, 0x40, 0x230)
        with self.assertRaisesRegex(ValueError, "exceeds file"):
            firm_inspect.inspect_firm(bytes(data))

    def test_rejects_overlapping_sections(self):
        data = bytearray(make_firm())
        struct.pack_into("<III", data, 0x70, 0x210, 0x08000000, 0x20)
        with self.assertRaisesRegex(ValueError, "overlap"):
            firm_inspect.inspect_firm(bytes(data))


if __name__ == "__main__":
    unittest.main()
