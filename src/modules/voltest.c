// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct VoltestRecord { s32 unk00; s8 first[4]; s8 second[4]; s8 third[8]; struct VoltestRecord *next; } VoltestRecord;
extern VoltestRecord *D_voltest_00400594;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/__entrypoint_func_voltest_400000.s")

void func_voltest_0040006C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_00400074.s")

#line 12 "src/modules/voltest.c"
/* Walk the volume-test list and set its 4 + 4 + 8 signed byte slots to -1.
 * Preserve the original list links and the two independent slot loops. */
void voltestResetByteSlots(void) {
    VoltestRecord *record = D_voltest_00400594;
    s32 index;
    while (record != NULL) {
        for (index = 0; index < 4; index++) {
            record->first[index] = -1;
            record->second[index] = -1;
        }
        for (index = 0; index < 8; index++) {
            record->third[index] = -1;
        }
        record = record->next;
    }
}
#line 13 "src/modules/voltest.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_00400194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_00400264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_004002FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_00400394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_0040044C.s")

