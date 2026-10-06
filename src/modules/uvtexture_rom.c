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
void func_uvtexture_rom_00400134(void);
u8 func_uvtexture_rom_00400164(s32 arg0);
void *func_uvtexture_rom_004001C0(s32 arg0, f32 *arg1, f32 *arg2);
void func_uvtexture_rom_00400244(s32 arg0);
s32 func_uvtexture_rom_00400500(s32 arg0);
void uvGfxTextureDL(Gfx **gdl, s32 textureId, s32 xparam);
void func_uvtexture_rom_00400B10(s32 arg0);
void func_uvtexture_rom_00400B7C(void);
s32 func_uvtexture_rom_00400B8C(s32 arg0);
void uvTextureGetProps(s32 arg0, ...);
void *func_uvtexture_rom_00400C6C(void);
void *func_uvtexture_rom_00400CB0(void);


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

void __entrypoint_func_uvtexture_rom_400000(UvTexture_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->func_uvtexture_rom_00400134 = func_uvtexture_rom_00400134;
    exports->func_uvtexture_rom_00400164 = func_uvtexture_rom_00400164;
    exports->func_uvtexture_rom_004001C0 = func_uvtexture_rom_004001C0;
    exports->func_uvtexture_rom_00400244 = func_uvtexture_rom_00400244;
    exports->func_uvtexture_rom_00400500 = func_uvtexture_rom_00400500;
    exports->func_uvtexture_rom_00400B7C = func_uvtexture_rom_00400B7C;
    exports->func_uvtexture_rom_00400B8C = func_uvtexture_rom_00400B8C;
    exports->uvTextureGetProps = uvTextureGetProps;
    exports->func_uvtexture_rom_00400C6C = func_uvtexture_rom_00400C6C;
    exports->func_uvtexture_rom_00400CB0 = func_uvtexture_rom_00400CB0;
    exports->D_uvtexture_rom_00400D00 = &D_uvtexture_rom_00400D00;
#ifdef __sgi
#line 77
#endif
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvTextureSequenceExport = uvLoadModule('TSEQ');
    sTextureFormFileId = uvGetFormFileIdByTagDup('UVTX');
    sUvCbackExports->uvAddCallback(
        sUvGfxMgrExports->func_uvgfxmgr_rom_00400AB8(1), func_uvtexture_rom_00400B10, 0, 0);
}

void func_uvtexture_rom_00400134(void) {
    uvUnloadModule('GMGR');
    uvUnloadModule('CBCK');
}

u8 func_uvtexture_rom_00400164(s32 textureId) {
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

void *func_uvtexture_rom_004001C0(s32 arg0, f32 *arg1, f32 *arg2) {
    UnkStruct_uvtexture_rom_00400244 *temp_v1;
    UnkStruct_uvtexture_rom_00400244_1 *temp_a0;

    if (arg0 == 0xFFF) {
        return NULL;
    }
    temp_v1 = gFormFiles[sTextureFormFileId].fileEntry[arg0].allocPtr;
    if (temp_v1 == NULL) {
        return NULL;
    }
    temp_a0 = temp_v1->unk4;
    if (temp_a0 == NULL) {
        return NULL;
    }
    *arg1 = temp_a0->unk8;
    *arg2 = temp_v1->unk4->unkC;
    return temp_v1->unk4;
}

void func_uvtexture_rom_00400244(s32 textureId) {
    Gfx **gdl;
    s32 var_t0;
    s32 var_t1;
    UnkStruct_uvtexture_rom_00400244 *temp_a0;
    UnkStruct_uvtexture_rom_00400244 *temp_t4;
    UnkStruct_uvtexture_rom_00400244_1 *temp_a1;
    s32 i;
    s32 uls;
    s32 ult;
    s32 lrs;
    s32 lrt;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    temp_t4 = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    if (temp_t4 == NULL) {
        return;
    }

    D_uvtexture_rom_00400D10[D_uvtexture_rom_00400D08]++;
    gSPDisplayList(gdl[0]++, OS_PHYSICAL_TO_K0(temp_t4->unk0));
    if (temp_t4->unk4 != NULL) {
        temp_a1 = temp_t4->unk4;
        if (temp_a1->unk1A != 0) {
            var_t0 = temp_t4->unk1C;
            var_t1 = temp_t4->unk1E;
            for (i = 1; i <= temp_t4->unk22; i++) {
                uls = (s32) (temp_a1->unk10 * var_t0 * 4.0f);
                ult = (s32) (temp_a1->unk14 * var_t1 * 4.0f);
                lrs = ((temp_t4->unk1C * 4) + uls) - 1;
                lrt = ((temp_t4->unk1E * 4) + ult) - 1;
                gDPSetTileSize(gdl[0]++, i, uls, ult, lrs, lrt);
                var_t0 >>= 1;
                var_t1 >>= 1;
            }
        }
    }
    if (temp_t4->unk8 != NULL) {
        temp_a1 = temp_t4->unk8;
        if (temp_a1->unk1A != 0) {
            temp_a0 = gFormFiles[sTextureFormFileId].fileEntry[temp_t4->unk18].allocPtr;
            if (temp_a0 != NULL) {
                var_t0 = temp_a0->unk1C;
                var_t1 = temp_a0->unk1E;

                uls = (s32) (temp_a1->unk10 * var_t0 * 4.0f);
                ult = (s32) (temp_a1->unk14 * var_t1 * 4.0f);
                gDPSetTileSize(gdl[0]++, 2, uls, ult, (((var_t0 * 4) + uls) - 1),
                               (((var_t1 * 4) + ult) - 1));
            }
        }
    }
}

s32 func_uvtexture_rom_00400500(s32 arg0) {
    Gfx **gdl;
    s32 var_a3;
    s32 var_a2;
    s32 var_a1;
    u8 alpha;
    s32 var_s2;
    s32 i;
    UnkStruct_uvtexture_rom_00400244 *var_s1;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    var_a3 = arg0 & 0xFFF;
    if (var_a3 == 0xFFE) {
        var_a3++;
    }
    if (var_a3 >= 0xFFF) {
        var_s2 = 0xFFF;
        var_s1 = NULL;
    } else {
        var_s1 = gFormFiles[sTextureFormFileId].fileEntry[var_a3].allocPtr;
        var_s2 = (var_s1->unk14 & ~0xFFF) | var_a3;
        if (var_s2 & 0x80000) {
            var_a3 = sUvTextureSequenceExport->uvTexSeqGetCurFrameTexture(var_s1->unk20);
            var_s1 = gFormFiles[sTextureFormFileId].fileEntry[var_a3].allocPtr;
        }
        if (var_s1 == NULL) {
            return 0xFFF;
        }
        var_s2 = (var_s1->unk14 & ~0xFFF) | var_a3;
    }

    if (arg0 & 0x01000000) {
        var_s2 |= 0x2000;
    }

    var_a1 = (arg0 & 0x80000000) && (arg0 & 0x800000);
    if ((var_s2 | 0x40000) != 0) {
        var_a1 = 0;
    }
    if (((var_a3 != (D_uvtexture_rom_00400D24 & 0xFFF))
         && ((D_uvtexture_rom_00400D00 == 0) || (D_uvtexture_rom_00400D04 == 0)))
        || (D_uvtexture_rom_00400D00 == 1)) {
        if ((var_a3 >= 0xFFE) || (D_uvtexture_rom_00400D00 == 3)) {
            gSPDisplayList(gdl[0]++, D_uvtexture_rom_00400CC0);
            if (var_a1 != 0) {
                gDPSetCombineLERP(gdl[0]++, 0, 0, 0, SHADE, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0,
                                  COMBINED);
            }
        } else {
            D_uvtexture_rom_00400D04 = 1;
            func_uvtexture_rom_00400244(var_a3);
            if ((var_a1 != 0) && !(var_s2 & 0x1000)) {
                if (var_s1->unk22 >= 2) {
                    gDPSetCombineLERP(gdl[0]++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0,
                                      LOD_FRACTION, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED);
                } else {
                    gDPSetCombineMode(gdl[0]++, G_CC_MODULATEIDECALA, G_CC_PASS2);
                }
            }
        }
    }
    if (var_s1 != NULL) {
        alpha = var_s1->colorAlpha;
    } else {
        alpha = 0xFF;
    }
    if (alpha != sPrevAlphaColor) {
        if (alpha == 0xFF) {
            gDPSetAlphaCompare(gdl[0]++, G_AC_NONE);

        } else {
            gDPSetAlphaCompare(gdl[0]++, G_AC_THRESHOLD);

            gDPSetBlendColor(gdl[0]++, 255, 255, 255, alpha);
        }
        sPrevAlphaColor = alpha;
    }
    if (sPrevAlphaColor != 0xFF) {
        var_s2 |= 0x10000;
    }
    if (var_s2 & 0x2000) {
        var_a2 = 0x10;
    } else {
        var_a2 = 0;
    }
    uvGfxTextureDL(gdl, var_a3, var_a2);
    if ((var_s1 != NULL) && (var_s1->unk21 == 0)) {
        for (i = 0; i < var_s1->unk22; i++) {
            gDPLoadTLUT_pal16(gdl[0]++, i + 1, (u8 *) (var_s1->unk10 + i * 0x40) + 0x80000000);
        }
        var_s2 |= 0x20000;
    } else {
        gDPSetTextureLUT(gdl[0]++, G_TT_NONE);
        var_s2 &= ~0x20000;
    }
    D_uvtexture_rom_00400D24 = var_s2;
    if ((var_s1 != NULL) && (var_s1->unk21 == 1)) {
        var_s2 |= 0x4000;
    } else {
        var_s2 &= ~0x4000;
    }
    D_uvtexture_rom_00400D24 = var_s2;
    return var_s2;
}

void uvGfxTextureDL(Gfx **gdl, s32 textureId, s32 xparam) {
    s32 var_v0;
    Gfx **textureDisplayList;

    if (xparam != D_uvtexture_rom_00400CEC) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }

    if (textureId == 0xFFF) {
        u32 t1 = D_uvtexture_rom_00400D24 & 0xFFF;
        if (t1 == 0xFFF) {
            if (!var_v0) {
                return;
            }
        }

        gSPTextureL(gdl[0]++, 0, 0, 0, xparam, G_TX_RENDERTILE, G_OFF);
        return;
    }
    textureDisplayList = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    if (xparam) {
        GFX_PATCH_DL(gdl[0], textureDisplayList[0], xparam);
        gdl[0]++;
    } else if (var_v0 != 0) {
        GFX_PATCH_DL(gdl[0], textureDisplayList[0], 0);
        gdl[0]++;
    }
}

void func_uvtexture_rom_00400B10(s32 arg0) {
    D_uvtexture_rom_00400D08 = D_uvtexture_rom_00400D08 ^ 1;
    D_uvtexture_rom_00400D10[D_uvtexture_rom_00400D08] = 0;
    D_uvtexture_rom_00400D24 = 0xFFD;
    D_uvtexture_rom_00400D04 = 0;
    if (D_uvtexture_rom_00400D28 != NULL) {
        uvMemSet(D_uvtexture_rom_00400D28, 0xFFU, 0x1000U);
    }
}

void func_uvtexture_rom_00400B7C(void) {
    D_uvtexture_rom_00400D24 = 0xFFE;
}

s32 func_uvtexture_rom_00400B8C(s32 arg0) {
    if (arg0 == 0) {
        return D_uvtexture_rom_00400D14[0 - D_uvtexture_rom_00400D08];
    }
    return 0;
}

void uvTextureGetProps(s32 textureId, ...) {
    va_list args;
    s32 prop;
    UnkStruct_uvtexture_rom_00400244 *temp_v0;

    if (textureId == 0xFFF) {
        return;
    }

    temp_v0 = gFormFiles[sTextureFormFileId].fileEntry[textureId].allocPtr;
    va_start(args, textureId);
    
    if (temp_v0 == NULL) {
        return;
    }

    while (TRUE) {
        prop = va_arg(args, s32);
        if ((prop == 0) || (prop != 1)) {
            break;
        }

        *va_arg(args, s32*) = temp_v0->unk1C;
        *va_arg(args, s32*) = temp_v0->unk1E;
    }
}

void *func_uvtexture_rom_00400C6C(void) {
    if (D_uvtexture_rom_00400D28 == NULL) {
        D_uvtexture_rom_00400D28 = _uvMemAlloc(0x1000U, 8U);
    }
    return D_uvtexture_rom_00400D28;
}

void *func_uvtexture_rom_00400CB0(void) {
    return D_uvtexture_rom_00400D28;
}
