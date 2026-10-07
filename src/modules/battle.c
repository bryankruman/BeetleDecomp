/*__SEEDEXTERNS__*/
typedef struct {
    /* 0x00 */ float unk0;
    /* 0x04 */ float unk4;
    /* 0x08 */ int unk8;
} BattleViewEntry_004090F0; /* size = 0xC */

typedef struct {
    /* 0x00 */ char pad[0x3C];
    /* 0x3C */ void (*unk3C)(float, float, int, int);
} UvGfxMgrExp_004090F0;
extern BattleViewEntry_004090F0 D_battle_00409D28[];
extern UvGfxMgrExp_004090F0 *gUvGfxMgrExports;
typedef struct {
    /* 0x00 */ int unk0;
    /* 0x04 */ int unk4;
    /* 0x08 */ char pad8[0xC];
    /* 0x14 */ void *unk14;
    /* 0x18 */ char pad18[0x10];
    /* 0x28 */ int unk28;
} Node_00407F30;
typedef struct { char pad0[0x14]; void (*unk14)(void *, void *); char pad18[0x18]; void (*unk30)(void *, int); } UvDobjExp_00407F30;
typedef struct { char pad0[0xCC]; void (*unkCC)(void *); } SndExp_00407F30;
extern void *D_battle_00409EF8[];
typedef struct { char pad[0xFC]; void (*unkFC)(void *, int, int); } MiscExp_00401A68;
extern MiscExp_00401A68 *gMiscExports;
extern int D_battle_00409AB0;
extern int D_battle_00409AB4;
extern int D_battle_00409AC0;
extern int D_battle_00409AC8;
extern int D_battle_00409AD0;
extern int D_battle_0040A058;
extern int D_battle_0040A05C;
extern int D_battle_0040A060;
extern int D_battle_0040A064;
typedef struct { char pad[0x38]; void (*unk38)(int, int); } UvDobjExp_407E78;
typedef struct { char pad[0x2C]; void (*unk2C)(int); } UvPfxExp_407E78;
typedef struct { char pad[0xCC]; void (*unkCC)(void *); } SndExp_407E78;
extern UvDobjExp_407E78 *gUvDobjExports;
extern UvPfxExp_407E78 *gUvPfxExports;
extern SndExp_407E78 *gSndExports;
typedef struct {
    /* 0x00 */ char pad0[0x4];
    /* 0x04 */ int unk4;
    /* 0x08 */ char pad8[0xC];
    /* 0x14 */ int unk14;
    /* 0x18 */ char pad18[0x10];
    /* 0x28 */ int unk28;
    /* 0x2C */ char unk2C[0x8];
    /* 0x34 */ char unk34[0x8];
} BattleObj_407E78;
typedef struct BattleObj_00405034_s {
    void *unk0;
    char pad4[0x5A0];
    float unk5A4;
    int   unk5A8;
} BattleObj_00405034;
typedef struct BattleSubObj_00405034_s {
    char pad0[0xC];
    void *unkC;
} BattleSubObj_00405034;
typedef struct CamTarget_00405034_s {
    char pad0[0x1C];
    float unk1C;
} CamTarget_00405034;
typedef struct CamExports_00405034_s {
    char pad0[0x20];
    void (*unk20)(void *, int, int, int, double, int);
} CamExports_00405034;
typedef struct {
    char pad[0x20];
    void (*unk20)(void *, int, int, int, double, int);
} CamExp_404F9C;
extern CamExp_404F9C *gCamExports;
typedef struct {
    char pad0[0xC];
    void *unkC;
} SubObj_404F9C;
typedef struct {
    char pad0[0x1C];
    float unk1C;
} CamTarget_404F9C;
typedef struct {
    SubObj_404F9C *unk0;
    char pad4[0x5A8];
    float unk5AC;
    int   unk5B0;
} Obj_404F9C;
extern float D_battle_00409C38;
typedef struct {
    char pad21C[0x21C];
    /* 0x21C */ int unk21C;
    char pad220[0x8];
    /* 0x228 */ float unk228;
    /* 0x22C */ float unk22C;
    /* 0x230 */ float unk230;
    /* 0x234 */ float unk234;
    /* 0x238 */ float unk238;
} Inner_404F18;
typedef struct {
    char pad0[0xC];
    /* 0x00C */ Inner_404F18 *unkC;
} Mid_404F18;
typedef struct {
    /* 0x000 */ Mid_404F18 *unk0;
    char pad4[0x59C];
    /* 0x5A0 */ float unk5A0;
} Outer_404F18;
typedef struct { char pad0[0xC]; void (*unkC)(void); } Exports_00401B34;
extern void func_80000CA4(int);
extern void func_80000D58(int);
extern void func_battle_00401BB8(void);
extern short D_80025D76;
extern Exports_00401B34 *D_battle_0040A044;
extern int D_battle_0040A068;
extern int D_debugEnable;
extern int gDebugFrateDisp;
typedef struct {
    /* 0x000 */ int unk0;
    /* 0x004 */ unsigned char pad4[0x5B8 - 0x4];
} Node_400D38; /* size = 0x5B8 */

extern void func_battle_00405ADC(Node_400D38 *, int);
extern Node_400D38 D_battle_0040A080[];
extern int D_battle_0040C2B4;
// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
typedef struct { Vec3F position; f32 scalarC, scalar10, time; u8 gap18[0xDC]; s32 flagF4; } BattleMotionSource;
typedef struct { BattleMotionSource *source; u8 gap4[0x14]; s32 handle; } BattleMotionLink;
typedef struct { BattleMotionLink *link; u8 gap4[0xAC]; f32 scalarB0, scalarB4; Vec3F position; } BattleResetNode;
typedef struct { u8 prefix[0x28]; void (*getMatrix)(s32, s32, Mtx4F *); } BattleReadMatrixExports;
typedef struct { u8 prefix[0x3C]; void (*apply)(BattleMotionSource *, Vec3F *, s32); } BattleMotionResetExports;
extern BattleMotionResetExports *D_battle_0040A050;
extern f32 D_80025D6C;
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct { u8 prefix[8]; s32 index; u8 gapC[8]; s32 handle; } BattleTranslatedObject;
typedef struct { u8 prefix[0x24]; void (*setMatrix)(s32, s32, Mtx4F *); u8 gap28[8]; void (*setMode)(s32, s32); } BattleTransformExports;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
#include "uvfvec_rom.h"
typedef struct { u8 prefix[0x2254]; s32 firstCount, secondCount; } BattleVectorCounts;
extern s32 D_battle_0040C2D8;
extern Vec3F D_battle_0040C2F8[], D_battle_0040C460[];
extern UvFVec_Rom_Exports *gUvFvecExports;

#include "uvgfxmgr_rom.h"
#include "uvfvec_rom.h"
typedef struct { s32 paletteIndex; } BattlePaletteSelector;
extern Vec3F D_battle_00409C80[];
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/__entrypoint_func_battle_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004006A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00400788.s")

/* Iterate D_battle_0040A080 array; call func_battle_00405ADC on each entry whose first field matches arg0. */
#line 145 "src/modules/battle.c"
/* Visit the original 0x5B8-byte battle nodes and run the state update
 * with mode zero for every matching first-word key. Reload shared count
 * after callbacks and preserve the empty/nonpositive-count behavior. */
void battleUpdateMatchingNodes(int key) {
    Node_400D38 *node;
    int index;

    index = 0;
    if (D_battle_0040C2B4 > 0) {
        node = &D_battle_0040A080[0];
        do {
            if (key == node->unk0) {
                func_battle_00405ADC(node, 0);
            }
            index += 1;
            node++;
        } while (index < D_battle_0040C2B4);
    }
}
#line 161 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00400DB0.s")

#line 164 "src/modules/battle.c"
/* Copy a vector into one of two original battle tables and increment
 * the matching count. Kind one deliberately indexes by shared word C2D8
 * while incrementing the separate count at 0x2258; retain that distinction.
 * Unsupported kinds do nothing and callers own table capacities. */
void battleStoreVectorByKind(s32 kind, Vec3F *value) {
    switch (kind) {
        case 0:
            gUvFvecExports->uvVec3FCopy(&D_battle_0040C2F8[((BattleVectorCounts *)D_battle_0040A080)->firstCount], value);
            ((BattleVectorCounts *)D_battle_0040A080)->firstCount++;
            return;
        case 1:
            gUvFvecExports->uvVec3FCopy(&D_battle_0040C460[D_battle_0040C2D8], value);
            ((BattleVectorCounts *)D_battle_0040A080)->secondCount++;
            return;
    }
}
#line 165 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004013D8.s")

/* Submit the original five diagnostic records through misc export 0xFC. */
#line 169 "src/modules/battle.c"
/* Submit the five original battle diagnostic records through misc export
 * 0xFC, retaining their associated words and the original 180/170/150/160/150
 * constants. This helper is used by the gated debug path in the frame callback. */
void battleSubmitFiveDebugRecords(void) {
    gMiscExports->unkFC(&D_battle_00409AB0, D_battle_0040A058, 0xB4);
    gMiscExports->unkFC(&D_battle_00409AB4, D_battle_0040A05C, 0xAA);
    gMiscExports->unkFC(&D_battle_00409AC0, D_battle_0040A060, 0x96);
    gMiscExports->unkFC(&D_battle_00409AC8, D_battle_0040A064, 0xA0);
    gMiscExports->unkFC(&D_battle_00409AD0, D_battle_0040A068, 0x96);
}
#line 176 "src/modules/battle.c"

/* Run the battle callbacks and conditionally submit debug records. */
#line 178 "src/modules/battle.c"
/* Run the optional callback, bracket the main battle callback with the
 * original two engine helpers, then submit diagnostics only when debug
 * output is enabled and its display selector is two. Preserve callback order. */
void battleRunFrameCallbacks(void) {
    if (D_80025D76 != 0) {
        D_battle_0040A044->unkC();
    }
    func_80000CA4(D_battle_0040A068);
    func_battle_00401BB8();
    func_80000D58(D_battle_0040A068);
    if ((D_debugEnable != 0) && (gDebugFrateDisp == 2)) {
        battleSubmitFiveDebugRecords();
    }
}
#line 189 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00401BB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00401DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00402750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040282C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00402CD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00402F6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040372C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00403A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00403D08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00404074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040425C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00404438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00404580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00404694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004049C8.s")

/* Reset linked fields only while the existing node scalar is nonnegative. */
#line 221 "src/modules/battle.c"
/* When the existing scalar at 0x5A0 is nonnegative, store the supplied
 * value and reset the linked record fields at 0x21C and 0x228..0x238.
 * Field units remain unproven; preserve the comparisons and store order. */
void battleResetLinkedFieldsWhenScalarEnabled(Outer_404F18 *node, float value) {
    if (node->unk5A0 >= 0.0f) {
        node->unk5A0 = value;
        node->unk0->unkC->unk234 = D_battle_00409C38;
        node->unk0->unkC->unk238 = 1.0f;
        node->unk0->unkC->unk228 = 1.0f;
        node->unk0->unkC->unk22C = 1.0f;
        node->unk0->unkC->unk230 = 1.0f;
        node->unk0->unkC->unk21C = 1;
    }
}
#line 232 "src/modules/battle.c"

/* Inferred camera export table; only unk20 is used here */
/* Sub-object reached via arg0->unk0; offset 0xC holds a camera-target pointer */
/* RE_UNKNOWN: linked field 0x1C supplies a camera scalar; its physical meaning and units require caller/callee evidence. */
/* Primary object passed as arg0 */
/* Gate the camera call on a nonnegative current scalar and a clear one-shot flag. */
#line 238 "src/modules/battle.c"
/* With the current scalar at 0x5AC nonnegative, store the new scalar.
 * If the separate one-shot flag is clear, set it and forward the negated
 * linked target scalar to camera export 0x20. No sign crossing is required. */
void battleSetNegatedCameraScalarOnce(Obj_404F9C *node, float value) {
    void *cameraTarget;

    cameraTarget = node->unk0->unkC;
    if (node->unk5AC >= 0.0f) {
        node->unk5AC = value;
        if (node->unk5B0 == 0) {
            node->unk5B0 = 1;
            gCamExports->unk20(cameraTarget, 0xA, 0, 9, (double)(-(((CamTarget_404F9C *)cameraTarget)->unk1C)), 0);
        }
    }
}
#line 250 "src/modules/battle.c"

/* Forward a scaled target scalar through the gated one-shot camera path. */
#line 252 "src/modules/battle.c"
/* With the current scalar at 0x5A4 nonnegative, store the new scalar.
 * If the separate one-shot flag is clear, set it and forward the linked
 * target scalar times 2.5 to camera export 0x20. Its physical unit is unproven. */
void battleSetScaledCameraScalarOnce(BattleObj_00405034 *node, float value) {
    void *cameraTarget;

    cameraTarget = ((BattleSubObj_00405034 *)node->unk0)->unkC;
    if (node->unk5A4 >= 0.0f) {
        node->unk5A4 = value;
        if (node->unk5A8 == 0) {
            node->unk5A8 = 1;
            ((CamExports_00405034 *)gCamExports)->unk20(cameraTarget, 0xA, 0, 9, (double)(((CamTarget_00405034 *)cameraTarget)->unk1C * 2.5f), 0);
        }
    }
}
#line 264 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004050D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405764.s")

#line 271 "src/modules/battle.c"
/* Clear the linked motion-state flag, copy node position and two
 * scalars, and record shared time. Read the object matrix, pass its translation
 * row to motion export 0x3C with mode zero, then update the battle node. The
 * motion callee uses three arguments; the fourth register is not an input. */
void battleCopyNodeStateAndUpdateMotion(BattleResetNode *node, s32 mode) {
    BattleMotionSource *source;
    Mtx4F matrix;
    node->link->source->flagF4 = 0;
    source = node->link->source;
    source->position = node->position;
    source->scalarC = node->scalarB0;
    source->scalar10 = node->scalarB4;
    source->time = D_80025D6C;
    ((BattleReadMatrixExports *)gUvDobjExports)->getMatrix(node->link->handle, 0, &matrix);
    D_battle_0040A050->apply(node->link->source, (Vec3F *)&matrix.m[3][0], 0);
    func_battle_00405ADC((Node_400D38 *)node, mode);
}
#line 272 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405ADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405C3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405E68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406344.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040652C.s")

/* Reset node fields and copy the shared scalar, then increment its count
   and clear the object flag bits in the original order. */
/* D_battle_0040A080 already declared as Node_400D38[] by an earlier function in this TU.
   Do not redeclare it here. */
typedef struct {
    /* 0x0000 */ char  pad0[0x1A30];
    /* 0x1A30 */ int   unk1A30;
    /* 0x1A34 */ float unk1A34;
} BattleState_00406784;
typedef struct {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ void (*unk38)(void *, int, void *);
} DobjExp3_00406784;
typedef struct {
    /* 0x00 */ char  pad0[0x4];
    /* 0x04 */ int   unk4;
    /* 0x08 */ int   unk8;
    /* 0x0C */ float unkC;
    /* 0x10 */ void *unk10;
} Node_00406784;

#line 308 "src/modules/battle.c"
/* Clear node fields 0x8 and 0x4, copy the shared scalar at 0x1A34,
 * and increment its associated count at 0x1A30. Clear object flag bits
 * two and one in order. The legacy third call argument remains preserved. */
void battleResetNodeAndIncrementFirstCount(Node_00406784 *node) {
    node->unk8 = 0;
    node->unkC = ((BattleState_00406784 *)((char *)D_battle_0040A080))->unk1A34;
    node->unk4 = 0;
    ((BattleState_00406784 *)((char *)D_battle_0040A080))->unk1A30 = ((BattleState_00406784 *)((char *)D_battle_0040A080))->unk1A30 + 1;
    ((DobjExp3_00406784 *)gUvDobjExports)->unk38(node->unk10, 2, node);
    ((DobjExp3_00406784 *)gUvDobjExports)->unk38(node->unk10, 1, node);
}
#line 318 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406804.s")

#line 315 "src/modules/battle.c"
/* Set the primitive RGB color from the indexed palette, with alpha 1.0.
 * The original routine trusts its selector and palette index. */
void battleSetPalettePrimitiveColor(BattlePaletteSelector *selector) {
    Vec3F *color = &D_battle_00409C80[selector->paletteIndex];
    ((UvGfxMgr_Exports *)gUvGfxMgrExports)->uvGfxSetPrimColorF(color->x, color->y, color->z, 1.0f);
}
#line 316 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406954.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406AD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406C84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406E98.s")

#line 325 "src/modules/battle.c"
/* Build an identity matrix with the indexed battle-table translation,
 * assign it to object matrix slot zero, select mode two and clear flag bit one.
 * The original caller owns the translation index and object handle bounds. */
void battleApplyIndexedObjectTranslation(BattleTranslatedObject *object) {
    Mtx4F matrix;
    gUvFmtxExports->uvMat4SetIdentity(&matrix);
    matrix.m[3][0] = D_battle_0040C460[object->index].x;
    matrix.m[3][1] = D_battle_0040C460[object->index].y;
    matrix.m[3][2] = D_battle_0040C460[object->index].z;
    ((BattleTransformExports *)gUvDobjExports)->setMatrix(object->handle, 0, &matrix);
    ((BattleTransformExports *)gUvDobjExports)->setMode(object->handle, 2);
    gUvDobjExports->unk38(object->handle, 1);
}
#line 326 "src/modules/battle.c"

/* Reset node fields, increment the shared count and clear object flag bits. */
typedef struct {
    /* 0x0000 */ char pad0[0x1D6C];
    /* 0x1D6C */ int  unk1D6C;
    /* 0x1D70 */ float unk1D70;
} BattleData_40733C;
typedef struct {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ void (*unk38)(void *, int, void *);
} UvDobjExp_40733C;
typedef struct {
    /* 0x00 */ char  pad0[0x4];
    /* 0x04 */ int   unk4;
    /* 0x08 */ int   unk8;
    /* 0x0C */ float unkC;
    /* 0x10 */ char  pad10[4];
    /* 0x14 */ void *unk14;
} BattleNode_40733C;

#line 346 "src/modules/battle.c"
/* Clear node fields 0x8 and 0x4, copy the shared scalar at 0x1D70,
 * and increment its associated count at 0x1D6C. Clear object flag bits
 * two and one in order. The legacy third call argument remains preserved. */
void battleResetNodeAndIncrementSecondCount(BattleNode_40733C *node) {
    node->unk8 = 0;
    node->unkC = ((BattleData_40733C *)(&D_battle_0040A080))->unk1D70;
    node->unk4 = 0;
    ((BattleData_40733C *)(&D_battle_0040A080))->unk1D6C = ((BattleData_40733C *)(&D_battle_0040A080))->unk1D6C + 1;
    ((UvDobjExp_40733C *)gUvDobjExports)->unk38(node->unk14, 2, node);
    ((UvDobjExp_40733C *)gUvDobjExports)->unk38(node->unk14, 1, node);
}
#line 355 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004073BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004078EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407A68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407C58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407DC4.s")

/* Clear object effects, release the particle handle and initialize sound handles. */
#line 369 "src/modules/battle.c"
/* Clear the node activity word and object flag bits two and one.
 * Release a nonnegative particle-effect handle and replace it with -1,
 * then initialize both embedded sound handles. Initialization does not stop playback. */
void battleClearObjectEffectsAndInitializeSounds(BattleObj_407E78 *node) {
    int particleHandle;

    node->unk4 = 0;
    ((UvDobjExp_407E78 *)gUvDobjExports)->unk38(node->unk14, 2);
    ((UvDobjExp_407E78 *)gUvDobjExports)->unk38(node->unk14, 1);
    particleHandle = node->unk28;
    if (particleHandle >= 0) {
        gUvPfxExports->unk2C(particleHandle);
        node->unk28 = -1;
    }
    gSndExports->unkCC(node->unk2C);
    gSndExports->unkCC(node->unk34);
}
#line 383 "src/modules/battle.c"

/* Enable the indexed object model, invalidate its particle handle and initialize sound handles. */
#line 385 "src/modules/battle.c"
/* Set the node activity word, assign its indexed object model and
 * invalidate its particle handle. Set object flag bits two and one,
 * then initialize both embedded sound handles; this does not start sound loops. */
void battleEnableIndexedModelAndInitializeSounds(Node_00407F30 *node) {
    node->unk4 = 1;
    ((UvDobjExp_00407F30 *)gUvDobjExports)->unk14(node->unk14, D_battle_00409EF8[node->unk0]);
    node->unk28 = -1;
    ((UvDobjExp_00407F30 *)gUvDobjExports)->unk30(node->unk14, 2);
    ((UvDobjExp_00407F30 *)gUvDobjExports)->unk30(node->unk14, 1);
    ((SndExp_00407F30 *)gSndExports)->unkCC((void *)((char *)node + 0x2C));
    ((SndExp_00407F30 *)gSndExports)->unkCC((void *)((char *)node + 0x34));
}
#line 394 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407FF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040807C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004081D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004085F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408B70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408DC8.s")

/* Set the primitive color from an indexed record, preserving raw-word arguments. */
#line 412 "src/modules/battle.c"
/* Read the indexed twelve-byte color record and call the primitive
 * color export. Preserve the legacy declaration: the last record channel
 * and alpha 0.5 are passed as raw words. The caller owns the index bounds. */
void battleSetIndexedPrimitiveColor(int *colorIndex) {
    BattleViewEntry_004090F0 *color;

    color = &D_battle_00409D28[*colorIndex];
    gUvGfxMgrExports->unk3C(color->unk0, color->unk4, color->unk8, 0x3F000000);
}
#line 418 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409314.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040969C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409838.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409910.s")

