// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

typedef struct { char pad00[0x9C]; void (*unk9C)(s32, char *); } TedGuiExports;
extern TedGuiExports *gUvGuiExports;
extern s32 D_ted_004072B0;
extern char D_ted_00406FB8[];
extern char D_ted_00406FC0[];
typedef struct { char pad00[0x84]; s32 unk84; char pad88[0x2C]; s32 unkB4; } TedCheckData;
extern TedCheckData D_ted_004071C0;
extern u8 *D_ted_00407290;
void func_ted_00406BD0(s32 arg0);
void func_ted_00400558();
void func_ted_00400718();
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
void func_ted_00404B18();
void func_ted_00404B5C();
void func_ted_00404BA0();
void func_ted_00404BE4();
void func_ted_00404C28();
void func_ted_00404CDC();
void func_ted_00404D20();
void func_ted_00404D64();
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
void func_ted_00406BD0();
void tedResetRecord(TedResetRecord *record);
void func_ted_00406C9C();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/__entrypoint_func_ted_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00400558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00400718.s")

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
    func_ted_00406BD0(D_ted_004072B0);
}

void func_ted_00403874(void) {
    gUvGuiExports->unk9C(D_ted_004072B0, D_ted_00406FC0);
    func_ted_00406BD0(D_ted_004072B0);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404B18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404B5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404BA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404BE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404C28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404CDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00404D64.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406BD0.s")

#line 210 "src/modules/ted.c"
/* For a non-null record, reset the nested GUI state referenced by field 0x28,
 * then restore the original halfword defaults and clear the six word fields.
 * Unknown fields retain offset names rather than speculative editor meanings. */
void tedResetRecord(TedResetRecord *record) {
    if (record != NULL) {
        func_ted_00406C9C(record->unk28, record);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406C9C.s")

