#!/usr/bin/env python3
"""Report unfinished assembly without hiding module entrypoints or claiming a percentage."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import re

def collect(root):
    unresolved = []
    address_names = []
    for source in sorted((root / 'src').rglob('*.c')):
        text = source.read_text(errors='replace')
        # Comments cannot make an inactive pragma look like unfinished executable code.
        clean = re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)
        for match in re.finditer(r'^\s*#pragma\s+GLOBAL_ASM\("([^"]+)"\)', clean, re.M):
            asm = root / match[1]
            name = asm.stem
            size = None
            if asm.is_file():
                first = asm.read_text(errors='replace').splitlines()[0]
                size_match = re.search(r'nonmatching\s+\S+,\s*(0x[0-9a-fA-F]+)', first)
                if size_match: size = int(size_match[1], 16)
            unresolved.append({'source': source.relative_to(root).as_posix(), 'symbol': name,
                               'assembly': match[1], 'bytes': size,
                               'entrypoint': name.startswith('__entrypoint')})
        definitions = re.findall(r'(?m)^\w[\w \t*]*\b(\w+)\s*\([^;{}]*\)\s*\{', clean)
        # Meaningful func_* names are allowed; hexadecimal addresses are audit debt.
        # Include recovered entrypoints, whose leading __entrypoint_ hid them before.
        definitions += ['__entrypoint_' + name for name in re.findall(
            r'(?m)^\w[\w \t*]*\bMODULE_ENTRY_POINT\((\w+)\)\s*\([^;{}]*\)\s*\{', clean)]
        for name in dict.fromkeys(definitions):
            if name.startswith(('func_', '__entrypoint_func_')) and re.search(r'(?:_|^)[0-9A-Fa-f]{6,8}$', name):
                address_names.append({'source': source.relative_to(root).as_posix(), 'symbol': name})
    counts = collections.Counter(row['source'] for row in unresolved)
    rom = root / 'build/beetleadventurerac.us.z64'
    expected = (root / 'beetleadventurerac.us.sha1').read_text().split()[0]
    built = hashlib.sha1(rom.read_bytes()).hexdigest() if rom.is_file() else None
    return {'schema': 1, 'root': str(root), 'assembly_references': len(unresolved),
            'ordinary_assembly_references': sum(not r['entrypoint'] for r in unresolved),
            'entrypoint_assembly_references': sum(r['entrypoint'] for r in unresolved),
            'known_remaining_code_bytes': sum(r['bytes'] or 0 for r in unresolved),
            'remaining_sizes_unknown': sum(r['bytes'] is None for r in unresolved),
            'c_definitions_with_address_names': len(address_names),
            'rom_expected_sha1': expected, 'rom_built_sha1': built, 'rom_matches': built == expected,
            'per_source': dict(counts.most_common()), 'remaining': unresolved,
            'address_named_c': address_names,
            'limitations': ['Source pragmas include conditional assembly fallbacks; no completion percentage is inferred.',
                           'Address-name scan includes recovered entrypoints and allows meaningful func_* names; it is not a full semantic/comment audit.']}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--output', type=Path)
    parser.add_argument('--require-complete', action='store_true')
    args = parser.parse_args()
    report = collect(args.root.resolve())
    if args.output: args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps({k: v for k, v in report.items() if k not in ('remaining', 'address_named_c', 'per_source')}, indent=2))
    if args.require_complete and (report['assembly_references'] or report['c_definitions_with_address_names'] or not report['rom_matches']):
        return 1
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
