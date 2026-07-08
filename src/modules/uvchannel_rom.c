// SPDX-License-Identifier: AGPL-3.0-or-later
//
// uvchannel_rom - view channel (viewport / camera) manager.
//
// A "channel" is one on-screen view: a camera transform, a projection frustum, a
// scissor rectangle and a pair of draw callbacks. The module owns a fixed pool of
// channels (D_uvchannel_rom_00401CD0[0 .. count-1]) sized from system property 0xB
// at init. Clients allocate a channel, configure its matrix/frustum/viewport via the
// varargs get/set property calls, then have it applied each frame to set up the RSP
// viewport, projection and clip state.
//
// Scribe pass: names + comments added for readability; the byte-exact match is
// unchanged. Each function carries a #line directive so these comments don't shift
// IDO's source-line-sensitive codegen. func_*/D_* renames are deferred to the
// scripted NAME phase. The cached D_uvchannel_rom_00401CDC.._00401CF8 pointers hold
// the export tables of the sibling modules this one loads: CDC=CBCK CE8=MATH CE4=FVEC
// CE0=FMTX CEC=GMGR(gfx mgr) CF0=STAT(gfx state) CF4=DGEO CF8=GEOM.
#include "common.h"
#include "module.h"

typedef struct ViewChannel_s {
    /* 0x000 */ u8 flags;  // bit0: channel is allocated / in use
    /* 0x001 */ u8 drawFlags;  // bit1(0x2): configured & drawable; bit2(0x4): skip gfxmgr end call
    /* 0x002 */ u8 clipRatioIndex;  // 1..6, selects FRUSTRATIO_n when applied
    /* 0x003 */ u8 unused;
    /* 0x004 */ Mtx4F viewMatrix;  // view/rotation matrix pushed when the channel is applied
    /* 0x044 */ Mtx4F cameraMatrix;  // camera world transform; translation lives in row 3
    /* 0x084 */ Mtx4F auxMatrix;  // secondary transform derived from the camera matrix
    /* 0x0C4 */ Vec3F position;  // camera position (cameraMatrix row 3)
    /* 0x0D0 */ Vec3F upVector;  // camera up axis (cameraMatrix row 1)
    /* 0x0DC */ f32 unkDC;
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ f32 unkE4;
    /* 0x0E8 */ f32 unkE8;
    /* 0x0EC */ f32 unkEC;
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ Vec3F frustumCorners[6];  // frustum corner points in view space
    /* 0x13C */ Vec3F frustumCornersXf[6];  // corners transformed by the camera matrix
    /* 0x184 */ Vec3F sidePlaneNormals[4];  // normals of the 4 side clip planes
    /* 0x1B4 */ Vec3F capPlaneNormals[2];  // normals of the near/far cap planes
    /* 0x1CC */ Vec3F clipPlanes[6];  // 6 clip-plane normals used by the sphere test
    /* 0x214 */ u16 viewportX0;  // scissor rectangle (left,right,top,bottom), inclusive
    /* 0x216 */ u16 viewportX1;
    /* 0x218 */ u16 viewportY0;
    /* 0x21A */ u16 viewportY1;
    /* 0x21C */ s32 drawCtx;  // uvcback draw context handle for this channel
    /* 0x220 */ s32 earlyCbHandle;  // callback registered at priority 0x01 (slot 0)
    /* 0x224 */ s32 lateCbHandle;  // callback registered at priority 0xFF (slot 1)
} ViewChannel; /* size = 0x228 */

typedef struct UnkStruct_Geom_Exports_s {
    char pad[0xC];
    void (*unkC)(f32, f32, f32, f32);
    void (*unk10)(s32, s32, s32, s32);
} UnkStruct_Geom_Exports;

extern ViewChannel *D_uvchannel_rom_00401CD0;
extern s32 D_uvchannel_rom_00401CD4;
extern UvCback_Exports *D_uvchannel_rom_00401CDC;
extern UvMath_Exports *D_uvchannel_rom_00401CE8;
extern UvFVec_Rom_Exports *D_uvchannel_rom_00401CE4;
extern UvFMtx_Rom_Exports *D_uvchannel_rom_00401CE0;
extern UvGfxMgr_Exports *D_uvchannel_rom_00401CEC;
extern UvGfxState_Rom_Exports *D_uvchannel_rom_00401CF0;
extern UvDGeom_Rom_Exports *D_uvchannel_rom_00401CF4;
extern s32 D_uvchannel_rom_00401CD8;

// geom exports
extern UnkStruct_Geom_Exports *D_uvchannel_rom_00401CF8;

extern f32 D_uvchannel_rom_00401CB0;
extern f32 D_uvchannel_rom_00401CB4;

// Module shutdown: release every sibling module and clear the cached pointers.
#line 58
void func_uvchannel_rom_004001D4(void);
// Query channel properties. Variadic: (channel, prop, out..., prop, out..., 0);
// each prop id copies the matching channel field(s) out through pointer args.
#line 59
void func_uvchannel_rom_00400288(s32 arg0, ...);
// Set channel properties. Mirror of the getter: (channel, prop, in..., ..., 0).
#line 60
void func_uvchannel_rom_004005DC(s32 arg0, ...);
// Convenience setter: set the channel's draw flags (property 14).
#line 61
void func_uvchannel_rom_00400AD4(s32 arg0, s32 arg1);
// Convenience setter: set the 6 frustum parameters (property 4).
#line 62
void func_uvchannel_rom_00400AFC(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
// Convenience setter: set the viewport rectangle (property 5).
#line 63
void func_uvchannel_rom_00400B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
// Register or clear one of the channel's two draw callbacks (arg1 picks the slot).
// arg2 != 0 registers the callback on the draw context; arg2 == 0 unregisters it.
#line 64
void func_uvchannel_rom_00400BB8(s32 arg0, s32 arg1, s32 arg2);
// Allocate a free channel: mark it in use, create its draw context, seed the
// viewport to the full screen and register the apply callback. Returns the channel
// index, or -1 if the pool is full.
#line 65
s32 func_uvchannel_rom_00400CCC(void);
// Free a channel: clear its flags and destroy its draw context.
#line 66
void func_uvchannel_rom_00400E7C(s32 arg0);
// Draw-context callback: emit this channel's clip-ratio command into the display list.
#line 67
void func_uvchannel_rom_00400EFC(s32 arg0);
// Apply the channel for rendering: set the scissor, load the view transform and
// camera inverse, program the projection scale, then run its draw callback.
#line 68
void func_uvchannel_rom_00401278(s32 arg0);
// Set the channel's camera matrix, cache its position/up vectors, and rebuild the frustum.
#line 69
void func_uvchannel_rom_00401414(s32 arg0, Mtx4F *arg1);
// Sphere/point-in-frustum test. Walks the clip planes in pairs; returns 0 as soon
// as the point falls outside a plane by more than the radius (arg4), else 1 (inside).
#line 70
s32 func_uvchannel_rom_004014E8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
// Rebuild the channel's frustum geometry from its parameters: derive the 6 corner
// points, the 4 side-plane and 2 cap-plane normals, then transform them by the camera matrix.
#line 71
void func_uvchannel_rom_00401658(s32 arg0);
// Draw callback (early): set up the debug ortho projection that visualizes the frustum.
#line 72
void func_uvchannel_rom_004018D8(s32 arg0);
// Draw callback (late): draw the frustum outline as a filled triangle.
#line 73
void func_uvchannel_rom_00401A4C(s32 arg0);

// Module init: resolve the sibling module export tables, size the channel pool
// from system property 0xB (default 4), then allocate and zero it.
#line 75
void __entrypoint_func_uvchannel_rom_400000(UvChannelExports *exports) {
    s32 *temp_v0;

    uvUpdateFileAllocPtr((s32) exports);
    exports->func_uvchannel_rom_004001D4 = func_uvchannel_rom_004001D4;
    exports->func_uvchannel_rom_00401414 = func_uvchannel_rom_00401414;
    exports->func_uvchannel_rom_00400288 = func_uvchannel_rom_00400288;
    exports->func_uvchannel_rom_004014E8 = func_uvchannel_rom_004014E8;
    exports->func_uvchannel_rom_004005DC = func_uvchannel_rom_004005DC;
    exports->func_uvchannel_rom_00400AD4 = func_uvchannel_rom_00400AD4;
    exports->func_uvchannel_rom_00400AFC = func_uvchannel_rom_00400AFC;
    exports->func_uvchannel_rom_00400B70 = func_uvchannel_rom_00400B70;
    exports->func_uvchannel_rom_00400BB8 = func_uvchannel_rom_00400BB8;
    exports->func_uvchannel_rom_00400CCC = func_uvchannel_rom_00400CCC;
    exports->func_uvchannel_rom_00400E7C = func_uvchannel_rom_00400E7C;
    exports->func_uvchannel_rom_00401278 = func_uvchannel_rom_00401278;
#line 81
    D_uvchannel_rom_00401CDC = uvLoadModule('CBCK');
    D_uvchannel_rom_00401CE8 = uvLoadModule('MATH');
    D_uvchannel_rom_00401CE4 = uvLoadModule('FVEC');
    D_uvchannel_rom_00401CE0 = uvLoadModule('FMTX');
    D_uvchannel_rom_00401CEC = uvLoadModule('GMGR');
    D_uvchannel_rom_00401CF0 = uvLoadModule('STAT');
    D_uvchannel_rom_00401CF4 = uvLoadModule('DGEO');
    D_uvchannel_rom_00401CF8 = uvLoadModule('GEOM');
    temp_v0 = uvGetSystemProp(0xB);
    if (temp_v0 != NULL) {
        D_uvchannel_rom_00401CD4 = *temp_v0;
    } else {
        D_uvchannel_rom_00401CD4 = 4;
    }
    D_uvchannel_rom_00401CD0 =
        _uvMemAllocAlign8(D_uvchannel_rom_00401CD4 * sizeof(ViewChannel));
    uvMemSet(D_uvchannel_rom_00401CD0, 0U,
             D_uvchannel_rom_00401CD4 * sizeof(ViewChannel));
    D_uvchannel_rom_00401CD8 = 0;
}

// Module shutdown: release every sibling module and clear the cached pointers.
#line 102
void func_uvchannel_rom_004001D4(void) {
    uvUnloadModule('CBCK');
    D_uvchannel_rom_00401CDC = NULL;
    uvUnloadModule('MATH');
    D_uvchannel_rom_00401CE8 = NULL;
    uvUnloadModule('FVEC');
    D_uvchannel_rom_00401CE4 = NULL;
    uvUnloadModule('FMTX');
    D_uvchannel_rom_00401CE0 = NULL;
    uvUnloadModule('GMGR');
    D_uvchannel_rom_00401CEC = NULL;
    uvUnloadModule('STAT');
    D_uvchannel_rom_00401CF0 = NULL;
    uvUnloadModule('DGEO');
    D_uvchannel_rom_00401CF4 = NULL;
    uvUnloadModule('GEOM');
    D_uvchannel_rom_00401CF8 = NULL;
}

#ifdef NEEDS_RODATA
// Query channel properties. Variadic: (channel, prop, out..., prop, out..., 0);
// each prop id copies the matching channel field(s) out through pointer args.
#line 122
void func_uvchannel_rom_00400288(s32 arg0, ...) {
    ViewChannel *temp_s2;
    int prop;
    va_list args;
    void *arg;

    if ((arg0 < 0) || (arg0 >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    va_start(args, arg0);
    temp_s2 = &D_uvchannel_rom_00401CD0[arg0];
    while ((prop = va_arg(args, s32)) != 0) {
        switch (prop) {
            case 1:
                D_uvchannel_rom_00401CE0->func_00400504(va_arg(args, Mtx4F *), &temp_s2->viewMatrix);
                break;
            case 2:
                D_uvchannel_rom_00401CE0->func_00400504(va_arg(args, Mtx4F *), &temp_s2->auxMatrix);
                break;
            case 3:
                D_uvchannel_rom_00401CE0->func_00400504(va_arg(args, Mtx4F *), &temp_s2->cameraMatrix);
                break;
            case 4:
                *(f32 *) (arg = va_arg(args, f32 *)) = temp_s2->unkDC;
                *(f32 *) (arg = va_arg(args, f32 *)) = temp_s2->unkE0;
                *(f32 *) (arg = va_arg(args, f32 *)) = temp_s2->unkE4;
                *(f32 *) (arg = va_arg(args, f32 *)) = temp_s2->unkE8;
                *(f32 *) (arg = va_arg(args, f32 *)) = temp_s2->unkEC;
                *(f32 *) (arg = va_arg(args, f32 *)) = temp_s2->unkF0;
                break;
            case 5:
                *(s32 *) (arg = va_arg(args, s32 *)) = temp_s2->viewportX0;
                *(s32 *) (arg = va_arg(args, s32 *)) = temp_s2->viewportX1;
                *(s32 *) (arg = va_arg(args, s32 *)) = temp_s2->viewportY0;
                *(s32 *) (arg = va_arg(args, s32 *)) = temp_s2->viewportY1;
                break;
            case 6:
                *(s32 *) (arg = va_arg(args, s32 *)) = temp_s2->drawCtx;
                break;
            case 7:
                D_uvchannel_rom_00401CE4->uvVec3FCopy(va_arg(args, Vec3F *), &temp_s2->position);
                break;
            case 8:
                D_uvchannel_rom_00401CE4->uvVec3FCopy(va_arg(args, Vec3F *), &temp_s2->upVector);
                break;
            case 9:
                *(Vec3F **) (arg = va_arg(args, Vec3F **)) = temp_s2->frustumCorners;
                break;
            case 10:
                *(Vec3F **) (arg = va_arg(args, Vec3F **)) = temp_s2->frustumCornersXf;
                break;
            case 11:
                *(Vec3F **) (arg = va_arg(args, Vec3F **)) = temp_s2->sidePlaneNormals;
                break;
            case 12:
                *(Vec3F **) (arg = va_arg(args, Vec3F **)) = temp_s2->clipPlanes;
                break;
            case 14:
                *(s32 *) (arg = va_arg(args, s32 *)) = temp_s2->drawFlags;
                break;
            case 13:
                *(s32 *) (arg = va_arg(args, s32 *)) = D_uvchannel_rom_00401CD4;
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvchannel_rom/func_uvchannel_rom_00400288.s")
#endif

// Non matching
#if 0
// Set channel properties. Mirror of the getter: (channel, prop, in..., ..., 0).
#line 195
void func_uvchannel_rom_004005DC(s32 arg0, ...) {
    ViewChannel *temp_s2;
    s32 temp_s3;
    va_list args;
    UvCback_Rom_004000F0 *sp60;
    int prop;

    if ((arg0 < 0) || (arg0 >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    va_start(args, arg0);
    temp_s2 = &D_uvchannel_rom_00401CD0[arg0];
    while ((prop = va_arg(args, s32)) != 0) {
        switch (prop) {
            case 1:
                D_uvchannel_rom_00401CE0->func_00400504(&temp_s2->viewMatrix, &va_arg(args, Mtx4F));
                break;
            case 2:
                D_uvchannel_rom_00401CE0->func_00400504(&temp_s2->auxMatrix, &va_arg(args, Mtx4F));
                break;
            case 3:
                D_uvchannel_rom_00401CE0->func_00400504(&temp_s2->cameraMatrix, &va_arg(args, Mtx4F));
                break;
            case 4:
                temp_s2->unkDC = va_arg(args, f64);
                temp_s2->unkE0 = va_arg(args, f64);
                temp_s2->unkE4 = va_arg(args, f64);
                temp_s2->unkE8 = va_arg(args, f64);
                temp_s2->unkEC = va_arg(args, f64);
                temp_s2->unkF0 = va_arg(args, f64);
                D_uvchannel_rom_00401CE0->func_00401F74(&temp_s2->viewMatrix, temp_s2->unkDC, temp_s2->unkE0,
                                                        temp_s2->unkE4, temp_s2->unkE8, temp_s2->unkEC,
                                                        temp_s2->unkF0);
                func_uvchannel_rom_00401658(arg0);
                break;
            case 5:
                temp_s2->viewportX0 = va_arg(args, s32);
                temp_s2->viewportX1 = va_arg(args, s32);
                temp_s2->viewportY0 = va_arg(args, s32);
                temp_s2->viewportY1 = va_arg(args, s32);
                break;
            case 15:
                temp_s2->clipRatioIndex = va_arg(args, s32);
                if (temp_s2->clipRatioIndex >= 7) {
                    temp_s2->clipRatioIndex = 6;
                }
                if (temp_s2->clipRatioIndex <= 0) {
                    temp_s2->clipRatioIndex = 1;
                }
                break;
            case 14:
                temp_s2->drawFlags = va_arg(args, s32);
                break;
            case 16:
                func_uvchannel_rom_00400288(arg0, 6, &sp60, 0);
                temp_s3 = va_arg(args, s32);
                if (sp60 == NULL) {
                    break;
                }


                if ((D_uvchannel_rom_00401CD8 == 0) && (temp_s3 != 0)) {

                    D_uvchannel_rom_00401CDC->func_uvcback_rom_0040016C(
                        sp60, &func_uvchannel_rom_004018D8, 0, 0x19);
                    D_uvchannel_rom_00401CDC->func_uvcback_rom_0040016C(
                        sp60, &func_uvchannel_rom_00401A4C, 0, 0xFA);
                } else if ((D_uvchannel_rom_00401CD8 != 0) && (temp_s3 == 0)) {
                    D_uvchannel_rom_00401CDC->func_uvcback_rom_00400320(
                        sp60, (s32) &func_uvchannel_rom_004018D8);
                    D_uvchannel_rom_00401CDC->func_uvcback_rom_00400320(
                        sp60, (s32) &func_uvchannel_rom_00401A4C);
                }
                D_uvchannel_rom_00401CD8 = temp_s3;
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvchannel_rom/func_uvchannel_rom_004005DC.s")
#endif

// Convenience setter: set the channel's draw flags (property 14).
#line 278
void func_uvchannel_rom_00400AD4(s32 arg0, s32 arg1) {
    func_uvchannel_rom_004005DC(arg0, 0xE, arg1, 0);
}

// Convenience setter: set the 6 frustum parameters (property 4).
#line 282
void func_uvchannel_rom_00400AFC(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    func_uvchannel_rom_004005DC(arg0, 4, (f64) arg1, (f64) arg2, (f64) arg3, (f64) arg4, (f64) arg5,
                                (f64) arg6, 0);
}

// Convenience setter: set the viewport rectangle (property 5).
#line 287
void func_uvchannel_rom_00400B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_uvchannel_rom_004005DC(arg0, 5, arg1, arg2, arg3, arg4, 0);
}

// Register or clear one of the channel's two draw callbacks (arg1 picks the slot).
// arg2 != 0 registers the callback on the draw context; arg2 == 0 unregisters it.
#line 291
void func_uvchannel_rom_00400BB8(s32 arg0, s32 arg1, s32 arg2) {
    ViewChannel *temp_s0;

    temp_s0 = &D_uvchannel_rom_00401CD0[arg0];
    switch (arg1) { /* irregular */
        case 0:
            if (arg2 != 0) {
                D_uvchannel_rom_00401CDC->func_uvcback_rom_0040016C(
                    (UvCback_Rom_004000F0 *) temp_s0->drawCtx, arg2, 0, 1);
                temp_s0->earlyCbHandle = arg2;
                return;
            }
            if (temp_s0->earlyCbHandle != 0) {
                D_uvchannel_rom_00401CDC->func_uvcback_rom_00400320(
                    (UvCback_Rom_004000F0 *) temp_s0->drawCtx, temp_s0->earlyCbHandle);
                temp_s0->earlyCbHandle = 0;
                return;
            }
            return;
        case 1:
            if (arg2 != 0) {
                D_uvchannel_rom_00401CDC->func_uvcback_rom_0040016C(
                    (UvCback_Rom_004000F0 *) temp_s0->drawCtx, arg2, 0, 0xFF);
                temp_s0->lateCbHandle = arg2;
                return;
            }
            if (temp_s0->lateCbHandle != 0) {
                D_uvchannel_rom_00401CDC->func_uvcback_rom_00400320(
                    (UvCback_Rom_004000F0 *) temp_s0->drawCtx, temp_s0->lateCbHandle);
                temp_s0->lateCbHandle = 0;
            }
            break;
    }
}

// Allocate a free channel: mark it in use, create its draw context, seed the
// viewport to the full screen and register the apply callback. Returns the channel
// index, or -1 if the pool is full.
#line 326
s32 func_uvchannel_rom_00400CCC(void) {
    s32 *sp20;
    s32 var_a0_2;
    s32 *temp_v0;
    ViewChannel *var_s1;
    s32 i;

    var_s1 = NULL;
    temp_v0 = uvGetSystemProp(0xB);

    for (i = 0; i < D_uvchannel_rom_00401CD4; i++) {
        if (!(D_uvchannel_rom_00401CD0[i].flags & 1)) {
            D_uvchannel_rom_00401CD0[i].flags = 1;
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
    var_s1->drawCtx = D_uvchannel_rom_00401CDC->func_uvcback_rom_00400080(var_a0_2);
    var_s1->viewportX0 = 0;
    var_s1->viewportX1 = (s16) (D_uvchannel_rom_00401CEC->uvGetScreenWidth() - 1);
    var_s1->viewportY0 = 0;
    var_s1->viewportY1 = (s16) (D_uvchannel_rom_00401CEC->uvGetScreenHeight() - 1);
    var_s1->clipRatioIndex = 2;
    D_uvchannel_rom_00401CE0->func_00400B68(&var_s1->auxMatrix);
    D_uvchannel_rom_00401CE0->func_00400B68(&var_s1->cameraMatrix);
    D_uvchannel_rom_00401CE0->func_00400B68(&var_s1->viewMatrix);
    // TODO: Find a better match
    var_a0_2 = var_s1->drawCtx;
    if (var_a0_2 == NULL) {
        var_s1->drawFlags = 0;
        var_a0_2 = *(void **) 0x21C;
        var_s1 = NULL;
    }
    D_uvchannel_rom_00401CDC->func_uvcback_rom_0040016C(var_a0_2, (s32) &func_uvchannel_rom_00400EFC, 0,
                                                        0x1E);
    D_uvchannel_rom_00401CDC->func_uvcback_rom_0040016C(var_s1->drawCtx,
                                                        (s32) &func_uvchannel_rom_00400EFC, 0, 0xC8);
    return i;
}

// Free a channel: clear its flags and destroy its draw context.
#line 375
void func_uvchannel_rom_00400E7C(s32 arg0) {
    ViewChannel *temp_v0;
    s32 temp_a1;

    if ((arg0 < 0) || (arg0 >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    temp_v0 = &D_uvchannel_rom_00401CD0[arg0];
    temp_a1 = temp_v0->drawCtx;
    temp_v0->drawFlags = 0;
    temp_v0->flags = 0;
    if (temp_a1 != 0) {
        D_uvchannel_rom_00401CDC->func_uvcback_rom_004000D0((void *) temp_a1);
        temp_v0->drawCtx = 0;
    }
}

#ifdef NEEDS_RODATA
// Draw-context callback: emit this channel's clip-ratio command into the display list.
#line 394
void func_uvchannel_rom_00400EFC(s32 arg0) {
    Gfx **gdl;

    gdl = D_uvchannel_rom_00401CEC->uvGetDisplayListHead();
    D_uvchannel_rom_00401CF0->func_uvgfxstate_rom_00401CE8();
    switch (D_uvchannel_rom_00401CD0[arg0].clipRatioIndex) {
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
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvchannel_rom/func_uvchannel_rom_00400EFC.s")
#endif

// Apply the channel for rendering: set the scissor, load the view transform and
// camera inverse, program the projection scale, then run its draw callback.
#line 424
void func_uvchannel_rom_00401278(s32 arg0) {
    ViewChannel *temp_s0;
    Mtx4F sp64;
    Mtx4F sp24;

    if ((arg0 < 0) || (arg0 >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    temp_s0 = &D_uvchannel_rom_00401CD0[arg0];
    if (temp_s0->drawFlags & 2) {
        D_uvchannel_rom_00401CEC->func_uvgfxmgr_rom_00401BD4(
            (s32) temp_s0->viewportX0, (s32) temp_s0->viewportX1, (s32) temp_s0->viewportY0, (s32) temp_s0->viewportY1);
        D_uvchannel_rom_00401CE0->func_00402908(&temp_s0->viewMatrix);
        D_uvchannel_rom_00401CE0->func_0040034C(temp_s0->cameraMatrix.m[3][0], temp_s0->cameraMatrix.m[3][1],
                                                temp_s0->cameraMatrix.m[3][2]);
        D_uvchannel_rom_00401CE0->func_00400370(&sp64, &temp_s0->cameraMatrix);
        D_uvchannel_rom_00401CE0->func_00401604(&sp24, &sp64);
        D_uvchannel_rom_00401CE0->func_004029DC(&sp24);
        D_uvchannel_rom_00401CEC->func_uvgfxmgr_rom_00401D94(
            (s16) (s32) (131072.0f / (temp_s0->unkF0 + temp_s0->unkEC)));
        if (!(temp_s0->drawFlags & 4)) {
            D_uvchannel_rom_00401CEC->func_uvgfxmgr_rom_00401DC4();
        }
        D_uvchannel_rom_00401CDC->func_uvcback_rom_004000F0((UvCback_Rom_004000F0 *) temp_s0->drawCtx,
                                                            arg0);
        D_uvchannel_rom_00401CE0->uvGfxMtxViewPop();
    }
}

// Set the channel's camera matrix, cache its position/up vectors, and rebuild the frustum.
#line 454
void func_uvchannel_rom_00401414(s32 arg0, Mtx4F *arg1) {
    ViewChannel *temp_v0;

    if ((arg0 < 0) || (arg0 >= D_uvchannel_rom_00401CD4)) {
        return;
    }

    temp_v0 = &D_uvchannel_rom_00401CD0[arg0];
    D_uvchannel_rom_00401CE0->func_00400504(&temp_v0->cameraMatrix, arg1);
    D_uvchannel_rom_00401CE0->func_00401604(&temp_v0->auxMatrix, arg1);
    temp_v0->position.x = arg1->m[3][0];
    temp_v0->position.y = arg1->m[3][1];
    temp_v0->position.z = arg1->m[3][2];
    temp_v0->upVector.x = arg1->m[1][0];
    temp_v0->upVector.y = arg1->m[1][1];
    temp_v0->upVector.z = arg1->m[1][2];
    func_uvchannel_rom_00401658(arg0);
}

// Sphere/point-in-frustum test. Walks the clip planes in pairs; returns 0 as soon
// as the point falls outside a plane by more than the radius (arg4), else 1 (inside).
#line 473
s32 func_uvchannel_rom_004014E8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    ViewChannel *temp_v0;
    f32 temp_fv0;
    s32 i;

    if ((arg0 >= 0) && (arg0 < D_uvchannel_rom_00401CD4)) {
        temp_v0 = &D_uvchannel_rom_00401CD0[arg0];

        for (i = 0; i < 6; i += 2) {
            Vec3F *a3 = &temp_v0->clipPlanes[i];
            Vec3F *v1 = &temp_v0->clipPlanes[i + 1];

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

// Rebuild the channel's frustum geometry from its parameters: derive the 6 corner
// points, the 4 side-plane and 2 cap-plane normals, then transform them by the camera matrix.
#line 512
void func_uvchannel_rom_00401658(s32 arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    s32 temp_s1;
    s32 var_v0;
    s32 i;
    ViewChannel *temp_s3;
    Vec3F *temp_s0;
    Mtx4F sp50;

    temp_s3 = &D_uvchannel_rom_00401CD0[arg0];
    temp_s0 = &temp_s3->frustumCorners[2];
    temp_fv0 = temp_s3->unkF0 / temp_s3->unkEC;
    temp_s3->frustumCorners[0].y = temp_s3->unkF0;
    temp_s3->frustumCorners[1].y = temp_s3->unkF0;

    temp_fa1 = temp_s3->unkDC * temp_fv0;
    temp_fa0 = temp_s3->unkE0 * temp_fv0;
    temp_ft4 = temp_s3->unkE4 * temp_fv0;
    temp_ft5 = temp_s3->unkE8 * temp_fv0;
    temp_s3->frustumCorners[0].x = temp_fa0;
    temp_s3->frustumCorners[1].x = temp_fa0;
    temp_s3->frustumCorners[0].z = temp_ft4;
    temp_s3->frustumCorners[1].z = temp_ft5;
    if (0)
        ; // FAKE
    temp_s0->x = temp_fa1;
    temp_s0->y = temp_s3->unkF0;
    temp_s0->z = temp_ft5;
    temp_s3->frustumCorners[3].z = temp_ft4;
    temp_s3->frustumCorners[3].x = temp_fa1;
    temp_s3->frustumCorners[4].z = 0.0f;
    temp_s3->frustumCorners[4].x = 0.0f;
    temp_s3->frustumCorners[5].z = 0.0f;
    temp_s3->frustumCorners[5].y = 0.0f;
    temp_s3->frustumCorners[5].x = 0.0f;
    temp_s3->frustumCorners[3].y = temp_s3->unkF0;
    temp_s3->frustumCorners[4].y = temp_s3->unkF0;

    for (i = 0; i < 4; i++) {
        Vec3F *temp_s2 = &temp_s3->frustumCorners[i];
        D_uvchannel_rom_00401CE4->uvVec3FCross(&temp_s3->sidePlaneNormals[i], &temp_s3->frustumCorners[(i + 1) % 4],
                                               temp_s2);
        D_uvchannel_rom_00401CE4->uvVec3FNormalize(&temp_s3->sidePlaneNormals[i], &temp_s3->sidePlaneNormals[i]);
    }
    temp_s0 = temp_s3->capPlaneNormals;
    D_uvchannel_rom_00401CE4->uvVec3FCopy(temp_s0, (Vec3F *) &temp_s3->frustumCorners[4].x);
    D_uvchannel_rom_00401CE4->uvVec3FNormalize(temp_s0, temp_s0);
    temp_s3->capPlaneNormals[1].x = -temp_s0->x;
    temp_s3->capPlaneNormals[1].y = -temp_s0->y;
    temp_s3->capPlaneNormals[1].z = -temp_s0->z;
    D_uvchannel_rom_00401CE0->func_00400504(&sp50, &temp_s3->cameraMatrix);

    for (i = 0; i < 6; i++) {
        D_uvchannel_rom_00401CE0->func_00401D0C(&sp50, &temp_s3->frustumCornersXf[i], &temp_s3->frustumCorners[i]);
    }
    sp50.m[3][0] = sp50.m[3][1] = sp50.m[3][2] = 0.0f;

    for (i = 0; i < 6; i++) {
        D_uvchannel_rom_00401CE0->func_00401D0C(&sp50, &temp_s3->clipPlanes[i], &temp_s3->sidePlaneNormals[i]);
    }
}

// Draw callback (early): set up the debug ortho projection that visualizes the frustum.
#line 578
void func_uvchannel_rom_004018D8(s32 arg0) {
    Mtx4F sp80;
    Mtx4F sp40;
    ViewChannel *temp_v0;
    f32 temp_fv1;
    f32 temp_fv0;

    temp_v0 = &D_uvchannel_rom_00401CD0[arg0];
    temp_fv1 = 2.0f * temp_v0->unkF0;
    D_uvchannel_rom_00401CF8->unkC(1.0f, 1.0f, 1.0f, 1.0f);
    D_uvchannel_rom_00401CF8->unk10(0, 0, 0x140, 0xF0);
    temp_fv0 = -temp_fv1;
    D_uvchannel_rom_00401CE0->func_00402038(&sp80, temp_fv0, temp_fv1, temp_fv0, temp_fv1,
                                            D_uvchannel_rom_00401CB0, D_uvchannel_rom_00401CB4);
    D_uvchannel_rom_00401CE0->func_00401000(&sp80, 1.5707963f, 0x78);
    D_uvchannel_rom_00401CE0->func_00402908(&sp80);
    D_uvchannel_rom_00401CE0->func_00400B68(&sp40);
    sp40.m[3][0] = -temp_v0->cameraMatrix.m[3][0];
    sp40.m[3][1] = -temp_v0->cameraMatrix.m[3][1];
    D_uvchannel_rom_00401CE0->func_004029DC(&sp40);
    D_uvchannel_rom_00401CE0->func_0040034C(0.0f, 0.0f, 0.0f);
}

// Draw callback (late): draw the frustum outline as a filled triangle.
#line 601
void func_uvchannel_rom_00401A4C(s32 arg0) {
    ViewChannel *temp_s0;

    temp_s0 = &D_uvchannel_rom_00401CD0[arg0];
    D_uvchannel_rom_00401CEC->func_uvgfxmgr_rom_00401DC4();
    D_uvchannel_rom_00401CF0->func_uvgfxstate_rom_00401F54(0.0f, 0.0f);
    D_uvchannel_rom_00401CF0->func_uvgfxstate_rom_00402218();
    D_uvchannel_rom_00401CF0->func_uvgfxstate_rom_00401314(0x820FFF);
    D_uvchannel_rom_00401CF0->func_uvgfxstate_rom_00401354(0xB27C0000);
    D_uvchannel_rom_00401CF4->uvVtxBeginPoly();
    D_uvchannel_rom_00401CF4->uvVtx((s32) temp_s0->frustumCornersXf[5].x, (s32) temp_s0->frustumCornersXf[5].y, 0x3E8, 0, 0, 0xFF, 0, 0, 0x80);
    D_uvchannel_rom_00401CF4->uvVtx((s32) temp_s0->frustumCornersXf[1].x, (s32) temp_s0->frustumCornersXf[1].y, 0x3E8, 0, 0, 0xFF, 0, 0, 0x80);
    D_uvchannel_rom_00401CF4->uvVtx((s32) temp_s0->frustumCornersXf[2].x, (s32) temp_s0->frustumCornersXf[2].y, 0x3E8, 0, 0, 0xFF, 0, 0, 0x80);
    D_uvchannel_rom_00401CF4->uvVtxEndPoly();
    D_uvchannel_rom_00401CF0->func_uvgfxstate_rom_00402254();
}
