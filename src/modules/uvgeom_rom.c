// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef struct GeometrySettings_s {
    s32 unk0;
    s32 unk4;
} GeometrySettings;

void __entrypoint_func_uvgeom_rom_400000(UvGeom_Exports *exports);
void uvGeomModuleCleanup(void);
void uvGeomFinishOwnedDisplayList(s32 arg0, Gfx **gdlh);
s32 uvGeomInitializeMeshDescriptor(s32 arg0, s32 arg1, UvGeom_Rom_0040019C *arg2, Gfx **arg3);
void uvEndTmesh(s32 arg0, s32 arg1, UvGeom_Rom_0040019C *arg2, Gfx **arg3);
void uvEndGridWide(s16 arg0, s16 arg1, u8 arg2, u8 arg3, s32 arg4, s32 arg5, UvGeom_Rom_0040019C *arg6,
                   Gfx **gdl);
void uvEndGrid(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, UvGeom_Rom_0040019C *arg6,
               Gfx **gdl);
void uvSetFillColor(f32 red, f32 green, f32 blue, f32 alpha);
void uvVtxRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvVtxEndPolyInternal(s32 arg0, s32 arg1, UvGeom_Rom_0040019C *arg2, Gfx **gdl);

// .bss
s32 D_uvgeom_rom_00401750;
UvGfxMgr_Exports *D_uvgeom_rom_00401754;
UvGfxMgr_Exports *D_uvgeom_rom_00401758;
Gfx *D_uvgeom_rom_0040175C;
u16 D_uvgeom_rom_00401760;

// .data
s32 D_uvgeom_rom_00401740[] = { 0x00180000, __entrypoint_func_uvgeom_rom_400000, 0, 0 };

void __entrypoint_func_uvgeom_rom_400000(UvGeom_Exports *exports) {
    GeometrySettings *settings;

    uvUpdateFileAllocPtr(exports);
    exports->uvVtxEndPolyInternal = uvVtxEndPolyInternal;
    exports->uvGeomModuleCleanup = uvGeomModuleCleanup;
    exports->uvEndTmesh = uvEndTmesh;
    exports->uvEndGrid = uvEndGrid;
    exports->uvSetFillColor = uvSetFillColor;
    exports->uvVtxRect = uvVtxRect;
    settings = uvGetSystemProp(SYSTEM_PROPID_GEOMETRY_SETTINGS);
    if (settings == NULL) {
        D_uvgeom_rom_00401750 = 0x3E8;
        D_uvgeom_rom_00401754 = NULL;
    } else {
        if (settings->unk0 != 0) {
            D_uvgeom_rom_00401750 = settings->unk0;
        } else {
            D_uvgeom_rom_00401750 = 0x3E8;
        }
        D_uvgeom_rom_00401754 = settings->unk4;
    }
    if (D_uvgeom_rom_00401754 == NULL) {
        D_uvgeom_rom_00401754 = _uvMemAlloc(D_uvgeom_rom_00401750 * 8, 0x10U);
        D_uvgeom_rom_00401760 |= 1;
    }
    D_uvgeom_rom_0040175C = (Gfx *) D_uvgeom_rom_00401754;
    D_uvgeom_rom_00401758 = uvLoadModule('GMGR');
}

#line 63 "src/modules/uvgeom_rom.c"
/* Unload the graphics manager and free the display-list buffer only when
 * the original ownership flag is set. */
void uvGeomModuleCleanup(void) {
    uvUnloadModule('GMGR');
    if (D_uvgeom_rom_00401760 & 1) {
        _uvMemFree(D_uvgeom_rom_00401754);
    }
}
#line 69 "src/modules/uvgeom_rom.c"

#line 70 "src/modules/uvgeom_rom.c"
/* For mode zero, append the end-display-list command and retain the new
 * shared cursor. Other modes leave the supplied cursor untouched. */
void uvGeomFinishOwnedDisplayList(s32 mode, Gfx **gdlh) {
    if (mode == 0) {
        gSPEndDisplayList(gdlh[0]++);
        D_uvgeom_rom_0040175C = *gdlh;
    }
}
#line 76 "src/modules/uvgeom_rom.c"

#line 77 "src/modules/uvgeom_rom.c"
/* Use the shared display-list cursor when the caller supplies null, then
 * initialize the original mesh descriptor fields. Return zero for shared
 * storage and one for a caller-supplied cursor. */
s32 uvGeomInitializeMeshDescriptor(s32 kind, s32 value, UvGeom_Rom_0040019C *mesh, Gfx **displayList) {
    s32 callerOwned;

    if (*displayList == NULL) {
        *displayList = D_uvgeom_rom_0040175C;
        callerOwned = 0;
    } else {
        callerOwned = 1;
    }
    mesh->unk4 = 0x160FFF;
    mesh->unk10 = 0;
    mesh->unk12 = 0;
    mesh->unkC = -1;
    mesh->unkE = kind;
    mesh->unk0 = value;
    mesh->unk8 = *displayList;
    return callerOwned;
}
#line 95 "src/modules/uvgeom_rom.c"

void uvEndTmesh(s32 arg0, s32 arg1, UvGeom_Rom_0040019C *arg2, Gfx **arg3) {
    s16 var_a2;
    s16 i;
    s16 var_t0;
    s16 sp20;
    Vtx *var_t2;

    if (arg0 < 3) {
        return;
    }

    var_t0 = FALSE;
    sp20 = uvGeomInitializeMeshDescriptor(arg0, arg1, arg2, arg3);
    var_t2 = arg2->unk0;
    while (arg0 >= 3) {
        if (arg0 < 16) {
            var_a2 = arg0;
        } else {
            var_a2 = 16;
        }

        arg2->unk10 += var_a2;

        gSPVertex(arg3[0]++, OS_PHYSICAL_TO_K0(var_t2), var_a2, 0);
        var_a2 -= 2;
        arg0 -= var_a2;
        var_t2 += var_a2;

        for (i = 0; i < var_a2; i++) {
            arg2->unk12++;
            if (var_t0) {
                gSP1Triangle(arg3[0]++, i, i + 2, i + 1, 0);
            } else {
                gSP1Triangle(arg3[0]++, i, i + 1, i + 2, 0);
            }
            var_t0 ^= TRUE;
        }
    }
    uvGeomFinishOwnedDisplayList((s32) sp20, arg3);
}

/* Emit alternating vertices from adjacent rows through the original modulo-16
 * slots, retaining each cursor reload and optional first-column repetition.
 * The third byte is tested for nonzero; the fourth byte adds its full value to
 * the row-pair bound, so preserve that addition rather than normalizing it.
 * RE_UNKNOWN: valid signed dimensions/closure values, vertex-address spans,
 * output capacity and alias/lifetime domains require original range/parameter
 * producers, drawing callers and display-list consumers. */
#line 137 "src/modules/uvgeom_rom.c"
void uvEndGridWide(s16 rowVertexCount, s16 rowCount, u8 columnClosureValue, u8 extraRowPairCount, s32 descriptorHalfwordInput, s32 vertexAddressWord, UvGeom_Rom_0040019C *mesh,
                   Gfx **displayListHead) {
    s32 earlierSlot;
    s32 unusedWord;
    s32 emittedVertexCount;
    s32 interleavedVertexIndex;
    Vtx *nextRow;
    Vtx *currentRow;
    Vtx *firstRow;
    s32 rowPairIndex;
    s32 useCurrentRow;
    s32 previousSlot;
    s32 currentSlot;
    s32 displayListMode;

    currentSlot = 0;
    previousSlot = 0;
    emittedVertexCount = 0;
    displayListMode = uvGeomInitializeMeshDescriptor(descriptorHalfwordInput, vertexAddressWord, mesh, displayListHead);
    firstRow = currentRow = mesh->unk0;

    for (rowPairIndex = 0; rowPairIndex < (rowCount + extraRowPairCount) - 1; rowPairIndex++) {
        useCurrentRow = 1;
        if (rowCount == rowPairIndex + 1) {
            nextRow = firstRow;
        } else {
            nextRow = rowVertexCount + currentRow;
        }

        for (interleavedVertexIndex = 0; interleavedVertexIndex < rowVertexCount * 2; interleavedVertexIndex++) {
            if (useCurrentRow) {
                earlierSlot = previousSlot;
                previousSlot = currentSlot;
                currentSlot = emittedVertexCount % 16;

                gSPVertex(displayListHead[0]++, (interleavedVertexIndex / 2) + (Vtx *) OS_PHYSICAL_TO_K0(currentRow), 1, currentSlot);
                emittedVertexCount++;
                if (interleavedVertexIndex >= 2) {
                    gSP1Triangle(displayListHead[0]++, earlierSlot, previousSlot, currentSlot, 0);
                }
            } else {
                earlierSlot = previousSlot;
                previousSlot = currentSlot;
                currentSlot = emittedVertexCount % 16;
                gSPVertex(displayListHead[0]++, (interleavedVertexIndex / 2) + (Vtx *) OS_PHYSICAL_TO_K0(nextRow), 1, currentSlot);
                emittedVertexCount++;
                if (interleavedVertexIndex >= 2) {
                    gSP1Triangle(displayListHead[0]++, earlierSlot, currentSlot, previousSlot, 0);
                }
            }
            useCurrentRow ^= 1;
        }
        if (columnClosureValue) {
            earlierSlot = previousSlot;
            previousSlot = currentSlot;
            currentSlot = emittedVertexCount % 16;
            gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(currentRow), 1, currentSlot);
            emittedVertexCount++;
            gSP1Triangle(displayListHead[0]++, earlierSlot, previousSlot, currentSlot, 0);

            earlierSlot = previousSlot;
            previousSlot = currentSlot;
            currentSlot = emittedVertexCount % 16;
            gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(nextRow), 1, currentSlot);
            emittedVertexCount++;
            gSP1Triangle(displayListHead[0]++, earlierSlot, currentSlot, previousSlot, 0);
        }
        currentRow += rowVertexCount;
    }
    uvGeomFinishOwnedDisplayList(displayListMode, displayListHead);
}
#line 208 "src/modules/uvgeom_rom.c"

/* Select dimensions using the original full-word comparison, then preserve
 * the signed-halfword narrowing, vertex-bank alternation and closure tests.
 * The wide path narrows the forwarded closure values to bytes; keep both
 * representations and the original unused local storage.
 * RE_UNKNOWN: valid dimensions/closure values, inherited pad role, vertex
 * spans and output capacity/alias/lifetime guarantees require original grid
 * callers, local-layout evidence and display-list consumers. */
#line 209 "src/modules/uvgeom_rom.c"
void uvEndGrid(s32 dimension0, s32 dimension1, s32 dimension0ClosureWord, s32 dimension1ClosureWord, s32 descriptorHalfwordInput, s32 vertexAddressWord, UvGeom_Rom_0040019C *mesh,
               Gfx **displayListHead) {
    s32 rowIndex;
    s32 columnIndex;
    s16 rowCount;
    s16 rowVertexCount;
    s16 columnClosureValue;
    s16 rowClosureValue;
    s16 activeVertexBank;
    Vtx *firstRow;
    Vtx *currentRow;
    s16 vertexBankStarts[2];
    s16 displayListMode;
    s32 pad;

    // clang-format off
    if (dimension1 < dimension0) {
        rowVertexCount = dimension1;\
        rowCount = dimension0;\
        columnClosureValue = dimension1ClosureWord;\
        rowClosureValue = dimension0ClosureWord;
    } else {
        rowVertexCount = dimension0;\
        rowCount = dimension1;\
        columnClosureValue = dimension0ClosureWord;\
        rowClosureValue = dimension1ClosureWord;
    }
    // clang-format on

    if (rowVertexCount >= 9) {
        uvEndGridWide(rowVertexCount, rowCount, rowClosureValue, columnClosureValue, descriptorHalfwordInput, vertexAddressWord, mesh, displayListHead);
        return;
    }

    if (rowCount < 2) {
        return;
    }

    displayListMode = uvGeomInitializeMeshDescriptor(descriptorHalfwordInput, vertexAddressWord, mesh, displayListHead);
    firstRow = mesh->unk0;
    vertexBankStarts[0] = 0;
    vertexBankStarts[1] = rowVertexCount;

    gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(firstRow), rowVertexCount, vertexBankStarts[0]);

    currentRow = (Vtx *) firstRow + rowVertexCount;

    activeVertexBank = 1;
    for (rowIndex = 1; rowIndex < rowCount; rowIndex++) {
        gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(currentRow), rowVertexCount, vertexBankStarts[activeVertexBank]);

        if (activeVertexBank) {
            for (columnIndex = 0; columnIndex < rowVertexCount - 1; columnIndex++) {
                gSP1Triangle(displayListHead[0]++, columnIndex, columnIndex + rowVertexCount, columnIndex + rowVertexCount + 1, 0);
                gSP1Triangle(displayListHead[0]++, columnIndex, columnIndex + rowVertexCount + 1, columnIndex + 1, 0);
            }

            if (columnClosureValue) {
                gSP1Triangle(displayListHead[0]++, columnIndex, columnIndex + rowVertexCount, rowVertexCount, 0);
                gSP1Triangle(displayListHead[0]++, columnIndex, rowVertexCount, 0, 0);
            }
        } else {
            for (columnIndex = 0; columnIndex < rowVertexCount - 1; columnIndex++) {
                gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, columnIndex, columnIndex + 1, 0);
                gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, columnIndex + 1, columnIndex + rowVertexCount + 1, 0);
            }
            if (columnClosureValue) {
                gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, 0, rowVertexCount, 0);
                gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, columnIndex, 0, 0);
            }
        }
        currentRow += rowVertexCount;
        activeVertexBank ^= 1;
    }

    if (rowClosureValue) {
        gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(firstRow), rowVertexCount, vertexBankStarts[0]);

        for (columnIndex = 0; columnIndex < rowVertexCount - 1; columnIndex++) {
            gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, columnIndex, columnIndex + 1, 0);
            gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, columnIndex + 1, columnIndex + rowVertexCount + 1, 0);
        }

        if (columnClosureValue) {
            gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, 0, rowVertexCount, 0);
            gSP1Triangle(displayListHead[0]++, columnIndex + rowVertexCount, columnIndex, 0, 0);
        }
    }
    uvGeomFinishOwnedDisplayList(displayListMode, displayListHead);
}
#line 299 "src/modules/uvgeom_rom.c"

void uvSetFillColor(f32 red, f32 green, f32 blue, f32 alpha) {
    Gfx **gdl;
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    r = red * 255.0f;
    g = green * 255.0f;
    b = blue * 255.0f;
    a = alpha * 255.0f;
    gdl = D_uvgeom_rom_00401758->uvGetDisplayListHead();
    gDPPipeSync(gdl[0]++);
    gDPSetPrimColor(gdl[0]++, 0, 0, r, g, b, a);
    gDPSetFillColor(gdl[0]++, GPACK_RGBA5551(r, g, b, a) << 16 | GPACK_RGBA5551(r, g, b, a));
}

void uvVtxRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Gfx **gdl;

    gdl = D_uvgeom_rom_00401758->uvGetDisplayListHead();
    arg3 = (D_uvgeom_rom_00401758->uvGetScreenHeight() - arg3) - 1;
    arg1 = (D_uvgeom_rom_00401758->uvGetScreenHeight() - arg1) - 1;
    if (arg0 < 0) {
        arg0 = 0;
    } else if (arg0 >= D_uvgeom_rom_00401758->uvGetScreenWidth()) {
        arg0 = D_uvgeom_rom_00401758->uvGetScreenWidth() - 1;
    }
    if (arg2 < 0) {
        arg2 = 0;
    } else if (arg2 >= D_uvgeom_rom_00401758->uvGetScreenWidth()) {
        arg2 = D_uvgeom_rom_00401758->uvGetScreenWidth() - 1;
    }
    if (arg3 < 0) {
        arg3 = 0;
    } else if (arg3 >= D_uvgeom_rom_00401758->uvGetScreenHeight()) {
        arg3 = D_uvgeom_rom_00401758->uvGetScreenHeight() - 1;
    }
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 >= D_uvgeom_rom_00401758->uvGetScreenHeight()) {
        arg1 = D_uvgeom_rom_00401758->uvGetScreenHeight() - 1;
    }
    gDPPipeSync(gdl[0]++);
    gDPSetCycleType(gdl[0]++, G_CYC_FILL);
    gDPSetRenderMode(gdl[0]++, G_RM_PASS, G_RM_NOOP2);
    gDPPipeSync(gdl[0]++);
    gDPFillRectangle(gdl[0]++, arg0, arg3, arg2, arg1);
    gDPPipeSync(gdl[0]++);
    gDPSetCycleType(gdl[0]++, G_CYC_2CYCLE);
}

#line 352 "src/modules/uvgeom_rom.c"

/* Emit polygon triangles in the original batches, retaining the first-batch
 * and later-batch vertex commands and repeated display-list-head reloads.
 * Count < 3 returns before descriptor use; otherwise the native initializer
 * fills the inner 20-byte descriptor before its vertex-address read.
 * RE_UNKNOWN: valid vertex-address/count spans, output capacity, alias/lifetime
 * domains and the historical source declaration of the forwarded 32-bit word
 * require original range producers, drawing callers and descriptor consumers. */
#line 352 "src/modules/uvgeom_rom.c"
void uvVtxEndPolyInternal(s32 remainingVertices, s32 vertexAddressWord, UvGeom_Rom_0040019C *mesh, Gfx **displayListHead) {
    s16 triangleCount;
    s16 displayListMode;
    s16 batchVertexCount;
    s16 triangleIndex;
    s16 firstBatch;
    Vtx *vertices;

    firstBatch = TRUE;
    if (remainingVertices < 3) {
        return;
    }
    displayListMode = uvGeomInitializeMeshDescriptor(remainingVertices, vertexAddressWord, mesh, displayListHead);
    vertices = mesh->unk0;
    while (remainingVertices > 0) {
        if (firstBatch) {
            firstBatch = FALSE;
            if (remainingVertices < 16) {
                batchVertexCount = remainingVertices;
            } else {
                batchVertexCount = 16;
            }
            gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(vertices), batchVertexCount, 0);
            triangleCount = batchVertexCount - 2;
        } else {
            if (remainingVertices >= 15) {
                batchVertexCount = 15;
                gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(vertices), 14, 1);
                gSP1Triangle(displayListHead[0]++, 0, 15, 1, 0);
                gSPVertex(displayListHead[0]++, (((u32) (vertices) + 0x80000000)) + 14 * sizeof(Vtx), 1, 15);
            } else {
                batchVertexCount = remainingVertices;
                gSPVertex(displayListHead[0]++, OS_PHYSICAL_TO_K0(vertices), batchVertexCount, 1);
                gSP1Triangle(displayListHead[0]++, 0, 15, 1, 0);
            }
            triangleCount = batchVertexCount - 1;
        }
        vertices += batchVertexCount;
        remainingVertices -= batchVertexCount;
        for (triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++) {
            gSP1Triangle(displayListHead[0]++, 0, triangleIndex + 1, triangleIndex + 2, 0);
        }
    }
    uvGeomFinishOwnedDisplayList((s32) displayListMode, displayListHead);
}
#line 397 "src/modules/uvgeom_rom.c"