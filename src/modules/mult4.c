// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void mult4ReleaseItemModules(void);
void func_mult4_00400124(void);

void __entrypoint_func_mult4_400000(Mult4_Exports* arg0) {
    uvUpdateFileAllocPtr(arg0);
    arg0->mult4ReleaseItemModules = mult4ReleaseItemModules;
    arg0->func_mult4_00400124 = func_mult4_00400124;
#line 1
    gLetterExports = uvLoadModule('lttr');
    gPowerupExports = uvLoadModule('pwup');
    gWeaponExports = uvLoadModule('wpon');
    gBattleExports = uvLoadModule('batl');
    gTdataExports = uvLoadModule('tdta');
    if (gGameSettings->currentGameState != TASK_EDITOR) {
        gTdataExports->unk24();
    }
    uvUnloadModule('tdta');
    gTdataExports = NULL;
}

#line 13 "src/modules/mult4.c"
/* Unload letter, powerup and weapon modules in order, then clear their
 * export pointers. Preserve the shared-module ownership convention. */
void mult4ReleaseItemModules(void) {
    uvUnloadModule('lttr');
    uvUnloadModule('pwup');
    uvUnloadModule('wpon');
    gLetterExports = 0;
    gWeaponExports = 0;
    gPowerupExports = 0;
}
#line 21 "src/modules/mult4.c"

#line 22 "src/modules/mult4.c"
/* Original no-op exported at mult4 export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_mult4_00400124(void) {

}
#line 25 "src/modules/mult4.c"
