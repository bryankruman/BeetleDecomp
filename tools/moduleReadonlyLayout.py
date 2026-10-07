"""Deterministic retained ASM spans around one compiler-owned readonly table.

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


def check_users(root, layout, decoded):
    allowed = {layout['monolithic_assembly'], layout['witness']}
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
    layout, decoded, prefix, suffix = load(root, config, module)
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
    """Use normal regenerated original ASM host, then append retained suffix."""
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
