// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvgfxmgr_rom.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track2/__entrypoint_func_track2_400000.s")

#line 7 "src/modules/track2.c"
/* Apply the original white environment color with a blue component of 0.8. */
void track2SetEnvironmentColor(void) {
    gUvGfxMgrExports->uvGfxSetEnvColorF(1.0f, 1.0f, 0.8f, 1.0f);
}
#line 8 "src/modules/track2.c"

void func_track2_00400B68(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track2/func_track2_00400B70.s")

