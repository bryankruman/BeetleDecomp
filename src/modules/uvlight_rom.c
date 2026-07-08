// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_uvlight_rom_0040174C;
extern s32 D_uvlight_rom_00401798;
extern s32 D_uvlight_rom_00401760;
extern u8 D_uvlight_rom_00401754;
extern s32 D_uvlight_rom_00401738;
extern s32 D_uvlight_rom_0040173C;
extern s32 D_uvlight_rom_00401740;
extern s32 D_uvlight_rom_00401744;
extern u8 D_uvlight_rom_00401748;
extern u8 D_uvlight_rom_00401750;
extern u8 D_uvlight_rom_00401752;
extern s32 D_uvlight_rom_00401758;
extern u8 D_uvlight_rom_00401794;
extern s32 D_uvlight_rom_004016E0;
void func_uvlight_rom_00400690(void);
void func_uvlight_rom_004004D8();
void func_uvlight_rom_00400568();
void func_uvlight_rom_004005F0();
void func_uvlight_rom_00400690();
void func_uvlight_rom_0040081C();
void func_uvlight_rom_004008D4();
void func_uvlight_rom_00400B64();
void func_uvlight_rom_00400C60();
void func_uvlight_rom_00400D90();
void func_uvlight_rom_00400EDC();
void func_uvlight_rom_00400FB8();
s32 func_uvlight_rom_004011D0();
void func_uvlight_rom_0040120C();
s32 func_uvlight_rom_0040131C();
void func_uvlight_rom_00401340();
void func_uvlight_rom_00401624();
void func_uvlight_rom_0040167C();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/__entrypoint_func_uvlight_rom_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_004004D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400568.s")

void func_uvlight_rom_004005A8(s32 arg0)
{
  s32 temp0;
  s32 temp1;
  s32 temp2;
  s32 temp3;
  *((s32 *) (((u8 *) (&arg0)) + 0x0)) = arg0;
  temp0 = D_uvlight_rom_00401738;
  temp1 = (D_uvlight_rom_00401738 = D_uvlight_rom_0040173C);
  temp2 = D_uvlight_rom_00401740;
  temp3 = (D_uvlight_rom_00401740 = D_uvlight_rom_00401744);
  D_uvlight_rom_0040173C = temp0;
  D_uvlight_rom_00401744 = temp2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_004005F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_0040081C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_004008D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400B64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400D90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400EDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00400FB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_004011D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_0040120C.s")

void func_uvlight_rom_00401260(s32 *arg0, f32 arg1, f32 arg2, f32 arg3)
{
  s32 temp_v1;
  s32 a2;
  s32 t0;
  s32 var_v0;
  int new_var;
  s32 var_a1;
  s32 var_a3;
  temp_v1 = (var_v0 = (s32) (255.0f * arg1));
  a2 = (var_a1 = (s32) (255.0f * arg2));
  t0 = (var_a3 = (s32) (255.0f * arg3));
  new_var = temp_v1 < 0;
  if (new_var)
  {
    var_v0 = 0;
  }
  else
    if (temp_v1 >= 0x100)
  {
    var_v0 = 0xFF;
  }
  if (a2 < 0)
  {
    var_a1 = 0;
  }
  else
    if (a2 >= 0x100)
  {
    var_a1 = 0xFF;
  }
  if (t0 < 0)
  {
    var_a3 = 0;
  }
  else
    if (t0 >= 0x100)
  {
    var_a3 = 0xFF;
  }
  *arg0 = ((var_v0 << 0x18) | (var_a1 << 0x10)) | (var_a3 << 8);
}

s32 func_uvlight_rom_0040131C(s32 arg0) {
    return arg0 * 0x34 + D_uvlight_rom_00401758;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_00401340.s")

void func_uvlight_rom_00401624(s32 arg0) {
    void *entry;
    s32 ref;
    if (arg0 >= -2 && arg0 < (s32)D_uvlight_rom_00401794 && arg0 >= 0) {
        entry = (void *)(arg0 * 0x34 + D_uvlight_rom_00401758);
        ref = *(s32 *)((u8 *)entry + 0x30);
        if (ref != 0) {
            *(s32 *)((u8 *)entry + 0x30) = ref - 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvlight_rom/func_uvlight_rom_0040167C.s")

