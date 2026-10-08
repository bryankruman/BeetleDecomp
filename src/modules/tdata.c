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
/* Register all thirty original callback addresses in their original store
 * order after updating the file allocation pointer. This is address storage,
 * not a declaration of a callable export interface.
 * RE_UNKNOWN: historical full table type and remaining callback signatures
 * and purposes. Resolve consumers and original callback bodies before adding
 * callable slot types or changing any empty or constant-return export. */
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
/* Sum the record counts of all track-data groups in their stored order. */
s32 tdataGetTotalRecordCount(void) {
    s32 result;
    u32 index;
    TdataBank *bank;
    u32 count;
    TdataGroup *group;
    index = result = 0;
    bank = (TdataBank *)D_tdata_004029DC;
    count = bank->groupCount;
    if (count != 0) {
        group = bank->groups;
        do {
            result += group->count;
            index++;
            group++;
        } while (index < count);
    }
    return result;
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
/* Convert the lower, center and upper linear indices to handles after
 * clamping the original window against zero and the last record. Return
 * upper minus lower; preserve integer division and caller-owned outputs. */
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
/* Convert the group/index handle to a linear index and read its float value,
 * returning zero above the stored count. The original routine has no negative
 * index check; valid handles remain the caller's responsibility. */
f32 tdataGetLinearRecordValue(TdataHandle handle) {
    s32 index = func_tdata_00401904(handle);
    if (index < D_tdata_004029E0) {
        return D_tdata_004029E4[index];
    }
    return 0.0f;
}
#line 150 "src/modules/tdata.c"

#line 151 "src/modules/tdata.c"
/* Pass the negated X and original Y components of the record vector to the
 * shared direction-angle helper. A missing record returns zero. */
f32 tdataGetRecordDirectionAngle(TdataHandle handle) {
    TdataRecord *record = tdataGetRecordByHandle(handle);
    if (record == NULL) {
        return 0.0f;
    }
    return gMiscExports->directionAngle(-record->vector18.x, record->vector18.y);
}
#line 152 "src/modules/tdata.c"

#line 151 "src/modules/tdata.c"
/* Return the record vector's Z component, or zero for an invalid (-1) handle. */
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
/* Convert a valid linear record index to its signed-halfword group/index handle.
 * The explicit output pointer preserves existing callers and the original ABI.
 * Group sizes and valid input indices remain the caller's responsibility. */
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
/* Move backward within the group, crossing to the preceding group when needed.
 * Group -1 marks the beginning boundary. Preserve signed-halfword conversion
 * and the original aggregate return ABI; no extra bounds checks are introduced. */
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
/* Resolve the signed-halfword group/index handle to a 56-byte track-data
 * record. Either -1 component returns null; other bounds remain caller-owned. */
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

