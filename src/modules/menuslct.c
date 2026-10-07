// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[4]; s16 value; u8 unk06[6]; } MenuInputRecord;
typedef struct { u8 unk00[8]; MenuInputRecord *records; } MenuInputState;
typedef struct { u8 unk00[0x24]; s32 (*busy)(void); } MenuInputGuiExports;
typedef struct { u8 unk00[0x28]; s32 (*hasFlags)(s32, s32); } MenuInputReplayExports;
#include "module.h"

/*__SEEDEXTERNS__*/
extern UvFont_Exports *gUvFontExports;
extern void *gGameGuiExports;
extern void *gReplayExports;
void func_menuslct_00400BCC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_menuslct_004000F8();
void func_menuslct_0040043C();
s32 menuslctGetGatedInputAction(s32 controller, MenuInputState *state);
void func_menuslct_0040062C();
s32 func_menuslct_004009FC(void *arg0);
s32 menuslctAreAllBytesNonzero(u8 *values, s16 count);
s32 menuslctAreAllBytesZero(u8 *values, s16 count);
void func_menuslct_00400BCC();
void func_menuslct_00400E48();
void func_menuslct_004010C4();
void menuslctDrawBottomLabel(s8 *label);
void func_menuslct_0040126C();
void func_menuslct_00401320();
void func_menuslct_004013F8();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/__entrypoint_func_menuslct_400000.s")

void func_menuslct_004000F0(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004000F8.s")

s32 func_menuslct_00400330(s32 arg0, s32 arg1) {
    if ((*(s32 (**)(void))((u8 *)gGameGuiExports + 0x24))() != 0) {
        return 0;
    }
    if ((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(arg0, 0x4000) != 0) {
        return 7;
    }
    if (*(s16 *)((u8 *)arg1 + (arg0 * 0xC) + 0x4) == -1) {
        return 0;
    }
    if ((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(arg0, 0x8000) != 0) {
        return 8;
    }
    if (((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(arg0, 0x1000) != 0) || ((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(arg0, 0x1000) != 0)) {
        return 8;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040043C.s")

#line 56 "src/modules/menuslct.c"
/* When the GUI is not busy and this controller has a valid record, map
 * replay flag 0x20 to action five and 0x10 to action six, in that order.
 * All other paths return zero; controller/table bounds remain unchanged. */
s32 menuslctGetGatedInputAction(s32 controller, MenuInputState *state) {
    if (((MenuInputGuiExports *)gGameGuiExports)->busy() != 0) return 0;
    if (state->records[controller].value != -1) {
        if (((MenuInputReplayExports *)gReplayExports)->hasFlags(controller, 0x20) != 0) return 5;
        if (((MenuInputReplayExports *)gReplayExports)->hasFlags(controller, 0x10) != 0) return 6;
    }
    return 0;
}
#line 57 "src/modules/menuslct.c"

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

#line 80 "src/modules/menuslct.c"
/* Return one only when every byte in the signed-length range is nonzero.
 * Zero or negative lengths are vacuously true, as in the original. */
s32 menuslctAreAllBytesNonzero(u8 *values, s16 count) {
    s32 index;
    for (index = 0; index < count; index++) {
        if (values[index] == 0) return 0;
    }
    return 1;
}
#line 81 "src/modules/menuslct.c"

#line 82 "src/modules/menuslct.c"
/* Return one only when every byte in the signed-length range is zero.
 * Zero or negative lengths are vacuously true, as in the original. */
s32 menuslctAreAllBytesZero(u8 *values, s16 count) {
    s32 index;
    for (index = 0; index < count; index++) {
        if (values[index] != 0) return 0;
    }
    return 1;
}
#line 83 "src/modules/menuslct.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400BCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00400E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004010C4.s")

#line 90 "src/modules/menuslct.c"
/* Draw a black, opaque label centered at X=159 above the menu's bottom edge.
 * Font metrics determine the horizontal center and baseline. */
void menuslctDrawBottomLabel(s8 *label) {
    s32 height;
    s32 width;

    gUvFontExports->uvFontColor(0U, 0U, 0U, 0xFFU);
    gUvFontExports->uvSetFont(0);
    width = gUvFontExports->uvFontWidth(label);
    height = gUvFontExports->uvFontHeight();
    gUvFontExports->uvFontPrintStr(159 - (width / 2), 218 - height, label);
}
#line 91 "src/modules/menuslct.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040126C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00401320.s")

void func_menuslct_004013F8(s32 arg0) {
    func_menuslct_00400BCC(0x16, 0xE1, 0x12A, 0x10, 0, 0, 0, arg0);
}

void func_menuslct_0040143C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8) {
    s32 sp24;

    sp24 = 2;
    (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(a2);
    (*(void (*)(f64, f64))(*(s32 *)((u8 *)gUvFontExports + 0x8)))(1.0, 1.0);
    if (a2 == 0) {
        (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(2);
        sp24 = 4;
    }
    if (a8 != 0) {
        if (a2 != 3) {
            (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0, 0, 0, 0xAF);
            (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(a0 + sp24, a1 - sp24, a7);
            (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(a2);
            (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0, 0, 0, 0xFF);
            (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(a0 + 1, a1 - 1, a7);
        }
        (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))((u8)a3, (u8)a4, (u8)a5, (u8)a6);
        (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(a0, a1, a7);
        return;
    }
    (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(a2);
    (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0, 0, 0, 0xFF);
    (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(a0 + 1, a1 - 1, a7);
    (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0x78, 0x78, 0xBE, 0xE1);
    (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(a0, a1, a7);
}

