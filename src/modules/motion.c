// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
typedef struct { u8 prefix[0x91C]; f32 firstScale; u8 gap920[0x18]; Vec3F secondScale; u8 gap944[0x58]; Vec3F first; u8 gap9A8[0x18]; Vec3F second; } MotionBasisAccumulator;
typedef struct { u8 prefix[0xC]; Vec3F coefficients; u8 gap18[0x40]; Vec3F firstX, firstY, firstZ; u8 gap7C[0x18]; Vec3F secondX, secondY, secondZ; } MotionBasisContribution;
#include "uvfvec_rom.h"
typedef struct { Vec3F position; f32 scalarC, scalar10, time; } MotionHistorySample;
typedef struct { MotionHistorySample samples[10]; f32 remaining; s32 index, markedIndex; u8 gapFC[0x51C]; Vec3F position; u8 gap624[0x4C]; f32 scalar670; u8 gap674[0x50]; f32 scalar6C4; } MotionHistoryState;
typedef struct { u8 prefix[8]; void (*update)(void *, f32, void *); } MotionHistoryTrackExports;
extern void *gTdataExports;
typedef struct { u8 prefix[0x111]; u8 flag; } MotionFlagState;
typedef struct { u8 prefix[0xA]; s16 value; } MotionFlagOutput;
typedef struct { u8 prefix[0x18]; MotionFlagState **(*record)(s32); s32 (*find)(s32); } MotionLookupExports;
typedef struct { u8 prefix[0x38]; s32 (*find)(s32, s32); } MotionAiLookupExports;
extern MotionLookupExports *D_motion_00416A88;
extern MotionAiLookupExports *gAiExports;

#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct { u8 prefix[0x984]; Vec3F linear, angular; } MotionVelocityState;
typedef struct { u8 prefix[0x30]; Vec3F offset; u8 gap[0x40]; Vec3F axisX, axisY; } MotionProjectionRecord;
typedef struct { u8 prefix[0x944]; Mtx4F matrix; u8 gap984[0x60]; Vec3F direction, transformed; u8 gap9FC[0x734]; u16 count; u8 gap1132[6]; Vec3F first; u8 gap1144[4]; Vec3F second; } MotionDirectionState;
typedef struct { s32 value0, index; u16 alternate; } MotionPointSelector;
extern UvFVec_Rom_Exports *gUvFvecExports;

#include "uvfvec_rom.h"
typedef struct { u8 unk00[0x6A0]; f32 rotationX; f32 rotationY; u8 unk6A8[0x2DC]; f32 component984; f32 component988; u8 unk98C[0xC]; f32 scale998; } MotionPlanarState;
typedef struct { u16 kind; u8 unk02[0x2E]; f32 offset30; f32 offset34; } MotionPlanarRecord;
void func_motion_004055BC(void *);
void motionComputePlanarRecordVector(MotionPlanarState *, MotionPlanarRecord *, Vec3F *);
typedef struct { u8 unk00[0x690]; f32 value690; u8 unk694[0x2F4]; f32 value988; u8 unk98C[0x14]; f32 value9A0; } MotionCorrectionState;
extern f32 D_motion_00416080, D_motion_00416084, D_motion_00416088, D_motion_00416090;
typedef struct { u8 unk00[0x126C]; s32 battleHandle; } MotionBattleState;
typedef struct { u8 unk00[0xC]; void (*notify)(s32); } MotionBattleExports;
extern MotionBattleExports *gBattleExports;
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
extern UvFMtx_Rom_Exports *gUvFmtxExports;
typedef struct { u8 unk00[0x5E8]; Mtx4F matrix; } MotionMatrixState;
#include "module.h"
extern UvGrph_Exports *gUvGrphExports;
extern UvGrphStruct D_motion_004163A8;
extern UvGrphStruct D_motion_0041644C;
extern Snd_Exports *gSndExports;
extern UvMath_Exports *gUvMathExports;
extern void *D_motion_00416B10;
extern s32 D_motion_00416AB8;
void motionUnloadModulesAndStopEmitters();
void func_motion_004002EC();
void func_motion_00400748();
void func_motion_00400D74();
void func_motion_00400F54();
void func_motion_0040130C();
void func_motion_004013B0();
void func_motion_004017E4();
void func_motion_00401B94();
void motionClearVelocityFields();
void motionRecordHistoryAndUpdateTrack(MotionHistoryState *state);
void func_motion_004039BC();
void func_motion_00403C04();
void motionClearValueForFlaggedLookup(MotionFlagState *state, MotionFlagOutput *output, s32 key);
void func_motion_00403E74();
void func_motion_0040424C();
void func_motion_0040441C();
void func_motion_0040456C();
void func_motion_00404868();
void motionCopyMatrix5E8(MotionMatrixState *state, Mtx4F *output);
void func_motion_00404C24();
void motionUpdateFourPlanarRecords(MotionPlanarState *state);
void func_motion_004055BC();
void motionComputePlanarRecordVector(MotionPlanarState *state, MotionPlanarRecord *record, Vec3F *output);
void motionProjectPointVelocity(MotionVelocityState *state, MotionProjectionRecord *record, Vec3F *output);
void func_motion_004057E4();
void func_motion_00405B44();
void func_motion_00405D7C();
void motionUpdateSharedState();
void func_motion_00405EBC();
void func_motion_004061FC();
void func_motion_00406478();
void func_motion_004066E4();
void func_motion_00406A58();
void func_motion_00406C30();
void func_motion_004077A8();
void func_motion_00407B44();
void func_motion_00407C10();
void func_motion_00407FC0();
void func_motion_00408254();
void func_motion_004087DC();
void func_motion_00408940();
void func_motion_00408A84();
void motionTransformSelectedPointVelocity(MotionVelocityState *state, Vec3F *output, MotionPointSelector *selector);
void func_motion_00408FD4();
void func_motion_00409734();
void func_motion_004098B8();
void motionRunBattleAndHotLavaUpdate(MotionBattleState *state, s32 context);
extern s32 gCurrentGameState;
void func_motion_00409B3C();
void func_motion_00409C68();
void func_motion_0040A3CC();
void func_motion_0040B4EC();
void func_motion_0040B7B8();
void func_motion_0040BBE0();
void func_motion_0040BFE0();
void func_motion_0040C7DC();
void func_motion_0040C8A0();
void func_motion_0040E7BC();
void motionAccumulateScaledBasisVectors(MotionBasisAccumulator *state, MotionBasisContribution *impulse);
void func_motion_0040F2EC();
void motionApplyConditionalCorrection(MotionCorrectionState *state);
void func_motion_0040F424();
void func_motion_0040F534();
void func_motion_0040F694();
void func_motion_0040FE84();
void func_motion_00411BB4();
void func_motion_00411C64();
void func_motion_00412770();
void func_motion_00412B14();
void func_motion_00412CF0();
void func_motion_00412E44();
void func_motion_00412F38();
void func_motion_004130E4(void *, void *, s32);
void func_motion_00413284();
void func_motion_00413568();
void func_motion_00414430();
void func_motion_00414774();
void func_motion_00414A70();
void func_motion_00414BB0();
void func_motion_004151CC();
void func_motion_004154B8();
void func_motion_00415724();
f32 motionEvaluateSelectedGraph(f32 value, s32 alternate);
void motionTryPlayHotLavaVoice(void);
void motionTryPlayExplosionVoice(void);
void func_motion_00415A3C();
void func_motion_00411C64(void *a0, s32 a1, void *a2, s32 a3);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/__entrypoint_func_motion_400000.s")

#line 94 "src/modules/motion.c"
/* Unload track/player modules and stop the motion sound emitters.
 * The optional second emitter uses 0xFF as its absent sentinel. */
#include "module.h"
extern UvEmitter_Exports *gUvEmitterExports;
extern u8 D_motion_00416AF0;
extern u8 D_motion_00416AF1;
void motionUnloadModulesAndStopEmitters(void) {
    uvUnloadModule(0x7472636B);
    uvUnloadModule(0x706C7972);
    gUvEmitterExports->uvEmitterStop(D_motion_00416AF0);
    if (D_motion_00416AF1 != 0xFF) gUvEmitterExports->uvEmitterStop(D_motion_00416AF1);
}
#line 95 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004002EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00400748.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00400D74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00400F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040130C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004013B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004017E4.s")

#line 110 "src/modules/motion.c"
/* Copy all 0x1294 bytes of the original motion state, preserving the
 * media-copy helper contract. */
void motionCopyState(void *destination, void *source) {
    _uvMediaCopy(destination, source, 0x1294);
}
#line 113 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00401B94.s")

#line 116 "src/modules/motion.c"
/* Clear the original halfword 0x70C and five three-component floating
 * regions at 0x984, 0x990, 0x99C, 0x9C0 and 0x9D8. Preserve their original
 * store order; only the first two vector roles are established. */
void motionClearVelocityFields(void *state) {
    *(s16 *)((u8 *)state + 0x70C) = 0;
    *(f32 *)((u8 *)state + 0x98C) = 0.0f;
    *(f32 *)((u8 *)state + 0x988) = 0.0f;
    *(f32 *)((u8 *)state + 0x984) = 0.0f;
    *(f32 *)((u8 *)state + 0x9E0) = 0.0f;
    *(f32 *)((u8 *)state + 0x9DC) = 0.0f;
    *(f32 *)((u8 *)state + 0x9D8) = 0.0f;
    *(f32 *)((u8 *)state + 0x998) = 0.0f;
    *(f32 *)((u8 *)state + 0x994) = 0.0f;
    *(f32 *)((u8 *)state + 0x990) = 0.0f;
    *(f32 *)((u8 *)state + 0x9A4) = 0.0f;
    *(f32 *)((u8 *)state + 0x9A0) = 0.0f;
    *(f32 *)((u8 *)state + 0x99C) = 0.0f;
    *(f32 *)((u8 *)state + 0x9C8) = 0.0f;
    *(f32 *)((u8 *)state + 0x9C4) = 0.0f;
    *(f32 *)((u8 *)state + 0x9C0) = 0.0f;
}
#line 134 "src/modules/motion.c"

#line 135 "src/modules/motion.c"
/* Advance the ten-slot history after the original floating countdown
 * crosses zero. Copy the position, two state scalars and shared field 0x7C,
 * invalidate an overwritten marked slot, then update optional track data. */
void motionRecordHistoryAndUpdateTrack(MotionHistoryState *state) {
    f32 remaining;
    s32 index;
    MotionHistorySample *sample;
    state->remaining -= gGameSettings->unk80;
    remaining = state->remaining;
    if (remaining < 0.0f) {
        index = ++state->index;
        state->remaining = remaining + 1.0f;
        if (index >= 10) { state->index = 0; index = 0; }
        sample = &state->samples[index];
        sample->position = state->position;
        sample->scalarC = state->scalar670;
        sample->scalar10 = state->scalar6C4;
        sample->time = gGameSettings->unk7C;
        if (state->markedIndex == state->index) state->markedIndex = -1;
    }
    if (gTdataExports != NULL) {
        ((MotionHistoryTrackExports *)gTdataExports)->update((u8 *)state + 0x100, 100.0f, &state->position);
    }
}
#line 136 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004039BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00403C04.s")

#line 141 "src/modules/motion.c"
/* Find the primary record for a key and optionally query the AI module.
 * Clear output halfword 0xA when this state is flagged and either lookup
 * succeeds, or when the primary referenced state is flagged. Preserve the
 * original nonnull returned-record contract and signed lookup sentinels. */
void motionClearValueForFlaggedLookup(MotionFlagState *state, MotionFlagOutput *output, s32 key) {
    s32 second, first;
    first = D_motion_00416A88->find(key);
    if (gAiExports != NULL) second = gAiExports->find(key, first);
    else second = -1;
    if (state->flag != 0 && (first >= 0 || second >= 0)) {
        output->value = 0;
        return;
    }
    if (first >= 0 && (*D_motion_00416A88->record(first))->flag != 0) output->value = 0;
}
#line 142 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00403E74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040424C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040441C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040456C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00404868.s")

#line 153 "src/modules/motion.c"
/* Copy the motion matrix at 0x5E8 into the caller-provided output matrix. */
void motionCopyMatrix5E8(MotionMatrixState *state, Mtx4F *output) {
    gUvFmtxExports->uvMat4FCopy(output, &state->matrix);
}
#line 154 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00404C24.s")

#line 157 "src/modules/motion.c"
/* Visit four original 0x130-byte record regions, compute each planar vector
 * and run its follow-up update. Preserve the original 16-bit index wrapping. */
void motionUpdateFourPlanarRecords(MotionPlanarState *state) {
    s32 index = 0;
    u8 *base;
    MotionPlanarRecord *record;
    do {
        base = (u8 *)state + index * 0x130;
        record = (MotionPlanarRecord *)(base + 0x128);
        motionComputePlanarRecordVector(state, record, (Vec3F *)(base + 0x164));
        func_motion_004055BC(record);
        index = (index + 1) & 0xFFFF;
    } while (index < 4);
}
#line 158 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004055BC.s")

#line 161 "src/modules/motion.c"
/* Form the original planar vector from two offsets and the shared scale.
 * Kinds below two apply the stored two-component rotation; other kinds retain
 * the unrotated pair. The output Z component is always zero. */
void motionComputePlanarRecordVector(MotionPlanarState *state, MotionPlanarRecord *record, Vec3F *output) {
    f32 x = state->component984 - state->scale998 * record->offset34;
    f32 y = state->component988 + state->scale998 * record->offset30;
    if (record->kind < 2) {
        output->x = state->rotationX * x - state->rotationY * y;
        output->y = state->rotationY * x + state->rotationX * y;
    } else {
        output->x = x;
        output->y = y;
    }
    output->z = 0.0f;
}
#line 162 "src/modules/motion.c"

#line 163 "src/modules/motion.c"
/* Compute angular velocity crossed with the record offset, add linear
 * velocity, and project onto the two record axes. Output Z is zero. The
 * physical names describe this observed formula, not an inferred unit system. */
void motionProjectPointVelocity(MotionVelocityState *state, MotionProjectionRecord *record, Vec3F *output) {
    Vec3F velocity;
    gUvFvecExports->uvVec3FCross(&velocity, &state->angular, &record->offset);
    gUvFvecExports->uvVec3FAdd(&velocity, &velocity, &state->linear);
    output->x = gUvFvecExports->uvVec3FDot(&velocity, &record->axisX);
    output->y = gUvFvecExports->uvVec3FDot(&velocity, &record->axisY);
    output->z = 0.0f;
}
#line 164 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004057E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00405B44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00405D7C.s")

void func_motion_00405E5C(s32 a0) {
}

#line 174 "src/modules/motion.c"
/* Skip absent shared state; conditionally run the 0x6D8-gated update,
 * then the second update when the shared enable word is nonzero. Preserve
 * global reloads and callback sequencing. */
void motionUpdateSharedState(void) {
    if (D_motion_00416B10 == NULL) {
        return;
    }
    if (*(s32 *)((u8 *)D_motion_00416B10 + 0x6D8) != 0) {
        func_motion_00406A58(D_motion_00416B10);
    }
    if (D_motion_00416AB8 == 0) {
        return;
    }
    func_motion_004066E4(D_motion_00416B10);
}
#line 186 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00405EBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004061FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00406478.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004066E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00406A58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00406C30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004077A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00407B44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00407C10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00407FC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004087DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408A84.s")

#line 215 "src/modules/motion.c"
/* Select one of the original 0x1C-byte point records, compute angular
 * cross offset plus linear velocity, then transform by matrix 0x5E8. The
 * selector flag chooses offset 0x728 or 0x71C; callers own index bounds. */
void motionTransformSelectedPointVelocity(MotionVelocityState *state, Vec3F *output, MotionPointSelector *selector) {
    Vec3F velocity;
    if (selector->alternate != 0) {
        gUvFvecExports->uvVec3FCross(&velocity, &state->angular, (Vec3F *)((u8 *)state + selector->index * 0x1C + 0x728));
    } else {
        gUvFvecExports->uvVec3FCross(&velocity, &state->angular, (Vec3F *)((u8 *)state + selector->index * 0x1C + 0x71C));
    }
    gUvFvecExports->uvVec3FAdd(&velocity, &velocity, &state->linear);
    gUvFmtxExports->uvMat4TransformDirection((Mtx4F *)((u8 *)state + 0x5E8), output, &velocity);
}
#line 216 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408FD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00409734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004098B8.s")

#line 223 "src/modules/motion.c"
/* In game state six, notify the battle module with the stored handle.
 * Always run the original motion update on substate 0x618 with mode one, then
 * check Hot Lava voice playback. The callback context is originally ignored. */
void motionRunBattleAndHotLavaUpdate(MotionBattleState *state, s32 context) {
    if (gCurrentGameState == 6) {
        gBattleExports->notify(state->battleHandle);
    }
    func_motion_004130E4(state, (u8 *)state + 0x618, 1);
    motionTryPlayHotLavaVoice();
}
#line 224 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00409B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00409C68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040A3CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040B4EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040B7B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040BBE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040BFE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040C7DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040C8A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040E7BC.s")

#line 245 "src/modules/motion.c"
/* Accumulate two weighted three-component basis combinations. The first
 * uses one shared scale; the second uses per-component scales. Preserve
 * Z/X/Y product order, sequential stores and original aliased-input behavior.
 * Physical units are unproven; first/second identify the observed field groups. */
void motionAccumulateScaledBasisVectors(MotionBasisAccumulator *state, MotionBasisContribution *impulse) {
    f32 scale;
    scale = state->firstScale;
    state->first.x = state->first.x + scale * (impulse->coefficients.z * impulse->firstZ.x + impulse->coefficients.x * impulse->firstX.x + impulse->coefficients.y * impulse->firstY.x);
    state->first.y = state->first.y + scale * (impulse->coefficients.z * impulse->firstZ.y + impulse->coefficients.x * impulse->firstX.y + impulse->coefficients.y * impulse->firstY.y);
    state->first.z = state->first.z + scale * (impulse->coefficients.z * impulse->firstZ.z + impulse->coefficients.x * impulse->firstX.z + impulse->coefficients.y * impulse->firstY.z);
    state->second.x = state->second.x + (impulse->coefficients.z * impulse->secondZ.x + impulse->coefficients.x * impulse->secondX.x + impulse->coefficients.y * impulse->secondY.x) * state->secondScale.x;
    state->second.y = state->second.y + (impulse->coefficients.z * impulse->secondZ.y + impulse->coefficients.x * impulse->secondX.y + impulse->coefficients.y * impulse->secondY.y) * state->secondScale.y;
    state->second.z = state->second.z + (impulse->coefficients.z * impulse->secondZ.z + impulse->coefficients.x * impulse->secondX.z + impulse->coefficients.y * impulse->secondY.z) * state->secondScale.z;
}
#line 246 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040F2EC.s")

#line 249 "src/modules/motion.c"
/* Apply the original scaled correction only above the 0x690 threshold and
 * below the positive 0x988 limit. Preserve floating evaluation order; the
 * full physical meaning of these three offset-named fields remains unknown. */
void motionApplyConditionalCorrection(MotionCorrectionState *state) {
    f32 difference;
    if (D_motion_00416090 - D_motion_00416088 < state->value690) {
        difference = D_motion_00416084 - state->value988;
        if (difference > 0.0f && D_motion_00416084 > 0.0f) {
            state->value9A0 = state->value9A0 + D_motion_00416080 * (difference / D_motion_00416084);
        }
    }
}
#line 250 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040F424.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040F534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040F694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040FE84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00411BB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00411C64.s")

#line 263 "src/modules/motion.c"
/* Forward state, mode one, matrix 0x5E8 and final mode zero to the
 * original motion helper. Matrix ownership remains with the state. */
void motionForwardStateMatrix(void *state) {
    func_motion_00411C64(state, 1, (void *)((u8 *)state + 0x5E8), 0);
}
#line 266 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412770.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412B14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412CF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412E44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004130E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00413284.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00413568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414430.s")

void func_motion_0041475C(void) {
}

void func_motion_00414764(void) {
}

void func_motion_0041476C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414774.s")

void func_motion_00414A68(s32 a0) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414A70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414BB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004151CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004154B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00415724.s")

#line 309 "src/modules/motion.c"
/* Evaluate one of the two original motion graphs at the supplied value.
 * Any nonzero selector chooses the alternate graph. */
f32 motionEvaluateSelectedGraph(f32 value, s32 alternate) {
    UvGrphStruct *graph;
    if (alternate != 0) {
        graph = &D_motion_004163A8;
    } else {
        graph = &D_motion_0041644C;
    }
    return gUvGrphExports->uvGrphEvaluateLinearCurve(graph, value);
}
#line 310 "src/modules/motion.c"

u16 func_motion_00415870(void *a0) {
    return *(u16 *)((u8 *)a0 + 0x70C);
}

#line 315 "src/modules/motion.c"
/* With speech enabled, play the hot-lava line on random choice 3 while
 * its pending flag is set, then clear that flag to prevent a repeat. */
extern s32 D_motion_004160A0;
extern s32 gOptionsSpeechVol;

void motionTryPlayHotLavaVoice(void) {
    s32 choice;

    if (gOptionsSpeechVol != 0) {
        gSndExports->sndSetSpeechVol(gOptionsSpeechVol);
        choice = (s32) (gUvMathExports->uvRandFLcg() * 4.0f);
        if ((choice != 0) && (choice != 1) && (choice != 2) && (choice == 3) && (D_motion_004160A0 != 0)) {
            D_motion_00416AF0 = gSndExports->func_snd_00400854(V_HOTLAVA, 0x7FFF, gSndExports->func_snd_004014C4(), 0x7A120);
            D_motion_004160A0 = 0;
        }
    }
}
#line 316 "src/modules/motion.c"

#line 317 "src/modules/motion.c"
/* With speech enabled, play the explosion line on random choice 3 while
 * its pending flag is set. Preserve its separate scale and sound priority. */
extern f32 D_motion_0041607C;
extern s32 D_motion_004160A4;
extern s32 gOptionsSpeechVol;

void motionTryPlayExplosionVoice(void) {
    s32 choice;

    if (gOptionsSpeechVol != 0) {
        gSndExports->sndSetSpeechVol(gOptionsSpeechVol);
        choice = (s32) (gUvMathExports->uvRandFLcg() * 4.0f);
        if ((choice != 0) && (choice != 1) && (choice != 2) && (choice == 3) && (D_motion_004160A4 != 0)) {
            D_motion_00416AF1 = gSndExports->func_snd_00400854(V_EXPLOSION, 0x7FFF, gSndExports->func_snd_004014C4() * D_motion_0041607C, 0x1F4);
            D_motion_004160A4 = 0;
        }
    }
}
#line 318 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00415A3C.s")

