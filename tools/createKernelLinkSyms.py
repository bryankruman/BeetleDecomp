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
aliases = {}
if args.aliases:
    text = re.sub(r'/\*.*?\*/|//[^\n]*', '', args.aliases.read_text(), flags=re.S)
    for line in text.splitlines():
        if not line.strip():
            continue
        match = re.fullmatch(r'\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+);\s*', line)
        if not match or match[1] in aliases:
            parser.error('invalid or repeated alias assignment: ' + line)
        aliases[match[1]] = int(match[2], 16)
    targets.update(aliases)

assignments = {}
pattern = re.compile(r'^\s*(0x[0-9A-Fa-f]+)\s+([A-Za-z_]\w*)\s*=')
for line in args.mapfile.read_text().splitlines():
    match = pattern.search(line)
    if match and match[2] in targets:
        value = int(match[1], 16)
        if match[2] in assignments and assignments[match[2]] != value:
            parser.error('conflicting linked assignment: ' + match[2])
        assignments[match[2]] = value
missing = targets.difference(assignments)
if missing:
    parser.error('linked symbols missing: ' + ', '.join(sorted(missing)))
for name, expected in aliases.items():
    if assignments[name] != expected:
        parser.error('linked alias differs from declared address: ' + name)
temporary = args.output.with_suffix(args.output.suffix + '.tmp')
temporary.write_text(''.join(f'{name} = 0x{assignments[name]:X};\n' for name in sorted(targets)))
temporary.replace(args.output)
print('Exported', len(targets), 'verified linker assignments.')
