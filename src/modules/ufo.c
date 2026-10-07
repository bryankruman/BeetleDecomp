// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
typedef struct { u8 unk00[0x10]; Vec3F position; f32 value1C, value20, value24; s32 cameraState, parameter; f32 value30; } UfoAllocatedState;
typedef struct { u8 unk00[4]; s32 (*get)(void); } UfoCameraExports;
typedef struct { u8 unk00[8]; void (*attach)(void *, f32, Vec3F *); u8 unk0C[4]; void (*initialize)(void *); } UfoTdataExports;
extern void *gCamExports, *gTdataExports;
void func_ufo_00400000(void) {
}

void func_ufo_00400008(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ufo/__entrypoint_func_ufo_400010.s")

void func_ufo_00400058(void) {
}

#line 19 "src/modules/ufo.c"
/* Allocate and clear the original 0x34-byte UFO state, retain its parameter
 * and starting position, obtain shared camera state, then run the original
 * track-data initialization/attachment hooks when available. The attachment
 * scalar is floating zero; opaque state fields retain offset-based names. */
UfoAllocatedState *ufoAllocateState(s32 parameter, Vec3F *position) {
    UfoAllocatedState *state = _uvMemAllocAlign8(0x34);
    uvMemSet(state, 0, 0x34);
    state->parameter = parameter;
    state->value1C = 0.0f;
    state->value20 = 0.0f;
    state->value24 = 0.0f;
    state->position = *position;
    state->value30 = 0.0f;
    state->cameraState = ((UfoCameraExports *)gCamExports)->get();
    if (gTdataExports != NULL) {
        ((UfoTdataExports *)gTdataExports)->initialize(state);
        ((UfoTdataExports *)gTdataExports)->attach(state, 0.0f, position);
    }
    return state;
}
#line 20 "src/modules/ufo.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ufo/func_ufo_00400138.s")

