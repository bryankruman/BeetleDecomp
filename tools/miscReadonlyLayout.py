"""Regenerate retained MISC assembly around its sixteen compiler-owned float bytes.

The patched module is an extraction input. Original-ROM equality is checked by
normal module packing and never replaced by the patched-input hash here.
"""
from pathlib import Path
import hashlib,json,os,re,struct
from moduleReadonlyLayout import original_bytes

def sha(raw):return hashlib.sha256(raw).hexdigest()
def require(ok,message):
 if not ok:raise ValueError('MISC readonly layout: '+message)
def inside(root,relative):
 require(type(relative)is str and relative and not Path(relative).is_absolute()and '..'not in Path(relative).parts,'relative project path required')
 root=Path(root).resolve();path=root/relative
 require(path.resolve().is_relative_to(root)and path.resolve()!=root,'path leaves project')
 require(not path.is_symlink()and all(not q.is_symlink()for q in path.parents),'symlink path')
 return path

def configuration(root,config,module):
 layout=json.loads(inside(root,config).read_bytes())
 keys={'version','module','source','source_sha256','helper_sha256','patched_module_sha256','original_packed_module_sha256','original_source_sha256','extraction_readonly_sha256','original_packed_readonly_sha256','begin','end','labels_sha256','prefix_assembly','suffix_assembly','bridge_assembly','monolithic_assembly','alias_script','alias_script_sha256','product_sha256'}
 require(set(layout)==keys and type(layout['version'])is int and layout['version']==5 and module==layout['module']=='misc','only MISC scalar-pool schema5 supported')
 require(layout['source']=='src/modules/misc.c'and(layout['begin'],layout['end'])==(0x404210,0x404300),'source or complete readonly boundary changed')
 require(layout['monolithic_assembly']=='asm/us/data/modules/misc.rodata.s','original generated source path changed')
 require([layout[k]for k in ('prefix_assembly','suffix_assembly','bridge_assembly')]==['asm/us/data/modules/misc.rodata-prefix.s','asm/us/data/modules/misc.rodata-suffix.s','asm/us/data/modules/misc.rodata-aliases.s'],'generated fragment paths changed')
 require(layout['alias_script']=='linker_scripts/us/module_files/misc_partial_aliases.ld','module alias path changed')
 for key in ('source_sha256','helper_sha256','patched_module_sha256','original_packed_module_sha256','original_source_sha256','extraction_readonly_sha256','original_packed_readonly_sha256','labels_sha256','alias_script_sha256'):
  require(type(layout[key])is str and re.fullmatch('[0-9a-f]{64}',layout[key]),'invalid hash: '+key)
 require(layout['patched_module_sha256']=='b9f8247b12918bfce6b70393a06e2b9385c8abbfea687501d18ee6a315f1eb84'and layout['original_packed_module_sha256']=='5860afcbb240b66074f15fa58e11822aba8e36fa8d3b541e8194349014aef0ec','patched/original module domains changed')
 require(layout['extraction_readonly_sha256']=='31e02a10d34f205cb27fdc1d75fb51d47073195d2bfc3193211a7d2268675afa'and layout['original_packed_readonly_sha256']=='09f7586f33f305a4c13be00ed068167dfd05c566f1cc101f995363bf9ba260e4','extraction and original packed RO domains changed')
 require(set(layout['product_sha256'])=={'prefix','suffix','bridge'}and all(re.fullmatch('[0-9a-f]{64}',v)for v in layout['product_sha256'].values()),'fragment hashes required')
 paths=[layout[k]for k in ('source','prefix_assembly','suffix_assembly','bridge_assembly','monolithic_assembly','alias_script')]
 require(len(set(paths))==len(paths),'overlapping paths')
 for name in paths:inside(root,name)
 require(sha(inside(root,'tools/miscReadonlyLayout.py').read_bytes())==layout['helper_sha256'],'layout helper changed')
 require(sha(inside(root,layout['source']).read_bytes())==layout['source_sha256'],'qualified C source changed')
 require(sha(inside(root,layout['alias_script']).read_bytes())==layout['alias_script_sha256'],'module order/aliases changed')
 return layout

def render(layout,raw):
 require(sha(raw)==layout['original_source_sha256'],'fresh original readonly assembly changed')
 text=raw.decode('utf-8');require(text.encode()==raw,'nonliteral UTF8 source')
 selected=['D_misc_00404290','D_misc_00404294','D_misc_00404298','D_misc_0040429C']
 start=text.index('nonmatching '+selected[0]+'\n');stop=text.index('nonmatching D_misc_004042A0\n',start)
 prefix,island,suffix=text[:start],text[start:stop],text[stop:]
 require(prefix+island+suffix==text,'original split inverse failed')
 labels=re.findall(r'(?m)^dlabel (D_misc_[0-9A-Fa-f]{8})\s*$',text)
 require(len(labels)==len(set(labels))==43 and sha(json.dumps(labels,separators=(',',':')).encode())==layout['labels_sha256'],'all43 original labels changed')
 require(re.findall(r'(?m)^dlabel (\w+)\s*$',island)==selected,'selected labels changed')
 require(len(re.findall(r'(?m)^enddlabel ',island))==4 and len(re.findall(r'(?m)^\s*(?:/\*.*?\*/\s*)?\.word ',island))==4,'selected original four nominal spans changed')
 require(not any(x in island for x in ('.space','.ascii','.asciz','.align')),'selected slice conceals storage')
 decoded=original_bytes(text,layout['begin'],layout['end'])
 require(len(decoded)==240 and sha(decoded)==layout['extraction_readonly_sha256'],'complete original240 bytes changed')
 require(original_bytes(prefix,layout['begin'],layout['begin']+128)==decoded[:128]and original_bytes(island,layout['begin']+128,layout['begin']+144)==decoded[128:144]and original_bytes(suffix,layout['begin']+144,layout['end'])==decoded[144:],'128/16/96 ownership mismatch')
 bridge='/* Undefined typed objects; the linker supplies their real pool coordinates. */\n'
 for name in selected:bridge+='\n.globl '+name+'\n.type '+name+', @object\n.size '+name+', 4\n'
 products={'prefix':prefix.encode(),'suffix':b'.include "macro.inc"\n.section .rodata\n.align 4\n'+suffix.encode(),'bridge':bridge.encode()}
 require({k:sha(v)for k,v in products.items()}==layout['product_sha256'],'generated retained fragments differ from qualified composition')
 return products

def prepare(root,config,module,binary):
 root=Path(root).resolve();layout=configuration(root,config,module)
 raw=Path(binary).read_bytes();require(sha(raw)==layout['patched_module_sha256'],'patched original extraction input changed')
 require(len(raw)>=0x50 and raw[:4]==b'FORM'and raw[8:12]==b'MODU'and raw[0x18:0x1c]==b'COMM','invalid patched module header')
 text_bytes,readonly_bytes=struct.unpack_from('>II',raw,0x28)
 require(text_bytes==16912 and readonly_bytes==240,'patched section boundaries changed')
 require(sha(raw[0x50+text_bytes:0x50+text_bytes+readonly_bytes])==layout['extraction_readonly_sha256'],'patched input readonly changed')
 # The original readonly witness is generated by the following disassembly.
 # Read and render that fresh output only in apply(), after extraction.
 for role in ('prefix','suffix','bridge'):
  path=inside(root,layout[role+'_assembly'])
  if path.exists():require(path.is_file()and sha(path.read_bytes())==layout['product_sha256'][role],'unrecognized existing retained fragment')
 return dict(root=root,config=config,module=module,binary=Path(binary),layout=layout,patched_input_sha256=sha(raw))

def apply(plan):
 # Existing moduleExtract regenerates the complete original ASM before this call.
 plan=prepare(plan['root'],plan['config'],plan['module'],plan['binary']);root=plan['root'];layout=plan['layout']
 original=inside(root,layout['monolithic_assembly']);require(original.is_file(),'normal extraction did not emit original readonly assembly')
 raw=original.read_bytes();products=render(layout,raw);outputs=[(inside(root,layout[role+'_assembly']),contents)for role,contents in products.items()]
 temporaries=[path.with_name(path.name+'.readonly-layout.tmp')for path,_ in outputs]
 require(all(path.parent.is_dir()and not temporary.exists()and not temporary.is_symlink()for(path,_),temporary in zip(outputs,temporaries)),'temporary output exists or parent missing')
 require(original.read_bytes()==raw,'original witness changed before write')
 try:
  for(_,contents),temporary in zip(outputs,temporaries):
   with temporary.open('xb')as stream:stream.write(contents)
   require(temporary.read_bytes()==contents,'staged fragment readback failed')
  for(path,_),temporary in zip(outputs,temporaries):os.replace(temporary,path)
  require(all(path.read_bytes()==contents for path,contents in outputs),'fragment readback changed')
  require(original.read_bytes()==raw,'original witness changed before retirement')
  original.unlink()
 finally:
  for temporary in temporaries:
   if temporary.exists():temporary.unlink()
