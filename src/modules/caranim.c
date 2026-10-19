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
typedef struct { u8 unk00[8]; s32 objectHandle; u8 unk0C[0x230]; u8 flag23C; } CarAnimRegisteredState; /* Focused view of the constructor's 0x45C-byte allocation; not a complete layout. */
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
s32 caranimFindRegisteredStateByObjectHandle(s32 objectHandle);
s32 func_caranim_00406094();
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *state);
extern s32 D_caranim_00407368;
/* Initializer-only storage views; seven words copied without interpreting them.
 * RE_UNKNOWN: table extent, selector domain, storage ownership and full export ABI. */
#include "uvgfxmgr_rom.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
extern s32 gNumPlayers;
extern s32 D_caranim_00407390;
extern u32 D_caranim_00407370[7];
extern void *D_caranim_00406B8C;
extern void *gSkidExports, *gSprayExports, *gSparksExports;
typedef struct { u32 words[7]; } CarAnimInitializerSevenWords;
void caranimUnloadEffectModules(void);
void caranimDrawLoadedTextureOverlay(s32 unused);
void *caranimGetMaterialRecord(s32 materialId);
void caranimInitializeState(void *state);
void caranimRegisterChannelCallback(s32 channelId);
s32 caranimGetLocalizedLabel(s32 labelId);
s32 caranimFindRegisteredStateByObjectHandle(s32 objectHandle);
void caranimSetStateByte24(void *state, s32 value);
s32 caranimGetRegisteredStateCount(void);
void caranimSetStateByte25(void *state, s32 value);
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *state);
void caranimAcquireParticleEffectAndReadProperties(s32 kind, f32 *firstOutput, f32 *secondOutput);
void func_caranim_00404074(s32 mode);
#line 90 "src/modules/caranim.c"
/* Publish the 19 original export addresses, load effect modules and assets,
 * copy the selected seven-word record and cache four particle property pairs.
 * Register the original callback on graphics callback list one.
 * RE_UNKNOWN: export/table capacity, selector validity, asset and callback
 * lifetimes and complete callable ABIs need producer and caller evidence. */
void __entrypoint_func_caranim_400000(u32 *exports) {
    uvUpdateFileAllocPtr(exports);
    exports[0x0 / 4] = (u32)caranimUnloadEffectModules;
    exports[0x28 / 4] = (u32)caranimDrawLoadedTextureOverlay;
    exports[0x4 / 4] = (u32)func_caranim_004003AC;
    exports[0x2C / 4] = (u32)caranimGetMaterialRecord;
    exports[0x8 / 4] = (u32)caranimInitializeState;
    exports[0x30 / 4] = (u32)func_caranim_00401C04;
    exports[0xC / 4] = (u32)func_caranim_004007B0;
    exports[0x34 / 4] = (u32)caranimRegisterChannelCallback;
    exports[0x10 / 4] = (u32)func_caranim_00400B08;
    exports[0x38 / 4] = (u32)caranimGetLocalizedLabel;
    exports[0x14 / 4] = (u32)func_caranim_00400C8C;
    exports[0x3C / 4] = (u32)caranimFindRegisteredStateByObjectHandle;
    exports[0x18 / 4] = (u32)func_caranim_00401420;
    exports[0x40 / 4] = (u32)func_caranim_00406094;
    exports[0x1C / 4] = (u32)caranimSetStateByte24;
    exports[0x44 / 4] = (u32)caranimGetRegisteredStateCount;
    exports[0x20 / 4] = (u32)caranimSetStateByte25;
    exports[0x48 / 4] = (u32)caranimApplyColorAndCallback;
    exports[0x24 / 4] = (u32)func_caranim_00401564;
    D_caranim_00407368 = 0;
    gSkidExports = uvLoadModule('skid');
    gSprayExports = uvLoadModule('spry');
    gSparksExports = uvLoadModule('spar');
    D_caranim_00406B8C = uvLoadModule('shad');
    uvLoadFile('UVMD', 0x6C);
    uvLoadFile('UVMD', 0x5E);
    uvLoadFile('UVTX', 0xB5);
    uvLoadFile('UVPX', 0xB);
    uvLoadFile('UVPX', 0xD);
    uvLoadFile('UVPX', 0xA);
    uvLoadFile('UVPX', 0xE);
    uvLoadFile('UVPX', 0xC);
    *(CarAnimInitializerSevenWords *)D_caranim_00407370 =
        ((CarAnimInitializerSevenWords *)&D_caranim_00406830)[D_caranim_00407390];
    caranimAcquireParticleEffectAndReadProperties(0xB, D_caranim_00407398, D_caranim_004073A8);
    caranimAcquireParticleEffectAndReadProperties(0xD, D_caranim_004073B8, D_caranim_004073C8);
    caranimAcquireParticleEffectAndReadProperties(0xA, D_caranim_004073D8, D_caranim_004073E8);
    caranimAcquireParticleEffectAndReadProperties(0xE, D_caranim_004073F8, D_caranim_00407408);
    uvLoadFile('UVTX', 0x1A7);
    if (gNumPlayers >= 2) {
        func_caranim_00404074(0);
    }
    (*(void (**)(s32, void *, s32, s32))((u8 *)gUvCbckExports + 0x10))(
        gUvGfxMgrExports->uvGfxGetCallbackList(1), &func_caranim_004014A4, 0, 0);
}
#line 91 "src/modules/caranim.c"

#line 59 "src/modules/caranim.c"
/* Unload loaded skid, spray, sparks and shadow effect modules, then clear
 * their export pointers so later cleanup does not unload them again. */
extern void *D_caranim_00406B8C;
extern void *gSkidExports;
extern void *gSparksExports;
extern void *gSprayExports;
void caranimUnloadEffectModules(void) { /* For each nonzero cached export, unload its literal tag and clear that export afterward. */
    if (gSkidExports != 0) { uvUnloadModule(0x736B6964); gSkidExports = 0; }
    if (gSprayExports != 0) { uvUnloadModule(0x73707279); gSprayExports = 0; }
    if (gSparksExports != 0) { uvUnloadModule(0x73706172); gSparksExports = 0; }
    if (D_caranim_00406B8C != 0) { uvUnloadModule(0x73686164); D_caranim_00406B8C = 0; }
/* RE_UNKNOWN: Shared users and unload reference-count/lifetime rules. */ }
#line 60 "src/modules/caranim.c"

/* func_caranim_004003AC consumes three incoming words and returns its
 * 0x45C-byte allocation. It publishes the first-free registry pointer before
 * clearing storage, initializes values/matrices and acquires light/object indices.
 * Four object slots get model0x6C; the separate object gets model0x5E. DOBJ tags
 * four/five retain callback and context words; preserve handle reloads after calls.
 * RE_ORIGINAL_QUIRK: a full eight-entry registry still increments the shared
 * counter and initializes an unregistered state. Allocation may return null,
 * UVLIGHT acquisition minus one and DOBJ acquisition0xFFFF; none is checked here.
 * RE_UNKNOWN: original caller/source/context types and domains, flag/scalar
 * policy/units, capacity/failure reachability, callback signatures and retained
 * storage ownership/lifetimes need callers, producers and teardown evidence.
 * Clean C has the same 988 bytes but 53 word and full relocation differences
 * from registry-loop lowering and independent store/address scheduling; retain
 * original assembly pending complete matching proof. */
#line 61 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004003AC.s")

#line 63 "src/modules/caranim.c"
/* Call original state helper 0x007B0, then the gated animation/material helper.
 * Preserve their order; scheduling and state ownership remain caller contracts. */
void caranimInitializeState(void *state) {
    func_caranim_004007B0(state);
    func_caranim_00400B08(state);
}
#line 67 "src/modules/caranim.c"

/* Apply shared controls to selection words 0x408/0x410, set or clear a
 * table-word object mask, then update packed light words and gated transforms.
 * The random path updates three signed components with LCG draws, clamps
 * 0..255 and sets steps -1/+1 at limits. Otherwise word 0x404 indexes a table.
 * Reload the request after the light callback; reread the saved old table
 * address for the default state's three masked byte globals. Reload byte 0x23F
 * after helper 0x3BDC. DOBJ 0x24 consumes matrix 0x318; FMTX copies it to 0x358.
 * RE_ORIGINAL_QUIRK: applied index uses the reread request, while default-state
 * bytes use the saved old table address; no callback nonmutation is assumed.
 * RE_UNKNOWN: control/flag policy, input arithmetic and table/handle domains,
 * component roles/units, mutation rights and storage/callback lifetimes need
 * original writers, callers, pool/table extents and teardown evidence.
 * Clean C is 852 versus 856 bytes with 199 word and full relocation differences
 * from dispatch lowering, storage/register scheduling and masked shifts;
 * retain assembly until complete matching proof. */
#line 68 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400B08.s")

/* Apply a variadic property list using signed-low-half tags 0..30; zero or an
 * invalid tag ends processing. Doubles narrow to f32, vectors copy component
 * by component, and tag 15 copies a matrix before optional local translation.
 * A changed byte23D transitions four skid/spray/particle slots and clears each
 * stored reference after its provider returns; these are not proved frees.
 * RE_ORIGINAL_QUIRK: tag 3 clears word10 according to the old flag; tag 7 stores
 * the shadow acquisition result, including null. Preserve callback reloads.
 * RE_UNKNOWN: property/flag policies, units, variadic argument/source extents,
 * valid handle/context chains and resource ownership/lifetimes need original
 * callers, writers, pool consumers and teardown. Native handler order is known;
 * historical source declarations and lexical organization remain unproved.
 * Two readable drafts retain all observed effects but do not match: both are
 * 1940 bytes, with 409 then 232 differing words. The observed-block-order draft
 * still changes temporary registers/loop-zero scheduling, resolves two PC16
 * branches locally and uses a synthesized table instead of the original label.
 * Complete 20/18 relocation records fail equality; retain original assembly
 * until instructions and every original dispatch-table target are proved. */
#line 72 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400C8C.s")

/* When unsigned byte 0x240 is nonzero, scan four pointer slots at 0x2C0
 * for the first null. A full list makes no call; otherwise SPARKS slot 0x0C
 * consumes the supplied three-float pointer, and its returned record or null
 * is stored in the selected slot saved across that provider callback.
 * Original loader tag spar supplies gSparksExports; the subsequent shad
 * load stores a different dependency. SPARKS has four 0x14-byte pool records.
 * RE_UNKNOWN: flag policy, vector role/units, valid state/source inputs and
 * retained pointer ownership/lifetime need original writers/readers/teardown.
 * Clean C differs in input-register retention, frame and load scheduling;
 * retain ASM pending complete instruction and relocation proof. */
#line 74 "src/modules/caranim.c"
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
 * byte0x23C: callback0x054B4 skips light/shadow helper0x05304 while nonzero.
 * Constructor0x003AC clears it; callback sets it after that helper returns.
 * RE_UNKNOWN: flag policy, reset cadence, pointer lifetime/capacity and incoming
 * argument type; trace callers. Preserve the homed incoming A0 word. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014A4.s")
#line 85 "src/modules/caranim.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014DC.s")

/* Copy four words from each stride-0x70 shared record, then construct a text
 * list and fifteen bound scalar rows, including state-dependent controls.
 * Preserve signed-16 allocation results, provider reloads, retained callback
 * and context words, and the two immediate selection-callback invocations.
 * RE_ORIGINAL_QUIRK: the allocation result is used without a local guard.
 * RE_UNKNOWN: shared-table declaration/alias boundaries, source/label extents,
 * GUI capacity, value-kind units and retained state/callback/context lifetimes
 * need original producers, widget dispatch and teardown. Offset proximity alone
 * does not establish historical owned arrays or a complete state type.
 * Clean C is 1616 versus 1388 bytes: runtime remainder plus four-group unrolling,
 * frame 112 versus 80, export-base rematerialization and FP argument lowering
 * differ; 398 words differ and complete 89/108-record equality fails.
 * Retain original assembly until every instruction and relocation matches. */
#line 88 "src/modules/caranim.c"
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

#line 1 "caranim_packed_color_bytes.c"
/* Read the high three bytes of one packed color-table word.
 * RE_ORIGINAL_QUIRK: a signed index outside 0..20 writes FF to all three
 * outputs in order. A valid word is loaded once before any output store;
 * the low byte is ignored, and there are no output-pointer checks.
 * RE_UNKNOWN: channel meanings, authored signed types, complete table bounds
 * beyond this consumed prefix, and valid output/alias domains. The s32 shifts
 * retain the original target's arithmetic-right-shift view. */
void caranimReadPackedColorBytes(s32 colorIndex, u8 *firstByte,
                               u8 *secondByte, u8 *thirdByte) {
    s32 packedColor;

    if (colorIndex < 0 || colorIndex >= 21) {
        *firstByte = 0xFF;
        *secondByte = 0xFF;
        *thirdByte = 0xFF;
        return;
    }
    packedColor = ((s32 *)&D_caranim_00407178)[colorIndex];
    *firstByte = (packedColor >> 24) & 0xFF;
    *secondByte = (packedColor >> 16) & 0xFF;
    *thirdByte = (packedColor >> 8) & 0xFF;
}


#line 121 "src/modules/caranim.c"
/* For cheat four/five/six, scale all four components of matrix row X/Y/Z
 * and publish axis plus one; other values clear the byte. Reload the handle.
 * RE_ORIGINAL_QUIRK: the local matrix is consumed even if DOBJ's getter exits
 * without output for a rejected handle/model; no output-validity check is made.
 * RE_UNKNOWN: rejection reachability, caller handles, scale units/labels and
 * shared-byte ownership beyond facing inhibit need callers/pool/model assets. */
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

/* Update four descriptor-driven effect slots from transformed local points.
 * Snapshot the optional source pointer, selector word and selected scalar;
 * preserve callback-dependent reference/state reloads and final ID stores.
 * SKID/SPRAY transitions and PFX final-interval calls precede clearing stored
 * references; those operations do not establish resource deallocation.
 * RE_ORIGINAL_QUIRK: mode-skipped slots retain their effect state. Descriptor
 * branches do not always initialize the style halfword; fallback paths leave
 * byte3 of the four-byte SKID input uninitialized. Matrix/normalize failures
 * are unchecked, and the first three TERRA54 output pointers intentionally
 * alias. Preserve native behavior without inventing default values.
 * RE_UNKNOWN: reachable descriptor/source domains, valid handles and matrix/
 * basis guarantees, setting/table extents, units, callback mutation and record
 * lifetimes need original producers, callers, pool consumers and teardown.
 * No wheel identity or complete historical array ownership is established.
 * A readable draft is 4640 versus 4712 native bytes, with 1149 differing words.
 * Both use a 424-byte frame, but local homes, saved pointers, loop organization
 * and branch lowering differ. The original direct D6838 halfword alias becomes
 * a D6830+8 field access; three named dispatch tables become synthesized data.
 * The two 101-record relocation lists differ. Retain original
 * assembly until instructions, table targets and historical aliases match. */
#line 123 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401D6C.s")

/* Update two configured particle positions using selected object matrices.
 * Ordered scalar >= 3 clears object flag mask 0x02, begins final intervals
 * for existing effects, then invalidates both handles after those calls.
 * Active updates preserve mode/handle/export reloads and property 0x1010's
 * three promoted doubles, including a single-precision Z + 0.5f operation.
 * RE_ORIGINAL_QUIRK: unordered scalar comparison follows the active path;
 * an unused three-word transformed-point copy is retained in original storage.
 * RE_UNKNOWN: scalar units/mode policy, selection/handle/storage domains,
 * matrix-output validity and callback ownership/lifetimes need original
 * callers, producers and teardown. Final-interval updates do not free effects.
 * Clean C is 1056 bytes with 46 identical ordered relocation records; 48 words
 * differ in frame/local homes, registers and argument/store scheduling.
 * Retain original assembly pending complete instruction equivalence. */
#line 125 "src/modules/caranim.c"
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

/* Add byte-derived offsets to both palettes' first three components and clamp
 * with ordered comparisons; both fourth components use the same byte/255 value.
 * Original setup queries four pairs of runtime buffers for kinds 11/13/10/14.
 * The UVPFX call passes four doubles for 0x1005 and four for 0x4026. Its original
 * consumer writes the latter extension only for kind 1; kind 2 returns before
 * that property handler, while other kinds skip its four double arguments.
 * RE_UNKNOWN: component/channel roles and caller buffer/handle validity or
 * lifetime beyond this setup need original effect producers/render consumers.
 * Clean C remains unmatched; retain assembly until full byte/relocation proof. */
#line 131 "src/modules/caranim.c"
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

/* Update two scalar accumulators and three configured object matrices after
 * matching the selected record's model words. Preserve single/double arithmetic,
 * scalar folds, ordered zero gates and owner/handle/index reloads around calls.
 * RE_ORIGINAL_QUIRK: only the first matrix index gates all three operations.
 * Secondary context is captured only for an initially nonnull owner; later
 * matrix iterations reread the owner before using that saved context.
 * RE_UNKNOWN: caller/producer guarantees for selection, handles, record/matrix
 * storage and captured-context lifetime, plus scalar units and flag policy,
 * need original callers, writers and teardown evidence. No default is invented.
 * Clean C is 1156 versus 1176 bytes: frame/local homes, table-address reuse,
 * floating operand scheduling and full relocation records differ. Retain
 * original assembly pending complete instruction and relocation proof. */
#line 146 "src/modules/caranim.c"
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

/* Approach two bounded state scalars, then apply X/Y matrix operations and
 * publish selected object matrices. The disabled path copies/publishes only.
 * Preserve double-precision target products before narrowing, ordered sign
 * clamps, two separate random draws and all state/export reloads after calls.
 * RE_ORIGINAL_QUIRK: an unused three-word translation copy is made from the
 * initialized original matrix; unordered comparisons keep the original paths.
 * RE_UNKNOWN: scalar units/policy, state/context and output validity, selected
 * index domains and callback ownership/lifetimes need original callers,
 * writers and teardown. D6BEC/D6BD8/D6B9C are distinct field-address aliases
 * with stride0x6C; their offsets alone do not prove a complete owned C array.
 * Clean C is 1232 versus 1240 bytes: frame208/216 and sign-clamp lowering differ;
 * 238 words and full relocations fail, including draft alias normalization.
 * Retain original assembly until every instruction and relocation matches. */
#line 154 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404ACC.s")

/* Snapshot selections 0x410/0x408 before waiting on graphics and releasing
 * texture-animation storage. Copy saved matrices into the old object, load the
 * requested models/textures, replace the model and update nested state words.
 * Rebuild animation storage, apply a table bit index, clear auxiliary masks,
 * retrieve matrices and finally reread the requested selection for 0x410.
 * RE_ORIGINAL_QUIRK: release uses old texture word 0x14 but new word 0x10;
 * nested graphics-state writes retain pointer/word reloads and a final bit clear.
 * RE_UNKNOWN: table/index/handle domains, resource success, model storage,
 * flag policy and shared mutation/ownership/lifetimes need callers/producers.
 * The target consumes A0; original caranimRefreshChangedSelection prepares
 * A0/A1/A2. Historical source declaration remains unresolved. Clean target C
 * is 1164 versus 1268 bytes with frame/record-address/loop scheduling and full
 * relocation differences. The scoped caller view also changes direct JAL to
 * HI/LO plus JALR. Retain original assembly and caller pending complete proof. */
#line 160 "src/modules/caranim.c"
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

/* func_caranim_00405304 applies light records using the object's saved position
 * or a query word, then conditionally updates shadow state and three scene records.
 * Snapshot matrix row 0x30 before LIGHT18; reread byte243 and callback-dependent
 * scene/state pointers afterward. Halfword3F2 values zero/one select -1.
 * RE_ORIGINAL_QUIRK: reads the row even when DOBJ rejects a handle without output.
 * RE_UNKNOWN: valid object/query/selector domains, flag policy and storage lifetimes
 * need original constructors, scene writers and callback callers; rejection
 * reachability is unproved. Clean C has 25 register/branch words and complete
 * relocation differences at the same 432-byte extent; retain original assembly. */
#line 183 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405304.s")

/* func_caranim_004054B4 gates helper5304 by camera query220 and byte23C,
 * selects a UVLIGHT buffer, optionally draws shadow state, then emits conversion
 * coefficients from an ordered scalar factor. The slct load and signed global
 * halfword override it to one. Shared byte gates precede helper5DE4; selection410
 * chooses the direction of a matching texture-ID replacement across model states.
 * Reread callback-dependent camera/flags/model pointers and byte counts.
 * RE_UNKNOWN: flag/scalar meanings and units, valid camera/state/table/model
 * domains, shared mutation rights and storage/callback lifetimes need original
 * writers, model producers and callers. RE_ORIGINAL_QUIRK: model/nested pointers
 * are consumed without added null/bounds guards; invalid-input reachability is
 * unproved. Clean C is 1072 versus 1116 bytes with 219 word and full relocation
 * differences; retain original assembly pending complete matching proof. */
#line 185 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004054B4.s")

/* Disable light-buffer selection with -1 before checking state selection 0x410.
 * Snapshot selected record words 0x14/0x10 as old/new texture IDs, query the
 * object's model and walk its 12/44/24-byte nested records with unsigned-byte
 * counts. GFXSTATE 0x24 compares the low twelve bits and ORs the unmasked new ID.
 * Preserve pointer/count/export reloads after callbacks. If bytes 0x6B84/0x6B88
 * are zero afterward, reread selection/handle and update the object's loaded model.
 * RE_ORIGINAL_QUIRK: the loaded-model pointer is used without a null check;
 * selection -1 still disables the light buffer before returning.
 * RE_UNKNOWN: selection/handle/texture domains, loaded-model availability,
 * nested-table validity, restore-gate policy and shared asset mutation/lifetimes
 * need original callers, writers, acquisition and teardown evidence. Clean C
 * remains 536 versus 532 bytes with 43 word and full relocation differences:
 * frame/homes, scratch-store order and final table/argument-address scheduling.
 * Retain assembly pending complete proof; no trial types or ABI edits accepted. */
#line 187 "src/modules/caranim.c"
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

/* Native callback consumes channel A0. When the default state and UVTX0x436
 * are available, reread the state and set texture selectors u2/v2 from its
 * scaled float 0x3A8: first value + value, then the saved value. Update main
 * object mask 0x2 from words 0x30/0x34 and the optional signed channel reference.
 * Retain the selected table address; reread table word 0x58 and state byte 0x24
 * after the main callback, then update four auxiliary handles and call 0x4ACC
 * only on the gated set path. Reload each handle/export after earlier calls.
 * RE_ORIGINAL_QUIRK: first null state or selection -1 terminates the registry
 * prefix; the final address is &D_caranim_00407368, not its counter value.
 * RE_UNKNOWN: flag/auxiliary policy, texture units, caller channel/table/handle
 * domains, registry validity and callback/storage lifetimes need original
 * writers, dispatch callers, table/pool setup and teardown evidence. Clean C
 * is 604 versus 616 bytes with 100 word and full relocation differences: frame,
 * channel home, shared loop bound, auxiliary cursor and end-address scheduling.
 * Retain assembly pending complete proof; no trial types or ABI edits accepted. */
#line 198 "src/modules/caranim.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405B7C.s")

/* Select a model from the record indexed by state word 0x410, using the
 * channel vector's projections onto queried object matrix rows. Preserve
 * ordered ratio tests, positive-copy/otherwise-negate magnitude and zero's
 * second-alternate branch. Reread alternate model words and the object handle
 * after provider calls; the record address and initial model are snapshots.
 * RE_ORIGINAL_QUIRK: local matrix/vector outputs are consumed without testing
 * whether object/channel getters rejected their inputs before writing outputs.
 * RE_UNKNOWN: vector role/units, table/model/handle domains, rejection
 * reachability and callback/storage lifetimes need original producers, callers,
 * pool/table extents, model setup and teardown evidence. Clean C is 508 versus
 * 516 bytes with 57 word and full relocation differences: frame/local homes,
 * zero-register reuse and address scheduling. Retain original assembly until
 * complete matching proof; no caller-validity or floating-effect claim. */
#line 200 "src/modules/caranim.c"
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
/* Find the first registered state for this DOBJ handle with unsigned 16-bit traversal. RE_ORIGINAL_QUIRK: constructor0x003AC increments count even when all eight slots are full.
 * RE_UNKNOWN: caller bounds/lifetime must keep the searched prefix in range and nonnull; resolve original creation/lifecycle call sites. */
#line 211 "src/modules/caranim.c"

s32 caranimFindRegisteredStateByObjectHandle(s32 objectHandle) {
    u16 index;
    for (index = 0; index < D_caranim_00407368; index++) {
        if (D_caranim_00407348[index]->objectHandle == objectHandle) {
            return index;
        }
    }
    return -1;
}
#line 220 "src/modules/caranim.c"
#line 210 "src/modules/caranim.c"

#line 1 "caranim-copy-only-body-92012.c"
/* Copy the registered-state pointer prefix and return the live registry
 * count. Recheck that count after each destination store; do not snapshot it.
 * RE_ORIGINAL_QUIRK: the constructor can increment the count when eight slots
 * are full. RE_UNKNOWN: destination capacity/aliasing and registry lifetime. */
s32 caranimCopyRegisteredStates(CarAnimRegisteredState **destination) {
    s32 index;

    for (index = 0; index < D_caranim_00407368; index++) {
        destination[index] = D_caranim_00407348[index];
    }
    return D_caranim_00407368;
}

#line 212 "src/modules/caranim.c"

#line 213 "src/modules/caranim.c"
/* Return the constructor-maintained registry counter; no recount or slot validation. */
s32 caranimGetRegisteredStateCount(void) {
    return D_caranim_00407368;
}
#line 216 "src/modules/caranim.c"

extern void *gCamExports;
extern void *gUvLightExports;

#line 220 "src/modules/caranim.c"
/* Read camera pointer cell CAM0x30; its signed word0x220 selects state light slot0x248
 * when nonnegative, otherwise -1. RE_UNKNOWN: camera/state pointer lifetime, slot bounds
 * and camera-word policy need original producers/callers. No pointer guard is added. */
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
void caranimApplyColorAndCallback(s32 objectId, CarAnimColorContext *colorContext) { /* Use one unchecked color-table word twice, then register the callback with the same context. */
    s32 colorTableIndex = colorContext->colorIndex;
    s32 selectedColorWord = ((s32 *)&D_caranim_00407178)[colorTableIndex];
    gUvDobjExports->uvDobjReplaceLightColorRecord(objectId, selectedColorWord, selectedColorWord, 0);
    gUvDobjExports->uvDobjProps(objectId, 4, caranimSelectCameraLightBufferSlot, colorContext, 0);
/* RE_UNKNOWN: Color-word packing, table bounds and callback context lifetime. */ }
#line 234 "src/modules/caranim.c"

