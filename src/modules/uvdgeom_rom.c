// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

#define VERTEX_COUNT_DEFAULT 100

// GEOM descriptor storage view; RE_UNKNOWN: historical outer prefix role.
typedef struct UnkStruct_DGeom_s {
    s32 unk0;
    UvGeom_Rom_0040019C unk4;
} UnkStruct_DGeom;


extern void *D_uvdgeom_rom_00400784;
extern UvGfxMgr_Exports *sGfxMgrExports;
extern Vtx *sVertexArray; // Dynamic array of vertices
extern s16 sVertexCount;
extern s16 D_uvdgeom_rom_00400796;
extern s16 sVertexToggle;
extern s32 sMaxVertexCount;
extern s16 D_uvdgeom_rom_00400798;
extern s16 sFirstPoly;
extern s16 sFirstGrid;
extern s16 sFirstTmesh;
extern s16 sFirstTmesh;
extern UvGeom_Exports *D_uvdgeom_rom_004007B0;

void uvDgeomModuleCleanup(void);
s16 uvVtx(s32 x, s32 y, s32 z, s32 s, s32 t, s32 r, s32 g, s32 b, s32 a);
void uvVtxFlip(u8 flip);
void uvFlipVtx(s32 arg0);
void uvDgeomSetVertexRange(s32 arg0, s32 arg1);
void uvVtxBeginPoly(void);
void uvBeginGrid(void);
void uvBeginTmesh(void);
void uvDgeomEndTriangleMesh(void);
void uvDgeomEndGrid(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvVtxEndPoly(void);
s16 uvVtxDup(s32 x, s32 y, s32 z, s32 s, s32 t, s32 r, s32 g, s32 b, s32 a);
void __entrypoint_func_uvdgeom_rom_400000(UvDGeom_Rom_Exports *exports);

extern f32 D_uvdgeom_rom_0040079C;
extern f32 D_uvdgeom_rom_004007A0;
extern s8 D_uvdgeom_rom_004007A4;
extern UvCback_Exports *D_uvdgeom_rom_004007AC;
extern void *sVertexDataPtrs[2];

void __entrypoint_func_uvdgeom_rom_400000(UvDGeom_Rom_Exports *exports) {
    s32 vertexCount;
    s32 *vertexCountPtr;

    uvUpdateFileAllocPtr(exports);
    exports->uvDgeomModuleCleanup = uvDgeomModuleCleanup;
    exports->uvVtx = uvVtx;
    exports->uvDgeomSetVertexRange = uvDgeomSetVertexRange;
    exports->uvVtxBeginPoly = uvVtxBeginPoly;
    exports->uvBeginGrid = uvBeginGrid;
    exports->uvBeginTmesh = uvBeginTmesh;
    exports->uvDgeomEndTriangleMesh = uvDgeomEndTriangleMesh;
    exports->uvDgeomEndGrid = uvDgeomEndGrid;
    exports->uvVtxEndPoly = uvVtxEndPoly;
    exports->uvVtxDup = uvVtxDup;
    vertexCountPtr = uvGetSystemProp(SYSTEM_PROPID_VERTEX_COUNT);
    if (vertexCountPtr == NULL) {
        sMaxVertexCount = VERTEX_COUNT_DEFAULT;
    } else {
        vertexCount = *vertexCountPtr;
        if (vertexCount != 0) {
            sMaxVertexCount = vertexCount;
        } else {
            sMaxVertexCount = VERTEX_COUNT_DEFAULT;
        }
    }
    sVertexDataPtrs[0] = _uvMemAlloc(sMaxVertexCount * sizeof(Vtx), 0x10);
    sVertexDataPtrs[1] = _uvMemAlloc(sMaxVertexCount * sizeof(Vtx), 0x10);

    uvMemSet(sVertexDataPtrs[0], 0U, sMaxVertexCount * sizeof(Vtx));
    uvMemSet(sVertexDataPtrs[1], 0U, sMaxVertexCount * sizeof(Vtx));
    sVertexToggle = 0;
    sVertexArray = sVertexDataPtrs[sVertexToggle];
    sVertexCount = 0;
    D_uvdgeom_rom_00400798 = -1;
    D_uvdgeom_rom_00400796 = D_uvdgeom_rom_00400798;
    D_uvdgeom_rom_0040079C = 1.0f;
    D_uvdgeom_rom_004007A0 = 1.0f;
    D_uvdgeom_rom_004007A4 = 0;
    D_uvdgeom_rom_004007B0 = uvLoadModule('GEOM');
    D_uvdgeom_rom_004007AC = uvLoadModule('CBCK');
    sGfxMgrExports = uvLoadModule('GMGR');
    D_uvdgeom_rom_004007AC->uvAddCallback(sGfxMgrExports->uvGfxGetCallbackList(1), uvFlipVtx, 0, 0);
}

#line 93 "src/modules/uvdgeom_rom.c"
/* Free both vertex buffers and unload geometry, callback and graphics modules. */
void uvDgeomModuleCleanup(void) {
    _uvMemFree(sVertexDataPtrs[0]);
    _uvMemFree(sVertexDataPtrs[1]);
    uvUnloadModule('GEOM');
    uvUnloadModule('CBCK');
    uvUnloadModule('GMGR');
}
#line 100 "src/modules/uvdgeom_rom.c"

/* Preserve the original signed limit < count rejection: equality reaches
 * the indexed stores, with repeated count/base reloads and 16-bit count update.
 * RE_ORIGINAL_QUIRK: there is no equality or negative-count rejection here.
 * RE_UNKNOWN: allocated extent and caller prevention of limit/negative/wrapped
 * counts require original allocation/settings and append/reset callers;
 * no reachable overrun or intended limit convention has been established. */
#line 101 "src/modules/uvdgeom_rom.c"
s16 uvVtx(s32 x, s32 y, s32 z, s32 s, s32 t, s32 r, s32 g, s32 b, s32 a) {
    if (sMaxVertexCount < sVertexCount) {
        return sVertexCount;
    }
    sVertexArray[sVertexCount].v.ob[0] = x;
    sVertexArray[sVertexCount].v.ob[1] = y;
    sVertexArray[sVertexCount].v.ob[2] = z;
    sVertexArray[sVertexCount].v.tc[0] = s;
    sVertexArray[sVertexCount].v.tc[1] = t;
    sVertexArray[sVertexCount].v.cn[0] = r;
    sVertexArray[sVertexCount].v.cn[1] = g;
    sVertexArray[sVertexCount].v.cn[2] = b;
    sVertexArray[sVertexCount].v.cn[3] = a;
    sVertexCount++;
    D_uvdgeom_rom_00400796 = -1;
    return sVertexCount - 1;
}

void uvVtxFlip(u8 flip) {
    sVertexCount = 0;
    if (flip) {
        sVertexToggle ^= 1;
        sVertexArray = (&sVertexDataPtrs[0])[sVertexToggle];
    }
}

void uvFlipVtx(s32 arg0) {
    uvVtxFlip(TRUE);
}

#line 131 "src/modules/uvdgeom_rom.c"
/* Store the requested first vertex and exclusive end as signed halfwords,
 * preserving the original narrowing and unchecked range. */
void uvDgeomSetVertexRange(s32 first, s32 count) {
    D_uvdgeom_rom_00400796 = first;
    D_uvdgeom_rom_00400798 = first + count;
}
#line 135 "src/modules/uvdgeom_rom.c"

void uvVtxBeginPoly(void) {
    sFirstPoly = sVertexCount;
}

void uvBeginGrid(void) {
    sFirstGrid = sVertexCount;
}

void uvBeginTmesh(void) {
    sFirstTmesh = sVertexCount;
}

#line 148 "src/modules/uvdgeom_rom.c"
/* Submit the current triangle-mesh vertex range, honoring the stored override. RE_UNKNOWN:
 * first/end indices, vertex/descriptor extent and cursor lifetime need original producers/callers. */
void uvDgeomEndTriangleMesh(void) {
    s32 pad[1]; // unused members from UvGeom_Rom_0040019C?
    UvGeom_Rom_0040019C mesh;
    Gfx **gdl;
    s16 endVertex;

    gdl = sGfxMgrExports->uvGetDisplayListHead();
    endVertex = sVertexCount;
    if (D_uvdgeom_rom_00400796 != -1) {
        sFirstTmesh = D_uvdgeom_rom_00400796;
        endVertex = D_uvdgeom_rom_00400798;
    }
    D_uvdgeom_rom_004007B0->uvEndTmesh(endVertex - sFirstTmesh,
                                 &sVertexArray[sFirstTmesh], &mesh, gdl);
}
#line 163 "src/modules/uvdgeom_rom.c"

#line 164 "src/modules/uvdgeom_rom.c"
#line 164 "src/modules/uvdgeom_rom.c"

/* Submit the current grid range and four supplied words, honoring the override.
 * Original GEOM slot 0x08 initializes the inner 20-byte descriptor before its
 * own reads, or returns at its minimum-dimension gate without reading it.
 * RE_UNKNOWN: the inherited outer prefix and pad roles, valid grid/range
 * domains, vertex extent and display-list capacity/alias/lifetime guarantees
 * need original local-storage evidence, range producers and drawing callers. */
#line 166 "src/modules/uvdgeom_rom.c"
void uvDgeomEndGrid(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 pad[1]; // RE_UNKNOWN: inherited local storage role; retain until original layout is proved.
    UnkStruct_DGeom descriptorStorage;
    Gfx **displayListHead;
    s16 endVertex;

    displayListHead = sGfxMgrExports->uvGetDisplayListHead();
    endVertex = sVertexCount;
    if (D_uvdgeom_rom_00400796 != -1) {
        sFirstGrid = D_uvdgeom_rom_00400796;
        endVertex = D_uvdgeom_rom_00400798;
    }
    D_uvdgeom_rom_004007B0->uvEndGrid(arg0, arg1, arg2, arg3, endVertex - sFirstGrid,
                                 &sVertexArray[sFirstGrid], &descriptorStorage.unk4, displayListHead);
}
#line 181 "src/modules/uvdgeom_rom.c"
#line 179 "src/modules/uvdgeom_rom.c"

#line 180 "src/modules/uvdgeom_rom.c"

/* Submit the current polygon range, honoring the stored range override.
 * Original GEOM slot 0x14 returns for count < 3 without reading the descriptor;
 * otherwise it initializes the inner 20 bytes before its descriptor read.
 * RE_UNKNOWN: the inherited outer prefix and pad roles, valid vertex ranges
 * and display-list capacity/alias/lifetime guarantees need original local
 * storage evidence, range producers and drawing callers. */
#line 181 "src/modules/uvdgeom_rom.c"
void uvVtxEndPoly(void) {
    s32 pad[1]; // RE_UNKNOWN: inherited local storage role; retain until original layout is proved.
    UnkStruct_DGeom descriptorStorage;
    Gfx **displayListHead;
    s16 endVertex;

    displayListHead = sGfxMgrExports->uvGetDisplayListHead();
    endVertex = sVertexCount;
    if (D_uvdgeom_rom_00400796 != -1) {
        sFirstPoly = D_uvdgeom_rom_00400796;
        endVertex = D_uvdgeom_rom_00400798;
    }
    D_uvdgeom_rom_004007B0->uvVtxEndPolyInternal(endVertex - sFirstPoly,
                                  &sVertexArray[sFirstPoly], &descriptorStorage.unk4, displayListHead);
}
#line 196 "src/modules/uvdgeom_rom.c"

/* The native instruction bytes match uvVtx. Preserve the original signed limit < count rejection: equality reaches
 * the indexed stores, with repeated count/base reloads and 16-bit count update.
 * RE_ORIGINAL_QUIRK: there is no equality or negative-count rejection here.
 * RE_UNKNOWN: allocated extent and caller prevention of limit/negative/wrapped
 * counts require original allocation/settings and append/reset callers;
 * no reachable overrun or intended limit convention has been established. */
#line 198 "src/modules/uvdgeom_rom.c"
s16 uvVtxDup(s32 x, s32 y, s32 z, s32 s, s32 t, s32 r, s32 g, s32 b, s32 a) {
    if (sMaxVertexCount < sVertexCount) {
        return sVertexCount;
    }
    sVertexArray[sVertexCount].v.ob[0] = x;
    sVertexArray[sVertexCount].v.ob[1] = y;
    sVertexArray[sVertexCount].v.ob[2] = z;
    sVertexArray[sVertexCount].v.tc[0] = s;
    sVertexArray[sVertexCount].v.tc[1] = t;
    sVertexArray[sVertexCount].v.cn[0] = r;
    sVertexArray[sVertexCount].v.cn[1] = g;
    sVertexArray[sVertexCount].v.cn[2] = b;
    sVertexArray[sVertexCount].v.cn[3] = a;
    sVertexCount++;
    D_uvdgeom_rom_00400796 = -1;
    return sVertexCount - 1;
}
