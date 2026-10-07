// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void mult7NoOpModuleCleanup(void);
void func_mult7_004000DC(void);

void __entrypoint_func_mult7_400000(Mult7_Exports* arg0) {
    uvUpdateFileAllocPtr(arg0);
    arg0->mult7NoOpModuleCleanup = mult7NoOpModuleCleanup;
    arg0->func_mult7_004000DC = func_mult7_004000DC;
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

#line 13 "src/modules/mult7.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void mult7NoOpModuleCleanup(void) {

}
#line 16 "src/modules/mult7.c"

#line 17 "src/modules/mult7.c"
/* Original no-op exported at mult7 export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_mult7_004000DC(void) {

}
#line 20 "src/modules/mult7.c"
