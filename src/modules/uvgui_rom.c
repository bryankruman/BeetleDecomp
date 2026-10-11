// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"
#include "uvgui_rom.h"
#define GUI_ROUNDF(val) (((val) >= 0.0f) ? (s32) ((val) + 0.50f) : (s32) ((val) - 0.50f))

/* Native readonly string-region view: the two 30-byte INPUT/OUTPUT reads
 * remain within this single 72-byte object. RE_UNKNOWN: Historical source
 * storage declaration and exported caller alias/lifetime domains are unresolved;
 * full readonly bytes and reference targets still require compiler proof. */
static const u8 sGuiNativeStringRegion[72] = {
    0x25, 0x66, 0x00, 0x00, 0x25, 0x64, 0x00, 0x00, 0x49, 0x4E, 0x50, 0x55,
    0x54, 0x00, 0x00, 0x00, 0x4F, 0x55, 0x54, 0x50, 0x55, 0x54, 0x00, 0x00,
    0x25, 0x73, 0x5F, 0x76, 0x73, 0x5F, 0x25, 0x73, 0x00, 0x00, 0x00, 0x00,
    0x25, 0x73, 0x20, 0x2A, 0x20, 0x25, 0x73, 0x00, 0x25, 0x66, 0x00, 0x00,
    0x25, 0x66, 0x00, 0x00, 0x25, 0x66, 0x00, 0x00, 0x25, 0x66, 0x00, 0x00,
    0x25, 0x66, 0x00, 0x00, 0x25, 0x64, 0x00, 0x00, 0x25, 0x66, 0x00, 0x00,
};


/* RE_UNKNOWN: Pool endpoints/strides match native BSS witnesses, but valid
 * indices, exhaustion paths, callback lifetimes and alias domains require callers.
 * Keep raw native-symbol aliases separate from these typed storage owners. */
// exports
Inner2C sGuiVectorSlots[10];
static UvFMtx_Rom_Exports *sUvFMtxExports;
static UvFont_Exports *sUvFontExports;
static UvGfxMgr_Exports *sUvGfxMgrExports;
static UvGfxState_Rom_Exports *sUvGfxStateExports;
static UvDGeom_Rom_Exports *sUvDGeomExports;
static UvGrph_Exports *sUvGrphExports;
static UvCont_Exports *sUvContExports;
static UvString_Exports *sUvStringExports;
GuiMenuItem sGuiMenuItems[120];
GuiMenu sGuiMenus[8];
GuiMenuOption sGuiMenuOptions[50];
Inner28 sGuiScalarSlots[135];
Inner30 sGuiValueSlots[20];

// .data
s16 D_uvgui_rom_00406F00 = 0;


#line 3 "src/modules/uvgui_rom.c"
typedef struct { u8 prefix[0x1E]; s16 state, left, right, top, bottom; void *children[80]; s16 count; s16 matchedChildIndex; s16 width; } GuiDrawTextList;
typedef struct { u8 prefix[0x28]; void *first, *second; } GuiCenteredAttachments;
typedef struct { u8 prefix[0x88]; s32 (*width)(void); } GuiDisplayWidthExports;
extern GuiDisplayWidthExports *D_uvgui_rom_00407220;
typedef struct { f32 x, y, z; } GuiVector3;
typedef struct { u8 unk00[0x20]; s16 kind; u8 unk22[2]; GuiVector3 value; GuiVector3 *source; f32 first, second; } GuiVectorState;
#include "stdarg.h"
/*__SEEDEXTERNS__*/
/* Prefix view for the option target; the complete object size is unknown. */
typedef struct { u8 unk00[0x62]; s16 unk62; } GuiField62Target;
typedef struct { u8 unk00[0x1E]; s16 active; u8 unk20[8]; s32 entries[12]; s16 unk58; s16 unk5A; } GuiPoolSlot5C;
typedef struct { u8 unk00[0xC]; s16 active; u8 unk0E[0x26]; } GuiPoolSlot34;
typedef struct { u8 unk00[0x1E]; s16 active; u8 unk20[0x150]; } GuiPoolSlot170;
typedef struct GuiPoolSlot48_s { u8 unk00[0x1E]; s16 active; u8 unk20[0x20]; void (*onActiveChanged)(struct GuiPoolSlot48_s *, s16); u8 unk44[4]; } GuiPoolSlot48;
typedef struct { u8 unk00[0x5E]; s16 active; u8 unk60[0x30]; } GuiPoolSlot90;
typedef struct { u8 unk00[0x1E]; s16 active; u8 unk20[0x2C]; } GuiPoolSlot4C;
extern void *D_uvgui_rom_0040721C;
extern u8 D_uvgui_rom_00407238;
extern u8 D_uvgui_rom_00408A98;
extern u8 D_uvgui_rom_00408D78;
extern u8 D_uvgui_rom_0040D558;
extern s16 D_uvgui_rom_0040D576;
extern u8 D_uvgui_rom_0040FB50;
extern u8 D_uvgui_rom_00406F20;
extern s16 D_uvgui_rom_00406F3E;
void uvGuiModuleCleanup();
void uvGuiSetChildContainerBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void uvGuiSetPositionAndCurrentScalars(void *arg0, s16 arg1, s16 arg2);
s16 uvGuiAllocatePool34Slot(void);
void *uvGuiGetCompactTextSlot(s16 arg0);
void uvGuiSetCompactTextBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void uvGuiSetPropertyWords(void *arg0, s16 arg1, s32 arg2);
void uvGuiAttachCenteredUpperChild(GuiCenteredAttachments *owner, void *child);
void uvGuiAttachCenteredLowerChild(GuiCenteredAttachments *owner, void *child);
s16 uvGuiAllocatePool5CSlot(void);
void *uvGuiGetChildGroupSlot(s16 arg0);
void uvGuiSetChildGroupBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
s16 uvGuiAllocatePool170Slot(void);
void *uvGuiGetTextListSlot(s16 arg0);
void uvGuiSetTextListBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void uvGuiDrawTextList(GuiDrawTextList *widget);
s32 uvGuiUpdateTextListHitState(GuiDrawTextList *, u8, s16, s16, s32, f32, f32);
s16 uvGuiAllocatePool48Slot(void);
void uvGuiClearUpperTextSlotState(short arg0);
void *uvGuiGetUpperTextSlot(s16 arg0);
void uvGuiSetUpperTextBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void uvGuiSetPool48Active(GuiPoolSlot48 *slot, s16 active);
s16 uvGuiAllocatePool90Slot(void);
void uvGuiClearValueWidgetSlotState(s32 arg0);
void *uvGuiGetValueWidgetSlot(s16 arg0);
void uvGuiSetValueWidgetBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void uvGuiConfigureValueWidget(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5);
void uvGuiSetValueWidgetState(void *arg0, s16 arg1);
void uvGuiSetField62Props(GuiField62Target *target, ...);
s16 uvGuiAllocatePool4CSlot(void);
void uvGuiClearLowerTextSlotState(s32 arg0);
void *uvGuiGetLowerTextSlot(s16 arg0);
void uvGuiSetLowerTextBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void uvGuiConfigureVectorSource(GuiVectorState *state, f32 first, f32 second, GuiVector3 *fallback, GuiVector3 *source);
void uvGuiSetMode(void *arg0, s16 arg1);
extern s16 D_uvgui_rom_00406F00;

void __entrypoint_func_uvgui_rom_400000(UvGui_Exports *exports);
void uvGuiModuleCleanup(void);
void uvGuiResetStateAndPools(uvGui *gui);
void uvGuiAppendChildRow(s32 *group, s32 child);
void uvGuiDrawMenusAndCursor(uvGui *arg0);
void uvGuiDrawShadedInsetRectangle(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 r, u8 g, u8 b, u8 a);
void uvGuiDrawCenteredText(s16 x0, s16 x1, s16 y0, s16 y1, void *str, u8 r, u8 g, u8 b, u8 a);
void uvGuiDrawFlashingCursor(s16 x, s16 y);
void uvGuiSetChildContainerBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
s32 uvGuiUpdateInputAndMenuHitStates(uvGui *arg0);
void uvGuiSetInputWordProperty(uvGui *arg0, s16 arg1, s32 arg2);
void uvGuiLoadDisplayDataAndPalette(void *widget, s16 displayData, s16 palette);
void uvGuiSetByte8A(void *element, u8 value);
void uvGuiSetPositionAndCurrentScalars(void *widget, s16 first, s16 second);
void uvGuiSetSharedShort(s16 value);
void uvGuiLayoutMenuOptionRows(uvGui *arg0);
void uvGuiResetMenuItemPool(void);
s16 uvGuiAllocatePool34Slot(void);
void *uvGuiGetCompactTextSlot(s16 index);
void uvGuiCopyCompactTextUppercaseSpan(s32 destinationAddress, u8 *source);
void uvGuiSetCompactTextState(void *widget, s16 state);
void uvGuiSetCompactTextBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
void uvGuiDrawMenuItemAndAttachments(GuiMenuItem *arg0);
s32 uvGuiUpdateMenuItemHitState(GuiMenuItem *arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4,
                            f32 arg5, f32 arg6);
void uvGuiSetPropertyWords(void *element, s16 property, s32 value);
void uvGuiAttachCenteredUpperChild(GuiCenteredAttachments *owner, void *child);
void uvGuiAttachCenteredLowerChild(GuiCenteredAttachments *owner, void *child);
void uvGuiAttachValueWidgetBesideItem(GuiMenuItem *arg0, Inner30 *arg1);
void uvGuiResetMenuPool(void);
s16 uvGuiAllocatePool5CSlot(void);
void *uvGuiGetChildGroupSlot(s16 index);
void uvGuiCopyChildGroupText(void *destination, u8 *source);
void uvGuiSetChildGroupState(void *widget, s16 state);
void uvGuiSetChildGroupBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
void uvGuiAppendMenuOption(GuiMenu *menu, GuiMenuOption *menuOption);
void uvGuiDrawPanelOrTextLists(void *panel);
s32 uvGuiUpdateMenuHitState(GuiMenu *arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5,
                            f32 arg6);
void uvGuiResetMenuOptionPool(void);
s16 uvGuiAllocatePool170Slot(void);
void *uvGuiGetTextListSlot(s16 index);
void uvGuiCopyTextListText(void *destination, u8 *source);
void uvGuiSetTextListState(void *widget, s16 state);
void uvGuiSetTextListBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
void uvGuiAppendCompactTextRow(void *panel, s32 text);
void uvGuiDrawTextList(GuiDrawTextList *widget);
s32 uvGuiUpdateTextListHitState(GuiDrawTextList *widget, u8 inputByte,
                           s16 horizontal, s16 vertical, s32 forwardedWord,
                           f32 firstScalar, f32 secondScalar);
void uvGuiResetScalarWidgetPool(void);
s16 uvGuiAllocatePool48Slot(void);
void uvGuiClearUpperTextSlotState(short index);
void *uvGuiGetUpperTextSlot(s16 index);
void uvGuiCopyUpperTextText(void *destination, u8 *source);
void uvGuiSetUpperTextBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
void uvGuiDrawScalarWidget(Inner28 *arg0);
void uvGuiSetWord40(void *element, s32 value);
void uvGuiConfigureScalarWidgetSource(Inner28 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 *arg4);
void uvGuiSetShort20(void *element, s16 value);
void uvGuiUpdateScalarWidget(Inner28 *arg0, u8 arg1, f32 arg2);
void uvGuiSetPool48Active(GuiPoolSlot48 *slot, s16 active);
void uvGuiSetWord44(void *element, s32 value);
void uvGuiResetValueWidgetPool(void);
s16 uvGuiAllocatePool90Slot(void);
void uvGuiClearValueWidgetSlotState(s32 indexWord);
void *uvGuiGetValueWidgetSlot(s16 index);
void uvGuiSetValueWidgetBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
void uvGuiSetValueWidgetLabels(Inner30 *arg0, u8 *arg1, u8 *arg2);
void uvGuiConfigureValueWidget(void *widget, s32 identifier, f32 first, f32 second, f32 fallback, f32 *source);
void uvGuiSetWord8C(void *element, s32 value);
void uvGuiUpdateGraphWidget(Inner30 *arg0, u8 button, f32 arg2);
void uvGuiDrawGraphWidget(Inner30 *arg0);
void uvGuiSetValueWidgetState(void *widget, s16 state);
void uvGuiSetField62Props(GuiField62Target *target, ...);
void uvGuiResetVectorWidgetPool(void);
s16 uvGuiAllocatePool4CSlot(void);
void uvGuiClearLowerTextSlotState(s32 index);
void *uvGuiGetLowerTextSlot(s16 index);
void uvGuiCopyLowerTextText(void *destination, u8 *source);
void uvGuiSetLowerTextBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom);
void uvGuiDrawVectorWidget(Inner2C *arg0);
void uvGuiSetWord48(void *element, s32 value);
void uvGuiConfigureVectorSource(GuiVectorState *state, f32 first, f32 second, GuiVector3 *fallback, GuiVector3 *source);
void uvGuiSetAlternateShort20(void *element, s16 value);
void uvGuiUpdateVectorWidget(Inner2C *arg0, u8 arg1, f32 arg2);
void uvGuiSetMode(void *element, s16 mode);

/* Original incoming export base and all 82 slots are independently proved.
 * Preserve accepted function signatures rather than impose upstream pool types.
 * RE_UNKNOWN: This observed view does not establish historical prototypes,
 * valid pool bounds, callback reachability, alias exclusions or lifetimes. */
struct UvGui_Exports_s {
    /* 0x000 */ void (*uvGuiModuleCleanup)(void);
    /* 0x004 */ void (*uvGuiResetStateAndPools)(uvGui *);
    /* 0x008 */ void (*uvGuiAppendChildRow)(s32 *, s32);
    /* 0x00C */ void (*uvGuiDrawMenusAndCursor)(uvGui *);
    /* 0x010 */ void (*uvGuiDrawShadedInsetRectangle)(s16, s16, s16, s16, s16, u8, u8, u8, u8);
    /* 0x014 */ void (*uvGuiDrawCenteredText)(s16, s16, s16, s16, void *, u8, u8, u8, u8);
    /* 0x018 */ void (*uvGuiDrawFlashingCursor)(s16, s16);
    /* 0x01C */ void (*uvGuiSetChildContainerBounds)(void *, s16, s16, s16, s16);
    /* 0x020 */ s32 (*uvGuiUpdateInputAndMenuHitStates)(uvGui *);
    /* 0x024 */ void (*uvGuiSetInputWordProperty)(uvGui *, s16, s32);
    /* 0x028 */ void (*uvGuiLoadDisplayDataAndPalette)(void *, s16, s16);
    /* 0x02C */ void (*uvGuiSetByte8A)(void *, u8);
    /* 0x030 */ void (*uvGuiSetPositionAndCurrentScalars)(void *, s16, s16);
    /* 0x034 */ void (*uvGuiSetSharedShort)(s16);
    /* 0x038 */ void (*uvGuiLayoutMenuOptionRows)(uvGui *);
    /* 0x03C */ void (*uvGuiResetMenuItemPool)(void);
    /* 0x040 */ s16 (*uvGuiAllocatePool34Slot)(void);
    /* 0x044 */ void * (*uvGuiGetCompactTextSlot)(s16);
    /* 0x048 */ void (*uvGuiCopyCompactTextUppercaseSpan)(s32, u8 *);
    /* 0x04C */ void (*uvGuiSetCompactTextState)(void *, s16);
    /* 0x050 */ void (*uvGuiSetCompactTextBounds)(void *, s16, s16, s16, s16);
    /* 0x054 */ void (*uvGuiDrawMenuItemAndAttachments)(GuiMenuItem *);
    /* 0x058 */ s32 (*uvGuiUpdateMenuItemHitState)(GuiMenuItem *, u8, s16, s16, s32, f32, f32);
    /* 0x05C */ void (*uvGuiSetPropertyWords)(void *, s16, s32);
    /* 0x060 */ void (*uvGuiAttachCenteredUpperChild)(GuiCenteredAttachments *, void *);
    /* 0x064 */ void (*uvGuiAttachCenteredLowerChild)(GuiCenteredAttachments *, void *);
    /* 0x068 */ void (*uvGuiAttachValueWidgetBesideItem)(GuiMenuItem *, Inner30 *);
    /* 0x06C */ void (*uvGuiResetMenuPool)(void);
    /* 0x070 */ s16 (*uvGuiAllocatePool5CSlot)(void);
    /* 0x074 */ void * (*uvGuiGetChildGroupSlot)(s16);
    /* 0x078 */ void (*uvGuiCopyChildGroupText)(void *, u8 *);
    /* 0x07C */ void (*uvGuiSetChildGroupState)(void *, s16);
    /* 0x080 */ void (*uvGuiSetChildGroupBounds)(void *, s16, s16, s16, s16);
    /* 0x084 */ void (*uvGuiAppendMenuOption)(GuiMenu *, GuiMenuOption *);
    /* 0x088 */ void (*uvGuiDrawPanelOrTextLists)(void *);
    /* 0x08C */ s32 (*uvGuiUpdateMenuHitState)(GuiMenu *, u8, s16, s16, s32, f32, f32);
    /* 0x090 */ void (*uvGuiResetMenuOptionPool)(void);
    /* 0x094 */ s16 (*uvGuiAllocatePool170Slot)(void);
    /* 0x098 */ void * (*uvGuiGetTextListSlot)(s16);
    /* 0x09C */ void (*uvGuiCopyTextListText)(void *, u8 *);
    /* 0x0A0 */ void (*uvGuiSetTextListState)(void *, s16);
    /* 0x0A4 */ void (*uvGuiSetTextListBounds)(void *, s16, s16, s16, s16);
    /* 0x0A8 */ void (*uvGuiAppendCompactTextRow)(void *, s32);
    /* 0x0AC */ void (*uvGuiDrawTextList)(GuiDrawTextList *);
    /* 0x0B0 */ s32 (*uvGuiUpdateTextListHitState)(GuiDrawTextList *, u8, s16, s16, s32, f32, f32);
    /* 0x0B4 */ void (*uvGuiResetScalarWidgetPool)(void);
    /* 0x0B8 */ s16 (*uvGuiAllocatePool48Slot)(void);
    /* 0x0BC */ void (*uvGuiClearUpperTextSlotState)(short);
    /* 0x0C0 */ void * (*uvGuiGetUpperTextSlot)(s16);
    /* 0x0C4 */ void (*uvGuiCopyUpperTextText)(void *, u8 *);
    /* 0x0C8 */ void (*uvGuiSetUpperTextBounds)(void *, s16, s16, s16, s16);
    /* 0x0CC */ void (*uvGuiDrawScalarWidget)(Inner28 *);
    /* 0x0D0 */ void (*uvGuiSetWord40)(void *, s32);
    /* 0x0D4 */ void (*uvGuiConfigureScalarWidgetSource)(Inner28 *, f32, f32, f32, s32 *);
    /* 0x0D8 */ void (*uvGuiSetShort20)(void *, s16);
    /* 0x0DC */ void (*uvGuiUpdateScalarWidget)(Inner28 *, u8, f32);
    /* 0x0E0 */ void (*uvGuiSetPool48Active)(GuiPoolSlot48 *, s16);
    /* 0x0E4 */ void (*uvGuiSetWord44)(void *, s32);
    /* 0x0E8 */ void (*uvGuiResetValueWidgetPool)(void);
    /* 0x0EC */ s16 (*uvGuiAllocatePool90Slot)(void);
    /* 0x0F0 */ void (*uvGuiClearValueWidgetSlotState)(s32);
    /* 0x0F4 */ void * (*uvGuiGetValueWidgetSlot)(s16);
    /* 0x0F8 */ void (*uvGuiSetValueWidgetBounds)(void *, s16, s16, s16, s16);
    /* 0x0FC */ void (*uvGuiSetValueWidgetLabels)(Inner30 *, u8 *, u8 *);
    /* 0x100 */ void (*uvGuiConfigureValueWidget)(void *, s32, f32, f32, f32, f32 *);
    /* 0x104 */ void (*uvGuiSetWord8C)(void *, s32);
    /* 0x108 */ void (*uvGuiUpdateGraphWidget)(Inner30 *, u8, f32);
    /* 0x10C */ void (*uvGuiDrawGraphWidget)(Inner30 *);
    /* 0x110 */ void (*uvGuiSetValueWidgetState)(void *, s16);
    /* 0x114 */ void (*uvGuiSetField62Props)(GuiField62Target *, ...);
    /* 0x118 */ void (*uvGuiResetVectorWidgetPool)(void);
    /* 0x11C */ s16 (*uvGuiAllocatePool4CSlot)(void);
    /* 0x120 */ void (*uvGuiClearLowerTextSlotState)(s32);
    /* 0x124 */ void * (*uvGuiGetLowerTextSlot)(s16);
    /* 0x128 */ void (*uvGuiCopyLowerTextText)(void *, u8 *);
    /* 0x12C */ void (*uvGuiSetLowerTextBounds)(void *, s16, s16, s16, s16);
    /* 0x130 */ void (*uvGuiDrawVectorWidget)(Inner2C *);
    /* 0x134 */ void (*uvGuiSetWord48)(void *, s32);
    /* 0x138 */ void (*uvGuiConfigureVectorSource)(GuiVectorState *, f32, f32, GuiVector3 *, GuiVector3 *);
    /* 0x13C */ void (*uvGuiSetAlternateShort20)(void *, s16);
    /* 0x140 */ void (*uvGuiUpdateVectorWidget)(Inner2C *, u8, f32);
    /* 0x144 */ void (*uvGuiSetMode)(void *, s16);
}; /* accessed extent = 0x148 */

#line 91 "src/modules/uvgui_rom.c"
#line 91 "src/modules/uvgui_rom.c"
/* Register the allocation base, bind all 82 export slots and load eight provider modules.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void __entrypoint_func_uvgui_rom_400000(UvGui_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvGuiDrawVectorWidget = uvGuiDrawVectorWidget;
    exports->uvGuiSetWord48 = uvGuiSetWord48;
    exports->uvGuiConfigureVectorSource = uvGuiConfigureVectorSource;
    exports->uvGuiSetAlternateShort20 = uvGuiSetAlternateShort20;
    exports->uvGuiResetStateAndPools = uvGuiResetStateAndPools;
    exports->uvGuiAppendChildRow = uvGuiAppendChildRow;
    exports->uvGuiDrawMenusAndCursor = uvGuiDrawMenusAndCursor;
    exports->uvGuiDrawShadedInsetRectangle = uvGuiDrawShadedInsetRectangle;
    exports->uvGuiDrawCenteredText = uvGuiDrawCenteredText;
    exports->uvGuiDrawFlashingCursor = uvGuiDrawFlashingCursor;
    exports->uvGuiSetChildContainerBounds = uvGuiSetChildContainerBounds;
    exports->uvGuiUpdateInputAndMenuHitStates = uvGuiUpdateInputAndMenuHitStates;
    exports->uvGuiSetInputWordProperty = uvGuiSetInputWordProperty;
    exports->uvGuiSetTextListState = uvGuiSetTextListState;
    exports->uvGuiSetTextListBounds = uvGuiSetTextListBounds;
    exports->uvGuiAppendCompactTextRow = uvGuiAppendCompactTextRow;
    exports->uvGuiDrawTextList = uvGuiDrawTextList;
    exports->uvGuiUpdateVectorWidget = uvGuiUpdateVectorWidget;
    exports->uvGuiUpdateTextListHitState = uvGuiUpdateTextListHitState;
    exports->uvGuiSetMode = uvGuiSetMode;
    exports->uvGuiResetScalarWidgetPool = uvGuiResetScalarWidgetPool;
    exports->uvGuiAllocatePool48Slot = uvGuiAllocatePool48Slot;
    exports->uvGuiClearUpperTextSlotState = uvGuiClearUpperTextSlotState;
    exports->uvGuiGetUpperTextSlot = uvGuiGetUpperTextSlot;
    exports->uvGuiCopyUpperTextText = uvGuiCopyUpperTextText;
    exports->uvGuiLoadDisplayDataAndPalette = uvGuiLoadDisplayDataAndPalette;
    exports->uvGuiSetByte8A = uvGuiSetByte8A;
    exports->uvGuiSetPositionAndCurrentScalars = uvGuiSetPositionAndCurrentScalars;
    exports->uvGuiSetSharedShort = uvGuiSetSharedShort;
    exports->uvGuiSetUpperTextBounds = uvGuiSetUpperTextBounds;
    exports->uvGuiLayoutMenuOptionRows = uvGuiLayoutMenuOptionRows;
    exports->uvGuiDrawScalarWidget = uvGuiDrawScalarWidget;
    exports->uvGuiResetMenuItemPool = uvGuiResetMenuItemPool;
    exports->uvGuiSetWord40 = uvGuiSetWord40;
    exports->uvGuiAllocatePool34Slot = uvGuiAllocatePool34Slot;
    exports->uvGuiConfigureScalarWidgetSource = uvGuiConfigureScalarWidgetSource;
    exports->uvGuiGetCompactTextSlot = uvGuiGetCompactTextSlot;
    exports->uvGuiSetShort20 = uvGuiSetShort20;
    exports->uvGuiCopyCompactTextUppercaseSpan = uvGuiCopyCompactTextUppercaseSpan;
    exports->uvGuiUpdateScalarWidget = uvGuiUpdateScalarWidget;
    exports->uvGuiSetCompactTextState = uvGuiSetCompactTextState;
    exports->uvGuiSetPool48Active = uvGuiSetPool48Active;
    exports->uvGuiSetWord44 = uvGuiSetWord44;
    exports->uvGuiResetValueWidgetPool = uvGuiResetValueWidgetPool;
    exports->uvGuiAllocatePool90Slot = uvGuiAllocatePool90Slot;
    exports->uvGuiModuleCleanup = uvGuiModuleCleanup;
    exports->uvGuiSetCompactTextBounds = uvGuiSetCompactTextBounds;
    exports->uvGuiDrawMenuItemAndAttachments = uvGuiDrawMenuItemAndAttachments;
    exports->uvGuiUpdateMenuItemHitState = uvGuiUpdateMenuItemHitState;
    exports->uvGuiSetPropertyWords = uvGuiSetPropertyWords;
    exports->uvGuiAttachCenteredUpperChild = uvGuiAttachCenteredUpperChild;
    exports->uvGuiClearValueWidgetSlotState = uvGuiClearValueWidgetSlotState;
    exports->uvGuiAttachCenteredLowerChild = uvGuiAttachCenteredLowerChild;
    exports->uvGuiGetValueWidgetSlot = uvGuiGetValueWidgetSlot;
    exports->uvGuiAttachValueWidgetBesideItem = uvGuiAttachValueWidgetBesideItem;
    exports->uvGuiSetValueWidgetBounds = uvGuiSetValueWidgetBounds;
    exports->uvGuiResetMenuPool = uvGuiResetMenuPool;
    exports->uvGuiSetValueWidgetLabels = uvGuiSetValueWidgetLabels;
    exports->uvGuiAllocatePool5CSlot = uvGuiAllocatePool5CSlot;
    exports->uvGuiConfigureValueWidget = uvGuiConfigureValueWidget;
    exports->uvGuiGetChildGroupSlot = uvGuiGetChildGroupSlot;
    exports->uvGuiSetWord8C = uvGuiSetWord8C;
    exports->uvGuiUpdateGraphWidget = uvGuiUpdateGraphWidget;
    exports->uvGuiDrawGraphWidget = uvGuiDrawGraphWidget;
    exports->uvGuiSetValueWidgetState = uvGuiSetValueWidgetState;
    exports->uvGuiSetField62Props = uvGuiSetField62Props;
    exports->uvGuiCopyChildGroupText = uvGuiCopyChildGroupText;
    exports->uvGuiSetChildGroupState = uvGuiSetChildGroupState;
    exports->uvGuiSetChildGroupBounds = uvGuiSetChildGroupBounds;
    exports->uvGuiAppendMenuOption = uvGuiAppendMenuOption;
    exports->uvGuiResetVectorWidgetPool = uvGuiResetVectorWidgetPool;
    exports->uvGuiDrawPanelOrTextLists = uvGuiDrawPanelOrTextLists;
    exports->uvGuiAllocatePool4CSlot = uvGuiAllocatePool4CSlot;
    exports->uvGuiUpdateMenuHitState = uvGuiUpdateMenuHitState;
    exports->uvGuiClearLowerTextSlotState = uvGuiClearLowerTextSlotState;
    exports->uvGuiResetMenuOptionPool = uvGuiResetMenuOptionPool;
    exports->uvGuiGetLowerTextSlot = uvGuiGetLowerTextSlot;
    exports->uvGuiAllocatePool170Slot = uvGuiAllocatePool170Slot;
    exports->uvGuiCopyLowerTextText = uvGuiCopyLowerTextText;
    exports->uvGuiGetTextListSlot = uvGuiGetTextListSlot;
    exports->uvGuiSetLowerTextBounds = uvGuiSetLowerTextBounds;
    exports->uvGuiCopyTextListText = uvGuiCopyTextListText;
#ifdef __sgi
#line 1
#endif
    sUvFMtxExports = uvLoadModule('FMTX');
    sUvFontExports = uvLoadModule('FONT');
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvGfxStateExports = uvLoadModule('STAT');
    sUvDGeomExports = uvLoadModule('DGEO');
    sUvGrphExports = uvLoadModule('grph');
    sUvStringExports = uvLoadModule('STRG');
    sUvContExports = uvLoadModule('CONT');
}
#line 92 "src/modules/uvgui_rom.c"

#line 89 "src/modules/uvgui_rom.c"
/* Unload the eight original GUI dependencies in their original order. */
void uvGuiModuleCleanup(void) {
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x464F4E54);
    uvUnloadModule(0x474D4752);
    uvUnloadModule(0x53544154);
    uvUnloadModule(0x4447454F);
    uvUnloadModule(0x67727068);
    uvUnloadModule(0x434F4E54);
    uvUnloadModule(0x53545247);
}
#line 99 "src/modules/uvgui_rom.c"

#line 100 "src/modules/uvgui_rom.c"
/* Reset six widget pools, menu slots, display bounds and observed input defaults.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiResetStateAndPools(uvGui *gui) {
    s32 i;

    uvGuiResetMenuItemPool();
    uvGuiResetMenuOptionPool();
    uvGuiResetMenuPool();
    uvGuiResetValueWidgetPool();
    uvGuiResetScalarWidgetPool();
    uvGuiResetVectorWidgetPool();
    gui->activeMenuCount = 0;

    // clang-format off
    for (i = 0; i < 20; i++) { gui->menus[i] = NULL; }
    // clang-format on

    gui->unk54 = 0;
    gui->unk56 = sUvGfxMgrExports->uvGetScreenWidth() - 1;
    gui->unk58 = 0;
    gui->unk5A = sUvGfxMgrExports->uvGetScreenHeight() - 1;
    gui->cursorX = (s16) (sUvGfxMgrExports->uvGetScreenWidth() / 2);
    gui->cursorY = (s16) (sUvGfxMgrExports->uvGetScreenHeight() / 2);
    gui->unk68 = gui->cursorX;
    gui->unk6C = gui->cursorY;
    gui->unk74 = 0x8000;
    gui->unk78 = 0x4000;
    gui->unk7C = 0;
    gui->unk80 = 1;
    gui->unk5C = 0;
    gui->fontId = -1;
    gui->unk8A = 1;
    gui->unk8B = 1;
    gui->unk60 = 0.0f;
    gui->unk64 = 0.0f;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (!sUvContExports->uvControllerPlugged(i)) {
            break;
        }
    }
    gui->contNo = i - 1;
}
#line 101 "src/modules/uvgui_rom.c"

#line 102 "src/modules/uvgui_rom.c"
/* Insert a child in the first of twenty free slots, update the count and
 * assign its twelve-pixel row bounds. Preserve original full-list behavior. */
void uvGuiAppendChildRow(s32 *group, s32 child)
{
  s16 rowY;
  s32 *slot;
  s32 i;
  u8 *groupBytes;
  slot = group;
 i = 0; loop: if ((*slot) != 0) {
    i += 1;
    slot += 1;
    if (i != 0x14)
    {
      goto loop;
    }
  }

  if (i != 0x14)
  {
    *slot = child;
    rowY = ((*((s16 *) (((u8 *) group) + 0x5A))) - (i * 0xC)) - 0xC;
    groupBytes = (u8 *) group;
    *((s16 *) (groupBytes + 0x50)) = (*((s16 *) (((u8 *) group) + 0x50))) + 1;
    uvGuiSetChildGroupBounds(child, *((s16 *) (((u8 *) group) + 0x54)), *((s16 *) (((u8 *) group) + 0x56)), ((*((s16 *) (((u8 *) group) + 0x5A))) - (i * 0xC)) - 0xC, rowY + 0xC);
  }
}
#line 127 "src/modules/uvgui_rom.c"

#line 128 "src/modules/uvgui_rom.c"
/* Set viewport/projection/state, draw each listed menu, emit font commands and optional cursor.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiDrawMenusAndCursor(uvGui *arg0) {
    s32 i;
    Mtx4F sp7C;
    Mtx4F sp3C;

    sUvGfxMgrExports->uvGfxAppendViewport(0, sUvGfxMgrExports->uvGetScreenWidth() - 1, 0,
                                                 sUvGfxMgrExports->uvGetScreenHeight() - 1);
    sUvFMtxExports->uvMat4SetOrtho(&sp7C, -0.5f, (f32) sUvGfxMgrExports->uvGetScreenWidth() + 0.5f,
                                   -0.5f, (f32) sUvGfxMgrExports->uvGetScreenHeight() + 0.5f);
    sUvFMtxExports->uvGfxMtxProjPushF(&sp7C);
    sUvFMtxExports->uvMat4SetIdentity(&sp3C);
    sUvFMtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&sp3C);
    sUvGfxStateExports->uvGfxStatePush();
    sUvGfxStateExports->uvGfxSetFogParameters(0.0f, 0.0f);
    sUvGfxStateExports->uvGfxStateSetFlags(0x04800FFF);
    sUvGfxStateExports->uvGfxClearCurrentStateBits(0x9A640000);
    if (arg0->fontId >= 0) {
        sUvFontExports->uvSetFont(arg0->fontId);
    }

    for (i = 0; i < arg0->activeMenuCount; i++) {
        uvGuiDrawPanelOrTextLists(arg0->menus[i]);
    }
    sUvFontExports->uvFontGenDList();
    if (((u8) arg0->unk8A != 0) && (D_uvgui_rom_00406F00 == 0)) {
        uvGuiDrawFlashingCursor(arg0->cursorX, arg0->cursorY);
    }
    sUvGfxStateExports->uvGfxStatePop();
}
#line 129 "src/modules/uvgui_rom.c"

#line 130 "src/modules/uvgui_rom.c"
/* Emit the inset rectangle and surrounding bands with successive RGB adjustments.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiDrawShadedInsetRectangle(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 r, u8 g, u8 b, u8 a) {
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(arg0 + arg4, arg2 + arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1 - arg4, arg2 + arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1 - arg4, arg3 - arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0 + arg4, arg3 - arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtxEndPoly();
    if (r >= 0x15) {
        r = (r - 0x14);
    }
    if (g >= 0x15) {
        g = (g - 0x14);
    }
    if (b >= 0x15) {
        b = (b - 0x14);
    }
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(arg1, arg3, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0, arg3, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0 + arg4, arg3 - arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1 - arg4, arg3 - arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtxEndPoly();
    if (r >= 0x15) {
        r = (r - 0x14);
    }
    if (g >= 0x15) {
        g = (g - 0x14);
    }
    if (b >= 0x15) {
        b = (b - 0x14);
    }
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(arg0, arg2, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0 + arg4, arg2 + arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0 + arg4, arg3 - arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0, arg3, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtxEndPoly();
    if (r >= 0x15) {
        r = (r - 0x14);
    }
    if (g >= 0x15) {
        g = (g - 0x14);
    }
    if (b >= 0x15) {
        b = (b - 0x14);
    }
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(arg0, arg2, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1, arg2, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1 - arg4, arg2 + arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg0 + arg4, arg2 + arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtxEndPoly();
    if (r >= 0x15) {
        r = (r - 0x14);
    }
    if (g >= 0x15) {
        g = (g - 0x14);
    }
    if (b >= 0x15) {
        b = (b - 0x14);
    }
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(arg1, arg2, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1, arg3, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1 - arg4, arg3 - arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtx(arg1 - arg4, arg2 + arg4, 0, 0, 0, r, g, b, a);
    sUvDGeomExports->uvVtxEndPoly();
}
#line 131 "src/modules/uvgui_rom.c"

#line 132 "src/modules/uvgui_rom.c"
/* Measure the forwarded text pointer and print it at the computed centered offsets.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_UNKNOWN: FontPrintStr can write str[49] when measured length >= 51.
 * Exported strings and accepted panel/list callers need NUL, writable extent
 * and alias/lifetime evidence; do not infer safety from a field width or add defaults. */
void uvGuiDrawCenteredText(s16 x0, s16 x1, s16 y0, s16 y1, void *str, u8 r, u8 g, u8 b, u8 a) {
    s16 pad[2];
    s16 width;
    s16 pad20;
    s16 sp1D;
    s16 y;
    s32 height;

    width = sUvFontExports->uvFontWidth(str);
    height = (s16) sUvFontExports->uvFontHeight();
    y = (y0 + ((s32) ((s16) (y1 - y0) - height) / 2)) - 1;
    sUvFontExports->uvFontColor(r, g, b, a);
    sUvFontExports->uvFontPrintStr((s16) ((x0 + ((s32) ((s16) (x1 - x0) - width) / 2)) - 1), y, str);
}
#line 133 "src/modules/uvgui_rom.c"

#line 134 "src/modules/uvgui_rom.c"
/* Toggle the shared color phase and emit two cursor triangles.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiDrawFlashingCursor(s16 x, s16 y) {
    u8 r;
    u8 g;
    u8 b;
    static s32 sCursorFlash = 0;

    sCursorFlash = !sCursorFlash;
    if (sCursorFlash) {
        b = 255;
        g = 255;
        r = 255;
    } else {
        b = 0;
        g = 0;
        r = 0;
    }
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(x, y, 0, 0, 0, r, g, b, 127);
    sUvDGeomExports->uvVtx(x + 6, y - 13, 0, 0, 0, r, g, b, 127);
    sUvDGeomExports->uvVtx(x + 6, y - 6, 0, 0, 0, r, g, b, 127);
    sUvDGeomExports->uvVtxEndPoly();
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(x, y, 0, 0, 0, r, g, b, 127);
    sUvDGeomExports->uvVtx(x + 6, y - 6, 0, 0, 0, r, g, b, 127);
    sUvDGeomExports->uvVtx(x + 13, y - 6, 0, 0, 0, r, g, b, 127);
    sUvDGeomExports->uvVtxEndPoly();
}
#line 135 "src/modules/uvgui_rom.c"

#line 136 "src/modules/uvgui_rom.c"
/* Store the four signed ChildContainer rectangle edges in original order.
 * Preserve conversion to signed 16-bit coordinates and leave validation to callers. */
void uvGuiSetChildContainerBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom) {
    (*(s16 *)((u8 *)widget + 0x54)) = left;
    (*(s16 *)((u8 *)widget + 0x56)) = right;
    (*(s16 *)((u8 *)widget + 0x58)) = top;
    (*(s16 *)((u8 *)widget + 0x5A)) = bottom;
}
#line 142 "src/modules/uvgui_rom.c"

#line 143 "src/modules/uvgui_rom.c"
/* Read controller words/scalars, update bounded cursor values and query every listed menu.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
s32 uvGuiUpdateInputAndMenuHitStates(uvGui *arg0) {
    f32 temp_fv0_2;
    s32 i;
    s32 v0;

    if ((u8) arg0->unk8B != 0) {
        uvGuiLayoutMenuOptionRows(arg0);
        arg0->unk8B = 0U;
    }
    arg0->unk5C = 0;
    if (sUvContExports->uvControllerButtonPress((u8) arg0->contNo, arg0->unk74) != 0) {
        arg0->unk5C = 1;
    }
    if (sUvContExports->uvControllerButtonPress((u8) arg0->contNo, arg0->unk78) != 0) {
        arg0->unk5C = 2;
    }
    arg0->unk60 = sUvContExports->uvControllerGetStick((u8) arg0->contNo, arg0->unk7C);
    arg0->unk64 = sUvContExports->uvControllerGetStick((u8) arg0->contNo, arg0->unk80);
    if (arg0->unk60 >= 0.0f) {
        v0 = 1;
    } else {
        v0 = -1;
    }
    arg0->unk60 = arg0->unk60 * (v0 * arg0->unk60);
    if (arg0->unk64 >= 0.0f) {
        v0 = 1;
    } else {
        v0 = -1;
    }
    arg0->unk64 = arg0->unk64 * (v0 * arg0->unk64);
    if (sUvContExports->uvControllerButtonPress((u8) arg0->contNo, L_JPAD) != 0) {
        arg0->unk60 -= 0.25f;
    }
    if (sUvContExports->uvControllerButtonPress((u8) arg0->contNo, R_JPAD) != 0) {
        arg0->unk60 += 0.25f;
    }
    if (D_uvgui_rom_00406F00 == 0) {
        temp_fv0_2 = sUvGfxMgrExports->uvGfxMgrGetScalarOverrideOrCurrent();
        arg0->unk68 = arg0->unk68 + (240.0f * arg0->unk60 * temp_fv0_2);
        arg0->unk6C = arg0->unk6C + (240.0f * arg0->unk64 * temp_fv0_2);
        if (arg0->unk68 < (arg0->unk54 + 1)) {
            arg0->unk68 = (arg0->unk54 + 1);
        } else {
            if ((arg0->unk56 - 1) < arg0->unk68) {
                arg0->unk68 = (arg0->unk56 - 1);
            }
        }
        if (arg0->unk6C < (arg0->unk58 + 1)) {
            arg0->unk6C = (arg0->unk58 + 1);
        } else {
            if ((arg0->unk5A - 1) < arg0->unk6C) {
                arg0->unk6C = (arg0->unk5A - 1);
            }
        }
        arg0->cursorX = arg0->unk68;
        arg0->cursorY = arg0->unk6C;
    }

    for (i = 0; i < arg0->activeMenuCount; i++) {
        uvGuiUpdateMenuHitState(arg0->menus[i], arg0->contNo, arg0->cursorX, arg0->cursorY, arg0->unk5C,
                                arg0->unk60, arg0->unk64);
    }
    return 1;
}
#line 144 "src/modules/uvgui_rom.c"

#line 145 "src/modules/uvgui_rom.c"
/* Assign the selected input mask, controller or stick-selector word; preserve unsupported no-write.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiSetInputWordProperty(uvGui *arg0, s16 arg1, s32 arg2) {
    switch (arg1) {
        case 1:
            arg0->unk74 = arg2;
            break;
        case 2:
            // RE_UNKNOWN: inherited compilation workaround; historical source unresolved.
            arg1++;
            arg1--;

            arg0->unk78 = arg2;
            break;
        case 17:
            arg0->unk7C = arg2;
            break;
        case 18:
            arg0->unk80 = arg2;
            break;
        case 16:
            arg0->contNo = arg2;
            break;
        default:
            break;
    }
}
#line 146 "src/modules/uvgui_rom.c"

#line 147 "src/modules/uvgui_rom.c"
/* Store display-data and palette IDs, load UVDS data unless its ID is -1,
 * load the palette through the original export and mark byte 0x8B ready.
 * Preserve resource lifetime and original loader order. */
void uvGuiLoadDisplayDataAndPalette(void *widget, s16 displayData, s16 palette) {
    *(s16 *)((u8 *)widget + 0x86) = displayData;
    *(s16 *)((u8 *)widget + 0x88) = palette;
    if (displayData != -1) {
        uvLoadFile(0x55564453, displayData);
    }
    (*(void (**)(s32))((u8 *)D_uvgui_rom_0040721C + 0x4))(palette); // load palette
    *(u8 *)((u8 *)widget + 0x8B) = 1;
}
#line 156 "src/modules/uvgui_rom.c"

#line 157 "src/modules/uvgui_rom.c"
/* Store the GUI element byte at offset 0x8A. */
void uvGuiSetByte8A(void *element, u8 value) {
    *(u8 *)((u8 *)element + 0x8A) = value;
}
#line 160 "src/modules/uvgui_rom.c"

#line 161 "src/modules/uvgui_rom.c"
/* Store signed coordinates at 0x70/0x72 and copy their floating values
 * to 0x68/0x6C. Preserve readback and conversion order. */
void uvGuiSetPositionAndCurrentScalars(void *widget, s16 first, s16 second) {
    (*(s16 *)((u8 *)widget + 0x70)) = first;
    (*(s16 *)((u8 *)widget + 0x72)) = second;
    (*(f32 *)((u8 *)widget + 0x68)) = (f32) (*(s16 *)((u8 *)widget + 0x70));
    (*(f32 *)((u8 *)widget + 0x6C)) = (f32) (*(s16 *)((u8 *)widget + 0x72));
}
#line 167 "src/modules/uvgui_rom.c"

#line 168 "src/modules/uvgui_rom.c"
/* Store the original shared GUI short value. */
void uvGuiSetSharedShort(s16 value) {
    D_uvgui_rom_00406F00 = value;
}
#line 171 "src/modules/uvgui_rom.c"

#line 172 "src/modules/uvgui_rom.c"
/* Measure option/item text and assign row bounds using repeated native dimension queries.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiLayoutMenuOptionRows(uvGui *arg0) {
    GuiMenu *menu;
    s16 var_s2;
    s16 two;
    s32 temp_s3;
    s32 i;
    s32 j;
    s32 k;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 sp8C;
    s32 var_fp;
    s32 sp5C;
    s32 temp;
    s32 temp_t2;
    GuiMenuOption *menuOption;
    GuiMenuItem *menuItem;

    sUvFontExports->uvSetFont(arg0->fontId);
    for (i = 0; i < arg0->activeMenuCount; i++) {
        menu = arg0->menus[i];
        sp8C = menu->x0;
        for (j = 0; j < menu->unk58; j++) {
            var_fp = 0;
            menuOption = menu->options[j];
            menuOption->unk16C = sUvFontExports->uvFontWidth(menuOption->name);
            menuOption->unk20 = (s16) (sp8C - 2);
            menuOption->unk22 = (s16) (menuOption->unk20 + menuOption->unk16C + 8);
            sp8C = menuOption->unk22 + 3;
            uvGuiSetTextListBounds(menuOption, menuOption->unk20, menuOption->unk22, menuOption->unk24,
                                    (s32) menuOption->unk26);

            two = 2;
            for (k = 0; k < menuOption->activeMenuItems; k++) {
                menuItem = menuOption->items[k];
                temp_v0_2 = sUvFontExports->uvFontWidth(menuItem->name);
                if (var_fp < temp_v0_2) {
                    var_fp = temp_v0_2;
                }
            }

            sp5C = var_fp / two;
            for (k = 0; k < menuOption->activeMenuItems; k++) {
                menuItem = menuOption->items[k];

                temp_v0_2 = ((menu->x1 - menu->x0) + 1); // t1
                temp_t2 = ((menu->x1 + menu->x0) / 2);
                temp_t8 = ((menuOption->unk20 + menuOption->unk22) / 2);

                temp = ((var_fp * ((temp_t8 - temp_t2) / (f32) temp_v0_2)) / 2);
                menuItem->unkE = (((temp_t8 - sp5C) - temp) - 2);
                menuItem->unk10 = (menuItem->unkE + var_fp + 4);
                uvGuiSetCompactTextBounds(menuItem, menuItem->unkE, menuItem->unk10, menuItem->unk12,
                                        menuItem->unk14);
                if (menuItem->unk30 != 0) {
                    if (menuOption->unk22 < (sUvGfxMgrExports->uvGetScreenWidth() / 2)) {
                        var_s2 = (arg0->unk56 - menuItem->unk10) - 0x14;
                        if (var_s2 < 0x28) {
                            var_s2 = 0x28;
                        } else if (var_s2 >= 0xA1) {
                            var_s2 = 0xA0;
                        }
                        temp_s3 = sUvGfxMgrExports->uvGetScreenHeight();
                        uvGuiSetValueWidgetBounds(
                            menuItem->unk30, (s16) (menuItem->unk10 + 0xA),
                            (s16) (menuItem->unk10 + var_s2 + 0xA), (s16) ((temp_s3 / 2) - (var_s2 / 2)),
                            (sUvGfxMgrExports->uvGetScreenHeight() / 2) + (var_s2 / 2));
                    } else {
                        var_s2 = (menuItem->unkE - arg0->unk54) - 0x14;
                        if (var_s2 < 0x28) {
                            var_s2 = 0x28;
                        } else if (var_s2 >= 0xA1) {
                            var_s2 = 0xA0;
                        }

                        temp_s3 = sUvGfxMgrExports->uvGetScreenHeight();
                        uvGuiSetValueWidgetBounds(
                            menuItem->unk30, (s16) ((menuItem->unkE - var_s2) - 0xA),
                            (s16) (menuItem->unkE - 0xA), (s16) ((temp_s3 / 2) - (var_s2 / 2)),
                            (sUvGfxMgrExports->uvGetScreenHeight() / 2) + (var_s2 / 2));
                    }
                }
            }
        }
    }
}
#line 173 "src/modules/uvgui_rom.c"

#line 174 "src/modules/uvgui_rom.c"
/* Reset the observed state, bounds, callback and attachment fields in 120 item slots.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiResetMenuItemPool(void) {
    s32 i;

    for (i = 0; i < 120; i++) {
        sGuiMenuItems[i].unkC = 0;
        sGuiMenuItems[i].unkE = 0;
        sGuiMenuItems[i].unk10 = 0x41;
        sGuiMenuItems[i].unk12 = 0;
        sGuiMenuItems[i].unk14 = 0xC;
        sGuiMenuItems[i].unk1C = 0;
        sGuiMenuItems[i].unk20 = 0;
        sGuiMenuItems[i].unk24 = 0;
        sGuiMenuItems[i].unk28 = 0;
        sGuiMenuItems[i].unk2C = 0;
        sGuiMenuItems[i].unk30 = 0;
    }
}
#line 175 "src/modules/uvgui_rom.c"

#line 170 "src/modules/uvgui_rom.c"
/* Scan 120 slots at stride 0x34 for the first zero active halfword, set only
 * that halfword to one and return its index. The inherited full-pool path
 * still writes slot 120, beyond the scanned range. RE_UNKNOWN: callers must
 * establish spare capacity, backing storage and reuse initialization; no
 * exhaustion repair is made here. */
#line 174 "src/modules/uvgui_rom.c"
s16 uvGuiAllocatePool34Slot(void) {
    GuiPoolSlot34 *slot;
    s32 index;

    for (index = 0, slot = (GuiPoolSlot34 *) &D_uvgui_rom_00407238; index != 120; index++, slot++) {
        if (slot->active == 0) {
            break;
        }
    }
    slot->active = 1;
    return (s16) index;
}
#line 186 "src/modules/uvgui_rom.c"
#line 171 "src/modules/uvgui_rom.c"

#line 172 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x34-byte CompactText pool.
 * RE_UNKNOWN: valid index/allocation/lifetime domains need pool writers and callers; no local guard. */
void *uvGuiGetCompactTextSlot(s16 index) {
    return (index * 0x34) + &D_uvgui_rom_00407238;
}
#line 175 "src/modules/uvgui_rom.c"

#line 176 "src/modules/uvgui_rom.c"
/* Copy exactly twelve bytes through the original byte transform, then copy
 * the local result to the raw-word destination through _uvMediaCopy.
 * RE_ORIGINAL_QUIRK: subtract 32 from every byte >= 97, including values above z.
 * Preserve the current destination ABI and comma-expression loop end.
 * RE_UNKNOWN: caller source/destination extents, byte domains and terminator
 * conventions. Inspect caller storage/data before generalizing this into
 * a string-copy routine; this helper neither scans for NUL nor checks addresses. */
void uvGuiCopyCompactTextUppercaseSpan(s32 destinationAddress, u8 *source)
{
  u8 uppercaseBytes[0xC];
  u8 *writeCursor;
  u8 *end;
  u8 *readCursor;
  u8 value;
  writeCursor = uppercaseBytes;
  end = &uppercaseBytes[0, 0xC];
  readCursor = source;
  do
  {
    value = *readCursor;
    if (((s32) value) >= 0x61)
    {
      *writeCursor = value - 0x20;
    }
    else
    {
      *writeCursor = value;
    }
    writeCursor += 1;
    readCursor += 1;
  }
  while (writeCursor != end);
  _uvMediaCopy((void *) destinationAddress, uppercaseBytes, 0xC);
}
#line 203 "src/modules/uvgui_rom.c"

#line 204 "src/modules/uvgui_rom.c"
/* Store the original signed state value at CompactText object offset 0xC.
 * State meanings remain with the corresponding update and drawing routines. */
void uvGuiSetCompactTextState(void *widget, s16 state) {
    *(s16 *)((u8 *)widget + 0xC) = state;
}
#line 207 "src/modules/uvgui_rom.c"

#line 208 "src/modules/uvgui_rom.c"
/* Store the compact-text rectangle, then its signed vertical and horizontal
 * extents in original order. Coordinate range remains caller-owned. */
void uvGuiSetCompactTextBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom) {
    (*(s16 *)((u8 *)widget + 0xE)) = left;
    (*(s16 *)((u8 *)widget + 0x10)) = right;
    (*(s16 *)((u8 *)widget + 0x12)) = top;
    (*(s16 *)((u8 *)widget + 0x14)) = bottom;
    (*(s16 *)((u8 *)widget + 0x18)) = (s16) ((*(s16 *)((u8 *)widget + 0x14)) - (*(s16 *)((u8 *)widget + 0x12)));
    (*(s16 *)((u8 *)widget + 0x16)) = (s16) ((*(s16 *)((u8 *)widget + 0x10)) - (*(s16 *)((u8 *)widget + 0xE)));
}
#line 216 "src/modules/uvgui_rom.c"

#line 217 "src/modules/uvgui_rom.c"
/* Draw the item text/border and attached widgets, preserving callback-dependent state reloads.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_UNKNOWN: The 12-byte name view is forwarded to the font printer, whose
 * long-string path writes byte 49. Original fixed-width copy does not add a
 * terminator; actual string extent/termination, aliases and caller reachability need proof. */
void uvGuiDrawMenuItemAndAttachments(GuiMenuItem *arg0) {
    u8 var_t1;
    u8 var_t0;
    u8 var_v1;
    u8 var_t2;
    s16 temp_v0;
    int s;
    Inner28 *v1;

    temp_v0 = arg0->unkC;
    switch (temp_v0) {
        case 1:
            var_v1 = 0;
            var_t0 = 0;
            var_t1 = 0;
            var_t2 = 0x50;
            break;
        case 2:
            var_v1 = 0xFF;
            var_t0 = 0xFF;
            var_t1 = 0xFF;
            var_t2 = 0xFF;
            break;
        case 3:
            var_v1 = 0;
            var_t0 = 0;
            var_t1 = 0;
            var_t2 = 0xFF;
            break;
        case 4:
            var_v1 = 0;
            var_t0 = 0;
            var_t1 = 0;
            var_t2 = 0x40;
            break;
        default:
            return;
    }

    uvGuiDrawShadedInsetRectangle(arg0->unkE, arg0->unk10, arg0->unk12, arg0->unk14, 2, var_t1, var_t0,
                            var_v1, var_t2);

    temp_v0 = arg0->unkC;
    switch (temp_v0) { /* irregular */
        case 1:
            var_t1 = 0xFF;
            var_t0 = 0xFF;
            var_v1 = 0xFF;
            var_t2 = 0xC8;
            break;
        case 2:
            var_t1 = 0;
            var_t0 = 0;
            var_v1 = 0;
            var_t2 = 0xFF;
            break;
        case 3:
            var_t1 = 0;
            var_t0 = 0xFF;
            var_v1 = 0;
            var_t2 = 0xFF;
            break;
        case 4:
            var_t1 = 0xFF;
            var_t0 = 0;
            var_v1 = 0;
            var_t2 = 0xFF;
            break;
    }
    uvGuiDrawCenteredText(arg0->unkE, arg0->unk10, arg0->unk12, arg0->unk14, arg0->name, var_t1,
                            var_t0, var_v1, var_t2);

    if (arg0->unk28 != NULL) {
        v1 = arg0->unk28;
        if (arg0->unkC == 3) {
            if (v1->unk1E == 1) {
                uvGuiSetPool48Active((GuiPoolSlot48 *)v1, 2);
                uvGuiSetSharedShort(1);
            } else {
                uvGuiSetPool48Active((GuiPoolSlot48 *)v1, 1);
                uvGuiSetSharedShort(0);
            }
        }
        if (arg0->unkC == 2) {
            uvGuiDrawScalarWidget(arg0->unk28);
        }
    }

    if (arg0->unk2C != NULL) {
        Inner2C *v1 = arg0->unk2C;
        if (arg0->unkC == 3) {
            if (v1->unk1E == 1) {
                uvGuiSetMode(v1, 2);
                uvGuiSetSharedShort(1);
            } else {
                uvGuiSetMode(v1, 1);
                uvGuiSetSharedShort(0);
            }
        }
        if (arg0->unkC == 2) {
            uvGuiDrawVectorWidget(arg0->unk2C);
        }
    }

    if (arg0->unk30 != NULL) {
        Inner30 *v1 = arg0->unk30;
        if (arg0->unkC == 3) {
            if (arg0->unk30->unk5E == 1) {
                uvGuiSetValueWidgetState(v1, 2);
                uvGuiSetSharedShort(1);
            } else {
                uvGuiSetValueWidgetState(v1, 1);
                uvGuiSetSharedShort(0);
            }
        }
        if (arg0->unkC == 2) {
            uvGuiDrawGraphWidget(arg0->unk30);
        }
    }
}
#line 218 "src/modules/uvgui_rom.c"

#line 219 "src/modules/uvgui_rom.c"
/* Update attached widgets, test item bounds and dispatch the selected state callback.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
s32 uvGuiUpdateMenuItemHitState(GuiMenuItem *arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4,
                            f32 arg5, f32 arg6) {
    if (arg0->unk28 != NULL) {
        uvGuiUpdateScalarWidget(arg0->unk28, arg1, arg5);
    }
    if (arg0->unk30 != NULL) {
        uvGuiUpdateGraphWidget(arg0->unk30, arg1, arg5);
    }
    if (arg0->unk2C != NULL) {
        uvGuiUpdateVectorWidget(arg0->unk2C, arg1, arg5);
    }
    if (arg2 < arg0->unkE) {
        arg0->unkC = 1;
        return 0;
    }
    if (arg0->unk10 < arg2) {
        arg0->unkC = 1;
        return 0;
    }
    if (arg3 < arg0->unk12) {
        arg0->unkC = 1;
        return 0;
    }
    if (arg0->unk14 < arg3) {
        arg0->unkC = 1;
        return 0;
    }
    if (arg4 & 1) {
        arg0->unkC = 3;
        if (arg0->unk20 != NULL) {
            arg0->unk20(arg0);
        }
    } else if (arg4 & 2) {
        arg0->unkC = 4;
        if (arg0->unk24 != NULL) {
            arg0->unk24(arg0);
        }
    } else {
        arg0->unkC = 2;
        if (arg0->unk1C != NULL) {
            arg0->unk1C(arg0);
        }
    }
    return 1;
}
#line 220 "src/modules/uvgui_rom.c"

#line 221 "src/modules/uvgui_rom.c"
/* Set property two/three/four to word 0x1C/0x20/0x24; ignore other properties. */
void uvGuiSetPropertyWords(void *element, s16 property, s32 value) {
    switch (property) {                                 /* irregular */
    case 2:
        (*(s32 *)((u8 *)element + 0x1C)) = value;
        return;
    case 3:
        (*(s32 *)((u8 *)element + 0x20)) = value;
        return;
    case 4:
        (*(s32 *)((u8 *)element + 0x24)) = value;
        return;
    }
}
#line 234 "src/modules/uvgui_rom.c"

#line 235 "src/modules/uvgui_rom.c"
/* Attach the child in slot 0x28 and place it in the original upper band.
 * Retain both display-width queries and their signed half-width arithmetic;
 * horizontal edges are centered +/-90 and vertical edges are 22 and 48. */
void uvGuiAttachCenteredUpperChild(GuiCenteredAttachments *owner, void *child) {
    s32 currentWidth;
    s32 width;
    owner->first = child;
    width = D_uvgui_rom_00407220->width();
    currentWidth = D_uvgui_rom_00407220->width();
    uvGuiSetUpperTextBounds(child, (s16)(width / 2 - 90), (s16)(currentWidth / 2 + 90), 0x16, 48);
}
#line 236 "src/modules/uvgui_rom.c"

#line 237 "src/modules/uvgui_rom.c"
/* Attach the child in slot 0x2C and place it in the original lower band.
 * Retain both display-width queries and their signed half-width arithmetic;
 * horizontal edges are centered +/-90 and vertical edges are 22 and 82. */
void uvGuiAttachCenteredLowerChild(GuiCenteredAttachments *owner, void *child) {
    s32 currentWidth;
    s32 width;
    owner->second = child;
    width = D_uvgui_rom_00407220->width();
    currentWidth = D_uvgui_rom_00407220->width();
    uvGuiSetLowerTextBounds(child, (s16)(width / 2 - 90), (s16)(currentWidth / 2 + 90), 0x16, 82);
}
#line 238 "src/modules/uvgui_rom.c"

#line 239 "src/modules/uvgui_rom.c"
/* Store the attached value-widget pointer and place its bounds relative to the item/display.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiAttachValueWidgetBesideItem(GuiMenuItem *arg0, Inner30 *arg1) {
    arg0->unk30 = arg1;
    if (arg0->unk10 < (sUvGfxMgrExports->uvGetScreenWidth() / 2)) {
        uvGuiSetValueWidgetBounds(arg1, (arg0->unk10 + 0xA), (arg0->unk10 + 0xAA),
                                ((sUvGfxMgrExports->uvGetScreenHeight() / 2) - 0x50),
                                (sUvGfxMgrExports->uvGetScreenHeight() / 2) + 0x50);
        return;
    }
    if ((sUvGfxMgrExports->uvGetScreenWidth() / 2) < arg0->unkE) {
        uvGuiSetValueWidgetBounds(arg1, (arg0->unkE - 0xAA), (arg0->unkE - 0xA),
                                ((sUvGfxMgrExports->uvGetScreenHeight() / 2) - 0x50),
                                (sUvGfxMgrExports->uvGetScreenHeight() / 2) + 0x50);
        return;
    }
    uvGuiSetValueWidgetBounds(arg1, ((sUvGfxMgrExports->uvGetScreenWidth() / 2) - 0x50),
                            ((sUvGfxMgrExports->uvGetScreenWidth() / 2) + 0x50),
                            ((sUvGfxMgrExports->uvGetScreenHeight() / 2) - 0x50),
                            (sUvGfxMgrExports->uvGetScreenHeight() / 2) + 0x50);
}
#line 240 "src/modules/uvgui_rom.c"

#line 241 "src/modules/uvgui_rom.c"
/* Clear eight menu states, twelve option pointers per menu and selection/count fields.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiResetMenuPool(void) {
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(sGuiMenus); i++) {
        sGuiMenus[i].unk1E = 0;
        for (j = 0; j < MAX_MENU_OPTIONS; j++) {
            sGuiMenus[i].options[j] = NULL;
        }
        sGuiMenus[i].unk58 = 0;
        sGuiMenus[i].unk5A = -1;
    }
}
#line 242 "src/modules/uvgui_rom.c"

#line 243 "src/modules/uvgui_rom.c"
/* Find the first inactive slot in the eight-slot, 0x5C-stride pool and set
 * only its active halfword. Return -1 without a write when all eight are
 * active. RE_UNKNOWN: callers must handle exhaustion and initialize any stale
 * fields before reuse; allocation ownership and release discipline need pool
 * consumers. */
#line 245 "src/modules/uvgui_rom.c"
s16 uvGuiAllocatePool5CSlot(void) {
    GuiPoolSlot5C *slot;
    s32 index;
    for (index = 0, slot = (GuiPoolSlot5C *) &D_uvgui_rom_00408A98; index != 8; index++, slot++) {
        if (slot->active == 0) break;
    }
    if (index == 8) return -1;
    slot->active = 1;
    return (s16) index;
}
#line 255 "src/modules/uvgui_rom.c"
#line 244 "src/modules/uvgui_rom.c"

#line 245 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x5C-byte ChildGroup pool.
 * RE_UNKNOWN: valid index/allocation/lifetime domains need pool writers and callers; no local guard. */
void *uvGuiGetChildGroupSlot(s16 index) {
    return (index * 0x5C) + &D_uvgui_rom_00408A98;
}
#line 248 "src/modules/uvgui_rom.c"

#line 249 "src/modules/uvgui_rom.c"
/* Copy exactly 30 bytes through the original uppercase transform: subtract
 * 32 from every byte >= 97, including values above z. Neither source nor
 * destination is NUL-scanned; callers must supply full fixed-width buffers. */
void uvGuiCopyChildGroupText(void *destination, u8 *source)
{
  u8 buffer[0x1E];
  u8 *end;
  u8 *write;
  u8 *read;
  u8 character;
  write = &buffer[0];
  end = &buffer[0x1E];
  read = source;
  do
  {
    character = *read;
    if (((s32) character) >= 0x61)
    {
      *write = character - 0x20;
    }
    else
    {
      *write = character;
    }
    write += 1;
    read += 1;
  }
  while (write != end);
  _uvMediaCopy(destination, &buffer[0], 0x1E);
}
#line 276 "src/modules/uvgui_rom.c"

#line 277 "src/modules/uvgui_rom.c"
/* Store the original signed state value at ChildGroup object offset 0x1E.
 * State meanings remain with the corresponding update and drawing routines. */
void uvGuiSetChildGroupState(void *widget, s16 state) {
    *(s16 *)((u8 *)widget + 0x1E) = state;
}
#line 280 "src/modules/uvgui_rom.c"

#line 281 "src/modules/uvgui_rom.c"
/* Store the four signed ChildGroup rectangle edges in original order.
 * Preserve conversion to signed 16-bit coordinates and leave validation to callers. */
void uvGuiSetChildGroupBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom) {
    (*(s16 *)((u8 *)widget + 0x20)) = left;
    (*(s16 *)((u8 *)widget + 0x22)) = right;
    (*(s16 *)((u8 *)widget + 0x24)) = top;
    (*(s16 *)((u8 *)widget + 0x26)) = bottom;
}
#line 287 "src/modules/uvgui_rom.c"

#line 288 "src/modules/uvgui_rom.c"
/* Fill the first empty option slot, increment the count and assign its row bounds.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiAppendMenuOption(GuiMenu *menu, GuiMenuOption *menuOption) {
    s16 temp_a1;
    s32 i;
    s16 a3;
    s16 a2;

    for (i = 0; i < 12; i++) {
        if (menu->options[i] == NULL) {
            break;
        }
    }
    if (i == 12) {
        return;
    }

    menu->options[i] = menuOption;
    menu->unk58++;
    a3 = menu->y1;
    a2 = menu->y0;
    temp_a1 = (menu->x0 + (i * 0x44) + 6);
    uvGuiSetTextListBounds(menuOption, temp_a1, temp_a1 + 0x41, a2, a3);
}
#line 289 "src/modules/uvgui_rom.c"

#line 290 "src/modules/uvgui_rom.c"
/* Draw the panel frame, then its regular content for non-list mode or
 * each attached text list in list mode. Preserve original child-count behavior. */
void uvGuiDrawPanelOrTextLists(void *panel) {
    s32 index;
    u8 *child;

    uvGuiDrawShadedInsetRectangle(*(s16 *)((u8 *)panel + 0x20), *(s16 *)((u8 *)panel + 0x22), *(s16 *)((u8 *)panel + 0x24), *(s16 *)((u8 *)panel + 0x26), 3, 0x2C, 0x94, 0xFF, 0xFF);
    if (*(s16 *)((u8 *)panel + 0x1E) != 2) {
        uvGuiDrawCenteredText(*(s16 *)((u8 *)panel + 0x20), *(s16 *)((u8 *)panel + 0x22), *(s16 *)((u8 *)panel + 0x24), *(s16 *)((u8 *)panel + 0x26), panel, 0xFF, 0xFF, 0xFF, 0xFF);
        return;
    }
    index = 0;
    child = panel;
    if (*(s16 *)((u8 *)panel + 0x58) > 0) {
        do {
            uvGuiDrawTextList(*(s32 *)(child + 0x28));
            index += 1;
            child += 4;
        } while (index < *(s16 *)((u8 *)panel + 0x58));
    }
}
#line 309 "src/modules/uvgui_rom.c"

#line 310 "src/modules/uvgui_rom.c"
/* Query option hit states, retain the last matched index and update the outer bounds state.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
s32 uvGuiUpdateMenuHitState(GuiMenu *arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, f32 arg5,
                            f32 arg6) {
    GuiMenu *var_s0;
    s32 i;
    s32 matchFound;

    if (arg0->unk1E == 2) {
        matchFound = -1;
        for (i = 0; i < arg0->unk58; i++) {
            if (uvGuiUpdateTextListHitState((GuiDrawTextList *)arg0->options[i], arg1, arg2, arg3, arg4, arg5, arg6) != 0) {
                matchFound = i;
            }
        }
        if (i == arg0->unk58) {
            arg0->unk5A = matchFound;
        }
    } else {
        arg0->unk5A = -1;
    }
    if (arg0->unk5A >= 0) {
        return 1;
    }
    if (arg2 < arg0->x0) {
        arg0->unk1E = 1;
        return 0;
    }
    if (arg0->x1 < arg2) {
        arg0->unk1E = 1;
        return 0;
    }
    if (arg3 < arg0->y0) {
        arg0->unk1E = 1;
        return 0;
    }
    if (arg0->y1 < arg3) {
        arg0->unk1E = 1;
        return 0;
    }
    arg0->unk1E = 2;
    return 1;
}
#line 311 "src/modules/uvgui_rom.c"

#line 312 "src/modules/uvgui_rom.c"
/* Clear 50 option states and each 80-entry item pointer list with native selection defaults.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiResetMenuOptionPool(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 50; i++) {
        sGuiMenuOptions[i].unk1E = 0;
        for (j = 0; j < 80; j++) {
            sGuiMenuOptions[i].items[j] = NULL;
        }
        sGuiMenuOptions[i].activeMenuItems = 0;
        sGuiMenuOptions[i].unk16A = -1;
    }
}
#line 313 "src/modules/uvgui_rom.c"

#line 314 "src/modules/uvgui_rom.c"
/* Scan 50 slots at stride 0x170 for the first zero active halfword, set only
 * that halfword to one and return its index. The inherited full-pool path
 * still writes slot 50, beyond the scanned range. RE_UNKNOWN: callers must
 * establish spare capacity, backing storage and reuse initialization; no
 * exhaustion repair is made here. */
#line 318 "src/modules/uvgui_rom.c"
s16 uvGuiAllocatePool170Slot(void) {
    GuiPoolSlot170 *slot;
    s32 index;

    for (index = 0, slot = (GuiPoolSlot170 *) &D_uvgui_rom_00408D78; index != 50; index++, slot++) {
        if (slot->active == 0) {
            break;
        }
    }
    slot->active = 1;
    return (s16) index;
}
#line 330 "src/modules/uvgui_rom.c"
#line 315 "src/modules/uvgui_rom.c"

#line 316 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x170-byte TextList pool.
 * RE_UNKNOWN: valid index/allocation/lifetime domains need pool writers and callers; no local guard. */
void *uvGuiGetTextListSlot(s16 index) {
    return (index * 0x170) + &D_uvgui_rom_00408D78;
}
#line 319 "src/modules/uvgui_rom.c"

#line 320 "src/modules/uvgui_rom.c"
/* Copy exactly 30 bytes through the original uppercase transform: subtract
 * 32 from every byte >= 97, including values above z. Neither source nor
 * destination is NUL-scanned; callers must supply full fixed-width buffers. */
void uvGuiCopyTextListText(void *destination, u8 *source)
{
  u8 buffer[0x1E];
  u8 *end;
  u8 *write;
  u8 *read;
  u8 character;
  write = &buffer[0];
  end = &buffer[0x1E];
  read = source;
  do
  {
    character = *read;
    if (((s32) character) >= 0x61)
    {
      *write = character - 0x20;
    }
    else
    {
      *write = character;
    }
    write = write + 1;
    read += 1;
  }
  while (write != end);
  _uvMediaCopy(destination, &buffer[0], 0x1E);
}
#line 347 "src/modules/uvgui_rom.c"

#line 348 "src/modules/uvgui_rom.c"
/* Store the original signed state value at TextList object offset 0x1E.
 * State meanings remain with the corresponding update and drawing routines. */
void uvGuiSetTextListState(void *widget, s16 state) {
    *(s16 *)((u8 *)widget + 0x1E) = state;
}
#line 351 "src/modules/uvgui_rom.c"

#line 352 "src/modules/uvgui_rom.c"
/* Store the list rectangle and its signed horizontal extent. Preserve
 * original edge order and truncation when the extent does not fit 16 bits. */
void uvGuiSetTextListBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom)
{
  *((s16 *) (((u8 *) widget) + 0x20)) = left;
  *((s16 *) (((u8 *) widget) + 0x22)) = right;
  *((s16 *) (((u8 *) widget) + 0x24)) = top;
  *((s16 *) (((u8 *) widget) + 0x26)) = bottom;
  *((s16 *) (((u8 *) widget) + 0x16C)) = (s16) ((*((s16 *) (((u8 *) widget) + 0x22))) - (*((s16 *) (((u8 *) widget) + 0x20))));
}
#line 360 "src/modules/uvgui_rom.c"

#line 361 "src/modules/uvgui_rom.c"
/* Insert text in the first of eighty free slots, update its count and
 * assign the original compact row bounds. Preserve full-list behavior. */
void uvGuiAppendCompactTextRow(void *panel, s32 text)
{
  u8 *entry;
  s32 index;
  s16 baseX;
  s16 row;
  entry = (u8 *) panel;
 index = 0; loop: if ((*((s32 *) (entry + 0x28))) != 0) {
    index += 1;
    entry += 4;
    if (index != 0x50)
    {
      goto loop;
    }
  }

  if (index != 0x50)
  {
    *((s32 *) (entry + 0x28)) = text;
    *((s16 *) (((u8 *) panel) + 0x168)) = (*((s16 *) (((u8 *) panel) + 0x168))) + 1;
    baseX = *((s16 *) (((u8 *) panel) + 0x20));
    row = (s16) ((*((s16 *) (((u8 *) panel) + 0x24))) - (index * 0xC));
    uvGuiSetCompactTextBounds(text, baseX, (s16) (baseX + 0x40), (s16) (row - 0xB), (s32) row);
  }
}
#line 386 "src/modules/uvgui_rom.c"

#line 387 "src/modules/uvgui_rom.c"
/* Draw the text-list panel in states 1 and 2; state 1 hides children.
 * State 2 visits child references; re-read state/count after drawing callbacks.
 * Four-byte child entries have no local bound. RE_UNKNOWN: child ownership,
 * lifetime and count-backed extent need original writers, callers and teardown. */
void uvGuiDrawTextList(GuiDrawTextList *widget) {
    s32 alpha;
    s32 red;
    s32 index;
    u8 *child;
    switch (widget->state) {
        case 1: alpha = 0x7F; break;
        case 2: alpha = 0xFF; break;
        default: return;
    }
    uvGuiDrawShadedInsetRectangle(widget->left, widget->right, widget->top, widget->bottom, 2, 0xD5, 0xD7, 0x25, alpha);
    switch (widget->state) {
        case 1: red = 0xFF; break;
        case 2: red = 0; break;
        default: return;
    }
    uvGuiDrawCenteredText(widget->left, widget->right, widget->top, widget->bottom, widget, red, 0, 0, 0xFF);
    if (widget->state != 1) {
        index = 0;
        child = (u8 *)widget;
        if (widget->count > 0) {
            do {
                uvGuiDrawMenuItemAndAttachments(*(void **)(child + 0x28));
                index++;
                child += 4;
            } while (index < widget->count);
        }
    }
}
#line 388 "src/modules/uvgui_rom.c"

#line 389 "src/modules/uvgui_rom.c"
/* While list state is two, call each child checker and retain the
 * last index returning nonzero. Reload the signed count after every call;
 * write the matched-child field only if the terminal index equals count.
 * Outside list state two, set that field to -1. A matched child returns one immediately;
 * otherwise use the original inclusive rectangle to set state two/one and
 * return one/zero. Retain low-byte and signed-halfword input conversions.
 * RE_ORIGINAL_QUIRK: count is neither bounded to the 80 observed child slots
 * nor frozen across callbacks; a negative count skips the loop and leaves
 * the previous matched index. Preserve that original control flow.
 * RE_UNKNOWN: complete widget allocation, valid count/child-pointer domain,
 * input-byte/forwarded-word/scalar roles, coordinate units and historical
 * source widths. Trace original allocator, helper 004020A0 and callers before
 * tightening bounds, assigning physical names or changing source ABI. */
s32 uvGuiUpdateTextListHitState(GuiDrawTextList *widget, u8 inputByte,
                           s16 horizontal, s16 vertical, s32 forwardedWord,
                           f32 firstScalar, f32 secondScalar) {
    s32 index;
    s32 lastMatchedChild;

    if (widget->state == 2) {
        lastMatchedChild = -1;
        for (index = 0; index < widget->count; index++) {
            /* RE_UNKNOWN: input-byte, word and scalar roles. Audit original
             * child helper 004020A0 and its callers before physical naming. */
            if (uvGuiUpdateMenuItemHitState(widget->children[index], inputByte,
                                      horizontal, vertical, forwardedWord,
                                      firstScalar, secondScalar) != 0) {
                lastMatchedChild = index;
            }
        }
        if (index == widget->count) {
            widget->matchedChildIndex = lastMatchedChild;
        }
    } else {
        widget->matchedChildIndex = -1;
    }
    if (widget->matchedChildIndex >= 0) {
        return 1;
    }
    if (horizontal < widget->left) {
        widget->state = 1;
        return 0;
    }
    if (horizontal > widget->right) {
        widget->state = 1;
        return 0;
    }
    if (vertical < widget->top) {
        widget->state = 1;
        return 0;
    }
    if (vertical > widget->bottom) {
        widget->state = 1;
        return 0;
    }
    widget->state = 2;
    return 1;
}
#line 390 "src/modules/uvgui_rom.c"

#line 391 "src/modules/uvgui_rom.c"
/* Initialize 135 scalar-widget state/source/range fields and computed display bounds.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiResetScalarWidgetPool(void) {
    Inner28 *var_s0;
    s32 i;

    for (i = 0; i < 135; i++) {
        var_s0 = &sGuiScalarSlots[i];
        var_s0->unk1E = 0;
        var_s0->unk20 = 0x11;
        var_s0->unk30 = 1.0f;
        var_s0->unk34 = -1.0f;
        var_s0->unk28 = 0.0f;
        var_s0->unk24 = 0.0f;
        var_s0->unk2C = 0;
        var_s0->unk44 = 0;
        uvGuiSetUpperTextBounds(var_s0, (s16) ((s32) (sUvGfxMgrExports->uvGetScreenWidth() - 0xB4) / 2),
                                (s16) ((s32) (sUvGfxMgrExports->uvGetScreenWidth() + 0xB4) / 2),
                                (s16) ((sUvGfxMgrExports->uvGetScreenHeight() - 0x28) / 2),
                                (sUvGfxMgrExports->uvGetScreenHeight() + 0x28) / 2);
        var_s0->unk40 = 0;
    }
}
#line 392 "src/modules/uvgui_rom.c"

#line 393 "src/modules/uvgui_rom.c"
/* Scan 135 slots at stride 0x48 for the first zero active halfword, set only
 * that halfword to one and return its index. The inherited full-pool path
 * still writes slot 135, beyond the scanned range. RE_UNKNOWN: callers must
 * establish spare capacity, backing storage and reuse initialization; no
 * exhaustion repair is made here. */
#line 397 "src/modules/uvgui_rom.c"
s16 uvGuiAllocatePool48Slot(void) {
    GuiPoolSlot48 *slot;
    s32 index;

    for (index = 0, slot = (GuiPoolSlot48 *) &D_uvgui_rom_0040D558; index != 135; index++, slot++) {
        if (slot->active == 0) {
            break;
        }
    }
    slot->active = 1;
    return (s16) index;
}
#line 409 "src/modules/uvgui_rom.c"
#line 394 "src/modules/uvgui_rom.c"

#line 395 "src/modules/uvgui_rom.c"
/* Clear the selected upper-text slot state at offset 0x1E. Preserve
 * signed 16-bit index truncation and the original unchecked pool access. */
void uvGuiClearUpperTextSlotState(short index)
{
  s32 slot = (s16) index;
  *((s16 *) (((u8 *) (&D_uvgui_rom_0040D576)) + (slot * 0x48))) = 0;
}
#line 400 "src/modules/uvgui_rom.c"

#line 401 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x48-byte UpperText pool.
 * RE_UNKNOWN: valid index/allocation/lifetime domains need pool writers and callers; no local guard. */
void *uvGuiGetUpperTextSlot(s16 index) {
    return (index * 0x48) + &D_uvgui_rom_0040D558;
}
#line 404 "src/modules/uvgui_rom.c"

#line 405 "src/modules/uvgui_rom.c"
/* Copy exactly 30 bytes through the original uppercase transform: subtract
 * 32 from every byte >= 97, including values above z. Neither source nor
 * destination is NUL-scanned; callers must supply full fixed-width buffers. */
void uvGuiCopyUpperTextText(void *destination, u8 *source)
{
  u8 buffer[0x1E];
  u8 *write;
  u8 *end;
  u8 *read;
  u8 character;
  write = buffer;
  end = &buffer[0x1E];
  read = source;
  do
  {
    character = *read;
    if (((s32) character) >= 0x61)
    {
      *write = character - 0x20;
    }
    else
    {
      *write = character;
    }
    write += 1;
    read += 1;
  }
  while (write != end);
  _uvMediaCopy(destination, buffer, 0x1E);
}
#line 432 "src/modules/uvgui_rom.c"

#line 433 "src/modules/uvgui_rom.c"
/* Store the four signed UpperText rectangle edges in original order.
 * Preserve conversion to signed 16-bit coordinates and leave validation to callers. */
void uvGuiSetUpperTextBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom) {
    (*(s16 *)((u8 *)widget + 0x38)) = left;
    (*(s16 *)((u8 *)widget + 0x3A)) = right;
    (*(s16 *)((u8 *)widget + 0x3C)) = top;
    (*(s16 *)((u8 *)widget + 0x3E)) = bottom;
}
#line 439 "src/modules/uvgui_rom.c"

#line 440 "src/modules/uvgui_rom.c"
/* Read/update the selected scalar view, format its display and emit widget text/borders.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_ORIGINAL_QUIRK: States outside 1/2 can read unwritten color scratch;
 * numeric display with neither format flag can read unwritten format scratch.
 * RE_UNKNOWN: Caller state/flag reachability and prior storage provenance. */
/* RE_UNKNOWN: Font calls use the 30-byte text view or 24-byte format scratch.
 * FontPrintStr may write input[49] for length >= 51; formatter bounds, NUL
 * termination, alias/writability and conditional scratch validity remain unproved. */
void uvGuiDrawScalarWidget(Inner28 *arg0) {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s16 sp7A;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 temp_a0;
    f32 var_fa0;
    s16 pad6A;
    s16 sp68;
    u8 sp50[24];
    s32 temp_v0_4;

    if (arg0->unk2C != 0) {
        if (arg0->unk20 & 2) {
            if ((*arg0->unk2C) < arg0->unk28) {
                var_fa0 = arg0->unk28 - (*arg0->unk2C);
            } else {
                var_fa0 = -(arg0->unk28 - (*arg0->unk2C));
            }
            if (var_fa0 > 1.0f) {
                if (arg0->unk28 >= 0.0f) {
                    arg0->unk28 = *arg0->unk2C;
                } else {
                    arg0->unk28 = *arg0->unk2C;
                }
            }
        } else {
            arg0->unk28 = *((f32 *) arg0->unk2C);
        }
        if (arg0->unk28 >= 0.0f) {
            arg0->unk24 = (f32) ((s32) (arg0->unk28 + 0.5f));
        } else {
            arg0->unk24 = (f32) ((s32) (arg0->unk28 - 0.5f));
        }
    }
    switch (arg0->unk1E) {
        case 1:
            r = 0xD5;
            g = 0xD7;
            b = 0x25;
            a = 0xFF;
            break;
        case 2:
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
            a = 0xFF;
            break;
        default:
            break;
    }
    uvGuiDrawShadedInsetRectangle(arg0->unk38, arg0->unk3A, arg0->unk3C, arg0->unk3E, 2, r, g, b, a);
    sp7A = arg0->unk38 + 5;
    sp78 = arg0->unk3A - 5;
    sp76 = (arg0->unk3C + (((s32) (arg0->unk3E - arg0->unk3C)) / 5)) + 5;
    sp74 = arg0->unk3E - 5;
    if (arg0->unk1E == 2) {
        uvGuiDrawShadedInsetRectangle(sp7A, sp78, sp76, sp74, 2, 50, 50, 50, 0xFFU);
    }
    if (arg0->unk34 != arg0->unk30) {
        var_fa0 = (arg0->unk28 - arg0->unk30) / (arg0->unk34 - arg0->unk30);
    } else {
        var_fa0 = 0.5f;
    }
    if (arg0->unk20 & 2) {
        temp_v0_4 = ((s32) arg0->unk34) - ((s32) arg0->unk30);
        if (temp_v0_4 > 0) {
            var_fa0 = ((f32) ((s32) ((temp_v0_4 * var_fa0) + 0.5f))) / temp_v0_4;
        } else {
            var_fa0 = 0.5f;
        }
    }
    if (arg0->unk1E == 2) {
        b = 0xFF;
        g = 0xFF;
        r = 0xFF;
        a = 0xFF;
        // RE_UNKNOWN: inherited compilation workaround; historical source unresolved.
        if (1) {
        }
    } else {
        b = 0;
        g = 0;
        r = 0;
        a = 0x50;
    }
    temp_a0 = (s32) (((f32) ((s16) ((sp78 - sp7A) - 0xC))) * var_fa0);
    temp_a0 = (sp7A + temp_a0) + 3;
    uvGuiDrawShadedInsetRectangle(temp_a0, temp_a0 + 6, sp76 + 2, sp74 - 2, 2, r, g, b,
                            a);
    if ((arg0->unk44 != 0) && (arg0->unk20 & 2)) {
        uvGuiCopyUpperTextText(arg0->unk0, arg0->unk44[(s32) arg0->unk24]);
    }
    sUvFontExports->uvFontWidth(arg0->unk0);
    sUvFontExports->uvFontColor(0, 0, 0, 255);
    sUvFontExports->uvFontPrintStr(arg0->unk38 + 7, arg0->unk3C + 2, arg0->unk0);
    if (arg0->unk20 & 0x10) {
        if (arg0->unk20 & 1) {
            sUvStringExports->uvSprintf(sp50, ((u8 *)&sGuiNativeStringRegion[0x00]), arg0->unk28);
        }
        if (arg0->unk20 & 2) {
            sUvStringExports->uvSprintf(sp50, ((u8 *)&sGuiNativeStringRegion[0x04]), (s32) arg0->unk24);
        }
        sp68 = sUvFontExports->uvFontWidth(sp50);
        sUvFontExports->uvFontColor(0, 0, 0, 255);
        sUvFontExports->uvFontPrintStr((arg0->unk3A - sp68) - 7, arg0->unk3C + 2, sp50);
    }
}
#line 441 "src/modules/uvgui_rom.c"

#line 442 "src/modules/uvgui_rom.c"
/* Store GUI element word 0x40 without guessing its detailed role. */
void uvGuiSetWord40(void *element, s32 value) {
    *(s32 *)((u8 *)element + 0x40) = value;
}
#line 445 "src/modules/uvgui_rom.c"

#line 446 "src/modules/uvgui_rom.c"
/* Store range/source words and initialize displayed scalar from the selected integer/float view.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiConfigureScalarWidgetSource(Inner28 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 *arg4) {
    f32 temp_fv0;

    arg0->unk30 = arg1;
    arg0->unk2C = arg4;
    arg0->unk34 = arg2;
    if (arg0->unk2C != NULL) {
        if (arg0->unk20 & 2) {
            arg0->unk28 = *arg0->unk2C;
        } else {
            arg0->unk28 = *(f32 *) arg0->unk2C;
        }
    } else {
        arg0->unk28 = arg3;
    }

    if (arg0->unk20 & 2) {
        if (arg0->unk28 >= 0.0f) {
            arg0->unk24 = (s32) (arg0->unk28 + 0.5f);
        } else {
            arg0->unk24 = (s32) (arg0->unk28 - 0.5f);
        }
    } else {
        arg0->unk24 = arg0->unk28;
    }
}
#line 447 "src/modules/uvgui_rom.c"

#line 448 "src/modules/uvgui_rom.c"
/* Store the GUI element short at offset 0x20. */
void uvGuiSetShort20(void *element, s16 value) {
    *(s16 *)((u8 *)element + 0x20) = value;
}
#line 451 "src/modules/uvgui_rom.c"

#line 452 "src/modules/uvgui_rom.c"
/* When active, apply controller-derived scalar adjustment and native range/write-back rules.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiUpdateScalarWidget(Inner28 *arg0, u8 arg1, f32 arg2) {
    f32 temp_ft4;
    f32 var_fv1;
    f32 var_fv0;
    if (arg0->unk1E != 2) {
        return;
    }
    if ((arg0->unk2C != 0) && (!(arg0->unk20 & 2))) {
        arg0->unk28 = *((f32 *) arg0->unk2C);
    }
    temp_ft4 = (arg0->unk34 - arg0->unk30) * 0.5f;
    var_fv1 = sUvGfxMgrExports->uvGfxMgrGetScalarOverrideOrCurrent();
    if (arg2 > 0.0f) {
        arg2 *= arg2;
    } else {
        arg2 *= -arg2;
    }
    if (arg0->unk20 == 0x11) {
        arg0->unk28 += ((0.5f * arg2) * temp_ft4) * var_fv1;
        if (arg0->unk28 < arg0->unk30) {
            arg0->unk28 = arg0->unk30;
        } else if (arg0->unk28 > arg0->unk34) {
            arg0->unk28 = arg0->unk34;
        }
        arg0->unk24 = arg0->unk28;
    } else {
        var_fv0 = 20.0f / (arg0->unk34 - arg0->unk30);
        if (var_fv0 < 1.0f) {
            var_fv0 = 1.0f;
        } else if (var_fv0 > 100.0f) {
            var_fv0 = 100.0f;
        }
        var_fv0 = (((var_fv0 * 0.5f) * arg2) * temp_ft4) * var_fv1;
        if (sUvContExports->uvControllerButtonPress(arg1, L_JPAD) != 0) {
            var_fv0 = -1.0f;
        }
        if (sUvContExports->uvControllerButtonPress(arg1, R_JPAD) != 0) {
            var_fv0 = 1.0f;
        }
        arg0->unk28 += var_fv0;
        if (arg0->unk28 < arg0->unk30) {
            arg0->unk28 = arg0->unk30;
        } else if (arg0->unk28 > arg0->unk34) {
            arg0->unk28 = arg0->unk34;
        }
        arg0->unk24 = GUI_ROUNDF(arg0->unk28);
    }
    if (arg0->unk2C != 0) {
        if (arg0->unk20 & 2) {
            *arg0->unk2C = GUI_ROUNDF(arg0->unk28);
        } else {
            *((f32 *) arg0->unk2C) = arg0->unk28;
        }
    }
    if (arg0->unk40 != 0) {
        arg0->unk40(arg0);
    }
}
#line 453 "src/modules/uvgui_rom.c"

#line 454 "src/modules/uvgui_rom.c"
/* Notify the optional callback only when the signed active halfword changes,
 * then store the requested value after the callback returns. The final store
 * also occurs when no callback runs. RE_UNKNOWN: valid slot storage, callback
 * lifetime and reentrancy must come from pool users; callback writes to active
 * can be overwritten. */
#line 456 "src/modules/uvgui_rom.c"
void uvGuiSetPool48Active(GuiPoolSlot48 *slot, s16 active) {
    if (active != slot->active) {
        if (slot->onActiveChanged != NULL) {
            slot->onActiveChanged(slot, active);
        }
    }
    slot->active = active;
}
#line 464 "src/modules/uvgui_rom.c"
#line 455 "src/modules/uvgui_rom.c"

#line 456 "src/modules/uvgui_rom.c"
/* Store GUI element word 0x44 without guessing its detailed role. */
void uvGuiSetWord44(void *element, s32 value) {
    *(s32 *)((u8 *)element + 0x44) = value;
}
#line 459 "src/modules/uvgui_rom.c"

#line 460 "src/modules/uvgui_rom.c"
/* Initialize 20 value/graph widget slots and copy the two native fixed-span label inputs.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* The original INPUT/OUTPUT offsets +8/+16 each support the native 30-byte
 * read within the declared 72-byte region. RE_UNKNOWN: Historical storage
 * declaration and external caller/input alias domains; prove full readonly layout. */

void uvGuiResetValueWidgetPool(void) {
    Inner30 *var_s0;
    s32 i;

    for (i = 0; i < 20; i++) {
        var_s0 = &sGuiValueSlots[i];
        var_s0->unk5E = 0;
        var_s0->unk68 = 0.0f;
        var_s0->unk6C = -1.0f;
        var_s0->unk70 = 1.0f;
        var_s0->unk80 = 0;
        var_s0->unk74 = 0.0f;
        var_s0->unk78 = -1.0f;
        var_s0->unk7C = 1.0f;
        var_s0->unk60 = -1;
        var_s0->unk62 = 1;
        uvGuiSetValueWidgetBounds(var_s0, ((sUvGfxMgrExports->uvGetScreenWidth() / 2) - 0x50),
                                ((sUvGfxMgrExports->uvGetScreenWidth() / 2) + 0x50),
                                ((sUvGfxMgrExports->uvGetScreenHeight() / 2) - 0x50),
                                (sUvGfxMgrExports->uvGetScreenHeight() / 2) + 0x50);
        var_s0->unk8C = 0;
        uvGuiSetValueWidgetLabels(var_s0, ((u8 *)&sGuiNativeStringRegion[0x08]), ((u8 *)&sGuiNativeStringRegion[0x10]));
    }
}
#line 461 "src/modules/uvgui_rom.c"

#line 462 "src/modules/uvgui_rom.c"
/* Scan 20 slots at stride 0x90 for the first zero active halfword, set only
 * that halfword to one and return its index. The inherited full-pool path
 * still writes slot 20, beyond the scanned range. RE_UNKNOWN: callers must
 * establish spare capacity, backing storage and reuse initialization; no
 * exhaustion repair is made here. */
#line 466 "src/modules/uvgui_rom.c"
s16 uvGuiAllocatePool90Slot(void) {
    GuiPoolSlot90 *slot;
    s32 index;

    for (index = 0, slot = (GuiPoolSlot90 *) &D_uvgui_rom_0040FB50; index != 20; index++, slot++) {
        if (slot->active == 0) {
            break;
        }
    }
    slot->active = 1;
    return (s16) index;
}
#line 478 "src/modules/uvgui_rom.c"
#line 463 "src/modules/uvgui_rom.c"

#line 464 "src/modules/uvgui_rom.c"
/* Clear state 0x5E in the selected 0x90-byte value-widget slot using the
 * signed low sixteen bits of the incoming word. Preserve the argument home
 * reference and existing empty branch; this cleanup changes only names.
 * RE_UNKNOWN: valid caller index range and intended original source form of
 * the empty branch. Check original callsites and assembly before removing
 * that source shape or narrowing the current incoming s32 ABI. */
void uvGuiClearValueWidgetSlotState(s32 indexWord)
{
  s32 slotIndex = (s16) indexWord;
  s32 *originalIndexWord;
  originalIndexWord = &indexWord;
  if (*originalIndexWord)
  {
  }
  *((s16 *) ((slotIndex * 0x90) + (((u8 *) (&D_uvgui_rom_0040FB50)) + 0x5E))) = 0;
}
#line 474 "src/modules/uvgui_rom.c"

#line 475 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x90-byte ValueWidget pool.
 * RE_UNKNOWN: valid index/allocation/lifetime domains need pool writers and callers; no local guard. */
void *uvGuiGetValueWidgetSlot(s16 index) {
    return (index * 0x90) + &D_uvgui_rom_0040FB50;
}
#line 478 "src/modules/uvgui_rom.c"

#line 479 "src/modules/uvgui_rom.c"
/* Store the four signed ValueWidget rectangle edges in original order.
 * Preserve conversion to signed 16-bit coordinates and leave validation to callers. */
void uvGuiSetValueWidgetBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom) {
    (*(s16 *)((u8 *)widget + 0x84)) = left;
    (*(s16 *)((u8 *)widget + 0x86)) = right;
    (*(s16 *)((u8 *)widget + 0x88)) = top;
    (*(s16 *)((u8 *)widget + 0x8A)) = bottom;
}
#line 485 "src/modules/uvgui_rom.c"

#line 486 "src/modules/uvgui_rom.c"
/* Format the paired label text and uppercase-copy exactly 30 bytes from each input.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_ORIGINAL_QUIRK: Reads exactly 30 bytes from each input, without a NUL
 * bound, and uppercases every byte >= 97. RE_UNKNOWN: Input object extents,
 * caller aliases and historical storage contracts; prove native backing. */
void uvGuiSetValueWidgetLabels(Inner30 *arg0, u8 *arg1, u8 *arg2) {
    u8 sp30[0x1E];
    s32 i;

    sUvStringExports->uvSprintf(arg0->unk40, ((u8 *)&sGuiNativeStringRegion[0x18]), arg1, arg2);
    for (i = 0; i < 0x1E; i++) {
        if (arg1[i] >= 'a') {
            sp30[i] = arg1[i] - ' ';
        } else {
            sp30[i] = arg1[i];
        }
    }
    _uvMediaCopy(arg0->unk4, sp30, 0x1EU);
    for (i = 0; i < 0x1E; i++) {
        if (arg2[i] >= 'a') {
            sp30[i] = arg2[i] - ' ';
        } else {
            sp30[i] = arg2[i];
        }
    }
    _uvMediaCopy(arg0->unk22, sp30, 0x1EU);
}
#line 487 "src/modules/uvgui_rom.c"

#line 488 "src/modules/uvgui_rom.c"
/* Store the identifier, scalar parameters and optional source address.
 * Read that source when present, otherwise use the fallback. RE_UNKNOWN:
 * source/widget extents, ownership and lifetime need setup, users and teardown. */
void uvGuiConfigureValueWidget(void *widget, s32 identifier, f32 first, f32 second, f32 fallback, f32 *source) {
    (*(s32 *)((u8 *)widget + 0x0)) = identifier;
    (*(f32 *)((u8 *)widget + 0x6C)) = first;
    (*(s32 *)((u8 *)widget + 0x80)) = source;
    (*(f32 *)((u8 *)widget + 0x70)) = second;
    if (source != NULL) {
        (*(f32 *)((u8 *)widget + 0x68)) = (f32) *source;
        return;
    }
    (*(f32 *)((u8 *)widget + 0x68)) = fallback;
}
#line 499 "src/modules/uvgui_rom.c"

#line 500 "src/modules/uvgui_rom.c"
/* Store GUI element word 0x8C without guessing its detailed role. */
void uvGuiSetWord8C(void *element, s32 value) {
    *(s32 *)((u8 *)element + 0x8C) = value;
}
#line 503 "src/modules/uvgui_rom.c"

#line 504 "src/modules/uvgui_rom.c"
/* Apply graph selection, point-count/edit controls and selected coordinate adjustments.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_UNKNOWN: Graph point/index domains, zero coordinate-span divisors and
 * callback mutation remain unproved; preserve native reloads/comparisons
 * and inherited workarounds until original caller/source evidence closes them. */
void uvGuiUpdateGraphWidget(Inner30 *arg0, u8 button, f32 arg2) {
    UvGrphInnerStruct *temp_t1;
    UvGrphInnerStruct *var_t2;
    UvGrphInnerStruct *var_t0;
    UvGrphStruct *sp38;
    f32 var_fa0_2;
    f32 temp_fv1;
    f32 var_fa1;
    f32 sp28;
    f32 sp24;
    s32 i;

    if ((arg0->unk0 == NULL) || (arg0->unk5E != 2)) {
        arg0->unk60 = -1;
        return;
    }
    sp38 = arg0->unk0;
    // RE_UNKNOWN: inherited compilation workaround; historical source unresolved.: Increase compiler stack for arg1
    if (button) {
    }

    if (sUvContExports->uvControllerButtonPress(button, START_BUTTON) != 0) {
        sUvGrphExports->uvGrphClampPointCount(arg0->unk40, &sp38->count);
        arg0->unk64 = 0x3C;
    }
    sp28 = (arg0->unk70 - arg0->unk6C) * 0.5f;
    sp24 = sUvGfxMgrExports->uvGfxMgrGetScalarOverrideOrCurrent();
    if (arg0->unk80 != NULL) {
        arg0->unk68 = *arg0->unk80;
    }
    if (arg2 > 0.0f) {
        arg2 *= arg2;
    } else {
        arg2 *= -arg2;
    }
    if (arg0->unk62) {
        arg0->unk68 += 0.5f * arg2 * sp28 * sp24;
        if (arg0->unk68 < arg0->unk6C) {
            arg0->unk68 = arg0->unk6C;
        } else {
            if (arg0->unk70 < arg0->unk68) {
                arg0->unk68 = arg0->unk70;
            }
        }

        // RE_UNKNOWN: inherited compilation workaround; historical source unresolved.
        if (1) {
        }
    }

    if (arg0->unk80 != NULL) {
        *arg0->unk80 = arg0->unk68;
    }
    if (sUvContExports->uvControllerHasButtons(button, Z_TRIG) != 0) {
        if (sUvContExports->uvControllerButtonPress(button, L_CBUTTONS) != 0) {
            arg0->unk60 -= 1;
            if (arg0->unk60 < 0) {
                arg0->unk60 = sp38->count - 1;
            }
        }
        if (sUvContExports->uvControllerButtonPress(button, R_CBUTTONS) != 0) {
            arg0->unk60 += 1;
            if (arg0->unk60 >= sp38->count) {
                arg0->unk60 = 0;
            }
        }
        if (sUvContExports->uvControllerButtonPress(button, U_CBUTTONS) != 0) {
            arg0->unk60 = sUvGrphExports->uvGrphInsertPointAfter(sp38, (s32) arg0->unk60);
        }
        if (sUvContExports->uvControllerButtonPress(button, D_CBUTTONS) != 0) {
            arg0->unk60 = sUvGrphExports->uvGrphRemovePoint(sp38, (s32) arg0->unk60);
        }
        if (arg0->unk60 == -1) {
            return;
        }
    }

    temp_t1 = &sp38->arr[arg0->unk60];
    if (arg0->unk60 < (sp38->count - 1)) {
        var_t2 = &sp38->arr[arg0->unk60 + 1];
    } else {
        var_t2 = NULL;
    }
    if (arg0->unk60 >= 2) {
        var_t0 = &sp38->arr[arg0->unk60 - 1];
    } else {
        var_t0 = NULL;
    }

    var_fa0_2 = sp38->arr->unk0;
    temp_fv1 = sp38->arr[sp38->count - 1].unk0;
    if (sUvContExports->uvControllerHasButtons(button, Z_TRIG) == 0) {
        if (sUvContExports->uvControllerHasButtons(button, L_CBUTTONS) != 0) {
            temp_t1->unk0 -= (temp_fv1 - var_fa0_2) * 0.0025f;
            if (var_t0 != NULL) {
                if (temp_t1->unk0 < var_t0->unk0) {
                    temp_t1->unk0 = var_t0->unk0;
                }
            }
        }
        if (sUvContExports->uvControllerHasButtons(button, R_CBUTTONS) != 0) {
            temp_t1->unk0 += (temp_fv1 - var_fa0_2) * 0.0025f;
            if (var_t2 != NULL) {
                if (var_t2->unk0 < temp_t1->unk0) {
                    temp_t1->unk0 = var_t2->unk0;
                }
            }
        }
        var_fa0_2 = 1000000.0f;
        for (i = 0; i < sp38->count; i++) {
            if (sp38->arr[i].unk4 < var_fa0_2) {
                var_fa0_2 = sp38->arr[i].unk4;
            }
        }
        temp_fv1 = -1000000.0f;
        for (i = 0; i < sp38->count; i++) {
            if (temp_fv1 < sp38->arr[i].unk4) {
                temp_fv1 = sp38->arr[i].unk4;
            }
        }

        var_fa1 = (temp_fv1 - var_fa0_2) * 0.15f * sp24;
        if (var_fa1 < 0.005f) {
            var_fa1 = 0.005f;
        } else if (var_fa1 > 10.0f) {
            var_fa1 = 10.0f;
        }
        if (sUvContExports->uvControllerHasButtons(button, D_CBUTTONS) != 0) {
            temp_t1->unk4 -= var_fa1;
        }
        if (sUvContExports->uvControllerHasButtons(button, U_CBUTTONS) != 0) {
            temp_t1->unk4 += var_fa1;
        }
    }

    if (arg0->unk8C != NULL) {
        arg0->unk8C(arg0);
    }
}
#line 505 "src/modules/uvgui_rom.c"

#line 506 "src/modules/uvgui_rom.c"
/* Draw the graph points, selection, labels and formatted coordinate text using native reloads.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_UNKNOWN: Graph point/index domains, zero coordinate-span divisors and
 * callback mutation remain unproved; preserve native reloads/comparisons
 * and inherited workarounds until original caller/source evidence closes them. */
/* RE_UNKNOWN: Font calls reuse writable 60-byte format scratch, but the
 * formatter has no output bound and input strings have unproved termination.
 * Its length >= 51 path can change scratch byte 49; preserve reuse/reloads and
 * establish caller text/alias domains rather than infer limits from field widths. */
void uvGuiDrawGraphWidget(Inner30 *arg0) {
    UvGrphStruct *sp1D4;
    f32 spA4;
    f32 temp_fa1;
    f32 sp1C8;
    f32 sp1C4;
    f32 sp1C0;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs3;
    f32 temp_fs5;
    f32 sp1A8;
    f32 sp1A4;
    f32 sp1A0;
    f32 sp19C;
    UvGrphInnerStruct *s0;
    f32 sp194;
    u8 var_s6;
    u8 sp192;
    u8 var_s5;
    u8 sp190;
    Mtx4F sp150;
    Mtx4F sp110;
    u8 spD4[0x3C];
    s32 i;
    UvGrphInnerStruct *var_v0;
    UvGrphInnerStruct *var_v1;
    static s32 D_uvgui_rom_00406F08 = 0;

    sp1D4 = arg0->unk0;
    if ((sp1D4 == NULL) || (sp1D4->count == 0)) {
        return;
    }

    if (arg0->unk80 != NULL) {
        arg0->unk68 = *arg0->unk80;
    }
    sUvGfxMgrExports->uvGfxAppendViewport(0, sUvGfxMgrExports->uvGetScreenWidth() - 1, 0,
                                                 sUvGfxMgrExports->uvGetScreenHeight() - 1);
    sUvFMtxExports->uvMat4SetOrtho(&sp150, 0.0f, (sUvGfxMgrExports->uvGetScreenWidth() - 1), 0.0f,
                                   (sUvGfxMgrExports->uvGetScreenHeight() - 1));
    sUvFMtxExports->uvGfxMtxProjPushF(&sp150);
    sUvFMtxExports->uvMat4SetIdentity(&sp110);
    sUvFMtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&sp110);
    sUvGfxStateExports->uvGfxStatePush();
    sUvGfxStateExports->uvGfxStateSetFlags(0x800FFF);
    sUvGfxStateExports->uvGfxClearCurrentStateBits(0x600000);
    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(arg0->unk84 - 2, arg0->unk88 - 2, 0, 0, 0, 0, 0, 0, 0x7F);
    sUvDGeomExports->uvVtx(arg0->unk86 + 2, arg0->unk88 - 2, 0, 0, 0, 0, 0, 0, 0x7F);
    sUvDGeomExports->uvVtx(arg0->unk86 + 2, arg0->unk8A + 2, 0, 0, 0, 0, 0, 0, 0x7F);
    sUvDGeomExports->uvVtx(arg0->unk84 - 2, arg0->unk8A + 2, 0, 0, 0, 0, 0, 0, 0x7F);
    sUvDGeomExports->uvVtxEndPoly();
    sUvGfxStateExports->uvGfxStatePop();
    sp1A8 = sp1D4->arr->unk0;
    sp1A4 = sp1D4->arr[sp1D4->count - 1].unk0;

    sp1A0 = 1000000.0f;
    for (i = 0; i < sp1D4->count; i++) {
        if (sp1D4->arr[i].unk4 < sp1A0) {
            sp1A0 = sp1D4->arr[i].unk4;
        }
    }
    sp19C = -1000000.0f;
    for (i = 0; i < sp1D4->count; i++) {
        if (sp19C < sp1D4->arr[i].unk4) {
            sp19C = sp1D4->arr[i].unk4;
        }
    }

    if (ABS_2(sp1A0 - sp19C) < 2.0f) {
        sp1A0 -= (0.01f * (sp1A4 - sp1A8));
        sp19C += (0.01f * (sp1A4 - sp1A8));
    }

    sp1C0 = (sp1A4 - sp1A8) * 0.02f;
    spA4 = ((sp19C - sp1A0) / (sp1A4 - sp1A8));
    temp_fs5 = (f32) (arg0->unk86 - arg0->unk84) / (sp1A4 - sp1A8);
    sp194 = (f32) (arg0->unk8A - arg0->unk88) / (sp19C - sp1A0);
    sUvGfxMgrExports->uvGfxAppendViewport(arg0->unk84, arg0->unk86, arg0->unk88, arg0->unk8A);
    sUvFMtxExports->uvMat4SetOrtho(
        &sp150, (sp1A8 - (2.0f * sp1C0)) * temp_fs5, ((2.0f * sp1C0) + sp1A4) * temp_fs5,
        (sp1A0 - ((2.0f * sp1C0) * spA4)) * sp194, (((2.0f * sp1C0) * spA4) + sp19C) * sp194);
    sUvFMtxExports->uvGfxMtxProjPushF(&sp150);
    sUvFMtxExports->uvMat4SetIdentity(&sp110);
    sUvFMtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&sp110);
    sUvGfxStateExports->uvGfxStatePush();
    sUvGfxStateExports->uvGfxStateSetFlags(0x800FFF);
    sUvGfxStateExports->uvGfxClearCurrentStateBits(0x600000);
    for (i = 0; i < (sp1D4->count - 1); i++) {
        var_v0 = &sp1D4->arr[i];
        var_v1 = &sp1D4->arr[i + 1];
        sp1C8 = var_v0->unk0 * temp_fs5;
        sp1C4 = var_v1->unk0 * temp_fs5;
        var_fs2 = var_v0->unk4 * sp194;
        var_fs0 = var_v1->unk4 * sp194;
        if (arg0->unk5E == 2) {
            if (arg0->unk64 > 0) {
                arg0->unk64--;
                var_s6 = 0xFF;
                sp192 = 0;
                var_s5 = 0;
                sp190 = 0xFF;
            } else {
                if (i % 2) {
                    var_s6 = 0xFF;
                    sp192 = 0xFF;
                    var_s5 = 0xFF;
                    sp190 = 0x7F;
                } else {
                    var_s6 = 0xC8;
                    sp192 = 0xC8;
                    var_s5 = 0xC8;
                    sp190 = 0x7F;
                }
            }
        } else {
            var_s6 = 0xFF;
            sp192 = 0xFF;
            var_s5 = 0;
            sp190 = 0x7F;
        }
        if ((var_fs2 < 0) && (var_fs0 < 0)) {
            var_fs3 = var_fs2;
            var_fs1 = var_fs0;
            var_fs0 = 0;
            var_fs2 = 0;
        } else {
            var_fs1 = 0;
            var_fs3 = 0;
        }
        if ((var_fs2 >= 0) && (var_fs0 >= 0)) {
            sUvDGeomExports->uvVtxBeginPoly();
            sUvDGeomExports->uvVtx(sp1C8, var_fs3, 0, 0, 0, var_s6, sp192, var_s5, sp190);
            sUvDGeomExports->uvVtx(sp1C4, var_fs1, 0, 0, 0, var_s6, sp192, var_s5, sp190);
            sUvDGeomExports->uvVtx(sp1C4, var_fs0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
            sUvDGeomExports->uvVtx(sp1C8, var_fs2, 0, 0, 0, var_s6, sp192, var_s5, sp190);
            sUvDGeomExports->uvVtxEndPoly();
        } else {
            f32 var_fs1 = var_v0->unk0 * temp_fs5;
            f32 var_fs0 = var_v0->unk4 * sp194;
            f32 var_fs2 = var_v1->unk0 * temp_fs5;
            f32 var_fs3 = var_v1->unk4 * sp194;
            if (var_fs3 < var_fs0) {
                sUvDGeomExports->uvVtxBeginPoly();
                sUvDGeomExports->uvVtx(var_fs1, 0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(
                    (var_fs2 - ((var_fs3 / (var_fs3 - var_fs0)) * (var_fs2 - var_fs1))), 0, 0, 0, 0,
                    var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(var_fs1, var_fs0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtxEndPoly();
                sUvDGeomExports->uvVtxBeginPoly();
                sUvDGeomExports->uvVtx(
                    (var_fs2 - ((var_fs3 / (var_fs3 - var_fs0)) * (var_fs2 - var_fs1))), 0, 0, 0, 0,
                    var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(var_fs2, var_fs3, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(var_fs2, 0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtxEndPoly();
            } else {
                sUvDGeomExports->uvVtxBeginPoly();
                sUvDGeomExports->uvVtx(var_fs1, 0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(var_fs1, var_fs0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(
                    (var_fs2 - ((var_fs3 / (var_fs3 - var_fs0)) * (var_fs2 - var_fs1))), 0, 0, 0, 0,
                    var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtxEndPoly();
                sUvDGeomExports->uvVtxBeginPoly();
                sUvDGeomExports->uvVtx(
                    (var_fs2 - ((var_fs3 / (var_fs3 - var_fs0)) * (var_fs2 - var_fs1))), 0, 0, 0, 0,
                    var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(var_fs2, 0, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtx(var_fs2, var_fs3, 0, 0, 0, var_s6, sp192, var_s5, sp190);
                sUvDGeomExports->uvVtxEndPoly();
            }
        }
    }
    if ((sp1A8 < 0) && (sp1A4 > 0)) {
        sUvDGeomExports->uvVtxBeginPoly();
        sUvDGeomExports->uvVtx(-1, (sp1A0 * sp194), 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtx(1, (sp1A0 * sp194), 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtx(1, (sp19C * sp194), 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtx(-1, (sp19C * sp194), 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtxEndPoly();
    }
    if ((sp1A0 < 0) && (sp19C > 0)) {
        sUvDGeomExports->uvVtxBeginPoly();
        sUvDGeomExports->uvVtx((sp1A8 * temp_fs5), -1, 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtx((sp1A4 * temp_fs5), -1, 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtx((sp1A4 * temp_fs5), 1, 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtx((sp1A8 * temp_fs5), 1, 0, 0, 0, 0, 0, 0, 0xFF);
        sUvDGeomExports->uvVtxEndPoly();
    }
    if ((arg0->unk60 != -1) && (arg0->unk60 < sp1D4->count)) {
        s0 = &sp1D4->arr[arg0->unk60];
        sp1C0 *= 0.5f;
        sp1C8 = (s0->unk0 - sp1C0) * temp_fs5;
        sp1C4 = (s0->unk0 + sp1C0) * temp_fs5;
        temp_fa1 = sp1C0 * spA4;
        var_fs3 = (s0->unk4 - temp_fa1) * sp194;
        var_fs2 = (s0->unk4 + temp_fa1) * sp194;
        sp1C0 *= 2.0f;
        D_uvgui_rom_00406F08 = !D_uvgui_rom_00406F08;
        if (D_uvgui_rom_00406F08) {
            var_s6 = 0xFF;
            sp192 = 0xFF;
            var_s5 = 0;
            sp190 = 0xFF;
        } else {
            var_s6 = 0;
            sp192 = 0;
            var_s5 = 0;
            sp190 = 0xFF;
        }

        sUvDGeomExports->uvVtxBeginPoly();
        sUvDGeomExports->uvVtx(sp1C8, var_fs3, 0, 0, 0, var_s6, sp192, var_s5, sp190);
        sUvDGeomExports->uvVtx(sp1C4, var_fs3, 0, 0, 0, var_s6, sp192, var_s5, sp190);
        sUvDGeomExports->uvVtx(sp1C4, var_fs2, 0, 0, 0, var_s6, sp192, var_s5, sp190);
        sUvDGeomExports->uvVtx(sp1C8, var_fs2, 0, 0, 0, var_s6, sp192, var_s5, sp190);
        sUvDGeomExports->uvVtxEndPoly();
    }
    arg0->unk74 = sUvGrphExports->uvGrphEvaluateLinearCurve(sp1D4, arg0->unk68);
    temp_fa1 = (sp1C0 * spA4);
    sp1C8 = (arg0->unk68 - sp1C0) * temp_fs5;
    sp1C4 = (arg0->unk68 + sp1C0) * temp_fs5;
    var_fs3 = ((arg0->unk74 - temp_fa1) * sp194);
    var_fs2 = ((arg0->unk74 + temp_fa1) * sp194);

    sUvDGeomExports->uvVtxBeginPoly();
    sUvDGeomExports->uvVtx(sp1C8, (arg0->unk74 * sp194), 0, 0, 0, 0, 0xFF, 0xFF, 0xFF);
    sUvDGeomExports->uvVtx((arg0->unk68 * temp_fs5), var_fs3, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF);
    sUvDGeomExports->uvVtx(sp1C4, (arg0->unk74 * sp194), 0, 0, 0, 0, 0xFF, 0xFF, 0xFF);
    sUvDGeomExports->uvVtx((arg0->unk68 * temp_fs5), var_fs2, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF);
    sUvDGeomExports->uvVtxEndPoly();
    if (arg0->unk5E != 2) {
        sUvFontExports->uvFontColor(0xFF, 0xFF, 0, 0xFF);
        sUvStringExports->uvSprintf(spD4, ((u8 *)&sGuiNativeStringRegion[0x24]), arg0->unk4, arg0->unk22);
        sUvFontExports->uvFontPrintStr(
            (s32) ((arg0->unk84 + arg0->unk86) - sUvFontExports->uvFontWidth(spD4)) / 2,
            (arg0->unk8A - sUvFontExports->uvFontHeight()) - 2, spD4);
    }
    if (arg0->unk5E == 2) {
        var_s6 = 0;
    } else {
        var_s6 = 0xFF;
    }
    sUvFontExports->uvFontColor(var_s6, 0xFF, 0xFF, 0xFF);
    sUvStringExports->uvSprintf(spD4, ((u8 *)&sGuiNativeStringRegion[0x2C]), arg0->unk68);
    sUvFontExports->uvFontPrintStr(arg0->unk84 + 4, arg0->unk88 - 2, spD4);
    sUvStringExports->uvSprintf(spD4, ((u8 *)&sGuiNativeStringRegion[0x30]), arg0->unk74);
    sUvFontExports->uvFontPrintStr((arg0->unk86 - sUvFontExports->uvFontWidth(spD4)) - 4,
                                   arg0->unk88 - 2, spD4);
    if ((arg0->unk5E == 2) && (arg0->unk60 != -1)) {
        sUvFontExports->uvFontColor(0xFF, 0xFF, 0, 0xFF);
        s0 = &sp1D4->arr[arg0->unk60];
        sUvStringExports->uvSprintf(spD4, ((u8 *)&sGuiNativeStringRegion[0x34]), s0->unk0);
        sUvFontExports->uvFontPrintStr(arg0->unk84 + 4,
                                       arg0->unk8A - (sUvFontExports->uvFontHeight() * 2), spD4);
        sUvStringExports->uvSprintf(spD4, ((u8 *)&sGuiNativeStringRegion[0x38]), s0->unk4);
        sUvFontExports->uvFontPrintStr((arg0->unk86 - sUvFontExports->uvFontWidth(spD4)) - 4,
                                       arg0->unk8A - (sUvFontExports->uvFontHeight() * 2), spD4);
    }
    sUvGfxStateExports->uvGfxStatePop();
    sUvGfxMgrExports->uvGfxAppendViewport(0, sUvGfxMgrExports->uvGetScreenWidth() - 1, 0,
                                                 sUvGfxMgrExports->uvGetScreenHeight() - 1);
    sUvFMtxExports->uvMat4SetOrtho(&sp150, -0.5f, sUvGfxMgrExports->uvGetScreenWidth() + 0.5f, -0.5f,
                                   sUvGfxMgrExports->uvGetScreenHeight() + 0.5f);
    sUvFMtxExports->uvGfxMtxProjPushF(&sp150);
}
#line 507 "src/modules/uvgui_rom.c"

#line 508 "src/modules/uvgui_rom.c"
/* Clear the state counter at 0x60 only when entering state two from
 * another state, then store the new signed state at 0x5E. */
void uvGuiSetValueWidgetState(void *widget, s16 state) {
    if ((state == 2) && ((*(s16 *)((u8 *)widget + 0x5E)) != 2)) {
        (*(s16 *)((u8 *)widget + 0x60)) = 0;
    }
    (*(s16 *)((u8 *)widget + 0x5E)) = state;
}
#line 514 "src/modules/uvgui_rom.c"

#line 515 "src/modules/uvgui_rom.c"
/* Read promoted property words until zero or an unsupported selector; selector
 * one reads another word and stores its low halfword at target+0x62. Preserve
 * the inherited early returns without va_end. RE_UNKNOWN: target extent and
 * complete argument lists must be supplied by callers; the remaining object
 * layout is unproven. */
#line 518 "src/modules/uvgui_rom.c"
void uvGuiSetField62Props(GuiField62Target *target, ...) {
    va_list args;
    s16 property;
    va_start(args, target);
    while (TRUE) {
        property = (s16) va_arg(args, s32);
        switch (property) {
            case 0:
                return;
            case 1:
                target->unk62 = va_arg(args, s32);
                break;
            default:
                return;
        }
    }
}
#line 535 "src/modules/uvgui_rom.c"
#line 516 "src/modules/uvgui_rom.c"

#line 517 "src/modules/uvgui_rom.c"
/* Initialize ten vector-widget states, source pointers, scalar ranges and display bounds.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiResetVectorWidgetPool(void) {
    Inner2C *var_s0;
    s32 i;

    for (i = 0; i < 10; i++) {
        var_s0 = &sGuiVectorSlots[i];
        var_s0->unk1E = 0;
        var_s0->unk20 = 1;
        var_s0->unk34 = 1.0f;
        var_s0->unk38 = -1.0f;
        var_s0->unk24 = 0.0f;
        var_s0->unk28 = 0.0f;
        var_s0->unk2C = 0.0f;
        var_s0->unk30 = 0;
        var_s0->unk44 = -1;
        uvGuiSetLowerTextBounds(var_s0, (s16) ((s32) (sUvGfxMgrExports->uvGetScreenWidth() - 0xB4) / 2),
                                ((sUvGfxMgrExports->uvGetScreenWidth() + 0xB4) / 2),
                                (s16) ((s32) (sUvGfxMgrExports->uvGetScreenHeight() - 0x50) / 2),
                                (s32) (sUvGfxMgrExports->uvGetScreenHeight() + 0x50) / 2);
        var_s0->unk48 = 0;
    }
}
#line 518 "src/modules/uvgui_rom.c"

#line 519 "src/modules/uvgui_rom.c"
/* Scan 10 slots at stride 0x4C for the first zero active halfword, set only
 * that halfword to one and return its index. The inherited full-pool path
 * still writes slot 10, beyond the scanned range. RE_UNKNOWN: callers must
 * establish spare capacity, backing storage and reuse initialization; no
 * exhaustion repair is made here. */
#line 523 "src/modules/uvgui_rom.c"
s16 uvGuiAllocatePool4CSlot(void) {
    GuiPoolSlot4C *slot;
    s32 index;

    for (index = 0, slot = (GuiPoolSlot4C *) &D_uvgui_rom_00406F20; index != 10; index++, slot++) {
        if (slot->active == 0) {
            break;
        }
    }
    slot->active = 1;
    return (s16) index;
}
#line 535 "src/modules/uvgui_rom.c"
#line 520 "src/modules/uvgui_rom.c"

#line 521 "src/modules/uvgui_rom.c"
/* Clear the selected lower-text slot state at offset 0x1E. Preserve
 * signed 16-bit index truncation and existing argument materialization. */
void uvGuiClearLowerTextSlotState(s32 index)
{
  s32 *indexAddress;
  s32 idx;
  indexAddress = &index;
  *((s16 *) (((u8 *) (&D_uvgui_rom_00406F3E)) + (((s16) (*indexAddress)) * 0x4C))) = 0;
}
#line 528 "src/modules/uvgui_rom.c"

#line 529 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x4C-byte LowerText pool.
 * RE_UNKNOWN: valid index/allocation/lifetime domains need pool writers and callers; no local guard. */
void *uvGuiGetLowerTextSlot(s16 index) {
    return (index * 0x4C) + &D_uvgui_rom_00406F20;
}
#line 532 "src/modules/uvgui_rom.c"

#line 533 "src/modules/uvgui_rom.c"
/* Copy exactly 30 bytes through the original uppercase transform: subtract
 * 32 from every byte >= 97, including values above z. Neither source nor
 * destination is NUL-scanned; callers must supply full fixed-width buffers. */
void uvGuiCopyLowerTextText(void *destination, u8 *source)
{
  u8 buffer[0x1E];
  u8 *write;
  u8 *end;
  u8 *read;
  u8 character;
  write = buffer;
  end = &buffer[0x1E];
  read = source;
  do
  {
    character = *read;
    if (((s32) character) >= 0x61)
    {
      *write = character - 0x20;
    }
    else
    {
      *write = character;
    }
    write += 1;
    read += 1;
  }
  while (write != end);
  _uvMediaCopy(destination, buffer, 0x1E);
}
#line 560 "src/modules/uvgui_rom.c"

#line 561 "src/modules/uvgui_rom.c"
/* Store the four signed LowerText rectangle edges in original order.
 * Preserve conversion to signed 16-bit coordinates and leave validation to callers. */
void uvGuiSetLowerTextBounds(void *widget, s16 left, s16 right, s16 top, s16 bottom) {
    (*(s16 *)((u8 *)widget + 0x3C)) = left;
    (*(s16 *)((u8 *)widget + 0x3E)) = right;
    (*(s16 *)((u8 *)widget + 0x40)) = top;
    (*(s16 *)((u8 *)widget + 0x42)) = bottom;
}
#line 567 "src/modules/uvgui_rom.c"

#line 568 "src/modules/uvgui_rom.c"
/* Reload the optional vector source and draw selected component values and widget text.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
/* RE_ORIGINAL_QUIRK: States outside 1/2 can read unwritten color scratch;
 * component selectors outside 0/1/2, except -1, can read unwritten value scratch.
 * RE_UNKNOWN: Caller selector/state reachability and prior scratch provenance;
 * trace native callers before asserting valid domains or adding defaults. */
/* RE_UNKNOWN: Font calls use the 30-byte text view or 24-byte format scratch.
 * Native long-string handling can write byte 49; formatting bounds, NUL
 * termination, writable backing, aliases and selector reachability need callers. */
void uvGuiDrawVectorWidget(Inner2C *arg0) {
    u8 spAF;
    u8 spAE;
    u8 spAD;
    u8 spAC;
    s16 spAA;
    s16 spA8;
    s16 spA6;
    s16 spA4;
    s16 spA2;
    s16 spA0;
    s16 sp9E;
    s16 sp9C;
    s16 sp9A;
    s16 sp98;
    s16 sp96;
    s16 sp94;
    s16 sp92;
    s16 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    u8 sp6C[0x18];
    f32 sp68;
    f32 temp_fa1;
    s32 pad;
    f32 sp5C;

    if (arg0->unk30 != 0) {
        arg0->unk24 = arg0->unk30->x;
        arg0->unk28 = arg0->unk30->y;
        arg0->unk2C = arg0->unk30->z;
    }

    // clang-format off
    switch (arg0->unk1E) {
        case 1:
            spAF = 0xD5;\
            spAE = 0xD7;\
            spAD = 0x25;\
            spAC = 0xFF;
            break;
        case 2:
            spAF = 0xFF;\
            spAE = 0xFF;\
            spAD = 0xFF;\
            spAC = 0xFF;
            break;
    }
    // clang-format on

    uvGuiDrawShadedInsetRectangle(arg0->unk3C, arg0->unk3E, arg0->unk40, arg0->unk42, 2, spAF, spAE, spAD,
                            spAC);
    if (arg0->unk20 == 1) {
        sp94 = arg0->unk3E - 5;
        sp92 = arg0->unk40 + 5;
        sp90 = arg0->unk42 - 5;
        sp96 = (sp94 - sp90) + sp92;
        spAF = arg0->unk24 * 255.0f;
        spAE = arg0->unk28 * 255.0f;
        spAD = arg0->unk2C * 255.0f;
        spAC = 0xFF;
        uvGuiDrawShadedInsetRectangle(sp96, sp94, sp92, sp90, 2, spAF, spAE, spAD, spAC);
    } else {
        sp96 = arg0->unk3E;
        sp94 = arg0->unk3E;
        sp92 = arg0->unk40;
        sp90 = arg0->unk42;
    }
    spAA = arg0->unk3C + 5;
    spA8 = sp96 - 5;
    spA6 = arg0->unk40 + ((arg0->unk42 - arg0->unk40) / 5) + 5;
    spA4 = arg0->unk42 - 5;
    if (arg0->unk1E == 2) {
        uvGuiDrawShadedInsetRectangle(spAA, spA8, spA6, spA4, 2, 0x32, 0x32, 0x32, 0xFF);
    }

    if (arg0->unk38 != arg0->unk34) {
        sp8C = (arg0->unk24 - arg0->unk34) / (arg0->unk38 - arg0->unk34);
        sp84 = (arg0->unk28 - arg0->unk34) / (arg0->unk38 - arg0->unk34);
        sp88 = (arg0->unk2C - arg0->unk34) / (arg0->unk38 - arg0->unk34);
    } else {
        sp8C = sp84 = sp88 = 0.5f;
    }
    sp98 = ((spA4 - spA6) - 8) / 3;
    sp9A = spA4 - 2;
    sp9C = sp9A - sp98;
    if (arg0->unk1E == 2) {
        if (arg0->unk44 == 0) {
            spAF = spAE = spAD = 0xFF;
            spAC = 0xFF;
        } else {
            spAF = spAE = spAD = 0x32;
            spAC = 0xFF;
        }
    } else {
        spAF = spAE = spAD = 0;
        spAC = 0x50;
    }
    spA2 = (spA8 - spAA) - 0xC;
    spA0 = spAA + (s16) (spA2 * sp8C) + 3;
    sp9E = spA0 + 6;
    uvGuiDrawShadedInsetRectangle(spA0, sp9E, sp9C, sp9A, 2, spAF, spAE, spAD, spAC);
    sp9A = sp9C - 2;
    sp9C = sp9A - sp98;
    if (arg0->unk1E == 2) {
        if (arg0->unk44 == 1) {
            spAF = spAE = spAD = 0xFF;
            spAC = 0xFF;
        } else {
            spAF = spAE = spAD = 0x32;
            spAC = 0xFF;
        }
    } else {
        spAF = spAE = spAD = 0;
        spAC = 0x50;
    }
    spA0 = spAA + (s16) (spA2 * sp84) + 3;
    sp9E = spA0 + 6;
    uvGuiDrawShadedInsetRectangle(spA0, sp9E, sp9C, sp9A, 2, spAF, spAE, spAD, spAC);
    sp9A = sp9C - 2;
    sp9C = sp9A - sp98;
    if (arg0->unk1E == 2) {
        if (arg0->unk44 == 2) {
            spAF = spAE = spAD = 0xFF;
            spAC = 0xFF;
        } else {
            spAF = spAE = spAD = 0x32;
            spAC = 0xFF;
        }
    } else {
        spAF = spAE = spAD = 0;
        spAC = 0x50;
    }
    spA0 = spAA + (s16) (spA2 * sp88) + 3;
    sp9E = spA0 + 6;
    uvGuiDrawShadedInsetRectangle(spA0, sp9E, sp9C, sp9A, 2, spAF, spAE, spAD, spAC);
    sUvFontExports->uvFontWidth(arg0->unk0);
    sUvFontExports->uvFontColor(0, 0, 0, 0xFF);
    sUvFontExports->uvFontPrintStr(arg0->unk3C + 7, arg0->unk40 + 2, arg0->unk0);
    if ((arg0->unk20 == 1) && (arg0->unk1E == 2)) {
        if (arg0->unk44 != -1) {
            switch (arg0->unk44) {
                case 0:
                    sp68 = arg0->unk24;
                    break;
                case 1:
                    sp68 = arg0->unk28;
                    break;
                case 2:
                    sp68 = arg0->unk2C;
                    break;
            }
            temp_fa1 = (arg0->unk24 + arg0->unk28 + arg0->unk2C) / 3.0f;
            if (temp_fa1 > 0.5f) {
                spAD = 0;
                spAE = 0;
                spAF = 0;
                spAC = 0xFF;
            } else {
                spAD = 0xFF;
                spAE = 0xFF;
                spAF = 0xFF;
                spAC = 0xFF;
            }
            sUvFontExports->uvFontColor(spAF, spAE, spAD, spAC);
            sUvStringExports->uvSprintf(sp6C, ((u8 *)&sGuiNativeStringRegion[0x3C]), sp68);
            sUvFontExports->uvFontPrintStr(((sp94 + sp96) - (s16) sUvFontExports->uvFontWidth(sp6C))
                                               / 2,
                                           (s32) ((sp90 + sp92) + 0xC) / 2, sp6C);
            sUvStringExports->uvSprintf(sp6C, ((u8 *)&sGuiNativeStringRegion[0x40]), (s32) (sp68 * 255.0f));
            sUvFontExports->uvFontPrintStr(((sp94 + sp96) - (s16) sUvFontExports->uvFontWidth(sp6C))
                                               / 2,
                                           (s32) ((sp90 + sp92) - 0xC) / 2, sp6C);
            return;
        }
    }
    if ((arg0->unk20 == 2) && (arg0->unk1E == 2)) {
        if (arg0->unk44 != -1) {
            switch (arg0->unk44) {
                case 0:
                    sp5C = arg0->unk24;
                    break;
                case 1:
                    sp5C = arg0->unk28;
                    break;
                case 2:
                    sp5C = arg0->unk2C;
                    break;
            }
            sUvStringExports->uvSprintf(sp6C, ((u8 *)&sGuiNativeStringRegion[0x44]), sp5C);
            sUvFontExports->uvFontPrintStr((spA8 - (s16) sUvFontExports->uvFontWidth(sp6C)) - 2,
                                           arg0->unk40 + 2, sp6C);
        }
    }
}
#line 569 "src/modules/uvgui_rom.c"

#line 570 "src/modules/uvgui_rom.c"
/* Store GUI element word 0x48 without guessing its detailed role. */
void uvGuiSetWord48(void *element, s32 value) {
    *(s32 *)((u8 *)element + 0x48) = value;
}
#line 573 "src/modules/uvgui_rom.c"

#line 574 "src/modules/uvgui_rom.c"
/* Store the source pointer and three component values, using the fallback when
 * source is null. Kind one forces the two scalar controls to zero/one.
 * Other kinds retain the supplied controls; component meanings remain opaque. */
void uvGuiConfigureVectorSource(GuiVectorState *state, f32 first, f32 second, GuiVector3 *fallback, GuiVector3 *source) {
    if (state->kind == 1) { first = 0.0f; second = 1.0f; }
    state->first = first;
    state->second = second;
    state->source = source;
    if (source != NULL) {
        state->value.x = source->x;
        state->value.y = source->y;
        state->value.z = source->z;
        return;
    }
    state->value.x = fallback->x;
    state->value.y = fallback->y;
    state->value.z = fallback->z;
}
#line 575 "src/modules/uvgui_rom.c"

#line 576 "src/modules/uvgui_rom.c"
/* Store short 0x20 through the original alternate GUI entry point. */
void uvGuiSetAlternateShort20(void *element, s16 value) {
    *(s16 *)((u8 *)element + 0x20) = value;
}
#line 579 "src/modules/uvgui_rom.c"

#line 580 "src/modules/uvgui_rom.c"
/* Cycle the selected component, apply its scalar adjustment and copy back to an optional source.
 * RE_UNKNOWN: Historical source, caller domains, storage extents/aliases
 * and callback lifetimes remain limited to the original evidence. */
void uvGuiUpdateVectorWidget(Inner2C *arg0, u8 arg1, f32 arg2) {
    f32 temp_ft4;
    f32 temp_fv0;

    if (arg0->unk1E != 2) {
        return;
    }

    if (arg0->unk44 == -1) {
        arg0->unk44 = 0;
    }
    if (sUvContExports->uvControllerButtonPress(arg1, Z_TRIG) != 0) {
        arg0->unk44 += 1;
        if (arg0->unk44 >= 3) {
            arg0->unk44 = 0;
        }
    }
    if (arg0->unk30 != NULL) {
        arg0->unk24 = arg0->unk30->x;
        arg0->unk28 = arg0->unk30->y;
        arg0->unk2C = arg0->unk30->z;
    }
    temp_ft4 = (arg0->unk38 - arg0->unk34) * 0.5f;
    temp_fv0 = sUvGfxMgrExports->uvGfxMgrGetScalarOverrideOrCurrent();
    if (arg2 > 0.0f) {
        arg2 *= arg2;
    } else {
        arg2 *= -arg2;
    }
    switch (arg0->unk44) { /* irregular */
        case 0:
            arg0->unk24 += 0.5f * arg2 * temp_ft4 * temp_fv0;
            if (arg0->unk24 < arg0->unk34) {
                arg0->unk24 = arg0->unk34;
            } else {
                if (arg0->unk38 < arg0->unk24) {
                    arg0->unk24 = arg0->unk38;
                }
            }
            break;
        case 1:
            arg0->unk28 += 0.5f * arg2 * temp_ft4 * temp_fv0;
            if (arg0->unk28 < arg0->unk34) {
                arg0->unk28 = arg0->unk34;
            } else {
                if (arg0->unk38 < arg0->unk28) {
                    arg0->unk28 = arg0->unk38;
                }
            }
            break;
        case 2:
            arg0->unk2C += 0.5f * arg2 * temp_ft4 * temp_fv0;
            if (arg0->unk2C < arg0->unk34) {
                arg0->unk2C = arg0->unk34;
            } else {
                if (arg0->unk38 < arg0->unk2C) {
                    arg0->unk2C = arg0->unk38;
                }
            }
            break;
    }
    if (arg0->unk30 != NULL) {
        arg0->unk30->x = arg0->unk24;
        arg0->unk30->y = arg0->unk28;
        arg0->unk30->z = arg0->unk2C;
    }
    if (arg0->unk48 != NULL) {
        arg0->unk48(arg0);
    }
}
#line 581 "src/modules/uvgui_rom.c"

#line 582 "src/modules/uvgui_rom.c"
/* Store the GUI element mode short at offset 0x1E. */
void uvGuiSetMode(void *element, s16 mode) {
    (*(s16 *)((u8 *)element + 0x1E)) = mode;
}
#line 585 "src/modules/uvgui_rom.c"


s32 D_uvgui_rom_00406F0C[] = { 0x01480000, __entrypoint_func_uvgui_rom_400000, 0, 0 };
