"""Restore the declared RACE table/island order in its compiled source object.

Only the reviewed two24B spans/six symbols/seven references are permitted.
Every other ELF byte is retained; already-laid-out input is checked without writes.
"""
from pathlib import Path
import argparse,hashlib,importlib.util,json,os,struct

sha=lambda raw:hashlib.sha256(raw).hexdigest()
class Blob:
    def __init__(self,raw):self.raw=raw
    def read_bytes(self):return self.raw
def parsed(raw):return elf(Blob(raw))

def elf(path):
 raw=path.read_bytes();h=struct.unpack_from('>16sHHIIIIIHHHHHH',raw)
 assert h[0][:6]==b'\x7fELF\x01\x02'and h[1]in(1,2)and h[2]==8 and h[11]==40
 assert h[6]+h[12]*40<=len(raw)
 sections=[struct.unpack_from('>10I',raw,h[6]+n*40)for n in range(h[12])]
 def data(i):
  q=sections[i]
  if q[1]==8:return b''
  assert q[4]+q[5]<=len(raw);return raw[q[4]:q[4]+q[5]]
 def string(t,i):assert i<len(t);return t[i:t.index(b'\0',i)].decode()
 names=[string(data(h[13]),s[0])for s in sections]
 def symbols(i):
  q=sections[i];assert q[1]==2 and q[9]==16 and q[5]%16==0;t=data(q[6]);out=[]
  for off in range(0,q[5],16):
   n,v,z,info,other,idx=struct.unpack_from('>IIIBBH',data(i),off)
   out.append(dict(name=string(t,n),value=v,bytes=z,type=info&15,binding=info>>4,section=names[idx]if idx<len(names)else'ABS'if idx==0xfff1 else'OTHER',section_index=idx))
  return out
 syms=symbols(names.index('.symtab'));relocs=[]
 for i,q in enumerate(sections):
  if q[1]not in(4,9):continue
  width=12 if q[1]==4 else 8;assert q[9]==width and q[5]%width==0;table=symbols(q[6])
  for off in range(0,q[5],width):
   fields=struct.unpack_from('>IIi'if width==12 else'>II',data(i),off);site,info=fields[:2];symbol=table[info>>8];kind=info&255
   assert kind in(2,4,5,6,10)
   relocs.append(dict(relocation_section=names[i],relocation_section_type=q[1],section=names[q[7]],offset=site,kind=kind,symbol=symbol['name'],symbol_section=symbol['section'],symbol_value=symbol['value'],explicit_addend=fields[2]if width==12 else None))
 assert len(set(names))==len(names)
 return dict(raw=raw,elf_type=h[1],sections={n:dict(address=s[3],flags=s[2],type=s[1],declared_bytes=s[5],data=data(i))for i,(n,s)in enumerate(zip(names,sections,strict=True))},symbols=syms,relocations=relocs)

def transform(raw, spans):
    h = struct.unpack_from('>16sHHIIIIIHHHHHH', raw)
    assert h[0][:6] == b'\x7fELF\x01\x02' and h[1] == 1 and h[2] == 8
    assert h[5] == 0 and h[11] == 40 and h[6] + 40 * h[12] <= len(raw)
    sec = [struct.unpack_from('>10I', raw, h[6] + 40 * i) for i in range(h[12])]
    def data(i):
        s = sec[i]
        assert s[1] != 8 and s[4] + s[5] <= len(raw)
        return raw[s[4]:s[4] + s[5]]
    def string(buf, at):
        assert 0 <= at < len(buf)
        return buf[at:buf.index(b'\0', at)].decode('ascii')
    names = [string(data(h[13]), s[0]) for s in sec]
    assert len(set(names)) == len(names)
    ro = names.index('.rodata')
    assert sec[ro][1] == 1 and sec[ro][5] == 1584
    assert spans and all(type(x) is int for row in spans for x in row)
    assert all(len(row) == 3 for row in spans)
    old_words = []; new_words = []
    for a, z, dest in spans:
        assert 0 <= a < z <= sec[ro][5] and 0 <= dest < dest + z-a <= sec[ro][5]
        assert a % 4 == z % 4 == dest % 4 == 0
        old_words.extend(range(a, z, 4)); new_words.extend(range(dest, dest+z-a, 4))
    assert len(set(old_words)) == len(old_words)
    assert len(set(new_words)) == len(new_words) and sorted(old_words) == sorted(new_words)
    def mapped(value):
        assert 0 <= value < sec[ro][5]
        for a, z, dest in spans:
            if a <= value < z: return dest + value-a
        return value
    out = bytearray(raw); edits = []; allowed = set()
    def put(at, payload, label):
        assert 0 <= at <= at+len(payload) <= len(raw)
        assert not allowed.intersection(range(at, at+len(payload)))
        allowed.update(range(at, at+len(payload)))
        out[at:at+len(payload)] = payload
        if payload != raw[at:at+len(payload)]: edits.append(dict(label=label, offset=at, bytes=len(payload)))
    for a, z, dest in spans:
        put(sec[ro][4]+dest, data(ro)[a:z], 'readonly-span')
    symtabs = {}; symnames = {}; symbol_changes = []
    for i, s in enumerate(sec):
        if s[1] != 2: continue
        assert s[9] == 16 and s[5] % 16 == 0
        entries = []; entry_names = []
        for at in range(0, s[5], 16):
            n, v, size, info, other, idx = struct.unpack_from('>IIIBBH', data(i), at)
            nv = v
            if idx == ro and (info & 15) != 3:
                assert v < sec[ro][5] or (v == sec[ro][5] and size == 0)
                if v < sec[ro][5]:
                    nv = mapped(v)
                    if size:
                        assert v + size <= sec[ro][5]
                        touched = [row for row in spans if v < row[1] and row[0] < v+size]
                        assert not touched or (len(touched) == 1 and touched[0][0] <= v and v+size <= touched[0][1])
                if nv != v:
                    put(s[4]+at+4, struct.pack('>I', nv), 'readonly-symbol-value')
                    symbol_changes.append(dict(name=string(data(s[6]), n), old=v, new=nv, bytes=size))
            elif idx == ro:
                assert v == 0 and size in (0, sec[ro][5])
            entries.append((v, nv, idx))
            entry_names.append(string(data(s[6]), n))
        symtabs[i] = entries
        symnames[i] = entry_names
    site_changes = []; operand_changes = []; reference_count = 0; affected_references = []
    for i, s in enumerate(sec):
        if s[1] not in (4, 9): continue
        width = 12 if s[1] == 4 else 8
        assert s[9] == width and s[5] % width == 0 and s[6] in symtabs
        target = s[7]; assert 0 <= target < len(sec) and sec[target][1] != 8
        pending = {}
        for at in range(0, s[5], width):
            site, info = struct.unpack_from('>II', data(i), at)
            symbol = info >> 8; kind = info & 255
            assert symbol < len(symtabs[s[6]]) and site % 4 == 0 and site+4 <= sec[target][5]
            sv, nsv, idx = symtabs[s[6]][symbol]
            if target == ro:
                new_site = mapped(site)
                if new_site != site:
                    put(s[4]+at, struct.pack('>I', new_site), 'readonly-relocation-site')
                    site_changes.append(dict(section=names[i], old=site, new=new_site, kind=kind))
            if idx != ro: continue
            reference_count += 1
            # This initial capability deliberately accepts only the actual REL
            # encodings. An explicit-addend readonly reference requires review.
            assert s[1] == 9 and kind in (2, 5, 6)
            word = struct.unpack_from('>I', data(target), site)[0]
            physical_site = sec[target][4] + (mapped(site) if target == ro else site)
            def rewrite_operand(new_word, label):
                if new_word != word:
                    put(physical_site, struct.pack('>I', new_word), label)
                    operand_changes.append(dict(section=names[target], site=site, kind=kind, old=word, new=new_word))
            if kind == 2:
                old_target = sv + word
                new_target = mapped(old_target)
                new_addend = new_target - nsv
                assert 0 <= new_addend <= 0xffffffff
                if new_target != old_target:
                    affected_references.append(dict(section=names[target],site=site,kind=2,symbol=symnames[s[6]][symbol],old_target=old_target,new_target=new_target))
                rewrite_operand(new_addend, 'readonly-R32-addend')
            elif kind == 5:
                assert word >> 26 == 15
                pending.setdefault(symbol, []).append((site, word))
            else:
                assert symbol in pending and pending[symbol]
                assert word >> 26 in (8, 9, 32, 33, 35, 36, 37, 40, 41, 43, 49, 53, 57, 61)
                low = word & 0xffff; signed_low = low if low < 0x8000 else low-0x10000
                lows = set()
                for hi_site, hi_word in pending.pop(symbol):
                    assert (hi_word >> 16) & 31 == (word >> 21) & 31
                    old_addend = ((hi_word & 0xffff) << 16) + signed_low
                    old_target = sv + old_addend
                    new_target = mapped(old_target)
                    new_addend = new_target - nsv
                    assert -0x80000000 <= new_addend <= 0x7fffffff
                    if new_target != old_target:
                        affected_references.append(dict(section=names[target],site=site,hi_site=hi_site,kind=6,symbol=symnames[s[6]][symbol],old_target=old_target,new_target=new_target))
                    high = ((new_addend + 0x8000) >> 16) & 0xffff
                    lows.add(new_addend & 0xffff)
                    new_hi_word = (hi_word & 0xffff0000) | high
                    if new_hi_word != hi_word:
                        physical_hi = sec[target][4] + (mapped(hi_site) if target == ro else hi_site)
                        put(physical_hi, struct.pack('>I', new_hi_word), 'readonly-HI16-addend')
                        operand_changes.append(dict(section=names[target], site=hi_site, kind=5, old=hi_word, new=new_hi_word))
                assert len(lows) == 1
                rewrite_operand((word & 0xffff0000) | lows.pop(), 'readonly-LO16-addend')
        assert not pending
    changed = {i for i, (a, b) in enumerate(zip(raw, out, strict=True)) if a != b}
    assert changed <= allowed and len(out) == len(raw)
    return bytes(out), dict(symbol_changes=symbol_changes, relocation_site_changes=site_changes,
                            operand_changes=operand_changes, readonly_reference_records=reference_count,
                            affected_references=affected_references,
                            changed_bytes=len(changed), edits=edits,
                            output_sha256=hashlib.sha256(out).hexdigest())

def _state_two_owner_legacy(raw,c):
    e = parsed(raw); ro = e['sections']['.rodata']['data']
    assert len(ro)==1584 and sha(ro[:1504])==c['readonly_prefix_sha256'] and sha(ro[1552:])==c['second_table_sha256']
    symbols = [s for s in e['symbols'] if s['section']=='.rodata' and 1504 <= s['value'] < 1552]
    assert len(symbols)==6 and {s['name'] for s in symbols}==set(c['floats'])
    assert all(s['type']==0 and s['bytes']==0 for s in symbols)
    positions = {s['name']:s['value'] for s in symbols}
    sites = {r['offset'] for r in e['relocations'] if r['section']=='.rodata'}
    assert len(sites)==29
    raw_state = (sha(ro[1504:1528])==c['retained_island_sha256'] and sha(ro[1528:1552])==c['first_table_sha256']
                 and positions==dict(zip(c['floats'],range(1504,1528,4)))
                 and sites.intersection(range(1504,1552,4))==set(range(1528,1552,4)))
    final_state = (sha(ro[1528:1552])==c['retained_island_sha256'] and sha(ro[1504:1528])==c['first_table_sha256']
                   and positions==dict(zip(c['floats'],range(1528,1552,4)))
                   and sites.intersection(range(1504,1552,4))==set(range(1504,1528,4)))
    assert raw_state != final_state
    return 'raw' if raw_state else 'laid-out'

def _restore_two_owner_legacy(raw,c):
    before_state = state(raw,c)
    if before_state=='laid-out':
        inverse, _ = transform(raw,c['spans'])
        restored, audit = restore(inverse,c)
        assert restored==raw
        return raw, dict(state='already-laid-out',rewritten=False,audit=audit)
    out,audit = transform(raw,c['spans'])
    assert state(out,c)=='laid-out'
    assert sorted(audit['affected_references'],key=lambda q:q['site'])==sorted(c['affected_references'],key=lambda q:q['site'])
    assert audit['operand_changes']==[dict(section='.text',site=14540,kind=6,old=0x8c2e05f8,new=0x8c2e05e0)]
    assert len(audit['symbol_changes'])==len(audit['relocation_site_changes'])==6
    inverse,_=transform(out,c['spans']);assert inverse==raw
    e=parsed(out);ro=e['sections']['.rodata']['data'];rr=[r for r in e['relocations']if r['section']=='.rodata']
    replay=bytearray(ro);bases={'.text':0x400000,'.rodata':0x4041D0,'.data':0x404800,'.bss':0x4049E0,'ABS':0}
    for r in rr:
        assert r['kind']==2 and r['explicit_addend'] is None and r['symbol_section'] in bases
        value=bases[r['symbol_section']]+r['symbol_value']+struct.unpack_from('>I',ro,r['offset'])[0]
        struct.pack_into('>I',replay,r['offset'],value)
    assert sha(replay)==c['native_readonly_sha256']
    expected=[tuple(row) for row in c['table_native_target_pairs']]
    assert sorted((r['offset'],struct.unpack_from('>I',replay,r['offset'])[0])for r in rr if r['offset'] in dict(expected))==expected
    assert [r for r in rr if r['offset'] not in dict(expected)]==c['original_non_table_RO_records']
    return out,dict(state='raw',rewritten=True,audit=audit)

def state_three_owners(raw,c):
    assert c['schema']==2 and c['coordinate_scope']=='ORIGINAL_ASM_ADDRESS_WITNESS_NOT_PACKED_RUNTIME'
    assert c['spans']==[[1484,1508,1528],[1508,1528,1484],[1528,1552,1504]]
    assert c['inverse_spans']==[[1528,1552,1484],[1484,1504,1508],[1504,1528,1528]]
    e=parsed(raw);ro=e['sections']['.rodata']['data']
    assert len(ro)==1584 and sha(ro[:1484])==c['readonly_prefix_sha256'] and sha(ro[1552:])==c['second_table_sha256']
    for name,value,size in(('raceDispatchStateAndUpdateOverlays',13144,308),('racePlayPendingTrackSound',14512,700),('racePlayPendingPlayerMessageSound',15212,1240)):
        symbol,=[q for q in e['symbols']if q['name']==name and q['section']=='.text']
        assert(symbol['binding'],symbol['type'],symbol['value'],symbol['bytes'])==(1,2,value,size)
    symbols=[q for q in e['symbols']if q['section']=='.rodata'and 1484<=q['value']<1552]
    assert len(symbols)==6 and {q['name']for q in symbols}==set(c['floats'])
    assert all(q['type']==0 and q['bytes']==0 for q in symbols)
    positions={q['name']:q['value']for q in symbols}
    records=[q for q in e['relocations']if q['section']=='.rodata']
    assert len(records)==29 and len({q['offset']for q in records})==29
    sites={q['offset']for q in records};assert all(0<=site<1584 and site%4==0 for site in sites)
    raw_state=(sha(ro[1484:1508])==c['retained_island_sha256']and sha(ro[1508:1528])==c['dispatch_table_sha256']and sha(ro[1528:1552])==c['first_table_sha256']and positions==dict(zip(c['floats'],range(1484,1508,4)))and sites.intersection(range(1484,1552,4))==set(range(1508,1552,4)))
    final_state=(sha(ro[1484:1504])==c['dispatch_table_sha256']and sha(ro[1504:1528])==c['first_table_sha256']and sha(ro[1528:1552])==c['retained_island_sha256']and positions==dict(zip(c['floats'],range(1528,1552,4)))and sites.intersection(range(1484,1552,4))==set(range(1484,1528,4)))
    assert raw_state!=final_state
    return 'raw'if raw_state else'laid-out'

def restore_three_owners(raw,c):
    before_state=state_three_owners(raw,c)
    if before_state=='laid-out':
        inverse,_=transform(raw,c['inverse_spans'])
        restored,audit=restore_three_owners(inverse,c)
        assert restored==raw
        return raw,dict(state='already-laid-out',rewritten=False,audit=audit)
    out,audit=transform(raw,c['spans']);assert state_three_owners(out,c)=='laid-out'
    canonical=lambda x:json.dumps(x,sort_keys=True,separators=(',',':')).encode()
    assert sha(canonical(audit['affected_references']))==c['affected_references_sha256']and len(audit['affected_references'])==8
    operands=[dict(section=q['section'],site=q['site'],kind=q['kind'],before_sha256=sha(struct.pack('>I',q['old'])),after_sha256=sha(struct.pack('>I',q['new'])))for q in audit['operand_changes']]
    operands=sorted(operands,key=lambda q:(q['section'],q['site'],q['kind']))
    assert operands==c['operand_change_word_hashes']and len(operands)==2
    assert len(audit['symbol_changes'])==6 and len(audit['relocation_site_changes'])==11
    inverse,_=transform(out,c['inverse_spans']);assert inverse==raw
    e=parsed(out);ro=e['sections']['.rodata']['data'];records=[q for q in e['relocations']if q['section']=='.rodata']
    # These bases reproduce the existing original ASM witness's analysis labels.
    # They are not packed module runtime addresses and carry no native credit.
    replay=bytearray(ro);bases={'.text':0x400000,'.rodata':0x4041D0,'.data':0x404800,'.bss':0x4049E0,'ABS':0}
    for q in records:
        assert q['kind']==2 and q['explicit_addend']is None and q['symbol_section']in bases
        value=bases[q['symbol_section']]+q['symbol_value']+struct.unpack_from('>I',ro,q['offset'])[0]
        struct.pack_into('>I',replay,q['offset'],value)
    assert sha(replay)==c['original_readonly_witness_sha256']
    expected=[tuple(row)for row in c['original_witness_table_target_pairs']];assert len(expected)==19
    assert sorted((q['offset'],struct.unpack_from('>I',replay,q['offset'])[0])for q in records if q['offset']in dict(expected))==expected
    assert[q for q in records if q['offset']not in dict(expected)]==c['original_non_table_RO_records']and len(c['original_non_table_RO_records'])==10
    return out,dict(state='raw',rewritten=True,audit=audit)


def state(raw,c):
    return state_three_owners(raw,c)if c.get('schema')==2 else _state_two_owner_legacy(raw,c)

def restore(raw,c):
    return restore_three_owners(raw,c)if c.get('schema')==2 else _restore_two_owner_legacy(raw,c)

def main():
    p=argparse.ArgumentParser();p.add_argument('--root',required=True);p.add_argument('--layout',required=True);p.add_argument('--object',required=True);a=p.parse_args()
    root=Path(a.root).resolve();layout_path=(root/a.layout).resolve()
    assert layout_path.is_relative_to(root) and layout_path!=root and not Path(root/a.layout).is_symlink()
    spec=importlib.util.spec_from_file_location('readonly_for_RACE_order',root/'tools/moduleReadonlyLayout.py')
    tool=importlib.util.module_from_spec(spec);spec.loader.exec_module(tool)
    layout,decoded,_,_=tool.load(root,a.layout,'race')
    order=layout['object_ordering'];c=order['contract']
    assert order['helper']=='tools/reorderRaceReadonly.py' and sha(Path(__file__).read_bytes())==order['helper_sha256']
    target=(root/a.object).resolve()
    assert a.object==c['source_object']=='build/src/modules/race.o' and target.is_relative_to(root) and target!=root
    assert not (root/a.object).is_symlink() and target.is_file() and 0<target.stat().st_size<=128*1024**2
    before=target.read_bytes();out,audit=restore(before,c)
    assert target.read_bytes()==before
    if out!=before:
        temporary=target.with_name(target.name+'.readonly-order.tmp')
        assert not temporary.exists() and not temporary.is_symlink()
        try:
            with temporary.open('xb') as stream:stream.write(out)
            assert temporary.read_bytes()==out
            os.replace(temporary,target)
        finally:
            if temporary.exists():temporary.unlink()
    assert target.read_bytes()==out
    print(json.dumps(dict(status='PASS_RACE_READONLY_ORDER',state=audit['state'],rewritten=audit['rewritten'],object_sha256=sha(out))))

if __name__=='__main__':main()
