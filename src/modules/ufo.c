// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
typedef struct { u8 unk00[0x10]; Vec3F position; f32 value1C, value20, value24; s32 cameraState, parameter; f32 value30; } UfoAllocatedState;
typedef struct { u8 unk00[4]; s32 (*get)(void); } UfoCameraExports;
typedef struct { u8 unk00[8]; void (*attach)(void *, f32, Vec3F *); u8 unk0C[4]; void (*initialize)(void *); } UfoTdataExports;
extern void *gCamExports, *gTdataExports;
#line 8 "src/modules/ufo.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ufo_00400000(void) {
}
#line 10 "src/modules/ufo.c"

#line 11 "src/modules/ufo.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ufo_00400008(void) {
}
#line 13 "src/modules/ufo.c"

/* Original three-word N64 address storage; no calls use this view.
 * RE_UNKNOWN: original export-table C type and callback 0x08 argument/result
 * contract. The unprototyped declaration only identifies its stored address;
 * recover its body and original consumers before adding a callable prototype. */
typedef struct {
    u32 emptyCallbackAddress;
    u32 allocateStateAddress;
    u32 unknownCallback08Address;
} UfoInitializerAddresses;
void func_ufo_00400058(void);
UfoAllocatedState *ufoAllocateState(s32 parameter, Vec3F *position);
void func_ufo_00400138();
#line 26 "src/modules/ufo.c"
/* Retain the file allocation pointer and publish the three original callback
 * addresses in their original order. This is an N64 address storage view;
 * unresolved callable/source-type contracts are marked at its declaration. */
void __entrypoint_func_ufoInitializeExportAddresses(UfoInitializerAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_ufo_00400058;
    exports->allocateStateAddress = (u32) ufoAllocateState;
    exports->unknownCallback08Address = (u32) func_ufo_00400138;
}
#line 27 "src/modules/ufo.c"

#line 16 "src/modules/ufo.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ufo_00400058(void) {
}
#line 18 "src/modules/ufo.c"

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

