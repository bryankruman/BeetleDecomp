"""Export verified linker assignments required by the module packing tool."""
import argparse
from pathlib import Path
import re

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('mapfile', type=Path)
parser.add_argument('output', type=Path)
parser.add_argument('--aliases', type=Path)
args = parser.parse_args()
targets = {'UVTS_25_ROM_END', 'FORM0_ROM_START', 'main_ROM_END',
           'MODULE_FILES_START', 'main_ROM_START', 'main_VRAM'}
# Only literal addresses or one linked symbol plus a literal offset are accepted.
# In particular, this does not evaluate arbitrary linker-script expressions.
symbol = r'(?:[A-Za-z_]\w*|\.L[A-Za-z0-9_]+)'
aliases = {}
if args.aliases:
    text = re.sub(r'/\*.*?\*/|//[^\n]*', '', args.aliases.read_text(), flags=re.S)
    for line in text.splitlines():
        if not line.strip():
            continue
        match = re.fullmatch(rf'\s*({symbol})\s*=\s*(0x[0-9A-Fa-f]+|{symbol})(?:\s*\+\s*(0x[0-9A-Fa-f]+))?;\s*', line)
        if not match or match[1] in aliases:
            parser.error('invalid or repeated alias assignment: ' + line)
        if match[2].startswith('0x'):
            if match[3]:
                parser.error('literal alias cannot have an offset: ' + line)
            aliases[match[1]] = int(match[2], 16)
        else:
            aliases[match[1]] = (match[2], int(match[3], 16) if match[3] else 0)
    targets.update(aliases)

assignments = {}
anchors = {value[0] for value in aliases.values() if isinstance(value, tuple)}
linked_symbols = {}
sections = []
pattern = re.compile(rf'^\s*(0x[0-9A-Fa-f]+)\s+({symbol})(?:\s*=|\s*$)')
section_pattern = re.compile(r'^(\.[A-Za-z_][\w.]*)\s+(0x[0-9A-Fa-f]+)\s+(0x[0-9A-Fa-f]+)(?:\s|$)')
for line in args.mapfile.read_text().splitlines():
    section = section_pattern.match(line)
    if section:
        start, size = int(section[2], 16), int(section[3], 16)
        if size and 0x80000000 <= start < start + size <= 0x100000000:
            sections.append((section[1], start, start + size))
    match = pattern.search(line)
    if match and match[2] in targets | anchors:
        value = int(match[1], 16)
        if match[2] in linked_symbols and linked_symbols[match[2]] != value:
            parser.error('conflicting linked symbol: ' + match[2])
        linked_symbols[match[2]] = value
    if match and match[2] in targets and '=' in line:
        value = int(match[1], 16)
        if match[2] in assignments and assignments[match[2]] != value:
            parser.error('conflicting linked assignment: ' + match[2])
        assignments[match[2]] = value
missing = targets.difference(assignments)
if missing:
    parser.error('linked symbols missing: ' + ', '.join(sorted(missing)))
for name, expected in aliases.items():
    if isinstance(expected, tuple):
        anchor, offset = expected
        if anchor in aliases or anchor not in linked_symbols:
            parser.error('alias anchor must be an independently linked symbol: ' + anchor)
        base = linked_symbols[anchor]
        expected = base + offset
        owners = [section for section in sections if section[1] <= base < section[2]]
        if len(owners) != 1 or not owners[0][1] <= expected < owners[0][2]:
            parser.error('symbolic alias is outside its unique native output section: ' + name)
    if assignments[name] != expected:
        parser.error('linked alias differs from declared address: ' + name)
temporary = args.output.with_suffix(args.output.suffix + '.tmp')
temporary.write_text(''.join(f'{name} = 0x{assignments[name]:X};\n' for name in sorted(targets)))
temporary.replace(args.output)
print('Exported', len(targets), 'verified linker assignments.')
