// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvtexture_rom.h"
/* Original initializer imports TEXT here. Its slot0x04 consumes the incoming
 * texture ID and returns loaded texture byte0x27; it is not a game-state getter. */
extern UvTexture_Exports *D_uvisect_rom_00408204;

/* The original TERR export table has seven actual 32-bit function-address
 * entries before slot 0x1C. Keep those unused addresses opaque rather than
 * inventing callable signatures; only the established texture getter is typed. */
typedef struct {
    u32 precedingExportAddresses[7];
    s32 (*getPackedTriangleTexture)(s32 terrainId, u32 handle);
} IsectTerrainTextureExports;
extern IsectTerrainTextureExports *D_uvisect_rom_00408200;

typedef struct { s32 count; s32 values[1]; } IsectCountedValues; /* Variable-length original allocation. */
typedef struct { u8 unk00[0xC]; s32 value0C; u8 unk10[2]; u16 value12; u16 value14; } IsectScalarPrefix;

typedef struct { s32 registryIndex; u8 unk04[0xF10]; } IsectLargeRecord;
extern IsectLargeRecord *D_uvisect_rom_00407828;
extern u16 D_uvisect_rom_00407878;
void uvIsectSetPropertyWord08(void *record, s32 property);

#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"

typedef struct { u32 unk00[11]; f32 value2C; u32 unk30[10]; } IsectCopyRecord88;

/* Accessed prefix only: two 12-byte vectors and raw word 0x18. RE_UNKNOWN:
 * layout, frame and mode-specific word meaning: low-bit-tested by 24AC/2B5C,
 * dereferenced by 1DA4. Trace mode setters and input producers before typing. */
typedef struct {
    Vec3F first;
    Vec3F second;
    u32 word18;
} IsectQueryInputPrefix;

/* Observed argument views preserve native 32-bit words and output addresses.
 * RE_UNKNOWN: complete historical declarations and the forwarded word roles.
 * The two six-argument helpers consume the final word's low16 bits; this
 * wrapper passes zero and does not establish a wider caller-domain contract. */
s32 uvIsectQueryInputVectorsIntoRecord(IsectQueryInputPrefix *input, s32 queryFlags,
    s32 contextWord, s32 queryWord, IsectCopyRecord88 *output);
s32 func_uvisect_rom_00401558(Vec3F *first, Vec3F *second, u32 inputWord18,
    s32 queryFlags, s32 contextWord, s32 queryWord, IsectCopyRecord88 *output);
s32 func_uvisect_rom_004024AC(Vec3F *first, Vec3F *second, u32 inputWord18,
    s32 queryWord, IsectCopyRecord88 *output, s32 modeWord);
s32 func_uvisect_rom_00402B5C(Vec3F *first, Vec3F *second, u32 inputWord18,
    s32 queryWord, IsectCopyRecord88 *output, s32 modeWord);
s32 func_uvisect_rom_00403054(Vec3F *first, Vec3F *second,
    IsectCopyRecord88 *output);
s32 uvIsectUpdateMinimumValueRecord(IsectCopyRecord88 *destination,
    f32 *minimumValue, IsectCopyRecord88 *candidate);
extern f32 D_uvisect_rom_004076DC;


/* Prefix views of original bytes actually accessed by 0x403F38; neither view
 * claims the allocation size or the meanings of the retained raw words. */
typedef struct {
    u32 words00[6];
    u32 flags18;
} IsectLinkedFlagsPrefix;
typedef struct {
    IsectLinkedFlagsPrefix *linkedRecord;
    s32 mode04;
    s32 kind08;
    u32 triangleHandle0C;
    u32 flags10;
    Vec3F point14;
    u32 words20[3];
    f32 value2C;
    u32 word30;
    Vec3F vector34;
} IsectFacingRecordPrefix;
extern f32 D_uvisect_rom_004076C4;


/* Address-valued shared query words keep their existing setter ABI. These
 * buffer declarations establish accessed element widths, not capacities. */
extern u32 D_uvisect_rom_004078F0[];
extern Vec3F D_uvisect_rom_00407A70[];
extern f32 D_uvisect_rom_00407EF0[];
extern u32 D_uvisect_rom_00408070[];
extern u32 D_uvisect_rom_00408130[];
void func_uvisect_rom_00405124(s32 *resultCount, void *record,
    Vec3F *first, Vec3F *second, u32 *recordWord, u32 *filterWord);

typedef struct { u8 unk00[0xE84]; Mtx4F transform; Vec3F vectorEC4; } IsectTransformPrefix;
extern UvFMtx_Rom_Exports *D_uvisect_rom_004081F0;
extern UvFVec_Rom_Exports *D_uvisect_rom_004081F4;

/* RE_UNKNOWN: These source-local views describe only native export offsets and
 * consumed argument words. Historical source declarations and unused callable
 * contracts remain unknown; resolve those from the original providers/callers.
 * The unused entries are original 32-bit address words, not guessed callbacks. */
typedef struct {
    u32 addresses00[6];
    void (*getTriangleNormal)(s32 terrainWord, u32 triangleWord, Vec3F *outNormal);
    u32 addresses1C[4];
    s32 (*queryTriangles)(s32 terrainWord, f32 firstX, f32 firstY, f32 firstZ,
                          f32 secondX, f32 secondY, f32 secondZ,
                          u32 **outWords, f32 **outScalars);
    u32 addresses30[25];
    s32 (*queryObjects)(s32 terrainWord, f32 firstX, f32 firstY, f32 firstZ,
                        f32 secondX, f32 secondY, f32 secondZ,
                        u32 **outWords, f32 **outScalars, Vec3F **outVectors);
} IsectTerrainCollectExports;

typedef struct {
    u32 addresses00[11];
    void (*setFlags)(s32 objectWord, s32 flags);
    u32 address30;
    s32 (*getFlags)(s32 objectWord);
    u32 addresses38[7];
    s32 (*queryObjects)(f32 firstX, f32 firstY, f32 firstZ,
                        f32 secondX, f32 secondY, f32 secondZ,
                        u32 **outWords, f32 **outScalars, Vec3F **outVectors);
} IsectDobjCollectExports;
extern IsectDobjCollectExports *D_uvisect_rom_004081FC;
#line 92 "src/modules/uvisect_rom.c"
void func_uvisect_rom_00400C8C(IsectTransformPrefix *record);


/* Prefix views: only the accessed offsets and array extents are established. */
typedef struct { s32 unk00; s32 kind; s32 count; } IsectValueRecord;
extern IsectValueRecord *D_uvisect_rom_004077D0;
typedef struct { void *owner; s32 unk04; } IsectOwnerResult;
typedef struct { s32 count; u8 unk04[0xDC4]; void *entries[40]; } IsectPendingRecords;

extern f32 D_uvisect_rom_004078B0;
extern s16 D_uvisect_rom_004078C8;
extern s16 D_uvisect_rom_004078CA;
extern s16 D_uvisect_rom_004078D4;
extern s16 D_uvisect_rom_004078D6;
extern s32 D_uvisect_rom_004077C0;
extern s32 D_uvisect_rom_00407898;
extern s32 D_uvisect_rom_004078CC;
extern s32 D_uvisect_rom_004078D0;
extern s32 D_uvisect_rom_004078D8;
extern s32 D_uvisect_rom_004078DC;
extern s32 D_uvisect_rom_004078E0;
extern s32 D_uvisect_rom_004078E4;
extern s32 D_uvisect_rom_004078E8;
extern s32 D_uvisect_rom_004078EC;
extern u8 D_uvisect_rom_00407880;
extern s32 D_uvisect_rom_0040787C;
extern u16 D_uvisect_rom_00407894;
extern f32 D_uvisect_rom_004077B8;
extern u16 D_uvisect_rom_00407820;
extern s32 D_uvisect_rom_004077BC;
extern s32 D_uvisect_rom_004078C4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/__entrypoint_func_uvisect_rom_400000.s")

#line 51 "src/modules/uvisect_rom.c"
/* Unload FMTX, FVEC, MATH, DOBJ, TERR, TEXT, ISCT, MODL and QERY
 * dependencies in their original order. */
void uvIsectModuleCleanup(void) {
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x46564543);
    uvUnloadModule(0x4D415448);
    uvUnloadModule(0x444F424A);
    uvUnloadModule(0x54455252);
    uvUnloadModule(0x54455854);
    uvUnloadModule(0x49534354);
    uvUnloadModule(0x4D4F444C);
    uvUnloadModule(0x51455259);
}
#line 62 "src/modules/uvisect_rom.c"

#line 58 "src/modules/uvisect_rom.c"
/* Allocate and clear the original 0xF14-byte record, register its 16-bit
 * index, set property 0xFFFF and initialize the self/shared-data links. Forty
 * link slots have stride 0x58; their complete layout and meanings are unknown.
 * Preserve the original unchecked allocation/registry assumptions and the
 * explicit 16-bit iteration value, without adding artificial stack padding. */
IsectLargeRecord *uvIsectCreateLargeRecord(void) {
    s32 index;
    IsectLargeRecord *record;
    record = _uvMemAllocAlign8(0xF14);
    uvMemSet(record, 0, 0xF14);
    ((IsectLargeRecord **) &D_uvisect_rom_00407828)[D_uvisect_rom_00407878] = record;
    record->registryIndex = D_uvisect_rom_00407878;
    D_uvisect_rom_00407878++;
    uvIsectSetPropertyWord08(record, 0xFFFF);
    *(IsectLargeRecord **) ((u8 *) record + 0xDE0) = record;
    for (index = 0; index < 40; index = (u16) (index + 1)) {
        *(u8 **) ((u8 *) record + 0x74 + index * 0x58) = (u8 *) record + 0x1C;
    }
    return record;
}
#line 59 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004004F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004005D0.s")

#line 64 "src/modules/uvisect_rom.c"
/* Convert property 3 (unsigned field 0x12), property 2 (unsigned field 0x14)
 * or property 5 (signed field 0x0C) to float. Return -1 for null records or
 * unsupported properties. RE_UNKNOWN: field roles; trace record constructors/callers. */
f32 uvIsectGetScalarProperty(IsectScalarPrefix *record, s32 property) {
    if (record == NULL) return -1.0f;
    switch (property) {
        case 3: return record->value12;
        case 2: return record->value14;
        case 5: return record->value0C;
        default: return -1.0f;
    }
}
#line 65 "src/modules/uvisect_rom.c"

#line 66 "src/modules/uvisect_rom.c"
/* Property 3 replaces matrix translation and refreshes dependent state.
 * Property 4 replaces the vector at 0xEC4 without refresh. Pass the vector by
 * value to preserve the original aggregate ABI; unsupported properties do nothing. */
void uvIsectSetVectorProperty(IsectTransformPrefix *record, s32 property, Vec3F value) {
    if (record == NULL) return;
    switch (property) {
        case 3:
            record->transform.m[3][0] = value.x;
            record->transform.m[3][1] = value.y;
            record->transform.m[3][2] = value.z;
            func_uvisect_rom_00400C8C(record);
            break;
        case 4:
            D_uvisect_rom_004081F4->uvVec3FCopy(&record->vectorEC4, &value);
            break;
    }
}
#line 67 "src/modules/uvisect_rom.c"

#line 68 "src/modules/uvisect_rom.c"
/* Native callback homes incoming A2 and tests A0, but performs no property work.
 * RE_UNKNOWN: complete parameter types/count, historical purpose and indirect
 * caller domain. Trace initializer/export consumers and original call sites
 * before changing the null check, argument home or callback identity. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400920.s")
#line 69 "src/modules/uvisect_rom.c"

#line 70 "src/modules/uvisect_rom.c"
/* Copy matrix translation for property 3 or the opaque 0xEC4 vector for
 * property 4. Null records and unsupported properties leave output unchanged. */
void uvIsectGetVectorProperty(IsectTransformPrefix *record, s32 property, Vec3F *destination) {
    if (record == NULL) return;
    switch (property) {
        case 3:
            destination->x = record->transform.m[3][0];
            destination->y = record->transform.m[3][1];
            destination->z = record->transform.m[3][2];
            break;
        case 4:
            D_uvisect_rom_004081F4->uvVec3FCopy(destination, &record->vectorEC4);
            break;
    }
}
#line 71 "src/modules/uvisect_rom.c"

#line 65 "src/modules/uvisect_rom.c"
/* Property 3 replaces the matrix at offset 0xE84, then invokes the original
 * dependent-state refresh helper. Other properties and null records do nothing. */
void uvIsectSetTransformProperty(IsectTransformPrefix *record, s32 property, Mtx4F *source) {
    if (record != NULL && property == 3) {
        D_uvisect_rom_004081F0->uvMat4FCopy(&record->transform, source);
        func_uvisect_rom_00400C8C(record);
    }
}
#line 66 "src/modules/uvisect_rom.c"

#line 67 "src/modules/uvisect_rom.c"
/* Native no-op homes incoming A2 and returns without property work.
 * RE_UNKNOWN: complete parameter types/count, historical callback purpose and
 * indirect callers. Recover actual initializer/export uses and call sites
 * before assigning a variadic prototype or removing its separate identity. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004009F0.s")
#line 68 "src/modules/uvisect_rom.c"

#line 69 "src/modules/uvisect_rom.c"
/* Property 3 copies the stored matrix at offset 0xE84 to the destination.
 * A null record or unsupported property leaves the destination unchanged. */
void uvIsectGetTransformProperty(IsectTransformPrefix *record, s32 property, Mtx4F *destination) {
    if (record != NULL && property == 3) {
        D_uvisect_rom_004081F0->uvMat4FCopy(destination, &record->transform);
    }
}
#line 70 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400A40.s")

#line 73 "src/modules/uvisect_rom.c"
/* Read the original 32-bit word at offset 0x18 without a null check.
 * RE_UNKNOWN: word meaning and valid record lifetime; trace original callers. */
s32 uvIsectGetWord18(void *record) {
    return *(s32 *)((u8 *)record + 0x18);
}
#line 76 "src/modules/uvisect_rom.c"

#line 77 "src/modules/uvisect_rom.c"
/* Return the original data address at record + 0x1C as 32-bit address bits.
 * Preserve the existing integer ABI while consumers are still being recovered. */
s32 uvIsectGetDataAddress1C(s32 recordAddress) {
    return recordAddress + 0x1C;
}
#line 80 "src/modules/uvisect_rom.c"

#line 81 "src/modules/uvisect_rom.c"
/* Replace the property word at offset 0x08. The original allocator initializes
 * this word to 0xFFFF; callers own record validity and property semantics. */
void uvIsectSetPropertyWord08(void *record, s32 property) {
    *(s32 *)((u8 *)record + 0x8) = property;
}
#line 84 "src/modules/uvisect_rom.c"

#line 85 "src/modules/uvisect_rom.c"
/* Read the property word at offset 0x08 without adding a new null check. */
s32 uvIsectGetPropertyWord08(void *record) {
    return *(s32 *)((u8 *)record + 0x8);
}
#line 88 "src/modules/uvisect_rom.c"

#line 89 "src/modules/uvisect_rom.c"
/* Store shared record count and the record, record-word and filter-word addresses.
 * RE_UNKNOWN: bounds and lifetime; trace setters and query 0x404D74 before changing this four-s32 interface. */
void uvIsectSetSharedQueryWords(s32 recordCount, s32 recordAddress, s32 recordWordAddress, s32 filterWordAddress) {
    D_uvisect_rom_004078E0 = recordCount;
    D_uvisect_rom_004078E4 = recordAddress;
    D_uvisect_rom_004078E8 = recordWordAddress;
    D_uvisect_rom_004078EC = filterWordAddress;
}
#line 95 "src/modules/uvisect_rom.c"

#line 84 "src/modules/uvisect_rom.c"
/* Set the active bank's unsigned first/end record indices and two address words.
 * Mode 2 toggles banks 1/2; mode 0 stores nothing; retain original 16/32-bit widths.
 * RE_UNKNOWN: bounds/ownership/lifetime; trace setters and query 0x404ED4 before tightening contracts. */
void uvIsectSetQueryParameterBank(s32 mode, u16 firstRecordIndex, u16 endRecordIndex, s32 recordAddress, s32 recordWordAddress) {
    if (mode == 2) {
        if (D_uvisect_rom_004077C0 == 1) D_uvisect_rom_004077C0 = mode;
        else D_uvisect_rom_004077C0 = 1;
    } else D_uvisect_rom_004077C0 = mode;
    switch (D_uvisect_rom_004077C0) {
    case 1:
        D_uvisect_rom_004078C8 = firstRecordIndex;
        D_uvisect_rom_004078CA = endRecordIndex;
        D_uvisect_rom_004078CC = recordAddress;
        D_uvisect_rom_004078D0 = recordWordAddress;
        return;
    case 2:
        D_uvisect_rom_004078D4 = firstRecordIndex;
        D_uvisect_rom_004078D6 = endRecordIndex;
        D_uvisect_rom_004078D8 = recordAddress;
        D_uvisect_rom_004078DC = recordWordAddress;
    case 0: return;
    }
}
#line 85 "src/modules/uvisect_rom.c"

/* Refresh payload points using the stored matrix and original FMTX slot 0x48.
 * Require record halfword 0x12 equal to one and nonnull payload at 0x18.
 * Layout zero uses the payload+0x08 group: signed count at zero, source
 * pointers at 0x04+4*i and output points at 0x54/0x60+0x1C*i. Capture each
 * source pointer across both transforms; reload the provider and signed
 * count after calls, retaining the original low16 loop increment.
 * Layout one transforms payload+0x08 into payload+0x18 with matrix at 0xE84.
 * RE_UNKNOWN: halfword/layout meanings, complete allocation and capacity,
 * aliasing, coordinate frames and valid count domain. Trace payload producers
 * and original property callers before adding bounds or ownership claims.
 * RE_UNKNOWN: historical source organization of the shared group/count
 * address. The readable draft adds a duplicate live address and saved register;
 * original operations and provider identity agree, but instructions do not.
 * Retain original assembly until a grounded source/layout contract resolves it. */
#line 86 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400DC0.s")

#line 90 "src/modules/uvisect_rom.c"
/* Store the supplied pointer at result offset 0x00 and clear word 0x04,
 * then append the entry address when fewer than 40 are pending. Return one on
 * insertion and zero when full; the function performs no allocation or release.
 * RE_UNKNOWN: the relationship and lifetimes of the result pointer and entry.
 * The existing owner label does not prove ownership; trace original producers,
 * queue consumers and release paths before relying on that interpretation. */
#line 93 "src/modules/uvisect_rom.c"
s32 uvIsectQueuePendingRecord(void *owner, IsectOwnerResult *result, IsectPendingRecords *pending, void *entry) {
    result->unk04 = 0;
    result->owner = owner;
    if (pending->count < 40) {
        pending->entries[pending->count] = entry;
        pending->count++;
        return 1;
    }
    return 0;
}
#line 91 "src/modules/uvisect_rom.c"

/* Merge shared query key/scalar pairs into record slots at 0xEE0/0xEF4,
 * skipping duplicate keys, and store the low16 caller source word at 0xF08.
 * LHU count0xF12 is captured for the duplicate search/key store and reloaded
 * independently before scalar, source-halfword and increment stores. Retain
 * original low16 loop increments and source-word normalization before guards.
 * RE_ORIGINAL_QUIRK: collected count <5 is checked only once on entry;
 * multiple unique shared pairs are appended without another capacity check.
 * RE_UNKNOWN: native producer/count bounds, key/scalar meanings, source-word
 * protocol and aliasing. The original allocator reserves/zeros 0xF14 bytes;
 * five scalar and halfword slots precede count0xF12. Trace original producers
 * and callers before changing checks or asserting reachable player impact.
 * RE_UNKNOWN: historical parameter/source organization causing the original
 * fullword argument home plus low16 normalized live value. Preserve original
 * instructions until readable C matches; a halfword store alone proves no
 * complete historical parameter declaration. */
#line 92 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004013F0.s")

#line 94 "src/modules/uvisect_rom.c"

/* Store input/zero at output byte offsets0x00/0x04, then delegate
 * using input vectors 0/0x0C and the raw word at 0x18. Preserve the original
 * second-vector/first-vector argument order and the helper return value.
 * The forwarded context/query words and query flags retain all native32 bits.
 * RE_UNKNOWN: complete input/record allocations, vector frame, flag and word
 * meanings, output lifetime and aliasing domain. Trace original callers and
 * helper 0x401558 before assigning ownership or adding validation/defaults.
 * The two prefix stores occur even when the delegated query fails; this
 * wrapper does not initialize the remaining output fields. */
s32 uvIsectQueryInputVectorsIntoRecord(IsectQueryInputPrefix *input, s32 queryFlags,
    s32 contextWord, s32 queryWord, IsectCopyRecord88 *output) {
    output->unk00[0] = (u32)input;
    output->unk00[1] = 0;
    return func_uvisect_rom_00401558(&input->second, &input->first,
        input->word18, queryFlags, contextWord, queryWord, output);
}
#line 95 "src/modules/uvisect_rom.c"

/* Query flags 2/8/1/4 delegate in native order. Flag 2 optionally subtracts
 * one from the actual DOBJ byte-0x04 flags when its low bit is set, then
 * restores the saved byte; object ID 0xFFFF skips these flag accesses.
 * Later successful candidates replace the existing 88-byte record only for
 * a strictly smaller value at byte 0x2C. The first nonzero helper result is
 * retained even when a later candidate wins; it is not normalized to one.
 * RE_UNKNOWN: input word 0x18 representation by mode, vector frame, query-word
 * meaning, complete allocations/aliasing and successful-helper field validity.
 * Two query helpers test that word's low bit, while 0x401DA4 can dereference
 * it in nonzero shared-query modes. Trace original producers, mode setters
 * and helper outputs before assigning one universal pointer/flag declaration.
 * RE_UNKNOWN: historical scratch declaration/alignment. The native scratch
 * prefix copies only words at bytes 0x04/0x00 before helper calls; its other
 * fields are not initialized here. The matching 88-byte copy contract alone
 * does not establish the original local declaration. Preserve native storage
 * and the separately indexed 0x403054 fraction-assignment observation. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00401558.s")
#line 97 "src/modules/uvisect_rom.c"

#line 98 "src/modules/uvisect_rom.c"
/* Combine requested provider lists in the original shared buffers, then
 * publish only the output addresses requested by the caller.
 * RE_ORIGINAL_QUIRK: In the flag-1 path, IDs are copied only if outWords is
 * non-null, but normal queries read shared IDs whenever outVectors is non-null.
 * RE_UNKNOWN: Valid flag/output combinations, prior shared-ID initialization,
 * buffer capacities, aliasing, lifetime and reentrant use require original
 * caller/producer tracing. Do not infer that a returned count bounds storage.
 * Counts are accumulated even when nonpositive; only positive counts copy.
 * Provider zero-result paths do not uniformly initialize their output pointers.
 * The focused export views preserve six scalar coordinate words and the full
 * object/terrain argument words without claiming historical C prototypes. */
s32 uvIsectCollectRequestedProviderLists(Vec3F *first, Vec3F *second, s32 queryFlags,
                            s32 excludedObjectWord, s32 terrainWord,
                            u32 **outWords, f32 **outScalars, Vec3F **outVectors)
{
    u8 originalObjectFlags;
    s32 index;
    s32 totalCount;
    s32 providerCount;
    u32 *providerWords;
    f32 *providerScalars;
    Vec3F *providerVectors;

    totalCount = 0;
    if (queryFlags & 1) {
        providerCount = ((IsectTerrainCollectExports *)D_uvisect_rom_00408200)->queryTriangles(
            terrainWord, first->x, first->y, first->z,
            second->x, second->y, second->z, &providerWords, &providerScalars);
        for (index = 0; index < providerCount; index++) {
            if (outWords != NULL) {
                D_uvisect_rom_004078F0[index] = providerWords[index];
            }
            if (outScalars != NULL) {
                D_uvisect_rom_00407EF0[index] = providerScalars[index];
            }
            if (outVectors != NULL) {
                ((IsectTerrainCollectExports *)D_uvisect_rom_00408200)->getTriangleNormal(
                    terrainWord, D_uvisect_rom_004078F0[index], &D_uvisect_rom_00407A70[index]);
            }
        }
        totalCount = providerCount;
    }
    if (queryFlags & 8) {
        providerCount = ((IsectTerrainCollectExports *)D_uvisect_rom_00408200)->queryObjects(
            terrainWord, first->x, first->y, first->z,
            second->x, second->y, second->z, &providerWords, &providerScalars, &providerVectors);
        for (index = 0; index < providerCount; index++) {
            if (outWords != NULL) {
                D_uvisect_rom_004078F0[totalCount + index] = providerWords[index];
            }
            if (outVectors != NULL) {
                D_uvisect_rom_00407A70[totalCount + index] = providerVectors[index];
            }
            if (outScalars != NULL) {
                D_uvisect_rom_00407EF0[totalCount + index] = providerScalars[index];
            }
        }
        totalCount += providerCount;
    }
    if (queryFlags & 2) {
        /* Preserve the exact full-word sentinel, byte snapshot and restore
         * sequence around the DOBJ query, including an unchanged flag byte. */
        if (excludedObjectWord != 65535) {
            originalObjectFlags = D_uvisect_rom_004081FC->getFlags(excludedObjectWord);
            if (originalObjectFlags & 1) {
                D_uvisect_rom_004081FC->setFlags(excludedObjectWord, originalObjectFlags - 1);
            }
        }
        providerCount = D_uvisect_rom_004081FC->queryObjects(
            first->x, first->y, first->z, second->x, second->y, second->z,
            &providerWords, &providerScalars, &providerVectors);
        if (excludedObjectWord != 65535) {
            D_uvisect_rom_004081FC->setFlags(excludedObjectWord, originalObjectFlags);
        }
        for (index = 0; index < providerCount; index++) {
            if (outWords != NULL) {
                D_uvisect_rom_004078F0[totalCount + index] = providerWords[index];
            }
            if (outVectors != NULL) {
                D_uvisect_rom_00407A70[totalCount + index] = providerVectors[index];
            }
            if (outScalars != NULL) {
                D_uvisect_rom_00407EF0[totalCount + index] = providerScalars[index];
            }
        }
        totalCount += providerCount;
    }
    if (outWords != NULL) {
        *outWords = D_uvisect_rom_004078F0;
    }
    if (outVectors != NULL) {
        *outVectors = D_uvisect_rom_00407A70;
    }
    if (outScalars != NULL) {
        *outScalars = D_uvisect_rom_00407EF0;
    }
    return totalCount;
}
#line 99 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00401DA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004024AC.s")

#line 104 "src/modules/uvisect_rom.c"



#line 107 "src/modules/uvisect_rom.c"
/* Return one when loaded texture byte 0x27 equals 0x0A, 0x11 or 0x1D,
 * or when the texture ID occurs in the registered integer list. The original
 * caller leaves its incoming A0 unchanged at TEXT slot 0x04; pass that ID
 * explicitly instead of relying on a guessed no-argument declaration.
 * RE_UNKNOWN: byte-code meaning and registered-list policy/ownership. Trace
 * original callers, list setters and texture metadata before interpreting them.
 * Missing-texture and sentinel handling remain in the existing texture getter;
 * this wrapper adds no other texture-ID validation. */
s32 uvIsectMatchesTextureByteOrIdList(s32 textureId) {
    s32 textureByte;
    s32 index;
    s32 *cursor;
    textureByte = D_uvisect_rom_00408204->uvTextureGetLoadedFlag27(textureId);
    if (textureByte == 0xA || textureByte == 0x11 || textureByte == 0x1D) return 1;
    for (index = 0, cursor = (s32 *)&D_uvisect_rom_00407880; index < D_uvisect_rom_0040787C; cursor++) {
            index++;
            if (textureId == *cursor) return 1;
    }
    return 0;
}
#line 119 "src/modules/uvisect_rom.c"
#line 105 "src/modules/uvisect_rom.c"

/* Select a scalar query result from shared mask-4 records or TERR slot 0x2C.
 * Preserve low-bit provider selection, low-16 mode consumption, ordered
 * tolerance/dot tests, texture filtering, callback reloads and full count return.
 * RE_ORIGINAL_QUIRK: capture the final point Z before TERR slot 0x14 writes
 * through a separate height-output address; its height does not replace point Z.
 * The supplied output record is written only after a result is selected.
 * RE_UNKNOWN: historical declarations/local storage, input-word/mode protocol,
 * buffer capacity/lifetime/aliases, vector frames and caller validity. TERR
 * slot 0x14 can leave its vector unwritten for a sentinel or unloaded terrain;
 * zero normal Z leaves height unwritten. Trace original query/input producers,
 * mode setters and packed-word/terrain validity before changing dependent reads
 * or replacing the assembly. */
#line 106 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00402B5C.s")
#line 107 "src/modules/uvisect_rom.c"

/* RE_ORIGINAL_QUIRK: the original plane-query fraction is assigned only
 * for a zero Z delta or when an endpoint Z compares <=0, after rejecting
 * positive endpoint products. Unordered Z comparisons, or unequal
 * positive finite Z values whose product becomes zero, can reach the
 * original stack0x48 fraction read without an assignment.
 * RE_UNKNOWN: caller input ranges and floating-point-mode reachability.
 * Trace original callers and the active floating-point exception mode
 * before claiming player impact or changing this preserved behavior. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403054.s")
#line 110 "src/modules/uvisect_rom.c"

#line 110 "src/modules/uvisect_rom.c"
/* Store words at 0x08/0x0C and the floating-point fraction at 0x2C. Copy the
 * supplied direction into 0x34 and point into 0x14, then clear 16-bit state 0x4C.
 * RE_UNKNOWN: word meanings, point/direction coordinate space, the state 0x4C
 * lifecycle and the complete record layout/ownership. Preserve unchecked inputs. */
void uvIsectInitializeScalarAndVectorQueryState(void *record, s32 word08, s32 word0C,
    f32 fraction, Vec3F *point, Vec3F *direction) {
    *(s32 *)((u8 *)record + 0x08) = word08;
    *(s32 *)((u8 *)record + 0x0C) = word0C;
    *(f32 *)((u8 *)record + 0x2C) = fraction;
    D_uvisect_rom_004081F4->uvVec3FCopy((Vec3F *)((u8 *)record + 0x34), direction);
    D_uvisect_rom_004081F4->uvVec3FCopy((Vec3F *)((u8 *)record + 0x14), point);
    *(u16 *)((u8 *)record + 0x4C) = 0;
}
#line 111 "src/modules/uvisect_rom.c"

/* Append accepted DOBJ query candidates to the supplied intersection records.
 * DOBJ slot 0x50 supplies parallel words, fractions and Vec3F values; QERY slot
 * 0x1C supplies auxiliary words. Cache the source pointer and its f32 at 0x0C,
 * then form each sqrt input by squaring in f32, subtracting from double 1.0,
 * and narrowing to f32. Native helper 0x404A7C may compact the owner records;
 * reload the owner count after the accepted candidate's record initializer.
 * RE_ORIGINAL_QUIRK: every append also initializes the next 0x58-stride record,
 * including after the final accepted result. A negative provider count still
 * invokes the auxiliary-array getter before skipping the loop.
 * RE_UNKNOWN: source scalar units, vector coordinate space, result-word
 * meanings, record capacity and shared-buffer lifetime/aliasing guarantees.
 * Trace owner allocation, actual DOBJ query producers and result consumers to
 * resolve these contracts. Retain original assembly until the paired 4-byte
 * and 12-byte buffer walks, pointer snapshots and complete instruction and
 * relocation records are matched by clean C. */
#line 112 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403208.s")

/* Append accepted TERR query candidates using the actual export at 0x90.
 * Preserve the cached source pointer/scalar, f32 square and f32 subtraction
 * before the square-root wrapper. Reload the shared fraction after native
 * helper 0x404A7C for scaling, then again after vector callbacks for the record
 * initializer. Capture the auxiliary element address before those callbacks
 * and read its word after the initializer; reload owner count before increment.
 * RE_ORIGINAL_QUIRK: every append also initializes the next 0x58-stride record,
 * including after the final accepted result. A negative provider count still
 * invokes the auxiliary-array getter before skipping the loop.
 * RE_UNKNOWN: source scalar units, vector coordinate space, result-word
 * meanings, record capacity and shared-buffer lifetime/aliasing guarantees.
 * Trace owner allocation, actual TERR query producers and result consumers to
 * resolve these contracts. Retain original assembly until clean C reproduces
 * complete native instructions, buffer read timing and relocation records. */
#line 114 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040344C.s")

/* Query actual TERR slot 0x20, skip auxiliary bit 2 and exclude registered
 * low-12-bit texture IDs obtained through actual TERR slot 0x1C. Preserve the
 * count snapshot after the texture callback, f32 square/subtraction and shared
 * fraction reloads after the owner filter and vector callbacks. Read the
 * auxiliary word again after the kind-1 record initializer, then reload and
 * increment the owner count before preparing the next record.
 * RE_ORIGINAL_QUIRK: the next 0x58-stride record is prepared even after the
 * final accepted result. Negative query counts still call the auxiliary-array
 * getter. Texture value 0xFFF receives the ordinary registered-ID test.
 * RE_UNKNOWN: auxiliary bit 2 and ID-list policy, scalar units, vector frame,
 * packed-word meanings, record capacity and shared-buffer lifetime/aliasing.
 * Trace actual query producers, ID-list setters, owner allocation and callers.
 * Keep original assembly until clean C matches native code and full relocations. */
#line 116 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004036A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040397C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403AB4.s")

#line 122 "src/modules/uvisect_rom.c"

/* Store the first incoming word masked to its low 16 bits in the first
 * shared word, then store the complete second word. The original also homes
 * the first incoming word. Retain the existing address-taken argument and
 * source-width prototype; this does not prove the historical C declaration.
 * RE_UNKNOWN: both shared words' meanings, caller domains and update
 * lifecycle. Trace original callers and readers before assigning flags/IDs
 * or narrowing either formal parameter. */
void uvIsectSetSharedWordPair(s32 low16Word, s32 storedWord) {
    s32 *firstWordHome;

    firstWordHome = &low16Word;
    D_uvisect_rom_004077BC = (*firstWordHome) & 0xFFFF;
    D_uvisect_rom_004078C4 = storedWord;
}
#line 129 "src/modules/uvisect_rom.c"

#line 130 "src/modules/uvisect_rom.c"
/* Append a value only if absent, preserving the original 16-bit scan index.
 * The original routine performs no capacity check; callers own the list limits. */
void uvIsectAppendUniqueValue(s32 value) {
    u16 index;
    for (index = 0; index < D_uvisect_rom_0040787C; index++) {
        if (value == ((s32 *)&D_uvisect_rom_00407880)[index]) return;
    }
    ((s32 *)&D_uvisect_rom_00407880)[D_uvisect_rom_0040787C] = value;
    D_uvisect_rom_0040787C++;
}
#line 131 "src/modules/uvisect_rom.c"

#line 132 "src/modules/uvisect_rom.c"
/* Scan the registered value array until a match or the original count limit.
 * Preserve 16-bit index updates. This original helper performs no state update;
 * RE_UNKNOWN: caller-observed export return value; audit original callers. */
void uvIsectScanRegisteredValues(s32 value) {
    s32 index;
    for (index = 0; index < D_uvisect_rom_0040787C; index = (u16)(index + 1)) {
        if (value == ((s32 *)&D_uvisect_rom_00407880)[index]) {
            break;
        }
    }
}
#line 133 "src/modules/uvisect_rom.c"

#line 134 "src/modules/uvisect_rom.c"
/* Return a registered value under the original upper-bound test.
 * RE_ORIGINAL_QUIRK: the test accepts index equal to count and negative
 * indices; preserve this matching behavior and the caller index contract. */
s32 uvIsectGetRegisteredValueAtIndex(s32 index) {
    if (D_uvisect_rom_0040787C < index) {
        return 0;
    }
    return *(s32 *)((u8 *)&D_uvisect_rom_00407880 + index * 4);
}
#line 140 "src/modules/uvisect_rom.c"

#line 141 "src/modules/uvisect_rom.c"
/* Return the registered-value count used by unique append and the
 * texture-ID membership test. */
s32 uvIsectGetRegisteredValueCount(void) {
    return D_uvisect_rom_0040787C;
}
#line 144 "src/modules/uvisect_rom.c"

#line 145 "src/modules/uvisect_rom.c"
/* Return the indexed integer/float query pair when the original inclusive
 * upper-bound check permits it. Outputs are unchanged on rejection. The query
 * parameter meaning and whether the bound is a count or last index are unknown. */
s32 uvIsectGetIndexedQueryPair(u16 index, s32 *value, f32 *parameter) {
    if (D_uvisect_rom_00407894 < index) return 0;
    *value = (&D_uvisect_rom_00407898)[index];
    *parameter = (&D_uvisect_rom_004078B0)[index];
    return 1;
}
#line 146 "src/modules/uvisect_rom.c"

#line 147 "src/modules/uvisect_rom.c"
/* Return the shared limit checked by the indexed query-pair getter.
 * RE_UNKNOWN: whether callers treat this value as count or final valid
 * index is unproven; the existing getter permits equality. */
u16 uvIsectGetIndexedQueryPairLimit(void) {
    return D_uvisect_rom_00407894;
}
#line 150 "src/modules/uvisect_rom.c"

#line 151 "src/modules/uvisect_rom.c"

/* Read the shared float written by ISCT slot 0x80.
 * RE_UNKNOWN: its physical units and full caller protocol; trace native
 * D_uvisect_rom_004077B8 consumers and original slot-0x80 callers. */
f32 uvIsectGetSharedScalar(void) {
    return D_uvisect_rom_004077B8;
}
#line 154 "src/modules/uvisect_rom.c"

#line 155 "src/modules/uvisect_rom.c"

/* Store the shared float exposed by original ISCT slot 0x80. Dynamics
 * update7C98 writes vector14BC length and later -1 through this exact slot.
 * RE_UNKNOWN: complete physical meaning, valid domain and cross-call
 * protocol; trace native D_uvisect_rom_004077B8 consumers and other callers. */
void uvIsectSetSharedScalar(f32 value) {
    D_uvisect_rom_004077B8 = value;
}
#line 158 "src/modules/uvisect_rom.c"

#line 159 "src/modules/uvisect_rom.c"
/* Get the packed triangle texture word through TERR slot 0x1C, mask its
 * low 12 bits, and compare TEXT slot 0x04's loaded texture byte 0x27 with the
 * low 16 bits of the caller's expected value. Return one on equality, else zero.
 * RE_UNKNOWN: metadata-byte meaning and caller policy for missing/sentinel
 * textures. The existing getter returns zero for those cases, so expected zero
 * can match; preserve that original behavior without adding a rejection. */
s32 uvIsectPackedTriangleTextureByteMatches(s32 terrainId, u32 handle, u16 expectedByte) {
    s32 textureWord;

    textureWord = D_uvisect_rom_00408200->getPackedTriangleTexture(terrainId, handle);
    if (expectedByte == D_uvisect_rom_00408204->uvTextureGetLoadedFlag27(textureWord & 0xFFF)) {
        return 1;
    }
    return 0;
}
#line 160 "src/modules/uvisect_rom.c"

#line 161 "src/modules/uvisect_rom.c"
/* Store/narrow the caller record byte at offset 0x10. */
void uvIsectSetRecordByte10(void *record, s8 value) {
    *(s8 *)((u8 *)record + 0x10) = value;
}
#line 164 "src/modules/uvisect_rom.c"

#line 165 "src/modules/uvisect_rom.c"

/* Read record byte0x10 as unsigned and return its value in the existing
 * signed-word ABI. RE_UNKNOWN: byte meaning and valid record lifetime;
 * trace the setter, original producers and consumers before naming flag bits.
 * Preserve the unchecked record access and the setter's low-byte storage. */
s32 uvIsectGetRecordByte10(void *record) {
    return *(u8 *)((u8 *)record + 0x10);
}
#line 168 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403E94.s")

#line 171 "src/modules/uvisect_rom.c"

/* Flip the stored vector when its dot with point14-reference is positive.
 * Kind 1 rejects packed terrain-texture bits 20/19. Kinds 2/8 require mode04
 * zero, linked-record flag bit 0 and clear record flag 0x20; other kinds return
 * zero. Reject displacement length below the original f32 threshold first.
 * A flip negates vector34 and also value2C when mode04 is one; return one only
 * when the flip occurs. Keep original comparisons, including unordered cases.
 * RE_UNKNOWN: kind/flag roles, linked-record lifetime, coordinate units and
 * value2C's meaning; trace record constructors and callers before assigning a
 * normal/distance interpretation or strengthening pointer/input checks. */
s32 uvIsectFlipRecordVectorTowardPoint(IsectFacingRecordPrefix *record,
    Vec3F *reference, s32 terrainId) {
    f32 length;
    f32 dot;
    Vec3F displacement;
    s32 packedTexture;

    switch (record->kind08) {
        case 1:
            packedTexture = D_uvisect_rom_00408200->getPackedTriangleTexture(
                terrainId, record->triangleHandle0C);
            if ((packedTexture & 0x100000) != 0 || (packedTexture & 0x80000) != 0) {
                return 0;
            }
            break;
        case 2:
        case 8:
            if (record->mode04 == 0 && (record->linkedRecord->flags18 & 1) != 0) {
                if ((record->flags10 & 0x20) != 0) {
                    return 0;
                }
            } else {
                return 0;
            }
            break;
        case 4:
        default:
            return 0;
    }
    displacement.x = record->point14.x - reference->x;
    displacement.y = record->point14.y - reference->y;
    displacement.z = record->point14.z - reference->z;
    length = D_uvisect_rom_004081F4->uvVec3FLen(&displacement);
    if (length < D_uvisect_rom_004076C4) {
        return 0;
    }
    dot = D_uvisect_rom_004081F4->uvVec3FDot(&displacement, &record->vector34);
    if (0.0f < dot) {
        record->vector34.x = -record->vector34.x;
        record->vector34.y = -record->vector34.y;
        record->vector34.z = -record->vector34.z;
        if (record->mode04 == 1) {
            record->value2C = -record->value2C;
        }
        return 1;
    }
    return 0;
}
#line 172 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404100.s")

#line 175 "src/modules/uvisect_rom.c"
/* Copy the complete 88-byte intersection record, including opaque fields. */

void uvIsectCopyRecord(IsectCopyRecord88 *destination, IsectCopyRecord88 *source) {
    *destination = *source;
}
#line 176 "src/modules/uvisect_rom.c"

/* Copy the input point twice, subtract the supplied span from the first Z,
 * and explicitly zero the local query word 0x18. Run flag-2, flag-8 and scalar
 * queries in that order, retaining native ordered comparisons of value 0x2C.
 * RE_ORIGINAL_QUIRK: scalar-only success returns with the scalar helper's
 * outputs. General success writes the adjusted scalar before the selected
 * handle, calls 0x403F38, then copies vector 0x34 through actual FVEC slot 0x1C.
 * No selection writes handle 4, scalar 0 and vector (0, 0, 1).
 * RE_UNKNOWN: historical return declaration, vector frame, scalar/span units,
 * nonzero-span caller guarantee, pointer alias/lifetime, successful-helper
 * output validity and original scratch declarations. Trace original slot-0xA0
 * callers, record producers and original build declarations before changing
 * these contracts or replacing the native assembly. */
#line 177 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040423C.s")

#line 179 "src/modules/uvisect_rom.c"
/* TERR slot28 supplies the low-byte triangle-list count at point XY;
 * slot14 samples a scalar/vector for each triangle. Mode0 selects the greatest
 * scalar <= pointZ, mode1 the least scalar >= pointZ; mode2 retains the native
 * signed-subtraction/negation comparisons, choosing mode1 on equal differences.
 * Preserve native sentinels and ordered predicates. Missing mode0 output writes
 * vector Y0/X0/Z1 then scalar0, leaving the handle; other failure paths leave
 * outputs unchanged. Successful outputs store handle, scalar, then vector XYZ.
 * RE_UNKNOWN: physical meaning/frame of scalar and vector, valid mode/domain,
 * triangle-list lifetime and provider output guarantees for invalid triangles
 * or zero normal Z. Trace original callers and the actual TERR slot14/28
 * providers/assets before generalizing the query or adding fallback behavior. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004045A8.s")
#line 180 "src/modules/uvisect_rom.c"

#line 181 "src/modules/uvisect_rom.c"

/* Run the selected original queries in flag order 2, 8, 1, 4, keeping the
 * successful 88-byte candidate with a strictly smaller value at offset 0x2C.
 * Equal values retain the earlier candidate; unordered comparisons do not win.
 * Accept only a final minimum <=1, then clear output word at0x04 before replacing
 * output word at0x00 with the input address. Failed queries leave output intact
 * except for any earlier successful minimum update, as in the native code.
 * RE_UNKNOWN: complete query-input layout, vector frame, flag/forwarded-word
 * meanings and valid input domains. Trace original callers and direct helper
 * bodies before assigning physical meanings or strengthening validation.
 * RE_ORIGINAL_QUIRK: the flag-4 helper 0x403054 retains its separately indexed
 * fraction-assignment observation. Helper success is the sole candidate-copy gate;
 * do not initialize candidate fields or alter those original helper semantics.
 * Flag 2 also forwards input word 0x18 through helper 0x4014FC. */
#line 195 "src/modules/uvisect_rom.c"

s32 uvIsectQueryMinimumValueRecord(IsectQueryInputPrefix *input, u32 queryFlags,
    s32 queryWord, s32 contextWord, IsectCopyRecord88 *output) {
    f32 minimumValue;
    IsectCopyRecord88 candidate;

    minimumValue = D_uvisect_rom_004076DC;
    if (queryFlags & 2) {
        if (uvIsectQueryInputVectorsIntoRecord(input, 2, contextWord, queryWord,
                &candidate)) {
            uvIsectUpdateMinimumValueRecord(output, &minimumValue, &candidate);
        }
    }
    if (queryFlags & 8) {
        if (func_uvisect_rom_004024AC(&input->second, &input->first,
                input->word18, queryWord, &candidate, 0)) {
            uvIsectUpdateMinimumValueRecord(output, &minimumValue, &candidate);
        }
    }
    if (queryFlags & 1) {
        if (func_uvisect_rom_00402B5C(&input->second, &input->first,
                input->word18, queryWord, &candidate, 0)) {
            uvIsectUpdateMinimumValueRecord(output, &minimumValue, &candidate);
        }
    }
    if (queryFlags & 4) {
        if (func_uvisect_rom_00403054(&input->second, &input->first,
                &candidate)) {
            uvIsectUpdateMinimumValueRecord(output, &minimumValue, &candidate);
        }
    }
    if (minimumValue <= 1.0f) {
        output->unk00[1] = 0;
        output->unk00[0] = (u32)input;
        return 1;
    }
    return 0;
}
#line 232 "src/modules/uvisect_rom.c"
#line 182 "src/modules/uvisect_rom.c"

#line 183 "src/modules/uvisect_rom.c"
/* Replace the 88-byte record only when its value at offset 0x2C is smaller
 * than the running minimum. The value meaning is unknown; equal values keep
 * the existing record and NaNs follow the original floating-point comparison. */
s32 uvIsectUpdateMinimumValueRecord(IsectCopyRecord88 *destination, f32 *minimumValue, IsectCopyRecord88 *candidate) {
    if (candidate->value2C < *minimumValue) {
        *minimumValue = candidate->value2C;
        uvIsectCopyRecord(destination, candidate);
        return 1;
    }
    return 0;
}
#line 184 "src/modules/uvisect_rom.c"

/* Filter against existing 0x58-stride owner records and compact selected
 * records, preserving live owner-count reloads and original u16 induction.
 * RE_ORIGINAL_QUIRK: selection stores full record pointers at native stack
 * offset 0x8C + index * 4, while compaction reads u16 values starting at 0x130.
 * The first 0x130 read occurs whenever selectedCount is nonzero, before the
 * compaction bound test. One through 41 sequential pointer stores do not reach
 * that offset; the 42nd would overlap it. Preserve the native code unchanged.
 * RE_UNKNOWN: scratch/index provenance, valid owner count and caller reachability
 * of these paths. Trace original owner constructors/callers and callback effects
 * before treating the halfword words as initialized indices or claiming a bug. */
#line 185 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404A7C.s")

#line 187 "src/modules/uvisect_rom.c"

/* Scan the shared 0x78-byte records whose parallel filter word intersects mask.
 * The original helper appends results for the two input vectors. Expose shared
 * buffers only when at least one result exists; preserve optional-output store
 * order even when caller output pointers alias.
 * RE_ORIGINAL_QUIRK: the iteration index wraps to 16 bits, and the signed record
 * bound is reloaded only after a matching record invokes the helper.
 * RE_UNKNOWN: record kinds, vector coordinate space, result-word meanings and
 * valid shared-buffer capacity/lifetime. Trace shared-query setter callers and
 * helper 0x405124/result consumers before strengthening these contracts. */
s32 uvIsectQueryFilteredSharedRecords(u32 mask, Vec3F *first, Vec3F *second,
    u32 **outRecordWords, f32 **outScalars, Vec3F **outVectors,
    u32 **outFilterWords, u32 **outRecord74Words) {
    u8 *record;
    u32 *filterWord;
    u32 *recordWord;
    s32 index;
    s32 resultCount;

    record = (u8 *)D_uvisect_rom_004078E4;
    filterWord = (u32 *)D_uvisect_rom_004078EC;
    recordWord = (u32 *)D_uvisect_rom_004078E8;
    resultCount = 0;
    for (index = 0; index < D_uvisect_rom_004078E0; index = (u16)(index + 1)) {
        if ((*filterWord & mask) != 0) {
            func_uvisect_rom_00405124(&resultCount, record, first, second,
                recordWord, filterWord);
        }
        record += 0x78;
        filterWord++;
        recordWord++;
    }
    if (resultCount != 0) {
        if (outRecordWords != NULL) {
            *outRecordWords = D_uvisect_rom_004078F0;
        }
        if (outVectors != NULL) {
            *outVectors = D_uvisect_rom_00407A70;
        }
        if (outScalars != NULL) {
            *outScalars = D_uvisect_rom_00407EF0;
        }
        if (outFilterWords != NULL) {
            *outFilterWords = D_uvisect_rom_00408070;
        }
        if (outRecord74Words != NULL) {
            *outRecord74Words = D_uvisect_rom_00408130;
        }
    }
    return resultCount;
}
#line 188 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404ED4.s")

/* Append triangle or transformed-bounds intersections to shared result arrays.
 * Original ISCT here is uvintersect: slot 0x40 consumes the supplied normal and
 * may write the fraction before rejecting a triangle. MODL slot 0x30 returns
 * 0/1/2/3; append only results 1/2, preserving the full-word/low-byte tests.
 * Snapshot the optional filter word; reread the record word and field 0x74 for
 * each append. Triangle success copies the normal before shared-word stores;
 * bounds success writes words/fraction before calling 0x4054F4 for its vector.
 * RE_ORIGINAL_QUIRK: triangle rejection leaves the count address untouched;
 * bounds rejection writes the cached count. The signed-16 loop increment and
 * ordered dot/mask gate remain in the native assembly, including NaN behavior.
 * RE_UNKNOWN: historical return and scratch declarations, record/frame/units,
 * raw flags, buffer capacity/count domain and pointer alias/lifetime. Trace
 * original callers, record producers and shared-buffer setters before changing
 * these contracts or replacing the assembly. */
#line 191 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405124.s")
#line 192 "src/modules/uvisect_rom.c"

/* Select signed columns from record offsets 0x30/0x40/0x50, 0x34/0x44/0x54,
 * or 0x38/0x48/0x58 for selectors +/-1, +/-2 or +/-3, then normalize the
 * destination in place through the original FVEC slot 0x08 and return its status.
 * Preserve interleaved source reads and output stores; overlap is not excluded.
 * RE_ORIGINAL_QUIRK: zero and unsupported signed-low16 selectors normalize the
 * existing destination without initializing it. Native code homes the incoming
 * full selector word before narrowing it; preserve the original assembly.
 * RE_UNKNOWN: column role/frame, historical declaration, record/output lifetime,
 * overlap and caller initialization for unsupported selectors. Trace original
 * producers and export consumers. The seven-entry native table at 0x4076E4 and
 * surrounding readonly bytes remain original-owned; any C recovery must prove
 * their targets and retain the separate table at 0x40771C. */
#line 193 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004054F4.s")

#line 195 "src/modules/uvisect_rom.c"
/* Select the side with the smallest signed XY face margin: +1/+2 select
 * maximum X/Y and -1/-2 minimum X/Y. Equal margins keep the first side.
 * RE_UNKNOWN: whether callers guarantee the point is inside the bounds. The
 * helper takes no absolute values and performs no containment check, so this
 * is not a general nearest-face calculation for outside points. Trace original
 * callers before relying on an inside-point precondition. */
#line 198 "src/modules/uvisect_rom.c"
typedef struct {
    f32 minimum[3];
    f32 maximum[3];
} IsectBounds;
#line 201 "src/modules/uvisect_rom.c"

s32 uvIsectFindMinimumSignedBoxMarginSide(IsectBounds *bounds, f32 *point) {
    f32 distance;
    f32 candidate;
    s32 side;
    distance = bounds->maximum[0] - point[0];
    side = 1;
    candidate = bounds->maximum[1] - point[1];
    if (candidate < distance) { distance = candidate; side = 2; }
    candidate = point[0] - bounds->minimum[0];
    if (candidate < distance) { distance = candidate; side = -1; }
    candidate = point[1] - bounds->minimum[1];
    if (candidate < distance) side = -2;
    return side;
}
#line 215 "src/modules/uvisect_rom.c"
#line 196 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405698.s")

/* Query transformed endpoints, then derive and orient the selector-dependent
 * output axis through the original FMTX and FVEC providers. Preserve the 1.1f
 * fallback write at 0x2C before failure gates, ordered scalar tests, helper
 * argument order, component-store order and the final input-divisor snapshot.
 * RE_ORIGINAL_QUIRK: an unsupported selector leaves vector 0x40 unchanged
 * before normalization; both normalization return values are ignored. Whether
 * that path is reached depends on the direct helper and input/alias contracts.
 * RE_UNKNOWN: historical declarations/local storage, vector frames, divisor
 * validity, record extent/aliases and selector/output initialization. Trace
 * original callers, input producers and helper 0x405EDC/0x405C8C success paths.
 * The 32 native selector-table entries remain assembly-owned. Resolve the
 * instruction/local-storage differences before any readonly ownership change;
 * a readable draft has not matched the complete original instructions. */
#line 199 "src/modules/uvisect_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405794.s")
#line 200 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405EDC.s")

#line 205 "src/modules/uvisect_rom.c"
/* Clear the value-record registry count without freeing registered
 * records or overwriting its pointer array. Preserve existing ownership. */
void uvIsectResetValueRecordRegistryCount(void) {
    D_uvisect_rom_00407820 = 0;
}
#line 208 "src/modules/uvisect_rom.c"

#line 209 "src/modules/uvisect_rom.c"
/* Allocate and clear the original 0x348-byte value record, register it at
 * the current 16-bit index, store that index and advance the registry count.
 * Preserve the original lack of allocation-failure and registry-capacity checks. */
IsectValueRecord *uvIsectCreateValueRecord(void) {
    IsectValueRecord *record;
    record = _uvMemAllocAlign8(0x348);
    uvMemSet(record, 0, 0x348);
    ((IsectValueRecord **) &D_uvisect_rom_004077D0)[D_uvisect_rom_00407820] = record;
    record->unk00 = D_uvisect_rom_00407820;
    D_uvisect_rom_00407820++;
    return record;
}
#line 210 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00407250.s")

#line 213 "src/modules/uvisect_rom.c"
/* Convert the scalar to a signed word at record offset four only for
 * a nonnull record and property one. Leave other properties unchanged. */
void uvIsectSetIntegerPropertyOneFromFloat(void *record, s32 property, f32 value) {
    if ((record != NULL) && (property == 1)) {
        (*(s32 *)((u8 *)record + 0x4)) = (s32) value;
    }
}
#line 218 "src/modules/uvisect_rom.c"

#line 219 "src/modules/uvisect_rom.c"
/* Convert record word four to float only for property one; return -1
 * for a null record or other property. */
f32 uvIsectGetIntegerPropertyOneAsFloat(void *record, s32 property) {
    if (record == NULL) {
        return -1.0f;
    }
    if (property == 1) {
        return (f32) (*(s32 *)((u8 *)record + 0x4));
    }
    return -1.0f;
}
#line 228 "src/modules/uvisect_rom.c"

#line 229 "src/modules/uvisect_rom.c"
/* Append an absent value and its attribute to a kind-zero record. Preserve
 * the original 16-bit scan and unchecked capacity; a duplicate leaves both
 * the existing attribute and count unchanged. Callers own storage limits. */
void uvIsectAppendUniqueRecordValue(IsectValueRecord *record, s32 value, s32 attribute) {
    u16 index;
    if (record == NULL) return;
    if (record->kind != 0) return;
    for (index = 0; index < record->count; index++) {
        if (value == ((s32 *) ((u8 *) record + 0xC))[index]) return;
    }
    ((s32 *) ((u8 *) record + 0xC))[record->count] = value;
    ((s32 *) ((u8 *) record + 0x28C))[record->count] = attribute;
    record->count++;
}
#line 230 "src/modules/uvisect_rom.c"

#line 231 "src/modules/uvisect_rom.c"
/* Scan kind-zero records using their count-prefixed value list and original
 * 16-bit index updates. Null/other-kind records are ignored. The original scan
 * performs no state update. RE_UNKNOWN: caller-observed return; trace export callers. */
void uvIsectScanRecordValues(IsectValueRecord *record, s32 value) {
    IsectCountedValues *list;
    s32 index;
    if (record != NULL && record->kind == 0) {
        list = (IsectCountedValues *)&record->count;
        for (index = 0; index < list->count; index = (u16)(index + 1)) {
            if (value == list->values[index]) {
                break;
            }
        }
    }
}
#line 232 "src/modules/uvisect_rom.c"

#line 233 "src/modules/uvisect_rom.c"
/* Store the attribute at offset 0x28C for a kind-zero record. Preserve the
 * original inclusive count check and lack of a negative-index check. The array
 * capacity is not established; callers must supply a valid index. */
void uvIsectSetValueAttribute(IsectValueRecord *record, s32 index, s32 attribute) {
    if (record == NULL) return;
    if (record->kind != 0) return;
    if (record->count < index) return;
    ((s32 *) ((u8 *) record + 0x28C))[index] = attribute;
}
#line 234 "src/modules/uvisect_rom.c"

#line 235 "src/modules/uvisect_rom.c"
/* Read the value at offset 0x0C for a kind-zero record, or return zero on the
 * original rejection paths. The inclusive count check and unchecked negative
 * index are original behavior; callers must supply a valid index. */
s32 uvIsectGetIndexedValue(IsectValueRecord *record, s32 index) {
    if (record == NULL) return 0;
    if (record->kind != 0) return 0;
    if (record->count < index) return 0;
    return ((s32 *) ((u8 *) record + 0xC))[index];
}
#line 236 "src/modules/uvisect_rom.c"

#line 237 "src/modules/uvisect_rom.c"
/* Return record word eight only for a nonnull record whose word four
 * is zero; return zero otherwise. */
s32 uvIsectGetZeroTypeRecordWord(void *record) {
    if (record == NULL) {
        return 0;
    }
    if ((*(s32 *)((u8 *)record + 0x4)) != 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)record + 0x8));
}
#line 246 "src/modules/uvisect_rom.c"

#line 247 "src/modules/uvisect_rom.c"
typedef struct UvIntersectionPayload_s { s32 unk0; s32 kind; u8 payload[1]; } UvIntersectionPayload;
/* Only kind-one intersection records expose their inline payload. */
void *uvIsectGetKindOnePayload(UvIntersectionPayload *record) {
 if (record == NULL) return NULL;
 if (record->kind != 1) return NULL;
 return record->payload;
}
#line 248 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00407554.s")

#line 251 "src/modules/uvisect_rom.c"
/* For kind-zero records, copy into the first or second vector in an
 * indexed 0x1C-byte region. Preserve the original inclusive index limit and
 * absence of a negative-index check; callers own those bounds. Unsupported
 * vector selectors and invalid record kinds leave the record unchanged. */
void uvIsectSetIndexedVector(IsectValueRecord *record, s32 index, s32 which, Vec3F *value) {
    if (record != NULL && record->kind == 0 && record->count >= index) {
        switch (which) {
            case 0:
                D_uvisect_rom_004081F4->uvVec3FCopy((Vec3F *)((u8 *)record + index * 0x1C + 0x5C), value);
                return;
            case 1:
                D_uvisect_rom_004081F4->uvVec3FCopy((Vec3F *)((u8 *)record + index * 0x1C + 0x68), value);
                break;
        }
    }
}
#line 252 "src/modules/uvisect_rom.c"

