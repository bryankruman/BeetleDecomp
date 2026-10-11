// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

extern s32 D_track7_004000B0;
extern void track7NoOpModuleCleanup(void);
extern void func_track7_0040009C(void);
extern UnkStruct_80025CF0 gGameSettings[];
extern s32 D_80025DE0;
/* Publish two callbacks and shared track data. Load tdta; call its slot 0x24
 * outside TASK_EDITOR, then unload tdta and clear the provider pointer.
 * RE_UNKNOWN: slot 0x24's purpose and shared-data lifetime need provider/callers. */
#line 12 "src/modules/track7.c"
void __entrypoint_func_track7_400000(Track7_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->track7NoOpModuleCleanup = &track7NoOpModuleCleanup;
    exports->func_track7_0040009C = &func_track7_0040009C;
    #line 1
    D_80025DE0 = &D_track7_004000B0;
    gTdataExports = uvLoadModule('tdta');
    if (gGameSettings->currentGameState != TASK_EDITOR) {
        gTdataExports->unk24();
    }
    uvUnloadModule('tdta');
    gTdataExports = NULL;
}

#line 26 "src/modules/track7.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void track7NoOpModuleCleanup(void) {
}
#line 28 "src/modules/track7.c"

#line 29 "src/modules/track7.c"
/* Original no-op exported at track7 export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_track7_0040009C(void) {
}
#line 31 "src/modules/track7.c"
