// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void __entrypoint_func_cbars_400000(Cbars_Exports* exports);
void func_cbars_004000E4(void);
void func_cbars_004000EC(void);
void cbarsRenderDiagnosticPattern(void);
void cbarsDrawColorBarsAndGrayscale(void);

// .bss
s32 B_cbars_00400580[4]; // unreferenced padding

void __entrypoint_func_cbars_400000(Cbars_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->func_cbars_004000E4 = &func_cbars_004000E4;
    exports->func_cbars_004000EC = &func_cbars_004000EC;
    exports->cbarsRenderDiagnosticPattern = &cbarsRenderDiagnosticPattern;
    gUvGfxMgrExports->uvGfxAppendViewport(0, gUvGfxMgrExports->uvGetScreenWidth(), 0, gUvGfxMgrExports->uvGetScreenHeight());
    gGameGuiExports->unk10(0);
    gGameGuiExports->unk1C(gGameGuiExports->unk4);
    gScrnExports->unk4(0, 0);
}

void func_cbars_004000E4(void) {
}

void func_cbars_004000EC(void) {
}

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
