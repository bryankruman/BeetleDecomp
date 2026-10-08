// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_game_004020B0[];
extern s32 D_game_004021E0;
/* Initializer-only original address registry, not a callable API.
 * RE_UNKNOWN: callback0x04/08 signatures and lifecycle require the original
 * target bodies and callers. Opaque linker code-label addresses are never
 * dereferenced or invoked through these declarations. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 unknownCallback04Address;
    /* 0x08 */ u32 unknownCallback08Address;
    /* 0x0C */ u32 unloadIndexedModuleCompletelyAddress;
    /* 0x10 */ u32 sharedStateWordAddress;
} GameExportAddresses;
extern u8 func_game_00400DB0[], func_game_00401338[];
void gameNoOpModuleCleanup(void);
void gameUnloadIndexedModuleCompletely(s32 index);
extern s32 D_game_00402120;
extern s32 D_game_004020F4[];
/* Accepted profiler definition consumes only its label and returns a signed
 * ID (or -1). The retained seed's extra first-call argument is not its ABI. */
s32 uvProfilerCreate(char* label);
/* The full original helper overwrites A0-A3 before use and reads no incoming
 * stack arguments; this initializer supplies none and ignores its result.
 * RE_UNKNOWN: its complete startup purpose and any return-value contract
 * need its other original callers and eventual body recovery. */
void func_game_004001E4(void);
/* Actual terrain initializer slot0x5C binds uvTerraSetSharedWordBF0(s32).
 * RE_UNKNOWN: the shared word's detailed role remains unresolved; trace
 * D_uvterra_rom_0040FBF0 consumers before assigning a physical meaning. */
typedef struct { u8 opaque00[0x5C]; void (*setSharedWordBF0)(s32); } GameStartupTerrainExports;
extern void *gUvTerraExports;
extern char D_game_00401F30[];
extern s32 D_game_00402218;
extern char D_game_00401F38[];
extern s32 D_game_00402210;
extern char D_game_00401F40[];
extern s32 D_game_004021E8;
extern char D_game_00401F48[];
extern s32 D_game_004021EC;
extern char D_game_00401F50[];
extern s32 D_game_00402214;
extern char D_game_00401F5C[];
extern s32 D_game_004021F0;
extern char D_game_00401F64[];
extern s32 D_game_004021F8;
extern char D_game_00401F70[];
extern s32 D_game_004021F4;
extern char D_game_00401F7C[];
extern s32 D_game_004021FC;
extern char D_game_00401F88[];
extern s32 D_game_00402208;
extern char D_game_00401F90[];
extern s32 D_game_00402200;
extern char D_game_00401F9C[];
extern s32 D_game_00402204;
extern char D_game_00401FA8[];
extern s32 D_game_0040220C;

#line 61 "src/modules/game.c"
/* Register four original game callbacks and the shared state-word address,
 * set that word to -1, then create the thirteen original profiler entries in
 * order and retain their IDs. Clear pause and settings float0xE8. Enable
 * display masks only when intro/replay state and settings word0x0C are both
 * zero, select the original frame-retrace threshold, run the original startup
 * helper and clear terrain's shared word0xBF0 through its proven setter.
 * RE_UNKNOWN: callback0x04/08 contracts, shared state-word and settings0x0C/E8
 * roles, full startup-helper purpose, frame-option index bounds and safe
 * initialization/reload ownership need original callers and data consumers.
 * Preserve unchecked profiler results, table indexing and terrain dependency;
 * this initializer does not establish successful allocation or general bounds. */
void __entrypoint_func_gameInitializeModuleState(GameExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) gameNoOpModuleCleanup;
    exports->unknownCallback04Address = (u32) func_game_00400DB0;
    exports->unknownCallback08Address = (u32) func_game_00401338;
    exports->unloadIndexedModuleCompletelyAddress = (u32) gameUnloadIndexedModuleCompletely;
    exports->sharedStateWordAddress = (u32) &D_game_00402120;
    D_game_00402120 = -1;
    D_game_00402218 = uvProfilerCreate(D_game_00401F30);
    D_game_00402210 = uvProfilerCreate(D_game_00401F38);
    D_game_004021E8 = uvProfilerCreate(D_game_00401F40);
    D_game_004021EC = uvProfilerCreate(D_game_00401F48);
    D_game_00402214 = uvProfilerCreate(D_game_00401F50);
    D_game_004021F0 = uvProfilerCreate(D_game_00401F5C);
    D_game_004021F8 = uvProfilerCreate(D_game_00401F64);
    D_game_004021F4 = uvProfilerCreate(D_game_00401F70);
    D_game_004021FC = uvProfilerCreate(D_game_00401F7C);
    D_game_00402208 = uvProfilerCreate(D_game_00401F88);
    D_game_00402200 = uvProfilerCreate(D_game_00401F90);
    D_game_00402204 = uvProfilerCreate(D_game_00401F9C);
    D_game_0040220C = uvProfilerCreate(D_game_00401FA8);
    gGameSettings[0].pauseFlag = 0;
    *(f32 *) ((u8 *) gGameSettings + 0xE8) = 0.0f;
    if ((gGameSettings[0].introReplayState != 0) || (gGameSettings[0].unkC != 0)) {
        gGameSettings[0].dbgDispMasks = 0;
    } else {
        gGameSettings[0].dbgDispMasks = 1;
    }
    uvScSetFrameRetraceThreshold(D_game_004020F4[gGameSettings[0].dbgOptsFrameRate]);
    func_game_004001E4();
    ((GameStartupTerrainExports *) gUvTerraExports)->setSharedWordBF0(0);
}
#line 62 "src/modules/game.c"

#line 7 "src/modules/game.c"
/* Original no-op GAME module-cleanup callback, registered at export offset 0.
 * Native UVMO disposal invokes that export before freeing the export storage.
 * RE_UNKNOWN: broader GAME teardown ownership and other callers need lifecycle
 * evidence; retain this distinct void(void) callback and empty implementation. */
#line 11 "src/modules/game.c"

void gameNoOpModuleCleanup(void) {
}
#line 13 "src/modules/game.c"
#line 9 "src/modules/game.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_004001E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00400C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00400DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00401338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00401568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_004016F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/game/func_game_00401CC0.s")

#line 24 "src/modules/game.c"
/* Release every loaded reference to the caller-indexed module, then clear D_game_004021E0.
 * RE_UNKNOWN: the cleared word's role needs its original writers/readers; table-index validity remains caller-owned. */
void gameUnloadIndexedModuleCompletely(s32 index) {
    s32 tag = D_game_004020B0[index];
    if (uvGetLoadedModule(tag) != NULL) {
        do {
            uvUnloadModule(tag);
        } while (uvGetLoadedModule(tag) != NULL);
    }
    D_game_004021E0 = 0;
}
#line 25 "src/modules/game.c"

