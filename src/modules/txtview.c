// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
extern UvGeom_Exports *gUvGeomExports;
extern UvGfxState_Rom_Exports *gUvGfxStateExports;
extern s32 D_txtview_00400C94;
extern s32 D_txtview_00400C98;
extern UnkGameGuiExports *gGameGuiExports;
void func_txtview_00400238(s32);
void func_txtview_00400420(void);
void func_txtview_004000EC();
void func_txtview_00400118();
void txtviewDrawTexturePanel(void);
void func_txtview_00400238();
void func_txtview_00400298();
void func_txtview_00400420();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/__entrypoint_func_txtview_400000.s")

void func_txtview_004000EC(void) {
    uvUnloadFile(0x55565458, D_txtview_00400C94);
}

void func_txtview_00400118(void) {
    if (D_txtview_00400C98 == 0) {
        func_txtview_00400238(0);
    }
}

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
        gUvGfxStateExports->func_uvgfxstate_rom_00402350(0x14, 0xC8, 0x14, 0xC8, 0.0f, D_txtview_00400C9C, 0.0f, D_txtview_00400CA0);
    }
}
#line 30 "src/modules/txtview.c"

void func_txtview_00400238(s32 arg0) {
    gGameGuiExports->unk1C((s32) func_txtview_00400420);
    gGameGuiExports->unk10(1);
    D_txtview_00400C98 += 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/func_txtview_00400298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/func_txtview_00400420.s")

