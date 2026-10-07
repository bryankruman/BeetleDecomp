// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_game_004020B0[];
extern s32 D_game_004021E0;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/__entrypoint_func_game_400000.s")

#line 7 "src/modules/game.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_game_004001DC(void) {
}
#line 9 "src/modules/game.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_004001E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00400C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00400DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00401338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00401568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_004016F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00401CC0.s")

#line 24 "src/modules/game.c"
/* Release every loaded reference to the module selected by table index,
 * then clear the original transition state. Callers own table-index validity. */
void gameUnloadIndexedModuleCompletely(s32 index) {
    s32 tag = D_game_004020B0[index];
    if (uvGetLoadedModule(tag) != NULL) {
        do {
            uvUnloadModule(tag);
        } while (uvGetLoadedModule(tag) != NULL);
    }
    D_game_004021E0 = 0;
}
#line 25 "src/modules/game.c"

