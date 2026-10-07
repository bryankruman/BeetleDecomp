// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
typedef struct { u8 unk00[0x260]; Mtx4F basis; u8 unk2A0[0x13C]; Vec3F direction; } CarAnimBasisState;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern UvFVec_Rom_Exports *gUvFvecExports;
#include "uvfvec_rom.h"
#include "uvquat_rom.h"
#include "uvdobj_rom.h"
extern UvDobj_Exports *gUvDobjExports;
typedef struct { u8 unk00[0x404]; s32 colorIndex; } CarAnimColorContext;
typedef struct { u8 unk00[8]; s32 key; u8 unk0C[0x230]; u8 flag23C; } CarAnimRegisteredState;
/*__SEEDEXTERNS__*/
extern void *gUvChanExports;
extern void *gUvCbckExports;
extern void func_caranim_00405B7C(void);
extern void *gUvPfxExports;
extern void *gUvGeomExports;
extern void *gUvGfxStateExports;
extern s32 D_caranim_004066A0;
extern s32 D_caranim_00407228;
extern s32 gOptionsLanguage;
extern CarAnimRegisteredState *D_caranim_00407348[8];
extern s32 D_caranim_00406830;
extern s32 D_caranim_00407178;
extern s32 gDebugDefaultMaterial;
extern void func_caranim_004007B0(void *);
extern void func_caranim_00400B08(void *);
void caranimUnloadEffectModules();
void func_caranim_004003AC();
void func_caranim_00400788();
void func_caranim_004007B0();
void func_caranim_00400B08();
void func_caranim_00400C8C();
void func_caranim_00401420();
void func_caranim_004014A4();
void func_caranim_004014DC();
void func_caranim_00401564();
void * caranimGetMaterialRecord();
void func_caranim_00401C04();
void func_caranim_00401C54();
void func_caranim_00401D6C();
void func_caranim_00402FD4();
void func_caranim_004033F4();
void func_caranim_0040358C();
void func_caranim_0040371C();
void func_caranim_00403A80();
void func_caranim_00403BDC();
void func_caranim_00404074();
void func_caranim_00404224();
void func_caranim_004042C4();
void func_caranim_00404568();
void func_caranim_00404A40();
void func_caranim_00404ACC();
void func_caranim_00404CA0();
void caranimBuildOrientationBasis(CarAnimBasisState *state);
void func_caranim_00405304();
void func_caranim_004054B4();
void func_caranim_00405910();
void func_caranim_00405B7C();
void func_caranim_00405DE4();
s32 caranimGetLocalizedLabel(s32 arg0);
s32 caranimFindRegisteredStateByKey(s32 key);
s32 func_caranim_00406094();
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *state);
extern s32 D_caranim_00407368;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/__entrypoint_func_caranim_400000.s")

#line 59 "src/modules/caranim.c"
/* Unload loaded skid, spray, sparks and shadow effect modules, then clear
 * their export pointers so later cleanup does not unload them again. */
extern void *D_caranim_00406B8C;
extern void *gSkidExports;
extern void *gSparksExports;
extern void *gSprayExports;
void caranimUnloadEffectModules(void) {
    if (gSkidExports != 0) { uvUnloadModule(0x736B6964); gSkidExports = 0; }
    if (gSprayExports != 0) { uvUnloadModule(0x73707279); gSprayExports = 0; }
    if (gSparksExports != 0) { uvUnloadModule(0x73706172); gSparksExports = 0; }
    if (D_caranim_00406B8C != 0) { uvUnloadModule(0x73686164); D_caranim_00406B8C = 0; }
}
#line 60 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004003AC.s")

void func_caranim_00400788(void *a0) {
    func_caranim_004007B0(a0);
    func_caranim_00400B08(a0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400B08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401420.s")

void func_caranim_00401494(void *a0, s32 a1) {
    *(u8 *)((u8 *)a0 + 0x24) = a1;
}

void func_caranim_0040149C(void *a0, s32 a1) {
    *(u8 *)((u8 *)a0 + 0x25) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401564.s")

void func_caranim_00401AD0(s32 arg0) {
    if (uvGetLoadedFile(0x55565458, 0x1A7) != 0) {
        // gfx: begin
        (*(void (**)(void))((u8 *)gUvGfxStateExports + 0x50))();
        // gfx: select loaded texture/file
        (*(void (**)(s32))((u8 *)gUvGfxStateExports + 0x14))(0x1A7);
        // gfx: set mode flags
        (*(void (**)(s32))((u8 *)gUvGfxStateExports + 0xC))(0x20000);
        // gfx: set framebuffer address
        (*(void (**)(s32))((u8 *)gUvGfxStateExports + 0x10))(0x9FFC0000);
        // geom: set color/scale
        (*(void (**)(f32, f32, f32, f32))((u8 *)gUvGeomExports + 0xC))(1.0f, 1.0f, 1.0f, 1.0f);
        // gfx: draw textured quad
        (*(void (**)(s32, s32, s32, s32, f32, f32, f32, f32))((u8 *)gUvGfxStateExports + 0x5C))(0x104, 0x124, 0xA, 0x2A, 0.0f, 1.0f, 0.0f, 1.0f);
        // gfx: end
        (*(void (**)(void))((u8 *)gUvGfxStateExports + 0x54))();
    }
}

#line 109 "src/modules/caranim.c"
/* Return the 0x1C-byte material record. Sentinel 0xFFF and the debug
 * default-material override select record zero; other bounds retain the
 * original caller contract. */
void *caranimGetMaterialRecord(s32 materialId) {
    if (materialId == 0xFFF) {
        materialId = 0;
    }
    if (gDebugDefaultMaterial != 0) {
        materialId = 0;
    }
    return (void *)((u8 *)&D_caranim_00406830 + materialId * 0x1C);
}
#line 118 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401C54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00402FD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004033F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040358C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040371C.s")

void func_caranim_004039E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 handle;

    // particle fx: create a new effect instance
    handle = (*(s32 (**)(s32))((u8 *)gUvPfxExports + 0x8))(arg0);
    // particle fx: attach source transform 0x1005
    (*(void (**)(s32, s32, s32, s32, s32, s32, s32))((u8 *)gUvPfxExports + 0x18))(handle, 0x1005, arg1, arg1 + 4, arg1 + 8, arg1 + 0xC, 0);
    // particle fx: attach source transform 0x4026
    (*(void (**)(s32, s32, s32, s32, s32, s32, s32))((u8 *)gUvPfxExports + 0x18))(handle, 0x4026, arg2, arg2 + 4, arg2 + 8, arg2 + 0xC, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00403A80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00403BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404224.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004042C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404CA0.s")

extern void *D_caranim_00407334;
extern u8 D_caranim_00406BF8[];
extern void *gUvGuiExports;

void func_caranim_00405194(s32 arg0)
{
  u8 *state = (u8 *) D_caranim_00407334;
  if ((*((s32 *) (state + 0x410))) != (*((s32 *) (state + 0x408))))
  {
    state = D_caranim_00407334;
    func_caranim_00404CA0(state, D_caranim_00407334, arg0);
    if (arg0 != 0)
    {
      s32 head;
      (*((void (**)(s32, s32)) (((u8 *) gUvGuiExports) + 0xC4)))(arg0, *((s32 *) (&D_caranim_00406BF8[(*((s32 *) (((u8 *) D_caranim_00407334) + 0x408))) * 0x6C])));
    }
  }
}

#line 181 "src/modules/caranim.c"
/* Reset the embedded matrix, normalize its Y axis from the stored direction,
 * derive X from Y cross Z, then derive Z from X cross Y and normalize both.
 * Preserve the shared vector helper behavior for degenerate input directions. */
void caranimBuildOrientationBasis(CarAnimBasisState *state) {
    Vec3F *axisY;
    Mtx4F *basis = &state->basis;
    Vec3F *axisZ;
    gUvFmtxExports->uvMat4SetIdentity(basis);
    axisY = (Vec3F *)&state->basis.m[1][0];
    gUvFvecExports->uvVec3FNormalize(axisY, &state->direction);
    axisZ = (Vec3F *)&state->basis.m[2][0];
    gUvFvecExports->uvVec3FCross((Vec3F *)basis, axisY, axisZ);
    gUvFvecExports->uvVec3FNormalize((Vec3F *)basis, (Vec3F *)basis);
    gUvFvecExports->uvVec3FCross(axisZ, (Vec3F *)basis, axisY);
    gUvFvecExports->uvVec3FNormalize(axisZ, axisZ);
}
#line 182 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004054B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405910.s")

#line 189 "src/modules/caranim.c"
/* Find channel property six and register the original animation
 * callback with null context and priority 0x14. */
void caranimRegisterChannelCallback(s32 channelId) {
    s32 callbackList;

    // uv callbackList: allocate callbackList of type 6
    (*(void (**)(s32, s32, s32 *, s32))((u8 *)gUvChanExports + 0x4))(channelId, 6, &callbackList, 0);
    // uv callback: bind callback to callbackList
    (*(void (**)(s32, void *, s32, s32))((u8 *)gUvCbckExports + 0x10))(callbackList, &func_caranim_00405B7C, 0, 0x14);
}
#line 197 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405DE4.s")

#line 202 "src/modules/caranim.c"
/* Return the language-indexed label for original IDs -1 through 20,
 * or the shared fallback outside that range. Preserve the original -1
 * convention and caller-owned language index. */
s32 caranimGetLocalizedLabel(s32 labelId) {
    if (labelId < -1 || labelId >= 0x15) {
        return (s32)&D_caranim_004066A0;
    }
    return *(s32 *)((u8 *)&D_caranim_00407228 + (gOptionsLanguage * 0x54 + labelId * 4));
}
#line 208 "src/modules/caranim.c"

#line 209 "src/modules/caranim.c"
/* Return the first registered animation state with this opaque key, or -1.
 * Preserve the original 16-bit index and valid registry-count contract. */
s32 caranimFindRegisteredStateByKey(s32 key) {
    u16 index;
    for (index = 0; index < D_caranim_00407368; index++) {
        if (D_caranim_00407348[index]->key == key) {
            return index;
        }
    }
    return -1;
}
#line 210 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00406094.s")

s32 func_caranim_004060E0(void) {
    return D_caranim_00407368;
}

extern void *gCamExports;
extern void *gUvLightExports;

void func_caranim_004060EC(void *arg0)
{
  s32 *temp;
  if ((*((s32 *) ((*((s32 *) (*((s32 **) (((u8 *) gCamExports) + 0x30))))) + 0x220))) >= 0)
  {
    (*((void (**)(s32)) (((u8 *) gUvLightExports) + 0x20)))(*((s32 *) (((u8 *) arg0) + 0x248)));
  }
  else
  {
    (*((void (**)(s32)) (((u8 *) gUvLightExports) + 0x20)))(-1);
  }
}

#line 233 "src/modules/caranim.c"
/* Apply the selected packed color to the object and register the original
 * property-four callback with the state pointer and zero terminator. */
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *state) {
    s32 index = state->colorIndex;
    s32 color = ((s32 *)&D_caranim_00407178)[index];
    gUvDobjExports->func_uvdobj_rom_004038C4(objectId, color, color, 0);
    gUvDobjExports->uvDobjProps(objectId, 4, func_caranim_004060EC, state, 0);
}
#line 234 "src/modules/caranim.c"

