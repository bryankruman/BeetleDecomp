// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
typedef struct { s32 objectId, active; f32 x,y,z,start,duration,size,alpha; } BubbleObjectState;
extern UvDobj_Exports *gUvDobjExports;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern f32 D_bubble_004008F0;
#include "uvgfxmgr_rom.h"
#include "uvmath_rom.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
extern UvMath_Exports *gUvMathExports;
extern f32 D_80025D6C;
typedef struct { f32 r, g, b; } BubbleRgb;
typedef struct {
    u8 unk00[0x20]; f32 alpha; BubbleRgb *color;
    u8 unk28[0xC]; f32 interval;
    u8 unk38[0xC]; f32 nextTime;
} BubbleState;
s32 func_bubble_004004C8(BubbleState *);

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/__entrypoint_func_bubble_400000.s")

#line 23 "src/modules/bubble.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_bubble_00400068(void) {
}
#line 25 "src/modules/bubble.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/func_bubble_00400070.s")

#line 23 "src/modules/bubble.c"
/* Set primitive RGB from the referenced color and alpha from the bubble state. */
void bubbleSetPrimitiveColor(BubbleState *state) {
    BubbleRgb *color = state->color;
    gUvGfxMgrExports->uvGfxSetPrimColorF(color->r, color->g, color->b, state->alpha);
}
#line 24 "src/modules/bubble.c"

#line 25 "src/modules/bubble.c"
/* Expire the bubble after its start-plus-duration deadline. Otherwise use
 * normalized age for scale, switch to model 0xE after the original threshold,
 * update fade alpha, and submit a translated uniform-scale matrix.
 * RE_UNKNOWN: duration domain and handle lifetime need original initializers/callers. */
void bubbleUpdateLifetimeAndTransform(BubbleObjectState *state) {
    f32 fraction;
    Mtx4F matrix;
    f32 start = state->start, duration = state->duration;
    if (start + duration < D_80025D6C) {
        state->active = 0;
        gUvDobjExports->uvDobjClearFlagBits(state->objectId, 2);
        return;
    }
    fraction = (D_80025D6C - start) / duration;
    if (D_bubble_004008F0 < fraction) {
        gUvDobjExports->uvDobjModel(state->objectId, 0xE);
        state->alpha = (1.0f - fraction) * 2.5f;
    }
    fraction *= state->size;
    gUvFmtxExports->uvMat4SetIdentity(&matrix);
    gUvFmtxExports->uvMat4Scale(&matrix, fraction, fraction, fraction);
    matrix.m[3][0] = state->x;
    matrix.m[3][1] = state->y;
    matrix.m[3][2] = state->z;
    gUvDobjExports->uvDobjPosm(state->objectId, 0, &matrix);
}
#line 26 "src/modules/bubble.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/func_bubble_004003AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/func_bubble_004004C8.s")

#line 31 "src/modules/bubble.c"
/* After the scheduled time, attempt emission. A successful attempt schedules
 * the next time using the original random fraction, interval and current time. */
void bubbleTryEmitAndSchedule(BubbleState *state) {
    if (state->nextTime < D_80025D6C) {
        if (func_bubble_004004C8(state) != 0) {
            state->nextTime = gUvMathExports->uvRandFLcg() * state->interval + D_80025D6C;
        }
    }
}
#line 32 "src/modules/bubble.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/func_bubble_00400820.s")

