// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[8]; s32 objectId; } VoltestObject;
typedef struct { u8 unk00[0x40]; s32 (*get)(VoltestObject **); } VoltestObjectExports;
typedef struct { u8 unk00[0x28]; void (*getPosm)(s32, s32, Mtx4F *); } VoltestDobjExports;
extern void *D_voltest_00400598, *gUvDobjExports;
typedef struct { u8 unk00[0x14]; s32 (*getScreens)(void **); } VoltestScreenExports;
extern VoltestScreenExports *gScrnExports;
s32 func_voltest_0040044C(s32, void *);
typedef struct VoltestRecord { s32 unk00; s8 first[4]; s8 second[4]; s8 third[8]; struct VoltestRecord *next; } VoltestRecord;
extern VoltestRecord *D_voltest_00400594;
void voltestRefreshFirstScreenSlot(VoltestRecord *, s32);
void voltestRefreshSecondScreenSlot(VoltestRecord *, s32);
void voltestRefreshObjectPositionSlot(VoltestRecord *record, s32 index);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/__entrypoint_func_voltest_400000.s")

#line 17 "src/modules/voltest.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_voltest_0040006C(void) {
}
#line 19 "src/modules/voltest.c"

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

#line 14 "src/modules/voltest.c"
/* Return one of the three signed-byte visibility caches, refreshing -1
 * entries through the matching test. Null records and unknown kinds return
 * zero. The original cache access precedes index validation; callers own bounds. */
s32 voltestGetCachedResult(VoltestRecord *record, s32 kind, s32 index) {
    if (record == NULL) return 0;
    switch (kind) {
    case 0:
        if (record->first[index] == -1) { voltestRefreshFirstScreenSlot(record, index); }
        return record->first[index];
    case 1:
        if (record->second[index] == -1) { voltestRefreshSecondScreenSlot(record, index); }
        return record->second[index];
    case 2:
        if (record->third[index] == -1) { voltestRefreshObjectPositionSlot(record, index); }
        return record->third[index];
    }
    return 0;
}
#line 15 "src/modules/voltest.c"

#line 16 "src/modules/voltest.c"
/* Refresh the first per-screen signed-byte cache using screen data at 0x1D8.
 * The original invalid-index path still writes first[index]; callers must keep
 * indices within the four-slot record. Preserve this unresolved caller contract. */
void voltestRefreshFirstScreenSlot(VoltestRecord *record, s32 index) {
    void *screens[4];
    s32 count = gScrnExports->getScreens(screens);
    if (index < 0 || index >= count) record->first[index] = 0;
    else if (func_voltest_0040044C(record->unk00, (u8 *)screens[index] + 0x1D8) != 0) record->first[index] = 1;
    else record->first[index] = 0;
}
#line 17 "src/modules/voltest.c"

#line 18 "src/modules/voltest.c"
/* Refresh the second per-screen signed-byte cache using screen data at 0x184.
 * The original invalid-index path still writes second[index]; callers must keep
 * indices within the four-slot record. Preserve this unresolved caller contract. */
void voltestRefreshSecondScreenSlot(VoltestRecord *record, s32 index) {
    void *screens[4];
    s32 count = gScrnExports->getScreens(screens);
    if (index < 0 || index >= count) record->second[index] = 0;
    else if (func_voltest_0040044C(record->unk00, (u8 *)screens[index] + 0x184) != 0) record->second[index] = 1;
    else record->second[index] = 0;
}
#line 19 "src/modules/voltest.c"

#line 20 "src/modules/voltest.c"
/* Refresh the eight-slot object cache using each object handle and its matrix translation.
 * The original invalid-index path still writes third[index]; callers own bounds. */
void voltestRefreshObjectPositionSlot(VoltestRecord *record, s32 index) {
    VoltestObject *objects[8];
    Mtx4F matrix;
    s32 count = ((VoltestObjectExports *)D_voltest_00400598)->get(objects);
    if (index < 0 || index >= count) record->third[index] = 0;
    else {
        ((VoltestDobjExports *)gUvDobjExports)->getPosm(objects[index]->objectId, 0, &matrix);
        if (func_voltest_0040044C(record->unk00, &matrix.m[3][0]) != 0) record->third[index] = 1;
        else record->third[index] = 0;
    }
}
#line 21 "src/modules/voltest.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_0040044C.s")

