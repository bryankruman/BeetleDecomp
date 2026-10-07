// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 prefix[0x34]; f32 (*mapDot)(f32); } ReplayDotExports;
#include "fileux.h"
typedef struct { u8 prefix[0xF0]; FileUx_Exports *(*loadFileModule)(void); } ReplayFileModuleExports;
typedef struct { u8 prefix[0x2C]; u8 *nameRecord; } ReplaySceneNameExports;
typedef struct { s32 value0, frameCount, value8, eventBytes; } ReplayWriteHeader;
extern ReplaySceneNameExports *gSceneExports;
extern char D_replay_00401AE4[], D_replay_00401AF4[];

#include "uvfvec_rom.h"
typedef struct ReplaySpatialRecord { Vec3F first, second; f32 value; f32 radiusSquared; struct ReplaySpatialRecord *next; } ReplaySpatialRecord;
extern ReplaySpatialRecord *D_replay_00401B60;
#include "uvmath_rom.h"
extern void *gMiscExports;
extern UvMath_Exports *gUvMathExports;
typedef struct { u8 unk00[0x11C]; void (*seedRandom)(s32); } ReplayMiscSeedExports;
typedef struct { u8 unk00[0x190]; s32 word190; u8 unk194[4]; s32 word198; } ReplaySettingsView;
typedef struct { s32 flags; u8 unk04[0x10]; } ReplayFlagRecord; /* Original stride 20 bytes. */
/*__SEEDEXTERNS__*/
extern u8 D_replay_00401AC0;
extern u8 D_replay_00401AC8;
extern u8 D_replay_00401AD4;
extern u8 D_replay_00401ADC;
extern u8 D_replay_00401B50;
extern u8 D_replay_00401B54;
extern u8 D_replay_00401B58;
extern void *gUvFvecExports;
extern void *D_replay_00401B64;
extern f32 D_replay_00401BA0;
void replayPrependSpatialRecord(f32 x, f32 y, f32 z, f32 radius, f32 secondX, f32 secondY, f32 secondZ, f32 value);
void replayResetStateAndRandomSeeds(void);
void func_replay_00400328();
void func_replay_00400748();
void func_replay_0040097C();
void func_replay_00400C50();
void func_replay_00400D84();
s32 replayHasNewRecordFlags();
s32 replayHasRecordFlags(s32 index, s32 mask);
f32 replayGetRecordScalar(s32 arg0, s32 arg1);
void func_replay_0040100C();
ReplaySpatialRecord *replayFindDirectedSpatialRecord(Vec3F *position, Vec3F *direction, f32 *distance);
void replayWriteVersionTwoFile(ReplayWriteHeader *state);
void func_replay_00401968();
extern u8 D_replay_00401B7C;
extern u8 D_replay_00401B78;
extern s32 D_replay_00401B98;
extern s32 D_replay_00401B9C;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/__entrypoint_func_replay_400000.s")

#line 51 "src/modules/replay.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_replay_0040017C(void) {
}
#line 53 "src/modules/replay.c"

#line 54 "src/modules/replay.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_replay_00400184(void) {
}
#line 56 "src/modules/replay.c"

#line 49 "src/modules/replay.c"
/* Allocate and prepend a 36-byte replay record containing two vectors, an
 * opaque scalar and the fourth parameter squared. Preserve call/store order
 * and the original allocation contract; vector roles remain unspecified. */
void replayPrependSpatialRecord(f32 x, f32 y, f32 z, f32 radius, f32 secondX, f32 secondY, f32 secondZ, f32 value) {
    ReplaySpatialRecord *record = _uvMemAllocAlign8(sizeof(ReplaySpatialRecord));
    ((UvFVec_Rom_Exports *)gUvFvecExports)->uvVec3FSet(&record->first, x, y, z);
    ((UvFVec_Rom_Exports *)gUvFvecExports)->uvVec3FSet(&record->second, secondX, secondY, secondZ);
    record->value = value;
    record->radiusSquared = radius * radius;
    record->next = D_replay_00401B60;
    D_replay_00401B60 = record;
}
#line 50 "src/modules/replay.c"

#line 51 "src/modules/replay.c"
/* Allocate and prepend a 20-byte record: vector export slot 4 writes the
 * first three words, followed by radius squared and the previous list head.
 * RE_UNKNOWN: point/list consumer roles and whether the third parameter
 * should be typed as a float; preserve its current raw-word s32 ABI.
 * RE_ORIGINAL_QUIRK: allocation is unchecked. */
void replayPrependPointRadiusRecord(f32 x, f32 y, s32 rawZWord, f32 radius) {
    void *record = _uvMemAllocAlign8(0x14);
    ((void (*)(void *, f32, f32, s32))(*(s32 *)((u8 *)gUvFvecExports + 0x4)))(record, x, y, rawZWord);
    *(f32 *)((u8 *)record + 0xC) = radius * radius;
    *(s32 *)((u8 *)record + 0x10) = (s32)D_replay_00401B64;
    D_replay_00401B64 = record;
}
#line 58 "src/modules/replay.c"

#line 59 "src/modules/replay.c"
/* Store the low eight bits of the argument in D_replay_00401B7C.
 * RE_UNKNOWN: shared byte purpose and caller/export contract. */
void func_replay_004002A8(s32 a0) {
    D_replay_00401B7C = (u8)a0;
}
#line 62 "src/modules/replay.c"

#line 60 "src/modules/replay.c"
/* Clear the original replay settings words/timer, seed both random number
 * generators with 12345 and mark replay active. The two settings words remain
 * offset-named because their full meaning is not yet established. */
void replayResetStateAndRandomSeeds(void) {
    ((ReplaySettingsView *)gGameSettings)->word190 = 0;
    ((ReplaySettingsView *)gGameSettings)->word198 = 0;
    gGameSettings->unk7C = 0.0f;
    gUvMathExports->uvSrand(12345);
    ((ReplayMiscSeedExports *)gMiscExports)->seedRandom(12345);
    D_replay_00401B78 = 1;
}
#line 61 "src/modules/replay.c"

#line 62 "src/modules/replay.c"
/* Clear the original shared replay-active flag. */
void replayClearActiveFlag(void) {
    D_replay_00401B78 = 0;
}
#line 65 "src/modules/replay.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400328.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400748.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040097C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400D84.s")

#line 76 "src/modules/replay.c"
/* Return one when requested bits are set in the current record word
 * and absent in its previous word. Preserve the original any-bit tests
 * and caller-owned 20-byte record index. */
s32 replayHasNewRecordFlags(s32 index, s32 mask) {
    u8 *record = (u8 *)&D_replay_00401B98 + index * 20;
    if (*(s32 *)record & mask && !(*(s32 *)(record + 4) & mask)) {
        return 1;
    }
    return 0;
}
#line 83 "src/modules/replay.c"

#line 84 "src/modules/replay.c"
/* Return the current flag word from the original 20-byte record.
 * Index validity remains the caller contract. */
s32 replayGetRecordFlags(s32 index) {
    return *(s32*)((u8*)&D_replay_00401B98 + index * 20);
}
#line 87 "src/modules/replay.c"

#line 88 "src/modules/replay.c"
/* Return the previous flag word from the original 20-byte record.
 * Index validity remains the caller contract. */
s32 replayGetPreviousRecordFlags(s32 index) {
    return *(s32*)((u8*)&D_replay_00401B9C + index * 20);
}
#line 91 "src/modules/replay.c"

#line 87 "src/modules/replay.c"
/* Return one if any requested bit is set in this 20-byte replay record.
 * The original caller owns index bounds; zero masks return zero. */
s32 replayHasRecordFlags(s32 index, s32 mask) {
    s32 result;
    if (((ReplayFlagRecord *)&D_replay_00401B98)[index].flags & mask) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
#line 88 "src/modules/replay.c"

#line 89 "src/modules/replay.c"
/* Return a floating component from the original 20-byte record at
 * offset eight plus component times four. Both indices remain caller-owned. */
f32 replayGetRecordScalar(s32 index, s32 component) {
    return *(f32 *)((u8 *)&D_replay_00401BA0 + (index * 0x14) + (component * 4));
}
#line 92 "src/modules/replay.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040100C.s")

#line 95 "src/modules/replay.c"
/* Find the first replay record whose strict radius and mapped direction-dot
 * tests contain the supplied position. Return that record and write normalized
 * displacement plus distance; zero distance retains its zero displacement.
 * Outputs are untouched on failure.
 * RE_UNKNOWN: record vector and threshold units. Trace original record writers,
 * loaded data and their gameplay consumers before assigning physical units. */
#line 100 "src/modules/replay.c"
ReplaySpatialRecord *replayFindDirectedSpatialRecord(Vec3F *position, Vec3F *direction, f32 *distance) {
    Vec3F delta;
    ReplaySpatialRecord *record;
    f32 squared;
    f32 length;
    record = D_replay_00401B60;
    while (record != NULL) {
        ((UvFVec_Rom_Exports *)gUvFvecExports)->uvVec3FSub(&delta, position, &record->first);
        squared = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
        if (squared < record->radiusSquared) {
            length = gUvMathExports->uvSqrtf(squared);
            if (length > 0.0f) {
                delta.x /= length;
                delta.y /= length;
                delta.z /= length;
            }
            if (((ReplayDotExports *)gMiscExports)->mapDot(((UvFVec_Rom_Exports *)gUvFvecExports)->uvVec3FDot(&record->second, &delta)) < record->value) {
                *direction = delta;
                *distance = length;
                return record;
            }
        }
        record = record->next;
    }
    return NULL;
}
#line 96 "src/modules/replay.c"

#line 97 "src/modules/replay.c"
/* Test the supplied point against the linked list of original
 * center/radius-squared regions. Use the strict squared-distance comparison
 * and return on the first containing region; an empty list returns zero. */
s32 replayIsPointInsideAnyRegion(s32 pointAddress) {
    f32 difference[4];
    void *node;

    node = D_replay_00401B64;
    if (node != 0) {
        do {
            (*(void (**)(void *, s32, void *))((u8 *)gUvFvecExports + 0x34))(&difference[0], pointAddress, node);
            if (difference[0] * difference[0] + difference[1] * difference[1] + difference[2] * difference[2] < *(f32 *)((u8 *)node + 0xC)) {
                return 1;
            }
            node = (void *)*(s32 *)((u8 *)node + 0x10);
        } while (node != 0);
    }
    return 0;
}
#line 113 "src/modules/replay.c"

#line 114 "src/modules/replay.c"
/* Create and attach a GUI child, bind its shared text, and add three
 * original range controls: zero to 100, then two minus-50 to 50 controls.
 * Keep the existing export signatures and shared storage bindings. */
void replayCreateThreeRangeControls(s32 parent) {
    typedef struct {
        char pad0[0x84];
        void (*unk84)(s32, s32);  /* 0x84 */
        char pad88[0x94 - 0x88];
        s32  (*unk94)(void);      /* 0x94 */
        s32  (*unk98)(s32);       /* 0x98 */
        void (*unk9C)(s32, u8 *); /* 0x9C */
    } ReplayGuiExports;
    typedef struct {
        char pad0[0x104];
        void (*unk104)(s32, u8 *, s32, f32, f32, u8 *, s32); /* 0x104 */
    } ReplayMiscExports;
    extern ReplayGuiExports *gUvGuiExports;
    extern void *gMiscExports;
    extern u8 D_replay_00401AC0;
    extern u8 D_replay_00401AC8;
    extern u8 D_replay_00401AD4;
    extern u8 D_replay_00401ADC;
    extern u8 D_replay_00401B50;
    extern u8 D_replay_00401B54;
    extern u8 D_replay_00401B58;
    s32 child;

    child = gUvGuiExports->unk98((s16)gUvGuiExports->unk94());
    gUvGuiExports->unk9C(child, &D_replay_00401AC0);
    gUvGuiExports->unk84(parent, child);
    ((ReplayMiscExports *)gMiscExports)->unk104(child, &D_replay_00401AC8, 0x11, 0.0f, 100.0f, &D_replay_00401B58, 0);
    ((ReplayMiscExports *)gMiscExports)->unk104(child, &D_replay_00401AD4, 0x11, -50.0f, 50.0f, &D_replay_00401B50, 0);
    ((ReplayMiscExports *)gMiscExports)->unk104(child, &D_replay_00401ADC, 0x11, -50.0f, 50.0f, &D_replay_00401B54, 0);
}
#line 145 "src/modules/replay.c"

#line 146 "src/modules/replay.c"
/* Write the original version-two replay layout through the game file
 * module: version byte, frame/event lengths, input bytes, four-byte frame
 * values and event bytes. The filename uses the original work-area prefix
 * and exactly four scene-name bytes. Ignore write/close status as originally
 * implemented; failed open skips all writes. No host file backend is added. */
void replayWriteVersionTwoFile(ReplayWriteHeader *state) {
    FileUx_Exports *exports;
    u8 version;
    char filename[128];
    s32 file;
    exports = ((ReplayFileModuleExports *)gMiscExports)->loadFileModule();
    version = 2;
    sprintf(filename, D_replay_00401AE4, D_replay_00401AF4, gSceneExports->nameRecord + 4);
    file = exports->fileuxOpen(filename, 0x301, 0x1B6);
    if (file >= 0) {
        exports->fileuxWrite(file, &version, 1);
        exports->fileuxWrite(file, (u8 *)&state->frameCount, 4);
        exports->fileuxWrite(file, (u8 *)&state->eventBytes, 4);
        exports->fileuxWrite(file, (u8 *)state + 0x10, state->frameCount);
        exports->fileuxWrite(file, (u8 *)state + 0xE20, state->frameCount * 4);
        exports->fileuxWrite(file, (u8 *)state + 0x4660, state->eventBytes);
        exports->fileuxClose(file);
    }
}
#line 147 "src/modules/replay.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00401968.s")

