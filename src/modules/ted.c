// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern char D_ted_0040701C[], D_ted_00407028[];
extern s32 D_ted_004072B8;
#include "fileux.h"
typedef struct { u8 prefix[0xF0]; FileUx_Exports *(*loadFileModule)(void); } TedFileLoaderExports;
typedef struct { u8 prefix[0x2C]; u8 *nameRecord; } TedSceneNameExports;
extern void *gMiscExports, *gSceneExports;
extern char D_ted_00407048[], D_ted_00407054[];
typedef struct { u8 unk00[4]; s32 (*write)(s32, void *, s32); } TedFileWriteExports;
extern void *D_ted_004071B4;
extern u8 D_ted_0040724C, D_ted_00407270;
/* Original PAUS export 0x08 binds func_pause_00400258.
 * RE_UNKNOWN: its initial node callback inherits incoming argument registers;
 * that callback's intended argument/result contract remains unresolved.
 * Preserve the existing caller view until original callback targets settle it.
 */
typedef struct {
    u8 prefix[8];
    void (*dispatchNodeAndControllerChecks)(void);
} TedPauseFrameExports;
typedef struct { u8 unk00[0x28]; void (*update)(s32, void *); } TedCameraFrameExports;
extern s16 D_80025D76;
extern void *D_ted_004071B8, *gCamExports;
extern s32 D_ted_0040722C, D_ted_00407224, D_ted_004071E4;
typedef struct { u8 unk00[0x28]; struct TedResetRecord *records[80]; u16 count; s16 selectedIndex; } TedRecordPool;
#include "module.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
typedef struct TedGuiState {
    u8 unk00[0x1E];
    u16 unk1E;
    u16 unk20;
    u8 unk22[2];
    f32 unk24;
    f32 unk28;
    s32 unk2C;
    f32 unk30;
    f32 unk34;
    u8 unk38[8];
    s32 unk40;
    s32 unk44;
} TedGuiState;


/* Fields are named by byte offset until the track editor consumers establish meaning. */
typedef struct TedResetRecord {
    u8 unk00[0xC];
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16[6];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    void *unk28;
    s32 unk2C;
    s32 unk30;
} TedResetRecord;

typedef struct {
    char pad00[0x9C];
    void (*unk9C)(s32, char *);
    char padA0[0x28];
    void (*unkC8)(void *, s16, s16, s16, s32);
} TedGuiExports;
extern TedGuiExports *gUvGuiExports;
extern s32 D_ted_004072B0;
extern char D_ted_00406FB8[];
extern char D_ted_00406FC0[];
typedef struct TedSelectedRecord {
    u8 unk00[0xC];
    f32 unk0C, unk10, unk14, unk18, unk1C, unk20, unk24;
    u8 unk28[4];
} TedSelectedRecord; /* Original array stride: 0x2C bytes. */
typedef struct {
    f32 x, y, z;
    u8 unk0C[0x28];
    f32 directionX, directionY, directionZ;
    u8 unk40[0x14];
    f32 mirrorX, mirrorY, mirrorZ;
    u8 unk60[0x24];
    s32 unk84;
    u8 unk88[4];
    u8 count8C;
    u8 unk8D[7];
    f32 unk94, unk98, unk9C, unkA0, unkA4, unkA8, unkAC;
    u8 countB0;
    u8 unkB1[3];
    s32 unkB4;
} TedCheckData;
extern TedSelectedRecord *D_ted_00407288;
extern TedCheckData D_ted_004071C0;
extern u8 *D_ted_00407290;
void tedResetRecordPool(TedRecordPool *pool);
void func_ted_00400558();
void tedDispatchFrameAndCamera(void);
void func_ted_004007B8();
void func_ted_00400C18();
void func_ted_00401004();
void func_ted_00401338();
void func_ted_00401A8C();
void func_ted_00401C6C();
void func_ted_00402320();
void func_ted_00402E58();
void func_ted_004031A0();
void func_ted_004034E8();
void tedResetPoolWithEnvPlnLabel();
void tedResetPoolWithChkPtLabel();
void func_ted_004038B8();
void func_ted_00403A58();
void func_ted_00403C20();
void tedReadVersionThreeFile(s32);
void tedWriteVersionThreeFile(s32 unused);
void func_ted_004040B4();
void tedWriteSelectedRecords(s32 file);
void func_ted_00404468();
void func_ted_0040465C();
void func_ted_004047DC();
void tedApplySelectedScalar18(s32 unused);
void tedApplySelectedScalar1C(s32 unused);
void tedApplySelectedScalar20(s32 unused);
void tedApplySelectedScalar24(s32 unused);
void func_ted_00404C28();
void tedApplySelectedScalar0C(s32 unused);
void tedApplySelectedScalar10(s32 unused);
void tedApplySelectedScalar14(s32 unused);
void func_ted_00404DA8();
void tedWriteSecondaryRecords(s32 file);
void func_ted_00405018();
void func_ted_004051F0();
void func_ted_00405344();
void func_ted_0040561C();
void tedStoreSelectedRecordByte();
void func_ted_00405804();
void func_ted_0040590C();
void func_ted_004059BC();
void func_ted_00405B94();
void func_ted_00405C9C();
void func_ted_00405EE8();
void func_ted_0040607C();
void func_ted_00406178();
void func_ted_00406280();
void func_ted_00406330();
void func_ted_00406508();
void func_ted_00406610();
void func_ted_0040685C();
void func_ted_004069F0();
void func_ted_00406B04();
void tedResetRecordPool();
void tedResetRecord(TedResetRecord *record);
void tedResetGuiState(TedGuiState *state);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/__entrypoint_func_ted_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00400558.s")

#line 132 "src/modules/ted.c"
/* A nonzero shared frame flag delegates to original PAUS export 0x08.
 * Otherwise dispatch editor modes zero/one, then update the original camera.
 * RE_UNKNOWN: full callback contracts remain unresolved; see notes below. */
#line 135 "src/modules/ted.c"
/* A nonzero shared frame flag invokes PAUS export 0x08 and returns.
 * Its original target dispatches the current pause-node callback selected
 * by short 0x10, updates linked menu state and performs controller checks.
 * Otherwise dispatch editor modes zero/one and update the original camera;
 * other editor modes still perform the camera update.
 * RE_UNKNOWN: pause-node callback argument/result contracts and the meanings
 * of its menu fields. The first callback inherits incoming argument registers.
 * Trace the original pause callback table and callers before tightening this
 * preserved no-argument caller view or naming specific menu-state semantics. */
void tedDispatchFrameAndCamera(void) {
    if (D_80025D76 != 0) {
        ((TedPauseFrameExports *)D_ted_004071B8)->dispatchNodeAndControllerChecks();
        return;
    }
    switch (D_ted_0040722C) {
    case 0: func_ted_004007B8(); break;
    case 1: func_ted_00400C18(); break;
    }
    ((TedCameraFrameExports *)gCamExports)->update(D_ted_00407224, &D_ted_004071E4);
}
#line 146 "src/modules/ted.c"
#line 133 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004007B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00400C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401004.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401C6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00402320.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00402E58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004031A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004034E8.s")

#line 154 "src/modules/ted.c"
/* Set the original GUI label to "EnvPln" and reset the shared record pool.
 * RE_UNKNOWN: the label expansion and the full GUI handle/pool type contract
 * remain unproven; preserve the original call signatures. */
void tedResetPoolWithEnvPlnLabel(void) {
    gUvGuiExports->unk9C(D_ted_004072B0, D_ted_00406FB8);
    tedResetRecordPool(D_ted_004072B0);
}
#line 158 "src/modules/ted.c"

#line 159 "src/modules/ted.c"
/* Set the original GUI label to "ChkPt" and reset the shared record pool.
 * RE_UNKNOWN: the label expansion and the full GUI handle/pool type contract
 * remain unproven; preserve the original call signatures. */
void tedResetPoolWithChkPtLabel(void) {
    gUvGuiExports->unk9C(D_ted_004072B0, D_ted_00406FC0);
    tedResetRecordPool(D_ted_004072B0);
}
#line 163 "src/modules/ted.c"
/*
 * Preserve the original shared-mode branch: mode0 or1 formats stack+0x30,
 * updates GUI bounds and then calls the shared selector refresh; other modes
 * skip both local formatting paths and still forward stack+0x30 to GUI0xC4.
 * RE_ORIGINAL_QUIRK: this routine does not initialize that forwarded scratch
 * on the other-mode path. This is not a proven reachable player-visible bug.
 * RE_UNKNOWN: allowed mode0x6C values, imported provider/callback contracts,
 * historical scratch extent and failure/alias lifecycle. Trace every original
 * mode writer and caller plus actual GUI0xC4 consumption before changing the
 * branch, initializing the scratch, or inferring a valid formatted read span.
 */
#line 164 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004038B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403A58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403C20.s")

#line 170 "src/modules/ted.c"
/* Load the original file backend and open the formatted scene filename
 * for reading. Close and return when the one-byte version differs from three.
 * For version three, dispatch the four original file helpers in order, close
 * the file, then run the original two refresh helpers. Preserve the unused
 * incoming word, fresh backend loads and raw refresh argument.
 * RE_ORIGINAL_QUIRK: only open success is checked; read/close results are
 * ignored, and version remains uninitialized unless the read writes it.
 * RE_UNKNOWN: complete helper/file-format contracts, filename source extents,
 * exact historical formatting-array extent and failed-read reachability.
 * Audit original helpers, format data, backend and callers before changing
 * parsing, input bounds, source ABI or failure behavior. */
void tedReadVersionThreeFile(s32 unused) {
    char filename[128];
    u8 version;
    s32 file;

    D_ted_004071B4 = ((TedFileLoaderExports *)gMiscExports)->loadFileModule();
    sprintf(filename, D_ted_0040701C, D_ted_00407028,
            ((TedSceneNameExports *)gSceneExports)->nameRecord + 4);
    file = ((FileUx_Exports *)D_ted_004071B4)->fileuxOpen(filename, 0, 0x1B6);
    if (file >= 0) {
        ((FileUx_Exports *)D_ted_004071B4)->fileuxRead(file, &version, 1);
        if (version != 3) {
            ((FileUx_Exports *)D_ted_004071B4)->fileuxClose(file);
            return;
        }
        func_ted_00404468(file);
        func_ted_00405018(file);
        func_ted_004059BC(file);
        func_ted_00406330(file);
        ((FileUx_Exports *)D_ted_004071B4)->fileuxClose(file);
        func_ted_00403A58(D_ted_004072B8);
        func_ted_00401C6C();
    }
}
#line 171 "src/modules/ted.c"

#line 172 "src/modules/ted.c"
/* Load the original file backend and write version three followed by
 * the four editor record sections. Preserve the filename format, open flags,
 * write order and ignored write/close statuses; failed opens write nothing. */
void tedWriteVersionThreeFile(s32 unused) {
    s32 file;
    u8 version;
    char filename[128];
    D_ted_004071B4 = ((TedFileLoaderExports *)gMiscExports)->loadFileModule();
    version = 3;
    sprintf(filename, D_ted_00407048, D_ted_00407054, ((TedSceneNameExports *)gSceneExports)->nameRecord + 4);
    file = ((FileUx_Exports *)D_ted_004071B4)->fileuxOpen(filename, 0x301, 0x1B6);
    if (file >= 0) {
        ((FileUx_Exports *)D_ted_004071B4)->fileuxWrite(file, &version, 1);
        tedWriteSelectedRecords(file);
        tedWriteSecondaryRecords(file);
        func_ted_0040590C(file);
        func_ted_00406280(file);
        ((FileUx_Exports *)D_ted_004071B4)->fileuxClose(file);
    }
}
#line 173 "src/modules/ted.c"
/*
 * RE_UNKNOWN: record/controller index bounds, backing and callback alias/mutation
 * domains, rotation frames/scalar domains and object property-seven meaning;
 * trace original file/GUI writers, callers and object consumers before changing
 * the 44-byte record view, shared reloads or f32-to-f64 property promotion.
 * Original FMTX slot 0x24 only stores incoming A0 in its argument stack slot;
 * preserve the gated 32-bit matrix-address call. Its intended source parameter
 * type and caller-facing purpose remain unknown; inspect all original callers.
 */
#line 174 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004040B4.s")

#line 176 "src/modules/ted.c"
/* Write the one-byte header followed by count8C records of 0x2C bytes.
 * Reload shared count/base after each callback; write statuses are ignored.
 * RE_UNKNOWN: record/count bounds and status handling need original producers/callers. */
void tedWriteSelectedRecords(s32 file) {
    s32 index;
    s32 offset;
    ((TedFileWriteExports *)D_ted_004071B4)->write(file, &D_ted_0040724C, 1);
    index = 0;
    offset = 0;
    if (D_ted_004071C0.count8C > 0) {
        do {
            ((TedFileWriteExports *)D_ted_004071B4)->write(file, (void *)(offset + (u32)D_ted_00407288), 0x2C);
            index++;
            offset += 0x2C;
        } while (index < D_ted_004071C0.count8C);
    }
}
#line 177 "src/modules/ted.c"
/*
 * RE_UNKNOWN: valid file counts, backing replacements, allocation failures,
 * record meanings and callback alias/mutation lifecycle; verify original file
 * producers, every count/base writer and actual callback/pool states before
 * changing 44-byte reads or the success-only record/ID cursor advances.
 * RE_ORIGINAL_QUIRK: read results are ignored and the file byte count is not
 * bounded by the original 50-slot allocation requests. DOBJ create returns
 * zero-extended 0xFFFF on exhaustion, but this caller rejects only full-word
 * -1. Malformed-file and exhausted-pool caller reachability remain unknown.
 */
#line 178 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040465C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004047DC.s")

#line 178 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x18.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar18(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk18 = D_ted_004071C0.unk94;
    }
}
#line 179 "src/modules/ted.c"

#line 180 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x1C.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar1C(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk1C = D_ted_004071C0.unk98;
    }
}
#line 181 "src/modules/ted.c"

#line 182 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x20.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar20(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk20 = D_ted_004071C0.unk9C;
    }
}
#line 183 "src/modules/ted.c"

#line 184 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x24.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar24(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk24 = D_ted_004071C0.unkA0;
    }
}
#line 185 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404C28.s")

#line 188 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x0C.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar0C(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk0C = D_ted_004071C0.unkA4;
    }
}
#line 189 "src/modules/ted.c"

#line 190 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x10.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar10(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk10 = D_ted_004071C0.unkA8;
    }
}
#line 191 "src/modules/ted.c"

#line 192 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x14.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar14(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk14 = D_ted_004071C0.unkAC;
    }
}
#line 193 "src/modules/ted.c"
/* RE_UNKNOWN: record/object bounds and callback mutations, rotation units/frames, SMACK model-word meaning and DOBJ tag-one scalar units; trace original record creators, SMACK table writers and model-scalar consumers before changing transforms or properties. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404DA8.s")

#line 196 "src/modules/ted.c"
/* Write the original secondary one-byte header followed by countB0 records
 * of 0x2C bytes. Preserve shared count/base reloads and ignored write statuses. */
void tedWriteSecondaryRecords(s32 file) {
    s32 index;
    s32 offset;
    ((TedFileWriteExports *)D_ted_004071B4)->write(file, &D_ted_00407270, 1);
    index = 0;
    offset = 0;
    if (D_ted_004071C0.countB0 > 0) {
        do {
            ((TedFileWriteExports *)D_ted_004071B4)->write(file, (void *)(offset + (u32)D_ted_00407290), 0x2C);
            index++;
            offset += 0x2C;
        } while (index < D_ted_004071C0.countB0);
    }
}
#line 197 "src/modules/ted.c"
/*
 * Clear the 100 parallel object slots through DOBJ tag4 and slot0x40, reading
 * each current handle again across callbacks. Read the original one-byte
 * header, then 44-byte records and rebuild handles/tag4 callback-context pairs.
 * Reload the byte count after callbacks; only successful full-word comparisons
 * advance record/handle destinations, while every file-read attempt advances.
 * RE_ORIGINAL_QUIRK: read statuses are ignored and the byte count has no local
 * clamp to the 100-entry startup allocation. DOBJ exhaustion returns zero-
 * extended0xFFFF, while this caller rejects full-word-1. Reachability of failed
 * reads, excess counts and exhausted object resources remains unresolved.
 * RE_UNKNOWN: validated file/count domains, allocation results/later pointer
 * replacement, historical record declarations, property meanings and callback
 * alias/lifetime effects. Trace all original file writers/read callers, record
 * and resource producers, allocation outcomes and callback mutations.
 * Readable C parked:472 native versus496 bytes, unequal instruction and full
 * relocation records; the compiler expands shared handle/export addresses.
 * Native-equivalent C plus complete packed TED/provider/ROM proof is required.
 */
#line 198 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405018.s")
/*
 * Append a secondary44-byte editor record under the pre-create byte-count<100
 * gate; reload/wrap count after DOBJ creation, write count/index words and the
 * parallel handle, copy shared translation through FVEC1C, apply transform and
 * store the DOBJ tag4 callback/context words before both GUI refresh helpers.
 * Original initializer requests4400 record/400 handle bytes and initializes100
 * records; that establishes these startup requests, not every later lifetime.
 * RE_ORIGINAL_QUIRK: actual DOBJ creation exhausts with zeroextended0xFFFF,
 * while this caller rejects fullword-1. Exhaustion reachability is unresolved.
 * RE_UNKNOWN: historical formal/record declarations, byte flags and scalar04/
 * transform1C meanings, rotation units, allocation failure/pointer replacement,
 * callback mutation/alias domains and resource exhaustion. Resolve original
 * record/file editors, allocation/resource producers and all callback callers.
 * Readable C remains unaccepted:340 native versus356 bytes; expanded editor
 * address constructions and reordered independent defaults prevent instruction/
 * full relocation equivalence. Native-equivalent C plus packed TED/ROM proof
 * is still required; the retained original assembly preserves machine behavior.
 */
#line 200 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004051F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405344.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040561C.s")

#line 206 "src/modules/ted.c"
/* If selection>=0, store the editor byte at selected 0x2C record offset one.
 * RE_UNKNOWN: upper index/storage bounds need original selection producers and callers. */
void tedStoreSelectedRecordByte(s32 unused) {
    s32 index = D_ted_004071C0.unk84;
    if (index >= 0) {
        ((u8 *)D_ted_00407290)[index * 0x2C + 1] = D_ted_004071C0.unkB4;
    }
}
#line 212 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405804.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040590C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004059BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405B94.s")
/* RE_UNKNOWN: first-list selection/count invariants, backing capacity, record word/vector roles and callback mutation domains; inspect original list creators, ID/record writers and callback targets before changing compaction, alias handling or count wraparound. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405C9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405EE8.s")
/*
 * RE_ORIGINAL_QUIRK: when unsigned D_ted_0040727C is outside 0..4,
 * the original skips every sprintf but still passes unwritten scratch SP+0x20
 * to GUI slot0xC4, whose original target reads 30 bytes. Reachability is
 * RE_UNKNOWN: trace all selector writers, initialization and callback callers
 * before claiming a player-visible fault or changing fallback behavior.
 * Historical scratch-object extent is not established by the stack frame.
 * After that callback, the original reloads selector and signed index D_ted_00407244;
 * nonnegative indices store through pointer D_ted_00407298 at 16*index.
 * RE_UNKNOWN: index/count bounds, backing-record extent, alias and callback
 * mutation/lifetime guarantees need original pool producers and consumers.
 */
#line 225 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040607C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406280.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406330.s")
/*
 * RE_UNKNOWN: second-list backing capacities, count/selection validity, alias and
 * callback-mutation domains, record word/triple roles and helper effects; verify
 * allocators, every writer/caller and DOBJ callback lifecycle before rewriting.
 * RE_ORIGINAL_QUIRK: original DOBJ create returns zero-extended 0xFFFF on pool
 * exhaustion, but this caller rejects only the full word -1. Exhausted-pool
 * reachability is unknown; inspect original pool sizing and actual call states.
 */
#line 233 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406508.s")
/* RE_UNKNOWN: second-list backing capacity, selection/count/alias
 * invariants, word/triple roles and callback mutation lifecycle; verify
 * allocators, all callers and DOBJ callbacks before changing 16-byte
 * compaction or the D_ted_00407280 count reload. RE_ORIGINAL_QUIRK: only
 * negative selection is guarded and byte decrement wraps; producer 6508's
 * count<20 test does not establish every caller's bounds. */
#line 235 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040685C.s")
/*
 * RE_ORIGINAL_QUIRK: when unsigned D_ted_00407284 is outside 0..5,
 * the original skips every sprintf but still passes unwritten scratch SP+0x20
 * to GUI slot0xC4, whose original target reads 30 bytes. Reachability is
 * RE_UNKNOWN: trace all selector writers, initialization and callback callers
 * before claiming a player-visible fault or changing fallback behavior.
 * Historical scratch-object extent is not established by the stack frame.
 * After that callback, the original reloads selector and signed index D_ted_00407244;
 * nonnegative indices store through pointer D_ted_004072A0 at 16*index.
 * RE_UNKNOWN: index/count bounds, backing-record extent, alias and callback
 * mutation/lifetime guarantees need original pool producers and consumers.
 */
#line 239 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004069F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406B04.s")

#line 243 "src/modules/ted.c"
/* Reset and clear 80 record pointers, then count/selection; ignore a null pool.
 * RE_UNKNOWN: node/GUI ownership/lifetime need original producers and teardown callers. */
void tedResetRecordPool(TedRecordPool *pool) {
    s32 index;
    if (pool != NULL) {
        for (index = 0; index < 80; index++) {
            tedResetRecord(pool->records[index]);
            pool->records[index] = NULL;
        }
        pool->count = 0;
        pool->selectedIndex = -1;
    }
}
#line 244 "src/modules/ted.c"

#line 210 "src/modules/ted.c"
/* For a non-null record, reset the nested GUI state referenced by field 0x28,
 * then restore the original halfword defaults and clear the six word fields.
 * Unknown fields retain offset names rather than speculative editor meanings. */
void tedResetRecord(TedResetRecord *record) {
    if (record != NULL) {
        tedResetGuiState(record->unk28);
        record->unk0C = 0;
        record->unk0E = 0;
        record->unk10 = 0x41;
        record->unk12 = 0;
        record->unk14 = 0xC;
        record->unk1C = 0;
        record->unk20 = 0;
        record->unk24 = 0;
        record->unk28 = 0;
        record->unk2C = 0;
        record->unk30 = 0;
    }
}
#line 211 "src/modules/ted.c"

#line 212 "src/modules/ted.c"
/* Restore the nested GUI state's original defaults and request a centered
 * 180-by-40 rectangle. Preserve all four original screen-size queries and
 * signed half-coordinate conversions rather than replacing them with shifts. */
void tedResetGuiState(TedGuiState *state) {
    s32 screenHeightForBottom;
    s32 screenHeightForTop;
    s32 screenWidthForRight;
    s32 screenWidthForLeft;

    if (state != NULL) {
        state->unk1E = 0;
        state->unk20 = 0x11;
        state->unk2C = 0;
        state->unk44 = 0;
        state->unk30 = 1.0f;
        state->unk28 = 0.0f;
        state->unk24 = 0.0f;
        state->unk34 = -1.0f;
        screenWidthForLeft = gUvGfxMgrExports->uvGetScreenWidth();
        screenWidthForRight = gUvGfxMgrExports->uvGetScreenWidth();
        screenHeightForTop = gUvGfxMgrExports->uvGetScreenHeight();
        screenHeightForBottom = gUvGfxMgrExports->uvGetScreenHeight();
        gUvGuiExports->unkC8(state, (s16) ((s32) (screenWidthForLeft - 0xB4) / 2), (s16) ((s32) (screenWidthForRight + 0xB4) / 2), (s16) ((s32) (screenHeightForTop - 0x28) / 2), (s32) (screenHeightForBottom + 0x28) / 2);
        state->unk40 = 0;
    }
}
#line 213 "src/modules/ted.c"

