// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern f32 D_uvdyn_rom_00411DB4;
extern u16 D_uvdyn_rom_00411EC0;
extern u16 D_uvdyn_rom_00411EC2;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/__entrypoint_func_uvdyn_rom_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400564.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004005F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400664.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004006D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004006EC.s")

f32 *func_uvdyn_rom_00400710(void) {
    return &D_uvdyn_rom_00411DB4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040071C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004009BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040232C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00402BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00402E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403294.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004033F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004034C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403574.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004035A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004037F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403860.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403A1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403C38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403D90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004041CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004043E0.s")

void func_uvdyn_rom_004044D0(void *arg0, s32 arg1) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x14B8) = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004044E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404538.s")

s32 func_uvdyn_rom_004045A8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004045B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404674.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004046B4.s")

s32 func_uvdyn_rom_004046E0(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x18);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004046FC.s")

s32 func_uvdyn_rom_00404734(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x38);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404750.s")

s32 func_uvdyn_rom_0040481C(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x28);
}

void func_uvdyn_rom_00404824(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x2C) = arg1;
}

s32 func_uvdyn_rom_0040482C(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x2C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404834.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040492C.s")

s32 func_uvdyn_rom_00404940(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x120C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040495C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004049F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404A58.s")

void func_uvdyn_rom_00404ACC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x12B6) = 0;
}

s32 func_uvdyn_rom_00404AD4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x1274);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404AF0.s")

u16 func_uvdyn_rom_00404BA4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(u16 *)((u8 *)arg0 + 0x12DA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404CE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404DE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404F34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404F8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404FE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040500C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00405040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004050EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040771C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004079B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407DF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004088EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409318.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004094CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040954C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040981C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409960.s")

u16 func_uvdyn_rom_00409A40(void *arg0) {
    return *(u16 *)((u8 *)arg0 + 0x12D6);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409A48.s")

void func_uvdyn_rom_00409A68(void) {
    D_uvdyn_rom_00411EC0 = 0;
    D_uvdyn_rom_00411EC2 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409AF0.s")

void func_uvdyn_rom_00409BC0(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x23C) = 1;
}

s32 func_uvdyn_rom_00409BCC(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409CE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A05C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A0D8.s")

s32 func_uvdyn_rom_0040A180(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040AFAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040AFD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B00C.s")

void func_uvdyn_rom_0040B070(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x240) = arg2;
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x258) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B75C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B838.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BAA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BAD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BB5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BC48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BCE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BD14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BFD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C064.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C100.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C1A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C20C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C2C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C3B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C464.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E4E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E8E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040F78C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040FC88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004107FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410C40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410E24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004110D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0041138C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411644.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004116A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411744.s")

s32 func_uvdyn_rom_004117B8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004117C0.s")

s32 func_uvdyn_rom_004118C8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004118D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411954.s")

