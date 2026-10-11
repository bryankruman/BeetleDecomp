// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvquat_rom.h"
#include "uvasset_types.h"
#include "uvdobj_rom.h"
#include "uvmodel_rom.h"
/* Consumed fields and export slots only; this is not a complete terrain ABI. */
typedef struct {
    u16 model; u8 opaque02[0x12];
    f32 scalar14; u8 opaque18[4];
    s32 word1C; u8 opaque20[0x20];
    u32 word40;
} PieceTerrainConsumedPrefix;
typedef struct {
    u8 opaque00[0x80];
    void (*getMatrix)(s32, s32, Mtx4F *);
    u8 opaque84[4];
    void (*setModel)(s32, s32);
    u8 opaque8C[0x18];
    PieceTerrainConsumedPrefix *(*getObject)(s32);
} PieceTerrainConsumedExports;
extern UvDobj_Exports *gUvDobjExports;
extern UvModel_Exports *gUvModelExports;
extern PieceTerrainConsumedExports *gUvTerraExports;
/* Consumed six-argument call interface: callers ignore any return value.
 * RE_UNKNOWN: The historical helper return type and complete API are unknown. */
void func_piece_004006E0(s32, s32, Vec3F *, f32, f32, f32);
#line 2 "src/modules/piece.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_004000CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_004001F4.s")

/* Original five-slot walk at stride0x20: re-read each byte0x10 and call
 * helper0x401F4 on that indexed record only when the byte is nonzero.
 * RE_UNKNOWN: byte meaning, complete record layout/extent, ownership and
 * helper update lifetime require original creation/field writers and callers.
 * RE_UNKNOWN: historical source access views; the readable draft preserves
 * the observed loop, loads, call and argument but compiler base-address
 * reuse/scheduling still differs. Retain native assembly until grounded. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400670.s")
#line 9 "src/modules/piece.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_004006E0.s")

/* Optionally create a dynamic object with the requested model and transfer
 * matrices from the source object. Matching model IDs copy the reported node
 * count; other models copy one matrix. Pass the borrowed vector and three
 * scalar arguments to the retained piece helper, then update the source model
 * or clear its flags. Return the created ID, or -1 when creation is skipped.
 * RE_ORIGINAL_QUIRK: Creation and property-query results are unchecked. The
 * source update still runs when the requested replacement model is -1.
 * RE_UNKNOWN: Property 7 scalar meaning, helper behavior, valid model/node
 * domains, provider failure outputs and borrowed-vector lifetime need callers. */
s32 pieceCreateDynamicReplacementAndUpdateSourceModel(s32 sourceId, s32 replacementModel, Vec3F *vector,
    f32 scalar0, f32 scalar1, s32 finalSourceModel) {
    s32 node;
    s32 copyCount;
    s32 modelNodeCount;
    s32 sourceModel;
    s32 newObjectId;
    f32 sourceScalar;
    Mtx4F nodeMatrix;

    newObjectId = -1;
    if (replacementModel != -1) {
        gUvDobjExports->uvDobjGetProp(sourceId, 8, &sourceModel, 7, &sourceScalar, 0);
        gUvModelExports->uvModelGetProps(replacementModel, 4, &modelNodeCount, 0);
        newObjectId = gUvDobjExports->uvDobjCreate();
        gUvDobjExports->uvDobjModel(newObjectId, replacementModel);
        if (sourceModel == replacementModel) {
            copyCount = modelNodeCount;
        } else {
            copyCount = 1;
        }
        for (node = 0; node < copyCount; node++) {
            gUvDobjExports->uvDobjGetPosm(sourceId, node, &nodeMatrix);
            gUvDobjExports->uvDobjPosm(newObjectId, node, &nodeMatrix);
        }
        func_piece_004006E0(newObjectId, replacementModel, vector,
            scalar0, scalar1, sourceScalar);
    }
    if (finalSourceModel != -1) {
        gUvDobjExports->uvDobjModel(sourceId, finalSourceModel);
    } else {
        gUvDobjExports->uvDobjSetFlags(sourceId, 0);
    }
    return newObjectId;
}
#line 13 "src/modules/piece.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/__entrypoint_func_piece_400e90.s")

#line 16 "src/modules/piece.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_piece_00400F48(void) {
}
#line 18 "src/modules/piece.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400F50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00401104.s")

