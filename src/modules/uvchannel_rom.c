// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef struct UnkStruct_uvchannel_rom_00401CD0_s {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unused;
    /* 0x004 */ Mtx4F unk4;
    /* 0x044 */ Mtx4F unk44;
    /* 0x084 */ Mtx4F unk84;
    /* 0x0C4 */ Vec3F unkC4;
    /* 0x0D0 */ Vec3F unkD0;
    /* 0x0DC */ f32 unkDC;
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ f32 unkE4;
    /* 0x0E8 */ f32 unkE8;
    /* 0x0EC */ f32 unkEC;
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ Vec3F unkF4[6];
    /* 0x13C */ Vec3F unk13C[6];
    /* 0x184 */ Vec3F unk184[4];
    /* 0x1B4 */ Vec3F unk1B4[2];
    /* 0x1CC */ Vec3F unk1CC[6];
    /* 0x214 */ u16 unk214;
    /* 0x216 */ u16 unk216;
    /* 0x218 */ u16 unk218;
    /* 0x21A */ u16 unk21A;
    /* 0x21C */ s32 unk21C;
    /* 0x220 */ CallbackRoutine unk220;
    /* 0x224 */ CallbackRoutine unk224;
} UnkStruct_uvchannel_rom_00401CD0; /* size = 0x228 */

void uvChannelModuleCleanup(void);
void uvChannelGetProperties(s32 arg0, ...);
void uvChannelSetProperties(s32 arg0, ...);
void uvChannelSetFlags(s32 arg0, s32 arg1);
void uvChannelSetFrustum(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void uvChannelSetViewport(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void uvChannelSetBoundaryCallback(s32 arg0, s32 arg1, CallbackRoutine arg2);
s32 func_uvchannel_rom_00400CCC(void);
void uvChannelRelease(s32 arg0);
void uvChannelApplyClipRatio(s32 arg0);
void uvChannelRender(s32 arg0);
void uvChannelSetViewMatrix(s32 arg0, Mtx4F *arg1);
s32 func_uvchannel_rom_004014E8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_uvchannel_rom_00401658(s32 arg0);
void uvChannelBeginDebugFrustum(s32 arg0);
void uvChannelDrawDebugFrustum(s32 arg0);
void __entrypoint_func_uvchannel_rom_400000(UvChannel_Exports *exports);

// .data
s32 D_uvchannel_rom_00401CC0[] = { 0x00300000, __entrypoint_func_uvchannel_rom_400000, 0, 0 };

// .bss
UnkStruct_uvchannel_rom_00401CD0 *D_uvchannel_rom_00401CD0;
s32 D_uvchannel_rom_00401CD4;
s32 D_uvchannel_rom_00401CD8;
static UvCback_Exports *sUvCbackExports;
static UvFMtx_Rom_Exports *sUvFmtxExports;
static UvFVec_Rom_Exports *sUvFvecExports;
static UvMath_Exports *sUvMathExports;
static UvGfxMgr_Exports *sUvGfxMgrExports;
static UvGfxState_Rom_Exports *sUvGfxStateExports;
static UvDGeom_Rom_Exports *sUvDGeomExports;
static UvGeom_Exports *sUvGeomExports;

void __entrypoint_func_uvchannel_rom_400000(UvChannel_Exports *exports) {
    s32 *channelCount;

    uvUpdateFileAllocPtr(exports);
    exports->uvChannelModuleCleanup = uvChannelModuleCleanup;
    exports->uvChannelSetViewMatrix = uvChannelSetViewMatrix;
    exports->uvChannelGetProperties = uvChannelGetProperties;
    exports->func_uvchannel_rom_004014E8 = func_uvchannel_rom_004014E8;
    exports->uvChannelSetProperties = uvChannelSetProperties;
    exports->uvChannelSetFlags = uvChannelSetFlags;
    exports->uvChannelSetFrustum = uvChannelSetFrustum;
    exports->uvChannelSetViewport = uvChannelSetViewport;
    exports->uvChannelSetBoundaryCallback = uvChannelSetBoundaryCallback;
    exports->func_uvchannel_rom_00400CCC = func_uvchannel_rom_00400CCC;
    exports->uvChannelRelease = uvChannelRelease;
    exports->uvChannelRender = uvChannelRender;
#ifdef __sgi
#line 74
#endif
    sUvCbackExports = uvLoadModule('CBCK');
    sUvMathExports = uvLoadModule('MATH');
    sUvFvecExports = uvLoadModule('FVEC');
    sUvFmtxExports = uvLoadModule('FMTX');
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvGfxStateExports = uvLoadModule('STAT');
    sUvDGeomExports = uvLoadModule('DGEO');
    sUvGeomExports = uvLoadModule('GEOM');
    channelCount = uvGetSystemProp(SYSTEM_PROPID_CHANNEL_SETTINGS);
    if (channelCount != NULL) {
        D_uvchannel_rom_00401CD4 = *channelCount;
    } else {
        D_uvchannel_rom_00401CD4 = 4;
    }
    D_uvchannel_rom_00401CD0 =
        _uvMemAllocAlign8(D_uvchannel_rom_00401CD4 * sizeof(UnkStruct_uvchannel_rom_00401CD0));
    uvMemSet(D_uvchannel_rom_00401CD0, 0,
             D_uvchannel_rom_00401CD4 * sizeof(UnkStruct_uvchannel_rom_00401CD0));
    D_uvchannel_rom_00401CD8 = 0;
}

#line 96 "src/modules/uvchannel_rom.c"
/* Unload and clear channel dependencies in original order. */
void uvChannelModuleCleanup(void) {
    uvUnloadModule('CBCK');
    sUvCbackExports = NULL;
    uvUnloadModule('MATH');
    sUvMathExports = NULL;
    uvUnloadModule('FVEC');
    sUvFvecExports = NULL;
    uvUnloadModule('FMTX');
    sUvFmtxExports = NULL;
    uvUnloadModule('GMGR');
    sUvGfxMgrExports = NULL;
    uvUnloadModule('STAT');
    sUvGfxStateExports = NULL;
    uvUnloadModule('DGEO');
    sUvDGeomExports = NULL;
    uvUnloadModule('GEOM');
    sUvGeomExports = NULL;
}
#line 114 "src/modules/uvchannel_rom.c"

#line 115 "src/modules/uvchannel_rom.c"
/* Read property/output pairs until zero, after the original channel-range guard.
 * Copy scalar/matrix/vector data or expose the four vector-array addresses.
 * RE_UNKNOWN: output extents/types, termination and array lifetime need callers/producers. */
void uvChannelGetProperties(s32 channel, ...) {
    UnkStruct_uvchannel_rom_00401CD0 *state;
    int property;
    va_list args;
    void *output;

    if ((channel < 0) || (channel >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    va_start(args, channel);
    state = &D_uvchannel_rom_00401CD0[channel];
    while ((property = va_arg(args, s32)) != 0) {
        switch (property) {
            case 1:
                sUvFmtxExports->uvMat4FCopy(va_arg(args, Mtx4F *), &state->unk4);
                break;
            case 2:
                sUvFmtxExports->uvMat4FCopy(va_arg(args, Mtx4F *), &state->unk84);
                break;
            case 3:
                sUvFmtxExports->uvMat4FCopy(va_arg(args, Mtx4F *), &state->unk44);
                break;
            case 4:
                *(f32 *) (output = va_arg(args, f32 *)) = state->unkDC;
                *(f32 *) (output = va_arg(args, f32 *)) = state->unkE0;
                *(f32 *) (output = va_arg(args, f32 *)) = state->unkE4;
                *(f32 *) (output = va_arg(args, f32 *)) = state->unkE8;
                *(f32 *) (output = va_arg(args, f32 *)) = state->unkEC;
                *(f32 *) (output = va_arg(args, f32 *)) = state->unkF0;
                break;
            case 5:
                *(s32 *) (output = va_arg(args, s32 *)) = state->unk214;
                *(s32 *) (output = va_arg(args, s32 *)) = state->unk216;
                *(s32 *) (output = va_arg(args, s32 *)) = state->unk218;
                *(s32 *) (output = va_arg(args, s32 *)) = state->unk21A;
                break;
            case 6:
                *(s32 *) (output = va_arg(args, s32 *)) = state->unk21C;
                break;
            case 7:
                sUvFvecExports->uvVec3FCopy(va_arg(args, Vec3F *), &state->unkC4);
                break;
            case 8:
                sUvFvecExports->uvVec3FCopy(va_arg(args, Vec3F *), &state->unkD0);
                break;
            case 9:
                *(Vec3F **) (output = va_arg(args, Vec3F **)) = state->unkF4;
                break;
            case 10:
                *(Vec3F **) (output = va_arg(args, Vec3F **)) = state->unk13C;
                break;
            case 11:
                *(Vec3F **) (output = va_arg(args, Vec3F **)) = state->unk184;
                break;
            case 12:
                *(Vec3F **) (output = va_arg(args, Vec3F **)) = state->unk1CC;
                break;
            case 14:
                *(s32 *) (output = va_arg(args, s32 *)) = state->unk1;
                break;
            case 13:
                *(s32 *) (output = va_arg(args, s32 *)) = D_uvchannel_rom_00401CD4;
                break;
        }
    }
}
#line 182 "src/modules/uvchannel_rom.c"

#line 183 "src/modules/uvchannel_rom.c"
/* Apply zero-terminated channel properties, rebuild the projection/frustum
 * when required and add/remove debug callbacks. Preserve by-value matrix
 * varargs on IDO, promoted doubles, flag truncation and original tag handling. */
void uvChannelSetProperties(s32 channel, ...) {
    UnkStruct_uvchannel_rom_00401CD0 *state;
    s32 enabled;
    va_list args;
    CallbackList *callbacks;
    int property;

    if ((channel < 0) || (channel >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    va_start(args, channel);
    state = &D_uvchannel_rom_00401CD0[channel];
    while ((property = va_arg(args, s32)) != 0) {
        switch (property) {
#ifdef __sgi
            case 1:
                sUvFmtxExports->uvMat4FCopy(&state->unk4, &va_arg(args, Mtx4F));
                break;
            case 2:
                sUvFmtxExports->uvMat4FCopy(&state->unk84, &va_arg(args, Mtx4F));
                break;
            case 3:
                sUvFmtxExports->uvMat4FCopy(&state->unk44, &va_arg(args, Mtx4F));
                break;
#endif
            case 4:
                state->unkDC = va_arg(args, f64);
                state->unkE0 = va_arg(args, f64);
                state->unkE4 = va_arg(args, f64);
                state->unkE8 = va_arg(args, f64);
                state->unkEC = va_arg(args, f64);
                state->unkF0 = va_arg(args, f64);
                sUvFmtxExports->func_uvfmtx_rom_00401F74(&state->unk4, state->unkDC, state->unkE0,
                                                         state->unkE4, state->unkE8, state->unkEC,
                                                         state->unkF0);
                func_uvchannel_rom_00401658(channel);
                break;
            case 5:
                state->unk214 = va_arg(args, s32);
                state->unk216 = va_arg(args, s32);
                state->unk218 = va_arg(args, s32);
                state->unk21A = va_arg(args, s32);
                break;
            case 15:
                state->unk2 = va_arg(args, s32);
                if (state->unk2 >= 7) {
                    state->unk2 = 6;
                }
                if (state->unk2 <= 0) {
                    state->unk2 = 1;
                }
                break;
            case 14:
                state->unk1 = va_arg(args, s32);
                break;
            case 16:
                uvChannelGetProperties(channel, 6, &callbacks, 0);
                enabled = va_arg(args, s32);
                if (callbacks != NULL) {
                    if ((D_uvchannel_rom_00401CD8 == 0) && (enabled != 0)) {
                        sUvCbackExports->uvAddCallback(callbacks, uvChannelBeginDebugFrustum, 0, 0x19);
                        sUvCbackExports->uvAddCallback(callbacks, uvChannelDrawDebugFrustum, 0, 0xFA);
                    } else if ((D_uvchannel_rom_00401CD8 != 0) && (enabled == 0)) {
                        sUvCbackExports->uvRemoveCallback(callbacks, uvChannelBeginDebugFrustum);
                        sUvCbackExports->uvRemoveCallback(callbacks, uvChannelDrawDebugFrustum);
                    }
                    D_uvchannel_rom_00401CD8 = enabled;
                }
                break;
        }
    }
}
#line 256 "src/modules/uvchannel_rom.c"

#line 257 "src/modules/uvchannel_rom.c"
/* Set original channel property 14 through the shared property setter. */
void uvChannelSetFlags(s32 channel, s32 flags) {
    uvChannelSetProperties(channel, 0xE, flags, 0);
}
#line 260 "src/modules/uvchannel_rom.c"

#line 261 "src/modules/uvchannel_rom.c"
/* Set left/right/bottom/top/near/far projection values through property
 * four with the original double promotions and argument order. */
void uvChannelSetFrustum(s32 channel, f32 left, f32 right, f32 bottom, f32 top, f32 nearPlane, f32 farPlane) {
    uvChannelSetProperties(channel, 4, (f64) left, (f64) right, (f64) bottom, (f64) top, (f64) nearPlane,
                                (f64) farPlane, 0);
}
#line 265 "src/modules/uvchannel_rom.c"

#line 266 "src/modules/uvchannel_rom.c"
/* Store the original four viewport edges through property five,
 * retaining signed-halfword truncation in the setter. */
void uvChannelSetViewport(s32 channel, s32 left, s32 right, s32 top, s32 bottom) {
    uvChannelSetProperties(channel, 5, left, right, top, bottom, 0);
}
#line 269 "src/modules/uvchannel_rom.c"

#line 270 "src/modules/uvchannel_rom.c"
/* For boundary zero or one, add a supplied callback at priority 1 or
 * 255, or remove the recorded callback for a null routine. Preserve the
 * original replacement behavior and unchecked channel index. */
void uvChannelSetBoundaryCallback(s32 channel, s32 boundary, CallbackRoutine callback) {
    UnkStruct_uvchannel_rom_00401CD0 *state;

    state = &D_uvchannel_rom_00401CD0[channel];
    switch (boundary) { /* irregular */
        case 0:
            if (callback != 0) {
                sUvCbackExports->uvAddCallback((CallbackList *) state->unk21C, callback, NULL, 1);
                state->unk220 = callback;
                return;
            }
            if (state->unk220 != 0) {
                sUvCbackExports->uvRemoveCallback((CallbackList *) state->unk21C, state->unk220);
                state->unk220 = 0;
                return;
            }
            return;
        case 1:
            if (callback != 0) {
                sUvCbackExports->uvAddCallback((CallbackList *) state->unk21C, callback, 0, 0xFF);
                state->unk224 = callback;
                return;
            }
            if (state->unk224 != 0) {
                sUvCbackExports->uvRemoveCallback((CallbackList *) state->unk21C, state->unk224);
                state->unk224 = 0;
            }
            break;
    }
}
#line 300 "src/modules/uvchannel_rom.c"

s32 func_uvchannel_rom_00400CCC(void) {
    s32 *sp20;
    s32 var_a0_2;
    s32 *temp_v0;
    UnkStruct_uvchannel_rom_00401CD0 *var_s1;
    s32 i;

    var_s1 = NULL;
    temp_v0 = uvGetSystemProp(SYSTEM_PROPID_CHANNEL_SETTINGS);
    for (i = 0; i < D_uvchannel_rom_00401CD4; i++) {
        if (!(D_uvchannel_rom_00401CD0[i].unk0 & 1)) {
            D_uvchannel_rom_00401CD0[i].unk0 = 1;
            var_s1 = &D_uvchannel_rom_00401CD0[i];
            break;
        }
    }

    if (var_s1 == NULL) {
        return -1;
    }
    if (temp_v0 != NULL) {
        var_a0_2 = temp_v0[1];
    } else {
        var_a0_2 = 0x14;
    }
    var_s1->unk21C = sUvCbackExports->uvCreateCallbackList(var_a0_2);
    var_s1->unk214 = 0;
    var_s1->unk216 = (s16) (sUvGfxMgrExports->uvGetScreenWidth() - 1);
    var_s1->unk218 = 0;
    var_s1->unk21A = (s16) (sUvGfxMgrExports->uvGetScreenHeight() - 1);
    var_s1->unk2 = 2;
    sUvFmtxExports->uvMat4SetIdentity(&var_s1->unk84);
    sUvFmtxExports->uvMat4SetIdentity(&var_s1->unk44);
    sUvFmtxExports->uvMat4SetIdentity(&var_s1->unk4);
    // TODO: Find a better match
    var_a0_2 = var_s1->unk21C;
    if (var_a0_2 == NULL) {
        var_s1->unk1 = 0;
        var_a0_2 = *(void **) 0x21C;
        var_s1 = NULL;
    }
    sUvCbackExports->uvAddCallback(var_a0_2, (s32) &uvChannelApplyClipRatio, 0, 0x1E);
    sUvCbackExports->uvAddCallback(var_s1->unk21C, (s32) &uvChannelApplyClipRatio, 0, 0xC8);
    return i;
}

#line 347 "src/modules/uvchannel_rom.c"
/* For a valid signed channel index, clear active flags and free the
 * callback list when present, then clear its pointer. */
void uvChannelRelease(s32 channel) {
    UnkStruct_uvchannel_rom_00401CD0 *state;
    s32 callbacks;

    if ((channel < 0) || (channel >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    state = &D_uvchannel_rom_00401CD0[channel];
    callbacks = state->unk21C;
    state->unk1 = 0;
    state->unk0 = 0;
    if (callbacks != 0) {
        sUvCbackExports->uvCallbackFree((void *) callbacks);
        state->unk21C = 0;
    }
}
#line 364 "src/modules/uvchannel_rom.c"

#line 365 "src/modules/uvchannel_rom.c"
/* Reset the original graphics state and emit the configured clip ratio
 * for values one through six. Other values emit no ratio command. */
void uvChannelApplyClipRatio(s32 channel) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    sUvGfxStateExports->uvGfxResetDefaultRenderState();
    switch (D_uvchannel_rom_00401CD0[channel].unk2) {
        case 1:
            gSPClipRatio(gdl[0]++, FRUSTRATIO_1);
            break;
        case 2:
            gSPClipRatio(gdl[0]++, FRUSTRATIO_2);
            break;
        case 3:
            gSPClipRatio(gdl[0]++, FRUSTRATIO_3);
            break;
        case 4:
            gSPClipRatio(gdl[0]++, FRUSTRATIO_4);
            break;
        case 5:
            gSPClipRatio(gdl[0]++, FRUSTRATIO_5);
            break;
        case 6:
            gSPClipRatio(gdl[0]++, FRUSTRATIO_6);
            break;
    }
}
#line 391 "src/modules/uvchannel_rom.c"

#line 392 "src/modules/uvchannel_rom.c"
/* For an enabled valid channel, submit viewport and projection/view
 * transforms, perspective normalization and callbacks, then pop the view.
 * Preserve the original flag-controlled graphics-manager operation. */
void uvChannelRender(s32 channel) {
    UnkStruct_uvchannel_rom_00401CD0 *state;
    Mtx4F rotation;
    Mtx4F inverseRotation;

    if ((channel < 0) || (channel >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    state = &D_uvchannel_rom_00401CD0[channel];
    if (state->unk1 & 2) {
        sUvGfxMgrExports->uvGfxAppendViewport((s32) state->unk214, (s32) state->unk216,
                                                     (s32) state->unk218, (s32) state->unk21A);
        sUvFmtxExports->uvGfxMtxProjPushF(&state->unk4);
        sUvFmtxExports->uvFmtxSetSharedAxes(state->unk44.m[3][0], state->unk44.m[3][1],
                                                 state->unk44.m[3][2]);
        sUvFmtxExports->uvMat4ApplySharedInverseTranslation(&rotation, &state->unk44);
        sUvFmtxExports->uvMat4InvertTranslationRotation(&inverseRotation, &rotation);
        sUvFmtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&inverseRotation);
        sUvGfxMgrExports->uvGfxPersp((s16) (s32) (131072.0f / (state->unkF0 + state->unkEC)));
        if (!(state->unk1 & 4)) {
            sUvGfxMgrExports->uvGfxClearDepthImageViewport();
        }
        sUvCbackExports->uvExecuteCallbacks((CallbackList *) state->unk21C, channel);
        sUvFmtxExports->uvGfxMtxFViewPop();
    }
}
#line 419 "src/modules/uvchannel_rom.c"

#line 420 "src/modules/uvchannel_rom.c"
/* Copy the supplied view matrix and inverse translation/rotation,
 * update cached position/up vectors, then rebuild the channel frustum. */
void uvChannelSetViewMatrix(s32 channel, Mtx4F *matrix) {
    UnkStruct_uvchannel_rom_00401CD0 *state;

    if ((channel < 0) || (channel >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    state = &D_uvchannel_rom_00401CD0[channel];
    sUvFmtxExports->uvMat4FCopy(&state->unk44, matrix);
    sUvFmtxExports->uvMat4InvertTranslationRotation(&state->unk84, matrix);
    state->unkC4.x = matrix->m[3][0];
    state->unkC4.y = matrix->m[3][1];
    state->unkC4.z = matrix->m[3][2];
    state->unkD0.x = matrix->m[1][0];
    state->unkD0.y = matrix->m[1][1];
    state->unkD0.z = matrix->m[1][2];
    func_uvchannel_rom_00401658(channel);
}
#line 438 "src/modules/uvchannel_rom.c"

s32 func_uvchannel_rom_004014E8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    UnkStruct_uvchannel_rom_00401CD0 *temp_v0;
    f32 temp_fv0;
    s32 i;

    if ((arg0 >= 0) && (arg0 < D_uvchannel_rom_00401CD4)) {
        temp_v0 = &D_uvchannel_rom_00401CD0[arg0];

        for (i = 0; i < 6; i += 2) {
            Vec3F *a3 = &temp_v0->unk1CC[i];
            Vec3F *v1 = &temp_v0->unk1CC[i + 1];

            // never true
            if (i == 5) {
                arg1 += a3->x * temp_v0->unkF0;
                arg2 += a3->y * temp_v0->unkF0;
                arg3 += a3->z * temp_v0->unkF0;
            }

            temp_fv0 = (a3->x * arg1) + (a3->y * arg2) + (a3->z * arg3);
            if ((temp_fv0 + arg4) < 0.0f) {
                return 0;
            }

            if (i == 4) {
                arg1 += v1->x * temp_v0->unkF0;
                arg2 += v1->y * temp_v0->unkF0;
                arg3 += v1->z * temp_v0->unkF0;
            }
            temp_fv0 = (v1->x * arg1) + (v1->y * arg2) + (v1->z * arg3);
            if ((temp_fv0 + arg4) < 0.0f) {
                return 0;
            }
        }
    }

    return 1;
}

void func_uvchannel_rom_00401658(s32 arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    s32 temp_s1;
    s32 var_v0;
    s32 i;
    UnkStruct_uvchannel_rom_00401CD0 *temp_s3;
    Vec3F *temp_s0;
    Mtx4F sp50;

    temp_s3 = &D_uvchannel_rom_00401CD0[arg0];
    temp_s0 = &temp_s3->unkF4[2];
    temp_fv0 = temp_s3->unkF0 / temp_s3->unkEC;
    temp_s3->unkF4[0].y = temp_s3->unkF0;
    temp_s3->unkF4[1].y = temp_s3->unkF0;

    temp_fa1 = temp_s3->unkDC * temp_fv0;
    temp_fa0 = temp_s3->unkE0 * temp_fv0;
    temp_ft4 = temp_s3->unkE4 * temp_fv0;
    temp_ft5 = temp_s3->unkE8 * temp_fv0;
    temp_s3->unkF4[0].x = temp_fa0;
    temp_s3->unkF4[1].x = temp_fa0;
    temp_s3->unkF4[0].z = temp_ft4;
    temp_s3->unkF4[1].z = temp_ft5;
    if (0)
        ; // FAKE
    temp_s0->x = temp_fa1;
    temp_s0->y = temp_s3->unkF0;
    temp_s0->z = temp_ft5;
    temp_s3->unkF4[3].z = temp_ft4;
    temp_s3->unkF4[3].x = temp_fa1;
    temp_s3->unkF4[4].z = 0.0f;
    temp_s3->unkF4[4].x = 0.0f;
    temp_s3->unkF4[5].z = 0.0f;
    temp_s3->unkF4[5].y = 0.0f;
    temp_s3->unkF4[5].x = 0.0f;
    temp_s3->unkF4[3].y = temp_s3->unkF0;
    temp_s3->unkF4[4].y = temp_s3->unkF0;

    for (i = 0; i < 4; i++) {
        Vec3F *temp_s2 = &temp_s3->unkF4[i];
        sUvFvecExports->uvVec3FCross(&temp_s3->unk184[i], &temp_s3->unkF4[(i + 1) % 4], temp_s2);
        sUvFvecExports->uvVec3FNormalize(&temp_s3->unk184[i], &temp_s3->unk184[i]);
    }
    temp_s0 = temp_s3->unk1B4;
    sUvFvecExports->uvVec3FCopy(temp_s0, (Vec3F *) &temp_s3->unkF4[4].x);
    sUvFvecExports->uvVec3FNormalize(temp_s0, temp_s0);
    temp_s3->unk1B4[1].x = -temp_s0->x;
    temp_s3->unk1B4[1].y = -temp_s0->y;
    temp_s3->unk1B4[1].z = -temp_s0->z;
    sUvFmtxExports->uvMat4FCopy(&sp50, &temp_s3->unk44);

    for (i = 0; i < 6; i++) {
        sUvFmtxExports->uvMat4TransformPoint(&sp50, &temp_s3->unk13C[i], &temp_s3->unkF4[i]);
    }
    sp50.m[3][0] = sp50.m[3][1] = sp50.m[3][2] = 0.0f;

    for (i = 0; i < 6; i++) {
        sUvFmtxExports->uvMat4TransformPoint(&sp50, &temp_s3->unk1CC[i], &temp_s3->unk184[i]);
    }
}

#line 543 "src/modules/uvchannel_rom.c"
/* Draw the original white rectangle and prepare the debug orthographic
 * projection and translation derived from the channel view. */
void uvChannelBeginDebugFrustum(s32 channel) {
    Mtx4F projection;
    Mtx4F view;
    UnkStruct_uvchannel_rom_00401CD0 *state;
    f32 extent;
    f32 negativeExtent;

    state = &D_uvchannel_rom_00401CD0[channel];
    extent = 2.0f * state->unkF0;
    sUvGeomExports->uvSetFillColor(1.0f, 1.0f, 1.0f, 1.0f);
    sUvGeomExports->uvVtxRect(0, 0, 0x140, 0xF0);
    negativeExtent = -extent;
    sUvFmtxExports->uvMat4BuildOrthographicProjection(&projection, negativeExtent, extent, negativeExtent, extent, 10000.0f,
                                             -10000.0f);
    sUvFmtxExports->uvMat4RotateAxis(&projection, 1.5707963f, 0x78);
    sUvFmtxExports->uvGfxMtxProjPushF(&projection);
    sUvFmtxExports->uvMat4SetIdentity(&view);
    view.m[3][0] = -state->unk44.m[3][0];
    view.m[3][1] = -state->unk44.m[3][1];
    sUvFmtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&view);
    sUvFmtxExports->uvFmtxSetSharedAxes(0.0f, 0.0f, 0.0f);
}
#line 565 "src/modules/uvchannel_rom.c"

#line 566 "src/modules/uvchannel_rom.c"
/* Submit the original translucent red triangle from cached frustum
 * corners inside a graphics-state push/pop. */
void uvChannelDrawDebugFrustum(s32 channel) {
    UnkStruct_uvchannel_rom_00401CD0 *state;

    state = &D_uvchannel_rom_00401CD0[channel];
    sUvGfxMgrExports->uvGfxClearDepthImageViewport();
    sUvGfxStateExports->uvGfxSetFogParameters(0.0f, 0.0f);
    sUvGfxStateExports->uvGfxStatePush();
    sUvGfxStateExports->uvGfxStateSetFlags(0x820FFF);
    sUvGfxStateExports->uvGfxClearCurrentStateBits(0xB27C0000);
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx((s32) state->unk13C[5].x, (s32) state->unk13C[5].y, 0x3E8, 0, 0, 0xFF, 0,
                           0, 0x80);
    sUvDGeomExports->uvVtx((s32) state->unk13C[1].x, (s32) state->unk13C[1].y, 0x3E8, 0, 0, 0xFF, 0,
                           0, 0x80);
    sUvDGeomExports->uvVtx((s32) state->unk13C[2].x, (s32) state->unk13C[2].y, 0x3E8, 0, 0, 0xFF, 0,
                           0, 0x80);
    sUvDGeomExports->uvVtxEndPoly();
    sUvGfxStateExports->uvGfxStatePop();
}
#line 585 "src/modules/uvchannel_rom.c"
