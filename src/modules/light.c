// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct LightSpatialRecord { f32 values00[3]; f32 position[3]; f32 values18[3]; f32 radiusSquared; u8 flags; u8 unk29[3]; struct LightSpatialRecord *next; } LightSpatialRecord;
extern LightSpatialRecord *D_light_00400DC4;
#include "module.h"
extern UvLights_Exports *gUvLightExports;
typedef struct { s16 handle; s16 parameter; f32 value04, value08, value0C, value10, value14, value18, value1C, value20, value24, value28; } LightInitializationState;
#include "common.h"
typedef struct LightListRecord { s32 key; f32 values[9]; struct LightListRecord *next; } LightListRecord;
extern LightListRecord *D_light_00400DC8;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/light/__entrypoint_func_light_400000.s")

void func_light_00400090(void) {
}

#line 14 "src/modules/light.c"
/* Allocate a light handle and initialize the original scalar defaults.
 * Preserve the original signed-16-bit handle comparison against 65535: it does
 * not catch allocator failure -1. Capacity/caller reachability needs auditing. */
void lightInitializeState(LightInitializationState *state, s32 parameter) {
    state->handle = gUvLightExports->uvLightAllocateDirectionalSet();
    if (state->handle != 0xFFFF) {
        state->parameter = parameter;
        state->value04 = 0.0f;
        state->value08 = 0.0f;
        state->value10 = 0.0f;
        state->value14 = 0.0f;
        state->value24 = 0.0f;
        state->value18 = 0.0f;
        state->value1C = 0.0f;
        state->value20 = 0.0f;
        state->value28 = 0.0f;
        state->value0C = -1.0f;
    }
}
#line 15 "src/modules/light.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/light/func_light_00400120.s")

#line 18 "src/modules/light.c"
/* Prepend the original 48-byte spatial light record. Store position, both
 * parameter triples, squared influence radius and flags in their original order.
 * The consumer compares squared distance against this radius before selection. */
void lightPrependSpatialRecord(f32 x, f32 y, f32 z, f32 radius, f32 first, f32 second, f32 third, f32 fourth, f32 fifth, f32 sixth, u8 flags) {
    LightSpatialRecord *record = _uvMemAllocAlign8(sizeof(LightSpatialRecord));
    record->position[0] = x;
    record->position[1] = y;
    record->position[2] = z;
    record->values18[0] = fourth;
    record->values18[1] = fifth;
    record->values18[2] = sixth;
    record->radiusSquared = radius * radius;
    record->values00[0] = first;
    record->values00[1] = second;
    record->values00[2] = third;
    record->flags = flags;
    record->next = D_light_00400DC4;
    D_light_00400DC4 = record;
}
#line 19 "src/modules/light.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/light/func_light_004005AC.s")

#line 18 "src/modules/light.c"
/* Allocate and prepend the original 44-byte light record, preserving all nine
 * parameter values in order. Callers retain the original allocation contract. */
void lightPrependParameterRecord(s32 key, f32 first, f32 second, f32 third, f32 fourth, f32 fifth, f32 sixth, f32 seventh, f32 eighth, f32 ninth) {
    LightListRecord *record = _uvMemAllocAlign8(sizeof(LightListRecord));
    record->key = key;
    record->values[0] = first;
    record->values[1] = second;
    record->values[2] = third;
    record->values[3] = fourth;
    record->values[4] = fifth;
    record->values[5] = sixth;
    record->values[6] = seventh;
    record->values[7] = eighth;
    record->values[8] = ninth;
    record->next = D_light_00400DC8;
    D_light_00400DC8 = record;
}
#line 19 "src/modules/light.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/light/func_light_00400950.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/light/func_light_00400BA8.s")

