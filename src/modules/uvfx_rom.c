// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

#define FX_COUNT 10

typedef struct UnkStruct_uvfx_rom_00401120_s {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ char pad20[4];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ char pad46[2]; 
    /* 0x48 */ Mtx4F unk48;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s16 unk8C;
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ u8 unk8F; 
    /* 0x90 */ char pad90[4];
} UnkStruct_uvfx_rom_00401120; /* size = 0x94 */

typedef struct UnkTerraExports_s {
    /* 0x00 */ char pad0[0xAC];
    /* 0xAC */ void (*unkAC)(s32, s32, f32, f32, void (*)(s32, UnkStruct_uvfx_rom_00401120*), UnkStruct_uvfx_rom_00401120*, f32); /* inferred */
} UnkTerraExports;       

void __entrypoint_func_uvfx_rom_400000(UvFx_Exports *exports);
void uvFxAttachChannelCallback(s32 arg0);
void uvFxModuleCleanup(void);
void uvFxResetFrameCaches(s32 arg0);
u8 uvFxGetActiveKind(s32 arg0);
void uvFxSetMatrix(s32 arg0, Mtx4F *arg1);
void uvFxProps(s32 arg0, ...);
s32 uvFxModel(s32 arg0, s32 arg1);
void uvFxDrawTexturedQuad(u16 arg0);
void uvFxUpdateAndQueueVisible(s32 arg0);
void func_uvfx_rom_00400E90(s32 arg0, UnkStruct_uvfx_rom_00401120 *arg1);
s32 uvFxFindFreeSlot(s32 arg0);

// .data
s32 D_uvfx_rom_00401110[] = {0x001C0000, __entrypoint_func_uvfx_rom_400000, 0, 0};

// .bss
UnkStruct_uvfx_rom_00401120 D_uvfx_rom_00401120[FX_COUNT];
u8 D_uvfx_rom_004016E8;
static UvFMtx_Rom_Exports *sUvFMtxExports;
static UvImtx_Rom_Exports *sUvIMtxExports;
static UvMath_Exports *sUvMathExports;
static UvGfxMgr_Exports *sUvGfxMgrExports;
static UvGfxState_Rom_Exports *sUvGfxStateExports;
static UvDGeom_Rom_Exports *sUvDGeomExports;
static UvTSeq_Exports *sUvTextureSequenceExports;
static UvCback_Exports *sUvCbackExports;
static UvChannel_Exports *sUvChannel_Exports;
static UvIntersect_Exports *sUvIntersectExports;
static UnkTerraExports *sUvTerraExports;


void __entrypoint_func_uvfx_rom_400000(UvFx_Exports* exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->uvFxModel = uvFxModel;
    exports->uvFxModuleCleanup = uvFxModuleCleanup;
    exports->uvFxFindFreeSlot = uvFxFindFreeSlot;
    exports->uvFxAttachChannelCallback = uvFxAttachChannelCallback;
    exports->uvFxGetActiveKind = uvFxGetActiveKind;
    exports->uvFxSetMatrix = uvFxSetMatrix;
    exports->uvFxProps = uvFxProps;
#ifdef __sgi
    #line 84
#endif
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvGfxStateExports = uvLoadModule('STAT');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvChannel_Exports = uvLoadModule('CHAN');
    sUvFMtxExports = uvLoadModule('FMTX');
    sUvIMtxExports = uvLoadModule('IMTX');
    sUvMathExports = uvLoadModule('MATH');
    sUvDGeomExports = uvLoadModule('DGEO');
    sUvIntersectExports = uvLoadModule('ISCT');
    sUvTextureSequenceExports = uvLoadModule('TSEQ');
    sUvTerraExports = uvLoadModule('TERR');
    // clang-format off
    for (i = 0; i < FX_COUNT; i++) { D_uvfx_rom_00401120[i].unk8E = 0; }
    // clang-format on
    
    sUvCbackExports->uvAddCallback(sUvGfxMgrExports->uvGfxGetCallbackList(1), uvFxResetFrameCaches, 0, 0);
    D_uvfx_rom_004016E8 = 0;
}

#line 111 "src/modules/uvfx_rom.c"
/* Find channel property-six callback list and register the original
 * effect update/queue callback at priority 65. */
void uvFxAttachChannelCallback(s32 channel) {
    CallbackList *callbackList;

    sUvChannel_Exports->uvChannelGetProperties(channel, 6, &callbackList, 0);
    sUvCbackExports->uvAddCallback(callbackList, uvFxUpdateAndQueueVisible, 0, 0x41);
}
#line 117 "src/modules/uvfx_rom.c"

#line 118 "src/modules/uvfx_rom.c"
/* Unload all eleven original effect dependencies in order. */
void uvFxModuleCleanup(void) {
    uvUnloadModule('GMGR');
    uvUnloadModule('STAT');
    uvUnloadModule('CBCK');
    uvUnloadModule('CHAN');
    uvUnloadModule('FMTX');
    uvUnloadModule('IMTX');
    uvUnloadModule('MATH');
    uvUnloadModule('DGEO');
    uvUnloadModule('ISCT');
    uvUnloadModule('TSEQ');
    uvUnloadModule('TERR');
}
#line 131 "src/modules/uvfx_rom.c"

#line 132 "src/modules/uvfx_rom.c"
/* Clear each effect update flag and cached words at 0x88/0x8C.
 * The incoming callback context is unused. */
void uvFxResetFrameCaches(s32 context) {
    s32 i;
 
    for (i = 0; i < FX_COUNT; i++) {
        D_uvfx_rom_00401120[i].unk8F = 0;
        D_uvfx_rom_00401120[i].unk88 = 0;
        D_uvfx_rom_00401120[i].unk8C = 0;
    }
}
#line 141 "src/modules/uvfx_rom.c"

#line 142 "src/modules/uvfx_rom.c"
/* Return the active effect kind, or byte sentinel 255 for an inactive
 * slot. The original slot index is unchecked. */
u8 uvFxGetActiveKind(s32 index) {
    if (D_uvfx_rom_00401120[index].unk8E != 0) {
        return D_uvfx_rom_00401120[index].unk1;
    }
    return 0xFF;
}
#line 148 "src/modules/uvfx_rom.c"

#line 149 "src/modules/uvfx_rom.c"
/* Copy the matrix into an effect slot unless the index is sentinel 255.
 * Other indices retain the original caller-owned bounds. */
void uvFxSetMatrix(s32 index, Mtx4F *matrix) {
    if (index != 0xFF) {
        sUvFMtxExports->uvMat4FCopy(&D_uvfx_rom_00401120[index].unk48, matrix);
    }
}
#line 154 "src/modules/uvfx_rom.c"

void uvFxProps(s32 arg0, ...) {
    f32 var_fa0;
    f32 var_fv1;
    s16 temp_v0;
    UnkStruct_uvfx_rom_00401120 *var_a2;
    va_list args;

    if (arg0 == 0xFF) {
        return;
    }

    var_a2 = &D_uvfx_rom_00401120[arg0];
    va_start(args, arg0);
    while (TRUE) {
        temp_v0 = (s16)va_arg(args, s32);
        switch (temp_v0) {
            case 1:
                var_a2->unk4 = va_arg(args, f64);
                break;
            case 7:
                var_a2->unk3C = va_arg(args, f64);
                break;
            case 8:
                var_a2->unk40 = va_arg(args, s32);
                if (var_a2->unk40 != 0xFFF) {
                    if (uvGetLoadedFile('UVTX', var_a2->unk40) == NULL) {
                        var_a2->unk40 = 0xFFF;
                    }
                }
                break;
            case 3:
                var_a2->unk24 = va_arg(args, f64);
                var_a2->unk14 = var_a2->unk24 * 0.005f;
                var_a2->unk28 = va_arg(args, f64);
                var_a2->unk18 = var_a2->unk28 * 0.005f;
                var_a2->unk2C = va_arg(args, f64);
                var_a2->unk1C = var_a2->unk2C * 0.005f;
                if (var_a2->unk28 <  var_a2->unk24) {
                    var_fv1 =  var_a2->unk24;
                } else {
                    var_fv1 = var_a2->unk28;
                }
                if (var_fv1 < var_a2->unk2C) {
                    var_fa0 = var_a2->unk2C;
                } else {
                    var_fa0 = var_fv1;
                }
                var_a2->unk8 = var_fa0;
                break;
            case 11:
                var_a2->unk8E = va_arg(args, s32);
                break;
            case 21:
                D_uvfx_rom_004016E8 = va_arg(args, s32);
                break;
            case 0:
            default:
                return;
        }
    }
}

s32 uvFxModel(s32 arg0, s32 arg1) {
    UnkStruct_uvfx_rom_00401120 *temp_a3;

    if (arg0 == 0xFF) {
        return 0;
    }
    temp_a3 = &D_uvfx_rom_00401120[arg0];
    uvMemSet(temp_a3, 0U, 0x94U);
    temp_a3->unk1 = (s8) arg1;
    if (arg1 == 0xFF) {
        return 1;
    }
    temp_a3->unk42 = 0xFF;
    temp_a3->unk43 = 0xFF;
    temp_a3->unk44 = 0xFF;
    temp_a3->unk45 = 0xFF;
    temp_a3->unk2 = 0xFF;
    temp_a3->unk40 = 0xFFF;
    temp_a3->unk8E = 1;
    temp_a3->unk4 = 1.0f;
    temp_a3->unk24 = 1.0f;
    temp_a3->unk28 = 1.0f;
    temp_a3->unk2C = 1.0f;
    temp_a3->unk30 = 1.0f;
    temp_a3->unk34 = 1.0f;
    temp_a3->unk38 = 1.0f;
    temp_a3->unkC = 1.0f;
    temp_a3->unk3C = 1.0f;
    temp_a3->unk14 = 0.005f;
    temp_a3->unk18 = 0.005f;
    temp_a3->unk1C = 0.005f;
    temp_a3->unk8 = 0.5f;
    sUvFMtxExports->uvMat4SetIdentity(&temp_a3->unk48);
    switch (arg1) {
        case 6:
            temp_a3->unk0 = 2;
            temp_a3->unk4 = 100000000000000000000.0f;
            break;
        case 7:
            temp_a3->unk0 = 3;
            temp_a3->unk4 = 100000000000000000000.0f;
            break;
        default:
            return 0;
    }
    return 1;
}

#line 265 "src/modules/uvfx_rom.c"
/* Resolve the sequence/current texture, build original quad UVs, apply
 * effect scale and alpha, and submit/reuse four cached vertices. Preserve
 * sentinel texture behavior, missing-texture early return and view push/pop. */
void uvFxDrawTexturedQuad(u16 index) {
    u16 textureId;
    Mtx4F scaledMatrix;
    ParsedUVTX *texture;
    UnkStruct_uvfx_rom_00401120 *effect;
    u8 alpha;
    u16 coordinates[8];
    Mtx4F viewMatrix;

    effect = &D_uvfx_rom_00401120[index];
    if (effect->unk2 != 0xFF) {
        textureId = sUvTextureSequenceExports->uvTexSeqGetCurFrameTexture(effect->unk2);
    } else {
        if (effect->unk40 != 0xFFF) {
            textureId = effect->unk40;
        } else {
            textureId = 0xFFF;
        }
    }

    if (textureId != 0xFFF) {
        texture = uvGetLoadedFile('UVTX', textureId);
        if (texture != NULL) {
            sUvGfxStateExports->uvGfxStateBindTexture(textureId);
            coordinates[0] = 0;
            coordinates[1] = 0;
            coordinates[2] = texture->width << 5;
            coordinates[3] = 0;
            coordinates[4] = texture->width << 5;
            coordinates[5] = texture->height << 5;
            coordinates[6] = 0;
            coordinates[7] = texture->height << 5;

        } else {
            return;
        }
    } else {
        sUvGfxStateExports->uvGfxStateSetFlags(0xFFF);
        coordinates[0] = 0;
        coordinates[1] = 0;
        coordinates[2] = 0;
        coordinates[3] = 0;
        coordinates[4] = 0;
        coordinates[5] = 0;
        coordinates[6] = 0;
        coordinates[7] = 0;
    }
    sUvFMtxExports->uvMat4FCopy(&scaledMatrix, &effect->unk48);
    scaledMatrix.m[0][0] *= effect->unk14;
    scaledMatrix.m[0][1] *= effect->unk14;
    scaledMatrix.m[0][2] *= effect->unk14;
    scaledMatrix.m[2][0] *= effect->unk1C;
    scaledMatrix.m[2][1] *= effect->unk1C;
    scaledMatrix.m[2][2] *= effect->unk1C;

    alpha = effect->unk3C * effect->unk45;
    sUvFMtxExports->func_uvfmtx_rom_00400370(&viewMatrix, &scaledMatrix);
    sUvFMtxExports->uvGfxMtxViewLoad(&viewMatrix, 1U);
    sUvDGeomExports->uvVtxBeginPoly();
    if (effect->unk8C != 0) {
        sUvDGeomExports->func_uvdgeom_rom_00400424(effect->unk8C - 1, 4);
    } else {
        effect->unk8C = sUvDGeomExports->uvVtx(-0x64, 0, 0, coordinates[0], coordinates[1], effect->unk42,
                                                    effect->unk43, effect->unk44, alpha)
                         + 1;
        sUvDGeomExports->uvVtx(0x64, 0, 0, coordinates[2], coordinates[3], effect->unk42, effect->unk43,
                                   effect->unk44, alpha);
        sUvDGeomExports->uvVtx(0x64, 0, 0xC8, coordinates[4], coordinates[5], effect->unk42, effect->unk43,
                                   effect->unk44, alpha);
        sUvDGeomExports->uvVtx(-0x64, 0, 0xC8, coordinates[6], coordinates[7], effect->unk42, effect->unk43,
                                   effect->unk44, alpha);
    }
    sUvDGeomExports->uvVtxEndPoly();
    sUvFMtxExports->uvGfxMtxFViewPop();
}
#line 340 "src/modules/uvfx_rom.c"

#line 341 "src/modules/uvfx_rom.c"
/* Advance each active effect at most once per frame unless frozen,
 * expire it at its lifetime and queue visible effects through terrain.
 * Preserve original channel-relative distance and ordering. */
void uvFxUpdateAndQueueVisible(s32 channel) {
    UnkStruct_uvfx_rom_00401120 *effect;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 delta;
    s32 i;
    Mtx4F channelMatrix;

    sUvChannel_Exports->uvChannelGetProperties(channel, 3, &channelMatrix, 0);

    for (i = 0; i < FX_COUNT; i++) {
        effect = &D_uvfx_rom_00401120[i];
        if (effect->unk8E == 0) {
            continue;
        }
        if (effect->unk1 == 0xFF) {
            continue;
        }

        if ((effect->unk8F == 0) && (D_uvfx_rom_004016E8 == 0)) {
            delta = sUvGfxMgrExports->func_uvgfxmgr_rom_00401004();
            effect->unk8F = 1;
            if (!(delta == 0.0f)) {
                effect->unk10 += delta;
            }
            if (effect->unk4 <= effect->unk10) {
                effect->unk8E = 0;
                continue;
            } 
        }
        dx = effect->unk48.m[3][0] - channelMatrix.m[3][0];
        dy = effect->unk48.m[3][1] - channelMatrix.m[3][1];
        dz = effect->unk48.m[3][2] - channelMatrix.m[3][2];
        if (sUvChannel_Exports->func_uvchannel_rom_004014E8(channel, dx, dy, dz,
                                                             effect->unk8)
            != 0) {
            sUvTerraExports->unkAC(
                channel, 1, effect->unk48.m[3][0], effect->unk48.m[3][1], func_uvfx_rom_00400E90, effect,
                sUvMathExports->uvSqrtf(SQ(dx) + SQ(dy) + SQ(dz)));
        }        
    }
}
#line 384 "src/modules/uvfx_rom.c"

void func_uvfx_rom_00400E90(s32 arg0, UnkStruct_uvfx_rom_00401120 *arg1) {
    f32 temp_fv1;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 var_fa0;
    f32 temp;
    s32 pad;
    Mtx4F sp28;

    sUvGfxStateExports->uvGfxStatePush();
    sUvGfxStateExports->uvGfxStateSetFlags(0x04E20FFF);
    sUvGfxStateExports->func_uvgfxstate_rom_00401354(0x9B1C0000);
    sUvChannel_Exports->uvChannelGetProperties(arg0, 3, &sp28, 0);
    if (arg1->unk0 == 2) {
        temp_fv1 = arg1->unk48.m[3][0] - sp28.m[3][0];
        temp_fa1 = arg1->unk48.m[3][1] - sp28.m[3][1];
        temp_fv0 = sUvMathExports->uvSqrtf(SQ(temp_fv1) + SQ(temp_fa1));
        if (temp_fv0 != 0.0f) {
            var_fa0 = 1.0f / temp_fv0;
        } else {
            var_fa0 = 1.0f;
        }
        temp_fa1 *= var_fa0;
        temp_fv1 *= var_fa0;

        // FAKE
        temp++;
        temp--;

        arg1->unk48.m[0][0] = -temp_fa1;
        arg1->unk48.m[0][1] = temp_fv1;
        arg1->unk48.m[0][2] = 0.0f;
        arg1->unk48.m[1][0] = temp_fv1;
        arg1->unk48.m[1][1] = temp_fa1;
        arg1->unk48.m[1][2] = 0.0f;
        arg1->unk48.m[2][0] = 0.0f;
        arg1->unk48.m[2][1] = 0.0f;
        arg1->unk48.m[2][2] = 1.0f;
    } else if (arg1->unk0 == 3) {
        sUvFMtxExports->uvMat4CopyLinear3x3(&arg1->unk48, &sp28);
    }

    if ((arg1->unk1 == 6) || (arg1->unk1 == 7)) {
        uvFxDrawTexturedQuad(arg1 - D_uvfx_rom_00401120);
    }
    sUvGfxStateExports->uvGfxStatePop();
}

#line 433 "src/modules/uvfx_rom.c"
/* Return the first inactive effect slot or sentinel 255. Preserve the
 * unused incoming context and original unsigned-halfword scan. */
s32 uvFxFindFreeSlot(s32 context) {
    u16 i;

    for (i = 0; i < FX_COUNT; i++) {
        if (D_uvfx_rom_00401120[i].unk8E == 0) {
            return i;
        }
    }
    return 0xFF;
}
#line 443 "src/modules/uvfx_rom.c"
