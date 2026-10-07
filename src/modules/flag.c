// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
/* Original address storage; slot signatures remain separate contracts. */
typedef struct { u32 slots[7]; } FlagModuleAddressStorage;
void func_flag_00400078(void);
#include "uvfvec_rom.h"
#include "matrix_types.h"
#include "uvgfxstate_rom.h"
extern UvGfxState_Rom_Exports *gUvGfxStateExports;
extern s32 D_flag_00401724;
typedef struct FlagDrawRecord_s {
    u8 prefix00[0xC];
    f32 extent0C;
    f32 extent10;
    u8 pad14[0x14];
    Vec3F position;
    u8 pad34[0x14];
    struct FlagDrawRecord_s *next;
} FlagDrawRecord;
typedef struct FlagVisibilityExports_s {
    u8 prefix00[0x2C];
    s32 (*testSphere)(s32, f32, f32, f32, f32);
} FlagVisibilityExports;
#include "uvfvec_rom.h"
#include "uvmath_rom.h"
extern UvMath_Exports *gUvMathExports;
extern f32 D_flag_00401660,D_flag_00401664;
extern void *D_flag_00401728;
typedef struct UnkCbckExports_s {
    char pad[0x10];
    void (*unk10)(s32, void *, s32, s32);
} UnkCbckExports;
typedef struct UnkChanExports_s {
    char pad[0x4];
    void (*unk4)(s32, s32, void *, s32);
} UnkChanExports;
extern UnkCbckExports *gUvCbckExports;
extern UnkChanExports *gUvChanExports;
void func_flag_00400080();
void func_flag_004004A4();
void flagAdjustPositionByDistanceBands(Vec3F *target, Vec3F *position, f32 scale);
void func_flag_004006BC();
void func_flag_004008F4();
void flagUpdateRegisteredRecords();
void func_flag_00400D54();
void flagDrawVisibleRegisteredRecords(s32 channel);
void flagAttachUpdateCallbackToChannel();
void func_flag_00401354();
#line 50 "src/modules/flag.c"
/* Register the original flag module addresses in their observed store order
 * after updating the file allocation pointer. Preserve separate empty exports. The
 * final slot is the address of shared word 0x00401724, not a callback.
 * RE_UNKNOWN: historical full export type and remaining callback signatures,
 * purposes and consumer contracts. Trace slot consumers and original target
 * bodies before assigning callable types or changing empty callbacks. */
void __entrypoint_func_flagInitializeModuleExports(FlagModuleAddressStorage *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->slots[5] = (u32)func_flag_00401354; /* 0x14 */
    exports->slots[0] = (u32)func_flag_00400078; /* 0x00 */
    exports->slots[1] = (u32)func_flag_00400080; /* 0x04 */
    exports->slots[2] = (u32)func_flag_004004A4; /* 0x08 */
    exports->slots[3] = (u32)flagUpdateRegisteredRecords; /* 0x0C */
    exports->slots[4] = (u32)flagAttachUpdateCallbackToChannel; /* 0x10 */
    exports->slots[6] = (u32)&D_flag_00401724; /* 0x18 */
}
#line 51 "src/modules/flag.c"

#line 48 "src/modules/flag.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_flag_00400078(void) {
}
#line 50 "src/modules/flag.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00400080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_004004A4.s")

#line 37 "src/modules/flag.c"
/* Adjust the position along its displacement from the target using two original
 * scale-dependent distance bands. Preserve both strict squared-radius tests,
 * the distinct inward/outward fractions and the original unordered behavior. */
void flagAdjustPositionByDistanceBands(Vec3F *target, Vec3F *position, f32 scale) {
    f32 upperRadius,lowerRadius,dx,dy,dz,lengthSquared;
    f32 upperLength,upperFraction,lowerLength,lowerFraction;
    upperRadius = scale * D_flag_00401660;
    lowerRadius = scale * D_flag_00401664;
    dx = target->x - position->x;
    dy = target->y - position->y;
    dz = target->z - position->z;
    lengthSquared = (dx * dx) + (dy * dy) + (dz * dz);
    if ((upperRadius * upperRadius) < lengthSquared) {
        upperLength = gUvMathExports->uvSqrtf(lengthSquared);
        upperFraction = (upperLength - upperRadius) / upperLength;
        dx *= upperFraction;
        dy *= upperFraction;
        dz *= upperFraction;
        position->x += dx;
        position->y += dy;
        position->z += dz;
        return;
    }
    if ((lowerRadius * lowerRadius) < lengthSquared) {
        lowerLength = gUvMathExports->uvSqrtf(lengthSquared);
        lowerFraction = (lowerRadius - lowerLength) / lowerLength;
        dx *= lowerFraction;
        dy *= lowerFraction;
        dz *= lowerFraction;
        position->x += dx;
        position->y += dy;
        position->z += dz;
    }
}
#line 38 "src/modules/flag.c"

#line 39 "src/modules/flag.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_flag_004006B4(void) {
}
#line 41 "src/modules/flag.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_004006BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_004008F4.s")

#line 46 "src/modules/flag.c"
/* Apply the original per-record helper to every registered flag record
 * in list order. Read the next link after each helper call so any original
 * link changes remain observable.
 * RE_UNKNOWN: The internal behavior of the per-record assembly helper remains unrecovered. */
void flagUpdateRegisteredRecords(void) {
    void *record;

    record = D_flag_00401728;
    if (record != NULL) {
        do {
            func_flag_004008F4(record);
            record = *(void **)((u8 *)record + 0x48);
        } while (record != NULL);
    }
}
#line 57 "src/modules/flag.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00400D54.s")

#line 60 "src/modules/flag.c"
/* Query the channel position and draw registered flag records passing the
 * original sphere-bounds query. Preserve head reloads around graphics-state
 * push/pop and read the next link after each per-record draw helper.
 * RE_UNKNOWN: the individual extent fields and detailed per-record draw
 * behavior remain unproven; retain their offsets and summed bound. */
void flagDrawVisibleRegisteredRecords(s32 channel) {
    FlagDrawRecord *record;
    Vec3F channelPosition;

    record = (FlagDrawRecord *)D_flag_00401728;
    if (D_flag_00401724 == 0) {
        gUvChanExports->unk4(channel, 7, &channelPosition, 0);
        if (D_flag_00401728 != NULL) {
            gUvGfxStateExports->uvGfxStatePush();
            gUvGfxStateExports->uvGfxStateSetFlags(0x620000);
            gUvGfxStateExports->uvGfxClearCurrentStateBits(0xAF9C0000);
        }
        if (record != NULL) {
            do {
                if (((FlagVisibilityExports *)gUvChanExports)->testSphere(channel,
                    record->position.x - channelPosition.x,
                    record->position.y - channelPosition.y,
                    record->position.z - channelPosition.z,
                    record->extent10 + record->extent0C) != 0) {
                    func_flag_00400D54(&channelPosition, record);
                }
                record = record->next;
            } while (record != NULL);
        }
        if (D_flag_00401728 != NULL) {
            gUvGfxStateExports->uvGfxStatePop();
        }
    }
}
#line 61 "src/modules/flag.c"

#line 62 "src/modules/flag.c"
/* Query channel property six and attach the original flag update
 * callback at priority 61, preserving the callback host contract. */
void flagAttachUpdateCallbackToChannel(s32 channel) {
    s32 callbackHost;

    gUvChanExports->unk4(channel, 6, &callbackHost, 0);
    gUvCbckExports->unk10(callbackHost, flagDrawVisibleRegisteredRecords, 0, 0x3D);
}
#line 68 "src/modules/flag.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00401354.s")

