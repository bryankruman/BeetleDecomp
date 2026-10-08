// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[0x224]; u8 first[0x20]; u8 second[0x20]; u8 pending; } CameraSceneSyncState;
typedef struct { u8 unk00[0x24]; void (*copy)(void *, void *); u8 unk28[4]; void *data; } CameraSceneSyncExports;
extern void *gSceneExports;
typedef struct { u8 unk00[0x158]; f32 component158; u8 unk15C[0x39]; u8 active; u8 unk196[2]; s32 remaining; f32 direction; f32 amplitude; } CameraShakeState;
extern f32 D_cam_004048D4, D_cam_004048D8;
/*__SEEDEXTERNS__*/
typedef struct { char pad[0xC]; void (*copyMatrix)(Mtx4F *, Mtx4F *); } UvFMtxExp_00403A9C;
extern UvFMtxExp_00403A9C *gUvFmtxExports;
extern void *D_cam_00404E28;
extern f32 D_cam_00404958;
extern void *D_cam_00404DF4;
extern s32 D_cam_00404E2C;
extern void *gUvChanExports;
extern void *gUvEnvExports;
extern void *D_cam_00404E08;
/* Initializer-only original address registry, not a callable API.
 * Existing unresolved prototypes remain unchanged; opaque linker code labels
 * below are only addresses and are never dereferenced or invoked here.
 * RE_UNKNOWN: original target/caller evidence must establish their complete
 * callback contracts before replacing unresolved declarations. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 unknownCallback04Address;
    /* 0x08 */ u32 releaseChannelHandleAddress;
    /* 0x0C */ u32 unknownCallback0CAddress;
    /* 0x10 */ u32 unknownCallback10Address;
    /* 0x14 */ u32 syncPendingSceneRecordsAddress;
    /* 0x18 */ u32 rememberCameraAndRenderChannelAddress;
    /* 0x1C */ u32 unknownCallback1CAddress;
    /* 0x20 */ u32 unknownCallback20Address;
    /* 0x24 */ u32 unknownCallback24Address;
    /* 0x28 */ u32 copyMatrixAt1A8Address;
    /* 0x2C */ u32 unknownCallback2CAddress;
    /* 0x30 */ u32 sharedPointerAddress;
    /* 0x34 */ u32 sharedScalarAddress;
} CameraExportAddresses;
extern f32 D_cam_00404DF8;
extern void *D_cam_00404DFC;
extern s32 D_cam_00404E00, D_cam_00404E04;
extern char D_cam_00404810[], D_cam_0040481C[];
/* Exact declaration from the accepted src/profiler.c definition. */
s32 uvProfilerCreate(char* label);
/* Copy the existing unresolved declaration here so the original
 * code-label address is visible before the initializer. */
extern void func_cam_00403394(void *, s32, s32, f64, s32);
void func_cam_00400128(void);
void camReleaseChannelHandle(s16 *channelHandle);
void camSyncPendingSceneRecords(CameraSceneSyncState *state);
void camRememberCameraAndRenderChannel(void *camera);
void camCopyMatrixIntoRecordOffset1A8(char *camera, Mtx4F *sourceMatrix);
extern u8 func_cam_00400190[];
extern u8 func_cam_00400E80[];
extern u8 func_cam_0040116C[];
extern u8 func_cam_004031B4[];
extern u8 func_cam_00403A20[];
extern u8 func_cam_00403ACC[];

#line 60 "src/modules/cam.c"
/* Register twelve original camera callback addresses and two shared-data
 * addresses in their original interleaved order; slot0x28 copies the incoming
 * matrix into camera offset0x1A8. Set shared scalar1/count0, load font file3 and
 * cara, then create the two original profiler entries and retain their IDs.
 * RE_UNKNOWN: callbacks 0x04/0C/10/1C/20/24/2C, shared pointer/scalar roles,
 * dependency ownership and safe initialization/reload require original target
 * bodies, data consumers and loader callers. Preserve unchecked dependency
 * loads and profiler results; changing failure handling needs caller evidence. */
void __entrypoint_func_camInitializeModuleState(CameraExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_cam_00400128;
    exports->copyMatrixAt1A8Address = (u32) camCopyMatrixIntoRecordOffset1A8;
    exports->unknownCallback04Address = (u32) func_cam_00400190;
    exports->unknownCallback2CAddress = (u32) func_cam_00403ACC;
    exports->releaseChannelHandleAddress = (u32) camReleaseChannelHandle;
    exports->unknownCallback0CAddress = (u32) func_cam_00400E80;
    exports->unknownCallback10Address = (u32) func_cam_0040116C;
    exports->syncPendingSceneRecordsAddress = (u32) camSyncPendingSceneRecords;
    exports->rememberCameraAndRenderChannelAddress = (u32) camRememberCameraAndRenderChannel;
    exports->unknownCallback1CAddress = (u32) func_cam_004031B4;
    exports->unknownCallback20Address = (u32) func_cam_00403394;
    exports->unknownCallback24Address = (u32) func_cam_00403A20;
    exports->sharedPointerAddress = (u32) &D_cam_00404DF4;
    exports->sharedScalarAddress = (u32) &D_cam_00404DF8;
    D_cam_00404DF8 = 1.0f;
    D_cam_00404E2C = 0;
    uvLoadFile(0x55564654, 3);
    D_cam_00404DFC = uvLoadModule(0x63617261);
    D_cam_00404E00 = uvProfilerCreate(D_cam_00404810);
    D_cam_00404E04 = uvProfilerCreate(D_cam_0040481C);
}
#line 61 "src/modules/cam.c"

#line 20 "src/modules/cam.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_cam_00400128(void) {
}
#line 22 "src/modules/cam.c"

#line 23 "src/modules/cam.c"
/* Unless sourceFileId is -1, copy that loaded UVEN record into the file ID
 * at camera+0x220. Then assign that destination file to the signed-short slot
 * at camera+0, reloading both camera fields after the optional copy callback.
 * Native A1 retains sourceFileId at slot0x1C; both original providers take two
 * integer arguments. RE_UNKNOWN: camera layout, valid IDs/slots, ownership,
 * aliasing and callback lifecycle need original producers and callers. */
#line 29 "src/modules/cam.c"

void camAssignEnvironmentFileWithOptionalCopy(void *camera, s32 sourceFileId) {
    void *savedCamera;

    savedCamera = camera;
    if (sourceFileId != -1) {
        (*(void (**)(s32, s32))((u8 *)gUvEnvExports + 0x1C))(*(s32 *)((u8 *)camera + 0x220), sourceFileId);
    }
    (*(void (**)(s32, s32))((u8 *)gUvEnvExports + 0x18))(*(s16 *)((u8 *)savedCamera + 0x0), *(s32 *)((u8 *)savedCamera + 0x220));
}
#line 38 "src/modules/cam.c"
#line 32 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00400190.s")

#line 35 "src/modules/cam.c"
/* Decrement the shared camera count, release the signed-short channel
 * handle and replace it with -1. Preserve unconditional release behavior. */
void camReleaseChannelHandle(s16 *channelHandle) {
    *(s32 *)((u8 *)&D_cam_00404E2C + 0) -= 1;
    (*(void (**)(s32))((u8 *)gUvChanExports + 0x20))(*channelHandle);
    *channelHandle = -1;
}
#line 40 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004007C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00400C0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00400E80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_0040116C.s")

#line 49 "src/modules/cam.c"
/* When pending, copy the shared scene record at offset 0xD8 into both
 * 32-byte camera records through scene export 0x24, then clear the pending byte. */
void camSyncPendingSceneRecords(CameraSceneSyncState *state) {
    if (state->pending != 0) {
        ((CameraSceneSyncExports *)gSceneExports)->copy(state->first, (u8 *)((CameraSceneSyncExports *)gSceneExports)->data + 0xD8);
        ((CameraSceneSyncExports *)gSceneExports)->copy(state->second, (u8 *)((CameraSceneSyncExports *)gSceneExports)->data + 0xD8);
        state->pending = 0;
    }
}
#line 50 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004015C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004018E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00401B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00401D3C.s")

extern void func_cam_00403394(void *, s32, s32, f64, s32);
extern f32 D_cam_004048D0;
typedef struct
{
  char pad[0x0C];
  s32 (*unkC)(void *, f32 *);
} ExplExp_00402158;
extern ExplExp_00402158 *gExplExports;
typedef struct
{
  char pad[0x20];
  void (*unk20)(f32, f32, s32, void *);
} MiscExp_00402158;
extern MiscExp_00402158 *gMiscExports;
typedef struct
{
  f32 x;
  f32 y;
  f32 z;
} Vec3F_00402158;
typedef struct
{
  char pad[0x28];
  void (*unk28)(Vec3F_00402158 *, Vec3F_00402158 *, Vec3F_00402158 *);
} UvFVecExp_00402158;
extern UvFVecExp_00402158 *gUvFvecExports;

#line 86 "src/modules/cam.c"
/* Accumulate camera scalar 0x15C, build/offset a point and forward a successful
 * query value to camera property selector0x12/index3 as a promoted double.
 * RE_ORIGINAL_QUIRK: the ordered >0 test negates nonpositive values and NaNs;
 * preserve this operation rather than substituting an absolute-value helper.
 * RE_UNKNOWN: scalar units, query role, export types and camera effect need
 * original providers/callers; offset-based local names imply no physical role. */
#line 92 "src/modules/cam.c"

void camAccumulateScalarAndQueryProperty(void *camera, void *sourceRecord, void *coefficients)
{
    f32 queriedPropertyValue;
    void *savedSourceRecord;
    f32 sourceScalar3B0;
    Vec3F_00402158 queryPoint;
    f32 sourceScalar3BC;
    f32 positiveOrNegated3BC;
    sourceScalar3BC = *((f32 *) (((u8 *) sourceRecord) + 0x3BC));
    if (sourceScalar3BC > 0.0f)
    {
        positiveOrNegated3BC = sourceScalar3BC;
    }
    else
    {
        positiveOrNegated3BC = -sourceScalar3BC;
    }
    savedSourceRecord = sourceRecord;
    sourceScalar3B0 = *((f32 *) (((u8 *) savedSourceRecord) + 0x3B0));
    *((f32 *) (((u8 *) camera) + 0x15C)) += (positiveOrNegated3BC * (*((f32 *) (((u8 *) coefficients) + 0x24)))) + (sourceScalar3B0 * (*((f32 *) (((u8 *) coefficients) + 0x28))));
    gMiscExports->unk20(*((f32 *) (((u8 *) camera) + 0x15C)), (*((f32 *) (((u8 *) camera) + 0x150))) - D_cam_004048D0, *((s32 *) (((u8 *) camera) + 0x154)), &queryPoint);
    gUvFvecExports->unk28(&queryPoint, &queryPoint, (Vec3F_00402158 *) (((u8 *) camera) + 0x1F0));
    if (gExplExports->unkC(&queryPoint, &queriedPropertyValue) != 0)
    {
        func_cam_00403394(camera, 0x12, 3, (f64) queriedPropertyValue, 0);
    }
}
#line 119 "src/modules/cam.c"
#line 113 "src/modules/cam.c"

#line 111 "src/modules/cam.c"
/* Alternate the offset direction by signed countdown parity and add its
 * scaled contribution to component 0x158. After countdown underflow, clear
 * activation, countdown, direction and amplitude in the original order. */
void camUpdateAlternatingOffset(CameraShakeState *state) {
    if (state->remaining % 2) state->direction = D_cam_004048D4;
    else state->direction = D_cam_004048D8;
    state->remaining--;
    if (state->remaining < 0) {
        state->active = 0;
        state->remaining = 0;
        state->direction = 0.0f;
        state->amplitude = 0.0f;
        return;
    }
    state->component158 = state->component158 + state->direction * state->amplitude;
}
#line 112 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004022E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_0040263C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00402934.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00402E08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00402FEC.s")

#line 123 "src/modules/cam.c"
/* Store the selected camera and render its signed-short channel
 * through the channel export.
 * RE_UNKNOWN: ownership/lifetime of the retained camera pointer. Trace
 * camera creators/releases and readers of D_cam_00404DF4 to establish when
 * the pointer can be released; retaining it does not prove caller ownership. */
void camRememberCameraAndRenderChannel(void *camera) {
    D_cam_00404DF4 = camera;
    (*(void (**)(s32))((u8 *)gUvChanExports + 0x24))(*(s16 *)camera);
}
#line 127 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004031B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00403394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00403A20.s")

/* Advances a Mtx4F pointer by 0x1A8 bytes into a camera struct and calls the UvFMtx export at offset 0xC */
#line 135 "src/modules/cam.c"
/* Copy sixteen floats from the incoming source into camera offset 0x1A8.
 * Original wrapper forwards A1 unchanged; actual FMTX slot0C consumes that
 * source pointer. RE_UNKNOWN: matrix frame/role, camera layout and valid source
 * lifetime/aliasing; trace original callback callers before generalizing. */
#line 139 "src/modules/cam.c"

void camCopyMatrixIntoRecordOffset1A8(char *camera, Mtx4F *sourceMatrix) {
    gUvFmtxExports->copyMatrix((Mtx4F *)(camera + 0x1A8), sourceMatrix);
}
#line 142 "src/modules/cam.c"
#line 138 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00403ACC.s")

#line 141 "src/modules/cam.c"
/* Clear the shared camera record word at offset 0x1EC; the argument is unused.
 * RE_UNKNOWN: word purpose, callback role and shared record layout. */
#line 143 "src/modules/cam.c"

void camClearSharedRecordWord1EC(s32 callbackValue) {
    *(s32*)((u8*)D_cam_00404E08 + 0x1EC) = 0;
}
#line 146 "src/modules/cam.c"
#line 144 "src/modules/cam.c"

#line 145 "src/modules/cam.c"
/* Multiply the shared record scalar at 0x14 by the original constant
 * into field 0x18, then set its flags at 0x10 and 0xC. Preserve the
 * unused callback parameter. RE_UNKNOWN: the scalar unit and effect role
 * have not been established, so no physical camera-effect name is inferred. */
void camArmSharedScaledValue(s32 callbackValue) {
    *(f32 *)((u8 *)D_cam_00404E28 + 0x18) = *(f32 *)((u8 *)D_cam_00404E28 + 0x14) * D_cam_00404958;
    *(s32 *)((u8 *)D_cam_00404E28 + 0x10) = 1;
    *(s32 *)((u8 *)D_cam_00404E28 + 0xC) = 1;
}
#line 150 "src/modules/cam.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004040D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_004042FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/cam/func_cam_00404558.s")

