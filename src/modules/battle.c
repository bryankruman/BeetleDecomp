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
    /* 0x14 */ void *objectHandle; /* RE_UNKNOWN: native DOBJ consumes this word as a signed pool index; historical pointer spelling and upstream producer/caller contract need original evidence. */
    /* 0x18 */ char pad18[0x10];
    /* 0x28 */ int unk28;
} Node_00407F30;
typedef struct { char pad0[0x14]; void (*unk14)(void *, void *); char pad18[0x18]; void (*setFlagBits)(void *, int); } UvDobjExp_00407F30;
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
extern void uvProfilerBegin(int);
extern void uvProfilerEnd(int);
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

/* Three words are copied without numerical conversion in the original;
 * their physical interpretation remains unproved. */
typedef struct { u32 words[3]; } BattleInitWordTriple;
typedef struct {
    u8 prefix[0x618];
    BattleInitWordTriple copiedWords;
    u8 unknown624[0x4C];
    f32 scalar670;
    u8 unknown674[0x50];
    f32 scalar6C4;
} BattleInitSource;
typedef struct {
    BattleInitSource *source;
    u8 unknown4[0x14];
    s32 objectHandle;
} BattleInitLink;
/* Observed offsets only; the final store establishes a required access
 * through 0x5B7, not a complete historical allocation or lifetime contract. */
typedef struct {
    BattleInitLink *link;
    s32 word4, word8, wordC;
    f32 scalar10, scalar14;
    s32 words18[30];
    s32 word90, word94, word98, word9C, wordA0;
    f32 scalarA4, scalarA8, scalarAC, scalarB0, scalarB4;
    BattleInitWordTriple copiedWordsB8;
    u8 firstSoundHandle[8];
    u8 unknownCC[0x4BC];
    u8 secondSoundHandle[8];
    u8 unknown590[4];
    f32 scalar594, scalar598;
    s32 modelId;
    f32 scalar5A0, scalar5A4;
    s32 word5A8;
    f32 scalar5AC;
    s32 word5B0, word5B4;
} BattleInitializedNode;
typedef struct { u8 prefix[0x18]; u16 (*getModelId)(s32); } BattleGetModelExports;
#include "uvfvec_rom.h"

/* Focused views of observed node/shared offsets and consumed export inputs;
 * these do not establish complete historical allocations or ownership. */
typedef struct {
    s32 word0, word4, word8;
    f32 scalarC;
    s32 objectHandle;
    u8 soundHandle[8];
} BattleResetSoundNode;

#include "uvmath_rom.h"
extern UvMath_Exports *gUvMathExports;
/* Consumed slots only; no complete historical module ABI is asserted. */
typedef struct {
    u8 opaque00[8];
    s16 (*setupHandle)(void *, s16, s32, f32, f32);
    u8 opaque0C[0x40];
    f32 (*getScalar)(void);
} BattleThreeSoundExports;
void battlePlayRandomThreeSoundVariant(BattleObj_407E78 *);

/* Focused consumed fields/slots only; historical complete types, ownership,
 * callback lifetimes and caller domains remain unproved. */
typedef struct {
    u8 unknown00[0x10];
    s32 kind;
    u8 unknown14[0xC];
    u8 soundHandle[8];
} BattleKindSoundRecord;

typedef struct {
    u8 unknown00[0x70];
    void (*processHandle)(void *);
} BattleKindHandleSoundExports;

void battleProcessKindSoundVariant(BattleKindSoundRecord *);

/* Observed scalar words and handle addresses only. Complete historical
 * declarations, gate purpose and storage ownership remain unproved. */
extern s32 D_battle_00409F9C;
extern f32 D_battle_00409BF4;
extern f32 D_battle_00409BF8;
extern f32 D_battle_00409BFC;
extern f32 D_battle_00409C00;
extern u8 D_battle_0040C5F0[];
extern u8 D_battle_0040C5F8[];
extern u8 D_battle_0040C600[];
extern u8 D_battle_0040C608[];
void battlePlayGatedIndexedSound(s32);
#line 177 "src/modules/battle.c"
typedef struct {
    u8 prefix[0x1A34];
    f32 scalar;
    s32 count;
    u8 unknown1A3C[8];
    s32 savedNodeWord;
} BattleResetSoundSharedState;
typedef struct {
    u8 prefix[4];
    void (*playSpatialSound)(void *, s16, s32, f32, f32, f32, Mtx4F *);
    u8 unknown8[0x40];
    f32 (*getVolumeScale)(void);
} BattleResetSoundExports;
#include "uvvattr_rom.h"
/* The request capacity and observed offsets separate two 150-word regions;
 * this focused view does not prove the complete historical allocation. */
typedef struct {
    u8 prefix[0xD0];
    s32 vertexCount;
    s32 vertexHandles[150];
    f32 scaledThirdCoordinates[150];
    u8 unknown584[4];
    u8 soundHandle[8];
} BattleVertexQueryState;
void battleCollectModelVertexHandlesAndScaledZ(BattleVertexQueryState *);
extern UvVAttr_Exports *D_battle_0040A054;
extern f32 D_battle_00409C10[];
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

/* Restore three saved settings words and the UPFX shared word, clear
 * settings bytes 98..9B, then visit two eight-byte sound-handle arrays four
 * times. Each SND70 call reloads its export pointer; the actual provider
 * validates identity before stop/refresh/reset, not storage deallocation.
 * RE_UNKNOWN: saved/shared-word and settings-byte purposes, complete array
 * allocations, caller domains, aliases and callback/module replacement
 * lifetimes need original writers, entry callers and provider evidence.
 * Readable C remains parked after two trials: native 228 versus draft 228
 * bytes with 22 differing words, then draft 220 with 54 differing positions.
 * The sole refinement retained the native whole-settings cursor +98 and
 * pre-call end snapshot. Its frame 48 and loop effects agree, but the draft
 * shares settings-base materialization across saved stores and the cursor,
 * unlike the native separate base pair. Prologue/register/load scheduling
 * and instruction sites differ; the eight-byte shrink is real, not padding.
 * Both 22-native/20-draft relocation lists differ; first the second-handle
 * base pair was shared, then the settings-base pair was shared. All unique
 * target roles remain represented. Full review supports no omitted effect,
 * width or ABI correction. Historical declarations/alias organization and
 * lowering remain unproved; require exact instructions and packed/ROM proof. */
#line 229 "src/modules/battle.c"
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
 * RE_UNKNOWN: table capacities and count/index domains need original writers/callers. */
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
    uvProfilerBegin(D_battle_0040A068);
    func_battle_00401BB8();
    uvProfilerEnd(D_battle_0040A068);
    if ((D_debugEnable != 0) && (gDebugFrateDisp == 2)) {
        battleSubmitFiveDebugRecords();
    }
}
#line 189 "src/modules/battle.c"

/* Original Battle1BB8 calls two distinct screen-width/height getter pairs,
 * appends the viewport, builds/pushes an orthographic matrix, then pushes,
 * sets and clears graphics-state bits before dispatching one mode snapshot.
 * Mode 0 gates two helpers on settings +0x86/+0x709C, then calls four more;
 * modes 1/2 share a helper, mode 3 calls the loaded PAUSE slot 0x0C.
 * The final graphics-state pop and all intervening export reloads remain.
 * RE_UNKNOWN: mode/settings meanings and writers, module availability and
 * callback replacement lifetimes need original producers and entry callers.
 * Historical declarations/local storage need original source or exact proof.
 * Trial2792: 504/504 bytes; six words differ solely in frame 104/112 bytes,
 * width home SP+0x20/SP+0x6C and stack restoration. The complete 35-record
 * reference-object and draft relocation lists are identical. No missing
 * callback, scalar conversion or control effect was identified. Retain ASM;
 * no trial headers, types, prototypes or C body accepted. */
#line 190 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00401BB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00401DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00402750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040282C.s")

/* func_battle_00402CD0 decrements each positive node counter at 0x5B4
 * and draws four vertices from channel tag 5's four unsigned-halfword outputs.
 * Preserve the initial texture bind, matrix setup, vertex order and count reload.
 * RE_UNKNOWN: visual purpose, coordinate/counter units, vertex-byte meanings,
 * node capacity and nested-link/channel lifetime need original producers/callers.
 * Clean C differs only in frame size (208/200); retain assembly pending proof. */
#line 198 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00402CD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00402F6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040372C.s")

/* Original Battle3A54 sets graphics state and a projection, then walks nodes
 * at stride 0x5B8. A signed count/limit or ordered-positive +0x598 gate selects
 * six texture/rectangle slots. Each slot scans all fixed +0x18 entry pointers
 * with a signed byte counter and a 32-bit count shift, retaining every match.
 * CHAN tag 5 supplies four word outputs; later count reads choose coordinates.
 * Reload the outer count after an active block; skipped nodes keep its snapshot.
 * RE_ORIGINAL_QUIRK: CHAN rejection leaves caller output words untouched;
 * the original caller initializes none and adds no rejection check.
 * RE_UNKNOWN: node/link/entry/texture extents, ID/count/shift domains, output
 * meanings, aliases and callback lifetimes need original producers/callers.
 * Historical declarations and read/storage organization remain unproved.
 * Trial2792: 692/684 bytes, 146 differing words; frame 256/240 bytes and
 * matrix/output homes differ. Draft merges the positive-test/bound count reads
 * and uses distinct count/limit aliases instead of shared-base fixed offsets.
 * The complete 20-record reference-object and 22-record draft lists differ.
 * All observed callbacks, gates and outer-count reload paths are represented;
 * no supported semantic correction identified. Retain ASM and trial-only types. */
#line 204 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00403A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00403D08.s")

#line 208 "src/modules/battle.c"
/* Select one of four sound handles only while DATA+0x31C is nonzero.
 * Each supported selector calls SND slot 0x4C, scales its result through its
 * own original coefficient word, calls slot 0x08, then clears the gate.
 * RE_UNKNOWN: selector producers, gate rearming/lifecycle, complete handle
 * storage types and callback replacement/ownership need original callers
 * and writers. Unsupported selectors leave the gate untouched. */
void battlePlayGatedIndexedSound(s32 selector)
{
    f32 scalar;

    switch (selector) {
    case 0:
        if (D_battle_00409F9C != 0) {
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(D_battle_0040C5F0, 162, 0x7F37,
                scalar * D_battle_00409BF4, 0.5f);
            D_battle_00409F9C = 0;
        }
        break;
    case 1:
        if (D_battle_00409F9C != 0) {
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(D_battle_0040C5F8, 163, 0x7F37,
                scalar * D_battle_00409BF8, 0.5f);
            D_battle_00409F9C = 0;
        }
        break;
    case 2:
        if (D_battle_00409F9C != 0) {
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(D_battle_0040C600, 164, 0x7F37,
                scalar * D_battle_00409BFC, 0.5f);
            D_battle_00409F9C = 0;
        }
        break;
    case 3:
        if (D_battle_00409F9C != 0) {
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(D_battle_0040C608, 165, 0x7F37,
                scalar * D_battle_00409C00, 0.5f);
            D_battle_00409F9C = 0;
        }
        break;
    }
}
#line 209 "src/modules/battle.c"

/* Original 425C draws a MATH slot 0x34 fraction before testing DATA+0x320.
 * When enabled it signed-truncates fraction * 4, submits one of four managed
 * handles through SND slot 0x4C then slot 0x08, and clears the gate afterward.
 * RE_ORIGINAL_QUIRK: disabled calls still draw; an enabled unsupported
 * selection still clears the gate. Preserve both paths and callback reloads.
 * RE_UNKNOWN: gate producers/rearming, callback replacement/return domains,
 * complete handle storage/ownership and historical declarations need original
 * callers and writers. Eight equal-bit coefficient words stay distinct symbols.
 * Retain ASM: draft 476 -> 476 bytes; 118 of 119 instruction words are exact.
 * At 0x43F4 native MUL.S takes scalar F0 then coefficient F4; the draft
 * reverses those sources. No floating exception/NaN equivalence is claimed.
 * The 38-record reference-object and draft relocation multisets agree;
 * enumeration differs. The draft's 20 module-local sites/kinds already follow
 * the original packed order. Existing C10[] spelling does not prove its
 * historical type. No operation/reload/ABI gap was identified; no trial C,
 * types or prototype is accepted. */
#line 210 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040425C.s")

#line 212 "src/modules/battle.c"
/* RE_ORIGINAL_QUIRK: initialize the sound handle at node +0x588 here;
 * the vertex collector initializes that same handle again after its vertex
 * callbacks. Preserve both calls and intervening reloads; the effects of
 * repeated initialization across those callbacks remain unproved. */
/* Initialize observed node fields, snapshot linked source values,
 * initialize two sound handles and clear the thirty-word region at 0x18.
 * Collect model vertex handles/scaled coordinates, then reload the node link
 * and record its current object model ID after the callbacks.
 * RE_UNKNOWN: node/source field meanings and units, allocation extents,
 * aliases, valid object-handle domains and callback/asset lifetimes need
 * original callers/producers. The model getter indexes an unchecked pool;
 * this routine adds no validation. The three copied words remain neutral. */
void battleInitializeNodeAndCollectVertexHandles(BattleInitializedNode *node)
{
    BattleInitLink *link;
    s32 index;

    link = node->link;
    node->word8 = 0;
    node->wordC = 0;
    node->wordA0 = 0;
    node->scalar10 = 0.0f;
    node->scalar14 = 0.0f;
    node->scalarAC = 0.0f;
    node->scalarA4 = 1.0f;
    node->scalarA8 = 0.75f;
    node->scalarB0 = link->source->scalar670;
    node->scalarB4 = link->source->scalar6C4;
    node->copiedWordsB8 = link->source->copiedWords;
    node->word90 = 0;
    node->word94 = 0;
    node->word98 = 0;
    node->word9C = 0;
    node->word5B4 = 0;
    node->word5B0 = 0;
    node->word5A8 = 0;
    node->scalar594 = 0.0f;
    node->scalar598 = 0.0f;
    node->scalar5A0 = 0.0f;
    node->scalar5A4 = 0.0f;
    node->scalar5AC = 0.0f;
    gSndExports->unkCC(node->firstSoundHandle);
    gSndExports->unkCC(node->secondSoundHandle);
    for (index = 0; index < 30; index += 1) {
        node->words18[index] = 0;
    }
    battleCollectModelVertexHandlesAndScaledZ((BattleVertexQueryState *)node);
    node->modelId = ((BattleGetModelExports *)gUvDobjExports)->getModelId(node->link->objectHandle);
}
#line 213 "src/modules/battle.c"

#line 214 "src/modules/battle.c"

/* Collect model 46 vertex handles through the original VATR query, then
 * store each selected vertex's signed third coordinate divided by 100.
 * Reload the shared query count and export pointer after each getter call.
 * RE_ORIGINAL_QUIRK: the promoted double argument is consumed as words by
 * VATR: its high word is the signed comparison reference; its zero low word
 * terminates the tuples. Keep the double argument and the trailing zero.
 * Query saturation overwrites its final allowed slot with later matches.
 * RE_UNKNOWN: historical varargs typing, state allocation/caller domains,
 * vertex/scalar units and asset/provider lifetimes need original callers
 * and source evidence; the view describes observed offsets only. */
void battleCollectModelVertexHandlesAndScaledZ(BattleVertexQueryState *state)
{
    s16 coordinate;
    s32 index;

    state->vertexCount = D_battle_0040A054->func_uvvattr_rom_00400514(
        150, state->vertexHandles, 8, 46, 4, 4,
        (f64)D_battle_00409C10[1], 0);
    index = 0;
    if (state->vertexCount > 0) {
        do {
            D_battle_0040A054->uvVattrGetPackedVertexAttributes(
                state->vertexHandles[index], 4, &coordinate, 0);
            state->scaledThirdCoordinates[index] = (f32)coordinate / 100.0f;
            index += 1;
        } while (index < state->vertexCount);
    }
    gSndExports->unkCC(state->soundHandle);
}
#line 215 "src/modules/battle.c"

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

/* Original gated scalar pass caps positive changes at one; other paths
 * clamp the negation and use DIV.S by 2 / MUL.S by 2 in configured modes.
 * RUMBLE 0x04 receives linked word 0x14, .5, .4, 0; retain callback reloads,
 * the first promoted-double gate, and negated action only after reset.
 * RE_UNKNOWN: scalar/gate/counter meanings, units, linked index/lifetime,
 * reset mode and historical source precision/dataflow need original producers
 * and source evidence. Clean C remains unmatched; retain original assembly. */
#line 269 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405764.s")

#line 271 "src/modules/battle.c"
/* Clear the linked motion-state flag, copy node position and two
 * scalars, and record shared time. Read the object matrix, pass its translation
 * row to motion export 0x3C with mode zero, then update the battle node. The
 * motion callee uses three arguments; the fourth register is not an input. RE_UNKNOWN: caller parameter mode carries an optional-pointer word at 5ADC; historical type, domain and pointed storage need original producers. */
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

/* Original Battle5ADC returns for an ordered-positive scalar at 0xA8;
 * otherwise it resets fields AC/5B4/A4/A8, sends linked word 0x14 and
 * scalars 1/.7/0 to RUMBLE04, sets CAR property 9 to 12, then invokes
 * SND70 on the embedded handle. Preserve fresh link and export reads.
 * It increments word 8; a nonzero second word is dereferenced at +0xC,
 * incremented and forwarded to 5D34 before linked-node removal.
 * RE_ORIGINAL_QUIRK: count != 0 selects one removal, including for a
 * negative count. The captured slot is cleared after the first-count helper;
 * the current count is reloaded before subtraction. A nonnull pointer at
 * 0x90 then selects the second-count helper after clearing word 0x94.
 * RE_UNKNOWN: the existing int declaration and caller parameter named mode
 * carry an optional-pointer word, not a proved integer mode. Historical
 * formal types, pointer/list/count domains, linked pattern-index bounds,
 * scalar units, aliases and callback replacement lifetimes require original
 * callers and producers. No cooldown unit, capacity or ownership is proved.
 * Readable trial2515 produced 348 versus 352 bytes and 31 differing words;
 * frame40 remains, but boolean-join and slot-address lowering differ. The
 * two nine-record relocation lists differ at later sites and downstream
 * symbol values. No missing callback/width/reload was identified in full
 * comparison2516; historical source/compiler organization remains unknown.
 * Retain original assembly. Neutral sound-view bridge2510 is unaccepted. */
#line 273 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405ADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405C3C.s")

/* Original Battle5D34 scans thirty 28-byte slots, probing the first flag
 * through D_battle_0040B764 and later slots through D_battle_0040A080.
 * It calls 652C then the accepted sound/flag reset before reloading the
 * identifier limit. Owner+0xA0 is captured once before the identifier loop;
 * the inner scan walks owner-relative pointer words at +0x18 using an
 * unsigned cursor/end comparison. Append reloads the count, stores the
 * selected node pointer, then reloads and increments the count again.
 * RE_ORIGINAL_QUIRK: exhausting the identifier scan does not undo either
 * preceding helper's effects; 652C also resamples without a proved retry
 * bound. These observations do not establish reachable failure or safety.
 * RE_UNKNOWN: caller/list capacity, count/identifier domains, pointer
 * arithmetic overflow, aliases and node/helper lifetimes require actual
 * original producers and callers. Native 308-byte assembly is retained.
 * Readable trials produced 408 bytes/94 differing words (10/6 relocation
 * records), then 296 bytes/61 differing words (10/10 records). The native
 * alias and unsigned cursor refinement still changes frame 48 to 64,
 * node/owner homes, registers, signed-bound lowering and relocation sites.
 * Historical types/declarations and exact compiler organization remain
 * unproved; neither draft, focused type/prototype nor extra storage is
 * accepted. Full evidence: comparisons 2466 and 2479. */
#line 277 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00405E68.s")

/* Original Battle6170 initializes thirty 28-byte records but sets the
 * active count to 24. Each record reloads the modulo divisor, creates an
 * object, assigns its indexed model, retains the palette callback/context
 * via DOBJ property 4, invokes the first-count reset helper, stores .5, then calls
 * SNDCC on its embedded eight-byte handle. Preserve that order and reloads.
 * RE_ORIGINAL_QUIRK: DOBJ3C can return 0xFFFF; this caller immediately
 * forwards the returned word to model assignment without a failure gate.
 * SNDCC writes sentinels for nonnull inputs; its null path stores at zero.
 * These native behaviors do not establish reachable failure for this caller.
 * RE_UNKNOWN: available object slots, settings/model/palette index domains,
 * divisor validity, input extent/aliases, retained callback invocation and
 * context lifetime, module replacement and scalar units require original
 * producers/callers. Thirty initialized slots do not prove full allocation.
 * The first compiled natural draft2553 produced 452 versus 468 bytes and
 * 116 differing instruction positions. Frame 80 becomes 72; the native
 * independent sound-address induction and S8 retention are not reproduced,
 * and the draft duplicates settings-base materialization. All observed
 * callback inputs, scalar/store order and per-record reads remain represented.
 * The two relocation lists contain 17/19 records and differ; downstream
 * symbol values also move with the shorter body. Full comparison2554 found
 * no supported missing native effect or ABI correction. Warning835 records
 * the unprototyped direct reset call; its later anonymous canonical type and
 * historical shared declaration remain unresolved. Keep the original ASM;
 * no draft types, prototypes, headers or guessed storage are accepted. */
#line 281 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406170.s")

/* Original Battle6344 clamps the shared signed limit, then walks 28-byte
 * records through a state-relative cursor and unsigned end comparison.
 * State0's inner gate selects decrement or the direct helper and reloads
 * count afterward; a false gate retains the incoming count. State1 reloads
 * count after either decrement or index-wrap/scalar-reset/model assignment.
 * State2/other values retain count. Ordered-positive tests send NaNs to the
 * alternate paths; preserve the callback, scalar and count-read ordering.
 * RE_UNKNOWN: caller count/index/handle domains, cursor/end arithmetic and
 * overflow bounds, settings/table extents, aliases, physical units and
 * callback/module replacement lifetimes need original producers/readers.
 * DOBJ model assignment indexes before its upper-bound check; no universal
 * valid-handle/output or reachable caller failure is proved by these bytes.
 * The first compiled natural draft2553 produced 496 versus 488 bytes and
 * 116 differing instruction positions. Frame 64 remains, but initial shared
 * base retention and repeated absolute HI/LO materialization differ from the
 * native cached base. The full 17/27-record lists differ in sites, multiplicity
 * and downstream direct-helper value; this is not a missing-call-target claim.
 * Full comparison2554 found no supported omitted store, count reload, ordered
 * test or callback input. Historical source declarations/alias organization
 * and compiler lowering remain unproved. Keep the original ASM; no draft
 * types, prototypes, headers, padding or declaration variants are accepted. */
#line 283 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406344.s")

/* Original 652C draws/clamps an index from MATH slot 0x34's LCG fraction and retries
 * while excluded or used by an active 28-byte record. Each scan captures
 * its count once and compares unshifted state cursors with fixed field
 * loads at +16E4/+16E8, without an early match exit. It updates two counts,
 * retains the selected index across callbacks, draws/clamps a model index,
 * sets the model, then submits the selected vector as matrix translation
 * before setting flag bits 2 and clearing bits 1 through fresh handle reads.
 * RE_ORIGINAL_QUIRK: retry has no exhaustion bound or alternate exit here.
 * RE_UNKNOWN: count/index/handle and address-wrap domains, table/record
 * capacities, countdown/count purposes and units, aliases and callback
 * lifetimes need original producers/callers; no reachable exhaustion claim.
 * DATA+230 numeric model words have no loader relocations at observed sites;
 * those bytes and the vector-table alias do not prove complete capacities.
 * Retain ASM: first draft 600->672 bytes / 168 differences; the sole unshifted scan
 * correction 600->656 bytes / 164 differences. Final frame 144->168 bytes, snapshot 0x88->0x54
 * and matrix 0x40->0x5C stack homes, shared-base rematerialization, MULTU by 28 versus
 * native shifts/subtraction, and commuted MUL.S operands remain different.
 * The 14-reference-object/32-draft object relocation lists differ in sites/multiplicity; all
 * six unique symbol identities remain. No further omitted call/input/reload
 * was found; historical declarations, lowering and exact FP effects remain
 * unproved. No C body, focused type or prototype from either trial accepted. */
#line 285 "src/modules/battle.c"
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
    /* 0x38 */ void (*clearFlagBits)(void *, int, void *);
} DobjExp3_00406784;
typedef struct {
    /* 0x00 */ char  pad0[0x4];
    /* 0x04 */ int   unk4;
    /* 0x08 */ int   unk8;
    /* 0x0C */ float unkC;
    /* 0x10 */ void *objectHandle;
} Node_00406784;

#line 308 "src/modules/battle.c"
/* Clear node fields 0x8 and 0x4, copy the shared scalar at 0x1A34,
 * and increment its associated count at 0x1A30. Clear object flag bits
 * masks 2 then 1; retain the legacy extra argument. RE_UNKNOWN: object-handle bounds/lifetime need original callers. */
#line 311 "src/modules/battle.c"

void battleResetNodeAndIncrementFirstCount(Node_00406784 *node) {
    node->unk8 = 0;
    node->unkC = ((BattleState_00406784 *)((char *)D_battle_0040A080))->unk1A34;
    node->unk4 = 0;
    ((BattleState_00406784 *)((char *)D_battle_0040A080))->unk1A30 = ((BattleState_00406784 *)((char *)D_battle_0040A080))->unk1A30 + 1;
    ((DobjExp3_00406784 *)gUvDobjExports)->clearFlagBits(node->objectHandle, 2, node);
    ((DobjExp3_00406784 *)gUvDobjExports)->clearFlagBits(node->objectHandle, 1, node);
}
#line 319 "src/modules/battle.c"
#line 318 "src/modules/battle.c"

#line 319 "src/modules/battle.c"

/* Save and clear node word 0x8, set word 0x4 to two, copy the shared
 * scalar and decrement the shared count. Read object matrix slot zero,
 * request sound 0x84 using the returned volume scale and that matrix,
 * then clear object flag bits two and one with fresh callback/handle reads.
 * RE_UNKNOWN: node/shared field purpose and units, handle and count domains,
 * shared aliases, asset lifetimes and matrix availability require original
 * callers/producers. DOBJ 0x28 can return without writing the matrix on
 * invalid/unloaded inputs; preserve the original uninitialized local rather
 * than inventing a default. No reachable failure is established here. */
void battleResetNodePlaySoundAndClearObjectFlags(BattleResetSoundNode *node)
{
    Mtx4F matrix;
    f32 volumeScale;

    ((BattleResetSoundSharedState *)D_battle_0040A080)->savedNodeWord = node->word8;
    node->word8 = 0;
    node->scalarC = ((BattleResetSoundSharedState *)D_battle_0040A080)->scalar;
    node->word4 = 2;
    ((BattleResetSoundSharedState *)D_battle_0040A080)->count -= 1;
    ((BattleReadMatrixExports *)gUvDobjExports)->getMatrix(node->objectHandle, 0, &matrix);
    volumeScale = ((BattleResetSoundExports *)gSndExports)->getVolumeScale();
    ((BattleResetSoundExports *)gSndExports)->playSpatialSound(
        node->soundHandle, 0x84, 0x7FFA, volumeScale, 1.0f, 0.0f, &matrix);
    gUvDobjExports->unk38(node->objectHandle, 2);
    gUvDobjExports->unk38(node->objectHandle, 1);
}
#line 320 "src/modules/battle.c"

#line 315 "src/modules/battle.c"
/* Set the primitive RGB color from the indexed palette, with alpha 1.0.
 * RE_UNKNOWN: selector/index bounds, retained context lifetime and actual tag4 invokers need original producers/readers. */
void battleSetPalettePrimitiveColor(BattlePaletteSelector *selector) {
    Vec3F *color = &D_battle_00409C80[selector->paletteIndex];
    ((UvGfxMgr_Exports *)gUvGfxMgrExports)->uvGfxSetPrimColorF(color->x, color->y, color->z, 1.0f);
}
#line 316 "src/modules/battle.c"

/* Original Battle6954 scans active 28-byte records using a reloaded
 * signed count, requests DOBJ property 7, then reloads the record index and
 * reads the input/table triples. It evaluates the grouped squared difference
 * through MATH04 and keeps the last index strictly below the mean of the
 * input and queried scalars; it returns -1 when no index passes.
 * RE_ORIGINAL_QUIRK: DOBJ7 only writes the float output when its signed
 * upper-bound test accepts the handle. The original query scratch has no
 * initialization here; caller evidence must establish any valid-output domain.
 * RE_UNKNOWN: count/index/handle bounds, output validity, aliases, physical
 * units, object lifetimes and historical declarations need original callers
 * and producers. Ordered NaN comparisons reject the test; no guard is added.
 * Trial2515 retained 380 bytes but changed 70 instruction words. Native
 * DIV.S by 2 became MUL.S by .5 despite the draft's /2.0f expression; exact
 * floating effects and historical precision/source organization are unproved.
 * Record-index scaling changed from shifts/subtraction to MULTU by 12;
 * stack scratch/result homes, base retention and scheduling also differ.
 * The two ten-record relocation lists differ in sites/enumeration. Full
 * comparison2516 found no omitted provider call, state reload or ABI input.
 * Retain original assembly; no clean draft or focused declarations accepted. */
#line 317 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406954.s")

/* Original Battle6AD0 initializes twenty forty-byte records while the
 * active count starts at 16. The settings word 7088 is captured once;
 * 6 with word 708C equal to 3, or captured value 8, selects limit zero.
 * Each record uses signed remainder by 7, creates/assigns its model,
 * invokes the second-count reset helper, initializes both embedded sound
 * handles through fresh SND exports, then stores .5 after both callbacks.
 * RE_ORIGINAL_QUIRK: DOBJ creation can return 0xFFFF, yet this caller
 * forwards the word to model assignment without a failure gate. SNDCC's
 * null path stores at zero; reachable caller failure is not established.
 * RE_UNKNOWN: original allocation/handle/count/index domains,
 * table extents, aliases, scalar units and callback/module lifetimes need
 * original producers/readers. Twenty iterations do not prove allocation.
 * First natural trial2569 produced 432 versus 436 bytes, with 54 differing
 * instruction positions. Both frames are 72; the native auxiliary record
 * pointer and backedge-delay scalar store become a direct earlier store,
 * still after both callbacks. Settings-base materialization duplicates,
 * saved registers and bound retention differ, and the full 9/11-record
 * relocation lists differ in sites/multiplicity/downstream helper value.
 * Full comparison2570 found no supported omitted effect or ABI correction.
 * Warning835 records the canonical reset helper's nonprototype call;
 * its historical shared declaration and later anonymous type remain
 * unresolved. Keep original ASM; no draft type/header/prototype accepted. */
#line 319 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406AD0.s")

/* Original Battle6C84 subtracts 2 from the shared range word before
 * comparing/clamping its signed limit. Walk forty-byte records with a
 * state-relative cursor and unsigned modulo-word end calculation.
 * State0 reloads count only after its true inner gate; state1 reloads after
 * either decrement or expiry path. Other paths retain the previous count.
 * Expiry resets the scalar before the model-index 3/settings-word 708C
 * gate, toggles the alternate index between zero and 2, reloads that field
 * for model lookup, assigns the model and calls the translation helper.
 * Ordered-positive scalar tests send NaNs to the alternate paths.
 * RE_UNKNOWN: caller count/index/handle domains, cursor/end overflow and
 * alias bounds, model/settings table extents, scalar units and callback/
 * module lifetimes need original producers/readers. The translated-object
 * argument view establishes fields 8/14 only, not a full historical type.
 * First natural trial2569 produced 528 versus 532 bytes, with 121 differing
 * instruction positions. Frame 72 becomes 64; cached settings/shared-base
 * retention becomes repeated absolute address materialization, with saved
 * register and scheduling changes. The full 18/30-record relocation lists
 * differ; direct helper values also move with the shorter body. This does
 * not establish missing call targets. Full comparison2570 found all visible
 * callbacks, count reloads, stores and ordered tests represented, with no
 * supported semantic correction. Historical declarations/alias organization
 * and compiler lowering remain unproved. Keep original ASM; no draft type,
 * header, prototype, padding or declaration-order variant accepted. */
#line 321 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406C84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00406E98.s")

#line 325 "src/modules/battle.c"
/* Build an identity matrix with the indexed battle-table translation,
 * assign it to object matrix slot zero, select mode two and clear flag bit one.
 * RE_UNKNOWN: translation index and handle validity/lifetime need original producers/callers. */
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
    /* 0x38 */ void (*clearFlagBits)(void *, int, void *);
} UvDobjExp_40733C;
typedef struct {
    /* 0x00 */ char  pad0[0x4];
    /* 0x04 */ int   unk4;
    /* 0x08 */ int   unk8;
    /* 0x0C */ float unkC;
    /* 0x10 */ char  pad10[4];
    /* 0x14 */ void *objectHandle;
} BattleNode_40733C;

#line 346 "src/modules/battle.c"
/* Clear node fields 0x8 and 0x4, copy the shared scalar at 0x1D70,
 * and increment its associated count at 0x1D6C. Clear object flag bits
 * masks 2 then 1; retain the legacy extra argument. RE_UNKNOWN: object-handle bounds/lifetime need original callers. */
#line 349 "src/modules/battle.c"

void battleResetNodeAndIncrementSecondCount(BattleNode_40733C *node) {
    node->unk8 = 0;
    node->unkC = ((BattleData_40733C *)(&D_battle_0040A080))->unk1D70;
    node->unk4 = 0;
    ((BattleData_40733C *)(&D_battle_0040A080))->unk1D6C = ((BattleData_40733C *)(&D_battle_0040A080))->unk1D6C + 1;
    ((UvDobjExp_40733C *)gUvDobjExports)->clearFlagBits(node->objectHandle, 2, node);
    ((UvDobjExp_40733C *)gUvDobjExports)->clearFlagBits(node->objectHandle, 1, node);
}
#line 357 "src/modules/battle.c"
#line 355 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004073BC.s")

/* Original Battle7740 looks up the object's loaded UVMD and optional +20
 * pointer, captures config scalars 8/20, then measures/scales source+9D8.
 * Add config C to the third component, invoke RUMBLE04, then PIECE0C/08.
 * PIECE tag 3 consumes a promoted double, then word pairs 1/0, 5/3, 2/0
 * and terminator 0. Keep the vector snapshot and later owner/handle reads.
 * RE_UNKNOWN: complete input/model/config/source extents and types, units,
 * handle/pattern-index domains, aliases and callback/module replacement
 * lifetimes need original producers/callers; ownership and downstream
 * action purpose are unproved. Retain the original null-pointer gates.
 * Trial2591: native 428/draft 424 bytes, 93 differing positions, frame 112/104.
 * Direct S0 config capture removes a native transfer; scalar homes and
 * register/address/arithmetic scheduling differ. Both 13-record relocation
 * lists retain identities but differ at later sites. Full native/provider/
 * candidate review found no supported missing callback/width/reload fix.
 * Historical declarations/storage/lowering remain unknown. Retain ASM;
 * no draft types, headers, prototypes or source-shape variants accepted. */
#line 358 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407740.s")

/* Original Battle78EC returns the last state-1 forty-byte record satisfying
 * strict distance < (incoming scalar + queried DOBJ property 7) / 2, or -1.
 * Keep grouped single squared distance and MATH04's clamped sqrt, index
 * reload after query, and signed count reload on every loop path.
 * RE_ORIGINAL_QUIRK: output storage is not initialized; DOBJ20's signed
 * upper-bound rejection leaves it unwritten. Preserve no fallback value.
 * RE_UNKNOWN: handle/count/index guarantees, full record/table extents,
 * units, aliases and callback/module replacement lifetimes need original
 * producers/readers. No reachable unwritten-output failure is established.
 * Trial2591: both 380 bytes, 66 differing words, same frame 120; property home
 * SP108 becomes SP100, pre-added record cursors replace fixed-offset bases,
 * and MULTU by 12 replaces shift/subtract/shift indexing. Explicit draft /2.0f
 * becomes MUL.S .5 versus native DIV.S by 2; identical floating exceptions/NaN
 * effects are unproved. Both ten-record lists differ in sites/order.
 * Full review found no supported missing callback/width/count-reload fix.
 * Historical storage/declarations/arithmetic lowering remain unknown.
 * Retain ASM; no draft types, headers or source-shape variants accepted. */
#line 360 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004078EC.s")

#line 362 "src/modules/battle.c"
/* Process SND slot 0x70, initialize the handle at +0x20, then choose the
 * kind-specific sound ID through a signed truncation of MATH slot 0x34.
 * RE_ORIGINAL_QUIRK: the fraction is truncated directly, with no multiplier;
 * retain both zero/one arms rather than guessing intended random variation.
 * RE_UNKNOWN: kind/handle validity, module replacement and lifetime contracts
 * need original producers/callers. SND slot 0x4C supplies the scalar; no
 * deallocation, position or physical meaning is inferred from these calls. */
void battleProcessKindSoundVariant(BattleKindSoundRecord *record)
{
    void *soundHandle;
    s32 selection;
    f32 scalar;

    soundHandle = record->soundHandle;
    ((BattleKindHandleSoundExports *)gSndExports)->processHandle(soundHandle);
    gSndExports->unkCC(soundHandle);
    switch (record->kind) {
    case 0:
        selection = (s32)gUvMathExports->uvRandFLcg();
        switch (selection) {
        case 0:
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(soundHandle, 134, 0x7FEB, scalar, 0.5f);
            break;
        case 1:
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(soundHandle, 172, 0x7FEB, scalar, 0.5f);
            break;
        }
        break;
    case 1:
        break;
    case 2:
        selection = (s32)gUvMathExports->uvRandFLcg();
        switch (selection) {
        case 0:
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(soundHandle, 173, 0x7FEB, scalar, 0.5f);
            break;
        case 1:
            scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
            ((BattleThreeSoundExports *)gSndExports)->setupHandle(soundHandle, 174, 0x7FEB, scalar, 0.5f);
            break;
        }
        break;
    }
}
#line 363 "src/modules/battle.c"

/* Original 7C58 initializes twenty 60-byte records using an identity matrix.
 * It clears words 0/0x10/0x0C, creates an object, reloads word 0 for the numeric
 * model table, submits tag 4's callback/context and the matrix, then invokes
 * the direct effect/sound helper with fresh handle reads between callbacks.
 * RE_ORIGINAL_QUIRK: that helper initializes both embedded sound handles,
 * then this caller initializes them again; preserve intervening callbacks.
 * RE_UNKNOWN: other caller spans, object exhaustion/handle/index domains,
 * DATA+0x278 historical element type, callback aliases/ownership/lifetimes
 * require original producers/readers. The original initializer supplies
 * BSS+0x1DC4; its observed 1200-byte span fits BSS, without proving other callers.
 * Retain ASM: first draft 364->364 bytes, 13 differing words; frame 168->160
 * bytes, handle/counter S2/S4 roles and preloop zero/address scheduling differ.
 * Matrix stays at SP+0x60. The 11-reference-object/11-draft relocation lists
 * differ in low-half sites/order; callback/helper identities remain present.
 * No omitted operation/ABI/reload was found. Historical declarations and
 * allocation remain unresolved; no trial C, focused types or prototypes accepted. */
#line 364 "src/modules/battle.c"
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
 * then initialize both sound handles. RE_UNKNOWN: object-handle bounds/lifetime need original callers; sound loops are not started here. */
#line 388 "src/modules/battle.c"

void battleEnableIndexedModelAndInitializeSounds(Node_00407F30 *node) {
    node->unk4 = 1;
    ((UvDobjExp_00407F30 *)gUvDobjExports)->unk14(node->objectHandle, D_battle_00409EF8[node->unk0]);
    node->unk28 = -1;
    ((UvDobjExp_00407F30 *)gUvDobjExports)->setFlagBits(node->objectHandle, 2);
    ((UvDobjExp_00407F30 *)gUvDobjExports)->setFlagBits(node->objectHandle, 1);
    ((SndExp_00407F30 *)gSndExports)->unkCC((void *)((char *)node + 0x2C));
    ((SndExp_00407F30 *)gSndExports)->unkCC((void *)((char *)node + 0x34));
}
#line 397 "src/modules/battle.c"
#line 394 "src/modules/battle.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00407FF4.s")

/* Original setup reuses the helper-selected record, sets countdown 30 and
 * its source-peer pointer, initializes model/flags/sounds, then derives a
 * translation through two matrices and local translation (0,-2,0).
 * DOBJ24 precedes copying the submitted matrix row into the record. SND48
 * returns 1.0f here and its returned scalar is forwarded to SND08/ID128.
 * RE_ORIGINAL_QUIRK: the selector can reuse an active minimum-countdown
 * record; this call does not establish a new allocation or ownership.
 * RE_UNKNOWN: input/link/handle domains, complete storage, countdown units,
 * aliases and module/callback replacement lifetimes need original writers
 * and callers. DOBJ28 rejection may leave the original matrix unwritten.
 * Matching debt: the first 348B draft had 12 differing words, including a
 * wrong SND4C view. The corrected SND48 draft has 11 differing matrix-home
 * words (SP2C/SP6C exchanged); all 16 ordered relocation records match.
 * Retain ASM; historical local storage/declarations remain unresolved. */
#line 397 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040807C.s")

/* Original update stores/reloads the countdown and tests ordered <=0.
 * Expiry submits sound 44, the matrix translation to EXPL/75, then clears.
 * Otherwise 9144 receives 27.0f; a match drives CAM18/word3/double1,5764,
 * RUMBLE and scalarA8=0, then sound 65, optional three-ID voice, EXPL,
 * 8454 and clear. SND48 results precede distinct readonly multiplier reads
 * and playback-export reloads; the matrix-row argument is an actual alias.
 * RE_UNKNOWN: valid count/index/handle domains, complete storage, units,
 * aliases and callback/module replacement lifetimes need original producers
 * and callers. Rejected DOBJ queries do not justify default local outputs.
 * Matching debt: first 636B draft had 32 differing words including two wrong
 * SND4C views; corrected SND48 draft has 30. Matrix/action stack homes and
 * FP registers differ; native float1-to-double conversion became a direct
 * double constant. The 34-record lists differ at the CAM pair sites
 * (304/308 to 308/312), with the same target sequence. Retain ASM; historical
 * declarations/storage/FP lowering remain unproved, not a gameplay bug. */
#line 399 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004081D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_004085F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408B70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00408DC8.s")

/* Set the primitive color from an indexed record, preserving raw-word arguments. */
#line 412 "src/modules/battle.c"
/* Read the indexed twelve-byte color record and call the primitive
 * color export; last channel and alpha 0.5 keep their original raw-word ABI.
 * RE_UNKNOWN: input/index validity and table extent need original producers/callers. */
void battleSetIndexedPrimitiveColor(int *colorIndex) {
    BattleViewEntry_004090F0 *color;

    color = &D_battle_00409D28[*colorIndex];
    gUvGfxMgrExports->unk3C(color->unk0, color->unk4, color->unk8, 0x3F000000);
}
#line 418 "src/modules/battle.c"

/* Original property 7 and matrix 0 queries precede the signed live-count
 * gate. Scan peers at stride 0x5B8; only the source-peer equality arm tests
 * record countdown against the supplied threshold. Query each eligible
 * peer, preserving link/provider reloads; retain the LAST strict match of
 * matrix-translation distance < (recordScalar+peerScalar)/2.0f, else -1.
 * RE_UNKNOWN: scalar/countdown units, valid count/handle domains, complete
 * input/table storage, aliases and callback replacement lifetimes need
 * original producers/callers. DOBJ rejection can leave outputs unwritten;
 * no default scalar or matrix is supplied by the original caller.
 * Matching debt: natural C 460B vs native 464B, 83 differing words. Frame 248
 * is unchanged, but matrix/scalar homes differ and duplicate A080 address
 * formation was commoned (8 original vs 6 draft relocation records).
 * Native DIV.S by 2 became MUL.S by 0.5; FP exception/NaN equivalence is not
 * established. Historical declarations/storage/lowering remain unknown;
 * retain ASM, with no accepted C, padding trim or runtime change. */
#line 419 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409144.s")

/* Query with the original scene signed-byte filter, then inspect kind 2's
 * low-24-bit identifier: self match returns 0; the first peer match returns
 * its one-based index. Query failure/absent peer return 0; other kinds -1.
 * RE_ORIGINAL_QUIRK: this caller leaves the output local uninitialized,
 * although original lower-isct slot 54 reads its first two words before
 * delegation. The observed 88-byte copy span is not a historical type or
 * complete allocation guarantee; do not invent zero/default prefix values.
 * RE_UNKNOWN: prefix provenance, caller pointer/identifier/count domains,
 * peer-array extent and pointer/module replacement lifetimes need original
 * producers, entry callers and full callback-path evidence. No reachable
 * invalid-input or player bug is established by this bounded native review.
 * Readable C remains parked: native 252 versus draft 248 bytes, 27 differing
 * instruction positions. Frame 160 becomes 152; result/output SP+68/72 become
 * SP+136/48. Native signed SLT/BNEZ termination becomes BNE after the draft's
 * positive-count gate and zero index; count capture and scan effects agree.
 * The two eight-record relocation lists differ at peer-array address sites;
 * all eight type/target roles remain represented. Full review supports no
 * missing effect, width or ABI correction. Historical local declarations,
 * stack storage and lowering need exact instruction and packed/ROM proof. */
#line 421 "src/modules/battle.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409314.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_0040969C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/battle/func_battle_00409838.s")

#line 429 "src/modules/battle.c"
/* Original 324-byte body and all fourteen ordered object records match. */
/* The original MATH34 provider returns a 15-bit LCG value divided by
 * 32768.0f. Preserve signed truncation of that result times 3.0f, and the
 * three distinct callback paths. SND4C returns 1.0f, which is passed as the
 * fourth SND08 input; the fifth input is 0.5f. Reload SND after that callback.
 * The existing eight-byte field at owner+0x34 is passed as a sound handle,
 * with IDs 175/176/177 and third input 0x7FEB.
 * RE_UNKNOWN: caller validity, handle lifetime, module replacement domains
 * and historical formal type require original callers/producers. Native
 * body extent is 324 bytes; the final object also has a separate 12-byte
 * zero tail at original TEXT end, whose historical purpose is unproved. */
void battlePlayRandomThreeSoundVariant(BattleObj_407E78 *owner)
{
    s32 selection;
    f32 scalar;

    selection = (s32)(gUvMathExports->uvRandFLcg() * 3.0f);
    switch (selection) {
    case 0:
        scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
        ((BattleThreeSoundExports *)gSndExports)->setupHandle(owner->unk34, 175, 0x7FEB, scalar, 0.5f);
        break;
    case 1:
        scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
        ((BattleThreeSoundExports *)gSndExports)->setupHandle(owner->unk34, 176, 0x7FEB, scalar, 0.5f);
        break;
    case 2:
        scalar = ((BattleThreeSoundExports *)gSndExports)->getScalar();
        ((BattleThreeSoundExports *)gSndExports)->setupHandle(owner->unk34, 177, 0x7FEB, scalar, 0.5f);
        break;
    }
}
#line 430 "src/modules/battle.c"

