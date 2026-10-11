// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void mult6NoOpModuleCleanup(void);
void func_mult6_00400124(void);

/*
 * Install two exports, load the letter, powerup, weapon, battle, TDATA and
 * volume-test modules, then pass volume-test query 0x27 to the environment
 * provider with the second argument one. Outside TASK_EDITOR, call the
 * TDATA reset provider. Unload TDATA and clear its shared export pointer.
 * RE_ORIGINAL_QUIRK: Keep the unused pointer local and the no-op cleanup
 * export. The other five loaded module references remain held by this body.
 * RE_UNKNOWN: Import failure, repeat initialization, the environment operation
 * and ownership of retained module references require the multiplayer owners.
 */
#line 9 "src/modules/mult6.c"
void __entrypoint_func_mult6_400000(Mult6_Exports* exports) {
    void* temp_v0;

    uvUpdateFileAllocPtr(exports);
    exports->mult6NoOpModuleCleanup = &mult6NoOpModuleCleanup;
    exports->func_mult6_00400124 = &func_mult6_00400124;
    gLetterExports = uvLoadModule('lttr');
    gPowerupExports = uvLoadModule('pwup');
    gWeaponExports = uvLoadModule('wpon');
    gBattleExports = uvLoadModule('batl');
    gTdataExports = uvLoadModule('tdta');
    gVolTestExports = uvLoadModule('volt');
    gEnvExports->unk1C(gVolTestExports->unk4(0x27), 1);
    if (gGameSettings->currentGameState != TASK_EDITOR) {
        gTdataExports->unk24();
    }
    uvUnloadModule('tdta');
    gTdataExports = NULL;
}

#line 29 "src/modules/mult6.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void mult6NoOpModuleCleanup(void) {

}
#line 32 "src/modules/mult6.c"

#line 33 "src/modules/mult6.c"
/* Original no-op exported at mult6 export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_mult6_00400124(void) {

}
#line 36 "src/modules/mult6.c"
