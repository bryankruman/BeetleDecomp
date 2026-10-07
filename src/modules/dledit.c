// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_dledit_00400600, D_dledit_00400658, D_dledit_004006C4, D_dledit_00400708;
u8 * func_dledit_00400098();
void func_dledit_004000C8();
s32 dleditLookupMappedWord(s32 context, s32 alternate, s32 row, s32 column);
void func_dledit_00400174();
void func_dledit_004001F8();
void func_dledit_0040030C();
void func_dledit_004003D4();
s32 * func_dledit_004004FC();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/__entrypoint_func_dledit_400000.s")

void func_dledit_00400090(void) {
}

u8 *func_dledit_00400098(u8 *a0, s32 a1) {
    s32 temp;

loop:
    temp = *a0;
    if (temp == a1) {
        return a0;
    }
    a0 += 8;
    if (((temp << 24) >> 24) == 0xDF) {
        return NULL;
    }
    goto loop;
}

void func_dledit_004000C8(u8 *a0, s32 a1) {
    u8 *temp;

    temp = func_dledit_00400098(a0, 0xFD);
    if (temp != NULL) {
        *(s32 *)(temp + 4) = (s32)((u32)a1 + 0x80000000U);
    }
}

#line 41 "src/modules/dledit.c"
/* Select an index from the original direct, eight-column or nine-column
 * lookup tables, then return the mapped 32-bit word. Preserve the unused
 * context and unchecked signed row/column contracts. */
s32 dleditLookupMappedWord(s32 context, s32 alternate, s32 row, s32 column) {
    s32 index;
    if (column >= 9) index = ((s32 *)&D_dledit_004006C4)[column];
    else if (alternate) index = *(s32 *)((u8 *)&D_dledit_00400708 + (row << 5) + column * 4);
    else index = *(s32 *)((u8 *)&D_dledit_00400658 + row * 0x24 + column * 4);
    return ((s32 *)&D_dledit_00400600)[index];
}
#line 42 "src/modules/dledit.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_00400174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_004001F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_0040030C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_004003D4.s")

s32 *func_dledit_004004FC(s32 *a0, s32 a1) {
    s32 temp;
    s32 word;

loop:
    temp = *(u8 *)a0;
    word = *a0;
    if (word == a1) {
        return a0;
    }
    a0 += 2;
    if (((temp << 24) >> 24) == 0xDF) {
        return NULL;
    }
    goto loop;
}

