// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/__entrypoint_func_track4_400000.s")

#line 4 "src/modules/track4.c"
/* Apply the course's pale-yellow environment color. Enable selects the
 * original course alpha constant; disable restores fully opaque alpha. */
#include "common.h"
#include "uvfvec_rom.h"
typedef struct { u8 unk00[4]; s16 state; u8 unk06[0xE]; f32 magnitude; } Track4CopyState;
extern Track4CopyState D_track4_00404800;
#include "module.h"
extern Snd_Exports *gSndExports;
#include "uvgfxmgr_rom.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
extern f32 D_track4_00403B50;
/* Set environment RGB to (1, 1, 0.8). Use the shared tint scalar for any nonzero
 * enabled word, or alpha 1 for zero; preserve the original branch and call.
 * RE_UNKNOWN: shared-scalar range, tint meaning and graphics-provider lifetime
 * are unproved. This wrapper performs no clamp or normalization. */
#line 15 "src/modules/track4.c"
void track4SetEnvironmentTint(s32 enabled) {
    f32 alpha;
    if (enabled != 0) alpha = D_track4_00403B50;
    else alpha = 1.0f;
    gUvGfxMgrExports->uvGfxSetEnvColorF(1.0f, 1.0f, 0.8f, alpha);
}
#line 21 "src/modules/track4.c"
#line 5 "src/modules/track4.c"

#line 6 "src/modules/track4.c"
/* Stop the four course sound handles that have a valid emitter ID.
 * The original 0xFF sentinel and cleanup order are preserved. */
extern UnkStruct_004005C8 D_track4_00404830;
extern UnkStruct_004005C8 D_track4_00404838;
extern UnkStruct_004005C8 D_track4_00404840;
extern UnkStruct_004005C8 D_track4_00404848;

/* Release each of four sound handles whose unsigned byte at offset four is not
 * 0xFF, in the original address order 0x4830, 0x4840, 0x4838, 0x4848.
 * RE_UNKNOWN: the rest of the handle layout and release ownership remain provider
 * contracts. This body neither resets handles nor broadens the sentinel test. */
#line 13 "src/modules/track4.c"
void track4StopEnvironmentSounds(void) {
    if (D_track4_00404830.unk4 != 0xFF) {
        gSndExports->sndReleaseHandle(&D_track4_00404830);
    }
    if (D_track4_00404840.unk4 != 0xFF) {
        gSndExports->sndReleaseHandle(&D_track4_00404840);
    }
    if (D_track4_00404838.unk4 != 0xFF) {
        gSndExports->sndReleaseHandle(&D_track4_00404838);
    }
    if (D_track4_00404848.unk4 != 0xFF) {
        gSndExports->sndReleaseHandle(&D_track4_00404848);
    }
}
#line 27 "src/modules/track4.c"
#line 7 "src/modules/track4.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004024A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_00402600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004029D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_00402B04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004030C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004032F4.s")

#line 20 "src/modules/track4.c"
/* Initialize once while the course state is -1: copy the vector, store the
 * original signed-comparison absolute magnitude and set state 1. Return one
 * even when initialization is skipped; preserve NaN/negative-zero behavior. */
s32 track4InitializeVectorMagnitude(Vec3F *destination, f32 value, Vec3F *source, s32 context) {
    if (D_track4_00404800.state != -1) {
        return 1;
    }
    *destination = *source;
    if (value > 0.0f) D_track4_00404800.magnitude = value;
    else D_track4_00404800.magnitude = -value;
    D_track4_00404800.state = 1;
    return 1;
}
#line 21 "src/modules/track4.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_0040355C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004036B0.s")

