"""Synthetic contract tests; no original ROM or fleet resources required."""
from pathlib import Path
import importlib.util,os,struct,unittest

path=Path(os.environ.get('BAR_TEXTURE_INVENTORY_TEST_TOOL',
                        str(Path(__file__).resolve().parents[1]/'inventory_texture_rows.py')))
spec=importlib.util.spec_from_file_location('inventory_texture_rows',path)
tool=importlib.util.module_from_spec(spec);spec.loader.exec_module(tool)

def stream(count,flags,links=b'',literals=b''):
    controls=b''.join(struct.pack('>I',value) for value in flags);link_start=16+len(controls)
    return b'MIO0'+struct.pack('>III',count,link_start,link_start+len(links))+controls+links+literals

class TextureInventoryContracts(unittest.TestCase):
    def test_literals_preserve_unsigned_byte_values(self):
        self.assertEqual(tool.mio0_decode(stream(3,[0xE0000000],literals=b'\x00\x80\xff'),3),b'\x00\x80\xff')

    def test_nonoverlapping_reference_distance(self):
        self.assertEqual(tool.mio0_decode(stream(6,[0xE0000000],b'\x00\x02',b'ABC'),6),b'ABCABC')

    def test_reference_may_read_bytes_it_just_wrote(self):
        self.assertEqual(tool.mio0_decode(stream(6,[0x80000000],b'\x20\x00',b'A'),6),b'AAAAAA')

    def test_maximum_match_length(self):
        self.assertEqual(tool.mio0_decode(stream(19,[0x80000000],b'\xf0\x00',b'Z'),19),b'Z'*19)

    def test_control_refill_after_32_tokens(self):
        data=bytes(range(33))
        self.assertEqual(tool.mio0_decode(stream(33,[0xFFFFFFFF,0x80000000],literals=data),33),data)

    def test_control_truncation(self):
        with self.assertRaises(AssertionError):tool.mio0_decode(b'MIO0'+struct.pack('>III',1,16,16),1)

    def test_link_truncation(self):
        with self.assertRaises(AssertionError):tool.mio0_decode(stream(3,[0],b'\x00'),3)

    def test_literal_truncation(self):
        with self.assertRaises(AssertionError):tool.mio0_decode(stream(1,[0x80000000]),1)

    def test_reference_before_output_rejected(self):
        with self.assertRaises(AssertionError):tool.mio0_decode(stream(3,[0],b'\x00\x00'),3)

    def test_match_cannot_overshoot_exact_output_end(self):
        with self.assertRaises(AssertionError):tool.mio0_decode(stream(2,[0x80000000],b'\x00\x00',b'A'),2)

    def test_zero_output_original_loop_precondition(self):
        with self.assertRaises(AssertionError):tool.mio0_decode(stream(0,[0]),0)

    def test_wrapper_and_inner_output_size_must_agree(self):
        with self.assertRaises(AssertionError):tool.decode_block(b'GZIP',b'COMM'+struct.pack('>I',2)+stream(1,[0x80000000],literals=b'A'))

    def test_unknown_codec_stays_opaque(self):
        tag,data,codec=tool.decode_block(b'GZIP',b'COMM'+struct.pack('>I',12)+b'UNKNOWN')
        self.assertEqual(tag,b'COMM');self.assertIsNone(data);self.assertTrue(codec['opaque_compression'])
        self.assertNotIn('encoded_prefix_hex',codec)

    def test_mode_zero_bound_and_payload_extent_are_independent(self):
        data=bytearray(54+7*32);data[53]=7
        result=tool.comm_metadata(data)
        self.assertFalse(result['six_row_storage_sufficient']);self.assertTrue(result['payload_extent_sufficient'])
        self.assertFalse(tool.comm_metadata(data[:-1])['payload_extent_sufficient'])

    def test_other_modes_do_not_consume_local_row_array(self):
        data=bytearray(54);data[43]=1;data[53]=255
        result=tool.comm_metadata(data)
        self.assertFalse(result['local_rows_used']);self.assertTrue(result['six_row_storage_sufficient'])
        self.assertTrue(result['payload_extent_sufficient'])

    def test_metadata_offset_uses_original_image_clamp_and_display_list_size(self):
        metadata=28+4096+16;data=bytearray(metadata+26+32)
        struct.pack_into('>HH',data,0,4097,2);data[metadata+25]=1
        result=tool.comm_metadata(data)
        self.assertEqual(result['metadata_offset'],metadata);self.assertEqual(result['row_count_byte'],1)
        self.assertTrue(result['payload_extent_sufficient'])

if __name__=='__main__':unittest.main()
