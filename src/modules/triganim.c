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
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/__entrypoint_func_triganim_400000.s")

void func_triganim_00400090(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400374.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_004007D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400A68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00400F7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_004010D4.s")

#line 28 "src/modules/triganim.c"
/* Release the dynamic object, invalidate its ID, stop any attached sound
 * handle, then clear the handle pointer in the original order. */
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
/* Copy dynamic-object transform 1 into transform 0, then reset transform 1
 * to identity. This preserves the original matrix stack layout. */
void triganimPromoteSecondaryTransform(s32 objectId) {
    Mtx4F secondaryTransform;
    Mtx4F identity;

    gUvFmtxExports->uvMat4SetIdentity(&identity);
    gUvDobjExports->uvDobjGetPosm(objectId, 1, &secondaryTransform);
    gUvDobjExports->uvDobjPosm(objectId, 0, &secondaryTransform);
    gUvDobjExports->uvDobjPosm(objectId, 1, &identity);
}
#line 30 "src/modules/triganim.c"

void func_triganim_0040154C(u8 a0) {
}

#line 34 "src/modules/triganim.c"
/* Allocate and prepend the original 0x94-byte transform node, copy both
 * matrices and attach its model/object. Modes zero/two set object flags three;
 * mode one clears them. Scalar 0x80 and mode meanings are not otherwise guessed.
 * Preserve the original negative-only allocation failure check: the object
 * allocator actually returns 0xFFFF on exhaustion, so callers must avoid it. */
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

