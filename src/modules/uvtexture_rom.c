// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

typedef struct UnkStruct_uvtexture_rom_00400244_1_s {
    u8 pad0[0x8];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x2];
    u8 unk1A;
} UnkStruct_uvtexture_rom_00400244_1;

typedef struct UnkStruct_uvtexture_rom_00400244_s {
    Gfx *unk0;
    UnkStruct_uvtexture_rom_00400244_1 *unk4;
    UnkStruct_uvtexture_rom_00400244_1 *unk8;
    u8 padC[0x4];
    u16 *unk10;
    s32 unk14;
    u16 unk18;
    u8 pad1A[0x2];
    u16 unk1C;
    u16 unk1E;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 colorAlpha;
} UnkStruct_uvtexture_rom_00400244;

void __entrypoint_func_uvtexture_rom_400000(UvTexture_Exports *exports);
void uvTextureModuleCleanup(void);
u8 uvTextureGetLoadedFlag27(s32 arg0);
void *uvTextureGetLoadedSubrecord(s32 arg0, f32 *arg1, f32 *arg2);
void uvTextureEmitDisplayListAndAnimatedTileSizes(s32 arg0);
s32 uvTextureApplyPackedState(s32 arg0);
void uvGfxTextureDL(Gfx **gdl, s32 textureId, s32 xparam);
void uvTextureBeginBuffer(s32 arg0);
void uvTextureInvalidateBinding(void);
s32 uvTextureGetOtherBufferValue(s32 arg0);
void uvTextureGetProps(s32 arg0, ...);
void *uvTextureGetOrAllocateScratch(void);
void *uvTextureGetScratch(void);


// .data
Gfx D_uvtexture_rom_00400CC0[] = {
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPEndDisplayList(),
};
u8 sPrevAlphaColor = 0xFF;
s32 D_uvtexture_rom_00400CEC = FALSE;
s32 D_uvtexture_rom_00400CF0[] = {0x002C0000, __entrypoint_func_uvtexture_rom_400000, 0, 0};


// .bss
s32 D_uvtexture_rom_00400D00;
s32 D_uvtexture_rom_00400D04;
s32 D_uvtexture_rom_00400D08;
s32 D_uvtexture_rom_00400D0C; // unreferenced padding
s32 D_uvtexture_rom_00400D10[1];
s32 D_uvtexture_rom_00400D14[1];
static UvGfxMgr_Exports *sUvGfxMgrExports;
static UvTSeq_Exports *sUvTextureSequenceExport;
static UvCback_Exports *sUvCbackExports;
s32 D_uvtexture_rom_00400D24;
void *D_uvtexture_rom_00400D28;
s32 sTextureFormFileId;

/*
 * Install ten texture function exports and the shared-word address export.
 * Load GMGR, CBCK and TSEQ, obtain the UVTX form ID, then register
 * uvTextureBeginBuffer on graphics callback list 1 with both user words zero.
 * RE_ORIGINAL_QUIRK: Preserve export/import/callback order and the existing
 * conditional line directive; this body does not reset the texture buffers.
 * RE_UNKNOWN: Import/form lookup failure, duplicate registration, buffer
 * ownership and callback lifetime require the texture and manager providers.
 */
#line 75 "src/modules/uvtexture_rom.c"
void __entrypoint_func_uvtexture_rom_400000(UvTexture_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvTextureModuleCleanup = uvTextureModuleCleanup;
    exports->uvTextureGetLoadedFlag27 = uvTextureGetLoadedFlag27;
    exports->uvTextureGetLoadedSubrecord = uvTextureGetLoadedSubrecord;
    exports->uvTextureEmitDisplayListAndAnimatedTileSizes = uvTextureEmitDisplayListAndAnimatedTileSizes;
    exports->uvTextureApplyPackedState = uvTextureApplyPackedState;
    exports->uvTextureInvalidateBinding = uvTextureInvalidateBinding;
    exports->uvTextureGetOtherBufferValue = uvTextureGetOtherBufferValue;
    exports->uvTextureGetProps = uvTextureGetProps;
    exports->uvTextureGetOrAllocateScratch = uvTextureGetOrAllocateScratch;
    exports->uvTextureGetScratch = uvTextureGetScratch;
    exports->D_uvtexture_rom_00400D00 = &D_uvtexture_rom_00400D00;
#ifdef __sgi
#line 77
#endif
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvTextureSequenceExport = uvLoadModule('TSEQ');
    sTextureFormFileId = uvGetFormFileIdByTagDup('UVTX');
    sUvCbackExports->uvAddCallback(
        sUvGfxMgrExports->uvGfxGetCallbackList(1), uvTextureBeginBuffer, 0, 0);
}

#line 86 "src/modules/uvtexture_rom.c"
/* Unload the original graphics-manager and callback dependencies. */
void uvTextureModuleCleanup(void) {
    uvUnloadModule('GMGR');
    uvUnloadModule('CBCK');
}
#line 90 "src/modules/uvtexture_rom.c"

#line 91 "src/modules/uvtexture_rom.c"
/* Return loaded texture byte0x27, or zero for sentinel 0xFFF/missing data.
 * RE_UNKNOWN: other texture-ID/file-table bounds need original asset tables and callers. */
u8 uvTextureGetLoadedFlag27(s32 textureId) {
    ParsedUVTX *parsedUvTexture;

    if (textureId == 0xFFF) {
        return 0U;
    }
    parsedUvTexture = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    if (parsedUvTexture != NULL) {
        return parsedUvTexture->unk27;
    }
    return 0U;
}
#line 103 "src/modules/uvtexture_rom.c"

#line 104 "src/modules/uvtexture_rom.c"
/* Return a loaded texture subrecord and copy its two floating values
 * to caller outputs. Return NULL for sentinel 0xFFF or missing records;
 * output pointers are not touched on those paths. */
void *uvTextureGetLoadedSubrecord(s32 textureId, f32 *value8, f32 *valueC) {
    UnkStruct_uvtexture_rom_00400244 *texture;
    UnkStruct_uvtexture_rom_00400244_1 *record;

    if (textureId == 0xFFF) {
        return NULL;
    }
    texture = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    if (texture == NULL) {
        return NULL;
    }
    record = texture->unk4;
    if (record == NULL) {
        return NULL;
    }
    *value8 = record->unk8;
    *valueC = texture->unk4->unkC;
    return texture->unk4;
}
#line 123 "src/modules/uvtexture_rom.c"

#line 124 "src/modules/uvtexture_rom.c"
/* Emit the loaded texture display list, then update enabled animated
 * tile coordinates for its levels and optional secondary texture.
 * Preserve the original fixed-point conversion and dimension handling. */
void uvTextureEmitDisplayListAndAnimatedTileSizes(s32 textureId) {
    Gfx **displayListHead;
    s32 tileWidth;
    s32 tileHeight;
    UnkStruct_uvtexture_rom_00400244 *secondaryTexture;
    UnkStruct_uvtexture_rom_00400244 *texture;
    UnkStruct_uvtexture_rom_00400244_1 *animation;
    s32 i;
    s32 uls;
    s32 ult;
    s32 lrs;
    s32 lrt;

    displayListHead = sUvGfxMgrExports->uvGetDisplayListHead();
    texture = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    if (texture == NULL) {
        return;
    }

    D_uvtexture_rom_00400D10[D_uvtexture_rom_00400D08]++;
    gSPDisplayList(displayListHead[0]++, OS_PHYSICAL_TO_K0(texture->unk0));
    if (texture->unk4 != NULL) {
        animation = texture->unk4;
        if (animation->unk1A != 0) {
            tileWidth = texture->unk1C;
            tileHeight = texture->unk1E;
            for (i = 1; i <= texture->unk22; i++) {
                uls = (s32) (animation->unk10 * tileWidth * 4.0f);
                ult = (s32) (animation->unk14 * tileHeight * 4.0f);
                lrs = ((texture->unk1C * 4) + uls) - 1;
                lrt = ((texture->unk1E * 4) + ult) - 1;
                gDPSetTileSize(displayListHead[0]++, i, uls, ult, lrs, lrt);
                tileWidth >>= 1;
                tileHeight >>= 1;
            }
        }
    }
    if (texture->unk8 != NULL) {
        animation = texture->unk8;
        if (animation->unk1A != 0) {
            secondaryTexture = gFormFiles[sTextureFormFileId].fileEntry[texture->unk18].allocPtr;
            if (secondaryTexture != NULL) {
                tileWidth = secondaryTexture->unk1C;
                tileHeight = secondaryTexture->unk1E;

                uls = (s32) (animation->unk10 * tileWidth * 4.0f);
                ult = (s32) (animation->unk14 * tileHeight * 4.0f);
                gDPSetTileSize(displayListHead[0]++, 2, uls, ult, (((tileWidth * 4) + uls) - 1),
                               (((tileHeight * 4) + ult) - 1));
            }
        }
    }
}
#line 177 "src/modules/uvtexture_rom.c"

#line 178 "src/modules/uvtexture_rom.c"

/* Apply the packed texture input to texture selection, display-list commands,
 * alpha/palette state and the cached output word. Preserve the two cache stores.
 * RE_ORIGINAL_QUIRK: the original OR with 0x40000 makes the nonzero test true
 * for every 32-bit state word, clearing the combine selector; keep that OR.
 * The first loaded record is read at offset 0x14 before the later null check.
 * RE_UNKNOWN: caller/asset guarantees for that first read, texture/sequence ID
 * bounds, asset lifetime and display-list/palette capacity require original
 * UVTX parsers, TSEQ providers and renderer callers; flag intent is incomplete. */
#line 178 "src/modules/uvtexture_rom.c"
s32 uvTextureApplyPackedState(s32 inputStateWord) {
    Gfx **displayListHead;
    s32 textureId;
    s32 textureParameter;
    s32 combineRequested;
    u8 alpha;
    s32 textureStateWord;
    s32 paletteIndex;
    UnkStruct_uvtexture_rom_00400244 *texture;

    displayListHead = sUvGfxMgrExports->uvGetDisplayListHead();
    textureId = inputStateWord & 0xFFF;
    if (textureId == 0xFFE) {
        textureId++;
    }
    if (textureId >= 0xFFF) {
        textureStateWord = 0xFFF;
        texture = NULL;
    } else {
        texture = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
        textureStateWord = (texture->unk14 & ~0xFFF) | textureId;
        if (textureStateWord & 0x80000) {
            textureId = sUvTextureSequenceExport->uvTexSeqGetCurFrameTexture(texture->unk20);
            texture = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
        }
        if (texture == NULL) {
            return 0xFFF;
        }
        textureStateWord = (texture->unk14 & ~0xFFF) | textureId;
    }

    if (inputStateWord & 0x01000000) {
        textureStateWord |= 0x2000;
    }

    combineRequested = (inputStateWord & 0x80000000) && (inputStateWord & 0x800000);
    if ((textureStateWord | 0x40000) != 0) {
        combineRequested = 0;
    }
    if (((textureId != (D_uvtexture_rom_00400D24 & 0xFFF))
         && ((D_uvtexture_rom_00400D00 == 0) || (D_uvtexture_rom_00400D04 == 0)))
        || (D_uvtexture_rom_00400D00 == 1)) {
        if ((textureId >= 0xFFE) || (D_uvtexture_rom_00400D00 == 3)) {
            gSPDisplayList(displayListHead[0]++, D_uvtexture_rom_00400CC0);
            if (combineRequested != 0) {
                gDPSetCombineLERP(displayListHead[0]++, 0, 0, 0, SHADE, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0,
                                  COMBINED);
            }
        } else {
            D_uvtexture_rom_00400D04 = 1;
            uvTextureEmitDisplayListAndAnimatedTileSizes(textureId);
            if ((combineRequested != 0) && !(textureStateWord & 0x1000)) {
                if (texture->unk22 >= 2) {
                    gDPSetCombineLERP(displayListHead[0]++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0,
                                      LOD_FRACTION, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED);
                } else {
                    gDPSetCombineMode(displayListHead[0]++, G_CC_MODULATEIDECALA, G_CC_PASS2);
                }
            }
        }
    }
    if (texture != NULL) {
        alpha = texture->colorAlpha;
    } else {
        alpha = 0xFF;
    }
    if (alpha != sPrevAlphaColor) {
        if (alpha == 0xFF) {
            gDPSetAlphaCompare(displayListHead[0]++, G_AC_NONE);

        } else {
            gDPSetAlphaCompare(displayListHead[0]++, G_AC_THRESHOLD);

            gDPSetBlendColor(displayListHead[0]++, 255, 255, 255, alpha);
        }
        sPrevAlphaColor = alpha;
    }
    if (sPrevAlphaColor != 0xFF) {
        textureStateWord |= 0x10000;
    }
    if (textureStateWord & 0x2000) {
        textureParameter = 0x10;
    } else {
        textureParameter = 0;
    }
    uvGfxTextureDL(displayListHead, textureId, textureParameter);
    if ((texture != NULL) && (texture->unk21 == 0)) {
        for (paletteIndex = 0; paletteIndex < texture->unk22; paletteIndex++) {
            gDPLoadTLUT_pal16(displayListHead[0]++, paletteIndex + 1, (u8 *) (texture->unk10 + paletteIndex * 0x40) + 0x80000000);
        }
        textureStateWord |= 0x20000;
    } else {
        gDPSetTextureLUT(displayListHead[0]++, G_TT_NONE);
        textureStateWord &= ~0x20000;
    }
    D_uvtexture_rom_00400D24 = textureStateWord;
    if ((texture != NULL) && (texture->unk21 == 1)) {
        textureStateWord |= 0x4000;
    } else {
        textureStateWord &= ~0x4000;
    }
    D_uvtexture_rom_00400D24 = textureStateWord;
    return textureStateWord;
}
#line 282 "src/modules/uvtexture_rom.c"

#line 283 "src/modules/uvtexture_rom.c"

/* Emit texture-off state for sentinel 0xFFF, or copy the loaded first command
 * while replacing its parameter byte. Preserve repeated output-head reloads.
 * RE_UNKNOWN: the reference parameter's update contract, valid non-sentinel
 * IDs and asset/output-buffer lifetime, capacity and alias domains require
 * original state producers, UVTX parsers and display-list consumers. */
#line 283 "src/modules/uvtexture_rom.c"
void uvGfxTextureDL(Gfx **displayListHead, s32 textureId, s32 textureParameter) {
    s32 parameterDiffers;
    Gfx **textureDisplayList;

    if (textureParameter != D_uvtexture_rom_00400CEC) {
        parameterDiffers = 1;
    } else {
        parameterDiffers = 0;
    }

    if (textureId == 0xFFF) {
        u32 cachedTextureId = D_uvtexture_rom_00400D24 & 0xFFF;
        if (cachedTextureId == 0xFFF) {
            if (!parameterDiffers) {
                return;
            }
        }

        gSPTextureL(displayListHead[0]++, 0, 0, 0, textureParameter, G_TX_RENDERTILE, G_OFF);
        return;
    }
    textureDisplayList = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    if (textureParameter) {
        GFX_PATCH_DL(displayListHead[0], textureDisplayList[0], textureParameter);
        displayListHead[0]++;
    } else if (parameterDiffers != 0) {
        GFX_PATCH_DL(displayListHead[0], textureDisplayList[0], 0);
        displayListHead[0]++;
    }
}
#line 313 "src/modules/uvtexture_rom.c"

#line 314 "src/modules/uvtexture_rom.c"
/* XOR the active counter index with one, clear D10[index], and reset binding state.
 * Original TEXT places D10/D14 in adjacent four-byte BSS words; loaded-texture emissions increment the selected word.
 * Fill existing shared 0x1000-byte scratch with 0xFF; callback context is unused. */
void uvTextureBeginBuffer(s32 context) {
    D_uvtexture_rom_00400D08 = D_uvtexture_rom_00400D08 ^ 1;
    D_uvtexture_rom_00400D10[D_uvtexture_rom_00400D08] = 0;
    D_uvtexture_rom_00400D24 = 0xFFD;
    D_uvtexture_rom_00400D04 = 0;
    if (D_uvtexture_rom_00400D28 != NULL) {
        uvMemSet(D_uvtexture_rom_00400D28, 0xFFU, 0x1000U);
    }
}
#line 323 "src/modules/uvtexture_rom.c"

#line 324 "src/modules/uvtexture_rom.c"
/* Set the original 0xFFE texture-binding sentinel. */
void uvTextureInvalidateBinding(void) {
    D_uvtexture_rom_00400D24 = 0xFFE;
}
#line 327 "src/modules/uvtexture_rom.c"

#line 328 "src/modules/uvtexture_rom.c"
/* Mode zero reads the opposite counter: D14 for index zero, D10 for index one; other modes return zero.
 * BSS-zero initialization is visible in accepted uvLoadModule source, not this TEXT entrypoint; preserve original cross-array indexing.
 * RE_UNKNOWN: C array bounds, indirect alias writes and reload domains; audit original loader/alias callers before stronger invariants. */
s32 uvTextureGetOtherBufferValue(s32 mode) {
    if (mode == 0) {
        return D_uvtexture_rom_00400D14[0 - D_uvtexture_rom_00400D08];
    }
    return 0;
}
#line 334 "src/modules/uvtexture_rom.c"

#line 335 "src/modules/uvtexture_rom.c"

/* Selector 1 copies record halfwords at 0x1C and 0x1E into two word outputs,
 * in that order. Zero or another selector ends the argument stream; sentinel
 * 0xFFF or a missing record returns without output writes.
 * RE_UNKNOWN: ID bounds, selector payload/termination guarantees, output
 * validity and field meanings require original callers and UVTX parsers. */
#line 335 "src/modules/uvtexture_rom.c"
void uvTextureGetProps(s32 textureId, ...) {
    va_list args;
    s32 selector;
    UnkStruct_uvtexture_rom_00400244 *texture;

    if (textureId == 0xFFF) {
        return;
    }

    texture = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    va_start(args, textureId);

    if (texture == NULL) {
        return;
    }

    while (TRUE) {
        selector = va_arg(args, s32);
        if ((selector == 0) || (selector != 1)) {
            break;
        }

        *va_arg(args, s32*) = texture->unk1C;
        *va_arg(args, s32*) = texture->unk1E;
    }
}
#line 361 "src/modules/uvtexture_rom.c"

#line 362 "src/modules/uvtexture_rom.c"
/* Lazily allocate the shared 4096-byte, eight-byte-aligned texture scratch
 * buffer, then return its pointer. Preserve original allocation-failure behavior. */
void *uvTextureGetOrAllocateScratch(void) {
    if (D_uvtexture_rom_00400D28 == NULL) {
        D_uvtexture_rom_00400D28 = _uvMemAlloc(0x1000U, 8U);
    }
    return D_uvtexture_rom_00400D28;
}
#line 368 "src/modules/uvtexture_rom.c"

#line 369 "src/modules/uvtexture_rom.c"
/* Return the shared texture scratch pointer without allocating it. */
void *uvTextureGetScratch(void) {
    return D_uvtexture_rom_00400D28;
}
#line 372 "src/modules/uvtexture_rom.c"
