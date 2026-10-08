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
/* Initializer-only storage view: each field is an original 32-bit address,
 * not an inferred callable export interface. Opaque assembly declarations
 * below identify linker code-label addresses only: no data object or function
 * signature is inferred, and these addresses are never dereferenced here.
 * RE_UNKNOWN: replace each opaque label declaration with a grounded function
 * prototype when its implementation and actual caller ABI are recovered. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 initializeStateAddress;
    /* 0x08 */ u32 unknownCallback08Address;
    /* 0x0C */ u32 prependSpatialRecordAddress;
    /* 0x10 */ u32 unknownCallback10Address;
    /* 0x14 */ u32 prependParameterRecordAddress;
    /* 0x18 */ u32 unknownCallback18Address;
    /* 0x1C */ u32 unknownCallback1CAddress;
} LightExportAddresses;
void func_light_00400090(void);
void lightInitializeState(LightInitializationState *state, s32 parameter);
void lightPrependSpatialRecord(f32 x, f32 y, f32 z, f32 radius, f32 first, f32 second, f32 third, f32 fourth, f32 fifth, f32 sixth, u8 flags);
void lightPrependParameterRecord(s32 key, f32 first, f32 second, f32 third, f32 fourth, f32 fifth, f32 sixth, f32 seventh, f32 eighth, f32 ninth);
extern u8 func_light_00400120[];
extern u8 func_light_004005AC[];
extern u8 func_light_00400950[];
extern u8 func_light_00400BA8[];

#line 36 "src/modules/light.c"
/* Register the eight original light callback addresses after updating the
 * allocation pointer; then clear the spatial and parameter list heads in
 * their original order. Preserve the empty callback's separate identity.
 * RE_UNKNOWN: callback contracts at slots 0x08/10/18/1C require their original
 * implementations and callers. Export storage capacity/lifetime and whether
 * existing list nodes can be live at initialization remain loader contracts;
 * inspect loader/reload callers before replacing or expanding these resets. */
void __entrypoint_func_lightInitializeModuleExports(LightExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_light_00400090;
    exports->initializeStateAddress = (u32) lightInitializeState;
    exports->unknownCallback08Address = (u32) func_light_00400120;
    exports->prependSpatialRecordAddress = (u32) lightPrependSpatialRecord;
    exports->unknownCallback10Address = (u32) func_light_004005AC;
    exports->prependParameterRecordAddress = (u32) lightPrependParameterRecord;
    exports->unknownCallback18Address = (u32) func_light_00400950;
    exports->unknownCallback1CAddress = (u32) func_light_00400BA8;
    D_light_00400DC4 = NULL;
    D_light_00400DC8 = NULL;
}
#line 37 "src/modules/light.c"

#line 13 "src/modules/light.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_light_00400090(void) {
}
#line 15 "src/modules/light.c"

#line 14 "src/modules/light.c"
/* Allocate the light handle and retain the original scalar defaults.
 * RE_ORIGINAL_QUIRK: signed-16 handle comparison with 65535 cannot reject -1.
 * RE_UNKNOWN: exhaustion/reachable handle values need original allocator/callers. */
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
/*
 * Get float triples from ENV properties 6, 8, and 9, then pass promoted
 * doubles through the LIGHT property parser to the scene record at offset
 * 0x28. Set three 44-byte records starting at offset 0x54 to the original
 * defaults; reload the scene base after every callback.
 * ENV property 6 copies floats at offsets 0x4C, 0x50, and 0x54. Properties
 * 8 and 9 normalize byte triples at offsets 0x06..0x08 and 0x09..0x0B.
 * LIGHT properties 1 and 2 store triples at offsets 0x04..0x0C and
 * 0x1C..0x24; property 3 stores offset 0x28; property 4 stores 0x10..0x18.
 * RE_ORIGINAL_QUIRK: property 4 skips value consumption when the signed
 * halfword at record offset 0x02 is nonzero. This caller still supplies the
 * full triple; the reachable lifecycle of that path remains unknown.
 * RE_UNKNOWN: historical formal and scratch types, physical property
 * meanings, coordinate frames and units, complete scene allocation and
 * ownership, valid resource and parameter domains, callback replacement and
 * aliases, and output initialization after a failed ENV lookup. Resolve the
 * original scene, environment, and light producers and all callback callers.
 * Readable C remains parked: 476 native/draft bytes, 18 differing instruction
 * words for frame and scratch storage, despite all six ordered relocation
 * records matching. The observed property-6 triple grouping changes four
 * storage instructions without resolving the frame difference. Equivalent C
 * and complete packed-module and ROM validation are still required.
 */
#line 22 "src/modules/light.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/light/func_light_00400BA8.s")

