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
void shadowUpdateCurrentFrame(CarShadowState *state, void *inputRecord);
void func_shadow_00400498();
void func_shadow_00400750();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/__entrypoint_func_shadow_400000.s")

#line 26 "src/modules/shadow.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_shadow_00400100(void) {
}
#line 28 "src/modules/shadow.c"

#line 29 "src/modules/shadow.c"
/* Choose the first inactive record among eight, returning null if all are active.
 * Store the source handle, mark the record active and clear valueD0; retain other
 * fields. RE_UNKNOWN: handle validity, record ownership and later initialization
 * require consumers; no allocation beyond this fixed pool occurs. */
#line 31 "src/modules/shadow.c"
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
#line 48 "src/modules/shadow.c"
#line 30 "src/modules/shadow.c"

#line 31 "src/modules/shadow.c"
/* If the state pointer is nonnull, set its source handle to -1 and clear active.
 * Other fields remain unchanged. RE_UNKNOWN: pointer provenance and outstanding
 * references require consumers; this does not free separate storage. */
#line 33 "src/modules/shadow.c"
void shadowReleaseState(CarShadowState *state) {
    if (state != NULL) {
        state->sourceHandle = -1;
        state->active = 0;
    }
}
#line 39 "src/modules/shadow.c"
#line 37 "src/modules/shadow.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/func_shadow_00400180.s")

#line 40 "src/modules/shadow.c"
/* While car shadows are enabled, pass the selected 32-byte frame and optional input record to the update helper.
 * RE_UNKNOWN: input-record meaning and valid frame selection require original producers/callers; the third argument supplies data. */
#line 42 "src/modules/shadow.c"

void shadowUpdateCurrentFrame(CarShadowState *state, void *inputRecord) {
    if (gDebugOptsCarShadow != 0) {
        func_shadow_00400180(state, &state->frames[state->frameIndex], inputRecord);
    }
}
#line 47 "src/modules/shadow.c"
#line 41 "src/modules/shadow.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/func_shadow_00400498.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/shadow/func_shadow_00400750.s")

