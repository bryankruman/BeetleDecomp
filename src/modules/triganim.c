// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_00401554.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/triganim/func_triganim_004016D4.s")

