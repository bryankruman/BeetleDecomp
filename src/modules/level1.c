// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

extern void level1NoOpModuleCleanup(void);
extern void func_level1_00400044(void);

void __entrypoint_func_level1_400000(Level1_Exports* arg0) {
    uvUpdateFileAllocPtr(arg0);
    arg0->level1NoOpModuleCleanup = &level1NoOpModuleCleanup;
    arg0->func_level1_00400044 = &func_level1_00400044;
}


#line 16 "src/modules/level1.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void level1NoOpModuleCleanup(void) {

}
#line 19 "src/modules/level1.c"


#line 21 "src/modules/level1.c"
/* Original no-op exported at level1 export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_level1_00400044(void) {

}
#line 24 "src/modules/level1.c"


