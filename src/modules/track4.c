// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/__entrypoint_func_track4_400000.s")

#line 4 "src/modules/track4.c"
/* Apply the course's pale-yellow environment color. Enable selects the
 * original course alpha constant; disable restores fully opaque alpha. */
#include "common.h"
#include "module.h"
extern Snd_Exports *gSndExports;
#include "uvgfxmgr_rom.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
extern f32 D_track4_00403B50;
void track4SetEnvironmentTint(s32 enabled) {
    f32 alpha;
    if (enabled != 0) alpha = D_track4_00403B50;
    else alpha = 1.0f;
    gUvGfxMgrExports->uvGfxSetEnvColorF(1.0f, 1.0f, 0.8f, alpha);
}
#line 5 "src/modules/track4.c"

#line 6 "src/modules/track4.c"
/* Stop the four course sound handles that have a valid emitter ID.
 * The original 0xFF sentinel and cleanup order are preserved. */
extern UnkStruct_004005C8 D_track4_00404830;
extern UnkStruct_004005C8 D_track4_00404838;
extern UnkStruct_004005C8 D_track4_00404840;
extern UnkStruct_004005C8 D_track4_00404848;

void track4StopEnvironmentSounds(void) {
    if (D_track4_00404830.unk4 != 0xFF) {
        gSndExports->func_snd_00401CDC(&D_track4_00404830);
    }
    if (D_track4_00404840.unk4 != 0xFF) {
        gSndExports->func_snd_00401CDC(&D_track4_00404840);
    }
    if (D_track4_00404838.unk4 != 0xFF) {
        gSndExports->func_snd_00401CDC(&D_track4_00404838);
    }
    if (D_track4_00404848.unk4 != 0xFF) {
        gSndExports->func_snd_00401CDC(&D_track4_00404848);
    }
}
#line 7 "src/modules/track4.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004024A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_00402600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004029D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_00402B04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004030C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004032F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004034F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_0040355C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004036B0.s")

