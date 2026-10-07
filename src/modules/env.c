// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct EnvVolumeRecord EnvVolumeRecord;
struct EnvVolumeRecord { s32 volume; u8 value04; u8 unk05[3]; EnvVolumeRecord *next; };
typedef struct { u8 unk00[0xC]; s32 (*test)(s32, s32, void *); } EnvVolumeExports;
extern EnvVolumeExports *gVolTestExports;

extern s32 D_env_00400848[];
extern s32 D_env_00400870;
extern EnvVolumeRecord *D_env_0040087C;
s32 envLookupVolumeValue(s32 queryAddress, f32 *output);

void func_env_004001F4();
void envAppendNonzeroRegisteredValue();
void func_env_00400380();
void envPrependVolumeRecord(s32 volume, u8 value);
u8 envFindVolumeRecordValue(void *query);
/* Initializer-only address registry, not an inferred callable interface.
 * Opaque assembly labels below are code addresses, not inferred data objects;
 * this initializer never dereferences or calls them. Existing unresolved
 * prototypes remain unchanged and do not establish a recovered callback ABI.
 * RE_UNKNOWN: replace opaque/old-style declarations with grounded function
 * prototypes after recovering each implementation and actual caller contract. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 prependVolumeScalarRecordAddress;
    /* 0x08 */ u32 lookupVolumeValueAddress;
    /* 0x0C */ u32 prependRecordAddress;
    /* 0x10 */ u32 unknownCallback10Address;
    /* 0x14 */ u32 appendRegisteredValueAddress;
    /* 0x18 */ u32 unknownCallback18Address;
    /* 0x1C */ u32 prependVolumeRecordAddress;
    /* 0x20 */ u32 findVolumeRecordValueAddress;
} EnvExportAddresses;
struct EnvRecord_00400190;
extern struct EnvRecord_00400190 *D_env_00400874;
extern void *D_env_00400878;
void func_env_004000AC(void);
void envPrependVolumeScalarRecord(s32 volume, f32 value);
s32 envLookupVolumeValue(s32 queryAddress, f32 *output);
void envPrependRecord(s32 first, s32 second, s32 third, u8 flags);
void envAppendNonzeroRegisteredValue(s32 value);
void envPrependVolumeRecord(s32 volume, u8 value);
u8 envFindVolumeRecordValue(void *query);

#line 46 "src/modules/env.c"
/* Register the nine original environment callback addresses after updating
 * the allocation pointer, then clear the registration count and three record
 * list heads in their original order. Preserve the empty callback identity.
 * RE_UNKNOWN: callback 0x10/18 contracts, complete environment value/flag
 * meanings and safe loader/reload ownership of existing records require the
 * original targets, list consumers and callers. Caller-owned export storage
 * must satisfy the original nine-word address registry contract. */
void __entrypoint_func_envInitializeModuleExports(EnvExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_env_004000AC;
    exports->prependVolumeScalarRecordAddress = (u32) envPrependVolumeScalarRecord;
    exports->lookupVolumeValueAddress = (u32) envLookupVolumeValue;
    exports->prependRecordAddress = (u32) envPrependRecord;
    exports->unknownCallback10Address = (u32) func_env_004001F4;
    exports->appendRegisteredValueAddress = (u32) envAppendNonzeroRegisteredValue;
    exports->unknownCallback18Address = (u32) func_env_00400380;
    exports->prependVolumeRecordAddress = (u32) envPrependVolumeRecord;
    exports->findVolumeRecordValueAddress = (u32) envFindVolumeRecordValue;
    D_env_00400870 = 0;
    D_env_00400874 = NULL;
    D_env_00400878 = NULL;
    D_env_0040087C = NULL;
}
#line 47 "src/modules/env.c"

#line 20 "src/modules/env.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_env_004000AC(void) {
}
#line 22 "src/modules/env.c"

typedef struct {
    s32 unk0;
    f32 unk4;
    void * unk8;
} AutoS_004000B4_temp_v0;

extern void *D_env_00400878;

#line 31 "src/modules/env.c"
/* Allocate and prepend a twelve-byte volume/scalar record used by
 * envLookupVolumeValue. Preserve insertion precedence, allocation handling
 * and the original order of publishing and filling the new record.
 * RE_UNKNOWN: The stored scalar meaning and units remain unproven. */
void envPrependVolumeScalarRecord(s32 volume, f32 value) {
    AutoS_004000B4_temp_v0 *record;

    record = _uvMemAllocAlign8(0xCU);
    record->unk8 = (void *) D_env_00400878;
    D_env_00400878 = record;
    record->unk0 = volume;
    record->unk4 = value;
}
#line 40 "src/modules/env.c"

#line 41 "src/modules/env.c"
/* Return the first environment value whose volume accepts this query.
 * The original list order determines precedence; a miss leaves output untouched. */
s32 envLookupVolumeValue(s32 queryAddress, f32 *output) {
    AutoS_004000B4_temp_v0 *record = D_env_00400878;
    while (record != NULL) {
        if (gVolTestExports->test(record->unk0, 0, (void *)queryAddress) != 0) {
            *output = record->unk4;
            return 1;
        }
        record = record->unk8;
    }
    return 0;
}
#line 42 "src/modules/env.c"

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

#line 42 "src/modules/env.c"
/* Append a nonzero value only while the original registration count
 * is below ten. Zero values and a full list are ignored; preserve duplicates
 * and the original shared-count contract.
 * RE_UNKNOWN: The registered value meaning remains unproven. */
void envAppendNonzeroRegisteredValue(s32 value) {
    if (D_env_00400870 < 0xA && value != 0) {
        D_env_00400848[D_env_00400870] = value;
        D_env_00400870 += 1;
    }
}
#line 48 "src/modules/env.c"

#line 49 "src/modules/env.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_env_00400378(void) {
}
#line 51 "src/modules/env.c"

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

