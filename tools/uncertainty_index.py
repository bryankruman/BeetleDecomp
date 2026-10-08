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
    'address_function': re.compile(r'\b(?:__entrypoint_func_|func_)(?:[A-Za-z0-9_]*_)?[0-9A-Fa-f]{6,8}\b'),
    'address_global': re.compile(r'\bD_[A-Za-z0-9_]*[0-9A-Fa-f]{8}\b'),
    'offset_field': re.compile(r'\b(?:unk[A-Za-z0-9_]*|(?:field|value|word|scalar|vector|pointer|callback|context|flag|byte|short|matrix|record|data|buffer|opaque)[0-9A-Fa-f]+(?:_[A-Za-z0-9_]+)?)\b'),
    'layout_padding': re.compile(r'\b(?:pad|padding|prefix|gap)(?:[0-9A-Fa-f]+(?:_[A-Za-z0-9_]+)?)?\b'),
    'opaque_type': re.compile(r'\bUnk[A-Z0-9_][A-Za-z0-9_]*\b'),
    'unused_identifier': re.compile(r'\bunused(?:[A-Z0-9_][A-Za-z0-9_]*)?\b'),
    'decompiler_local': re.compile(r'\b(?:arg[0-9]+|sp(?=[0-9A-Fa-f]*[0-9A-F])[0-9A-Fa-f]+|temp_[A-Za-z0-9_]+|var_[A-Za-z0-9_]+|new_var[0-9]*)\b'),
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


def declaration_owners(code):
    """Locate ordinary C definitions/declarations in a literal-masked view.

    This is a conservative lexical aid, not a C parser. Unsupported declarators
    remain unowned rather than borrowing the next recognizable function name.
    Preprocessor text is masked without applying #line logical line numbers.
    """
    code=re.sub(r'^[ \t]*#(?:[^\n]*\\\n)*[^\n]*',
                lambda m:re.sub(r'[^\r\n]',' ',m[0]),code,flags=re.M)
    tokens=list(re.finditer(r'[A-Za-z_]\w*|[^\s]',code));owners=[];i=0
    identifier=re.compile(r'[A-Za-z_]\w*\Z')
    def function_name(header):
        if not header or header[-1]!=')' or '=' in header:return None
        depth=0
        for j in range(len(header)-1,-1,-1):
            if header[j]==')':depth+=1
            elif header[j]=='(':
                depth-=1
                if depth==0:
                    if j and identifier.fullmatch(header[j-1]) and header[j-1] not in ('__attribute__','__declspec'):
                        return header[j-1]
                    return None
        return None
    def declarator_name(parts,allow_single=False):
        # Common function-pointer declarations have a name inside (*name).
        for j in range(len(parts)-3):
            if parts[j:j+2]==['(','*'] and identifier.fullmatch(parts[j+2]) and parts[j+3]==')':
                return parts[j+2]
        # Ignore array bounds rather than confusing a bound macro with a name.
        parts=parts[:parts.index('[')] if '[' in parts else parts
        if len(parts)>=(1 if allow_single else 2) and all(identifier.fullmatch(t) or t=='*' for t in parts):
            return parts[-1] if identifier.fullmatch(parts[-1]) else None
        return None
    while i<len(tokens):
        first=i;j=i;parens=brackets=0
        while j<len(tokens):
            t=tokens[j][0]
            if t=='(':parens+=1
            elif t==')':parens-=1
            elif t=='[':brackets+=1
            elif t==']':brackets-=1
            if parens==0 and brackets==0 and t in (';','{'):break
            j+=1
        if j==len(tokens):break
        header=[t[0] for t in tokens[first:j]];boundary=tokens[j][0]
        name=function_name(header);kind='function' if name else None;end=j;close=None
        if boundary=='{':
            depth=1;end=j+1
            while end<len(tokens) and depth:
                if tokens[end][0]=='{':depth+=1
                elif tokens[end][0]=='}':depth-=1
                end+=1
            if depth:break
            end-=1;close=end
            if kind!='function':
                # A top-level type/global initializer ends at its semicolon.
                while end+1<len(tokens) and tokens[end][0]!=';':end+=1
                if tokens[end][0]!=';':break
        if not kind:
            tail=[t[0] for t in tokens[close+1:end]] if close is not None else header
            if 'typedef' in header:
                name=declarator_name(tail,allow_single=close is not None)
                if name:kind='type'
            elif boundary=='{' and header and header[0] in ('struct','union','enum') and '=' not in header:
                if not tail:
                    if len(header)==2:kind='type';name=header[1]
                else:
                    name=declarator_name(tail,allow_single=True)
                    if name:kind='global'
            elif '=' not in header or boundary!='{':
                before=header[:header.index('=')] if '=' in header else header
                name=declarator_name(before)
                if name:kind='global'
        if kind and name:
            owners.append({'kind':kind,'name':name,'start':tokens[first].start(),'end':tokens[end].end()})
        i=end+1
    return owners


def definition_location_wrapper(code,text,end,owner):
    """Recognize the paired #line wrapper used when banking an old definition.

    Its one blank line is generated inside the wrapper, after an immediately
    leading note. Ordinary detached notes, prototypes, assembly pragmas and
    arbitrary location directives do not qualify. Keep physical offsets.
    """
    if owner['kind']!='function':return False
    declaration=code[owner['start']:owner['end']]
    if not declaration.rstrip().endswith('}'):return False
    filename=r'"(?:[^"\\\r\n]|\\[^\r\n])*"'
    gap=text[end:owner['start']]
    opening=re.fullmatch(r'\r?\n[ \t]*#[ \t]*line[ \t]+[0-9]+[ \t]+('+filename+r')[ \t]*\r?\n[ \t]*\r?\n[ \t]*',gap)
    if not opening:return False
    # A quoted example or macro continuation is never a real wrapper.
    directive=gap.find('#');offset=end+directive
    if not re.match(r'#[ \t]*line\b',code[offset:owner['start']]):return False
    closing=re.match(r'[ \t]*\r?\n[ \t]*#[ \t]*line[ \t]+[0-9]+[ \t]+('+filename+r')[ \t]*(?:\r?\n|$)',text[owner['end']:])
    if not closing or closing[1]!=opening[1]:return False
    close_offset=owner['end']+closing[0].find('#')
    return bool(re.match(r'#[ \t]*line\b',code[close_offset:close_offset+len(closing[0])]))


def owner_at(owners,code,text,start,end=None):
    """Use enclosure first, then an immediately leading standalone comment.

    A same-line trailing comment is never attached to the following declaration.
    Blank lines after a comment deliberately break leading ownership, except
    for one generated blank inside a paired definition-location wrapper.
    """
    for owner in owners:
        if owner['start']<=start<owner['end']:return owner
    if end is None:return None
    line_start=text.rfind('\n',0,start)+1
    if code[line_start:start].strip():return None
    for owner in owners:
        if owner['start']>=end:
            if definition_location_wrapper(code,text,end,owner):return owner
            gap=code[end:owner['start']]
            # A complete physical #line directive restores logical locations;
            # it does not detach a leading note. Keep all other gap text and
            # blank lines, and never treat masked literal/comment text as one.
            raw_gap=text[end:owner['start']]
            directives=list(re.finditer(
                r'^[ \t]*#[ \t]*line[ \t]+[0-9]+(?:[ \t]+"(?:[^"\\\r\n]|\\[^\r\n])*")?[ \t]*\r?\n',
                raw_gap,re.M))
            for directive in reversed(directives):
                offset=end+directive.start()
                if not re.match(r'^[ \t]*#[ \t]*line\b',code[offset:end+directive.end()]):continue
                if text[text.rfind('\n',0,offset)+1:offset].strip():continue
                gap=gap[:directive.start()]+gap[directive.end():]
            if not gap.strip() and gap.count('\n')<=1:return owner
            return None
    return None


def assembly_declarations(code,comment_free):
    """Locate real standalone assembly pragmas without interpreting their data.

    The literal-masked code confirms the directive is outside a quoted example;
    a preceding continued macro line cannot introduce a standalone directive.
    Function and retained-data paths both receive neutral assembly context.
    """
    matches=[]
    for m in re.finditer(r'^[ \t]*#pragma\s+GLOBAL_ASM\s*\(\s*"([^"\n]+)"\s*\)',comment_free,re.M):
        if not re.match(r'^[ \t]*#pragma\s+GLOBAL_ASM\b',code[m.start():m.end()]):continue
        previous_end=m.start()-1
        if previous_end>=0:
            previous_start=code.rfind('\n',0,previous_end)+1
            if code[previous_start:previous_end].rstrip(' \t\r').endswith('\\'):continue
        matches.append(m)
    return matches


def collect(root):
    groups={}; hashes={}
    def add(kind,path,symbol,line,evidence=None,owner=None,owner_line=None):
        key=(kind,path,symbol)
        if key not in groups:
            groups[key]={'id':'Q-'+hashlib.sha256('\0'.join(key).encode()).hexdigest()[:12],
                         'kind':kind,'path':path,'symbol':symbol,'lines':set()}
            if evidence:groups[key]['evidence']=evidence
        groups[key]['lines'].add(line)
        if owner:
            owners=groups[key].setdefault('owners',{})
            owner_key=(owner['kind'],owner['name'],owner_line)
            owners.setdefault(owner_key,set()).add(line)
    paths=sorted(p for directory in ['src','include'] for p in (root/directory).rglob('*')
                 if p.is_file() and p.suffix in ['.c','.h'])
    for p in paths:
        raw=p.read_bytes();path=p.relative_to(root).as_posix();hashes[path]=hashlib.sha256(raw).hexdigest()
        text=raw.decode();code,comment_free,comments=lexical_views(text)
        newlines=[m.start() for m in re.finditer('\n',text)]
        def line(offset):return bisect.bisect_left(newlines,offset)+1
        assembly=assembly_declarations(code,comment_free)
        owners=sorted(declaration_owners(code)+[
            {'kind':'assembly','name':Path(m[1]).stem,'start':m.start(),'end':m.end()}
            for m in assembly],key=lambda owner:(owner['start'],owner['end']))
        def contextual_add(kind,symbol,offset,evidence=None,end=None):
            owner=owner_at(owners,code,text,offset,end)
            add(kind,path,symbol,line(offset),evidence,owner,line(owner['start']) if owner else None)
        for kind,pattern in PATTERNS.items():
            for m in pattern.finditer(code):contextual_add(kind,m[0],m.start())
        for m in assembly:
            add('assembly',path,Path(m[1]).stem,line(m.start()),m[1])
        for start,comment in comments:
            normalized=' '.join(comment.replace('/*','').replace('*/','').replace('//','').split())
            kinds=[]
            if 'RE_UNKNOWN' in comment:kinds.append('explicit_unknown')
            if 'RE_ORIGINAL_QUIRK' in comment:kinds.append('original_quirk')
            if not kinds and UNCERTAIN.search(comment):kinds.append('uncertainty_note')
            for kind in kinds:contextual_add(kind,normalized,start,normalized,start+len(comment))
            for m in PATTERNS['draft_marker'].finditer(comment):
                owner=owner_at(owners,code,text,start,start+len(comment))
                add('draft_marker',path,m[0],line(start+m.start()),normalized,owner,line(owner['start']) if owner else None)
    for filename in ['STRATEGY_V4.md','VALIDATION_20261006.md']:
        p=root/'docs'/filename
        if not p.exists():continue
        path=p.relative_to(root).as_posix();raw=p.read_bytes();hashes[path]=hashlib.sha256(raw).hexdigest()
        for n,line in enumerate(raw.decode().splitlines(),1):
            for m in re.finditer(r'\bOC[0-9]+\b',line):add('audit_debt',path,m[0],n,line.strip())
    records=[]
    for key,value in sorted(groups.items()):
        if 'owners' in value:
            value['owners']=[{'kind':kind,'name':name,'declaration_line':n,'lines':sorted(locations)}
                             for (kind,name,n),locations in sorted(value['owners'].items())]
        value['lines']=sorted(value['lines']);records.append(value)
    counts=Counter(x['kind'] for x in records)
    return {'schema':1,'scope':'src/**/*.c and include/**/*.h, plus named audit entries in strategy/validation docs',
            'limitations':['Includes inactive conditional code; counts are search groups, not unique unknown meanings or completion percentages.',
                           'Neutral names, explicit notes and known naming conventions are indexed. Undiscovered semantic assumptions cannot be detected automatically.',
                           'Padding describes binary layout and is not an instruction to remove bytes. Original quirks require caller/reachability evidence before runtime changes.',
                           'Physical line locations are regenerated. Q identifiers remain stable while category, path and symbol/comment text remain unchanged.',
                           'Owners are conservative lexical function/type/global/assembly contexts, not semantic ownership. Complex declarators and detached/trailing comments can remain unowned.'],
            'source_hashes':hashes,'counts':dict(sorted(counts.items())),'items':records}


def markdown(index):
    lines=['# Reverse-engineering uncertainty index','',
           'Generated by `python3 tools/uncertainty_index.py`. Do not edit this index by hand.','',
           'Use `python3 tools/uncertainty_index.py --query NAME` to find indexed notes and identifiers by routine/type/global name, note text, category or source path. ',
           'Use `--check` to verify this index matches the current source. The complete locations and source hashes are in `UNCERTAINTIES.json`.','',
           '`RE_UNKNOWN:` comments state what remains unproven and what evidence would settle it. ',
           '`RE_ORIGINAL_QUIRK:` comments describe behavior intentionally preserved from the original game; they do not authorize a runtime change. ',
           'Keep offset names until field meaning and units are established. Record a caller, binary observation or data-format proof when resolving a note. ',
           'For every future source wave, regenerate and check this index after code and strategy edits, then include both generated files in that wave.','',
           '**Coverage:** recognizable unknown names, all assembly pragmas, explicit/older uncertainty comments, draft markers and named original-behavior audits. ',
           '**Limits:** this is a search aid, not proof that every undiscovered assumption is flagged. Counts include conditional/inactive code and repeated names. Padding is binary layout to preserve.','',
           '**Context:** owner names identify a lexically enclosing or immediately following C declaration or standalone assembly pragma, not proven runtime ownership. Assembly context uses the original assembly filename, including retained data. Detached/trailing notes and unsupported declarators remain unowned. All links use physical source lines, including files with `#line` directives.','',
           '| Category | Search groups |','| --- | ---: |']
    for kind,title in CATEGORIES.items():lines.append(f'| {title} | {index["counts"].get(kind,0)} |')
    by_path=defaultdict(list)
    for item in index['items']:by_path[item['path']].append(item)
    for path,items in sorted(by_path.items()):
        lines+=['',f'## {path}','', '| Kind | Identifier or note | Declaration context | Physical lines |','| --- | --- | --- | --- |']
        for item in items:
            symbol=item['symbol'].replace('|','\\|').replace('`',"'")
            if len(symbol)>180:symbol=symbol[:177]+'...'
            links=', '.join(f'[{n}](../{path}#L{n})' for n in item['lines'][:8])
            if len(item['lines'])>8:links+=f' (+{len(item["lines"])-8} in JSON)'
            contexts=', '.join(f'{o["kind"]} `{o["name"]}`' for o in item.get('owners',[])) or '—'
            lines.append(f'| {item["kind"]} | `{symbol}` | {contexts} | {links} |')
    return '\n'.join(line.rstrip() for line in lines)+'\n'


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root',type=Path,default=Path(__file__).resolve().parent.parent)
    parser.add_argument('--check',action='store_true')
    parser.add_argument('--query')
    args=parser.parse_args();root=args.root.resolve();index=collect(root)
    if args.query:
        needle=args.query.casefold();matches=[x for x in index['items'] if needle in (x['symbol']+' '+x['path']+' '+x['kind']+' '+' '.join(o['name'] for o in x.get('owners',[]))).casefold()]
        for item in matches:
            for n in item['lines']:
                contexts=', '.join(o['name'] for o in item.get('owners',[]) if n in o['lines'])
                context=f' [{contexts}]' if contexts else ''
                print(f'{item["path"]}:{n}: {item["kind"]}{context}: {item["symbol"]}')
        print(f'{len(matches)} search groups');return
    outputs={root/'docs/UNCERTAINTIES.json':json.dumps(index,indent=2)+'\n',root/'docs/UNCERTAINTIES.md':markdown(index)}
    for p,text in outputs.items():
        if args.check:
            if not p.exists() or p.read_bytes()!=text.encode():raise SystemExit(f'Stale uncertainty index: {p}; regenerate after source/doc edits.')
        else:p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(text.encode())
    print(json.dumps({'status':'PASS','mode':'check' if args.check else 'generate','source_files':len(index['source_hashes']),'search_groups':len(index['items']),'counts':index['counts']}))


if __name__=='__main__':main()
