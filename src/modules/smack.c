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
void func_smack_00401240();
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_0040038C.s")

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

