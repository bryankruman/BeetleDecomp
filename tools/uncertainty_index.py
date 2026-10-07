#!/usr/bin/env python3
"""Index explicit reverse-engineering debt without interpreting game behavior.

The index is deterministic and contains source locations, never ROM data. It
includes inactive conditional branches; it is not a completion percentage.
"""
from pathlib import Path
from collections import Counter, defaultdict
import argparse
import bisect
import hashlib
import json
import re

CATEGORIES = {
    'explicit_unknown': 'Explicit RE_UNKNOWN notes',
    'original_quirk': 'Preserved RE_ORIGINAL_QUIRK notes',
    'uncertainty_note': 'Older comments with uncertainty language',
    'audit_debt': 'Documented original-behavior audits',
    'assembly': 'Assembly-backed functions or data',
    'address_function': 'Address-based function identifiers',
    'address_global': 'Address-based global identifiers',
    'offset_field': 'Offset-based fields or neutral typed fields',
    'layout_padding': 'Layout padding to preserve',
    'opaque_type': 'Unresolved type names',
    'unused_identifier': 'Explicit unused ABI, storage or local identifiers',
    'decompiler_local': 'Decompiler parameter/local names',
    'draft_marker': 'Fake, unresolved or TODO draft markers',
    'conditional_draft': 'Data-dependent conditional draft guards',
}
PATTERNS = {
    'address_function': re.compile(r'\b(?:__entrypoint_func_|func_)[A-Za-z0-9_]*_[0-9A-Fa-f]{6,8}\b'),
    'address_global': re.compile(r'\bD_[A-Za-z0-9_]*[0-9A-Fa-f]{8}\b'),
    'offset_field': re.compile(r'\b(?:unk[A-Za-z0-9_]*|(?:field|value|word|scalar|vector|pointer|callback|context|flag|byte|short|matrix|record|data|buffer|opaque)[0-9A-Fa-f]+(?:_[A-Za-z0-9_]+)?)\b'),
    'layout_padding': re.compile(r'\b(?:pad|padding|prefix|gap)(?:[0-9A-Fa-f]+(?:_[A-Za-z0-9_]+)?)?\b'),
    'opaque_type': re.compile(r'\bUnk[A-Z0-9_][A-Za-z0-9_]*\b'),
    'unused_identifier': re.compile(r'\bunused(?:[A-Z0-9_][A-Za-z0-9_]*)?\b'),
    'decompiler_local': re.compile(r'\b(?:arg[0-9]+|sp[0-9A-Fa-f]+|temp_[A-Za-z0-9_]+|var_[A-Za-z0-9_]+)\b'),
    'draft_marker': re.compile(r'\b(?:FAKE|M2C_ERROR|MIPS2C_ERROR|TODO|FIXME)\b'),
    'conditional_draft': re.compile(r'\bNEEDS_(?:DATA|RODATA|BSS)\b'),
}
UNCERTAIN = re.compile(r'\b(?:opaque|unproven|unresolved|unknown|unverified|uninitialized|undefined)\b|not (?:yet )?(?:established|known|proven|initialized)', re.I)


def lexical_views(text):
    """Mask comments and literals while preserving physical source offsets.

    This prevents fake identifiers in strings, comments or assembly paths from
    being counted as C identifiers. A second view keeps pragma string literals.
    """
    code=list(text); comment_free=list(text); comments=[]; i=0
    def blank(view,start,end):
        for position in range(start,end):
            if view[position] not in '\r\n':view[position]=' '
    while i<len(text):
        if text.startswith('//',i):
            end=text.find('\n',i)
            if end<0:end=len(text)
            comments.append((i,text[i:end]));blank(code,i,end);blank(comment_free,i,end);i=end
        elif text.startswith('/*',i):
            end=text.find('*/',i+2)
            if end<0:raise ValueError('Unterminated C comment')
            end+=2;comments.append((i,text[i:end]));blank(code,i,end);blank(comment_free,i,end);i=end
        elif text[i] in '\"\'':
            quote=text[i];end=i+1
            while end<len(text):
                if text[end]=='\\':end+=2;continue
                if text[end]==quote:end+=1;break
                end+=1
            blank(code,i,end);i=end
        else:i+=1
    return ''.join(code),''.join(comment_free),comments


def collect(root):
    groups={}; hashes={}
    def add(kind,path,symbol,line,evidence=None):
        key=(kind,path,symbol)
        if key not in groups:
            groups[key]={'id':'Q-'+hashlib.sha256('\0'.join(key).encode()).hexdigest()[:12],
                         'kind':kind,'path':path,'symbol':symbol,'lines':set()}
            if evidence:groups[key]['evidence']=evidence
        groups[key]['lines'].add(line)
    paths=sorted(p for directory in ['src','include'] for p in (root/directory).rglob('*')
                 if p.is_file() and p.suffix in ['.c','.h'])
    for p in paths:
        raw=p.read_bytes();path=p.relative_to(root).as_posix();hashes[path]=hashlib.sha256(raw).hexdigest()
        text=raw.decode();code,comment_free,comments=lexical_views(text)
        newlines=[m.start() for m in re.finditer('\n',text)]
        def line(offset):return bisect.bisect_left(newlines,offset)+1
        for kind,pattern in PATTERNS.items():
            for m in pattern.finditer(code):add(kind,path,m[0],line(m.start()))
        for m in re.finditer(r'^[ \t]*#pragma\s+GLOBAL_ASM\s*\(\s*"([^"\n]+)"\s*\)',comment_free,re.M):
            add('assembly',path,Path(m[1]).stem,line(m.start()),m[1])
        for start,comment in comments:
            normalized=' '.join(comment.replace('/*','').replace('*/','').replace('//','').split())
            kinds=[]
            if 'RE_UNKNOWN' in comment:kinds.append('explicit_unknown')
            if 'RE_ORIGINAL_QUIRK' in comment:kinds.append('original_quirk')
            if not kinds and UNCERTAIN.search(comment):kinds.append('uncertainty_note')
            for kind in kinds:add(kind,path,normalized,line(start),normalized)
            for m in PATTERNS['draft_marker'].finditer(comment):
                add('draft_marker',path,m[0],line(start+m.start()),normalized)
    for filename in ['STRATEGY_V4.md','VALIDATION_20261006.md']:
        p=root/'docs'/filename
        if not p.exists():continue
        path=p.relative_to(root).as_posix();raw=p.read_bytes();hashes[path]=hashlib.sha256(raw).hexdigest()
        for n,line in enumerate(raw.decode().splitlines(),1):
            for m in re.finditer(r'\bOC[0-9]+\b',line):add('audit_debt',path,m[0],n,line.strip())
    records=[]
    for key,value in sorted(groups.items()):
        value['lines']=sorted(value['lines']);records.append(value)
    counts=Counter(x['kind'] for x in records)
    return {'schema':1,'scope':'src/**/*.c and include/**/*.h, plus named audit entries in strategy/validation docs',
            'limitations':['Includes inactive conditional code; counts are search groups, not unique unknown meanings or completion percentages.',
                           'Neutral names, explicit notes and known naming conventions are indexed. Undiscovered semantic assumptions cannot be detected automatically.',
                           'Padding describes binary layout and is not an instruction to remove bytes. Original quirks require caller/reachability evidence before runtime changes.',
                           'Physical line locations are regenerated. Q identifiers remain stable while category, path and symbol/comment text remain unchanged.'],
            'source_hashes':hashes,'counts':dict(sorted(counts.items())),'items':records}


def markdown(index):
    lines=['# Reverse-engineering uncertainty index','',
           'Generated by `python3 tools/uncertainty_index.py`. Do not edit this index by hand.','',
           'Use `python3 tools/uncertainty_index.py --query NAME` to find every indexed source location. ',
           'Use `--check` to verify this index matches the current source. The complete locations and source hashes are in `UNCERTAINTIES.json`.','',
           '`RE_UNKNOWN:` comments state what remains unproven and what evidence would settle it. ',
           '`RE_ORIGINAL_QUIRK:` comments describe behavior intentionally preserved from the original game; they do not authorize a runtime change. ',
           'Keep offset names until field meaning and units are established. Record a caller, binary observation or data-format proof when resolving a note. ',
           'For every future source wave, regenerate and check this index after code and strategy edits, then include both generated files in that wave.','',
           '**Coverage:** recognizable unknown names, all assembly pragmas, explicit/older uncertainty comments, draft markers and named original-behavior audits. ',
           '**Limits:** this is a search aid, not proof that every undiscovered assumption is flagged. Counts include conditional/inactive code and repeated names. Padding is binary layout to preserve.','',
           '| Category | Search groups |','| --- | ---: |']
    for kind,title in CATEGORIES.items():lines.append(f'| {title} | {index["counts"].get(kind,0)} |')
    by_path=defaultdict(list)
    for item in index['items']:by_path[item['path']].append(item)
    for path,items in sorted(by_path.items()):
        lines+=['',f'## {path}','', '| Kind | Identifier or note | Physical lines |','| --- | --- | --- |']
        for item in items:
            symbol=item['symbol'].replace('|','\\|').replace('`',"'")
            if len(symbol)>180:symbol=symbol[:177]+'...'
            links=', '.join(f'[{n}](../{path}#L{n})' for n in item['lines'][:8])
            if len(item['lines'])>8:links+=f' (+{len(item["lines"])-8} in JSON)'
            lines.append(f'| {item["kind"]} | `{symbol}` | {links} |')
    return '\n'.join(line.rstrip() for line in lines)+'\n'


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root',type=Path,default=Path(__file__).resolve().parent.parent)
    parser.add_argument('--check',action='store_true')
    parser.add_argument('--query')
    args=parser.parse_args();root=args.root.resolve();index=collect(root)
    if args.query:
        needle=args.query.casefold();matches=[x for x in index['items'] if needle in (x['symbol']+' '+x['path']+' '+x['kind']).casefold()]
        for item in matches:
            for n in item['lines']:print(f'{item["path"]}:{n}: {item["kind"]}: {item["symbol"]}')
        print(f'{len(matches)} search groups');return
    outputs={root/'docs/UNCERTAINTIES.json':json.dumps(index,indent=2)+'\n',root/'docs/UNCERTAINTIES.md':markdown(index)}
    for p,text in outputs.items():
        if args.check:
            if not p.exists() or p.read_bytes()!=text.encode():raise SystemExit(f'Stale uncertainty index: {p}; regenerate after source/doc edits.')
        else:p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(text.encode())
    print(json.dumps({'status':'PASS','mode':'check' if args.check else 'generate','source_files':len(index['source_hashes']),'search_groups':len(index['items']),'counts':index['counts']}))


if __name__=='__main__':main()
