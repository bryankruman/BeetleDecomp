"""Set only the O32 ABI field on the native-matching MIPS3 LL object.

IDO's historical -mips3 -32 recipe emits the exact LL instructions but leaves
its ELF ABI field unspecified. The normal kernel link uses O32 objects. This
closed postcompile step changes no instruction, symbol, section, or other flag.
"""
from pathlib import Path
import hashlib
import struct
import sys

TEXT_SHA256 = 'ccf2a1fcc516893d7a2343a6fe49332f551ecb037d7de2e3dda5d2205bcd9ccc'
FUNCTIONS = {'__ull_rshift': (0,44), '__ull_rem': (44,60), '__ull_div': (104,60), '__ll_lshift': (164,44), '__ll_rem': (208,60), '__ll_div': (268,92), '__ll_mul': (360,48), '__ull_divremi': (408,96), '__ll_mod': (504,156), '__ll_rshift': (660,44)}
RAW_FLAGS = 0x20000000
O32_FLAGS = RAW_FLAGS | 0x1000


def transform(raw):
    assert isinstance(raw, bytes) and len(raw) >= 52
    assert raw[:16] == bytes.fromhex('7f454c46010201000000000000000000')
    kind,machine,version,entry,phoff,shoff,flags,ehsize,phentsize,phnum,shentsize,shnum,shstrndx = struct.unpack_from('>HHIIIIIHHHHHH', raw, 16)
    assert (kind,machine,version,entry,phoff,ehsize,phentsize,phnum,shentsize) == (1,8,1,0,0,52,0,0,40)
    assert flags in (RAW_FLAGS,O32_FLAGS)
    assert 0 < shstrndx < shnum and shoff >= 52 and shoff+shnum*40 <= len(raw)
    sections = [struct.unpack_from('>10I', raw, shoff+i*40) for i in range(shnum)]
    def payload(section):
        offset,size = section[4:6]
        assert section[1] != 8 and offset+size <= len(raw)
        return raw[offset:offset+size]
    names = payload(sections[shstrndx]); assert sections[shstrndx][1] == 3
    def cstring(table, offset):
        assert 0 <= offset < len(table)
        end=table.find(b'\0',offset); assert end >= 0
        return table[offset:end].decode('ascii')
    named = {cstring(names,s[0]): (i,s) for i,s in enumerate(sections)}
    assert len(named) == len(sections)
    textindex,text = named['.text']; textbytes = payload(text)
    assert (text[1],text[2],text[3],text[5]) == (1,6,0,704)
    assert hashlib.sha256(textbytes).hexdigest() == TEXT_SHA256
    assert all(s[5] == 0 for s in sections if s[1] in (4,9))
    assert all(name in ('.text','.reginfo') or not(s[2]&2 and s[5]) for name,(i,s) in named.items())
    symindex,sym = named['.symtab']; assert sym[1] == 2 and sym[9] == 16 and sym[5] % 16 == 0
    assert 0 < sym[6] < shnum and sections[sym[6]][1] == 3
    strings = payload(sections[sym[6]]); symbols = payload(sym); functions = {}
    for at in range(0,len(symbols),16):
        name,value,size,info,other,section = struct.unpack_from('>IIIBBH', symbols, at)
        if info&15 == 2:
            label = cstring(strings,name)
            assert label not in functions and section == textindex and info>>4 == 1
            functions[label] = (value,size)
    assert functions == FUNCTIONS
    value = raw[:36] + struct.pack('>I',O32_FLAGS) + raw[40:]
    assert value[:36] == raw[:36] and value[40:] == raw[40:] and len(value) == len(raw)
    return value


def main():
    assert len(sys.argv) == 2
    root = Path(__file__).resolve().parents[1]
    target = root/'build/src/libultra/libc/ll.o'
    supplied = Path(sys.argv[1])
    assert supplied.resolve() == target.resolve() and supplied.is_file() and not supplied.is_symlink()
    assert target.resolve().is_relative_to(root)
    raw = target.read_bytes(); value = transform(raw)
    if value != raw:
        with target.open('r+b') as output:
            assert output.read() == raw
            output.seek(36); assert output.write(value[36:40]) == 4
        assert target.read_bytes() == value
    assert transform(value) == value


if __name__ == '__main__': main()
