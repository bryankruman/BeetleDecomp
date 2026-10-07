// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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
void func_tdata_00400234();
void func_tdata_00400738();
void func_tdata_0040087C();
void func_tdata_004008B8();
void func_tdata_004008D4();
void func_tdata_004009B0();
void func_tdata_00400DB4();
s32 tdataGetTotalRecordCount(void);
Vec3F tdataGetLinearRecordVector0C(s32 linearIndex);
void func_tdata_00401344();
s32 func_tdata_00401354(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
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
void func_tdata_004027CC();
void func_tdata_00400DB4(void);
extern s32 D_tdata_004029D8;
extern s32 D_tdata_004029F0;
extern s32 D_tdata_004029F4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/__entrypoint_func_tdata_400000.s")

void func_tdata_0040018C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00400738.s")

void func_tdata_0040087C(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x0) = 0;
    *(s16 *)((u8 *)arg0 + 0x2) = 0;
    *(s16 *)((u8 *)arg0 + 0xC) = 0;
    *(f32 *)((u8 *)arg0 + 0x8) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x4) = 0.0f;
}

void func_tdata_00400898(void) {
    func_tdata_00400DB4();
}

void func_tdata_004008B8(s32 a0, s32 a1) {
}

void func_tdata_004008C4(void) {
}

void func_tdata_004008CC(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_004008D4.s")

s32 func_tdata_004009A8(void) {
    return 0;
}

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

void func_tdata_00401344(s32 a0, s32 a1, s32 a2) {
}

s32 func_tdata_00401354(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s32 sp1C;
  s32 t0;
  s32 v0;
  s32 v1;
  s32 v0b;
  v0 = arg3 - (arg4 / 2);
  sp1C = v0;
  v1 = v0 + arg4;
  t0 = v1;
  if (v0 <= 0)
  {
    sp1C = 0;
  }
  v0b = (*((s32 *) (&D_tdata_004029E0))) - 1;
  if (v1 >= v0b)
  {
    t0 = v0b;
  }
  tdataHandleFromLinearIndex(arg0, sp1C);
  tdataHandleFromLinearIndex(arg1, arg3);
  tdataHandleFromLinearIndex(arg2, t0);
  return t0 - sp1C;
}

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

f32 func_tdata_00401860(s32 arg0) {
    return 0.0f;
}

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

void func_tdata_00401C58(void *a0) {
    *(s32*)((u8*)a0 + 0x18) = D_tdata_004029D8;
    D_tdata_004029D8 = (s32)a0;
}

void* func_tdata_00401C70(f32 arg0, f32 arg1) {
    void* temp_v0;
    temp_v0 = _uvMemAllocAlign8(0xC);
    *(f32*)((u8*)temp_v0 + 0x0) = arg0;
    *(f32*)((u8*)temp_v0 + 0x4) = arg1;
    *(s32*)((u8*)temp_v0 + 0x8) = *(s32*)((u8*)&D_tdata_004029D4 + 0x0);
    *(s32*)((u8*)&D_tdata_004029D4 + 0x0) = (s32)temp_v0;
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401CBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00401D38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_00402388.s")

void func_tdata_004027B8(s32 a0, s32 a1) {
    D_tdata_004029F0 = a0;
    D_tdata_004029F4 = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/tdata/func_tdata_004027CC.s")

