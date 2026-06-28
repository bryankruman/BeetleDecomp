// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern char D_letter_00400480[];
void func_letter_00400140();
void func_letter_00400230();
void * func_letter_004003E8();
void func_letter_00400420();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/letter/__entrypoint_func_letter_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/letter/func_letter_00400140.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/letter/func_letter_00400230.s")

void *func_letter_004003E8(s32 arg0) {
    if (arg0 < 0 || arg0 >= 6) {
        return D_letter_00400480;
    }
    return D_letter_00400480 + arg0 * 0x14;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/letter/func_letter_00400420.s")

