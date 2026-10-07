// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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
void func_uvgui_rom_00400510();
void func_uvgui_rom_00400754();
void func_uvgui_rom_00400990();
void func_uvgui_rom_00400F44();
void func_uvgui_rom_0040104C();
void uvGuiSetChildContainerBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_00401290();
void func_uvgui_rom_004015B8();
void uvGuiSetPositionAndCurrentScalars(void *arg0, s16 arg1, s16 arg2);
void func_uvgui_rom_004016F0();
void func_uvgui_rom_00401BC8();
s16 uvGuiAllocatePool34Slot(void);
void *uvGuiGetCompactTextSlot(s16 arg0);
void uvGuiSetCompactTextBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_00401DC4();
void func_uvgui_rom_004020A0();
void func_uvgui_rom_0040221C(void *arg0, s16 arg1, s32 arg2);
void uvGuiAttachCenteredUpperChild(GuiCenteredAttachments *owner, void *child);
void uvGuiAttachCenteredLowerChild(GuiCenteredAttachments *owner, void *child);
void func_uvgui_rom_004023A8();
void func_uvgui_rom_00402638();
s16 uvGuiAllocatePool5CSlot(void);
void *uvGuiGetChildGroupSlot(s16 arg0);
void uvGuiSetChildGroupBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_004027AC();
void func_uvgui_rom_0040293C();
void func_uvgui_rom_00402B00();
s16 uvGuiAllocatePool170Slot(void);
void *uvGuiGetTextListSlot(s16 arg0);
void uvGuiSetTextListBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_00402D1C();
void func_uvgui_rom_00402E48();
void func_uvgui_rom_0040300C();
s16 uvGuiAllocatePool48Slot(void);
void uvGuiClearUpperTextSlotState(short arg0);
void *uvGuiGetUpperTextSlot(s16 arg0);
void uvGuiSetUpperTextBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_004032BC();
void func_uvgui_rom_004037E0();
void func_uvgui_rom_004038E4();
void uvGuiSetPool48Active(GuiPoolSlot48 *slot, s16 active);
void func_uvgui_rom_00403CAC();
s16 uvGuiAllocatePool90Slot(void);
void func_uvgui_rom_00403EB8(s32 arg0);
void *uvGuiGetValueWidgetSlot(s16 arg0);
void uvGuiSetValueWidgetBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_00403F2C();
void uvGuiConfigureValueWidget(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5);
void func_uvgui_rom_00404054();
void func_uvgui_rom_004046B4();
void uvGuiSetValueWidgetState(void *arg0, s16 arg1);
void uvGuiSetField62Props(GuiField62Target *target, ...);
void func_uvgui_rom_00405D78();
s16 uvGuiAllocatePool4CSlot(void);
void uvGuiClearLowerTextSlotState(s32 arg0);
void *uvGuiGetLowerTextSlot(s16 arg0);
void uvGuiSetLowerTextBounds(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_uvgui_rom_00406048();
void uvGuiConfigureVectorSource(GuiVectorState *state, f32 first, f32 second, GuiVector3 *fallback, GuiVector3 *source);
void func_uvgui_rom_00406B88();
void func_uvgui_rom_00406E28(void *arg0, s16 arg1);
extern s16 D_uvgui_rom_00406F00;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/__entrypoint_func_uvgui_rom_400000.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400510.s")

void func_uvgui_rom_004006B8(s32 *arg0, s32 arg1)
{
  s16 rowY;
  s32 *slot;
  s32 i;
  u8 *new_var;
  slot = arg0;
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
    *slot = arg1;
    rowY = ((*((s16 *) (((u8 *) arg0) + 0x5A))) - (i * 0xC)) - 0xC;
    new_var = (u8 *) arg0;
    *((s16 *) (new_var + 0x50)) = (*((s16 *) (((u8 *) arg0) + 0x50))) + 1;
    uvGuiSetChildGroupBounds(arg1, *((s16 *) (((u8 *) arg0) + 0x54)), *((s16 *) (((u8 *) arg0) + 0x56)), ((*((s16 *) (((u8 *) arg0) + 0x5A))) - (i * 0xC)) - 0xC, rowY + 0xC);
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400754.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400990.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00400F44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040104C.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004015B8.s")

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

void func_uvgui_rom_004016A0(void *a0, u8 a1) {
    *(u8 *)((u8 *)a0 + 0x8A) = a1;
}

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

void func_uvgui_rom_004016E0(s16 a0) {
    D_uvgui_rom_00406F00 = a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004016F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401BC8.s")

#line 170 "src/modules/uvgui_rom.c"
/* Claim the first inactive slot in the 120-entry, 0x34-byte GUI pool.
 * Preserve the original exhaustion behavior: it returns the capacity and writes
 * one slot beyond the pool when every entry is active. Callers must avoid exhaustion.
 * The widget purpose remains unknown; the name identifies the verified layout. */
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
#line 171 "src/modules/uvgui_rom.c"

#line 172 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x34-byte CompactText pool.
 * This accessor does not check bounds or allocation state; callers own both. */
void *uvGuiGetCompactTextSlot(s16 index) {
    return (index * 0x34) + &D_uvgui_rom_00407238;
}
#line 175 "src/modules/uvgui_rom.c"

void func_uvgui_rom_00401D10(s32 arg0, u8 *arg1)
{
  u8 buf[0xC];
  u8 *dst;
  u8 *new_var;
  u8 *src;
  u8 c;
  dst = buf;
  new_var = &buf[0, 0xC];
  src = arg1;
  do
  {
    c = *src;
    if (((s32) c) >= 0x61)
    {
      *dst = c - 0x20;
    }
    else
    {
      *dst = c;
    }
    dst += 1;
    src += 1;
  }
  while (dst != new_var);
  _uvMediaCopy((void *) arg0, buf, 0xC);
}

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00401DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004020A0.s")

void func_uvgui_rom_0040221C(void *arg0, s16 arg1, s32 arg2) {
    switch (arg1) {                                 /* irregular */
    case 2:
        (*(s32 *)((u8 *)arg0 + 0x1C)) = arg2;
        return;
    case 3:
        (*(s32 *)((u8 *)arg0 + 0x20)) = arg2;
        return;
    case 4:
        (*(s32 *)((u8 *)arg0 + 0x24)) = arg2;
        return;
    }
}

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004023A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402638.s")

#line 243 "src/modules/uvgui_rom.c"
/* Claim an inactive slot in the eight-entry GUI pool, or return -1 without
 * writing when full. This pool checks exhaustion unlike the other GUI allocators. */
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
#line 244 "src/modules/uvgui_rom.c"

#line 245 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x5C-byte ChildGroup pool.
 * This accessor does not check bounds or allocation state; callers own both. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004027AC.s")

void func_uvgui_rom_00402850(void *arg0) {
    s32 i;
    u8 *child;

    func_uvgui_rom_00400990(*(s16 *)((u8 *)arg0 + 0x20), *(s16 *)((u8 *)arg0 + 0x22), *(s16 *)((u8 *)arg0 + 0x24), *(s16 *)((u8 *)arg0 + 0x26), 3, 0x2C, 0x94, 0xFF, 0xFF);
    if (*(s16 *)((u8 *)arg0 + 0x1E) != 2) {
        func_uvgui_rom_00400F44(*(s16 *)((u8 *)arg0 + 0x20), *(s16 *)((u8 *)arg0 + 0x22), *(s16 *)((u8 *)arg0 + 0x24), *(s16 *)((u8 *)arg0 + 0x26), arg0, 0xFF, 0xFF, 0xFF, 0xFF);
        return;
    }
    i = 0;
    child = arg0;
    if (*(s16 *)((u8 *)arg0 + 0x58) > 0) {
        do {
            func_uvgui_rom_00402D1C(*(s32 *)(child + 0x28));
            i += 1;
            child += 4;
        } while (i < *(s16 *)((u8 *)arg0 + 0x58));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040293C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402B00.s")

#line 314 "src/modules/uvgui_rom.c"
/* Claim the first inactive slot in the 50-entry, 0x170-byte GUI pool.
 * Preserve the original exhaustion behavior: it returns the capacity and writes
 * one slot beyond the pool when every entry is active. Callers must avoid exhaustion.
 * The widget purpose remains unknown; the name identifies the verified layout. */
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
#line 315 "src/modules/uvgui_rom.c"

#line 316 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x170-byte TextList pool.
 * This accessor does not check bounds or allocation state; callers own both. */
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

void func_uvgui_rom_00402C74(void *arg0, s32 arg1)
{
  u8 *entry;
  s32 index;
  s16 baseX;
  s16 row;
  entry = (u8 *) arg0;
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
    *((s32 *) (entry + 0x28)) = arg1;
    *((s16 *) (((u8 *) arg0) + 0x168)) = (*((s16 *) (((u8 *) arg0) + 0x168))) + 1;
    baseX = *((s16 *) (((u8 *) arg0) + 0x20));
    row = (s16) ((*((s16 *) (((u8 *) arg0) + 0x24))) - (index * 0xC));
    uvGuiSetCompactTextBounds(arg1, baseX, (s16) (baseX + 0x40), (s16) (row - 0xB), (s32) row);
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402D1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00402E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_0040300C.s")

#line 393 "src/modules/uvgui_rom.c"
/* Claim the first inactive slot in the 135-entry, 0x48-byte GUI pool.
 * Preserve the original exhaustion behavior: it returns the capacity and writes
 * one slot beyond the pool when every entry is active. Callers must avoid exhaustion.
 * The widget purpose remains unknown; the name identifies the verified layout. */
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
 * This accessor does not check bounds or allocation state; callers own both. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004032BC.s")

void func_uvgui_rom_004037D8(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x40) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004037E0.s")

void func_uvgui_rom_004038D8(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0x20) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004038E4.s")

#line 454 "src/modules/uvgui_rom.c"
/* Notify the optional callback before changing the slot active value. The
 * callback runs only on a change; the original assignment still occurs every time. */
void uvGuiSetPool48Active(GuiPoolSlot48 *slot, s16 active) {
    if (active != slot->active) {
        if (slot->onActiveChanged != NULL) {
            slot->onActiveChanged(slot, active);
        }
    }
    slot->active = active;
}
#line 455 "src/modules/uvgui_rom.c"

void func_uvgui_rom_00403CA4(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x44) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403CAC.s")

#line 462 "src/modules/uvgui_rom.c"
/* Claim the first inactive slot in the 20-entry, 0x90-byte GUI pool.
 * Preserve the original exhaustion behavior: it returns the capacity and writes
 * one slot beyond the pool when every entry is active. Callers must avoid exhaustion.
 * The widget purpose remains unknown; the name identifies the verified layout. */
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
#line 463 "src/modules/uvgui_rom.c"

void func_uvgui_rom_00403EB8(s32 arg0)
{
  s32 idx = (s16) arg0;
  s32 *new_var;
  new_var = &arg0;
  if (*new_var)
  {
  }
  *((s16 *) ((idx * 0x90) + (((u8 *) (&D_uvgui_rom_0040FB50)) + 0x5E))) = 0;
}

#line 475 "src/modules/uvgui_rom.c"
/* Return the signed-index slot in the original 0x90-byte ValueWidget pool.
 * This accessor does not check bounds or allocation state; callers own both. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00403F2C.s")

#line 488 "src/modules/uvgui_rom.c"
/* Store the value-widget identifier, two scalar parameters and optional
 * source pointer. Initialize current value from that source when present,
 * otherwise from the fallback; the source remains caller-owned. */
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

void func_uvgui_rom_0040404C(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x8C) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00404054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_004046B4.s")

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
/* Process signed 16-bit option selectors from promoted integer arguments.
 * Option 1 stores a narrowed integer at offset 0x62; zero or an unsupported
 * selector ends parsing. The field purpose and complete target layout are unknown. */
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
#line 516 "src/modules/uvgui_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00405D78.s")

#line 519 "src/modules/uvgui_rom.c"
/* Claim the first inactive slot in the 10-entry, 0x4C-byte GUI pool.
 * Preserve the original exhaustion behavior: it returns the capacity and writes
 * one slot beyond the pool when every entry is active. Callers must avoid exhaustion.
 * The widget purpose remains unknown; the name identifies the verified layout. */
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
 * This accessor does not check bounds or allocation state; callers own both. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406048.s")

void func_uvgui_rom_00406B00(void *a0, s32 a1) {
    *(s32 *)((u8 *)a0 + 0x48) = a1;
}

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

void func_uvgui_rom_00406B7C(void *a0, s16 a1) {
    *(s16 *)((u8 *)a0 + 0x20) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgui_rom/func_uvgui_rom_00406B88.s")

void func_uvgui_rom_00406E28(void *arg0, s16 arg1) {
    (*(s16 *)((u8 *)arg0 + 0x1E)) = arg1;
}

