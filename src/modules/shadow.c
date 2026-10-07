// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef struct { u8 bytes[0x20]; } ShadowFrame;
typedef struct {
    ShadowFrame frames[4];
    s32 frameIndex;
    s32 sourceHandle;
    u8 unk88[0x48];
    f32 valueD0;
    u8 active;
    u8 unkD5[3];
} CarShadowState;
typedef struct { u8 unk00[8]; s32 handle; } CarShadowSource;
extern CarShadowState *D_shadow_00400B84;

extern s32 gDebugOptsCarShadow;
CarShadowState *shadowAllocateState(CarShadowSource *source);
void shadowReleaseState(CarShadowState *state);
void func_shadow_00400180(CarShadowState *, ShadowFrame *, void *);
void shadowUpdateCurrentFrame(CarShadowState *state, void *output);
void func_shadow_00400498();
void func_shadow_00400750();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/__entrypoint_func_shadow_400000.s")

void func_shadow_00400100(void) {
}

#line 29 "src/modules/shadow.c"
/* Reserve the first inactive state in the eight-record shadow pool.
 * Preserve the source handle, zero the scalar at 0xD0 and return null when full. */
CarShadowState *shadowAllocateState(CarShadowSource *source) {
    CarShadowState *state;
    s32 offset;
    for (offset = 0; offset < 8; offset++) {
        state = &D_shadow_00400B84[offset];
        if (state->active == 0) {
            break;
        }
    }
    if (offset == 8) {
        return NULL;
    }
    state->sourceHandle = source->handle;
    state->active = 1;
    state->valueD0 = 0.0f;
    return state;
}
#line 30 "src/modules/shadow.c"

#line 31 "src/modules/shadow.c"
/* Release a non-null shadow state by invalidating its source handle and
 * clearing its active flag. The remaining pooled fields are intentionally retained. */
void shadowReleaseState(CarShadowState *state) {
    if (state != NULL) {
        state->sourceHandle = -1;
        state->active = 0;
    }
}
#line 37 "src/modules/shadow.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/func_shadow_00400180.s")

#line 40 "src/modules/shadow.c"
/* Update the selected 32-byte shadow frame while car shadows are enabled.
 * Frame selection and output storage follow the original caller contract. */
void shadowUpdateCurrentFrame(CarShadowState *state, void *output) {
    if (gDebugOptsCarShadow != 0) {
        func_shadow_00400180(state, &state->frames[state->frameIndex], output);
    }
}
#line 41 "src/modules/shadow.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/func_shadow_00400498.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/func_shadow_00400750.s")

