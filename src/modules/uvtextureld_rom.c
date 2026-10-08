// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef struct UnkTexture_Exports_s {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ void* (*unk20)(void);
    /* 0x24 */ void* (*unk24)(void);    
    /* 0x28 */ char pad28[4];
} UnkTexture_Exports;                               /* size = 0x2C */

void __entrypoint_func_uvtextureld_rom_400000(UvTextureLd_Exports *exports);
void uvTextureLoaderCleanup(void);
ParsedUVTX* uvParseUVTX(u8 *data);
ParsedUVTX *uvTextureLoadImageBytes(u8 *arg0);
void *_uvExpandTexture(u8 *inputCursor);
void uvTextureFreeResource(UnkStruct_uvtextureld_rom_00400A40 *parsedUvTexture);

// .data
s32 D_uvtextureld_rom_00400B50[] = {0x000C0000, __entrypoint_func_uvtextureld_rom_400000, 0, 0};

// .bss
static UvGfxMgr_Exports* sUvGfxMgrExports; // unused export
static UnkTexture_Exports* sUvTextureExports;
static UvTSeq_Exports* sUvTextureSequenceExports;
static UvtSeqLd_Rom_Exports* sUvTextureSequenceLdExports;
u16 D_uvtextureld_rom_00400B70;
u16 D_uvtextureld_rom_00400B72;

#line 30 "src/modules/uvtextureld_rom.c"

void __entrypoint_func_uvtextureld_rom_400000(UvTextureLd_Exports* exports) {
    u16* imageCountLimitProperty;

    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVTX = uvParseUVTX;
    exports->uvTextureLoaderCleanup = uvTextureLoaderCleanup;
    exports->uvTextureFreeResource = uvTextureFreeResource;
    imageCountLimitProperty = uvGetSystemProp(0x12);
    if (imageCountLimitProperty == NULL) {
        D_uvtextureld_rom_00400B72 = 0x2710;
    } else {
        D_uvtextureld_rom_00400B72 = *imageCountLimitProperty;
    }
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvTextureExports = uvLoadModule('TEXT');
    sUvTextureSequenceExports = uvLoadModule('TSEQ');
    sUvTextureSequenceLdExports = uvLoadModule('UVTS');
    D_uvtextureld_rom_00400B70 = 0;
}
#line 49 "src/modules/uvtextureld_rom.c"

#line 50 "src/modules/uvtextureld_rom.c"
/* Unload graphics, texture, sequence and sequence-loader dependencies
 * in original order. Individual texture resources use their own destructor. */
void uvTextureLoaderCleanup(void) {
    uvUnloadModule('GMGR');
    uvUnloadModule('TEXT');
    uvUnloadModule('TSEQ');
    uvUnloadModule('UVTS');
}
#line 56 "src/modules/uvtextureld_rom.c"

ParsedUVTX* uvParseUVTX(u8* data) {
    s32 fileId;
    ParsedUVTX* parsedUvTexture;
    u32 size;
    void* blockData;
    s32 ptr;
    u32 tag;

    parsedUvTexture = NULL;
    fileId = uvFileReadHeader(data);
    tag = uvFileReadBlock(fileId, &size, &blockData, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                ptr = blockData;
                parsedUvTexture = _uvExpandTexture(ptr);
                _uvMemFree(ptr);
                break;
            default:
                break;
        }
        tag = uvFileReadBlock(fileId, &size, &blockData, 1);
    }
    uvFileFree(fileId);
    return parsedUvTexture;
}

#line 84 "src/modules/uvtextureld_rom.c"
/* Clamp image bytes to 4096 and copy into a private eight-byte-aligned buffer below the allocation-count limit.
 * At the limit, call TEXT's lazy 4096-byte scratch allocator; that path copies no asset pixels.
 * Its reset callback fills existing scratch with 0xFF when invoked through uvGfxBegin's list-one dispatch.
 * Texture destruction recognizes the current scratch pointer and skips its free/count decrement.
 * TEXT's module cleanup contains no scratch free.
 * RE_UNKNOWN: initial contents before a subsequent reset, other writers and intended reuse/teardown lifetime;
 * trace original fallback loads, shared-pointer aliases and module reload paths before stronger claims. */
ParsedUVTX* uvTextureLoadImageBytes(u8* data) {
    void* image;
    u16 displayListCount;
    u16 imageBytes;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;

    uvConsumeBytes(&imageBytes, &data, 2U);
    if (imageBytes >= 0x1001) {
        imageBytes = 0x1000;
    }
    uvConsumeBytes(&displayListCount, &data, 2U);
    uvConsumeBytes(&sp34, &data, 4U);
    uvConsumeBytes(&sp30, &data, 4U);
    uvConsumeBytes(&sp34, &data, 4U);
    uvConsumeBytes(&sp30, &data, 4U);
    uvConsumeBytes(&sp2C, &data, 4U);
    uvConsumeBytes(&sp28, &data, 4U);
    if (D_uvtextureld_rom_00400B70 < D_uvtextureld_rom_00400B72) {
        D_uvtextureld_rom_00400B70++;
        image = _uvMemAlloc((u32) imageBytes, 8U);
        _uvMediaCopy(image, data, (u32) imageBytes);
    } else {
        image = sUvTextureExports->unk20();
    }
    return image;
}
#line 113 "src/modules/uvtextureld_rom.c"

#line 114 "src/modules/uvtextureld_rom.c"

void* _uvExpandTexture(u8* inputCursor) {
    u32 imageAddress;
    Gfx* displayList;
    s32 fileCount;
    s32 frameCount;
    s32 pad;
    s32 var_a3;
    s32 setImageCommandIndex;
    u16 pad_sp162;
    u16 displayListCount;
    u16 imageByteCount;
    u16 pad_sp15C;
    UnkUVTX_1C* firstAnimation;
    UnkUVTX_1C* secondAnimation;
    f32 sp150;
    f32 sp14C;
    s32 i;
    u8* originalInput = inputCursor;
    f32 sp140;
    f32 sp13C;
    s32 sp138;
    u16 sp136;
    u8 sp135;
    s32 j;
    s32 k;
    s32 pad2;
    ParsedUVTX* texture;
    s32 pad3[4];
    u16 sp54[6][16];
    s32 sequenceFound;
    ParsedUVTX* referencedTexture;

    uvConsumeBytes(&imageByteCount, &inputCursor, 2);
    if (imageByteCount > 0x1000) {
        imageByteCount = 0x1000;
    }
    uvConsumeBytes(&displayListCount, &inputCursor, 2);
    uvConsumeBytes(&sp150, &inputCursor, 4);
    uvConsumeBytes(&sp14C, &inputCursor, 4);
    if ((sp150 != 0.0f) || (sp14C != 0.0f)) {
        firstAnimation = _uvMemAllocAlign8(0x1C);
        firstAnimation->unk0 = 1.0f;
        firstAnimation->unk4 = 1.0f;
        firstAnimation->unk8 = sp150;
        firstAnimation->unkC = sp14C;
        firstAnimation->unk18 = 0;
        firstAnimation->unk19 = 0;
        firstAnimation->unk1A = 1;
        firstAnimation->unk10 = 0.0f;
        firstAnimation->unk14 = 0.0f;
    } else {
        firstAnimation = NULL;
    }
    uvConsumeBytes(&sp150, &inputCursor, 4);
    uvConsumeBytes(&sp14C, &inputCursor, 4);
    uvConsumeBytes(&sp140, &inputCursor, 4);
    uvConsumeBytes(&sp13C, &inputCursor, 4);
    if ((sp150 != 0.0f) || (sp14C != 0.0f) || (sp140 != 0.0f) || (sp13C != 0.0f)) {
        secondAnimation = _uvMemAllocAlign8(0x1C);
        secondAnimation->unk0 = 1.0f;
        secondAnimation->unk4 = 1.0f;
        secondAnimation->unk8 = sp150;
        secondAnimation->unkC = sp14C;
        secondAnimation->unk10 = sp140;
        secondAnimation->unk14 = sp13C;
        secondAnimation->unk18 = 0;
        secondAnimation->unk19 = 0;
        secondAnimation->unk1A = 1;
    } else {
        secondAnimation = NULL;
    }
    inputCursor += imageByteCount;
    displayList = _uvMemAlloc(displayListCount * 8, 8);
    uvConsumeBytes(displayList, &inputCursor, displayListCount * 8);
    texture = _uvMemAllocAlign8(0x28);
    uvConsumeBytes(&texture->width, &inputCursor, 2);
    uvConsumeBytes(&texture->height, &inputCursor, 2);
    uvConsumeBytes(&texture->unk24, &inputCursor, 1);
    uvConsumeBytes(&texture->unk25, &inputCursor, 1);
    uvConsumeBytes(&texture->unk26, &inputCursor, 1);
    uvConsumeBytes(&texture->unk14, &inputCursor, 4);
    uvConsumeBytes(&texture->pad18, &inputCursor, 2);
    uvConsumeBytes(&sp136, &inputCursor, 2);
    texture->unk27 =  sp136;
    uvConsumeBytes(&texture->unk21, &inputCursor, 1);
    uvConsumeBytes(&sp135, &inputCursor, 1);
    uvConsumeBytes(&sp135, &inputCursor, 1);
    uvConsumeBytes(&sp135, &inputCursor, 1);
    uvConsumeBytes(&sp135, &inputCursor, 1);
    uvConsumeBytes(&sp138, &inputCursor, 4);
    uvConsumeBytes(&texture->unk23, &inputCursor, 1);
    uvConsumeBytes(&texture->unk22, &inputCursor, 1);
    texture->unk20 = 0xFF;
    if (texture->unk14 & 0x80000) {
        sequenceFound = FALSE;
        texture->unk20 = sUvTextureSequenceExports->uvTexSeqFindFree();
        if (texture->unk20 != 0xFF) {
            fileCount = uvGetFilesCount('UVTS');
            for (i = 0; i < fileCount; i++) {
                if (sUvTextureSequenceLdExports->uvGetFirstFrameTexture(i) == (texture->unk14 & 0xFFF)) {
                    sequenceFound = TRUE;
                    uvLoadFile('UVTS', i);
                    sUvTextureSequenceExports->uvTexSeqModel((s32) texture->unk20, i);
                    frameCount = sUvTextureSequenceExports->uvTexSeqGetFrameCount((s32) texture->unk20);
                    for (j = 1; j < frameCount; j++) {
                        uvLoadFile('UVTX', sUvTextureSequenceExports->uvTexSeqGetFrameTexture(texture->unk20, j));
                    }
                    break;
                }
            }
        }
        if (!sequenceFound) {
            texture->unk14 &= ~0x80000;
            if (texture->unk20 != 0xFF) {
                sUvTextureSequenceExports->uvTexSeqFree(texture->unk20);
            }
            texture->unk20 = 0xFF;
        }
    }
    if (texture->unk21 == 0) {
        for (i = 0; i < texture->unk22; i++)  {
            uvConsumeBytes(&sp54[i], &inputCursor, 0x20);
        }
    }
    texture->unk1A = imageByteCount;
    imageAddress = uvTextureLoadImageBytes(originalInput);
    texture->unk0 = displayList;
    texture->data.pointer = imageAddress;
    texture->unk4 = (void*)firstAnimation; // TODO
    texture->size.as_s32 = secondAnimation;
    setImageCommandIndex = 0;
    for (i = 0; i < displayListCount; i++) {
        Gfx* gfxCmd = &displayList[i];
        u32* imageAddressWord;
        u8 cmd = gfxCmd->setimg.cmd;
        if (cmd != 0xFD) {
            continue;
        }
        if (setImageCommandIndex == 0) {
            gfxCmd->setimg.dram |= (u32)OS_PHYSICAL_TO_K0(imageAddress);
        } else {
            if (texture->pad18 == (texture->unk14 & 0xFFF)) {
                referencedTexture = texture;
            } else {
                referencedTexture = uvLoadFile('UVTX', texture->pad18);
            }
            imageAddressWord = (u32*)&gfxCmd->setimg.dram;
            if (referencedTexture == NULL) {
            }  else {
                *imageAddressWord |= (u32)OS_PHYSICAL_TO_K0(referencedTexture->data.pointer);
            }
        }
        setImageCommandIndex++;
    }
    if (texture->unk21 == 0) {
        texture->unk10 = _uvMemAlloc(texture->unk22 * 0x80, 0x10);
        for (j = 0; j < texture->unk22; j++) {
            for (i = 0; i < 0x10; i++) {
                texture->unk10[(j * 0x40) + 0x0 + i] =
                    texture->unk10[(j * 0x40) + 0x10 + i] =
                        texture->unk10[(j * 0x40) + 0x20 + i] =
                            texture->unk10[(j * 0x40) + 0x30 + i] = sp54[j][i];
            }
        }
    } else {
        texture->unk10 = NULL;
    }
    return texture;
}
#line 283 "src/modules/uvtextureld_rom.c"

#line 284 "src/modules/uvtextureld_rom.c"
/* Release the secondary texture and sequence handle, optional animation
 * records, display list and privately allocated image bytes, then the resource.
 * Shared texture scratch is not freed or charged against the allocation count. */
void uvTextureFreeResource(UnkStruct_uvtextureld_rom_00400A40* texture) {
    s32 pad;
    s32* image;

    image = texture->unkC;
    if ((texture->unk18 != 0xFFF) && (texture->unk18 != (texture->unk14 & 0xFFF))) {
        uvUnloadFile('UVTX', texture->unk18);
    }
    if (texture->unk20 != 0xFF) {
        sUvTextureSequenceExports->uvTexSeqFree(texture->unk20);
    }
    if (texture->unk4 != NULL) {
        _uvMemFree(texture->unk4);
    }
    if (texture->unk8 != NULL) {
        _uvMemFree(texture->unk8);
    }
    if (texture->unk0 != NULL) {
        _uvMemFree(texture->unk0);
    }
    if ((image != NULL) && (sUvTextureExports->unk24() != image)) {
        _uvMemFree(image);
        D_uvtextureld_rom_00400B70 -= 1;
    }
    _uvMemFree(texture);
}
#line 310 "src/modules/uvtextureld_rom.c"


