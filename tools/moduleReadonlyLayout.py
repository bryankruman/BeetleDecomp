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
    if duplicate.exists():
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
    require(set(layout) == common and type(layout['version']) is int and
            layout['version'] == 3 and layout['module'] == module,
            'unsupported V3 metadata schema/module')
    tables, spans = layout['tables'], layout['late_spans']
    require(isinstance(tables, list) and len(tables) > 0 and
            isinstance(spans, list) and len(spans) == len(tables),
            'each V3 compiler table requires one explicit following-span entry')
    paths = [layout[key] for key in ('witness', 'prefix_assembly', 'monolithic_assembly')]
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
            require(table['table_end'] == following,
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
