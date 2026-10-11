// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void __entrypoint_func_cbars_400000(Cbars_Exports* exports);
void cbarsNoOpModuleCleanup(void);
void func_cbars_004000EC(void);
void cbarsRenderDiagnosticPattern(void);
void cbarsDrawColorBarsAndGrayscale(void);

// .bss
s32 B_cbars_00400580[4]; // unreferenced padding

/*
 * Install the no-op cleanup, separate no-op export and diagnostic-pattern
 * renderer. Append a viewport from zero to the provider screen dimensions,
 * then call GUI slot 0x10 with zero, GUI slot 0x1C with its slot-0x04 value,
 * and SCRN slot 0x04 with two zeros, in that order.
 * RE_ORIGINAL_QUIRK: Keep both distinct no-op exports and reload shared
 * provider pointers after calls; this initializer draws no color bars itself.
 * RE_UNKNOWN: GUI/SCRN slot semantics, callback effects, screen-range validity
 * and provider lifetime require the diagnostic setup owners.
 */
#line 15 "src/modules/cbars.c"
void __entrypoint_func_cbars_400000(Cbars_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->cbarsNoOpModuleCleanup = &cbarsNoOpModuleCleanup;
    exports->func_cbars_004000EC = &func_cbars_004000EC;
    exports->cbarsRenderDiagnosticPattern = &cbarsRenderDiagnosticPattern;
    gUvGfxMgrExports->uvGfxAppendViewport(0, gUvGfxMgrExports->uvGetScreenWidth(), 0, gUvGfxMgrExports->uvGetScreenHeight());
    gGameGuiExports->unk10(0);
    gGameGuiExports->unk1C(gGameGuiExports->unk4);
    gScrnExports->unk4(0, 0);
}

#line 26 "src/modules/cbars.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void cbarsNoOpModuleCleanup(void) {
}
#line 28 "src/modules/cbars.c"

#line 29 "src/modules/cbars.c"
/* Original no-op exported at cbars export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_cbars_004000EC(void) {
}
#line 31 "src/modules/cbars.c"

#line 32 "src/modules/cbars.c"
/* Render the original color-bar and grayscale diagnostic pattern
 * through its dedicated draw helper. Preserve the exported callback ABI. */
void cbarsRenderDiagnosticPattern(void) {
    cbarsDrawColorBarsAndGrayscale();
}
#line 35 "src/modules/cbars.c"

#line 36 "src/modules/cbars.c"
/* Set the original inset viewport and draw seven full-color bars,
 * seven alternating reference bars and twenty-eight grayscale steps.
 * Preserve the reused floating scalar, coordinate narrowing and color order. */
void cbarsDrawColorBarsAndGrayscale(void) {
    f32 sharedValue;
    f32 red;
    f32 green;
    f32 blue;
    f32 left;
    int tmp;
    f32 firstY;
    f32 secondY;
    f32 temp_s3;
    s32 barIndex;

    sharedValue = 78.100006f;
    gUvGfxMgrExports->uvGfxAppendViewport(0x16, 0x129, 0x10, 0xDF);
    left = 22.0f;
    firstY = 223.0f;
    secondY = 78.100006f;
    for (barIndex = 0; barIndex < 7; barIndex++) {
        switch (barIndex) {
            case 0:
                red = 1.0f;
                green = 1.0f;
                blue = 1.0f;
                break;

            case 1:
                red = 1.0f;
                green = 1.0f;
                blue = 0.0f;
                break;

            case 2:
                red = 0.0f;
                green = 1.0f;
                blue = 1.0f;
                break;

            case 3:
                red = 0.0f;
                green = 1.0f;
                blue = 0.0f;
                break;

            case 4:
                red = 1.0f;
                green = 0.0f;
                blue = 1.0f;
                break;

            case 5:
                red = 1.0f;
                green = 0.0f;
                blue = 0.0f;
                break;

            case 6:
                red = 0.0f;
                green = 0.0f;
                blue = 1.0f;
                break;
        }

        gUvGeomExports->uvSetFillColor(red, green, blue, 1.0f);
        gUvGeomExports->uvVtxRect(((s16)left), (s16) secondY, ((s16)left) + 39.42857f, (s16) firstY);
        left += 39.42857f;
    }

    left = 22.0f;
    secondY = sharedValue;
    firstY = 67.0f;
    for (barIndex = 0; barIndex < 7; barIndex++) {
        switch (barIndex) {
            case 0:
                red = 0.0f;
                green = 0.0f;
                blue = 1.0f;
                break;

            case 1:
                red = 0.0f;
                green = 0.0f;
                blue = 0.0f;
                break;

            case 2:
                red = 1.0f;
                green = 0.0f;
                blue = 1.0f;
                break;

            case 3:
                red = 0.0f;
                green = 0.0f;
                blue = 0.0f;
                break;

            case 4:
                red = 0.0f;
                green = 1.0f;
                blue = 1.0f;
                break;

            case 5:
                red = 0.0f;
                green = 0.0f;
                blue = 0.0f;
                break;

            case 6:
                red = 1.0f;
                green = 1.0f;
                blue = 1.0f;
                break;
        }

        gUvGeomExports->uvSetFillColor(red, green, blue, 1.0f);
        gUvGeomExports->uvVtxRect(((s16)left), (s16) firstY, ((s16)left) + 39.42857f, (s16) secondY);
        left += 39.42857f;
        sharedValue = 67;
    }

    firstY = 16.0f;
    secondY = sharedValue;
    left = 22.0f;
    for (barIndex = 0; barIndex < 0x1C; barIndex++) {
        sharedValue = barIndex / 27.0f;
        gUvGeomExports->uvSetFillColor(sharedValue, sharedValue, sharedValue, 1.0f);
        gUvGeomExports->uvVtxRect(((s16)left), (s16) firstY, ((s16)left) + 9.857142f, (s16) secondY);
        left += 9.857142f;
    }
}
#line 167 "src/modules/cbars.c"

// .data
s32 D_cbars_00400570[] = {0x000C0000, __entrypoint_func_cbars_400000, 0, 0};
