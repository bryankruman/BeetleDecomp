"""Deterministic retained ASM spans around compiler-owned readonly tables.

This deliberately small ownership format preserves original assembly, not newly
guessed C data. The original ASM witness and decoded section bytes must agree
with the real patched module before generated outputs are touched. The remaining
assembly function is only a native asm-processor layout host.
"""
from pathlib import Path
import hashlib
import json
import os
import re
import struct

SUFFIX_MARKER = b'/* readonly-layout: original suffix begins */\n'


def require(condition, message):
    if not condition:
        raise ValueError('readonly layout: ' + message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def inside(root, value):
    require(isinstance(value, str) and value and not Path(value).is_absolute(), 'expected relative path')
    result = (root / value).resolve()
    require(result.is_relative_to(root.resolve()) and result != root.resolve(), 'path leaves project')
    return result


def original_bytes(text, begin, end):
    """Read original byte annotations; reject gaps, overlaps and false words."""
    result = [None] * (end - begin)
    lines = text.splitlines()
    for i, line in enumerate(lines):
        match = re.search(r'/\* [0-9A-F]+ ([0-9A-F]+) ([0-9A-F]{8}) \*/\s*\.word\s+(\S+)', line)
        if match:
            address, raw, operand = int(match[1], 16), bytes.fromhex(match[2]), match[3]
            expected = int(operand, 16) if operand.startswith('0x') else int(operand.rsplit('_', 1)[1], 16)
            require(int.from_bytes(raw, 'big') == expected, 'word annotation disagrees with assembly')
        else:
            match = re.search(r'/\* [0-9A-F]+ ([0-9A-F]+) \*/\s*\.asciz', line)
            if not match:
                continue
            require(i + 1 < len(lines), 'missing original string bytes')
            hexline = re.fullmatch(r'\s*/\* ([0-9A-F]+) \*/\s*', lines[i + 1])
            require(hexline is not None, 'missing original string bytes')
            address, raw = int(match[1], 16), bytes.fromhex(hexline[1])
        for k, value in enumerate(raw):
            offset = address - begin + k
            require(0 <= offset < len(result) and result[offset] is None, 'overlapping/out-of-range original bytes')
            result[offset] = value
    require(None not in result, 'original readonly annotations do not cover complete section')
    return bytes(result)


def retained(text):
    output = []
    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith(('.include', '.section', 'nonmatching ', 'enddlabel ')) or stripped == '.align 4':
            continue
        if stripped.startswith('dlabel '):
            line = line.replace('dlabel ', 'glabel ', 1)
        output.append(line)
    return '\n'.join(output).strip() + '\n'


def render(layout, witness):
    label = layout['table_label']
    start = witness.index('nonmatching ' + label + '\n')
    stop = witness.index('enddlabel ' + label, start) + len('enddlabel ' + label)
    table = witness[start:stop]
    words = re.findall(r'/\* [0-9A-F]+ ([0-9A-F]+) ([0-9A-F]{8}) \*/\s*\.word\s+(\.L\w+)', table)
    count = (layout['table_end'] - layout['table_begin']) // 4
    require(len(words) == count, 'wrong compiler table entry count')
    require([int(word[0], 16) for word in words] == list(range(layout['table_begin'], layout['table_end'], 4)), 'wrong table addresses')
    prefix = '.section .rodata\n' + retained(witness[:start])
    suffix = '.section .late_rodata\n.late_rodata_alignment 4\n' + retained(witness[stop:])
    return prefix.encode('utf-8'), suffix.encode('utf-8')


def load(root, config, module):
    path = inside(root, config)
    layout = json.loads(path.read_text(encoding='utf-8'))
    if layout.get('version') == 4:
        return load_v4(root, layout, module)
    if layout.get('version') == 3:
        return load_v3(root, layout, module)
    if layout.get('version') == 2:
        return load_v2(root, layout, module)
    keys = {'version', 'module', 'source', 'witness', 'witness_sha256', 'readonly_sha256',
            'begin', 'table_begin', 'table_end', 'end', 'table_label', 'owner_original_symbol',
            'owner_c_symbol', 'host_symbol', 'host_assembly', 'host_sha256', 'host_bytes',
            'prefix_assembly', 'monolithic_assembly', 'duplicate_assembly',
            'owner_address', 'owner_bytes', 'owner_instruction_sha256', 'owner_asm_normalized_sha256'}
    require(set(layout) == keys and layout['version'] == 1 and layout['module'] == module, 'unsupported metadata schema/module')
    for name in ('begin', 'table_begin', 'table_end', 'end', 'host_bytes', 'owner_address', 'owner_bytes'):
        require(type(layout[name]) is int and 0 <= layout[name] < 2**32, 'expected unsigned integer: ' + name)
    require(layout['begin'] < layout['table_begin'] < layout['table_end'] < layout['end'], 'ranges must be ordered and nonempty')
    require(all(layout[name] % 4 == 0 for name in ('begin', 'table_begin', 'table_end', 'end', 'host_bytes')), 'word-aligned boundaries required')
    require(layout['table_begin'] % 8 == 4 and layout['table_end'] % 8 == 4, 'supported native late alignment is four')
    require(layout['host_bytes'] >= layout['end'] - layout['table_end'], 'host lacks native late-data capacity')
    for name in ('table_label', 'owner_original_symbol', 'owner_c_symbol', 'host_symbol'):
        require(re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', layout[name]), 'invalid symbol name')
    for name in ('witness_sha256', 'readonly_sha256', 'host_sha256', 'owner_instruction_sha256', 'owner_asm_normalized_sha256'):
        require(re.fullmatch(r'[0-9a-f]{64}', layout[name]), 'expected SHA-256: ' + name)
    for name in ('source', 'witness', 'host_assembly', 'prefix_assembly', 'monolithic_assembly', 'duplicate_assembly'):
        inside(root, layout[name])
    require(layout['prefix_assembly'].endswith('.rodata-prefix.s'), 'prefix must not match monolithic *.rodata.s wildcard')
    require(len({layout[n] for n in ('witness', 'host_assembly', 'prefix_assembly', 'monolithic_assembly', 'duplicate_assembly')}) == 5, 'overlapping paths')
    raw = inside(root, layout['witness']).read_bytes()
    require(sha(raw) == layout['witness_sha256'], 'original ASM witness changed')
    witness = raw.decode('utf-8')
    decoded = original_bytes(witness, layout['begin'], layout['end'])
    require(sha(decoded) == layout['readonly_sha256'], 'original readonly bytes changed')
    prefix, suffix = render(layout, witness)
    return layout, decoded, prefix, suffix


def host_text(layout, raw, suffix):
    if SUFFIX_MARKER in raw:
        require(raw.count(SUFFIX_MARKER) == 1, 'duplicate managed suffix')
        original, existing_suffix = raw.split(SUFFIX_MARKER)
        require(existing_suffix == suffix, 'managed suffix differs from original')
    else:
        original = raw
    require(sha(original) == layout['host_sha256'], 'original assembly host changed')
    text = original.decode('utf-8')
    require(re.search(r'^nonmatching\s+' + re.escape(layout['host_symbol']) + r',\s*0x' + format(layout['host_bytes'], 'X') + r'\s*$', text, re.M), 'original host boundary changed')
    instructions = re.findall(r'^\s*/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]{8} \*/', text, re.M)
    require(len(instructions) * 4 == layout['host_bytes'], 'original host instruction count changed')
    require(re.search(r'^endlabel\s+' + re.escape(layout['host_symbol']) + r'\s*$', text, re.M), 'missing original host endlabel')
    require('.rodata' not in text and '.late_rodata' not in text, 'host already owns readonly')
    return original


def validate_source(root, layout):
    if layout['version'] == 4:
        return validate_source_v4(root, layout)
    if layout['version'] == 3:
        return validate_source_v3(root, layout)
    if layout['version'] == 2:
        return validate_source_v2(root, layout)
    source = inside(root, layout['source']).read_text(encoding='utf-8')
    # Preserve positions/newlines while removing comments; text inside comments
    # must not masquerade as an active owner or ownership pragma.
    tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
    code = tokens.sub(lambda match: ''.join('\n' if c == '\n' else ' ' for c in match[0])
                      if match[0].startswith(('/*', '//')) else match[0], source)
    prefix = '#pragma GLOBAL_ASM("' + layout['prefix_assembly'] + '")'
    host = '#pragma GLOBAL_ASM("' + layout['host_assembly'] + '")'
    require(code.count(prefix) == code.count(host) == 1, 'prefix or active original host missing; C host migration needs a new proved layout')
    owners = list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\b' + re.escape(layout['owner_c_symbol']) + r'\s*\([^;{}]*\)\s*\{', code, re.M))
    require(len(owners) == 1, 'expected exactly one complete C table owner')
    owner = owners[0]
    depth = 0
    offset = 0
    for line in code.splitlines(keepends=True):
        directive = re.match(r'^\s*#\s*(if|ifdef|ifndef|endif)\b', line)
        if directive:
            depth += -1 if directive[1] == 'endif' else 1
            require(depth >= 0, 'unbalanced source conditionals')
        if prefix in line or host in line:
            require(depth == 0 and line.strip() in (prefix, host), 'ownership pragma must be unconditional, standalone source')
        if offset <= owner.start() < offset + len(line):
            require(depth == 0, 'C table owner must be unconditional')
        offset += len(line)
    require(depth == 0, 'unbalanced source conditionals')
    definitions = list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\([^;{}]*\)\s*\{', code, re.M))
    require(all(code.index(prefix) < match.start() for match in definitions), 'prefix must precede every function definition')
    require(code.index(prefix) < owner.start() < code.index(host), 'table owner/host source order changed')
    for name in (layout['owner_original_symbol'], layout['owner_c_symbol']):
        require(not re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(name) + r'\.s"\)', code), 'owner still assembly-backed')


def normalized_owner_asm(text, name):
    text = text.replace('\r\n', '\n')
    text = re.sub(r'\b' + re.escape(name) + r'\b', 'READONLY_TABLE_OWNER', text)
    # The disassembler's comment ordinal is bookkeeping, not instructions.
    return re.sub(r'^(glabel READONLY_TABLE_OWNER)[ \t]*#[ \t]*[0-9]+[ \t]*$', r'\1', text, flags=re.M)


def validate_unused_owner_asm(layout, path, name):
    """Allow only the exact original getter under original/semantic filenames."""
    text = path.read_text(encoding='utf-8')
    clean = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    lines = [line.strip() for line in clean.splitlines() if line.strip()]
    require(lines[0] == 'nonmatching ' + name + ', 0x' + format(layout['owner_bytes'], 'X'), 'unexpected unused owner boundary')
    require(re.fullmatch(r'glabel ' + re.escape(name) + r'(?:\s*#\s*[0-9]+)?', lines[1]) and lines[-1] == 'endlabel ' + name, 'unexpected unused owner wrappers')
    records = re.findall(r'^\s*/\* [0-9A-F]+ ([0-9A-F]+) ([0-9A-F]{8}) \*/\s+\S.*$', text, re.M)
    require([int(r[0], 16) for r in records] == list(range(layout['owner_address'], layout['owner_address'] + layout['owner_bytes'], 4)), 'unused owner instruction addresses/count changed')
    require(sha(b''.join(bytes.fromhex(r[1]) for r in records)) == layout['owner_instruction_sha256'], 'unused owner original instruction words changed')
    # This additionally freezes instruction operands, relocation expressions,
    # local labels and wrapper/directive text; annotations alone cannot excuse
    # a different instruction whose byte comment was left unchanged.
    require(sha(normalized_owner_asm(text, name).encode('utf-8')) == layout['owner_asm_normalized_sha256'], 'unused owner instruction/relocation text changed')


def check_users(root, layout, decoded, extra_original_data=()):
    if layout['version'] == 4:
        return check_users_v4(root, layout, decoded)
    if layout['version'] == 3:
        return check_users_v3(root, layout, decoded)
    if layout['version'] == 2:
        # The first V2 extraction can start with the accepted V1 prefix, which
        # still defines the newly owned table. Exempt only a complete exact
        # original prefix ending at a declared compiler table boundary. Never
        # ignore arbitrary contents merely because they use the prefix path.
        prefix = inside(root, layout['prefix_assembly'])
        allowed_prefix = ()
        if prefix.exists():
            witness = inside(root, layout['witness']).read_text(encoding='utf-8')
            originals = [render(dict(layout, **table), witness)[0] for table in layout['tables']]
            require(prefix.read_bytes() in originals, 'generated prefix is not an exact original retained prefix')
            allowed_prefix = (layout['prefix_assembly'],)
        for table, span in zip(layout['tables'], layout['late_spans']):
            check_users(root, table_view(layout, table, span), decoded, allowed_prefix)
        return
    allowed = {layout['monolithic_assembly'], layout['witness'], *extra_original_data}
    for name in (layout['owner_original_symbol'], layout['owner_c_symbol']):
        relative = 'asm/us/nonmatchings/modules/' + layout['module'] + '/' + name + '.s'
        path = inside(root, relative)
        if path.exists():
            validate_unused_owner_asm(layout, path, name)
            allowed.add(relative)
    duplicate = inside(root, layout['duplicate_assembly'])
    terminal_duplicate = duplicate.exists() and dyn_terminal_duplicate111100(root, layout, decoded, duplicate)
    if terminal_duplicate:
        allowed.add(layout['duplicate_assembly'])
    if duplicate.exists() and not terminal_duplicate:
        clean = re.sub(r'/\*.*?\*/', '', duplicate.read_text(encoding='utf-8'), flags=re.S)
        lines = [line.strip() for line in clean.splitlines() if line.strip()]
        table = layout['table_label']
        require(lines[:3] == ['.section .rodata', 'nonmatching ' + table, 'dlabel ' + table] and lines[-1:] == ['enddlabel ' + table], 'unexpected duplicate table definition')
        words = []
        for line in lines[3:-1]:
            match = re.fullmatch(r'\.word \.L\w+_([0-9A-F]{8})', line)
            require(match is not None, 'duplicate is not data-only')
            words.append(struct.pack('>I', int(match[1], 16)))
        lo, hi = layout['table_begin'] - layout['begin'], layout['table_end'] - layout['begin']
        require(b''.join(words) == decoded[lo:hi], 'duplicate table differs from original')
        allowed.add(layout['duplicate_assembly'])
    for folder in ('asm/us', 'src', 'include'):
        for path in (root / folder).rglob('*'):
            if not path.is_file() or path.suffix not in ('.s', '.c', '.h') or path.relative_to(root).as_posix() in allowed:
                continue
            require(re.search(r'\b' + re.escape(layout['table_label']) + r'\b', path.read_text(encoding='utf-8')) is None,
                    'extra table user requires a real exported symbol: ' + str(path))


def prepare(root, config, module, binary):
    """Read-only preflight before any module extraction output is written."""
    root = Path(root).resolve()
    # Version6 is one measured PFX scalar/two-table owner group.
    if json.loads(inside(root, config).read_bytes()).get('version') == 6:
        from pfxReadonlyLayout import prepare as prepare_pfx_group
        return prepare_pfx_group(root, config, module, binary)
    # MISC scalar constants are not switch-table owners.
    if json.loads(inside(root, config).read_bytes()).get('version') == 5:
        from miscReadonlyLayout import prepare as prepare_misc_scalar_pool
        return prepare_misc_scalar_pool(root, config, module, binary)
    layout, decoded, prefix, suffix = load(root, config, module)
    if layout['version'] == 4:
        return prepare_v4(root, config, module, binary, layout, decoded, prefix, suffix)
    if layout['version'] == 3:
        return prepare_v3(root, config, module, binary, layout, decoded, prefix, suffix)
    if layout['version'] == 2:
        return prepare_v2(root, config, module, binary, layout, decoded, prefix, suffix)
    raw = Path(binary).read_bytes()
    require(len(raw) >= 0x50 and raw[:4] == b'FORM' and raw[8:12] == b'MODU' and raw[0x18:0x1C] == b'COMM', 'invalid original module header')
    text_bytes, readonly_bytes = struct.unpack_from('>II', raw, 0x28)
    require(0x400000 + text_bytes == layout['begin'] and readonly_bytes == len(decoded), 'original module section boundaries changed')
    require(raw[0x50 + text_bytes:0x50 + text_bytes + readonly_bytes] == decoded, 'actual patched module readonly differs from witness')
    validate_source(root, layout)
    check_users(root, layout, decoded)
    host = inside(root, layout['host_assembly'])
    if host.exists():
        host_text(layout, host.read_bytes(), suffix)
    # Existing monolithic output can be removed only if it is precisely the
    # original generated witness. Unrecognised files are never silently deleted.
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        require(monolithic.read_text(encoding='utf-8') == inside(root, layout['witness']).read_text(encoding='utf-8'), 'unexpected monolithic readonly source')
    return {'root': root, 'config': config, 'module': module, 'binary': Path(binary),
            'layout': layout, 'prefix': prefix, 'suffix': suffix}


def apply(plan):
    """Use normal regenerated original ASM hosts and retained readonly spans."""
    if plan['layout']['version'] == 6:
        from pfxReadonlyLayout import apply as apply_pfx_group
        return apply_pfx_group(plan)
    if plan['layout']['version'] == 5:
        from miscReadonlyLayout import apply as apply_misc_scalar_pool
        return apply_misc_scalar_pool(plan)
    if plan['layout']['version'] == 4:
        return apply_v4(plan)
    if plan['layout']['version'] == 3:
        return apply_v3(plan)
    if plan['layout']['version'] == 2:
        return apply_v2(plan)
    # Recheck all preconditions against current outputs before writing anything.
    plan = prepare(plan['root'], plan['config'], plan['module'], plan['binary'])
    root, layout, suffix = plan['root'], plan['layout'], plan['suffix']
    host = inside(root, layout['host_assembly'])
    require(host.is_file(), 'normal function extraction did not emit original host')
    original_host = host_text(layout, host.read_bytes(), suffix)
    prefix = inside(root, layout['prefix_assembly'])
    outputs = [(prefix, plan['prefix']), (host, original_host + SUFFIX_MARKER + suffix)]
    # Prepare both complete files before replacement; metadata/byte failures
    # above leave all existing outputs untouched.
    staged = []
    try:
        for path, contents in outputs:
            path.parent.mkdir(parents=True, exist_ok=True)
            temporary = path.with_name(path.name + '.readonly-layout.tmp')
            require(not temporary.exists(), 'temporary output already exists')
            temporary.write_bytes(contents)
            staged.append((temporary, path))
        for temporary, path in staged:
            os.replace(temporary, path)
    finally:
        for temporary, _ in staged:
            if temporary.exists():
                temporary.unlink()
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        monolithic.unlink()


def table_view(layout, table, span):
    """Reuse V1 owner/host guards for one pair without weakening their checks."""
    return dict(layout, **table, **{key: value for key, value in span.items()
                                 if key.startswith('host_')}, version=1)


def load_v2(root, layout, module):
    common = {'version', 'module', 'source', 'witness', 'witness_sha256',
              'readonly_sha256', 'begin', 'end', 'prefix_assembly',
              'monolithic_assembly', 'tables', 'late_spans'}
    table_keys = {'table_begin', 'table_end', 'table_label', 'owner_original_symbol',
                  'owner_c_symbol', 'duplicate_assembly', 'owner_address', 'owner_bytes',
                  'owner_instruction_sha256', 'owner_asm_normalized_sha256'}
    span_keys = {'begin', 'end', 'host_symbol', 'host_address', 'host_assembly',
                 'host_sha256', 'host_bytes'}
    require(set(layout) == common and type(layout['version']) is int and
            layout['version'] == 2 and layout['module'] == module,
            'unsupported V2 metadata schema/module')
    tables, spans = layout['tables'], layout['late_spans']
    require(isinstance(tables, list) and len(tables) > 0 and
            isinstance(spans, list) and len(spans) == len(tables),
            'each compiler table requires exactly one retained following span')
    paths = [layout[key] for key in ('witness', 'prefix_assembly', 'monolithic_assembly')]
    symbols = []
    numbers = [layout['begin'], layout['end']]
    hashes = [layout['witness_sha256'], layout['readonly_sha256']]
    inside(root, layout['source'])
    require(isinstance(layout['prefix_assembly'], str) and
            layout['prefix_assembly'].endswith('.rodata-prefix.s'),
            'prefix must not match monolithic *.rodata.s wildcard')
    for table, span in zip(tables, spans):
        require(isinstance(table, dict) and set(table) == table_keys and
                isinstance(span, dict) and set(span) == span_keys, 'unsupported table/span schema')
        numbers += [table[key] for key in ('table_begin', 'table_end', 'owner_address', 'owner_bytes')]
        numbers += [span[key] for key in ('begin', 'end', 'host_address', 'host_bytes')]
        hashes += [table['owner_instruction_sha256'], table['owner_asm_normalized_sha256'], span['host_sha256']]
        paths += [table['duplicate_assembly'], span['host_assembly']]
        symbols += [table['owner_original_symbol'], table['owner_c_symbol'], span['host_symbol']]
        require(isinstance(table['table_label'], str) and
                re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', table['table_label']), 'invalid table symbol')
    require(all(type(n) is int and 0 <= n < 2**32 and n % 4 == 0 for n in numbers),
            'V2 addresses and lengths must be unsigned word-aligned integers')
    require(all(isinstance(value, str) and re.fullmatch(r'[0-9a-f]{64}', value) for value in hashes),
            'expected SHA-256')
    require(all(isinstance(value, str) and re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', value)
                for value in symbols) and len(set(symbols)) == len(symbols),
            'owner and host symbols must be valid and distinct')
    require(len({t['table_label'] for t in tables}) == len(tables), 'duplicate compiler table')
    for path in paths:
        inside(root, path)
    require(len(set(paths)) == len(paths), 'overlapping retained/owner data paths')
    require(layout['begin'] < tables[0]['table_begin'], 'retained prefix must be nonempty')
    for i, (table, span) in enumerate(zip(tables, spans)):
        following = tables[i + 1]['table_begin'] if i + 1 < len(tables) else layout['end']
        require(table['table_begin'] < table['table_end'] == span['begin'] < span['end'] == following,
                'tables and retained spans must alternate with exact nonempty coverage')
        require(table['table_begin'] % 8 == table['table_end'] % 8 == 4,
                'supported native late alignment is four')
        require(table['owner_bytes'] > 0 and span['host_bytes'] >= span['end'] - span['begin'],
                'empty owner or host lacks native late-data capacity')
        require(table['owner_address'] + table['owner_bytes'] <= span['host_address'],
                'assembly host must follow its compiler owner')
        if i + 1 < len(tables):
            require(span['host_address'] + span['host_bytes'] <= tables[i + 1]['owner_address'],
                    'assembly host must precede the next compiler owner')
    raw = inside(root, layout['witness']).read_bytes()
    require(sha(raw) == layout['witness_sha256'], 'original ASM witness changed')
    witness = raw.decode('utf-8')
    decoded = original_bytes(witness, layout['begin'], layout['end'])
    require(sha(decoded) == layout['readonly_sha256'], 'original readonly bytes changed')
    bounds = []
    for table in tables:
        label = table['table_label']
        require(witness.count('nonmatching ' + label + '\n') == 1 and
                witness.count('enddlabel ' + label + '\n') == 1,
                'expected exactly one original table definition')
        start = witness.index('nonmatching ' + label + '\n')
        stop = witness.index('enddlabel ' + label, start) + len('enddlabel ' + label)
        fragment = witness[start:stop]
        table_bytes = original_bytes(fragment, table['table_begin'], table['table_end'])
        lo, hi = table['table_begin'] - layout['begin'], table['table_end'] - layout['begin']
        require(table_bytes == decoded[lo:hi], 'table bytes disagree with original section')
        targets = struct.unpack('>' + 'I' * (len(table_bytes) // 4), table_bytes)
        require(all(table['owner_address'] <= target < table['owner_address'] + table['owner_bytes']
                    for target in targets), 'table target leaves its original owner')
        # Retain V1's exact table-word/address validation, including directives.
        render(dict(layout, **table), witness)
        bounds.append((start, stop))
    require(all(bounds[i][1] < bounds[i + 1][0] for i in range(len(bounds) - 1)),
            'original table definitions differ from declared physical order')
    prefix = ('.section .rodata\n' + retained(witness[:bounds[0][0]])).encode('utf-8')
    require(original_bytes(prefix.decode(), layout['begin'], tables[0]['table_begin']) ==
            decoded[:tables[0]['table_begin'] - layout['begin']], 'prefix coverage mismatch')
    fragments = {}
    for i, span in enumerate(spans):
        stop = bounds[i + 1][0] if i + 1 < len(bounds) else len(witness)
        fragment = ('.section .late_rodata\n.late_rodata_alignment 4\n' +
                    retained(witness[bounds[i][1]:stop])).encode('utf-8')
        require(original_bytes(fragment.decode(), span['begin'], span['end']) ==
                decoded[span['begin'] - layout['begin']:span['end'] - layout['begin']],
                'retained span coverage mismatch')
        fragments[span['host_assembly']] = fragment
    return layout, decoded, prefix, fragments


def validate_source_v2(root, layout):
    source = inside(root, layout['source']).read_text(encoding='utf-8')
    positions = [source.index('#pragma GLOBAL_ASM("' + layout['prefix_assembly'] + '")')]
    for table, span in zip(layout['tables'], layout['late_spans']):
        # The existing guard requires exactly one unconditional C definition,
        # unconditional standalone host pragma, and no remaining owner pragma.
        validate_source(root, table_view(layout, table, span))
        tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
        code = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0])
                          if m[0].startswith(('/*', '//')) else m[0], source)
        owner = re.search(r'^[ \t]*[A-Za-z_][^;{}\n]*\b' + re.escape(table['owner_c_symbol']) +
                          r'\s*\([^;{}]*\)\s*\{', code, re.M)
        positions += [owner.start(), code.index('#pragma GLOBAL_ASM("' + span['host_assembly'] + '")')]
    require(all(a < b for a, b in zip(positions, positions[1:])),
            'compiler owners and original hosts must follow readonly physical order')


def original_span_host(layout, table, span, raw, fragment):
    original = host_text(table_view(layout, table, span), raw, fragment)
    addresses = re.findall(r'^\s*/\* [0-9A-F]+ ([0-9A-F]+) [0-9A-F]{8} \*/', original.decode(), re.M)
    require([int(value, 16) for value in addresses] ==
            list(range(span['host_address'], span['host_address'] + span['host_bytes'], 4)),
            'original host instruction address coverage changed')
    return original


def prepare_v2(root, config, module, binary, layout, decoded, prefix, fragments):
    raw = Path(binary).read_bytes()
    require(len(raw) >= 0x50 and raw[:4] == b'FORM' and raw[8:12] == b'MODU' and
            raw[0x18:0x1C] == b'COMM', 'invalid original module header')
    text_bytes, readonly_bytes = struct.unpack_from('>II', raw, 0x28)
    require(0x400000 + text_bytes == layout['begin'] and readonly_bytes == len(decoded),
            'original module section boundaries changed')
    require(raw[0x50 + text_bytes:0x50 + text_bytes + readonly_bytes] == decoded,
            'actual patched module readonly differs from witness')
    validate_source(root, layout)
    check_users(root, layout, decoded)
    for table, span in zip(layout['tables'], layout['late_spans']):
        host = inside(root, span['host_assembly'])
        if host.exists():
            original_span_host(layout, table, span, host.read_bytes(), fragments[span['host_assembly']])
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        require(monolithic.read_text(encoding='utf-8') == inside(root, layout['witness']).read_text(encoding='utf-8'),
                'unexpected monolithic readonly source')
    return {'root': root, 'config': config, 'module': module, 'binary': Path(binary),
            'layout': layout, 'prefix': prefix, 'suffix': fragments}


def apply_v2(plan):
    # Revalidate every owner, host, table and output before the first write.
    plan = prepare(plan['root'], plan['config'], plan['module'], plan['binary'])
    root, layout = plan['root'], plan['layout']
    outputs = [(inside(root, layout['prefix_assembly']), plan['prefix'])]
    for table, span in zip(layout['tables'], layout['late_spans']):
        host = inside(root, span['host_assembly'])
        require(host.is_file(), 'normal function extraction did not emit original host')
        fragment = plan['suffix'][span['host_assembly']]
        original = original_span_host(layout, table, span, host.read_bytes(), fragment)
        outputs.append((host, original + SUFFIX_MARKER + fragment))
    staged = []
    try:
        for path, contents in outputs:
            path.parent.mkdir(parents=True, exist_ok=True)
            temporary = path.with_name(path.name + '.readonly-layout.tmp')
            require(not temporary.exists(), 'temporary output already exists')
            temporary.write_bytes(contents)
            staged.append((temporary, path))
        for temporary, path in staged:
            os.replace(temporary, path)
    finally:
        for temporary, _ in staged:
            if temporary.exists():
                temporary.unlink()
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        monolithic.unlink()


def v3_witness_bounds(layout, witness):
    bounds = []
    for table in layout['tables']:
        label = table['table_label']
        require(witness.count('nonmatching ' + label + '\n') == 1 and
                witness.count('enddlabel ' + label + '\n') == 1,
                'expected exactly one V3 original table definition')
        start = witness.index('nonmatching ' + label + '\n')
        stop = witness.index('enddlabel ' + label, start) + len('enddlabel ' + label)
        bounds.append((start, stop))
    require(all(bounds[i][1] < bounds[i + 1][0] for i in range(len(bounds) - 1)),
            'V3 table definitions differ from declared physical order')
    return bounds


def v3_fragment(begin, text):
    # Native asm-processor alignment describes the actual start modulo eight,
    # not an invented padding requirement. Both phases are supported by IDO.
    alignment = 8 if begin % 8 == 0 else 4
    return ('.section .late_rodata\n.late_rodata_alignment ' + str(alignment) + '\n' +
            retained(text)).encode('utf-8')


def load_v3(root, layout, module):
    common = {'version', 'module', 'source', 'witness', 'witness_sha256',
              'readonly_sha256', 'begin', 'end', 'prefix_assembly',
              'monolithic_assembly', 'tables', 'late_spans'}
    table_keys = {'table_begin', 'table_end', 'table_label', 'owner_original_symbol',
                  'owner_c_symbol', 'duplicate_assembly', 'owner_address', 'owner_bytes',
                  'owner_instruction_sha256', 'owner_asm_normalized_sha256'}
    span_keys = {'begin', 'end', 'host_symbol', 'host_address', 'host_assembly',
                 'host_sha256', 'host_bytes'}
    require(set(layout) in (common, common | {'terminal_literal_tail'}, common | {'terminal_c_literals'}) and type(layout['version']) is int and
            layout['version'] == 3 and layout['module'] == module,
            'unsupported V3 metadata schema/module')
    tail = dyn_terminal_tail111100(root, layout)
    tables, spans = layout['tables'], layout['late_spans']
    require(isinstance(tables, list) and len(tables) > 0 and
            isinstance(spans, list) and len(spans) == len(tables),
            'each V3 compiler table requires one explicit following-span entry')
    paths = [layout[key] for key in ('witness', 'prefix_assembly', 'monolithic_assembly')]
    if tail is not None:
        paths.append(tail['assembly'])
    numbers = [layout['begin'], layout['end']]
    hashes = [layout['witness_sha256'], layout['readonly_sha256']]
    symbols = []
    inside(root, layout['source'])
    require(isinstance(layout['prefix_assembly'], str) and
            layout['prefix_assembly'].endswith('.rodata-prefix.s'),
            'prefix must not match monolithic *.rodata.s wildcard')
    for table, span in zip(tables, spans):
        require(isinstance(table, dict) and set(table) == table_keys and
                (span is None or isinstance(span, dict) and set(span) == span_keys),
                'unsupported V3 table/span schema')
        numbers += [table[key] for key in ('table_begin', 'table_end', 'owner_address', 'owner_bytes')]
        hashes += [table['owner_instruction_sha256'], table['owner_asm_normalized_sha256']]
        paths.append(table['duplicate_assembly'])
        symbols += [table['owner_original_symbol'], table['owner_c_symbol']]
        encoded = re.fullmatch(r'func_' + re.escape(module) + r'_([0-9A-Fa-f]{8})', table['owner_original_symbol'])
        require(encoded is not None and int(encoded[1], 16) == table['owner_address'],
                'V3 original owner symbol and address disagree')
        require(isinstance(table['table_label'], str) and
                re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', table['table_label']), 'invalid V3 table symbol')
        if span is not None:
            numbers += [span[key] for key in ('begin', 'end', 'host_address', 'host_bytes')]
            hashes.append(span['host_sha256'])
            paths.append(span['host_assembly'])
            symbols.append(span['host_symbol'])
    require(all(type(n) is int and 0 <= n < 2**32 and n % 4 == 0 for n in numbers),
            'V3 addresses and lengths must be unsigned word-aligned integers')
    require(all(isinstance(value, str) and re.fullmatch(r'[0-9a-f]{64}', value) for value in hashes),
            'expected V3 SHA-256')
    require(all(isinstance(value, str) and re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', value)
                for value in symbols) and len(set(symbols)) == len(symbols),
            'V3 owner and real host symbols must be valid and distinct')
    require(len({t['table_label'] for t in tables}) == len(tables), 'duplicate V3 compiler table')
    for path in paths:
        inside(root, path)
    require(len(set(paths)) == len(paths), 'overlapping V3 retained/owner data paths')
    require(layout['begin'] < tables[0]['table_begin'], 'V3 retained prefix must be nonempty')
    for i, (table, span) in enumerate(zip(tables, spans)):
        following = tables[i + 1]['table_begin'] if i + 1 < len(tables) else layout['end']
        require(table['table_begin'] < table['table_end'] <= following and table['owner_bytes'] > 0,
                'V3 tables must be nonempty and disjoint in physical order')
        if span is None:
            require(table['table_end'] == following or
                    (tail is not None and i == len(tables) - 1 and
                     table['table_end'] == tail['begin'] and following == tail['end']),
                    'null V3 span requires an adjacent table or the exact section end')
            if i + 1 < len(tables):
                require(table['owner_address'] + table['owner_bytes'] <= tables[i + 1]['owner_address'],
                        'adjacent V3 owners must follow text order')
        else:
            require(table['table_end'] == span['begin'] < span['end'] == following,
                    'V3 retained spans must cover the exact nonempty table gap')
            require(span['host_bytes'] >= span['end'] - span['begin'],
                    'V3 host lacks native late-data capacity')
            require(table['owner_address'] + table['owner_bytes'] <= span['host_address'],
                    'V3 assembly host must follow its compiler owner')
            if i + 1 < len(tables):
                require(span['host_address'] + span['host_bytes'] <= tables[i + 1]['owner_address'],
                        'V3 assembly host must precede next compiler owner')
    raw = inside(root, layout['witness']).read_bytes()
    require(sha(raw) == layout['witness_sha256'], 'V3 original ASM witness changed')
    witness = raw.decode('utf-8')
    decoded = original_bytes(witness, layout['begin'], layout['end'])
    require(sha(decoded) == layout['readonly_sha256'], 'V3 original readonly bytes changed')
    bounds = v3_witness_bounds(layout, witness)
    for table, (start, stop) in zip(tables, bounds):
        data = original_bytes(witness[start:stop], table['table_begin'], table['table_end'])
        lo, hi = table['table_begin'] - layout['begin'], table['table_end'] - layout['begin']
        require(data == decoded[lo:hi], 'V3 table bytes disagree with original section')
        targets = struct.unpack('>' + 'I' * (len(data) // 4), data)
        require(all(table['owner_address'] <= target < table['owner_address'] + table['owner_bytes']
                    for target in targets), 'V3 table target leaves its original owner')
        render(dict(layout, **table), witness)
    prefix = ('.section .rodata\n' + retained(witness[:bounds[0][0]])).encode('utf-8')
    require(original_bytes(prefix.decode(), layout['begin'], tables[0]['table_begin']) ==
            decoded[:tables[0]['table_begin'] - layout['begin']], 'V3 prefix coverage mismatch')
    fragments = {}
    for i, span in enumerate(spans):
        stop = bounds[i + 1][0] if i + 1 < len(bounds) else len(witness)
        contents = witness[bounds[i][1]:stop]
        if span is None:
            if tail is not None and i == len(spans) - 1:
                fragment = v4_island(tail['begin'], tail['end'], contents)
                data = original_bytes(fragment.decode(), tail['begin'], tail['end'])
                require(data == decoded[tail['begin'] - layout['begin']:tail['end'] - layout['begin']]
                        and sha(data) == tail['readonly_sha256'], 'DYN terminal literal coverage/hash changed')
                if not tail.get('c_owned'):
                    fragments[tail['assembly']] = fragment
            else:
                require(not retained(contents).strip(), 'adjacent V3 tables conceal retained contents')
            continue
        fragment = v3_fragment(span['begin'], contents)
        require(original_bytes(fragment.decode(), span['begin'], span['end']) ==
                decoded[span['begin'] - layout['begin']:span['end'] - layout['begin']],
                'V3 retained span coverage mismatch')
        fragments[span['host_assembly']] = fragment
    return layout, decoded, prefix, fragments


def validate_source_v3(root, layout):
    source = inside(root, layout['source']).read_text(encoding='utf-8')
    tail = dyn_terminal_tail111100(root, layout)
    tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
    code = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0])
                      if m[0].startswith(('/*', '//')) else m[0], source)
    prefix = '#pragma GLOBAL_ASM("' + layout['prefix_assembly'] + '")'
    require(code.count(prefix) == 1, 'V3 requires exactly one active retained prefix')
    positions = [code.index(prefix)]
    owner_offsets = []
    pragmas = {prefix}
    for table, span in zip(layout['tables'], layout['late_spans']):
        owner = table['owner_c_symbol']
        matches = list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\b' + re.escape(owner) +
                                  r'\s*\([^;{}]*\)\s*\{', code, re.M))
        require(len(matches) == 1, 'V3 requires exactly one complete C table owner')
        owner_offsets.append(matches[0].start())
        positions.append(matches[0].start())
        for name in (table['owner_original_symbol'], owner):
            require(not re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(name) + r'\.s"\)', code),
                    'V3 owner still assembly-backed')
        if span is not None:
            host = '#pragma GLOBAL_ASM("' + span['host_assembly'] + '")'
            require(code.count(host) == 1, 'V3 active original host missing; host migration needs a new proved layout')
            pragmas.add(host)
            positions.append(code.index(host))
    if tail is not None and not tail.get('c_owned'):
        pragma = '#pragma GLOBAL_ASM("' + tail['assembly'] + '")'
        require(code.count(pragma) == 1, 'DYN terminal tail requires one active data-only pragma')
        # Complete-body brace accounting is the existing V4 spelling, with
        # strings/comments masked while preserving exact source positions.
        braces = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), source)
        depth, cursor = 1, matches[0].end()
        while depth and cursor < len(braces):
            depth += (braces[cursor] == '{') - (braces[cursor] == '}')
            cursor += 1
        require(depth == 0, 'DYN terminal owner body is incomplete')
        position = code.index(pragma)
        require(cursor <= position and not code[cursor:position].strip(),
                'DYN terminal tail must immediately follow the complete final owner body')
        positions.extend([cursor, position])
        pragmas.add(pragma)
    if tail is not None and tail.get('c_owned'):
        natural_owner = dyn_natural_source113100(root, layout, source, code)
        owner_offsets.append(natural_owner)
        positions.append(natural_owner)
    depth = offset = 0
    for line in code.splitlines(keepends=True):
        directive = re.match(r'^\s*#\s*(if|ifdef|ifndef|endif)\b', line)
        if directive:
            depth += -1 if directive[1] == 'endif' else 1
            require(depth >= 0, 'unbalanced V3 source conditionals')
        for pragma in pragmas:
            if pragma in line:
                require(depth == 0 and line.strip() == pragma, 'V3 ownership pragma must be unconditional standalone source')
        if any(offset <= position < offset + len(line) for position in owner_offsets):
            require(depth == 0, 'V3 C table owner must be unconditional')
        offset += len(line)
    require(depth == 0, 'unbalanced V3 source conditionals')
    definitions = list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\([^;{}]*\)\s*\{', code, re.M))
    require(all(positions[0] < m.start() for m in definitions), 'V3 prefix must precede every function definition')
    require(all(a < b for a, b in zip(positions, positions[1:])),
            'V3 compiler owners and real hosts must follow readonly physical order')


def v3_original_host(root, layout, index, raw, fragment):
    table, span = layout['tables'][index], layout['late_spans'][index]
    require(span is not None, 'adjacent V3 tables cannot invent an assembly host')
    if SUFFIX_MARKER in raw:
        require(raw.count(SUFFIX_MARKER) == 1, 'duplicate V3 managed suffix')
        original, existing = raw.split(SUFFIX_MARKER)
        allowed = [fragment]
        # A previous ownership layout may have hosted the now compiler-owned
        # adjacent table as original data. Accept only that exact witness span,
        # never another path/content merely bearing a managed suffix marker.
        j = index + 1
        if j < len(layout['tables']) and layout['late_spans'][j] is None:
            while j < len(layout['tables']) and layout['late_spans'][j] is None:
                j += 1
            witness = inside(root, layout['witness']).read_text(encoding='utf-8')
            bounds = v3_witness_bounds(layout, witness)
            # A newly compiler-owned terminal table has no following ASM host.
            # Migrate only the exact old witness suffix, through the real end.
            stop = bounds[j][0] if j < len(bounds) else len(witness)
            end = layout['tables'][j]['table_begin'] if j < len(bounds) else layout['end']
            transition = v3_fragment(span['begin'], witness[bounds[index][1]:stop])
            decoded = original_bytes(transition.decode(), span['begin'], end)
            all_original = original_bytes(witness, layout['begin'], layout['end'])
            require(decoded == all_original[span['begin'] - layout['begin']:
                                           end - layout['begin']],
                    'V3 transition is not exact original readonly')
            allowed.append(transition)
        require(existing in allowed, 'V3 managed suffix differs from exact original retained/transition spans')
    else:
        original = raw
    return original_span_host(layout, table, span, original, fragment)


def check_users_v3(root, layout, decoded):
    _, original, prefix, fragments = load_v3(root, layout, layout['module'])
    require(original == decoded, 'V3 user scan original readonly disagreement')
    allowed = []
    path = inside(root, layout['prefix_assembly'])
    if path.exists():
        require(path.read_bytes() == prefix, 'V3 generated prefix is not the exact original retained prefix')
        allowed.append(layout['prefix_assembly'])
    for i, span in enumerate(layout['late_spans']):
        if span is None:
            continue
        path = inside(root, span['host_assembly'])
        if path.exists():
            v3_original_host(root, layout, i, path.read_bytes(), fragments[span['host_assembly']])
            allowed.append(span['host_assembly'])
    tail = dyn_terminal_tail111100(root, layout)
    if tail is not None:
        path = inside(root, tail['assembly'])
        if path.exists():
            if tail.get('c_owned'):
                dyn_natural_obsolete113100(root, layout, path)
            else:
                require(path.is_file() and path.read_bytes() == fragments[tail['assembly']],
                        'DYN terminal generated literal data changed')
            allowed.append(tail['assembly'])
    for table in layout['tables']:
        # Existing exact duplicate/unused-owner and real-reference guards are
        # reused unchanged. There is no fictitious host for adjacent tables.
        check_users(root, dict(layout, **table, version=1), decoded, allowed)


def prepare_v3(root, config, module, binary, layout, decoded, prefix, fragments):
    raw = Path(binary).read_bytes()
    require(len(raw) >= 0x50 and raw[:4] == b'FORM' and raw[8:12] == b'MODU' and
            raw[0x18:0x1C] == b'COMM', 'invalid V3 original patched module header')
    text_bytes, readonly_bytes = struct.unpack_from('>II', raw, 0x28)
    require(0x400000 + text_bytes == layout['begin'] and readonly_bytes == len(decoded),
            'V3 original module section boundaries changed')
    require(raw[0x50 + text_bytes:0x50 + text_bytes + readonly_bytes] == decoded,
            'V3 actual patched readonly differs from original witness')
    validate_source_v3(root, layout)
    check_users_v3(root, layout, decoded)
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        require(monolithic.read_text(encoding='utf-8') == inside(root, layout['witness']).read_text(encoding='utf-8'),
                'unexpected V3 monolithic readonly source')
    return {'root': root, 'config': config, 'module': module, 'binary': Path(binary),
            'layout': layout, 'prefix': prefix, 'suffix': fragments}


def apply_v3(plan):
    plan = prepare(plan['root'], plan['config'], plan['module'], plan['binary'])
    root, layout = plan['root'], plan['layout']
    outputs = [(inside(root, layout['prefix_assembly']), plan['prefix'])]
    for i, span in enumerate(layout['late_spans']):
        if span is None:
            continue
        host = inside(root, span['host_assembly'])
        require(host.is_file(), 'normal V3 extraction did not emit original host')
        fragment = plan['suffix'][span['host_assembly']]
        original = v3_original_host(root, layout, i, host.read_bytes(), fragment)
        outputs.append((host, original + SUFFIX_MARKER + fragment))
    tail = dyn_terminal_tail111100(root, layout)
    if tail is not None and not tail.get('c_owned'):
        outputs.append((inside(root, tail['assembly']), plan['suffix'][tail['assembly']]))
    staged = []
    try:
        for path, contents in outputs:
            path.parent.mkdir(parents=True, exist_ok=True)
            temporary = path.with_name(path.name + '.readonly-layout.tmp')
            require(not temporary.exists(), 'V3 temporary output already exists')
            temporary.write_bytes(contents)
            staged.append((temporary, path))
        for temporary, path in staged:
            os.replace(temporary, path)
    finally:
        for temporary, _ in staged:
            if temporary.exists():
                temporary.unlink()
    if tail is not None and tail.get('c_owned'):
        obsolete = inside(root, tail['assembly'])
        if obsolete.exists():
            dyn_natural_obsolete113100(root, layout, obsolete)
            obsolete.unlink()
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        monolithic.unlink()



def v4_island(begin, end, text):
    """Literal non-relocating words only: reserve data, never fabricate TEXT."""
    fragment = '.section .rodata\n' + retained(text)
    lines = re.sub(r'/\*.*?\*/', '', fragment, flags=re.S).splitlines()
    labels = []
    words = 0
    for line in lines[1:]:
        line = line.strip()
        if not line:
            continue
        label = re.fullmatch(r'glabel ([A-Za-z_][A-Za-z0-9_]*)', line)
        if label:
            labels.append(label[1])
            continue
        require(re.fullmatch(r'\.word 0x[0-9A-Fa-f]{8}', line) is not None,
                'V4 island must contain only literal non-relocating words and labels')
        words += 1
    require(labels and len(labels) == len(set(labels)) and words * 4 == end - begin,
            'V4 island labels/word extent changed')
    original_bytes(fragment, begin, end)
    return fragment.encode('utf-8')


def validate_three_owner_order_contract(c,layout):
    keys={'schema','source_object','spans','inverse_spans','floats','affected_references_sha256','operand_change_word_hashes','readonly_prefix_sha256','dispatch_table_sha256','first_table_sha256','retained_island_sha256','second_table_sha256','original_readonly_witness_sha256','original_witness_table_target_pairs','original_non_table_RO_records','coordinate_scope'}
    require(isinstance(c,dict)and set(c)==keys and c['schema']==2 and c['source_object']=='build/src/modules/race.o','invalid three-owner object-order contract')
    require(c['coordinate_scope']=='ORIGINAL_ASM_ADDRESS_WITNESS_NOT_PACKED_RUNTIME','three-owner readonly coordinate scope changed')
    require(c['spans']==[[1484,1508,1528],[1508,1528,1484],[1528,1552,1504]]and c['inverse_spans']==[[1528,1552,1484],[1484,1504,1508],[1504,1528,1528]],'three-owner spans/inverse changed')
    require(c['floats']==['D_race_004047'+s for s in('C8','CC','D0','D4','D8','DC')],'three-owner float identities changed')
    require(all(isinstance(c[k],str)and re.fullmatch(r'[0-9a-f]{64}',c[k])for k in keys if k.endswith('_sha256')),'invalid three-owner digest')
    require(c['original_readonly_witness_sha256']==layout['readonly_sha256'],'three-owner original ASM witness changed')
    table_shape=[(q['table_begin'],q['table_end'],q['owner_original_symbol'],q['owner_c_symbol'],q['owner_address'],q['owner_bytes'])for q in layout['tables']]
    require(table_shape==[(0x40479C,0x4047B0,'func_race_00403358','raceDispatchStateAndUpdateOverlays',0x403358,308),(0x4047B0,0x4047C8,'func_race_004038B0','racePlayPendingTrackSound',0x4038B0,700),(0x4047E0,0x404800,'func_race_00403B6C','racePlayPendingPlayerMessageSound',0x403B6C,1240)],'three-owner table/positive extent association changed')
    require(len(layout['retained_islands'])==3 and layout['retained_islands'][0]is None and layout['retained_islands'][2]is None,'three-owner explicit island count changed')
    island=layout['retained_islands'][1];require(isinstance(island,dict)and(island['begin'],island['end'])==(0x4047C8,0x4047E0),'three-owner exact retained island changed')
    expected_sites=list(range(1484,1528,4))+list(range(1552,1584,4))
    pairs=c['original_witness_table_target_pairs'];require(isinstance(pairs,list)and len(pairs)==19 and all(isinstance(q,list)and len(q)==2 and all(type(v)is int for v in q)for q in pairs),'invalid three-owner witness table records')
    require([q[0]for q in pairs]==expected_sites,'three-owner exact table site inventory changed')
    for site,target in pairs:
        owners=[q for q in layout['tables']if q['table_begin']-layout['begin']<=site<q['table_end']-layout['begin']]
        require(len(owners)==1 and owners[0]['owner_address']<=target<owners[0]['owner_address']+owners[0]['owner_bytes']and target%4==0,'three-owner table target leaves exact owner')
    other=c['original_non_table_RO_records'];require(isinstance(other,list)and len(other)==10 and len({q['offset']for q in other})==10 and all(q['section']=='.rodata'and q['offset']not in expected_sites and 0<=q['offset']<1484 and q['kind']==2 and q['explicit_addend']is None for q in other),'three-owner exact other readonly records changed')
    operands=c['operand_change_word_hashes'];require(isinstance(operands,list)and len(operands)==2,'three-owner full-word change closure changed')
    require(all(set(q)=={'section','site','kind','before_sha256','after_sha256'}and q['section']=='.text'and type(q['site'])is int and q['site']%4==0 and 0<=q['site']<16848 and q['kind']==6 and all(isinstance(q[k],str)and re.fullmatch(r'[0-9a-f]{64}',q[k])for k in('before_sha256','after_sha256'))for q in operands),'invalid three-owner exact word hash records')
    require(len({q['site']for q in operands})==2,'duplicate three-owner changed word')

def load_v4(root, layout, module):
    common = {'version', 'module', 'source', 'witness', 'witness_sha256',
              'readonly_sha256', 'begin', 'end', 'prefix_assembly',
              'monolithic_assembly', 'tables', 'retained_islands'}
    table_keys = {'table_begin', 'table_end', 'table_label', 'owner_original_symbol',
                  'owner_c_symbol', 'duplicate_assembly', 'owner_address', 'owner_bytes',
                  'owner_instruction_sha256', 'owner_asm_normalized_sha256'}
    island_keys = {'begin', 'end', 'assembly', 'readonly_sha256'}
    require(set(layout) in (common, common | {'object_ordering'}) and type(layout['version']) is int and
            layout['version'] == 4 and layout['module'] == module,
            'unsupported V4 metadata schema/module')
    if 'object_ordering' in layout:
        order=layout['object_ordering']
        require(isinstance(order,dict) and set(order)=={'helper','helper_sha256','contract'}, 'invalid V4 object-order schema')
        require(module=='race' and layout['source']=='src/modules/race.c' and order['helper']=='tools/reorderRaceReadonly.py', 'object-order scope is only the reviewed RACE source')
        require(isinstance(order['helper_sha256'],str) and re.fullmatch(r'[0-9a-f]{64}',order['helper_sha256']), 'invalid object-order helper hash')
        c=order['contract']
        if isinstance(c,dict)and c.get('schema')==2:
            validate_three_owner_order_contract(c,layout)
        else:
            keys={'schema','source_object','spans','floats','affected_references','readonly_prefix_sha256','first_table_sha256','retained_island_sha256','second_table_sha256','native_readonly_sha256','table_native_target_pairs','original_non_table_RO_records'}
            require(isinstance(c,dict) and set(c)==keys and c['schema']==1 and c['source_object']=='build/src/modules/race.o', 'invalid object-order contract')
            require(c['spans']==[[1504,1528,1528],[1528,1552,1504]] and c['native_readonly_sha256']==layout['readonly_sha256'], 'object-order spans/native bytes changed')
            require(c['floats']==['D_race_004047'+s for s in ('C8','CC','D0','D4','D8','DC')] and len(c['affected_references'])==7, 'object-order symbol/reference closure changed')
            require(all(isinstance(c[k],str) and re.fullmatch(r'[0-9a-f]{64}',c[k]) for k in keys if k.endswith('_sha256')), 'invalid object-order storage hash')
            require(len(c['table_native_target_pairs'])==14 and len(c['original_non_table_RO_records'])==15, 'object-order complete readonly records changed')
    tables, islands = layout['tables'], layout['retained_islands']
    require(isinstance(tables, list) and len(tables) > 0 and
            isinstance(islands, list) and len(islands) == len(tables),
            'each V4 table requires an explicit following-island entry')
    paths = [layout[key] for key in ('source', 'witness', 'prefix_assembly', 'monolithic_assembly')]
    numbers = [layout['begin'], layout['end']]
    hashes = [layout['witness_sha256'], layout['readonly_sha256']]
    symbols = []
    require(isinstance(layout['prefix_assembly'], str) and
            layout['prefix_assembly'].endswith('.rodata-prefix.s'),
            'V4 prefix must not match monolithic *.rodata.s wildcard')
    for table, island in zip(tables, islands):
        require(isinstance(table, dict) and set(table) == table_keys and
                (island is None or isinstance(island, dict) and set(island) == island_keys),
                'unsupported V4 table/island schema')
        numbers += [table[key] for key in ('table_begin', 'table_end', 'owner_address', 'owner_bytes')]
        hashes += [table['owner_instruction_sha256'], table['owner_asm_normalized_sha256']]
        paths.append(table['duplicate_assembly'])
        symbols += [table['owner_original_symbol'], table['owner_c_symbol']]
        encoded = re.fullmatch(r'func_' + re.escape(module) + r'_([0-9A-Fa-f]{8})', table['owner_original_symbol'])
        require(encoded is not None and int(encoded[1], 16) == table['owner_address'],
                'V4 original owner symbol and address disagree')
        require(isinstance(table['table_label'], str) and
                re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', table['table_label']), 'invalid V4 table symbol')
        if island is not None:
            numbers += [island['begin'], island['end']]
            hashes.append(island['readonly_sha256'])
            paths.append(island['assembly'])
            require(isinstance(island['assembly'], str) and island['assembly'].endswith('.rodata-island.s'),
                    'V4 island must use a data-only .rodata-island.s path')
    require(all(type(n) is int and 0 <= n < 2**32 and n % 4 == 0 for n in numbers),
            'V4 addresses and lengths must be unsigned word-aligned integers')
    require(all(isinstance(value, str) and re.fullmatch(r'[0-9a-f]{64}', value) for value in hashes),
            'expected V4 SHA-256')
    require(all(isinstance(value, str) and re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', value)
                for value in symbols) and len(set(symbols)) == len(symbols),
            'V4 owner symbols must be valid and distinct')
    require(len({t['table_label'] for t in tables}) == len(tables), 'duplicate V4 compiler table')
    for path in paths:
        inside(root, path)
    require(len(set(paths)) == len(paths), 'overlapping V4 source/retained/owner paths')
    require(layout['begin'] < tables[0]['table_begin'], 'V4 retained prefix must be nonempty')
    for i, (table, island) in enumerate(zip(tables, islands)):
        following = tables[i + 1]['table_begin'] if i + 1 < len(tables) else layout['end']
        require(table['table_begin'] < table['table_end'] <= following and table['owner_bytes'] > 0,
                'V4 tables must be nonempty and disjoint in physical order')
        if i + 1 < len(tables):
            require(table['owner_address'] + table['owner_bytes'] <= tables[i + 1]['owner_address'],
                    'V4 C owners must follow nonoverlapping text order')
        if island is None:
            require(table['table_end'] == following, 'null V4 island conceals retained bytes')
        else:
            require(table['table_end'] == island['begin'] < island['end'] == following,
                    'V4 island must cover the complete exact table gap')
    raw = inside(root, layout['witness']).read_bytes()
    require(sha(raw) == layout['witness_sha256'], 'V4 original ASM witness changed')
    witness = raw.decode('utf-8')
    decoded = original_bytes(witness, layout['begin'], layout['end'])
    require(sha(decoded) == layout['readonly_sha256'], 'V4 original readonly bytes changed')
    bounds = v3_witness_bounds(layout, witness)
    for table, (start, stop) in zip(tables, bounds):
        data = original_bytes(witness[start:stop], table['table_begin'], table['table_end'])
        lo, hi = table['table_begin'] - layout['begin'], table['table_end'] - layout['begin']
        require(data == decoded[lo:hi], 'V4 table differs from complete original section')
        targets = struct.unpack('>' + 'I' * (len(data) // 4), data)
        require(all(table['owner_address'] <= target < table['owner_address'] + table['owner_bytes']
                    for target in targets), 'V4 table target leaves its original owner')
        render(dict(layout, **table), witness)
    prefix = ('.section .rodata\n' + retained(witness[:bounds[0][0]])).encode('utf-8')
    require(original_bytes(prefix.decode(), layout['begin'], tables[0]['table_begin']) ==
            decoded[:tables[0]['table_begin'] - layout['begin']], 'V4 prefix coverage mismatch')
    fragments = {}
    for i, island in enumerate(islands):
        stop = bounds[i + 1][0] if i + 1 < len(bounds) else len(witness)
        contents = witness[bounds[i][1]:stop]
        if island is None:
            require(not retained(contents).strip(), 'adjacent V4 tables conceal original contents')
            continue
        fragment = v4_island(island['begin'], island['end'], contents)
        data = original_bytes(fragment.decode(), island['begin'], island['end'])
        require(data == decoded[island['begin'] - layout['begin']:island['end'] - layout['begin']]
                and sha(data) == island['readonly_sha256'], 'V4 island coverage/hash mismatch')
        fragments[island['assembly']] = fragment
    return layout, decoded, prefix, fragments


def validate_source_v4(root, layout):
    source = inside(root, layout['source']).read_text(encoding='utf-8')
    tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
    code = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0])
                      if m[0].startswith(('/*', '//')) else m[0], source)
    prefix = '#pragma GLOBAL_ASM("' + layout['prefix_assembly'] + '")'
    require(code.count(prefix) == 1, 'V4 requires exactly one active retained prefix')
    positions = [code.index(prefix)]
    owner_offsets = []
    pragmas = {prefix}
    # Brace counting uses masked strings as well as comments; source positions stay exact.
    braces = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), source)
    for table, island in zip(layout['tables'], layout['retained_islands']):
        owner = table['owner_c_symbol']
        matches = list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\b' + re.escape(owner) +
                                  r'\s*\([^;{}]*\)\s*\{', code, re.M))
        require(len(matches) == 1, 'V4 requires exactly one complete C table owner')
        match = matches[0]
        owner_offsets.append(match.start())
        positions.append(match.start())
        depth, cursor = 1, match.end()
        while depth and cursor < len(braces):
            depth += (braces[cursor] == '{') - (braces[cursor] == '}')
            cursor += 1
        require(depth == 0, 'V4 unterminated C owner body')
        positions.append(cursor)
        for name in (table['owner_original_symbol'], owner):
            require(not re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(name) + r'\.s"\)', code),
                    'V4 owner still assembly-backed')
        if island is not None:
            pragma = '#pragma GLOBAL_ASM("' + island['assembly'] + '")'
            require(code.count(pragma) == 1, 'V4 requires exactly one active data-only island')
            pragmas.add(pragma)
            positions.append(code.index(pragma))
    depth = offset = 0
    for line in code.splitlines(keepends=True):
        directive = re.match(r'^\s*#\s*(if|ifdef|ifndef|endif)\b', line)
        if directive:
            depth += -1 if directive[1] == 'endif' else 1
            require(depth >= 0, 'unbalanced V4 source conditionals')
        for pragma in pragmas:
            if pragma in line:
                require(depth == 0 and line.strip() == pragma, 'V4 ownership pragma must be unconditional standalone source')
        if any(offset <= position < offset + len(line) for position in owner_offsets):
            require(depth == 0, 'V4 C table owner must be unconditional')
        offset += len(line)
    require(depth == 0, 'unbalanced V4 source conditionals')
    definitions = list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\([^;{}]*\)\s*\{', code, re.M))
    require(all(positions[0] < m.start() for m in definitions), 'V4 prefix must precede every function definition')
    require(all(a < b for a, b in zip(positions, positions[1:])),
            'V4 owners and data-only islands must follow complete body/readonly order')


def check_users_v4(root, layout, decoded):
    _, original, prefix, fragments = load_v4(root, layout, layout['module'])
    require(original == decoded, 'V4 user scan original readonly disagreement')
    allowed = []
    for name, contents in [(layout['prefix_assembly'], prefix), *fragments.items()]:
        path = inside(root, name)
        if path.exists():
            require(path.is_file() and path.read_bytes() == contents, 'V4 generated retained data changed')
            allowed.append(name)
    for table in layout['tables']:
        check_users(root, dict(layout, **table, version=1), decoded, allowed)


def prepare_v4(root, config, module, binary, layout, decoded, prefix, fragments):
    raw = Path(binary).read_bytes()
    require(len(raw) >= 0x50 and raw[:4] == b'FORM' and raw[8:12] == b'MODU' and
            raw[0x18:0x1C] == b'COMM', 'invalid V4 original patched module header')
    text_bytes, readonly_bytes = struct.unpack_from('>II', raw, 0x28)
    require(0x400000 + text_bytes == layout['begin'] and readonly_bytes == len(decoded),
            'V4 original module section boundaries changed')
    require(raw[0x50 + text_bytes:0x50 + text_bytes + readonly_bytes] == decoded,
            'V4 actual patched readonly differs from original witness')
    validate_source_v4(root, layout)
    check_users_v4(root, layout, decoded)
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        require(monolithic.read_bytes() == inside(root, layout['witness']).read_bytes(),
                'unexpected V4 monolithic readonly source')
    return {'root': root, 'config': config, 'module': module, 'binary': Path(binary),
            'layout': layout, 'prefix': prefix, 'suffix': fragments}


def apply_v4(plan):
    plan = prepare(plan['root'], plan['config'], plan['module'], plan['binary'])
    root, layout = plan['root'], plan['layout']
    outputs = [(inside(root, layout['prefix_assembly']), plan['prefix'])]
    outputs += [(inside(root, name), contents) for name, contents in plan['suffix'].items()]
    staged = []
    try:
        for path, contents in outputs:
            path.parent.mkdir(parents=True, exist_ok=True)
            temporary = path.with_name(path.name + '.readonly-layout.tmp')
            require(not temporary.exists() and not temporary.is_symlink(), 'V4 temporary output already exists')
            temporary.write_bytes(contents)
            staged.append((temporary, path))
        for temporary, path in staged:
            os.replace(temporary, path)
    finally:
        for temporary, _ in staged:
            if temporary.exists():
                temporary.unlink()
    monolithic = inside(root, layout['monolithic_assembly'])
    if monolithic.exists():
        monolithic.unlink()




def uvterra_duplicate_scalar_transform(raw_compiler_elf, readonly_source):
    """Module-scoped bridge; transformed output still requires NORMAL/native gates."""
    import hashlib
    import json
    import re
    import struct

    CONTRACT_SHA = '411220cd41a59c9affae995f23367ecb1efddb506a5c4f4d7469ffbe6499b879'
    OWNER_SHA = '36796a86b164c8e0bf7283b0569bf9db27da681c3453ff0b2dbd47da9828f0b8'
    TEXT_SHA = '3e128c671f8de2b2566517dc793b50a3a2f3d5e51852325695b62602fec02937'
    OWNER_DATA_SHA = '33c316ff34e2d830efbfdc2bfa73990a567434e4eb9fda67763b7224d24fa6ad'
    NAME = 'D_uvterra_rom_0040D6CC'
    POOL = bytes.fromhex('3eaa7efa') + bytes(12)
    SITES = ((25384, 5), (25388, 6))
    LIMIT = 262144


    class BridgeError(ValueError):
        pass


    def require(ok, why):
        if not ok:
            raise BridgeError(why)


    def sha(data):
        return hashlib.sha256(data).hexdigest()


    def unique_json_pairs(pairs):
        result = {}
        for key, value in pairs:
            require(key not in result, 'duplicate JSON key')
            result[key] = value
        return result


    def owner_proof(source, contract_bytes):
        """Authenticate and decode this one repository readonly witness, not an ELF."""
        require(type(contract_bytes) is bytes and len(contract_bytes) <= 4096 and
                sha(contract_bytes) == CONTRACT_SHA, 'exact bounded public contract')
        contract = json.loads(contract_bytes, object_pairs_hook=unique_json_pairs)
        require(type(source) is bytes and len(source) == 9769 and sha(source) == OWNER_SHA,
                'unchanged repository readonly source')
        text = source.decode('utf-8')
        require(text.encode('utf-8') == source, 'literal UTF8 owner source')
        begin, end = contract['owner_begin'], contract['owner_end']
        require(end - begin == 960 and begin + 892 == 0x40D6CC, 'owner coordinates')
        decoded = [None] * 960
        lines = text.splitlines()
        for index, line in enumerate(lines):
            match = re.search(r'/\* [0-9A-F]+ ([0-9A-F]+) ([0-9A-F]{8}) \*/\s*\.word\s+(\S+)', line)
            if match:
                address = int(match[1], 16)
                raw = bytes.fromhex(match[2])
                operand = match[3]
                try:
                    value = int(operand, 16) if operand.startswith('0x') else int(operand.rsplit('_', 1)[1], 16)
                except (ValueError, IndexError) as exc:
                    raise BridgeError('unsupported readonly word operand') from exc
                require(int.from_bytes(raw, 'big') == value, 'word annotation/operand disagree')
            else:
                match = re.search(r'/\* [0-9A-F]+ ([0-9A-F]+) \*/\s*\.asciz', line)
                if not match:
                    continue
                require(index + 1 < len(lines), 'missing string byte annotation')
                tail = re.fullmatch(r'\s*/\* ([0-9A-F]+) \*/\s*', lines[index + 1])
                require(tail is not None and len(tail[1]) % 2 == 0,
                        'bounded literal original string bytes')
                address, raw = int(match[1], 16), bytes.fromhex(tail[1])
            for delta, value in enumerate(raw):
                at = address - begin + delta
                require(0 <= at < 960 and decoded[at] is None,
                        'readonly annotation gap/overlap/range')
                decoded[at] = value
        require(None not in decoded, 'full960-byte owner annotation coverage')
        data = bytes(decoded)
        require(sha(data) == OWNER_DATA_SHA and data[892:896] == POOL[:4],
                'full original owner and scalar contents')
        labels = list(re.finditer(r'(?m)^dlabel ' + re.escape(NAME) + r'\s*$', text))
        require(len(labels) == 1, 'unique named scalar label')
        stop = text.find('enddlabel ' + NAME, labels[0].end())
        require(stop >= 0, 'named scalar closing label')
        block = text[labels[0].end():stop]
        words = re.findall(r'/\* [0-9A-F]+ ([0-9A-F]+) ([0-9A-F]{8}) \*/\s*\.word\s+(\S+)', block)
        require(words == [('0040D6CC', '3EAA7EFA', '0x3EAA7EFA')] and
                not any(x in block for x in ('.space', '.asciz', '.ascii', '.align')),
                'exact named4-byte scalar extent, not an owning array')
        return contract, dict(source_sha256=OWNER_SHA, section_sha256=OWNER_DATA_SHA,
                              owner_offset=892, owner_bytes=4, allocated_owner_bytes=960,
                              proof='repository readonly annotations/operands and bounded contract')


    def elf_tables(raw):
        """Bounded structural reader, used only by this recipe and later controls."""
        require(type(raw) is bytes and 52 <= len(raw) <= LIMIT, 'ELF byte bound')
        h = struct.unpack_from('>16sHHIIIIIHHHHHH', raw)
        ident, etype, machine, version, entry, phoff, shoff, flags, ehsize, phsize, phnum, shsize, shnum, shstr = h
        require(ident[:7] == b'\x7fELF\x01\x02\x01' and ident[7] in (0, 3),
                'ELF32 big endian version1')
        require(etype == 1 and machine == 8 and version == 1 and entry == 0,
                'MIPS relocatable object only')
        # Exact IDO -32 recipe: MIPS2+noreorder, with no ELF O32 ABI tag.
        # The compiler -32 contract supplies O32 context; flags alone do not.
        require(flags == 0x10000001, 'exact pinned IDO recipe flags')
        require(phoff == 0 and phnum == 0 and phsize == 0 and ehsize == 52 and
                shsize == 40 and 1 < shnum <= 32 and 0 < shstr < shnum and
                shoff >= 52 and shoff + 40 * shnum <= len(raw), 'bounded section table')
        sections = [list(struct.unpack_from('>10I', raw, shoff + 40 * i))
                    for i in range(shnum)]
        require(sections[0] == [0] * 10, 'no extended section numbering')

        def payload(index):
            s = sections[index]
            require(s[3] == 0 and s[8] in (0, 1, 2, 4, 8, 16, 32), 'section address/alignment')
            require(not (s[2] & 0x80), 'no SHF_LINK_ORDER')
            if s[1] in (0, 8):
                return b''
            require(s[4] >= 52 and s[4] <= len(raw) and s[5] <= len(raw) - s[4],
                    'section payload bound')
            require(not s[9] or s[5] % s[9] == 0, 'section entry extent')
            return raw[s[4]:s[4] + s[5]]

        data = [payload(i) for i in range(shnum)]
        occupied = sorted((s[4], s[4] + s[5]) for s in sections
                          if s[1] not in (0, 8) and s[5])
        occupied += [(0, 52), (shoff, shoff + 40 * shnum)]
        occupied.sort()
        require(all(a[1] <= b[0] for a, b in zip(occupied, occupied[1:])),
                'overlapping payload/header regions')

        def string(blob, offset):
            require(0 <= offset < len(blob), 'string index')
            end = blob.find(b'\0', offset)
            require(end >= offset and end - offset <= 4096, 'bounded NUL string')
            try:
                return blob[offset:end].decode('ascii')
            except UnicodeError as exc:
                raise BridgeError('non-ASCII ELF name') from exc

        require(sections[shstr][1] == 3, 'section-name string table')
        names = [string(data[shstr], s[0]) for s in sections]
        require(len(names) == len(set(names)), 'unique section names')
        st = [i for i, s in enumerate(sections) if s[1] == 2]
        require(len(st) == 1, 'one symtab')
        si = st[0]
        ss = sections[si]
        require(ss[9] == 16 and ss[5] % 16 == 0 and 1 <= ss[5] // 16 <= 512 and
                0 < ss[6] < shnum and sections[ss[6]][1] == 3 and ss[6] != shstr,
                'bounded separate symbol strings')
        symbols = [struct.unpack_from('>IIIBBH', data[si], i)
                   for i in range(0, len(data[si]), 16)]
        require(symbols[0] == (0, 0, 0, 0, 0, 0), 'mandatory null symbol')
        # Only ordinary section indices, SHN_UNDEF(0), ABS and COMMON are supported.
        # SHN_XINDEX and every other reserved section index are deliberately rejected.
        require(all(s[5] < shnum or s[5] in (0xFFF1, 0xFFF2) for s in symbols),
                'unsupported symbol section index')
        require(0 < ss[7] <= len(symbols), 'local/global boundary')
        require(all((x[3] >> 4 == 0) == (i < ss[7]) for i, x in enumerate(symbols)),
                'literal local/global symbol order')
        symbol_names = [string(data[ss[6]], s[0]) for s in symbols]
        rels = []
        for ri, s in enumerate(sections):
            require(s[1] != 4, 'RELA unsupported for this REL-only recipe')
            if s[1] != 9:
                continue
            require(s[6] == si and 0 < s[7] < shnum and s[9] == 8,
                    'REL table symbol/target links')
            for off in range(0, len(data[ri]), 8):
                site, info = struct.unpack_from('>II', data[ri], off)
                require(info >> 8 < len(symbols) and site % 4 == 0 and
                        site + 4 <= sections[s[7]][5], 'REL symbol/site range')
                rels.append((ri, off, site, info >> 8, info & 255))
        require(len(rels) <= 2048, 'REL row cap')
        return dict(header=h, sections=sections, data=data, names=names, symtab=si,
                    strtab=ss[6], symbols=symbols, symbol_names=symbol_names, rels=rels)


    def transform(raw_compiler_elf, readonly_source, contract_bytes):
        """Return bytes/report only. Calling code owns any separately admitted write."""
        raw = raw_compiler_elf
        require(type(raw) is bytes and 52 <= len(raw) <= LIMIT,
                'bounded literal NORMAL/compiler object required')
        contract, owner = owner_proof(readonly_source, contract_bytes)
        e = elf_tables(raw)
        sec, data, names = e['sections'], e['data'], e['names']
        require('.text' in names and '.rodata' in names and '.rel.text' in names,
                'required recipe sections')
        ti, pi, ri = (names.index(n) for n in ('.text', '.rodata', '.rel.text'))
        require(sec[ti][1:3] == [1, 6] and len(data[ti]) == 54096 and
                sha(data[ti]) == TEXT_SHA, 'entire literal compiler TEXT')
        require(sec[pi][1:3] == [1, 2] and data[pi] == POOL,
                'exact scalar plus twelve alignment zero bytes')
        require(len(e['rels']) == 988 and NAME not in e['symbol_names'],
                'complete988REL and absent owner import')
        targets = [x for x, name in zip(e['symbols'], e['symbol_names'])
                   if name == contract['target_name']]
        require(len(targets) == 1 and targets[0][1:] == (25380, 804, 0x12, 0, ti) and
                sha(data[ti][25380:25380 + 804]) == contract['target_TEXT_sha256'],
                'exact positive target FUNC804 and complete target bytes')
        require(all(struct.unpack_from('>I', data[ti], site)[0] & 0xFFFF == 0
                    for site, _ in SITES), 'literal zero HI16/LO16 implicit addends')
        pool_symbols = [(i, s) for i, s in enumerate(e['symbols']) if s[5] == pi]
        require(len(pool_symbols) == 1, 'only local section symbol owns duplicate pool')
        pool_index, ps = pool_symbols[0]
        require(e['symbol_names'][pool_index] == '.rodata' and
                ps[1:] == (0, 16, 3, 0, pi), 'exact unused-after-bridge SECTION symbol')
        uses = [r for r in e['rels'] if r[3] == pool_index]
        require([(r[2], r[4]) for r in uses] == list(SITES) and
                all(r[0] == ri and sec[ri][7] == ti for r in uses),
                'exact two pool references only')
        si, sti = e['symtab'], e['strtab']
        new_index = len(e['symbols'])
        strings = data[sti] + NAME.encode('ascii') + b'\0'
        symbols = data[si] + struct.pack('>IIIBBH', len(data[sti]), 0, 0, 0x10, 0, 0)
        out = bytearray(raw)
        changed_ranges = []

        def patch(offset, value):
            require(0 <= offset <= len(raw) - len(value), 'patch stays in old file')
            out[offset:offset + len(value)] = value
            changed_ranges.append((offset, offset + len(value)))

        for _, relative, site, _, kind in uses:
            patch(sec[ri][4] + relative + 4, struct.pack('>I', new_index << 8 | kind))
        shoff = e['header'][6]
        patch(shoff + 40 * pi + 8, struct.pack('>I', sec[pi][2] & ~2))
        patch(shoff + 40 * pi + 20, struct.pack('>I', 0))
        for index, blob in ((sti, strings), (si, symbols)):
            alignment = max(1, sec[index][8])
            out.extend(bytes((-len(out)) % alignment))
            start = len(out)
            out.extend(blob)
            patch(shoff + 40 * index + 16, struct.pack('>II', start, len(blob)))
        require(len(out) <= LIMIT, 'transformed size cap')
        permitted = {j for a, b in changed_ranges for j in range(a, b)}
        require(all(out[i] == raw[i] for i in range(len(raw)) if i not in permitted),
                'all other literal compiler bytes unchanged')
        after = elf_tables(bytes(out))
        require(after['header'] == e['header'] and after['names'] == names,
                'header/section indices and names literal')
        require(after['data'][ti] == data[ti] and after['data'][si] == symbols and
                after['data'][sti] == strings and after['symbols'][:-1] == e['symbols'],
                'whole TEXT and old symbol/string prefix identity')
        expected_rels = [(a, b, c, new_index if d == pool_index else d, k)
                         for a, b, c, d, k in e['rels']]
        require(after['rels'] == expected_rels and
                after['sections'][si][7] == sec[si][7] and
                after['sections'][pi][2] == 0 and after['sections'][pi][5] == 0,
                'only two REL identities and duplicate allocation changed')
        result = bytes(out)
        return result, dict(
            status='TRANSFORMED_UVTERRA_DUPLICATE_POOL_NOT_LITERAL_COMPILER_OUTPUT',
            raw_compiler_sha256=sha(raw), raw_compiler_bytes=len(raw),
            transformed_sha256=sha(result), transformed_bytes=len(result),
            owner=owner, appended_global_UND_NOTYPE0=NAME,
            old_symbol_indices_and_sh_info_preserved=True,
            retargeted_sites=[list(x) for x in SITES],
            compiler_pool_native_allocation_bytes_before=16,
            compiler_pool_native_allocation_bytes_after=0,
            compiler_pool_physical_payload_retained=True,
            old_unused_local_SECTION_symbol_metadata_retained=True,
            all_TEXT_and_all_other_old_file_bytes_outside_declared_ranges_literal=True,
            historical_raw_caller_J26_alias_holds_unchanged=True,
            raw_implicit_HI16_LO16=[0, 0],
            expected_native_owner_offset=892,
            normal_object_compatibility='UNMEASURED_NOT_EXECUTION_ADMISSION',
            native_REL_addend_replay='REQUIRED_NOT_QUALIFIED',
            all133_ROM_Git_acceptance='REQUIRED_NOT_QUALIFIED',
            accepted=False, operations=0, coverage_credit=0)

    return transform(raw_compiler_elf, readonly_source, b'{\n  "version": 1,\n  "module": "uvterra_rom",\n  "source": "src/modules/uvterra_rom.c",\n  "owner_source": "asm/us/data/modules/uvterra_rom.rodata.s",\n  "owner_source_bytes": 9769,\n  "owner_source_sha256": "36796a86b164c8e0bf7283b0569bf9db27da681c3453ff0b2dbd47da9828f0b8",\n  "owner_begin": 4248400,\n  "owner_end": 4249360,\n  "owner_allocated_bytes": 960,\n  "owner_payload_sha256": "33c316ff34e2d830efbfdc2bfa73990a567434e4eb9fda67763b7224d24fa6ad",\n  "owner_name": "D_uvterra_rom_0040D6CC",\n  "owner_offset": 892,\n  "owner_object_bytes": 4,\n  "scalar_word_hex": "3EAA7EFA",\n  "compiler_pool_bytes": 16,\n  "compiler_alignment_zero_bytes": 12,\n  "whole_TEXT_bytes": 54096,\n  "whole_TEXT_sha256": "3e128c671f8de2b2566517dc793b50a3a2f3d5e51852325695b62602fec02937",\n  "target_name": "uvTerraComputeTriangleSliceWeights",\n  "target_start": 25380,\n  "target_bytes": 804,\n  "target_TEXT_sha256": "1bce558cbc59a82e68054774e1351c9a6af9e2254b177963c08942d83c8c04b5",\n  "complete_REL_count": 988,\n  "pool_REL_sites": [\n    [\n      25384,\n      5\n    ],\n    [\n      25388,\n      6\n    ]\n  ],\n  "supported_observed_flags": [\n    268435457\n  ],\n  "raw_HI16_immediate": 0,\n  "raw_LO16_immediate": 0,\n  "normal_object_compatibility": "UNMEASURED_REQUIRED_BEFORE_ADOPTION",\n  "undefined_import": {\n    "binding": 1,\n    "type": 0,\n    "bytes": 0,\n    "value": 0,\n    "other_raw": 0,\n    "section_index": 0\n  },\n  "consumed_load_bytes": 4,\n  "import_extent_note": "Exact original untyped assembler import GLOBAL/UND/NOTYPE0/st_size0. This is not a recovered C extern type and not an allocation claim; independent positive readonly owner remains GLOBAL OBJECT4@892."\n}\n')


def uvterra_duplicate_scalar_main():
    """The single US source-object hook; no private receipt or arbitrary decoder."""
    import argparse
    import stat
    p = argparse.ArgumentParser()
    p.add_argument('--uvterra-duplicate-scalar', action='store_true', required=True)
    p.add_argument('--root', required=True)
    p.add_argument('--object', required=True)
    args = p.parse_args()
    root = Path(args.root).resolve()
    require(root.is_dir(), 'UVTERRA project root missing')
    require(args.object == 'build/src/modules/uvterra_rom.o', 'UVTERRA object path changed')
    target = root / args.object
    owner = root / 'asm/us/data/modules/uvterra_rom.rodata.s'

    def read_regular(path, limit):
        # The build namespace remains externally guarded; this is not a sandbox.
        require(path.is_relative_to(root), 'UVTERRA input leaves project')
        require(not path.is_symlink() and all(not q.is_symlink() for q in path.parents), 'UVTERRA symlink path')
        fd = os.open(path, os.O_RDONLY | os.O_NOFOLLOW | os.O_NONBLOCK)
        try:
            before = os.fstat(fd)
            require(stat.S_ISREG(before.st_mode) and 0 < before.st_size <= limit, 'UVTERRA bounded regular input required')
            with os.fdopen(fd, 'rb', closefd=False) as stream:
                raw = stream.read(limit + 1)
            after = os.fstat(fd)
            current = path.lstat()
            identity = lambda s: (s.st_dev, s.st_ino, s.st_mode, s.st_size, s.st_mtime_ns, s.st_ctime_ns)
            require(len(raw) == before.st_size and identity(before) == identity(after) == identity(current), 'UVTERRA input changed during read')
            return raw, before.st_mode
        finally:
            os.close(fd)

    raw, mode = read_regular(target, 262144)
    source, _ = read_regular(owner, 16384)
    transformed, report = uvterra_duplicate_scalar_transform(raw, source)
    temporary = target.with_name(target.name + '.uvterra-scalar.tmp')
    require(not temporary.exists() and not temporary.is_symlink(), 'UVTERRA temporary already exists')
    created = False
    try:
        with temporary.open('xb') as stream:
            created = True
            require(stream.write(transformed) == len(transformed), 'UVTERRA short staged write')
        os.chmod(temporary, stat.S_IMODE(mode))
        require(read_regular(temporary, 262144)[0] == transformed, 'UVTERRA staged readback differs')
        require(read_regular(target, 262144)[0] == raw, 'UVTERRA compiler object changed before replace')
        require(read_regular(owner, 16384)[0] == source, 'UVTERRA owner source changed before replace')
        os.replace(temporary, target)
        require(read_regular(target, 262144)[0] == transformed, 'UVTERRA transformed readback differs')
        require(read_regular(owner, 16384)[0] == source, 'UVTERRA owner source changed after replace')
    finally:
        if created and temporary.exists():
            temporary.unlink()
    print(json.dumps(report, sort_keys=True))


# This accepted helper previously had no CLI. Imports continue to define DYN below.
if __name__ == '__main__':
    uvterra_duplicate_scalar_main()


# One audited ownership closure, not a general allowance for terminal gaps.
DYN_TERMINAL_LAYOUT111100 = {'begin': 4266528, 'end': 4267408, 'late_spans': [{'begin': 4266892, 'end': 4266972, 'host_address': 4210064, 'host_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403D90.s', 'host_bytes': 520, 'host_sha256': 'fc3f9018478887d888ef15718e683d3a4aaeb58561a8ba44deb236fdb36a5390', 'host_symbol': 'func_uvdyn_rom_00403D90'}, None, None, {'begin': 4267196, 'end': 4267336, 'host_address': 4215020, 'host_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004050EC.s', 'host_bytes': 9384, 'host_sha256': '5bd49fc0194d2fc896cfd0bf11335fcd14808411437745f93aa2ef684108f3b9', 'host_symbol': 'func_uvdyn_rom_004050EC'}, None], 'module': 'uvdyn_rom', 'monolithic_assembly': 'asm/us/data/modules/uvdyn_rom.rodata.s', 'prefix_assembly': 'asm/us/data/modules/uvdyn_rom.rodata-prefix.s', 'readonly_sha256': 'ebf5750d6c6c5efc21f1a2632733dda77295f10ff90974f400a1fc591c821c7e', 'source': 'src/modules/uvdyn_rom.c', 'tables': [{'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411B1C.s', 'owner_address': 4209720, 'owner_asm_normalized_sha256': 'ee8600d051787c7823bbaf8a555b32861db4dbdb006501ecd261ac79674990a3', 'owner_bytes': 344, 'owner_c_symbol': 'uvDynGetNodeScalarProperty', 'owner_instruction_sha256': 'b31ab1d8d4d7d1f80b9efdbb0b42ef3d5e5ccc6ef22422c88a9be410dd4b9b9d', 'owner_original_symbol': 'func_uvdyn_rom_00403C38', 'table_begin': 4266780, 'table_end': 4266892, 'table_label': 'D_uvdyn_rom_00411B1C'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411BDC.s', 'owner_address': 4210584, 'owner_asm_normalized_sha256': '8d1d17dd5230e43336c0154e6ede7250dc6375c36162c657052b34906e775146', 'owner_bytes': 128, 'owner_c_symbol': 'uvDynGetNodePropertyAddress', 'owner_instruction_sha256': 'bd81a6f9db80d17ceaf60df43f820732e1111afccfda2a8a50f9f68b24769e56', 'owner_original_symbol': 'func_uvdyn_rom_00403F98', 'table_begin': 4266972, 'table_end': 4267040, 'table_label': 'D_uvdyn_rom_00411BDC'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411C20.s', 'owner_address': 4210712, 'owner_asm_normalized_sha256': '7a5b2db5d261f6da3037ca1c85d92de0126efe98ae44a63caaff12659977a5eb', 'owner_bytes': 436, 'owner_c_symbol': 'uvDynGetNodeVectorProperty', 'owner_instruction_sha256': '7f5e1965abb2b6d056ad435f5efcd4bb4dd3d2f21a011abfcd3843db7a9c5251', 'owner_original_symbol': 'func_uvdyn_rom_00404018', 'table_begin': 4267040, 'table_end': 4267116, 'table_label': 'D_uvdyn_rom_00411C20'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411C6C.s', 'owner_address': 4211680, 'owner_asm_normalized_sha256': '09a35a67918a289f3fe679f7911941efff7312073a39294337d0be022a679df5', 'owner_bytes': 240, 'owner_c_symbol': 'uvDynGetNodeMatrixProperty', 'owner_instruction_sha256': 'f4ea07a78f4863d9c4dfe3c36dee1653e88f391079c0c2ea08bafa6e5a1118bd', 'owner_original_symbol': 'func_uvdyn_rom_004043E0', 'table_begin': 4267116, 'table_end': 4267196, 'table_label': 'D_uvdyn_rom_00411C6C'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411D48.s', 'owner_address': 4264704, 'owner_asm_normalized_sha256': 'd32b6813d2f88fc58b45b64fac1d846f7355b7656b6764df64fc33d928342dbe', 'owner_bytes': 140, 'owner_c_symbol': 'uvDynGetSecondaryPropertyAddress', 'owner_instruction_sha256': '8ae3b00fc0c56c58babb50d96a4b3a21d4a6b31486e4ad7d0aa19310642e2449', 'owner_original_symbol': 'func_uvdyn_rom_00411300', 'table_begin': 4267336, 'table_end': 4267364, 'table_label': 'D_uvdyn_rom_00411D48'}], 'terminal_literal_tail': {'assembly': 'asm/us/data/modules/uvdyn_rom-secondary.rodata-island.s', 'begin': 4267364, 'end': 4267408, 'readonly_sha256': '485b6ea86b8159929e6e77cf65fbf64fec31657b2b6615e0614201bf8ff713a6'}, 'version': 3, 'witness': 'tools/readonly_layout/uvdyn_rom.five-table-rodata.s', 'witness_sha256': '4ac8728a5cdbe08b158f61a1a06fad8acaa29cd98c5a252808ae0ed4a2025268'}
DYN_ORIGINAL_WITNESS111100 = ('tools/readonly_layout/uvdyn_rom.original-rodata.s', '37498ed9124fc0b3d7dd80888c25e8002c039f1b0abaab8a8cc8595e186dcce8')
DYN_TERMINAL_MAKE_SHA111100 = 'b2a6ae895d26d0eb0b25f117a8c61df6b198c32db3ea5e963dd38ab99a37f5c0'
DYN_UNUSED_DUPLICATE_SHA111100 = '587905d952414132dc714062021b05931c5ec18fd060b5b8eeabb68aff98bc31'

def dyn_terminal_tail111100(root, layout):
    if 'terminal_c_literals' in layout:
        return dyn_natural_tail113100(root, layout)
    if 'terminal_literal_tail' not in layout:
        return None
    require(layout == DYN_TERMINAL_LAYOUT111100,
            'terminal literal tail is only the fixed five-owner DYN closure')
    name, expected = DYN_ORIGINAL_WITNESS111100
    require(sha(inside(root, name).read_bytes()) == expected,
            'immutable original DYN witness changed')
    make = inside(root, 'Makefile').read_bytes()
    require(sha(make) == DYN_TERMINAL_MAKE_SHA111100 and
            b'ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*")' in make,
            'DYN terminal Makefile/excluded unused-witness membership changed')
    return layout['terminal_literal_tail']

def dyn_terminal_duplicate111100(root, layout, decoded, duplicate):
    if 'terminal_c_literals' in layout:
        table = DYN_NATURAL_LAYOUT113100['tables'][-1]
        if layout != dict(DYN_NATURAL_LAYOUT113100, **table, version=1):
            return False
        dyn_natural_tail113100(root, DYN_NATURAL_LAYOUT113100)
        return dyn_terminal_duplicate111100(root, dict(DYN_TERMINAL_LAYOUT111100, **table, version=1), decoded, duplicate)
    if 'terminal_literal_tail' not in layout:
        return False
    table = DYN_TERMINAL_LAYOUT111100['tables'][-1]
    expected = dict(DYN_TERMINAL_LAYOUT111100, **table, version=1)
    # A table-view consult only; no other duplicate or original guard is waived.
    if layout != expected:
        return False
    dyn_terminal_tail111100(root, DYN_TERMINAL_LAYOUT111100)
    raw = duplicate.read_bytes()
    require(len(raw) == 596 and sha(raw) == DYN_UNUSED_DUPLICATE_SHA111100,
            'DYN original unused seven-target-plus-zero witness changed')
    original = original_bytes(raw.decode(), 0x411D48, 0x411D68)
    require(len(decoded) == 880 and sha(decoded) == DYN_TERMINAL_LAYOUT111100['readonly_sha256'] and
            original == decoded[808:840], 'DYN unused32 witness differs from original decoded bytes')
    # This path lies under nonmatchings, excluded by the exact Makefile above.
    # The caller still scans every source/ASM/header for actual table users.
    return True

DYN_NATURAL_LAYOUT113100={'begin': 4266528, 'end': 4267408, 'late_spans': [{'begin': 4266892, 'end': 4266972, 'host_address': 4210064, 'host_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403D90.s', 'host_bytes': 520, 'host_sha256': 'fc3f9018478887d888ef15718e683d3a4aaeb58561a8ba44deb236fdb36a5390', 'host_symbol': 'func_uvdyn_rom_00403D90'}, None, None, {'begin': 4267196, 'end': 4267336, 'host_address': 4215020, 'host_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004050EC.s', 'host_bytes': 9384, 'host_sha256': '5bd49fc0194d2fc896cfd0bf11335fcd14808411437745f93aa2ef684108f3b9', 'host_symbol': 'func_uvdyn_rom_004050EC'}, None], 'module': 'uvdyn_rom', 'monolithic_assembly': 'asm/us/data/modules/uvdyn_rom.rodata.s', 'prefix_assembly': 'asm/us/data/modules/uvdyn_rom.rodata-prefix.s', 'readonly_sha256': 'ebf5750d6c6c5efc21f1a2632733dda77295f10ff90974f400a1fc591c821c7e', 'source': 'src/modules/uvdyn_rom.c', 'tables': [{'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411B1C.s', 'owner_address': 4209720, 'owner_asm_normalized_sha256': 'ee8600d051787c7823bbaf8a555b32861db4dbdb006501ecd261ac79674990a3', 'owner_bytes': 344, 'owner_c_symbol': 'uvDynGetNodeScalarProperty', 'owner_instruction_sha256': 'b31ab1d8d4d7d1f80b9efdbb0b42ef3d5e5ccc6ef22422c88a9be410dd4b9b9d', 'owner_original_symbol': 'func_uvdyn_rom_00403C38', 'table_begin': 4266780, 'table_end': 4266892, 'table_label': 'D_uvdyn_rom_00411B1C'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411BDC.s', 'owner_address': 4210584, 'owner_asm_normalized_sha256': '8d1d17dd5230e43336c0154e6ede7250dc6375c36162c657052b34906e775146', 'owner_bytes': 128, 'owner_c_symbol': 'uvDynGetNodePropertyAddress', 'owner_instruction_sha256': 'bd81a6f9db80d17ceaf60df43f820732e1111afccfda2a8a50f9f68b24769e56', 'owner_original_symbol': 'func_uvdyn_rom_00403F98', 'table_begin': 4266972, 'table_end': 4267040, 'table_label': 'D_uvdyn_rom_00411BDC'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411C20.s', 'owner_address': 4210712, 'owner_asm_normalized_sha256': '7a5b2db5d261f6da3037ca1c85d92de0126efe98ae44a63caaff12659977a5eb', 'owner_bytes': 436, 'owner_c_symbol': 'uvDynGetNodeVectorProperty', 'owner_instruction_sha256': '7f5e1965abb2b6d056ad435f5efcd4bb4dd3d2f21a011abfcd3843db7a9c5251', 'owner_original_symbol': 'func_uvdyn_rom_00404018', 'table_begin': 4267040, 'table_end': 4267116, 'table_label': 'D_uvdyn_rom_00411C20'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411C6C.s', 'owner_address': 4211680, 'owner_asm_normalized_sha256': '09a35a67918a289f3fe679f7911941efff7312073a39294337d0be022a679df5', 'owner_bytes': 240, 'owner_c_symbol': 'uvDynGetNodeMatrixProperty', 'owner_instruction_sha256': 'f4ea07a78f4863d9c4dfe3c36dee1653e88f391079c0c2ea08bafa6e5a1118bd', 'owner_original_symbol': 'func_uvdyn_rom_004043E0', 'table_begin': 4267116, 'table_end': 4267196, 'table_label': 'D_uvdyn_rom_00411C6C'}, {'duplicate_assembly': 'asm/us/nonmatchings/modules/uvdyn_rom/D_uvdyn_rom_00411D48.s', 'owner_address': 4264704, 'owner_asm_normalized_sha256': 'd32b6813d2f88fc58b45b64fac1d846f7355b7656b6764df64fc33d928342dbe', 'owner_bytes': 140, 'owner_c_symbol': 'uvDynGetSecondaryPropertyAddress', 'owner_instruction_sha256': '8ae3b00fc0c56c58babb50d96a4b3a21d4a6b31486e4ad7d0aa19310642e2449', 'owner_original_symbol': 'func_uvdyn_rom_00411300', 'table_begin': 4267336, 'table_end': 4267364, 'table_label': 'D_uvdyn_rom_00411D48'}], 'version': 3, 'witness': 'tools/readonly_layout/uvdyn_rom.five-table-rodata.s', 'witness_sha256': '4ac8728a5cdbe08b158f61a1a06fad8acaa29cd98c5a252808ae0ed4a2025268', 'terminal_c_literals': {'begin': 4267364, 'end': 4267408, 'readonly_sha256': '485b6ea86b8159929e6e77cf65fbf64fec31657b2b6615e0614201bf8ff713a6', 'owner_c_symbol': 'uvDynSetSecondaryMatrixProperty', 'owner_address': 70740, 'owner_bytes': 496, 'owner_native_sha256': 'c36b7cf7fe88af4e7d27e9d8299506386920d8a677d9753d507d0204d478bbb2', 'compiler_source_sha256': '1cf8da25e4099b171c83dcdb8cf03801f095b1066ec74db4a12a5c6b3ec87077', 'literal_binary64': ['3ee4f8b588e368f1', 'bee4f8b588e368f1', '3ee4f8b588e368f1', 'bee4f8b588e368f1'], 'obsolete_assembly': 'asm/us/data/modules/uvdyn_rom-secondary.rodata-island.s', 'obsolete_assembly_sha256': '82260626a61617c31d8f765b4b3ec49384bdcd5bb74f7027c9ef84d2761a8704', 'obsolete_assembly_bytes': 705}}

def dyn_natural_tail113100(root, layout):
    require(layout == DYN_NATURAL_LAYOUT113100, 'natural terminal literals require the fixed measured DYN closure')
    name, expected = DYN_ORIGINAL_WITNESS111100
    require(sha(inside(root, name).read_bytes()) == expected, 'immutable original DYN witness changed')
    make = inside(root, 'Makefile').read_bytes()
    require(sha(make) == DYN_TERMINAL_MAKE_SHA111100 and
            b'ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*")' in make,
            'natural DYN Makefile/excluded unused-witness membership changed')
    tail = layout['terminal_c_literals']
    exclusion = [line for line in make.decode().splitlines() if line.startswith('S_FILES') and 'filter-out' in line]
    require(len(exclusion) == 1 and tail['obsolete_assembly'] in exclusion[0].split(), 'obsolete tail is not excluded from standalone compilation')
    return dict(begin=tail['begin'], end=tail['end'], readonly_sha256=tail['readonly_sha256'],
                assembly=tail['obsolete_assembly'], c_owned=True)

def dyn_natural_source113100(root, layout, source, code):
    tail = layout['terminal_c_literals']
    require(sha(source.encode()) == tail['compiler_source_sha256'], 'natural DYN C source changed from measured TU')
    pragma = '#pragma GLOBAL_ASM("' + tail['obsolete_assembly'] + '")'
    require(pragma not in code and code.count('state->value134 < 1e-5 && -1e-5 < state->value134') == 2,
            'natural terminal literals/obsolete pragma changed')
    for name in ('D_uvdyn_rom_00411D68', 'D_uvdyn_rom_00411D70', 'D_uvdyn_rom_00411D78', 'D_uvdyn_rom_00411D80'):
        require(source.count(name) == 1 and 'extern f64 ' + name + ';' in source, 'retained unused extern declaration changed')
    header = 'void uvDynSetSecondaryMatrixProperty(DynSecondaryState *state, s32 selector, Mtx4F *inputMatrix) {'
    require(code.count(header) == 1, 'natural literal owner is not one complete definition')
    return code.index(header)

def dyn_natural_obsolete113100(root, layout, path):
    tail = layout['terminal_c_literals'];raw = path.read_bytes()
    require(path.is_file() and len(raw) == tail['obsolete_assembly_bytes'] and sha(raw) == tail['obsolete_assembly_sha256'],
            'obsolete terminal ASM preimage changed')
    decoded = original_bytes(raw.decode(), tail['begin'], tail['end'])
    require(len(decoded) == 44 and sha(decoded) == tail['readonly_sha256'], 'obsolete terminal ASM native data changed')
    return True
