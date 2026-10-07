// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
/* Access prefix only: original AI loads the pointer at 0x1DC and forwards
 * the existing vector at 0x100 plus its scalar at 0x104. RE_UNKNOWN: complete
 * allocation, vector units and caller lifecycle; no full object layout implied. */
typedef struct AiCarAnimationFields {
    u8 opaque00[0x100];
    Vec3F vector100;
    u8 opaque10C[0xD0];
    void *animationState;
} AiCarAnimationFields;
/* Original cara initializer: slot10=00400B08, slot14=00400C8C. Target10
 * dereferences its state; target14 consumes a signed-low16 tagged vararg list.
 * Table D_caranim_004066C0: tag17 copies three floats to 0x3B8..0x3C0;
 * tag14 converts a double to float at 0x3A8; tag0 returns.
 * RE_UNKNOWN: intended historical source declarations and physical units. */
typedef struct AiCarAnimationFieldExports {
    u8 opaque00[0x10];
    void (*applyState)(void *);
    void (*setTaggedFields)(void *, ...);
} AiCarAnimationFieldExports;
#include "uvfvec_rom.h"
#include "module.h"
typedef struct {
    u8 opaque00[0x10];
    Vec3F dotVector;
    u8 opaque1C[0xA2];
    s16 phase;
    u8 opaqueC0[0x28];
    Vec3F position;
} AiTargetSnapState;
typedef struct {
    u8 opaque00[0x328];
    Vec3F dotVector;
    u8 opaque334[0xA8];
    Vec3F position;
} AiTargetSnapTarget;
typedef struct { u8 opaque00[0x14]; AiTargetSnapTarget *target; } AiTargetSnapLink;
extern void *D_ai_00407FF4;
extern f32 D_ai_00407E8C, D_ai_00407858;
extern UvFVec_Rom_Exports *gUvFvecExports;

#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct {
    Mtx4F transform;
    Mtx4F previousTransform;
    u8 opaque80[4];
    f32 value84;
    u8 opaque88[0x2E];
    s16 cameraTest;
    s16 targetDistanceTest;
    s16 valueBA;
    s16 valueBC;
    s16 phase;
    u8 opaqueC0[2];
    u8 byteC2;
    u8 byteC3;
    u8 opaqueC4[8];
    f32 valueCC;
    u8 opaqueD0[8];
    f32 remainingD8;
    u8 opaqueDC[0xC];
    Vec3F vectorE8;
    Vec3F previousVectorE8;
    Vec3F vector100;
    Vec3F previousVector100;
    Vec3F vector118;
    Vec3F previousVector118;
    Vec3F clearedVector130;
    u8 opaque13C[0xA4];
    void *previousLinkNode;
} AiDecisionUpdateState;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern UvFVec_Rom_Exports *gUvFvecExports;
extern void *gTdataExports;
extern f32 D_80025D70;
extern f32 D_80025DDC;

#include "uvfvec_rom.h"
#include "module.h"
typedef struct {
    u8 opaque00[0x30];
    Vec3F position;
    u8 opaque3C[0x60];
    s32 objectHandle;
    u8 opaqueA0[0x1C];
    s16 valueBC;
    s16 phase;
    u8 opaqueC0[3];
    u8 byteC3;
    u8 opaqueC4[0x18];
    f32 remaining;
    f32 valueE0;
    f32 valueE4;
    Vec3F effectPosition;
    u8 opaqueF4[0xE8];
    s32 effectHandle;
} AiEffectDelayState;
/* Caller-proven word ABI only: argument 0x41000000 is left uninterpreted. */
typedef struct {
    u8 opaque00[8];
    s32 (*createForObject)(s32, s32, Vec3F *, u32, f32, s32);
} AiPieceCallExports;
typedef struct {
    u8 opaque00[0x14];
    void (*setPropertyWords)(s32, s32, s32, s32);
    u8 opaque18[0x30];
    void (*bindPieceWord)(s32, s32);
} AiEffectCallExports;
extern Snd_Exports *gSndExports;
extern UvDobj_Exports *gUvDobjExports;
extern void *gPieceExports;
extern UnkStruct_004005C8 D_ai_00408EA0;
extern f32 D_80025D70;

/* Original AI source declares this same export-table pointer later. */
extern void *D_ai_00408E58;

typedef struct { u8 unk00[0x30]; f32 x, y, z; u8 unk3C[0x68]; f32 distance; } AiDistanceState;
typedef struct { u8 unk00[0x348]; f32 x, y, z; } AiDistanceTarget;
typedef struct { u8 unk00[0x14]; AiDistanceTarget *target; } AiDistanceLink;
typedef struct AiLinkedRecord { u8 unk00[8]; s32 word08; struct AiLinkedRecord *previous; struct AiLinkedRecord *next; s32 source; f32 value18; } AiLinkedRecord;
extern s32 D_ai_00408D60;
typedef struct { u8 unk00[0x9C]; s32 value; u8 unkA0[0x14]; s16 active; u8 unkB6[0x132]; } AiIndexedRecord; /* Original stride 0x1E8. */
typedef struct { u8 unk00[0x1D]; u8 excluded; } AiRankActor;
typedef struct { AiRankActor *actor; } AiRankSource;
typedef struct AiRankNode { u8 unk00[0xC]; struct AiRankNode *next; u8 unk10[4]; AiRankSource *source; } AiRankNode;
#include "module.h"
extern UvFVec_Rom_Exports *gUvFvecExports;
/*__SEEDEXTERNS__*/
extern f32 D_ai_0040810C;
extern s32 D_ai_00407EA0;
extern void *D_ai_00408E40;
extern void *D_ai_00407FF4;
extern s32 D_ai_00408E48;
extern s32 D_ai_00408E4C;
extern s32 D_ai_00408008;
void func_ai_00400000();
void func_ai_0040019C();
void func_ai_0040089C();
void func_ai_00400A24();
void aiBuildOrthonormalBasisFromX(Mtx4F *basis, Vec3F *direction);
void func_ai_00400F18();
void func_ai_00400FF0();
void func_ai_004017A4();
void func_ai_004019EC();
void func_ai_00401C84();
void func_ai_00401EF0();
void func_ai_00402028();
void func_ai_004021E0();
void func_ai_004022A4();
void func_ai_00402858();
void func_ai_00402974();
s32 aiUpdateTargetManhattanDistance(AiDistanceState *state);
s32 func_ai_00402AE0(void *);
void func_ai_00402C2C();
void func_ai_00402E4C();
void aiUpdateExplosionEffectAndRestoreDelay(AiEffectDelayState *state);
void aiSnapshotAndUpdateDecisionState(AiDecisionUpdateState *state);
void func_ai_00403448();
void func_ai_004037B4();
void func_ai_00403994();
void func_ai_00403C80();
void func_ai_00403F4C(s32 arg0);
void func_ai_00403F54();
void func_ai_00404064();
void aiCopySelectedRecordScalarPair(void *arg0, void *arg1);
void func_ai_00404194();
void aiSetFlagAndClearScalarPair();
void func_ai_004042A4();
s32 aiSnapPositionToTargetWhenRequired(AiTargetSnapState *state);
s32 func_ai_0040462C(Mtx4F *, Mtx4F *);
s32 aiTestBoundsContainmentEitherOrder(Mtx4F *first, Mtx4F *second);
void func_ai_0040490C();
void func_ai_00404E10();
void func_ai_004051A4();
void func_ai_00405324();
void func_ai_004053A8();
void func_ai_004057C0();
void *aiAllocateLinkedRecord(f32 value, s32 parameter, s32 source);
void func_ai_00405B4C(AiLinkedRecord *, f32, s32, s32);
void aiUnlinkRecord(AiLinkedRecord *record);
void aiInsertRecordBetweenNeighbors();
void func_ai_00405D50();

void func_ai_00405EF4();
s32 aiGetEligibleListRank(AiRankNode *target);
void func_ai_0040617C();
void func_ai_00406400();
void func_ai_004068A8();
void func_ai_004069CC();
void func_ai_00406D84();
void func_ai_00407054();
s32 aiCountPreviousLinks();
void func_ai_004075B8();
s32 aiGetActiveRecordValue9C(u16 index);
extern s32 D_ai_00408E44;
extern s32 D_ai_00407FFC;
extern s32 D_ai_00408000;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040019C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040089C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/__entrypoint_func_ai_400bbc.s")

#line 94 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_00400E38(void) {
}
#line 96 "src/modules/ai.c"

#line 88 "src/modules/ai.c"
/* Set X from direction, cross existing Y to rebuild Z/Y, then normalize; zero-length normalization leaves output unchanged.
 * RE_UNKNOWN: audit callers' nonzero/nonparallel direction/existing-Y initialization before assuming orthonormality; translation/W stay intact. */
void aiBuildOrthonormalBasisFromX(Mtx4F *basis, Vec3F *direction) {
    Vec3F *axisZ;
    Vec3F *axisY;

    gUvFvecExports->uvVec3FCopy((Vec3F *)&basis->m[0][0], direction);
    axisZ = (Vec3F *)&basis->m[2][0];
    axisY = (Vec3F *)&basis->m[1][0];
    gUvFvecExports->uvVec3FCross(axisZ, direction, axisY);
    gUvFvecExports->uvVec3FCross(axisY, axisZ, direction);
    gUvFvecExports->uvVec3FNormalize((Vec3F *)&basis->m[0][0], (Vec3F *)&basis->m[0][0]);
    gUvFvecExports->uvVec3FNormalize(axisY, axisY);
    gUvFvecExports->uvVec3FNormalize(axisZ, axisZ);
}
#line 89 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400FF0.s")

#line 94 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_0040179C(void) {
}
#line 96 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004017A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004019EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00401C84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00401EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402028.s")

#line 107 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_004021D8(void) {
}
#line 109 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004021E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004022A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402974.s")

#line 118 "src/modules/ai.c"
/* Cache the target separation as abs(X) + abs(Y) + abs(Z), preserving the
 * original floating addition order and positive-test absolute-value semantics.
 * Return zero above 105, otherwise one. A missing target link stores zero and
 * returns one; a present link must contain a valid target pointer. */
s32 aiUpdateTargetManhattanDistance(AiDistanceState *state) {
    f32 z;
    f32 distance;
    f32 x;
    f32 y;
    f32 absY;
    f32 absZ;
    f32 absX;
    AiDistanceTarget *target;
    if (D_ai_00407FF4 == NULL) { state->distance = 0; return 1; }
    target = ((AiDistanceLink *)D_ai_00407FF4)->target;
    x = target->x - state->x;
    y = target->y - state->y;
    z = target->z - state->z;
    if (y > 0.0f) absY = y; else absY = -y;
    if (x > 0.0f) absX = x; else absX = -x;
    if (z > 0.0f) absZ = z; else absZ = -z;
    distance = absX + absY;
    distance = absZ + distance;
    state->distance = distance;
    if (distance > 105.0f) return 0;
    return 1;
}
#line 119 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402E4C.s")

#line 126 "src/modules/ai.c"
/* A positive phase creates the piece effect and car-explosion sound, clears
 * object flag mask 0x01, then starts the original two-unit restore countdown.
 * Phase -1 advances that countdown in the same call; expiry restores that mask
 * and sets halfword BC to one. Preserve callback and field-store order.
 * RE_UNKNOWN: piece parameter/model meanings, effect property 0x1B, phase
 * ownership, scalar units and fields BC/C3/E0/E4 need caller/callee confirmation.
 * The original !(remaining > 0) test also expires a NaN countdown; do not
 * replace it with remaining <= 0 or impose a new positive-delta contract. */
void aiUpdateExplosionEffectAndRestoreDelay(AiEffectDelayState *state) {
    s16 phase;

    phase = state->phase;
    if (phase > 0) {
        gSndExports->sndInitializeHandle(&D_ai_00408EA0);
        state->effectPosition.z = state->effectPosition.z + 2.0f;
        ((AiEffectCallExports *)D_ai_00408E58)->bindPieceWord(
            ((AiPieceCallExports *)gPieceExports)->createForObject(
                state->objectHandle, 0x63, &state->effectPosition,
                0x41000000, 2.0f, -1), state->effectHandle);
        gSndExports->sndPlayManagedSpatialSound(&D_ai_00408EA0, CAREXPLODE,
            0x7FFF, gSndExports->sndGetSfxVolumeScale(), 1.0f, 0.0f,
            (UnkStruct_uvemitter_rom_004008CC *)state);
        ((AiEffectCallExports *)D_ai_00408E58)->setPropertyWords(
            state->effectHandle, 0x1B, 0, 0);
        gUvDobjExports->uvDobjClearFlagBits(state->objectHandle, 1);
        state->phase = -1;
        state->byteC3 = 0;
        phase = state->phase;
        state->remaining = 2.0f;
        state->valueE4 = 0.0f;
        state->valueE0 = 0.0f;
        state->position.z = -1000.0f;
    }
    if (phase == -1) {
        state->remaining = state->remaining - D_80025D70;
        if (!(state->remaining > 0.0f)) {
            gUvDobjExports->uvDobjSetFlagBits(state->objectHandle, 1);
            state->phase = 0;
            state->valueBC = 1;
        }
    }
}
#line 127 "src/modules/ai.c"

#line 128 "src/modules/ai.c"
/* With track data available, snapshot the transform and three vectors,
 * update camera/distance tests, decrement a positive remaining value and
 * clear the original per-update fields. Dispatch through the original phase
 * and marker tests, preserving helper calls, reloads and store order.
 * RE_UNKNOWN: vector/scalar units, threshold/phase ownership and the three
 * terminal dispatch routines' complete roles. Recover the remaining dispatch
 * callees and audit original callers/vector consumers to establish them.
 * The original link-count call assumes a valid previous-link node; trace its
 * producers before adding a null guard. Negative/NaN remaining values are
 * unchanged, and both ordered threshold comparisons exclude NaNs. */
void aiSnapshotAndUpdateDecisionState(AiDecisionUpdateState *state) {
    f32 remaining;

    if (gTdataExports != NULL) {
        gUvFmtxExports->uvMat4FCopy(&state->previousTransform, &state->transform);
        gUvFvecExports->uvVec3FCopy(&state->previousVectorE8, &state->vectorE8);
        gUvFvecExports->uvVec3FCopy(&state->previousVector100, &state->vector100);
        gUvFvecExports->uvVec3FCopy(&state->previousVector118, &state->vector118);
        state->cameraTest = func_ai_00402AE0(state);
        state->targetDistanceTest = aiUpdateTargetManhattanDistance((AiDistanceState *)state);
        remaining = state->remainingD8;
        if (remaining > 0.0f) {
            state->remainingD8 = remaining - D_80025D70;
        }
        state->byteC3 = 0;
        state->clearedVector130.z = 0.0f;
        state->clearedVector130.y = 0.0f;
        state->clearedVector130.x = 0.0f;
        if ((D_80025DDC <= state->valueCC) &&
            (D_80025DDC <= (state->valueCC -
                ((f32)aiCountPreviousLinks(state->previousLinkNode) * 3.0f)))) {
            aiSetFlagAndClearScalarPair(state);
        }
        if (state->phase == 0) {
            if (state->byteC2 != 0) {
                state->value84 = 0.0f;
                return;
            }
            if (state->valueBC == 0) {
                if ((state->targetDistanceTest == 0) && (state->valueBA == 0)) {
                    func_ai_00402858(state);
                    return;
                }
                func_ai_00402974(state);
                func_ai_004019EC(state);
            }
        }
    }
}
#line 129 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403448.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004037B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403994.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403C80.s")

#line 138 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_00403F44(void) {
}
#line 140 "src/modules/ai.c"

#line 141 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_00403F4C(s32 arg0) {

}
#line 144 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00404064.s")

#line 149 "src/modules/ai.c"
/* When a shared record is selected, copy its scalar from the original
 * 0x1E8-byte record array and set the second output to zero. A selection of
 * -1 leaves both outputs untouched; other index validation remains caller-owned.
 * RE_UNKNOWN: The selected scalar meaning and units are not established. */
void aiCopySelectedRecordScalarPair(void *selectedValue, void *zeroValue) {
    s32 selectedIndex = D_ai_00407EA0;
    if (selectedIndex != -1) {
        *(f32 *)selectedValue = *(f32 *)((u8 *)&D_ai_0040810C + selectedIndex * 0x1E8);
        *(f32 *)zeroValue = 0.0f;
    }
}
#line 156 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00404194.s")

#line 159 "src/modules/ai.c"
/* Set record byte 0xC2 to one and clear floating fields 0x84 and 0xB0
 * in their observed order. Their physical meanings remain unresolved. */
void aiSetFlagAndClearScalarPair(void *record) {
    *(u8 *)((u8 *)record + 0xC2) = 0x1;
    *(f32 *)((u8 *)record + 0x84) = 0.0f;
    *(f32 *)((u8 *)record + 0xB0) = 0.0f;
}
#line 164 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004042A4.s")

#line 167 "src/modules/ai.c"
/* Evaluate the dot callback and compare target separation against the
 * squared product threshold unless settings force a snap. On success copy
 * target coordinates and set zero phase BE to one; retain every target reload.
 * RE_UNKNOWN: settings/threshold/phase roles and target validity across
 * callbacks need writers/callers. The selector can store a null shared link;
 * this routine dereferences it even for a forced snap or unused dot result. */
s32 aiSnapPositionToTargetWhenRequired(AiTargetSnapState *state) {
    Vec3F separation;
    f32 distanceSquared;
    f32 threshold;
    s32 forceSnap;

    forceSnap = gGameSettings->pad6FA4[3] == 2;
    if (gGameSettings->unk6F74 == 2) forceSnap = 0;
    gUvFvecExports->uvVec3FDot(&state->dotVector,
        &((AiTargetSnapLink *)D_ai_00407FF4)->target->dotVector);
    gUvFvecExports->uvVec3FSub(&separation,
        &((AiTargetSnapLink *)D_ai_00407FF4)->target->position, &state->position);
    distanceSquared = gUvFvecExports->uvVec3FLenSquared(&separation);
    if (forceSnap != 0 ||
        (threshold = D_ai_00407E8C * D_ai_00407858, threshold * threshold < distanceSquared)) {
        state->position.x = ((AiTargetSnapLink *)D_ai_00407FF4)->target->position.x;
        state->position.y = ((AiTargetSnapLink *)D_ai_00407FF4)->target->position.y;
        state->position.z = ((AiTargetSnapLink *)D_ai_00407FF4)->target->position.z;
        if (state->phase == 0) state->phase = 1;
        return 1;
    }
    return 0;
}
#line 168 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040462C.s")

#line 171 "src/modules/ai.c"
/* Run the original transformed nine-point bounds-containment test in each
 * order. Short-circuit after the first hit; boundary rules belong to that test. */
s32 aiTestBoundsContainmentEitherOrder(Mtx4F *first, Mtx4F *second) {
    if (func_ai_0040462C(first, second) || func_ai_0040462C(second, first)) {
        return 1;
    }
    return 0;
}
#line 172 "src/modules/ai.c"

#line 173 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_00404904(void) {
}
#line 175 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040490C.s")

#line 178 "src/modules/ai.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ai_00404DE8(void) {
}
#line 180 "src/modules/ai.c"

#line 181 "src/modules/ai.c"
/* Clear record short 0xA only when the shared AI flag is nonzero;
 * preserve the unused second parameter and original ABI. */
void aiClearRecordShortWhenEnabled(void *record, s16 unused) {
    if (D_ai_00407FFC) {
        *(s16 *)((u8 *)record + 0xA) = 0;
    }
}
#line 186 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00404E10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004051A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004053A8.s")

extern void *D_ai_00408E58;

#line 197 "src/modules/ai.c"
/* Copy AI floats at 0x100/0x104/0x108 to car-animation fields
 * 0x3B8/0x3BC/0x3C0 through tag 0x11; tag 0xE separately copies float
 * 0x104 to field 0x3A8 after the original variadic double promotion.
 * Tag zero terminates the list. Then apply the animation state, reloading
 * its pointer at AI offset 0x1DC and the dependency after the first call.
 * RE_UNKNOWN: physical field meanings/units, complete AI allocation and
 * lifecycle guarantees, and intended historical source declarations.
 * Trace original field producers/consumers before assigning physical names
 * or treating the access prefix as the complete AI object. */
void aiApplyCarAnimationStateFields(AiCarAnimationFields *state) {
    ((AiCarAnimationFieldExports *)D_ai_00408E58)->setTaggedFields(
        state->animationState, 0x11, &state->vector100,
        0xE, (f64)state->vector100.y, 0);
    ((AiCarAnimationFieldExports *)D_ai_00408E58)->applyState(state->animationState);
}
#line 205 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004057C0.s")

#line 208 "src/modules/ai.c"
/* Select an original eight-record slot, clear links/scalars, then run helper 05B4C.
 * RE_UNKNOWN: shared index D_ai_00408E48 also resets/recounts in aiCountPreviousLinks; occupancy/lifetime is unproven.
 * Audit both helpers' call order and all index writers before treating this index as persistent allocation. */
void *aiAllocateLinkedRecord(f32 value, s32 parameter, s32 source) {
    AiLinkedRecord *record;
    if (D_ai_00408E48 >= 8) return NULL;
    record = &((AiLinkedRecord *)&D_ai_00408D60)[D_ai_00408E48];
    D_ai_00408E48++;
    record->previous = NULL;
    record->next = NULL;
    record->word08 = 0;
    record->source = source;
    record->value18 = 0.0f;
    func_ai_00405B4C(record, value, parameter, source);
    return record;
}
#line 209 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405B4C.s")

#line 212 "src/modules/ai.c"
/* Remove a linked record from its neighbors and update the shared head/tail.
 * An already detached non-head record is unchanged. Reload links after writes
 * so original aliasing behavior is preserved, then clear both record links. */
void aiUnlinkRecord(AiLinkedRecord *record) {
    if (record->next != NULL || record->previous != NULL || record == D_ai_00408E40) {
        if (record->previous != NULL) record->previous->next = record->next;
        if (record->next != NULL) record->next->previous = record->previous;
        if (record->previous == NULL) D_ai_00408E40 = record->next;
        if (record->next == NULL) D_ai_00408E44 = (s32)record->previous;
        record->next = NULL;
        record->previous = NULL;
    }
}
#line 213 "src/modules/ai.c"

#line 214 "src/modules/ai.c"
/* Link the record between its supplied previous and next neighbors,
 * updating the shared head or tail when the corresponding neighbor is null. */
void aiInsertRecordBetweenNeighbors(void *record, void *previous, void *next) {
    *(s32 *)((u8 *)record + 0x10) = (s32)next;
    *(s32 *)((u8 *)record + 0xC) = (s32)previous;
    if (previous == NULL) {
        D_ai_00408E40 = record;
    } else {
        *(s32 *)((u8 *)previous + 0x10) = (s32)record;
    }
    if (next == NULL) {
        D_ai_00408E44 = (s32)record;
        return;
    }
    *(s32 *)((u8 *)next + 0xC) = (s32)record;
}
#line 228 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405D50.s")

#line 229 "src/modules/ai.c"
/* Find the first active AI record with this key, or return -1.
 * The record stride and field offsets come from the original lookup code. */
typedef struct {
    u8 pad0[0x9C];
    s32 key;
    u8 padA0[0x14];
    s16 active;
    u8 padB6[0x132];
} AiLookupRecord;
s32 aiFindActiveRecordByKey(s32 value) {
    s32 index;
    for (index = 0; index < D_ai_00408E4C; index = (index + 1) & 0xFFFF) {
        AiLookupRecord *record = &((AiLookupRecord *)&D_ai_00408008)[index];
        if (record->active != 0 && value == record->key) return index;
    }
    return -1;
}
#line 230 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405EF4.s")

#line 233 "src/modules/ai.c"
/* Return one plus the number of eligible predecessors, or zero if absent.
 * A predecessor counts when its source actor is absent or its exclusion byte
 * is zero; the target itself is not filtered by that byte. */
s32 aiGetEligibleListRank(AiRankNode *target) {
    AiRankNode *node = (AiRankNode *)D_ai_00408E44;
    AiRankActor *actor;
    s32 rank = 1;
    while (node != NULL) {
        if (node == target) {
            break;
        }
        actor = node->source->actor;
        if (actor == NULL || actor->excluded == 0) {
            rank++;
        }
        node = node->next;
    }
    if (node == NULL) {
        rank = 0;
    }
    return rank;
}
#line 234 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040617C.s")

#line 237 "src/modules/ai.c"
/* Walk backward from the shared list tail while record word eight is
 * nonzero. Store the first unmarked record and return its one-based position;
 * a null tail or traversal past the head returns one and stores null.
 * RE_UNKNOWN: The meaning of the nonzero word-eight marker remains unproven. */
s32 aiSelectFirstUnmarkedPreviousRecord(void) {
    s32 count;
    void *node;

    node = D_ai_00408E44;
    count = 1;
    if (node != NULL) {
loop:
        if (*(s32 *)((u8 *)node + 0x8) != 0) {
            node = *(void **)((u8 *)node + 0xC);
            count += 1;
            if (node != NULL) {
                goto loop;
            }
        }
    }
    if (node == NULL) {
        count = 1;
    }
    D_ai_00407FF4 = node;
    return count;
}
#line 259 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00406400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004068A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004069CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00406D84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00407054.s")

#line 270 "src/modules/ai.c"
/* Return the shared linked-record tail using the original signed-word
 * address contract. Null remains zero; no ownership is transferred. */
s32 aiGetLinkedRecordTailAddress(void) {
    return D_ai_00408E44;
}
#line 273 "src/modules/ai.c"

#line 274 "src/modules/ai.c"
/* Set the shared gate used by aiClearRecordShortWhenEnabled.
 * Preserve the full caller word rather than normalizing it to a boolean. */
void aiSetRecordShortClearEnabled(s32 enabled) {
    D_ai_00407FFC = enabled;
}
#line 277 "src/modules/ai.c"

#line 278 "src/modules/ai.c"
/* Count links at offset 0xC before the first null predecessor, storing
 * and returning the shared count. The input node itself is not counted
 * and must be nonnull under the original caller contract. */
s32 aiCountPreviousLinks(void *node) {
    D_ai_00408E48 = 0;
    if (*(s32 *)((u8 *)node + 0xC) != 0) {
        do {
            D_ai_00408E48++;
            node = *(void **)((u8 *)node + 0xC);
        } while (*(s32 *)((u8 *)node + 0xC) != 0);
    }
    return D_ai_00408E48;
}
#line 288 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004075B8.s")

#line 291 "src/modules/ai.c"
/* Store the caller word without boolean normalization. Original func_ai_00402028 uses nonzero to bypass both difference bounds and choose adjustment 9 instead of 4.5. RE_UNKNOWN: shared-word ownership, lifetime and other consumers require caller/export evidence. */
void func_ai_00407718(s32 value) {
    D_ai_00408000 = value;
}
#line 294 "src/modules/ai.c"

#line 295 "src/modules/ai.c"
/* Return field 0x9C for an active indexed 0x1E8-byte AI record, otherwise -1.
 * Preserve the original unsigned-16 index conversion and signed count check. */
s32 aiGetActiveRecordValue9C(u16 index) {
    AiIndexedRecord *record;
    if (index < D_ai_00408E4C) {
        record = &((AiIndexedRecord *)&D_ai_00408008)[index];
        if (record->active != 0) {
            return record->value;
        }
    }
    return -1;
}
#line 296 "src/modules/ai.c"

