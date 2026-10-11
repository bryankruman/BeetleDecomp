// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

typedef struct Logo_Exports_s {
    void (*logoNoOpModuleCleanup)(void);
    void (*func_logo_0040017C)(void);
    void (*unusedLogoRender)(void);
} Logo_Exports;

void __entrypoint_func_logo_400000(Logo_Exports* arg0) ;
void logoNoOpModuleCleanup(void);
void func_logo_0040017C(void);
void unusedLogoRender(void);

s32 D_logo_004002E0[2]; //padding?
s32 D_logo_004002E8[2];
s32 D_logo_004002D0[] = {0x01000000, 0x000C0000, __entrypoint_func_logo_400000, 0};

/*
 * Install the three logo exports, allocate one sprite and clear its companion
 * word. Load UVBT 40, configure the sprite with the original property list,
 * append a viewport from zero to current screen width/height, reset the
 * GameGUI mode/handler and send screen property 0 with a NULL argument.
 * RE_ORIGINAL_QUIRK: Keep the unused render export and empty cleanup provider;
 * this initializer does not check resource/sprite allocation or import results.
 * RE_UNKNOWN: Property-list meanings beyond the existing provider contract,
 * handler lifetime, viewport capacity and resource release require callers.
 */
#line 21 "src/modules/logo.c"
void __entrypoint_func_logo_400000(Logo_Exports* exports) {
    uvUpdateFileAllocPtr(exports);

    exports->logoNoOpModuleCleanup = logoNoOpModuleCleanup;
    exports->func_logo_0040017C = func_logo_0040017C;
    exports->unusedLogoRender = unusedLogoRender;

    D_logo_004002E8[0] = gUvSprtExports->uvSpriteAllocateFirstFree();
    D_logo_004002E8[1] = 0;

    uvLoadFile('UVBT', 40);

    gUvSprtExports->uvSprtProps(
        D_logo_004002E8[0], 9, 40, 2,
        0, 0, 3, 1,
        7, 0, 0, 0,
        0xFF, 0
    );

    gUvGfxMgrExports->uvGfxAppendViewport(
        0,
        gUvGfxMgrExports->uvGetScreenWidth(),
        0,
        gUvGfxMgrExports->uvGetScreenHeight()
    );

    gGameGuiExports->unk10(0);
    gGameGuiExports->unk1C(gGameGuiExports->unk4);

    gScrnExports->unk4(0, 0);
}

#line 53 "src/modules/logo.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void logoNoOpModuleCleanup(void) {

}
#line 56 "src/modules/logo.c"

#line 57 "src/modules/logo.c"
/* Original no-op exported at logo export slot 0x04. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_logo_0040017C(void) {

}
#line 60 "src/modules/logo.c"

/*
 * While the shared counter is below 90, increment it and truncate the sine
 * ramp times 255 to an integer; later calls use 255. Push graphics state,
 * apply the original masks, set the logo sprite RGB to that intensity with
 * alpha 255, render the sprite and pop graphics state.
 * RE_ORIGINAL_QUIRK: Keep the unused stack local and the (0,255.0f) comma
 * expression. The counter and intensity are neither clamped nor reset here.
 * RE_UNKNOWN: Invocation despite the unused public name, initial counter
 * range and borrowed sprite/provider lifetime require the logo caller.
 */
#line 61 "src/modules/logo.c"
void unusedLogoRender(void) {
    s32 sp28;
    s32 grayIntensity;

    if (D_logo_004002E8[1] < 0x5A) {
        grayIntensity = (s32) ( gUvMathExports->uvSinF((++D_logo_004002E8[1] * 1.5707963f) / 90.0f) * (0,255.0f));
    } else {
        grayIntensity = 0xFF;
    }
    gUvGfxStateExports->uvGfxStatePush();
    gUvGfxStateExports->uvGfxStateSetFlags(0x04800000);
    gUvGfxStateExports->uvGfxClearCurrentStateBits(0x600000);
    gUvSprtExports->uvSprtProps(D_logo_004002E8[0], 7, grayIntensity, grayIntensity, grayIntensity, 0xFF, 0);
    gUvSprtExports->uvSpriteRender(D_logo_004002E8[0]);
    gUvGfxStateExports->uvGfxStatePop();
}
