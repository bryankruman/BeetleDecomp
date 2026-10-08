#ifndef UVGUI_ROM_H
#define UVGUI_ROM_H

#include "uvfvec_rom.h"
#include "uvgrph_rom.h"

/* RE_UNKNOWN: These observed field views do not prove caller bounds,
 * allocation/lifetime guarantees, alias exclusions or universal callback ABI.
 * The accepted active setter uses its separate two-argument prefix view. */

#define MAX_MENU_ITEM_NAME 12
#define MAX_MENU_OPTION_NAME_LEN 30
#define MAX_MENU_TITLE_LEN 30
#define MAX_MENU_OPTIONS 12

typedef void (*UvGuiRoutine)(void* arg0);

typedef struct Inner28_s {
    /* 0x00 */ u8 unk0[0x1E];                             /* inferred */
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char pad22[2];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32* unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ void (*unk40)(void*);
    /* 0x44 */ u8** unk44; /* Observed text-pointer entries; extent unknown. */
} Inner28;                                          /* size = 0x48 */

typedef struct Inner2C_s {
    /* 0x00 */ u8 unk0[0x1E];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char pad22[2];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ Vec3F* unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s16 unk3C;                           /* inferred */
    /* 0x3E */ s16 unk3E;                           /* inferred */
    /* 0x40 */ s16 unk40;                           /* inferred */
    /* 0x42 */ s16 unk42;                           /* inferred */
    /* 0x44 */ s16 unk44;
    /* 0x46 */ char pad46[2];
    /* 0x48 */ void (*unk48)(void*);
} Inner2C;                                          /* size = 0x4C */

typedef struct Inner30_s {
    /* 0x00 */ UvGrphStruct* unk0;
    /* 0x04 */ s8 unk4[0x1E];
    /* 0x22 */ u8 unk22[0x1E];
    /* 0x40 */ u8 unk40[0x1E];
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ s16 unk60;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char pad66[2];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;                           /* inferred */
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C; 
    /* 0x80 */ f32* unk80;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ void (*unk8C)(void*);
} Inner30;                                          /* size = 0x90 */

// Item Entry?
typedef struct GuiMenuItem_s {
    /* 0x00 */ u8 name[MAX_MENU_ITEM_NAME];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char pad1A[2];
    /* 0x1C */ UvGuiRoutine unk1C; /* inferred */
    /* 0x20 */ UvGuiRoutine unk20; /* inferred */
    /* 0x24 */ UvGuiRoutine unk24; /* inferred */
    /* 0x28 */ Inner28* unk28;
    /* 0x2C */ Inner2C* unk2C;
    /* 0x30 */ Inner30* unk30;
} GuiMenuItem;    /* size = 0x34 */

// MenuEntry?
typedef struct GuiMenuOption_s {
    /* 0x000 */ u8 name[MAX_MENU_OPTION_NAME_LEN];                    /* maybe part of unk0[0x20]? */
    /* 0x01E */ s16 unk1E;
    /* 0x020 */ s16 unk20;                          /* inferred */
    /* 0x022 */ s16 unk22;                          /* inferred */
    /* 0x024 */ s16 unk24;                          /* inferred */
    /* 0x026 */ s16 unk26;                          /* inferred */
    /* 0x028 */ GuiMenuItem* items[80]; // itemEntry?
    /* 0x168 */ s16 activeMenuItems;                         /* inferred */
    /* 0x16A */ s16 unk16A;
    /* 0x16C */ s16 unk16C;                         /* inferred */
    /* 0x16E */ char pad16E[2];
} GuiMenuOption;          /* size = 0x170 */

typedef struct GuiMenu_s {
    /* 0x00 */ u8 title[MAX_MENU_TITLE_LEN];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 x0;
    /* 0x22 */ s16 x1;
    /* 0x24 */ s16 y0;                           /* inferred */
    /* 0x26 */ s16 y1;                           /* inferred */
    /* 0x28 */ GuiMenuOption* options[MAX_MENU_OPTIONS];
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
} GuiMenu;                /* size = 0x5C */

typedef struct uvGui_s {
    /* 0x00 */ GuiMenu* menus[20];
    /* 0x50 */ s16 activeMenuCount;
    /* 0x52 */ char pad52[2];
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ s16 cursorX;
    /* 0x72 */ s16 cursorY;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s8 contNo;
    /* 0x85 */ char pad85[1];
    /* 0x86 */ s16 uvds;                           /* inferred */
    /* 0x88 */ s16 fontId;
    /* 0x8A */ s8 unk8A;
    /* 0x8B */ s8 unk8B;
} uvGui;                     /* size = 0x8C */

/* The complete observed export view is source-local so it can retain
 * the accepted opaque/raw-word and private prefix types exactly.
 * RE_UNKNOWN: These are observed call views, not historical source ABI. */
typedef struct UvGui_Exports_s UvGui_Exports;
 


#endif /* UVGUI_ROM_H */
