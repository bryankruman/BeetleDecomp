#include "common.h"
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct {
    u8 opaque00[4]; void (*getProperties)(s32, ...);
} GlareChannelMatrixExports;
typedef struct {
    Vec3F worldPoint; u8 opaque0C[0xC];
    f32 screenX, screenY; s16 visible;
} GlareProjectionSharedPrefix;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern s32 gDebugOptsGlare;
extern GlareProjectionSharedPrefix D_glare_00400DF0;
extern const f32 D_glare_00400DC4;
/*__SEEDEXTERNS__*/
typedef struct { char pad[0x10]; int (*unk10)(int); } GfxMgrExp_004000D0;
typedef struct { char pad[0x10]; int (*unk10)(int, void *, int, int); } CbckExp_004000D0;
typedef struct { char pad[0x4]; void (*unk4)(int, int, int *, int); } ChanExp_004000D0;
extern GfxMgrExp_004000D0 *gUvGfxMgrExports;
extern CbckExp_004000D0 *gUvCbckExports;
extern ChanExp_004000D0 *gUvChanExports;
extern void func_glare_004006B0(void);
extern void func_glare_00400BA4(void);
// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/__entrypoint_func_glare_400000.s")

#line 13 "src/modules/glare.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_glare_004000C8(void) {
}
#line 15 "src/modules/glare.c"

/* Retrieve the graphics and channel callback hosts, then register the original glare callbacks in order. */
#line 17 "src/modules/glare.c"
/* Attach the original glare callbacks to graphics callback host two
 * and channel property-six host, both with priority 200. Preserve callback
 * registration order and the caller-owned channel contract. */
void glareAttachGraphicsAndChannelCallbacks(int channel) {
    int channelCallbackHost;

    gUvCbckExports->unk10(gUvGfxMgrExports->unk10(2), (void *)func_glare_00400BA4, 0, 0xC8);
    gUvChanExports->unk4(channel, 6, &channelCallbackHost, 0);
    gUvCbckExports->unk10(channelCallbackHost, (void *)func_glare_004006B0, 0, 0xC8);
}
#line 24 "src/modules/glare.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_00400170.s")

/* Obtain both channel matrices, build the original quarter-turn adjustment,
 * and transform the shared point. Mark points below the retained depth
 * threshold invisible; otherwise store the original projected screen values.
 * RE_ORIGINAL_QUIRK: Disabling glare leaves all shared fields unchanged. The ordered
 * depth test permits NaNs to continue; division and output stores are not
 * clamped. Preserve the in-place point transform and original arithmetic.
 * RE_UNKNOWN: Coordinate frames, matrix/output initialization on provider
 * failure, threshold role and valid finite/depth/alias domains need callers. */
void func_glare_00400518(s32 channel) {
    Vec3F projectedPoint;
    Mtx4F secondChannelMatrix;
    Mtx4F channelMatrix;
    Mtx4F adjustment;

    if (gDebugOptsGlare == 0) {
        return;
    }
    ((GlareChannelMatrixExports *)gUvChanExports)->getProperties(channel, 1,
        &channelMatrix, 2, &secondChannelMatrix, 0);
    gUvFmtxExports->uvMat4SetIdentity(&adjustment);
    gUvFmtxExports->uvMat4RotateAxis(&channelMatrix, -1.5707969665527344f, 'x');
    gUvFmtxExports->uvMat4Mul(&adjustment, &channelMatrix, &secondChannelMatrix);
    projectedPoint.x = D_glare_00400DF0.worldPoint.x;
    projectedPoint.y = D_glare_00400DF0.worldPoint.y;
    projectedPoint.z = D_glare_00400DF0.worldPoint.z;
    gUvFmtxExports->uvMat4TransformPoint(&adjustment, &projectedPoint, &projectedPoint);
    if (projectedPoint.z < D_glare_00400DC4) {
        D_glare_00400DF0.visible = 0;
        return;
    }
    D_glare_00400DF0.visible = 1;
    D_glare_00400DF0.screenX = projectedPoint.x / projectedPoint.z;
    D_glare_00400DF0.screenY = projectedPoint.y / projectedPoint.z;
    D_glare_00400DF0.screenX = ((D_glare_00400DF0.screenX + 1.0f) * 276.0f) * 0.5f + 22.0f + 0.5f;
    D_glare_00400DF0.screenY = ((D_glare_00400DF0.screenY + 1.0f) * 208.0f) * 0.5f + 16.0f + 0.5f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_004006B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_004009EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_00400BA4.s")

