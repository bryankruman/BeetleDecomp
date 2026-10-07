// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvfmtx_rom.h"
#include "uvgfxmgr_rom.h"
#include "uvgfxstate_rom.h"
#include "uvdgeom_rom.h"
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern UvGfxMgr_Exports *gUvGfxMgrExports;
extern UvGfxState_Rom_Exports *gUvGfxStateExports;
extern UvDGeom_Rom_Exports *gUvDGeomExports;
/*__SEEDEXTERNS__*/
extern s32 gDebugHudState;
extern s16 D_80025D78;
extern u8 D_plyr_00406B68;
extern u8 D_plyr_00406B70;
extern u8 D_plyr_00406B78;
extern u8 D_plyr_00406B80;
extern u8 D_plyr_00406B88;
extern u8 D_plyr_00406B90;
extern u8 D_plyr_00406B98;
extern u8 D_plyr_00406BA0;
extern s32 D_plyr_0040690C;
typedef struct { char pad00[0x30]; void (*unk30)(void); } UnkStruct_D_plyr_00406B1C;
typedef struct { char pad00[0x24]; void (*unk24)(s32); } UnkStruct_D_plyr_00406B20;
typedef struct { char pad00[0x70]; void (*unk70)(void *); } UnkStruct_80025C78;
extern UnkStruct_D_plyr_00406B1C *D_plyr_00406B1C;
extern UnkStruct_D_plyr_00406B20 *D_plyr_00406B20;
extern UnkStruct_80025C78 *gSndExports;
extern u8 D_plyr_00406B48[];
void func_plyr_00400590();
void func_plyr_00400678();
void func_plyr_00400C3C();
void func_plyr_00401484();
void func_plyr_00401DC4();
void func_plyr_00402220();
void func_plyr_00402268();
s32 func_plyr_004022E0(s32 arg0);
void func_plyr_00402340();
void func_plyr_00402B90();
void func_plyr_00402F14();
void func_plyr_0040397C();
void func_plyr_00403B40();
void func_plyr_00404088();
void plyrDrawRedArrowWithShadow(Mtx4F *matrix);
void func_plyr_004047C8();
void func_plyr_00404CE0();
void func_plyr_004050AC();
void func_plyr_00405624();
void func_plyr_00405688();
void func_plyr_00405C1C();
void func_plyr_00406604();
extern s32 D_plyr_00406B28[];
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/__entrypoint_func_plyr_400000.s")

void func_plyr_00400590(void) {
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B70);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B78);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B68);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B80);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B88);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B90);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B98);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406BA0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00400678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00400C3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00401484.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00401DC4.s")

void func_plyr_00402220(s32 a0) {
    D_plyr_00406B1C->unk30();
    D_plyr_00406B20->unk24(a0);
}

void func_plyr_00402268(void) {
    (*(void (**)(void))((u8 *)D_plyr_00406B1C + 0x34))();
    if (D_plyr_0040690C < 3) {
        if (*(s16 *)&D_80025D78 == 0 || *(s16 *)&D_80025D78 == 3) {
            func_plyr_00402340();
        }
    }
}

s32 func_plyr_004022CC(s32 a0) {
    return D_plyr_00406B28[a0];
}

s32 func_plyr_004022E0(s32 arg0)
{
  s32 var_v1;
 var_v1 = 0; if (D_plyr_0040690C > 0) { do { if (arg0 == (*((s32 *) (((u8 *) (*((void **) (((u8 *) (&D_plyr_00406B28)) + (var_v1 * 4))))) + 0x18)))) {
        return var_v1;
      }
      var_v1 = (var_v1 + 1) & 0xFFFF;
    }
    while (((s32) var_v1) < D_plyr_0040690C);
    arg0 = arg0;
  }
  return -1;
}

void func_plyr_00402338(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00402340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00402B90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00402F14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_0040397C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00403B40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00404088.s")

#line 122 "src/modules/plyr.c"
/* Draw the original red player arrow and offset translucent black shadow.
 * Use current screen dimensions for projection, translate the supplied matrix
 * by -14 on Y and preserve the original matrix/state stack operations. */
void plyrDrawRedArrowWithShadow(Mtx4F *matrix) {
    Mtx4F projection;
    s32 width;
    width = gUvGfxMgrExports->uvGetScreenWidth();
    gUvFmtxExports->uvMat4SetOrtho(&projection,0.0f,(f32)(width - 1),0.0f,(f32)(gUvGfxMgrExports->uvGetScreenHeight() - 1));
    gUvFmtxExports->uvGfxMtxProjPushF(&projection);
    gUvGfxStateExports->uvGfxStateBindTexture(0xFFF);
    gUvGfxStateExports->uvGfxStateSetFlags(0x400000);
    gUvFmtxExports->uvMat4LocalTranslate(matrix,0.0f,-14.0f,0.0f);
    gUvFmtxExports->func_uvfmtx_rom_004029DC(matrix);
    gUvDGeomExports->uvVtxBeginPoly();
    gUvDGeomExports->uvVtx(-1,0,0,0,0,0,0,0,128);
    gUvDGeomExports->uvVtx(-3,0,0,0,0,0,0,0,128);
    gUvDGeomExports->uvVtx(-2,-21,0,0,0,0,0,0,128);
    gUvDGeomExports->uvVtxEndPoly();
    gUvDGeomExports->uvVtxBeginPoly();
    gUvDGeomExports->uvVtx(1,0,0,0,0,200,0,0,255);
    gUvDGeomExports->uvVtx(-1,0,0,0,0,200,0,0,255);
    gUvDGeomExports->uvVtx(0,-21,0,0,0,200,0,0,255);
    gUvDGeomExports->uvVtxEndPoly();
    gUvFmtxExports->uvGfxMtxFViewPop();
    gUvGfxStateExports->uvGfxClearCurrentStateBits(0x400000);
}
#line 123 "src/modules/plyr.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_004047C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00404CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_004050AC.s")

void func_plyr_00405624(s32 arg0) {
    s32 temp_v0;

    temp_v0 = gDebugHudState;
    if (temp_v0 == 1 || temp_v0 == 3) {
        func_plyr_00405688(arg0);
        temp_v0 = gDebugHudState;
    }
    if (temp_v0 == 2 || temp_v0 == 3) {
        func_plyr_00405C1C(arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00405688.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00405C1C.s")

void func_plyr_00406604(void *a0) {
    gSndExports->unk70(D_plyr_00406B48 + *(s32 *)((u8 *)a0 + 0x14) * 8);
}

