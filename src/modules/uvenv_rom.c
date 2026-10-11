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

/*
 * Publish ten callbacks and two shared storage addresses, then load FMTX, STAT,
 * GMGR, CHAN, CBCK and MODL in that order. Query channel 0 property 0x0D,
 * allocate four bytes per returned count and fill each word with 0x0000FFFF.
 * Preserve the signed loop test and live count/base rereads on each iteration.
 * RE_UNKNOWN: Count bounds, allocation failure, reinitialization ownership and
 * export-storage lifetime remain external; no checks or cleanup are added.
 */
#line 43 "src/modules/uvenv_rom.c"
void __entrypoint_func_uvenv_rom_400000(UvEnv_Exports* exports) {
    s32 channelIndex;

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
    for (channelIndex = 0; channelIndex < D_uvenv_rom_00403C0C; channelIndex++) {
        D_uvenv_rom_00403C08[channelIndex] = 0xFFFF;
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

/* Apply a zero-terminated property stream to a loaded environment, preserving fog updates, lookup allocation and numeric conversions. */
#line 59 "src/modules/uvenv_rom.c"
void uvEnvProps(s32 envId, ...) {
    ParsedUVEN *environment;
    va_list args;
    s32 historicalUnusedPad; /* RE_UNKNOWN: retain unused storage; the historical declaration is unproved. */
    f32 firstControl;
    f32 secondControl;
    u32 property;
    void *lookup;

    environment = uvGetLoadedFile('UVEN', envId);

    if (environment == NULL) {
        return;
    }
    va_start(args, envId); /* RE_UNKNOWN: argument promotions, termination and caller storage domains need caller proof. */
    while (TRUE) {  
        property = va_arg(args, s32);
        switch (property) { /* Unsupported selectors consume only their selector and continue; selector 0 returns without va_end. */
            case 2:
                firstControl = va_arg(args, f64);
                secondControl = va_arg(args, f64);
                if (!(firstControl > 1.0f) && !(firstControl < 0.0f)) { /* RE_ORIGINAL_QUIRK: NaN bypasses both range comparisons; preserve the original guard. */
                    sUvGfxStateExports->uvGfxSetFogParameters(firstControl, secondControl); /* Keep this call before field writes; RE_UNKNOWN: environment/display-list storage aliases and lifetimes need caller proof. */
                    if ((firstControl == 0.0f) || (firstControl == 1.0f)) {
                        environment->unk1C = 0;
                    } else {
                        environment->unk1C = 1;
                        environment->unk1D = 0;
                        environment->unk3C = firstControl;
                        environment->unk40 = secondControl;
                    }
                }
                break;
            case 3:
                firstControl = va_arg(args, f64);
                secondControl = va_arg(args, f64);
                if (!(firstControl > 1.0f) && !(firstControl < 0.0f)) { /* RE_ORIGINAL_QUIRK: NaN bypasses both range comparisons; preserve the original guard. */
                    if ((firstControl != 0.0f) && (firstControl != 1.0f)) {
                        lookup = environment->unk44;
                        environment->unk3C = firstControl;
                        environment->unk40 = secondControl;
                        environment->unk1D = 1;
                        environment->unk1C = 0;
                        if (lookup == NULL) {
                            lookup = _uvMemAlloc(0x200U, 8U); /* RE_UNKNOWN: allocation success, ownership and lookup lifetime need allocator/caller proof; keep publication even on failure. */
                            environment->unk44 = lookup;
                        }
                        uvEnvBuildDepthFogLookup(firstControl, secondControl, lookup, environment);
                    } else {
                        environment->unk1D = 0;
                    }
                }
                break;
            case 5:
                environment->unkC = va_arg(args, f64) * 255.0; /* RE_UNKNOWN: finite/range and floating-point conversion contracts remain unproved; preserve byte narrowing. */
                environment->unkD = va_arg(args, f64) * 255.0;
                environment->unkE = va_arg(args, f64) * 255.0;
                break;
            case 1:
                environment->unk3 = va_arg(args, f64) * 255.0;
                environment->unk4 = va_arg(args, f64) * 255.0;
                environment->unk5 = va_arg(args, f64) * 255.0;
                break;
            case 4:
                environment->unkF = va_arg(args, f64) * 255.0;
                environment->unk10 = va_arg(args, f64) * 255.0;
                environment->unk11 = va_arg(args, f64) * 255.0;
                break;
            case 8:
                environment->unk6 = va_arg(args, f64) * 255.0;
                environment->unk7 = va_arg(args, f64) * 255.0;
                environment->unk8 = va_arg(args, f64) * 255.0;
                break;
            case 9:
                environment->unk9 = va_arg(args, f64) * 255.0;
                environment->unkA = va_arg(args, f64) * 255.0;
                environment->unkB = va_arg(args, f64) * 255.0;
                break;
            case 6:
                environment->unk4C = (u8)(va_arg(args, f64) * 255.0); /* Preserve double-to-byte quantization before storing the float field. */
                environment->unk50 = (u8)(va_arg(args, f64) * 255.0);
                environment->unk54 = (u8)(va_arg(args, f64) * 255.0);
                break;
            case 10:
                environment->unk0 = va_arg(args, f64) * 255.0;
                environment->unk1 = va_arg(args, f64) * 255.0;
                environment->unk2 = va_arg(args, f64) * 255.0;
                break;
            case 7:
                environment->unk48 = va_arg(args, f64);
                break;
            case 12:
                environment->unk58 = va_arg(args, s32); /* Preserve the byte store at +0x58. */
                break;
            case 13:
                environment->unk2E = va_arg(args, s32); /* Preserve the distinct byte store at +0x2E. */
                break;
            case 0:
                return;
       
        }
    }
}

/* Read environment properties into a zero-terminated output stream, preserving captured pairs, fresh model-table reads and duplicate selectors. */
#line 163 "src/modules/uvenv_rom.c"
void uvEnvGetProps(s32 envId, ...) {
    va_list args;
    ParsedUVEN *environment;
    f32 secondControl;
    f32 firstControl;
    s32 modelIndex;
    u32 property;
    s32 *modelIds;

    environment = uvGetLoadedFile('UVEN', envId);
    va_start(args, envId); /* RE_UNKNOWN: output capacities, aliasing, argument promotions and stream termination need caller proof. */
    if (environment == NULL) {
        PANIC; /* RE_ORIGINAL_QUIRK: a missing file reaches PANIC before return; preserve the original failure path. */
        return;
    }

    while (TRUE) {
        property = va_arg(args, s32);
        switch (property) { /* Unsupported selectors, including 13, consume only their selector and continue. */
            case 2:
                if (environment->unk1C != 0) { /* Capture both control values before sequential output stores; preserve possible output alias effects. */
                    firstControl = environment->unk3C;
                    secondControl = environment->unk40;
                } else {
                    firstControl = 0.0f;
                    secondControl = 0.0f;
                }
                *va_arg(args, f32*) = firstControl;
                *va_arg(args, f32*) = secondControl;
                break;
            case 3:
                if (environment->unk1D != 0) {
                    firstControl = environment->unk3C;
                    secondControl = environment->unk40;
                } else {
                    firstControl = 0.0f;
                    secondControl = 0.0f;
                }
                *va_arg(args, f32*) = firstControl;
                *va_arg(args, f32*) = secondControl;
                break;
            case 11:
                *va_arg(args, s32*) = environment->modelCount; /* Publish the count first, then freshly read the count/table during copying; RE_UNKNOWN: output extent and mutation domains need caller proof. */
                modelIds = va_arg(args, s32*); /* Copy each unsigned halfword model ID into a full output word. */
                for (modelIndex = 0; modelIndex < environment->modelCount; modelIndex++) {
                    modelIds[modelIndex] = environment->modelTable[modelIndex].modelId;
                }
                break;
            case 1:
                *va_arg(args, f32*) = environment->unk3 * 0.0039215684f;
                *va_arg(args, f32*) = (environment->unk4 * 0.0039215684f);
                *va_arg(args, f32*) = (environment->unk5 * 0.0039215684f);
                break;
            case 5:
                *va_arg(args, f32*) = environment->unkC * 0.0039215684f;
                *va_arg(args, f32*) = (environment->unkD * 0.0039215684f);
                *va_arg(args, f32*) = (environment->unkE * 0.0039215684f);
                break;
            case 4:
                *va_arg(args, f32*) = environment->unkF * 0.0039215684f;
                *va_arg(args, f32*) = (environment->unk10 * 0.0039215684f);
                *va_arg(args, f32*) = (environment->unk11 * 0.0039215684f);
                break;
            case 8:
                *va_arg(args, f32*) = environment->unk6 * 0.0039215684f;
                *va_arg(args, f32*) = (environment->unk7 * 0.0039215684f);
                *va_arg(args, f32*) = (environment->unk8 * 0.0039215684f);
                break;
            case 6:
                *va_arg(args, f32*) = environment->unk4C;
                *va_arg(args, f32*) = environment->unk50;
                *va_arg(args, f32*) = environment->unk54;
                break;
            case 9:
                *va_arg(args, f32*) = environment->unk9 * 0.0039215684f;
                *va_arg(args, f32*) = (environment->unkA * 0.0039215684f);
                *va_arg(args, f32*) = (environment->unkB * 0.0039215684f);
                break;
            case 10:
                *va_arg(args, f32*) = environment->unk0 * 0.0039215684f;
                *va_arg(args, f32*) = (environment->unk1 * 0.0039215684f);
                *va_arg(args, f32*) = (environment->unk2 * 0.0039215684f);
                break;
            case 7:
                *va_arg(args, f32*) = environment->unk48;
                break;
            case 12:
                *va_arg(args, s32*) = environment->unk58;
                break;
            case 14: /* RE_ORIGINAL_QUIRK: selectors 12 and 14 both read byte +0x58; keep the duplicate mapping. */
                *va_arg(args, s32*) = environment->unk58;
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
/*
 * Read channel property 6 into the local host, then register environment draw
 * at priority 0x14 followed by the depth/fog overlay at 0x57, each with zero
 * insertion argument. Reuse the same host output; neither lookup nor callback
 * registration result is checked. RE_UNKNOWN: Host lifetime, valid channel
 * and callback teardown order remain provider/caller obligations.
 */
#line 281 "src/modules/uvenv_rom.c"
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

/* Draw the environment assigned to a channel using model flags, threshold bands, temporary matrices and saved graphics-state words. */
#line 351 "src/modules/uvenv_rom.c"
void _uvEnvDraw(s32 channel) {
    ParsedUVMD *model;
    ParsedUVEN *environment;
    f32 secondSideGap;
    f32 reciprocalWord10;
    f32 firstSideGap;
    u8 modelFlags;
    f32 fogFirstControl;
    f32 fogSecondControl;
    Gfx **displayList;
    f32 axisGap;
    s32 environmentFileId;
    Vec3F channelVector;
    f32 projectionInput0;
    f32 projectionInput1;
    f32 projectionInput3;
    f32 projectionInput2;
    f32 projectionInput4;
    f32 unusedProjectionInput5;
    Mtx4F modelMatrix;
    Mtx4F channelMatrix;
    Mtx4F projectionMatrix;
    s32 requestedModelCount;
    s32 bandIndex;
    s32 filledBackground;
    Mtx4F translatedMatrix;
    uvModelLOD *lod;
    s32 modelIndex;
    s32 lodOrStateIndex;

    displayList = sUvGfxMgrExports->uvGetDisplayListHead(); /* RE_UNKNOWN: display-list capacity, ownership and lifetime need producer/caller proof. */
    environmentFileId = D_uvenv_rom_00403C08[channel]; /* RE_ORIGINAL_QUIRK: read the assignment before the upper-bound check; RE_UNKNOWN: negative/index domains need caller proof. */
    filledBackground = 0;
    if (D_uvenv_rom_00403C04 != 0) { /* The disabled path fills black and returns before checking the channel bound. */
        sUvGfxMgrExports->uvGfxFillRect(0U, 0U, 0U);
        return;
    }
    if (channel >= D_uvenv_rom_00403C0C) {
        return;
    }

    sUvChannel_Exports->uvChannelGetProperties(channel, 7, &channelVector, 0);
    if (environmentFileId == 0xFFFF) {
        environment = NULL;
    } else {
        environment = uvGetLoadedFile('UVEN', environmentFileId);
    }
    if (environment == NULL) {
        return;
    }

    if (environment->unk5C != NULL) {
        environment->unk5C(); /* RE_UNKNOWN: callback mutation/reentry and imported-file lifetime remain unproved; reload fields after the call. */
    }
    
    if (environment->unk1C != 0) {
        fogFirstControl = environment->unk3C;
        fogSecondControl = environment->unk40;
    } else {
        fogFirstControl = 0.0f;
        fogSecondControl = 0.0f;
    }
    if (environment->unk2E != 0) {
        sUvGfxMgrExports->uvGfxFillRect(environment->unk0, environment->unk1, environment->unk2);
        filledBackground = 1;
    }

    gDPSetFogColor(displayList[0]++, environment->unk3, environment->unk4, environment->unk5, 0xFF);
    if (environment->unk58 != 0) {
        requestedModelCount = environment->modelCount;
    } else {
        requestedModelCount = 0;
    }

    for (modelIndex = 0; modelIndex != requestedModelCount; modelIndex++) { /* Use the captured byte count; RE_UNKNOWN: model-table extent and count domains need producer/caller proof. */
        if (modelIndex == 0) {
            gSPClipRatio(displayList[0]++, FRUSTRATIO_1);
        }
        model = uvGetLoadedFile('UVMD', environment->modelTable[modelIndex].modelId);
        if (model == NULL) { /* RE_ORIGINAL_QUIRK: missing model returns before fog restoration and the post-draw callback. */
            return;
        }

        modelFlags = environment->modelTable[modelIndex].flag;
        if ((modelFlags & 2) && (environment->unk40 > 0.95) && (environment->unk1D != 0)) {
            if (filledBackground == 0) {
                sUvGfxMgrExports->uvGfxFillRect(environment->unk3, environment->unk4, environment->unk5);
                filledBackground = 1;
            }
            continue;
        }
        
        bandIndex = 0;
        if (model->unk4 >= 2) {
            uvModelLOD_inner bounds; /* RE_UNKNOWN: bounds stay uninitialized if no populated band exists; prove that domain from assets/callers. */
            f32 maximumGap;
            maximumGap = 0.0f;
            for (lodOrStateIndex = 0; lodOrStateIndex < model->unk4; lodOrStateIndex++) {
                if ((model->unk0[lodOrStateIndex].unk0)->unk4 == 0) {
                    continue;
                }
                bounds = (model->unk0[lodOrStateIndex].unk0)->unk8;
                break;
            }
            firstSideGap = bounds.unk0 - channelVector.x;
            secondSideGap = channelVector.x - bounds.unkC;
            if (firstSideGap < secondSideGap) {
                axisGap = secondSideGap;
            } else {
                axisGap = firstSideGap;
            }
            firstSideGap = bounds.unk4 - channelVector.y;
            secondSideGap = channelVector.y - bounds.unk10;
            if (axisGap > 0.0f) {
                maximumGap = axisGap;
            }
            if (firstSideGap < secondSideGap) {
                axisGap = secondSideGap;
            } else {
                axisGap = firstSideGap;
            }
            if (maximumGap < axisGap) {
                maximumGap = axisGap;
            }
            firstSideGap = bounds.unk8 - channelVector.z;
            secondSideGap = channelVector.z - bounds.unk14;
            if (firstSideGap < secondSideGap) {
                axisGap = secondSideGap;
            } else {
                axisGap = firstSideGap;
            }
            if (maximumGap < axisGap) {
                maximumGap = axisGap;
            }
            bandIndex = sUvModelExports->uvModelFindThresholdBand(model, SQ(maximumGap)); /* Preserve per-axis comparison grouping and the squared threshold input; no distance convention is inferred. */
            if (bandIndex == 0xFF) {
                continue;
            }
             // RE_UNKNOWN: retain the no-op matching scaffold; historical source form is unproved.
            if (1) {} 
        } else {
            lodOrStateIndex = 1; /* RE_UNKNOWN: retain the historical matching assignment even though the next drawing loop resets this local. */
        }
        
        lod = model->unk0[bandIndex].unk0;
        if (modelFlags & 4) {
            sUvGfxStateExports->uvGfxSetFogParameters(fogFirstControl, fogSecondControl);
        } else {
            sUvGfxStateExports->uvGfxSetFogParameters(0.0f, 0.0f);
        }
        if (modelFlags & 2) {
            sUvChannel_Exports->uvChannelGetProperties(channel, 4, &projectionInput0, &projectionInput1, &projectionInput2,
                                                              &projectionInput3, &projectionInput4, &unusedProjectionInput5, 1, &channelMatrix, 0); /* Consume all six scalar outputs and the matrix; the sixth scalar remains unused. */
            sUvFmtxExports->uvMat4BuildPerspectiveProjection(&projectionMatrix, projectionInput0, projectionInput1, projectionInput2, projectionInput3, projectionInput4,
                                                27000.0f);
            sUvFmtxExports->uvGfxMtxProjPushF(&projectionMatrix);
            if (environment->unk1D != 0) {
                gDPSetEnvColor(displayList[0]++, environment->unk3, environment->unk4, environment->unk5, (u8)(255.0f * environment->unk40));
            } else {
                gDPSetEnvColor(displayList[0]++, environment->unk3, environment->unk4, environment->unk5, 0);
            }
        }
        sUvFmtxExports->uvMat4SetIdentity(&modelMatrix);
        if (modelFlags & 8) {
            modelMatrix.m[3][0] = channelVector.x;
            modelMatrix.m[3][1] = channelVector.y; /* Only X/Y translation is written here; RE_UNKNOWN: coordinate and matrix conventions need caller proof. */
        }
        reciprocalWord10 = 1.0f / model->unk10; /* RE_UNKNOWN: zero/nonfinite values and floating-point contracts need asset/caller proof; preserve reciprocal and store order. */
        modelMatrix.m[2][2] = reciprocalWord10;
        modelMatrix.m[1][1] = reciprocalWord10;
        modelMatrix.m[0][0] = reciprocalWord10;
        sUvFmtxExports->uvMat4ApplySharedInverseTranslation(&translatedMatrix, &modelMatrix);
        sUvFmtxExports->uvGfxMtxViewLoad(&translatedMatrix, 3);
        for (lodOrStateIndex = 0; lodOrStateIndex < (u32)lod->unk4; lodOrStateIndex++) {
            int savedState = lod->stateTable[lodOrStateIndex].state;
            if (!(modelFlags & 1)) {
                lod->stateTable[lodOrStateIndex].state &= ~0x200000;
            }
            if (modelFlags & 0x10) {
                lod->stateTable[lodOrStateIndex].state &= ~0x400000;
            }
            sUvGfxStateExports->uvGfxStateDraw(&lod->stateTable[lodOrStateIndex]); /* RE_UNKNOWN: callback mutation and state-table lifetime remain unproved; reload the table before restoring its saved word. */
            lod->stateTable[lodOrStateIndex].state = savedState;
        }
        if (modelFlags & 2) {
            sUvFmtxExports->uvGfxMtxProjPushF(&channelMatrix);
        }
        sUvFmtxExports->uvGfxMtxFViewPop();
    }
    sUvGfxStateExports->uvGfxSetFogParameters(fogFirstControl, fogSecondControl);
    if (environment->unk38 != NULL) {
        environment->unk38(); /* This callback follows normal fog restoration; early returns above bypass it. */
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

