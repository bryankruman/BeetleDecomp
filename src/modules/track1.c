// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
extern UvDobj_Exports *gUvDobjExports;
extern s32 D_track1_00401178;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track1/__entrypoint_func_track1_400000.s")

#line 8 "src/modules/track1.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_track1_00400BD8(void) {
}
#line 10 "src/modules/track1.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/track1/func_track1_00400BE0.s")

#line 13 "src/modules/track1.c"
/* Clear mask 0x2 on the track dynamic object and return zero. Retain the
 * current four-argument callback interface; this body ignores all inputs. */
s32 track1ClearDynamicObjectFlagTwoCallback(s32 first, s32 second, s32 third, s32 fourth) {
    gUvDobjExports->uvDobjClearFlagBits(D_track1_00401178, 2);
    return 0;
}
#line 14 "src/modules/track1.c"

