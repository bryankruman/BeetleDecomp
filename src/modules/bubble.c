// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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

void func_bubble_00400068(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/func_bubble_00400070.s")

#line 23 "src/modules/bubble.c"
/* Set primitive RGB from the referenced color and alpha from the bubble state. */
void bubbleSetPrimitiveColor(BubbleState *state) {
    BubbleRgb *color = state->color;
    gUvGfxMgrExports->uvGfxSetPrimColorF(color->r, color->g, color->b, state->alpha);
}
#line 24 "src/modules/bubble.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/bubble/func_bubble_00400258.s")

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

