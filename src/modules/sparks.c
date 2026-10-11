// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvquat_rom.h"
#include "uvdobj_rom.h"
#include "uvcback_rom.h"
#include "uvchannel_rom.h"
extern UvDobj_Exports *gUvDobjExports;
extern UvCback_Exports *gUvCbckExports;
extern UvChannel_Exports *gUvChanExports;
typedef struct { s32 dobjHandle; s32 transformCountdown; } SparksStatePrefix;

extern void *D_sparks_00400454;
void sparksModuleCleanup();
void sparksRegisterChannelCallback(s32 channel);
void func_sparks_004001EC();
void func_sparks_0040027C();
s32 sparksUpdateObjectTransform(SparksStatePrefix *state, Mtx4F *matrix);
void sparksResetStateAndDobjMode(SparksStatePrefix *state);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/sparks/__entrypoint_func_sparks_400000.s")

#line 22 "src/modules/sparks.c"
/* Unload spark model 0x47 and free the shared allocation in the
 * original order. Preserve the existing cleanup lifetime contract. */
void sparksModuleCleanup(void) {
    uvUnloadFile('UVMD', 0x47);
    _uvMemFree(D_sparks_00400454);
}
#line 26 "src/modules/sparks.c"

#line 27 "src/modules/sparks.c"
/* Request channel property 6, then add the object-transform callback with NULL
 * context and priority 0x2E. Preserve the two provider calls in that order.
 * RE_ORIGINAL_QUIRK: the local list pointer is not initialized or checked here.
 * RE_UNKNOWN: the channel must populate it, and list/callback lifetime and duplicate
 * registration behavior remain provider/caller obligations. */
#line 28 "src/modules/sparks.c"
void sparksRegisterChannelCallback(s32 channel) {
    CallbackList *callbacks;
    gUvChanExports->uvChannelGetProperties(channel, 6, &callbacks, 0);
    gUvCbckExports->uvAddCallback(callbacks, sparksUpdateObjectTransform, NULL, 0x2E);
}
#line 33 "src/modules/sparks.c"
#line 28 "src/modules/sparks.c"

/* Reset all four 20-byte slots in the original 0x50-byte allocation.
 * Set each countdown to -1, reread the shared base and clear DOBJ flag mask 2
 * on that slot's handle. Preserve live base/provider reads across callbacks.
 * RE_UNKNOWN: Allocation failure and teardown/reentrancy guarantees remain
 * caller-owned. This uses the existing two-word prefix, not a full slot type. */
void func_sparks_004001EC() {
    s32 byteOffset;

    for (byteOffset = 0; byteOffset != 0x50; byteOffset += 0x14) {
        ((SparksStatePrefix *)((u8 *)D_sparks_00400454 + byteOffset))
            ->transformCountdown = -1;
        gUvDobjExports->uvDobjClearFlagBits(
            ((SparksStatePrefix *)((u8 *)D_sparks_00400454 + byteOffset))
                ->dobjHandle,
            2);
    }
}
#line 30 "src/modules/sparks.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/sparks/func_sparks_0040027C.s")

#line 33 "src/modules/sparks.c"
/* Apply the matrix while transformCountdown is nonnegative, then decrement it.
 * Acquisition sets five; zero still updates, and negative state resets/returns zero.
 * RE_UNKNOWN: callback cadence and state lifetime need original callers/teardown. */
#line 36 "src/modules/sparks.c"
s32 sparksUpdateObjectTransform(SparksStatePrefix *state, Mtx4F *matrix) {
    if (state == NULL) return 0;
    if (state->transformCountdown < 0) { sparksResetStateAndDobjMode(state); return 0; }
    gUvDobjExports->uvDobjSetFlagBits(state->dobjHandle, 2);
    gUvDobjExports->uvDobjPosm(state->dobjHandle, 0, matrix);
    state->transformCountdown--;
    return 1;
}
#line 44 "src/modules/sparks.c"
#line 34 "src/modules/sparks.c"

#line 35 "src/modules/sparks.c"
/* Set transformCountdown to -1 and clear DOBJ flag mask 2. */
#line 36 "src/modules/sparks.c"
void sparksResetStateAndDobjMode(SparksStatePrefix *state) {
    state->transformCountdown = -1;
    gUvDobjExports->uvDobjClearFlagBits(state->dobjHandle, 2);
}
#line 40 "src/modules/sparks.c"
#line 36 "src/modules/sparks.c"

