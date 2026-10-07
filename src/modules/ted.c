// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[8]; void (*update)(void); } TedFrameExports;
typedef struct { u8 unk00[0x28]; void (*update)(s32, void *); } TedCameraFrameExports;
extern s16 D_80025D76;
extern void *D_ted_004071B8, *gCamExports;
extern s32 D_ted_0040722C, D_ted_00407224, D_ted_004071E4;
typedef struct { u8 unk00[0x28]; struct TedResetRecord *records[80]; u16 count; s16 selectedIndex; } TedRecordPool;
#include "module.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
typedef struct TedGuiState {
    u8 unk00[0x1E];
    u16 unk1E;
    u16 unk20;
    u8 unk22[2];
    f32 unk24;
    f32 unk28;
    s32 unk2C;
    f32 unk30;
    f32 unk34;
    u8 unk38[8];
    s32 unk40;
    s32 unk44;
} TedGuiState;


/* Fields are named by byte offset until the track editor consumers establish meaning. */
typedef struct TedResetRecord {
    u8 unk00[0xC];
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 unk16[6];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    void *unk28;
    s32 unk2C;
    s32 unk30;
} TedResetRecord;

typedef struct {
    char pad00[0x9C];
    void (*unk9C)(s32, char *);
    char padA0[0x28];
    void (*unkC8)(void *, s16, s16, s16, s32);
} TedGuiExports;
extern TedGuiExports *gUvGuiExports;
extern s32 D_ted_004072B0;
extern char D_ted_00406FB8[];
extern char D_ted_00406FC0[];
typedef struct TedSelectedRecord {
    u8 unk00[0xC];
    f32 unk0C, unk10, unk14, unk18, unk1C, unk20, unk24;
    u8 unk28[4];
} TedSelectedRecord; /* Original array stride: 0x2C bytes. */
typedef struct {
    char pad00[0x84];
    s32 unk84;
    char pad88[0xC];
    f32 unk94, unk98, unk9C, unkA0, unkA4, unkA8, unkAC;
    char padB0[4];
    s32 unkB4;
} TedCheckData;
extern TedSelectedRecord *D_ted_00407288;
extern TedCheckData D_ted_004071C0;
extern u8 *D_ted_00407290;
void tedResetRecordPool(TedRecordPool *pool);
void func_ted_00400558();
void tedDispatchFrameAndCamera(void);
void func_ted_004007B8();
void func_ted_00400C18();
void func_ted_00401004();
void func_ted_00401338();
void func_ted_00401A8C();
void func_ted_00401C6C();
void func_ted_00402320();
void func_ted_00402E58();
void func_ted_004031A0();
void func_ted_004034E8();
void func_ted_00403830();
void func_ted_00403874();
void func_ted_004038B8();
void func_ted_00403A58();
void func_ted_00403C20();
void func_ted_00403E90();
void func_ted_00403FC0();
void func_ted_004040B4();
void func_ted_004043A8();
void func_ted_00404468();
void func_ted_0040465C();
void func_ted_004047DC();
void tedApplySelectedScalar18(s32 unused);
void tedApplySelectedScalar1C(s32 unused);
void tedApplySelectedScalar20(s32 unused);
void tedApplySelectedScalar24(s32 unused);
void func_ted_00404C28();
void tedApplySelectedScalar0C(s32 unused);
void tedApplySelectedScalar10(s32 unused);
void tedApplySelectedScalar14(s32 unused);
void func_ted_00404DA8();
void func_ted_00404F58();
void func_ted_00405018();
void func_ted_004051F0();
void func_ted_00405344();
void func_ted_0040561C();
void func_ted_004057C0();
void func_ted_00405804();
void func_ted_0040590C();
void func_ted_004059BC();
void func_ted_00405B94();
void func_ted_00405C9C();
void func_ted_00405EE8();
void func_ted_0040607C();
void func_ted_00406178();
void func_ted_00406280();
void func_ted_00406330();
void func_ted_00406508();
void func_ted_00406610();
void func_ted_0040685C();
void func_ted_004069F0();
void func_ted_00406B04();
void tedResetRecordPool();
void tedResetRecord(TedResetRecord *record);
void tedResetGuiState(TedGuiState *state);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/__entrypoint_func_ted_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00400558.s")

#line 132 "src/modules/ted.c"
/* A nonzero shared frame flag delegates to editor export eight and returns.
 * Otherwise dispatch editor modes zero/one, then update the original camera
 * from its shared state. Other editor modes still perform the camera update. */
void tedDispatchFrameAndCamera(void) {
    if (D_80025D76 != 0) {
        ((TedFrameExports *)D_ted_004071B8)->update();
        return;
    }
    switch (D_ted_0040722C) {
    case 0: func_ted_004007B8(); break;
    case 1: func_ted_00400C18(); break;
    }
    ((TedCameraFrameExports *)gCamExports)->update(D_ted_00407224, &D_ted_004071E4);
}
#line 133 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004007B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00400C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401004.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00401C6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00402320.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00402E58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004031A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004034E8.s")

void func_ted_00403830(void) {
    gUvGuiExports->unk9C(D_ted_004072B0, D_ted_00406FB8);
    tedResetRecordPool(D_ted_004072B0);
}

void func_ted_00403874(void) {
    gUvGuiExports->unk9C(D_ted_004072B0, D_ted_00406FC0);
    tedResetRecordPool(D_ted_004072B0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004038B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403A58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403C20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403E90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00403FC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004040B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004043A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040465C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004047DC.s")

#line 178 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x18.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar18(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk18 = D_ted_004071C0.unk94;
    }
}
#line 179 "src/modules/ted.c"

#line 180 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x1C.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar1C(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk1C = D_ted_004071C0.unk98;
    }
}
#line 181 "src/modules/ted.c"

#line 182 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x20.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar20(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk20 = D_ted_004071C0.unk9C;
    }
}
#line 183 "src/modules/ted.c"

#line 184 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x24.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar24(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk24 = D_ted_004071C0.unkA0;
    }
}
#line 185 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404C28.s")

#line 188 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x0C.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar0C(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk0C = D_ted_004071C0.unkA4;
    }
}
#line 189 "src/modules/ted.c"

#line 190 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x10.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar10(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk10 = D_ted_004071C0.unkA8;
    }
}
#line 191 "src/modules/ted.c"

#line 192 "src/modules/ted.c"
/* Apply the pending editor scalar to selected record field 0x14.
 * A negative index leaves the record array unchanged. Retain the original
 * 0x2C stride and offset name until consumers establish the scalar meaning. */
void tedApplySelectedScalar14(s32 unused) {
    s32 selectedIndex;

    selectedIndex = D_ted_004071C0.unk84;
    if (selectedIndex >= 0) {
        D_ted_00407288[selectedIndex].unk14 = D_ted_004071C0.unkAC;
    }
}
#line 193 "src/modules/ted.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404F58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004051F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405344.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040561C.s")

void func_ted_004057C0(s32 arg0) {
    s32 v0 = D_ted_004071C0.unk84;
    if (v0 >= 0) {
        ((u8 *)D_ted_00407290)[v0 * 0x2C + 1] = D_ted_004071C0.unkB4;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405804.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040590C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004059BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405B94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405C9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00405EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040607C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406280.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_0040685C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_004069F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406B04.s")

#line 243 "src/modules/ted.c"
/* Reset and clear all 80 record pointers, then reset count and selection.
 * A null pool is ignored; resetting records preserves their existing ownership. */
void tedResetRecordPool(TedRecordPool *pool) {
    s32 index;
    if (pool != NULL) {
        for (index = 0; index < 80; index++) {
            tedResetRecord(pool->records[index]);
            pool->records[index] = NULL;
        }
        pool->count = 0;
        pool->selectedIndex = -1;
    }
}
#line 244 "src/modules/ted.c"

#line 210 "src/modules/ted.c"
/* For a non-null record, reset the nested GUI state referenced by field 0x28,
 * then restore the original halfword defaults and clear the six word fields.
 * Unknown fields retain offset names rather than speculative editor meanings. */
void tedResetRecord(TedResetRecord *record) {
    if (record != NULL) {
        tedResetGuiState(record->unk28);
        record->unk0C = 0;
        record->unk0E = 0;
        record->unk10 = 0x41;
        record->unk12 = 0;
        record->unk14 = 0xC;
        record->unk1C = 0;
        record->unk20 = 0;
        record->unk24 = 0;
        record->unk28 = 0;
        record->unk2C = 0;
        record->unk30 = 0;
    }
}
#line 211 "src/modules/ted.c"

#line 212 "src/modules/ted.c"
/* Restore the nested GUI state's original defaults and request a centered
 * 180-by-40 rectangle. Preserve all four original screen-size queries and
 * signed half-coordinate conversions rather than replacing them with shifts. */
void tedResetGuiState(TedGuiState *state) {
    s32 screenHeightForBottom;
    s32 screenHeightForTop;
    s32 screenWidthForRight;
    s32 screenWidthForLeft;

    if (state != NULL) {
        state->unk1E = 0;
        state->unk20 = 0x11;
        state->unk2C = 0;
        state->unk44 = 0;
        state->unk30 = 1.0f;
        state->unk28 = 0.0f;
        state->unk24 = 0.0f;
        state->unk34 = -1.0f;
        screenWidthForLeft = gUvGfxMgrExports->uvGetScreenWidth();
        screenWidthForRight = gUvGfxMgrExports->uvGetScreenWidth();
        screenHeightForTop = gUvGfxMgrExports->uvGetScreenHeight();
        screenHeightForBottom = gUvGfxMgrExports->uvGetScreenHeight();
        gUvGuiExports->unkC8(state, (s16) ((s32) (screenWidthForLeft - 0xB4) / 2), (s16) ((s32) (screenWidthForRight + 0xB4) / 2), (s16) ((s32) (screenHeightForTop - 0x28) / 2), (s32) (screenHeightForBottom + 0x28) / 2);
        state->unk40 = 0;
    }
}
#line 213 "src/modules/ted.c"

