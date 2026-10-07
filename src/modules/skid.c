// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct UnkCbckExports_s {
    char pad[0x10];
    void (*unk10)(s32, void *, s32, s32);
} UnkCbckExports;
typedef struct UnkChanExports_s {
    char pad[0x4];
    void (*unk4)(s32, s32, void *, s32);
} UnkChanExports;
extern UnkCbckExports *gUvCbckExports;
extern UnkChanExports *gUvChanExports;
void func_skid_00400788(s32 arg0);
void skidModuleCleanup();
void skidRegisterChannelCallback();
void func_skid_0040018C();
void skidActivateRecord();
void func_skid_004002E0();
void func_skid_00400788();
void func_skid_00400968();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/skid/__entrypoint_func_skid_400000.s")

#line 23 "src/modules/skid.c"
/* Unload original skid texture 0x1B8. */
void skidModuleCleanup(void) {
    uvUnloadFile('UVTX', 0x1B8);
}
#line 26 "src/modules/skid.c"

#line 27 "src/modules/skid.c"
/* Find channel property six and register the original skid callback
 * with null context and priority 0x2E. */
void skidRegisterChannelCallback(s32 channel) {
    s32 callbackList;
    gUvChanExports->unk4(channel, 6, &callbackList, 0);
    gUvCbckExports->unk10(callbackList, func_skid_00400788, 0, 0x2E);
}
#line 32 "src/modules/skid.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/skid/func_skid_0040018C.s")

#line 35 "src/modules/skid.c"
/* Set the active byte and clear scalar 0x8 in original store order. */
void skidActivateRecord(void *record) {
    *(u8 *)((u8 *)record + 0x0) = 0x1;
    *(f32 *)((u8 *)record + 0x8) = 0.0f;
}
#line 39 "src/modules/skid.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/skid/func_skid_004002E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/skid/func_skid_00400788.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/skid/func_skid_00400968.s")

