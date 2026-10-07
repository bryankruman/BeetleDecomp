// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

#define QUERY_ARRAYS_COUNT 100

void __entrypoint_func_uvquery_rom_400000(UvQuery_Exports *exports);
void uvQueryCleanup(void);
f32 *uvQueryGetFloatValues(void);
s32 *uvQueryGetIntValues(void);
Vec3F *uvQueryGetFloatVectors(void);
s32 uvQueryGetRecordCapacity(void);
s32 *uvQueryGetHitCountAddress(void);
s32 *uvQueryGetSharedWord40Address(void);
s32 uvQueryGetAuxiliaryArrayAddress(void);
void uvQueryDoSorting(void);
query_78 *uvQueryGetActiveRecordArray(void);
void uvQueryProps(s32 id, ...);
void uvQueryGetProps(s32 id, ...);
void uvQuerySetRecordArrayOverride(f32 *arg0, s32 arg1);
void uvQuerySetSecondaryRecordArray(s32 arg0, u16 arg1);
query_28 *uvQueryGetSecondaryRecordArray(void);
s32 *uvQueryGetSecondaryCountAddress(void);
s32 uvQueryGetSecondaryCount(void);
u16 uvQueryGetSecondaryValue(void);

s32 sQueryArraysCount = QUERY_ARRAYS_COUNT;

s32 D_uvquery_rom_00400624[] = { 0x00480000, __entrypoint_func_uvquery_rom_400000, 0 };

s32 *sQueryIntValues;
f32 *sQueryFloatValues;
Vec3F *sQueryFloatVectors;
s32 sQueryCount;
s32 D_uvquery_rom_00400640;
void *D_uvquery_rom_00400644;
s32 D_uvquery_rom_00400648;
query_78 *D_uvquery_rom_0040064C;
query_78 *D_uvquery_rom_00400650;
s32 D_uvquery_rom_00400654;
s32 D_uvquery_rom_00400658;
query_78 *D_uvquery_rom_0040065C;
u16 D_uvquery_rom_00400660;

void __entrypoint_func_uvquery_rom_400000(UvQuery_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvQueryCleanup = uvQueryCleanup;
    exports->uvQueryProps = uvQueryProps;
    exports->uvQueryGetFloatValues = uvQueryGetFloatValues;
    exports->uvQueryGetProps = uvQueryGetProps;
    exports->uvQueryGetIntValues = uvQueryGetIntValues;
    exports->uvQuerySetRecordArrayOverride = uvQuerySetRecordArrayOverride;
    exports->uvQueryGetFloatVectors = uvQueryGetFloatVectors;
    exports->uvQuerySetSecondaryRecordArray = uvQuerySetSecondaryRecordArray;
    exports->uvQueryGetRecordCapacity = uvQueryGetRecordCapacity;
    exports->uvQueryGetSecondaryRecordArray = uvQueryGetSecondaryRecordArray;
    exports->uvQueryGetHitCountAddress = uvQueryGetHitCountAddress;
    exports->uvQueryGetSecondaryCountAddress = uvQueryGetSecondaryCountAddress;
    exports->uvQueryGetSharedWord40Address = uvQueryGetSharedWord40Address;
    exports->uvQueryGetSecondaryCount = uvQueryGetSecondaryCount;
    exports->uvQueryGetAuxiliaryArrayAddress = uvQueryGetAuxiliaryArrayAddress;
    exports->uvQueryGetSecondaryValue = uvQueryGetSecondaryValue;
    exports->uvQueryDoSorting = uvQueryDoSorting;
    exports->uvQueryGetActiveRecordArray = uvQueryGetActiveRecordArray;
    sQueryIntValues = _uvMemAllocAlign8(sQueryArraysCount * sizeof(s32));
    sQueryFloatValues = _uvMemAllocAlign8(sQueryArraysCount * sizeof(f32));
    sQueryFloatVectors = _uvMemAllocAlign8(sQueryArraysCount * sizeof(Vec3F));
    D_uvquery_rom_00400644 = _uvMemAllocAlign8(sQueryArraysCount * sizeof(int));
    D_uvquery_rom_0040064C = _uvMemAllocAlign8(sQueryArraysCount * sizeof(query_78));
    D_uvquery_rom_00400650 = 0;
    D_uvquery_rom_00400654 = 0;
    D_uvquery_rom_0040065C = 0;
    D_uvquery_rom_00400660 = 0;
}

#line 77 "src/modules/uvquery_rom.c"
/* Release the five owned query arrays in original order; external override
 * storage remains caller-owned. */
void uvQueryCleanup(void) {
    _uvMemFree(sQueryIntValues);
    _uvMemFree(sQueryFloatValues);
    _uvMemFree(sQueryFloatVectors);
    _uvMemFree(D_uvquery_rom_00400644);
    _uvMemFree(D_uvquery_rom_0040064C);
}
#line 84 "src/modules/uvquery_rom.c"

f32 *uvQueryGetFloatValues(void) {
    return sQueryFloatValues;
}

s32 *uvQueryGetIntValues(void) {
    return sQueryIntValues;
}

Vec3F *uvQueryGetFloatVectors(void) {
    return sQueryFloatVectors;
}

#line 97 "src/modules/uvquery_rom.c"
/* Return base capacity, limited by the supplied override count when
 * an external record array is active. Preserve original signed comparison. */
s32 uvQueryGetRecordCapacity(void) {
    if (D_uvquery_rom_00400650 != NULL) {
        return (D_uvquery_rom_00400654 < sQueryArraysCount) ? D_uvquery_rom_00400654
                                                            : sQueryArraysCount;
    }
    return sQueryArraysCount;
}
#line 104 "src/modules/uvquery_rom.c"

#line 105 "src/modules/uvquery_rom.c"
/* Return writable storage for the shared query hit count. */
s32 *uvQueryGetHitCountAddress(void) {
    return &sQueryCount;
}
#line 108 "src/modules/uvquery_rom.c"

#line 109 "src/modules/uvquery_rom.c"
/* Return writable query word 0x40; its detailed role remains unproven. */
s32 *uvQueryGetSharedWord40Address(void) {
    return &D_uvquery_rom_00400640;
}
#line 112 "src/modules/uvquery_rom.c"

#line 113 "src/modules/uvquery_rom.c"
/* Return the auxiliary four-byte-per-entry array address through the
 * original integer ABI; element meaning remains unproven. */
s32 uvQueryGetAuxiliaryArrayAddress(void) {
    return D_uvquery_rom_00400644;
}
#line 116 "src/modules/uvquery_rom.c"

/*
 * Sort values from the query arrays using a selection sort algorithm
 *
 * original name: _uvDbSortHits
 */
void uvQueryDoSorting(void) {
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    s32 intVal;
    f32 floatVal;

    if (sQueryCount >= sQueryArraysCount) {
        return;
    }

    for (i = 0; i < sQueryCount; i++) {
        if (sQueryFloatValues[i] == 2.0f) {
            continue;
        }
        for (j = i + 1; j < sQueryCount; j++) {
#if UV_OLD
            if (FABS(sQueryFloatValues[i] - sQueryFloatValues[j]) < 0.001f) {
                sQueryFloatValues[i] = 2.0f;
                sQueryFloatValues[j] = 2.0f;
            }
#endif
        }
    }

    // Sort values from smallest to largest
    for (i = 0; i < sQueryCount; i++) {
        for (j = i; j < sQueryCount; j++) {
            // Sort using the float values
            if (sQueryFloatValues[j] < sQueryFloatValues[i]) {
                intVal = sQueryIntValues[i];
                floatVal = sQueryFloatValues[i];
                x = sQueryFloatVectors[i].x;
                y = sQueryFloatVectors[i].y;
                z = sQueryFloatVectors[i].z;
                sQueryIntValues[i] = sQueryIntValues[j];
                sQueryFloatValues[i] = sQueryFloatValues[j];
                sQueryFloatVectors[i].x = sQueryFloatVectors[j].x;
                sQueryFloatVectors[i].y = sQueryFloatVectors[j].y;
                sQueryFloatVectors[i].z = sQueryFloatVectors[j].z;
                sQueryIntValues[j] = intVal;
                sQueryFloatValues[j] = floatVal;
                sQueryFloatVectors[j].x = x;
                sQueryFloatVectors[j].y = y;
                sQueryFloatVectors[j].z = z;
            }
        }
    }

    while (sQueryCount != 0) {
        if (sQueryFloatValues[sQueryCount - 1] != 2.0f) {
            break;
        }
        sQueryCount--;
    }
}

#line 181 "src/modules/uvquery_rom.c"
/* Return the supplied external record array or the owned default array. */
query_78 *uvQueryGetActiveRecordArray(void) {
    if (D_uvquery_rom_00400650 != NULL) {
        return D_uvquery_rom_00400650;
    }
    return D_uvquery_rom_0040064C;
}
#line 187 "src/modules/uvquery_rom.c"

void uvQueryProps(s32 id, ...) {
    s32 prop;
    va_list args;

    va_start(args, id);

    while (TRUE) {
        prop = va_arg(args, s32);
        if ((prop == 0) || (prop != 1)) {
            break;
        }
        D_uvquery_rom_00400648 = va_arg(args, s32);
    }
}

void uvQueryGetProps(s32 id, ...) {
    s32 prop;
    va_list args;

    va_start(args, id);

    while (TRUE) {
        prop = va_arg(args, s32);
        if ((prop == 0) || (prop != 1)) {
            break;
        }
        *va_arg(args, s32 *) = D_uvquery_rom_00400648;
    }
}

#line 218 "src/modules/uvquery_rom.c"
/* Store an external record-array address and its count. Preserve the
 * historical float-pointer parameter ABI; no allocation or copying occurs. */
void uvQuerySetRecordArrayOverride(f32 *records, s32 count) {
    D_uvquery_rom_00400650 = records;
    D_uvquery_rom_00400654 = count;
}
#line 222 "src/modules/uvquery_rom.c"

#line 223 "src/modules/uvquery_rom.c"
/* Store the secondary query-array address word and its 16-bit associated value. */
void uvQuerySetSecondaryRecordArray(s32 recordsAddress, u16 value) {
    D_uvquery_rom_0040065C = recordsAddress;
    D_uvquery_rom_00400660 = value;
}
#line 227 "src/modules/uvquery_rom.c"

#line 228 "src/modules/uvquery_rom.c"
/* Return the secondary query-array address through the original pointer ABI. */
query_28 *uvQueryGetSecondaryRecordArray(void) {
    return D_uvquery_rom_0040065C;
}
#line 231 "src/modules/uvquery_rom.c"

#line 232 "src/modules/uvquery_rom.c"
/* Return writable storage for the shared secondary query count. */
s32 *uvQueryGetSecondaryCountAddress(void) {
    return &D_uvquery_rom_00400658;
}
#line 235 "src/modules/uvquery_rom.c"

#line 236 "src/modules/uvquery_rom.c"
/* Return the shared secondary query count. */
s32 uvQueryGetSecondaryCount(void) {
    return D_uvquery_rom_00400658;
}
#line 239 "src/modules/uvquery_rom.c"

#line 240 "src/modules/uvquery_rom.c"
/* Return the stored 16-bit secondary query value. */
u16 uvQueryGetSecondaryValue(void) {
    return D_uvquery_rom_00400660;
}
#line 243 "src/modules/uvquery_rom.c"
