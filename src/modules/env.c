// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct EnvVolumeRecord EnvVolumeRecord;
struct EnvVolumeRecord { s32 volume; u8 value04; u8 unk05[3]; EnvVolumeRecord *next; };
typedef struct { u8 unk00[0xC]; s32 (*test)(s32, s32, void *); } EnvVolumeExports;
extern EnvVolumeExports *gVolTestExports;

extern s32 D_env_00400848[];
extern s32 D_env_00400870;
extern EnvVolumeRecord *D_env_0040087C;
void func_env_00400100();

void func_env_004001F4();
void func_env_0040033C();
void func_env_00400380();
void envPrependVolumeRecord(s32 volume, u8 value);
u8 envFindVolumeRecordValue(void *query);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/__entrypoint_func_env_400000.s")

void func_env_004000AC(void) {
}

typedef struct {
    s32 unk0;
    f32 unk4;
    void * unk8;
} AutoS_004000B4_temp_v0;

extern void *D_env_00400878;

void func_env_004000B4(s32 arg0, f32 arg1) {
    AutoS_004000B4_temp_v0 *temp_v0;

    temp_v0 = _uvMemAllocAlign8(0xCU);
    temp_v0->unk8 = (void *) D_env_00400878;
    D_env_00400878 = temp_v0;
    temp_v0->unk0 = arg0;
    temp_v0->unk4 = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_00400100.s")

#line 38 "src/modules/env.c"
/* Allocate and prepend a 20-byte environment record. The three values and flags
 * remain opaque until their consumers establish a more specific meaning. */
typedef struct EnvRecord_00400190 {
    s32 values[3];
    u8 flags;
    u8 padD[3];
    struct EnvRecord_00400190 *next;
} EnvRecord_00400190;
extern EnvRecord_00400190 *D_env_00400874;
void envPrependRecord(s32 first, s32 second, s32 third, u8 flags) {
    EnvRecord_00400190 *record;
    record = _uvMemAllocAlign8(sizeof(EnvRecord_00400190));
    record->values[0] = first;
    record->values[1] = second;
    record->values[2] = third;
    record->flags = flags;
    record->next = D_env_00400874;
    D_env_00400874 = record;
}
#line 39 "src/modules/env.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_004001F4.s")

void func_env_0040033C(s32 arg0) {
    if (D_env_00400870 < 0xA && arg0 != 0) {
        D_env_00400848[D_env_00400870] = arg0;
        D_env_00400870 += 1;
    }
}

void func_env_00400378(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_00400380.s")

#line 54 "src/modules/env.c"
/* Allocate and prepend a volume/value record; preserve the original allocator
 * contract and opaque byte value rather than assigning an unproven gameplay name. */
void envPrependVolumeRecord(s32 volume, u8 value) {
    EnvVolumeRecord *record = _uvMemAllocAlign8(sizeof(EnvVolumeRecord));
    record->next = D_env_0040087C;
    D_env_0040087C = record;
    record->volume = volume;
    record->value04 = value;
}
#line 55 "src/modules/env.c"

#line 56 "src/modules/env.c"
/* Return the first record value whose volume test accepts the query, or zero.
 * A stored zero is intentionally indistinguishable from no matching record. */
u8 envFindVolumeRecordValue(void *query) {
    EnvVolumeRecord *record = D_env_0040087C;
    while (record != NULL) {
        if (gVolTestExports->test(record->volume, 2, query) != 0) {
            return record->value04;
        }
        record = record->next;
    }
    return 0;
}
#line 57 "src/modules/env.c"

