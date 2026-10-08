// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"
#include "stdarg.h"

typedef struct UnkModel_Exports_s {
    /* 0x00 */ char pad0[0x1C];
    /* 0x1C */ s32 (*uvModelFindThresholdBand)(void *arg0, f32 arg1); /* inferred */
    /* 0x20 */ char pad20[0x30];                    /* maybe part of unk1C[0xD]? */
} UnkModel_Exports;                                 /* size = 0x50 */


void __entrypoint_func_uvenv_rom_400000(UvEnv_Exports *exports);
void uvEnvModuleCleanup(void);
void uvEnvBuildDepthFogLookup(f32 arg0, f32 arg1, u16 *arg2, ParsedUVEN *arg3);
void uvEnvProps(s32 envId, ...);
void uvEnvGetProps(s32 envId, ...);
void uvEnvSetLoadedRecordProperty(s32 fileId, s32 arg1, s32 arg2);
void uvEnvAttachDrawCallbacksToChannel(s32 arg0);
void uvEnvApplyDepthFogOverlay(s32 arg0);
void _uvEnvDraw(s32 arg0);
void uvEnvAssignFileToSlot(s32 arg0, s32 arg1);
void uvEnvCopyLoadedRecord(s32 arg0, s32 arg1);
void uvEnvBlendLoadedRecords(s32 arg0, s32 arg1, s32 arg2, f32 arg3);
s32 uvEnvGetAssignedFileId(s32 arg0);

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
    exports->uvEnvModuleCleanup = uvEnvModuleCleanup;
    exports->uvEnvBuildDepthFogLookup = uvEnvBuildDepthFogLookup;
    exports->uvEnvProps = uvEnvProps;
    exports->uvEnvGetProps = uvEnvGetProps;
    exports->uvEnvSetLoadedRecordProperty = uvEnvSetLoadedRecordProperty;
    exports->uvEnvAttachDrawCallbacksToChannel = uvEnvAttachDrawCallbacksToChannel;
    exports->uvEnvAssignFileToSlot = uvEnvAssignFileToSlot;
    exports->uvEnvCopyLoadedRecord = uvEnvCopyLoadedRecord;
    exports->uvEnvBlendLoadedRecords = uvEnvBlendLoadedRecords;
    exports->uvEnvGetAssignedFileId = uvEnvGetAssignedFileId;
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
    sUvChannel_Exports->uvChannelGetProperties(0, 0xD, &D_uvenv_rom_00403C0C, 0);
    D_uvenv_rom_00403C08 = _uvMemAllocAlign8(D_uvenv_rom_00403C0C * 4);
    for (i = 0; i < D_uvenv_rom_00403C0C; i++) {
        D_uvenv_rom_00403C08[i] = 0xFFFF;
    }
}

#line 15 "src/modules/uvenv_rom.c"
/* Release the environment assignment table, then unload FMTX, STAT,
 * GMGR, CHAN, CBCK and MODL in the existing order.
 * RE_UNKNOWN: initialization and single-owner cleanup remain caller contracts. */
void uvEnvModuleCleanup(void) {
    _uvMemFree(D_uvenv_rom_00403C08);
    uvUnloadModule('FMTX');
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
    uvUnloadModule('MODL');
}
#line 24 "src/modules/uvenv_rom.c"

#line 25 "src/modules/uvenv_rom.c"
/* Build the 256-entry, duplicated-byte intensity lookup used by the
 * depth-image fog overlay. Model flag two suppresses the final seven entries;
 * entries before the scaled start are zero and entries through 248 ramp.
 * RE_ORIGINAL_QUIRK: a zero ramp span becomes 1000000.0f.
 * RE_UNKNOWN: input ranges and flag semantics beyond this operation are unproved. */
void uvEnvBuildDepthFogLookup(f32 rampStart, f32 intensity, u16* lookup, ParsedUVEN* environment) {
    f32 rampValue;
    f32 tailValue;
    f32 rampSpan;
    s32 startIndex;
    s32 packedIntensity;
    s32 i;

    tailValue = 1.0f;
    for (i = 0; i < environment->modelCount; i++) {
        if (environment->modelTable[i].flag & 2) {
            tailValue = 0.0f;
        }
    }

    startIndex = (s32) (rampStart * 248.0f);
    rampSpan = (f32) (0xF8 - startIndex);
    if (rampSpan == 0.0f) {
        rampSpan = 1000000.0f;
    }

    for (i = 0; i < 256; i++) {
        if (i < startIndex) {
            rampValue = 0.0f;
        } else if (i < 0xF9) {
            rampValue = (i - startIndex) / rampSpan;
        } else {
            rampValue = tailValue;
        }
        packedIntensity = (s32) (rampValue * intensity * 255.0f);
        lookup[i] = ((packedIntensity << 8) | packedIntensity);
    }
}
#line 58 "src/modules/uvenv_rom.c"

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
                    sUvGfxStateExports->uvGfxSetFogParameters(temp_fa0, temp_fa1);
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
                        uvEnvBuildDepthFogLookup(temp_fa0, temp_fa1, var_a2, var_a3);
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

#line 261 "src/modules/uvenv_rom.c"
/* Set loaded environment word 0x38 for property zero or word 0x5C for
 * property one. A missing file or another property leaves data unchanged. */
void uvEnvSetLoadedRecordProperty(s32 fileId, s32 property, s32 value) {
    ParsedUVEN *parsedUvEnv;

    parsedUvEnv = uvGetLoadedFile('UVEN', fileId);
    if (parsedUvEnv == NULL) {
        return;
    }

    switch (property) {
        case 0:
            parsedUvEnv->unk38 = value;
            return;
        case 1:
            parsedUvEnv->unk5C = value;
            break;
    }
}
#line 278 "src/modules/uvenv_rom.c"

#line 279 "src/modules/uvenv_rom.c"
/* Query channel property six and attach the environment draw callbacks
 * at priorities 20 and 87 in their observed order. */
void uvEnvAttachDrawCallbacksToChannel(s32 channel) {
    CallbackList* callbackHost;

    sUvChannel_Exports->uvChannelGetProperties(channel, 6, &callbackHost, 0);
    sUvCbackExports->uvAddCallback(callbackHost, _uvEnvDraw, 0, 0x14);
    sUvCbackExports->uvAddCallback(callbackHost, uvEnvApplyDepthFogOverlay, 0, 0x57);
}
#line 286 "src/modules/uvenv_rom.c"

#line 287 "src/modules/uvenv_rom.c"
/* Apply the assigned environment lookup to the depth image using
 * three-row strips and the original fog-color blend commands. Skip disabled,
 * unassigned, missing and non-overlay environments; restore texture LUT and
 * shade-combine state afterward.
 * RE_UNKNOWN: slot validity and the fixed 320-pixel transfer geometry remain
 * existing renderer contracts; the hard-coded command values are preserved. */
void uvEnvApplyDepthFogOverlay(s32 slot) {
    ParsedUVEN *environment;
    s32 fileId;
    s32 screenHeight;
    Gfx **gdl;
    s32 screenWidth;
    s32 rowOffset;
    s32 sourceByteOffset;
    u16 *depthEnd;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    fileId = D_uvenv_rom_00403C08[slot];
    if (D_uvenv_rom_00403C00 != 0) {
        return;
    }

    screenHeight = sUvGfxMgrExports->uvGetScreenHeight();
    screenWidth = sUvGfxMgrExports->uvGetScreenWidth();
    if (fileId == 0xFFFF) {
        return;
    }

    environment = uvGetLoadedFile('UVEN', fileId);
    if ((environment == NULL) || (environment->unk1D == 0)) {
        return;
    }

    depthEnd = sUvGfxMgrExports->uvGfxGetDepthImageBuffer();
    sUvGfxStateExports->uvGfxSync();
    gSPTexture(gdl[0]++, 0xFFFF, 0xFFFF, 0, 1, G_ON);
    gDPSetTextureLOD(gdl[0]++, G_TL_TILE);
    gDPSetTextureFilter(gdl[0]++, G_TF_POINT);
    gDPSetTextureDetail(gdl[0]++, G_TD_CLAMP);
    gDPSetTexturePersp(gdl[0]++, G_TP_NONE);
    gDPSetTileSize(gdl[0]++, 1, 0, 0, 0x04FC, 0x0008);
    gDPSetTile(gdl[0]++, G_IM_FMT_IA, G_IM_SIZ_16b, 80, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, 2, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 9, G_TX_NOLOD);
    gDPSetCycleType(gdl[0]++, G_CYC_2CYCLE);
    gDPSetTextureImage(gdl[0]++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, OS_K0_TO_PHYSICAL(environment->unk44));
    gDPTileSync(gdl[0]++);
    gDPSetTile(gdl[0]++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0100, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(gdl[0]++);
    gDPLoadTLUTCmd(gdl[0]++, G_TX_LOADTILE, 255);
    gDPPipeSync(gdl[0]++);
    gDPSetTextureLUT(gdl[0]++, G_TT_IA16);
    gDPSetFogColor(gdl[0]++, environment->unk3, environment->unk4, environment->unk5, 255);
    gDPSetRenderMode(gdl[0]++, AA_EN | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | G_RM_PASS, AA_EN | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gDPSetCombineLERP(gdl[0]++, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetColorDither(gdl[0]++, G_CD_NOISE);
    gDPSetAlphaDither(gdl[0]++, G_AD_NOISE);
    gDPSetTile(gdl[0]++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 2, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 9, G_TX_NOLOD);



    depthEnd = &depthEnd[screenWidth * screenHeight];
    for (rowOffset = 0; rowOffset <= (screenHeight - 3); rowOffset += 3) {
        sourceByteOffset = screenWidth * 2 * (rowOffset + 3);
        gDPSetTextureImage(gdl[0]++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, (u32)depthEnd - sourceByteOffset);
        gDPLoadBlock(gdl[0]++, G_TX_LOADTILE, 0, 0, 959, 26);
        gSPTextureRectangle(gdl[0]++, 0, (screenHeight - 3 - rowOffset) << 2, 0x4FC, (screenHeight - rowOffset) << 2, 1, 0, 0, 0x400, 0x400);
    }
    gDPSetTextureLUT(gdl[0]++, G_TT_NONE);
    sUvGfxStateExports->uvGfxResetShadeCombineMode();
}
#line 350 "src/modules/uvenv_rom.c"

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

    sUvChannel_Exports->uvChannelGetProperties(arg0, 7, &sp1F8, 0);
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
            var_a0 = sUvModelExports->uvModelFindThresholdBand(parsedUvMD, SQ(var_fa1));
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
            sUvGfxStateExports->uvGfxSetFogParameters(sp214, sp210);
        } else {
            sUvGfxStateExports->uvGfxSetFogParameters(0.0f, 0.0f);
        }
        if (temp_s2 & 2) {
            sUvChannel_Exports->uvChannelGetProperties(arg0, 4, &sp1F4, &sp1F0, &sp1E8,
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
        sUvFmtxExports->uvMat4ApplySharedInverseTranslation(&spD4, &sp1A0);
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
    sUvGfxStateExports->uvGfxSetFogParameters(sp214, sp210);
    if (var_s6->unk38 != NULL) {
        var_s6->unk38();
    }
}

#line 546 "src/modules/uvenv_rom.c"
/* Assign a UVEN file to the environment slot, loading it on demand.
 * Convert -1 and failed loads to the existing 0xFFFF sentinel.
 * RE_ORIGINAL_QUIRK: retain the inclusive upper-bound comparison and low-word
 * sentinel test; this cleanup does not add range checks or unload old files.
 * RE_UNKNOWN: callers must provide an allocated slot; negative and count-equal
 * indices are not rejected by this body. */
void uvEnvAssignFileToSlot(s32 slot, s32 fileId) {
    if (D_uvenv_rom_00403C0C >= slot) {
        if (fileId == -1) {
            fileId = 0xFFFF;
        }
        if ((fileId & 0xFFFF) != 0xFFFF) {
            if (uvGetLoadedFile('UVEN', fileId) == NULL) {
                if (uvLoadFile('UVEN', fileId) == NULL) {
                    fileId = 0xFFFF;
                }
            }
        }
        D_uvenv_rom_00403C08[slot] = fileId;
    }
}
#line 561 "src/modules/uvenv_rom.c"


#line 563 "src/modules/uvenv_rom.c"
/* Copy one loaded UVEN record into another, returning if either is absent.
 * When the copied lookup pointer is non-null, allocate and copy its 512 bytes.
 * RE_UNKNOWN: replacement ownership and self-copy behavior are unproved;
 * preserve the record copy before lookup allocation and introduce no frees. */
void uvEnvCopyLoadedRecord(s32 destinationFileId, s32 sourceFileId) {
    ParsedUVEN* destination;
    ParsedUVEN* source;

    destination = uvGetLoadedFile('UVEN', destinationFileId);
    source = uvGetLoadedFile('UVEN', sourceFileId);
    if ((destination == NULL) || (source == NULL)) {
        return;
    }

    _uvMediaCopy(destination, source, sizeof(ParsedUVEN));

    if (destination->unk44 != NULL) {
        destination->unk44 = _uvMemAlloc(0x200U, 8U);
        _uvMediaCopy(destination->unk44, source->unk44, 0x200U);
    }
}
#line 580 "src/modules/uvenv_rom.c"


#line 582 "src/modules/uvenv_rom.c"
/* Blend the selected scalar and color fields of two loaded UVEN records.
 * Exact weights zero and one use the record-copy path. Replace a zero source
 * fog-start value by one before blending and combine the three enable fields
 * with logical OR, retaining the existing assignment order and conversions.
 * RE_UNKNOWN: complete record semantics, aliasing and weight range remain
 * caller contracts; fields not written here are deliberately left alone. */
void uvEnvBlendLoadedRecords(s32 destinationFileId, s32 firstFileId, s32 secondFileId, f32 secondWeight) {
    ParsedUVEN *destination;
    ParsedUVEN *first;
    ParsedUVEN *second;
    f32 firstWeight;
    f32 firstFogStart;
    f32 secondFogStart;


    if (secondWeight == 0.0f) {
        uvEnvCopyLoadedRecord(destinationFileId, firstFileId);
        return;
    }
    if (secondWeight == 1.0f) {
        uvEnvCopyLoadedRecord(destinationFileId, secondFileId);
        return;
    }
    destination = uvGetLoadedFile('UVEN', destinationFileId);
    first = uvGetLoadedFile('UVEN', firstFileId);
    second = uvGetLoadedFile('UVEN', secondFileId);
    if ((destination == NULL) || (first == NULL) || (second == NULL)) {
        return;
    }

    firstWeight = 1.0f - secondWeight;
    destination->unk0 = ((first->unk0 * firstWeight) + (second->unk0 * secondWeight));
    destination->unk1 = ((first->unk1 * firstWeight) + (second->unk1 * secondWeight));
    destination->unk2 = ((first->unk2 * firstWeight) + (second->unk2 * secondWeight));
    destination->unk3 = ((first->unk3 * firstWeight) + (second->unk3 * secondWeight));
    destination->unk4 = ((first->unk4 * firstWeight) + (second->unk4 * secondWeight));
    destination->unk5 = ((first->unk5 * firstWeight) + (second->unk5 * secondWeight));
    destination->unk6 = ((first->unk6 * firstWeight) + (second->unk6 * secondWeight));
    destination->unk7 = ((first->unk7 * firstWeight) + (second->unk7 * secondWeight));
    destination->unk8 = ((first->unk8 * firstWeight) + (second->unk8 * secondWeight));
    destination->unk9 = ((first->unk9 * firstWeight) + (second->unk9 * secondWeight));
    destination->unkA = ((first->unkA * firstWeight) + (second->unkA * secondWeight));
    destination->unkB = ((first->unkB * firstWeight) + (second->unkB * secondWeight));
    destination->unk4C = (second->unk4C * secondWeight) + (first->unk4C * firstWeight);
    destination->unk50 = (second->unk50 * secondWeight) + (first->unk50 * firstWeight);
    destination->unk54 = (second->unk54 * secondWeight) + (first->unk54 * firstWeight);
    destination->unk48 = (first->unk48 * firstWeight) + (second->unk48 * secondWeight);
    destination->unk40 = (first->unk40 * firstWeight) + (second->unk40 * secondWeight);
    if (first->unk3C == 0.0f) {
        firstFogStart = 1.0f;
    } else {
        firstFogStart = first->unk3C;
    }
    if (second->unk3C == 0.0f) {
        secondFogStart = 1.0f;
    } else {
        secondFogStart = second->unk3C;
    }
    destination->unk3C = (firstFogStart * firstWeight) + (secondFogStart * secondWeight);
    if ((first->unk1D != 0) || (second->unk1D != 0)) {
        destination->unk1D = 1;
    } else {
        destination->unk1D = 0;
    }
    if ((first->unk1C != 0) || (second->unk1C != 0)) {
        destination->unk1C = 1;
    } else {
        destination->unk1C = 0;
    }
    if ((first->unk2E != 0) || (second->unk2E != 0)) {
        destination->unk2E = 1;
        return;
    }
    destination->unk2E = 0;
}
#line 651 "src/modules/uvenv_rom.c"

#line 652 "src/modules/uvenv_rom.c"
/* Return the file identifier stored in the environment assignment table,
 * or -1 when the supplied slot is greater than the configured count.
 * RE_ORIGINAL_QUIRK: retain the inclusive upper-bound comparison.
 * RE_UNKNOWN: negative and count-equal slots require caller validation. */
s32 uvEnvGetAssignedFileId(s32 slot) {
    if (D_uvenv_rom_00403C0C < slot) {
        return -1;
    }
    return D_uvenv_rom_00403C08[slot];
}
#line 658 "src/modules/uvenv_rom.c"

