// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

/* Original GUI initializer binds these exact slots. Return words are narrowed
 * explicitly as in the caller; unused slots are not callable declarations.
 * RE_UNKNOWN: historical allocator/caller declarations and complete GUI API;
 * original bindings establish the consumed operations, not source typedefs. */
typedef struct {
    u8 unused00[8];
    void (*appendChild)(void *, void *);
    u8 unused0C[0x34];
    s32 (*allocateCompactText)(void);
    void *(*getCompactText)(s16);
    void (*copyCompactText12)(void *, u8 *);
    u8 unused4C[0x14];
    void (*attachUpperChild)(void *, void *);
    u8 unused64[0xC];
    s32 (*allocateChildGroup)(void);
    void *(*getChildGroup)(s16);
    void (*copyChildGroupText30)(void *, u8 *);
    u8 unused7C[8];
    void (*attachTextList)(void *, void *);
    u8 unused88[0xC];
    s32 (*allocateTextList)(void);
    void *(*getTextList)(s16);
    void (*copyTextListText30)(void *, u8 *);
    u8 unusedA0[8];
    void (*appendCompactTextRow)(void *, void *);
    u8 unusedAC[0xC];
    s32 (*allocateUpperText)(void);
    u8 unusedBC[4];
    void *(*getUpperText)(s16);
    void (*copyUpperText30)(void *, u8 *);
    u8 unusedC8[8];
    void (*setWord40)(void *, u32);
    void (*configureBoundScalar)(void *, f32, f32, f32, void *);
    void (*setShort20)(void *, s16);
} TxtviewGuiConstructionExports;
extern TxtviewGuiConstructionExports *gUvGuiExports;
/* Original GAMEGUI slot28 is a shared byte-storage address; this caller takes
 * its+0x10 before invoking slot14. Preserve that snapshot across the callback.
 * RE_UNKNOWN: complete storage extent/lifecycle and historical source layout;
 * inspect original allocation and every shared-state reader before expanding. */
typedef struct {
    u8 unused00[0x14];
    void (*initializeSharedWidget)(void);
    u8 unused18[0x10];
    u8 *sharedState;
} TxtviewGameGuiConstructionExports;
extern u8 D_txtview_00400C14[];
extern u8 D_txtview_00400C24[];
extern u8 D_txtview_00400C34[];
extern u8 D_txtview_00400C40[];
extern u8 D_txtview_00400C44[];
extern u8 D_txtview_00400C54[];
extern u8 D_txtview_00400C64[];
extern u8 D_txtview_00400C68[];
extern u8 D_txtview_00400C70[];
extern u8 D_txtview_00400C78[];

extern UvGeom_Exports *gUvGeomExports;
extern UvGfxState_Rom_Exports *gUvGfxStateExports;
extern s32 D_txtview_00400C94;
extern s32 D_txtview_00400C98;
extern UnkGameGuiExports *gGameGuiExports;
void txtviewBindDrawCallbackAndEnableGui(s32);
void txtviewBuildTextureControlPanel(void);
void txtviewUnloadCurrentTexture();
void txtviewEnableWhenInactive();
void txtviewDrawTexturePanel(void);
void txtviewBindDrawCallbackAndEnableGui();
void func_txtview_00400298();
void txtviewBuildTextureControlPanel();
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
    gGameGuiExports->unk1C((s32) txtviewBuildTextureControlPanel);
    gGameGuiExports->unk10(1);
    D_txtview_00400C98 += 1;
}
#line 36 "src/modules/txtview.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/txtview/func_txtview_00400298.s")

#line 39 "src/modules/txtview.c"
/* Build the texture-viewer GUI group and seven controls for texture ID,
 * U/V coordinates and RGBA components. Preserve the shared-root snapshot,
 * GUI export reloads, allocation/get conversions and original attachment order.
 * Bind each coordinate/color control directly to its existing persistent float;
 * texture-ID selection retains the original callback and zero initial value.
 * RE_UNKNOWN: complete root and GUI-pool capacity/lifetime, label-object extents
 * and texture-selection callback ABI. Original text helpers read fixed12/30
 * bytes rather than stopping at NUL; inspect original data and callers before
 * assuming each short label has that much individual storage. No caller-side
 * allocation-failure or empty-file-list checks are added; reachability of those
 * original conditions requires pool and resource inventory evidence. */
void txtviewBuildTextureControlPanel(void) {
    void *group;
    void *row;
    void *textList;
    void *control;
    s32 maximumTextureId;
    u8 *root;

    root = ((TxtviewGameGuiConstructionExports *)gGameGuiExports)->sharedState + 0x10;
    ((TxtviewGameGuiConstructionExports *)gGameGuiExports)->initializeSharedWidget();
    group = gUvGuiExports->getChildGroup((s16)gUvGuiExports->allocateChildGroup());
    gUvGuiExports->copyChildGroupText30(group, D_txtview_00400C14);
    gUvGuiExports->appendChild(root, group);
    textList = gUvGuiExports->getTextList((s16)gUvGuiExports->allocateTextList());
    gUvGuiExports->copyTextListText30(textList, D_txtview_00400C24);
    gUvGuiExports->attachTextList(group, textList);

    /* Texture selection keeps its original zero default and callback word. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C34);
    gUvGuiExports->appendCompactTextRow(textList, row);
    maximumTextureId = uvGetFilesCount(0x55565458) - 1;
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 2);
    gUvGuiExports->configureBoundScalar(control, 0.0f, (f32)maximumTextureId, 0.0f, NULL);
    /* RE_UNKNOWN: callback source prototype/argument contract. SlotD0 stores
     * this original raw32 address; inspect the original invocation path before
     * turning the stored word into a typed function-pointer declaration. */
    gUvGuiExports->setWord40(control, (u32)func_txtview_00400298);
    gUvGuiExports->copyUpperText30(control, D_txtview_00400C40);
    gUvGuiExports->attachUpperChild(row, control);

    /* U coordinate, using the original persistent scalar binding. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C44);
    gUvGuiExports->appendCompactTextRow(textList, row);
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 0x11);
    gUvGuiExports->configureBoundScalar(control, 0.0f, 2.0f, 0.0f, &D_txtview_00400C9C);
    gUvGuiExports->attachUpperChild(row, control);

    /* V coordinate, using the original persistent scalar binding. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C54);
    gUvGuiExports->appendCompactTextRow(textList, row);
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 0x11);
    gUvGuiExports->configureBoundScalar(control, 0.0f, 2.0f, 0.0f, &D_txtview_00400CA0);
    gUvGuiExports->attachUpperChild(row, control);

    /* Red component, using the original persistent scalar binding. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C64);
    gUvGuiExports->appendCompactTextRow(textList, row);
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 0x11);
    gUvGuiExports->configureBoundScalar(control, 0.0f, 1.0f, 0.0f, &D_txtview_00400CA4);
    gUvGuiExports->attachUpperChild(row, control);

    /* Green component, using the original persistent scalar binding. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C68);
    gUvGuiExports->appendCompactTextRow(textList, row);
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 0x11);
    gUvGuiExports->configureBoundScalar(control, 0.0f, 1.0f, 0.0f, &D_txtview_00400CA8);
    gUvGuiExports->attachUpperChild(row, control);

    /* Blue component, using the original persistent scalar binding. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C70);
    gUvGuiExports->appendCompactTextRow(textList, row);
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 0x11);
    gUvGuiExports->configureBoundScalar(control, 0.0f, 1.0f, 0.0f, &D_txtview_00400CAC);
    gUvGuiExports->attachUpperChild(row, control);

    /* Alpha component, using the original persistent scalar binding. */
    row = gUvGuiExports->getCompactText((s16)gUvGuiExports->allocateCompactText());
    gUvGuiExports->copyCompactText12(row, D_txtview_00400C78);
    gUvGuiExports->appendCompactTextRow(textList, row);
    control = gUvGuiExports->getUpperText((s16)gUvGuiExports->allocateUpperText());
    gUvGuiExports->setShort20(control, 0x11);
    gUvGuiExports->configureBoundScalar(control, 0.0f, 1.0f, 0.0f, &D_txtview_00400CB0);
    gUvGuiExports->attachUpperChild(row, control);
}
#line 40 "src/modules/txtview.c"

