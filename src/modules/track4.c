// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/__entrypoint_func_track4_400000.s")

#line 4 "src/modules/track4.c"
/* Apply the course's pale-yellow environment color. Enable selects the
 * original course alpha constant; disable restores fully opaque alpha. */
#include "common.h"
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004023E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004024A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_00402600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004029D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_00402B04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004030C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004032F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004034F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_0040355C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track4/func_track4_004036B0.s")

