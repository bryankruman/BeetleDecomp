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
typedef struct { s32 dobjHandle; s32 value04; } SparksStatePrefix;

extern void *D_sparks_00400454;
void func_sparks_00400160();
void sparksRegisterChannelCallback(s32 channel);
void func_sparks_004001EC();
void func_sparks_0040027C();
void func_sparks_00400360(s32);
void sparksResetStateAndDobjMode(SparksStatePrefix *state);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/sparks/__entrypoint_func_sparks_400000.s")

void func_sparks_00400160(void) {
    uvUnloadFile('UVMD', 0x47);
    _uvMemFree(D_sparks_00400454);
}

#line 27 "src/modules/sparks.c"
/* Register the spark update callback on channel property six at priority 0x2E. */
void sparksRegisterChannelCallback(s32 channel) {
    CallbackList *callbacks;
    gUvChanExports->func_uvchannel_rom_00400288(channel, 6, &callbacks, 0);
    gUvCbckExports->uvAddCallback(callbacks, func_sparks_00400360, NULL, 0x2E);
}
#line 28 "src/modules/sparks.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/sparks/func_sparks_004001EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/sparks/func_sparks_0040027C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/sparks/func_sparks_00400360.s")

#line 35 "src/modules/sparks.c"
/* Reset the opaque spark value to -1 and set the original DOBJ mode to two. */
void sparksResetStateAndDobjMode(SparksStatePrefix *state) {
    state->value04 = -1;
    gUvDobjExports->func_uvdobj_rom_004010B4(state->dobjHandle, 2);
}
#line 36 "src/modules/sparks.c"

