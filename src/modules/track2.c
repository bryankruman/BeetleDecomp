// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvgfxmgr_rom.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track2/__entrypoint_func_track2_400000.s")

#line 7 "src/modules/track2.c"
/* Forward the fixed environment color (1, 1, 0.8, 1) to the graphics manager.
 * RE_UNKNOWN: its scene role and graphics-provider lifetime remain unresolved;
 * this wrapper changes no local state and performs no resource initialization. */
#line 8 "src/modules/track2.c"
void track2SetEnvironmentColor(void) {
    gUvGfxMgrExports->uvGfxSetEnvColorF(1.0f, 1.0f, 0.8f, 1.0f);
}
#line 11 "src/modules/track2.c"
#line 8 "src/modules/track2.c"

#line 9 "src/modules/track2.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_track2_00400B68(void) {
}
#line 11 "src/modules/track2.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track2/func_track2_00400B70.s")

