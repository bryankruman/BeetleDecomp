// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/* Focused slot/record views; neither establishes complete historical layout. */
typedef struct { u8 unused00[0xC4]; void (*copyText)(void *, char *); } TedSelectorLabelExports;
typedef struct { s32 selector; u8 unknown04[12]; } TedSelectorLabelRecord;
extern s32 D_ted_00407244;
extern s32 D_ted_0040727C;
extern TedSelectorLabelRecord *D_ted_00407298;
extern char D_ted_00407090[];
extern char D_ted_00407098[];
extern char D_ted_004070A0[];
extern char D_ted_004070AC[];
extern char D_ted_004070B4[];
extern s32 D_ted_00407284;
extern TedSelectorLabelRecord *D_ted_004072A0;
extern char D_ted_004070BC[];
extern char D_ted_004070C4[];
extern char D_ted_004070CC[];
extern char D_ted_004070D4[];
extern char D_ted_004070E0[];
extern char D_ted_004070EC[];
#line 3 "src/modules/ted.c"
/* Minimal original slot-consumption views; unused storage is not a complete
 * export-table or historical ABI declaration. Keep shared provider reloads.
 * RE_UNKNOWN: full table lifecycle, historical formals and all unused slots. */
typedef struct {
    u8 prefix00[0x14];
    void (*initializeSharedWidget)(void);
    u8 prefix18[0x10];
    void *sharedState;
} TedTaskEditorGameGuiExports;
typedef struct {
    u8 prefix00[8];
    void (*appendChildRow)(void *, void *);
    u8 prefix0C[0x64];
    s32 (*allocateChildGroup)(void);
    void *(*getChildGroup)(s16);
    void (*copyChildGroupText)(void *, u8 *);
    u8 prefix7C[8];
    void (*attachTextList)(void *, void *);
    u8 prefix88[0xC];
    s32 (*allocateTextList)(void);
    void *(*getTextList)(s16);
} TedTaskEditorGuiExports;
extern void *gGameGuiExports;
extern s32 D_ted_004072A8, D_ted_004072AC, D_ted_00407240;
extern char D_ted_00406E60[];
#line 3 "src/modules/ted.c"
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
void tedCreateTaskEditorGroupsAndDispatchSelector();
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
void tedUpdateSelectedItemLabel(void *widget);
void func_ted_00406178();
void func_ted_00406280();
void func_ted_00406330();
void func_ted_00406508();
void func_ted_00406610();
void func_ted_0040685C();
void tedUpdateSelectedColoredLetterLabel(void *widget);
void func_ted_00406B04();
void tedResetRecordPool();
void tedResetRecord(TedResetRecord *record);
void tedResetGuiState(TedGuiState *state);
#pragma GLOBAL_ASM("asm/us/data/modules/ted.rodata-prefix.s")
#line 154 "src/modules/ted.c"
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

#line 142 "src/modules/ted.c"
/* Create the "Task Editor" child group and two text lists, append the group
 * to the original GAMEGUI shared-state address plus 0x10, then refresh and
 * dispatch the current selector. Original relocated table entries establish
 * cases 1, 2, 3, 4, 7 and 8; selectors 5, 6 and out-of-range values do nothing.
 * Keep signed-low16 allocation indices, shared pointer stores/reloads and calls
 * in their original order. The s32 globals retain their existing word ABI;
 * casts represent pointer bits, without changing shared definitions.
 * RE_ORIGINAL_QUIRK: allocation results are not checked before indexed access.
 * The text copier reads 30 source bytes without stopping at NUL, although the
 * visible title contains 12 bytes including its terminator. Neither the title
 * string nor frame size proves a complete historical backing-object extent.
 * RE_UNKNOWN: selector meanings, backing allocations/capacities, pool exhaustion
 * reachability, title backing/adjacent bytes, aliases and provider/callback
 * lifetimes, and historical helper/caller signatures. Resolve original shared
 * state and selector producers, asset layout, all allocation/reset callers and
 * callback consumers before changing names, bounds, fallback or source ABI. */
void tedCreateTaskEditorGroupsAndDispatchSelector(void) {
    void *parentGroup;

    parentGroup = (u8 *)((TedTaskEditorGameGuiExports *)gGameGuiExports)->sharedState + 0x10;
    ((TedTaskEditorGameGuiExports *)gGameGuiExports)->initializeSharedWidget();

    D_ted_004072A8 = (s32)((TedTaskEditorGuiExports *)gUvGuiExports)->getChildGroup(
        (s16)((TedTaskEditorGuiExports *)gUvGuiExports)->allocateChildGroup());
    ((TedTaskEditorGuiExports *)gUvGuiExports)->copyChildGroupText(
        (void *)D_ted_004072A8, (u8 *)D_ted_00406E60);
    ((TedTaskEditorGuiExports *)gUvGuiExports)->appendChildRow(
        parentGroup, (void *)D_ted_004072A8);

    D_ted_004072AC = (s32)((TedTaskEditorGuiExports *)gUvGuiExports)->getTextList(
        (s16)((TedTaskEditorGuiExports *)gUvGuiExports)->allocateTextList());
    ((TedTaskEditorGuiExports *)gUvGuiExports)->attachTextList(
        (void *)D_ted_004072A8, (void *)D_ted_004072AC);

    D_ted_004072B0 = (s32)((TedTaskEditorGuiExports *)gUvGuiExports)->getTextList(
        (s16)((TedTaskEditorGuiExports *)gUvGuiExports)->allocateTextList());
    ((TedTaskEditorGuiExports *)gUvGuiExports)->attachTextList(
        (void *)D_ted_004072A8, (void *)D_ted_004072B0);
    func_ted_00401C6C();

    switch (D_ted_00407240) {
    case 1:
        func_ted_00402320();
        break;
    case 2:
        func_ted_00402E58();
        break;
    case 3:
        func_ted_004031A0();
        break;
    case 4:
        func_ted_004034E8();
        break;
    case 7:
        tedResetPoolWithEnvPlnLabel();
        break;
    case 8:
        tedResetPoolWithChkPtLabel();
        break;
    }
}
#line 143 "src/modules/ted.c"

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
/*
 * Reset the shared selector's scalar/word defaults and selected index before
 * dispatching. Selectors 1, 2, 3, 4, 7 and 8 choose the original literal label
 * and count; selectors 5, 6 and out-of-range values retain the old active count
 * and skip the formatter, bound update, shared helper and label copy.
 * GUI slot 0xD4 receives bounds -1 and count-minus-one plus the selected value
 * and its signed-word binding. Preserve state reads after formatting, provider
 * reloads and the raw supplied word to the direct helper; that helper homes
 * its incoming word without consuming it, leaving its historical formal unknown.
 * RE_ORIGINAL_QUIRK: formatting initializes at most 12 bytes, then GUI slot
 * 0xC4 reads 30 bytes without stopping at NUL and writes 30 destination bytes.
 * This does not establish the historical scratch extent or valid tail contents.
 * RE_UNKNOWN: state/scratch/destination capacities, physical scalar meanings,
 * selector/count lifecycle and reachable bounds, callback mutations, aliases,
 * allocation ownership and historical declarations. Trace original writers,
 * widget flags, allocations, callers and consumers before changing validation,
 * defaults, storage views, names, initialization or argument contracts.
 * Readable C is parked: 456 native bytes versus 496 draft bytes, with expanded
 * shared-state addressing and different scratch storage. Original effects and
 * supplied argument widths were reviewed; no missing operation was identified.
 * The native selector table is still retained in the existing readonly suffix.
 * Resolve natural storage/lifetime evidence and compiler table ownership, then
 * prove all instructions, complete relocations, packed providers and ROM.
 */
#line 166 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403A58.s")

/* Refresh shared editor fields from the selected record, then dispatch the
 * original selector-specific refresh callback. Selectors 1 and 2 use 44-byte
 * record strides; selectors 3 and 4 use 16-byte strides and parallel word lists.
 * Negative selection writes the original defaults. Selectors 7 and 8 reset
 * their labeled pools; selectors 5, 6 and values outside 1..8 return unchanged.
 * RE_ORIGINAL_QUIRK: selection is checked only for negativity, with no upper
 * bound here. Selector 1 reads the selected index five times before its first
 * field store and reads three freshly written default scalars back. Preserve
 * these accesses and callback order; invalid-index reachability is unresolved.
 * RE_UNKNOWN: selector/field meanings and scalar units, valid index domains,
 * complete state and record storage, aliases and mutation/lifetime guarantees,
 * callback invocation arguments and historical formal/local qualifications.
 * The registered callback homes incoming A0 without reading it again; this
 * does not prove a no-argument historical declaration. Resolve original GUI
 * invocations, selector/index writers, pool allocations and field consumers
 * before narrowing types, removing reads or claiming capacity guarantees.
 * Readable C is parked: 624 native bytes versus 660 ordinary-view bytes or
 * 704 observed-access-view bytes; the final draft differs in 168 words and
 * has 74 complete relocation records versus 31 native records. Explicit
 * observed reads survive, but repeated state-address construction and compiler
 * scheduling differ. Historical volatile qualification is not established.
 * The original eight-entry table remains inside the retained readonly suffix;
 * the draft emits another table. Require exact native instructions and proven
 * readonly composition plus full packed-module/ROM equality before replacing
 * ASM; no further shape variants or ownership migration without new evidence. */
#line 168 "src/modules/ted.c"
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
/*
 * For a nonnegative selected secondary object, copy its scalar triple twice,
 * subtract 100.0f from the second z component and query the original segment
 * provider with words 0, 255, the reloaded object ID and a signed scene byte.
 * On success, copy query offset 0x1C into record offset 0x10, build an identity
 * matrix with the record triple in its final row, then update the reloaded
 * object ID and invoke the original follow-up helper. Retain provider, selected
 * index and object-list reloads across calls; the incoming word is only homed.
 * RE_ORIGINAL_QUIRK: the query provider reads output-prefix words at offsets
 * 0 and 4 before delegation, although this caller does not initialize them.
 * RE_UNKNOWN: historical query/scratch declarations, those prefix inputs,
 * selected-index and object-list capacities, aliases and callback mutations,
 * physical frames/units, and the incoming formal's intended role. The observed
 * 44-byte record stride and 88-byte query copy span do not prove complete
 * historical object extents. Trace original callers, allocations, query writers
 * and downstream consumers before changing initialization, bounds or types.
 * Readable C is parked: 420 native/draft bytes, with 15 stack-offset differences
 * only. All 31 complete relocation records agree as a multiset; serialization
 * order differs. No missing operation or supplied argument was identified.
 * Recover actual source storage/lifetimes before another draft, without invented
 * padding, then prove instructions, complete records, packed providers and ROM.
 */
#line 204 "src/modules/ted.c"
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
/*
 * Reset 30 object-list entries, then read a byte count and 16-byte records.
 * Keep separate attempted-read and retained-record counters: the record and
 * object-list cursors advance only when creation does not return full-word -1.
 * Preserve the count, list and provider reloads after callbacks, ignored file
 * read statuses, the direct record helper and property-4 callback installation.
 * The initializer requests 480 record bytes and 120 object-list bytes. Each
 * observed record supplies one word and three f32 values at offsets 4, 8 and 12;
 * the helper's later offset-0x10 read instead uses a separate SMACK result.
 * RE_ORIGINAL_QUIRK: the byte count is not locally capped at 30, and creation
 * exhaustion returns zero-extended 0xFFFF while this caller tests full-word -1.
 * RE_UNKNOWN: reachable file counts, partial-read contents, pool replacement
 * and capacity, callback mutations/aliases, SMACK-result extent/lifetime and
 * physical record meanings. Trace original file writers, allocations, callers,
 * callback consumers and exhaustion paths before changing bounds or recovery.
 * Readable C remains parked: both trials contain 472 native/draft bytes. The
 * byte-pointer draft differs in 60 words and relocation sites; the minimum
 * typed-record draft differs in 16 register-allocation words only. Its 17 full
 * relocation records agree as a multiset, with serialization order differing.
 * No missing native effect was found. Recover original source/lifetime evidence
 * before another draft, then prove complete instructions, records, module and ROM.
 */
#line 217 "src/modules/ted.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004059BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405B94.s")
/* RE_UNKNOWN: first-list selection/count invariants, backing capacity, record word/vector roles and callback mutation domains; inspect original list creators, ID/record writers and callback targets before changing compaction, alias handling or count wraparound. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405C9C.s")
/*
 * Copy the first selected editor record's position twice, subtract 100 from
 * the second Z, and query the segment with flags 255. On success, copy the
 * query scalar at offset 0x1C into the retained record's Z, build a translation
 * matrix, update the current object, and invoke the original editor follow-up.
 * Preserve selection and handle reloads after callbacks and negative gates.
 * RE_ORIGINAL_QUIRK: this caller does not initialize the query scratch record;
 * the original query reads its words at offsets 0x00 and 0x04 before delegation.
 * Dependent helper use and reachable caller domains remain unresolved; this
 * observation alone does not establish a player-visible fault.
 * RE_UNKNOWN: historical scratch and callback declarations, complete record
 * and handle capacities, aliases and callback lifetimes, the coordinate frame
 * and 100-unit meaning, scene byte 0x08, and successful query-field validity.
 * The proven 88-byte query copy span does not establish a historical local or
 * complete object extent. Resolve original pool producers, query modes/helpers,
 * and all callback callers before changing initialization, layout, or bounds.
 * Readable C remains parked: 404 native/draft bytes differ in 15 stack-address
 * instruction words. All 31 complete relocation records match as a multiset;
 * only pair serialization differs. Natural exact C and complete packed-module
 * and ROM validation are still required; no scratch padding is inferred.
 */
#line 223 "src/modules/ted.c"
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
#line 225 "src/modules/ted.c"
/* Format the current selector's original label, forward the stack text to
 * GUI slot 0xC4, then reload the selected index and current selector for the
 * 16-byte record store. The GUI callback may change shared state.
 * RE_ORIGINAL_QUIRK: an out-of-range selector skips formatting but still
 * forwards uninitialized scratch. Preserve that path; reachability is unknown.
 * RE_ORIGINAL_QUIRK: the GUI provider consumes 30 bytes even past a short
 * formatted label's terminator; the original scratch tail is not initialized.
 * RE_UNKNOWN: historical scratch extent (32 is a draft local view), valid
 * selector/index domains, GUI's 30-byte consumption, backing allocations,
 * callback mutation/lifetimes and full argument/record declarations. */
void tedUpdateSelectedItemLabel(void *widget)
{
    char text[32];
    s32 selectedIndex;

    switch (D_ted_0040727C) {
    case 0:
        sprintf(text, D_ted_00407090);
        break;
    case 1:
        sprintf(text, D_ted_00407098);
        break;
    case 2:
        sprintf(text, D_ted_004070A0);
        break;
    case 3:
        sprintf(text, D_ted_004070AC);
        break;
    case 4:
        sprintf(text, D_ted_004070B4);
        break;
    }
    ((TedSelectorLabelExports *)gUvGuiExports)->copyText(widget, text);
    selectedIndex = D_ted_00407244;
    if (selectedIndex >= 0) {
        D_ted_00407298[selectedIndex].selector = D_ted_0040727C;
    }
}
#line 226 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406280.s")
/*
 * Reset 20 object-list slots, then read a byte count and 16-byte records.
 * Keep attempted reads separate from retained-record and object-list indices;
 * only a stored creation result unequal to full-word -1 advances the latter.
 * Preserve ignored read statuses, count/provider/list reloads across callbacks,
 * the direct record helper and the property-4 callback/index installation.
 * The initializer requests 320 record bytes and 80 object-list bytes. The
 * helper reads record word 0 and f32 members 4, 8 and 12; its later offset-0x10
 * read uses a separate LETTER result, not a neighboring file-record member.
 * RE_ORIGINAL_QUIRK: the byte count is not locally capped at 20. Creation
 * exhaustion returns zero-extended 0xFFFF, while this caller tests full-word -1.
 * RE_UNKNOWN: reachable file counts, partial-read contents, pool replacement
 * and capacity, physical record meanings, callback aliases/mutations, resource
 * bounds and LETTER-result extent/lifetime. Trace original writers, allocations,
 * callback/resource consumers and exhaustion callers before adding validation.
 * Readable C is parked: minimum-record and typed-slot reset drafts each contain
 * 472 native/draft bytes with 16 register-allocation differences. The final
 * draft's 17 complete relocation records agree as a multiset; serialization
 * order differs. The typed reset did not resolve the second-loop register
 * assignment. No missing operation or ABI effect was identified. Recover
 * original source/lifetime evidence before another draft, then prove complete
 * instructions, records, packed providers and ROM without invented storage.
 */
#line 231 "src/modules/ted.c"
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
/*
 * Apply the segment-query update to the second selected editor pool: retain
 * its 16-byte record, copy position twice, subtract 100 from the second Z,
 * and use flags 255. On success, copy query scalar 0x1C to record Z, update
 * the current object's translation, and invoke the original editor follow-up.
 * Reload selection and parallel handles after callbacks; preserve negative
 * gates. The initializer allocates and clears 20 second-pool records and
 * handles, versus 30 in the first pool. This caller has no upper-index gate.
 * RE_ORIGINAL_QUIRK: query scratch words 0x00 and 0x04 are not initialized
 * here before the original query reads them. Reachable query-helper use and
 * caller domains remain unresolved; no player-visible fault is established.
 * RE_UNKNOWN: historical scratch/callback declarations, complete pool bounds
 * over its lifetime, aliases and callback replacement, scene byte 0x08,
 * coordinate frame and 100-unit meaning, and successful query-field validity.
 * The proven 88-byte query copy span is not a complete historical local or
 * object extent. Trace original pool setters, selection producers, query
 * modes/helpers, and all callbacks before changing layout or validation.
 * Original assembly is retained; no second-pool C recovery is claimed.
 */
#line 237 "src/modules/ted.c"
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
#line 239 "src/modules/ted.c"
/* Format the current selector's original label, forward the stack text to
 * GUI slot 0xC4, then reload the selected index and current selector for the
 * 16-byte record store. The GUI callback may change shared state.
 * RE_ORIGINAL_QUIRK: an out-of-range selector skips formatting but still
 * forwards uninitialized scratch. Preserve that path; reachability is unknown.
 * RE_ORIGINAL_QUIRK: the GUI provider consumes 30 bytes even past a short
 * formatted label's terminator; the original scratch tail is not initialized.
 * RE_UNKNOWN: historical scratch extent (32 is a draft local view), valid
 * selector/index domains, GUI's 30-byte consumption, backing allocations,
 * callback mutation/lifetimes and full argument/record declarations. */
void tedUpdateSelectedColoredLetterLabel(void *widget)
{
    char text[32];
    s32 selectedIndex;

    switch (D_ted_00407284) {
    case 0:
        sprintf(text, D_ted_004070BC);
        break;
    case 1:
        sprintf(text, D_ted_004070C4);
        break;
    case 2:
        sprintf(text, D_ted_004070CC);
        break;
    case 3:
        sprintf(text, D_ted_004070D4);
        break;
    case 4:
        sprintf(text, D_ted_004070E0);
        break;
    case 5:
        sprintf(text, D_ted_004070EC);
        break;
    }
    ((TedSelectorLabelExports *)gUvGuiExports)->copyText(widget, text);
    selectedIndex = D_ted_00407244;
    if (selectedIndex >= 0) {
        D_ted_004072A0[selectedIndex].selector = D_ted_00407284;
    }
}
#line 240 "src/modules/ted.c"

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

