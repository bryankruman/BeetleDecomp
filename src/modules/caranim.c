// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
#include "uvpfx_rom.h"
extern void *gUvPfxExports;
extern u8 D_caranim_004071FC[];
extern f32 D_caranim_00407398[], D_caranim_004073A8[];
extern f32 D_caranim_004073B8[], D_caranim_004073C8[];
extern f32 D_caranim_004073D8[], D_caranim_004073E8[];
extern f32 D_caranim_004073F8[], D_caranim_00407408[];
extern void func_caranim_0040371C(s32 effectId, f32 *firstPalette, f32 *secondPalette, u8 *colorInputs);

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
typedef struct { u8 unk00[8]; s32 key; u8 unk0C[0x230]; u8 flag23C; } CarAnimRegisteredState; /* Focused view of the constructor's 0x45C-byte allocation; not a complete layout. */
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
s32 caranimAcquireConfiguredParticleEffect(s32 kind, f32 scalar, u8 *colorInputs);
void func_caranim_0040371C();
void func_caranim_00403A80();
void func_caranim_00403BDC();
void func_caranim_00404074();
f32 caranimAdjustScalarAndGetMaterialOffset(s32 materialId, f32 *value, s16 alternate);
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
/* Call original state helper 0x007B0, then the gated animation/material helper.
 * Preserve their order; scheduling and state ownership remain caller contracts. */
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

#line 84 "src/modules/caranim.c"
/* Walk at most eight registry entries, stopping at the first null, and clear
 * byte0x23C: callback0x054B4 skips helper0x05304 while this byte is nonzero.
 * Constructor0x003AC clears it; callback sets it after that helper returns.
 * RE_UNKNOWN: helper role, reset cadence, pointer lifetime/capacity and incoming
 * argument type; trace callers. Preserve the homed incoming A0 word. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014A4.s")
#line 85 "src/modules/caranim.c"

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
        // gfx: clear current state bits selected by the mask
        (*(void (**)(s32))((u8 *)gUvGfxStateExports + 0x10))(0x9FFC0000);
        // geom: set fill color
        (*(void (**)(f32, f32, f32, f32))((u8 *)gUvGeomExports + 0xC))(1.0f, 1.0f, 1.0f, 1.0f);
        // gfx: draw textured quad
        (*(void (**)(s32, s32, s32, s32, f32, f32, f32, f32))((u8 *)gUvGfxStateExports + 0x5C))(0x104, 0x124, 0xA, 0x2A, 0.0f, 1.0f, 0.0f, 1.0f);
        // gfx: end
        (*(void (**)(void))((u8 *)gUvGfxStateExports + 0x54))();
    }
}
#line 108 "src/modules/caranim.c"

#line 109 "src/modules/caranim.c"
/* Return an address in the module's 0x1C-stride table without allocating.
 * Sentinel 0xFFF and the debug override select record zero. RE_UNKNOWN: caller
 * index bounds and mutation rights; an address alone establishes no ownership. */
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

#line 129 "src/modules/caranim.c"
/* Acquire an inactive particle effect of the requested kind, configure it,
 * then restart it. The shared-data address and requested count ten go through
 * export 0x3C; the scalar is promoted to double for property 0x1007 at 0x14.
 * Kinds 10, 11, 13 and 14 select the original palette pairs and consume four
 * caller bytes through the color helper. Preserve both failure returns and
 * the original switch, property-list and call order.
 * RE_UNKNOWN: gameplay kind identities, scalar units and shared definition
 * data ownership require the callers and particle assets. Other nonnegative
 * kinds keep the original configuration path without a new range check. */
s32 caranimAcquireConfiguredParticleEffect(s32 kind, f32 scalar, u8 *colorInputs) {
    s32 effectId;

    if (kind < 0) {
        return -1;
    }
    effectId = ((UvPfx_Exports *)gUvPfxExports)->uvPfxAcquireInactiveByKind(kind);
    if (effectId != -1) {
        ((UvPfx_Exports *)gUvPfxExports)->uvPfxSetTypeOneCountAndValue(
            effectId, (s32)D_caranim_004071FC, 10);
        ((UvPfx_Exports *)gUvPfxExports)->func_uvpfx_rom_004004D0(
            effectId, 0x1015, 1, 0x1026, 1, 0x1007, (f64)scalar, 0);
        switch (kind) {
            case 11:
                func_caranim_0040371C(effectId, D_caranim_00407398, D_caranim_004073A8, colorInputs);
                break;
            case 13:
                func_caranim_0040371C(effectId, D_caranim_004073B8, D_caranim_004073C8, colorInputs);
                break;
            case 10:
                func_caranim_0040371C(effectId, D_caranim_004073D8, D_caranim_004073E8, colorInputs);
                break;
            case 14:
                func_caranim_0040371C(effectId, D_caranim_004073F8, D_caranim_00407408, colorInputs);
                break;
        }
        ((UvPfx_Exports *)gUvPfxExports)->uvPfxRestart(effectId);
    }
    return effectId;
}
#line 130 "src/modules/caranim.c"

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
/* Compute the material offset and conditionally update the caller's scalar.
 * Kinds two/three add 0.125; the special record adds 0.5 when suppressSpecialCase
 * is zero, raising only values less than ten (NaN preserved). 0xFFF selects zero.
 * RE_UNKNOWN: scalar/offset units and caller index bounds; trace material callers. */
#line 154 "src/modules/caranim.c"

f32 caranimAdjustScalarAndGetMaterialOffset(s32 materialId, f32 *scalar, s16 suppressSpecialCase) {
    f32 scalarOffset;
    s16 materialKind;
    CarAnimMaterialOffset *materialRecord;
    scalarOffset = 0.0f;
    if (materialId == 0xFFF) materialId = 0;
    materialRecord = (CarAnimMaterialOffset *)((u8 *)&D_caranim_00406830 + materialId * 0x1C);
    materialKind = materialRecord->kind;
    if (materialKind == 2 || materialKind == 3) scalarOffset += 0.125f;
    if (materialRecord == (CarAnimMaterialOffset *)&D_caranim_00406A28 && suppressSpecialCase == 0) {
        if (*scalar < 10.0f) *scalar = 10.0f;
        scalarOffset += 0.5f;
    }
    return scalarOffset;
}
#line 169 "src/modules/caranim.c"
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
/* On selection change, update, reread selection and copy 30 bytes via its text pointer.
 * GUI slot 0xC4 uppercases bytes >= 97 without NUL-scanning or retaining source.
 * RE_UNKNOWN: audit source extent, widget capacity and selection bounds. */
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
/* Build Y from direction, X from Y cross Z, then Z from X cross Y.
 * RE_ORIGINAL_QUIRK: a nonzero Y parallel to identity Z produces zero X/Z.
 * RE_UNKNOWN: producer direction constraints need audit before assuming a full-rank basis. */
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
/* Register the animation callback at priority 0x14; zero means no insert-before callback.
 * RE_UNKNOWN: caller channel/list validity and ignored failure need caller/pool audit. */
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
/* Stored rows 0..2 each hold 21 label addresses; IDs outside -1..20 return "INVALID".
 * RE_ORIGINAL_QUIRK: ID -1 yields 0x01020000 for row0, or the preceding row's last label.
 * RE_UNKNOWN: runtime language domain and -1 caller reachability; trace setters/callers. */
s32 caranimGetLocalizedLabel(s32 labelId) {
    if (labelId < -1 || labelId >= 0x15) {
        return (s32)&D_caranim_004066A0;
    }
    return *(s32 *)((u8 *)&D_caranim_00407228 + (gOptionsLanguage * 0x54 + labelId * 4));
}
#line 208 "src/modules/caranim.c"

#line 209 "src/modules/caranim.c"
/* Find the first registered key with unsigned 16-bit traversal. RE_ORIGINAL_QUIRK: constructor0x003AC increments count even when all eight slots are full.
 * RE_UNKNOWN: caller bounds/lifetime must keep the searched prefix in range and nonnull; resolve original creation/lifecycle call sites. */
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
/* Return the constructor-maintained registry counter; no recount or slot validation. */
s32 caranimGetRegisteredStateCount(void) {
    return D_caranim_00407368;
}
#line 216 "src/modules/caranim.c"

extern void *gCamExports;
extern void *gUvLightExports;

#line 220 "src/modules/caranim.c"
/* Select the state light-buffer slot at 0x248 when camera word 0x220 is nonnegative.
 * Otherwise select -1, suppressing emission through UVLIGHT 0x20. RE_UNKNOWN: camera-word
 * meaning, caller slot validity and record lifetime; trace camera/animation producers. */
#line 223 "src/modules/caranim.c"

void caranimSelectCameraLightBufferSlot(void *state)
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
#line 235 "src/modules/caranim.c"
#line 232 "src/modules/caranim.c"

#line 233 "src/modules/caranim.c"
/* Apply color and register property-four callback; the object retains state.
 * RE_UNKNOWN: color-index bounds and retained-state lifetime need producers/teardown. */
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *state) {
    s32 index = state->colorIndex;
    s32 color = ((s32 *)&D_caranim_00407178)[index];
    gUvDobjExports->uvDobjReplaceLightColorRecord(objectId, color, color, 0);
    gUvDobjExports->uvDobjProps(objectId, 4, caranimSelectCameraLightBufferSlot, state, 0);
}
#line 234 "src/modules/caranim.c"

