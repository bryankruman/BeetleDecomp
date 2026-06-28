// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
void func_menuslct_00400BCC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_menuslct_004000F8();
void func_menuslct_00400330();
void func_menuslct_0040043C();
void func_menuslct_0040056C();
void func_menuslct_0040062C();
s32 func_menuslct_004009FC(void *arg0);
void func_menuslct_00400A5C();
void func_menuslct_00400B14();
void func_menuslct_00400BCC();
void func_menuslct_00400E48();
void func_menuslct_004010C4();
void func_menuslct_004011B0();
void func_menuslct_0040126C();
void func_menuslct_00401320();
void func_menuslct_004013F8();
void func_menuslct_0040143C();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/__entrypoint_func_menuslct_400000.s")

void func_menuslct_004000F0(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004000F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040043C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040056C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040062C.s")

s32 func_menuslct_004009FC(void *arg0)
{
  s16 count;
  s16 i;
  void *base;
  count = *((s16 *) (((u8 *) arg0) + 0x0));
  i = 0;
  if (count > 0)
  {
    base = (void *) (*((s32 *) (((u8 *) arg0) + 0x8)));
    do
    {
      if ((*((s16 *) ((((u8 *) base) + (i * 0x14)) + 0x2))) == 1)
      {
        return i;
      }
      i = i + 1;
    }
    while (i < count);
  }
  return -1;
  return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400B14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400BCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004010C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004011B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040126C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00401320.s")

void func_menuslct_004013F8(s32 arg0) {
    func_menuslct_00400BCC(0x16, 0xE1, 0x12A, 0x10, 0, 0, 0, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040143C.s")

