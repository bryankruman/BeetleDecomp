// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
s32 func_uvterra_rom_0040CF98(const u8 *packedLevels, s32 index);
extern f32 D_uvterra_rom_0040D704;
extern f32 D_uvterra_rom_0040D708;
#include "uvsort_rom.h"
extern UvSort_Exports *D_uvterra_rom_0040F770;
extern s32 D_uvterra_rom_0040FBCC;
extern s32 D_uvterra_rom_0040FBC8;
extern s32 D_uvterra_rom_0040FBD4;
extern s32 D_uvterra_rom_0040FBD0;
typedef struct { u8 prefix[4]; void (*get)(s32, ...); } TerrainChannelListExports;
extern void *D_uvterra_rom_0040F760;
void func_uvterra_rom_0040078C(s32);
void func_uvterra_rom_0040AC9C(s32);
void uvTerraRefreshProjectionAndDrawQueuedTiles(s32);
#include "module.h"
extern UvModel_Exports *D_uvterra_rom_0040F758;
extern s32 *D_uvterra_rom_0040F78C;
#line 18 "src/modules/uvterra_rom.c"
extern UvFMtx_Rom_Exports *D_uvterra_rom_0040F744;
extern s32 D_uvterra_rom_0040FBD8, D_uvterra_rom_0040FBDC;
void func_uvterra_rom_004072EC(s32, u16, uvUnkTileStruct *, void *, u16);
void func_uvterra_rom_004076A8(s32, uvUnkTileStruct *, u16, u16, void *, u16);
#include "stdarg.h"
extern void *D_uvterra_rom_0040F774;
extern s32 D_uvterra_rom_0040F778;
#include "uvfvec_rom.h"
extern UvFVec_Rom_Exports *D_uvterra_rom_0040F748;
extern f32 D_uvterra_rom_0040D6F8;
extern s32 D_uvterra_rom_0040FBF0;
extern s32 D_uvterra_rom_0040FBF4;
extern u8 D_uvterra_rom_0040F7A0[];
#include "module.h"
#include "uvasset_types.h"
/* Original draw queue uses 16-byte records. This view names only observed
 * consumers; RE_UNKNOWN: byte 0x05 and word 0x0C meanings and the complete
 * historical record declaration. Trace the original 0x40078C queue producer. */
typedef struct {
    /* 0x00 */ uvUnkTileStruct *tile;
    /* 0x04 */ u8 secondMask;
    /* 0x05 */ u8 unknown5;
    /* 0x06 */ u16 firstMask;
    /* 0x08 */ f32 comparisonValue;
    /* 0x0C */ u32 unknownC;
} TerrainTileDrawRecord;
extern TerrainTileDrawRecord *D_uvterra_rom_0040FBE8;
extern f32 D_uvterra_rom_0040FBA8;
extern f32 D_uvterra_rom_0040D710;
void uvTerraDrawTileGeometry(s32, uvUnkTileStruct *, u16, u16);
#include "uvgfxmgr_rom.h"
#include "uvchannel_rom.h"
extern UvGfxState_Rom_Exports *D_uvterra_rom_0040F750;
extern UvGfxMgr_Exports *D_uvterra_rom_0040F754;
extern s32 D_uvterra_rom_0040FBC4;
extern f32 D_uvterra_rom_0040FBAC;
extern f32 D_uvterra_rom_0040FBB0;
extern f32 D_uvterra_rom_0040FBB4;
extern f32 D_uvterra_rom_0040FBB8;
extern f32 D_uvterra_rom_0040FBBC;
extern f32 D_uvterra_rom_0040FBC0;
UnkSobjDraw *uvTerraGetStaticObject(s32 handle);
#line 8 "src/modules/uvterra_rom.c"
extern f32 D_uvterra_rom_0040D6E4;
extern s32 D_uvterra_rom_0040FBA4;
extern u16 D_uvterra_rom_0040D718[64][64];
// uvchan_rom exports
typedef struct UnkStruct_uvterra_rom_0040F760_s {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ void (*unk4)(s32, s32, f32 *, s32); /* inferred */
    /* 0x08 */ char pad8[0x24];                    /* maybe part of unk4[0xA]? */
    /* 0x2C */ s32 (*unk2C)(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4); /* inferred */
} UnkStruct_uvterra_rom_0040F760;                                              /* size = 0x30 */

/* Original initializer imports ISCT here. Export 0x18 is the existing
 * scaled-triangle normal helper; use its producer's full typed interface. */
#include "uvintersect_rom.h"


/*
 * D_uvterra_rom_0040F760 = uvLoadModule('CHAN');
 * D_uvterra_rom_0040F770 = uvLoadModule(0x534F5254);
 * D_uvterra_rom_0040F74C = uvLoadModule(0x494D5458);
 * D_uvterra_rom_0040F744 = uvLoadModule(0x464D5458);
 * D_uvterra_rom_0040F748 = uvLoadModule(0x46564543);
 * D_uvterra_rom_0040F750 = uvLoadModule(0x53544154);
 * D_uvterra_rom_0040F754 = uvLoadModule(0x474D4752);
 * D_uvterra_rom_0040F75C = uvLoadModule('MATH');
 * D_uvterra_rom_0040F758 = uvLoadModule(0x4D4F444C);
 * D_uvterra_rom_0040F764 = uvLoadModule('CBCK');
 * D_uvterra_rom_0040F768 = uvLoadModule('ISCT');
 * D_uvterra_rom_0040F76C = uvLoadModule('QERY');
 */

u16 uvTerraLookupAdjustedWrappedIndexPair(s16 arg0, s16 arg1, u8 arg2);
void func_uvterra_rom_0040B26C(s16 *arg0, s16 *arg1, s16 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7, f32 arg8, f32 arg9, u8 arg10, f32 arg11, f32 arg12);
void *func_uvterra_rom_0040C0F8(s32);
void func_uvterra_rom_0040C218(s32);
s32 func_uvterra_rom_0040B8C0(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6, s16 *arg7, s16 *arg8, u8 arg9);

extern UvCback_Exports *D_uvterra_rom_0040F764;
extern s32 *D_uvterra_rom_0040F77C;
extern UvMath_Exports *D_uvterra_rom_0040F75C;
extern UvQuery_Exports* D_uvterra_rom_0040F76C;
extern f32 D_uvterra_rom_0040D6A8;
extern s32 D_uvterra_rom_0040F740;
extern s32 D_uvterra_rom_0040FBEC;
extern UvIntersect_Exports* D_uvterra_rom_0040F768;

#line 1 "uvterra-draft-extra-declarations"
s32 func_uvterra_rom_00406324(Vtx *, Vtx *, Vtx *, f32 *, f32 *, f32 *, f32, f32);
UnkSobjDraw *func_uvterra_rom_0040AC14(s32);
extern s32 D_uvterra_rom_0040D714;
#line 1 "uvterra-full-module-draft-context"
#include "uvimtx_rom.h"
#include "uvquery_rom.h"
#include "uvfmtx_rom.h"
#include "uvmodel_rom.h"
/* Private consumed offsets only. RE_UNKNOWN: canonical asset declarations and
 * complete storage owners. Existing shared declarations and bodies stay literal. */
typedef struct DraftTerrainObjectView DraftTerrainObjectView;
typedef struct DraftTerrainGroupView DraftTerrainGroupView;
typedef struct DraftTerrainCellView DraftTerrainCellView;
typedef struct DraftTerrainTileView DraftTerrainTileView;
typedef struct DraftTerrainExports DraftTerrainExports;
struct DraftTerrainObjectView {
    u16 modelId; s16 unk2; Mtx *unk4;
    f32 unk8, unkC, unk10, unk14; u16 unk18, unk1A; s32 unk1C;
    /* Current ASM: float+20/+24, pointer word+28, byte+2C. */
    f32 unk20, unk24; Mtx4F *unk28; u8 unk2C; u8 opaque2D[3];
    f32 unk30, unk34; s32 unk38; f32 unk3C; s32 unk40;
    DraftTerrainTileView *unk44; s32 unk48;
}; /* stride0x4C */
struct DraftTerrainGroupView {
    void *unk0; s32 texture; void *unk8; s16 unkC, unkE;
    u16 unk10, unk12; s32 unk14; Unk80225FBC_0x28_UnkC *unk18;
    u16 unk1C, unk1E; f32 unk20, unk24, unk28, unk2C, unk30, unk34; s32 unk38;
}; /* stride0x3C; STAT state starts at this same base */
struct DraftTerrainCellView {
    Vtx *vtxTable; u16 vtxCount, pad6; DraftTerrainGroupView *unk8;
    u16 unkC, padE; DraftTerrainObjectView *unk10; u16 unk14, pad16;
    f32 unk18, unk1C, unk20, unk24, unk28, unk2C, unk30;
}; /* stride0x34 */
struct DraftTerrainTileView {
    Mtx4F unk0; DraftTerrainCellView *unk40; u16 unk44; u8 opaque46[2];
    /* Original scalar-query float+48; accepted second matrix already at+4C. */
    f32 unk48; Mtx4F unk4C;
}; /* stride0x8C */
typedef struct {
    uvUnkTeraStruct unk0; u8 unk18, unk19; u8 opaque1A[2];
    f32 unk1C, unk20, unk24; DraftTerrainTileView *unk28;
    u16 unk2C, unk2E; s32 unk30;
} DraftTerrainView; /* stride0x34 */
typedef struct {
    DraftTerrainTileView *unk0; u8 unk4, opaque5; u16 unk6;
    f32 unk8; u8 unkC; u8 opaqueD[3];
} DraftTerrainDrawRecord; /* producer byte+0C, stride0x10 */
typedef struct { f32 unk0, unk4, unk8, unkC, unk10, unk14; } DraftTerrainProjectionBounds;
typedef struct {
    Vec3F unk0[6]; u8 unk48; u8 opaque49[3]; DraftTerrainProjectionBounds unk4C;
} DraftTerrainProjectionCache; /* pending UV8 consumed shape0x64 */
typedef struct { s32 unk0, unk4; } DraftTerrainSettings;
extern UvImtx_Rom_Exports *D_uvterra_rom_0040F74C;
extern s32 D_uvterra_rom_0040FBE0, D_uvterra_rom_0040FBE4;
extern s32 D_uvterra_rom_0040FC04, D_uvterra_rom_0040FC08[130];
extern UnkSobjDraw *D_8002D1A0;
extern Unk80225FBC_0x28 *D_8002D198;
extern s32 D_8002D19C;
/* RE_UNKNOWN: canonical FBA4 pointer type. Existing integer-typed storage stays;
 * initializer/readers explicitly use its original32-bit pointer-word ABI. */
#define UVTERRA_DRAFT_ROUND_HALF_AWAY(x) ((x) >= 0.0f ? (s32)((x) + 0.5f) : (s32)((x) - 0.5f))
#define UV_COMPUTE_LINE_MACRO(cond, arg2, arg0)                                                        \
    if ((cond)) {                                                                                      \
        *(arg2) = 0;                                                                                   \
    }                                                                                                  \
    *(arg0) = -1;

/* Canonical declarations; all raw legacy declarations remain unchanged. */
void __entrypoint_func_uvterra_rom_400000(DraftTerrainExports* exports);
s32 func_uvterra_rom_00407A80(s32 arg0, s32 arg1, s32 arg2);
void uvTerraAdjustProjectionEndpointsToBounds(ParsedUVTR* terrain, Vec3F* origin, Vec3F* first, Vec3F* second, Vec3F* third, Vec3F* fourth);
void uvTerraAllocateRecordBuffer(void);

s32 uvTerraAppendStaticObjectSegmentQueryResults(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ,
                              UnkSobjDraw *object);
void uvTerraCleanup(void);
void uvTerraClipLineToCellPerimeter(s16 *arg0, s16 *arg1, u16 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7, f32 arg8, f32 arg9, u8 arg10, f32 arg11, f32 arg12);
s32 uvTerraCollectHeightsMeetingNormalZThreshold(s32 terrainId, f32 worldX, f32 worldY, f32 *outHeights);
s32 uvTerraCollectSegmentContacts(s32 terraId, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              f32 arg7, s32 **arg8, f32 **arg9, Vec3F **arg10, s32 **arg11);
s32 uvTerraCollectSphereContacts(s32 terrainId, s32 queryFlags, f32 centerX, f32 centerY, f32 centerZ, f32 queryRadius, s32 **outHandles,
                              f32 **outFractions, Vec3F **outContactVectors, s32 **outFlags);
s32 uvTerraCollectStaticObjectHandlesByModel(s32 arg0, s32 modelId, s32 **arg2);
s32 uvTerraCollectStaticObjectScalarContacts(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 **arg5,
                              f32 **arg6, Vec3F **arg7);
s32 uvTerraCollectStaticObjectSegmentContacts(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              s32 **arg7, f32 **arg8, Vec3F **arg9);
u32 uvTerraCollectTriangleHandlesAtPoint(s32 terrainId, f32 worldX, f32 worldY, s32 **outTriangleHandles);
s32 uvTerraCollectTriangleHandlesByTexture(s32 terrainId, s32 texture, s32 **outTriangleHandles);
s32 uvTerraCollectTriangleScalarContacts(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32** arg5, f32** arg6, Vec3F** arg7);
s32 uvTerraCollectTriangleSegmentContacts(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              s32 **arg7, f32 **arg8);
u16 uvTerraComputeRectangleGridMask(f32 width, f32 height, uvUnkTileStruct *tile, f32 xScale, f32 yScale);
u16 uvTerraComputeScalarExtentGridMask(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
s32 uvTerraComputeTriangleSliceWeights(Vtx *arg0, Vtx *arg1, Vtx *arg2, f32 *arg3, f32 *arg4, f32 *arg5,
                              f32 arg6, f32 arg7);
void uvTerraCopyAdjustedStaticObjectMatrix(s32 contour, s32 arg1, Mtx4F *arg2);
void uvTerraDrawBillboardStaticObjectLods(s32 arg0, DraftTerrainObjectView *arg1);
void uvTerraDrawBillboardStaticObjectWithView(s32 arg0, DraftTerrainObjectView *sobj);
void uvTerraDrawProjectedTerrain(s32 arg0);
void uvTerraDrawQueuedTerrainTiles(s32 arg0);
void uvTerraDrawStaticObjectLods(UNUSED s32 arg0, DraftTerrainObjectView *sobj);
void uvTerraDrawStaticObjectWithView(s32 arg0, DraftTerrainObjectView *sobj);
void uvTerraDrawStaticObjects(s32 arg0, Mtx4F *arg1, u16 arg2, u16 arg3, DraftTerrainObjectView *arg4, u16 arg5);
void uvTerraDrawTerrainObjectGroups(s32 arg0, u16 arg1, Mtx4F *arg2, DraftTerrainGroupView *arg3, u16 arg4);
void uvTerraDrawTileGeometry(s32 channel, uvUnkTileStruct *tile, u16 firstMask, u16 secondMask);
s32 uvTerraFindStaticObjectContainingPoint(s32 terraId, f32 arg1, f32 arg2, f32 arg3);
s32 uvTerraGetChannelTerrain(s32 channel);
void uvTerraGetColor(s32 terraId, u32 surfaceId, f32 arg2, f32 arg3, u8 *r, u8 *g, u8 *b,
                               u8 *a);
void uvTerraGetHeightAndNormalAtPackedTriangle(s32 terrainId, u32 packedTriangle, f32 worldX, f32 worldY, f32* outHeight, Vec3F* outNormal);
u8 uvTerraGetIndexedDrawByte(s32 index);
void *uvTerraGetLoadedTerrain(s32 terrainId);
s32 uvTerraGetPackedTileTranslationXY(s32 terrainId, u32 handle, f32 *outX, f32 *outY);
void uvTerraGetPackedTriangleMeanVertexChannels(s32 terrainId, u32 handle,
    u8 *channel0, u8 *channel1, u8 *channel2);
void uvTerraGetPackedTriangleNormal(s32 terrainId, u32 handle, Vec3F* vector);
s32 uvTerraGetPackedTriangleTexture(s32 terrainId, u32 handle);
s32 uvTerraGetSharedWordBF0(void);
s32 uvTerraGetSharedWordBF4(void);
UnkSobjDraw *uvTerraGetStaticObject(s32 handle);
u16 uvTerraGetStaticObjectModelId(s32 handle);
void uvTerraGetStaticObjectProperties(s32 handle, ...);
s32 uvTerraGetStaticObjectValue(s32 handle);
s32 uvTerraGetTileTranslationXYAtWorldPosition(s32 terrainId, f32 worldX, f32 worldY,
                              f32 *outX, f32 *outY);
void uvTerraGetTriangleLocalVertices(s32 terrainId, u32 triangleHandle, Vec3F *vertex0, Vec3F *vertex1, Vec3F *vertex2);
s32 uvTerraGetTriangleTextureId(s32 terrainId, u32 triangleHandle);
void uvTerraInitializeSortGroups(void);
u16 uvTerraIntersectSegmentAndBoundsMasks(f32 firstX, f32 firstY, f32 secondX, f32 secondY, f32 xBoundA, f32 yBoundA, f32 xBoundB,
                              f32 yBoundB, f32 spanStartX, f32 spanEndX, f32 spanEndY, f32 spanStartY, void *center);
s32 uvTerraLocateTileAndSubcellMask(ParsedUVTR* arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6, u16* arg7, u16* arg8, u8 arg9);
u16 uvTerraLookupAdjustedWrappedIndexPair(s16 firstIndex, s16 secondIndex, u8 mode);
void uvTerraOrderProjectionPointPointers(Vec3F **points, u8 *count);
void uvTerraProjectEndpointToZPlane(Vec3F *origin, f32 planeZ, Vec3F *endpoint);
void uvTerraQueueDrawCallbackForTerrainCell(s32 arg0, s32 arg1, f32 arg2, f32 arg3, void (*arg4 )(s32, DraftTerrainObjectView* ),
                               s32 arg5, f32 arg6);
s32 uvTerraReadPackedFiveBitLevel(const u8 *packedLevels, s32 index);
void uvTerraRefreshProjectionAndDrawQueuedTiles(s32 channel);
void uvTerraRefreshProjectionPointCache(s32 channel);
void uvTerraRegisterChannelCallbacks(s32 channel);
void uvTerraSampleTextureColorAtSurface(s32 arg0, u32 arg1, f32 arg2, f32 arg3, u8 *r, u8 *g, u8 *b, u8 *a);
s32 uvTerraSelectLowestZCandidate(Vec3F *first, Vec3F *second, Vec3F *third, Vec3F *fourth);
void uvTerraSetChannelTerrain(s32 channel, s32 terrainId);
void uvTerraSetReciprocalByIndex(s32 index, f32 value);
void uvTerraSetSharedWordBF0(s32 value);
void uvTerraSetSharedWordBF4(s32 value);
void uvTerraSetStaticObjectFlags(s32 handle, ...);
void uvTerraSetStaticObjectModel(s32 handle, s32 modelId);
void uvTerraSetStaticObjectValue(s32 handle, s32 value);
void uvTerraStoreComposedStaticObjectMatrix(s32 contour, s32 arg1, Mtx4F *arg2);
s32 uvTerraTestPackedAngularLevelThreshold(const u8 *packedLevels, f32 sampleX, f32 sampleY, f32 levelInput);
s16 func_uvterra_rom_0040A43C(f32 arg0, f32 arg1, f32 arg2, UnkSobjDraw *sobj);
void *uvTerraUpdateProjectionRecordBounds(s32 recordIndex);

/* Original pointer-slot export view; RE_UNKNOWN: canonical full declaration. */
struct DraftTerrainExports {
    /* 0x00 */ void (*uvTerraCleanup)(void);
    /* 0x04 */ void (*uvTerraRegisterChannelCallbacks)(s32 channel);
    /* 0x08 */ void (*uvTerraSetChannelTerrain)(s32 channel, s32 terrainId);
    /* 0x0C */ s32 (*uvTerraGetChannelTerrain)(s32 channel);
    /* 0x10 */ void (*uvTerraDrawProjectedTerrain)(s32 arg0);
    /* 0x14 */ void (*uvTerraGetHeightAndNormalAtPackedTriangle)(s32 terrainId, u32 packedTriangle, f32 worldX, f32 worldY, f32* outHeight, Vec3F* outNormal);
    /* 0x18 */ void (*uvTerraGetPackedTriangleNormal)(s32 terrainId, u32 handle, Vec3F* vector);
    /* 0x1C */ s32 (*uvTerraGetPackedTriangleTexture)(s32 terrainId, u32 handle);
    /* 0x20 */ s32 (*uvTerraCollectTriangleScalarContacts)(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32** arg5, f32** arg6, Vec3F** arg7);
    /* 0x24 */ void * (*uvTerraGetLoadedTerrain)(s32 terrainId);
    /* 0x28 */ u32 (*uvTerraCollectTriangleHandlesAtPoint)(s32 terrainId, f32 worldX, f32 worldY, s32 **outTriangleHandles);
    /* 0x2C */ s32 (*uvTerraCollectTriangleSegmentContacts)(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              s32 **arg7, f32 **arg8);
    /* 0x30 */ void (*uvTerraGetPackedTriangleMeanVertexChannels)(s32 terrainId, u32 handle,
    u8 *channel0, u8 *channel1, u8 *channel2);
    /* 0x34 */ void (*uvTerraGetTriangleLocalVertices)(s32 terrainId, u32 triangleHandle, Vec3F *vertex0, Vec3F *vertex1, Vec3F *vertex2);
    /* 0x38 */ s32 (*uvTerraGetTileTranslationXYAtWorldPosition)(s32 terrainId, f32 worldX, f32 worldY,
                              f32 *outX, f32 *outY);
    /* 0x3C */ s32 (*uvTerraGetPackedTileTranslationXY)(s32 terrainId, u32 handle, f32 *outX, f32 *outY);
    /* 0x40 */ s32 (*uvTerraCollectSegmentContacts)(s32 terraId, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              f32 arg7, s32 **arg8, f32 **arg9, Vec3F **arg10, s32 **arg11);
    /* 0x44 */ s32 (*uvTerraCollectSphereContacts)(s32 terrainId, s32 queryFlags, f32 centerX, f32 centerY, f32 centerZ, f32 queryRadius, s32 **outHandles,
                              f32 **outFractions, Vec3F **outContactVectors, s32 **outFlags);
    /* 0x48 */ s32 (*uvTerraGetTriangleTextureId)(s32 terrainId, u32 triangleHandle);
    /* 0x4C */ s32 (*uvTerraCollectTriangleHandlesByTexture)(s32 terrainId, s32 texture, s32 **outTriangleHandles);
    /* 0x50 */ void (*uvTerraGetColor)(s32 terraId, u32 surfaceId, f32 arg2, f32 arg3, u8 *r, u8 *g, u8 *b,
                               u8 *a);
    /* 0x54 */ void (*uvTerraSampleTextureColorAtSurface)(s32 arg0, u32 arg1, f32 arg2, f32 arg3, u8 *r, u8 *g, u8 *b, u8 *a);
    /* 0x58 */ s32 (*uvTerraCollectHeightsMeetingNormalZThreshold)(s32 terrainId, f32 worldX, f32 worldY, f32 *outHeights);
    /* 0x5C */ void (*uvTerraSetSharedWordBF0)(s32 value);
    /* 0x60 */ s32 (*uvTerraGetSharedWordBF0)(void);
    /* 0x64 */ void (*uvTerraSetSharedWordBF4)(s32 value);
    /* 0x68 */ s32 (*uvTerraGetSharedWordBF4)(void);
    /* 0x6C */ s32 (*uvTerraCollectStaticObjectHandlesByModel)(s32 arg0, s32 modelId, s32 **arg2);
    /* 0x70 */ void (*uvTerraSetReciprocalByIndex)(s32 index, f32 value);
    /* 0x74 */ s32 (*func_uvterra_rom_00407A80)(s32 arg0, s32 arg1, s32 arg2);
    /* 0x78 */ void (*uvTerraStoreComposedStaticObjectMatrix)(s32 contour, s32 arg1, Mtx4F *arg2);
    /* 0x7C */ void (*uvTerraSetStaticObjectFlags)(s32 handle, ...);
    /* 0x80 */ void (*uvTerraCopyAdjustedStaticObjectMatrix)(s32 contour, s32 arg1, Mtx4F *arg2);
    /* 0x84 */ u16 (*uvTerraGetStaticObjectModelId)(s32 handle);
    /* 0x88 */ void (*uvTerraSetStaticObjectModel)(s32 handle, s32 modelId);
    /* 0x8C */ s32 (*uvTerraFindStaticObjectContainingPoint)(s32 terraId, f32 arg1, f32 arg2, f32 arg3);
    /* 0x90 */ s32 (*uvTerraCollectStaticObjectScalarContacts)(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 **arg5,
                              f32 **arg6, Vec3F **arg7);
    /* 0x94 */ s32 (*uvTerraCollectStaticObjectSegmentContacts)(s32 terraId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              s32 **arg7, f32 **arg8, Vec3F **arg9);
    /* 0x98 */ void (*uvTerraGetStaticObjectProperties)(s32 handle, ...);
    /* 0x9C */ void (*uvTerraSetStaticObjectValue)(s32 handle, s32 value);
    /* 0xA0 */ s32 (*uvTerraGetStaticObjectValue)(s32 handle);
    /* 0xA4 */ UnkSobjDraw * (*uvTerraGetStaticObject)(s32 handle);
    /* 0xA8 */ u8 (*uvTerraGetIndexedDrawByte)(s32 index);
    /* 0xAC */ void (*uvTerraQueueDrawCallbackForTerrainCell)(s32 arg0, s32 arg1, f32 arg2, f32 arg3, void (*arg4 )(s32, DraftTerrainObjectView* ),
                               s32 arg5, f32 arg6);
    /* 0xB0 */ s32 *D_uvterra_rom_0040FBD8;
    /* 0xB4 */ s32 *D_uvterra_rom_0040FBDC;
    /* 0xB8 */ s32 *D_uvterra_rom_0040FBE0;
};

#line 55 "src/modules/uvterra_rom.c"
#line 55 "src/modules/uvterra_rom.c"
#line 1 "uvterra-full-module-existing-storage-declarations"
/* Existing globals are declared again before the original initializer.
 * Types are literal to the later declarations; src/profiler.c supplies the
 * exact create prototype. No storage, initialization or body is added here. */
extern s32 D_uvterra_rom_0040FBF8, D_uvterra_rom_0040FBFC, D_uvterra_rom_0040FC00;
extern f32 *D_uvterra_rom_0040F780;
extern s32 *D_uvterra_rom_0040F784;
extern Vec3F *D_uvterra_rom_0040F788;
extern s32 *D_uvterra_rom_0040F790, *D_uvterra_rom_0040F794, *D_uvterra_rom_0040F798;
s32 uvProfilerCreate(char* label);
#line 1 "uvterra-full-module-draft-0000"
/* Initialize export slots, imports, original tables and shared query arrays. RE_UNKNOWN: property limits, allocation-failure behavior and global storage owners; preserve initialization order. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/__entrypoint_func_uvterra_rom_400000.s")
#line 54 "uvterra-full-module-draft-0000"
#line 56 "src/modules/uvterra_rom.c"

#line 58 "src/modules/uvterra_rom.c"
/* Unload the eleven terrain-module dependencies in original order. */
void uvTerraCleanup(void) {
    uvUnloadModule('IMTX');
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('MATH');
    uvUnloadModule('MODL');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
    uvUnloadModule('ISCT');
    uvUnloadModule('SORT');
}
#line 71 "src/modules/uvterra_rom.c"

#line 72 "src/modules/uvterra_rom.c"
/* Obtain the supplied channel's callback list through property six.
 * Register the three terrain callbacks in original priority order 40, 45,
 * 100. The incoming channel is a real argument, not an unused register. */
void uvTerraRegisterChannelCallbacks(s32 channel) {
    CallbackList *callbacks;
    ((TerrainChannelListExports *)D_uvterra_rom_0040F760)->get(channel, 6, &callbacks, 0);
    D_uvterra_rom_0040F764->uvAddCallback(callbacks, func_uvterra_rom_0040078C, NULL, 0x28);
    D_uvterra_rom_0040F764->uvAddCallback(callbacks, func_uvterra_rom_0040AC9C, NULL, 0x2D);
    D_uvterra_rom_0040F764->uvAddCallback(callbacks, uvTerraRefreshProjectionAndDrawQueuedTiles, NULL, 0x64);
}
#line 73 "src/modules/uvterra_rom.c"

#line 74 "src/modules/uvterra_rom.c"
/* Store a loaded terrain ID for the selected channel, or 65535 for either
 * invalid sentinel or a missing terrain. The original table index is unchecked.
 * RE_UNKNOWN: caller channel bounds and initialized-table lifetime. The native
 * initializer allocates the table from channel property 13; trace that count
 * and all exported callers before claiming an enforced bounds/lifetime contract. */
#line 76 "src/modules/uvterra_rom.c"
void uvTerraSetChannelTerrain(s32 channel, s32 terrainId) {
    if ((terrainId == 0xFFFF) || (terrainId == -1)) {
        D_uvterra_rom_0040F77C[channel] = 0xFFFF;
    } else if (uvGetLoadedFile('UVTR', terrainId) == NULL) {
        D_uvterra_rom_0040F77C[channel] = 0xFFFF;
    } else {
        D_uvterra_rom_0040F77C[channel] = terrainId;
    }
}
#line 83 "src/modules/uvterra_rom.c"

#line 84 "src/modules/uvterra_rom.c"
/* Return the terrain ID through the original unchecked channel-table index.
 * RE_UNKNOWN: valid channel range and initialized-table lifetime. Trace the
 * native property-13 allocation and exported callers before adding guards. */
#line 85 "src/modules/uvterra_rom.c"
s32 uvTerraGetChannelTerrain(s32 channel) {
    return D_uvterra_rom_0040F77C[channel];
}
#line 87 "src/modules/uvterra_rom.c"

// _uvTerraDraw
#ifdef NEEDS_RODATA
void func_uvterra_rom_0040078C(s32 arg0) {
    s32 var_v0;
    s32 sp1A8;
    s32 sp1A4;
    s32 var_v1;
    s32 sp19C;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 var_t5;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 x;
    f32 y;
    f32 z;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fa0;
    f32 temp_fv1;
    f32 temp_fv0;
    Vec3F sp158;
    Vec3F sp14C;
    f32 temp_fs2_2;
    f32 temp_fs3_2;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_fa1;
    f32 var_ft4;
    f32 var_fv0;
    u16 temp_s0;
    u16 temp_v0_6;
    u16 var_s6;
    u16 temp_v0;
    s32 temp_t0;
    f32 sp110[5];
    f32 spFC[5];
    f32 spE8[5];
    u8 spE0[5];
    u16 spDE;
    ParsedUVTR_inner *temp_fp;
    UnkStruct_uvterra_rom_0040FBE8 *temp_s0_2;
    UnkStruct_uvterra_rom_0040078C *temp_v0_2;
    s16 spCE;
    s16 spCC;
    ParsedUVTR *spC8;
    s32 i;
    f32 temp_ft0;
    UnkStruct_uvterra_rom_0040F774 *spBC;

    spBC = &D_uvterra_rom_0040F774[arg0];
    D_uvterra_rom_0040F740 = 0;
    if (D_uvterra_rom_0040F77C[arg0] == 0xFFFF) {
        return;
    }

    spC8 = uvGetLoadedFile('UVTR', D_uvterra_rom_0040F77C[arg0]);
    if (spC8 == NULL) {
        return;
    }

    func_uvterra_rom_0040C218(arg0);
    temp_v0_2 = func_uvterra_rom_0040C0F8(arg0);
    temp_fs2 = spC8->unk1C;
    temp_fs3 = spC8->unk20;
    var_t2 = (s32) ((temp_v0_2->unk0 - spC8->unk0.unk0) / temp_fs2);
    var_t3 = (s32) ((temp_v0_2->unkC - spC8->unk0.unk0) / temp_fs2);
    var_t4 = (s32) ((temp_v0_2->unk4 - spC8->unk0.unk4) / temp_fs3);
    var_t5 = (s32) ((temp_v0_2->unk10 - spC8->unk0.unk4) / temp_fs3);

    if (var_t2 < 0) {
        var_t2 = 0;
    }

    if ((spC8->unk18 - 1) < var_t3) {
        var_t3 = spC8->unk18 - 1;
    }
    if (var_t4 < 0) {
        var_t4 = 0;
    }

    if ((spC8->unk19 - 1) < var_t5) {
        var_t5 = spC8->unk19 - 1;
    }

    for (i = 0; i < spBC->unk48; i++) {
        temp_fv1 = spBC->unk0[i].x;
        temp_fa1 = spBC->unk0[i].y;
        if (i < (spBC->unk48 - 1)) {
            var_fv0 = spBC->unk0[i + 1].x;
            var_ft4 = spBC->unk0[i + 1].y;
        } else {
            var_fv0 = spBC->unk0[0].x;
            var_ft4 = spBC->unk0[0].y;
        }

        temp_fa0 = var_fv0 - temp_fv1;
        temp_ft0 = var_ft4 - temp_fa1;

        if (temp_fa0 == 0.0f) {
            sp110[i] = 2140143600.0f;
            spE8[i] = 0.0f;
            spFC[i] = temp_fv1;
            if (temp_ft0 > 0.0f) {
                spE0[i] = 1;
            } else {
                spE0[i] = 0;
            }
        } else {
            temp_fv0 = (var_ft4 - temp_fa1) / temp_fa0;
            if (temp_fa0 > 0.0f) {
                spE0[i] = 1;
            } else {
                spE0[i] = 0;
            }
            sp110[i] = temp_fv0;
            spE8[i] = 1.0f / temp_fv0;
            spFC[i] = temp_fa1 - (temp_fv0 * temp_fv1);
        }
    }

    D_uvterra_rom_0040F760->unk4(arg0, 7, &sp158, 0);
    D_uvterra_rom_0040F760->unk4(arg0, 8, &sp14C, 0);

    for (sp1A8 = var_t2; sp1A8 <= var_t3; sp1A8++) {
        for (sp1A4 = var_t4; sp1A4 <= var_t5; sp1A4++) {
            if ((D_uvterra_rom_0040FBEC != 0) && (sp14C.x > 0.0f) ^ (D_uvterra_rom_0040FBEC == 2)) {
                var_v1 = (var_t3 - sp1A8) + var_t2;
            } else {
                var_v1 = sp1A8;
            }
            if ((D_uvterra_rom_0040FBEC != 0) && (sp14C.y > 0.0f) ^ (D_uvterra_rom_0040FBEC == 2)) {
                var_v0 = (var_t5 - sp1A4) + var_t4;
            } else {
                var_v0 = sp1A4;
            }
            sp19C = (spC8->unk18 * var_v0) + var_v1;
            temp_fp = spC8->unk28 + sp19C;
            if (temp_fp == NULL) {
                continue;
            }

            if (temp_fp->unk40 == NULL) {
                continue;
            }

            x = (temp_fp->unk30 + temp_fp->unk40->unk18);
            y = (temp_fp->unk34 + temp_fp->unk40->unk1C);
            z = (temp_fp->unk38 + temp_fp->unk40->unk20);
            if (!D_uvterra_rom_0040F760->unk2C(arg0, x - sp158.x, y - sp158.y, z - sp158.z, temp_fp->unk40->unk24)) {
                continue;
            }

            temp_fs0 = 15.0f / temp_fs2;
            temp_fs1 = 15.0f / temp_fs3;
            temp_fs2_2 = temp_fp->unk30 - (0.5f * temp_fs2);
            temp_fs3_2 = temp_fp->unk30 + (0.5f * temp_fs2);
            temp_fs4 = temp_fp->unk34 + (0.5f * temp_fs3);
            temp_fs5 = temp_fp->unk34 - (0.5f * temp_fs3);

            var_s6 = 0;
            spDE = 0xFFFF;
            for (i = 0; i < spBC->unk48; i++) {
                func_uvterra_rom_0040B26C(&spCE, &spCC, &spDE, temp_fs2_2, temp_fs3_2, temp_fs4,
                                          temp_fs5, spFC[i], sp110[i], spE8[i], (s32) spE0[i],
                                          temp_fs0, temp_fs1);
                if (spCE >= 0) {
                    temp_s0 = uvTerraLookupAdjustedWrappedIndexPair(spCE, spCC, 0);
                    temp_v0_6 = uvTerraLookupAdjustedWrappedIndexPair(spCE, spCC, 1);
                    var_s6 |= temp_s0 & temp_v0_6;
                    if (spE0[i] != 0) {
                        spDE &= temp_v0_6;
                    } else {
                        spDE &= temp_s0;
                    }
                }

                if (spDE == 0) {
                    break;
                }
            }

            temp_v0 = spDE & ~var_s6;
            if (spDE) {
                temp_s0_2 = &D_uvterra_rom_0040FBE8[D_uvterra_rom_0040F740];
                temp_s0_2->unk0 = temp_fp;
                temp_s0_2->unk6 = spDE;
                temp_s0_2->unk4 = temp_v0;
                temp_s0_2->unkC = sp19C;

                temp_s0_2->unk8 =
                    D_uvterra_rom_0040F75C->uvSqrtf(SQ(sp158.z - temp_fp->unk38) + (SQ(sp158.x - temp_fp->unk30) + SQ(sp158.y - temp_fp->unk34)));
                D_uvterra_rom_0040F740++;
            }
        }
    }
}
#else
#line 1 "uvterra-full-module-draft-078C"
/* Project the cached terrain polygon into grid cells and append draw records. RE_ORIGINAL_QUIRK: sentinel slopes, ordered boundaries and unchecked append paths. RE_UNKNOWN: cache capacity and finite-input contract. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040078C.s")
#line 182 "uvterra-full-module-draft-078C"
#line 288 "src/modules/uvterra_rom.c"
#endif

// uvTerraGetPlane
#line 291 "src/modules/uvterra_rom.c"
/* Resolve the packed tile, group and triangle indices and derive the
 * surface normal and height at the supplied world X/Y position. Retain
 * the upward-normal fallback and leave height untouched for zero normal Z. */
void uvTerraGetHeightAndNormalAtPackedTriangle(s32 terrainId, u32 packedTriangle, f32 worldX, f32 worldY, f32* outHeight, Vec3F* outNormal) {
    f32 vertexX;
    uvUnkTileStruct* tile;
    ParsedUVTR* terrain;
    Unk80225FBC_0x28_UnkC* triangle;
    Vtx* vertices;
    f32 localX;
    f32 localY;
    f32 localZ;
    s16 tileX;
    s16 tileY;
    Unk80225FBC_0x28* group;
    f32 vertexY;
    f32 vertexZ;
    f32 horizontalToVerticalScale;

    if (packedTriangle == -1) {
        return;
    }

    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return;
    }

    tile = &terrain->unk28[(packedTriangle >> 0x16) & 0x3FF];
    group = &tile->unk40->unk8[(packedTriangle >> 0xC) & 0x3FF];
    triangle = &group->unk18[packedTriangle & 0xFFF];
    vertices = tile->unk40->vtxTable;

    func_uvterra_rom_0040B8C0(terrain, worldX, worldY, 0.0f, &localX, &localY, &localZ, &tileX, &tileY, 0U);
    localX *= tile->unk40->unk2C;
    localY *= tile->unk40->unk2C;
    localZ *= tile->unk40->unk30;
    horizontalToVerticalScale = (tile->unk40->unk2C / tile->unk40->unk30);
    if (D_uvterra_rom_0040F768->uvIntersectGetScaledTriangleNormal(vertices, triangle->unk0, triangle->unk2, triangle->unk4, outNormal, horizontalToVerticalScale) == 0) {
        outNormal->x = 0.0f;
        outNormal->y = 0.0f;
        outNormal->z = 1.0f;
    }

    vertexX = vertices[triangle->unk0].v.ob[0];
    vertexY = vertices[triangle->unk0].v.ob[1];
    vertexZ = vertices[triangle->unk0].v.ob[2];
    if (outNormal->z != 0.0f) {
        *outHeight = (((outNormal->x * (vertexX - localX)) + (outNormal->y * (vertexY - localY))) /
             ( outNormal->z * horizontalToVerticalScale)) + vertexZ;
        *outHeight /= tile->unk40->unk30;
        *outHeight += tile->unk0.m[3][2];
    }
}
#line 342 "src/modules/uvterra_rom.c"


#line 344 "src/modules/uvterra_rom.c"
/* Decode the packed tile/group/triangle indices and obtain the normalized
 * triangle normal from ISCT export 0x18, scaling vertex Z by cell->unk2C/unk30.
 * A failed normalization writes zero; the all-ones handle sentinel or absent
 * terrain leaves output unchanged. Other packed indices are used unchecked.
 * RE_UNKNOWN: caller index validation and the normal's intended coordinate
 * space after terrain scaling. Trace actual callers and cell-scale producers
 * before assigning validation responsibility or calling the normal world-space. */
#line 351 "src/modules/uvterra_rom.c"
#line 348 "src/modules/uvterra_rom.c"
void uvTerraGetPackedTriangleNormal(s32 terrainId, u32 handle, Vec3F* vector) {
    ParsedUVCT* cell;
    ParsedUVTR* terrain;
    Unk80225FBC_0x28 *group;
    uvUnkTileStruct* tile;
    Unk80225FBC_0x28_UnkC* triangle;

    if (handle == -1U) {
        return;
    }

    terrain = uvGetLoadedFile(0x55565452, terrainId);
    if (terrain == NULL) {
        return;
    }

    tile = &terrain->unk28[(handle >> 0x16) & 0x3FF];
    cell = tile->unk40;
    group =  &cell->unk8[(handle >> 0xC) & 0x3FF];
    triangle = &group->unk18[handle & 0xFFF];

    if (D_uvterra_rom_0040F768->uvIntersectGetScaledTriangleNormal(cell->vtxTable, triangle->unk0, triangle->unk2, triangle->unk4, vector, cell->unk2C / cell->unk30) == 0) {
        vector->x = 0.0f;
        vector->y = 0.0f;
        vector->z = 0.0f;
    }
}
#line 371 "src/modules/uvterra_rom.c"

#line 372 "src/modules/uvterra_rom.c"
/* Return the selected group texture word, or 4095 for the all-ones handle
 * sentinel, absent terrain, tile index beyond the stored grid product,
 * null derived tile pointer or absent cell. The original does not check
 * the group index or group-table pointer before reading the texture word.
 * RE_UNKNOWN: how callers validate packed group indices. Trace original
 * TERR export0x1C callers and handle producers before assigning that responsibility. */
#line 375 "src/modules/uvterra_rom.c"
s32 uvTerraGetPackedTriangleTexture(s32 terrainId, u32 handle) {
    ParsedUVCT* cell;
    ParsedUVTR* terrain;
    s32 tileIndex;
    uvUnkTileStruct* tile;
    Unk80225FBC_0x28 *group;

    if (handle == -1U) {
        return 0xFFF;
    }
    terrain = uvGetLoadedFile(0x55565452, terrainId);
    if (terrain == NULL) {
        return 0xFFF;
    }
    tileIndex = (handle >> 0x16) & 0x3FF;
    if (tileIndex >= (terrain->unk18 * terrain->unk19)) {
        return 0xFFF;
    }
    tile = &terrain->unk28[tileIndex];
    if (tile == NULL) {
        return 0xFFF;
    }
    cell = tile->unk40;
    if (cell == NULL) {
        return 0xFFF;
    }
    group = &cell->unk8[(handle >> 0xC) & 0x3FF];
    return group->texture;
}
#line 401 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-1284"
/* Collect triangle scalar-extent contacts into shared query arrays. RE_ORIGINAL_QUIRK: conditional record advancement, live capacity calls and original coordinate increments. RE_UNKNOWN: radius domain and output ownership. */
s32 uvTerraCollectTriangleScalarContacts(s32 terrainId, f32 centerX, f32 centerY, f32 centerZ, f32 radius, s32** packedHandlesOut, f32** scalarsOut, Vec3F** vectorsOut) {
    s32 tileX;
    s32 tileY;
    s32 groupIndex;
    s32 triangleIndex;
    f32 inverseXYScale;
    s32 minTileX;
    s32 maxTileX;
    s32 minTileY;
    s32 maxTileY;
    s32 tileIndex;
    f32 inverseZScale;
    s32 queryRecordFlag;
    f32 scaledRadiusXY;
    DraftTerrainView* terrain;
    f32 scaledCenterX;
    DraftTerrainCellView* cell;
    DraftTerrainGroupView* group;
    s32 vertexBound;
    s32 contactClass;
    DraftTerrainTileView* tile;
    Unk80225FBC_0x28_UnkC* triangle;
    query_78* queryRecords;
    f32 gridLowerX;
    f32 gridUpperX;
    f32 gridUpperY;
    f32 gridLowerY;
    s32 resultCount;
    f32 tileLocalX;
    f32 tileLocalY;
    f32 tileLocalZ;
    f32 scaledCenterY;
    f32 scaledRadiusZ;
    Vtx* vertex0;
    Vtx* vertex1;
    f32 scaledCenterZ;
    f32 axisScaleRatio;
    Vtx* vertex2;
    f32 queryLowerZ;
    u16 queryGridMask;

    queryRecordFlag = 0;
    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return 0;
    }
    if ((centerX + radius) < terrain->unk0.unk0) {
        return 0;
    }
    if (terrain->unk0.unkC < (centerX - radius)) {
        return 0;
    }
    if ((centerY + radius) < terrain->unk0.unk4) {
        return 0;
    }
    if (terrain->unk0.unk10 < (centerY - radius)) {
        return 0;
    }
    minTileX = ((centerX - radius) - terrain->unk0.unk0) / terrain->unk1C;
    maxTileX = ((centerX + radius) - terrain->unk0.unk0) / terrain->unk1C;
    minTileY = ((centerY - radius) - terrain->unk0.unk4) / terrain->unk20;
    maxTileY = ((centerY + radius) - terrain->unk0.unk4) / terrain->unk20;
    if (minTileX < 0) {
        minTileX = 0;
    }
    if ((terrain->unk18 - 1) < maxTileX) {
        maxTileX = terrain->unk18 - 1;
    }

    if (minTileY < 0) {
        minTileY = 0;
    }

    if ((terrain->unk19 - 1) < maxTileY) {
        maxTileY = terrain->unk19 - 1;
    }

    resultCount = 0;
    gridLowerX = terrain->unk0.unk0;
    gridUpperX = terrain->unk1C + gridLowerX;
    for (tileX = minTileX; maxTileX >= tileX; tileX++) {
        gridLowerY = terrain->unk0.unk4;
        gridUpperY = terrain->unk20 + gridLowerY;
        for (tileY = minTileY; maxTileY >= tileY; tileY++) {
            tileIndex = (terrain->unk18 * tileY) + tileX;
            tile = &terrain->unk28[tileIndex];
            if (tile == NULL) {
                continue;
            }
            cell = tile->unk40;
            if (cell == NULL) {
                continue;
            }
            queryLowerZ = centerZ - radius;
            if ((tile->unk48 < queryLowerZ)) {
                continue;
            }
            scaledRadiusXY = cell->unk2C * radius;
            scaledRadiusZ = cell->unk30 * radius;
            tileLocalX = centerX - tile->unk0.m[3][0];
            tileLocalY = centerY - tile->unk0.m[3][1];
            tileLocalZ = centerZ - tile->unk0.m[3][2];
            queryGridMask = uvTerraComputeScalarExtentGridMask(tileLocalX, tileLocalY, radius, gridLowerX, gridUpperX, gridLowerY, gridUpperY);
            scaledCenterX = cell->unk2C * tileLocalX;
            scaledCenterY = cell->unk2C * tileLocalY;
            scaledCenterZ = cell->unk30 * tileLocalZ;
            axisScaleRatio = cell->unk2C / cell->unk30;
            for (groupIndex = 0; groupIndex < cell->unkC; groupIndex++) {
                group = cell->unk8 + groupIndex;
                if (!(group->unk1E & queryGridMask) || ((tile->unk0.m[3][2] + group->unk34) < queryLowerZ) || !((SQ(group->unk30 + radius) >= SQ(tileLocalX - group->unk24) + SQ(tileLocalY - group->unk28) + SQ(tileLocalZ - group->unk2C)))) {
                    continue;
                }

                for (triangleIndex = 0; triangleIndex < group->unk1C; triangleIndex++) {
                    triangle = &group->unk18[triangleIndex];
                    if (triangle->unk6 & queryGridMask) {
                        vertex0 = &cell->vtxTable[triangle->unk0];
                        vertex1 = &cell->vtxTable[triangle->unk2];
                        vertex2 = &cell->vtxTable[triangle->unk4];

                        vertexBound = MIN(MIN(vertex0->v.ob[0], vertex1->v.ob[0]), vertex2->v.ob[0]);
                        if (scaledRadiusXY < (vertexBound - scaledCenterX)) {
                            continue;
                        }

                        vertexBound = MAX(MAX(vertex0->v.ob[0], vertex1->v.ob[0]), vertex2->v.ob[0]);
                        if (scaledRadiusXY < (scaledCenterX - vertexBound)) {
                            continue;
                        }

                        vertexBound = MIN(MIN(vertex0->v.ob[1], vertex1->v.ob[1]), vertex2->v.ob[1]);
                        if (scaledRadiusXY < (vertexBound - scaledCenterY)) {
                            continue;
                        }

                        vertexBound = MAX(MAX(vertex0->v.ob[1], vertex1->v.ob[1]), vertex2->v.ob[1]);
                        if (scaledRadiusXY < (scaledCenterY - vertexBound)) {
                            continue;
                        }

                        vertexBound = MIN(MIN(vertex0->v.ob[2], vertex1->v.ob[2]), vertex2->v.ob[2]);
                        if (scaledRadiusZ < (vertexBound - scaledCenterZ)) {
                            continue;
                        }

                        vertexBound = MAX(MAX(vertex0->v.ob[2], vertex1->v.ob[2]), vertex2->v.ob[2]);
                        if (scaledRadiusZ < (scaledCenterZ - vertexBound)) {
                            continue;
                        }

                        if (resultCount >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                            break;
                        }

                        contactClass = D_uvterra_rom_0040F768->uvIntersectClassifySphereTriangleContact(
                            scaledCenterX, scaledCenterY, scaledCenterZ, scaledRadiusXY, axisScaleRatio,
                            vertex0->v.ob[0], vertex0->v.ob[1], vertex0->v.ob[2],
                            vertex1->v.ob[0], vertex1->v.ob[1], vertex1->v.ob[2],
                            vertex2->v.ob[0], vertex2->v.ob[1], vertex2->v.ob[2],
                            &D_uvterra_rom_0040F788[resultCount], &D_uvterra_rom_0040F780[resultCount]
                        );
                        if (contactClass == 0) {
                        } else {
                            if (contactClass == 1) {
                                D_uvterra_rom_0040F794[resultCount] |= 1;
                            } else {
                                D_uvterra_rom_0040F794[resultCount] &= ~1;
                            }
                            if (queryRecordFlag == 0) {
                                D_uvterra_rom_0040F76C->uvQueryGetProps(0, 1, &queryRecordFlag, 0);
                            }
                            if (queryRecordFlag != 0) {
                                inverseXYScale = 1.0f / cell->unk2C;
                                inverseZScale = 1.0f / cell->unk30;
                                queryRecords = D_uvterra_rom_0040F76C->uvQueryGetActiveRecordArray();
                                queryRecords[resultCount].unk0.x = (inverseXYScale * vertex0->v.ob[0]) + tile->unk0.m[3][0];
                                queryRecords[resultCount].unk0.y = (inverseXYScale * vertex0->v.ob[1]) + tile->unk0.m[3][1];
                                queryRecords[resultCount].unk0.z = (inverseZScale * vertex0->v.ob[2]) + tile->unk0.m[3][2];
                                queryRecords[resultCount].unkC.x = (inverseXYScale * vertex1->v.ob[0]) + tile->unk0.m[3][0];
                                queryRecords[resultCount].unkC.y = (inverseXYScale * vertex1->v.ob[1]) + tile->unk0.m[3][1];
                                queryRecords[resultCount].unkC.z = (inverseZScale * vertex1->v.ob[2]) + tile->unk0.m[3][2];
                                queryRecords[resultCount].unk18.x = (inverseXYScale * vertex2->v.ob[0]) + tile->unk0.m[3][0];
                                queryRecords[resultCount].unk18.y = (inverseXYScale * vertex2->v.ob[1]) + tile->unk0.m[3][1];
                                queryRecords[resultCount].unk18.z = (inverseZScale * vertex2->v.ob[2]) + tile->unk0.m[3][2];
                                queryRecords[resultCount].unk24 = D_uvterra_rom_0040F788[resultCount];
                                queryRecords[resultCount].unk70 |= 1;
                                queryRecords[resultCount].unk74 = group->texture;
                            }
                            D_uvterra_rom_0040F780[resultCount] /= -radius * cell->unk2C;

                            // 10 bits of tileIndex, 10 bits of groupIndex and 12 bits of triangleIndex = 32 bits total
                            D_uvterra_rom_0040F784[resultCount] = ((tileIndex & 0x3FF) << 0x16) + ((groupIndex & 0x3FF) << 0xC) + (triangleIndex & 0xFFF);
                            resultCount++;
                        }
                    }
                }
            }

            if (maxTileY >= tileY) {
                gridLowerY += terrain->unk20;
                gridUpperY += terrain->unk20;
            }
        }

        if (maxTileX >= tileX) {
            gridLowerX += terrain->unk1C;
            gridUpperX += terrain->unk20;
        }
    }
    *packedHandlesOut = D_uvterra_rom_0040F784;
    *scalarsOut = D_uvterra_rom_0040F780;
    *vectorsOut = D_uvterra_rom_0040F788;
    return resultCount;
}
#line 403 "src/modules/uvterra_rom.c"

#line 404 "src/modules/uvterra_rom.c"
/* Return an already loaded terrain pointer, or null for an absent terrain. */
void *uvTerraGetLoadedTerrain(s32 terrainId) {
    void *terrain;

    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return NULL;
    }
    return terrain;
}
#line 413 "src/modules/uvterra_rom.c"

/* Native 992-byte triangle-list query: locate the tile, scale local coordinates,
 * filter live group/triangle masks and signed vertex bounds, and call the
 * positive-winding triangle test before storing packed handles in QERY storage.
 * RE_ORIGINAL_QUIRK: store a handle before checking capacity with an unsigned
 * count comparison; reaching capacity stops only the current group's loop.
 * Later groups remain eligible. This does not prove a reachable overflow.
 * RE_UNKNOWN: coordinate frame/units, valid nonzero truncated cell divisors,
 * loaded terrain and asset/index guarantees, mask meanings, and shared-buffer
 * capacity, lifetime and maximum hits across groups. Trace UVTR/UVCT producers,
 * QERY allocation/overrides and actual TERR export 0x28 callers before changing
 * limits or assigning ownership.
 *
 */
#line 414 "src/modules/uvterra_rom.c"
extern s32 *D_uvterra_rom_0040F784;
/* Collect packed triangle handles whose masked triangles contain the query point.
 * RE_ORIGINAL_QUIRK: append before checking capacity; reaching the limit breaks
 * only the current group loop. Later groups can still be visited.
 * RE_UNKNOWN: valid terrain/indices, mask meaning and buffer capacity/lifetime.
 * Strict bounds and unordered comparisons retain the original query behavior. */
#line 414 "src/modules/uvterra_rom.c"
u32 uvTerraCollectTriangleHandlesAtPoint(s32 terrainId, f32 worldX, f32 worldY, s32 **outTriangleHandles) {
    f32 localX;
    f32 localY;
    f32 localZ;
    ParsedUVCT *geometry;
    ParsedUVTR *terrain;
    Unk80225FBC_0x28 *group;
    Unk80225FBC_0x28_UnkC *triangle;
    Vtx *firstVertex;
    u16 cellMask;
    Vtx *secondVertex;
    u16 tileIndex;
    Vtx *thirdVertex;
    f32 secondX;
    f32 thirdX;
    f32 thirdY;
    f32 firstX;
    f32 firstY;
    f32 secondY;
    uvUnkTileStruct* tile;
    u16 triangleIndex;
    u16 groupIndex;
    u32 hitCount;

    hitCount = 0;
    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (func_uvterra_rom_0040B8C0(terrain, worldX, worldY, 0.0f, &localX, &localY, &localZ, (s16 *) &tileIndex, (s16 *) &cellMask,
                                  0)
        == 0) {
        *outTriangleHandles = NULL;
        return 0U;
    }
    tile = &terrain->unk28[tileIndex];
    geometry = tile->unk40;
    if (geometry == NULL) {
        *outTriangleHandles = NULL;
        return 0U;
    }
    localX *= geometry->unk2C;
    localY *= geometry->unk2C;
    localZ *= geometry->unk30;
    for (groupIndex = 0; groupIndex < geometry->unkC; groupIndex++) {
        group = &geometry->unk8[groupIndex];
        if (!(group->unk1E & cellMask)) {
            continue;
        }

        for (triangleIndex = 0; triangleIndex < group->unk1C; triangleIndex++) {
            triangle = &group->unk18[triangleIndex];
            if (!(triangle->unk6 & cellMask)) {
                continue;
            }
            firstVertex = (Vtx*)geometry->vtxTable + triangle->unk0;
            firstX = firstVertex->v.ob[0];
            secondVertex = (Vtx*)geometry->vtxTable + triangle->unk2;
            secondX = secondVertex->v.ob[0];
            thirdVertex = (Vtx*)geometry->vtxTable + triangle->unk4;
            thirdX = thirdVertex->v.ob[0];

            if (((firstX < localX)) && (secondX < localX) && (thirdX < localX)) {
                continue;
            }

            if (((localX < firstX) && (localX < secondX) && (localX < thirdX))) {
                continue;
            }

            firstY = firstVertex->v.ob[1];
            secondY = secondVertex->v.ob[1];
            thirdY = thirdVertex->v.ob[1];

            if (((firstY < localY)) && (secondY < localY) && (thirdY < localY)) {
                continue;
            }

            if (((localY < firstY) && (localY < secondY) && (localY < thirdY))) {
                continue;
            }

            if (D_uvterra_rom_0040F768->uvIntersectPointInPositiveWindingTriangle2D(
                    localX, localY, firstX, firstY, secondX, secondY, thirdX, thirdY, 1.0f)
                == 0) {
                continue;
            }
            D_uvterra_rom_0040F784[hitCount++] = (tileIndex << 12 << 10) + ((groupIndex & 0x3FF) << 0xC) + (triangleIndex & 0xFFF);
            if (hitCount >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                break;
            }
        }
    }
    *outTriangleHandles = D_uvterra_rom_0040F784;
    return hitCount;
}
#line 415 "src/modules/uvterra_rom.c"
#line 415 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-2244"
/* Clip a segment to terrain cells and collect triangle fractions. RE_ORIGINAL_QUIRK: partial early outputs, byte counter and uninitialized/stale traversal-slot paths. RE_UNKNOWN: valid caller paths and buffer limits; do not invent an initializer. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00402244.s")
#line 322 "uvterra-full-module-draft-2244"
#line 417 "src/modules/uvterra_rom.c"

#line 418 "src/modules/uvterra_rom.c"

/* Average the three unsigned vertex bytes at offsets 0x0C/0x0D/0x0E.
 * Packed handle bits select tile/group/triangle as in the vertex-copy helper.
 * Keep each channel's index reads before its store, including aliased outputs;
 * reload all three indices for each of the three separate channel assignments.
 * Sentinel, missing terrain, null tile address or null geometry leaves outputs
 * unchanged. The original does not check group/triangle/vertex bounds.
 * RE_UNKNOWN: whether these bytes represent colors or another vertex encoding,
 * valid index ranges and output alias policy. Trace UVCT producers and original
 * TERR slot0x30 callers before assigning RGB/normal semantics or adding checks. */
void uvTerraGetPackedTriangleMeanVertexChannels(s32 terrainId, u32 handle,
    u8 *channel0, u8 *channel1, u8 *channel2) {
    ParsedUVTR *terrain;
    uvUnkTileStruct *tile;
    ParsedUVCT *geometry;
    Unk80225FBC_0x28 *group;
    Unk80225FBC_0x28_UnkC *triangle;
    Vtx *vertices;
    s32 vertexCount;

    if (handle == 0xFFFFFFFF) {
        return;
    }
    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return;
    }
    tile = &terrain->unk28[(handle >> 22) & 0x3FF];
    if (tile == NULL) {
        return;
    }
    geometry = tile->unk40;
    vertexCount = 3;
    if (geometry == NULL) {
        return;
    }
    group = &geometry->unk8[(handle >> 12) & 0x3FF];
    triangle = &group->unk18[handle & 0xFFF];
    vertices = geometry->vtxTable;
    *channel0 = (vertices[triangle->unk0].v.cn[0] +
        vertices[triangle->unk2].v.cn[0] + vertices[triangle->unk4].v.cn[0]) / vertexCount;
    *channel1 = (vertices[triangle->unk0].v.cn[1] +
        vertices[triangle->unk2].v.cn[1] + vertices[triangle->unk4].v.cn[1]) / vertexCount;
    *channel2 = (vertices[triangle->unk0].v.cn[2] +
        vertices[triangle->unk2].v.cn[2] + vertices[triangle->unk4].v.cn[2]) / vertexCount;
}
#line 419 "src/modules/uvterra_rom.c"

/* Decode a packed tile/mesh/triangle handle and copy its three local vertices.
 * Invalid handles or missing terrain leave the caller outputs untouched.
 * RE_UNKNOWN: handle bounds and asset lifetimes; subordinate pointers and vertex
 * indices remain unchecked, and no tile/world transform is applied here. */
void uvTerraGetTriangleLocalVertices(s32 terrainId, u32 triangleHandle, Vec3F *vertex0, Vec3F *vertex1, Vec3F *vertex2) {
    ParsedUVCT *chunk;
    ParsedUVTR *terrain;
    Unk80225FBC_0x28_UnkC *triangle;
    uvUnkTileStruct *tile;
    Unk80225FBC_0x28 *mesh;
    Vtx *vertices;
    Unk80225FBC_0x28_UnkC *selectedTriangle;

    if (triangleHandle == -1U) {
        return;
    }

    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return;
    }

    tile = &terrain->unk28[(triangleHandle >> 0x16) & 0x3FF];
    chunk = tile->unk40;
    mesh = &chunk->unk8[(triangleHandle >> 0xC) & 0x3FF];
    triangle = &mesh->unk18[triangleHandle & 0xFFF];
    vertices = chunk->vtxTable;
    vertex0->x = vertices[triangle->unk0].v.ob[0];
    vertex0->y = vertices[triangle->unk0].v.ob[1];
    selectedTriangle = triangle;
    vertex0->z = vertices[selectedTriangle->unk0].v.ob[2];
    vertex1->x = vertices[selectedTriangle->unk2].v.ob[0];
    vertex1->y = vertices[selectedTriangle->unk2].v.ob[1];
    vertex1->z = vertices[selectedTriangle->unk2].v.ob[2];
    vertex2->x = vertices[selectedTriangle->unk4].v.ob[0];
    vertex2->y = vertices[selectedTriangle->unk4].v.ob[1];
    vertex2->z = vertices[selectedTriangle->unk4].v.ob[2];
}
#line 421 "src/modules/uvterra_rom.c"

#line 422 "src/modules/uvterra_rom.c"

/* Select a terrain grid tile and return its stored X/Y translation.
 * On a missing terrain or an out-of-range grid index, retain the input X/Y.
 * RE_ORIGINAL_QUIRK: integer division uses separately truncated numerator
 * and tile-size values, not a floating quotient. Preserve that boundary rule.
 * RE_UNKNOWN: grid-size units and the valid input domain (nonzero truncated
 * divisors, finite coordinates) remain unproved. Trace UVTR field producers
 * and callers before assigning units or changing exceptional-input handling. */
s32 uvTerraGetTileTranslationXYAtWorldPosition(s32 terrainId, f32 worldX, f32 worldY,
                              f32 *outX, f32 *outY) {
    ParsedUVTR *terrain;
    s32 tileX;
    s32 tileY;
    s32 tileIndex;

    *outX = worldX;
    *outY = worldY;
    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return 0;
    }
    tileX = (s32)(worldX - terrain->unk0.unk0) / (s32)terrain->unk1C;
    tileY = (s32)(worldY - terrain->unk0.unk4) / (s32)terrain->unk20;
    if ((tileX >= terrain->unk18) || (tileX < 0) ||
        (tileY >= terrain->unk19) || (tileY < 0)) {
        *outX = worldX;
        *outY = worldY;
        return 0;
    }
    /* Snapshot the selected index before either output write; the original
     * reuses that index while reloading the tile-array pointer for Y. */
    tileIndex = terrain->unk18 * tileY + tileX;
    *outX = terrain->unk28[tileIndex].unk0.m[3][0];
    *outY = terrain->unk28[tileIndex].unk0.m[3][1];
    return 1;
}
#line 423 "src/modules/uvterra_rom.c"

#line 424 "src/modules/uvterra_rom.c"
/* Clear both outputs, resolve the loaded UVTR terrain, and return the X/Y
 * translation of the tile selected by handle bits 22..31. Return zero when the
 * terrain is absent, or one after copying both coordinates in original order.
 * RE_UNKNOWN: translation coordinate-space convention and valid tile-index
 * limits. The original performs no sentinel/index check and requires valid
 * output storage; keep separate terrain-table reads across the output writes. */
s32 uvTerraGetPackedTileTranslationXY(s32 terrainId, u32 handle, f32 *outX, f32 *outY) {
    s32 tileIndex;
    ParsedUVTR *terrain;

    *outX = 0.0f;
    *outY = 0.0f;
    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return 0;
    }
    tileIndex = (handle >> 22) & 0x3FF;
    *outX = terrain->unk28[tileIndex].unk0.m[3][0];
    *outY = terrain->unk28[tileIndex].unk0.m[3][1];
    return 1;
}
#line 425 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-385C"
/* Collect static-object and terrain-triangle segment contacts by query flags. RE_ORIGINAL_QUIRK: zero-length perturbation, partial outputs, live counters and uninitialized/stale traversal slots. RE_UNKNOWN: caller contract and complete buffer ownership. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040385C.s")
#line 426 "uvterra-full-module-draft-385C"
#line 427 "src/modules/uvterra_rom.c"

/* Consumed local views only. Keep the shared asset/header declarations and
 * every older body literal; these spans do not prove full allocation ownership. */
typedef struct TerrainContactObjectView {
    /* +00 model ID; only the following consumed fields are named. */
    u16 modelId; u8 opaque02[6];
    /* +08/+0C/+10 bound center and +14 bound radius use original float loads. */
    f32 unk8, unkC, unk10, unk14;
    /* +18 intersects the cell mask; +40 bit0 gates this static-object entry. */
    u16 unk18; u8 opaque1A[0x26];
    s32 unk40; u8 opaque44[8];
} TerrainContactObjectView; /* stride0x4C */
typedef struct TerrainContactGroupView {
    u8 opaque00[4]; s32 texture; u8 opaque08[0x10];
    /* +18 points to eight-byte triangle index/mask records; +1C count, +1E mask. */
    Unk80225FBC_0x28_UnkC *unk18;
    u16 unk1C, unk1E; u8 opaque20[4];
    /* +24/+28/+2C group-bound center and +30 radius, all original float loads. */
    f32 unk24, unk28, unk2C, unk30; u8 opaque34[8];
} TerrainContactGroupView; /* stride0x3C */
typedef struct TerrainContactCellView {
    /* Cell+00 vertex table; +08 groups and +10 objects retain 0x3C/0x4C strides. */
    Vtx *vtxTable; u8 opaque04[4]; TerrainContactGroupView *unk8;
    u16 unkC; u8 opaque0E[2]; TerrainContactObjectView *unk10;
    /* +14 object count; +2C shared X/Y scale and +30 Z scale are consumed. */
    u16 unk14; u8 opaque16[0x16]; f32 unk2C, unk30;
} TerrainContactCellView; /* stride0x34 */
typedef struct TerrainContactTileView {
    /* Tile+30/+34/+38 translation, +40 cell pointer, +44 packed-handle component. */
    Mtx4F unk0; TerrainContactCellView *unk40; u16 unk44;
    /* +4C is the genuine second matrix operand; RE_UNKNOWN: initialization/ownership. */
    u8 opaque46[6]; Mtx4F unk4C;
} TerrainContactTileView; /* stride0x8C */
typedef struct TerrainContactTerrainView {
    /* Terrain+18/+19 are byte column/row counts; bounds are in the six-float prefix. */
    uvUnkTeraStruct unk0; u8 unk18, unk19; u8 opaque1A[2];
    /* +1C/+20 grid steps, +28 tile-array pointer; no full allocation claim. */
    f32 unk1C, unk20; u8 opaque24[4];
    TerrainContactTileView *unk28; u8 opaque2C[8];
} TerrainContactTerrainView; /* stride0x34 */
extern s32 *D_uvterra_rom_0040F790, *D_uvterra_rom_0040F794, *D_uvterra_rom_0040F798;
extern f32 *D_uvterra_rom_0040F780;
extern Vec3F *D_uvterra_rom_0040F788;
extern s32 D_uvterra_rom_0040FBF8, D_uvterra_rom_0040FBFC, D_uvterra_rom_0040FC00;
void uvProfilerBegin(s32);
void uvProfilerEnd(s32);
s32 func_uvterra_rom_0040BBC0(f32, f32, f32, f32, f32, f32, f32);
/* A08C returns a signed16 value in the original; this caller ignores it. */
s16 func_uvterra_rom_0040A08C(f32, f32, f32, f32, TerrainContactObjectView *);
s32 uvTerraCollectSphereContacts(s32, s32, f32, f32, f32, f32, s32 **, f32 **, Vec3F **, s32 **);

/* Collect nearby model and triangle sphere-contact results across terrain cells.
 * Public recovery: LLONSIT-glitch, commit c3e54b43f9fcec4b875c60f01f3befb8613615a9;
 * PR141 credits inspectredc for matching work. SPDX: AGPL-3.0-or-later.
 * RE_ORIGINAL_QUIRK: query-record cursor advancement is conditional; secondary
 * lookup is called twice; some capacity checks follow writes; the simple-model
 * fraction keeps only negative values; outer cell endpoints use different steps.
 * Keep the original ordered squared-distance comparison, including unordered
 * inputs, rather than the public draft's subtract-then-compare expression.
 * RE_UNKNOWN: complete buffer capacities/ownership, flag and handle meanings,
 * valid radius/divisor/nonfinite domains and callback mutation reachability.
 * Public local declarations/order remain as the matching-source lead.
 */
s32 uvTerraCollectSphereContacts(s32 terrainId, s32 queryFlags, f32 centerX, f32 centerY, f32 centerZ, f32 queryRadius, s32 **outHandles,
                              f32 **outFractions, Vec3F **outContactVectors, s32 **outFlags) {
    s32 columnIndex;
    s32 rowIndex;
    s32 entryIndex;
    Vtx *firstVertex;
    Vtx *secondVertex;
    Vtx *thirdVertex;
    s32 lastColumn;
    s32 firstRow;
    s32 lastRow;
    s32 cellIndex;
    ParsedUVMD *model;
    s32 worldSpaceResults;
    TerrainContactObjectView *staticObject;
    f32 localCenterX;
    f32 localCenterY;
    f32 localCenterZ;
    Vec3F *contactVector;
    f32 scaledRadiusZ;
    f32 xyToZScaleRatio;
    f32 columnMinimumX;
    f32 columnMaximumX;
    f32 rowMaximumY;
    f32 rowMinimumY;
    f32 radiusOrInverseXYScale;
    f32 scaledCenterY;
    f32 scaledCenterZ;
    f32 objectXOrInverseZScale;
    TerrainContactTerrainView *terrain;
    f32 objectCenterY;
    TerrainContactCellView *cell;
    f32 objectCenterZ;
    f32 scaledRadiusXY;
    f32 scaledCenterX;
    /* RE_UNKNOWN: preserve the public unused declaration and its original order. */
    f32 unusedScalar;
    f32 contactFraction;
    u16 cellMask;
    s32 triangleContactClass;
    s32 firstColumn;
    query_28 *secondaryRecord;
    s32 primaryResultIndex;
    s32 secondaryResultIndex;
    s32 triangleIndex;
    s32 groupMayOverlap;
    TerrainContactTileView *tile;
    Mtx4F transformedMatrix;
    TerrainContactGroupView *triangleGroup;
    Unk80225FBC_0x28_UnkC *triangleIndices;
    query_78 *primaryRecord;

    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return 0;
    }

    if ((centerX + queryRadius) < terrain->unk0.unk0) {
        return 0;
    }

    if (terrain->unk0.unkC < (centerX - queryRadius)) {
        return 0;
    }

    if ((centerY + queryRadius) < terrain->unk0.unk4) {
        return 0;
    }

    if (terrain->unk0.unk10 < (centerY - queryRadius)) {
        return 0;
    }
    uvProfilerBegin(D_uvterra_rom_0040FBF8);
    firstColumn = (s32) (((centerX - queryRadius) - terrain->unk0.unk0) / terrain->unk1C);
    lastColumn = (s32) (((centerX + queryRadius) - terrain->unk0.unk0) / terrain->unk1C);
    firstRow = (s32) (((centerY - queryRadius) - terrain->unk0.unk4) / terrain->unk20);
    lastRow = (s32) (((centerY + queryRadius) - terrain->unk0.unk4) / terrain->unk20);
    if (firstColumn < 0) {
        firstColumn = 0;
    }
    if ((terrain->unk18 - 1) < lastColumn) {
        lastColumn = (terrain->unk18 - 1);
    }
    if (firstRow < 0) {
        firstRow = 0;
    }
    if ((terrain->unk19 - 1) < lastRow) {
        lastRow = (terrain->unk19 - 1);
    }
    /* RE_UNKNOWN: these pointers expose shared counters, not proven allocation bounds. */
    *D_uvterra_rom_0040F790 = 0;
    *D_uvterra_rom_0040F798 = 0;
    columnMinimumX = terrain->unk0.unk0;
    columnMaximumX = terrain->unk1C + columnMinimumX;
    D_uvterra_rom_0040F76C->uvQueryGetProps(0, 1, &worldSpaceResults, 0);
    for (columnIndex = firstColumn; columnIndex <= lastColumn; columnIndex++) {
        rowMinimumY = terrain->unk0.unk4;
        rowMaximumY = terrain->unk20 + rowMinimumY;
        for (rowIndex = firstRow; rowIndex <= lastRow; rowIndex++) {
            cellIndex = (terrain->unk18 * rowIndex) + columnIndex;
            tile = &terrain->unk28[cellIndex];
            if (tile == NULL) {
                continue;
            }

            cell = tile->unk40;
            if (cell == NULL) {
                continue;
            }

            scaledRadiusXY = cell->unk2C * queryRadius;
            scaledRadiusZ = cell->unk30 * queryRadius;
            localCenterX = centerX - tile->unk0.m[3][0];
            localCenterY = centerY - tile->unk0.m[3][1];
            localCenterZ = centerZ - tile->unk0.m[3][2];
            scaledCenterX = cell->unk2C * localCenterX;
            scaledCenterY = cell->unk2C * localCenterY;
            scaledCenterZ = cell->unk30 * localCenterZ;
            xyToZScaleRatio = cell->unk2C / cell->unk30;
            cellMask = func_uvterra_rom_0040BBC0(localCenterX, localCenterY, queryRadius, columnMinimumX, columnMaximumX, rowMinimumY, rowMaximumY);
            uvProfilerBegin(D_uvterra_rom_0040FC00);
            if (queryFlags & 2) {
                for (entryIndex = 0; entryIndex < cell->unk14; entryIndex++) {
                    staticObject = &cell->unk10[entryIndex];
                    if (!(staticObject->unk40 & 1)) {
                        continue;
                    }

                    if (staticObject->modelId == 0xFFFF) {
                        continue;
                    }

                    if (!((staticObject->unk18 & cellMask))) {
                        continue;
                    }
                    /* The same locals later hold reciprocal scales; do not split declarations. */
                    radiusOrInverseXYScale = staticObject->unk14;
                    objectXOrInverseZScale = staticObject->unk8;
                    objectCenterY = staticObject->unkC;
                    objectCenterZ = staticObject->unk10;

                    if (((localCenterX + radiusOrInverseXYScale + queryRadius) < objectXOrInverseZScale)) {
                        continue;
                    }

                    if ((objectXOrInverseZScale < ((localCenterX - radiusOrInverseXYScale) - queryRadius))) {
                        continue;
                    }

                    if (((localCenterY + radiusOrInverseXYScale + queryRadius) < objectCenterY)) {
                        continue;
                    }

                    if ((objectCenterY < ((localCenterY - radiusOrInverseXYScale) - queryRadius))) {
                        continue;
                    }

                    if (((localCenterZ + radiusOrInverseXYScale + queryRadius) < objectCenterZ)) {
                        continue;
                    }

                    if ((objectCenterZ < ((localCenterZ - radiusOrInverseXYScale) - queryRadius))) {
                        continue;
                    }

                    if (D_uvterra_rom_0040F768->uvIntersectSpheresOverlap(
                            localCenterX, localCenterY, localCenterZ, queryRadius, objectXOrInverseZScale, objectCenterY, objectCenterZ, radiusOrInverseXYScale)
                        == 0) {
                        continue;
                    }
                    model = uvGetLoadedFile('UVMD', (s32) staticObject->modelId);
                    if (model == NULL) {
                        continue;
                    }
                    *D_uvterra_rom_0040F78C = (tile->unk44 << 0xC) | entryIndex;
                    if (model->unk5 & 0x76) {
                        secondaryResultIndex = *D_uvterra_rom_0040F798;
                        primaryResultIndex = *D_uvterra_rom_0040F790;
                        func_uvterra_rom_0040A08C(localCenterX, localCenterY, localCenterZ, queryRadius, staticObject);
                        primaryRecord = D_uvterra_rom_0040F76C->uvQueryGetActiveRecordArray() + primaryResultIndex;
                        while (primaryResultIndex < *D_uvterra_rom_0040F790) {
                            /* RE_ORIGINAL_QUIRK: only this branch advances primaryRecord. */
                            if (worldSpaceResults != 0) {
                                if (primaryRecord->unk70 & 1) {
                                    primaryRecord->unk0.x += tile->unk0.m[3][0];
                                    primaryRecord->unk0.y += tile->unk0.m[3][1];
                                    primaryRecord->unk0.z += tile->unk0.m[3][2];
                                    primaryRecord->unkC.x += tile->unk0.m[3][0];
                                    primaryRecord->unkC.y += tile->unk0.m[3][1];
                                    primaryRecord->unkC.z += tile->unk0.m[3][2];
                                    primaryRecord->unk18.x += tile->unk0.m[3][0];
                                    primaryRecord->unk18.y += tile->unk0.m[3][1];
                                    primaryRecord->unk18.z += tile->unk0.m[3][2];
                                } else {
                                    D_uvterra_rom_0040F744->uvMat4Mul(&transformedMatrix, &primaryRecord->unk30,
                                                                      &tile->unk4C);
                                    D_uvterra_rom_0040F744->uvMat4FCopy(&primaryRecord->unk30, &transformedMatrix);
                                }
                                primaryRecord++;
                            }
                            D_uvterra_rom_0040F794[primaryResultIndex] |= 2;
                            D_uvterra_rom_0040F794[primaryResultIndex] &= ~4;
                            primaryResultIndex++;
                        }

                        /* RE_ORIGINAL_QUIRK: test and fetch remain two separate callbacks. */
                        if (D_uvterra_rom_0040F76C->uvQueryGetSecondaryRecordArray() != NULL) {
                            secondaryRecord = D_uvterra_rom_0040F76C->uvQueryGetSecondaryRecordArray() + secondaryResultIndex;
                            while (secondaryResultIndex < *D_uvterra_rom_0040F798) {
                                D_uvterra_rom_0040F748->uvVec3FAdd(&secondaryRecord->unk14, &secondaryRecord->unk14,
                                                                   (Vec3F *) tile->unk0.m[3]);

                                D_uvterra_rom_0040F748->uvVec3FAdd(&secondaryRecord->unk8, &secondaryRecord->unk8,
                                                                   (Vec3F *) tile->unk0.m[3]);
                                secondaryResultIndex++;
                                secondaryRecord++;
                            }
                        }
                        /* RE_ORIGINAL_QUIRK: this capacity test follows the recorded writes. */
                        if (*D_uvterra_rom_0040F790
                            >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                            rowIndex = lastRow + 1;
                            columnIndex = lastColumn + 1;
                            break;
                        }
                    } else {
                        D_uvterra_rom_0040F784[*D_uvterra_rom_0040F790] = *D_uvterra_rom_0040F78C;
                        contactVector = &D_uvterra_rom_0040F788[*D_uvterra_rom_0040F790];
                        contactVector->x = localCenterX - objectXOrInverseZScale;
                        contactVector->y = localCenterY - objectCenterY;
                        contactVector->z = localCenterZ - objectCenterZ;
                        contactFraction = (queryRadius
                                      - (D_uvterra_rom_0040F75C->uvSqrtf(
                                             SQ(contactVector->x) + SQ(contactVector->y) + SQ(contactVector->z))
                                         - radiusOrInverseXYScale))
                                     / queryRadius;
                        /* RE_ORIGINAL_QUIRK: keep negative fractions; nonnegative/NaN becomes zero. */
                        if (contactFraction < 0.0f) {
                            D_uvterra_rom_0040F780[*D_uvterra_rom_0040F790] = contactFraction;
                        } else {
                            D_uvterra_rom_0040F780[*D_uvterra_rom_0040F790] = 0;
                        }
                        D_uvterra_rom_0040F794[*D_uvterra_rom_0040F790] |= 1;
                        D_uvterra_rom_0040F748->uvVec3FNormalize(contactVector, contactVector);
                        *D_uvterra_rom_0040F790 += 1;
                        /* RE_ORIGINAL_QUIRK: this capacity test follows the recorded writes. */
                        if (*D_uvterra_rom_0040F790
                            >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                            rowIndex = lastRow + 1;
                            columnIndex = lastColumn + 1;
                            break;
                        }
                    }
                }
            }

            uvProfilerEnd(D_uvterra_rom_0040FC00);
            uvProfilerBegin(D_uvterra_rom_0040FBFC);
            if ((queryFlags & 4)
                && (*D_uvterra_rom_0040F790 < D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity())) {
                for (entryIndex = 0; entryIndex < cell->unkC; entryIndex++) {
                    triangleGroup = &cell->unk8[entryIndex];
                    if (!(triangleGroup->unk1E & cellMask)) {
                        continue;
                    }

                    /* Preserve the original ordered distance<=radius comparison, including overflow/NaN. */
                    groupMayOverlap = ((SQ(localCenterX - triangleGroup->unk24) + SQ(localCenterY - triangleGroup->unk28)
                             + SQ(localCenterZ - triangleGroup->unk2C))
                            <= SQ(triangleGroup->unk30 + queryRadius));

                    if (groupMayOverlap == 0) {
                        continue;
                    }
                    for (triangleIndex = 0; triangleIndex < triangleGroup->unk1C; triangleIndex++) {
                        triangleIndices = &triangleGroup->unk18[triangleIndex];
                        if (!(triangleIndices->unk6 & cellMask)) {
                            continue;
                        }

                        firstVertex = &cell->vtxTable[triangleIndices->unk0];
                        secondVertex = &cell->vtxTable[triangleIndices->unk2];
                        thirdVertex = &cell->vtxTable[triangleIndices->unk4];

                        if ((scaledRadiusXY < (MIN(MIN(firstVertex->v.ob[0], secondVertex->v.ob[0]), thirdVertex->v.ob[0])
                                         - scaledCenterX))) {
                            continue;
                        }
                        if ((scaledRadiusXY
                             < (scaledCenterX
                                - MAX(MAX(firstVertex->v.ob[0], secondVertex->v.ob[0]), thirdVertex->v.ob[0])))) {
                            continue;
                        }
                        if ((scaledRadiusXY < (MIN(MIN(firstVertex->v.ob[1], secondVertex->v.ob[1]), thirdVertex->v.ob[1])
                                         - scaledCenterY))) {
                            continue;
                        }
                        if ((scaledRadiusXY
                             < (scaledCenterY
                                - MAX(MAX(firstVertex->v.ob[1], secondVertex->v.ob[1]), thirdVertex->v.ob[1])))) {
                            continue;
                        }
                        if ((scaledRadiusZ < (MIN(MIN(firstVertex->v.ob[2], secondVertex->v.ob[2]), thirdVertex->v.ob[2])
                                      - scaledCenterZ))) {
                            continue;
                        }
                        if ((scaledRadiusZ
                             < (scaledCenterZ
                                - MAX(MAX(firstVertex->v.ob[2], secondVertex->v.ob[2]), thirdVertex->v.ob[2])))) {
                            continue;
                        }

                        /* This triangle path checks capacity before its contact callback. */
                        if (*D_uvterra_rom_0040F790
                            >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                            break;
                        }

                        triangleContactClass = D_uvterra_rom_0040F768->uvIntersectClassifySphereTriangleContact(
                            scaledCenterX, scaledCenterY, scaledCenterZ, scaledRadiusXY, xyToZScaleRatio, firstVertex->v.ob[0], firstVertex->v.ob[1],
                            firstVertex->v.ob[2], secondVertex->v.ob[0], secondVertex->v.ob[1], secondVertex->v.ob[2],
                            thirdVertex->v.ob[0], thirdVertex->v.ob[1], thirdVertex->v.ob[2],
                            &D_uvterra_rom_0040F788[*D_uvterra_rom_0040F790],
                            &D_uvterra_rom_0040F780[*D_uvterra_rom_0040F790]);

                        if (triangleContactClass == 0) {
                            continue;
                        }
                        if (triangleContactClass == 1) {
                            D_uvterra_rom_0040F794[*D_uvterra_rom_0040F790] |= 1;
                        } else {
                            D_uvterra_rom_0040F794[*D_uvterra_rom_0040F790] &= ~1;
                        }
                        D_uvterra_rom_0040F794[*D_uvterra_rom_0040F790] |= 4;
                        D_uvterra_rom_0040F794[*D_uvterra_rom_0040F790] &= ~2;
                        if (worldSpaceResults != 0) {
                            radiusOrInverseXYScale = 1.0f / cell->unk2C;
                            objectXOrInverseZScale = 1.0f / cell->unk30;
                            primaryRecord = D_uvterra_rom_0040F76C->uvQueryGetActiveRecordArray()
                                       + *D_uvterra_rom_0040F790;
                            primaryRecord->unk0.x = (radiusOrInverseXYScale * firstVertex->v.ob[0]) + tile->unk0.m[3][0];
                            primaryRecord->unk0.y = (radiusOrInverseXYScale * firstVertex->v.ob[1]) + tile->unk0.m[3][1];
                            primaryRecord->unk0.z = (objectXOrInverseZScale * firstVertex->v.ob[2]) + tile->unk0.m[3][2];
                            primaryRecord->unkC.x = (radiusOrInverseXYScale * secondVertex->v.ob[0]) + tile->unk0.m[3][0];
                            primaryRecord->unkC.y = (radiusOrInverseXYScale * secondVertex->v.ob[1]) + tile->unk0.m[3][1];
                            primaryRecord->unkC.z = (objectXOrInverseZScale * secondVertex->v.ob[2]) + tile->unk0.m[3][2];
                            primaryRecord->unk18.x = (radiusOrInverseXYScale * thirdVertex->v.ob[0]) + tile->unk0.m[3][0];
                            primaryRecord->unk18.y = (radiusOrInverseXYScale * thirdVertex->v.ob[1]) + tile->unk0.m[3][1];
                            primaryRecord->unk18.z = (objectXOrInverseZScale * thirdVertex->v.ob[2]) + tile->unk0.m[3][2];
                            primaryRecord->unk24 = D_uvterra_rom_0040F788[*D_uvterra_rom_0040F790];
                            primaryRecord->unk70 |= 1;
                            primaryRecord->unk74 = triangleGroup->texture;
                        }
                        D_uvterra_rom_0040F780[*D_uvterra_rom_0040F790] /= -queryRadius * cell->unk2C;
                        D_uvterra_rom_0040F784[*D_uvterra_rom_0040F790] =
                            ((cellIndex & 0x3FF) << 0x16) + ((entryIndex & 0x3FF) << 0xC) + (triangleIndex & 0xFFF);
                        *D_uvterra_rom_0040F790 += 1;
                    }
                }
            }
            uvProfilerEnd(D_uvterra_rom_0040FBFC);
            if (lastRow >= rowIndex) {
                rowMinimumY += terrain->unk20;
                rowMaximumY += terrain->unk20;
            }
        }
        if (lastColumn >= columnIndex) {
            columnMinimumX += terrain->unk1C;
            /* RE_ORIGINAL_QUIRK: upper X advances by +20, while lower X uses +1C. */
            columnMaximumX += terrain->unk20;
        }
    }
    *outHandles = D_uvterra_rom_0040F784;
    *outFractions = D_uvterra_rom_0040F780;
    *outContactVectors = D_uvterra_rom_0040F788;
    *outFlags = D_uvterra_rom_0040F794;
    uvProfilerEnd(D_uvterra_rom_0040FBF8);
    return *D_uvterra_rom_0040F790;
}

#line 429 "src/modules/uvterra_rom.c"

/* Return the selected mesh texture's low 12 bits, or 0xFFF on the original
 * invalid-handle/missing-terrain/tile/chunk paths. Preserve the tile null test.
 * RE_UNKNOWN: tile/mesh bounds and loaded asset lifetime are caller contracts;
 * the triangle subindex is deliberately unused by this texture query. */
s32 uvTerraGetTriangleTextureId(s32 terrainId, u32 triangleHandle) {
    ParsedUVCT* chunk;
    ParsedUVTR* terrain;
    uvUnkTileStruct* tile;
    Unk80225FBC_0x28* mesh;
    s32 textureId;

    if (triangleHandle == -1U) {
        return 0xFFF;
    }
    terrain = uvGetLoadedFile('UVTR', terrainId);
    if (terrain == NULL) {
        return 0xFFF;
    }
    tile = &terrain->unk28[(triangleHandle >> 0x16) & 0x3FF];
    if (tile == NULL) {
        return 0xFFF;
    }
    chunk = tile->unk40;
    if (chunk == NULL) {
        return 0xFFF;
    }
    mesh = &chunk->unk8[(triangleHandle >> 0xC) & 0x3FF];
    textureId = mesh->texture & 0xFFF;
    return textureId;
}
#line 431 "src/modules/uvterra_rom.c"

/* Collect packed handles for every triangle in meshes with the requested
 * low 12-bit texture ID, using the existing shared scratch buffer.
 * Missing terrain returns 0 and a null output; otherwise return the scratch base
 * even when no mesh matches. RE_UNKNOWN: scratch capacity, asset bounds and
 * reentrancy. Preserve the original 16-bit tile encoding and masked indices. */
s32 uvTerraCollectTriangleHandlesByTexture(s32 terrainId, s32 texture, s32 **outTriangleHandles) {
    ParsedUVTR *uvtr;
    s32 tileCount;
    s32 triangleIndex;
    s32 tileIndex;
    s32 meshIndex;
    s32 packedValue;
    s32 *handles;
    s32 triangleCount;
    u16 meshCount;
    ParsedUVCT *chunk;
    Unk80225FBC_0x28 *mesh;
    s32 handleCount;
    uvUnkTileStruct *tile;
    
    handles = D_uvterra_rom_0040F784;
    handleCount = 0;
    uvtr = uvGetLoadedFile('UVTR', terrainId);
    if (uvtr == NULL) {
        *outTriangleHandles = NULL;
        return 0;
    }
    tileCount = uvtr->unk18 * uvtr->unk19;
    for (tileIndex = 0; tileIndex < tileCount; tileIndex++) {
        tile = &uvtr->unk28[tileIndex];
        if (tile == NULL) {
            continue;
        }
        chunk = tile->unk40;
        if (chunk == NULL) {
            continue;
        }

        meshIndex = 0;
        meshCount = chunk->unkC;
        if (meshCount > 0) {
            do {
                mesh = &tile->unk40->unk8[meshIndex];
                triangleCount = mesh->unk1C;
                if (triangleCount == 0) {
                    continue;
                }
                packedValue = (mesh->texture & 0xFFF);
                if (packedValue != texture) {
                    continue;
                }
                packedValue = ((u16)tileIndex << 22);
                for (triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++) {
                    handles[handleCount++] = (u32)packedValue + ((meshIndex & 0x3FF) << 0xC) + (triangleIndex & 0xFFF);
                }
            } while (++meshIndex != meshCount);
        }
    }
    *outTriangleHandles = handles;
    return handleCount;
}
#line 433 "src/modules/uvterra_rom.c"

/* Compute three weights from signed-16 vertex X/Y coordinates and a point,
 * preserving strict Y partition, integer differences before float conversion,
 * equal-Y rejection and the collapsed-X-span blend of zero. Keep output
 * store/reload order, including the left-associated 1 - second - third tail.
 * RE_ORIGINAL_QUIRK: one native 0.333f load (bits 0x3EAA7EFA) initializes the
 * third/second/first outputs. Rejection may leave fallback or partial weights;
 * both observed direct callers at 0x4067A4/0x406E1C ignore the return status.
 * Ordered float comparisons retain native nonfinite-coordinate behavior.
 * RE_UNKNOWN: coordinate units, valid/degenerate/nonfinite input domains,
 * additional callers and alias/lifetime guarantees, and the rationale for
 * the fallback value. Trace original UVCT vertex assets and coordinate
 * producers at 0x406648/0x406C60 before changing these contracts or the ASM. */
#line 434 "src/modules/uvterra_rom.c"
/* Compute vertex weights by intersecting a triangle with a Y slice, then locating X.
 * RE_ORIGINAL_QUIRK: initialize outputs to exactly 0.333f; rejected inputs may leave
 * defaults or partial updates. Preserve strict comparisons, pointer swaps,
 * store order, float grouping, and the separate zero-span branches.
 * RE_UNKNOWN: caller output aliasing and degenerate/nonfinite input contracts. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00406324.s")
#line 514 "src/modules/uvterra_rom.c"
#line 435 "src/modules/uvterra_rom.c"
#line 435 "src/modules/uvterra_rom.c"

/* Interpolate four vertex channels at a packed terrain surface and query position.
 * RE_ORIGINAL_QUIRK: sentinel/missing terrain leaves outputs untouched; helper
 * return values are ignored. Do not add bounds checks or fallback outputs.
 * The raw helper call uses the unchanged legacy declaration, so signed-halfword
 * locals retain the original call interface; the callee stores the same 16 bits.
 * RE_UNKNOWN: color space, nonfinite/out-of-range byte conversion, output
 * aliasing and packed-handle validity. */
void uvTerraGetColor(s32 terraId, u32 surfaceId, f32 arg2, f32 arg3, u8 *r, u8 *g, u8 *b,
                               u8 *a) {
    Unk80225FBC_0x28 *temp_t2;
    uvUnkTileStruct *sp60;
    ParsedUVTR *uvtr;
    Vtx *vtx;
    Unk80225FBC_0x28_UnkC *sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s16 sp3A;
    s16 sp38;
    ParsedUVCT *uvct;

    if (surfaceId == -1U) {
        return;
    }

    uvtr = uvGetLoadedFile('UVTR', terraId);
    if (uvtr == NULL) {
        return;
    }

    sp60 = &uvtr->unk28[(surfaceId >> 0x16) & 0x3FF];
    if (sp60 == NULL) {
        return;
    }

    uvct = sp60->unk40;
    if (uvct == NULL) {
        return;
    }

    temp_t2 = &uvct->unk8[(surfaceId >> 0xC) & 0x3FF];
    sp54 = &temp_t2->unk18[surfaceId & 0xFFF];
    vtx = uvct->vtxTable;
    func_uvterra_rom_0040B8C0(uvtr, arg2, arg3, 0.0f, &sp50, &sp4C, &sp3C, &sp3A, &sp38, 0U);
    sp50 *= sp60->unk40->unk2C;
    sp4C *= sp60->unk40->unk2C;
    func_uvterra_rom_00406324(&vtx[sp54->unk0], &vtx[sp54->unk2], &vtx[sp54->unk4], &sp48, &sp44, &sp40,
                              sp50, sp4C);

    *r = ((vtx[sp54->unk0].v.cn[0] * sp48) + (vtx[sp54->unk2].v.cn[0] * sp44))
         + (vtx[sp54->unk4].v.cn[0] * sp40);
    *g = ((vtx[sp54->unk0].v.cn[1] * sp48) + (vtx[sp54->unk2].v.cn[1] * sp44))
         + (vtx[sp54->unk4].v.cn[1] * sp40);
    *b = ((vtx[sp54->unk0].v.cn[2] * sp48) + (vtx[sp54->unk2].v.cn[2] * sp44))
         + (vtx[sp54->unk4].v.cn[2] * sp40);
    *a = ((vtx[sp54->unk0].v.cn[3] * sp48) + (vtx[sp54->unk2].v.cn[3] * sp44))
         + (vtx[sp54->unk4].v.cn[3] * sp40);
}
#line 437 "src/modules/uvterra_rom.c"

/* Sample packed-surface texture channels at interpolated texture coordinates.
 * RE_ORIGINAL_QUIRK: first initialize all outputs to 255; retain coordinate
 * reflection/wrap comparisons, format branches, signed loads and narrowing.
 * The current header names group word +0x04 texture; original ASM loads that word
 * then masks 0xFFF. Only the upstream field spelling unk0.state is adapted.
 * RE_UNKNOWN: nonzero dimensions, loaded texture lifetime, authored format names,
 * output aliasing and full DATA ownership/native equivalence.
 * RE_ORIGINAL_QUIRK: format 4 uses signed 16-bit loads and shifts, with byte truncation;
 * alpha can be 128 rather than 255. Format 2 returns raw four-bit channel values.
 * Do not replace these target-compiler operations with portable color expansion. */
void uvTerraSampleTextureColorAtSurface(s32 arg0, u32 arg1, f32 arg2, f32 arg3, u8 *r, u8 *g, u8 *b, u8 *a) {
    ParsedUVTR *sp84;
    uvUnkTileStruct *sp80;
    f32 var_fv0;
    ParsedUVTX *sp78;
    Vtx *sp74;
    Unk80225FBC_0x28_UnkC *sp70;
    f32 var_fv1;
    f32 sp68;
    f32 sp64;
    s32 temp_t8;
    s32 temp_v0_6;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s32 pad_sp4C;
    f32 sp48;
    s16 sp46;
    s16 sp44;

    *r = 0xFF;
    *g = 0xFF;
    *b = 0xFF;
    *a = 0xFF;

    if (arg1 == -1) {
        return;
    }

    sp84 = uvGetLoadedFile('UVTR', arg0);
    if (sp84 == NULL) {
        return;
    }

    sp80 = &sp84->unk28[(arg1 >> 22) & 0x3FF];
    if (sp80 == NULL || sp80->unk40 == NULL) {
        return;
    }

    sp70 = &sp80->unk40->unk8[(arg1 >> 12) & 0x3FF].unk18[arg1 & 0xFFF];
    temp_t8 = sp80->unk40->unk8[(arg1 >> 12) & 0x3FF].texture & 0xFFF;
    if (temp_t8 == 0xFFF) {
        return;
    }

    sp78 = uvGetLoadedFile('UVTX', temp_t8);
    sp74 = sp80->unk40->vtxTable;
    func_uvterra_rom_0040B8C0(sp84, arg2, arg3, 0.0f, &sp68, &sp64, &sp48, &sp46, &sp44, 0U);
    sp68 *= sp80->unk40->unk2C;
    sp64 *= sp80->unk40->unk2C;
    func_uvterra_rom_00406324(&sp74[sp70->unk0], &sp74[sp70->unk2], &sp74[sp70->unk4], &sp58, &sp54,
                              &sp50, sp68, sp64);
    var_fv0 = ((sp74[sp70->unk0].v.tc[0] * sp58) + (sp74[sp70->unk2].v.tc[0] * sp54)
               + (sp74[sp70->unk4].v.tc[0] * sp50));
    var_fv1 = ((sp74[sp70->unk0].v.tc[1] * sp58) + (sp74[sp70->unk2].v.tc[1] * sp54)
               + (sp74[sp70->unk4].v.tc[1] * sp50));
    var_fv0 *= 0.03125f;
    var_fv1 *= 0.03125f;
    if (sp78->width < var_fv0) {
        var_fv0 -= 2.0f * sp78->width * (f32) (s32) (var_fv0 / sp78->width);
    }
    if (var_fv0 < -sp78->width) {
        var_fv0 += 2.0f * sp78->width * (f32) (s32) (-var_fv0 / sp78->width);
    }
    if (sp78->height < var_fv1) {
        var_fv1 -= 2.0f * sp78->height * (f32) (s32) (var_fv1 / sp78->height);
    }
    if (var_fv1 < -sp78->height) {
        var_fv1 += 2.0f * sp78->height * (f32) (s32) (-var_fv1 / sp78->height);
    }
    if (sp78->unk25 == 2) {
        if (!(var_fv0 > 0.0f)) {
            var_fv0 = -var_fv0;
        }
    } else if (var_fv0 < 0.0f) {
        var_fv0 += sp78->width;
    }
    if (sp78->unk26 == 2) {
        if (!(var_fv1 > 0.0f)) {
            var_fv1 = -var_fv1;
        }
    } else if (var_fv1 < 0.0f) {
        var_fv1 += sp78->height;
    }

    switch (sp78->unk21) {
        case 4:
            temp_v0_6 = (&((s16 *) sp78->data.pointer)[((s32) var_fv0)])[(s32) var_fv1 * sp78->width];
            *r = (temp_v0_6 >> 0xB) << 1 << 2;
            *g = (temp_v0_6 >> 6) << 1 << 2;
            *b = (temp_v0_6 >> 1) << 1 << 2;
            *a = temp_v0_6 << 1 << 6;
            break;
        case 2:
            temp_v0_6 = (&((u8 *) sp78->data.pointer)[(s32) var_fv0])[(s32) var_fv1 * sp78->width];
            *r = ((s32) temp_v0_6 >> 4) & 0xF;
            *g = ((s32) temp_v0_6 >> 4) & 0xF;
            *b = ((s32) temp_v0_6 >> 4) & 0xF;
            *a = temp_v0_6 & 0xF;
            break;
    }
}
#line 439 "src/modules/uvterra_rom.c"

#line 440 "src/modules/uvterra_rom.c"

/* Original height collector keeps at most ten results with normal.z at least
 * native threshold D_uvterra_rom_0040D6D0, after signed-16 count narrowing.
 * RE_ORIGINAL_QUIRK: each provider call receives the current height slot before
 * filtering; rejection does not advance it, so rejected writes can remain after
 * the returned accepted outputs. Preserve this write timing in a future recovery.
 * RE_UNKNOWN: threshold/frame/units, caller capacity, and whether queried handles
 * always satisfy the provider's output-writing paths. Trace original callers,
 * list construction and asset lifetimes before changing validation or outputs. */
#line 449 "src/modules/uvterra_rom.c"
/* Collect up to ten heights with sampled normal.z >= the fixed 0.34f threshold.
 * Preserve the signed-low-half candidate count, list-pointer reread after each
 * sample, and NaN-rejecting comparison. RE_UNKNOWN: caller output capacity and
 * lifetime of the provider's handle list; no new bounds or fallback is added. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004071A4.s")
#line 473 "src/modules/uvterra_rom.c"
#line 450 "src/modules/uvterra_rom.c"
#line 441 "src/modules/uvterra_rom.c"

#line 442 "src/modules/uvterra_rom.c"
/* Store terrain word 0xBF0 without guessing its detailed role. */
void uvTerraSetSharedWordBF0(s32 value) {
    D_uvterra_rom_0040FBF0 = value;
}
#line 445 "src/modules/uvterra_rom.c"

#line 446 "src/modules/uvterra_rom.c"
/* Return terrain word 0xBF0. */
s32 uvTerraGetSharedWordBF0(void) {
    return D_uvterra_rom_0040FBF0;
}
#line 449 "src/modules/uvterra_rom.c"

#line 450 "src/modules/uvterra_rom.c"
/* Store terrain word 0xBF4 without guessing its detailed role. */
void uvTerraSetSharedWordBF4(s32 value) {
    D_uvterra_rom_0040FBF4 = value;
}
#line 453 "src/modules/uvterra_rom.c"

#line 454 "src/modules/uvterra_rom.c"
/* Return terrain word 0xBF4. */
s32 uvTerraGetSharedWordBF4(void) {
    return D_uvterra_rom_0040FBF4;
}
#line 457 "src/modules/uvterra_rom.c"

/* Draw masked 0x3C terrain groups after CHAN property 7/slot 0x2C tests.
 * Preserve group - (channel position - tile translation) float association,
 * cached low-16 count/mask and the live terrain-field/global angular gate.
 * MATH slot 0x04 precedes the group 0x38 read and packed-level predicate;
 * the address comparison writes 1/2 to 0x8002D19C before STAT slot 0x38 draws.
 * RE_ORIGINAL_QUIRK: invalid CHAN property queries leave position unwritten,
 * while its later plane test returns 1. No fallback is initialized here.
 * RE_UNKNOWN: caller channel domain, loaded-terrain/group extents and alias/
 * lifetime, historical float fields 0x24..0x30, coordinate frame/units and
 * shared-status meanings. Trace original callers, UVCT/UVTR producers and
 * writers of 0x8002D198/0x8002D19C before changing these contracts or the ASM. */
#line 458 "src/modules/uvterra_rom.c"
#line 1 "uvterra-full-module-draft-72EC"
/* Draw terrain groups passing mask, channel and angular tests. RE_UNKNOWN: authored visibility semantics; consume captured STAT and channel interfaces only. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004072EC.s")
#line 49 "uvterra-full-module-draft-72EC"
#line 459 "src/modules/uvterra_rom.c"
#line 459 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-74EC"
/* Collect packed static-object handles for one model, stopping at128. RE_ORIGINAL_QUIRK: untouched output on absent terrain and redundant cell reload. RE_UNKNOWN: output lifetime. */
s32 uvTerraCollectStaticObjectHandlesByModel(s32 arg0, s32 modelId, s32 **arg2) {
    DraftTerrainView *uvtr;
    s32 i;
    s32 j;
    DraftTerrainObjectView *sobj;
    DraftTerrainCellView *uvct;
    s32 idx;
    DraftTerrainTileView *temp_a3;

    /* RE_ORIGINAL_QUIRK: Disabled diagnostic string remains in the original rodata owner. */
    idx = 0;
    uvtr = uvGetLoadedFile('UVTR', arg0);
    if (uvtr == NULL) {
        return 0;
    }

    *arg2 = D_uvterra_rom_0040FC08;
    for (i = 0; i < (uvtr->unk18 * uvtr->unk19); i++) {
        temp_a3 = &uvtr->unk28[i];
        if (temp_a3 == NULL) {
            continue;
        }
        uvct = temp_a3->unk40;
        if (uvct == NULL) {
            continue;
        }

        for (j = 0; j < uvct->unk14; j++) {
            sobj = &uvct->unk10[j];
            if (modelId != sobj->modelId) {
                continue;
            }
            D_uvterra_rom_0040FC08[idx++] = ((temp_a3->unk44 & 0xFFF) << 0xC) | (j & 0xFFF);
            if (idx >= 0x80) {
                return 0x80;
            }
            // redundant assignment
            uvct = temp_a3->unk40;
        }
    }
    return idx;
}
#line 461 "src/modules/uvterra_rom.c"

#line 462 "src/modules/uvterra_rom.c"
/* Store 1.0f / value in the indexed terrain array without input checks.
 * RE_UNKNOWN: index bounds and divisor domain; trace original callers/storage. */
void uvTerraSetReciprocalByIndex(s32 index, f32 value)
{
  s32 unusedBase = D_uvterra_rom_0040FBA4;
  *((f32 *) (((u8 *) D_uvterra_rom_0040FBA4) + (index * 4))) = 1.0f / value;
}
#line 467 "src/modules/uvterra_rom.c"

/* Native 984-byte static-object renderer: subtract tile translation from
 * channel property seven; walk cached-count 0x4C records, filter both masks,
 * the channel-plane low-byte result and optional packed angular levels.
 * Reload terrain/model/global gates, preserve scale * (distanceSquared * scale),
 * publish LOD/X/Y/tile, then draw or queue the proven record callbacks.
 * RE_ORIGINAL_QUIRK: an invalid-channel property getter can leave the local
 * position unwritten while the later plane provider returns success. The
 * original supplies no fallback; caller-domain reachability is unproved.
 * RE_UNKNOWN: historical record fields/coordinate units, channel/table bounds,
 * loaded-terrain guarantee, aliases and queued-record lifetime, plus meanings
 * of masks, scale and status values. Trace original UVCT writers, channel
 * initialization and D128/callback consumers. Draft1799 retains provider calls
 * and publication order but fails exact native instructions: duplicated final
 * distance-square evaluation across scale branches, different LOD narrowing,
 * local homes/registers and shifted relocation records. Recover original
 * source dataflow before replacing assembly; no runtime fault is established. */
#line 468 "src/modules/uvterra_rom.c"
#line 1 "uvterra-full-module-draft-76A8"
/* Select static-object LODs and draw or queue callbacks. RE_ORIGINAL_QUIRK: preserve the Z snapshot and model-dependent paths. RE_UNKNOWN: LOD policy and scratch-field ownership; offsets20/24/28/2C are measured views. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004076A8.s")
#line 94 "uvterra-full-module-draft-76A8"
#line 469 "src/modules/uvterra_rom.c"
#line 469 "src/modules/uvterra_rom.c"

/* Copy the three arguments into the retained local words, then return zero.
 * RE_UNKNOWN: the historical terrain operation and intended use of those locals remain unresolved. */
#line 470 "src/modules/uvterra_rom.c"
s32 func_uvterra_rom_00407A80(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    sp0 = arg0;
    sp4 = arg1;
    sp8 = arg2;
    return 0;
}
#line 479 "src/modules/uvterra_rom.c"

#line 480 "src/modules/uvterra_rom.c"
/* Apply the shared inverse translation to the matrix pointer at object
 * byte28, load that view with native flags3, invoke the original model-draw
 * helper, then pop the view. Preserve all four calls and their original order.
 *
 * RE_UNKNOWN: object byte28 matrix provenance/frame and lifetime, complete
 * callback declaration and the forwarded context word's meaning. Original
 * helpers consume the existing modelId/matrix/flag fields; they only home the
 * first word. Trace the original object producer, callback registrations and
 * helper callers before giving that word channel or ownership semantics.
 * The byte28 pointer is an observed access within an existing opaque region;
 * do not infer a complete historical object declaration from this wrapper. */
#line 1 "uvterra-full-module-draft-7A94"
/* Load the stored view, draw static-object LODs, then pop it. RE_UNKNOWN: callback lifetime. This is the original target, not an added wrapper. */
void uvTerraDrawStaticObjectWithView(s32 arg0, DraftTerrainObjectView *sobj) {
    s32 pad[2];
    Mtx4F mtx;

    D_uvterra_rom_0040F744->uvMat4ApplySharedInverseTranslation(&mtx, sobj->unk28);
    D_uvterra_rom_0040F744->uvGfxMtxViewLoad(&mtx, G_MTX_PUSH | G_MTX_LOAD);
    uvTerraDrawStaticObjectLods(arg0, sobj);
    D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
}
#line 492 "src/modules/uvterra_rom.c"
#line 481 "src/modules/uvterra_rom.c"

/* Native 848-byte model-node renderer: submit the record's fixed matrices,
 * optionally convert the first matrix by value and adjust tile translation,
 * draw node state records, and preserve depth-driven matrix-pop accounting.
 * Selected-band and tile reads precede shared status writes; node counts,
 * state-table pointers and the post-draw node-table base are read live.
 * RE_ORIGINAL_QUIRK: a skipped node with flag 0x02 reads the following node's
 * depth byte before testing for the last node. A historical terminal record
 * may exist; this observation does not prove an invalid read or player fault.
 * RE_UNKNOWN: complete record and asset-table extents, terminal-node rules,
 * loaded-model/band validity, aliases and matrix/resource lifetime, plus
 * flag/depth/status meanings. Trace original model/UVCT writers and draw
 * callers before adding validation or changing traversal. Draft1827 preserves
 * actual provider bindings and observed reloads but fails exact instructions:
 * native 320-byte frame versus 312, explicit low-five-bit shift normalization,
 * local/register lifetimes and branch forms differ. Recover original source
 * dataflow before replacing this assembly; no runtime correction is implied. */
#line 482 "src/modules/uvterra_rom.c"
#line 1 "uvterra-full-module-draft-7B0C"
/* Submit reference integer matrices and draw enabled object LOD states. RE_ORIGINAL_QUIRK: path-specific strict/inclusive pop loops and depth accounting. RE_UNKNOWN: successor/depth contract. */
void uvTerraDrawStaticObjectLods(UNUSED s32 arg0, DraftTerrainObjectView *sobj) {
    ParsedUVMD *uvmd;
    ParsedUVMD_1 *temp_fp;
    s32 temp_s2;
    s32 var_s0;
    s32 j;
    s32 var_s3;
    s32 i;
    s32 temp_s1;
    s32 v1;
    Mtx4F spDC;
    s32 padD4;
    uvModelLOD *modelLod;
    s32 padD0;
    Mtx4F *spCC;
    Mtx4F sp8C;

    uvmd = uvGetLoadedFile('UVMD', sobj->modelId);
    v1 = sobj->unk2C;
    spCC = sobj->unk28;
    if (sobj == ((DraftTerrainObjectView *)D_8002D1A0)) {
        D_8002D19C = 1;
    } else {
        D_8002D19C = 2;
    }
    var_s3 = 0;
    temp_fp = &uvmd->unk0[v1];
    for (i = 0; i < temp_fp->unk8; i++) {
        modelLod = &temp_fp->unk0[i];
        if ((sobj->unk1C & (1 << i)) || (((modelLod->unk7 & 1) != 0))) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }

        if (var_s0 == 0) {
            if (modelLod->unk7 & 2) {
                temp_s2 = temp_fp->unk0[i].unk6 - temp_fp->unk0[i + 1].unk6;
                for (j = 0; j < temp_s2; j++) {
                    D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
                    var_s3--;
                }
                continue;
            }
        }
        var_s3 += 1;
        D_uvterra_rom_0040F74C->uvIMtxSubmitMatrix(&sobj->unk4[i], 1U);
        if (var_s0 != 0) {
            if (modelLod->unk20 != 0) {
                D_uvterra_rom_0040F744->uvMat4CopyL2F(&spDC, *sobj->unk4);
                spDC.m[3][0] += spCC->m[3][0];
                spDC.m[3][1] += spCC->m[3][1];
                spDC.m[3][2] += spCC->m[3][2];
                D_uvterra_rom_0040F744->uvMat4ApplySharedInverseTranslation(&sp8C, &spDC);
                D_uvterra_rom_0040F750->uvGfxEmitLookAtAndOptionalHilites(&sp8C, 1);
            }
            temp_s1 = modelLod->unk4;
            j = 0;
            if (temp_s1 > 0) {
                do {
                    D_uvterra_rom_0040F750->uvGfxStateDraw(&modelLod->stateTable[j]);
                    j++;
                } while (j != temp_s1);
            }
            if ((i + 1) == temp_fp->unk8) {
                break;
            }

            temp_s2 = temp_fp->unk0[i].unk6 - temp_fp->unk0[i + 1].unk6;
            for (j = 0; j <= temp_s2; j++) {
                var_s3--;
                D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
            }
        }
    }

    for (i = 0; i < var_s3; i++) {
        D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
    }
}
#line 483 "src/modules/uvterra_rom.c"
#line 483 "src/modules/uvterra_rom.c"

#line 484 "src/modules/uvterra_rom.c"
/* Apply the shared inverse translation to the matrix pointer at object
 * byte28, load that view with native flags3, invoke the original model-draw
 * helper, then pop the view. Preserve all four calls and their original order.
 * The second helper temporarily rewrites native fixed-matrix XY entries
 * using object words20/24/30 and restores those entries before returning.
 * RE_UNKNOWN: object byte28 matrix provenance/frame and lifetime, complete
 * callback declaration and the forwarded context word's meaning. Original
 * helpers consume the existing modelId/matrix/flag fields; they only home the
 * first word. Trace the original object producer, callback registrations and
 * helper callers before giving that word channel or ownership semantics.
 * The byte28 pointer is an observed access within an existing opaque region;
 * do not infer a complete historical object declaration from this wrapper. */
#line 1 "uvterra-full-module-draft-7E5C"
/* Load the stored view, draw billboard LODs, then pop it. RE_UNKNOWN: callback lifetime and authored mode; no extra thunk. */
void uvTerraDrawBillboardStaticObjectWithView(s32 arg0, DraftTerrainObjectView *sobj) {
    s32 pad[1];
    Mtx4F sp1C;

    D_uvterra_rom_0040F744->uvMat4ApplySharedInverseTranslation(&sp1C, sobj->unk28);
    D_uvterra_rom_0040F744->uvGfxMtxViewLoad(&sp1C, 3U);
    uvTerraDrawBillboardStaticObjectLods(arg0, sobj);
    D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
}
#line 497 "src/modules/uvterra_rom.c"
#line 485 "src/modules/uvterra_rom.c"

/* Native 1068-byte hierarchy draw: derive temporary fixed-matrix terms from
 * record words 0x20/0x24/0x30 and model word 0x10. Preserve the four original
 * matrix-word snapshots, halfword store order, live node/state/count reloads,
 * matrix submissions, pop accounting and final four-word restoration.
 * RE_ORIGINAL_QUIRK: matrix-push failure is ignored while the local outstanding
 * count still increases. An unselected flag-0x02 node reads following-node depth
 * before the last-node test; historical terminal-record capacity is unresolved.
 * RE_UNKNOWN: record-component frame/units, model divisor meaning/nonzero domain,
 * finite fixed-conversion inputs, loaded asset/band/node/state/matrix extents,
 * flags/depths, push-failure reachability and callback/global/matrix aliases and
 * lifetime. Trace original UVMD/UVCT producers and actual caller paths.
 * Draft 1886 fails exact instructions despite represented observed effects:
 * frame/local homes, cached band and byte-offset lifetimes, explicit shift
 * normalization, positive-count loop lowering and cleanup counter reuse differ.
 * Recover original source dataflow before replacing this retained assembly. */
#line 486 "src/modules/uvterra_rom.c"
#line 1 "uvterra-full-module-draft-7ED4"
/* Temporarily rotate the fixed matrix toward the view and draw billboard LODs. RE_ORIGINAL_QUIRK: save/restore four words, sign-sensitive fixed conversion and original depth loops. RE_UNKNOWN: scale/nonfinite domain. */
void uvTerraDrawBillboardStaticObjectLods(s32 arg0, DraftTerrainObjectView *arg1) {
    uvModelLOD *temp_s4;
    ParsedUVMD_1 *spF8;
    s32 temp_s1;
    uvMtx *spF0;
    Mtx spB0;
    ParsedUVMD *temp_a0;
    f32 temp_fv0;
    s32 temp_s2;
    s32 var_fp;
    s32 var_s0;
    s32 j;
    s32 i;
    u8 a1;
    s32 temp;
    f32 sp88;
    s32 var_s3;
    f32 sp80;
    f32 sp7C;

    temp_a0 = uvGetLoadedFile('UVMD', arg1->modelId);
    a1 = arg1->unk2C;
    sp88 = temp_a0->unk10;
    sp80 = arg1->unk20;
    sp7C = arg1->unk24;
    if (arg1 == ((DraftTerrainObjectView *)D_8002D1A0)) {
        D_8002D19C = 1;
    } else {
        D_8002D19C = 2;
    }
    spF8 = &temp_a0->unk0[a1];
    spF0 = (uvMtx*)arg1->unk4;
    spB0.m[0][0] = spF0->m[0][0];
    spB0.m[0][2] = spF0->m[0][2];
    spB0.m[2][0] = spF0->m[2][0];
    spB0.m[2][2] = spF0->m[2][2];
    temp_fv0 = D_uvterra_rom_0040F75C->uvSqrtf(SQ(sp80) + SQ(sp7C));
    if (temp_fv0 != 0.0f) {
        sp80 /= temp_fv0;
        sp7C /= temp_fv0;
    }
    temp_fv0 = arg1->unk30;

    temp = ((((-sp7C * temp_fv0) / sp88) * 65536.0f) + 0.5f);
    spF0->u.i[0][0] = temp >> 0x10;
    spF0->u.i[1][1] = temp >> 0x10;
    spF0->u.f[0][0] = temp & 0xFFFF;
    spF0->u.f[1][1] = temp & 0xFFFF;
    temp = ((((sp80 * temp_fv0) / sp88) * 65536.0f) + 0.5f);
    spF0->u.i[0][1] = temp >> 0x10;
    spF0->u.f[0][1] = (temp & 0xFFFF);
    temp = ((((-sp80 * temp_fv0) / sp88) * 65536.0f) + 0.5f);
    spF0->u.i[1][0] = temp >> 0x10;
    spF0->u.f[1][0] = (temp & 0xFFFF);

    var_s3 = 0;
    for (i = 0; i < spF8->unk8; i++) {
        temp_s4 = &spF8->unk0[i];
        if ((arg1->unk1C & (1 << i)) || (((temp_s4->unk7 & 1) != 0))) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }

        if (var_s0 == 0) {
            if (temp_s4->unk7 & 2) {
                temp_s2 = spF8->unk0[i].unk6 - spF8->unk0[i + 1].unk6;
                for (j = 0; j < temp_s2; j++) {
                    D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
                    var_s3 -= 1;
                }
                continue;
            }
        }
        var_s3++;
        D_uvterra_rom_0040F74C->uvIMtxPush(arg1->unk4[i], 1U);
        if (var_s0 != 0) {
            temp_s1 = temp_s4->unk4;
            j = 0;
            if (temp_s1 > 0) {
                do {
                    D_uvterra_rom_0040F750->uvGfxStateDraw(temp_s4->stateTable + j);
                    j++;
                } while (j != temp_s1);
            }
        }
        if ((i + 1) == spF8->unk8) {
            break;
        }

        temp_s2 = spF8->unk0[i].unk6 - spF8->unk0[i + 1].unk6;
        for (j = 0; j <= temp_s2; j++) {
            D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
            var_s3--;
        }
    }
    for (i = 0; i < var_s3; i++) {
        D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
    }
    spF0->m[0][0] = spB0.m[0][0];
    spF0->m[0][2] = spB0.m[0][2];
    spF0->m[2][0] = spB0.m[2][0];
    spF0->m[2][2] = spB0.m[2][2];
}
#line 487 "src/modules/uvterra_rom.c"
#line 487 "src/modules/uvterra_rom.c"

#line 488 "src/modules/uvterra_rom.c"

/* Compose the tile-tail matrix at byte0x4C with the incoming transform and
 * store the selected static-object matrix through original FMTX interfaces.
 * RE_ORIGINAL_QUIRK: matrix-zero local scaling requires BOTH relative scale
 * factors unequal to one; the native change marker only transitions zero to one.
 * RE_UNKNOWN: matrix capacity, tile-tail matrix/frame provenance, scale/divisor
 * domains and threshold/marker meaning. Trace original UVCT/UVTR loaders,
 * callers and marker consumers before naming frames or altering original guards. */
/* Compose the tile-tail transform with the input and store one fixed object matrix. RE_ORIGINAL_QUIRK: scale only when BOTH ratios differ from one; existing DATA marker only changes zero to one. RE_UNKNOWN: matrix capacity, tile-tail frame, marker meaning and divisor domains. Reuse the accepted consumed tile view; it does not prove full ownership. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00408300.s")
#line 544 "src/modules/uvterra_rom.c"
#line 497 "src/modules/uvterra_rom.c"
#line 489 "src/modules/uvterra_rom.c"

#line 490 "src/modules/uvterra_rom.c"
/* Apply a zero-terminated property list to a valid static-object record.
 * Property one assigns the flag word, two clears one bit and three sets one bit.
 * Unknown properties continue scanning as originally; callers own termination,
 * argument types and bit-index bounds. A missing object consumes no properties. */
void uvTerraSetStaticObjectFlags(s32 handle, ...) {
    va_list args;
    UnkSobjDraw *object = uvTerraGetStaticObject(handle);
    s32 property;
    va_start(args, handle);
    if (object != NULL) {
        for (;;) {
            property = va_arg(args, s32);
            switch (property) {
            case 0: va_end(args); return;
            case 2: object->unk1C &= ~(1 << va_arg(args, s32)); break;
            case 3: object->unk1C |= 1 << va_arg(args, s32); break;
            case 1: object->unk1C = va_arg(args, s32); break;
            default: break;
            }
        }
    }
    va_end(args);
}
#line 491 "src/modules/uvterra_rom.c"

/* Copy and adjust one static-object matrix, then add the tile translation. RE_ORIGINAL_QUIRK: compare the X ratio to one twice, never substitute the Z ratio. A missing model returns after the first by-value Mtx copy. RE_UNKNOWN: frame/scale units, matrix-index and nonzero-divisor contracts. */
void uvTerraCopyAdjustedStaticObjectMatrix(s32 objectHandle, s32 matrixIndex, Mtx4F *destination) {
    f32 translationXYScale;
    f32 xyScaleRatio;
    f32 translationZScale;
    f32 zScaleRatio;
    ParsedUVMD *model;
    UnkSobjDraw *object;
    uvUnkTileStruct *tile;

    object = uvTerraGetStaticObject(objectHandle);
    if (object == NULL) {
        return;
    }
    if (object->modelId == 0xFFFF) {
        return;
    }

    tile = object->unk44;
    D_uvterra_rom_0040F744->uvMat4CopyL2F(destination, object->unk4[matrixIndex]);
    model = uvGetLoadedFile('UVMD', object->modelId);
    if (model == NULL) {
        return;
    }

    if (matrixIndex == 0) {
        xyScaleRatio = model->unk10 / object->unk30;
        zScaleRatio = (model->unk10 / object->unk34);
        translationXYScale = 1.0f / object->unk30;
        translationZScale = 1.0f / object->unk34;
        if ((xyScaleRatio != 1.0f) || (xyScaleRatio != 1.0f)) {
            D_uvterra_rom_0040F744->uvMat4Scale(destination, xyScaleRatio, xyScaleRatio, zScaleRatio);
        }
    } else {
        translationXYScale = 1.0f / model->unk10;
        translationZScale = 1.0f / model->unk10;
    }
    destination->m[3][0] *= translationXYScale;
    destination->m[3][1] *= translationXYScale;
    destination->m[3][2] *= translationZScale;
    destination->m[3][0] += tile->unk0.m[3][0];
    destination->m[3][1] += tile->unk0.m[3][1];
    destination->m[3][2] += tile->unk0.m[3][2];
}
#line 493 "src/modules/uvterra_rom.c"

#line 494 "src/modules/uvterra_rom.c"
/* Resolve the packed handle and read the object's unsigned model halfword
 * at offset 0x00, or return 0xFFFF when the resolver returns null.
 * RE_UNKNOWN: object-index validity, model-ID domain and loaded-contour lifetime;
 * this wrapper adds no bounds check or resource reference to the resolver. */
#line 495 "src/modules/uvterra_rom.c"
u16 uvTerraGetStaticObjectModelId(s32 handle) {
    UnkSobjDraw *record = uvTerraGetStaticObject(handle);
    if (record == NULL) return 0xFFFFU;
    return record->modelId;
}
#line 500 "src/modules/uvterra_rom.c"
#line 502 "src/modules/uvterra_rom.c"

#line 503 "src/modules/uvterra_rom.c"
/* Replace a static object's model ID only when the requested UVMD is loaded;
 * 65535 writes the native cleared-model sentinel without a model lookup.
 * RE_ORIGINAL_QUIRK: after looking up the current model, native code tests the
 * already validated requested-model pointer again and ignores the old lookup's
 * result. Preserve both lookups and that test rather than substituting the
 * old-model result or adding an ownership/release operation.
 * RE_UNKNOWN: purpose of the second lookup and caller guarantees for model
 * IDs/lifetimes. Trace original callers and the asset lookup provider before
 * changing this preserved sequence or inferring missing-model player impact. */
#line 512 "src/modules/uvterra_rom.c"
/* Set the static object's model only when the requested asset is loaded.
 * RE_ORIGINAL_QUIRK: keep the old-model lookup and the repeated new-model
 * null test; the native routine ignores the old lookup's return value.
 * RE_UNKNOWN: intended asset bookkeeping and object/asset lifetime. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040880C.s")
#line 538 "src/modules/uvterra_rom.c"
#line 513 "src/modules/uvterra_rom.c"
#line 504 "src/modules/uvterra_rom.c"

#line 505 "src/modules/uvterra_rom.c"

/* Find the first eligible/mask-selected static object passing the original
 * ISCT sphere test and, for model flag0x02, the nonnegative detail-helper test.
 * Native UVCT parser 0x40041C copies four bytes to object offset 0x14,
 * read as f32 by this sphere query. RE_UNKNOWN: shared header's two-u16 view;
 * audit all field users and asset format before layout or physical-unit claims.
 * Position frame/units, locator input domain, flag/detail-result convention,
 * list/resource lifetime and query-handle consumers also require original
 * caller/loader/provider tracing before collision or ownership claims. */
#line 1 "uvterra-full-module-draft-888C"
/* Return the first packed static-object handle containing the point. RE_ORIGINAL_QUIRK: live reloads and model-dependent traversal. RE_UNKNOWN: ordering policy and stale-slot contracts of the LOD helper. */
s32 uvTerraFindStaticObjectContainingPoint(s32 terraId, f32 pointX, f32 pointY, f32 pointZ) {
    s16 subcellMask;
    s16 tileIndex;
    f32 tileLocalX;
    f32 tileLocalY;
    f32 tileLocalZ;
    u32 objectIndex;
    DraftTerrainObjectView *object;
    DraftTerrainTileView *tile;
    DraftTerrainView *terrain;
    DraftTerrainCellView *cell;
    ParsedUVMD *model;
    s32 v0;

    terrain = uvGetLoadedFile('UVTR', terraId);
    if (terrain == NULL) {
        return -1;
    }
    if (func_uvterra_rom_0040B8C0((void *)terrain, pointX, pointY, pointZ, &tileLocalX, &tileLocalY, &tileLocalZ, &tileIndex, &subcellMask, 0U) == 0) {
        return -1;
    }
    tile = &terrain->unk28[(u16) tileIndex];
    cell = tile->unk40;
    if (cell == NULL) {
        return -1;
    }

    for (objectIndex = 0; objectIndex < cell->unk14; objectIndex++) {
        object = &cell->unk10[objectIndex];
        if (!(object->unk40 & 1)) {
            continue;
        }

        if ((object->modelId == 0xFFFF)) {
            continue;
        }

        if (!((u16) subcellMask & object->unk18)) {
            continue;
        }

        if (D_uvterra_rom_0040F768->uvIntersectPointInsideSphere(tileLocalX, tileLocalY, tileLocalZ, object->unk8,
                                                                  object->unkC, object->unk10, object->unk14)
            != 0) {
            model = uvGetLoadedFile('UVMD', (s32) object->modelId);
            if (model == NULL) {
                // redundant statement
                cell = tile->unk40;
                continue;
            }
            *D_uvterra_rom_0040F78C = (tile->unk44 << 0xC) | objectIndex;
            if (model->unk5 & 2) {
                if (func_uvterra_rom_0040A43C(tileLocalX, tileLocalY, tileLocalZ, (UnkSobjDraw *)object) >= 0) {
                    return ((tile->unk44 & 0xFFF) << 0xC) | (objectIndex & 0xFFF);
                }
            } else {
                return ((tile->unk44 & 0xFFF) << 0xC) | (objectIndex & 0xFFF);
            }
        }
        // redundant statement
        cell = tile->unk40;
    }
    return -1;
}
#line 515 "src/modules/uvterra_rom.c"
#line 506 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-8AD8"
/* Collect static-object scalar-extent contacts through model-LOD queries or a direct sphere fallback. RE_ORIGINAL_QUIRK: swapped record translations, conditional record cursor and coordinate increment. RE_UNKNOWN: capacities and scalar semantics. */
s32 uvTerraCollectStaticObjectScalarContacts(s32 terraId, f32 centerX, f32 centerY, f32 centerZ, f32 radius, s32 **packedHandlesOut,
                              f32 **scalarsOut, Vec3F **vectorsOut) {
    s32 tileX;
    s32 tileY;
    s32 minTileX;
    s32 appendedResultIndex;
    s32 maxTileX;
    s32 minTileY;
    s32 maxTileY;
    DraftTerrainTileView *tile;
    query_78 *queryRecord;
    s32 queryRecordFlag;
    f32 tileLocalX;
    f32 tileLocalY;
    DraftTerrainObjectView *object;
    ParsedUVMD *model;
    f32 gridUpperX;
    f32 gridLowerX;
    f32 gridUpperY;
    f32 gridLowerY;
    u16 queryGridMask;
    DraftTerrainView *terrain;
    DraftTerrainCellView *cell;
    f32 objectY;
    f32 queryScalar;
    f32 objectZ;
    Vec3F *resultVector;
    f32 objectRadius;
    f32 objectX;
    f32 tileLocalZ;
    s32 objectIndex;
    s32 pad;

    queryRecordFlag = 0;
    terrain = uvGetLoadedFile('UVTR', terraId);
    if (terrain == NULL) {
        return 0;
    }
    if ((centerX + radius) < terrain->unk0.unk0) {
        return 0;
    }
    if (terrain->unk0.unkC < (centerX - radius)) {
        return 0;
    }
    if ((centerY + radius) < terrain->unk0.unk4) {
        return 0;
    }
    if (terrain->unk0.unk10 < (centerY - radius)) {
        return 0;
    }
    minTileX = (s32) (((centerX - radius) - terrain->unk0.unk0) / terrain->unk1C);
    maxTileX = (s32) (((centerX + radius) - terrain->unk0.unk0) / terrain->unk1C);
    minTileY = (s32) (((centerY - radius) - terrain->unk0.unk4) / terrain->unk20);
    maxTileY = (s32) (((centerY + radius) - terrain->unk0.unk4) / terrain->unk20);
    if (minTileX < 0) {
        minTileX = 0;
    }
    if ((terrain->unk18 - 1) < maxTileX) {
        maxTileX = terrain->unk18 - 1;
    }
    if (minTileY < 0) {
        minTileY = 0;
    }
    if ((terrain->unk19 - 1) < maxTileY) {
        maxTileY = terrain->unk19 - 1;
    }
    *D_uvterra_rom_0040F790 = 0;
    gridLowerX = terrain->unk0.unk0;
    gridUpperX = terrain->unk1C + gridLowerX;
    for (tileX = minTileX; tileX <= maxTileX; tileX++) {
        gridLowerY = terrain->unk0.unk4;
        gridUpperY = terrain->unk20 + gridLowerY;
        for (tileY = minTileY; tileY <= maxTileY; tileY++) {
            s32 tileIndex = (terrain->unk18 * tileY) + tileX;
            tile = &terrain->unk28[tileIndex];
            if (tile == NULL) {
                continue;
            }

            cell = tile->unk40;
            if (cell == NULL) {
                continue;
            }

            if ((tile->unk48 < (centerZ - radius))) {
                continue;
            }

            tileLocalX = centerX - tile->unk0.m[3][0];
            tileLocalY = centerY - tile->unk0.m[3][1];
            tileLocalZ = centerZ - tile->unk0.m[3][2];
            queryGridMask = uvTerraComputeScalarExtentGridMask(tileLocalX, tileLocalY, radius, gridLowerX, gridUpperX, gridLowerY, gridUpperY);

            for (objectIndex = 0; objectIndex < cell->unk14; objectIndex++) {
                object = &cell->unk10[objectIndex];

                if (!(object->unk40 & 1)) {
                    continue;
                }

                if (object->modelId == 0xFFFF) {
                    continue;
                }

                if (!(object->unk18 & queryGridMask)) {
                    continue;
                }

                if (object->unk3C < (tileLocalZ - radius)) {
                    continue;
                }
                objectRadius = object->unk14;
                objectX = object->unk8;
                objectY = object->unkC;
                objectZ = object->unk10;

                if (((centerX + radius) + objectRadius) < objectX) {
                    continue;
                }

                if (objectX < ((centerX - radius) - objectRadius)) {
                    continue;
                }

                if (((centerY + radius) + objectRadius) < objectY) {
                    continue;
                }

                if (objectY < ((centerY - radius) - objectRadius)) {
                    continue;
                }

                if ((centerZ + radius + objectRadius) < objectZ) {
                    continue;
                }

                if (objectZ < ((centerZ - radius) - objectRadius)) {
                    continue;
                }

                if (D_uvterra_rom_0040F768->uvIntersectSpheresOverlap(
                        tileLocalX, tileLocalY, tileLocalZ, radius, objectX, objectY, objectZ, objectRadius)
                    == 0) {
                    continue;
                }
                model = uvGetLoadedFile('UVMD', object->modelId);
                if (model == NULL) {
                    continue;
                }
                *D_uvterra_rom_0040F78C = objectIndex | (tile->unk44 << 0xC);
                if (queryRecordFlag == 0) {
                    D_uvterra_rom_0040F76C->uvQueryGetProps(0, 1, &queryRecordFlag, 0);
                }
                if (model->unk5 & 6) {
                    appendedResultIndex = *D_uvterra_rom_0040F790;
                    func_uvterra_rom_0040A08C(tileLocalX, tileLocalY, tileLocalZ, radius, (TerrainContactObjectView *)object);
                    queryRecord = D_uvterra_rom_0040F76C->uvQueryGetActiveRecordArray() + appendedResultIndex;
                    while (appendedResultIndex < *D_uvterra_rom_0040F790) {
                        if (queryRecordFlag != 0) {
                            queryRecord->unk0.x += tile->unk0.m[3][0];
                            queryRecord->unk0.y += tile->unk0.m[3][1];
                            queryRecord->unk0.z += tile->unk0.m[3][2];
                            queryRecord->unkC.y += tile->unk0.m[3][0];
                            queryRecord->unkC.x += tile->unk0.m[3][1];
                            queryRecord->unkC.z += tile->unk0.m[3][2];
                            queryRecord->unk18.x += tile->unk0.m[3][0];
                            queryRecord->unk18.y += tile->unk0.m[3][1];
                            queryRecord->unk18.z += tile->unk0.m[3][2];
                            queryRecord++;
                        }
                        appendedResultIndex++;
                    }
                    if (*D_uvterra_rom_0040F790
                        >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                        tileY = maxTileY + 1;
                        tileX = maxTileX + 1;
                        break;
                    }
                } else {
                    D_uvterra_rom_0040F784[*D_uvterra_rom_0040F790] = *D_uvterra_rom_0040F78C;
                    resultVector = &D_uvterra_rom_0040F788[*D_uvterra_rom_0040F790];
                    resultVector->x = tileLocalX - objectX;
                    resultVector->y = tileLocalY - objectY;
                    resultVector->z = tileLocalZ - objectZ;
                    queryScalar = (radius
                                - (D_uvterra_rom_0040F75C->uvSqrtf(SQ(resultVector->x) + SQ(resultVector->y)
                                                                   + SQ(resultVector->z))
                                   - objectRadius))
                               / radius;
                    if (queryScalar < 0.0f) {
                        D_uvterra_rom_0040F780[*D_uvterra_rom_0040F790] = queryScalar;
                    } else {
                        D_uvterra_rom_0040F780[*D_uvterra_rom_0040F790] = 0.0f;
                    }
                    D_uvterra_rom_0040F794[*D_uvterra_rom_0040F790] |= 1;
                    D_uvterra_rom_0040F748->uvVec3FNormalize(resultVector, resultVector);
                    if (++*D_uvterra_rom_0040F790
                        >= D_uvterra_rom_0040F76C->uvQueryGetRecordCapacity()) {
                        tileY = maxTileY + 1;
                        tileX = maxTileX + 1;
                        break;
                    }
                }
            }
            if (maxTileY >= tileY) {
                gridLowerY += terrain->unk20;
                gridUpperY += terrain->unk20;
            }
        }
        if (maxTileX >= tileX) {
            gridLowerX += terrain->unk1C;
            gridUpperX += terrain->unk20;
        }
    }
    *packedHandlesOut = D_uvterra_rom_0040F784;
    *scalarsOut = D_uvterra_rom_0040F780;
    *vectorsOut = D_uvterra_rom_0040F788;
    return *D_uvterra_rom_0040F790;
}
#line 508 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-9394"
/* Collect and sort segment contacts against static-object LODs. RE_ORIGINAL_QUIRK: zero-length perturbation, partial outputs and degenerate clipped branch continuing after a write. RE_UNKNOWN: alias/capacity contract. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00409394.s")
#line 318 "uvterra-full-module-draft-9394"
#line 510 "src/modules/uvterra_rom.c"

/* Native 944-byte point/scalar node query: cache the first model band's node
 * count, convert fixed matrices by value, apply first-node reciprocal scales,
 * and preserve live node reads, selection flags and depth-driven matrix pops.
 * RE_ORIGINAL_QUIRK: initialize the signed 16-bit accumulated result to -1,
 * publish the selected node index in the shared QERY word's high byte, and wrap
 * each model-query contribution to 16 bits. Reaching the shared hit limit calls
 * the capacity getter again and returns immediately without the remaining pops.
 * RE_UNKNOWN: point/scalar frame and units, nonzero reciprocal divisors, loaded
 * model/node/matrix extents, flag/depth meanings, aliases and shared-query / matrix
 * stack lifetime. Trace original UVMD/UVCT producers and actual caller paths
 * before interpreting negative results or changing limit-exit cleanup.
 * Draft1865 preserves observed providers and effects but fails exact instructions:
 * matrix/result/count homes, register lifetimes, shift normalization and cleanup
 * counter allocation differ. Recover the original source dataflow before
 * replacing this retained assembly. */
#line 511 "src/modules/uvterra_rom.c"
/* Append MODEL scalar/extent query results for the first model band. RE_ORIGINAL_QUIRK: result starts at -1; preserve signed-halfword wrapping, inclusive depth pops and live provider reloads. Capacity exhaustion calls capacity again and returns its signed low halfword without cleanup. RE_UNKNOWN: scalar units, mask/depth validity, node/matrix extents and stack lifetime. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040A08C.s")
#line 576 "src/modules/uvterra_rom.c"
#line 512 "src/modules/uvterra_rom.c"
#line 512 "src/modules/uvterra_rom.c"

/* RE_ORIGINAL_QUIRK: native 0x40A680 stores the tested-node result to
 * stack byte offset 0x104 only when the node is selected. At 0x40A684 the
 * function reads that signed halfword even when the node is not selected
 * and flag 0x02 is clear, after preparing its matrix. On the first such
 * path there is no earlier store to this slot in this function; after a
 * previously tested node, this path can reuse that stored result. The read
 * controls an immediate nonnegative return or further hierarchy traversal.
 * Original UVCT parser 0x400494 initializes object mask word at 0x1C to zero;
 * TERR export 0x7C / native 0x408534 can replace, clear or set mask bits.
 * RE_UNKNOWN: node-flag combinations and later mask writes on actual query
 * paths, intended result lifetime and observable caller impact. Trace original
 * assets, mask-setter imports and query callers before assigning a default.
 * These producer/setter observations do not prove or exclude reachability. */
#line 513 "src/modules/uvterra_rom.c"
/* Test a point against selected first-band static-object LODs. RE_ORIGINAL_QUIRK: result is not initialized; a disabled matrix-preserving LOD reads the stale/indeterminate halfword. A nonnegative result returns without stack cleanup. RE_UNKNOWN: authored data contract avoiding the first indeterminate read; no claim of total defined ISO C semantics. Do not initialize or repair that machine path. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040A43C.s")
#line 579 "src/modules/uvterra_rom.c"
#line 514 "src/modules/uvterra_rom.c"
#line 514 "src/modules/uvterra_rom.c"

/* Native 888-byte two-point node query: cache the first model band's node
 * count, convert fixed matrices by value, apply first-node reciprocal scales,
 * and preserve selection flags, live node-table reads and depth-driven pops.
 * RE_ORIGINAL_QUIRK: update the shared QERY word's high byte with each selected
 * node index, ignore its model-query return and return -1 on every exit.
 * RE_UNKNOWN: coordinate frame/units, nonzero reciprocal divisors, loaded model
 * and node/matrix extents, mask/flag/depth meanings, aliases and matrix-stack /
 * shared-query lifetime. Trace original UVMD/UVCT producers and actual callers
 * before interpreting the result, adding validation or changing traversal.
 * Draft1859 preserves actual provider arguments and observed effects but fails
 * exact instructions: frame/local homes, first-band register lifetime, explicit
 * low-five-bit shift normalization and branch/counter allocation differ.
 * Recover original source dataflow before replacing this retained assembly. */
#line 515 "src/modules/uvterra_rom.c"
/* Walk model LODs, convert each stored matrix by value and query enabled
 * segments through the model provider. Undo the object's scale for the first
 * LOD, publish the LOD in the shared handle's high byte, then balance the stack.
 * RE_ORIGINAL_QUIRK: the return is always -1; no model-null or zero-scale guard.
 * RE_UNKNOWN: LOD flags/depth validity, shared output capacity and matrix/model
 * ownership. Preserve callback reloads, floating operation order and pop loops. */
s32 uvTerraAppendStaticObjectSegmentQueryResults(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ,
                              UnkSobjDraw *object) {
    s16 modelLodCount;
    ParsedUVMD_1 *modelHeader;
    f32 inverseZScale;
    f32 inverseXYScale;
    ParsedUVMD *model;
    s16 parentPopDifference;
    s16 popIndex;
    Mtx4F transform;
    s16 stackDepth;
    s16 lodIndex;
    s32 shouldQuery;
    uvModelLOD *modelLod;

    model = uvGetLoadedFile('UVMD', (s32) object->modelId);
    modelHeader = model->unk0;
    modelLodCount = modelHeader->unk8;
    D_uvterra_rom_0040F758->uvModelResetMatrixStack();
    stackDepth = 0;
    for (lodIndex = 0; lodIndex < modelLodCount; lodIndex++) {
        modelLod = &modelHeader->unk0[lodIndex];
        if ((object->unk1C & (1 << lodIndex)) || (((modelLod->unk7 & 1)))) {
            shouldQuery = FALSE;
        } else {
            shouldQuery = TRUE;
        }

        if ((!shouldQuery) && (modelLod->unk7 & 2)) {
            continue;
        }

        D_uvterra_rom_0040F744->uvMat4CopyL2F(&transform, object->unk4[lodIndex]);
        if (lodIndex == 0) {
            inverseXYScale = 1.0f / object->unk30;
            inverseZScale = 1.0f / object->unk34;
            D_uvterra_rom_0040F744->uvMat4Scale(&transform, inverseXYScale, inverseXYScale, inverseZScale);
            transform.m[3][0] *= inverseXYScale;
            transform.m[3][1] *= inverseXYScale;
            transform.m[3][2] *= inverseZScale;
        }
        D_uvterra_rom_0040F758->uvModelPushMatrix(&transform);
        stackDepth++;
        if (shouldQuery != 0) {
            *D_uvterra_rom_0040F78C = (*D_uvterra_rom_0040F78C & 0xFFFFFF) | (lodIndex << 0x18);
            D_uvterra_rom_0040F758->uvModelAppendSegmentLodQueryResults(startX, startY, startZ, endX, endY, endZ,
                                                  D_uvterra_rom_0040F758->uvModelGetCurrentMatrix(),
                                                  &modelHeader->unk0[lodIndex], model);
        }
        if (lodIndex == (modelLodCount - 1)) {
            break;
        }
        parentPopDifference = modelHeader->unk0[lodIndex].unk6 - modelHeader->unk0[lodIndex + 1].unk6;
        // clang-format off
        for (popIndex = 0; popIndex <= parentPopDifference; popIndex++) { \
            D_uvterra_rom_0040F758->uvModelPopMatrix();  \
            stackDepth--; \
        }
        // clang-format on
    }

    for (lodIndex = 0; lodIndex < stackDepth; lodIndex++) {
        D_uvterra_rom_0040F758->uvModelPopMatrix();
    }
    return -1;
}
#line 516 "src/modules/uvterra_rom.c"
#line 516 "src/modules/uvterra_rom.c"

#line 517 "src/modules/uvterra_rom.c"
/* Read static-object properties: one writes flags, four writes model ID,
 * and zero terminates. Unknown properties return; absent objects read no outputs.
 * RE_UNKNOWN: output-pointer validity and variadic-list termination/type domain;
 * trace original export callers before claiming that all arguments are valid. */
void uvTerraGetStaticObjectProperties(s32 handle, ...) {
    va_list args;
    UnkSobjDraw *object;
    s32 property;
    object = uvTerraGetStaticObject(handle);
    va_start(args, handle);
    if (object != NULL) {
        for (;;) {
            property = va_arg(args, s32);
            switch (property) {
            case 0: va_end(args); return;
            case 1: *va_arg(args, s32 *) = object->unk1C; break;
            case 4: *va_arg(args, s32 *) = object->modelId; break;
            default: va_end(args); return;
            }
        }
    }
    va_end(args);
}
#line 518 "src/modules/uvterra_rom.c"

#line 519 "src/modules/uvterra_rom.c"
/* Resolve the packed handle and write the signed raw word at object
 * 0x40 when resolution succeeds; otherwise do nothing.
 * RE_UNKNOWN: word meaning, object-index validity and loaded-contour lifetime.
 * This wrapper validates no object bound and changes no resource ownership. */
#line 520 "src/modules/uvterra_rom.c"
void uvTerraSetStaticObjectValue(s32 handle, s32 value) {
    UnkSobjDraw *record = uvTerraGetStaticObject(handle);
    if (record != NULL) record->unk40 = value;
}
#line 524 "src/modules/uvterra_rom.c"
#line 520 "src/modules/uvterra_rom.c"

typedef struct {
    u8 pad0[0x40];
    s32 unk40;
} AutoS_0040ABE0_temp_v0;

#line 527 "src/modules/uvterra_rom.c"
/* Resolve the packed handle and read signed raw word 0x40, or return
 * zero when resolution fails. Zero is also a possible stored word.
 * RE_UNKNOWN: word meaning, object-index validity and loaded-contour lifetime;
 * this wrapper adds neither a bounds check nor a resource reference. */
#line 528 "src/modules/uvterra_rom.c"
s32 uvTerraGetStaticObjectValue(s32 handle) {
    UnkSobjDraw *record = uvTerraGetStaticObject(handle);
    if (record == NULL) return 0;
    return record->unk40;
}
#line 533 "src/modules/uvterra_rom.c"
#line 535 "src/modules/uvterra_rom.c"

#line 536 "src/modules/uvterra_rom.c"
#line 539 "src/modules/uvterra_rom.c"
/* Load UVCT selected by handle bits 12..23, then compute object-array
 * base + (bits 0..11)*0x4C. Upper eight handle bits are ignored. Preserve
 * both the absent-contour test and original computed-address null test.
 * RE_ORIGINAL_QUIRK: no object-count or array-base validity check is present.
 * RE_UNKNOWN: index validity and coordination with UVCT unload/reload; the
 * returned interior address acquires no visible resource reference. */
#line 539 "src/modules/uvterra_rom.c"
UnkSobjDraw *uvTerraGetStaticObject(s32 handle) {
    ParsedUVCT *contour;
    UnkSobjDraw *object;
    contour = uvGetLoadedFile('UVCT', (handle & 0xFFF000U) >> 12);
    if (contour == NULL) return NULL;
    object = &contour->unk10[handle & 0xFFF];
    if (object == NULL) return NULL;
    return object;
}
#line 548 "src/modules/uvterra_rom.c"
#line 537 "src/modules/uvterra_rom.c"

#line 538 "src/modules/uvterra_rom.c"
#line 538 "src/modules/uvterra_rom.c"

/* Return the indexed byte also updated by the queued-tile draw callback.
 * RE_UNKNOWN: the public export's caller index domain and byte meaning.
 * Original 0x40AC9C writes this array by tile-pointer difference, so a channel
 * interpretation is not established. Trace original TERR export 0xA8 callers
 * and all array writers before assigning channel or visibility semantics. */
u8 uvTerraGetIndexedDrawByte(s32 index) {
    return D_uvterra_rom_0040F7A0[index];
}
#line 542 "src/modules/uvterra_rom.c"
#line 541 "src/modules/uvterra_rom.c"

#line 542 "src/modules/uvterra_rom.c"
/* Registered channel callback at priority45: reset the shared threshold,
 * visit 16-byte queued tile records, clear the tile-indexed byte when the
 * record value is below threshold, otherwise draw with its two stored masks
 * and set the byte to one. Store threshold minus terrain field0x24 afterward.
 * RE_UNKNOWN: comparison/threshold units, mask/byte meanings and queue ordering,
 * extent and tile-array membership. Channel/resource lifetime must also be
 * traced: the original loaded-terrain result is used without a null guard.
 * Resolve through original 0x40078C queue construction, shared-threshold writers,
 * TERR export0xA8 consumers and channel callback registration/teardown. */
#line 1 "uvterra-full-module-draft-AC9C"
/* Draw queued terrain tiles and update comparison flags and threshold. RE_ORIGINAL_QUIRK: ordered threshold comparisons. RE_UNKNOWN: units and queue lifetime. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040AC9C.s")
#line 26 "uvterra-full-module-draft-AC9C"
#line 552 "src/modules/uvterra_rom.c"
#line 543 "src/modules/uvterra_rom.c"

#line 544 "src/modules/uvterra_rom.c"

/* When requested, disable fog, restore default render state, clear the
 * depth viewport, install the six stored channel-frustum values and load
 * the channel's property-one matrix through the projection interface.
 * Then visit queued tiles, skipping only threshold <= comparisonValue;
 * preserve the original unordered-value draw path and queue reloads.
 * RE_UNKNOWN: why this callback restores projection, the shared threshold's
 * units/order, mask meanings and valid channel/matrix-output guarantees.
 * Trace original refresh-flag/frustum writers, queue construction and the
 * registered callback order before assigning camera or visibility intent. */
void uvTerraRefreshProjectionAndDrawQueuedTiles(s32 channel) {
    s32 queueIndex;
    TerrainTileDrawRecord *record;
    Mtx4F projection;

    if (D_uvterra_rom_0040FBC4 != 0) {
        D_uvterra_rom_0040F750->uvGfxSetFogParameters(0.0f, 0.0f);
        D_uvterra_rom_0040F750->uvGfxResetDefaultRenderState();
        D_uvterra_rom_0040F754->uvGfxClearDepthImageViewport();
        ((UvChannel_Exports *)D_uvterra_rom_0040F760)->uvChannelSetFrustum(channel,
            D_uvterra_rom_0040FBAC, D_uvterra_rom_0040FBB0,
            D_uvterra_rom_0040FBB4, D_uvterra_rom_0040FBB8,
            D_uvterra_rom_0040FBBC, D_uvterra_rom_0040FBC0);
        ((UvChannel_Exports *)D_uvterra_rom_0040F760)->uvChannelGetProperties(
            channel, 1, &projection, 0);
        D_uvterra_rom_0040F744->uvGfxMtxProjPushF(&projection);
        D_uvterra_rom_0040FBC4 = 0;
    }
    for (queueIndex = 0; queueIndex < D_uvterra_rom_0040F740; queueIndex++) {
        record = &D_uvterra_rom_0040FBE8[queueIndex];
        if (D_uvterra_rom_0040FBA8 <= record->comparisonValue) {
            continue;
        }
        uvTerraDrawTileGeometry(channel, record->tile, record->firstMask,
            record->secondMask);
    }
}
#line 545 "src/modules/uvterra_rom.c"

#line 546 "src/modules/uvterra_rom.c"
/* Apply FMTX's shared negative translation to the tile matrix and load it
 * as view matrix one. Dispatch each geometry list unless its shared disable
 * flag is set, preserving the two 16-bit masks and list counts, then pop the
 * view matrix. Tiles without geometry do nothing.
 * RE_UNKNOWN: which coordinate origin the shared FMTX translation represents
 * at this call. Trace FMTX export 0x04 setters and their render ordering. */
#line 551 "src/modules/uvterra_rom.c"
#line 551 "src/modules/uvterra_rom.c"

void uvTerraDrawTileGeometry(s32 channel, uvUnkTileStruct *tile, u16 firstMask, u16 secondMask) {
    Mtx4F matrix;
    if (tile->unk40 != NULL) {
        D_uvterra_rom_0040F744->uvMat4ApplySharedInverseTranslation(&matrix, &tile->unk0);
        D_uvterra_rom_0040F744->uvGfxMtxViewLoad(&matrix, 1);
        if (D_uvterra_rom_0040FBDC == 0) {
            func_uvterra_rom_004072EC(channel, firstMask, tile, tile->unk40->unk8, tile->unk40->unkC);
        }
        if (D_uvterra_rom_0040FBD8 == 0) {
            func_uvterra_rom_004076A8(channel, tile, firstMask, secondMask, tile->unk40->unk10, tile->unk40->unk14);
        }
        D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
    }
}
#line 565 "src/modules/uvterra_rom.c"
#line 547 "src/modules/uvterra_rom.c"

#line 548 "src/modules/uvterra_rom.c"

/* Adjust a signed index pair by one, apply one 64-entry wrap correction to
 * each index, then read the original DATA-backed 64 by 64 u16 table.
 * A nonzero low mode byte increments first/decrements second; zero reverses
 * those adjustments and transposes the lookup. Preserve signed-16 narrowing
 * and the branch-specific differences that return 0xFFFF before the lookup.
 * RE_UNKNOWN: the table value meanings, mode convention and valid caller index
 * domain. One correction is not general modulo: trace original callers and
 * table construction before assigning geometry meanings or changing bounds. */
u16 uvTerraLookupAdjustedWrappedIndexPair(s16 firstIndex, s16 secondIndex, u8 mode) {
    s16 difference;

    if (mode) {
        difference = secondIndex - firstIndex;
        if (difference == 1 || difference == 0 || difference == -63) {
            return 0xFFFF;
        }
        firstIndex++;
        secondIndex--;
        if (firstIndex >= 64) {
            firstIndex -= 64;
        } else if (firstIndex < 0) {
            firstIndex += 64;
        }
        if (secondIndex >= 64) {
            secondIndex -= 64;
        } else if (secondIndex < 0) {
            secondIndex += 64;
        }
        return D_uvterra_rom_0040D718[firstIndex][secondIndex];
    } else {
        difference = secondIndex - firstIndex;
        if (difference == -1 || difference == 0 || difference == 63) {
            return 0xFFFF;
        }
        firstIndex--;
        secondIndex++;
        if (firstIndex >= 64) {
            firstIndex -= 64;
        } else if (firstIndex < 0) {
            firstIndex += 64;
        }
        if (secondIndex >= 64) {
            secondIndex -= 64;
        } else if (secondIndex < 0) {
            secondIndex += 64;
        }
        return D_uvterra_rom_0040D718[secondIndex][firstIndex];
    }
}
#line 549 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-B26C"
/* Map clipped line endpoints to perimeter indices and mask. RE_ORIGINAL_QUIRK: sentinel slope, sign-conditional rounding and partial writes. RE_UNKNOWN: arithmetic domain; no extra guard or shift mask. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040B26C.s")
#line 66 "uvterra-full-module-draft-B26C"
#line 551 "src/modules/uvterra_rom.c"

/* Native 768-byte grid locator: write the supplied X/Y/Z outputs before
 * reading terrain origins/cell sizes, then publish the wrapped cell index and
 * centered coordinates. Reload output X after writing output Y; preserve aliases.
 * RE_ORIGINAL_QUIRK: truncate coordinates and divisors before signed integer
 * division, wrap cell coordinates to 16 bits, and decrement axes via mode bits
 * 0/1. Coarse-grid failure returns 0 with both indices unwritten; centered bounds
 * failure writes mask 0 and returns 1. Native bounds use signed comparisons while
 * centered calculations use unsigned-to-float conversions; retain ordered FP tests.
 * RE_UNKNOWN: coordinate units, valid finite/truncatable inputs, nonzero truncated
 * divisors, signed-division overflow reachability and output/terrain aliases.
 * Trace original UVTR producers and actual callers before adding validation.
 * Historical draft1878 failed exact recovery; that assessment belongs to the
 * older draft, not this retained stable53 body. The new six-function view still
 * requires a genuine current compile and linked/native proof. No historical
 * result is promoted; valid-domain and caller-alias contracts remain unknown. */
#line 552 "src/modules/uvterra_rom.c"
/* Copy a query position, locate its terrain tile, and form a 4x4 subcell mask.
 * RE_ORIGINAL_QUIRK: signed integer truncation/division feeds u16 indices;
 * mode bits decrement before bounds checks. Keep wrap, output-store order,
 * pointed output reloads and the upstream shift without extra masking.
 * Compatibility: retain the accepted raw void-pointer/signed-halfword-pointer
 * declaration and all raw callers. The clean definition keeps the original u16
 * stores; a reviewed same-address linker alias must bind raw name to clean name.
 * RE_UNKNOWN: authored tile/mode contracts and arbitrary pointer aliasing.
 * This is not the prior u32-index/masked-shift candidate. */
s32 uvTerraLocateTileAndSubcellMask(ParsedUVTR* terrain, f32 pointX, f32 pointY, f32 pointZ, f32* queryXOut, f32* queryYOut, f32* queryZOut, u16* tileIndexOut, u16* subcellMaskOut, u8 boundaryFlags) {
    f32 tileWidth;
    f32 tileHeight;
    f32 halfTileWidth;
    f32 halfTileHeight;
    f32 terrainMinX;
    f32 terrainMinY;
    u16 tileX;
    u16 tileY;
    u16 subcellX;
    u16 subcellY;
    u8 outsideCenteredTile;

    *queryXOut = pointX;
    *queryYOut = pointY;
    *queryZOut = pointZ;
    tileWidth = terrain->unk1C;
    tileHeight = terrain->unk20;
    halfTileWidth = tileWidth * 0.5f;
    halfTileHeight = tileHeight * 0.5f;
    terrainMinX = terrain->unk0.unk0;
    tileX = (s32) (pointX - terrainMinX) / (s32) tileWidth;

    if (boundaryFlags & 1) {
        tileX -= 1;
    }
    terrainMinY = terrain->unk0.unk4;
    tileY = (s32) (pointY - terrainMinY) / (s32) tileHeight;
    if (boundaryFlags & 2) {
        tileY -= 1;
    }

    if ((tileX >= terrain->unk18) || (tileY >= terrain->unk19)) {
        return 0;
    }

    *tileIndexOut = tileX + (tileY * terrain->unk18);

    *queryXOut = ((pointX - (tileX * tileWidth)) - terrainMinX) - halfTileWidth;

    *queryYOut = ((pointY - (tileY * tileHeight)) - terrainMinY) - halfTileHeight;

    if (*queryXOut < -halfTileWidth) {
        outsideCenteredTile = 1;
    } else if (halfTileWidth <= *queryXOut) {
        outsideCenteredTile = 1;
    } else if (*queryYOut < -halfTileHeight) {
        outsideCenteredTile = 1;
    } else if (halfTileHeight <= *queryYOut) {
        outsideCenteredTile = 1;
    } else {
        outsideCenteredTile = 0;
    }

    if (outsideCenteredTile) {
        *subcellMaskOut = 0;
    } else {
        subcellX = (s32) (((*queryXOut + halfTileWidth) * 4.0f) / tileWidth);
        subcellY = (s32) (((*queryYOut + halfTileHeight) * 4.0f) / tileHeight);
        if (subcellX == 4) {
            subcellX = 3;
        }

        if (subcellY == 4) {
            subcellY = 3;
        }
        *subcellMaskOut = 0x8000 >> ((subcellY * 4) + (subcellX % 4));
    }
    return 1;
}
#line 553 "src/modules/uvterra_rom.c"
#line 553 "src/modules/uvterra_rom.c"

#line 1 "uvterra-full-module-draft-BBC0"
/* Build the four-by-four mask overlapped by a scalar extent. RE_ORIGINAL_QUIRK: inclusive float limits and original loop arithmetic. RE_UNKNOWN: negative/nonfinite extent contract. */
u16 uvTerraComputeScalarExtentGridMask(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_fa0;
    f32 temp_fs1;
    f32 temp_ft4;
    f32 temp_ft5;
    u16 var_a0;
    s32 i;
    u16 var_v1;
    f32 var_fv1;
    f32 var_fv0;
    
    var_v1 = 0;
    var_a0 = 0;
    temp_ft4 = (arg4 - arg3) * 0.25f;
    temp_fs1 = 2.0f * temp_ft4;
    temp_ft5 = (arg6 - arg5) * 0.25f;
    var_fv0 = -temp_ft4;
    var_fv1 = -temp_ft5;
    for (i = 0; (var_fv0 <= temp_fs1) && (i < 4); i++) {
        if (((arg0 - arg2) <= var_fv0) && ((var_fv0 - temp_ft4) <= (arg0 + arg2))) {
            var_a0 |= 0x8888 >> i;
        }
        var_fv0 += temp_ft4;
    }

    temp_fa0 = 2.0f * temp_ft5;
    for (i = 0; (var_fv1 <= temp_fa0) && (i < 4); i++) {
        if (((arg1 - arg2) <= var_fv1) && ((var_fv1 - temp_ft5) <= (arg1 + arg2))) {
            var_v1 |= 0xF000 >> (i * 4);
        }
        var_fv1 += temp_ft5;
    }

    var_fv0 = -temp_ft4;
    return var_v1 & var_a0;
}
#line 555 "src/modules/uvterra_rom.c"

#line 556 "src/modules/uvterra_rom.c"
/* Compose two four-sample bound masks with the BF74 centered-span mask.
 * The native loops use quarter-span steps and floating limits; equal first
 * coordinates select native scalar D6E8 instead of dividing.
 * RE_UNKNOWN: coordinate frame/units, valid bound/span domain, equal-coordinate
 * scalar convention and complete center owner (BF74 reads floats0x30/0x34).
 * Resolve through original callers and BF74/B26C consumers before normalizing
 * zero/negative spans, unordered inputs or changing the native scalar. */
#line 1 "uvterra-grid-mask-context-130506.h"
/* Consumed o32 contract: two leading f32 arguments, center in A2, slope in A3,
 * intercept in the caller stack. BF74 returns an unsigned16 mask.
 * RE_UNKNOWN: full authored center record; native reads only floats+30/+34. */
extern f32 D_uvterra_rom_0040D6E8;
u16 func_uvterra_rom_0040BF74(f32, f32, uvUnkTileStruct *, f32, f32);
#line 1 "uvterra-grid-mask-body-130504.c"
// SPDX-License-Identifier: AGPL-3.0-or-later
/* Intersect two four-by-four bounds masks with a segment-derived tile mask.
 * Each axis scans at most four quarter-span positions. The helper consumes
 * only center+0x30/+0x34 as floats; its complete record type remains unnamed.
 * RE_ORIGINAL_QUIRK: preserve the ordered comparisons, increment order and
 * unsigned16 mask narrowing on every union; no span normalization or clamp.
 * Equal segment X uses the original shared slope sentinel, then secondX.
 * RE_UNKNOWN: coordinate units, allowed zero/negative spans, nonfinite inputs,
 * center lifetime and authored API. Reused scan scalars below follow the public
 * source hypothesis; declaration/lifetime matching remains unmeasured.
 * Adapted from synamaxmusic/bar-decomp PR141, main cee90d9784eae4c19cfa260ecac88cf01562481d.
 * Public body is NEEDS_RODATA conditional. Earlier1211/1213 shapes failed. */
u16 uvTerraIntersectSegmentAndBoundsMasks(f32 firstX, f32 firstY, f32 secondX, f32 secondY, f32 xBoundA, f32 yBoundA, f32 xBoundB,
                              f32 yBoundB, f32 spanStartX, f32 spanEndX, f32 spanEndY, f32 spanStartY, void *center) {
    f32 horizontalSpan;
    f32 verticalSpan;
    f32 scanYOrSlope;
    f32 scanX;
    f32 stepX;
    f32 stepY;
    f32 upperYLimit;
    f32 maximumX;
    f32 minimumY;
    f32 maximumY;
    f32 horizontalLimitOrIntercept;
    f32 minimumX;
    s32 index;
    u16 rowMask;
    u16 columnMask;
    u16 helperMask;
    u16 boundsMask;

    rowMask = 0;
    columnMask = 0;
    horizontalSpan = spanEndX - spanStartX;
    verticalSpan = spanEndY - spanStartY;

    if (xBoundA < xBoundB) {
        minimumX = xBoundA;
        maximumX = xBoundB;
    } else {
        minimumX = xBoundB;
        maximumX = xBoundA;
    }

    if (yBoundA < yBoundB) {
        minimumY = yBoundA;
        maximumY = yBoundB;
    } else {
        minimumY = yBoundB;
        maximumY = yBoundA;
    }

    stepX = 0.25f * horizontalSpan;
    horizontalLimitOrIntercept = 2.0f * stepX;
    scanX = -stepX;

    stepY = 0.25f * verticalSpan;
    scanYOrSlope = -stepY;

    for (index = 0; (scanX <= horizontalLimitOrIntercept) && (index < 4); index++) {
        if ((minimumX <= scanX) && ((scanX - stepX) <= maximumX)) {
            columnMask |= 0x8888 >> index;
        }
        scanX += stepX;
    }
    upperYLimit = 2.0f * stepY;

    for (index = 0; (scanYOrSlope <= upperYLimit) && (index < 4); index++) {
        if ((minimumY <= scanYOrSlope) && ((scanYOrSlope - stepY) <= maximumY)) {
            rowMask |= 0xF000 >> (index * 4);
        }
        scanYOrSlope += stepY;
    }
    /* The completed scan values are reused for the line slope/intercept. */
    if (secondX != firstX) {
        scanYOrSlope = (secondY - firstY) / (secondX - firstX);
        horizontalLimitOrIntercept = secondY - (scanYOrSlope * secondX);
    } else {
        scanYOrSlope = D_uvterra_rom_0040D6E8;
        horizontalLimitOrIntercept = secondX;
    }

    boundsMask = rowMask & columnMask;
    helperMask = func_uvterra_rom_0040BF74(horizontalSpan, verticalSpan, center, scanYOrSlope, horizontalLimitOrIntercept);

    return boundsMask & helperMask;
}
#line 564 "src/modules/uvterra_rom.c"
#line 557 "src/modules/uvterra_rom.c"

#line 558 "src/modules/uvterra_rom.c"
/* Intersect the two wrapped-index masks at the rectangle's computed grid cell.
 * Retain the native reciprocal expressions and the grid-X-only rejection.
 * RE_UNKNOWN: nonzero dimensions/scales and caller coordinate domain. The
 * accepted line helper exposes its third 16-bit result through signed storage;
 * the corresponding unsigned view preserves the mask's native bit pattern. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040BF74.s")
#line 585 "src/modules/uvterra_rom.c"
#line 559 "src/modules/uvterra_rom.c"

#line 560 "src/modules/uvterra_rom.c"
/* Allocate and zero the shared array of 100-byte terrain records using the
 * original count. Preserve the original unchecked allocation/count contract. */
void uvTerraAllocateRecordBuffer(void) {
    D_uvterra_rom_0040F774 = _uvMemAllocAlign8(D_uvterra_rom_0040F778 * 0x64);
    uvMemSet(D_uvterra_rom_0040F774, 0, D_uvterra_rom_0040F778 * 0x64);
}
#line 561 "src/modules/uvterra_rom.c"

s32 uvTerraSelectLowestZCandidate(Vec3F *first, Vec3F *second, Vec3F *third, Vec3F *fourth);
void uvTerraProjectEndpointToZPlane(Vec3F *origin, f32 planeZ, Vec3F *endpoint);
#line 1 "uvterra-upstream-projection-context-210560.h"
/* Private consumed view of the existing 100-byte channel projection records.
 * The allocator's stride, point slots, count byte and bounds prefix are observed.
 * RE_UNKNOWN: effective ownership, valid channel/count range and coordinate frame.
 * No canonical header or original DATA/RODATA owner is replaced here. */
typedef struct {
    f32 minimumX, minimumY, minimumZ;
    f32 maximumX, maximumY, maximumZ;
} TerrainProjectionBoundsView;
typedef struct {
    Vec3F points[6];
    u8 pointCount;
    u8 unknown49[3];
    TerrainProjectionBoundsView bounds;
} TerrainProjectionCacheView;
void func_uvterra_rom_0040C50C(ParsedUVTR *, Vec3F *, Vec3F *, Vec3F *, Vec3F *, Vec3F *);
void func_uvterra_rom_0040CA64(Vec3F **, u8 *);
#line 4 "uvterra-upstream-projection-bodies-210562.c"
/* Refresh the six cached bounds from the record's live point-count snapshot.
 * Canonical name: uvTerraUpdateProjectionRecordBounds.
 * RE_ORIGINAL_QUIRK: retain ordered comparisons and the six initial sentinel stores;
 * an empty record keeps those sentinels. RE_UNKNOWN: point capacity and finite-value guarantees. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040C0F8.s")
#line 53 "uvterra-upstream-projection-bodies-210562.c"
#line 563 "src/modules/uvterra_rom.c"

#line 564 "src/modules/uvterra_rom.c"
/* Build channel record X/Y slots at 12-byte strides and count byte0x48
 * within the original100-byte record stride. CHAN property10 supplies six
 * shared points; property2 supplies a matrix. Depending on matrix float0x18,
 * select three points using the proven0..3 lowest-Z result, or pass five
 * point pointers through C50C's in-place Z-plane adjustment and CA64's
 * pointer-list reordering. Preserve shared-point writes and untouched record Z.
 * RE_UNKNOWN: matrix/point frame, complete historical record layout/capacity,
 * valid channel/resource lifetimes and caller guarantees for C50C's unchecked
 * projection arithmetic. Resolve through CHAN producers, C50C/C998/CA64,
 * record-buffer allocation and original record consumers. */
#line 54 "uvterra-upstream-projection-bodies-210562.c"
/* Refresh a channel's projection point list and copy only X/Y into its cache.
 * Canonical name: uvTerraRefreshProjectionPointCache.
 * Preserve the signed absolute-value expression, three/five-point paths, shared
 * endpoint mutations and untouched cached Z fields. No new validity checks. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040C218.s")
#line 130 "uvterra-upstream-projection-bodies-210562.c"
#line 575 "src/modules/uvterra_rom.c"
#line 565 "src/modules/uvterra_rom.c"

#line 566 "src/modules/uvterra_rom.c"
/* Return the index of the first Z value strictly below the running minimum,
 * initialized from the original terrain threshold. Ties, NaNs and no value
 * below the threshold preserve the original comparisons/default index zero. */
s32 uvTerraSelectLowestZCandidate(Vec3F *first, Vec3F *second, Vec3F *third, Vec3F *fourth) {
    f32 minimum = D_uvterra_rom_0040D6F8;
    f32 value = first->z;
    s32 selected = 0;
    if (value < minimum) minimum = value;
    value = second->z;
    if (value < minimum) { minimum = value; selected = 1; }
    value = third->z;
    if (value < minimum) { minimum = value; selected = 2; }
    value = fourth->z;
    if (value < minimum) selected = 3;
    return selected;
}
#line 567 "src/modules/uvterra_rom.c"

#line 568 "src/modules/uvterra_rom.c"
/* Classify four endpoint Z values against the terrain's two Z bounds,
 * then conditionally project endpoints from the shared origin onto a bound.
 * Preserve native all-four/side-count early returns and ordered comparisons;
 * each unordered comparison stays false.
 * Each projection can mutate shared endpoints. Reread subsequent endpoint Z
 * fields after calls while retaining the original bound snapshots.
 * RE_UNKNOWN: point/terrain coordinate convention, valid bound ordering and
 * origin/endpoint domain for the callee's unchecked normalization/division.
 * Resolve through original C218/CHAN point producers and terrain assets before
 * assigning physical clipping semantics or adding degenerate-point handling. */
#line 131 "uvterra-upstream-projection-bodies-210562.c"
/* Classify four endpoints against the terrain Z-bound snapshots, then adjust
 * selected endpoints through the existing accepted Z-plane helper.
 * Canonical name: uvTerraAdjustProjectionEndpointsToBounds.
 * RE_ORIGINAL_QUIRK: retain every ordered/negated comparison, all-four counts,
 * RE_UNKNOWN: aliasing and nonfinite inputs; retain endpoint reloads after earlier calls. */
void uvTerraAdjustProjectionEndpointsToBounds(ParsedUVTR* terrain, Vec3F* origin, Vec3F* first, Vec3F* second, Vec3F* third, Vec3F* fourth) {
    s32 belowCount;
    s32 aboveCount;
    f32 upper;
    f32 lower;

    upper = terrain->unk0.unk14;
    lower = terrain->unk0.unk8;
    belowCount = 0;
    aboveCount = 0;
    if (upper <= first->z) {
        aboveCount = 1;
    } else if (first->z <= lower) {
        belowCount = 1;
    }
    if (upper <= second->z) {
        aboveCount += 1;
    } else if (second->z <= lower) {
        belowCount += 1;
    }
    if (upper <= third->z) {
        aboveCount += 1;
    } else if (third->z <= lower) {
        belowCount += 1;
    }
    if (upper <= fourth->z) {
        aboveCount += 1;
    } else if (fourth->z <= lower) {
        belowCount += 1;
    }
    if (upper < origin->z) {
        if ((!(upper <= first->z) || !(upper <= second->z) || !(upper <= third->z) || !(upper <= fourth->z)) && (belowCount == 4)) {
            if (first->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, first);
            }
            if (second->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, second);
            }
            if (third->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, third);
            }
            if (fourth->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, fourth);
            }
        }
    } else if (origin->z < lower) {
        if ((!(first->z <= lower) || !(second->z <= lower) || !(third->z <= lower) || !(fourth->z <= lower)) && (aboveCount == 4)) {
            if (upper <= first->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, first);
            }
            if (upper <= second->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, second);
            }
            if (upper <= third->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, third);
            }
            if (upper <= fourth->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, fourth);
            }
        }
    } else if ((aboveCount == 0) || (belowCount == 0)) {
        if (aboveCount == 4) {
            if (upper <= first->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, first);
            }
            if (upper <= second->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, second);
            }
            if (upper <= third->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, third);
            }
            if (upper <= fourth->z) {
                uvTerraProjectEndpointToZPlane(origin, upper, fourth);
            }
        } else if (belowCount == 4) {
            if (first->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, first);
            }
            if (second->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, second);
            }
            if (third->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, third);
            }
            if (fourth->z <= lower) {
                uvTerraProjectEndpointToZPlane(origin, lower, fourth);
            }
        }
    }
}
#line 579 "src/modules/uvterra_rom.c"
#line 569 "src/modules/uvterra_rom.c"

#line 570 "src/modules/uvterra_rom.c"
/* Normalize endpoint-minus-origin, then move the endpoint along that direction
 * to the requested Z plane using the original floating-point expression order.
 * RE_UNKNOWN: coordinate-space convention and caller guarantees for nonzero
 * direction.z. Preserve the ignored normalization result, unchecked pointers and
 * sequential endpoint writes; no zero-direction fallback or final Z override. */
void uvTerraProjectEndpointToZPlane(Vec3F *origin, f32 planeZ, Vec3F *endpoint) {
    f32 scale;
    Vec3F direction;

    direction.x = endpoint->x - origin->x;
    direction.y = endpoint->y - origin->y;
    direction.z = endpoint->z - origin->z;
    D_uvterra_rom_0040F748->uvVec3FNormalize(&direction, &direction);
    scale = (planeZ - origin->z) / direction.z;
    endpoint->x = origin->x + direction.x * scale;
    endpoint->y = origin->y + direction.y * scale;
    endpoint->z = origin->z + direction.z * scale;
}
#line 571 "src/modules/uvterra_rom.c"

#line 572 "src/modules/uvterra_rom.c"
/* Order point pointers using the minimum-X seed and repeated least normalized
 * XY direction dot product; stop on returning to the initial pointer, then
 * write the pointer list and byte count. Preserve the prior best index when
 * no candidate direction improves the native threshold.
 * RE_ORIGINAL_QUIRK: even input count zero seeds points[0] and output count one.
 * RE_UNKNOWN: intended geometric guarantee, valid count/capacity and
 * coincident/nonfinite-point caller domain. Native scratch holds five entries;
 * C218 supplies five. Trace original callers and CHAN point producers before
 * claiming a general polygon algorithm or adding degenerate-input behavior.
 * RE_UNKNOWN: historical declarations of native DATA initializers F718/F72C.
 * The routine copies their observed 20-byte pointer and 12-byte vector
 * prefixes. F72C's retained label also contains trailing module/footer words;
 * preserve their storage and resolve object boundaries before migrating DATA.
 * FVEC's original import/export bindings establish normalization at slot 08
 * and the two-coordinate dot product at slot 5C. */
#line 227 "uvterra-upstream-projection-bodies-210562.c"
/* Order the pointer list from its minimum-X seed using normalized XY turns.
 * Canonical name: uvTerraOrderProjectionPointPointers.
 * Preserve the prior best index when no candidate improves, callback order and
 * byte output count. Count zero still seeds points[0] and returns one pointer.
 * RE_UNKNOWN: general geometry/domain guarantees and five-entry scratch capacity.
 * Local aggregate initializers mirror the original 20-byte pointer and 12-byte
 * vector template copies; their complete DATA owner boundaries are not claimed. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040CA64.s")
#line 312 "uvterra-upstream-projection-bodies-210562.c"
#line 588 "src/modules/uvterra_rom.c"
#line 573 "src/modules/uvterra_rom.c"

#line 574 "src/modules/uvterra_rom.c"

/* Test a packed five-bit level selected by the original atan2 quantization.
 * A null table returns one. Otherwise preserve native angle bias/scale,
 * division by 5.625, signed-16 index narrowing, and the separate 15.625 level
 * quantization. Levels at least 32 require the packed value to equal 31;
 * lower levels use the original signed comparison and inverted boolean.
 * RE_UNKNOWN: table extent/angle wrap, sample frame/units and levelInput's
 * valid nonzero/finite conversion domain. The same input divides both atan2
 * operands and determines the threshold. Trace original table builders/callers
 * before assigning physical range semantics or adding normalization/clamps. */
s32 uvTerraTestPackedAngularLevelThreshold(const u8 *packedLevels, f32 sampleX, f32 sampleY, f32 levelInput) {
    s32 packedLevel;
    s32 quantizedLevel;
    s32 passes;

    passes = 0;
    if (packedLevels == NULL) {
        return 1;
    }
    packedLevel = func_uvterra_rom_0040CF98(packedLevels,
        (s16)(s32)(((D_uvterra_rom_0040F75C->uvAtan2F(sampleY / levelInput,
            sampleX / levelInput) + D_uvterra_rom_0040D704)
            * D_uvterra_rom_0040D708) / 5.625f));
    quantizedLevel = (s32)(levelInput / 15.625f);
    if ((s16)quantizedLevel >= 32) {
        if (packedLevel == 31) {
            passes = 1;
        }
    } else {
        passes = (packedLevel >= (s16)quantizedLevel);
    }
    return passes;
}
#line 575 "src/modules/uvterra_rom.c"

#line 576 "src/modules/uvterra_rom.c"

/* Read five most-significant-bit-first packed bits at the caller index.
 * Original offset=index*5 uses signed division/remainder by 8; a straddling value
 * combines two zero-extended bytes. No bounds check appears in this reader.
 * RE_UNKNOWN: table extent, valid nonnegative index range and guarantees for
 * second-byte reads. Trace original allocators/writers and uvTerraTestPackedAngularLevelThreshold and other callers
 * before changing signed arithmetic, wrapping indices or adding validation. */
#line 583 "src/modules/uvterra_rom.c"
/* Read one five-bit field from the packed terrain levels, high bits first.
 * Preserve signed quotient/remainder and the two-byte crossing case. The
 * single-byte shift is the native variable shift reduced to its defined
 * mathematical count, not an out-of-range C shift. RE_UNKNOWN: valid index,
 * multiplication-overflow domain and backing span; callers add no guard here. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040CF98.s")
#line 608 "src/modules/uvterra_rom.c"
#line 584 "src/modules/uvterra_rom.c"
#line 577 "src/modules/uvterra_rom.c"

#line 578 "src/modules/uvterra_rom.c"

/* Create SORT groups for tags 80, 85, 110, 115 and enable option 1 on the first
 * and third returned handles, preserving original creation/call/store order.
 * Original TERR initializer at 0x004002C0 calls this just after importing SORT.
 * RE_ORIGINAL_QUIRK: both actual SORT slot0x14 calls pass only handle,1,1,
 * without the zero option terminator read by original target 0x00400B24.
 * On valid-handle/normal-return paths the first setter leaves a3 holding its
 * group-table-global address. No intervening instruction changes a3; the second
 * setter receives that nonzero unsupplied tag and scans following words for zero.
 * RE_UNKNOWN: allocation/error paths, first-call residual a3, following stack
 * values, live initialization paths and observable impact. Trace callers and
 * runtime before a separate recomp correction; keep original arguments here. */
void uvTerraInitializeSortGroups(void) {
    D_uvterra_rom_0040FBCC = D_uvterra_rom_0040F770->uvSortAllocateGroupForTag(80);
    D_uvterra_rom_0040FBC8 = D_uvterra_rom_0040F770->uvSortAllocateGroupForTag(85);
    D_uvterra_rom_0040FBD4 = D_uvterra_rom_0040F770->uvSortAllocateGroupForTag(110);
    D_uvterra_rom_0040FBD0 = D_uvterra_rom_0040F770->uvSortAllocateGroupForTag(115);
    D_uvterra_rom_0040F770->uvSortSetGroupOptions(D_uvterra_rom_0040FBCC, 1, 1);
    D_uvterra_rom_0040F770->uvSortSetGroupOptions(D_uvterra_rom_0040FBD4, 1, 1);
}
#line 579 "src/modules/uvterra_rom.c"

#line 580 "src/modules/uvterra_rom.c"
/* Choose one of four initialized SORT groups from a channel's terrain
 * tile byte (or the shared threshold when no tile exists), then append the
 * callback/context/key through the actual SORT export0x10.
 * RE_ORIGINAL_QUIRK: subtract each XY origin, truncate the differences and
 * cell sizes to signed integers, then divide; do not replace with floating
 * division before truncation. Upper XY bounds are excluded.
 * RE_UNKNOWN: point/key coordinate units, valid finite conversion/nonzero
 * truncated-cell domain, tile-array extent and meanings of the shared byte,
 * threshold sentinel-1 and alternate group selection. Trace original callers,
 * terrain asset builders and AC9C/AE4C queue/threshold writers. Callback words
 * use the existing SORT API type; complete historical callback contracts
 * require their producers and eventual invocation paths. */
#line 1 "uvterra-full-module-draft-D128"
/* Choose one of four draw queues from cell visibility and append the callback. RE_ORIGINAL_QUIRK: exclusive boundaries and negative-one sentinel. RE_UNKNOWN: callback ownership/capacity; preserve SORT pointer bits. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040D128.s")
#line 54 "uvterra-full-module-draft-D128"
#line 593 "src/modules/uvterra_rom.c"
#line 581 "src/modules/uvterra_rom.c"
