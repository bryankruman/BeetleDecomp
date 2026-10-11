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

/*
 * Publish ten dynamic-geometry exports and choose the vertex capacity from
 * system property 14, using 100 when the property is absent or its word is zero.
 * Allocate and zero two capacity-times-16-byte buffers, select buffer zero,
 * clear the count, set both range overrides to -1 and two shared floats to 1.
 * Load GEOM, CBCK and GMGR in that order, then register uvFlipVtx on list 1.
 * RE_ORIGINAL_QUIRK: Any nonzero signed capacity is retained; no allocation
 * failure or multiplication-range check is introduced.
 * RE_UNKNOWN: Settings lifetime, valid capacity domain, allocation success,
 * export storage extent and callback teardown ordering require loader proof.
 */
#line 48 "src/modules/uvdgeom_rom.c"
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
/*
 * Append one vertex to the current buffer: narrow position and texture
 * coordinates to halfwords and RGBA components to bytes, then increment the
 * signed halfword count, clear the first-vertex override to -1 and return
 * the previous index through the original signed-halfword conversion.
 * RE_ORIGINAL_QUIRK: Reject only capacity < count and return that count;
 * equality and negative counts reach the stores. Preserve all base/count
 * reloads, narrowing and count-wrap behavior.
 * RE_UNKNOWN: Caller prevention of equal, negative or wrapped indices and
 * buffer lifetime remain unproved; initialization alone supplies no such gate.
 */
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

/*
 * Reset the signed-halfword vertex count on every call. When the incoming
 * byte is nonzero, XOR the buffer selector with one and reload the selected
 * buffer pointer; zero leaves the selector and pointer unchanged.
 * RE_ORIGINAL_QUIRK: This helper neither clears vertex memory nor resets
 * polygon/grid/mesh markers or range overrides.
 * RE_UNKNOWN: A selector outside the initialized 0/1 domain, buffer lifetime
 * and synchronization with outstanding drawing work require caller proof.
 */
#line 119 "src/modules/uvdgeom_rom.c"
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

/*
 * Snapshot the current signed-halfword vertex count as the polygon start.
 * The polygon-end wrapper later uses this marker unless a range override
 * replaces it; this call does not append, allocate or reset vertices.
 * RE_UNKNOWN: Begin/end ordering, valid count and buffer lifetime remain
 * caller obligations; no range validation is performed here.
 */
#line 136 "src/modules/uvdgeom_rom.c"
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
/*
 * Append the supplied position, texture coordinates and RGBA components
 * using the same complete native instruction sequence as uvVtx. This entry
 * does not read or duplicate an existing vertex despite its inherited name.
 * Narrow coordinates to halfwords and colors to bytes, advance the signed
 * halfword count, clear the first-vertex override and return the prior index.
 * RE_ORIGINAL_QUIRK: The strict capacity < count rejection admits equality
 * and negative indices; retain repeated loads and halfword wrap/narrowing.
 * RE_UNKNOWN: Valid caller indices, capacity convention and buffer lifetime
 * need caller proof; the allocator does not establish those guarantees.
 */
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
