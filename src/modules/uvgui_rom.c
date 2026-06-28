// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern u8 D_uvgui_rom_00407238;
extern u8 D_uvgui_rom_00408A98;
extern u8 D_uvgui_rom_00408D78;
extern u8 D_uvgui_rom_0040D558;
extern s16 D_uvgui_rom_0040D576;
extern u8 D_uvgui_rom_0040FB50;
extern u8 D_uvgui_rom_00406F20;
extern s16 D_uvgui_rom_00406F3E;
void func_uvgui_rom_00400498();
void func_uvgui_rom_00400510();
void func_uvgui_rom_004006B8();
void func_uvgui_rom_00400754();
void func_uvgui_rom_00400990();
void func_uvgui_rom_00400F44();
void func_uvgui_rom_0040104C();
void func_uvgui_rom_0040126C();
void func_uvgui_rom_00401290();
void func_uvgui_rom_004015B8();
void func_uvgui_rom_00401614();
void func_uvgui_rom_004016AC();
void func_uvgui_rom_004016F0();
void func_uvgui_rom_00401BC8();
s16 func_uvgui_rom_00401CA0();
void * func_uvgui_rom_00401CE0();
void func_uvgui_rom_00401D10();
void func_uvgui_rom_00401D80();
void func_uvgui_rom_00401DC4();
void func_uvgui_rom_004020A0();
void func_uvgui_rom_0040221C();
void func_uvgui_rom_00402268();
void func_uvgui_rom_00402308();
void func_uvgui_rom_004023A8();
void func_uvgui_rom_00402638();
s16 func_uvgui_rom_00402698();
void * func_uvgui_rom_004026E8();
void func_uvgui_rom_00402718();
void func_uvgui_rom_00402788();
void func_uvgui_rom_004027AC();
void func_uvgui_rom_00402850();
void func_uvgui_rom_0040293C();
void func_uvgui_rom_00402B00();
s16 func_uvgui_rom_00402B60();
void * func_uvgui_rom_00402BA0();
void func_uvgui_rom_00402BD0();
void func_uvgui_rom_00402C40();
void func_uvgui_rom_00402C74();
void func_uvgui_rom_00402D1C();
void func_uvgui_rom_00402E48();
void func_uvgui_rom_0040300C();
s16 func_uvgui_rom_004031A4();
void func_uvgui_rom_004031E4();
void * func_uvgui_rom_0040320C();
void func_uvgui_rom_00403234();
void func_uvgui_rom_00403298();
void func_uvgui_rom_004032BC();
void func_uvgui_rom_004037E0();
void func_uvgui_rom_004038E4();
void func_uvgui_rom_00403C50();
void func_uvgui_rom_00403CAC();
s16 func_uvgui_rom_00403E78();
void func_uvgui_rom_00403EB8();
void * func_uvgui_rom_00403EE0();
void func_uvgui_rom_00403F08();
void func_uvgui_rom_00403F2C();
void func_uvgui_rom_00404010();
void func_uvgui_rom_00404054();
void func_uvgui_rom_004046B4();
void func_uvgui_rom_00405CEC();
void func_uvgui_rom_00405D1C();
void func_uvgui_rom_00405D78();
s16 func_uvgui_rom_00405F20();
void func_uvgui_rom_00405F60();
void * func_uvgui_rom_00405F90();
void func_uvgui_rom_00405FC0();
void func_uvgui_rom_00406024();
void func_uvgui_rom_00406048();
void func_uvgui_rom_00406B08();
void func_uvgui_rom_00406B88();
void func_uvgui_rom_00406E28();
extern s16 D_uvgui_rom_00406F00;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/__entrypoint_func_uvgui_rom_400000.s")

void func_uvgui_rom_00400498(void) {
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x464F4E54);
    uvUnloadModule(0x474D4752);
    uvUnloadModule(0x53544154);
    uvUnloadModule(0x4447454F);
    uvUnloadModule(0x67727068);
    uvUnloadModule(0x434F4E54);
    uvUnloadModule(0x53545247);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004006B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400754.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400990.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400F44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040104C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040126C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004015B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401614.s")

void func_uvgui_rom_004016A0(void *a0, u8 a1) {
    *(u8 *)((u8 *)a0 + 0x8A) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004016AC.s")

void func_uvgui_rom_004016E0(s16 a0) {
    D_uvgui_rom_00406F00 = a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004016F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401D10.s")

void func_uvgui_rom_00401D74(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0xC) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004020A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040221C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402268.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004023A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004026E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402718.s")

void func_uvgui_rom_0040277C(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0x1E) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402788.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004027AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402850.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040293C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402B60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402BA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402BD0.s")

void func_uvgui_rom_00402C34(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0x1E) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402C40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402C74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402D1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040300C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004031A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004031E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040320C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004032BC.s")

void func_uvgui_rom_004037D8(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x40) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004037E0.s")

void func_uvgui_rom_004038D8(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0x20) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004038E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403C50.s")

void func_uvgui_rom_00403CA4(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x44) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403CAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403E78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403EE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403F2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00404010.s")

void func_uvgui_rom_0040404C(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x8C) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00404054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004046B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405CEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405D1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405D78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405F20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405F90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405FC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406024.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406048.s")

void func_uvgui_rom_00406B00(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x48) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406B08.s")

void func_uvgui_rom_00406B7C(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0x20) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406E28.s")

