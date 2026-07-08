// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/*__SEEDEXTERNS__*/
typedef struct { char pad[0xC]; void (*unkC)(Mtx4F *); } UvFMtxExp_00403A9C;
extern UvFMtxExp_00403A9C *gUvFmtxExports;
extern void *D_cam_00404E28;
extern f32 D_cam_00404958;
extern void *D_cam_00404DF4;
extern s32 D_cam_00404E2C;
extern void *gUvChanExports;
extern void *gUvEnvExports;
extern void *D_cam_00404E08;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/__entrypoint_func_cam_400000.s")

void func_cam_00400128(void) {
}

void func_cam_00400130(void *arg0, s32 arg1) {
    void *temp_a2;

    temp_a2 = arg0;
    if (arg1 != -1) {
        (*(void (**)(s32))((u8 *)gUvEnvExports + 0x1C))(*(s32 *)((u8 *)arg0 + 0x220));
    }
    (*(void (**)(s32, s32))((u8 *)gUvEnvExports + 0x18))(*(s16 *)((u8 *)temp_a2 + 0x0), *(s32 *)((u8 *)temp_a2 + 0x220));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00400190.s")

void func_cam_0040076C(s16 *arg0) {
    *(s32 *)((u8 *)&D_cam_00404E2C + 0) -= 1;
    (*(void (**)(s32))((u8 *)gUvChanExports + 0x20))(*arg0);
    *arg0 = -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004007C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00400C0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00400E80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_0040116C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_0040154C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004015C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004018E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00401B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00401D3C.s")

extern void func_cam_00403394(void *, s32, s32, f64, s32);
extern f32 D_cam_004048D0;
typedef struct
{
  char pad[0x0C];
  s32 (*unkC)(void *, f32 *);
} ExplExp_00402158;
extern ExplExp_00402158 *gExplExports;
typedef struct
{
  char pad[0x20];
  void (*unk20)(f32, f32, s32, void *);
} MiscExp_00402158;
extern MiscExp_00402158 *gMiscExports;
typedef struct
{
  f32 x;
  f32 y;
  f32 z;
} Vec3F_00402158;
typedef struct
{
  char pad[0x28];
  void (*unk28)(Vec3F_00402158 *, Vec3F_00402158 *, Vec3F_00402158 *);
} UvFVecExp_00402158;
extern UvFVecExp_00402158 *gUvFvecExports;

void func_cam_00402158(void *arg0, void *arg1, void *arg2)
{
  f32 sp4C;
  void *new_var;
  f32 new_var2;
  Vec3F_00402158 sp38;
  f32 temp_fv0;
  f32 var_fv1;
  temp_fv0 = *((f32 *) (((u8 *) arg1) + 0x3BC));
  if (temp_fv0 > 0.0f)
  {
    var_fv1 = temp_fv0;
  }
  else
  {
    var_fv1 = -temp_fv0;
  }
  new_var = arg1;
  new_var2 = *((f32 *) (((u8 *) new_var) + 0x3B0));
  *((f32 *) (((u8 *) arg0) + 0x15C)) += (var_fv1 * (*((f32 *) (((u8 *) arg2) + 0x24)))) + (new_var2 * (*((f32 *) (((u8 *) arg2) + 0x28))));
  gMiscExports->unk20(*((f32 *) (((u8 *) arg0) + 0x15C)), (*((f32 *) (((u8 *) arg0) + 0x150))) - D_cam_004048D0, *((s32 *) (((u8 *) arg0) + 0x154)), &sp38);
  gUvFvecExports->unk28(&sp38, &sp38, (Vec3F_00402158 *) (((u8 *) arg0) + 0x1F0));
  if (gExplExports->unkC(&sp38, &sp4C) != 0)
  {
    func_cam_00403394(arg0, 0x12, 3, (f64) sp4C, 0);
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_0040225C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004022E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_0040263C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00402934.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00402E08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00402FEC.s")

void func_cam_0040317C(void *arg0) {
    D_cam_00404DF4 = arg0;
    (*(void (**)(s32))((u8 *)gUvChanExports + 0x24))(*(s16 *)arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004031B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00403394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00403A20.s")

/* Advances a Mtx4F pointer by 0x1A8 bytes into a camera struct and calls the UvFMtx export at offset 0xC */
void func_cam_00403A9C(char *arg0) {
    gUvFmtxExports->unkC((Mtx4F *)(arg0 + 0x1A8));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00403ACC.s")

void func_cam_00404080(s32 a0) {
    *(s32*)((u8*)D_cam_00404E08 + 0x1EC) = 0;
}

void func_cam_00404094(s32 arg0) {
    *(f32 *)((u8 *)D_cam_00404E28 + 0x18) = *(f32 *)((u8 *)D_cam_00404E28 + 0x14) * D_cam_00404958;
    *(s32 *)((u8 *)D_cam_00404E28 + 0x10) = 1;
    *(s32 *)((u8 *)D_cam_00404E28 + 0xC) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004040D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004042FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00404558.s")

