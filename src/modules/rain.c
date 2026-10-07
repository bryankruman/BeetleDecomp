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
void func_rain_0040010C();
void func_rain_00400140();
void func_rain_00400390(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/__entrypoint_func_rain_400054.s")

void func_rain_0040010C(void) {
    gSndExports->unk70(D_rain_004016B8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400140.s")

void func_rain_00400388(void *arg0, s32 arg1) {
    *(u8 *)((u8 *)arg0 + 0x12D4) = arg1;
}

void func_rain_00400390(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3) {
    if ((*arg0 < arg1) && (arg3 >= 0.0f)) {
        *arg2 = arg3;
        *arg0 = arg1;
    }
}

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

void func_rain_00401404(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    AutoS_00401404_temp_v0 *temp_v0;

    temp_v0 = _uvMemAllocAlign8(0x1CU);
    temp_v0->unk0 = 1;
    temp_v0->unk4 = arg0;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = arg1;
    temp_v0->unk10 = arg4;
    temp_v0->unk14 = arg2;
    temp_v0->unk18 = (void *) D_rain_004016C0;
    D_rain_004016C0 = temp_v0;
}

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

void func_rain_0040157C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    AutoS_0040157C_temp_v0 *temp_v0;

    temp_v0 = _uvMemAllocAlign8(0x1CU);
    temp_v0->unk0 = 0;
    temp_v0->unk4 = arg0;
    temp_v0->unk8 = arg1;
    temp_v0->unkC = arg3;
    temp_v0->unk10 = arg2;
    temp_v0->unk14 = arg4;
    temp_v0->unk18 = (void *) D_rain_004016C0;
    D_rain_004016C0 = temp_v0;
}

