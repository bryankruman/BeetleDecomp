// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
#include "uvquat_rom.h"
#include "uvdobj_rom.h"
typedef struct { u8 opaque00[8]; s32 objectHandle; } CarAnimAxisScaleState;
extern f32 D_caranim_0040673C, D_caranim_00406740, D_caranim_00406744;
extern u8 D_caranim_00406B84;
extern u8 gCheatCars;

typedef struct { u8 prefix[8]; s16 kind; u8 gap0A[0x12]; } CarAnimMaterialOffset;
extern s32 D_caranim_00406A28;
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
void caranimInitializeState();
void func_caranim_004007B0();
void func_caranim_00400B08();
void func_caranim_00400C8C();
void func_caranim_00401420();
void func_caranim_004014A4();
void func_caranim_004014DC();
void func_caranim_00401564();
void * caranimGetMaterialRecord();
void func_caranim_00401C04();
void caranimScaleObjectAxisForCheat(CarAnimAxisScaleState *state);
void func_caranim_00401D6C();
void func_caranim_00402FD4();
void func_caranim_004033F4();
void func_caranim_0040358C();
void func_caranim_0040371C();
void func_caranim_00403A80();
void func_caranim_00403BDC();
void func_caranim_00404074();
f32 caranimGetMaterialScalarOffset(s32 materialId, f32 *value, s16 alternate);
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

#line 63 "src/modules/caranim.c"
/* Run the two original state initialization phases in order. Their detailed
 * fields and ownership remain in the individual helpers. */
void caranimInitializeState(void *state) {
    func_caranim_004007B0(state);
    func_caranim_00400B08(state);
}
#line 67 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400B08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401420.s")

#line 76 "src/modules/caranim.c"
/* Store the low byte of the supplied value at state offset 0x24. */
void caranimSetStateByte24(void *state, s32 value) {
    *(u8 *)((u8 *)state + 0x24) = value;
}
#line 79 "src/modules/caranim.c"

#line 80 "src/modules/caranim.c"
/* Store the low byte of the supplied value at state offset 0x25. */
void caranimSetStateByte25(void *state, s32 value) {
    *(u8 *)((u8 *)state + 0x25) = value;
}
#line 83 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401564.s")

#line 90 "src/modules/caranim.c"
/* When texture 0x1A7 is loaded, draw its original white texture
 * rectangle inside a saved graphics state. Preserve the unused
 * argument and original mode values. */
void caranimDrawLoadedTextureOverlay(s32 unused) {
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
#line 108 "src/modules/caranim.c"

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

#line 121 "src/modules/caranim.c"
/* For cheat values four/five/six, scale all four components of matrix
 * row X/Y/Z respectively and publish axis plus one in the shared byte.
 * Other cheat values clear that byte and leave the object matrix untouched.
 * Reload the object handle after fetching/scaling its matrix, as originally.
 * RE_UNKNOWN: scale constant units/labels and shared-byte ownership outside
 * its established facing-object inhibit use require callers/assets. */
void caranimScaleObjectAxisForCheat(CarAnimAxisScaleState *state) {
    Mtx4F transform;
    s32 axis;
    f32 scale;
    f32 *row;

    switch (gCheatCars) {
        case 4:
            scale = D_caranim_0040673C;
            axis = 0;
            break;
        case 5:
            scale = D_caranim_00406740;
            axis = 1;
            break;
        case 6:
            scale = D_caranim_00406744;
            axis = 2;
            break;
        default:
            D_caranim_00406B84 = 0;
            return;
    }
    D_caranim_00406B84 = axis + 1;
    gUvDobjExports->uvDobjGetPosm(state->objectHandle, 0, &transform);
    row = transform.m[axis];
    row[0] *= scale;
    row[1] *= scale;
    row[2] *= scale;
    row[3] *= scale;
    gUvDobjExports->uvDobjPosm(state->objectHandle, 0, &transform);
}
#line 122 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00402FD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004033F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040358C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040371C.s")

#line 133 "src/modules/caranim.c"



#line 136 "src/modules/caranim.c"










#line 146 "src/modules/caranim.c"
/* Acquire an inactive particle effect of the requested kind, then read
 * properties 0x1005 and 0x4026 into two four-float output regions.
 * The actual getter at export 0x18 writes definition shorts 0x16..0x1C
 * divided by 255 for 0x1005. For 0x4026 it writes extension shorts
 * 0x0E..0x14 divided by 255 when definition kind is one, or four ones.
 * RE_ORIGINAL_QUIRK: the acquired handle is used without checking for -1.
 * RE_UNKNOWN: acquisition-failure reachability, output-region lifetime and
 * broader component meanings. Trace original wrapper callers and effect-pool
 * setup before asserting valid capacities, ownership or channel semantics. */
void caranimAcquireParticleEffectAndReadProperties(s32 kind, f32 *firstOutput, f32 *secondOutput) {
    s32 handle;

    // Acquire an inactive effect matching kind through export 0x08.
    handle = (*(s32 (**)(s32))((u8 *)gUvPfxExports + 0x8))(kind);
    // Getter export 0x18 writes four property-0x1005 float outputs.
    (*(void (**)(s32, ...))((u8 *)gUvPfxExports + 0x18))(handle, 0x1005, firstOutput, firstOutput + 1, firstOutput + 2, firstOutput + 3, 0);
    // Getter property 0x4026 writes four scaled float outputs, or four ones.
    (*(void (**)(s32, ...))((u8 *)gUvPfxExports + 0x18))(handle, 0x4026, secondOutput, secondOutput + 1, secondOutput + 2, secondOutput + 3, 0);
}
#line 156 "src/modules/caranim.c"
#line 146 "src/modules/caranim.c"
#line 143 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00403A80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00403BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404074.s")

#line 150 "src/modules/caranim.c"
/* Return 0.125 for material kinds two/three, plus 0.5 for the
 * original special material when alternate is zero. The special case also
 * clamps the supplied scalar upward to ten. Sentinel 0xFFF selects zero;
 * other material bounds remain the original caller contract. */
f32 caranimGetMaterialScalarOffset(s32 materialId, f32 *value, s16 alternate) {
    f32 offset;
    s16 kind;
    CarAnimMaterialOffset *material;
    offset = 0.0f;
    if (materialId == 0xFFF) materialId = 0;
    material = (CarAnimMaterialOffset *)((u8 *)&D_caranim_00406830 + materialId * 0x1C);
    kind = material->kind;
    if (kind == 2 || kind == 3) offset += 0.125f;
    if (material == (CarAnimMaterialOffset *)&D_caranim_00406A28 && alternate == 0) {
        if (*value < 10.0f) *value = 10.0f;
        offset += 0.5f;
    }
    return offset;
}
#line 151 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004042C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404CA0.s")

extern void *D_caranim_00407334;
extern u8 D_caranim_00406BF8[];
extern void *gUvGuiExports;

#line 166 "src/modules/caranim.c"
/* When the shared selection words 0x410/0x408 differ, run the original
 * update and optionally replace GUI text from the selected 0x6C-byte record.
 * Selection bounds and the GUI handle remain caller-owned. */
void caranimRefreshChangedSelection(s32 guiHandle)
{
  u8 *state = (u8 *) D_caranim_00407334;
  if ((*((s32 *) (state + 0x410))) != (*((s32 *) (state + 0x408))))
  {
    state = D_caranim_00407334;
    func_caranim_00404CA0(state, D_caranim_00407334, guiHandle);
    if (guiHandle != 0)
    {
      (*((void (**)(s32, s32)) (((u8 *) gUvGuiExports) + 0xC4)))(guiHandle, *((s32 *) (&D_caranim_00406BF8[(*((s32 *) (((u8 *) D_caranim_00407334) + 0x408))) * 0x6C])));
    }
  }
}
#line 180 "src/modules/caranim.c"

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

    // Read callback-list property six from this channel; this query does not allocate a list.
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

#line 213 "src/modules/caranim.c"
/* Return the number of registered animation states. */
s32 caranimGetRegisteredStateCount(void) {
    return D_caranim_00407368;
}
#line 216 "src/modules/caranim.c"

extern void *gCamExports;
extern void *gUvLightExports;

#line 220 "src/modules/caranim.c"
/* Select the state light handle at 0x248 when the current camera word
 * 0x220 is nonnegative, otherwise select sentinel -1. Preserve the shared
 * camera indirection and original light-export contract. */
void caranimSelectCameraLight(void *state)
{
  s32 *temp;
  if ((*((s32 *) ((*((s32 *) (*((s32 **) (((u8 *) gCamExports) + 0x30))))) + 0x220))) >= 0)
  {
    (*((void (**)(s32)) (((u8 *) gUvLightExports) + 0x20)))(*((s32 *) (((u8 *) state) + 0x248)));
  }
  else
  {
    (*((void (**)(s32)) (((u8 *) gUvLightExports) + 0x20)))(-1);
  }
}
#line 232 "src/modules/caranim.c"

#line 233 "src/modules/caranim.c"
/* Apply the selected packed color to the object and register the original
 * property-four callback with the state pointer and zero terminator. */
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *state) {
    s32 index = state->colorIndex;
    s32 color = ((s32 *)&D_caranim_00407178)[index];
    gUvDobjExports->uvDobjReplaceLightColorRecord(objectId, color, color, 0);
    gUvDobjExports->uvDobjProps(objectId, 4, caranimSelectCameraLight, state, 0);
}
#line 234 "src/modules/caranim.c"

