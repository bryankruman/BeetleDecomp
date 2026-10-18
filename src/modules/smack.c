// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvquat_rom.h"
#include "uvdobj_rom.h"
#include "module.h"
#include "global_exports.h"
#line 6 "src/modules/smack.c"
extern UvDobj_Exports *gUvDobjExports;
typedef struct { u8 unk00[0x18]; Vec3F position; u8 unk24[8]; s32 objectId; u8 unk30[8]; u8 active; u8 unk39; u8 blocked; } SmackObjectRecord;
void func_smack_004000E8();
void func_smack_00400290();
void func_smack_0040038C();
SmackObjectRecord *func_smack_0040062C(s32, s32);
SmackObjectRecord *smackAttachObjectRecord(s32 objectId);
void func_smack_00400824();
void smackDetachActiveRecord();
s32 func_smack_0040097C(void *, Vec3F *, Vec3F *, Mtx4F *);
#line 16 "src/modules/smack.c"
typedef struct {
    Vec3F velocity;             /* observed float fields 0x00..0x08 */
    Vec3F angularVelocity;      /* observed rotation rates 0x0C..0x14 */
    Vec3F position;             /* observed copied position 0x18..0x20 */
    u8 unknown24[8];
    s32 objectId;               /* observed DOBJ identifier at 0x2C */
} SmackMotionState;
extern f32 D_80025D70;
extern f32 D_smack_0040161C;
void smackAdvanceObjectMotion(SmackMotionState *);
#line 17 "src/modules/smack.c"
extern f32 D_smack_00401620;
void smackSetVelocityAndRandomizeSpin(SmackMotionState *, f32, Vec3F *);
#line 18 "src/modules/smack.c"
void func_smack_00401240(void *, f32, Vec3F *);
s32 smackGetPlayerValue(u8 player);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/__entrypoint_func_smack_400000.s")

#line 22 "src/modules/smack.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_smack_004000E0(void) {
}
#line 24 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_004000E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00400290.s")

/* Consumed views only. RE_UNKNOWN: authored full types, backing extents and
 * callback/provider mutation and lifetime guarantees; no storage is added. */
#include "uvasset_types.h"
typedef struct {
    u8 unknown00[0x18];
    Vec3F position18;
    u8 unknown24[8];
    s32 objectId2C;
    u8 unknown30[4];
    s32 modelId34;
    u8 dynamicObject38;
    u8 occupied39;
    u8 blocked3A;
    u8 detachRequested3B;
} SmackImpactRecordView;
typedef struct { u8 unknown00[0x14]; s32 controllerIndex14; } SmackImpactSourceView;
typedef struct {
    f32 minimumMagnitude00;
    f32 replacementThreshold04;
    u8 unknown08[0x18];
    f32 gateReset20;
    u8 unknown24[0xC];
    s32 returnFlag30;
    u8 unknown34[4];
    s32 (*callback38)(SmackImpactRecordView *, f32, Vec3F *, SmackImpactSourceView *);
} SmackImpactConfigurationView;
typedef struct {
    u8 unknown00[0x18];
    void (*impact18)(s32, f32, Vec3F *);
} SmackImpactAudioExportsView;
extern void *gCarAudioExports;
extern f32 D_smack_00401638;
extern f32 D_smack_0040163C;
extern f32 D_smack_00401610;
extern f32 D_smack_00401614;
s32 smackProcessObjectImpact(SmackImpactRecordView *, Vec3F *, SmackImpactSourceView *);
/* The func_smack_00401240 prototype is completed near its original declaration
 * using the actual 192-instruction provider: A0 is the record; A1 is homed then
 * read as f32 at 0x00401490; A2 is the vector passed to scaling at 0x00401428.
 * RE_UNKNOWN: the helper's authored record type and callback 0x38's authored
 * type. The callback view describes only arguments consumed at this callsite. */

/* Apply the loaded model's impact thresholds, optional hook and effects.
 * A weak hit requests detachment and returns zero. Models 0x80/0xF6 also use
 * their shared gate before audio. Audio may set blocked; the later hook may
 * end processing before rumble and motion/replacement dispatch.
 * RE_ORIGINAL_QUIRK: reload blocked after audio, preserve ordered float tests,
 * retain the configuration pointer across callbacks, and finally store 1 to
 * blocked even if audio already changed it. No callback rollback is added.
 * RE_UNKNOWN: source/controller bounds, magnitude/gate units, descriptor and
 * callback lifetimes/aliasing, return-code meanings and authored full types.
 */
s32 smackProcessObjectImpact(SmackImpactRecordView *record, Vec3F *impactVector,
                             SmackImpactSourceView *source) {
    f32 magnitude;
    ParsedUVMD *model;
    SmackImpactConfigurationView *configuration;
    s32 (*callback)(SmackImpactRecordView *, f32, Vec3F *, SmackImpactSourceView *);

    if (record == NULL) {
        return 0;
    }
    if (record->occupied39 == 0) {
        return 0;
    }
    if (record->blocked3A != 0) {
        return 1;
    }
    model = uvGetLoadedFile('UVMD', record->modelId34);
    if (model == NULL || model->unk20 == NULL) {
        return 0;
    }
    configuration = (SmackImpactConfigurationView *)model->unk20;
    magnitude = gUvFvecExports->uvVec3FLen(impactVector);
    if (magnitude < configuration->minimumMagnitude00) {
        record->detachRequested3B = 1;
        return 0;
    }
    if (record->modelId34 == 0x80) {
        if (D_smack_00401638 > 0.0f || magnitude < D_smack_00401610) {
            return 1;
        }
        D_smack_00401638 = configuration->gateReset20;
    }
    if (record->modelId34 == 0xF6) {
        if (D_smack_0040163C > 0.0f || magnitude < D_smack_00401614) {
            return 1;
        }
        D_smack_0040163C = configuration->gateReset20;
    }
    ((SmackImpactAudioExportsView *)gCarAudioExports)->impact18(
        record->modelId34, magnitude, &record->position18);
    if (record->blocked3A == 0) {
        callback = configuration->callback38;
        if (callback != NULL && callback(record, magnitude, impactVector, source) != 0) {
            record->detachRequested3B = 1;
            return 1;
        }
        if (source != NULL) {
            ((Rumble_Exports *)gRumbleExports)->rumbleMergeQuantizedPatternValues(
                source->controllerIndex14, 0.5f, 0.3f, 0.0f);
        }
        if (configuration->replacementThreshold04 < magnitude) {
            func_smack_00401240(record, magnitude, impactVector);
        } else {
            smackSetVelocityAndRandomizeSpin((SmackMotionState *)record,
                                            magnitude, impactVector);
        }
    }
    record->blocked3A = 1;
    if (configuration->returnFlag30 != 0) {
        if (record->dynamicObject38 != 0) {
            return 2;
        }
        return 3;
    }
    return 1;
}


#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_0040062C.s")

#line 33 "src/modules/smack.c"
/* Find the effect record for this object model. Unless blocked, activate it,
 * retain the object ID and copy the object matrix translation into position.
 * Return the original lookup result even when the record is blocked. */
SmackObjectRecord *smackAttachObjectRecord(s32 objectId) {
    SmackObjectRecord *record;
    Mtx4F matrix;
    record = func_smack_0040062C(gUvDobjExports->uvDobjGetModel(objectId), objectId);
    if (record != NULL && record->blocked == 0) {
        record->active = 1;
        record->objectId = objectId;
        gUvDobjExports->uvDobjGetPosm(objectId, 0, &matrix);
        record->position = *(Vec3F *)&matrix.m[3][0];
    }
    return record;
}
#line 34 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00400824.s")

#line 37 "src/modules/smack.c"
/* When record byte 0x39 is active, set its object word at 0x2C to -1
 * and clear that byte. Leave inactive records unchanged. */
void smackDetachActiveRecord(void *record) {
    if (*(u8 *)((u8 *)record + 0x39) != 0) {
        *(s32 *)((u8 *)record + 0x2C) = -1;
        *(u8 *)((u8 *)record + 0x39) = 0;
    }
}
#line 43 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_0040097C.s")

/* Advance the object's translation by velocity times the shared scalar.
 * The existing step helper decides whether rotations and matrix publication
 * run; gravity-like Z acceleration and the position copy run on either path.
 * RE_ORIGINAL_QUIRK: retain the scalar snapshot across provider callbacks,
 * live record reloads and the pre-step translation copied into position.
 * RE_UNKNOWN: time units, the step helper's full policy and record lifetime. */
void smackAdvanceObjectMotion(SmackMotionState *record) {
    Mtx4F transform;
    Vec3F previousPosition;
    Vec3F nextPosition;
    f32 step;

    step = D_80025D70;
    gUvDobjExports->uvDobjGetPosm(record->objectId, 0, &transform);
    gUvFvecExports->uvVec3FCopy(&previousPosition, (Vec3F *)&transform.m[3][0]);
    transform.m[3][0] += record->velocity.x * step;
    transform.m[3][1] += record->velocity.y * step;
    transform.m[3][2] += record->velocity.z * step;
    gUvFvecExports->uvVec3FCopy(&nextPosition, (Vec3F *)&transform.m[3][0]);
    if (func_smack_0040097C(record, &previousPosition, &nextPosition, &transform) == 0) {
        gUvFmtxExports->uvMat4RotateAxis(&transform, record->angularVelocity.x * step, 'x');
        gUvFmtxExports->uvMat4RotateAxis(&transform, record->angularVelocity.y * step, 'y');
        gUvFmtxExports->uvMat4RotateAxis(&transform, record->angularVelocity.z * step, 'z');
        gUvDobjExports->uvDobjPosm(record->objectId, 0, &transform);
    }
    record->velocity.z += D_smack_0040161C * step;
    gUvFvecExports->uvVec3FCopy(&record->position, &previousPosition);
}
#line 47 "src/modules/smack.c"

/* Scale the supplied vector into velocity, add a magnitude-scaled Z term,
 * and generate angular components using separate sign/value random draws.
 * X/Y angular fields change only for strength > 8 or matrix[2][2] < 0.5;
 * Z always changes. Preserve ordered calls and left-associated float products.
 * RE_ORIGINAL_QUIRK: the sign draw and value draw are independent; this is
 * not an absolute-value random sampler. Nonpositive strength is negated,
 * retaining the original signed-zero/unordered comparison behavior.
 * RE_UNKNOWN: strength units, random distribution contract and record aliasing. */
void smackSetVelocityAndRandomizeSpin(SmackMotionState *record, f32 strength, Vec3F *vector) {
    Mtx4F transform;
    Vec3F scaledVector;
    f32 magnitude;
    f32 draw;

    if (strength > 0.0f) {
        magnitude = strength;
    } else {
        magnitude = -strength;
    }
    gUvDobjExports->uvDobjGetPosm(record->objectId, 0, &transform);
    gUvFvecExports->uvVec3FScale(&scaledVector, vector, 1.5f);
    gUvFvecExports->uvVec3FCopy(&record->velocity, &scaledVector);
    record->velocity.z += D_smack_00401620 * magnitude;
    if ((strength > 8.0f) || (transform.m[2][2] < 0.5f)) {
        draw = (gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f;
        draw = (draw > 0.0f)
            ? (gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f
            : -((gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f);
        record->angularVelocity.x = (draw * 0.5f) * magnitude;
        draw = (gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f;
        draw = (draw > 0.0f)
            ? (gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f
            : -((gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f);
        record->angularVelocity.y = (draw * 0.5f) * magnitude;
    }
    draw = (gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f;
    draw = (draw > 0.0f)
        ? (gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f
        : -((gUvMathExports->uvRandFLcg() - 0.5f) * 2.0f);
    record->angularVelocity.z = (draw * 0.5f) * magnitude;
}
#line 49 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00401240.s")

#line 47 "src/modules/smack.c"
extern s16 D_smack_00401630[];
/* Return zero for player indices at least four; otherwise return the selected
 * signed halfword from the shared four-entry table.
 * RE_UNKNOWN: table meaning and refresh lifetime require consumers. */
#line 49 "src/modules/smack.c"
s32 smackGetPlayerValue(u8 player) {
    if (player >= 4) { return 0; }
    return D_smack_00401630[player];
}
#line 53 "src/modules/smack.c"
#line 48 "src/modules/smack.c"

