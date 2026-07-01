// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern void *gCamExports;
extern s32 D_med_00406C00;
extern s32 D_med_00407F28;
extern void *D_med_004080A0;
extern s32 D_med_00407F64;
extern s32 D_med_00407FB0;
extern s32 D_med_00407F68;
extern s32 D_med_00407FC0;
extern s32 D_med_00407FDC;
extern void *gUvTexAnimExports;
void func_med_004000DC();
void func_med_00400160();
void func_med_004007B4();
void func_med_004008C0();
void func_med_004008F0();
void func_med_00400D18();
void func_med_00401174();
void func_med_004011B4();
void func_med_0040144C(s32 arg0);
void func_med_004014C4();
void func_med_00401C10();
void func_med_00401EF8();
void func_med_004021A0();
void func_med_004023E0();
void func_med_00402920();
void func_med_00402C7C();
void func_med_00404FB8();
void func_med_00404FE0();
void func_med_0040505C();
void func_med_00405128();
void func_med_00405168();
void func_med_004051A8();
void func_med_004052C8();
void func_med_00405338();
void func_med_004053B4();
void func_med_00405488();
void func_med_004057A8();
void func_med_004059E8();
void func_med_00405DC4();
void func_med_00405FEC();
void func_med_00406204();
void func_med_004062BC();
void func_med_004063D4();
void func_med_00406420();
#include "ultra64.h"
/*__SEEDEXTERNS__*/
typedef struct MedObj_s {
    char pad0[0x248];
    s32 unk248;
} MedObj;
typedef struct D_med_00408028_s {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} D_med_00408028_t;
typedef struct LightExports_s {
    char pad0[0x8];
    void (*unk8)(void *, s32, s32, f64, f64, f64, s32);
} LightExports;
typedef struct SceneExports2_s {
    char pad0[0x2C];
    void *unk2C;
} SceneExports2;
extern MedObj *D_med_00407F08;
extern D_med_00408028_t D_med_00408028;
extern LightExports *gLightExports;
extern SceneExports2 *gSceneExports;
extern f32 D_med_00407FE4;
extern f32 D_med_00407FE8;
extern f32 D_med_00407FEC;
extern f32 D_med_00407FF0;

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/__entrypoint_func_med_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004000DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00400160.s")

void func_med_0040078C(void) {
    func_med_004021A0();
}

void func_med_004007AC(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004007B4.s")

void func_med_004008C0(s32 arg0) {
    (*(void (**)(s32))((u8*)gCamExports + 0x8))(*(s32*)arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004008F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00400D18.s")

void func_med_00401174(void) {
    if (D_med_00406C00 == 0) {
        func_med_00400D18();
        return;
    }
    func_med_004008F0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004011B4.s")

void func_med_0040144C(s32 arg0) {
    D_med_00407FE4 = (f32) ((arg0 >> 0x18) & 0xFF) / 255.0f;
    D_med_00407FE8 = (f32) ((arg0 >> 0x10) & 0xFF) / 255.0f;
    D_med_00407FEC = (f32) ((arg0 >> 8) & 0xFF) / 255.0f;
    D_med_00407FF0 = (f32) (arg0 & 0xFF) / 255.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004014C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00401C10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00401EF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004021A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004023E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00402920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00402C7C.s")

void func_med_00404FB8(s32 arg0) {
    s32 temp;
    temp = *(s32*)((u8*)&D_med_00407F28 + 0x0);
    if (temp != 0) {
        *(u8*)(temp + 0x23) = *(s32*)((u8*)&D_med_00407F28 + 0x2C);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00404FE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_0040505C.s")

void func_med_00405128(s32 arg0) {
    (*(void (**)(s32, u8*, s32))((u8*)D_med_004080A0 + 0x10))(D_med_00407F64, &D_med_00407FB0, 0xFA);
}

void func_med_00405168(s32 arg0) {
    (*(void (**)(s32, u8*, s32))((u8*)D_med_004080A0 + 0x10))(D_med_00407F68, &D_med_00407FC0, 0xFB);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004051A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004052C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004053B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004057A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004059E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405FEC.s")

void func_med_00406204(s32 a0) {
    if (D_med_00407FDC != -1) {
        func_med_004014C4();
    }
}

/* Set a light via gLightExports->unk8, using a scene-object pointer and three f32 RGB/dir values from a global table. */
void func_med_00406238(s32 arg0) {
    if (D_med_00407F08 != NULL) {
        gLightExports->unk8((char *)gSceneExports->unk2C + 0x28, D_med_00407F08->unk248, 1,
                            (f64) D_med_00408028.unk0, (f64) D_med_00408028.unk4,
                            (f64) D_med_00408028.unk8, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004062BC.s")

void func_med_004063CC(s16 a0) {
}

void func_med_004063D4(s32 arg0) {
    (*(void (**)(void))((u8*)gUvTexAnimExports + 0x8))();
    (*(void (**)(void))((u8*)gUvTexAnimExports + 0x4))();
}

void func_med_00406418(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00406420.s")

