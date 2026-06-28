// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_scene_00402CF8;
extern s32 D_scene_00402D10;
extern s32 D_scene_00402D34;
extern s32 D_scene_00402D40;
s32 func_scene_00400000();
s32 func_scene_00400030();
void func_scene_00400060();
void func_scene_004000FC();
void func_scene_00400188();
void func_scene_004002A8();
void func_scene_004002F0();
void func_scene_00400374();
void func_scene_004003F4();
void func_scene_00400C60();
void func_scene_00400CB8();
void func_scene_00400EC8();
void func_scene_00401254();
void func_scene_004012B8();
void func_scene_00401324();
void func_scene_004013F4();
void func_scene_00401438();
s32 func_scene_00400000(s32 a0) {
    if (a0 >= 6) {
        a0 = 5;
    } else if (a0 < 0) {
        a0 = 0;
    }
    return (&D_scene_00402CF8)[a0];
}

s32 func_scene_00400030(s32 a0) {
    if (a0 >= 9) {
        a0 = 8;
    } else if (a0 < 0) {
        a0 = 0;
    }
    return (&D_scene_00402D10)[a0];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400060.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004000FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004002A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004002F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400374.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004003F4.s")

void func_scene_00400C58(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/__entrypoint_func_scene_400e0c.s")

void func_scene_00400EC0(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00401254.s")

void func_scene_004012B0(s32 a0) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004012B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00401324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004013F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00401438.s")

