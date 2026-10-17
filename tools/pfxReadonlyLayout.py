"""Version6: one measured PFX getter owns one scalar and two adjacent tables.

The retained suffix uses the existing asm-processor late-rodata host mechanism.
This helper never trims or rewrites an ELF object. Normal packed/native gates
must still prove the final512-byte section,106 relocations and original ROM.
"""
from pathlib import Path
import os,re,struct
import moduleReadonlyLayout as common

MODULE='uvpfx_rom'
SOURCE='src/modules/uvpfx_rom.c'
OWNER='uvPfxGetProps'
RAW_OWNER='func_uvpfx_rom_004012CC'
HOST='func_uvpfx_rom_00401888'
PREFIX='asm/us/data/modules/uvpfx_rom.rodata-prefix.s'
WITNESS='tools/readonly_layout/uvpfx_rom.original-rodata.s'
HOST_ASM='asm/us/nonmatchings/modules/uvpfx_rom/'+HOST+'.s'
MONOLITH='asm/us/data/modules/uvpfx_rom.rodata.s'
GROUP=[['D_uvpfx_rom_00404E20',0x404E20,0x404E24,'scalar'],
       ['D_uvpfx_rom_00404E24',0x404E24,0x404E5C,'table'],
       ['D_uvpfx_rom_00404E5C',0x404E5C,0x404EF4,'table']]

def require(value,message):common.require(value,'PFX group: '+message)

def validate_layout(layout,module):
    keys={'version','module','source','source_sha256','witness','witness_sha256','readonly_sha256',
          'begin','end','group','owner_original_symbol','owner_c_symbol','owner_address','owner_bytes',
          'owner_instruction_sha256','owner_asm_normalized_sha256','owner_body_sha256',
          'host_symbol','host_address','host_bytes','host_assembly','host_sha256',
          'prefix_assembly','monolithic_assembly','partial_alias','partial_alias_sha256',
          'expected_normal_rodata_bytes','expected_normal_REL_records','expected_normal_suffix_offset'}
    require(set(layout)==keys and type(layout['version'])is int and layout['version']==6 and layout['module']==module==MODULE,'finite schema/module')
    require(all(type(layout[key])is int for key in ('begin','end','owner_address','owner_bytes','host_address','host_bytes','expected_normal_rodata_bytes','expected_normal_REL_records','expected_normal_suffix_offset')),'integer extents')
    require(isinstance(layout['group'],list)and all(isinstance(row,list)and len(row)==4 and type(row[1])is int and type(row[2])is int for row in layout['group']),'typed group ranges')
    require(layout['source']==SOURCE and layout['witness']==WITNESS and layout['prefix_assembly']==PREFIX and layout['monolithic_assembly']==MONOLITH,'finite storage paths')
    require(layout['group']==GROUP and(layout['begin'],layout['end'])==(0x404D40,0x404F40),'finite grouped ranges')
    require((layout['owner_original_symbol'],layout['owner_c_symbol'],layout['owner_address'],layout['owner_bytes'])==(RAW_OWNER,OWNER,0x4012CC,1348),'finite owner')
    require((layout['host_symbol'],layout['host_address'],layout['host_bytes'],layout['host_assembly'])==(HOST,0x401888,284,HOST_ASM),'finite real assembly host')
    require(layout['partial_alias']=='linker_scripts/us/module_files/uvpfx_rom_partial_aliases.ld','finite alias path')
    require((layout['expected_normal_rodata_bytes'],layout['expected_normal_REL_records'],layout['expected_normal_suffix_offset'])==(512,106,436),'required future normal gates')
    for key in keys:
        if key.endswith('_sha256'):require(isinstance(layout[key],str)and re.fullmatch('[0-9a-f]{64}',layout[key]),'invalid digest: '+key)
    require(layout['witness_sha256']=='c0bec1e9f3d2f0eb246f646021faea4ed0a59b52075b54f0fc1be084b95fe69c','original readonly witness')
    require(layout['readonly_sha256']=='9a7c004f2b26fb6bcc89ede98e51a7bd4c45a32d48034133f74477e3c5879f13','complete original readonly annotations')
    require(layout['host_sha256']=='72eaf35adc25032d5786eb6b8838b6cbf8f11cce6f0886aeca43f18a894dcf07','original assembly host')

def fragments(layout,witness):
    validate_layout(layout,MODULE)
    require(common.sha(witness.encode())==layout['witness_sha256'],'witness changed')
    decoded=common.original_bytes(witness,layout['begin'],layout['end'])
    require(len(decoded)==512 and common.sha(decoded)==layout['readonly_sha256'],'complete witness bytes')
    bounds=[]
    for label,begin,end,kind in GROUP:
        start='nonmatching '+label+'\n';stop='enddlabel '+label
        require(witness.count(start)==1 and witness.count(stop)==1,'single group component')
        lo=witness.index(start);hi=witness.index(stop,lo)+len(stop)
        payload=common.original_bytes(witness[lo:hi],begin,end)
        require(payload==decoded[begin-layout['begin']:end-layout['begin']],'component byte coverage')
        if kind=='scalar':require(payload==bytes.fromhex('3c23d70a'),'literal0.01f scalar')
        else:
            words=struct.unpack('>'+str(len(payload)//4)+'I',payload)
            require(all(0x4012CC<=word<0x401810 and word%4==0 for word in words),'table target outside measured getter')
        bounds.append((lo,hi))
    require(all(bounds[i][1]<bounds[i+1][0]for i in (0,1)),'component physical order')
    prefix=('.section .rodata\n'+common.retained(witness[:bounds[0][0]])).encode()
    suffix=common.v3_fragment(0x404EF4,witness[bounds[-1][1]:])
    require(common.original_bytes(prefix.decode(),0x404D40,0x404E20)==decoded[:224],'prefix exact224')
    require(common.original_bytes(suffix.decode(),0x404EF4,0x404F40)==decoded[436:],'suffix exact76')
    require(suffix.startswith(b'.section .late_rodata\n.late_rodata_alignment 4\n'),'suffix phase4')
    return decoded,prefix,suffix

def validate_source(root,layout):
    source=common.inside(root,SOURCE).read_bytes()
    require(common.sha(source)==layout['source_sha256'],'complete grouped source changed')
    text=source.decode()
    masked=re.sub(r'/\*.*?\*/|//[^\n]*',lambda m:'\n'*m[0].count('\n'),text,flags=re.S)
    prefix='#pragma GLOBAL_ASM("'+PREFIX+'")';host='#pragma GLOBAL_ASM("'+HOST_ASM+'")'
    require(masked.count(prefix)==masked.count(host)==1,'single prefix and actual host pragma')
    require(not re.search(r'^\s*#\s*define\s+NEEDS_RODATA\b',masked,re.M),'parked draft macro must stay undefined')
    require('-DNEEDS_RODATA'not in common.inside(root,'Makefile').read_text(encoding='utf-8'),'Makefile enables parked draft macro')
    stack=[]
    for line in masked.splitlines():
        directive=re.match(r'^\s*#\s*(if|ifdef|ifndef|else|elif|endif)\b(.*)',line)
        if directive:
            kind,expression=directive[1],directive[2].strip()
            if kind in ('if','ifdef','ifndef'):stack.append([kind,expression,False])
            elif kind in ('else','elif'):
                require(stack and stack[-1][2]is False,'unexpected conditional arm');stack[-1][2]=kind
            else:require(stack,'unbalanced conditional');stack.pop()
        if prefix in line:require(not stack and line.strip()==prefix,'prefix must be unconditional standalone source')
        if host in line:
            # Only this exact, source-hash-bound existing parked draft is
            # supported. Historical validators and all other arms stay strict.
            require(stack==[['ifdef','NEEDS_RODATA','else']]and line.strip()==host,'host is not the measured undefined-macro else arm')
    require(not stack,'unterminated source conditional')
    match=re.search(r'^void uvPfxGetProps\([^;{}]*\)\s*\{',masked,re.M)
    require(match is not None,'getter body absent')
    definitions=list(re.finditer(r'^[ \t]*[A-Za-z_][^;{}\n]*\([^;{}]*\)\s*\{',masked,re.M))
    require(all(masked.index(prefix)<match.start()for match in definitions),'prefix must precede every C definition')
    require(masked.index(prefix)<match.start()<masked.index(host),'grouped owner/host source order')
    require(not re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/(?:'+RAW_OWNER+'|'+OWNER+r')\.s"\)',masked),'owner remains assembly-backed')
    start=text.index('void uvPfxGetProps(');brace=text.index('{',start);depth=1;at=brace+1
    while depth and at<len(text):
        depth+=(text[at]=='{')-(text[at]=='}');at+=1
    require(depth==0 and common.sha(text[brace:at].encode())==layout['owner_body_sha256'],'frozen getter body changed')
    alias=common.inside(root,layout['partial_alias']).read_bytes()
    require(common.sha(alias)==layout['partial_alias_sha256']and alias==b'func_uvpfx_rom_004012CC = uvPfxGetProps;\n','genuine raw-to-canonical alias expression')

def validate_users(root,layout,prefix):
    allowed={WITNESS,MONOLITH,PREFIX}
    # --dont-split-rodata suppresses the monolithic output, while function
    # migration still emits these three unreferenced original RO witnesses.
    # Bind all standalone-assembly rules; accepting definitions must never
    # admit another compiled owner or a source reference to these components.
    require(common.sha(common.inside(root,'Makefile').read_bytes())==
            'a1383418fa1cfac6e03c53b564c1693af08e8cdcb7b1b1df7e2ae973d1a0ac50',
            'finite grouped-witness Makefile changed')
    witness=common.inside(root,WITNESS).read_text(encoding='utf-8')
    require(common.sha(witness.encode())==layout['witness_sha256'],'group witness changed')
    for label,begin,end,kind in GROUP:
        start='nonmatching '+label+'\n';stop='enddlabel '+label
        require(witness.count(start)==witness.count(stop)==1,'single generated witness component')
        lo=witness.index(start);hi=witness.index(stop,lo)+len(stop)
        expected=('.section .rodata\n'+witness[lo:hi]+'\n').encode()
        component=common.inside(root,'asm/us/nonmatchings/modules/'+MODULE+'/'+label+'.s')
        if component.exists():
            require(component.is_file()and component.read_bytes()==expected,
                    'generated grouped witness changed: '+label)
            allowed.add(component.relative_to(root).as_posix())
    for name in (RAW_OWNER,OWNER):
        path=common.inside(root,'asm/us/nonmatchings/modules/'+MODULE+'/'+name+'.s')
        if path.exists():
            common.validate_unused_owner_asm(layout,path,name);allowed.add(path.relative_to(root).as_posix())
    generated=common.inside(root,PREFIX)
    if generated.exists():require(generated.read_bytes()==prefix,'existing retained prefix changed')
    labels=re.compile(r'\b(?:D_uvpfx_rom_00404E20|D_uvpfx_rom_00404E24|D_uvpfx_rom_00404E5C)\b')
    for folder in ('asm/us','src','include'):
        for path in (root/folder).rglob('*'):
            if path.is_file()and path.suffix in ('.s','.c','.h')and path.relative_to(root).as_posix()not in allowed:
                contents=path.read_text(encoding='utf-8')
                require(labels.search(contents)is None,'another grouped-data user: '+path.relative_to(root).as_posix())
                if path.suffix=='.h':require(not re.search(r'^\s*#\s*define\s+NEEDS_RODATA\b',contents,re.M),'header enables parked draft macro')

def configuration(root,config,module):
    root=Path(root).resolve();layout=__import__('json').loads(common.inside(root,config).read_bytes())
    validate_layout(layout,module)
    for key in ('source','witness','host_assembly','prefix_assembly','monolithic_assembly','partial_alias'):common.inside(root,layout[key])
    witness=common.inside(root,WITNESS).read_text(encoding='utf-8');decoded,prefix,suffix=fragments(layout,witness)
    validate_source(root,layout);validate_users(root,layout,prefix)
    host=common.inside(root,HOST_ASM)
    if host.exists():common.host_text(layout,host.read_bytes(),suffix)
    monolith=common.inside(root,MONOLITH)
    if monolith.exists():require(monolith.read_bytes()==witness.encode(),'unexpected monolithic readonly source')
    return dict(root=root,config=config,module=module,layout=layout,decoded=decoded,prefix=prefix,suffix=suffix)

def prepare(root,config,module,binary):
    plan=configuration(root,config,module);raw=Path(binary).read_bytes()
    require(len(raw)>=0x50 and raw[:4]==b'FORM'and raw[8:12]==b'MODU'and raw[0x18:0x1C]==b'COMM','original patched module header')
    text_bytes,readonly_bytes=struct.unpack_from('>II',raw,0x28)
    require((text_bytes,readonly_bytes)==(19776,512),'original section extents')
    require(raw[0x50+text_bytes:0x50+text_bytes+readonly_bytes]==plan['decoded'],'actual patched module readonly differs from original witness')
    plan['binary']=Path(binary)
    return plan

def declared_prefix(root,config,module):
    """Report exactly one data pragma; the real ASM host remains unfinished."""
    plan=configuration(root,config,module);root,layout=plan['root'],plan['layout']
    prefix=common.inside(root,PREFIX);host=common.inside(root,HOST_ASM)
    require(prefix.is_file()and prefix.read_bytes()==plan['prefix'],'declared prefix missing or changed')
    require(host.is_file(),'declared real suffix host absent')
    original=common.host_text(layout,host.read_bytes(),plan['suffix'])
    require(host.read_bytes()==original+common.SUFFIX_MARKER+plan['suffix'],'declared suffix missing or changed')
    return dict(source=SOURCE,symbol=prefix.stem,assembly=PREFIX,bytes=224,module=MODULE,metadata=config,
                witness=WITNESS,witness_sha256=layout['witness_sha256'],assembly_sha256=common.sha(plan['prefix']),
                original_readonly_bytes=512,retained_readonly_bytes=300,compiler_owned_readonly_bytes=212,
                ownership='preserved-original-readonly-prefix')

def apply(plan):
    # Revalidate source, original binary, complete witness and every user before
    # staging the two ordinary extraction outputs. Existing schemas are untouched.
    plan=prepare(plan['root'],plan['config'],plan['module'],plan['binary'])
    root,layout=plan['root'],plan['layout'];host=common.inside(root,HOST_ASM)
    require(host.is_file(),'normal function extraction did not emit real host')
    original=common.host_text(layout,host.read_bytes(),plan['suffix'])
    outputs=[(common.inside(root,PREFIX),plan['prefix']),(host,original+common.SUFFIX_MARKER+plan['suffix'])]
    staged=[]
    try:
        for path,content in outputs:
            path.parent.mkdir(parents=True,exist_ok=True);temporary=path.with_name(path.name+'.readonly-layout.tmp')
            require(not temporary.exists()and not temporary.is_symlink(),'temporary output already exists')
            temporary.write_bytes(content);staged.append((temporary,path))
        for temporary,path in staged:os.replace(temporary,path)
    finally:
        for temporary,path in staged:
            if temporary.exists():temporary.unlink()
    monolith=common.inside(root,MONOLITH)
    if monolith.exists():
        require(monolith.read_bytes()==common.inside(root,WITNESS).read_bytes(),'monolithic readonly changed before removal')
        monolith.unlink()
