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

/*
 * Update the file allocation pointer, publish the eighteen query exports,
 * then allocate five parallel/auxiliary arrays and clear four controls.
 * Preserve allocation order and each reload of the shared capacity.
 * RE_UNKNOWN: Capacity sign/overflow, allocation failure, array backing
 * and provider lifetime are not validated by this initializer.
 */
#line 46 "src/modules/uvquery_rom.c"
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
/* Release the five default query arrays in original order; override storage is untouched.
 * RE_UNKNOWN: override storage ownership and lifetime need original caller proof. */
void uvQueryCleanup(void) {
    _uvMemFree(sQueryIntValues);
    _uvMemFree(sQueryFloatValues);
    _uvMemFree(sQueryFloatVectors);
    _uvMemFree(D_uvquery_rom_00400644);
    _uvMemFree(D_uvquery_rom_0040064C);
}
#line 84 "src/modules/uvquery_rom.c"

/* Return the shared float-array pointer without copying or allocating.
 * The QUERY initializer supplies this backing array; DOBJ/MODL callers retain
 * its address. No capacity, initialization or lifetime check occurs here.
 * RE_UNKNOWN: coordination with QUERY cleanup/reinitialization; callers must
 * not infer ownership or a nonnull/live allocation from this getter alone. */
#line 85 "src/modules/uvquery_rom.c"
f32 *uvQueryGetFloatValues(void) {
    return sQueryFloatValues;
}
#line 88 "src/modules/uvquery_rom.c"

/* Return the shared signed-word-array pointer without copying or allocating.
 * The QUERY initializer supplies the array and DOBJ/MODL callers retain its
 * address. Capacity and allocation state are not returned or checked here.
 * RE_UNKNOWN: caller bounds and QUERY cleanup/reinitialization lifetime;
 * returning this address does not transfer ownership. */
#line 89 "src/modules/uvquery_rom.c"
s32 *uvQueryGetIntValues(void) {
    return sQueryIntValues;
}
#line 92 "src/modules/uvquery_rom.c"

/* Return the shared Vec3F-array pointer without copying or allocating.
 * The QUERY initializer supplies the array; DOBJ/MODL callers retain its
 * address. This getter checks neither capacity nor allocation state.
 * RE_UNKNOWN: caller bounds and QUERY cleanup/reinitialization lifetime;
 * returning this address does not transfer ownership. */
#line 93 "src/modules/uvquery_rom.c"
Vec3F *uvQueryGetFloatVectors(void) {
    return sQueryFloatVectors;
}
#line 96 "src/modules/uvquery_rom.c"

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
 * Swap parallel entries on strict scalar comparisons, then trim trailing 2.0f.
 * RE_UNKNOWN: count bounds, array overlap and scalar domains need caller proof.
 * Existing source records the original name as _uvDbSortHits.
 */
/*
 * Swap parallel scalar, integer and vector entries on strict scalar less-
 * comparison, preserving pointer reloads and component store order. Trim
 * trailing 2.0f entries by decreasing the shared hit count.
 * RE_ORIGINAL_QUIRK: count >= capacity returns, but negative counts are
 * not rejected. Preserve the first scan and its UV_OLD-only near-equality
 * marking branch; the current native build retains the empty inner scan.
 * RE_UNKNOWN: Array extents/overlap, negative counts and nonfinite scalar
 * domains need caller proof; no stable-order or finite-input claim is made.
 */
#line 122 "src/modules/uvquery_rom.c"
void uvQueryDoSorting(void) {
    s32 firstIndex;
    s32 secondIndex;
    f32 savedVectorX;
    f32 savedVectorY;
    f32 savedVectorZ;
    s32 savedIntValue;
    f32 savedFloatValue;

    if (sQueryCount >= sQueryArraysCount) {
        return;
    }

    for (firstIndex = 0; firstIndex < sQueryCount; firstIndex++) {
        if (sQueryFloatValues[firstIndex] == 2.0f) {
            continue;
        }
        for (secondIndex = firstIndex + 1; secondIndex < sQueryCount; secondIndex++) {
#if UV_OLD
            if (FABS(sQueryFloatValues[firstIndex] - sQueryFloatValues[secondIndex]) < 0.001f) {
                sQueryFloatValues[firstIndex] = 2.0f;
                sQueryFloatValues[secondIndex] = 2.0f;
            }
#endif
        }
    }

    // Preserve strict scalar comparison and ordered parallel-array swaps.
    for (firstIndex = 0; firstIndex < sQueryCount; firstIndex++) {
        for (secondIndex = firstIndex; secondIndex < sQueryCount; secondIndex++) {
            // Preserve pointer reloads and the original component store order.
            if (sQueryFloatValues[secondIndex] < sQueryFloatValues[firstIndex]) {
                savedIntValue = sQueryIntValues[firstIndex];
                savedFloatValue = sQueryFloatValues[firstIndex];
                savedVectorX = sQueryFloatVectors[firstIndex].x;
                savedVectorY = sQueryFloatVectors[firstIndex].y;
                savedVectorZ = sQueryFloatVectors[firstIndex].z;
                sQueryIntValues[firstIndex] = sQueryIntValues[secondIndex];
                sQueryFloatValues[firstIndex] = sQueryFloatValues[secondIndex];
                sQueryFloatVectors[firstIndex].x = sQueryFloatVectors[secondIndex].x;
                sQueryFloatVectors[firstIndex].y = sQueryFloatVectors[secondIndex].y;
                sQueryFloatVectors[firstIndex].z = sQueryFloatVectors[secondIndex].z;
                sQueryIntValues[secondIndex] = savedIntValue;
                sQueryFloatValues[secondIndex] = savedFloatValue;
                sQueryFloatVectors[secondIndex].x = savedVectorX;
                sQueryFloatVectors[secondIndex].y = savedVectorY;
                sQueryFloatVectors[secondIndex].z = savedVectorZ;
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

/* Ignore id and consume repeated property-1/signed-word pairs, replacing
 * the same shared query control word each time. Zero or any other property
 * ends the scan without consuming a value for that property.
 * RE_ORIGINAL_QUIRK: the original body has no va_end or argument-count check.
 * RE_UNKNOWN: control-word meaning and caller-supplied variadic termination/types. */
#line 188 "src/modules/uvquery_rom.c"
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
#line 202 "src/modules/uvquery_rom.c"

/* Ignore id and consume repeated property-1/output-address pairs, writing
 * the same shared query control word to each unchecked signed-word output.
 * Zero or any other property stops without consuming an output address.
 * RE_ORIGINAL_QUIRK: the original body has no va_end or argument-count check.
 * RE_UNKNOWN: control meaning and valid variadic types, termination and outputs. */
#line 203 "src/modules/uvquery_rom.c"
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
#line 217 "src/modules/uvquery_rom.c"

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
