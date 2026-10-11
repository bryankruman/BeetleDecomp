// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
/* Address storage only; this view does not assign callable slot signatures. */
typedef struct { u32 slots[30]; } TdataCallbackAddresses;
void func_tdata_0040018C(void);
void tdataRefreshSharedData(void);
void func_tdata_004008C4(void);
s32 func_tdata_004009A8(void);
void tdataPrependRecordLink(void *);
void *tdataAllocateScalarPair(f32, f32);
void tdataSetSharedParameters(s32, s32);
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern UvFVec_Rom_Exports *gUvFvecExports;
#include "uvfvec_rom.h"
typedef struct { u8 prefix[0x30]; Vec3F position; } TdataPositionState;
typedef struct { s32 prefix; f32 value; } TdataScalarState;
typedef struct { Vec3F minimum, maximum; f32 lower, upper, target; } TdataScalarRegion;
#include "uvfvec_rom.h"
extern Vec3F D_tdata_004029B0;
typedef struct { s16 group; s16 index; } TdataHandle;
#include "uvfvec_rom.h"
typedef struct { u8 unk00[0xC]; Vec3F vector0C, vector18; u8 unk24[0x14]; } TdataRecord;
typedef struct { s32 firstRecord; s32 count; } TdataGroup;
typedef struct { u8 unk00[4]; s32 groupCount; TdataRecord *records; TdataGroup *groups; } TdataBank;

extern s32 D_tdata_004029E0;
/*__SEEDEXTERNS__*/
extern u8 D_tdata_004029D4;
extern s32 D_tdata_004029DC;
typedef struct { u8 unk00[0x68]; f32 (*directionAngle)(f32, f32); } TdataMiscAngleExports;
extern TdataMiscAngleExports *gMiscExports;
void func_tdata_00400194();
void func_tdata_00400234(TdataScalarState *, f32, s32);
TdataHandle *func_tdata_00400738(TdataHandle *, void *, Vec3F *, Vec3F *);
void tdataResetProgressRecord();
void func_tdata_004008B8();
void func_tdata_004008D4();
void func_tdata_004009B0();
void func_tdata_00400DB4();
s32 tdataGetTotalRecordCount(void);
Vec3F tdataGetLinearRecordVector0C(s32 linearIndex);
void func_tdata_00401344();
s32 tdataGetClampedHandleWindow(TdataHandle *, TdataHandle *, TdataHandle *, s32, s32);
TdataRecord *tdataBuildMatrixFromQuery(void *, Mtx4F *);
f32 tdataGetLinearRecordValue(TdataHandle handle);
f32 tdataGetRecordDirectionAngle(TdataHandle handle);
f32 tdataGetRecordVectorZ(TdataHandle handle);
void func_tdata_00401638();
f32 tdataReturnZeroScalar(s32 unusedWord);
TdataHandle *tdataHandleFromLinearIndex(TdataHandle *output, s32 index);
s32 func_tdata_00401904(TdataHandle);
extern f32 *D_tdata_004029E4;
void func_tdata_00401998();
TdataHandle tdataPreviousHandle(TdataHandle handle);
TdataRecord *tdataGetRecordByHandle(TdataHandle handle);
/* Minimum original access views used by the scalar-link query.
 * RE_UNKNOWN: complete state/link allocation, physical roles and units need
 * original producers/callers; these prefixes do not establish capacity. */
typedef struct {
    TdataHandle handle;
    u8 opaque04[8];
    u16 fractionWord0C;
} TdataScalarLinkStateView;
typedef struct TdataScalarLinkView {
    f32 first;
    f32 second;
    f32 tolerance;
    f32 lower;
    f32 upper;
    f32 target;
    struct TdataScalarLinkView *next;
} TdataScalarLinkView;
extern f32 D_tdata_00402968;
void tdataApplyFirstMatchingScalarLink(TdataScalarLinkStateView *, f32 *);
#line 60 "src/modules/tdata.c"
void func_tdata_00401CBC();
void func_tdata_00401D38();
void func_tdata_00402388();
void tdataApplyScalarRegions(TdataPositionState *position, TdataScalarState *state);
void func_tdata_00400DB4(void);
extern s32 D_tdata_004029D8;
extern s32 D_tdata_004029F0;
extern s32 D_tdata_004029F4;
#line 68 "src/modules/tdata.c"
/*
 * Update the allocation pointer and publish thirty original callback addresses
 * at offsets 0x00 through 0x74. Preserve the nonascending publication order,
 * including slot 0 after slots 1..9 and the interleaved later slot groups.
 * Publishing addresses does not invoke callbacks or initialize shared banks.
 * RE_UNKNOWN: Opaque callback signatures and writable export-storage lifetime
 * remain loader/consumer obligations; no new callable types are inferred.
 */
#line 74 "src/modules/tdata.c"
void __entrypoint_func_tdataInitializeModuleExports(TdataCallbackAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->slots[1] = (u32)func_tdata_00400194; /* 0x04 */
    exports->slots[2] = (u32)func_tdata_00400234; /* 0x08 */
    exports->slots[3] = (u32)func_tdata_00400738; /* 0x0C */
    exports->slots[4] = (u32)tdataResetProgressRecord; /* 0x10 */
    exports->slots[5] = (u32)tdataRefreshSharedData; /* 0x14 */
    exports->slots[6] = (u32)func_tdata_004008B8; /* 0x18 */
    exports->slots[7] = (u32)func_tdata_004008C4; /* 0x1C */
    exports->slots[8] = (u32)func_tdata_004009A8; /* 0x20 */
    exports->slots[9] = (u32)func_tdata_004009B0; /* 0x24 */
    exports->slots[0] = (u32)func_tdata_0040018C; /* 0x00 */
    exports->slots[10] = (u32)tdataGetTotalRecordCount; /* 0x28 */
    exports->slots[20] = (u32)func_tdata_00401904; /* 0x50 */
    exports->slots[11] = (u32)tdataGetLinearRecordVector0C; /* 0x2C */
    exports->slots[21] = (u32)func_tdata_00401998; /* 0x54 */
    exports->slots[12] = (u32)func_tdata_00401344; /* 0x30 */
    exports->slots[22] = (u32)tdataPreviousHandle; /* 0x58 */
    exports->slots[13] = (u32)tdataBuildMatrixFromQuery; /* 0x34 */
    exports->slots[23] = (u32)tdataGetRecordByHandle; /* 0x5C */
    exports->slots[14] = (u32)tdataGetLinearRecordValue; /* 0x38 */
    exports->slots[24] = (u32)tdataPrependRecordLink; /* 0x60 */
    exports->slots[15] = (u32)tdataGetRecordDirectionAngle; /* 0x3C */
    exports->slots[25] = (u32)tdataAllocateScalarPair; /* 0x64 */
    exports->slots[16] = (u32)tdataGetRecordVectorZ; /* 0x40 */
    exports->slots[26] = (u32)func_tdata_00401CBC; /* 0x68 */
    exports->slots[17] = (u32)func_tdata_00401638; /* 0x44 */
    exports->slots[27] = (u32)func_tdata_00401D38; /* 0x6C */
    exports->slots[18] = (u32)tdataReturnZeroScalar; /* 0x48 */
    exports->slots[28] = (u32)tdataSetSharedParameters; /* 0x70 */
    exports->slots[19] = (u32)tdataHandleFromLinearIndex; /* 0x4C */
    exports->slots[29] = (u32)tdataApplyScalarRegions; /* 0x74 */
}
#line 69 "src/modules/tdata.c"

#line 56 "src/modules/tdata.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_tdata_0040018C(void) {
}
#line 58 "src/modules/tdata.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400738.s")

#line 61 "src/modules/tdata.c"
/* Clear the group/index and halfword 0xC, then the two progress scalars
 * in original store order. The complete record layout remains unresolved. */
void tdataResetProgressRecord(void *record) {
    *(s16 *)((u8 *)record + 0x0) = 0;
    *(s16 *)((u8 *)record + 0x2) = 0;
    *(s16 *)((u8 *)record + 0xC) = 0;
    *(f32 *)((u8 *)record + 0x8) = 0.0f;
    *(f32 *)((u8 *)record + 0x4) = 0.0f;
}
#line 68 "src/modules/tdata.c"

#line 69 "src/modules/tdata.c"
/* Forward the refresh request to the original shared track-data helper. */
void tdataRefreshSharedData(void) {
    func_tdata_00400DB4();
}
#line 72 "src/modules/tdata.c"

#line 73 "src/modules/tdata.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_tdata_004008B8(s32 a0, s32 a1) {
}
#line 75 "src/modules/tdata.c"

#line 76 "src/modules/tdata.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_tdata_004008C4(void) {
}
#line 78 "src/modules/tdata.c"

#line 79 "src/modules/tdata.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_tdata_004008CC(void) {
}
#line 81 "src/modules/tdata.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_004008D4.s")

#line 84 "src/modules/tdata.c"
/* Return integer zero unconditionally.
 * RE_UNKNOWN: caller/export role and meaning of this constant result. */
s32 func_tdata_004009A8(void) {
    return 0;
}
#line 87 "src/modules/tdata.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_004009B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400DB4.s")

#line 89 "src/modules/tdata.c"
/*
 * Sum each group count in the shared bank and return zero when the unsigned
 * group-count snapshot is zero. The bank pointer and group-count value are
 * read once; group records advance by their original eight-byte stride.
 * RE_ORIGINAL_QUIRK: The signed groupCount field is interpreted as u32.
 * A negative field therefore requests a large traversal; the sum has no
 * overflow guard. Preserve the existing addition and comparison types.
 * RE_UNKNOWN: Bank/group lifetime, nonnegative counts, readable group extent
 * and representable totals require the bank producer and all callers.
 */
#line 90 "src/modules/tdata.c"
s32 tdataGetTotalRecordCount(void) {
    s32 totalRecords;
    u32 groupIndex;
    TdataBank *bank;
    u32 numberOfGroups;
    TdataGroup *group;
    groupIndex = totalRecords = 0;
    bank = (TdataBank *)D_tdata_004029DC;
    numberOfGroups = bank->groupCount;
    if (numberOfGroups != 0) {
        group = bank->groups;
        do {
            totalRecords += group->count;
            groupIndex++;
            group++;
        } while (groupIndex < numberOfGroups);
    }
    return totalRecords;
}
#line 115 "src/modules/tdata.c"

#line 116 "src/modules/tdata.c"
/* Return the three-component vector at record offset 0x0C for a
 * linear index, or the original shared fallback vector when lookup is null.
 * Preserve the original struct-return ABI and group/index conversion. */
Vec3F tdataGetLinearRecordVector0C(s32 linearIndex) {
    Vec3F fallback = D_tdata_004029B0;
    TdataHandle handle;
    TdataRecord *record;
    tdataHandleFromLinearIndex(&handle, linearIndex);
    record = tdataGetRecordByHandle(handle);
    if (record == NULL) return fallback;
    return record->vector0C;
}
#line 117 "src/modules/tdata.c"

#line 118 "src/modules/tdata.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_tdata_00401344(s32 a0, s32 a1, s32 a2) {
}
#line 120 "src/modules/tdata.c"

#line 121 "src/modules/tdata.c"
/* Adjust only lower<=0 to zero and upper>=count-1 to count-1; center is unchanged.
 * Return upper-lower after handle conversion. RE_UNKNOWN: valid index/count/width
 * and output/alias domains need original callers, count producers and converters. */
s32 tdataGetClampedHandleWindow(TdataHandle *lowerOutput, TdataHandle *centerOutput, TdataHandle *upperOutput, s32 centerIndex, s32 width)
{
  s32 lower;
  s32 upper;
  s32 start;
  s32 end;
  s32 lastIndex;
  start = centerIndex - (width / 2);
  lower = start;
  end = start + width;
  upper = end;
  if (start <= 0)
  {
    lower = 0;
  }
  lastIndex = (*((s32 *) (&D_tdata_004029E0))) - 1;
  if (end >= lastIndex)
  {
    upper = lastIndex;
  }
  tdataHandleFromLinearIndex(lowerOutput, lower);
  tdataHandleFromLinearIndex(centerOutput, centerIndex);
  tdataHandleFromLinearIndex(upperOutput, upper);
  return upper - lower;
}
#line 146 "src/modules/tdata.c"

#line 147 "src/modules/tdata.c"
/* Initialize the matrix, resolve the query's group/index handle and
 * obtain helper 00400738's translation and record-vector outputs. Cross
 * record vector 0x18 with the helper vector for row zero; copy vector 0x18
 * into row one and the helper vector into row two. Return the selected record.
 * RE_ORIGINAL_QUIRK: preserve three translation aggregate copies (matrix,
 * local, matrix) and the unchecked record lookup result.
 * RE_UNKNOWN: query field meanings, coordinate space/units, basis validity,
 * allocation/alias guarantees and historical explicit-versus-hidden handle
 * output convention. The helper's pointer view describes the observed four
 * machine arguments and returned output address, not a proven original C
 * spelling. Audit original helper 00400738, query producers and callers
 * before assigning physical names or changing ABI, copies or failure behavior. */
TdataRecord *tdataBuildMatrixFromQuery(void *query, Mtx4F *matrix) {
    Vec3F rowTwo;
    Vec3F translation;
    Vec3F *rowOne;
    Vec3F rowZero;
    TdataHandle handle;
    TdataRecord *record;
    Vec3F *matrixTranslation;

    gUvFmtxExports->uvMat4SetIdentity(matrix);
    func_tdata_00400738(&handle, query, &translation, &rowTwo);
    record = tdataGetRecordByHandle(handle);
    rowOne = &record->vector18;
    gUvFvecExports->uvVec3FCross(&rowZero, rowOne, &rowTwo);
    *(Vec3F *)matrix->m[0] = rowZero;
    matrixTranslation = (Vec3F *)matrix->m[3];
    *(Vec3F *)matrix->m[1] = *rowOne;
    *(Vec3F *)matrix->m[2] = rowTwo;
    *matrixTranslation = translation;
    translation = *matrixTranslation;
    *matrixTranslation = translation;
    return record;
}
#line 148 "src/modules/tdata.c"

#line 149 "src/modules/tdata.c"
/*
 * Convert the packed handle with helper 00401904. Return the indexed shared
 * float when the signed result is below the shared count; otherwise return zero.
 * RE_ORIGINAL_QUIRK: There is no lower-bound test, so a negative converter
 * result still indexes the array when it is below the count.
 * RE_UNKNOWN: The converter contract, valid count/array extent and lifetime
 * must be proved from the original converter and record-storage producers.
 */
#line 152 "src/modules/tdata.c"
f32 tdataGetLinearRecordValue(TdataHandle handle) {
    s32 index = func_tdata_00401904(handle);
    if (index < D_tdata_004029E0) {
        return D_tdata_004029E4[index];
    }
    return 0.0f;
}
#line 150 "src/modules/tdata.c"

#line 151 "src/modules/tdata.c"
/*
 * Resolve the handle and return zero only when the record lookup returns NULL.
 * Otherwise pass the negated vector18 X component and unchanged Y component
 * to MISC export 0x68, retaining the floating negation and callback ordering.
 * RE_UNKNOWN: The lookup rejects only -1 components; other bounds, record
 * lifetime, vector coordinate frame and the angle helper units remain external.
 * No angle normalization or additional invalid-handle handling is introduced.
 */
#line 153 "src/modules/tdata.c"
f32 tdataGetRecordDirectionAngle(TdataHandle handle) {
    TdataRecord *record = tdataGetRecordByHandle(handle);
    if (record == NULL) {
        return 0.0f;
    }
    return gMiscExports->directionAngle(-record->vector18.x, record->vector18.y);
}
#line 152 "src/modules/tdata.c"

#line 151 "src/modules/tdata.c"
/*
 * Resolve the handle and return vector18.z, or zero when the lookup returns NULL.
 * RE_ORIGINAL_QUIRK: Preserve the local float copy and the packed-handle ABI.
 * RE_UNKNOWN: The lookup accepts nonsentinel out-of-range components without
 * a bound check; valid bank/record lifetime and index ranges remain caller-owned.
 */
#line 152 "src/modules/tdata.c"
f32 tdataGetRecordVectorZ(TdataHandle handle) {
    TdataRecord *record;
    f32 value;
    record = tdataGetRecordByHandle(handle);
    if (record == NULL) {
        return 0.0f;
    }
    value = record->vector18.z;
    return value;
}
#line 152 "src/modules/tdata.c"
/*
 * Look up the current packed handle, then interpolate neighboring record18
 * triples across the u16 fraction midpoint. Normalize only when a neighbor
 * exists; otherwise copy the current triple unchanged. Store MISC68(-x,y)
 * before z, retaining lookup reloads and callback/output alias ordering.
 * RE_ORIGINAL_QUIRK: current lookup is dereferenced without a NULL guard;
 * normalization status is ignored. Reachability of invalid inputs is unknown.
 * RE_UNKNOWN: original state/record extents, handle/group/index and fraction
 * producers, vector frame and angle units, callback mutation/alias domains and
 * output lifetime. Resolve original link/record writers and all callers.
 * Readable C remains parked:552 native versus544 bytes,119 differing words
 * and unequal full relocation records. Explicit shared returned-handle storage
 * produces the same136 words and17 records as the nested-call draft; no further
 * source-shape variants are justified. Native-equivalent C and full packed
 * module/ROM validation remain required; original assembly preserves behavior.
 */
#line 153 "src/modules/tdata.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401638.s")

#line 155 "src/modules/tdata.c"
#line 155 "src/modules/tdata.c"

/* Return float zero unconditionally, retaining the unused s32 argument.
 * RE_UNKNOWN: caller/export role and meaning of this constant result. */
f32 tdataReturnZeroScalar(s32 unusedWord) {
    return 0.0f;
}
#line 160 "src/modules/tdata.c"
#line 158 "src/modules/tdata.c"

#line 158 "src/modules/tdata.c"
/*
 * Start at group zero, narrow the supplied linear index into the signed-halfword
 * handle field, and subtract successive group counts until that narrowed index
 * is below the current count. Copy the handle to output and return output.
 * RE_ORIGINAL_QUIRK: Each subtraction and group increment narrows back to s16.
 * There is no bank, group-limit, negative-input or output-pointer check; even
 * an initially negative index still reads the first group count.
 * RE_UNKNOWN: Representable indices, traversable group/count storage, output
 * extent and aliasing require producers and the clamped-window/query callers.
 */
#line 161 "src/modules/tdata.c"
TdataHandle *tdataHandleFromLinearIndex(TdataHandle *output, s32 index) {
    TdataHandle handle;
    TdataBank *bank = (TdataBank *)D_tdata_004029DC;
    handle.group = 0;
    handle.index = index;
    while (handle.index >= bank->groups[handle.group].count) {
        handle.index -= bank->groups[handle.group].count;
        handle.group++;
    }
    *output = handle;
    return output;
}
#line 159 "src/modules/tdata.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401904.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401998.s")

#line 164 "src/modules/tdata.c"
/*
 * Decrement the signed-halfword record index. If the narrowed result is negative,
 * decrement the group and, unless it becomes -1, select that group count minus one.
 * Return the aggregate through the original ABI, preserving every s16 narrowing.
 * RE_ORIGINAL_QUIRK: Group -1 is tested only after a crossing. Empty groups,
 * other negative groups and halfword wrap receive no extra handling.
 * RE_UNKNOWN: Valid initial handles, count ranges and bank/group lifetime must
 * be established by callers; no clamp or multi-group skip is added.
 */
#line 167 "src/modules/tdata.c"
TdataHandle tdataPreviousHandle(TdataHandle handle) {
    handle.index--;
    if (handle.index < 0) {
        handle.group--;
        if (handle.group != -1) {
            handle.index = ((TdataBank *)D_tdata_004029DC)->groups[handle.group].count - 1;
        }
    }
    return handle;
}
#line 165 "src/modules/tdata.c"

#line 166 "src/modules/tdata.c"
/*
 * Return NULL when either signed-halfword component is exactly -1. Otherwise
 * add the selected group firstRecord to the record index and return the address
 * in the original 56-byte record array; no record contents are copied.
 * RE_ORIGINAL_QUIRK: Other negative values and upper bounds are unchecked.
 * RE_UNKNOWN: Complete bank/group/record extents, addition range, returned-pointer
 * lifetime and writable/aliased uses require the original bank producer/callers.
 */
#line 168 "src/modules/tdata.c"
TdataRecord *tdataGetRecordByHandle(TdataHandle handle) {
    TdataBank *bank;
    if (handle.group == -1 || handle.index == -1) {
        return NULL;
    }
    bank = (TdataBank *)D_tdata_004029DC;
    return &bank->records[bank->groups[handle.group].firstRecord + handle.index];
}
#line 167 "src/modules/tdata.c"

#line 168 "src/modules/tdata.c"

/* Apply the first scalar link whose strict two-component tolerance tests
 * and lower/upper bounds contain the original derived record value. Snapshot
 * the packed handle before both getters, then use the reloaded unsigned
 * fraction at 0x0C divided by D2968 and record scalar at 0x30. Cache the two
 * supplied components only when the shared link head is nonnull.
 * Preserve the original ordered center<sample difference/negation branches;
 * fabs would change NaN and signed-zero behavior. Request target-minus-value
 * through the original adjustment helper with its optional position word zero,
 * then return after the first match; the helper updates state handle/fraction
 * and scalar fields. RE_ORIGINAL_QUIRK: lookup results are dereferenced without
 * checking here. RE_UNKNOWN: handle/state/link/sample extents, alias/lifetime,
 * acyclic-list and valid-handle guarantees, value meanings/units and caller
 * reachability require original state/link producers and every entry caller. */
void tdataApplyFirstMatchingScalarLink(TdataScalarLinkStateView *state, f32 *samplePair) {
    TdataHandle handle;
    TdataRecord *record;
    f32 derivedValue;
    TdataScalarLinkView *link;
    f32 firstSample;
    f32 secondSample;
    f32 center;
    f32 firstDifference;
    f32 secondDifference;
    f32 tolerance;

    handle = state->handle;
    record = tdataGetRecordByHandle(handle);
    derivedValue = tdataGetLinearRecordValue(handle);
    derivedValue += (state->fractionWord0C / D_tdata_00402968) *
        *(f32 *)((u8 *)record + 0x30);
    link = (TdataScalarLinkView *)D_tdata_004029D8;
    if (link != NULL) {
        firstSample = samplePair[0];
        secondSample = samplePair[1];
        do {
            center = link->first;
            if (center < firstSample) {
                firstDifference = firstSample - center;
            } else {
                firstDifference = -(firstSample - center);
            }
            center = link->second;
            if (center < secondSample) {
                secondDifference = secondSample - center;
            } else {
                secondDifference = -(secondSample - center);
            }
            tolerance = link->tolerance;
            if (firstDifference < tolerance && secondDifference < tolerance &&
                derivedValue < link->upper && link->lower < derivedValue) {
                func_tdata_00400234((TdataScalarState *)state,
                    link->target - derivedValue, 0);
                return;
            }
            link = link->next;
        } while (link != NULL);
    }
}
#line 169 "src/modules/tdata.c"

#line 170 "src/modules/tdata.c"
/* Prepend the supplied record through its link word at 0x18 and retain
 * its address in the original shared head D_tdata_004029D8.
 * RE_UNKNOWN: record ownership/lifetime. Linking a supplied record does not
 * establish an ownership transfer; trace original allocation, insertion,
 * removal and list teardown before assigning a release contract. */
#line 173 "src/modules/tdata.c"
void tdataPrependRecordLink(void *record) {
    *(s32*)((u8*)record + 0x18) = D_tdata_004029D8;
    D_tdata_004029D8 = (s32)record;
}
#line 174 "src/modules/tdata.c"

#line 175 "src/modules/tdata.c"
/* Allocate the original 12-byte scalar-pair node and prepend it to the
 * shared list. Preserve unchecked allocation and the original 32-bit head. */
void* tdataAllocateScalarPair(f32 first, f32 second) {
    void* node;
    node = _uvMemAllocAlign8(0xC);
    *(f32*)((u8*)node + 0x0) = first;
    *(f32*)((u8*)node + 0x4) = second;
    *(s32*)((u8*)node + 0x8) = *(s32*)((u8*)&D_tdata_004029D4 + 0x0);
    *(s32*)((u8*)&D_tdata_004029D4 + 0x0) = (s32)node;
    return node;
}
#line 184 "src/modules/tdata.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401CBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401D38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00402388.s")

#line 191 "src/modules/tdata.c"
/* Replace both opaque track-data parameters in their original store order. */
void tdataSetSharedParameters(s32 first, s32 second) {
    D_tdata_004029F0 = first;
    D_tdata_004029F4 = second;
}
#line 195 "src/modules/tdata.c"

#line 196 "src/modules/tdata.c"
/* For every strict interior XYZ/scalar region, request target-minus-current
 * adjustment through the original float-argument helper. Re-read position,
 * scalar, count and region data after callbacks; overlapping regions can apply
 * more than one adjustment.
 * RE_UNKNOWN: ownership/lifetime and allocated extent of the region storage
 * retained in D_tdata_004029F4, and whether D_tdata_004029F0 always fits it.
 * Trace original shared-parameter setters, allocation and teardown before
 * attributing ownership or proving the loop's storage bound. */
#line 201 "src/modules/tdata.c"
void tdataApplyScalarRegions(TdataPositionState *position, TdataScalarState *state) {
    f32 x, y, z, value;
    s32 index, offset;
    TdataScalarRegion *region;
    index = 0; if (D_tdata_004029F0 > 0) {
        offset = 0; do {
            x = position->position.x;
            region = (TdataScalarRegion *)(offset + D_tdata_004029F4);
            if (region->minimum.x < x && x < region->maximum.x) {
                y = position->position.y;
                if (region->minimum.y < y && y < region->maximum.y) {
                    z = position->position.z;
                    if (region->minimum.z < z && z < region->maximum.z) {
                        value = state->value;
                        if (region->lower < value && value < region->upper) {
                            func_tdata_00400234(state, region->target - value, 0);
                        }
                    }
                }
            }
            index++;
            offset += 0x24;
        } while (index < D_tdata_004029F0);
    }
}
#line 197 "src/modules/tdata.c"

