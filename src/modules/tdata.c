// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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
void func_tdata_00400738();
void tdataResetProgressRecord();
void func_tdata_004008B8();
void func_tdata_004008D4();
void func_tdata_004009B0();
void func_tdata_00400DB4();
s32 tdataGetTotalRecordCount(void);
Vec3F tdataGetLinearRecordVector0C(s32 linearIndex);
void func_tdata_00401344();
s32 tdataGetClampedHandleWindow(TdataHandle *, TdataHandle *, TdataHandle *, s32, s32);
void func_tdata_004013EC();
f32 tdataGetLinearRecordValue(TdataHandle handle);
f32 tdataGetRecordDirectionAngle(TdataHandle handle);
f32 tdataGetRecordVectorZ(TdataHandle handle);
void func_tdata_00401638();
f32 func_tdata_00401860(s32 arg0);
TdataHandle *tdataHandleFromLinearIndex(TdataHandle *output, s32 index);
s32 func_tdata_00401904(TdataHandle);
extern f32 *D_tdata_004029E4;
void func_tdata_00401998();
TdataHandle tdataPreviousHandle(TdataHandle handle);
TdataRecord *tdataGetRecordByHandle(TdataHandle handle);
void func_tdata_00401ADC();
void func_tdata_00401CBC();
void func_tdata_00401D38();
void func_tdata_00402388();
void tdataApplyScalarRegions(TdataPositionState *position, TdataScalarState *state);
void func_tdata_00400DB4(void);
extern s32 D_tdata_004029D8;
extern s32 D_tdata_004029F0;
extern s32 D_tdata_004029F4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/__entrypoint_func_tdata_400000.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_004013EC.s")

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
/* Return float zero unconditionally, retaining the unused s32 argument.
 * RE_UNKNOWN: caller/export role and meaning of this constant result. */
f32 func_tdata_00401860(s32 arg0) {
    return 0.0f;
}
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401ADC.s")

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

