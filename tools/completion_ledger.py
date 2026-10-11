#!/usr/bin/env python3
"""Report unfinished assembly without hiding module entrypoints or claiming a percentage."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import re

def declared_assembly_data(root):
    """Only validated explicit module ownership can classify a pragma as data."""
    config = root / 'config/us/modules.yaml'
    if not config.is_file():
        return {}
    config_text = config.read_text(encoding='utf-8')
    if 'readonly_layout' not in config_text:
        return {}
    # YAML is an existing module-extraction dependency. Import it only when
    # checking module ownership so the legacy no-config ledger remains usable.
    import yaml
    modules = yaml.safe_load(config_text)['Modules']
    declared = {}
    for module in modules:
        metadata = module.get('readonly_layout')
        if metadata is None:
            continue
        if 'rodata' not in module.get('done_sections', []):
            raise ValueError('readonly_layout lacks whole-object rodata ownership')
        from moduleReadonlyLayout import load, validate_source, check_users, inside, sha
        layout, original, prefix, suffix = load(root, metadata, module['name'])
        validate_source(root, layout)
        check_users(root, layout, original)
        assembly = layout['prefix_assembly']
        path = inside(root, assembly)
        if not path.is_file() or path.read_text(encoding='utf-8') != prefix.decode('utf-8'):
            raise ValueError('Declared readonly prefix is missing or changed: ' + assembly)
        if assembly in declared:
            raise ValueError('Multiple owners declare the same readonly prefix: ' + assembly)
        tables = layout['tables'] if layout['version'] in (2, 3, 4) else [layout]
        owned_bytes = sum(table['table_end'] - table['table_begin'] for table in tables)
        declared[assembly] = {
            'source': layout['source'], 'symbol': path.stem, 'assembly': assembly,
            'bytes': tables[0]['table_begin'] - layout['begin'], 'module': module['name'],
            'metadata': metadata, 'witness': layout['witness'],
            'witness_sha256': layout['witness_sha256'], 'assembly_sha256': sha(path.read_bytes()),
            'original_readonly_bytes': len(original),
            'retained_readonly_bytes': len(original) - owned_bytes,
            'compiler_owned_readonly_bytes': owned_bytes,
            'ownership': 'preserved-original-readonly-prefix',
        }
        if layout['version'] == 4:
            # One full-section ownership row; islands are exact subordinate
            # data references, not functions or another copy of section totals.
            islands = []
            for island in layout['retained_islands']:
                if island is None:
                    continue
                name = island['assembly']
                data_path = inside(root, name)
                if not data_path.is_file() or data_path.read_bytes() != suffix[name]:
                    raise ValueError('Declared readonly island is missing or changed: ' + name)
                islands.append({'assembly': name, 'bytes': island['end'] - island['begin'],
                                'begin': island['begin'], 'end': island['end'],
                                'assembly_sha256': sha(data_path.read_bytes()),
                                'readonly_sha256': island['readonly_sha256']})
            declared[assembly]['retained_islands'] = islands
    return declared

def collect(root):
    declared_data = declared_assembly_data(root)
    island_data = {}
    for row in declared_data.values():
        for island in row.get('retained_islands', []):
            name = island['assembly']
            if name in island_data or name in declared_data:
                raise ValueError('Readonly island has multiple owners: ' + name)
            island_data[name] = row['source']
    assembly_data = []
    unresolved = []
    address_names = []
    for source in sorted((root / 'src').rglob('*.c')):
        text = source.read_text(errors='replace')
        # Comments cannot make an inactive pragma look like unfinished executable code.
        clean = re.sub(r'/\*.*?\*/|//[^\n]*', '', text, flags=re.S)
        for match in re.finditer(r'^\s*#pragma\s+GLOBAL_ASM\("([^"]+)"\)', clean, re.M):
            if match[1] in declared_data:
                row = declared_data[match[1]]
                if row['source'] != source.relative_to(root).as_posix():
                    raise ValueError('Readonly prefix referenced by undeclared source: ' + match[1])
                assembly_data.append(dict(row))
                continue
            if match[1] in island_data:
                if island_data[match[1]] != source.relative_to(root).as_posix():
                    raise ValueError('Readonly island referenced by undeclared source: ' + match[1])
                # Its one full-section owner row already includes this exact
                # island, so section storage/counters cannot be counted twice.
                continue
            if match[1].endswith(('.rodata-prefix.s', '.rodata-island.s')):
                raise ValueError('Readonly prefix has no validated ownership metadata: ' + match[1])
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
            'assembly_data_references': len(assembly_data), 'assembly_data': assembly_data,
            'ordinary_assembly_references': sum(not r['entrypoint'] for r in unresolved),
            'entrypoint_assembly_references': sum(r['entrypoint'] for r in unresolved),
            'known_remaining_code_bytes': sum(r['bytes'] or 0 for r in unresolved),
            'remaining_sizes_unknown': sum(r['bytes'] is None for r in unresolved),
            'c_definitions_with_address_names': len(address_names),
            'rom_expected_sha1': expected, 'rom_built_sha1': built, 'rom_matches': built == expected,
            'per_source': dict(counts.most_common()), 'remaining': unresolved,
            'address_named_c': address_names,
            'limitations': ['Source pragmas include conditional assembly fallbacks; no completion percentage is inferred.',
                           'Validated retained readonly prefixes are reported separately; assembly_references and code bytes describe instruction functions only.',
                           'Address-name scan includes recovered entrypoints and allows meaningful func_* names; it is not a full semantic/comment audit.'] +
                           (['Validated readonly island pragmas are included in their prefix ownership row; assembly_data_references counts section ownership rows.'] if island_data else [])}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--output', type=Path)
    parser.add_argument('--require-complete', action='store_true')
    args = parser.parse_args()
    report = collect(args.root.resolve())
    if args.output: args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps({k: v for k, v in report.items() if k not in ('remaining', 'address_named_c', 'per_source', 'assembly_data')}, indent=2))
    if args.require_complete and (report['assembly_references'] or report['c_definitions_with_address_names'] or not report['rom_matches']):
        return 1
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
