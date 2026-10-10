// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct {
    u8 opaque00[0x1C];
    f32 response;
    u8 opaque20[0x1C];
    f32 x, y;
} MotionPlanarAngleRecord;
/* Original misc entrypoint binds 0x58 to degree folding and 0x68 to the
 * normalized pair-angle evaluator; no other export contracts inferred. */
typedef struct {
    u8 unused00[0x58];
    f32 (*foldAngleDegrees)(f32);
    u8 unused5C[0xC];
    f32 (*normalizedPairAngle)(f32, f32);
} MotionPlanarAngleMiscExports;
extern void *gMiscExports;
extern f32 D_motion_00415DE4, D_motion_00415DE8, D_motion_00415DEC;
extern f32 D_motion_00415DF0, D_motion_00415DF4;

#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct {
    u8 opaque00[0x674];
    f32 value674;
    u8 opaque678[0x94];
    u16 kind;
    u8 opaque70E[0x236];
    Mtx4F transform;
    u8 opaque984[0x18];
    Vec3F accumulatedVector;
} MotionConfiguredVectorState;
extern f32 D_motion_00415F84, D_motion_00415F88;

typedef struct { u8 prefix[0x11C]; s16 mode; u8 gap11E[0x5A6]; f32 gateValue; u8 gap6C8[0x2C0]; f32 value988; u8 gap98C[0xC]; f32 response; } MotionModeResponseState;
extern f32 D_motion_00415F8C;
extern f32 D_80025D70;
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
void motionComputePlanarRecordAngleResponse(MotionPlanarAngleRecord *record);
void motionComputePlanarRecordVector(MotionPlanarState *, MotionPlanarRecord *, Vec3F *);
typedef struct { u8 unk00[0x690]; f32 value690; u8 unk694[0x2F4]; f32 value988; u8 unk98C[0x14]; f32 value9A0; } MotionCorrectionState;
extern f32 D_motion_00416080, D_motion_00416084, D_motion_00416088, D_motion_00416090;
typedef struct { u8 unk00[0x126C]; s32 battleIdentityWord; } MotionBattleState;
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
void motionComputePlanarRecordAngleResponse();
void motionComputePlanarRecordVector(MotionPlanarState *state, MotionPlanarRecord *record, Vec3F *output);
void motionProjectPointVelocity(MotionVelocityState *state, MotionProjectionRecord *record, Vec3F *output);
void func_motion_004057E4();
void func_motion_00405B44();
void func_motion_00405D7C();
void motionUpdateSharedState();
/* Focused original consumers only. RE_UNKNOWN: complete input allocation,
 * historical local/parameter declarations and callback ownership are unproved. */
#include "uvfont_rom.h"
extern UvFont_Exports *gUvFontExports;
typedef struct MotionBasisDrawInput {
    u8 opaque00[0x14];
    Vec3F vector14;
    u8 opaque20[0x14];
    Vec3F vector34;
} MotionBasisDrawInput;
/* Each row's fourth component is real identity-matrix storage consumed by
 * FMTX08/68; these are not added padding or extra independent vector locals. */
typedef union MotionBasisDrawMatrix {
    Mtx4F matrix;
    struct {
        Vec3F first; f32 fourth0;
        Vec3F second; f32 fourth1;
        Vec3F third; f32 fourth2;
        Vec3F translation; f32 fourth3;
    } rows;
} MotionBasisDrawMatrix;
extern f32 D_motion_00415E20, D_motion_00415E24, D_motion_00415E28;
extern f32 D_motion_00415E2C, D_motion_00415E30, D_motion_00415E34;
extern f64 D_motion_00415E38;
extern f32 D_motion_00415E40, D_motion_00415E44;
void func_motion_00405EBC(f32, f32, s16, s16, s16);
void motionCallScalarHelperWithThreeTransforms(f32, f32, f32, f32, f32, f32);
void motionBuildBasisAndCallScalarHelper(MotionBasisDrawInput *);
#line 115 "src/modules/motion.c"
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
void motionRunBattleAndHotLavaUpdate(MotionBattleState *state, s32 unusedIncomingWord);
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
void motionAccumulateTransformedConfiguredVector(MotionConfiguredVectorState *state);
void motionApplyGatedModeResponse(MotionModeResponseState *state, s32 enabled, f32 input);
void func_motion_0040F694();
void func_motion_0040FE84();
/* Focused views of the original isct query input and copied result span.
 * The native record copier transfers exactly 0x58 bytes. RE_UNKNOWN: these
 * views do not establish historical declarations or complete allocations. */
typedef struct {
    f32 first[3];
    f32 second[3];
    u32 modeWord18;
} MotionCollisionInput;
typedef struct {
    u32 prefix00[2];
    s32 kind;
    u32 triangleHandle;
    u32 opaque10[18];
} MotionCollisionResult;
typedef struct {
    u8 opaque00[8];
    s8 terrainId;
} MotionCollisionSceneState;
typedef struct {
    u32 opaque00[11];
    MotionCollisionSceneState *sharedState;
} MotionCollisionSceneExports;
typedef struct {
    u32 opaque00[20];
    s32 (*query)(MotionCollisionInput *, s32, s32, s32, MotionCollisionResult *);
    u32 opaque54[12];
    s32 (*matchesTextureByte)(s32, u32, u16);
} MotionCollisionQueryExports;
extern void *gSceneExports;
extern void *gUvIsectExports;
u16 motionQueryHasNonExcludedKind(MotionCollisionInput *input);
void func_motion_00411C64();
void func_motion_00412770();
void func_motion_00412B14();
/* Observed offsets and narrowly consumed callback inputs only; these views
 * do not establish complete original allocations or pointer ownership. */
typedef struct MotionModePropertySource {
    u8 opaque00[0x70];
    f64 comparisonValue;
    u8 opaque78[0xC];
    s32 activeWord;
} MotionModePropertySource;
typedef struct MotionModePropertyContext {
    u8 opaque00[4];
    void *animationState;
    u8 opaque08[4];
    void *cameraRecord;
} MotionModePropertyContext;
typedef struct MotionModePropertyState {
    u8 opaque00[0x70E];
    u8 mode;
    u8 opaque70F;
    MotionModePropertySource *source;
    u8 opaque714[0x200];
    void *dynamicRecord;
    u8 opaque918[0x954];
    MotionModePropertyContext *context;
} MotionModePropertyState;
typedef struct MotionModePropertyCarExports {
    u8 opaque00[0x14];
    void (*setProperties)(void *, s32, ...);
} MotionModePropertyCarExports;
typedef struct MotionModePropertyDynamicExports {
    u8 opaque00[0xFC];
    void (*setValue)(void *, s32, f32);
} MotionModePropertyDynamicExports;
typedef struct MotionModePropertyCameraExports {
    u8 opaque00[0x20];
    void (*setProperties)(void *, s32, ...);
} MotionModePropertyCameraExports;
extern void *D_motion_00416A84;
extern void *gUvDynExports;
extern void *gCamExports;
extern f32 D_80025D6C;
void motionUpdateModeGatedProperties(MotionModePropertyState *);
#line 184 "src/modules/motion.c"
void func_motion_00412E44();
/* Focused observed offsets and consumed callback inputs only. These views
 * establish neither complete historical allocations nor pointer ownership. */
#include "uvfvec_rom.h"
typedef struct MotionPropertySequenceCamera {
    u8 opaque00[0x15C];
    f32 value15C;
} MotionPropertySequenceCamera;
typedef struct MotionPropertySequenceContext {
    u8 opaque00[4];
    void *animationState;
    u8 opaque08[4];
    MotionPropertySequenceCamera *cameraRecord;
    u8 opaque10[4];
    s32 rumbleIndex;
    s32 objectHandle;
} MotionPropertySequenceContext;
typedef struct MotionPropertySequenceState {
    u8 opaque00[0x918];
    void *dynamicRecord;
    u8 opaque91C[0x950];
    MotionPropertySequenceContext *context;
} MotionPropertySequenceState;
typedef struct MotionPropertySequenceDynamicExports {
    u8 opaque00[0x70];
    void (*setReference)(void *, void *);
} MotionPropertySequenceDynamicExports;
typedef struct MotionPropertySequenceObjectExports {
    u8 opaque00[0x38];
    void (*clearFlags)(s32, u32);
} MotionPropertySequenceObjectExports;
typedef struct MotionPropertySequenceCarExports {
    u8 opaque00[0x14];
    void (*setProperties)(void *, s32, ...);
    u8 opaque18[0x30];
    void (*configureObject)(s32, void *);
} MotionPropertySequenceCarExports;
typedef struct MotionPropertySequenceRumbleExports {
    u8 opaque00[4];
    void (*mergePatternValues)(s32, f32, f32, f32);
} MotionPropertySequenceRumbleExports;
typedef struct MotionPropertySequenceCameraExports {
    u8 opaque00[0x20];
    void (*setProperties)(void *, s32, ...);
} MotionPropertySequenceCameraExports;
typedef struct MotionPropertySequencePieceExports {
    u8 opaque00[8];
    s32 (*createFromObject)(s32, s32, Vec3F *, f32, f32, s32);
} MotionPropertySequencePieceExports;
extern void *gUvDynExports;
extern void *gUvDobjExports;
extern void *D_motion_00416A84;
extern void *gRumbleExports;
extern void *gCamExports;
extern void *gPieceExports;
/* Original DATA+9E4 supplies exactly three copied words; the original PIECE
 * helper forwards them to the proven FVEC1C three-float copy. No units inferred. */
extern Vec3F D_motion_00416A64;
void motionApplyPropertyAndRumbleSequence(MotionPropertySequenceState *);
#line 186 "src/modules/motion.c"
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
f32 motionEvaluateSelectedGraph(f32 inputValue, s32 alternateGraphSelector);
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
void motionUnloadModulesAndStopEmitters(void) { /* Unload trck then plyr; stop the first byte ID, and stop the second only when it is not 255. */
    uvUnloadModule(0x7472636B);
    uvUnloadModule(0x706C7972);
    gUvEmitterExports->uvEmitterStop(D_motion_00416AF0);
    if (D_motion_00416AF1 != 0xFF) gUvEmitterExports->uvEmitterStop(D_motion_00416AF1);
/* RE_UNKNOWN: Emitter ID validity and teardown ownership; neither stored byte is cleared here. */ }
#line 95 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004002EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00400748.s")

/* Blend raw scalar fields using a snapshotted player-two handicap selector.
 * Mode 4 leaves the fields unchanged; mode 3 uses the computed limit directly.
 * The original loads the record pointer even on the mode-4 return path.
 * RE_ORIGINAL_QUIRK: selector values outside 0..4 can consume an untouched
 * divisor local. Denominators are unchecked; ordered clamps retain NaNs.
 * RE_UNKNOWN: reachable selector and denominator domains, scalar units,
 * historical storage aliases, record lifetime and caller guarantees require
 * original setting writers, field producers and callers. Global values remain
 * runtime reads, not hardcoded constants inferred from shipped bytes.
 * A readable draft is 476 versus 480 native bytes, with 116 differing words.
 * Native reference-scalar stack snapshot/reload becomes a register value;
 * draft spills the blended100 value, uses a 40- versus 32-byte frame, and
 * schedules scalar/global loads differently. The two 22-record relocation
 * lists differ in offsets. No supported omitted operation or call was found.
 * Retain original assembly until complete instructions and records match. */
#line 100 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00400D74.s")

/* Reset scalar/history state, build matrix5E8, then copy the source vector
 * to618 and ten 24-byte history rows with a fresh settings7C read per row.
 * Matrix5E8 and vector618 overlap; preserve that storage and callback order.
 * The optional track query, matrix copies, terrain update and intersection
 * property5 precede the direct helper and dynamic matrix/vector callbacks.
 * DYN50 receives each whole three-word vector through A2/A3/stack10, and
 * selectors17/18 copy those words to dynamic record14BC/14E0. The focused
 * by-value call view does not establish the full historical dispatch ABI.
 * RE_UNKNOWN: complete allocations/input and terrain-index domains, scalar
 * and property purposes/units, source/state overlap guarantees, captured
 * context and module replacement lifetimes require original producers,
 * entry callers and callback lifetime evidence. Callback-sensitive members
 * and module pointers must retain their native reloads.
 * Readable C remains parked: native/draft952 bytes, 170 differing words.
 * All22 ordered relocation identities agree, but instruction sites differ.
 * Native frame112/contextSP104 become120/SP116; an extra saved register,
 * saved240/BNE instead of signedSLTI240, zero materialization and terrain
 * comparison lowering differ. No supported missing effect/type/ABI gap was
 * found. Historical declarations/lowering remain unknown; require exact
 * instructions, packed-module equality and fresh original-ROM proof. */
#line 102 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00400F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040130C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004013B0.s")

/* Query four 0x130-stride sample views after stores at 0x12A/0x12E/0x12C.
 * ISCT 0xA4 mode 2 outputs key/scalar/XYZ; misses or loaded texture flag 4
 * trigger ISCT 0xA0 mask 0xFE, with a prepared elevated retry when key 4 remains.
 * Select greatest scalar independently of least normal Z, preserve first
 * ties/NaNs, update matrix Z, rebuild its linear rows through MISC 0x18,
 * reset four sample Z values and halfwords, and initialize matrix 0x62C.
 * RE_ORIGINAL_QUIRK: fallback return values are ignored; its no-result
 * path writes key 4/scalar 0/normal(0,0,1). Elevated XYZ is copied before
 * the first query. Configuration reloads and arithmetic grouping matter.
 * RE_UNKNOWN: context/key/flag/mode domains, scalar units, validity,
 * allocation/aliasing and callback lifetimes need producers/callers;
 * strided partial views do not establish a complete array/allocation.
 * Clean trial is 920 versus 912 bytes; frame 216 versus 208, count spills,
 * local homes and persistent export-base lowering differ. The 18/14 full
 * relocation lists differ. Coordinate ADD operand allocation also differs;
 * exact NaN payload/exception identity is unproved. Native's initial dead
 * stack read does not justify invented scratch storage or padding.
 * Retain original ASM until complete instructions/relocations match. */
#line 108 "src/modules/motion.c"
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
/* Subtract shared delta; a negative result advances one ten-slot history entry and adds one to remaining.
 * RE_ORIGINAL_QUIRK: no catch-up loop runs even if remaining stays negative; preserve one history write per call.
 * RE_UNKNOWN: interval/delta constraints need the delta producer and caller schedule audit; optional track update still runs. */
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

/* Preserve the captured context126C across the optional TDATA query path or
 * indexed-history path, then CARANIM property10, byte111/value114 stores,
 * optional AI4C word store, direct helpers, both camera calls and value714.
 * Actual TDATA0C writes one word and three floats; TDATA44 writes two floats.
 * The first scalar and vector feed F54; the other outputs retain native
 * provider writes. Each callback/global/context-member reload stays ordered.
 * RE_ORIGINAL_QUIRK: only marked index -1 selects the cycling path, whose
 * increment is reset at >=10. Other signed marked values directly select
 * a 24-byte row without a local range check. Do not infer caller validity.
 * RE_UNKNOWN: complete state/index and output-storage contracts, scalar and
 * property meanings/units, aliasing, captured-context and module lifetimes
 * need original producers, entry callers and callback replacement evidence.
 * Readable C remains parked: both trials give 584 native/draft bytes and
 * all 24 complete ordered relocation records match. The first has 29 word
 * differences; the sole output-declaration refinement has 34. Native frame
 * 72/context SP68 become 80/SP76 in both. Native word/vector/scalar homes
 * SP40/56/52/48 become SP68/56/52/48 first and SP48/60/56/52 in the refinement.
 * Cycling register choices and the marked-index store/move order also differ.
 * No supported omitted effect, width or callback ABI correction was found.
 * Historical local declarations and lowering remain unproved; require exact
 * instructions plus original packed-module/fresh ROM proof before recovery. */
#line 137 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004039BC.s")

/* Preserve the positive value714 copy/reset group and the byte111 gate.
 * Modes 5/7 clear value114 and byte111, optionally call the AI word store,
 * then return without a CARANIM call. Other active paths retain the captured
 * context, ordered value114 test and original decrement snapshot before the
 * byte store; CARANIM property 27 receives the selected word and terminator 0.
 * Actual conditional RACE loader publication proves aimd at 80025CAC, and
 * original AI4C binds 7570: its three instructions store the supplied A0 word
 * at AI BSS+3C. Do not infer the word's purpose or exhaustive module lifetime.
 * RE_ORIGINAL_QUIRK: byte111==2 forces signed TRUNC.W.S of value114*1000.0f
 * even when value114 is nonpositive or unordered. The result word is treated
 * as unsigned for remainder 160; remainder>80 selects property 1, otherwise 0.
 * RE_UNKNOWN: runtime floating-conversion domain, values/property meanings
 * and units, complete caller storage, aliases, captured-context lifetimes and
 * module availability/replacement need original producers and entry callers.
 * Readable C remains parked. First trial: 416 native versus 412 draft bytes,
 * 57 differing words. The sole native two-arm property-join refinement gives
 * 416/416 bytes and 45 differing words; both ten-record relocation lists
 * still differ. The 40-byte frame and captured context at SP36 agree.
 * Gate/mode, conversion-result and floating registers differ; the refined
 * property join retains the native explicit jump, but an earlier AI address
 * instruction adds a word before the numeric path. Actual global reads stay
 * after the clear stores. Decrement and active CAR pair sites shift by four
 * bytes; the final CAR pair sites now agree. All signed truncation/unsigned
 * remainder operations, state effects and callback arguments remain present.
 * No supported missing provider effect or arithmetic-width correction was
 * found. Historical source/local and instruction lowering remain unproved;
 * require exact instructions/relocations and packed-module/fresh ROM proof. */
#line 139 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00403C04.s")

#line 141 "src/modules/motion.c"
/* Find the primary record for a key and optionally query the AI module.
 * Clear output halfword 0xA when this state is flagged and either lookup
 * succeeds, or when the primary referenced state is flagged; retain signed sentinels.
 * RE_UNKNOWN: returned-record/state validity and lifetime need original providers/callers. */
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

/* Advance scalar 0x694 toward the graph-derived target; optional debug
 * assist preserves separate ordered magnitude/sign gates. Native averaging
 * starts with positive float zero, sums four samples in single precision,
 * then multiplies by double 0.25 and converts back to float.
 * Keep the initial config/rate-factor snapshots across helper 0x424C and
 * reload current config after the second graph call. Preserve reversing-rate,
 * overshoot and lower/upper bounds, then cosine and fresh-value sine inputs.
 * RE_UNKNOWN: physical units, coefficient domains, complete state/config
 * extents, aliasing and lifetimes need original producers/callers.
 * Clean C drops the initial zero add and changes allocation/load scheduling;
 * retain ASM pending complete instruction and relocation proof. */
#line 143 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00403E74.s")

/* Select a material-row scalar unless shared game state is 6, then evaluate
 * two curves with the input field reloaded before each call. Store the
 * selected scalar at 704 before curve calls. Output 148/278 uses curve A and
 * config E0; output 3A8/4D8 uses curve B and config E4, with config reloaded.
 * RE_UNKNOWN: material/input domains, curve/scalar units, game-state meaning,
 * allocation, aliasing and callback lifetimes require original producers
 * and callers; four observed stores do not establish a complete array.
 * Native constant slot-branch arms remain unexplained source organization.
 * A readable loop draft is 304 versus 464 native bytes, with 116 differing
 * words and frame 56 versus 40. The compiler shares a scalar*curveA multiply
 * that native repeats, so exceptional floating-point effects are unproved.
 * The two 12-record relocation lists differ in offsets/order. Retain original
 * assembly until complete instruction and relocation identity is recovered. */
#line 145 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040424C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040441C.s")

/* Update scalar 0x684, signed counter 0x688 and configuration scale 0x6AC
 * through enable/gate/sign tests. Original MISC 0x54 clamps value to ordered
 * upper/lower singles; its leaf has no calls or nonstack writes. Keep the
 * original response/config read timing and double quarter-scale conversion.
 * RE_UNKNOWN: physical scalar/flag/mode meanings, counter schedule and
 * state/config lifetime need original producers/callers. Clean C remains
 * unmatched; retain assembly pending complete byte/relocation proof. */
#line 149 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040456C.s")

/* Update scalar 0x680 through level 0x6C4, signed mode 0xA3C and
 * ordered sign/magnitude gates, including sample 0x3A4 and both incoming
 * word gates. Every path joins original MISC 0x54 ordered single clamp;
 * reload the stored result before possible scalar-0x998 accumulation.
 * RE_UNKNOWN: scalar units, mode/gate domains, tuning constants and state
 * lifetime need original producers/callers. Clean C differs in branches,
 * reloads and operand order; retain ASM pending full byte/relocation proof. */
#line 151 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00404868.s")

#line 153 "src/modules/motion.c"
/* Copy the motion matrix at 0x5E8 into the caller-provided output matrix. */
void motionCopyMatrix5E8(MotionMatrixState *matrixState, Mtx4F *outputMatrix) { /* Copy the state's matrix through the current matrix-copy callback. */
    gUvFmtxExports->uvMat4FCopy(outputMatrix, &matrixState->matrix);
/* RE_UNKNOWN: Caller pointer validity and permitted source/output overlap. */ }
#line 154 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00404C24.s")

#line 157 "src/modules/motion.c"
/* Visit four state-relative 0x130-byte regions. Pass each region+0x128
 * to the vector helper with output region+0x164, then its angle response.
 * RE_ORIGINAL_QUIRK: wrap the index to 16 bits before the signed <4 test.
 * RE_UNKNOWN: the two focused record views, full state extent and lifetime
 * need allocation/writer evidence; no four-element C array is established. */
#line 159 "src/modules/motion.c"
void motionUpdateFourPlanarRecords(MotionPlanarState *state) {
    s32 recordIndex = 0;
    u8 *recordRegion;
    MotionPlanarRecord *planarRecord;
    do {
        recordRegion = (u8 *)state + recordIndex * 0x130;
        planarRecord = (MotionPlanarRecord *)(recordRegion + 0x128);
        motionComputePlanarRecordVector(state, planarRecord, (Vec3F *)(recordRegion + 0x164));
        motionComputePlanarRecordAngleResponse(planarRecord);
        recordIndex = (recordIndex + 1) & 0xFFFF;
    } while (recordIndex < 4);
}
#line 158 "src/modules/motion.c"

#line 159 "src/modules/motion.c"
/* From the planar record's X/Y pair, compute a normalized pair angle,
 * apply the shared angle scale and fold degrees through the misc exports.
 * Below the first ordered Y-magnitude threshold store zero; below the second,
 * multiply the folded result by the original (magnitude-offset)/span factor.
 * Preserve positive-test magnitude semantics for zero/NaN and reload the
 * stored response before attenuation. RE_UNKNOWN: constant units/ranges and
 * the response's consumer meaning require original writers/callers. */
void motionComputePlanarRecordAngleResponse(MotionPlanarAngleRecord *record) {
    f32 magnitude;
    f32 y;

    y = record->y;
    if (y > 0.0f) magnitude = y;
    else magnitude = -y;
    if (magnitude < D_motion_00415DE4) {
        record->response = 0.0f;
        return;
    }
    record->response = ((MotionPlanarAngleMiscExports *)gMiscExports)->foldAngleDegrees(
        ((MotionPlanarAngleMiscExports *)gMiscExports)->normalizedPairAngle(record->x, y) *
        D_motion_00415DE8);
    if (magnitude < D_motion_00415DEC) {
        record->response = record->response *
            ((magnitude - D_motion_00415DF0) / D_motion_00415DF4);
    }
}
#line 160 "src/modules/motion.c"

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

/* Update three selected-record scalars with the original pre-gate ratio,
 * promoted-double gate, signed samples, MISC 0x58 degree fold and GRPH 0x04
 * curve. Selector halfwords stride 0x10; records begin at 0x128, stride 0x130.
 * Preserve the live count at 0x1130, u16 traversal and ordered zero/NaN gates.
 * RE_UNKNOWN: physical units, selector/record capacities, divisor/curve
 * domains, alternate-mode meaning and alias/lifetime need original producers.
 * Clean C differs in reloads, branches, frame and operand order; retain ASM
 * pending complete instruction and relocation proof. */
#line 165 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004057E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00405B44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00405D7C.s")

#line 171 "src/modules/motion.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_motion_00405E5C(s32 a0) {
}
#line 173 "src/modules/motion.c"

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

#line 189 "src/modules/motion.c"
/* Original instruction and relocation match; unresolved contracts follow. */
/* Apply three ordered transforms and call the scalar helper after each.
 * Preserve separate original RODATA loads and the signed16 conversions of
 * 255*weight and 255-(255*weight); no input clamping is introduced.
 * RE_UNKNOWN: scalar/weight domains and units, conversion validity, rendered
 * purpose, FONT resource availability and module/callback lifetimes need
 * original callers and resource producers. Historical parameter/local types
 * remain inferred consumed views; axis tags120/122 are actual provider tags. */
void motionCallScalarHelperWithThreeTransforms(f32 weight, f32 scalar1, f32 scalar2,
                          f32 scalar3, f32 offsetX, f32 offsetY)
{
    Mtx4F transform;
    s16 inverseWeight;
    s16 scaledWeight;
    f32 scaled;

    gUvFontExports->uvSetFont(3);
    gUvFontExports->uvFontColor(255, 0, 0, 255);
    gUvFmtxExports->uvMat4SetIdentity(&transform);
    gUvFmtxExports->uvMat4LocalTranslate(&transform, offsetX, offsetY, 0.0f);
    gUvFmtxExports->uvMat4RotateAxis(&transform, 1.570797f, 'x');
    gUvFmtxExports->uvGfxMtxViewLoad(&transform, 1);
    scaled = 255.0f * weight;
    scaledWeight = (s16)scaled;
    inverseWeight = (s16)(255.0f - scaled);
    func_motion_00405EBC(scalar3 * D_motion_00415E20, D_motion_00415E24,
                          inverseWeight, scaledWeight, 0);
    gUvFmtxExports->uvGfxMtxFViewPop();

    gUvFmtxExports->uvMat4SetIdentity(&transform);
    gUvFmtxExports->uvMat4LocalTranslate(&transform, offsetX, offsetY, 0.0f);
    gUvFmtxExports->uvMat4RotateAxis(&transform, -1.570797f, 'z');
    gUvFmtxExports->uvGfxMtxViewLoad(&transform, 1);
    func_motion_00405EBC(scalar1 * D_motion_00415E28, D_motion_00415E2C,
                          inverseWeight, scaledWeight, 0);
    gUvFmtxExports->uvGfxMtxFViewPop();

    gUvFmtxExports->uvMat4SetIdentity(&transform);
    gUvFmtxExports->uvMat4LocalTranslate(&transform, offsetX, offsetY, 0.0f);
    gUvFmtxExports->uvGfxMtxViewLoad(&transform, 1);
    func_motion_00405EBC(scalar2 * D_motion_00415E30, D_motion_00415E34,
                          inverseWeight, scaledWeight, 0);
    gUvFmtxExports->uvGfxMtxFViewPop();
}
#line 190 "src/modules/motion.c"

#line 191 "src/modules/motion.c"
/* Original instruction and relocation match; unresolved contracts follow. */
/* Build a basis in one matrix, preserving its vector-row aliases and
 * translation copied from input14. Cross-product order depends on the
 * ordered magnitude test against the original double0.2 threshold.
 * RE_ORIGINAL_QUIRK: all three normalization return values are ignored;
 * the actual provider leaves the destination unchanged on zero length.
 * RE_UNKNOWN: full input allocation/ownership and vector meanings/frames,
 * finite/nondegenerate domains, rendering purpose and module/callback
 * lifetime guarantees need original producers/callers. This union describes
 * actual shared local storage, not a proved historical union declaration. */
void motionBuildBasisAndCallScalarHelper(MotionBasisDrawInput *input)
{
    Mtx4F scale;
    MotionBasisDrawMatrix basis;
    Mtx4F adjusted;
    f32 magnitude;

    gUvFmtxExports->uvMat4SetIdentity(&basis.matrix);
    basis.rows.translation = input->vector14;
    basis.rows.second = input->vector34;
    if (basis.rows.second.z > 0.0f) {
        magnitude = basis.rows.second.z;
    } else {
        magnitude = -basis.rows.second.z;
    }
    if (magnitude < D_motion_00415E38) {
        gUvFvecExports->uvVec3FCross(&basis.rows.first, &basis.rows.second,
                                      &basis.rows.third);
        gUvFvecExports->uvVec3FCross(&basis.rows.third, &basis.rows.first,
                                      &basis.rows.second);
    } else {
        gUvFvecExports->uvVec3FCross(&basis.rows.third, &basis.rows.first,
                                      &basis.rows.second);
        gUvFvecExports->uvVec3FCross(&basis.rows.first, &basis.rows.second,
                                      &basis.rows.third);
    }
    gUvFvecExports->uvVec3FNormalize(&basis.rows.first, &basis.rows.first);
    gUvFvecExports->uvVec3FNormalize(&basis.rows.second, &basis.rows.second);
    gUvFvecExports->uvVec3FNormalize(&basis.rows.third, &basis.rows.third);
    gUvFmtxExports->uvMat4ApplySharedInverseTranslation(&adjusted, &basis.matrix);
    gUvFmtxExports->uvGfxMtxViewLoad(&adjusted, 3);
    gUvFmtxExports->uvMat4SetIdentity(&scale);
    gUvFmtxExports->uvMat4Scale(&scale, D_motion_00415E40,
                                 D_motion_00415E40, D_motion_00415E40);
    gUvFmtxExports->uvGfxMtxViewLoad(&scale, 1);
    func_motion_00405EBC(3.0f, D_motion_00415E44, 0, 0, 255);
    gUvFmtxExports->uvGfxMtxFViewPop();
    gUvFmtxExports->uvGfxMtxFViewPop();
}
#line 192 "src/modules/motion.c"

/* Query between matrix translations and retain the original drawing calls.
 * Original matrix-row aliases, three single-precision component divisions,
 * MISC110 returned scalar, query arguments and export reloads are established
 * by native providers. Positive results select the first flag; any nonzero
 * result reaches the downstream basis helper. Preserve this distinction.
 * RE_ORIGINAL_QUIRK: the local query record is uninitialized before isct54
 * reads its first two words; no caller initialization guarantee is established.
 * RE_UNKNOWN: original state/input allocations, zero-length/finite domains,
 * result-prefix initialization, vector/scalar meanings and units, query flags,
 * pointer aliases and module/resource lifetimes need original callers/producers.
 * The observed 88-byte query and 64-byte draw access views share local storage;
 * they do not prove complete historical object declarations or allocations.
 * Readable C remains parked: the first draft has 880 versus 884 native bytes
 * and 73 differing positions. Preserving native zero-before-test flag flow
 * gives 884/884 bytes and all 30 complete relocation records match by site;
 * only the initial three HI/LO pair groups differ in record enumeration.
 * Seven instruction words still differ: native positive/other flag registers
 * V1/A1 become V0/V1, including their shared halfword stores. All 214 other
 * words, frame and local homes match. No further effect/type correction is
 * supported; historical declarations and flag lifetimes remain unproved.
 * Require exact instructions and original packed-module/fresh ROM proof
 * before replacing ASM; no dummy storage or register forcing is justified. */
#line 193 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004066E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00406A58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00406C30.s")

/* Dispatch original record kinds 1/2/4/8/24, then apply indexed/dot gates.
 * Native table entries and providers establish the callback arguments, not
 * physical meanings. Entry record and initial context remain captured; the
 * final SMACK callback reloads context, and its key store reloads record+0C.
 * Kind 2 stores flag70C=1 and returns when that reloaded halfword is zero.
 * Tail index >=0 and <4 guards the 0x130-stride halfword; count10E2>=3 and
 * count10E0<3 gate FVEC18's three-float dot and ordered threshold comparison.
 * RE_UNKNOWN: full allocations, reachable kind/index/key/count domains,
 * flag/scalar/vector purposes and units, aliases, pointer replacement and
 * module lifetimes need original producers, callers and callback evidence.
 * Readable C remains parked: 924 native versus 900 draft bytes, with 204
 * differing positions. Native frame80 becomes88; draft retains entry in S2
 * instead of its argument home, changing reloads, local homes and epilogue.
 * Context/output/key/SMACK homes SP+52/56/68/72 become SP+64/68/80/84.
 * Native shared branch/flag-clear lowering differs from draft early returns.
 * The complete 40/31 relocation lists differ: nine native PC16 label records
 * resolve locally in C, the table uses .rodata, and sites/downstream helper
 * values shift. All 31 non-PC16 type/target roles remain represented.
 * Existing direct154B8/14BB0/98B8 calls lack full source prototypes; their
 * historical declarations require original callers/consumption evidence.
 * Full review supports no omitted effect, width, precision, ABI or reload
 * correction. Historical declarations/storage/lowering remain unproved;
 * require exact instructions and original packed-module/fresh ROM proof. */
#line 199 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004077A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00407B44.s")

/* Dispatch record kinds and process a selected three-float output.
 * Native SMACK10/14 return record pointers; SMACK0C consumes the output and
 * a fresh state+126C pointer. Earlier context/record pointers stay captured;
 * the final stored key is read again after the callback. Category20 is
 * tested before the later u16 narrowing. Signed selectors and ordered
 * single-precision open scalar intervals are preserved in the parked C.
 * RE_ORIGINAL_QUIRK: the indexed selector halfword read has no bound test;
 * the later signed index < 4 test has no nonnegative check. These operations
 * do not establish that any caller supplies an out-of-range index.
 * RE_UNKNOWN: complete state/entry/record allocations, index/key/category
 * domains, pointer aliases and replacement lifetimes, module availability,
 * flag/vector/scalar purposes and units need original callers and producers.
 * Readable C remains parked: 944 native versus 964 draft bytes, with 225
 * differing positions. The native retains state in S0 and entry in S1;
 * the draft homes state at SP+84 and retains entry in S0, adding reloads.
 * Both use an 80-byte frame. All 34 relocation symbol/type identities keep
 * their order, but sites and downstream helper values shift with the real
 * 20-byte growth; complete relocation equality fails. No missing effect,
 * width, precision, argument or callback reload is supported by full review.
 * Historical declarations/storage remain unproved; require exact code and
 * original packed-module/fresh ROM proof before replacing retained ASM. */
#line 203 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00407C10.s")

/* Dispatch record kinds and transform state+984 through matrix+5E8.
 * Native FMTXB0 writes three floats for SMACK0C, which receives a fresh
 * state+126C pointer. Earlier context/record pointers remain captured, and
 * the final stored key is read again after the callback. Category20 is
 * tested before the later u16 narrowing; the same-key case returns early.
 * RE_UNKNOWN: complete allocations, key/category domains, pointer aliases
 * and replacement lifetimes, module availability, flag/vector purposes and
 * historical declarations need original callers, producers and lifetimes.
 * Readable C remains parked at 660/660 bytes. Thirteen instruction words
 * move genuine local homes by four bytes: native SMACK pointer SP+72, key
 * SP+68, context SP+52 and output SP+56 become SP+76/72/56/60. One BNE swaps
 * its symmetric equality operands. All other 151 words and all 23 complete
 * ordered relocation records match; the 80-byte frame is unchanged.
 * Full review supports no missing effect, width, argument, precision or
 * callback reload correction. Historical local storage remains unproved;
 * require exact instructions and original packed-module/fresh ROM proof
 * before replacing ASM; no padding or register forcing is justified. */
#line 205 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00407FC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004087DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00408A84.s")

#line 215 "src/modules/motion.c"
/* Select one of the original 0x1C-byte point records, compute angular
 * cross offset plus linear velocity, then transform by matrix 0x5E8.
 * RE_UNKNOWN: index bounds for tables at 0x728/0x71C need original state/selector producers. */
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

/* Query the descriptor's dynamic word, forward CAM tag 18 and copy the two
 * vectors in their original order; the store at 10C4 also occurs when signed E50=-1.
 * Preserve the ordered single multiply/negate threshold gates, post-DYN
 * reloads and shared E50=1 failure store. The successful mode2/gameState!=6
 * path calls 130E4 then the voice helper without that replacement.
 * Original DYN64 selector6 copies 16 floats; the natural 64-byte matrix output
 * and its +48 interior address are grounded by actual FMTX0C/native callers.
 * The 130E4 call receives third word 0 and does not dereference that address on
 * this path; retain the object/address/call, not an invented unused vector.
 * RE_UNKNOWN: state/property/value meanings and units, caller record extents,
 * module availability, aliases/lifetimes and historical local declarations
 * require original producers/callers; historical storage declarations remain unproved.
 * Readable C remains parked: first draft 412 versus 388 native bytes; preserving
 * the observed shared failure store gives 388/388 and all 18 complete ordered
 * relocation records match. Exactly four instruction words still differ:
 * frame 128 versus 120 and captured-context homeSP120 versus116. All 93 other
 * words match, including matrix SP52 and final-row SP100. No dummy storage or
 * alignment/declaration permutation is justified by these residual offsets.
 * Require exact instructions and packed-module/fresh ROM proof before C. */
#line 219 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00409734.s")

/* Initialize the shared sound handle before checking byte70E, then try a
 * SPLASH acquisition while that byte is zero. Copy input XYZ to matrix5E8
 * translation row618; rumble runs after acquisition even on failure.
 * Success sets kind+1 and updates dynamic/animation/camera/audio state,
 * with BATTLE0C after sound only when current game state is 6. Player is
 * snapshotted before initialization; fields and acquired pointer reload
 * across callbacks. RE_ORIGINAL_QUIRK: initialization precedes the active
 * exit; either attempted outcome ends by storing halfword70C=5.
 * RE_UNKNOWN: input flags, state byte/halfword policy, state6, sound10,
 * scalar units, caller index/null guarantees, allocation, aliasing and
 * callback/resource lifetimes need original producers/callers.
 * Both genuine local declaration orders match 540 bytes and 132/135 words;
 * only two SH and one LHU kind stack offsets differ: native SP+54 decimal,
 * first draft SP+50, sole order alternative SP+46 (hex 36/32/2E).
 * Each trial's 30 full relocation records match the original as a multiset;
 * enumeration differs. Historical local storage/order remains unknown.
 * Retain original ASM until complete instruction identity is recovered;
 * no padding, extra local or further declaration permutation is inferred. */
#line 221 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004098B8.s")

#line 223 "src/modules/motion.c"
/* In game state six, forward the stored word to BATTLE's identity scan.
 * Always call helper130E4(state, state+618, 1), then the voice helper.
 * RE_UNKNOWN: identity/phase roles and lifetimes need producers/callers; the second incoming word is unused. */
void motionRunBattleAndHotLavaUpdate(MotionBattleState *motionState, s32 unusedIncomingWord) { /* Notify the battle callback in game state 6, then invoke the state helper before checking the voice cue. */
    if (gCurrentGameState == 6) {
        gBattleExports->notify(motionState->battleIdentityWord);
    }
    func_motion_004130E4(motionState, (u8 *)motionState + 0x618, 1);
    motionTryPlayHotLavaVoice();
/* RE_UNKNOWN: Meaning of the unused incoming word and unchecked state/callback lifetime. */ }
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

#line 251 "src/modules/motion.c"
/* Transform a configured local Z vector through the state's linear matrix
 * and add it to the existing accumulated vector. Kind two selects the first
 * constant; other kinds select the alternate. Recheck kind after the helper.
 * For kind one, halve transformed Y in double precision only when value674
 * is strictly negative or positive; zeros and NaNs leave Y unchanged.
 * RE_UNKNOWN: kind/value ownership, constant units and the accumulated
 * vector's physical interpretation require original producers/callers. */
void motionAccumulateTransformedConfiguredVector(MotionConfiguredVectorState *state) {
    Vec3F localVector;
    Vec3F transformedVector;
    f32 signal;

    localVector.y = 0.0f;
    localVector.x = 0.0f;
    if (state->kind == 2) {
        localVector.z = D_motion_00415F84;
    } else {
        localVector.z = D_motion_00415F88;
    }
    gUvFmtxExports->uvMat4TransformDirection(&state->transform,
                                           &transformedVector, &localVector);
    if (state->kind == 1) {
        signal = state->value674;
        if (signal < 0.0f) {
            transformedVector.y = (f32)((f64)transformedVector.y * 0.5);
        } else if (signal > 0.0f) {
            transformedVector.y = (f32)((f64)transformedVector.y * 0.5);
        }
    }
    gUvFvecExports->uvVec3FAdd(&state->accumulatedVector,
                             &state->accumulatedVector, &transformedVector);
}
#line 252 "src/modules/motion.c"

#line 253 "src/modules/motion.c"
/* For enabled input with magnitude at least 0.5, gate on field 0x6C4
 * magnitude at most five and mode zero/two. Smooth response 0x998 toward
 * the signed mode target and enforce the original mode-dependent 0x988 bound.
 * Field units remain unproven; preserve strict comparisons and NaN paths. */
void motionApplyGatedModeResponse(MotionModeResponseState *state, s32 enabled, f32 input) {
    f32 gateValue;
    f32 previous;
    f32 magnitude;
    f32 target;
    s16 mode;
    if (enabled != 0) {
        if (input > 0.0f) {
            magnitude = input;
        } else {
            magnitude = -input;
        }
        if (!(magnitude < 0.5f)) {
            gateValue = state->gateValue;
            if (gateValue > 0.0f) {
                magnitude = gateValue;
            } else {
                magnitude = -gateValue;
            }
            if (!(magnitude > 5.0f) && ((mode = state->mode, mode == 0) || mode == 2)) {
                target = ((gateValue * D_motion_00415F8C) + 1.0f) * -15.0f;
                if (target < -3.0f) {
                    target = -3.0f;
                }
                if (mode == 0) {
                    target = -target;
                }
                previous = state->response;
                state->response += 5.0f * ((target * input) - previous) * D_80025D70;
                if (state->value988 < 2.0f && state->mode == 2) {
                    state->value988 = 2.0f;
                }
                if (state->value988 > -2.0f && state->mode == 0) {
                    state->value988 = -2.0f;
                }
            }
        }
    }
}
#line 254 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040F694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_0040FE84.s")

#line 259 "src/modules/motion.c"

/* Return one for a successful query whose final kind is not four.
 * Kind one is reclassified as four when its terrain triangle resolves to
 * loaded texture byte 0x27 equal to four. Reload shared terrain state for
 * that second query, preserving the original signed-byte promotion.
 * RE_UNKNOWN: caller input domain, mode/kind meanings, terrain-ID validity
 * and provider/shared-state lifetimes need original producers/callers. */
u16 motionQueryHasNonExcludedKind(MotionCollisionInput *input)
{
    MotionCollisionResult result;
    u16 hasNonExcludedKind = 0;

    if (((MotionCollisionQueryExports *)gUvIsectExports)->query(input, 9, 0,
            ((MotionCollisionSceneExports *)gSceneExports)->sharedState->terrainId,
            &result) != 0) {
        if (result.kind == 1) {
            if (((MotionCollisionQueryExports *)gUvIsectExports)->matchesTextureByte(
                    ((MotionCollisionSceneExports *)gSceneExports)->sharedState->terrainId,
                    result.triangleHandle, 4) != 0) {
                result.kind = 4;
            }
        }
        if (result.kind != 4) {
            hasNonExcludedKind = 1;
        }
    }
    return hasNonExcludedKind;
}
#line 260 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00411C64.s")

#line 263 "src/modules/motion.c"
/* Forward state, 1, embedded matrix 0x5E8 and 0 to the original helper.
 * RE_UNKNOWN: helper retention and mode meanings require its body and callers. */
void motionForwardStateMatrix(void *state) {
    func_motion_00411C64(state, 1, (void *)((u8 *)state + 0x5E8), 0);
}
#line 266 "src/modules/motion.c"

/* Bound selected paired scalars, then advance them through the original
 * sqrt, cosine, sine and MISC 0xDC factor callbacks in that order. Full-word
 * selectors stride 0x10; records start at 0x128, stride 0x130. Mirror the
 * stored scalar through each record's u16 slot and preserve live u16 count.
 * Forward state, 1, state+0x5E8, 0 to helper 0x11C64 when count is nonzero.
 * RE_UNKNOWN: physical units, selector/slot capacities, coefficient/divisor
 * domains, flag meaning and allocation/alias/lifetime need original producers.
 * Clean C differs in address reuse, branches, allocation and scheduling;
 * retain ASM pending complete instruction and relocation proof. */
#line 267 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412770.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412B14.s")

#line 271 "src/modules/motion.c"
/* RE_UNKNOWN: The s32 snapshot preserves promoted byte values; original lexical local type/order and complete historical allocation types remain unproved.
 * Runtime module availability and pointer lifetime/alias guarantees still require original loading and caller paths; no new null/default handling is added. */
/* Update CARANIM property 27 from the byte mode and ordered double
 * comparison. A zero mode activates the dynamic record, sets property 27,
 * clears CAM property 14, then invokes the existing state helper.
 * RE_UNKNOWN: mode/value meanings and units, object/input domains, allocation
 * extents, aliases and retained context lifetimes require original callers
 * and producers. Keep context captured before callbacks and reload mode
 * after the property callback; do not invent null/default handling. */
void motionUpdateModeGatedProperties(MotionModePropertyState *state)
{
    MotionModePropertySource *source;
    MotionModePropertyContext *context;
    s32 mode;

    mode = state->mode;
    context = state->context;
    if (mode != 0) {
        source = state->source;
        if (source->activeWord == 0) {
            mode = state->mode = 0;
        } else {
            if (((f64)D_80025D6C - source->comparisonValue > 0.25) || (mode == 1)) {
                ((MotionModePropertyCarExports *)D_motion_00416A84)->setProperties(
                    context->animationState, 27, 0, 0);
            } else {
                ((MotionModePropertyCarExports *)D_motion_00416A84)->setProperties(
                    context->animationState, 27, 1, 0);
            }
            mode = state->mode;
        }
    }
    if (mode == 0) {
        ((MotionModePropertyDynamicExports *)gUvDynExports)->setValue(
            state->dynamicRecord, 0, 1.0f);
        ((MotionModePropertyCarExports *)D_motion_00416A84)->setProperties(
            context->animationState, 27, 1, 0);
        ((MotionModePropertyCameraExports *)gCamExports)->setProperties(
            context->cameraRecord, 14, 0, 0);
        func_motion_004039BC(state);
    }
}
#line 272 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00412E44.s")

#line 275 "src/modules/motion.c"
/* Preserve the original callback inputs, captured context and later context reload. */
/* Apply the original dynamic/object flags, CARANIM properties and three
 * rumble merges, then forward CAM tag18 and configure the returned PIECE object.
 * RE_ORIGINAL_QUIRK: the PIECE source handle reloads state->context after
 * callbacks, while the final CARANIM call uses the initially captured context.
 * RE_UNKNOWN: property/value roles and physical units, caller ID domains,
 * module availability, record allocations, aliases and retained pointer
 * lifetimes require original producers/callers. Keep the original read order
 * and callback results without adding null/default handling. */
void motionApplyPropertyAndRumbleSequence(MotionPropertySequenceState *state)
{
    MotionPropertySequenceContext *context;
    Vec3F pieceVector;
    s32 pieceHandle;

    context = state->context;
    ((MotionPropertySequenceDynamicExports *)gUvDynExports)->setReference(
        state->dynamicRecord, 0);
    ((MotionPropertySequenceObjectExports *)gUvDobjExports)->clearFlags(
        context->objectHandle, 1);
    ((MotionPropertySequenceCarExports *)D_motion_00416A84)->setProperties(
        context->animationState, 27, 0, 10, 0, 0);
    ((MotionPropertySequenceRumbleExports *)gRumbleExports)->mergePatternValues(
        context->rumbleIndex, 1.0f, 0.5f, 0.0f);
    ((MotionPropertySequenceRumbleExports *)gRumbleExports)->mergePatternValues(
        context->rumbleIndex, 0.7f, 0.5f, 0.5f);
    ((MotionPropertySequenceRumbleExports *)gRumbleExports)->mergePatternValues(
        context->rumbleIndex, 0.4f, 0.5f, 1.0f);
    ((MotionPropertySequenceCameraExports *)gCamExports)->setProperties(
        context->cameraRecord, 18, 3, (f64)context->cameraRecord->value15C, 0);
    pieceVector = D_motion_00416A64;
    pieceHandle = ((MotionPropertySequencePieceExports *)gPieceExports)->createFromObject(
        state->context->objectHandle, 99, &pieceVector, 8.0f, 2.0f, -1);
    ((MotionPropertySequenceCarExports *)D_motion_00416A84)->configureObject(
        pieceHandle, context->animationState);
}
#line 276 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004130E4.s")

/* Original cross/add/transform and dot products update phase 0x8D4 and
 * component 0x998; 0x988/0x998 overlap vector 0x984.y / vector 0x990.z.
 * RE_ORIGINAL_QUIRK: caller passes 1-dot*dot directly; the bound sqrt export
 * returns zero for ordered-negative input. Keep phase reloads and NaN tests.
 * RE_UNKNOWN: vector frames/units, normalized-input/phase domains and linked
 * record lifetime need original producers/callers. Clean C remains unmatched;
 * retain original assembly pending complete instruction/relocation proof. */
#line 279 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00413284.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00413568.s")

/* Gate scaling of scalar 0x988 by count 0x10E0, mode 0xA3C, vector dots
 * and signed kinds 0xA40/0xA68. Original UVFV 0x18 is a three-single dot
 * leaf; preserve repeated calls and postcall field reloads. Mode 1 returns
 * after a successful vector gate even when the input/kind test rejects it.
 * RE_ORIGINAL_QUIRK: mode-2 kinds 4/6 accept input >= 0; 7/5 require > 0.
 * RE_UNKNOWN: vector frames/normalization, scalar units, kind/count domains
 * and state/config lifetime need original producers/callers. Clean C remains
 * unmatched; retain assembly pending complete byte/relocation proof. */
#line 283 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414430.s")

#line 285 "src/modules/motion.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_motion_0041475C(void) {
}
#line 287 "src/modules/motion.c"

#line 288 "src/modules/motion.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_motion_00414764(void) {
}
#line 290 "src/modules/motion.c"

#line 291 "src/modules/motion.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_motion_0041476C(void) {
}
#line 293 "src/modules/motion.c"

/* Draw background, graph-derived red/green bars, direct-value blue bar and
 * a white marker from saved input 0x6D4. Preserve single arithmetic grouping,
 * truncating signed coordinates and input reads between draw callbacks.
 * Original UVGRPH 0x04 is linear evaluation; UVGEOM 0x0C/0x10 consume four
 * singles for color / four signed words for rectangle coordinates.
 * RE_UNKNOWN: scalar meanings/units, reachable input/coordinate ranges and
 * graphics-state ownership need original producers/callers. Clean C remains
 * unmatched; retain assembly pending complete byte/relocation proof. */
#line 294 "src/modules/motion.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414774.s")

#line 296 "src/modules/motion.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_motion_00414A68(s32 a0) {
}
#line 298 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414A70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00414BB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004151CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_004154B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00415724.s")

#line 309 "src/modules/motion.c"
/* Any nonzero selector chooses D_motion_004163A8; zero chooses
 * D_motion_0041644C. Forward the input to the original curve evaluator.
 * RE_UNKNOWN: input units/range, graph writers/knot ordering and module
 * availability need producers; this wrapper adds no input clamp. */
#line 311 "src/modules/motion.c"
f32 motionEvaluateSelectedGraph(f32 inputValue, s32 alternateGraphSelector) {
    UvGrphStruct *selectedGraph;
    if (alternateGraphSelector != 0) {
        selectedGraph = &D_motion_004163A8;
    } else {
        selectedGraph = &D_motion_0041644C;
    }
    return gUvGrphExports->uvGrphEvaluateLinearCurve(selectedGraph, inputValue);
}
#line 310 "src/modules/motion.c"

#line 311 "src/modules/motion.c"
/* Read the unsigned halfword at state offset 0x70C without modifying the caller object. RE_UNKNOWN: the field role requires its writers and consumers; no status or identifier meaning is assumed. */
u16 func_motion_00415870(void *state) {
    return *(u16 *)((u8 *)state + 0x70C);
}
#line 314 "src/modules/motion.c"

#line 315 "src/modules/motion.c"
/* For a nonzero speech setting, set volume, then truncate randomScalar*4.
 * Only choice three with pending word D_motion_004160A0 set submits Hot Lava
 * speech with priority 0x7FFF and playback value 0x7A120.
 * RE_ORIGINAL_QUIRK: retain every choice gate, store the emitter byte and
 * clear pending after the attempt even when the returned emitter is 255.
 * RE_UNKNOWN: speech-setting bounds, pending writers/rearming, module
 * availability and playback-value units need producer/consumer evidence. */
#line 317 "src/modules/motion.c"
extern s32 D_motion_004160A0;
extern s32 gOptionsSpeechVol;

void motionTryPlayHotLavaVoice(void) {
    s32 voiceChoice;

    if (gOptionsSpeechVol != 0) {
        gSndExports->sndSetSpeechVol(gOptionsSpeechVol);
        voiceChoice = (s32) (gUvMathExports->uvRandFLcg() * 4.0f);
        if ((voiceChoice != 0) && (voiceChoice != 1) && (voiceChoice != 2) && (voiceChoice == 3) && (D_motion_004160A0 != 0)) {
            D_motion_00416AF0 = gSndExports->sndPlaySharedHandleWithPlaybackValue(V_HOTLAVA, 0x7FFF, gSndExports->sndGetSpeechVolumeScale(), 0x7A120);
            D_motion_004160A0 = 0;
        }
    }
}
#line 316 "src/modules/motion.c"

#line 317 "src/modules/motion.c"
/* For a nonzero speech setting, set volume, then truncate randomScalar*4.
 * Only choice three with pending word D_motion_004160A4 set submits explosion
 * speech. Scale the getter result by original D_motion_0041607C (0.9f);
 * retain priority 0x7FFF and playback value 0x1F4.
 * RE_ORIGINAL_QUIRK: retain every choice gate, store the emitter byte and
 * clear pending after the attempt even when the returned emitter is 255.
 * RE_UNKNOWN: speech-setting bounds, pending writers/rearming, module
 * availability, tuning purpose and playback-value units need evidence. */
#line 319 "src/modules/motion.c"
extern f32 D_motion_0041607C;
extern s32 D_motion_004160A4;
extern s32 gOptionsSpeechVol;

void motionTryPlayExplosionVoice(void) {
    s32 voiceChoice;

    if (gOptionsSpeechVol != 0) {
        gSndExports->sndSetSpeechVol(gOptionsSpeechVol);
        voiceChoice = (s32) (gUvMathExports->uvRandFLcg() * 4.0f);
        if ((voiceChoice != 0) && (voiceChoice != 1) && (voiceChoice != 2) && (voiceChoice == 3) && (D_motion_004160A4 != 0)) {
            D_motion_00416AF1 = gSndExports->sndPlaySharedHandleWithPlaybackValue(V_EXPLOSION, 0x7FFF, gSndExports->sndGetSpeechVolumeScale() * D_motion_0041607C, 0x1F4);
            D_motion_004160A4 = 0;
        }
    }
}
#line 318 "src/modules/motion.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/motion/func_motion_00415A3C.s")

