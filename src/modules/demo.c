// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_demo_00402270;
extern s32 gNumAiCars;
extern void *gSceneExports;
extern void *D_demo_00402274;
void func_demo_00400244();
void func_demo_00400290();
void func_demo_0040041C();
void func_demo_00400538();
void func_demo_00400910();
void func_demo_004009F8();
void func_demo_00400BC4();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/__entrypoint_func_demo_400000.s")

void func_demo_00400244(void) {
    gNumAiCars = D_demo_00402270;
    gGameSettings->currentTrack = ((s32 (*)(s32))((s32 *)gSceneExports)[1])(0);
    gGameSettings->unk180 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_0040041C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400910.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_004009F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400BC4.s")

