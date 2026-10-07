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
/* Original MOTN slots: 0x30 -> func_motion_00405E5C;
 * 0x34 -> motionUpdateSharedState(void).
 * Slot 0x30 returns immediately, storing incoming a0 in its argument home
 * at 0(sp) in the return delay slot; preserve this original machine input.
 * RE_UNKNOWN: intended original argument/result contract of empty slot 0x30.
 * Its current target C declares one s32; retain this caller's no-argument view
 * until original callers establish the prototype. An empty body is insufficient.
 */
typedef struct {
    u8 prefix[0x30];
    void (*emptyCallback30)(void);
    void (*updateSharedState)(void);
} PlyrMotionExports;
typedef struct { char pad00[0x24]; void (*unk24)(s32); } UnkStruct_D_plyr_00406B20;
typedef struct { char pad00[0x70]; void (*unk70)(void *); } UnkStruct_80025C78;
extern PlyrMotionExports *D_plyr_00406B1C;
extern UnkStruct_D_plyr_00406B20 *D_plyr_00406B20;
extern UnkStruct_80025C78 *gSndExports;
extern u8 D_plyr_00406B48[];
void plyrReleaseSharedSoundHandles();
void func_plyr_00400678();
void func_plyr_00400C3C();
void func_plyr_00401484();
void func_plyr_00401DC4();
void plyrInvokeMotionNoopAndCarAudioCallback();
void plyrUpdateMotionAndConditionallyDispatch();
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
void plyrDispatchDebugHudPasses();
void func_plyr_00405688();
void func_plyr_00405C1C();
void plyrReleaseIndexedSoundHandle();
extern s32 D_plyr_00406B28[];
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/__entrypoint_func_plyr_400000.s")

#line 56 "src/modules/plyr.c"
/* Release eight shared player sound handles in their original order.
 * RE_UNKNOWN: storage ownership and safe handle lifetime require original initialization, users and release paths; global addresses alone establish neither. */
void plyrReleaseSharedSoundHandles(void) {
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B70);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B78);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B68);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B80);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B88);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B90);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406B98);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_plyr_00406BA0);
}
#line 66 "src/modules/plyr.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00400678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00400C3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00401484.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00401DC4.s")

#line 75 "src/modules/plyr.c"
/* Invoke motion export 0x30, then pass the supplied
 * word to car-audio export 0x24. Original player initialization binds these
 * dependencies to tags 'motn' and 'cara', respectively.
 * Original motion slot 0x30 returns immediately after storing incoming a0
 * into its argument home at 0(sp); retain that original machine input.
 * RE_UNKNOWN: empty motion callback's intended argument/result prototype and
 * the car-audio callback's word meaning. Preserve existing call forms; resolve
 * original callers and car-audio slot 0x24 before assigning parameter roles. */
void plyrInvokeMotionNoopAndCarAudioCallback(s32 a0) {
    D_plyr_00406B1C->emptyCallback30();
    D_plyr_00406B20->unk24(a0);
}
#line 79 "src/modules/plyr.c"

#line 80 "src/modules/plyr.c"
/* Invoke motionUpdateSharedState through proven motion export 0x34,
 * then run the original player helper when shared word 0x0040690C is below
 * three and the shared halfword is zero or three.
 * RE_UNKNOWN: broader roles of these shared values and the conditional helper.
 * Trace their original writers and helper callers before interpreting the
 * conditions as a particular gameplay mode or player-count rule. */
void plyrUpdateMotionAndConditionallyDispatch(void) {
    D_plyr_00406B1C->updateSharedState();
    if (D_plyr_0040690C < 3) {
        if (*(s16 *)&D_80025D78 == 0 || *(s16 *)&D_80025D78 == 3) {
            func_plyr_00402340();
        }
    }
}
#line 88 "src/modules/plyr.c"

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

#line 107 "src/modules/plyr.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_plyr_00402338(void) {
}
#line 109 "src/modules/plyr.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00402340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00402B90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00402F14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_0040397C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00403B40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00404088.s")

#line 122 "src/modules/plyr.c"
/* Draw the red arrow and translucent black shadow using current screen dimensions.
 * Apply local-Y displacement -14 directly to the caller's matrix; popping graphics state does not restore its translation row.
 * RE_UNKNOWN: caller matrix reuse and coordinate units require original callsites and input-matrix construction; preserve the original stack operations. */
void plyrDrawRedArrowWithShadow(Mtx4F *matrix) {
    Mtx4F projection;
    s32 width;
    width = gUvGfxMgrExports->uvGetScreenWidth();
    gUvFmtxExports->uvMat4SetOrtho(&projection,0.0f,(f32)(width - 1),0.0f,(f32)(gUvGfxMgrExports->uvGetScreenHeight() - 1));
    gUvFmtxExports->uvGfxMtxProjPushF(&projection);
    gUvGfxStateExports->uvGfxStateBindTexture(0xFFF);
    gUvGfxStateExports->uvGfxStateSetFlags(0x400000);
    gUvFmtxExports->uvMat4LocalTranslate(matrix,0.0f,-14.0f,0.0f);
    gUvFmtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(matrix);
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

#line 130 "src/modules/plyr.c"
/* Run the first debug HUD pass for modes one/three and the second for
 * modes two/three. Re-read the mode after the first pass as originally done. */
void plyrDispatchDebugHudPasses(s32 player) {
    s32 mode;

    mode = gDebugHudState;
    if (mode == 1 || mode == 3) {
        func_plyr_00405688(player);
        mode = gDebugHudState;
    }
    if (mode == 2 || mode == 3) {
        func_plyr_00405C1C(player);
    }
}
#line 142 "src/modules/plyr.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00405688.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/plyr/func_plyr_00405C1C.s")

#line 147 "src/modules/plyr.c"
/* Release the sound handle selected by the caller record word at 0x14
 * from shared storage D_plyr_00406B48, using the original eight-byte stride.
 * RE_UNKNOWN: shared handle-array extent, index validity and handle lifetime.
 * The wrapper does not establish caller ownership of that global array.
 * Trace original array initialization, index writers and release paths before
 * assigning an ownership contract or proving the unchecked index bound. */
#line 151 "src/modules/plyr.c"
void plyrReleaseIndexedSoundHandle(void *record) {
    gSndExports->unk70(D_plyr_00406B48 + *(s32 *)((u8 *)record + 0x14) * 8);
}
#line 150 "src/modules/plyr.c"

