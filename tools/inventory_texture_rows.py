"""Read-only original US UVTX COMM row-count audit; no extraction/build/write.

Unknown compression is reported, never guessed from the historical decoder name.
MIO0 is grounded in original decoder instructions; other codecs need actual header identification.
"""
from pathlib import Path
from collections import Counter
import argparse,hashlib,json,struct,zlib
import yaml

ROOT=Path.cwd()
ROM_SHA1='e5ab4d226c08d22f68a2edcc48870203e67454b8'
MAX_COMM=1024*1024

def u16(raw,offset):
    assert offset+2<=len(raw)
    return struct.unpack_from('>H',raw,offset)[0]

def u32(raw,offset):
    assert offset+4<=len(raw)
    return struct.unpack_from('>I',raw,offset)[0]

def comm_metadata(raw):
    assert len(raw)>=28,'Truncated COMM prefix'
    encoded_image_bytes=u16(raw,0);image_bytes=min(encoded_image_bytes,4096);dl_count=u16(raw,2)
    metadata=28+image_bytes+dl_count*8
    assert metadata+26<=len(raw),'Truncated post-display-list metadata'
    row_mode=raw[metadata+15];row_count=raw[metadata+25]
    required=metadata+26+(row_count*32 if row_mode==0 else 0)
    return {'encoded_image_bytes':encoded_image_bytes,'consumed_image_bytes':image_bytes,
        'display_list_count':dl_count,'metadata_offset':metadata,'width':u16(raw,metadata),
        'height':u16(raw,metadata+2),'row_mode_byte':row_mode,'row_count_byte':row_count,
        'local_rows_used':row_mode==0,'six_row_storage_sufficient':row_mode!=0 or row_count<=6,
        'required_payload_end':required,'payload_bytes':len(raw),'payload_extent_sufficient':required<=len(raw),
        'comm_sha256':hashlib.sha256(raw).hexdigest()}


# Original ROM0x6190..0x6230, symbol80005590; receipt original-asset-decoder-1206.json.
DECODER_SHA256='037bb1ccb42acf9e075cbdbff9925a1ddc90953a310d0b56d30387f9cb3adc6d'
DECODER_RECEIPT_SHA256='e8b9d55b948d641d174eadd9733ae9f9297a2933adf6af8640b7571d13c68bdd'

def mio0_decode(raw,expected):
    """Bounded inventory decoder; reject inputs outside original decoder preconditions.

    Original5590 loads link/literal/output fields at8/C/4. Original55B8 loads
    32-bit control words and55C4 tests their sign (MSB first).55D0 copies a literal.
    Original55EC/55F0/55F8 form length=(word>>12)+3, distance=(word&0xFFF)+1.
    Original55FC copies one byte at a time, allowing overlapping back-references.
    Original5618 requires exact output end; zero/overrun are rejected here.
    """
    assert raw[:4]==b'MIO0' and len(raw)>=16,'Bad MIO0 header'
    assert 0<expected<=MAX_COMM and u32(raw,4)==expected,'MIO0 output size disagreement'
    link_start=u32(raw,8);literal_start=u32(raw,12)
    assert 16<=link_start<=literal_start<=len(raw),'Invalid MIO0 stream offsets'
    control_cursor=16;link_cursor=link_start;literal_cursor=literal_start
    flags=0;bits=0;output=bytearray()
    while len(output)<expected:
        if not bits:
            assert control_cursor+4<=link_start,'Truncated MIO0 control stream'
            flags=u32(raw,control_cursor);control_cursor+=4;bits=32
        if flags&0x80000000:
            assert literal_cursor<len(raw),'Truncated MIO0 literal stream'
            output.append(raw[literal_cursor]);literal_cursor+=1
        else:
            assert link_cursor+2<=literal_start,'Truncated MIO0 link stream'
            match=u16(raw,link_cursor);link_cursor+=2
            length=(match>>12)+3;distance=(match&0xFFF)+1
            assert distance<=len(output),'MIO0 back-reference before output start'
            assert len(output)+length<=expected,'MIO0 back-reference exceeds output end'
            for _ in range(length):output.append(output[-distance])
        flags=(flags<<1)&0xFFFFFFFF;bits-=1
    return bytes(output)

def mio0_selftest():
    def encoded(expected,controls,links=b'',literals=b''):
        bits=b''.join(struct.pack('>I',word) for word in controls)
        start=16+len(bits)
        return b'MIO0'+struct.pack('>III',expected,start,start+len(links))+bits+links+literals
    assert mio0_decode(encoded(3,[0xE0000000],literals=b'ABC'),3)==b'ABC'
    assert mio0_decode(encoded(6,[0xE0000000],b'\x00\x02',b'ABC'),6)==b'ABCABC'
    assert mio0_decode(encoded(6,[0x80000000],b'\x20\x00',b'A'),6)==b'AAAAAA'
    assert mio0_decode(encoded(19,[0x80000000],b'\xf0\x00',b'Z'),19)==b'Z'*19
    expected=bytes(range(33))
    assert mio0_decode(encoded(33,[0xFFFFFFFF,0x80000000],literals=expected),33)==expected
    malformed=[
        (b'MIO0'+struct.pack('>III',1,16,16),1), # no control word
        (encoded(3,[0],b'\x00'),3), # truncated two-byte link
        (encoded(1,[0x80000000]),1), # missing literal
        (encoded(3,[0],b'\x00\x00'),3), # invalid initial distance
        (encoded(2,[0x80000000],b'\x00\x00',b'A'),2), # output overrun
        (encoded(0,[0x80000000],literals=b'A'),0), # zero violates original exact-end loop
        (encoded(1,[0x80000000],literals=b'A'),2), # wrapper/header size mismatch
        (b'MIO0'+struct.pack('>III',1,999,999),1), # offset outside input
        (b'XXXX'+struct.pack('>III',1,20,20)+b'\x80\x00\x00\x00A',1),
    ]
    for raw,size in malformed:
        try:mio0_decode(raw,size)
        except AssertionError:pass
        else:raise AssertionError('Malformed MIO0 accepted')
    wrapped=b'COMM'+struct.pack('>I',6)+encoded(6,[0x80000000],b'\x20\x00',b'A')
    tag,raw,codec=decode_block(b'GZIP',wrapped)
    assert tag==b'COMM' and raw==b'AAAAAA' and codec['codec']=='original-instruction-verified-MIO0'

def decode_block(tag,raw):
    if tag!=b'GZIP':return tag,raw,'uncompressed'
    assert len(raw)>=8,'Truncated GZIP wrapper'
    inner=raw[:4];expected=u32(raw,4);compressed=raw[8:]
    assert expected<=MAX_COMM,'Advertised block exceeds reviewed one-MiB bound'
    if compressed.startswith(b'MIO0'):
        return inner,mio0_decode(compressed,expected),{'codec':'original-instruction-verified-MIO0',
            'advertised_bytes':expected,'original_decoder_sha256':DECODER_SHA256}
    if compressed.startswith(b'\x1f\x8b'):
        window=31;codec='header-identified-standard-gzip'
    elif len(compressed)>=2 and compressed[0]&15==8 and compressed[0]>>4<=7 and ((compressed[0]<<8)|compressed[1])%31==0:
        window=15;codec='header-identified-standard-zlib'
    else:
        return inner,None,{'opaque_compression':True,'advertised_bytes':expected,
                           'encoded_prefix_sha256':hashlib.sha256(compressed[:16]).hexdigest()}
    decoder=zlib.decompressobj(window);decoded=decoder.decompress(compressed,expected+1)
    assert len(decoded)==expected and decoder.eof and not decoder.unconsumed_tail,'Compressed length/stream disagreement'
    # IFF block padding can follow one compressed stream; retain it as evidence.
    return inner,decoded,{'codec':codec,'advertised_bytes':expected,'trailing_encoded_bytes':len(decoder.unused_data)}

def selftest():
    for count,mode in [(0,0),(6,0),(7,0),(255,1)]:
        raw=bytearray(54+(count*32 if mode==0 else 0));raw[28+15]=mode;raw[28+25]=count
        value=comm_metadata(raw)
        assert value['six_row_storage_sufficient']==(mode!=0 or count<=6)
        assert value['payload_extent_sufficient']
    raw=bytearray(54+192);raw[53]=6
    assert not comm_metadata(raw[:-1])['payload_extent_sufficient']
    wrapped=b'COMM'+struct.pack('>I',len(raw))+zlib.compress(raw)
    tag,value,codec=decode_block(b'GZIP',wrapped)
    assert tag==b'COMM' and value==raw and codec['codec'].endswith('zlib')
    tag,value,codec=decode_block(b'GZIP',b'COMM'+struct.pack('>I',32)+b'NOT-A-CODEC')
    assert tag==b'COMM' and value is None and codec['opaque_compression']

def main():
    global ROOT
    parser=argparse.ArgumentParser(description='Read-only original US texture-row contract inventory; requires private original ROM and validated packed loader.')
    parser.add_argument('--root',type=Path,default=Path.cwd(),help='Decomp repository root')
    parser.add_argument('--self-test',action='store_true',help='Run synthetic parser tests without private assets')
    args=parser.parse_args();selftest();mio0_selftest()
    if args.self_test:
        print(json.dumps({'status':'PASS','scope':'Synthetic metadata/codec tests; no original asset claim'}));return
    ROOT=args.root.resolve()
    rom=(ROOT/'baserom.us.z64').read_bytes();assert hashlib.sha1(rom).hexdigest()==ROM_SHA1
    assert hashlib.sha256(rom[0x6190:0x6230]).hexdigest()==DECODER_SHA256,'Original decoder byte guard failed'
    # The current loader whose source supplies offsets must still represent the original packed module.
    original=ROOT/'bin/us/uvtextureld_rom.uvmo';packed=ROOT/'build/partial_uvtextureld_rom.o.generated.uvmo'
    assert packed.read_bytes()==original.read_bytes(),'Loader packed-original proof failed'
    config=ROOT/'config/us/beetleadventurerac.us.yaml'
    segments=yaml.safe_load(config.read_text())['segments'];manifest=ROOT/'config/us/form0.json'
    form=json.loads(manifest.read_bytes());category=next(x for x in form['FormFiles'] if x['category']=='UVTX')
    wanted={x['name'] for x in category['files'] if not x['nullEntry']}
    spans={}
    for index,segment in enumerate(segments[:-1]):
        if not isinstance(segment,dict) or segment.get('name') not in wanted:continue
        following=segments[index+1];end=following['start'] if isinstance(following,dict) else following[0]
        assert segment['name'] not in spans
        spans[segment['name']]=(segment['start'],end)
    assert set(spans)==wanted and category['count']==len(category['files'])
    rows=[];opaque=[];errors=[]
    for name,(start,end) in spans.items():
        try:
            raw=rom[start:end];assert raw[:4]==b'FORM' and raw[8:12]==b'UVTX',(name,'Unexpected FORM type')
            limit=u32(raw,4)+8;assert 12<=limit<=len(raw)
            cursor=12;found=0
            while cursor<limit:
                assert cursor+8<=limit,'Truncated block header'
                tag=raw[cursor:cursor+4];size=u32(raw,cursor+4);begin=cursor+8
                assert begin+size<=limit,'Block extends outside FORM'
                if tag!=b'PAD ':
                    inner,decoded,codec=decode_block(tag,raw[begin:begin+size])
                    if inner==b'COMM':
                        found+=1;record={'asset':name,'rom_offset':start,'block_offset':cursor,
                            'asset_sha256':hashlib.sha256(raw[:limit]).hexdigest(),'compression':codec}
                        if decoded is None:opaque.append(record)
                        else:rows.append({**record,**comm_metadata(decoded)})
                cursor=begin+size
            assert cursor==limit and found==1,(name,'COMM count differs from one')
        except Exception as exc:errors.append({'asset':name,'error':str(exc)})
    histogram=Counter(str(x['row_count_byte']) for x in rows if x['local_rows_used'])
    violations=[x for x in rows if not x['six_row_storage_sufficient'] or not x['payload_extent_sufficient']]
    sources={}
    for relative in ['src/modules/uvtextureld_rom.c','src/file_manager.c','src/filesystem.c']:
        raw=(ROOT/relative).read_bytes();sources[relative]={'sha256':hashlib.sha256(raw).hexdigest()}
    report={'read_only':True,'accepted':False,'rom_sha1':ROM_SHA1,'loader_packed_original_equal':True,
        'original_decoder_sha256':DECODER_SHA256,'decoder_receipt_sha256':DECODER_RECEIPT_SHA256,
        'manifest_sha256':hashlib.sha256(manifest.read_bytes()).hexdigest(),'config_sha256':hashlib.sha256(config.read_bytes()).hexdigest(),
        'expected_assets':len(wanted),'decoded_assets':len(rows),'opaque_assets':opaque,'errors':errors,
        'complete_inventory':not opaque and not errors and len(rows)==len(wanted),
        'local_row_count_histogram':dict(sorted(histogram.items(),key=lambda item:int(item[0]))),
        'violations':violations,'assets':rows,'source_evidence':sources,
        'proof_boundary':'Observed original-ROM COMM counts only. No guarantee for modified assets or unreviewed input paths; no new bounds check or invented format meaning. Unknown compression remains opaque.'}
    print(json.dumps(report))
    if not report['complete_inventory'] or violations:raise SystemExit(1)

if __name__=='__main__':main()
