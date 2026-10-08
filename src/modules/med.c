// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern f32 D_med_00407FE4,D_med_00407FE8,D_med_00407FEC,D_med_00407FF0;
#include "module.h"
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
void func_med_00400160();
void medInitializeCameraNode();
void medReleaseStoredCameraChannel();



void medPackScaledSharedRgba(f32 scale, u32 *color);
void medSetNormalizedColor(s32 arg0);
void func_med_004014C4();
void func_med_00401C10();
void func_med_00401EF8();
void func_med_004021A0();
void func_med_004023E0();
void func_med_00402920();
void func_med_00402C7C();
void medStoreSharedNodeByte23();
void func_med_00404FE0();
void medRefreshMatchedControlText();
void medWriteFirstSharedRgbaCommand();
void medWriteSecondSharedRgbaCommand();
void func_med_004051A8();
void func_med_00405338();
void func_med_004053B4();
void func_med_00405488();
void func_med_004057A8();
void func_med_004059E8();
void func_med_00405DC4();
void func_med_00405FEC();
void medRefreshSelectedEnvironment();
void medQuerySelectedEnvironmentProperties(s32 unused);
void medResetTextureAnimation();
void func_med_00406420();
#include "ultra64.h"
/*__SEEDEXTERNS__*/
extern UvDobj_Exports* gUvDobjExports;
extern s32 D_med_00406BD8[];
extern s32 D_med_00406BF8[];
extern s32 D_med_00406C08;
void medReleaseStoredCameraChannel(const s32 *);
void medReleaseObjectsAndCamera(void);
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
    void (*setTaggedProperties)(void *, s32, ...);
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

#line 82 "src/modules/med.c"
/* Release each non-0xFFFF dynamic-object handle in the original table
 * walk, then release the editor camera. Preserve the overlapping word walk. */
void medReleaseObjectsAndCamera(void)
{
  s32 *entry;
  s32 handle;
  s32 sentinel;
  sentinel = 0xFFFF;
 do { entry = D_med_00406BD8; do { handle = entry[2]; if (sentinel != handle) { gUvDobjExports->uvDobjClearModelAndStateByte(handle); } entry++; } while (entry != D_med_00406BF8); } while (0);
  medReleaseStoredCameraChannel(&D_med_00406C08);
}
#line 91 "src/modules/med.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00400160.s")

#line 94 "src/modules/med.c"
/* Delegate to the preview draw helper, which draws the color swatch and an
 * optional selected texture before the existing overlay callbacks.
 * RE_UNKNOWN: complete preview/editor callback lifecycle. */
void medDrawPreview(void) {
    func_med_004021A0();
}
#line 97 "src/modules/med.c"

#line 98 "src/modules/med.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_med_004007AC(void) {
}
#line 100 "src/modules/med.c"

/* Initialize a camera entity node: create cam entity, set up camera params, identity matrix, and initial pose. */
typedef struct {
    /* 0x00 */ char pad0[0x4];
    /* 0x04 */ s32 (*unk4)(void);
    /* 0x08 */ char pad8[0x18];
    /* 0x20 */ void (*setTaggedProperties)(s32, ...);
} CamExp_4007B4;
typedef struct {
    /* 0x00 */ char pad0[0x1C];
    /* 0x1C */ void (*unk1C)(Mtx4F*);
} UvFMtxExp_4007B4;
extern void *gUvFmtxExports;
extern f32 D_med_00406A94;
extern f32 D_med_00406A98;
extern f32 D_med_00406A9C;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char pad4[0x4];
    /* 0x08 */ Mtx4F unk8;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
} Node_4007B4;
void func_med_00400D18(Node_4007B4 *node);
void func_med_004008F0(void *node);
void medUpdateCameraByMode(Node_4007B4 *node);

#line 131 "src/modules/med.c"
/* Create and configure the editor camera, initialize its pose scalars
 * and identity matrix, set translation Y=-10/Z=5, then select the original
 * camera-update path. Preserve property order and double promotions.
 * The original dispatcher forwards the incoming node pointer unchanged
 * to both update paths. RE_UNKNOWN: mode transitions and node/camera
 * lifetime require original mode writers and create/use callers. */
#line 137 "src/modules/med.c"

void medInitializeCameraNode(Node_4007B4 *node)
{
  float unitScale;
  s32 camera;
  camera = ((CamExp_4007B4 *) gCamExports)->unk4();
  unitScale = 1.0f;
  node->unk0 = camera;
  ((CamExp_4007B4 *) gCamExports)->setTaggedProperties(camera, 0x9, (f64) D_med_00406A94, 0x6, (f64) unitScale, 0x7, (f64) D_med_00406A98, 0);
  node->unk48 = 0.0f;
  node->unk4C = D_med_00406A9C;
  node->unk50 = 10.0f;
  node->unk54 = 0.0f;
  node->unk58 = 0.0f;
  node->unk5C = 0.0f;
  node->unk60 = 0.0f;
  node->unk64 = 0.0f;
  node->unk68 = 0.0f;
  ((UvFMtxExp_4007B4 *) gUvFmtxExports)->unk1C(&node->unk8);
  node->unk8.m[3][1] = -10.0f;
  node->unk8.m[3][2] = 5.0f;
  medUpdateCameraByMode(node);
}
#line 159 "src/modules/med.c"
#line 153 "src/modules/med.c"

#line 154 "src/modules/med.c"
#line 154 "src/modules/med.c"

/* Forward the stored camera address to CAM slot 0x08: it forwards the signed-short channel through UVCHAN slot 0x20, then writes -1.
 * RE_UNKNOWN: camera allocation/ownership, repeated-release validity and alias/lifetime require original channel consumers, storage writers and create/use/release callers. */
void medReleaseStoredCameraChannel(const s32 *cameraWord) {
    (*(void (**)(s16 *))((u8*)gCamExports + 0x8))((s16 *)(u32)*cameraWord);
}
#line 159 "src/modules/med.c"
#line 157 "src/modules/med.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004008F0.s")
/* RE_UNKNOWN: node angular/target-offset frames and physical meanings, shared control-scale domain, camera object extent/lifetime and the historical extra MISC60 float-input declaration require original node/scale/mode writers and source callers; actual FMTX4C builds a facing basis and CAM28 copies into object+0x1A8, while the original incoming node word is forwarded by the dispatcher. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00400D18.s")

#line 162 "src/modules/med.c"
/* Dispatch to the original camera update selected by the shared mode word. */
#line 163 "src/modules/med.c"

void medUpdateCameraByMode(Node_4007B4 *node) {
    if (D_med_00406C00 == 0) {
        func_med_00400D18(node);
        return;
    }
    func_med_004008F0(node);
}
#line 170 "src/modules/med.c"
#line 169 "src/modules/med.c"

#line 170 "src/modules/med.c"
/* Scale each shared color component by 255 and the caller scale, perform the
 * original unsigned conversion and retain each low byte before packing RGBA.
 * Preserve conversion/truncation behavior rather than adding color clamps. */
void medPackScaledSharedRgba(f32 scale, u32 *color) {
    u32 red,green,blue,alpha;
    red = (u32)(D_med_00407FE4 * 255.0f * scale) & 0xFF;
    green = (u32)(D_med_00407FE8 * 255.0f * scale) & 0xFF;
    blue = (u32)(D_med_00407FEC * 255.0f * scale) & 0xFF;
    alpha = (u32)(D_med_00407FF0 * 255.0f * scale) & 0xFF;
    *color = (red << 24) | (green << 16) | (blue << 8) | alpha;
}
#line 171 "src/modules/med.c"

#line 172 "src/modules/med.c"
/* Unpack the supplied RGBA word into four normalized scalar channels
 * using the original division by 255 and store order. */
void medSetNormalizedColor(s32 rgba) {
    D_med_00407FE4 = (f32) ((rgba >> 0x18) & 0xFF) / 255.0f;
    D_med_00407FE8 = (f32) ((rgba >> 0x10) & 0xFF) / 255.0f;
    D_med_00407FEC = (f32) ((rgba >> 8) & 0xFF) / 255.0f;
    D_med_00407FF0 = (f32) (rgba & 0xFF) / 255.0f;
}
#line 178 "src/modules/med.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004014C4.s")
/* RE_UNKNOWN: the original model-ID output starts 32 bytes before the count word, but ENV selector 11 copies its full u8 count without an eight-item clamp; historical stack-object capacity, UVEN asset/caller bounds, UVMD load-success/lifetime and VATR variadic filter/vertex meaning require original object-layout, asset and producer/caller evidence. Preserve the original promoted-word VATR calls and do not infer a reachable fault from the unproved bounds. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00401C10.s")
/* RE_UNKNOWN: editor sentinel/flag lifecycle, D_med_00406BD8 word-window bounds, signed scene-file IDs, CARA input/selector roles, resource/allocation success and the MED code-address word stored by GAMEGUI require original record/control writers, assets, state readers and shared-word consumers; preserve the common +8/+0x30 storage base and do not infer callback invocation from the stored address. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00401EF8.s")
/* RE_UNKNOWN: selected texture-sequence validity, shared color/property-four scalar domains and units, file-load success and callback/resource lifetime guarantees require original control/sequence producers, resource inventory and callers; the pre-property loaded-file snapshot is intentional, and CARA slot28 only homes the forwarded word, leaving its historical source type unresolved. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004021A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004023E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00402920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00402C7C.s")

#line 193 "src/modules/med.c"
/* When the shared node is present, copy the shared word at 0x2C into
 * node byte 0x23. Preserve the unused argument and low-byte conversion. */
void medStoreSharedNodeByte23(s32 unused) {
    s32 nodeAddress;
    nodeAddress = *(s32*)((u8*)&D_med_00407F28 + 0x0);
    if (nodeAddress != 0) {
        *(u8*)(nodeAddress + 0x23) = *(s32*)((u8*)&D_med_00407F28 + 0x2C);
    }
}
#line 200 "src/modules/med.c"
/* RE_UNKNOWN: shared word-window and referenced-record extents/ownership, four interleaved scalar-pair meanings and historical unused-argument type require original D_med_00407F28 producers, record readers and source/caller declarations; preserve the initial reference gate, two-pointer snapshot, four-byte source step and separate original load/store order without assuming complete object layouts. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00404FE0.s")

typedef struct {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ void *unk28;
} MedNode_0040505C;
typedef struct {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ f32 unk24;
} MedObj_0040505C;
typedef struct {
    /* 0x00 */ char pad0[0xC];
    /* 0x0C */ s32 (*unkC)(s32, s32, s32, s32);
    /* 0x10 */ char pad10[0x4];
    /* 0x14 */ void (*unk14)(void *, s32);
} MedExp_0040505C;
/* Original GUI C4 copies30 source bytes; the source is an address.
 * RE_UNKNOWN: full GUI prefix and unreferenced slots. */
typedef struct {
    u8 unused00[0xC4];
    void (*copyUpperTextText)(void *, u8 *);
} UvGuiExp_0040505C;
extern MedNode_0040505C *D_med_00408048[];
extern void *D_med_00407F70;
extern s32 D_med_00407F60;
extern UvGuiExp_0040505C *gUvGuiExports;

#line 226 "src/modules/med.c"

#line 227 "src/modules/med.c"
/* Find the control in the original 16-entry table and derive lookup selectors.
 * Actual DLED slot 0x0C returns a mapped original combiner-source label word;
 * pass that address to GUI C4, then preserve the existing DLED follow-up.
 * Original DLED ignores the first lookup word and uses unchecked signed indices.
 * Slot 0x14 packs the observed 16-word shared window into the supplied FC command.
 * RE_UNKNOWN: index validity, label's 30-byte source window, shared backing extent,
 * alias/lifetime and historical source declarations require original producers/callers. */
void medRefreshMatchedControlText(void *control)
{
  void **entry;
  s32 index;
  int middleIndex;
 entry = (void **) D_med_00408048; index = 0; loop_1: if (control != ((MedNode_0040505C *) (*entry))->unk28) {
    index += 1;
    entry += 1;
    if (index != 0x10)
    {
      goto loop_1;
    }
  }

  middleIndex = (index >> 2) & 1;
  if (index != 0x10)
  {
    gUvGuiExports->copyUpperTextText(control, (u8 *)((MedExp_0040505C *) D_med_004080A0)->unkC((index >> 3) & 1, middleIndex, index & 3, (s32) ((MedObj_0040505C *) control)->unk24));
    ((MedExp_0040505C *) D_med_004080A0)->unk14(&D_med_00407F70, D_med_00407F60);
  }
}
#line 248 "src/modules/med.c"
#line 248 "src/modules/med.c"

#line 249 "src/modules/med.c"
/* Pack four shared RGBA floats at D_med_00407FB0 into the selected 0xFA command; preserve unused.
 * RE_UNKNOWN: command address/lifetime, shared backing extent and scalar domains require original writers/callers; actual DLED slot 0x10 truncates scaled channels without clamps and skips a null command. */
#line 251 "src/modules/med.c"

#line 252 "src/modules/med.c"

void medWriteFirstSharedRgbaCommand(s32 unused) {
    (*(void (**)(void *, const f32 *, u32))((u8*)D_med_004080A0 + 0x10))((void *)(u32)D_med_00407F64, (const f32 *)&D_med_00407FB0, 0xFA);
}
#line 255 "src/modules/med.c"
#line 254 "src/modules/med.c"
#line 252 "src/modules/med.c"

#line 253 "src/modules/med.c"
/* Pack four shared RGBA floats at D_med_00407FC0 into the selected 0xFB command; preserve unused.
 * RE_UNKNOWN: command address/lifetime, shared backing extent and scalar domains require original writers/callers; actual DLED slot 0x10 truncates scaled channels without clamps and skips a null command. */
#line 255 "src/modules/med.c"

#line 256 "src/modules/med.c"

void medWriteSecondSharedRgbaCommand(s32 unused) {
    (*(void (**)(void *, const f32 *, u32))((u8*)D_med_004080A0 + 0x10))((void *)(u32)D_med_00407F68, (const f32 *)&D_med_00407FC0, 0xFB);
}
#line 259 "src/modules/med.c"
#line 258 "src/modules/med.c"
#line 256 "src/modules/med.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004051A8.s")

/* Environment export call (single float pair) when D_med_00407FD4 != -1 */
typedef struct {
    char pad0[0x8];
    void (*unk8)(s32, s32, f64, f64, s32);
} UvEnvExp_4052C8;
extern UvEnvExp_4052C8 *gUvEnvExports;
typedef struct {
    char pad0[0x24];
    f32 unk24;
} Node_4052C8;
extern s32 D_med_00407FD4;

#line 271 "src/modules/med.c"
/* Set environment property three from node scalar 0x24 with rate one
 * when the environment handle is valid. Preserve double promotions. */
void medSetEnvironmentBlendFromNode(Node_4052C8 *node)
{
  s32 environment;
  float rate;
  s32 savedEnvironment;
  environment = D_med_00407FD4;
  savedEnvironment = environment;
  if (environment != (-1))
  {
    rate = 1.0f;
    gUvEnvExports->unk8(savedEnvironment, 3, (f64) node->unk24, (f64) rate, 0);
  }
}
#line 284 "src/modules/med.c"
/* RE_UNKNOWN: physical meaning/units, valid environment/control domains and camera object bounds/lifetime require original UVEN/CAM field readers, assets and create/use callers; original ENV7 consumes one promoted double into record+0x48, CAM7 marks object+0x10 and stores float+0x24, and the same once-promoted control value is saved across both calls without a validity guard. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405338.s")
/* RE_UNKNOWN: original GUI C4 reads 30 bytes from the formatted NO PALETTE/decimal label address, but historical local-object extent and trailing-byte state remain unresolved; truncated control domain, UVTP resource bounds/load success and selected-table lifetime require original stack/source, control callers and asset/load-unload evidence. Preserve the saved pre-callback selection and 0xFFFF clear sentinel without adding clamps or assuming a reachable fault. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004053B4.s")
/* RE_ORIGINAL_QUIRK: DLED opcode scans cannot stop at positive 0xDF after sign extension. RE_UNKNOWN: selected-index/count domains, required command presence, scratch allocation success, shared/control backing extent/alias/lifetime and the GUI label's 30-byte read window/trailing state require original control/storage writers, UVTX assets, allocation paths and callers; preserve restore/search/scratch/FC/FA/FB order and do not assume target-absent fallbacks or a reachable player fault. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405488.s")
/* RE_ORIGINAL_QUIRK: unbounded load retry and unchecked object-create result. RE_UNKNOWN: scalar domain, overlapping word-table bounds/lifetime, label extent/trailing bytes and failure reachability; trace original control/table producers, stack objects, resource inventory and callers before changing retry, traversal or failure behavior. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004057A8.s")
/* RE_UNKNOWN: selected-ID/selector domains, scene-byte versus signed-cache relation, property units/frames, storage alias/lifetime and the label's 30-byte consumer window/trailing state require original control/storage writers, UVEN assets and create-use-release callers. LIGHT tag 4 conditionally skips its supplied triple when context halfword +2 is nonzero; inspect original flag writers/caller contexts before changing the preserved call. Readable C is not yet instruction-equivalent; resolve original local declarations and compiler dataflow without inventing storage or changing callback/reload order. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_004059E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405DC4.s")
/* RE_UNKNOWN: control-selection domain/lifecycle, color-property/resource interpretation and shared label extent/trailing-byte state require original control and selector producers, resource readers and backing-storage/source evidence; preserve the checked ten-case label/selector mapping, default -1, original pre-callback input snapshot, GUI C4 30-byte read and cache store after the color-query callback. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00405FEC.s")

#line 299 "src/modules/med.c"
/* Run the original environment refresh only when the selection is not -1.
 * Preserve the unused argument and original sentinel check. */
void medRefreshSelectedEnvironment(s32 unused) {
    if (D_med_00407FDC != -1) {
        func_med_004014C4();
    }
}
#line 304 "src/modules/med.c"

/* Forward the selected object's light handle and three promoted scalars through the existing property-one call. */
#line 306 "src/modules/med.c"
#line 306 "src/modules/med.c"

/* Forward the selected light handle and three promoted shared scalars as tag1, then tag0; preserve unused.
 * Actual LIGHT08 writes context+4/8/C and forwards that triple through UVLIGHT14.
 * RE_UNKNOWN: triple meaning/units and scene/object/shared alias/lifetime require original UVLIGHT14 readers, storage writers and callers. */
void medSetSelectedObjectLightScalarTriple(s32 unused) {
    if (D_med_00407F08 != NULL) {
        gLightExports->setTaggedProperties((char *)gSceneExports->unk2C + 0x28, D_med_00407F08->unk248, 1,
                            (f64) D_med_00408028.unk0, (f64) D_med_00408028.unk4,
                            (f64) D_med_00408028.unk8, 0);
    }
}
#line 316 "src/modules/med.c"
#line 313 "src/modules/med.c"

#line 314 "src/modules/med.c"
/* Query five RGB property triplets, two blend values and one scalar from
 * the selected environment. The original editor routine discards the results
 * and shares one output for both blend rates. Preserve the unused argument
 * and skip the call when the environment handle is -1. */
void medQuerySelectedEnvironmentProperties(s32 unused) {
    f32 color8R, color8G, color8B;
    f32 color9R, color9G, color9B;
    f32 color5R, color5G, color5B;
    f32 color10R, color10G, color10B;
    f32 blend2, blend3, scalar7;
    f32 color4R, color4G, color4B;
    f32 sharedBlendRate;
    if (D_med_00407FD4 != -1) {
        ((UvEnv_Exports *)gUvEnvExports)->uvEnvGetProps(D_med_00407FD4,
            8, &color8R, &color8G, &color8B,
            9, &color9R, &color9G, &color9B,
            5, &color5R, &color5G, &color5B,
            4, &color4R, &color4G, &color4B,
            10, &color10R, &color10G, &color10B,
            2, &blend2, &sharedBlendRate,
            3, &blend3, &sharedBlendRate,
            7, &scalar7, 0);
    }
}
#line 315 "src/modules/med.c"

#line 316 "src/modules/med.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_med_004063CC(s16 a0) {
}
#line 318 "src/modules/med.c"

#line 319 "src/modules/med.c"
/* Run the original texture-animation cleanup and initialization hooks
 * in order. The argument is intentionally unused. */
void medResetTextureAnimation(s32 unused) {
    (*(void (**)(void))((u8*)gUvTexAnimExports + 0x8))();
    (*(void (**)(void))((u8*)gUvTexAnimExports + 0x4))();
}
#line 323 "src/modules/med.c"

#line 324 "src/modules/med.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_med_00406418(void) {
}
#line 326 "src/modules/med.c"
/* RE_UNKNOWN: the 64-byte signed-word read window at D_med_00407F70 does not prove one backing array allocation; control scalar roles/units, non-null pointers and alias domains require original storage writers, GUI creators/readers and callers before changing bounds or types. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/med/func_med_00406420.s")

