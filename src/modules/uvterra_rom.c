// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 prefix[4]; void (*get)(s32, ...); } TerrainChannelListExports;
extern void *D_uvterra_rom_0040F760;
void func_uvterra_rom_0040078C(s32);
void func_uvterra_rom_0040AC9C(s32);
void func_uvterra_rom_0040AE4C(s32);
#include "module.h"
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/__entrypoint_func_uvterra_rom_400000.s")

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
    D_uvterra_rom_0040F764->uvAddCallback(callbacks, func_uvterra_rom_0040AE4C, NULL, 0x64);
}
#line 73 "src/modules/uvterra_rom.c"

#line 74 "src/modules/uvterra_rom.c"
/* Store a loaded terrain ID for the caller-selected channel, or 65535
 * for either invalid sentinel or a missing terrain. Channel bounds are caller-owned. */
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
/* Return the terrain ID stored for the caller-selected channel. */
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040078C.s")
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00401284.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00401E64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00402244.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00403464.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040385C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00404E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004060A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00406160.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00406324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00406648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00406C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004071A4.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004072EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004074EC.s")

#line 462 "src/modules/uvterra_rom.c"
/* Store the reciprocal in the caller-indexed terrain scalar array.
 * Original index and nonzero-divisor requirements remain caller-owned. */
void uvTerraSetReciprocalByIndex(s32 index, f32 value)
{
  s32 unusedBase = D_uvterra_rom_0040FBA4;
  *((f32 *) (((u8 *) D_uvterra_rom_0040FBA4) + (index * 4))) = 1.0f / value;
}
#line 467 "src/modules/uvterra_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_004076A8.s")

s32 func_uvterra_rom_00407A80(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    sp0 = arg0;
    sp4 = arg1;
    sp8 = arg2;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00407A94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00407B0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00407E5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00407ED4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00408300.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00408614.s")

#line 494 "src/modules/uvterra_rom.c"
/* Return the static object model ID, or 0xFFFF when its contour is absent. */
u16 uvTerraGetStaticObjectModelId(s32 handle) {
    UnkSobjDraw *record = uvTerraGetStaticObject(handle);
    if (record == NULL) return 0xFFFFU;
    return record->modelId;
}
#line 502 "src/modules/uvterra_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040880C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040888C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00408AD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_00409394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040A08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040A43C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040A79C.s")

#line 517 "src/modules/uvterra_rom.c"
/* Read static-object properties through the original variadic list: one
 * writes the flag word, four writes the model ID, and zero terminates.
 * Unknown properties return immediately; absent objects consume no outputs.
 * The caller supplies valid output pointers and a terminating property. */
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
/* Set the static object's opaque value at offset 0x40 when its contour exists. */
void uvTerraSetStaticObjectValue(s32 handle, s32 value) {
    UnkSobjDraw *record = uvTerraGetStaticObject(handle);
    if (record != NULL) record->unk40 = value;
}
#line 520 "src/modules/uvterra_rom.c"

typedef struct {
    u8 pad0[0x40];
    s32 unk40;
} AutoS_0040ABE0_temp_v0;

#line 527 "src/modules/uvterra_rom.c"
/* Read the opaque value at offset 0x40, or zero when its contour is absent. */
s32 uvTerraGetStaticObjectValue(s32 handle) {
    UnkSobjDraw *record = uvTerraGetStaticObject(handle);
    if (record == NULL) return 0;
    return record->unk40;
}
#line 535 "src/modules/uvterra_rom.c"

#line 536 "src/modules/uvterra_rom.c"
/* Resolve a packed contour/object handle: bits 12..23 select UVCT and
 * bits 0..11 select its static object; bits 24..31 are ignored. Return an address
 * inside the loaded UVCT object array, preserving the original null checks.
 * RE_UNKNOWN: object-index limits and coordination with resource unloading.
 * This helper allocates no object and acquires no visible resource reference;
 * trace UVCT loaders/releases and handle consumers before assigning ownership. */
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
#line 537 "src/modules/uvterra_rom.c"

#line 538 "src/modules/uvterra_rom.c"
/* Return the caller-indexed terrain channel byte without new validation. */
u8 uvTerraGetChannelByte(s32 channel) {
    return D_uvterra_rom_0040F7A0[channel];
}
#line 541 "src/modules/uvterra_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040AC9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040AE4C.s")

#line 546 "src/modules/uvterra_rom.c"
/* Apply FMTX's shared negative translation to the tile matrix and load it
 * as view matrix one. Dispatch each geometry list unless its shared disable
 * flag is set, preserving the two 16-bit masks and list counts, then pop the
 * view matrix. Tiles without geometry do nothing.
 * RE_UNKNOWN: which coordinate origin the shared FMTX translation represents
 * at this call. Trace FMTX export 0x04 setters and their render ordering. */
#line 551 "src/modules/uvterra_rom.c"
void uvTerraDrawTileGeometry(s32 terrainId, uvUnkTileStruct *tile, u16 firstMask, u16 secondMask) {
    Mtx4F matrix;
    if (tile->unk40 != NULL) {
        D_uvterra_rom_0040F744->uvMat4ApplySharedInverseTranslation(&matrix, &tile->unk0);
        D_uvterra_rom_0040F744->uvGfxMtxViewLoad(&matrix, 1);
        if (D_uvterra_rom_0040FBDC == 0) {
            func_uvterra_rom_004072EC(terrainId, firstMask, tile, tile->unk40->unk8, tile->unk40->unkC);
        }
        if (D_uvterra_rom_0040FBD8 == 0) {
            func_uvterra_rom_004076A8(terrainId, tile, firstMask, secondMask, tile->unk40->unk10, tile->unk40->unk14);
        }
        D_uvterra_rom_0040F744->uvGfxMtxFViewPop();
    }
}
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040B26C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040B8C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040BBC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040BD38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040BF74.s")

#line 560 "src/modules/uvterra_rom.c"
/* Allocate and zero the shared array of 100-byte terrain records using the
 * original count. Preserve the original unchecked allocation/count contract. */
void uvTerraAllocateRecordBuffer(void) {
    D_uvterra_rom_0040F774 = _uvMemAllocAlign8(D_uvterra_rom_0040F778 * 0x64);
    uvMemSet(D_uvterra_rom_0040F774, 0, D_uvterra_rom_0040F778 * 0x64);
}
#line 561 "src/modules/uvterra_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040C0F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040C218.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040C50C.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040CA64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040CEA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040CF98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040D050.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterra_rom/func_uvterra_rom_0040D128.s")
