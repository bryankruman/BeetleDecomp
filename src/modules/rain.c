// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[0x12DC]; f32 minX, maxX, minY, maxY; } RainClipBounds;
typedef struct { f32 minX, maxX, minY, maxY; u8 unk10[0x1C]; f32 depth; } RainClipParticle;
typedef struct {
    u8 unk00[0x12C0]; s32 value12C0;
    f32 value12C4, value12C8, value12CC, value12D0;
    u8 flag12D4;
} RainInitialState;

typedef struct { char pad0[0x70]; void (*unk70)(void *); } UnkRainSndExports;
extern UnkRainSndExports *gSndExports;
extern u8 D_rain_004016B8[8];
void rainInitializeStateAndTextures(RainInitialState *state);
void rainReleaseSoundHandle();
void func_rain_00400140();
void rainUpdateMaximumWithValue(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3);
void func_rain_004003D4();
void func_rain_00400678();
void func_rain_004008FC();
void func_rain_00400B2C();
void func_rain_00400D48();
s32 rainIsParticleOutsideClipRange(RainClipBounds *state, RainClipParticle *particle);
void func_rain_00401068();
void func_rain_00401200();
void func_rain_00401304();
void rainPrependFractionCommand(f32 fraction, f32 valueC, f32 value14, f32 value8, f32 value10);
#line 26 "src/modules/rain.c"
/* Clear the original rain state fields in their observed order and load
 * UVTX textures 0x40 and 0x45. Allocation/texture ownership remains unchanged. */
void rainInitializeStateAndTextures(RainInitialState *state) {
    state->flag12D4 = 0;
    state->value12C0 = 0;
    state->value12C4 = 0.0f;
    state->value12CC = 0.0f;
    state->value12C8 = 0.0f;
    state->value12D0 = 0.0f;
    uvLoadFile(0x55565458, 0x40);
    uvLoadFile(0x55565458, 0x45);
}
#line 27 "src/modules/rain.c"

#include "common.h"
#include "file_manager.h"
/* Original address storage only. Assembly-only labels declared below are
 * opaque code addresses, never data objects or inferred callable interfaces.
 * RE_UNKNOWN: remaining callback prototypes and export storage capacity/lifetime.
 * Recover implementations and actual slot consumers before assigning interfaces. */
typedef struct { u32 slots[10]; } RainModuleAddressStorage;
void rainSetStateFlag(void *state, s32 flag);
void rainPrependKindOneCommand(s32 count, f32 valueC, f32 value14, f32 value8, f32 value10);
void rainPrependKindZeroCommand(s32 count, f32 value8, f32 value10, f32 valueC, f32 value14);
extern u8 D_rain_004016B4;
/* Sound slot 0xCC is the validated handle initializer: it writes the
 * byte-invalid emitter and negative generation to the supplied handle.
 * RE_UNKNOWN: full sound export table and handle ownership across module reload.
 * Trace original sound/rain creation and cleanup callers before changing storage. */
typedef struct { u8 opaque00[0xCC]; void (*initializeHandle)(void *); } RainHandleInitializationExports;
#line 44 "src/modules/rain.c"
/* Register original rain export addresses in observed store order, after
 * updating the file allocation pointer. Preserve separate empty callbacks.
 * Slot 0x24 exports shared data; initialize the existing rain sound handle
 * through sound slot 0xCC after registering all addresses.
 * RE_UNKNOWN: original full export type, remaining callback contracts and
 * shared data meanings/lifetime. Resolve each implementation and slot consumer
 * before replacing address-only storage with callable interfaces. */
void __entrypoint_func_rainInitializeModuleExports(RainModuleAddressStorage *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->slots[0] = (u32)rainReleaseSoundHandle; /* 0x00 */
    exports->slots[1] = (u32)func_rain_00400140; /* 0x04 */
    exports->slots[2] = (u32)rainSetStateFlag; /* 0x08 */
    exports->slots[3] = (u32)func_rain_00400678; /* 0x0C */
    exports->slots[4] = (u32)func_rain_00401068; /* 0x10 */
    exports->slots[5] = (u32)func_rain_00401304; /* 0x14 */
    exports->slots[6] = (u32)rainPrependKindOneCommand; /* 0x18 */
    exports->slots[7] = (u32)rainPrependFractionCommand; /* 0x1C */
    exports->slots[8] = (u32)rainPrependKindZeroCommand; /* 0x20 */
    exports->slots[9] = (u32)&D_rain_004016B4; /* 0x24 */
    ((RainHandleInitializationExports *)gSndExports)->initializeHandle(D_rain_004016B8);
}
#line 45 "src/modules/rain.c"

#line 30 "src/modules/rain.c"
/* Release the original shared rain sound handle through sound export
 * 0x70. Handle initialization and ownership remain with the existing callers. */
void rainReleaseSoundHandle(void) {
    gSndExports->unk70(D_rain_004016B8);
}
#line 33 "src/modules/rain.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400140.s")

#line 36 "src/modules/rain.c"
/* Set the original rain-state byte at 0x12D4. Preserve byte narrowing
 * and the caller-owned allocation contract. */
void rainSetStateFlag(void *state, s32 flag) {
    *(u8 *)((u8 *)state + 0x12D4) = flag;
}
#line 39 "src/modules/rain.c"

#line 40 "src/modules/rain.c"
/* Replace the maximum and its associated value only for a strictly
 * larger candidate with a nonnegative associated value. Unordered floating
 * comparisons retain their original behavior. */
void rainUpdateMaximumWithValue(f32 *maximum, f32 candidate, f32 *storedValue, f32 candidateValue) {
    if ((*maximum < candidate) && (candidateValue >= 0.0f)) {
        *storedValue = candidateValue;
        *maximum = candidate;
    }
}
#line 46 "src/modules/rain.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_004003D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_004008FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400D48.s")

#line 57 "src/modules/rain.c"
/* Reject separated two-dimensional bounds or depth outside one through ten.
 * Touching bounds and depth endpoints are accepted. Preserve strict floating
 * comparisons, including the original behavior for unordered values. */
s32 rainIsParticleOutsideClipRange(RainClipBounds *state, RainClipParticle *particle) {
    f32 depth;
    if (particle->maxY < state->minY) return 1;
    if (state->maxY < particle->minY) return 1;
    if (particle->maxX < state->minX) return 1;
    if (state->maxX < particle->minX) return 1;
    depth = particle->depth;
    if (depth < 1.0f) return 1;
    if (depth > 10.0f) return 1;
    return 0;
}
#line 58 "src/modules/rain.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401068.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401200.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401304.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    void * unk18;
} AutoS_00401404_temp_v0;

extern void *D_rain_004016C0;

#line 77 "src/modules/rain.c"
/* Allocate and prepend a kind-one rain command. Scalar meanings remain
 * offset-named; preserve the original slot order and allocation contract. */
void rainPrependKindOneCommand(s32 count, f32 valueC, f32 value14, f32 value8, f32 value10) {
    AutoS_00401404_temp_v0 *node;

    node = _uvMemAllocAlign8(0x1CU);
    node->unk0 = 1;
    node->unk4 = count;
    node->unk8 = value8;
    node->unkC = valueC;
    node->unk10 = value10;
    node->unk14 = value14;
    node->unk18 = (void *) D_rain_004016C0;
    D_rain_004016C0 = node;
}
#line 90 "src/modules/rain.c"

#line 91 "src/modules/rain.c"
/* Prepend a kind-two rain command. Convert fraction times 100 to the
 * original unsigned count and preserve the four scalar fields in their
 * observed slots. Allocation failure and scalar validation are unchanged. */
void rainPrependFractionCommand(f32 fraction, f32 valueC, f32 value14, f32 value8, f32 value10) {
    AutoS_00401404_temp_v0 *node;
    node = _uvMemAllocAlign8(0x1C);
    node->unk0 = 2;
    node->unk4 = (u32)(fraction * 100.0f);
    node->unk8 = value8;
    node->unkC = valueC;
    node->unk10 = value10;
    node->unk14 = value14;
    node->unk18 = D_rain_004016C0;
    D_rain_004016C0 = node;
}
#line 92 "src/modules/rain.c"

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    void * unk18;
} AutoS_0040157C_temp_v0;

extern void *D_rain_004016C0;

#line 105 "src/modules/rain.c"
/* Allocate and prepend a kind-zero rain command. This kind stores its
 * scalar arguments in a different order from kind one and kind two. */
void rainPrependKindZeroCommand(s32 count, f32 value8, f32 value10, f32 valueC, f32 value14) {
    AutoS_0040157C_temp_v0 *node;

    node = _uvMemAllocAlign8(0x1CU);
    node->unk0 = 0;
    node->unk4 = count;
    node->unk8 = value8;
    node->unkC = valueC;
    node->unk10 = value10;
    node->unk14 = value14;
    node->unk18 = (void *) D_rain_004016C0;
    D_rain_004016C0 = node;
}
#line 118 "src/modules/rain.c"

