// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"
#include "stdarg.h"

typedef struct UnkModel_Exports_s {
    /* 0x00 */ char pad0[0x1C];
    /* 0x1C */ s32 (*func_uvmodel_rom_00400608)(void *arg0, f32 arg1); /* inferred */
    /* 0x20 */ char pad20[0x30];                    /* maybe part of unk1C[0xD]? */
} UnkModel_Exports;                                 /* size = 0x50 */


void __entrypoint_func_uvenv_rom_400000(UvEnv_Exports *exports);
void func_uvenv_rom_004001B4(void);
void func_uvenv_rom_00400220(f32 arg0, f32 arg1, u16 *arg2, ParsedUVEN *arg3);
void uvEnvProps(s32 envId, ...);
void uvEnvGetProps(s32 envId, ...);
void func_uvenv_rom_00401F7C(s32 fileId, s32 arg1, s32 arg2);
void func_uvenv_rom_00401FE0(s32 arg0);
void func_uvenv_rom_0040205C(s32 arg0);
void _uvEnvDraw(s32 arg0);
void func_uvenv_rom_00402DD8(s32 arg0, s32 arg1);
void func_uvenv_rom_00402E68(s32 arg0, s32 arg1);
void func_uvenv_rom_00402F00(s32 arg0, s32 arg1, s32 arg2, f32 arg3);
s32 func_uvenv_rom_00403AFC(s32 arg0);

// .data
s32 D_uvenv_rom_00403BF0[] = {0x00300000, __entrypoint_func_uvenv_rom_400000, 0, 0};

// .bss
s32 D_uvenv_rom_00403C00;
s32 D_uvenv_rom_00403C04;
s32* D_uvenv_rom_00403C08;
s32 D_uvenv_rom_00403C0C;
static UvFMtx_Rom_Exports* sUvFmtxExports;
static UvGfxState_Rom_Exports* sUvGfxStateExports;
static UvGfxMgr_Exports* sUvGfxMgrExports;
static UvChannel_Exports* sUvChannel_Exports;
static UvCback_Exports* sUvCbackExports;
static UnkModel_Exports* sUvModelExports;

void __entrypoint_func_uvenv_rom_400000(UvEnv_Exports* exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->func_uvenv_rom_004001B4 = func_uvenv_rom_004001B4;
    exports->func_uvenv_rom_00400220 = func_uvenv_rom_00400220;
    exports->uvEnvProps = uvEnvProps;
    exports->uvEnvGetProps = uvEnvGetProps;
    exports->func_uvenv_rom_00401F7C = func_uvenv_rom_00401F7C;
    exports->func_uvenv_rom_00401FE0 = func_uvenv_rom_00401FE0;
    exports->func_uvenv_rom_00402DD8 = func_uvenv_rom_00402DD8;
    exports->func_uvenv_rom_00402E68 = func_uvenv_rom_00402E68;
    exports->func_uvenv_rom_00402F00 = func_uvenv_rom_00402F00;
    exports->func_uvenv_rom_00403AFC = func_uvenv_rom_00403AFC;
    exports->unk28 = &D_uvenv_rom_00403C00;
    exports->unk2C = &D_uvenv_rom_00403C04;
#ifdef __sgi
#line 1
#endif
    sUvFmtxExports = uvLoadModule('FMTX');
    sUvGfxStateExports = uvLoadModule('STAT');
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvChannel_Exports = uvLoadModule('CHAN');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvModelExports = uvLoadModule('MODL');
    sUvChannel_Exports->func_uvchannel_rom_00400288(0, 0xD, &D_uvenv_rom_00403C0C, 0);
    D_uvenv_rom_00403C08 = _uvMemAllocAlign8(D_uvenv_rom_00403C0C * 4);
    for (i = 0; i < D_uvenv_rom_00403C0C; i++) {
        D_uvenv_rom_00403C08[i] = 0xFFFF;
    }
}

void func_uvenv_rom_004001B4(void) {
    _uvMemFree(D_uvenv_rom_00403C08);
    uvUnloadModule('FMTX');
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
    uvUnloadModule('MODL');
}

void func_uvenv_rom_00400220(f32 arg0, f32 arg1, u16* arg2, ParsedUVEN* arg3) {
    f32 var_fa0;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_ft2;
    s32 temp_ft3;
    s32 i;

    var_fv0 = 1.0f;
    for (i = 0; i < arg3->modelCount; i++) {
        if (arg3->modelTable[i].flag & 2) {
            var_fv0 = 0.0f;
        }
    }
    
    temp_ft2 = (s32) (arg0 * 248.0f);
    var_fv1 = (f32) (0xF8 - temp_ft2);
    if (var_fv1 == 0.0f) {
        var_fv1 = 1000000.0f;
    }
    
    for (i = 0; i < 256; i++) {
        if (i < temp_ft2) {
            var_fa0 = 0.0f;
        } else if (i < 0xF9) {
            var_fa0 = (i - temp_ft2) / var_fv1;
        } else {
            var_fa0 = var_fv0;
        }
        temp_ft3 = (s32) (var_fa0 * arg1 * 255.0f);
        arg2[i] = ((temp_ft3 << 8) | temp_ft3);
    }
}

void uvEnvProps(s32 envId, ...) {
    ParsedUVEN *var_a3;
    va_list args;
    s32 pad;
    f32 temp_fa0;
    f32 temp_fa1;
    u32 temp_v0_2;
    void *var_a2;

    var_a3 = uvGetLoadedFile('UVEN', envId);

    if (var_a3 == NULL) {
        return;
    }
    va_start(args, envId);
    while (TRUE) {  
        temp_v0_2 = va_arg(args, s32);
        switch (temp_v0_2) {
            case 2:
                temp_fa0 = va_arg(args, f64);
                temp_fa1 = va_arg(args, f64);
                if (!(temp_fa0 > 1.0f) && !(temp_fa0 < 0.0f)) {
                    sUvGfxStateExports->func_uvgfxstate_rom_00401F54(temp_fa0, temp_fa1);
                    if ((temp_fa0 == 0.0f) || (temp_fa0 == 1.0f)) {
                        var_a3->unk1C = 0;
                    } else {
                        var_a3->unk1C = 1;
                        var_a3->unk1D = 0;
                        var_a3->unk3C = temp_fa0;
                        var_a3->unk40 = temp_fa1;
                    }
                }
                break;
            case 3:
                temp_fa0 = va_arg(args, f64);
                temp_fa1 = va_arg(args, f64);
                if (!(temp_fa0 > 1.0f) && !(temp_fa0 < 0.0f)) {
                    if ((temp_fa0 != 0.0f) && (temp_fa0 != 1.0f)) {
                        var_a2 = var_a3->unk44;
                        var_a3->unk3C = temp_fa0;
                        var_a3->unk40 = temp_fa1;
                        var_a3->unk1D = 1;
                        var_a3->unk1C = 0;
                        if (var_a2 == NULL) {
                            var_a2 = _uvMemAlloc(0x200U, 8U);
                            var_a3->unk44 = var_a2;
                        }
                        func_uvenv_rom_00400220(temp_fa0, temp_fa1, var_a2, var_a3);
                    } else {
                        var_a3->unk1D = 0;
                    }
                }
                break;
            case 5:
                var_a3->unkC = va_arg(args, f64) * 255.0;
                var_a3->unkD = va_arg(args, f64) * 255.0;
                var_a3->unkE = va_arg(args, f64) * 255.0;
                break;
            case 1:
                var_a3->unk3 = va_arg(args, f64) * 255.0;
                var_a3->unk4 = va_arg(args, f64) * 255.0;
                var_a3->unk5 = va_arg(args, f64) * 255.0;
                break;
            case 4:
                var_a3->unkF = va_arg(args, f64) * 255.0;
                var_a3->unk10 = va_arg(args, f64) * 255.0;
                var_a3->unk11 = va_arg(args, f64) * 255.0;
                break;
            case 8:
                var_a3->unk6 = va_arg(args, f64) * 255.0;
                var_a3->unk7 = va_arg(args, f64) * 255.0;
                var_a3->unk8 = va_arg(args, f64) * 255.0;
                break;
            case 9:
                var_a3->unk9 = va_arg(args, f64) * 255.0;
                var_a3->unkA = va_arg(args, f64) * 255.0;
                var_a3->unkB = va_arg(args, f64) * 255.0;
                break;
            case 6:
                var_a3->unk4C = (u8)(va_arg(args, f64) * 255.0);
                var_a3->unk50 = (u8)(va_arg(args, f64) * 255.0);
                var_a3->unk54 = (u8)(va_arg(args, f64) * 255.0);
                break;
            case 10:
                var_a3->unk0 = va_arg(args, f64) * 255.0;
                var_a3->unk1 = va_arg(args, f64) * 255.0;
                var_a3->unk2 = va_arg(args, f64) * 255.0;
                break;
            case 7:
                var_a3->unk48 = va_arg(args, f64);
                break;
            case 12:
                var_a3->unk58 = va_arg(args, s32);
                break;
            case 13:
                var_a3->unk2E = va_arg(args, s32);
                break;
            case 0:
                return;
       
        }
    }
}

void uvEnvGetProps(s32 envId, ...) {
    va_list args;
    ParsedUVEN *parsedUvEnv;
    f32 var_fa0;
    f32 var_fv1;
    s32 i;
    u32 prop;
    s32 *modelIdsPtr;

    parsedUvEnv = uvGetLoadedFile('UVEN', envId);
    va_start(args, envId);
    if (parsedUvEnv == NULL) {
        PANIC;
        return;
    }

    while (TRUE) {
        prop = va_arg(args, s32);
        switch (prop) {
            case 2:
                if (parsedUvEnv->unk1C != 0) {
                    var_fv1 = parsedUvEnv->unk3C;
                    var_fa0 = parsedUvEnv->unk40;
                } else {
                    var_fv1 = 0.0f;
                    var_fa0 = 0.0f;
                }
                *va_arg(args, f32*) = var_fv1;
                *va_arg(args, f32*) = var_fa0;
                break;
            case 3:
                if (parsedUvEnv->unk1D != 0) {
                    var_fv1 = parsedUvEnv->unk3C;
                    var_fa0 = parsedUvEnv->unk40;
                } else {
                    var_fv1 = 0.0f;
                    var_fa0 = 0.0f;
                }
                *va_arg(args, f32*) = var_fv1;
                *va_arg(args, f32*) = var_fa0;
                break;
            case 11:
                *va_arg(args, s32*) = parsedUvEnv->modelCount;
                modelIdsPtr = va_arg(args, s32*);
                for (i = 0; i < parsedUvEnv->modelCount; i++) {
                    modelIdsPtr[i] = parsedUvEnv->modelTable[i].modelId;
                }
                break;
            case 1:
                *va_arg(args, f32*) = parsedUvEnv->unk3 * 0.0039215684f;
                *va_arg(args, f32*) = (parsedUvEnv->unk4 * 0.0039215684f);
                *va_arg(args, f32*) = (parsedUvEnv->unk5 * 0.0039215684f);
                break;
            case 5:
                *va_arg(args, f32*) = parsedUvEnv->unkC * 0.0039215684f;
                *va_arg(args, f32*) = (parsedUvEnv->unkD * 0.0039215684f);
                *va_arg(args, f32*) = (parsedUvEnv->unkE * 0.0039215684f);
                break;
            case 4:
                *va_arg(args, f32*) = parsedUvEnv->unkF * 0.0039215684f;
                *va_arg(args, f32*) = (parsedUvEnv->unk10 * 0.0039215684f);
                *va_arg(args, f32*) = (parsedUvEnv->unk11 * 0.0039215684f);
                break;
            case 8:
                *va_arg(args, f32*) = parsedUvEnv->unk6 * 0.0039215684f;
                *va_arg(args, f32*) = (parsedUvEnv->unk7 * 0.0039215684f);
                *va_arg(args, f32*) = (parsedUvEnv->unk8 * 0.0039215684f);
                break;
            case 6:
                *va_arg(args, f32*) = parsedUvEnv->unk4C;
                *va_arg(args, f32*) = parsedUvEnv->unk50;
                *va_arg(args, f32*) = parsedUvEnv->unk54;
                break;
            case 9:
                *va_arg(args, f32*) = parsedUvEnv->unk9 * 0.0039215684f;
                *va_arg(args, f32*) = (parsedUvEnv->unkA * 0.0039215684f);
                *va_arg(args, f32*) = (parsedUvEnv->unkB * 0.0039215684f);
                break;
            case 10:
                *va_arg(args, f32*) = parsedUvEnv->unk0 * 0.0039215684f;
                *va_arg(args, f32*) = (parsedUvEnv->unk1 * 0.0039215684f);
                *va_arg(args, f32*) = (parsedUvEnv->unk2 * 0.0039215684f);
                break;
            case 7:
                *va_arg(args, f32*) = parsedUvEnv->unk48;
                break;
            case 12:
                *va_arg(args, s32*) = parsedUvEnv->unk58;
                break;
            case 14:
                *va_arg(args, s32*) = parsedUvEnv->unk58;
                break;
            case 0:
                return;
        }
    }
}

void func_uvenv_rom_00401F7C(s32 fileId, s32 arg1, s32 arg2) {
    ParsedUVEN *parsedUvEnv;

    parsedUvEnv = uvGetLoadedFile('UVEN', fileId);
    if (parsedUvEnv == NULL) {
        return;
    }

    switch (arg1) {
        case 0:
            parsedUvEnv->unk38 = arg2;
            return;
        case 1:
            parsedUvEnv->unk5C = arg2;
            break;
    }
}

void func_uvenv_rom_00401FE0(s32 arg0) {
    CallbackList* sp1C;

    sUvChannel_Exports->func_uvchannel_rom_00400288(arg0, 6, &sp1C, 0);
    sUvCbackExports->uvAddCallback(sp1C, _uvEnvDraw, 0, 0x14);
    sUvCbackExports->uvAddCallback(sp1C, func_uvenv_rom_0040205C, 0, 0x57);
}

void func_uvenv_rom_0040205C(s32 arg0) {
    ParsedUVEN *temp_v0_2;
    s32 temp_s0;
    s32 temp_s2;
    Gfx **gdl;
    s32 temp_s3;
    s32 var_t0;
    s32 temp_lo;
    u16 *temp_s6;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    temp_s0 = D_uvenv_rom_00403C08[arg0];
    if (D_uvenv_rom_00403C00 != 0) {
        return;
    }

    temp_s2 = sUvGfxMgrExports->uvGetScreenHeight();
    temp_s3 = sUvGfxMgrExports->uvGetScreenWidth();
    if (temp_s0 == 0xFFFF) {
        return;
    }

    temp_v0_2 = uvGetLoadedFile('UVEN', temp_s0);
    if ((temp_v0_2 == NULL) || (temp_v0_2->unk1D == 0)) {
        return;
    }

    temp_s6 = sUvGfxMgrExports->func_uvgfxmgr_rom_0040204C();
    sUvGfxStateExports->uvGfxSync();
    gSPTexture(gdl[0]++, 0xFFFF, 0xFFFF, 0, 1, G_ON);
    gDPSetTextureLOD(gdl[0]++, G_TL_TILE);
    gDPSetTextureFilter(gdl[0]++, G_TF_POINT);
    gDPSetTextureDetail(gdl[0]++, G_TD_CLAMP);
    gDPSetTexturePersp(gdl[0]++, G_TP_NONE);
    gDPSetTileSize(gdl[0]++, 1, 0, 0, 0x04FC, 0x0008);
    gDPSetTile(gdl[0]++, G_IM_FMT_IA, G_IM_SIZ_16b, 80, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, 2, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 9, G_TX_NOLOD);
    gDPSetCycleType(gdl[0]++, G_CYC_2CYCLE);
    gDPSetTextureImage(gdl[0]++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, OS_K0_TO_PHYSICAL(temp_v0_2->unk44));
    gDPTileSync(gdl[0]++);
    gDPSetTile(gdl[0]++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0100, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(gdl[0]++);
    gDPLoadTLUTCmd(gdl[0]++, G_TX_LOADTILE, 255);
    gDPPipeSync(gdl[0]++);
    gDPSetTextureLUT(gdl[0]++, G_TT_IA16);
    gDPSetFogColor(gdl[0]++, temp_v0_2->unk3, temp_v0_2->unk4, temp_v0_2->unk5, 255);
    gDPSetRenderMode(gdl[0]++, AA_EN | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | G_RM_PASS, AA_EN | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gDPSetCombineLERP(gdl[0]++, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetColorDither(gdl[0]++, G_CD_NOISE);
    gDPSetAlphaDither(gdl[0]++, G_AD_NOISE);
    gDPSetTile(gdl[0]++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 2, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 9, G_TX_NOLOD);



    temp_s6 = &temp_s6[temp_s3 * temp_s2];
    for (var_t0 = 0; var_t0 <= (temp_s2 - 3); var_t0 += 3) {
        temp_lo = temp_s3 * 2 * (var_t0 + 3);
        gDPSetTextureImage(gdl[0]++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, (u32)temp_s6 - temp_lo);
        gDPLoadBlock(gdl[0]++, G_TX_LOADTILE, 0, 0, 959, 26);
        gSPTextureRectangle(gdl[0]++, 0, (temp_s2 - 3 - var_t0) << 2, 0x4FC, (temp_s2 - var_t0) << 2, 1, 0, 0, 0x400, 0x400);
    }
    gDPSetTextureLUT(gdl[0]++, G_TT_NONE);
    sUvGfxStateExports->func_uvgfxstate_rom_004022B0();
}

void _uvEnvDraw(s32 arg0) {
    ParsedUVMD *parsedUvMD;
    ParsedUVEN *var_s6;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_s2;
    f32 sp214;
    f32 sp210;
    Gfx **gdl;
    f32 var_fv0;
    s32 temp_s0;
    Vec3F sp1F8;
    f32 sp1F4;
    f32 sp1F0;
    f32 sp1EC;
    f32 sp1E8;
    f32 sp1E4;
    f32 sp1E0;
    Mtx4F sp1A0;
    Mtx4F sp160;
    Mtx4F sp120;
    s32 sp11C;
    s32 var_a0;
    s32 sp114;
    Mtx4F spD4;
    uvModelLOD *modLod;
    s32 i;
    s32 j;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    temp_s0 = D_uvenv_rom_00403C08[arg0];
    sp114 = 0;
    if (D_uvenv_rom_00403C04 != 0) {
        sUvGfxMgrExports->uvGfxFillRect(0U, 0U, 0U);
        return;
    }
    if (arg0 >= D_uvenv_rom_00403C0C) {
        return;
    }

    sUvChannel_Exports->func_uvchannel_rom_00400288(arg0, 7, &sp1F8, 0);
    if (temp_s0 == 0xFFFF) {
        var_s6 = NULL;
    } else {
        var_s6 = uvGetLoadedFile('UVEN', temp_s0);
    }
    if (var_s6 == NULL) {
        return;
    }

    if (var_s6->unk5C != NULL) {
        var_s6->unk5C();
    }
    
    if (var_s6->unk1C != 0) {
        sp214 = var_s6->unk3C;
        sp210 = var_s6->unk40;
    } else {
        sp214 = 0.0f;
        sp210 = 0.0f;
    }
    if (var_s6->unk2E != 0) {
        sUvGfxMgrExports->uvGfxFillRect(var_s6->unk0, var_s6->unk1, var_s6->unk2);
        sp114 = 1;
    }

    gDPSetFogColor(gdl[0]++, var_s6->unk3, var_s6->unk4, var_s6->unk5, 0xFF);
    if (var_s6->unk58 != 0) {
        sp11C = var_s6->modelCount;
    } else {
        sp11C = 0;
    }

    for (i = 0; i != sp11C; i++) {
        if (i == 0) {
            gSPClipRatio(gdl[0]++, FRUSTRATIO_1);
        }
        parsedUvMD = uvGetLoadedFile('UVMD', var_s6->modelTable[i].modelId);
        if (parsedUvMD == NULL) {
            return;
        }

        temp_s2 = var_s6->modelTable[i].flag;
        if ((temp_s2 & 2) && (var_s6->unk40 > 0.95) && (var_s6->unk1D != 0)) {
            if (sp114 == 0) {
                sUvGfxMgrExports->uvGfxFillRect(var_s6->unk3, var_s6->unk4, var_s6->unk5);
                sp114 = 1;
            }
            continue;
        }
        
        var_a0 = 0;
        if (parsedUvMD->unk4 >= 2) {
            uvModelLOD_inner sp9C;
            f32 var_fa1;
            var_fa1 = 0.0f;
            for (j = 0; j < parsedUvMD->unk4; j++) {
                if ((parsedUvMD->unk0[j].unk0)->unk4 == 0) {
                    continue;
                }
                sp9C = (parsedUvMD->unk0[j].unk0)->unk8;
                break;
            }
            temp_fv1 = sp9C.unk0 - sp1F8.x;
            temp_fa0 = sp1F8.x - sp9C.unkC;
            if (temp_fv1 < temp_fa0) {
                var_fv0 = temp_fa0;
            } else {
                var_fv0 = temp_fv1;
            }
            temp_fv1 = sp9C.unk4 - sp1F8.y;
            temp_fa0 = sp1F8.y - sp9C.unk10;
            if (var_fv0 > 0.0f) {
                var_fa1 = var_fv0;
            }
            if (temp_fv1 < temp_fa0) {
                var_fv0 = temp_fa0;
            } else {
                var_fv0 = temp_fv1;
            }
            if (var_fa1 < var_fv0) {
                var_fa1 = var_fv0;
            }
            temp_fv1 = sp9C.unk8 - sp1F8.z;
            temp_fa0 = sp1F8.z - sp9C.unk14;
            if (temp_fv1 < temp_fa0) {
                var_fv0 = temp_fa0;
            } else {
                var_fv0 = temp_fv1;
            }
            if (var_fa1 < var_fv0) {
                var_fa1 = var_fv0;
            }
            var_a0 = sUvModelExports->func_uvmodel_rom_00400608(parsedUvMD, SQ(var_fa1));
            if (var_a0 == 0xFF) {
                continue;
            }
             // FAKE
            if (1) {} 
        } else {
            j = 1;
        }
        
        modLod = parsedUvMD->unk0[var_a0].unk0;
        if (temp_s2 & 4) {
            sUvGfxStateExports->func_uvgfxstate_rom_00401F54(sp214, sp210);
        } else {
            sUvGfxStateExports->func_uvgfxstate_rom_00401F54(0.0f, 0.0f);
        }
        if (temp_s2 & 2) {
            sUvChannel_Exports->func_uvchannel_rom_00400288(arg0, 4, &sp1F4, &sp1F0, &sp1E8,
                                                              &sp1EC, &sp1E4, &sp1E0, 1, &sp160, 0);
            sUvFmtxExports->func_uvfmtx_rom_00401F74(&sp120, sp1F4, sp1F0, sp1E8, sp1EC, sp1E4,
                                                27000.0f);
            sUvFmtxExports->uvGfxMtxProjPushF(&sp120);
            if (var_s6->unk1D != 0) {
                gDPSetEnvColor(gdl[0]++, var_s6->unk3, var_s6->unk4, var_s6->unk5, (u8)(255.0f * var_s6->unk40));
            } else {
                gDPSetEnvColor(gdl[0]++, var_s6->unk3, var_s6->unk4, var_s6->unk5, 0);
            }
        }
        sUvFmtxExports->uvMat4SetIdentity(&sp1A0);
        if (temp_s2 & 8) {
            sp1A0.m[3][0] = sp1F8.x;
            sp1A0.m[3][1] = sp1F8.y;
        }
        temp_fv0 = 1.0f / parsedUvMD->unk10;
        sp1A0.m[2][2] = temp_fv0;
        sp1A0.m[1][1] = temp_fv0;
        sp1A0.m[0][0] = temp_fv0;
        sUvFmtxExports->func_uvfmtx_rom_00400370(&spD4, &sp1A0);
        sUvFmtxExports->uvGfxMtxViewLoad(&spD4, 3);
        for (j = 0; j < (u32)modLod->unk4; j++) {
            int prev = modLod->stateTable[j].state;
            if (!(temp_s2 & 1)) {
                modLod->stateTable[j].state &= ~0x200000;
            }
            if (temp_s2 & 0x10) {
                modLod->stateTable[j].state &= ~0x400000;
            }
            sUvGfxStateExports->uvGfxStateDraw(&modLod->stateTable[j]);
            modLod->stateTable[j].state = prev;
        }
        if (temp_s2 & 2) {
            sUvFmtxExports->uvGfxMtxProjPushF(&sp160);
        }
        sUvFmtxExports->uvGfxMtxFViewPop();
    }
    sUvGfxStateExports->func_uvgfxstate_rom_00401F54(sp214, sp210);
    if (var_s6->unk38 != NULL) {
        var_s6->unk38();
    }
}

void func_uvenv_rom_00402DD8(s32 arg0, s32 arg1) {
    if (D_uvenv_rom_00403C0C >= arg0) {
        if (arg1 == -1) {
            arg1 = 0xFFFF;
        }
        if ((arg1 & 0xFFFF) != 0xFFFF) {
            if (uvGetLoadedFile('UVEN', arg1) == NULL) {
                if (uvLoadFile('UVEN', arg1) == NULL) {
                    arg1 = 0xFFFF;
                }
            }
        }
        D_uvenv_rom_00403C08[arg0] = arg1;
    }
}


void func_uvenv_rom_00402E68(s32 arg0, s32 arg1) {
    ParsedUVEN* temp_s0;
    ParsedUVEN* temp_v0;

    temp_s0 = uvGetLoadedFile('UVEN', arg0);
    temp_v0 = uvGetLoadedFile('UVEN', arg1);
    if ((temp_s0 == NULL) || (temp_v0 == NULL)) {
        return;
    }
        
    _uvMediaCopy(temp_s0, temp_v0, sizeof(ParsedUVEN));
     
    if (temp_s0->unk44 != NULL) {
        temp_s0->unk44 = _uvMemAlloc(0x200U, 8U);
        _uvMediaCopy(temp_s0->unk44, temp_v0->unk44, 0x200U);
    }
}


void func_uvenv_rom_00402F00(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    ParsedUVEN *sp1C;
    ParsedUVEN *sp18;
    ParsedUVEN *temp_v0;
    f32 temp_fv1;
    f32 var_ft4;
    f32 var_fv0;


    if (arg3 == 0.0f) {
        func_uvenv_rom_00402E68(arg0, arg1);
        return;
    }
    if (arg3 == 1.0f) {
        func_uvenv_rom_00402E68(arg0, arg2);
        return;
    }
    sp1C = uvGetLoadedFile('UVEN', arg0);
    sp18 = uvGetLoadedFile('UVEN', arg1);
    temp_v0 = uvGetLoadedFile('UVEN', arg2);
    if ((sp1C == NULL) || (sp18 == NULL) || (temp_v0 == NULL)) {
        return;
    }

    temp_fv1 = 1.0f - arg3;
    sp1C->unk0 = ((sp18->unk0 * temp_fv1) + (temp_v0->unk0 * arg3));
    sp1C->unk1 = ((sp18->unk1 * temp_fv1) + (temp_v0->unk1 * arg3));
    sp1C->unk2 = ((sp18->unk2 * temp_fv1) + (temp_v0->unk2 * arg3));
    sp1C->unk3 = ((sp18->unk3 * temp_fv1) + (temp_v0->unk3 * arg3));
    sp1C->unk4 = ((sp18->unk4 * temp_fv1) + (temp_v0->unk4 * arg3));
    sp1C->unk5 = ((sp18->unk5 * temp_fv1) + (temp_v0->unk5 * arg3));
    sp1C->unk6 = ((sp18->unk6 * temp_fv1) + (temp_v0->unk6 * arg3));
    sp1C->unk7 = ((sp18->unk7 * temp_fv1) + (temp_v0->unk7 * arg3));
    sp1C->unk8 = ((sp18->unk8 * temp_fv1) + (temp_v0->unk8 * arg3));
    sp1C->unk9 = ((sp18->unk9 * temp_fv1) + (temp_v0->unk9 * arg3));
    sp1C->unkA = ((sp18->unkA * temp_fv1) + (temp_v0->unkA * arg3));
    sp1C->unkB = ((sp18->unkB * temp_fv1) + (temp_v0->unkB * arg3));
    sp1C->unk4C = (temp_v0->unk4C * arg3) + (sp18->unk4C * temp_fv1);
    sp1C->unk50 = (temp_v0->unk50 * arg3) + (sp18->unk50 * temp_fv1);
    sp1C->unk54 = (temp_v0->unk54 * arg3) + (sp18->unk54 * temp_fv1);
    sp1C->unk48 = (sp18->unk48 * temp_fv1) + (temp_v0->unk48 * arg3);
    sp1C->unk40 = (sp18->unk40 * temp_fv1) + (temp_v0->unk40 * arg3);
    if (sp18->unk3C == 0.0f) {
        var_ft4 = 1.0f;
    } else {
        var_ft4 = sp18->unk3C;
    }
    if (temp_v0->unk3C == 0.0f) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = temp_v0->unk3C;
    }
    sp1C->unk3C = (var_ft4 * temp_fv1) + (var_fv0 * arg3);
    if ((sp18->unk1D != 0) || (temp_v0->unk1D != 0)) {
        sp1C->unk1D = 1;
    } else {
        sp1C->unk1D = 0;
    }
    if ((sp18->unk1C != 0) || (temp_v0->unk1C != 0)) {
        sp1C->unk1C = 1;
    } else {
        sp1C->unk1C = 0;
    }
    if ((sp18->unk2E != 0) || (temp_v0->unk2E != 0)) {
        sp1C->unk2E = 1;
        return;
    }
    sp1C->unk2E = 0;
}

s32 func_uvenv_rom_00403AFC(s32 arg0) {
    if (D_uvenv_rom_00403C0C < arg0) {
        return -1;
    }
    return D_uvenv_rom_00403C08[arg0];
}

