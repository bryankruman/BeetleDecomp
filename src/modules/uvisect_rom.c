// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvtexture_rom.h"
/* Original initializer imports TEXT here. Its slot0x04 consumes the incoming
 * texture ID and returns loaded texture byte0x27; it is not a game-state getter. */
extern UvTexture_Exports *D_uvisect_rom_00408204;
typedef struct { s32 count; s32 values[1]; } IsectCountedValues; /* Variable-length original allocation. */
typedef struct { u8 unk00[0xC]; s32 value0C; u8 unk10[2]; u16 value12; u16 value14; } IsectScalarPrefix;

typedef struct { s32 registryIndex; u8 unk04[0xF10]; } IsectLargeRecord;
extern IsectLargeRecord *D_uvisect_rom_00407828;
extern u16 D_uvisect_rom_00407878;
void uvIsectSetPropertyWord08(void *record, s32 property);

#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct { u8 unk00[0xE84]; Mtx4F transform; Vec3F vectorEC4; } IsectTransformPrefix;
extern UvFMtx_Rom_Exports *D_uvisect_rom_004081F0;
extern UvFVec_Rom_Exports *D_uvisect_rom_004081F4;
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
 * unsupported properties; the scalar field meanings remain unknown. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400920.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004009F0.s")

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
/* Read the original 32-bit word at offset 0x18. Its full meaning is not yet
 * established; preserve the original non-null caller contract. */
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
/* Store the four original shared query words in their original order.
 * Consumers must establish more specific parameter names and constraints. */
void uvIsectSetSharedQueryWords(s32 first, s32 second, s32 third, s32 fourth) {
    D_uvisect_rom_004078E0 = first;
    D_uvisect_rom_004078E4 = second;
    D_uvisect_rom_004078E8 = third;
    D_uvisect_rom_004078EC = fourth;
}
#line 95 "src/modules/uvisect_rom.c"

#line 84 "src/modules/uvisect_rom.c"
/* Store query parameters in the active bank. Mode 2 alternates banks 1 and 2;
 * other modes replace the state directly. Mode 0 stores no parameters.
 * Parameter meanings remain opaque; preserve their original 16/32-bit widths. */
void uvIsectSetQueryParameterBank(s32 mode, u16 first, u16 second, s32 third, s32 fourth) {
    if (mode == 2) {
        if (D_uvisect_rom_004077C0 == 1) D_uvisect_rom_004077C0 = mode;
        else D_uvisect_rom_004077C0 = 1;
    } else D_uvisect_rom_004077C0 = mode;
    switch (D_uvisect_rom_004077C0) {
    case 1:
        D_uvisect_rom_004078C8 = first;
        D_uvisect_rom_004078CA = second;
        D_uvisect_rom_004078CC = third;
        D_uvisect_rom_004078D0 = fourth;
        return;
    case 2:
        D_uvisect_rom_004078D4 = first;
        D_uvisect_rom_004078D6 = second;
        D_uvisect_rom_004078D8 = third;
        D_uvisect_rom_004078DC = fourth;
    case 0: return;
    }
}
#line 85 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400DC0.s")

#line 90 "src/modules/uvisect_rom.c"
/* Initialize the owner result, then append an entry when fewer than 40 are
 * pending. Return one on insertion and zero when full; opaque fields stay opaque. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004013F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004014FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00401558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004017D8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00402B5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040318C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040344C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004036A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040397C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403AB4.s")

void func_uvisect_rom_00403CAC(s32 arg0, s32 arg1)
{
  s32 *new_var;
  new_var = &arg0;
  D_uvisect_rom_004077BC = (*new_var) & 0xFFFF;
  D_uvisect_rom_004078C4 = arg1;
}

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
 * its export return-value contract remains a caller-audit item. */
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
/* Return the current registered-value count used by unique append
 * and current-state membership testing. */
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

f32 func_uvisect_rom_00403E0C(void) {
    return D_uvisect_rom_004077B8;
}

void func_uvisect_rom_00403E18(f32 arg0) {
    D_uvisect_rom_004077B8 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403E24.s")

#line 161 "src/modules/uvisect_rom.c"
/* Store/narrow the caller record byte at offset 0x10. */
void uvIsectSetRecordByte10(void *record, s8 value) {
    *(s8 *)((u8 *)record + 0x10) = value;
}
#line 164 "src/modules/uvisect_rom.c"

s32 func_uvisect_rom_00403E8C(void *arg0) {
    return *(u8 *)((u8 *)arg0 + 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403E94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404100.s")

#line 175 "src/modules/uvisect_rom.c"
/* Copy the complete 88-byte intersection record, including opaque fields. */
typedef struct { u32 unk00[11]; f32 value2C; u32 unk30[10]; } IsectCopyRecord88;
void uvIsectCopyRecord(IsectCopyRecord88 *destination, IsectCopyRecord88 *source) {
    *destination = *source;
}
#line 176 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040423C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004045A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004048DC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404D74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404ED4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004054F4.s")

#line 195 "src/modules/uvisect_rom.c"
/* Return the nearest side in the XY projection of the bounding box: +1/+2
 * select maximum X/Y and -1/-2 minimum X/Y. Equal distances keep the first side. */
typedef struct {
    f32 minimum[3];
    f32 maximum[3];
} IsectBounds;
s32 uvIsectFindNearestBoxSide(IsectBounds *bounds, f32 *point) {
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
#line 196 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405794.s")

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
void uvIsectSetTypeOneRecordValue(void *record, s32 property, f32 value) {
    if ((record != NULL) && (property == 1)) {
        (*(s32 *)((u8 *)record + 0x4)) = (s32) value;
    }
}
#line 218 "src/modules/uvisect_rom.c"

#line 219 "src/modules/uvisect_rom.c"
/* Convert record word four to float only for property one; return -1
 * for a null record or other property. */
f32 uvIsectGetTypeOneRecordValue(void *record, s32 property) {
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
 * performs no state update; its export return-value contract remains unproven. */
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

