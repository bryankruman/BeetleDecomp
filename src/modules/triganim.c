// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
typedef struct TriganimTransformNode { Mtx4F first, second; f32 rate; s32 objectId, value88, mode; struct TriganimTransformNode *next; } TriganimTransformNode;
extern TriganimTransformNode *D_triganim_00401878;
#include "module.h"
typedef struct { s32 objectId; u8 unk04[4]; UnkStruct_004005C8 *sound; } TriganimObjectSound;
extern Snd_Exports *gSndExports;
#include "module.h"
extern UvDobj_Exports *gUvDobjExports;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
/* Initializer-only storage view: each field is an original 32-bit address,
 * not an inferred callable export interface. Opaque assembly declarations
 * below identify linker code-label addresses only: no data object or function
 * signature is inferred, and these addresses are never dereferenced here.
 * RE_UNKNOWN: replace each opaque label declaration with a grounded function
 * prototype when its implementation and actual caller ABI are recovered. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 unknownCallback04Address;
    /* 0x08 */ u32 unknownCallback08Address;
    /* 0x0C */ u32 unknownCallback0CAddress;
    /* 0x10 */ u32 unknownCallback10Address;
    /* 0x14 */ u32 promoteSecondaryTransformAddress;
    /* 0x18 */ u32 createTransformNodeAddress;
    /* 0x1C */ u32 unknownCallback1CAddress;
} TriganimExportAddresses;
/* Access view only: opaque spans are not inferred member identities.
 * RE_UNKNOWN: historical node declarations, complete allocation/lifetime and
 * callback mutation contracts need original producers and consumers. */
typedef struct TriganimUpdateNode {
    /* 0x00 */ s32 objectId;
    /* 0x04 */ s32 animationId;
    /* 0x08 */ u8 opaque08[0x1C];
    /* 0x24 */ s16 state;
    /* 0x26 */ u8 promoteTransform;
    /* 0x27 */ u8 opaque27[7];
    /* 0x2E */ s16 triggerMode;
    /* 0x30 */ f32 time;
    /* 0x34 */ u8 opaque34[0xC];
    /* 0x40 */ s32 effectId;
    /* 0x44 */ f32 triggerTime;
    /* 0x48 */ void *dynamicStates[5];
    /* 0x5C */ s32 modelLods[5];
    /* 0x70 */ u8 attachmentsUpdated;
    /* 0x71 */ u8 opaque71[3];
    /* 0x74 */ struct TriganimUpdateNode *next;
} TriganimUpdateNode;
/* Only called slots are typed, using the current provider definitions and
 * native caller arguments. Gaps are unused export-address storage. */
typedef struct {
    u8 opaque00[0x13C];
    void *(*createSecondaryState)(void);
    u8 opaque140[4];
    void (*copySecondaryCompanionFields)(void *);
    void (*setSecondaryScalarProperty)(void *, s32, f32);
    u8 opaque14C[0x10];
    void (*setSecondaryMatrixProperty)(void *, s32, Mtx4F *);
    u8 opaque160[8];
    void (*setSecondaryCollection)(void *, void *);
    u8 opaque16C[4];
    void (*setSecondaryModelLod)(void *, s32, s32);
    u8 opaque174[4];
    void (*updateSecondaryStateOnce)(void *, f32);
} TriganimDynamicExports;
typedef struct {
    u8 opaque00[0xEC];
    s32 (*copyObjectHierarchyMatrices)(Mtx4F *, s32, s32, s32);
} TriganimMatrixExports;
extern TriganimDynamicExports *gUvDynExports;
extern TriganimMatrixExports *gMiscExports;
extern UvJanim_Exports *gUvJanimExports;
extern UvPfx_Exports *gUvPfxExports;
extern u32 D_triganim_00401874;
s32 func_triganim_00401274(TriganimUpdateNode *);
s32 func_triganim_00400A68(TriganimUpdateNode *);
void func_triganim_00400374(TriganimUpdateNode *);
void func_triganim_004010D4(TriganimUpdateNode *);
void func_triganim_0040154C(u8);
#include <stdarg.h>
void func_triganim_00400090(void);
void triganimPromoteSecondaryTransform(s32 objectId);
TriganimTransformNode *triganimCreateTransformNode(Mtx4F *first, Mtx4F *second, f32 rate, s32 modelId, s32 mode);
extern u8 func_triganim_00400098[];
void func_triganim_00400624(void);
extern u8 func_triganim_004007D4[];
void func_triganim_00400F7C(TriganimUpdateNode *, ...);
extern u8 func_triganim_004016D4[];

#line 38 "src/modules/triganim.c"
/* Register the eight original trigger-animation callback addresses after
 * updating the allocation pointer; then clear word 0x1874 and the transform
 * list head in their original order. Preserve the empty callback identity.
 * RE_UNKNOWN: callback contracts at slots 0x04/08/0C/10/1C and the role/type
 * of word 0x1874 require their original implementations and readers/writers.
 * Export storage capacity/lifetime and safe initialization of existing lists
 * remain loader/caller contracts. Audit those callers before changing resets. */
void __entrypoint_func_triganimInitializeModuleExports(TriganimExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_triganim_00400090;
    exports->unknownCallback04Address = (u32) func_triganim_00400098;
    exports->unknownCallback08Address = (u32) func_triganim_00400624;
    exports->unknownCallback0CAddress = (u32) func_triganim_004007D4;
    exports->unknownCallback10Address = (u32) func_triganim_00400F7C;
    exports->promoteSecondaryTransformAddress = (u32) triganimPromoteSecondaryTransform;
    exports->createTransformNodeAddress = (u32) triganimCreateTransformNode;
    exports->unknownCallback1CAddress = (u32) func_triganim_004016D4;
    D_triganim_00401874 = 0;
    D_triganim_00401878 = NULL;
}
#line 39 "src/modules/triganim.c"

#line 14 "src/modules/triganim.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_triganim_00400090(void) {
}
#line 16 "src/modules/triganim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400374.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_004007D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400A68.s")

/* Fill up to five empty dynamic-state slots from signed16 variadic LOD IDs.
 * Each populated slot receives the owner object/model LOD, scalar property
 * nine equal to one, then the shared secondary collection in that order.
 * RE_QUIRK: an occupied slot or -1 ID stops the whole operation, preserving
 * earlier writes; allocation failure is not checked before provider calls.
 * RE_UNKNOWN: historical promoted argument declarations, valid model/LOD and
 * collection domains, allocation failure behavior and ownership/lifetime
 * require original callers/providers. Read each promoted four-byte argument
 * and narrow to its signed low halfword, as the native code does. */
void func_triganim_00400F7C(TriganimUpdateNode *node, ...) {
    va_list arguments;
    s32 index;
    s16 modelLod;

    if (node == NULL) {
        return;
    }
    va_start(arguments, node);
    node->attachmentsUpdated = 0;
    for (index = 0; index < 5; index++) {
        if (node->dynamicStates[index] != NULL) {
            return;
        }
        modelLod = (s16)va_arg(arguments, s32);
        if (modelLod == -1) {
            return;
        }
        node->modelLods[index] = modelLod;
        node->dynamicStates[index] = gUvDynExports->createSecondaryState();
        gUvDynExports->setSecondaryModelLod(
            node->dynamicStates[index], node->objectId, modelLod);
        gUvDynExports->setSecondaryScalarProperty(
            node->dynamicStates[index], 9, 1.0f);
        gUvDynExports->setSecondaryCollection(
            node->dynamicStates[index], (void *)gGameSettings->unkPtr90);
    }
    va_end(arguments);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_004010D4.s")

#line 28 "src/modules/triganim.c"
/*
 * Clear the dynamic object unconditionally, then read the sound pointer and
 * store -1 to the object ID. Release the sound only when non-NULL, and clear
 * the sound pointer afterward on both paths. Preserve this callback/store order.
 * RE_UNKNOWN: Whether invalid object IDs are accepted belongs to the provider.
 */
#line 30 "src/modules/triganim.c"
void triganimReleaseObjectAndSound(TriganimObjectSound *state) {
    UnkStruct_004005C8 *sound;
    gUvDobjExports->uvDobjClearModelAndStateByte(state->objectId);
    sound = state->sound;
    state->objectId = -1;
    if (sound != NULL) gSndExports->sndReleaseHandle(sound);
    state->sound = NULL;
}
#line 29 "src/modules/triganim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00401274.s")

#line 29 "src/modules/triganim.c"
/*
 * Build a local identity matrix, read object transform slot 1, write that matrix
 * to slot 0, then replace slot 1 with the identity. Preserve the four callback
 * calls and both distinct local matrix lifetimes; no matrix is combined here.
 * RE_UNKNOWN: Object validity and transform-slot ownership remain caller-owned.
 */
#line 31 "src/modules/triganim.c"
void triganimPromoteSecondaryTransform(s32 objectId) {
    Mtx4F secondaryTransform;
    Mtx4F identity;

    gUvFmtxExports->uvMat4SetIdentity(&identity);
    gUvDobjExports->uvDobjGetPosm(objectId, 1, &secondaryTransform);
    gUvDobjExports->uvDobjPosm(objectId, 0, &secondaryTransform);
    gUvDobjExports->uvDobjPosm(objectId, 1, &identity);
}
#line 30 "src/modules/triganim.c"

#line 31 "src/modules/triganim.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_triganim_0040154C(u8 a0) {
}
#line 33 "src/modules/triganim.c"

#line 34 "src/modules/triganim.c"
/* Allocate/prepend the original 0x94-byte node, copy both matrices and attach
 * its model/object. Modes zero/two set object flags three; mode one clears them.
 * Scalar 0x80 and mode meanings remain unresolved.
 * RE_ORIGINAL_QUIRK: negative-only object failure test does not reject provider's 0xFFFF.
 * RE_UNKNOWN: exhaustion reachability, node allocation/lifetime need original callers/allocator. */
TriganimTransformNode *triganimCreateTransformNode(Mtx4F *first, Mtx4F *second, f32 rate, s32 modelId, s32 mode) {
    TriganimTransformNode *node;
    s32 objectId;
    s32 acquired;
    if (modelId < 0) return NULL;
    acquired = gUvDobjExports->uvDobjCreate();
    objectId = acquired;
    if (acquired < 0) return NULL;
    uvLoadFile('UVMD', modelId);
    node = _uvMemAllocAlign8(0x94);
    node->next = D_triganim_00401878;
    D_triganim_00401878 = node;
    node->objectId = objectId;
    node->rate = rate;
    node->mode = mode;
    node->value88 = 0;
    gUvFmtxExports->uvMat4FCopy(&node->first, first);
    gUvFmtxExports->uvMat4FCopy(&node->second, second);
    gUvDobjExports->uvDobjModel(node->objectId, modelId);
    gUvDobjExports->uvDobjPosm(node->objectId, 0, first);
    if (mode == 2 || mode == 0) gUvDobjExports->uvDobjSetFlagBits(node->objectId, 3);
    if (mode == 1) gUvDobjExports->uvDobjClearFlagBits(node->objectId, 3);
    return node;
}
#line 35 "src/modules/triganim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_004016D4.s")

