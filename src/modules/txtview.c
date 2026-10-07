// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
extern UvGeom_Exports *gUvGeomExports;
extern UvGfxState_Rom_Exports *gUvGfxStateExports;
extern s32 D_txtview_00400C94;
extern s32 D_txtview_00400C98;
extern UnkGameGuiExports *gGameGuiExports;
void txtviewBindDrawCallbackAndEnableGui(s32);
void func_txtview_00400420(void);
void txtviewUnloadCurrentTexture();
void txtviewEnableWhenInactive();
void txtviewDrawTexturePanel(void);
void txtviewBindDrawCallbackAndEnableGui();
void func_txtview_00400298();
void func_txtview_00400420();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/__entrypoint_func_txtview_400000.s")

#line 19 "src/modules/txtview.c"
/* Unload the currently selected UVTX texture file through the
 * original file manager. Retain the stored texture ID. */
void txtviewUnloadCurrentTexture(void) {
    uvUnloadFile(0x55565458, D_txtview_00400C94);
}
#line 22 "src/modules/txtview.c"

#line 23 "src/modules/txtview.c"
/* Enable the texture viewer only while its shared activation count
 * is zero. Further calls preserve the existing count and callback binding. */
void txtviewEnableWhenInactive(void) {
    if (D_txtview_00400C98 == 0) {
        txtviewBindDrawCallbackAndEnableGui(0);
    }
}
#line 28 "src/modules/txtview.c"

#line 29 "src/modules/txtview.c"
/* Fill the screen and draw the text-view texture panel when its texture ID
 * is valid. Keep the original render state and texture coordinates. */
extern f32 D_txtview_00400C9C;
extern f32 D_txtview_00400CA0;
extern f32 D_txtview_00400CA4;
extern f32 D_txtview_00400CA8;
extern f32 D_txtview_00400CAC;
extern f32 D_txtview_00400CB0;

void txtviewDrawTexturePanel(void) {
    if (D_txtview_00400C94 >= 0) {
        gUvGeomExports->uvSetFillColor(D_txtview_00400CA4, D_txtview_00400CA8, D_txtview_00400CAC, D_txtview_00400CB0);
        gUvGeomExports->uvVtxRect(0, 0, 0x13F, 0xEF);
        gUvGfxStateExports->uvGfxClearCurrentStateBits(0x1A240000);
        gUvGfxStateExports->uvGfxStateBindTexture(D_txtview_00400C94);
        gUvGfxStateExports->uvGfxDrawTextureRectangleWithUvRange(0x14, 0xC8, 0x14, 0xC8, 0.0f, D_txtview_00400C9C, 0.0f, D_txtview_00400CA0);
    }
}
#line 30 "src/modules/txtview.c"

#line 31 "src/modules/txtview.c"
/* Bind the texture-viewer draw callback, enable the game GUI and
 * increment the shared activation count. Preserve the unused callback
 * parameter and original increment behavior. */
void txtviewBindDrawCallbackAndEnableGui(s32 callbackValue) {
    gGameGuiExports->unk1C((s32) func_txtview_00400420);
    gGameGuiExports->unk10(1);
    D_txtview_00400C98 += 1;
}
#line 36 "src/modules/txtview.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/func_txtview_00400298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/func_txtview_00400420.s")

