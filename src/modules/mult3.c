// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void mult3ReleaseItemModules(void);
void func_mult3_00400124(void);

/*
 * Install two MULT3 exports, including the item-module release hook.
 * Load letter, powerup, weapon and battle, then load TDATA. Outside
 * TASK_EDITOR call its slot-0x24 provider; unload TDATA and clear the
 * shared TDATA export pointer on either branch.
 * RE_ORIGINAL_QUIRK: Preserve the unconditional line directive and loading
 * order. The other four shared export pointers remain stored by this body;
 * no import-error or repeated-initialization branch is added.
 * RE_UNKNOWN: The TDATA operation, import failure, shared reference ownership
 * and provider lifetime require the multiplayer mode and loader owners.
 */
#line 9 "src/modules/mult3.c"
void __entrypoint_func_mult3_400000(Mult3_Exports* arg0) {
    uvUpdateFileAllocPtr(arg0);
    arg0->mult3ReleaseItemModules = mult3ReleaseItemModules;
    arg0->func_mult3_00400124 = func_mult3_00400124;
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

#line 13 "src/modules/mult3.c"
/* Unload letter, powerup and weapon, then clear their export pointers.
 * RE_UNKNOWN: shared ownership/lifetime need original loader/reload/teardown callers. */
void mult3ReleaseItemModules(void) {
    uvUnloadModule('lttr');
    uvUnloadModule('pwup');
    uvUnloadModule('wpon');
    gLetterExports = 0;
    gWeaponExports = 0;
    gPowerupExports = 0;
}
#line 21 "src/modules/mult3.c"

#line 22 "src/modules/mult3.c"
/* Original no-op exported at mult3 export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_mult3_00400124(void) {

}
#line 25 "src/modules/mult3.c"
