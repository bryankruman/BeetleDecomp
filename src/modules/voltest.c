// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[8]; s32 objectId; } VoltestObject;
typedef struct { u8 unk00[0x40]; s32 (*get)(VoltestObject **); } VoltestObjectExports;
typedef struct { u8 unk00[0x28]; void (*getPosm)(s32, s32, Mtx4F *); } VoltestDobjExports;
extern void *D_voltest_00400598, *gUvDobjExports;
typedef struct { u8 unk00[0x14]; s32 (*getScreens)(void **); } VoltestScreenExports;
extern VoltestScreenExports *gScrnExports;
s32 func_voltest_0040044C(void *, void *);
typedef struct VoltestRecord { void *testData; s8 first[4]; s8 second[4]; s8 third[8]; struct VoltestRecord *next; } VoltestRecord;
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
/* Return signed-byte test results, refreshing -1 entries through the matching
 * test; null records and unknown kinds return zero. Cache reads are unchecked.
 * RE_UNKNOWN: index bounds/test meaning; inspect original callers and test target. */
/*
 * Select one of three signed-byte caches for kinds 0 through 2. Refresh only
 * a byte equal to -1, then reread and return that byte with sign extension.
 * A null record or unsupported kind returns zero. RE_UNKNOWN: the caller
 * must supply a valid cache index; this wrapper performs no index-range
 * check.
 */
#line 17 "src/modules/voltest.c"
s32 voltestGetCachedResult(VoltestRecord *record, s32 cacheKind, s32 slotIndex) {
    if (record == NULL) return 0;
    switch (cacheKind) {
    case 0:
        if (record->first[slotIndex] == -1) { voltestRefreshFirstScreenSlot(record, slotIndex); }
        return record->first[slotIndex];
    case 1:
        if (record->second[slotIndex] == -1) { voltestRefreshSecondScreenSlot(record, slotIndex); }
        return record->second[slotIndex];
    case 2:
        if (record->third[slotIndex] == -1) { voltestRefreshObjectPositionSlot(record, slotIndex); }
        return record->third[slotIndex];
    }
    return 0;
}
#line 15 "src/modules/voltest.c"

#line 16 "src/modules/voltest.c"
/* Refresh the first screen cache using data at 0x1D8 and loaded testData.
 * Keep invalid-index writes. RE_UNKNOWN: index/count and loaded data extent/lifetime
 * need original assets, screen getter and callers; no complete data type inferred. */
void voltestRefreshFirstScreenSlot(VoltestRecord *record, s32 index) {
    void *screens[4];
    s32 count = gScrnExports->getScreens(screens);
    if (index < 0 || index >= count) record->first[index] = 0;
    else if (func_voltest_0040044C(record->testData, (u8 *)screens[index] + 0x1D8) != 0) record->first[index] = 1;
    else record->first[index] = 0;
}
#line 17 "src/modules/voltest.c"

#line 18 "src/modules/voltest.c"
/* Refresh the second screen cache using data at 0x184 and loaded testData.
 * Keep invalid-index writes. RE_UNKNOWN: index/count and loaded data extent/lifetime
 * need original assets, screen getter and callers; no complete data type inferred. */
/*
 * Obtain the live screen list and test the selected screen bytes at offset
 * 0x184 against the stored test data. Write 1 for a nonzero helper result
 * and 0 otherwise. A negative index or one outside the provider count still
 * writes zero to the caller-selected cache slot. RE_UNKNOWN: the provider
 * count is not clamped to the local four-pointer array here, and cache-index
 * safety and the screen data shape remain caller/provider contracts.
 */
#line 21 "src/modules/voltest.c"
void voltestRefreshSecondScreenSlot(VoltestRecord *record, s32 slotIndex) {
    void *screens[4];
    s32 screenCount = gScrnExports->getScreens(screens);
    if (slotIndex < 0 || slotIndex >= screenCount) record->second[slotIndex] = 0;
    else if (func_voltest_0040044C(record->testData, (u8 *)screens[slotIndex] + 0x184) != 0) record->second[slotIndex] = 1;
    else record->second[slotIndex] = 0;
}
#line 19 "src/modules/voltest.c"

#line 20 "src/modules/voltest.c"
/* Refresh the object-position cache; preserve the original invalid-index writes.
 * RE_UNKNOWN: index/count and testData extent/lifetime need original assets/getter/callers. */
/*
 * Obtain the live object list, then test the selected object translation
 * against the stored test data. Write 1 for a nonzero helper result and 0
 * otherwise. A negative index or one outside the provider count still writes
 * zero to the caller-selected cache slot. RE_UNKNOWN: the provider count is
 * not clamped to the local eight-pointer array here, and cache-index safety
 * and test-data shape remain caller/provider contracts.
 */
#line 22 "src/modules/voltest.c"
void voltestRefreshObjectPositionSlot(VoltestRecord *record, s32 slotIndex) {
    VoltestObject *objects[8];
    Mtx4F objectTransform;
    s32 objectCount = ((VoltestObjectExports *)D_voltest_00400598)->get(objects);
    if (slotIndex < 0 || slotIndex >= objectCount) record->third[slotIndex] = 0;
    else {
        ((VoltestDobjExports *)gUvDobjExports)->getPosm(objects[slotIndex]->objectId, 0, &objectTransform);
        if (func_voltest_0040044C(record->testData, &objectTransform.m[3][0]) != 0) record->third[slotIndex] = 1;
        else record->third[slotIndex] = 0;
    }
}
#line 21 "src/modules/voltest.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/voltest/func_voltest_0040044C.s")

