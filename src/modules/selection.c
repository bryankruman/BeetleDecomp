// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/* Observed offsets only; RE_UNKNOWN: complete historical node/export declarations need producer/caller evidence. */
typedef struct {
    u8 opaque00[0x12];
    s16 drawCallbackIndex12;
} SelectionDrawNodeView;

typedef struct {
    u8 opaque00[0x14];
    void (*drawNode)(void *node, s32 highlightWord);
    u8 opaque18[0xC];
    void (*drawRectangle)(s32 word0, s32 word1, s32 word2, s32 word3,
                          s32 word4, s32 word5, s32 word6, s32 word7);
} SelectionDrawMenuExports;

/* Address comparisons only; these declarations do not establish object extent. */
extern s32 D_selection_00420160;
extern s32 D_selection_004202E4;
void selectionRenderSharedSpritePair(void);
#line 3 "src/modules/selection.c"
/* Minimum original call/access views; these declare no backing storage.
 * MENU slot 0x08 consumes a word controller index and a record pointer.
 * RE_UNKNOWN: complete historical declarations and node/latch lifetimes
 * require original callers and producers; observed offsets alone are typed. */
typedef struct {
    u8 opaque00[8];
    s32 (*getAction)(s32 controller, void *records);
} SelectionLatchedActionExports;
typedef struct {
    u8 opaque00[4];
    s32 word04;
    void *records08;
} SelectionActionNodeView;
extern s32 D_selection_00420F1C;
extern s32 D_selection_00421CDC;
#line 3 "src/modules/selection.c"
/* Focused call-site view: original callers consume word-sized dimension
 * results; sprite IDs remain signed 16-bit globals. No shared ABI is changed. */
typedef struct AgentTrackPreviewSpriteExports_s {
    char pad0[4];
    s32 (*allocate)(void);
    void (*clearState)(s32);
    char padC[8];
    s32 (*getWidth)(s32);
    s32 (*getHeight)(s32);
    void (*setProperties)(s32, ...);
} AgentTrackPreviewSpriteExports;
extern s32 gNumOpenTracks;

typedef struct { u8 prefix[4]; s16 selected; } AgentLanguageExpressionChoices;
typedef struct { u8 prefix[4]; struct SelectionState2E98_s *returnMenu; AgentLanguageExpressionChoices *choices; } AgentLanguageExpressionMenu;
extern s8 D_80025E69;
#include "uvdgeom_rom.h"
extern UvDGeom_Rom_Exports *gUvDGeomExports;
extern f32 D_selection_0041F4E4, D_selection_0041F4E8;
typedef struct { f32 x, y; } SelectionMenuPosition;
typedef struct { u8 prefix[8]; void (*update)(s32); } SelectionObjectUpdateExports;
extern SelectionMenuPosition D_selection_00421E60;
extern s32 D_selection_00421D48[];
extern SelectionObjectUpdateExports *D_selection_00421B8C;
extern char D_80025E50[], D_selection_0041ECF8[];
void func_selection_004017E0(void);
extern s32 D_selection_004213F8[4], D_selection_00421408[4];
extern s32 D_selection_004213F8[4], D_selection_00421408[4];
typedef struct { u8 unk00[0xC]; s32 (*get)(s16, void *); } SelectionValueInputExports;
extern s32 D_selection_004213D8[4], D_selection_004213E8[4];
typedef struct { f32 value; u8 id; } SelectionSoundHandle;
typedef struct { u8 unk00[8]; s16 (*play)(SelectionSoundHandle *, s16, s32, f32, f32); u8 unk0C[0x38]; void (*setVolume)(s32); u8 unk48[4]; f32 (*getVolume)(void); u8 unk50[0x7C]; void (*initialize)(SelectionSoundHandle *); } SelectionSpeechExports;
extern f32 D_selection_0041F4C8;
typedef struct { u8 unk00[0x20]; void (*channel)(s32); u8 unk24[4]; void (*enable)(s32); u8 unk2C[0x10]; void (*music)(s32); void (*sfx)(s32); void (*speech)(s32); u8 unk48[0x94]; void (*reset)(void); } SelectionSoundConfigExports;
typedef struct { u8 unk00[0x2C]; u8 (*getState)(s32); u8 unk30[8]; s32 (*repair)(s32); } SelectionPakRepairExports;
extern f32 D_selection_00420E50;
extern void *D_selection_0041FDC0;
typedef struct { u8 unk00[0x10]; void (*format)(char *, const char *, ...); } SelectionFormatExports;
extern char D_80025E40[], D_selection_0041ECBC[];
extern s32 D_80025E64;
extern char *D_selection_004207C4[];
typedef struct { u8 unk00[0x3C]; void (*select)(u16, s32); u8 unk40[4]; s32 (*find)(s32, s32, s32); u8 unk48[0x10]; s32 (*write)(s32, s32, s32, s32, u8 *); } SelectionPakWriteExports;
typedef struct { s32 words[9]; } SelectionPresetRecord;
extern s16 D_selection_00420DF0;
extern s32 D_selection_00421670;
extern void *D_selection_0041FE64;
extern s32 D_selection_0041FE60;
extern s32 D_selection_0041FDBC;
typedef struct { u8 unk00[8]; s32 (*test)(s32); } SelectionControllerStatusExports;
extern void *D_selection_0041FCF4;
extern s32 D_selection_00420E7C;
typedef struct { u8 unk00[0x16]; s16 word16; u8 unk18[0x12]; s16 word2A; } SelectionResetWords;
extern s32 D_selection_00421B98;
extern s32 D_selection_00420E8C;
extern s32 D_selection_00420E88;
extern s32 D_selection_00420E80;
typedef struct { u8 unk00[4]; u16 value; s16 active; u8 unk08[0x2C]; } SelectionValueRecord; /* Original stride 0x34. */
void selectionRotateViewMatrixAroundPivot(f32, f32, f32);
#include "uvcback_rom.h"
#include "uvchannel_rom.h"
extern UvCback_Exports *gUvCbckExports;
extern UvChannel_Exports *gUvChanExports;
/*__SEEDEXTERNS__*/
extern f32 D_selection_0041F4EC;
extern f32 D_selection_0041F4F0;
extern f32 D_selection_00420E20;
typedef struct {
    /* 0x00 */ char pad0[0xF8];
    /* 0xF8 */ f32 unkF8;
    /* 0xFC */ Mtx4F unkFC;
    /* 0x13C */ char pad13C[0x6C];
    /* 0x1A8 */ Mtx4F unk1A8;
} ObjNode_4168C4;
typedef struct {
    /* 0x00 */ char pad00[0x0C];
    /* 0x0C */ void (*unk0C)(Mtx4F *, Mtx4F *);
    /* 0x10 */ char pad10[0x18];
    /* 0x28 */ void (*unk28)(Mtx4F *, f32, s8);
    /* 0x2C */ void (*unk2C)(Mtx4F *, f32, f32, f32);
} UvFMtxExp_4168C4;
extern UvFMtxExp_4168C4 *gUvFmtxExports;
typedef struct {
    char pad[0x40];
    void (*unk40)(s32, s32, s32, s32, s32, s32, s32, s32, s32);
} SelPrinter_00411038;
typedef struct {
    void (*unk0)(void);
    void (*unk4)(s32);
    char pad8[0x14];
    s32 (*unk1C)(void);
    char pad20[0x8];
    void (*unk28)(void);
} UvFontExp_00411038;
extern UvFontExp_00411038 *gUvFontExports;
extern s32 D_selection_00421CE8;
extern s32 D_selection_00421E98;
extern s32 D_selection_00421E9C;
typedef struct {
    char pad0[0x3C];
    s32 (*unk3C)(u16, s32);
    char pad40[0x4];
    s32 (*unk44)(s32, s32, s32);
} UvContExp_413418;
extern s32 D_selection_00420E4C;
extern void func_selection_00411B9C(void);
typedef struct { char pad[0x74]; void (*unk74)(void); } UvGfxMgrExp_BEC8;
typedef struct { char pad[0x8]; void (*unk8)(void); } UvTexAnimExp_BEC8;
extern s16 D_selection_00420D24[];
extern s16 D_selection_00420D3C[];
extern s16 D_selection_00420D48[];
extern s32 D_selection_00420E04;
extern s16 D_selection_00420D6C;
extern s16 D_selection_00420D7E;
extern s16 D_selection_00421E3A;
extern s16 D_selection_00421E3C;
typedef struct { /* 0x00 */ char pad0[4]; /* 0x04 */ s16 unk4; /* 0x06 */ char pad6[0xE]; } InnerItem_0041B19C;
typedef struct { /* 0x00 */ char pad0[4]; /* 0x04 */ s16 unk4; /* 0x06 */ char pad6[2]; /* 0x08 */ InnerItem_0041B19C *unk8; } InnerObj_0041B19C;
typedef struct { /* 0x00 */ char pad0[8]; /* 0x08 */ InnerObj_0041B19C *unk8; } D1CTarget_0041B19C;
typedef struct { /* 0x00 */ char pad0[4]; /* 0x04 */ void (*unk4)(void *, s32, InnerObj_0041B19C *); /* 0x08 */ s32 (*unk8)(s32, InnerObj_0041B19C *); } ContExp_0041B19C;
typedef struct { char pad[0x74]; void (*unk74)(void); } UvGfxMgrExp_sel_0041A0CC;
typedef struct {
    char pad0[0x3C];
    void (*unk3C)(u16, s32);
    char pad40[0x4];
    s32  (*unk44)(s32, s32, s32);
} UvContExp_00419AA4;
extern void func_selection_00419084(void);
extern void func_selection_00419B9C(void);
extern s32 D_8002CC8C;
extern s16 D_selection_00421BA4;
extern s16 D_selection_00421E34;
extern s16 D_selection_00421E36;
typedef struct {
    /* 0x00 */ char pad00[0x0C];
    /* 0x0C */ void (*unkC)(s32);
    /* 0x10 */ void (*unk10)(s32);
    /* 0x14 */ char pad14[0x3C];
    /* 0x50 */ void (*unk50)(void);
    /* 0x54 */ void (*unk54)(void);
} GfxStateExp_00416D94;
typedef struct {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ void (*unk10)(s32);
    /* 0x14 */ char pad14[0x08];
    /* 0x1C */ void (*unk1C)(s32, s32, s32, s32, s32, s32, s32, s32);
} SprtExp_00416D94;
typedef struct {
    char pad0[0x4];
    s16 (*unk4)(void);
    char pad8[0xC];
    s16 (*unk14)(s32);
    s16 (*unk18)(s32);
    void (*unk1C)(s32, ...);
} UvSprtFull_0040F0F8;
extern s32 D_selection_00421CE4;
void selectionApplySoundOptions(void);
extern void func_selection_004017E0(void);
extern void selectionPrepareTransitionAndOptionalIntroReset(s32);
extern void selectionPlayGatedVoice7B(void);
extern s16 D_selection_00421E24;
typedef struct {
    char pad00[0x34];
    void (*unk34)(s32);
    void (*unk38)(s32);
    void (*unk3C)(s32);
    char pad3C[0xA0];
    void (*unkE0)(s32);
} SndExp_409FC8;
typedef struct {
    char pad00[0x2C];
    void (*unk2C)(void);
} UvCMidiExp_409FC8;
extern UvCMidiExp_409FC8 *gUvCmidiExports;
typedef struct UnkSelectionObj_004158DC_s {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x220 - 0x2];
    /* 0x220 */ s32 unk220;
} UnkSelectionObj_004158DC;
typedef struct CamExp_004158DC_s {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ void (*unk20)(void *, s32, f64, s32);
} CamExp_004158DC;
typedef struct UvGfxMgrExp_004158DC_s {
    /* 0x00 */ char pad0[0x74];
    /* 0x74 */ void (*unk74)(void);
} UvGfxMgrExp_004158DC;
typedef struct UvTexAnimExp_004158DC_s {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ void (*unk8)(void);
} UvTexAnimExp_004158DC;
typedef struct UvTerraExp_004158DC_s {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ void (*unk8)(s16, s32);
} UvTerraExp_004158DC;
typedef struct UvEnvExp_004158DC_s {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ void (*unk18)(s16, s32);
} UvEnvExp_004158DC;
extern f32 D_selection_0041F4C4;
extern CamExp_004158DC *gCamExports;
extern s32 D_selection_00421E84;
extern s32 D_selection_00421E88;
extern s32 D_selection_00421E8C;
extern s32 D_selection_00421E94;
typedef struct {
    char pad0[0xC];
    void (*unkC)(f32, f32, f32, f32);
    void (*unk10)(s32, s32, s32, s32);
} UvGeomExp_00410D20;
extern UvGeomExp_00410D20 *gUvGeomExports;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} Node_0040D8B4;
extern s32 D_8002CCB0;
extern s32 D_8002CCB4;
extern s32 D_8002CCB8;
extern Node_0040D8B4 D_8002CCBC;
typedef struct { char pad[0x74]; void (*unk74)(void); } UvGfxMgrExp_0040C96C;
typedef struct { char pad[0x8]; void (*unk8)(void); } UvTexAnimExp_0040C96C;
typedef struct { /* 0x000 */ s16 unk0; /* 0x002 */ char pad2[0x21E]; /* 0x220 */ s32 unk220; } Node_0040C96C;
typedef struct { char pad[0x8]; void (*unk8)(s16, s32); } UvTerraExp_0040C96C;
typedef struct { char pad[0x18]; void (*unk18)(s16, s32); } UvEnvExp_0040C96C;
extern s32 D_selection_00420E68;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8  pad6[0x14 - 0x6];
} Node_0040D98C;
typedef struct {
    /* 0x00 */ s32          unk0;
    /* 0x04 */ s16          unk4;
    /* 0x06 */ u8           pad6[0x8 - 0x6];
    /* 0x08 */ Node_0040D98C *unk8;
} Inner_0040D98C;
typedef struct {
    /* 0x00 */ u8           pad0[0x8];
    /* 0x08 */ Inner_0040D98C *unk8;
} Outer_0040D98C;
void func_selection_00401FB0(void);
void func_selection_00404888(void);
void func_selection_004048D8(void);
extern s16 D_selection_00421E38;
typedef struct {
    /* 0x00 */ char pad[0x8];
    /* 0x08 */ s32 (*unk8)(s32, s32);
} Ctrl_0040CA50;
typedef struct {
    /* 0x00 */ char pad[0x8];
    /* 0x08 */ s32 unk8;
} Data_0040CA50;
void selectionAdjustWrappedMenuValue(s32 *value, s32 minimum, s32 maximum);
void selectionOpenMenuPreservingOrigin(void);
extern s8 D_selection_00421CF0;
typedef struct {
    char pad0[0xC];
    void (*unk0C)(s32);
    void (*unk10)(s32);
    char pad14[0x3C];
    void (*unk50)(void);
    void (*unk54)(void);
} UvGfxStateExp_0040626C;
extern UvGfxStateExp_0040626C *gUvGfxStateExports;
typedef struct { char pad[0x10]; void (*unk10)(s16); } UvSprtLocal_0040626C;
extern s32 gOptionsSfxVol;
typedef struct {
    char pad0[0x34];
    void (*unk34)(s32 *, s32, s32, s32, void *);
} UnkStruct_00421B90_00403C2C;
typedef struct {
    char pad0[0x44];
    void (*unk44)(s32);
    char pad48[0x98];
    void (*unkE0)(s32);
    char padE4[0x10];
    void (*unkF4)(s32);
} UnkSndExports_00403C2C;
extern s32 gOptionsSpeechVol;
typedef struct UnkContExports_004030E4_s {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ s32 (*unk8)(s32);
} UnkContExports_004030E4;
extern void func_selection_00415CA0(s32);
void selectionResetTransientWords(void);
extern s32 D_8002CC64;
extern s32 D_8002CD54;
extern s32 D_8002CD58;
extern s32 D_8002CD5C;
extern s32 D_8002CD60;
extern s32 D_8002CD64;
extern s32 D_8002CD68;
extern s32 D_8002CD6C;
extern s32 D_8002CD70;
extern s32 D_selection_0041FF9C;
typedef struct UnkSelectionObj_s {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x220 - 0x2];
    /* 0x220 */ s32 unk220;
} UnkSelectionObj;
typedef struct UvGfxMgrExp_0040372C_s {
    /* 0x00 */ char pad0[0x74];
    /* 0x74 */ void (*unk74)(void);
} UvGfxMgrExp_0040372C;
typedef struct UvTexAnim_Exports_s {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ void (*unk8)(void);
} UvTexAnim_Exports;
typedef struct UvTerra_Exports_s {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ void (*unk8)(s16, s32);
} UvTerra_Exports;
typedef struct UvEnv_Exports_s {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ void (*unk18)(s16, s32);
} UvEnv_Exports;
extern void func_selection_00416A50(s32, s32);
extern UnkSelectionObj **D_selection_00421D18;
extern UvGfxMgrExp_0040372C *gUvGfxMgrExports;
extern UvTexAnim_Exports *gUvTexAnimExports;
extern UvTerra_Exports *gUvTerraExports;
extern UvEnv_Exports *gUvEnvExports;
extern s32 D_selection_00421E40;
typedef struct UnkContExports_s {
    /* 0x00 */ char pad0[0x5C];
    /* 0x5C */ void (*unk5C)(s32, s32);
} UnkContExports;
extern UnkContExports *gUvContExports;
typedef struct UvString_Exports4_s {
    char pad0[0x10];
    void (*unk10)(char *, char *, s32, s32);
} UvString_Exports4;
typedef struct D_selection_004217C8_entry_s {
    s32 unk0;
    s32 unk4;
    char pad8[0x2C - 0x8];
} D_selection_004217C8_entry;
extern UvString_Exports4 *gUvStringExports;
extern D_selection_004217C8_entry D_selection_004217C8[];
extern char D_selection_0041EEA0[];
void func_selection_00410E78(s32, s32, char *);
typedef struct {
    s32 text;
    s8  pad[0x28];
} SelectionLangEntry; /* sizeof == 0x2C */

extern SelectionLangEntry D_selection_004217F0[];
extern s32 gOptionsLanguage;
typedef struct UvSprt_Exports_s {
    char pad0[0x8];
    void (*unk8)(s16);
} UvSprt_Exports;
void func_selection_00404888(void);
typedef struct {
    char pad0[0xE0];
    void (*unkE0)(s32);
} SndExports_sel3D24;
typedef struct {
    char pad0[0x3C];
    void (*unk3C)(s32);
} SndExports_sel3D24b;
typedef struct {
    char pad0[0x34];
    void (*unk34)(s32 *, s32, s32, s32, s32);
} SelectionCtrl3D24;
extern SelectionCtrl3D24 *D_selection_00421B90;
extern s32 gOptionsMusicVol;
void selectionPlayRaceModeVoice(s32 option);
extern s32 D_selection_0041FC38;
typedef struct SelLeaf_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char pad4[0x12];
    /* 0x16 */ s16 unk16;
} SelLeaf;
typedef struct SelNodeData_s {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ SelLeaf *unk8;
} SelNodeData;
typedef struct SelNode_s {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ struct SelNode_s *unk4;
    /* 0x08 */ SelNodeData *unk8;
} SelNode;
void func_selection_00415CA0(s32);
extern SelNode D_selection_0041FBB4;
extern SelNode D_selection_0041FCF0;
typedef struct {
    char pad0[0xE0];
    void (*unkE0)(s32);
} SndExports_sel2E98;
typedef struct SelectionState2E98_s {
    char pad0[0x14];
    s16 unk14;
} SelectionState2E98;
extern SelectionState2E98 D_selection_0041F808;
extern void (*D_selection_00420F18[])(void);
extern SelectionState2E98 *D_selection_00421D20;
extern s32 D_selection_00421240[];
extern s16 D_selection_00421E08;
extern s32 D_selection_00420E24;
extern s32 D_selection_004201BC;
extern s32 D_selection_00421768;
extern s32 D_selection_0042176C[];
extern s8 D_selection_00421CF3;
extern s8 D_selection_00421CFB;
extern s8 D_selection_00421D03;
extern s8 D_selection_00421D0B;
extern s8 D_selection_00421DF4;
extern s8 D_selection_00421DF5;
extern s8 D_selection_00421DF6;
extern s8 D_selection_00421DF7;
typedef struct { char pad0[0xF4]; void (*unkF4)(u8); } UnkSndExports_sel;
typedef struct { char pad0[8]; void (*unk8)(s16); } UnkUvSprtExports_sel;
typedef struct { char pad0[0x7C]; s16 (*unk7C)(void); } UnkUvEmitterExports_sel;
extern UnkSndExports_sel *gSndExports;
extern UnkUvSprtExports_sel *gUvSprtExports;
extern UnkUvEmitterExports_sel *gUvEmitterExports;
extern u8 gOptionsStereoMono;
extern u8 gOptionsSpeed;
extern u8 gOptionsMap;
extern u8 gOptionsDisplay;
extern u8 D_80025E6A;
extern s32 gNumPlayers;
extern s32 gNumAiCars;
extern u8 gTransmissionType;
extern s32 D_80025E70;
extern s16 D_selection_00420DF0;
extern s16 D_selection_00420DFC;
extern s16 D_selection_00420DF8;
extern s32 D_selection_00421CE0;
extern void *D_selection_00421D1C;
extern s32 D_selection_00421D28;
extern s32 D_selection_00420E18;
extern s32 D_selection_00420E1C;
extern s32 D_selection_0041FC80;
extern s32 D_selection_0041FF2C;
extern s32 D_selection_0041FD74;
extern s32 D_selection_0041F770;
extern s32 D_selection_00420104;
extern s32 D_selection_0041FED0;
extern s32 D_selection_0041F94C;
extern s32 D_selection_0041FB58;
extern s32 D_selection_0041F994;
extern s32 D_selection_0041F904;
extern s32 D_selection_0041FE04;
extern s32 D_selection_0041FFE4;
extern s32 D_selection_00420218;
extern s32 D_selection_00420074;
extern s32 D_selection_0041F728;
extern s32 D_selection_00420260;
extern s32 D_selection_00420E90;
extern s32 D_selection_00420E84;
extern s32 D_selection_00420E74;
extern s32 D_selection_00420E78;
extern s32 D_selection_00420E70;
extern s32 D_selection_0041F5B4;
extern s32 D_selection_00421BA0;
extern s8 D_selection_00420DE8;
extern s16 D_selection_00420DEC;
extern s16 D_8002CC84;
extern s32 gCheatBattleNumLadybugs;
extern s32 gCheatBattleLadybugColor;
extern s32 gCheatBattleHealth;
extern s32 gCheatBattlePowerups;
extern s32 gCheatBattleTimeLimit;
extern s32 gCheatBattleRadar;
extern s32 gCheatBattleDamage;
extern s32 gCheatBattleMysteryBoxMode;
extern s32 gCheatTimeAttackBonusBoxes;
extern s32 gCheatBreakables;
extern s32 gCheatEnvironment;
extern s32 gCheatCars;
extern s32 gCheatPlayer2Handicap;
extern s32 gCheatColorChange;
extern s32 gCheatFieldOfView;
extern s32 gCheatHornSfxId;
extern s32 gCheatTrackMusic;
extern s32 gCheatHandbreakPower;
void func_selection_004000E4();
void selectionDrawCurrentMenuAndConditionalOverlay();
void func_selection_00400580();
void func_selection_004008B0();
void selectionRegisterChannelCallback(s32 channel);
void func_selection_004015D4();
void func_selection_004016CC();
void func_selection_004017E0();
void func_selection_0040189C();
void selectionAdjustWrappedMenuValue();
void selectionAdjustWrappedMenuShort(s16 *value, s32 minimum, s32 maximum);
void selectionAdjustWrappedMenuByte(u8 *value, s32 minimum, s32 maximum);
void selectionApplyLatchedMenuActionWords();
void func_selection_00401D04();
void func_selection_00401FB0();
void func_selection_00402254();
void func_selection_00402588();
void func_selection_00402994();
void selectionStartTwoPlayerMode(void);
void func_selection_004031E8();
void func_selection_00403220();
void func_selection_00403254();
void func_selection_00403284();
void func_selection_004032BC();
void func_selection_00403338();
void selectionChooseTournament0();
void selectionChooseTournament1();
void selectionChooseTournament2();
void selectionChooseTournament3();
void func_selection_004038E0();
void func_selection_0040390C();
void selectionPreparePlayerOneMenu(void);
void selectionOpenMenuPreservingOrigin();
void func_selection_00403A38();
void func_selection_00403A64();
void func_selection_00403A9C();
void selectionOpenMenuPreservingReturnNode(void);
void func_selection_00403B40();
void selectionChoose2Players();
void selectionChoose3Players();
void selectionChoose4Players();
void selectionApplyStereoMonoOption();
void selectionAdjustSpeedOption();
void func_selection_00403E04();
void selectionAdjustOptionsMap();
void selectionAdjustDisplayOption();
void selectionAdjustLanguageAndReloadTextures(void);
void func_selection_0040437C();
void selectionAdjustCheatBattleNumLadybugs();
void selectionAdjustCheatBattleLadybugColor();
void selectionAdjustCheatBattleHealth();
void selectionAdjustCheatBattlePowerups();
void selectionAdjustCheatBattleTimeLimit();
void selectionAdjustCheatBattleRadar();
void selectionAdjustCheatBattleDamage();
void selectionAdjustCheatBattleMysteryBoxMode();
void selectionAdjustCheatTimeAttackBonusBoxes();
void selectionAdjustCheatBreakables();
void selectionAdjustCheatEnvironment();
void selectionAdjustCheatCars();
void selectionAdjustCheatPlayer2Handicap();
void selectionAdjustCheatColorChange();
void selectionAdjustCheatFieldOfView();
void func_selection_00404888();
void func_selection_004048D8();
void selectionAdjustCheatHornSound();
void selectionAdjustCheatTrackMusic();
void selectionAdjustCheatHandbreakPower();
void func_selection_00404B2C();
void func_selection_00404C24();
void func_selection_00405140();
void func_selection_00405644();
void func_selection_00405CB0();
void func_selection_00405E38();
void func_selection_00405F48();
void selectionAdjustSelectedPlayerTransmission();
void func_selection_0040611C();
void func_selection_004062F8();
void func_selection_00406924();
void func_selection_00406DC4();
void func_selection_00406F80();
void func_selection_0040705C();
void func_selection_004078D4();
void func_selection_00407AF8();
void selectionUnloadFourPlayerTerrainPreview(void);
void selectionUpdateFourSlotStatesAndPivot(void);
void func_selection_00408304();
void func_selection_004083DC();
void func_selection_0040884C();
void func_selection_00408BEC();
void func_selection_004092F0();
void func_selection_004099A0();
void func_selection_00409C94();
void func_selection_00409EA4();
void func_selection_0040A104();
void func_selection_0040A5E0();
void selectionStoreTextAndUnloadPreview(void);
void func_selection_0040A820();
void func_selection_0040B070();
void func_selection_0040B144();
void selectionUpdateMenuAndPlayerObjects(void);
void func_selection_0040B534();
void func_selection_0040B608();
void selectionApplyNegativeTenRotationOffset(void);
void func_selection_0040B74C();
void func_selection_0040BB14();
void selectionAdjustThreeWayMenuChoice();
/* Wait for graphics and release shared texture-animation storage, then
 * adjust the track choice through the last unlocked index, capped at five.
 * On a change, replace three UVBT assets and their sprites in original order.
 * Center the two property-three-disabled sprites at X=160 and Y=208-height;
 * center the property-three-enabled sprite at (160,120). Preserve every
 * repeated shared-index read and the original property lists.
 * RE_UNKNOWN: the three images' presentation roles and property-three flag's
 * complete drawing contract require asset/draw-path evidence. */
void selectionAdjustTrackAndReloadPreviewSprites(void);
void func_selection_0040C454();
void selectionChooseSevenAiRace();
void selectionChooseOneAiRace();
void selectionChooseNoAiRace();
void selectionChooseMenuMode0();
void selectionChooseMenuMode1();
void selectionChooseMenuMode2();
void selectionChooseMenuMode3();
void func_selection_0040CBEC();
void selectionSetPlayerTransmissionOne();
void selectionSetPlayerTransmissionZero();
void func_selection_0040D280();
void func_selection_0040D514();
void selectionApplyRecordPreset(s32 option);
void func_selection_0040D9F8();
void func_selection_0040F294();
void func_selection_0040F4BC();
void func_selection_0040F6E0();
void func_selection_0040F704();
void func_selection_0040F9EC();
void func_selection_0040FDB4();
void func_selection_004103CC();
void func_selection_00410614();
void func_selection_0041088C();
void func_selection_00410AA8();
void func_selection_00410E78();
void func_selection_0041129C();
void func_selection_004114A0();
void func_selection_004116E0();
void func_selection_00411870();
void func_selection_00411B9C();
void func_selection_00411F40();
void selectionSetRecordValueAndActivate(s32 index, s32 context, u16 value);
void func_selection_004134F4();
void func_selection_00413568();
void func_selection_00413594();
void selectionLoadPakFileAndShowResult(void);
void func_selection_0041378C();
void func_selection_004137D0();
void func_selection_00413A88();
void selectionDeleteSharedSprite();
void func_selection_00413E1C();
void func_selection_00413E48();
void func_selection_00413FC4();
void selectionDrawFilledRectangleOrSteppedBorder(s32 indent, s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 red, s32 green, s32 blue, s32 alpha);
void func_selection_00414CF4();
void func_selection_00415040();
void func_selection_0041532C();
void func_selection_004155A0();
void func_selection_004159FC();
void selectionRequestIntroOrGameState();
void selectionPlayGatedVoice(s16 soundId, s32 *gate);
void selectionPlayGatedVoiceBC();
void selectionPlayGatedVoiceE4();
void selectionPlayGatedVoice7B();
void func_selection_00415CA0();
void selectionPlayRaceModeVoice();
void selectionPlayGatedVoiceB5();
void selectionPlayGatedVoiceB6();
void selectionPlayTournamentVoice(s32 option);
void selectionPlayAiRacePresetVoice(s32 option);
void selectionApplySoundOptions();
void selectionPlayPlayerCountVoiceIndex(s32 option);
void func_selection_00416028();
void func_selection_0041639C();
void selectionRotatePreviewAroundPoint(f32 x, f32 z, s32 unused, f32 angle);
void func_selection_00416A50();
void func_selection_00416ABC();
void selectionRepairControllerPak(void);
void func_selection_00416F28();
s32 selectionWritePakSettingsBlock(void);
s32 func_selection_00416FF4(s32 file);
void selectionRememberPakDeleteSelection();
void func_selection_004172B4();
void func_selection_004177A8();
void func_selection_004181D0();
void func_selection_0041844C();
void func_selection_00418800();
void func_selection_00418E98();
void selectionResetTransientWords();
void func_selection_00419084();
void func_selection_00419194();
void func_selection_00419384();
void func_selection_00419B78();
void func_selection_00419B9C();
void func_selection_00419BC8();
void func_selection_00419D54();
void selectionLatchMenuActionsWithRecordGuard();
void func_selection_0041A210();
void func_selection_0041A244();
void func_selection_0041A5BC();
void func_selection_0041A7D0();
void func_selection_0041A960();
f32 selectionComposeTimeScalar(s32 arg0, s32 arg1, s32 arg2);
void selectionApplyChosenLanguageAndReloadTextures(void);
void selectionChooseLanguage1AndSpeedOption();
void selectionChooseLanguage2AndSpeedOption();
void func_selection_0041B28C();
void func_selection_0041B370();
extern s32 D_selection_00420E28;
extern s32 D_selection_0041F794;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/__entrypoint_func_selection_400000.s")

#line 703 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_004000DC(void) {
}
#line 705 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004000E4.s")

#line 708 "src/modules/selection.c"
/* Draw the current node through its signed callback-table index at offset
 * 0x12, then pass the freshly loaded node and highlight word 1 to MENU slot
 * 0x14. Preserve the original seven address exclusions and conditional direct
 * drawing helpers, reloading the shared node after each effectful call at the
 * same points as the native routine. Flush queued FONT text even when the
 * initial node is null. If the original unsigned byte is nonzero, call MENU
 * slot 0x24 with words 0, 240, 320, 0, 0, 0, 0 and the signed shared halfword.
 * RE_UNKNOWN: complete node/export declarations, callback-table extent and
 * valid signed index; callback and provider effects, ownership, aliasing,
 * initialization/reset ordering and pointer lifetimes; physical meanings of
 * the address classes and overlay controls. Trace original node/table/control
 * producers, callbacks and all callers before strengthening these contracts.
 * The focused node view proves only the halfword access at offset 0x12.
 * RE_ORIGINAL_QUIRK: callback indexing is unchecked and the node is used after
 * callbacks without another null test. Retained drawing helpers also assume
 * handled shared mode/selector domains before reading their local scratch.
 * Invalid-domain and failure reachability remain unproved; no runtime fix or
 * confirmed player fault is claimed. */
void selectionDrawCurrentMenuAndConditionalOverlay(void) {
    void *currentNode;

    if (D_selection_00421D1C != NULL) {
        D_selection_00420F18[
            ((SelectionDrawNodeView *)D_selection_00421D1C)->drawCallbackIndex12]();
        ((SelectionDrawMenuExports *)D_selection_00421B90)->drawNode(
            D_selection_00421D1C, 1);
        currentNode = D_selection_00421D1C;
        if (currentNode != &D_selection_0041F770 &&
            currentNode != &D_selection_0041F5B4 &&
            currentNode != &D_selection_0041F728 &&
            currentNode != &D_selection_00420160 &&
            currentNode != &D_selection_004201BC &&
            currentNode != &D_selection_00420218 &&
            currentNode != &D_selection_004202E4) {
            func_selection_00416ABC();
            if (D_selection_00421D1C != &D_selection_00420260) {
                func_selection_00413FC4();
                currentNode = D_selection_00421D1C;
            } else {
                func_selection_0041A244();
                currentNode = D_selection_00421D1C;
            }
        }
        if (currentNode == &D_selection_0041FE60) {
            func_selection_0041844C();
            currentNode = D_selection_00421D1C;
        }
        if (currentNode == &D_selection_0041FDBC ||
            currentNode == &D_selection_0041FE04) {
            selectionRenderSharedSpritePair();
        }
    }
    ((UvFontExp_00411038 *)gUvFontExports)->unk28();
    if (*(u8 *)&D_selection_00420DE8 != 0) {
        ((SelectionDrawMenuExports *)D_selection_00421B90)->drawRectangle(
            0, 240, 320, 0, 0, 0, 0, D_selection_00420DEC);
    }
}
#line 709 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00400580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004008B0.s")

#line 648 "src/modules/selection.c"
/* Register the selection callback at priority 5 when channel query 6 returns
 * a callback list. A missing list needs no registration. */
void func_selection_004015D4(s32 channel);             /* extern */

void selectionRegisterChannelCallback(s32 channel) {
    CallbackList *callbacks;

    gUvChanExports->uvChannelGetProperties(channel, 6, &callbacks, 0);
    if (callbacks != NULL) {
        gUvCbckExports->uvAddCallback(callbacks, func_selection_004015D4, NULL, 5);
    }
}
#line 649 "src/modules/selection.c"

/* Dispatch on the original unsigned halfword selector: 0 does no work,
 * 4 calls the shared sprite/state helper, 3 fills with RGB words 255, 255,
 * 255, and 2 binds texture word 4 then reloads STAT before the rectangle
 * call with integer words 0, 320, 0, 240 and f32 words 0, 1, 0, 1.
 * Selector 1 and values outside 0 through 4 fill with RGB words 0, 0, 0.
 * Five original readonly words and their TEXT relocations prove this map.
 * The incoming callback word is homed but otherwise unused.
 * RE_UNKNOWN: complete historical callback/export declarations, selector
 * meaning and writer domain, resource availability and shared-pointer/state
 * initialization, reset and lifetime contracts. Trace original writers,
 * callback registration/invocation and provider initialization to resolve.
 * The original calls do not test provider/resource failure; invalid-domain
 * reachability is unproved. No reachable fault or runtime fix is claimed.
 * Recovery remains deferred: native 248 bytes versus draft 244 bytes,
 * with 44 differing words and changed relocation sites. All observed call
 * effects remain represented; the compiler uses comparisons instead of the
 * original five-entry jump table and hoists provider address construction.
 * Historical source/lowering evidence is needed before another attempt;
 * retain original ASM and readonly ownership without shape variants. */
#line 650 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004015D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004016CC.s")

#line 654 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_004017C8(void) {
}
#line 656 "src/modules/selection.c"

#line 657 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_004017D0(void) {
}
#line 659 "src/modules/selection.c"

#line 660 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_004017D8(void) {
}
#line 662 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004017E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040189C.s")

#line 667 "src/modules/selection.c"
/* Adjust a numeric menu value on a newly active horizontal action.
 * Action one decrements and wraps below minimum to maximum; action two
 * increments and wraps above maximum to minimum. Cache the current action
 * even when unchanged. RE_UNKNOWN: initial value/index/limit validity need callers. */
void selectionAdjustWrappedMenuValue(s32 *value, s32 minimum, s32 maximum) {
    s32 action = ((SelectionValueInputExports *)D_selection_00421B90)->get(D_selection_00420DF0, D_selection_00421D1C);
    if (D_selection_004213E8[D_selection_00420DF0] == 0) {
        if (action == 1) {
            *value = *value - 1;
            if (*value < minimum) *value = maximum;
        } else if (action == 2) {
            *value = *value + 1;
            if (maximum < *value) *value = minimum;
        }
    }
    D_selection_004213E8[D_selection_00420DF0] = action;
}
#line 668 "src/modules/selection.c"

#line 669 "src/modules/selection.c"
/* Adjust a signed 16-bit menu value when its previous horizontal action is zero.
 * Store/narrow each step before comparing inclusive limits, then cache the action.
 * RE_UNKNOWN: valid controller/index and representable ordered limits need original caller/producer evidence. */
void selectionAdjustWrappedMenuShort(s16 *value, s32 minimum, s32 maximum) {
    s32 action = ((SelectionValueInputExports *)D_selection_00421B90)->get(D_selection_00420DF0, D_selection_00421D1C);
    if (D_selection_004213F8[D_selection_00420DF0] == 0) {
        if (action == 1) {
            *value -= 1;
            if (*value < minimum) *value = maximum;
        } else if (action == 2) {
            *value += 1;
            if (maximum < *value) *value = minimum;
        }
    }
    D_selection_004213F8[D_selection_00420DF0] = action;
}
#line 670 "src/modules/selection.c"

#line 671 "src/modules/selection.c"
/* Adjust a byte menu value on a newly active horizontal action. Decrement
 * wraps at the minimum; increment narrows to a byte before checking maximum.
 * Cache every action. RE_UNKNOWN: controller/index/limit and pointed-byte storage domains need original callers/producers. */
void selectionAdjustWrappedMenuByte(u8 *value, s32 minimum, s32 maximum) {
    s32 action = ((SelectionValueInputExports *)D_selection_00421B90)->get(D_selection_00420DF0, D_selection_00421D1C);
    s32 current;
    if (D_selection_00421408[D_selection_00420DF0] == 0) {
        if (action == 1) {
            current = *value;
            if (minimum == current) *value = maximum;
            else *value = current - 1;
        } else if (action == 2) {
            *value += 1;
            if (maximum < *value) *value = minimum;
        }
    }
    D_selection_00421408[D_selection_00420DF0] = action;
}
#line 672 "src/modules/selection.c"

#line 673 "src/modules/selection.c"
/* Clear the original shared halfword and byte, then ask the imported MENU
 * provider for its numeric action using controller word zero and the current
 * node's pointer at offset 0x08. Latch action 7 in byte 1 and action 8 in byte 0.
 * A new action 7 with nonzero node word 0x04 copies the first original callback
 * table word and sets shared words to 1 and 0, returning before the byte-0 reset.
 * A new action 8 copies the signed-index callback table word, stores byte 2 and
 * clears the original halfword. Other actions reset their corresponding latch.
 * Preserve the node reload after the provider returns and all original store order.
 * RE_UNKNOWN: complete node/latch declarations, table capacity and signed-index
 * range, callback-word consumers, latch initialization/reset and dependency
 * lifetimes. The original accesses prove only a 12-byte node prefix and two
 * adjacent latch bytes, not historical complete storage or ownership. Resolve
 * through original node/table producers, deferred-word consumers and all callers.
 * RE_ORIGINAL_QUIRK: the current node and provider are used without local null
 * tests; the signed table index is unchecked. Invalid-domain/failure reachability
 * remains unproved. No runtime change or confirmed player fault is claimed. */
void selectionApplyLatchedMenuActionWords(void) {
    s32 action;

    D_selection_00420DF0 = 0;
    D_selection_00420DE8 = 0;
    action = ((SelectionLatchedActionExports *) D_selection_00421B90)->getAction(
        0, ((SelectionActionNodeView *) D_selection_00421D1C)->records08);
    if (action == 7) {
        if (((u8 *) &D_selection_00421CF0)[1] == 0) {
            ((u8 *) &D_selection_00421CF0)[1] = 1;
            if (((SelectionActionNodeView *) D_selection_00421D1C)->word04 != 0) {
                D_selection_00421D28 = D_selection_00420F1C;
                D_selection_00421CDC = 1;
                D_selection_00421CE0 = 0;
                return;
            }
        }
    } else {
        ((u8 *) &D_selection_00421CF0)[1] = 0;
    }
    if (action == 8) {
        if (*(u8 *) &D_selection_00421CF0 == 0) {
            *(u8 *) &D_selection_00421CF0 = 1;
            D_selection_00421D28 = D_selection_00421240[D_selection_00421E08];
            D_selection_00420DE8 = 2;
            D_selection_00420DEC = 0;
        }
    } else {
        *(u8 *) &D_selection_00421CF0 = 0;
    }
}
#line 674 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401D04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401FB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402588.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402994.s")

#line 685 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00402D7C(void) {
}
#line 687 "src/modules/selection.c"

/* Follow the menu link between exit/entry callbacks, waiting for graphics and releasing shared texture-animation storage. */
#line 689 "src/modules/selection.c"
/* When the current menu has a link, run its exit callback, save it
 * as the previous menu and select the linked menu. Wait for graphics,
 * release shared texture-animation storage and run the new entry callback. */
void selectionNavigateToLinkedMenu(void) {
    if (*(void **)((u8 *)D_selection_00421D1C + 0x4) != NULL) {
        D_selection_00420F18[*(s16 *)((u8 *)D_selection_00421D1C + 0x16)]();
        D_selection_00421D20 = D_selection_00421D1C;
        D_selection_00421D1C = *(void **)((u8 *)D_selection_00421D1C + 0x4);
        gUvGfxMgrExports->unk74();
        gUvTexAnimExports->unk8();
        D_selection_00420F18[*(s16 *)((u8 *)D_selection_00421D1C + 0x14)]();
    }
}
#line 699 "src/modules/selection.c"

// Wait for requested graphics completion, release shared texture-animation storage, then call the current menu exit callback.
#line 701 "src/modules/selection.c"
/* Wait for requested graphics completion and release the shared
 * texture-animation array before calling the current menu exit callback. */
void selectionRunCurrentMenuExitCallback(void) {
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    D_selection_00420F18[*(s16 *)((u8 *)D_selection_00421D1C + 0x16)]();
}
#line 706 "src/modules/selection.c"

// Activate the menu node, suppress cancel/directional sounds for the special root node, then call its entry callback.
#line 708 "src/modules/selection.c"
/* Save the previous menu, activate the supplied node and run its entry callback.
 * Retain root sound suppression and the post-call reload. RE_UNKNOWN: complete node layout,
 * callback index/domain and mixed-view caller storage require original producer/caller proof. */
void selectionActivateMenuNode(SelectionState2E98 *node) {
    SelectionState2E98 *activeNode;

    if (D_selection_00421D1C != NULL) {
        D_selection_00421D20 = D_selection_00421D1C;
    }
    D_selection_00421D1C = node;
    activeNode = node;
    if (node == &D_selection_0041F808) {
        ((SndExports_sel2E98 *)gSndExports)->unkE0(0xE);
        ((SndExports_sel2E98 *)gSndExports)->unkE0(0xDB);
        activeNode = D_selection_00421D1C;
    }
    D_selection_00420F18[activeNode->unk14]();
}
#line 723 "src/modules/selection.c"

#line 724 "src/modules/selection.c"
/* With exactly two players, replace map mode one with mode two.
 * Request state five, then run the current menu exit callback. */
void selectionRequestRaceStateWithMapRestriction(void) {
    if (gGameSettings[0].numPlayers == 2 && gGameSettings[0].optionsMap == 1) {
        gGameSettings[0].optionsMap = 2;
    }
    gGameSettings[0].newGameState = 5;
    selectionRunCurrentMenuExitCallback();
}
#line 731 "src/modules/selection.c"

#line 732 "src/modules/selection.c"
/* Request state six and exit the current menu, then raise player
 * count to two and track ID to 17 only when each is smaller. Preserve
 * the callback-before-normalization order. */
void selectionRequestBattleStateWithMinimums(void) {
    gGameSettings[0].newGameState = 6;
    selectionRunCurrentMenuExitCallback();
    if (gGameSettings[0].numPlayers < 2) {
        gGameSettings[0].numPlayers = 2;
    }
    if (gGameSettings[0].currentTrack < 0x11) {
        gGameSettings[0].currentTrack = 0x11;
    }
}
#line 742 "src/modules/selection.c"

/* Initialize single-player selection state and wire up the active context node. */
void func_selection_00402FE4(void) {
    func_selection_00415CA0(0);
    selectionRunCurrentMenuExitCallback();
    D_selection_00421CE0 = 1;
    gGameSettings[0].numPlayers = 1;
    D_selection_0041FCF0.unk8->unk8->unk16 = 1;
    D_selection_0041FCF0.unk4 = &D_selection_0041FBB4;
    D_selection_0041FBB4.unk8->unk8->unk2 = 1;
    selectionActivateMenuNode(&D_selection_0041FBB4);
}

#line 755 "src/modules/selection.c"
/* Enter the two-player setup only when controller index one is available.
 * Otherwise reset transient selection state. Preserve the original state node,
 * AI count zero, player count two and opaque mode value three. */
void selectionStartTwoPlayerMode(void) {
    if (((SelectionControllerStatusExports *)gUvContExports)->test(1) == 0) {
        selectionResetTransientWords();
        return;
    }
    func_selection_00415CA0(1);
    selectionRunCurrentMenuExitCallback();
    D_selection_00421CE0 = 1;
    gGameSettings->numAiCars = 0;
    gGameSettings->numPlayers = 2;
    gGameSettings->unk6F74 = 3;
    D_selection_0041FCF4 = &D_selection_0041F808;
    selectionOpenMenuPreservingOrigin();
}
#line 756 "src/modules/selection.c"

/* Check controller presence, then either abort or initialize the selection screen. */
void func_selection_004030E4(void) {
    if (((UnkContExports_004030E4 *)gUvContExports)->unk8(1) == 0) {
        selectionResetTransientWords();
        return;
    }
    func_selection_00415CA0(2);
    D_8002CD54 = 0;
    D_8002CD64 = 0;
    D_8002CD58 = 0;
    D_8002CD68 = 0;
    D_8002CD5C = 0;
    D_8002CD6C = 0;
    D_8002CD60 = 0;
    D_8002CD70 = 0;
    selectionRunCurrentMenuExitCallback();
    D_selection_00421CE0 = 1;
    D_8002CC64 = 4;
    selectionActivateMenuNode(&D_selection_0041FF9C);
}

#line 778 "src/modules/selection.c"
/* Prepare the multiplayer menu, raise player count to two only when
 * smaller, then open the original multiplayer node. */
void selectionOpenMultiplayerMenuAtLeastTwo(void) {
    selectionRunCurrentMenuExitCallback();
    if (gGameSettings[0].numPlayers < 2) {
        gGameSettings[0].numPlayers = 2;
    }
    selectionActivateMenuNode(&D_selection_0041FFE4);
}
#line 785 "src/modules/selection.c"

void func_selection_004031E8(void) {
    func_selection_00415CA0(3);
    D_selection_00421CE0 = 0;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F904);
}

void func_selection_00403220(void) {
    D_selection_00421CE0 = 1;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FED0);
}

void func_selection_00403254(void) {
    D_selection_00421CE0 = 0;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F94C);
}

void func_selection_00403284(void) {
    selectionApplySoundOptions();
    D_selection_00421CE0 = 0;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F994);
}

void func_selection_004032BC(void) {
    D_selection_00421CE0 = 0;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FB58);
}

/* Set up num AI cars + unk6F74, then transition to D_selection_0041FC38 screen. */
void func_selection_004032EC(void) {
    selectionRunCurrentMenuExitCallback();
    gGameSettings[0].numAiCars = 7;
    gGameSettings[0].unk6F74 = 2;
    selectionPlayRaceModeVoice(1);
    selectionActivateMenuNode(&D_selection_0041FC38);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403338.s")

/* Tear down the selection screen: clear gfx/texanim, unload files, reset track object. */
void func_selection_0040372C(void) {
    func_selection_00416A50(0, 0);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55565452, 9);
    uvUnloadFile(0x5556454E, 0xB);
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
}

#line 841 "src/modules/selection.c"
/* Select tournament 0 with 3 races, play its voice and continue
 * through the original tournament menu helper. */
void selectionChooseTournament0(void) {
    selectionPlayTournamentVoice(0);
    gGameSettings->currentTournament = 0;
    gGameSettings->numTournRaces = 3;
    func_selection_004038E0();
}
#line 847 "src/modules/selection.c"

#line 848 "src/modules/selection.c"
/* Select tournament 1 with 4 races, play its voice and continue
 * through the original tournament menu helper. */
void selectionChooseTournament1(void) {
    selectionPlayTournamentVoice(1);
    gGameSettings->currentTournament = 1;
    gGameSettings->numTournRaces = 4;
    func_selection_004038E0();
}
#line 854 "src/modules/selection.c"

#line 855 "src/modules/selection.c"
/* Select tournament 2 with 5 races, play its voice and continue
 * through the original tournament menu helper. */
void selectionChooseTournament2(void) {
    selectionPlayTournamentVoice(2);
    gGameSettings->currentTournament = 2;
    gGameSettings->numTournRaces = 5;
    func_selection_004038E0();
}
#line 861 "src/modules/selection.c"

#line 862 "src/modules/selection.c"
/* Select tournament 3 with 6 races, play its voice and continue
 * through the original tournament menu helper. */
void selectionChooseTournament3(void) {
    selectionPlayTournamentVoice(3);
    gGameSettings->currentTournament = 3;
    gGameSettings->numTournRaces = 6;
    func_selection_004038E0();
}
#line 868 "src/modules/selection.c"

void func_selection_004038E0(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FC80);
}

void func_selection_0040390C(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FF2C);
}

#line 879 "src/modules/selection.c"
/* Reset transient menu resources, select shared mode one and play race-mode
 * voice zero. Copy the localized PLAYER 1 label, then enter the original node. */
void selectionPreparePlayerOneMenu(void) {
    selectionRunCurrentMenuExitCallback();
    D_8002CC64 = 1;
    selectionPlayRaceModeVoice(0);
    ((SelectionFormatExports *)gUvStringExports)->format(D_80025E40, D_selection_0041ECBC, D_selection_004207C4[D_80025E64]);
    selectionActivateMenuNode((SelectionState2E98 *)&D_selection_0041FCF0);
}
#line 880 "src/modules/selection.c"

#line 881 "src/modules/selection.c"
/* Preserve the return link for three recognized origin nodes. The second
 * recognized origin also runs the original reset helper before menu entry.
 * Other origins leave the return link unchanged. */
void selectionOpenMenuPreservingOrigin(void) {
    if (D_selection_00421D1C == &D_selection_0041FCF0) D_selection_0041FDC0 = &D_selection_0041FCF0;
    else if (D_selection_00421D1C == &D_selection_0041FD74) {
        selectionPlayGatedVoiceBC();
        D_selection_0041FDC0 = &D_selection_0041FD74;
    }
    else if (D_selection_00421D1C == &D_selection_0041F808) D_selection_0041FDC0 = &D_selection_0041F808;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode((SelectionState2E98 *)&D_selection_0041FDBC);
}
#line 882 "src/modules/selection.c"

void func_selection_00403A38(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FD74);
}

void func_selection_00403A64(void) {
    func_selection_00415CA0(4);
    D_selection_00421CE0 = 0;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FE04);
}

void func_selection_00403A9C(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F770);
}

#line 900 "src/modules/selection.c"
/* Preserve the current return node only for the three original recognized
 * menus, reset selection resources, then enter the shared destination menu.
 * Other origins keep the previously stored return pointer. */
void selectionOpenMenuPreservingReturnNode(void) {
    if (D_selection_00421D1C == &D_selection_0041FC80) D_selection_0041FE64 = &D_selection_0041FC80;
    else if (D_selection_00421D1C == &D_selection_0041FDBC) D_selection_0041FE64 = &D_selection_0041FDBC;
    else if (D_selection_00421D1C == &D_selection_0041FFE4) D_selection_0041FE64 = &D_selection_0041FFE4;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode((SelectionState2E98 *)&D_selection_0041FE60);
}
#line 901 "src/modules/selection.c"

void func_selection_00403B40(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_00420104);
}

#line 907 "src/modules/selection.c"
/* Select 2 players, play the corresponding count voice and open the
 * original shared multiplayer menu node. */
void selectionChoose2Players(void) {
    gNumPlayers = 2;
    selectionPlayPlayerCountVoiceIndex(0);
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FFE4);
}
#line 913 "src/modules/selection.c"

#line 914 "src/modules/selection.c"
/* Select 3 players, play the corresponding count voice and open the
 * original shared multiplayer menu node. */
void selectionChoose3Players(void) {
    gNumPlayers = 3;
    selectionPlayPlayerCountVoiceIndex(1);
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FFE4);
}
#line 920 "src/modules/selection.c"

#line 921 "src/modules/selection.c"
/* Select 4 players, play the corresponding count voice and open the
 * original shared multiplayer menu node. */
void selectionChoose4Players(void) {
    gNumPlayers = 4;
    selectionPlayPlayerCountVoiceIndex(2);
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041FFE4);
}
#line 927 "src/modules/selection.c"

/* Suppress confirmation audio, adjust the speech-volume option through the menu helper, then apply its value. */
#line 929 "src/modules/selection.c"
/* Suppress confirmation sound 0xAB, adjust speech volume with the
 * original eight-step menu helper on channel zero, then immediately
 * apply the resulting speech volume to the sound module. */
void selectionAdjustAndApplySpeechVolume(void) {
    ((UnkSndExports_00403C2C *)gSndExports)->unkE0(0xAB);
    D_selection_00421B90->unk34(&gOptionsSpeechVol, 8, 1, 0, D_selection_00421D1C);
    ((UnkSndExports_00403C2C *)gSndExports)->unk44(gOptionsSpeechVol);
}
#line 934 "src/modules/selection.c"

/* Suppress confirmation audio, adjust the SFX option and apply its new volume. */
#line 936 "src/modules/selection.c"
/* Suppress confirm sound 0xAB, adjust the sound-effect volume through
 * the original eight-step option helper on channel one, then immediately
 * apply the resulting volume to the sound module. */
void selectionAdjustAndApplySfxVolume(void) {
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xAB);
    (*(void (**)(s32 *, s32, s32, s32, void *))((u8 *)D_selection_00421B90 + 0x34))(&gOptionsSfxVol, 8, 1, 1, D_selection_00421D1C);
    (*(void (**)(s32))((u8 *)gSndExports + 0x40))(gOptionsSfxVol);
}
#line 941 "src/modules/selection.c"

// Suppress confirmation audio, adjust the music-volume option through the menu helper, then apply its value.
#line 943 "src/modules/selection.c"
/* Suppress confirmation sound 0xAB, adjust music volume with the
 * original eight-step menu helper on channel two, then immediately
 * apply the resulting music volume to the sound module. */
void selectionAdjustAndApplyMusicVolume(void) {
    ((SndExports_sel3D24 *)gSndExports)->unkE0(0xAB);
    D_selection_00421B90->unk34(&gOptionsMusicVol, 8, 1, 2, D_selection_00421D1C);
    ((SndExports_sel3D24b *)gSndExports)->unk3C(gOptionsMusicVol);
}
#line 948 "src/modules/selection.c"

#line 949 "src/modules/selection.c"
/* Adjust the stereo/mono setting through the selection helper and
 * immediately apply the resulting value to the sound module. */
void selectionApplyStereoMonoOption(void) {
    func_selection_0040189C(&gOptionsStereoMono);
    gSndExports->unkF4(gOptionsStereoMono);
}
#line 953 "src/modules/selection.c"

#line 954 "src/modules/selection.c"
/* Pass the shared speed-option byte to the original selection input
 * helper. RE_UNKNOWN: the speed-option unit meaning remains unproven. */
void selectionAdjustSpeedOption(void) {
    func_selection_0040189C(&gOptionsSpeed);
}
#line 957 "src/modules/selection.c"

void func_selection_00403E04(void) {
    func_selection_0040189C(&D_80025E6A);
}

#line 962 "src/modules/selection.c"
/* Apply the current horizontal menu action to gOptionsMap within zero
 * through 2, wrapping at either endpoint through the shared input latch. */
void selectionAdjustOptionsMap(void) {
    selectionAdjustWrappedMenuByte(&gOptionsMap, 0, 2);
}
#line 965 "src/modules/selection.c"

#line 966 "src/modules/selection.c"
/* Pass the shared display-option byte to the original selection
 * input helper, preserving its existing input and latching behavior. */
void selectionAdjustDisplayOption(void) {
    func_selection_0040189C(&gOptionsDisplay);
}
#line 969 "src/modules/selection.c"

#line 970 "src/modules/selection.c"
/* Wrap the selected language through IDs zero to two. On change, wait for
 * graphics before unloading the old thirteen textures and loading the new
 * thirteen in their original order. Set the associated option byte to one
 * for language zero and zero for the other two. The settings member and
 * D_80025E64 alias the same word; retain reloads after resource operations. */
void selectionAdjustLanguageAndReloadTextures(void) {
    s32 previousLanguage;
    s32 language;
    previousLanguage = gGameSettings->currentLanguage;
    selectionAdjustWrappedMenuValue(&D_80025E64,0,2);
    language = D_80025E64;
    if (previousLanguage != language) {
        switch (previousLanguage) {
        case 0:
            gUvGfxMgrExports->unk74();
            uvUnloadFile('UVTX',0x31);
            uvUnloadFile('UVTX',0x4A);
            uvUnloadFile('UVTX',0x6);
            uvUnloadFile('UVTX',0x3C);
            uvUnloadFile('UVTX',0x14);
            uvUnloadFile('UVTX',0x4B);
            uvUnloadFile('UVTX',0x1C);
            uvUnloadFile('UVTX',0x41);
            uvUnloadFile('UVTX',0x3F);
            uvUnloadFile('UVTX',0x44);
            uvUnloadFile('UVTX',0x15);
            uvUnloadFile('UVTX',0x18);
            uvUnloadFile('UVTX',0x56F);
            language = D_80025E64;
            break;
        case 1:
            gUvGfxMgrExports->unk74();
            uvUnloadFile('UVTX',0x57C);
            uvUnloadFile('UVTX',0x5A1);
            uvUnloadFile('UVTX',0x58D);
            uvUnloadFile('UVTX',0x599);
            uvUnloadFile('UVTX',0x58F);
            uvUnloadFile('UVTX',0x5A3);
            uvUnloadFile('UVTX',0x595);
            uvUnloadFile('UVTX',0x59F);
            uvUnloadFile('UVTX',0x591);
            uvUnloadFile('UVTX',0x593);
            uvUnloadFile('UVTX',0x597);
            uvUnloadFile('UVTX',0x59D);
            uvUnloadFile('UVTX',0x44);
            language = D_80025E64;
            break;
        case 2:
            gUvGfxMgrExports->unk74();
            uvUnloadFile('UVTX',0x57B);
            uvUnloadFile('UVTX',0x5A0);
            uvUnloadFile('UVTX',0x58C);
            uvUnloadFile('UVTX',0x598);
            uvUnloadFile('UVTX',0x58E);
            uvUnloadFile('UVTX',0x5A2);
            uvUnloadFile('UVTX',0x594);
            uvUnloadFile('UVTX',0x59E);
            uvUnloadFile('UVTX',0x590);
            uvUnloadFile('UVTX',0x592);
            uvUnloadFile('UVTX',0x596);
            uvUnloadFile('UVTX',0x59C);
            uvUnloadFile('UVTX',0x44);
            language = D_80025E64;
            break;
        }
        switch (language) {
        case 0:
            gUvGfxMgrExports->unk74();
            uvLoadFile('UVTX',0x31);
            uvLoadFile('UVTX',0x4A);
            uvLoadFile('UVTX',0x6);
            uvLoadFile('UVTX',0x3C);
            uvLoadFile('UVTX',0x14);
            uvLoadFile('UVTX',0x4B);
            uvLoadFile('UVTX',0x1C);
            uvLoadFile('UVTX',0x41);
            uvLoadFile('UVTX',0x3F);
            uvLoadFile('UVTX',0x44);
            uvLoadFile('UVTX',0x15);
            uvLoadFile('UVTX',0x18);
            uvLoadFile('UVTX',0x56F);
            D_80025E69 = 1;
            return;
        case 1:
            gUvGfxMgrExports->unk74();
            uvLoadFile('UVTX',0x57C);
            uvLoadFile('UVTX',0x5A1);
            uvLoadFile('UVTX',0x58D);
            uvLoadFile('UVTX',0x599);
            uvLoadFile('UVTX',0x58F);
            uvLoadFile('UVTX',0x5A3);
            uvLoadFile('UVTX',0x595);
            uvLoadFile('UVTX',0x59F);
            uvLoadFile('UVTX',0x591);
            uvLoadFile('UVTX',0x593);
            uvLoadFile('UVTX',0x597);
            uvLoadFile('UVTX',0x59D);
            uvLoadFile('UVTX',0x44);
            D_80025E69 = 0;
            break;
        case 2:
            gUvGfxMgrExports->unk74();
            uvLoadFile('UVTX',0x57B);
            uvLoadFile('UVTX',0x5A0);
            uvLoadFile('UVTX',0x58C);
            uvLoadFile('UVTX',0x598);
            uvLoadFile('UVTX',0x58E);
            uvLoadFile('UVTX',0x5A2);
            uvLoadFile('UVTX',0x594);
            uvLoadFile('UVTX',0x59E);
            uvLoadFile('UVTX',0x590);
            uvLoadFile('UVTX',0x592);
            uvLoadFile('UVTX',0x596);
            uvLoadFile('UVTX',0x59C);
            uvLoadFile('UVTX',0x44);
            D_80025E69 = 0;
            break;
        }
    }
}
#line 971 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040437C.s")

#line 974 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleNumLadybugs within zero
 * through 7, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleNumLadybugs(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleNumLadybugs, 0, 7);
}
#line 977 "src/modules/selection.c"

#line 978 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleLadybugColor within zero
 * through 3, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleLadybugColor(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleLadybugColor, 0, 3);
}
#line 981 "src/modules/selection.c"

#line 982 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleHealth within zero
 * through 3, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleHealth(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleHealth, 0, 3);
}
#line 985 "src/modules/selection.c"

#line 986 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattlePowerups within zero
 * through 8, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattlePowerups(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattlePowerups, 0, 8);
}
#line 989 "src/modules/selection.c"

#line 990 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleTimeLimit within zero
 * through 6, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleTimeLimit(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleTimeLimit, 0, 6);
}
#line 993 "src/modules/selection.c"

#line 994 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleRadar within zero
 * through 1, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleRadar(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleRadar, 0, 1);
}
#line 997 "src/modules/selection.c"

#line 998 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleDamage within zero
 * through 3, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleDamage(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleDamage, 0, 3);
}
#line 1001 "src/modules/selection.c"

#line 1002 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBattleMysteryBoxMode within zero
 * through 3, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBattleMysteryBoxMode(void) {
    selectionAdjustWrappedMenuValue(&gCheatBattleMysteryBoxMode, 0, 3);
}
#line 1005 "src/modules/selection.c"

#line 1006 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatTimeAttackBonusBoxes within zero
 * through 1, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatTimeAttackBonusBoxes(void) {
    selectionAdjustWrappedMenuByte(&gCheatTimeAttackBonusBoxes, 0, 1);
}
#line 1009 "src/modules/selection.c"

#line 1010 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatBreakables within zero
 * through 2, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatBreakables(void) {
    selectionAdjustWrappedMenuByte(&gCheatBreakables, 0, 2);
}
#line 1013 "src/modules/selection.c"

#line 1014 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatEnvironment within zero
 * through 2, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatEnvironment(void) {
    selectionAdjustWrappedMenuByte(&gCheatEnvironment, 0, 2);
}
#line 1017 "src/modules/selection.c"

#line 1018 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatCars within zero
 * through 6, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatCars(void) {
    selectionAdjustWrappedMenuByte(&gCheatCars, 0, 6);
}
#line 1021 "src/modules/selection.c"

#line 1022 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatPlayer2Handicap within zero
 * through 4, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatPlayer2Handicap(void) {
    selectionAdjustWrappedMenuByte(&gCheatPlayer2Handicap, 0, 4);
}
#line 1025 "src/modules/selection.c"

#line 1026 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatColorChange within zero
 * through 1, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatColorChange(void) {
    selectionAdjustWrappedMenuByte(&gCheatColorChange, 0, 1);
}
#line 1029 "src/modules/selection.c"

#line 1030 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatFieldOfView within zero
 * through 2, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatFieldOfView(void) {
    selectionAdjustWrappedMenuByte(&gCheatFieldOfView, 0, 2);
}
#line 1033 "src/modules/selection.c"

typedef struct
{
  char pad[0x8];
  void (*unk8)(u8);
} UvEmitterExp_00404888;
extern s32 D_selection_00420D94;
extern s32 D_selection_00420D98;

void func_selection_00404888(void)
{
  s32 slot = D_selection_00420D94;
  if (slot != (-1))
  {
    ((UvEmitterExp_00404888 *) gUvEmitterExports)->unk8((u8) slot);
  }
 do { D_selection_00420D94 = -1; } while (0);
  D_selection_00420D98 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004048D8.s")

#line 1055 "src/modules/selection.c"
/* Adjust the cheat horn sound byte from zero through the emitter module
 * limit using the original menu input and wrapping rules. */
void selectionAdjustCheatHornSound(void) {
    selectionAdjustWrappedMenuByte(&gCheatHornSfxId, 0, gUvEmitterExports->unk7C());
}
#line 1058 "src/modules/selection.c"

#line 1059 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatTrackMusic within zero
 * through 1, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatTrackMusic(void) {
    selectionAdjustWrappedMenuByte(&gCheatTrackMusic, 0, 1);
}
#line 1062 "src/modules/selection.c"

#line 1063 "src/modules/selection.c"
/* Apply the current horizontal menu action to gCheatHandbreakPower within zero
 * through 2, wrapping at either endpoint through the shared input latch. */
void selectionAdjustCheatHandbreakPower(void) {
    selectionAdjustWrappedMenuByte(&gCheatHandbreakPower, 0, 2);
}
#line 1066 "src/modules/selection.c"

#line 1067 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00404B24(void) {
}
#line 1069 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00404B2C.s")

#line 1072 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00404C1C(void) {
}
#line 1074 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00404C24.s")

/* Tear down the selection screen (variant B): reset gfx/texanim, clear object flag, unload terra/env, then unload files 0xA and 0xB. */
void func_selection_00405078(void) {
    func_selection_00416A50(0, 0);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
    uvUnloadFile(0x55565452, 0xA);
    uvUnloadFile(0x5556454E, 0xB);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405140.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405644.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405CB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405F48.s")

#line 1099 "src/modules/selection.c"
/* Adjust the selected player transmission option using the original
 * six-byte player stride. Preserve the caller-owned player index. */
void selectionAdjustSelectedPlayerTransmission(void) {
    func_selection_0040189C((u8*)gGameSettings + (s32)D_selection_00420DF0 * 6 + 0x13C);
}
#line 1102 "src/modules/selection.c"

#line 1103 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00406114(void) {
}
#line 1105 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040611C.s")

#line 1108 "src/modules/selection.c"
/* Save graphics state, set mask 0x4800000 and clear mask 0x600000,
 * render the shared selection sprite, then restore the graphics state. */
void selectionRenderSharedSpriteWithState(void) {
    gUvGfxStateExports->unk50();
    gUvGfxStateExports->unk0C(0x4800000);
    gUvGfxStateExports->unk10(0x600000);
    ((UvSprtLocal_0040626C *)gUvSprtExports)->unk10(D_selection_00420DF8);
    gUvGfxStateExports->unk54();
}
#line 1115 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004062F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00406924.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00406DC4.s")

#line 1122 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00406F78(void) {
}
#line 1124 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00406F80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040705C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004078D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00407AF8.s")

#line 1133 "src/modules/selection.c"
/* Reset all four player slots, flush graphics/texture animation, unload
 * terrain 0xB and environment zero, clear the selection object field 0x220,
 * then reset its terrain and environment bindings in the original order. */
void selectionUnloadFourPlayerTerrainPreview(void) {
    s32 player;
    player = 0;
    do {
        func_selection_00416A50(player, 0);
        player++;
    } while (player != 4);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile('UVTR', 0xB);
    uvUnloadFile('UVEN', 0);
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
}
#line 1134 "src/modules/selection.c"

#line 1135 "src/modules/selection.c"
/* Apply the current menu's 0/1/2 choice to four indexed slot states.
 * RE_UNKNOWN: the choice labels, the state helper's broader contract and
 * the dirty flag's consumers need their remaining callers decompiled.
 * Keep the menu reload after the input callback and after setting the flag. */
void selectionUpdateFourSlotStatesAndPivot(void) {
    s16 previousChoice;
    s16 currentChoice;
    s32 slot;

    previousChoice = ((AgentLanguageExpressionMenu *)D_selection_00421D1C)->choices->selected;
    func_selection_00401D04();
    currentChoice = ((AgentLanguageExpressionMenu *)D_selection_00421D1C)->choices->selected;
    if (previousChoice != currentChoice) {
        D_selection_00420E8C = 1;
        currentChoice = ((AgentLanguageExpressionMenu *)D_selection_00421D1C)->choices->selected;
    }
    switch (currentChoice) {
    case 0:
        for (slot = 0; slot < 2; slot++) func_selection_00416A50(slot, 1);
        for (slot = 2; slot != 4; slot++) func_selection_00416A50(slot, 0);
        break;
    case 1:
        for (slot = 0; slot < 3; slot++) func_selection_00416A50(slot, 1);
        for (slot = 3; slot != 4; slot++) func_selection_00416A50(slot, 0);
        break;
    case 2:
        for (slot = 0; slot != 4; slot++) func_selection_00416A50(slot, 1);
        break;
    }
    selectionRotateViewMatrixAroundPivot(D_selection_00421E60.x, D_selection_00421E60.y, -10.0f);
}
#line 1136 "src/modules/selection.c"

#line 1137 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_004082FC(void) {
}
#line 1139 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00408304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004083DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040884C.s")

#line 1146 "src/modules/selection.c"

/* RE_UNKNOWN: historical source statement organization in the bitmap loop.
 * Expanding the proven loop layout onto separate lines changes two original
 * instruction positions under the original compiler. Retain the verified
 * statement layout pending compiler/source evidence; no runtime fix is implied. */
/* Call the two shared callbacks without supplying explicit arguments, unload
 * UVBT file 0x26, pass the two signed-halfword sprite arguments through slot
 * 0x08, then unload each bitmap ID before the original end-address sentinel.
 * Keep the first sprite argument assignment and all callback/unload
 * ordering. RE_UNKNOWN: callback input contracts/lifecycle, sprite argument
 * roles and the ID range's allocation/ownership. Trace original slot
 * targets, ID writers and callers before changing release behavior or
 * treating the end label as a C array size. */
void selectionUnloadBitmapRangeAndForwardSpriteArguments(void)
{
  s32 bitmapTag;
  s16 *bitmapIdCursor;
  s16 firstSpriteArgument;
  gUvGfxMgrExports->unk74();
  gUvTexAnimExports->unk8();
  bitmapTag = 0x55564254;
  uvUnloadFile(bitmapTag, 0x26);
  gUvSprtExports->unk8(firstSpriteArgument = D_selection_00421E3A);
  gUvSprtExports->unk8(D_selection_00421E3C);
 bitmapIdCursor = &D_selection_00420D6C; do { uvUnloadFile(bitmapTag, *bitmapIdCursor);
    bitmapIdCursor += 1;
  }
  while (bitmapIdCursor != (&D_selection_00420D7E));
}
#line 1162 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00408BEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004092F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004099A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00409C94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00409EA4.s")

void func_selection_00409FC8(void) {
    s16 temp_v0;

    selectionApplySoundOptions();
    ((SndExp_409FC8 *)gSndExports)->unkE0(0xAB);
    ((SndExp_409FC8 *)gSndExports)->unkE0(0xE);
    ((SndExp_409FC8 *)gSndExports)->unkE0(0xC);
    ((SndExp_409FC8 *)gSndExports)->unkE0(0xDB);
    D_selection_00421E24 += 1;
    func_selection_004017E0();
    temp_v0 = D_selection_00421E24;
    if (temp_v0 == 4 || temp_v0 == 3) {
        selectionPrepareTransitionAndOptionalIntroReset(1);
        temp_v0 = D_selection_00421E24;
    }
    if (temp_v0 < 5) {
        return;
    }
    selectionRunCurrentMenuExitCallback();
    selectionPlayGatedVoice7B();
    ((SndExp_409FC8 *)gSndExports)->unk3C(gOptionsMusicVol);
    gUvCmidiExports->unk2C();
    ((SndExp_409FC8 *)gSndExports)->unk34(0);
    ((SndExp_409FC8 *)gSndExports)->unk38(0);
    selectionActivateMenuNode(&D_selection_0041F808);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A5E0.s")

#line 1204 "src/modules/selection.c"
/* Run the original selection reset and format shared text from the saved
 * text buffer. Wait for graphics, release texture-animation storage, unload bitmap zero,
 * release the preview sprite and set its handle to -1 in original order. */
void selectionStoreTextAndUnloadPreview(void) {
    func_selection_004017E0();
    ((SelectionFormatExports *)gUvStringExports)->format(D_80025E50, D_selection_0041ECF8, D_80025E40);
    ((UvGfxMgrExp_BEC8 *)gUvGfxMgrExports)->unk74();
    ((UvTexAnimExp_BEC8 *)gUvTexAnimExports)->unk8();
    uvUnloadFile(0x55564254, D_selection_00420D24[0]);
    gUvSprtExports->unk8(D_selection_00420DF8);
    D_selection_00420DF8 = -1;
}
#line 1205 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A820.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B070.s")

#line 1210 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_0040B13C(void) {
}
#line 1212 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B144.s")

#line 1215 "src/modules/selection.c"
/* Update the menu, mark a changed selection, and position its preview.
 * Update one object handle per configured player; handles are consecutive
 * four-byte words, and the player count is re-read after each callback. */
void selectionUpdateMenuAndPlayerObjects(void) {
    s16 previous;
    s32 *object;
    s32 index;
    previous = ((D1CTarget_0041B19C *)D_selection_00421D1C)->unk8->unk4;
    func_selection_00401D04();
    if (previous != ((D1CTarget_0041B19C *)D_selection_00421D1C)->unk8->unk4) D_selection_00420E7C = 1;
    selectionRotateViewMatrixAroundPivot(D_selection_00421E60.x, D_selection_00421E60.y, -10.0f);
    for (index = 0, object = D_selection_00421D48; index < gGameSettings->numPlayers; index++, object++) {
        D_selection_00421B8C->update(*object);
    }
}
#line 1216 "src/modules/selection.c"

#line 1217 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_0040B52C(void) {
}
#line 1219 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B534.s")

#line 1222 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_0040B600(void) {
}
#line 1224 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B608.s")

#line 1227 "src/modules/selection.c"
/* Apply the original (0, 0, -10) rotation offset. Distinct zero literal forms
 * preserve IDO's separate argument materialization without extra operations. */
void selectionApplyNegativeTenRotationOffset(void) {
    selectionRotateViewMatrixAroundPivot(0.0f, 0, -10.0f);
}
#line 1228 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B74C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040BB14.s")

#line 1233 "src/modules/selection.c"

void selectionUnloadIndexedBitmapsAndSprites(void) { /* Wait for requested graphics work, release the shared texture-animation array, unload three indexed UVBT files, clear three sprite states and invalidate the final shared sprite ID. RE_UNKNOWN: table-index and live-sprite validity require original setup/teardown callers. */
    gUvGfxMgrExports->unk74();
    ((UvTexAnimExp_BEC8 *)gUvTexAnimExports)->unk8();
    uvUnloadFile(0x55564254, D_selection_00420D3C[D_selection_00420E04]);
    uvUnloadFile(0x55564254, D_selection_00420D48[D_selection_00420E04]);
    uvUnloadFile(0x55564254, D_selection_00420D24[D_selection_00420E04]);
    gUvSprtExports->unk8(D_selection_00421E36);
    gUvSprtExports->unk8(D_selection_00421E34);
    gUvSprtExports->unk8(D_selection_00420DF8);
    D_selection_00420DF8 = -1;
}
#line 1244 "src/modules/selection.c"

#line 1245 "src/modules/selection.c"
/* Adjust the shared menu choice within zero through two using the
 * existing horizontal-action latch and endpoint wrapping. */
void selectionAdjustThreeWayMenuChoice(void) {
    selectionAdjustWrappedMenuValue(&D_80025E70, 0, 2);
}
#line 1248 "src/modules/selection.c"

#line 1249 "src/modules/selection.c"
/* Wait for graphics and release shared texture-animation storage, then
 * adjust the track choice through the last unlocked index, capped at five.
 * On a change, replace three UVBT assets and their sprites in original order.
 * Center the two property-three-disabled sprites at X=160 and Y=208-height;
 * center the property-three-enabled sprite at (160,120). Preserve every
 * repeated shared-index read and the original property lists.
 * Property three gates automatic drawing; explicit rendering bypasses it.
 * RE_UNKNOWN: the three images' presentation roles require asset evidence. */
/* Wait for graphics and release shared texture-animation storage, then
 * adjust the track choice through the last unlocked index, capped at five.
 * On a change, replace three UVBT assets and their sprites in original order.
 * Center the two property-three-disabled sprites at X=160 and Y=208-height;
 * center the property-three-enabled sprite at (160,120). Preserve every
 * repeated shared-index read and the original property lists.
 * Property three gates automatic drawing; explicit rendering bypasses it.
 * RE_UNKNOWN: the three images' presentation roles require asset evidence. */
void selectionAdjustTrackAndReloadPreviewSprites(void) {
    s32 lastUnlockedIndex;
    s32 halfWidth;
    s32 previousSelection;
    s32 lastSelectableIndex;

    lastUnlockedIndex = gNumOpenTracks - 1;
    if (lastUnlockedIndex >= 6) {
        lastSelectableIndex = 5;
    } else {
        lastSelectableIndex = lastUnlockedIndex;
    }
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8(); /* Release shared animation storage through slot 0x08. */
    previousSelection = D_selection_00420E04;
    selectionAdjustWrappedMenuValue(&D_selection_00420E04, 0, lastSelectableIndex);
    if (previousSelection != D_selection_00420E04) {
        uvUnloadFile(0x55564254, (s32) D_selection_00420D3C[previousSelection]);
        uvUnloadFile(0x55564254, (s32) D_selection_00420D48[previousSelection]);
        uvUnloadFile(0x55564254, (s32) D_selection_00420D24[previousSelection]);
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->clearState(D_selection_00421E36);
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->clearState(D_selection_00421E34);
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->clearState(D_selection_00420DF8);
        D_selection_00420DF8 = -1;
        uvLoadFile(0x55564254, (s32) D_selection_00420D3C[D_selection_00420E04]);
        uvLoadFile(0x55564254, (s32) D_selection_00420D48[D_selection_00420E04]);
        uvLoadFile(0x55564254, (s32) D_selection_00420D24[D_selection_00420E04]);
        D_selection_00421E36 = ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->allocate();
        D_selection_00421E34 = ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->allocate();
        D_selection_00420DF8 = ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->allocate();
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->setProperties(D_selection_00421E34, 9, D_selection_00420D3C[D_selection_00420E04], 0);
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->setProperties(D_selection_00421E36, 9, D_selection_00420D48[D_selection_00420E04], 0);
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->setProperties(D_selection_00420DF8, 9, D_selection_00420D24[D_selection_00420E04], 0);
        halfWidth = ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->getWidth(D_selection_00421E34) / 2;
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->setProperties(D_selection_00421E34, 2, 0xA0 - halfWidth, 0xD0 - ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->getHeight(D_selection_00421E34), 0xB, 1, 0xC, 0, 3, 0, 0);
        halfWidth = ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->getWidth(D_selection_00421E36) / 2;
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->setProperties(D_selection_00421E36, 2, 0xA0 - halfWidth, 0xD0 - ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->getHeight(D_selection_00421E36), 0xB, 1, 0xC, 0, 3, 0, 0);
        halfWidth = ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->getWidth(D_selection_00420DF8) / 2;
        ((AgentTrackPreviewSpriteExports *)gUvSprtExports)->setProperties(D_selection_00420DF8, 2, 0xA0 - halfWidth, 0x78 - (((AgentTrackPreviewSpriteExports *)gUvSprtExports)->getHeight(D_selection_00420DF8) / 2), 3, 1, 0);
    }
}
#line 1250 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040C454.s")

void func_selection_0040C96C(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_selection_00416A50(var_s0, 0);
        var_s0 += 1;
    } while (var_s0 != 8);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55565452, 0xB);
    uvUnloadFile(0x5556454E, 0);
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
}

/* Adjust AI-car count from zero through seven, then continue when the separate menu-action result is eight. */
#line 1271 "src/modules/selection.c"
/* Adjust the AI-car count across zero through seven. On menu action
 * eight, set the shared confirmation latch and open the original next
 * menu while preserving its origin. */
void selectionAdjustAiCountAndConfirm(void) {
    selectionAdjustWrappedMenuValue(&gNumAiCars, 0, 7);
    if (((Ctrl_0040CA50 *)D_selection_00421B90)->unk8(0, ((Data_0040CA50 *)D_selection_00421D1C)->unk8) == 8) {
        D_selection_00421CF0 = 1;
        selectionOpenMenuPreservingOrigin();
    }
}
#line 1278 "src/modules/selection.c"

#line 1279 "src/modules/selection.c"
/* Play AI-race preset zero, select seven AI cars and continue through
 * the original race selection helper. */
void selectionChooseSevenAiRace(void) {
    selectionPlayAiRacePresetVoice(0);
    gNumAiCars = 7;
    func_selection_00403A38();
}
#line 1284 "src/modules/selection.c"

#line 1285 "src/modules/selection.c"
/* Play AI-race preset one, select one AI car and continue through
 * the original race selection helper. */
void selectionChooseOneAiRace(void) {
    selectionPlayAiRacePresetVoice(1);
    gNumAiCars = 1;
    func_selection_00403A38();
}
#line 1290 "src/modules/selection.c"

#line 1291 "src/modules/selection.c"
/* Play AI-race preset two, select zero AI cars and shared value five,
 * then open the existing menu while preserving its origin. */
void selectionChooseNoAiRace(void) {
    selectionPlayAiRacePresetVoice(2);
    gGameSettings->numAiCars = 0;
    gGameSettings->unk6F74 = 5;
    selectionOpenMenuPreservingOrigin();
}
#line 1297 "src/modules/selection.c"

#line 1298 "src/modules/selection.c"
/* Set the shared menu mode to 0 and open the next menu while
 * preserving the current origin. Mode labels remain unproven. */
void selectionChooseMenuMode0(void) {
    D_80025E70 = 0;
    selectionOpenMenuPreservingOrigin();
}
#line 1302 "src/modules/selection.c"

#line 1303 "src/modules/selection.c"
/* Set the shared menu mode to 1 and open the next menu while
 * preserving the current origin. Mode labels remain unproven. */
void selectionChooseMenuMode1(void) {
    D_80025E70 = 1;
    selectionOpenMenuPreservingOrigin();
}
#line 1307 "src/modules/selection.c"

#line 1308 "src/modules/selection.c"
/* Set the shared menu mode to 2 and open the next menu while
 * preserving the current origin. Mode labels remain unproven. */
void selectionChooseMenuMode2(void) {
    D_80025E70 = 2;
    selectionOpenMenuPreservingOrigin();
}
#line 1312 "src/modules/selection.c"

#line 1313 "src/modules/selection.c"
/* Set the shared menu mode to 3 and open the next menu while
 * preserving the current origin. Mode labels remain unproven. */
void selectionChooseMenuMode3(void) {
    D_80025E70 = 3;
    selectionOpenMenuPreservingOrigin();
}
#line 1317 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040CBEC.s")

/* Teardown: destroy player instances, flush gfx/texanim, unload files, reset terra/env, cleanup. */
void func_selection_0040D134(void) {
    s32 var_s0;

    var_s0 = 0;
    if (gGameSettings->numPlayers > 0) {
        do {
            func_selection_00416A50(var_s0, 0);
            var_s0 += 1;
        } while (var_s0 < gGameSettings->numPlayers);
    }
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55565452, 0x3);
    uvUnloadFile(0x5556454E, 0x12);
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
    func_selection_004017E0();
}

#line 1341 "src/modules/selection.c"
/* Set the selected player transmission byte to one; preserve the original
 * six-byte player stride and caller-owned player index. */
void selectionSetPlayerTransmissionOne(void) {
    ((u8*)&gTransmissionType)[D_selection_00420DF0 * 6] = 1;
}
#line 1344 "src/modules/selection.c"

#line 1345 "src/modules/selection.c"
/* Set the selected player transmission byte to zero; preserve the original
 * six-byte player stride and caller-owned player index. */
void selectionSetPlayerTransmissionZero(void) {
    ((u8*)&gTransmissionType)[D_selection_00420DF0 * 6] = 0;
}
#line 1348 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D280.s")

/* Unload selection screen resources: flush gfx/texanim state, unload VB/VTX files, free sprite. */
void func_selection_0040D488(void) {
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55564254, 0x1D);
    uvUnloadFile(0x55565458, 0x5B6);
    uvUnloadFile(0x55565458, 0x5B7);
    gUvSprtExports->unk8(D_selection_00421E38);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D514.s")

#line 1363 "src/modules/selection.c"
/* Copy the selected 36-byte preset into the original indexed settings slot.
 * Option three preserves the current record. Both original indices remain
 * unchecked; the precise preset-field meanings are not yet established. */
void selectionApplyRecordPreset(s32 option) {
    if (option != 3) ((SelectionPresetRecord *)((u8 *)gGameSettings + 0x6FC0))[D_selection_00420DF0] = ((SelectionPresetRecord *)&D_selection_00421670)[option];
}
#line 1364 "src/modules/selection.c"

#line 1365 "src/modules/selection.c"
/* Return the first of eleven shared words containing any bit from
 * the caller mask, or -1. Preserve the first-three-word checks followed
 * by the two original unrolled groups of four. */
s32 selectionFindFirstMaskIntersection(s32 mask) {
    Node_0040D8B4 *words;
    s32 index;

    if (D_8002CCB0 & mask) {
        return 0;
    }
    if (D_8002CCB4 & mask) {
        return 1;
    }
    words = &D_8002CCBC;
    index = 3;
    if (D_8002CCB8 & mask) {
        return 2;
    }
loop_7:
    if (words->unk0 & mask) {
        return index;
    }
    if (words->unk4 & mask) {
        return index + 1;
    }
    if (words->unk8 & mask) {
        return index + 2;
    }
    if (words->unkC & mask) {
        return index + 3;
    }
    index += 4;
    words += 1;
    if (index == 0xB) {
        return -1;
    }
    goto loop_7;
}
#line 1400 "src/modules/selection.c"

/* Dispatch to enter or exit selection based on current menu item type (0xB7 = confirm). */
void func_selection_0040D98C(void) {
    Inner_0040D98C *temp_v0;

    func_selection_00401FB0();
    temp_v0 = ((Outer_0040D98C *)D_selection_00421D1C)->unk8;
    if (temp_v0->unk8[temp_v0->unk4].unk4 == 0xB7) {
        func_selection_004048D8();
        return;
    }
    func_selection_00404888();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D9F8.s")

/* Prepare the menu, load UVBT bitmap 0x63, create its sprite and center it using integer half-width and half-height. */
#line 1417 "src/modules/selection.c"
/* Apply sound options and suppress confirmation audio, reset the
 * original menu fields, load UVBT file 0x63 and allocate its sprite.
 * Center the sprite at (160, 120) using integer half-width and half-height. */
void selectionCreateCenteredBitmapSprite(void) {
    s32 halfWidth;

    selectionApplySoundOptions();
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xAB);
    D_selection_00420DFC = 0;
    *(s16 *)((u8 *)*(void **)((u8 *)D_selection_00421D1C + 8) + 4) = 0;
    D_selection_00421CE4 = 0xC;
    uvLoadFile(0x55564254, 0x63);
    D_selection_00420DF8 = ((UvSprtFull_0040F0F8 *)gUvSprtExports)->unk4();
    ((UvSprtFull_0040F0F8 *)gUvSprtExports)->unk1C(D_selection_00420DF8, 9, 0x63, 0);
    halfWidth = ((UvSprtFull_0040F0F8 *)gUvSprtExports)->unk14(D_selection_00420DF8) / 2;
    ((UvSprtFull_0040F0F8 *)gUvSprtExports)->unk1C(D_selection_00420DF8, 2, 0xA0 - halfWidth, 0x78 - (((UvSprtFull_0040F0F8 *)gUvSprtExports)->unk18(D_selection_00420DF8) / 2), 3, 1, 0);
}
#line 1431 "src/modules/selection.c"

// Unloads the UVBT sprite file and resets the sprite manager, then tears down selection state.
void func_selection_0040F248(void) {
    uvUnloadFile(0x55564254, 0x63);
    gUvSprtExports->unk8(D_selection_00420DF8);
    func_selection_00404888();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F294.s")

#line 1441 "src/modules/selection.c"
/* Return the first matching index in the original thirteen-entry
 * word table, or -1. Retain the first-word check and the following
 * three unrolled groups of four to preserve original comparison order. */
s32 selectionFindValueInThirteenEntryTable(s32 value) {
    s32 *words;
    s32 index;

    words = &D_selection_0042176C[0];
    index = 1;
    if (value == D_selection_00421768) {
        return 0;
    }
loop_3:
    if (value == words[0]) {
        return index;
    }
    if (value == words[1]) {
        return index + 1;
    }
    if (value == words[2]) {
        return index + 2;
    }
    if (value == words[3]) {
        return index + 3;
    }
    index += 4;
    words += 4;
    if (index == 0xD) {
        return -1;
    }
    goto loop_3;
}
#line 1470 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F4BC.s")

extern s32 D_8002CD98;
extern s32 D_selection_00421C70;

void func_selection_0040F64C(s32 arg0)
{
  s32 *var_s1;
  s32 *var_s2;
  s32 var_s0;
  s32 temp_v0;
 var_s0 = (s32) (&D_selection_00421C70); do { var_s1 = (s32 *) ((arg0 * 0x2C) + var_s0); var_s2 = (s32 *) (((arg0 * 0x24) + 0x284) + ((s32) (&D_8002CD98))); var_s0 = 0; } while (0);
  do
  {
    temp_v0 = selectionFindValueInThirteenEntryTable(*var_s2);
    var_s0 += 1;
    var_s1 += 1;
    var_s2 += 1;
 *(var_s1 - 1) = temp_v0; goto dummy_label_890411; dummy_label_890411: ;
  }
  while (var_s0 != 9);
}

void func_selection_0040F6E0(void) {
    func_selection_0040F4BC(D_selection_00420DF0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F9EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040FDB4.s")

/* Snapshot the source-row address from the signed shared index at
 * base 0x8002CD98 + 0x284 + index * 36 before the original file loads.
 * Load UVBT file 0x57 and UVTX files 0x5B6/0x5B7, clear the two DATA
 * halfwords, allocate a sprite, and forward property words 9, 0x57, 0.
 * Fresh width/height calls supply signed dimensions divided by two;
 * forward position words 160 - width/2 and 120 - height/2, then 3, 1, 0.
 * The property parser applies its own vertical transformation. Property 9
 * delegates its word to a helper; no additional physical purpose is proven.
 * Map nine consecutive source words through the thirteen-entry lookup,
 * reloading the signed shared row index after each call for stores at
 * destination base + index * 44 + word offset. Only nine words are written.
 * RE_ORIGINAL_QUIRK: allocation -1 is truncated to a signed halfword and
 * passed to upper-only index guards without a failure check; lookup -1 is
 * stored unchanged. Exhaustion and invalid-index reachability are unproved.
 * RE_UNKNOWN: full historical callback/export and row declarations,
 * source/destination capacity and ownership, shared-index writer domains,
 * resource availability, initialization/reset ordering and provider/state
 * lifetimes. Trace original callers, row/index producers, pool configuration
 * and resource initialization before strengthening these contracts.
 * Recovery remains deferred: 432 native bytes versus 424 draft bytes,
 * 99 differing words and changed relocation sites. All observed effects
 * remain represented. Native stride arithmetic uses shifts/adds; the draft
 * retains constants 36/44 and uses multiplication, saves another register
 * and holds its source pointer differently, within the same 64-byte frame.
 * Resolve historical source/dataflow evidence before another attempt;
 * retain original ASM without guessed row types or compiler-shape changes. */
#line 1504 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004103CC.s")

/* Teardown: flush GFX, stop tex-anim, unload files, clear sprite sheet. */
void func_selection_0041057C(void) {
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55564254, 0x57);
    uvUnloadFile(0x55565458, 0x5B6);
    uvUnloadFile(0x55565458, 0x5B7);
    D_selection_00421CE0 = 1;
    gUvSprtExports->unk8(D_selection_00421E38);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410614.s")

#line 1519 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00410864(s16 a0, s16 a1) {
}
#line 1521 "src/modules/selection.c"

#line 1522 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00410870(s16 a0, s16 a1) {
}
#line 1524 "src/modules/selection.c"

#line 1525 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_0041087C(void) {
}
#line 1527 "src/modules/selection.c"

#line 1528 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00410884(void) {
}
#line 1530 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041088C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410AA8.s")

extern s32 D_selection_00421E90;

#line 1537 "src/modules/selection.c"
/* Draw the horizontal bar around the requested center using the
 * stored offsets and half thickness. Layer light, dark and middle
 * gray rectangles at the original one-pixel offsets and retain draw order. */
void selectionDrawHorizontalBeveledBar(s32 left, s32 right, s32 centerY)
{
  s32 leftX;
  s32 rightX;
  s32 bottomY;
  s32 topY;
  s32 halfThickness;
  float shadeComponent;
  leftX = left + D_selection_00421E88;
  halfThickness = ((s32) D_selection_00421E84) / 2;
  bottomY = (centerY - halfThickness) + D_selection_00421E8C;
  rightX = right + D_selection_00421E90;
  topY = (halfThickness + centerY) + D_selection_00421E8C;
  gUvGeomExports->unkC(0.75f, 0.75f, 0.75f, 1.0f);
  gUvGeomExports->unk10(leftX, bottomY + 1, rightX, topY + 1);
  gUvGeomExports->unkC(0.25f, 0.25f, shadeComponent = 0.25f, 1.0f);
  gUvGeomExports->unk10(leftX, bottomY - 1, rightX, topY - 1);
  gUvGeomExports->unkC(0.5f, 0.5f, 0.5f, 1.0f);
  gUvGeomExports->unk10(leftX, bottomY, rightX, topY);
}
#line 1557 "src/modules/selection.c"

/* Draw a 3-color layered highlight box used by the selection-screen UI. */
#line 1559 "src/modules/selection.c"
/* Draw the vertical bar around the requested center using stored
 * offsets and half thickness. Preserve the distinct corner offsets
 * of the light, dark and middle gray layers. */
void selectionDrawVerticalBeveledBar(s32 bottom, s32 top, s32 centerX) {
    s32 leftX;
    s32 bottomY;
    s32 rightX;
    s32 topY;
    s32 halfThickness;

    halfThickness = D_selection_00421E84 / 2;
    leftX = (centerX - halfThickness) + D_selection_00421E88;
    bottomY = bottom + D_selection_00421E8C;
    rightX = (halfThickness + centerX) + D_selection_00421E88;
    topY = top + D_selection_00421E94;
    gUvGeomExports->unkC(0.75f, 0.75f, 0.75f, 1.0f);
    gUvGeomExports->unk10(leftX + 1, bottomY + 1, rightX + 1, topY);
    gUvGeomExports->unkC(0.25f, 0.25f, 0.25f, 1.0f);
    gUvGeomExports->unk10(leftX - 1, bottomY, rightX - 1, topY - 1);
    gUvGeomExports->unkC(0.5f, 0.5f, 0.5f, 1.0f);
    gUvGeomExports->unk10(leftX, bottomY, rightX, topY);
}
#line 1578 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410E78.s")

/* Draw a selection label at (arg0+xOff+5, arg1+yOff - fontH/2) in highlight or normal color. */
#line 1582 "src/modules/selection.c"
/* Draw font-eleven text at the stored offset, vertically centered
 * by integer half-height. Use the original yellow or gray palette
 * according to the shared highlight flag, then generate the font list. */
void selectionDrawHighlightedMenuLabel(s32 x, s32 y, s32 textAddress) {
    s32 fontHeight;

    ((UvFontExp_00411038 *)gUvFontExports)->unk4(0xB);
    if (D_selection_00421CE8 != 0) {
        fontHeight = ((UvFontExp_00411038 *)gUvFontExports)->unk1C();
        ((SelPrinter_00411038 *)D_selection_00421B90)->unk40(x + D_selection_00421E98 + 5, (y + D_selection_00421E9C) - (fontHeight / 2), 0xB, 0xFB, 0xCC, 0x1E, 0xFF, textAddress, 1);
    } else {
        fontHeight = ((UvFontExp_00411038 *)gUvFontExports)->unk1C();
        ((SelPrinter_00411038 *)D_selection_00421B90)->unk40(x + D_selection_00421E98 + 5, (y + D_selection_00421E9C) - (fontHeight / 2), 0xB, 0xD2, 0xD2, 0xD2, 0xFF, textAddress, 1);
    }
    ((UvFontExp_00411038 *)gUvFontExports)->unk28();
}
#line 1595 "src/modules/selection.c"

void func_selection_004111B8(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0x74, 0xA3, 0xBD);
    selectionDrawVerticalBeveledBar(0x86, 0xBD, 0xA3);
    func_selection_00410E78(0x74, 0xBD, arg0);
}

void func_selection_00411204(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0x74, 0x8E, 0xB1);
    selectionDrawVerticalBeveledBar(0x98, 0xB1, 0x8E);
    func_selection_00410E78(0x74, 0xB1, arg0);
}

void func_selection_00411250(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0x74, 0x88, 0x90);
    selectionDrawVerticalBeveledBar(0x8B, 0x90, 0x88);
    func_selection_00410E78(0x74, 0x90, arg0);
}

void func_selection_0041129C(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0x74, 0x80, 0x81);
    func_selection_00410E78(0x74, 0x81, arg0);
}

void func_selection_004112D8(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0x74, 0x88, 0x72);
    selectionDrawVerticalBeveledBar(0x72, 0x76, 0x88);
    func_selection_00410E78(0x74, 0x72, arg0);
}

void func_selection_00411324(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0x74, 0x91, 0x63);
    selectionDrawVerticalBeveledBar(0x63, 0x7D, 0x91);
    func_selection_00410E78(0x74, 0x63, arg0);
}

void func_selection_00411370(s32 arg0) {
    selectionDrawVerticalBeveledBar(0x57, 0x5C, 0x97);
    selectionDrawHorizontalBeveledBar(0x74, 0x97, 0x57);
    func_selection_00410E78(0x74, 0x57, arg0);
}

void func_selection_004113BC(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0xB9, 0xCD, 0xAD);
    selectionDrawVerticalBeveledBar(0x89, 0xAD, 0xB9);
    selectionDrawHighlightedMenuLabel(0xCD, 0xAD, arg0);
}

void func_selection_00411408(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0xBE, 0xCD, 0x9F);
    selectionDrawVerticalBeveledBar(0x96, 0x9F, 0xBE);
    selectionDrawHighlightedMenuLabel(0xCD, 0x9F, arg0);
}

void func_selection_00411454(s32 arg0) {
    selectionDrawVerticalBeveledBar(0x8C, 0x91, 0xC0);
    selectionDrawHorizontalBeveledBar(0xC0, 0xCD, 0x91);
    selectionDrawHighlightedMenuLabel(0xCD, 0x91, arg0);
}

void func_selection_004114A0(s32 arg0) {
    selectionDrawHorizontalBeveledBar(0xCA, 0xCD, 0x82);
    selectionDrawHighlightedMenuLabel(0xCD, 0x82, arg0);
}

void func_selection_004114DC(s32 arg0) {
    selectionDrawVerticalBeveledBar(0x75, 0x79, 0xC0);
    selectionDrawHorizontalBeveledBar(0xC0, 0xCD, 0x75);
    selectionDrawHighlightedMenuLabel(0xCD, 0x75, arg0);
}

void func_selection_00411528(s32 arg0) {
    selectionDrawVerticalBeveledBar(0x67, 0x71, 0xB9);
    selectionDrawHorizontalBeveledBar(0xB9, 0xCD, 0x67);
    selectionDrawHighlightedMenuLabel(0xCD, 0x67, arg0);
}

void func_selection_00411574(s32 arg0) {
    selectionDrawVerticalBeveledBar(0x59, 0x77, 0xB3);
    selectionDrawHorizontalBeveledBar(0xB3, 0xCD, 0x59);
    selectionDrawHighlightedMenuLabel(0xCD, 0x59, arg0);
}

// Draw three UI elements using fixed coords, with the third element's text
// pointer selected from a per-language table at D_selection_004217F0.
#line 1680 "src/modules/selection.c"
/* Draw the fixed horizontal and vertical beveled bars, then the
 * language-indexed label at their original shared screen position.
 * The existing language index contract remains unchanged. */
void selectionDrawLocalizedLabelWithBeveledBars(void) {
    selectionDrawHorizontalBeveledBar(0xA3, 0xCD, 0x4A);
    selectionDrawVerticalBeveledBar(0x4A, 0x64, 0xA3);
    selectionDrawHighlightedMenuLabel(0xCD, 0x4A, D_selection_004217F0[gOptionsLanguage].text);
}
#line 1685 "src/modules/selection.c"

#line 1686 "src/modules/selection.c"
/* Format the language-selected pair of strings into the original
 * eighty-byte buffer. Draw the surrounding beveled bars and label,
 * using the alternate horizontal coordinate only for language ID two.
 * RE_ORIGINAL_QUIRK: formatting retains the original unbounded string helper. */
void selectionDrawFormattedLocalizedLabel(void) {
    char text[0x50];
    s32 left;
    D_selection_004217C8_entry *localizedParts;

    left = 0x74;
    localizedParts = &D_selection_004217C8[gOptionsLanguage];
    gUvStringExports->unk10(text, D_selection_0041EEA0, localizedParts->unk0, localizedParts->unk4);
    if (gOptionsLanguage == 2) {
        left = 0x8C;
    }
    selectionDrawHorizontalBeveledBar(left, 0xA3, 0x4A);
    selectionDrawVerticalBeveledBar(0x4A, 0x64, 0xA3);
    func_selection_00410E78(left, 0x4A, text);
}
#line 1701 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004116E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411F40.s")

#line 1710 "src/modules/selection.c"
/* Store the 16-bit value and active flag in the indexed 0x34-byte record.
 * RE_UNKNOWN: index/table extent need original producers/callers; context is unused. */
void selectionSetRecordValueAndActivate(s32 index, s32 context, u16 value) {
    SelectionValueRecord *record = &((SelectionValueRecord *)&D_selection_00421BA0)[index];
    record->value = value;
    record->active = 1;
}
#line 1711 "src/modules/selection.c"

/* Controller export table view: unk3C(u16,s32) and unk44(s32,s32,s32) */
/* Reset selection state, look up the stored Controller Pak file when enabled, and bind the next callback. */
#line 1714 "src/modules/selection.c"
/* Reset the original selection state and copy the current Pak flags
 * into settings. When flag one is set, apply the stored Pak identity
 * and look up its file on controller zero. Store a successful file
 * number or the original failure sentinels, then bind the next callback. */
void selectionPrepareControllerPakFileChoice(void) {
    s32 fileNumber;

    D_selection_00420DFC = 1;
    D_selection_00420E24 = -1;
    D_selection_00420E4C = 0;
    func_selection_00419084();
    *(s16 *)((u8 *)gGameSettings + 0x6F9A) = D_selection_00421BA4;
    if (D_selection_00421BA4 & 1) {
        ((UvContExp_413418 *)gUvContExports)->unk3C((u16)gGameSettings->unk6FB8, gGameSettings->unk6FBC);
        fileNumber = ((UvContExp_413418 *)gUvContExports)->unk44(0, gGameSettings->unk6FB0, gGameSettings->unk6FB4);
        if (fileNumber >= 0) {
            D_selection_00420E24 = fileNumber;
            D_8002CC8C = fileNumber;
        } else {
            D_selection_00420E24 = -1;
            *(s32 *)((u8 *)gGameSettings + 0x6F9C) = -1;
        }
    }
    func_selection_00411B9C();
    D_selection_00421D28 = (s32)func_selection_00411B9C;
}
#line 1736 "src/modules/selection.c"

void func_selection_004134F4(void) {
    D_selection_00420DFC = 1;
    func_selection_004017E0();
}

#line 1742 "src/modules/selection.c"
/* When the stored Pak file number is nonnegative, exit the current
 * menu and activate its existing-file node. Otherwise call the original
 * fallback handler. RE_UNKNOWN: the exact fallback screen label is unproven. */
void selectionChoosePakMenuFromFileLookup(void) {
    if (D_selection_00420E24 >= 0) {
        selectionRunCurrentMenuExitCallback();
        selectionActivateMenuNode(&D_selection_004201BC);
        return;
    }
    func_selection_00413594();
}
#line 1750 "src/modules/selection.c"

void func_selection_00413568(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_00420218);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413594.s")

#line 1758 "src/modules/selection.c"
/* Select the configured Controller Pak identity, find its file and run
 * the original settings read. A successful read stores the file and sets
 * status one; failure sets status two and resets selection. Both statuses
 * retain the original three-second display timer. */
void selectionLoadPakFileAndShowResult(void) {
    s32 file;
    ((UvContExp_413418 *)gUvContExports)->unk3C((u16)gGameSettings->unk6FB8, gGameSettings->unk6FBC);
    file = ((UvContExp_413418 *)gUvContExports)->unk44(0, gGameSettings->unk6FB0, gGameSettings->unk6FB4);
    if (file >= 0) {
        if (func_selection_00416FF4(file) != 0) {
            *(s32 *)((u8 *)gGameSettings + 0x6F9C) = file;
            *(s16 *)((u8 *)gGameSettings + 0x6F94) = 1;
            D_selection_00420E4C = 1;
            D_selection_00420E50 = 3.0f;
            return;
        }
    }
    D_selection_00420E4C = 2;
    D_selection_00420E50 = 3.0f;
    func_selection_004017E0();
}
#line 1759 "src/modules/selection.c"

void func_selection_0041378C(void) {
    D_selection_00420DE8 = 2;
    D_selection_00420DEC = 0;
    D_8002CC84 = 0;
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F770);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004137D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413A88.s")

#line 1772 "src/modules/selection.c"
/* Delete the shared selection sprite and replace its handle with -1.
 * Preserve the original unconditional deletion call. */
void selectionDeleteSharedSprite(void) {
    gUvSprtExports->unk8(D_selection_00420DF8);
    D_selection_00420DF8 = -1;
}
#line 1776 "src/modules/selection.c"

void func_selection_00413E1C(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_00420074);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413E48.s")

#line 1784 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00413FA4(void) {
}
#line 1786 "src/modules/selection.c"

#line 1787 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00413FAC(void) {
}
#line 1789 "src/modules/selection.c"

#line 1790 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00413FB4(void) {
}
#line 1792 "src/modules/selection.c"

#line 1793 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00413FBC(void) {
}
#line 1795 "src/modules/selection.c"

/* Draw through the original shared mode and unsigned selector dispatch.
 * RE_ORIGINAL_QUIRK: a mode outside 0, 1, and 2, or a selector at least 16,
 * can bypass writes to scratch words at original SP+0x34, +0x38, and +0x3C,
 * then reach their reads at 0x41454C, 0x414590, and 0x414568 respectively.
 * RE_UNKNOWN: actual mode/selector writer domains, initialization/reset
 * order and caller reachability. Trace all original producers and dispatch
 * callers before deciding whether any unwritten-scratch path is reachable.
 * Preserve original ASM; no reachable player fault or runtime fix is claimed. */
#line 1796 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413FC4.s")

#line 1798 "src/modules/selection.c"
/* Draw a filled rectangle when indent is zero. Otherwise draw the original
 * three thin rectangles forming a stepped menu border, with one-pixel offsets
 * and caller RGBA. Preserve triangle order and save/restore graphics state. */
void selectionDrawFilledRectangleOrSteppedBorder(s32 indent, s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 red, s32 green, s32 blue, s32 alpha) {
    gUvGfxStateExports->unk50();
    gUvGfxStateExports->unk0C(0x800000);
    gUvGfxStateExports->unk10((s32)0xBE7C0000);
    if (indent == 0) {
        gUvDGeomExports->uvBeginTmesh();
        gUvDGeomExports->uvVtx(firstX,firstY,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX,secondY,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(secondX,firstY,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(secondX,firstY,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX,secondY,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(secondX,secondY,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvDgeomEndTriangleMesh();
    } else {
        gUvDGeomExports->uvBeginTmesh();
        gUvDGeomExports->uvVtx(firstX,secondY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX,secondY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent,secondY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent,secondY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX,secondY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent,secondY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvDgeomEndTriangleMesh();
        gUvDGeomExports->uvBeginTmesh();
        gUvDGeomExports->uvVtx(firstX + indent,secondY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent,firstY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent + 2,secondY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent + 2,secondY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent,firstY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent + 2,firstY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvDgeomEndTriangleMesh();
        gUvDGeomExports->uvBeginTmesh();
        gUvDGeomExports->uvVtx(firstX + indent + 1,firstY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(secondX,firstY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent + 1,firstY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(firstX + indent + 1,firstY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(secondX,firstY - 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvVtx(secondX,firstY + 1,0,0,0,red,green,blue,alpha);
        gUvDGeomExports->uvDgeomEndTriangleMesh();
    }
    gUvGfxStateExports->unk54();
}
#line 1799 "src/modules/selection.c"

#line 1800 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_00414CEC(void) {
}
#line 1802 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00414CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041532C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004155A0.s")

/* Tear down selection screen: camera reset, clear gfx/texanim, unload files, reset track object. */
void func_selection_004158DC(void) {
    s32 var_s0;

    gCamExports->unk20(*D_selection_00421D18, 0x9, (f64) D_selection_0041F4C4, 0);
    var_s0 = 0;
    do {
        func_selection_00416A50(var_s0, 0);
        var_s0 += 1;
    } while (var_s0 != 8);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55565452, 0x2);
    uvUnloadFile(0x5556454E, 0xB);
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
}

void func_selection_004159FC(void) {
    selectionRunCurrentMenuExitCallback();
    D_selection_00420DFC = 1;
    selectionActivateMenuNode(&D_selection_00420074);
}

#line 1836 "src/modules/selection.c"
/* For mode one, reset intro progress and select track 27. Store the
 * caller mode, choose transition callback slot eight, set transition
 * state two and clear its scalar. RE_UNKNOWN: the transition stage
 * meanings remain numeric; their original order and values are preserved. */
void selectionPrepareTransitionAndOptionalIntroReset(s32 mode) {
    if (mode == 1) {
        gGameSettings->currentTrack = 0x1B;
        gGameSettings->finishedIntroCount = 0;
    }
    D_selection_00421E08 = 8;
    gGameSettings->unkC = mode;
    D_selection_00421D28 = D_selection_00421240[D_selection_00421E08];
    D_selection_00420DE8 = 2;
    D_selection_00420DEC = 0;
}
#line 1847 "src/modules/selection.c"

#line 1848 "src/modules/selection.c"
/* Request state two when the intro flag is set; otherwise request
 * state three. Preserve the original early-return behavior. */
void selectionRequestIntroOrGameState(void) {
    if (gGameSettings->playIntroFlag != 0) {
        gGameSettings->newGameState = 2;
        return;
    }
    gGameSettings->newGameState = 3;
}
#line 1855 "src/modules/selection.c"

#line 1856 "src/modules/selection.c"
/* With speech enabled, set its volume and initialize a local sound handle.
 * A nonzero gate permits the voice at scaled volume and original scalar 0.5,
 * then clears the gate. A zero gate still performs the original initialization. */
void selectionPlayGatedVoice(s16 soundId, s32 *gate) {
    SelectionSoundHandle handle;
    if (gOptionsSpeechVol != 0) {
        ((SelectionSpeechExports *)gSndExports)->setVolume(gOptionsSpeechVol);
        ((SelectionSpeechExports *)gSndExports)->initialize(&handle);
        if (*gate != 0) {
            ((SelectionSpeechExports *)gSndExports)->play(&handle, soundId, 0x7FFF, ((SelectionSpeechExports *)gSndExports)->getVolume() * D_selection_0041F4C8, 0.5f);
            *gate = 0;
        }
    }
}
#line 1857 "src/modules/selection.c"

#line 1858 "src/modules/selection.c"
/* Play voice 0xBC through its own existing gate; preserve the gate at 0x00420E90. */
void selectionPlayGatedVoiceBC(void) {
    selectionPlayGatedVoice(0xBC, &D_selection_00420E90);
}
#line 1861 "src/modules/selection.c"

#line 1862 "src/modules/selection.c"
/* Play voice 0xE4 through its own existing gate; preserve the gate at 0x00420E84. */
void selectionPlayGatedVoiceE4(void) {
    selectionPlayGatedVoice(0xE4, &D_selection_00420E84);
}
#line 1865 "src/modules/selection.c"

/* Stop active sounds then play the circuit-announce sfx when arg0 == 3. */
#line 1867 "src/modules/selection.c"
/* Suppress cancel, select and directional-menu sounds in order.
 * Only kind three is passed to the gated title-voice helper; retain
 * the original explicit exclusions and shared pending flag. */
void selectionSuppressNavigationAndTryTitleVoice(s32 kind) {
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xE);
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xC);
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xDB);
    if (kind != 0 && kind != 1 && kind != 2 && kind == 3) {
        selectionPlayGatedVoice(0x7A, &D_selection_00420E68);
    }
}
#line 1875 "src/modules/selection.c"

#line 1876 "src/modules/selection.c"
/* Play voice 0x7B through its own existing gate; preserve the gate at 0x00420E74. */
void selectionPlayGatedVoice7B(void) {
    selectionPlayGatedVoice(0x7B, &D_selection_00420E74);
}
#line 1879 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415CA0.s")

#line 1882 "src/modules/selection.c"
/* Select race-mode voice E0/E1 for option 0/1 through the original speech
 * helper and shared gate. Unsupported options do nothing. */
void selectionPlayRaceModeVoice(s32 option) {
    switch (option) {
    case 0:
        selectionPlayGatedVoice(0xE0, &D_selection_00420E80);
        return;
    case 1:
        selectionPlayGatedVoice(0xE1, &D_selection_00420E80);
        return;
    }
}
#line 1883 "src/modules/selection.c"

#line 1884 "src/modules/selection.c"
/* Play voice 0xB5 through its own existing gate; preserve the gate at 0x00420E78. */
void selectionPlayGatedVoiceB5(void) {
    selectionPlayGatedVoice(0xB5, &D_selection_00420E78);
}
#line 1887 "src/modules/selection.c"

#line 1888 "src/modules/selection.c"
/* Play voice 0xB6 through its own existing gate; preserve the gate at 0x00420E70. */
void selectionPlayGatedVoiceB6(void) {
    selectionPlayGatedVoice(0xB6, &D_selection_00420E70);
}
#line 1891 "src/modules/selection.c"

#line 1892 "src/modules/selection.c"
/* Select the gated voice for tournament indices zero through three.
 * Unsupported indices do nothing; callers also set tournament race counts. */
void selectionPlayTournamentVoice(s32 option) {
    switch (option) {
    case 0: selectionPlayGatedVoice(0xBF, &D_selection_00420E7C); return;
    case 1: selectionPlayGatedVoice(0xC0, &D_selection_00420E7C); return;
    case 2: selectionPlayGatedVoice(0xC1, &D_selection_00420E7C); return;
    case 3: selectionPlayGatedVoice(0xC2, &D_selection_00420E7C); return;
    }
}
#line 1893 "src/modules/selection.c"

#line 1894 "src/modules/selection.c"
/* Select the voice for the seven-AI, one-AI or no-AI race preset (options
 * 0/1/2 map to E2/B8/E3). Unsupported options leave the original gate alone. */
void selectionPlayAiRacePresetVoice(s32 option) {
    switch (option) {
    case 0:
        selectionPlayGatedVoice(0xE2, &D_selection_00420E88);
        return;
    case 1:
        selectionPlayGatedVoice(0xB8, &D_selection_00420E88);
        return;
    case 2:
        selectionPlayGatedVoice(0xE3, &D_selection_00420E88);
        return;
    }
}
#line 1895 "src/modules/selection.c"

#line 1896 "src/modules/selection.c"
/* Apply saved speech, effects and music volumes, reset the original sound
 * state, enable it and initialize all four original sound channels. */
void selectionApplySoundOptions(void) {
    s32 index;
    ((SelectionSoundConfigExports *)gSndExports)->speech(gGameSettings->optionsSpeechVol);
    ((SelectionSoundConfigExports *)gSndExports)->sfx(gGameSettings->optionsSfxVol);
    ((SelectionSoundConfigExports *)gSndExports)->music(gGameSettings->optionsMusicVol);
    ((SelectionSoundConfigExports *)gSndExports)->reset();
    ((SelectionSoundConfigExports *)gSndExports)->enable(1);
    for (index = 0; index != 4; index++) ((SelectionSoundConfigExports *)gSndExports)->channel(index);
}
#line 1897 "src/modules/selection.c"

#line 1898 "src/modules/selection.c"
/* Select two-, three- or four-player speech using zero-based option 0/1/2
 * and the original E5/EE/EF sounds. Unsupported options do nothing. */
void selectionPlayPlayerCountVoiceIndex(s32 option) {
    switch (option) {
    case 0:
        selectionPlayGatedVoice(0xE5, &D_selection_00420E8C);
        return;
    case 1:
        selectionPlayGatedVoice(0xEE, &D_selection_00420E8C);
        return;
    case 2:
        selectionPlayGatedVoice(0xEF, &D_selection_00420E8C);
        return;
    }
}
#line 1899 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416028.s")

/* Tear down the selection screen: clear gfx/texanim, unload files, reset track object. */
void func_selection_004162D4(void) {
    func_selection_00416A50(0, 0);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55565452, 0x8);
    uvUnloadFile(0x5556454E, 0x12);
    (*D_selection_00421D18)->unk220 = -1;
    gUvTerraExports->unk8((*D_selection_00421D18)->unk0, -1);
    gUvEnvExports->unk18((*D_selection_00421D18)->unk0, -1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041639C.s")

/* Tear-down: resets selection render state, unloads track/env files, clears terrain and env. */
void func_selection_004166CC(void) {
    func_selection_00416A50(0, 0);
    gUvGfxMgrExports->unk74();
    gUvTexAnimExports->unk8();
    uvUnloadFile(0x55565452, 0x9);
    uvUnloadFile(0x5556454E, 0xB);
    (**D_selection_00421D18).unk220 = -1;
    gUvTerraExports->unk8((**D_selection_00421D18).unk0, -1);
    gUvEnvExports->unk18((**D_selection_00421D18).unk0, -1);
}

#line 1928 "src/modules/selection.c"
/* Translate the current preview matrix around X/Z and its stored Y,
 * apply the original scaled Z then X rotations, translate back, and copy
 * the result to the second matrix. Re-read the current object between
 * export calls. The third argument is an unused incoming 32-bit word;
 * its original meaning is not established. */
void selectionRotatePreviewAroundPoint(f32 x, f32 z, s32 unused, f32 angle) {
    ObjNode_4168C4 *object;
    object = (ObjNode_4168C4 *)*D_selection_00421D18;
    gUvFmtxExports->unk2C(&object->unkFC, -x, -object->unkF8, -z);
    gUvFmtxExports->unk28(&((ObjNode_4168C4 *)*D_selection_00421D18)->unkFC, D_selection_00420E20 * D_selection_0041F4E4, 0x7A);
    gUvFmtxExports->unk28(&((ObjNode_4168C4 *)*D_selection_00421D18)->unkFC, angle * D_selection_0041F4E8, 0x78);
    gUvFmtxExports->unk2C(&((ObjNode_4168C4 *)*D_selection_00421D18)->unkFC, x, ((ObjNode_4168C4 *)*D_selection_00421D18)->unkF8, z);
    gUvFmtxExports->unk0C(&((ObjNode_4168C4 *)*D_selection_00421D18)->unk1A8, &((ObjNode_4168C4 *)*D_selection_00421D18)->unkFC);
}
#line 1929 "src/modules/selection.c"

/* Rotate the shared matrix around the caller pivot after resetting its rotation basis; retain the translated position. */
#line 1931 "src/modules/selection.c"
/* Copy the shared matrix and translate to the caller X/Z pivot with stored Y.
 * Reset its rotation basis, apply Z then X rotations, translate back and copy
 * to both matrix fields. RE_UNKNOWN: view/world space needs matrix-consumer evidence. */
void selectionRotateViewMatrixAroundPivot(f32 pivotX, f32 pivotZ, f32 rotationInput) {
    Mtx4F matrix;

    gUvFmtxExports->unk0C(&matrix, &((ObjNode_4168C4 *)(*D_selection_00421D18))->unkFC);
    gUvFmtxExports->unk2C(&matrix, -pivotX, -((ObjNode_4168C4 *)(*D_selection_00421D18))->unkF8, -pivotZ);
    matrix.xx = 1.0f;
    matrix.yy = 1.0f;
    matrix.zz = 1.0f;
    matrix.yx = 0.0f;
    matrix.zx = 0.0f;
    matrix.xy = 0.0f;
    matrix.zy = 0.0f;
    matrix.xz = 0.0f;
    matrix.yz = 0.0f;
    gUvFmtxExports->unk28(&matrix, D_selection_00420E20 * D_selection_0041F4EC, 0x7A);
    gUvFmtxExports->unk28(&matrix, rotationInput * D_selection_0041F4F0, 0x78);
    gUvFmtxExports->unk2C(&matrix, pivotX, ((ObjNode_4168C4 *)(*D_selection_00421D18))->unkF8, pivotZ);
    gUvFmtxExports->unk0C(&((ObjNode_4168C4 *)(*D_selection_00421D18))->unkFC, &matrix);
    gUvFmtxExports->unk0C(&((ObjNode_4168C4 *)(*D_selection_00421D18))->unk1A8, &((ObjNode_4168C4 *)(*D_selection_00421D18))->unkFC);
}
#line 1951 "src/modules/selection.c"

/* CARANIM slot0x14 property27 stores the promoted word at state+0x30; this wrapper then rereads indexed state and calls slot0x08. RE_UNKNOWN: word meaning and state/index validity/lifetime need original callers/readers. Clean C remains unmatched on two stack-slot words. */
#line 1952 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416A50.s")
#line 1953 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416ABC.s")

/* Set sprite props then render two sprites with gfx state push/pop */
#line 1957 "src/modules/selection.c"
/* Apply the first sprite properties, push graphics state and set
 * the original render bits. Render both shared sprites in order and
 * restore the graphics state afterward. */
void selectionRenderSharedSpritePair(void) {
    ((SprtExp_00416D94 *)gUvSprtExports)->unk1C(D_selection_00421E36, 3, 1, 0xB, 1, 0xC, 0, 0);
    ((GfxStateExp_00416D94 *)gUvGfxStateExports)->unk50();
    ((GfxStateExp_00416D94 *)gUvGfxStateExports)->unkC(0x800000);
    ((GfxStateExp_00416D94 *)gUvGfxStateExports)->unk10((s32)0xBE7C0000);
    ((SprtExp_00416D94 *)gUvSprtExports)->unk10(D_selection_00421E36);
    ((SprtExp_00416D94 *)gUvSprtExports)->unk10(D_selection_00421E34);
    ((GfxStateExp_00416D94 *)gUvGfxStateExports)->unk54();
}
#line 1966 "src/modules/selection.c"

#line 1967 "src/modules/selection.c"
/* Repair controller zero's Pak, select original status five on nonzero SDK
 * status or six on success, set the three-second timer, and refresh the
 * peripheral-state byte. Preserve both original branches and shared writes. */
void selectionRepairControllerPak(void) {
    if (((SelectionPakRepairExports *)gUvContExports)->repair(0) != 0) {
        D_selection_00420E4C = 5;
        D_selection_00420E50 = 3.0f;
        D_selection_00421BA4 = ((SelectionPakRepairExports *)gUvContExports)->getState(0);
    } else {
        D_selection_00420E4C = 6;
        D_selection_00420E50 = 3.0f;
        D_selection_00421BA4 = ((SelectionPakRepairExports *)gUvContExports)->getState(0);
    }
}
#line 1968 "src/modules/selection.c"

void func_selection_00416F28(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F728);
}

#line 1974 "src/modules/selection.c"
/* Select the original Controller Pak identity, locate its file on controller
 * zero and write the shared 1024-byte settings block. Return one only when
 * lookup succeeds and the transfer returns SDK success zero. */
s32 selectionWritePakSettingsBlock(void) {
    s32 file;
    ((SelectionPakWriteExports *)gUvContExports)->select(gGameSettings->unk6FB8, gGameSettings->unk6FBC);
    file = ((SelectionPakWriteExports *)gUvContExports)->find(0, gGameSettings->unk6FB0, gGameSettings->unk6FB4);
    if (file >= 0 && ((SelectionPakWriteExports *)gUvContExports)->write(0, file, 0, 0x400, (u8 *)&D_8002CD98) == 0) return 1;
    return 0;
}
#line 1975 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416FF4.s")

#line 1978 "src/modules/selection.c"

void selectionRememberPakDeleteSelection(void) { /* Copy the nested signed-halfword selection into the shared value later passed to Pak deletion and set its pending word to one. RE_UNKNOWN: selection-to-file mapping and nested-record validity require original menu/table producers. */
    D_selection_00420E18 = *(s16*)((u8*)*(void**)((u8*)D_selection_00421D1C + 8) + 4);
    D_selection_00420E1C = 1;
}
#line 1982 "src/modules/selection.c"

/* Request deletion of the tracked Controller Pak file on controller zero, ignore success/failure, then clear the three tracking values. */
#line 1984 "src/modules/selection.c"

void selectionDeleteTrackedPakFileOnControllerZero(void) { /* Request Controller Pak file deletion on controller zero, ignore its result and reset three shared tracking values. RE_UNKNOWN: selected menu value to SDK file-number mapping and error/retry policy require original menu producers/callers. */
    gUvContExports->unk5C(0, D_selection_00420E18);
    D_selection_00421E40 = 0;
    D_selection_00420E1C = 0;
    D_selection_00420E18 = -1;
}
#line 1990 "src/modules/selection.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004172B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004177A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004181D0.s")

void func_selection_0041843C(void) {
    D_selection_00420E28 = -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041844C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00418800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00418E98.s")

void func_selection_00419020(void) {
    *(s16 *)((u8 *)&D_selection_0041F794 + 0x16) = 1;
    *(s16 *)((u8 *)&D_selection_0041F794 + 0x2A) = 1;
}

#line 2012 "src/modules/selection.c"
/* Mark shared state, clear words 0x16/0x2A and reset the nested word if 1 or 2.
 * RE_UNKNOWN: required non-null nested chain, allocation/lifetime and word meanings
 * need original state producers and callers; preserve the observed stores. */
void selectionResetTransientWords(void) {
    SelectionResetWords *flags = (SelectionResetWords *)&D_selection_0041F794;
    InnerObj_0041B19C *record;
    D_selection_00421B98 = 1;
    flags->word16 = 0;
    flags->word2A = 0;
    record = ((D1CTarget_0041B19C *)D_selection_00421D1C)->unk8;
    if (record->unk4 == 1 || record->unk4 == 2) record->unk4 = 0;
}
#line 2013 "src/modules/selection.c"

/* Refresh four controller rows after clearing D_selection_00421B98 and
 * calling CONT slot 0x04. Reload the provider for each presence/state query.
 * The observed row stride is 0x34: write presence at offset 0, controller
 * index at 2, the peripheral-state byte as a halfword at 4, and zero at 6.
 * An absent controller clears only presence. The original second traversal
 * uses the distinct D_selection_00421C70 end address, 208 bytes after the row
 * base; actual BSS relocation records establish that four-row span.
 * Register selectionSetRecordValueAndActivate through CONT slot 0x30 after
 * counting. The native setter stores one address word. The original update
 * dispatcher supplies index, prior peripheral byte masked to sixteen bits,
 * and current peripheral byte or zero; the callback ignores the middle
 * word, stores the third word's low halfword at row+4, and writes 1 at row+6.
 * RE_ORIGINAL_QUIRK: counting stops at the first zero presence halfword,
 * even if a later refreshed row is active. Inactive rows retain the other
 * fields. Preserve this leading-active-prefix count, not a count of all
 * active rows.
 * RE_UNKNOWN: complete historical row and callback declarations, backing
 * storage ownership/capacity, the count's consumers and any required
 * contiguous-presence invariant, and callback registration/reset/scheduler
 * lifetimes. Original row/count producers, consumers and callback ordering
 * must establish those contracts; invalid-domain reachability is unproved.
 * Recovery is deferred: the first draft emits 284 bytes versus 272 native
 * bytes. One bounded correction restores the original end-symbol identity,
 * but emits 288 bytes and still differs in 64 words. The compiler retains
 * an extra loop-limit register, changes saved-register homes and scheduling,
 * and adds a second-loop entry comparison absent from the original flow.
 * All twelve final object records retain the same symbol/type/value/addend
 * identities, but relocation sites differ; the actual module has ten native
 * records, excluding the kernel-address pair. No missing call or store was
 * identified. Original source/compiler lifetime evidence is needed before
 * another attempt; retain ASM without invented storage or register forcing. */
#line 2014 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419084.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419384.s")

/* Initialize controller context, bind buttons, then read or default an axis value */
#line 2021 "src/modules/selection.c"
/* Apply sound options and the original menu initialization helpers,
 * then mark the menu for refresh. With Pak flag one set, apply the
 * stored identity and look up its file on controller zero, preserving
 * both success/failure outputs. Otherwise activate the original fallback menu. */
void selectionFindControllerPakFileForCurrentMenu(void) {
    s32 fileNumber;

    selectionApplySoundOptions();
    func_selection_004017E0();
    func_selection_00419084();
    *(s32 *)((u8 *)D_selection_00421D1C + 0x20) = 1;
    if (D_selection_00421BA4 & 1) {
        ((UvContExp_00419AA4 *)gUvContExports)->unk3C((u16)gGameSettings[0].unk6FB8, gGameSettings[0].unk6FBC);
        fileNumber = ((UvContExp_00419AA4 *)gUvContExports)->unk44(0, gGameSettings[0].unk6FB0, gGameSettings[0].unk6FB4);
        if (fileNumber >= 0) {
            D_selection_00420E24 = fileNumber;
            D_8002CC8C = fileNumber;
            return;
        }
        D_selection_00420E24 = -1;
        D_8002CC8C = -1;
        return;
    }
    func_selection_00419B9C();
}
#line 2042 "src/modules/selection.c"

void func_selection_00419B78(void) {
    D_selection_00421D28 = 0;
    func_selection_004017E0();
}

void func_selection_00419B9C(void) {
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_0041F5B4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419D54.s")

#line 2057 "src/modules/selection.c"
/* Clear the original shared DATA byte, then query MENU slot 0x08 with
 * controller word 0 and the current node's record pointer at offset 0x08.
 * Use the returned numeric action once; reload the current node after that
 * effectful callback. Action 7 uses latch byte 1, sets it before testing node
 * word 0x04, and, when nonzero, copies D_selection_00420F1C into the deferred
 * word and writes the two state words 1 and 0. Action 8 uses latch byte 0,
 * sets it before reading the record's signed halfword at offset 0x04, and,
 * unless that value is -1, stores the address of func_selection_004159FC
 * and the two state words 1 and 1. Other actions clear their respective
 * latch bytes. Preserve the second action test after the action-7 stores;
 * there is no early return before latch byte 0 is cleared for action 7.
 * The existing focused views describe only consumed offsets, not complete
 * historical nodes, records, or latch storage. No new types or storage are added.
 * RE_UNKNOWN: record/node validity and ownership, signed selection domains
 * beyond the -1 sentinel, latch initialization/reset and callback-sensitive
 * lifetimes, historical complete export declarations, and deferred-word
 * consumer contracts. Trace original producers, registration, consumers and
 * callers before strengthening those promises. The original latch remains
 * set when its node/record guard rejects an action; whether rejected states
 * are reachable or expected requires that producer and caller evidence. */
void selectionLatchMenuActionsWithRecordGuard(void) {
    s32 action;

    D_selection_00420DE8 = 0;
    action = ((SelectionLatchedActionExports *)D_selection_00421B90)->getAction(
        0, ((SelectionActionNodeView *)D_selection_00421D1C)->records08);
    if (action == 7) {
        if (((u8 *)&D_selection_00421CF0)[1] == 0) {
            ((u8 *)&D_selection_00421CF0)[1] = 1;
            if (((SelectionActionNodeView *)D_selection_00421D1C)->word04 != 0) {
                D_selection_00421D28 = D_selection_00420F1C;
                D_selection_00421CDC = 1;
                D_selection_00421CE0 = 0;
            }
        }
    } else {
        ((u8 *)&D_selection_00421CF0)[1] = 0;
    }
    if (action == 8) {
        if (*(u8 *)&D_selection_00421CF0 == 0) {
            *(u8 *)&D_selection_00421CF0 = 1;
            if (((AgentLanguageExpressionChoices *)
                 ((SelectionActionNodeView *)D_selection_00421D1C)->records08)->selected != -1) {
                D_selection_00421D28 = (s32)func_selection_004159FC;
                D_selection_00421CDC = 1;
                D_selection_00421CE0 = 1;
            }
        }
    } else {
        *(u8 *)&D_selection_00421CF0 = 0;
    }
}
#line 2058 "src/modules/selection.c"

/* Release assets for numeric language IDs 0..2; RE_UNKNOWN: mapping IDs to language names requires localized-text or asset evidence. */
#line 2060 "src/modules/selection.c"
/* Wait for graphics and unload the original language-specific UVTX
 * and UVBT files for language IDs zero through two. Independently free
 * the shared sprite and invalidate its handle for every language value. */
void selectionReleaseLanguageScreenAssets(void) {
    switch (gOptionsLanguage) {
    case 0:
        gUvGfxMgrExports->unk74();
        uvUnloadFile(0x55565458, 9);
        uvUnloadFile(0x55565458, 8);
        uvUnloadFile(0x55564254, 0x1A);
        break;
    case 1:
        gUvGfxMgrExports->unk74();
        uvUnloadFile(0x55565458, 0x5A6);
        uvUnloadFile(0x55565458, 8);
        uvUnloadFile(0x55564254, 0x52);
        break;
    case 2:
        gUvGfxMgrExports->unk74();
        uvUnloadFile(0x55565458, 0x5A5);
        uvUnloadFile(0x55565458, 0x5A4);
        uvUnloadFile(0x55564254, 0x51);
        break;
    }
    gUvSprtExports->unk8(D_selection_00420DF8);
    D_selection_00420DF8 = -1;
}
#line 2084 "src/modules/selection.c"

#line 2085 "src/modules/selection.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_selection_0041A208(void) {
}
#line 2087 "src/modules/selection.c"

void func_selection_0041A210(void) {
    selectionPlayGatedVoiceB5();
    selectionRunCurrentMenuExitCallback();
    selectionActivateMenuNode(&D_selection_00420260);
}

/* Draw the original mode-dependent rows and update the shared scalar.
 * RE_ORIGINAL_QUIRK: a shared mode outside 0, 1, and 2 can bypass writes to
 * scratch words at original SP+0x30, +0x34, and +0x3C before their first
 * drawing-call reads at 0x41A3F0, 0x41A3F4, and 0x41A3EC respectively.
 * RE_UNKNOWN: actual shared-mode producer domain, initialization/reset
 * order and caller reachability. Trace original writers and all dispatch
 * callers before deciding whether this unwritten-scratch path is reachable.
 * Preserve original ASM; no reachable player fault or runtime fix is claimed. */
#line 2094 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A5BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A7D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A960.s")

#line 2102 "src/modules/selection.c"
/* Convert minutes, seconds and hundredths to the original floating time
 * scalar; preserve integer multiplication/addition before float conversion. */
f32 selectionComposeTimeScalar(s32 minutes, s32 seconds, s32 hundredths) {
    return (f32) ((minutes * 0x3C) + seconds) + ((f32) hundredths / 100.0f);
}
#line 2105 "src/modules/selection.c"

#line 2106 "src/modules/selection.c"
/* Store the signed 16-bit menu choice as a language word, even when unchanged.
 * On a change, replace old/current thirteen-texture sets in original file order.
 * Preserve graphics waits and word-sized language reloads after asset calls.
 * Update the language-dependent speed option and return via the current menu.
 * RE_UNKNOWN: choice producers must establish language 0..2; no local clamp.
 * Speed-option physical meaning remains unproved; trace menu/option consumers. */
void selectionApplyChosenLanguageAndReloadTextures(void) {
    s32 language;
    s32 previousLanguage;
    AgentLanguageExpressionMenu *menu = (AgentLanguageExpressionMenu *)D_selection_00421D1C;
    previousLanguage = gGameSettings->currentLanguage;
    language = menu->choices->selected;
    if (previousLanguage != (gGameSettings->currentLanguage = language)) {
        switch (previousLanguage) {
        case 0:
            gUvGfxMgrExports->unk74();
            uvUnloadFile('UVTX',0x31);
            uvUnloadFile('UVTX',0x4A);
            uvUnloadFile('UVTX',0x6);
            uvUnloadFile('UVTX',0x3C);
            uvUnloadFile('UVTX',0x14);
            uvUnloadFile('UVTX',0x4B);
            uvUnloadFile('UVTX',0x1C);
            uvUnloadFile('UVTX',0x41);
            uvUnloadFile('UVTX',0x3F);
            uvUnloadFile('UVTX',0x44);
            uvUnloadFile('UVTX',0x15);
            uvUnloadFile('UVTX',0x18);
            uvUnloadFile('UVTX',0x56F);
            language = D_80025E64;
            break;
        case 1:
            gUvGfxMgrExports->unk74();
            uvUnloadFile('UVTX',0x57C);
            uvUnloadFile('UVTX',0x5A1);
            uvUnloadFile('UVTX',0x58D);
            uvUnloadFile('UVTX',0x599);
            uvUnloadFile('UVTX',0x58F);
            uvUnloadFile('UVTX',0x5A3);
            uvUnloadFile('UVTX',0x595);
            uvUnloadFile('UVTX',0x59F);
            uvUnloadFile('UVTX',0x591);
            uvUnloadFile('UVTX',0x593);
            uvUnloadFile('UVTX',0x597);
            uvUnloadFile('UVTX',0x59D);
            uvUnloadFile('UVTX',0x44);
            language = D_80025E64;
            break;
        case 2:
            gUvGfxMgrExports->unk74();
            uvUnloadFile('UVTX',0x57B);
            uvUnloadFile('UVTX',0x5A0);
            uvUnloadFile('UVTX',0x58C);
            uvUnloadFile('UVTX',0x598);
            uvUnloadFile('UVTX',0x58E);
            uvUnloadFile('UVTX',0x5A2);
            uvUnloadFile('UVTX',0x594);
            uvUnloadFile('UVTX',0x59E);
            uvUnloadFile('UVTX',0x590);
            uvUnloadFile('UVTX',0x592);
            uvUnloadFile('UVTX',0x596);
            uvUnloadFile('UVTX',0x59C);
            uvUnloadFile('UVTX',0x44);
            language = D_80025E64;
            break;
        }
        switch (language) {
        case 0:
            gUvGfxMgrExports->unk74();
            uvLoadFile('UVTX',0x31);
            uvLoadFile('UVTX',0x4A);
            uvLoadFile('UVTX',0x6);
            uvLoadFile('UVTX',0x3C);
            uvLoadFile('UVTX',0x14);
            uvLoadFile('UVTX',0x4B);
            uvLoadFile('UVTX',0x1C);
            uvLoadFile('UVTX',0x41);
            uvLoadFile('UVTX',0x3F);
            uvLoadFile('UVTX',0x44);
            uvLoadFile('UVTX',0x15);
            uvLoadFile('UVTX',0x18);
            uvLoadFile('UVTX',0x56F);
            D_80025E69 = 1;
            break;
        case 1:
            gUvGfxMgrExports->unk74();
            uvLoadFile('UVTX',0x57C);
            uvLoadFile('UVTX',0x5A1);
            uvLoadFile('UVTX',0x58D);
            uvLoadFile('UVTX',0x599);
            uvLoadFile('UVTX',0x58F);
            uvLoadFile('UVTX',0x5A3);
            uvLoadFile('UVTX',0x595);
            uvLoadFile('UVTX',0x59F);
            uvLoadFile('UVTX',0x591);
            uvLoadFile('UVTX',0x593);
            uvLoadFile('UVTX',0x597);
            uvLoadFile('UVTX',0x59D);
            uvLoadFile('UVTX',0x44);
            D_80025E69 = 0;
            break;
        case 2:
            gUvGfxMgrExports->unk74();
            uvLoadFile('UVTX',0x57B);
            uvLoadFile('UVTX',0x5A0);
            uvLoadFile('UVTX',0x58C);
            uvLoadFile('UVTX',0x598);
            uvLoadFile('UVTX',0x58E);
            uvLoadFile('UVTX',0x5A2);
            uvLoadFile('UVTX',0x594);
            uvLoadFile('UVTX',0x59E);
            uvLoadFile('UVTX',0x590);
            uvLoadFile('UVTX',0x592);
            uvLoadFile('UVTX',0x596);
            uvLoadFile('UVTX',0x59C);
            uvLoadFile('UVTX',0x44);
            D_80025E69 = 0;
            break;
        }
        menu = (AgentLanguageExpressionMenu *)D_selection_00421D1C;
    }
    selectionActivateMenuNode(menu->returnMenu);
}
#line 2107 "src/modules/selection.c"

#line 2108 "src/modules/selection.c"
/* Set language ID 1 and the speed option byte to one, then return
 * through the existing menu node. Language labels are not inferred here. */
void selectionChooseLanguage1AndSpeedOption(void) {
    gGameSettings->currentLanguage = 1;
    gGameSettings->optionsSpeed = 1;
    selectionActivateMenuNode(*(s32*)((u8*)D_selection_00421D1C + 4));
}
#line 2113 "src/modules/selection.c"

#line 2114 "src/modules/selection.c"
/* Set language ID 2 and the speed option byte to one, then return
 * through the existing menu node. Language labels are not inferred here. */
void selectionChooseLanguage2AndSpeedOption(void) {
    gGameSettings->currentLanguage = 2;
    gGameSettings->optionsSpeed = 1;
    selectionActivateMenuNode(*(s32*)((u8*)D_selection_00421D1C + 4));
}
#line 2119 "src/modules/selection.c"

/* Inferred struct for items in the InnerObj array (size 0x14) */
/* Inferred struct pointed to by D_selection_00421D1C->unk8 (InnerObj at offset 8 of D1C target) */
/* Inferred struct layout for what D_selection_00421D1C points to (InnerObj* at offset 8) */
/* Inferred struct pointed to by D_selection_00421B90 (cast-only, no extern redecl) */
/* Handles controller confirm input for selection screen, sets game state and selected function pointer */
#line 2125 "src/modules/selection.c"
/* Poll the current menu and schedule its selected callback once
 * while action eight is held. Set transition mode two and clear its
 * scalar only on that first action; release clears the shared latch.
 * Preserve the original unchecked callback-table index. */
void selectionScheduleChosenMenuActionOnce(void) {
    InnerObj_0041B19C *menuEntries;

    D_selection_00420DE8 = 0;
    ((ContExp_0041B19C *)D_selection_00421B90)->unk4(&D_selection_00421CF0, 0, ((D1CTarget_0041B19C *)D_selection_00421D1C)->unk8);
    if (((ContExp_0041B19C *)D_selection_00421B90)->unk8(0, ((D1CTarget_0041B19C *)D_selection_00421D1C)->unk8) == 8) {
        if (*(u8 *)&D_selection_00421CF0 == 0) {
            D_selection_00421CF0 = 1;
            menuEntries = ((D1CTarget_0041B19C *)D_selection_00421D1C)->unk8;
            D_selection_00421D28 = (s32)D_selection_00420F18[menuEntries->unk8[menuEntries->unk4].unk4];
            D_selection_00420DE8 = 2;
            D_selection_00420DEC = 0;
        }
    } else {
        D_selection_00421CF0 = 0;
    }
}
#line 2142 "src/modules/selection.c"

/* Draw the original multilingual language question using FONT slots
 * 0x04, 0x18, and 0x1C for font 1, text width, and font height. Preserve
 * each provider reload and capture the current node after those callbacks.
 * Read the signed coordinate halfwords through node offset 0x0C and
 * the word at offset 0x1C. Forward x - width/2 and
 * y + 2 * (height + word1C) to MENU slot 0x40 with the original words
 * 1, 30, 227, 255, 255, text address, and 1. Signed division truncates
 * toward zero. Width uses D_selection_0041F0BC; drawing uses the distinct
 * D_selection_0041F0D8. Both original readonly literals contain
 * "Language? Sprache? Langue?"; their separate storage identities remain.
 * RE_UNKNOWN: complete node/coordinate storage and ownership, node word
 * 0x1C meaning and domain, callback/export declarations, and font/resource
 * lifetimes across calls. Original node producers, callback registration,
 * resource setup and callers must establish those contracts; local null
 * checks are absent, but invalid-domain reachability is unproved.
 * Recovery remains deferred: both drafts contain 228 native/draft bytes.
 * The first differs in ten words; one bounded sum-first expression and
 * used-scalar declaration refinement restores the original width home at
 * SP+48, within the same 56-byte frame. Eight remaining words change roles for
 * the node word, y coordinate, arithmetic and MENU base. All fourteen
 * complete object relocation records agree as a multiset; pair emission
 * order differs. No missing operation or ABI discrepancy was identified.
 * Historical source/storage evidence is needed before another attempt;
 * retain original ASM without invented padding or register-shape changes. */
#line 2143 "src/modules/selection.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041B28C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041B370.s")

