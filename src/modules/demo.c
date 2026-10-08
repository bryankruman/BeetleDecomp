// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/*__SEEDEXTERNS__*/
typedef struct {
    /* 0x00 */ char pad[0xC];
    /* 0x0C */ void (*unkC)(f32, f32, f32, f32);
} UvGeomExp_00400910;
extern UvGeomExp_00400910 *gUvGeomExports;
typedef struct {
    /* 0x00 */ char pad00[0xC];
    /* 0x0C */ void (*unkC)(s32);
    /* 0x10 */ void (*unk10)(s32);
    /* 0x14 */ void (*unk14)(s32);
    /* 0x18 */ char pad18[0x38];
    /* 0x50 */ void (*unk50)(void);
    /* 0x54 */ void (*unk54)(void);
    /* 0x58 */ char pad58[0x4];
    /* 0x5C */ void (*unk5C)(s32, s32, s32, s32, f32, f32, f32, f32);
} UvGfxStateExp_00400910;
extern UvGfxStateExp_00400910 *gUvGfxStateExports;
extern s32 D_demo_00402270;
extern s32 gNumAiCars;
extern void *gSceneExports;
extern void *D_demo_00402274;
void demoRestoreRaceSelection();
void func_demo_00400290();
void func_demo_0040041C();
void func_demo_00400538();
void func_demo_004009F8();
void func_demo_00400BC4();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/__entrypoint_func_demo_400000.s")

#line 33 "src/modules/demo.c"
/* Restore the saved AI-car count, obtain track zero from the scene export
 * and clear the tournament selection. Preserve the original export lookup. */
void demoRestoreRaceSelection(void) {
    gNumAiCars = D_demo_00402270;
    gGameSettings->currentTrack = ((s32 (*)(s32))((s32 *)gSceneExports)[1])(0);
    gGameSettings->currentTournament = 0;
}
#line 38 "src/modules/demo.c"
/*
 * RE_UNKNOWN: shared threshold/step units, replay masks 0x1000/0x8000 and
 * AI-tail/camera/collection storage/alias/lifetime guarantees. Trace original
 * setup, record/step writers and downstream copied-word readers. Original
 * callbacks copy tail word 0x14 to camera 0x1E8, write 13 at 0x1EC and pass tail
 * word 4 through CAM tag19 to 0x214; tag0 terminates. Preserve ordered f32
 * comparison, independent AI checks and every callback/global-reload order.
 * RE_ORIGINAL_QUIRK: the original returned AI tail is dereferenced unchecked;
 * empty-tail reachability requires caller/setup proof, not a new player bug.
 * Readable recovery remains parked: 396 original versus 404 candidate bytes,
 * 87 differing words and relocation mismatches, including generated global
 * address lifetimes. Require complete instruction/module/ROM proof before
 * replacing ASM; no storage/layout or physical meanings inferred to match.
 */
#line 39 "src/modules/demo.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_0040041C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400538.s")

/* Set up the graphics state and draw a full-screen demo overlay rectangle. */
#line 46 "src/modules/demo.c"
/* Push graphics state, select the original modes and texture, draw a black
 * rectangle with supplied alpha at X 22..297/Y 16..223, then pop state. */
void demoDrawBlackOverlay(f32 alpha) {
    gUvGfxStateExports->unk50();
    gUvGfxStateExports->unkC(0x04820FFF);
    gUvGfxStateExports->unk10(0x9B7C0000);
    gUvGeomExports->unkC(0.0f, 0.0f, 0.0f, alpha);
    gUvGfxStateExports->unk14(0xFFF);
    gUvGfxStateExports->unk5C(0x16, 0x129, 0x10, 0xDF, 0.0f, 2.0f, 0.0f, 2.0f);
    gUvGfxStateExports->unk54();
}
#line 55 "src/modules/demo.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_004009F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400BC4.s")

