// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stdarg.h"
#include "module.h"
#include "uvasset_types.h"

#define	G_F3DEX_IMMFIRST		-65
#define G_F3DEX_ENDDL			(G_F3DEX_IMMFIRST-7)
#define G_F3DEX_VTX 4

extern UvTexture_Exports *D_uvvattr_rom_004012A0;

void uvVattrUnloadTextureModule(void);
void uvVattrGetPackedVertexAttributes(u32 arg0, u32 arg1, ...);
void uvVattrSetPackedVertexAttributes(u32 arg0, s32 arg1, ...);
s32 uvVattrAnyAttributeMatchesRelation(Vtx_t *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 uvVattrModelUsesVertexWithTextureFilter(ParsedUVMD *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 uvVattrContourUsesVertexWithTextureFilter(ParsedUVCT *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 uvVattrDisplayListLoadsVertexAddress(s32 arg0, Gfx* gdl);
void uvVattrGetTerrainTriangleVertexHandles(s32 arg0, u32 arg1, s32 *arg2, s32 *arg3, s32 *arg4);
s32 func_uvvattr_rom_00400514(s32 capacity, s32 *vertexHandles, s32 flags, ...);

void __entrypoint_func_uvvattr_rom_400000(UvVAttr_Exports *exports);

void __entrypoint_func_uvvattr_rom_400000(UvVAttr_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvVattrUnloadTextureModule = uvVattrUnloadTextureModule;
    exports->uvVattrGetPackedVertexAttributes = uvVattrGetPackedVertexAttributes;
    exports->uvVattrSetPackedVertexAttributes = uvVattrSetPackedVertexAttributes;
    exports->func_uvvattr_rom_00400514 = func_uvvattr_rom_00400514;
    exports->uvVattrGetTerrainTriangleVertexHandles = uvVattrGetTerrainTriangleVertexHandles;
    #ifdef __sgi
    #line 25
    #endif
    D_uvvattr_rom_004012A0 = uvLoadModule('TEXT');
}

#line 38 "src/modules/uvvattr_rom.c"
/* Unconditionally unload the texture dependency through TEXT. RE_UNKNOWN: shared
 * dependency references/lifetime need original loader, registration and teardown callers. */
void uvVattrUnloadTextureModule(void) {
    uvUnloadModule('TEXT');
}
#line 41 "src/modules/uvvattr_rom.c"

#line 42 "src/modules/uvvattr_rom.c"
/* Resolve a packed UVCT/UVMD vertex handle and return selected XYZ,
 * texture-coordinate and color bytes through variadic output pointers, in
 * ascending mask-bit order. RE_UNKNOWN: file/index/output extents need original assets/callers.
 * RE_ORIGINAL_QUIRK: color outputs zero through two use signed-byte pointers,
 * while the final color/alpha output uses an unsigned-byte pointer. */
void uvVattrGetPackedVertexAttributes(u32 vertexHandle, u32 attributeMask, ...) {
    Vtx_t vertex;
    ParsedUVCT *contour;
    ParsedUVMD *model;
    va_list outputs;
    s32 unusedWord;

    va_start(outputs, attributeMask);

    if (vertexHandle & 0x80000000) {
        contour = uvGetLoadedFile('UVCT', (vertexHandle & 0x7FFF0000) >> 16);
        vertex = contour->vtxTable[vertexHandle & 0xFFFF].v;
    } else {
        model = uvGetLoadedFile('UVMD', (vertexHandle & 0x7FFF0000) >> 16);
        vertex = model->vtxTable[vertexHandle & 0xFFFF].v;
    }

    if (attributeMask & 0x001) {
        *va_arg(outputs, s16 *) = vertex.ob[0];
    }
    if (attributeMask & 0x002) {
        *va_arg(outputs, s16 *) = vertex.ob[1];
    }
    if (attributeMask & 0x004) {
        *va_arg(outputs, s16 *) = vertex.ob[2];
    }
    if (attributeMask & 0x008) {
        *va_arg(outputs, s16 *) = vertex.tc[0];
    }
    if (attributeMask & 0x010) {
        *va_arg(outputs, s16 *) = vertex.tc[1];
    }
    if (attributeMask & 0x020) {
        *va_arg(outputs, s8 *) = vertex.cn[0];
    }
    if (attributeMask & 0x040) {
        *va_arg(outputs, s8 *) = vertex.cn[1];
    }
    if (attributeMask & 0x080) {
        *va_arg(outputs, s8 *) = vertex.cn[2];
    }
    if (attributeMask & 0x100) {
        *va_arg(outputs, u8 *) = vertex.cn[3];
    }

    va_end(outputs);
}
#line 89 "src/modules/uvvattr_rom.c"

#line 90 "src/modules/uvvattr_rom.c"
/* Resolve a packed UVCT/UVMD vertex handle and write selected XYZ,
 * texture coordinates and color bytes from variadic signed-word values in
 * ascending mask-bit order. Preserve original narrowing and unchecked access. */
void uvVattrSetPackedVertexAttributes(u32 vertexHandle, s32 attributeMask, ...) {
    ParsedUVCT *contour;
    Vtx_t *vertex;
    ParsedUVMD *model;
    va_list values;

    va_start(values, attributeMask);
    if (vertexHandle & 0x80000000) {
        contour = uvGetLoadedFile('UVCT', (vertexHandle & 0x7FFF0000) >> 16);
        vertex = &contour->vtxTable[vertexHandle & 0xFFFF].v;
    } else {
        model = uvGetLoadedFile('UVMD', (vertexHandle & 0x7FFF0000) >> 16);
        vertex = &model->vtxTable[vertexHandle & 0xFFFF].v;
    }
    if (attributeMask & 1) {
        vertex->ob[0] = va_arg(values, s32);
    }
    if (attributeMask & 2) {
        vertex->ob[1] = va_arg(values, s32);
    }
    if (attributeMask & 4) {
        vertex->ob[2] = va_arg(values, s32);
    }
    if (attributeMask & 8) {
        vertex->tc[0] = va_arg(values, s32);
    }
    if (attributeMask & 0x10) {
        vertex->tc[1] = va_arg(values, s32);
    }
    if (attributeMask & 0x20) {
        vertex->cn[0] = va_arg(values, s32);
    }
    if (attributeMask & 0x40) {
        vertex->cn[1] = va_arg(values, s32);
    }
    if (attributeMask & 0x80) {
        vertex->cn[2] = va_arg(values, s32);
    }
    if (attributeMask & 0x100) {
        vertex->cn[3] = va_arg(values, s32);
    }
}
#line 132 "src/modules/uvvattr_rom.c"

// NON MATCHING
#if 0
s32 func_uvvattr_rom_00400514(s32 arg0, s32 *arg1, s32 arg2, ...) {
    s32 sp214;
    s32 sp210;
    s32 temp_v0;
    s32 sp208;
    s32 temp_s5;
    s32 var_fp;
    s32 sp1FC;
    s32 var_s1;
    s32 var_s3;
    s32 sp174[32];
    s32 spF4[32];
    s32 sp74[32];
    s32 var_s0;
    s32 var_v1;
    ParsedUVCT *temp_v0_2;
    ParsedUVMD *temp_v0_4;
    va_list args;
    va_start(args, arg2);

    sp1FC = 0;
    var_fp = 0;
    sp208 = 0xFFFF;
    if (arg2 & 0xC) {
        sp208 = va_arg(args, s32*);
    }

    while (TRUE) {
        sp214 = va_arg(args, s32);
        if (!sp214) {
            break;
        }
        sp210 = va_arg(args, s32);
        temp_v0 = va_arg(args, s32);
        sp174[var_fp] = sp214;
        spF4[var_fp] = sp210;
        sp74[var_fp] = temp_v0;
        var_fp += 1;
        if (var_fp >= 0x20) {
            var_fp--;
        }
    }

    if (arg2 & 4) {
        var_s0 = sp208;
        var_v1 = sp208;
    } else {
        if (arg2 & 1) {
            var_s0 = 0;
            var_v1 = uvGetFilesCount('UVCT') - 1;
        } else {
            var_s0 = 0;
            var_v1 = -1;
        }

    }

    for (sp214 = var_s0; sp214 <= var_v1; sp214++) {
        temp_v0_2 = uvGetLoadedFile('UVCT', sp214);
        if (temp_v0_2 == NULL) {
            continue;
        }

        for (sp210 = 0; sp210 < temp_v0_2->vtxCount; sp210++) {
            temp_s5 = &temp_v0_2->vtxTable[sp210];
            var_s3 = 0;
            for (var_s1 = 0; var_s1 < var_fp; var_s1++) {
                if (sp174[var_s1] & 0x600) {
                    var_s3 += uvVattrContourUsesVertexWithTextureFilter(temp_v0_2, temp_s5, sp174[var_s1], spF4[var_s1],
                                                       sp74[var_s1]);
                } else {
                    var_s3 +=
                        uvVattrAnyAttributeMatchesRelation(temp_s5, sp174[var_s1], spF4[var_s1], sp74[var_s1]);
                }
            }

            if (var_s3 == var_fp) {
                if (sp1FC >= arg0) {
                    sp1FC--;
                }
                arg1[sp1FC] = (sp214 << 0x10) | 0x80000000 | sp210;
                sp1FC++;
            }

        }
    }

    if (arg2 & 8) {
        var_s0 = sp208;
        var_v1 = sp208;
    } else {
        if (arg2 & 2) {
            var_s0 = 0;
            var_v1 = uvGetFilesCount('UVMD') - 1;
        } else {
            var_s0 = 0;
            var_v1 = -1;
        }
    }

    for (sp214 = var_s0; sp214 <= var_v1; sp214++) {
        temp_v0_4 = uvGetLoadedFile('UVMD', sp214);
        if (temp_v0_4 == NULL) {
            continue;
        }

        for (sp210 = 0; sp210 < temp_v0_4->vtxCount; sp210++) {
            temp_s5 = &temp_v0_4->vtxTable[sp210];
            var_s3 = 0;
            for (var_s1 = 0; var_s1 < var_fp; var_s1++) {
                if (sp174[var_s1] & 0x600) {
                    var_s3 += uvVattrModelUsesVertexWithTextureFilter(temp_v0_4, temp_s5, sp174[var_s1], spF4[var_s1],
                                                         sp74[var_s1]);
                } else {
                    var_s3 += uvVattrAnyAttributeMatchesRelation(temp_s5, sp174[var_s1], spF4[var_s1], sp74[var_s1]);
                }
            }
            if (var_s3 == var_fp) {
                if (sp1FC >= arg0) {
                    sp1FC--;
                }
                arg1[sp1FC] = (sp214 << 0x10) | sp210;
                sp1FC += 1;
            }
        }
    }
    return sp1FC;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvvattr_rom/func_uvvattr_rom_00400514.s")
#endif

#line 267 "src/modules/uvvattr_rom.c"
/* Return true when any selected vertex attribute meets an enabled
 * comparison: mask 1 equality, mask 2 less-than, mask 4 greater-than.
 * Position/texture fields use signed shorts; color fields keep byte promotion.
 * RE_UNKNOWN: color-byte interpretation as RGB versus normal remains asset-defined. */
s32 uvVattrAnyAttributeMatchesRelation(Vtx_t *vertex, s32 attributeMask, s32 relationMask, s32 reference) {
    s16 value;

    if (attributeMask & 1) {
        value = vertex->ob[0];
        if ((relationMask & 2) && (value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 2) {
        value = vertex->ob[1];
        if ((relationMask & 2) && (value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 4) {
        value = vertex->ob[2];
        if ((relationMask & 2) && (value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 8) {
        value = vertex->tc[0];
        if ((relationMask & 2) && (value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 0x10) {
        value = vertex->tc[1];
        if ((relationMask & 2) && (value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 0x20) {
        value = vertex->cn[0];
        if ((relationMask & 2) && ((s32) value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < (s32) value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 0x40) {
        value = vertex->cn[1];
        if ((relationMask & 2) && ((s32) value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < (s32) value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 0x80) {
        value = vertex->cn[2];
        if ((relationMask & 2) && ((s32) value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < (s32) value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    if (attributeMask & 0x100) {
        value = vertex->cn[3];
        if ((relationMask & 2) && ((s32) value < reference)) {
            return 1;
        }
        if ((relationMask & 4) && (reference < (s32) value)) {
            return 1;
        }
        if ((relationMask & 1) && (value == reference)) {
            return 1;
        }
    }
    return 0;
}
#line 380 "src/modules/uvvattr_rom.c"

#line 381 "src/modules/uvvattr_rom.c"
/* Search model groups, levels and graphics states for a display list
 * loading the requested vertex address. Apply selected texture-flag and/or
 * texture-ID filters first; selected relations must all pass.
 * Texture ID 4095 is excluded when the texture-flag filter is requested.
 * RE_UNKNOWN: higher-level gameplay meaning of texture flag 0x27 is unproven. */
s32 uvVattrModelUsesVertexWithTextureFilter(ParsedUVMD *model, s32 vertexAddress, s32 filterMask, s32 relationMask, s32 reference) {
    s32 groupIndex;
    s32 levelIndex;
    s32 stateIndex;
    s32 textureId;
    s32 textureFlag;
    ParsedUVMD_1 *group;
    uvModelLOD *level;
    uvGfxState *state;

    for (groupIndex = 0; groupIndex < model->unk4; groupIndex++) {
        group = &model->unk0[groupIndex];
        for (levelIndex = 0; levelIndex < group->unk8; levelIndex++) {
            level = &group->unk0[levelIndex];
            for (stateIndex = 0; stateIndex < level->unk4; stateIndex++) {
                state = &level->stateTable[stateIndex];
                textureId = state->state & 0xFFF;
                if (filterMask & 0x200) {
                    if (textureId == 0xFFF) {
                        continue;
                    }
                    textureFlag = D_uvvattr_rom_004012A0->uvTextureGetLoadedFlag27(textureId);
                    if ((relationMask & 1) && (textureFlag != reference)) {
                        continue;
                    }
                    if ((relationMask & 2) && (reference < textureFlag)) {
                        continue;
                    }
                    if ((relationMask & 4) && (textureFlag < reference)) {
                        continue;
                    }
                }
                if (filterMask & 0x400) {
                    if ((relationMask & 1) && (textureId != reference)) {
                        continue;
                    }
                    if ((relationMask & 2) && (reference < textureId)) {
                        continue;
                    }
                    if ((relationMask & 4) && (textureId < reference)) {
                        continue;
                    }
                }
                if (uvVattrDisplayListLoadsVertexAddress(vertexAddress, state->displayList) != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
#line 432 "src/modules/uvvattr_rom.c"

#line 433 "src/modules/uvvattr_rom.c"
/* Search contour display-list batches for the requested vertex address
 * after applying the original texture-flag and/or texture-ID filters. Preserve
 * sentinel handling, comparison conjunction and first-match return behavior.
 * RE_UNKNOWN: higher-level gameplay meaning of texture flag 0x27 is unproven. */
s32 uvVattrContourUsesVertexWithTextureFilter(ParsedUVCT *contour, s32 vertexAddress, s32 filterMask, s32 relationMask, s32 reference) {
    s32 textureId;
    s32 textureFlag;
    s32 batchIndex;
    s32 unusedWord;
    u16 unusedShort;
    Unk80225FBC_0x28 *batch;

    for (batchIndex = 0; batchIndex < contour->unkC; batchIndex++) {
        batch = &contour->unk8[batchIndex];
        textureId = batch->texture & 0xFFF;
        if (filterMask & 0x200) {
            if (textureId == 0xFFF) {
                continue;
            }
            textureFlag = D_uvvattr_rom_004012A0->uvTextureGetLoadedFlag27(textureId);
            if ((relationMask & 1) && (textureFlag != reference)) {
                continue;
            }
            if ((relationMask & 2) && (reference < textureFlag)) {
                continue;
            }
            if ((relationMask & 4) && (textureFlag < reference)) {
                continue;
            }
        }
        if (filterMask & 0x400) {
            if ((relationMask & 1) && (textureId != reference)) {
                continue;
            }
            if ((relationMask & 2) && (reference < textureId)) {
                continue;
            }
            if ((relationMask & 4) && (textureId < reference)) {
                continue;
            }
        }
        if (uvVattrDisplayListLoadsVertexAddress(vertexAddress, batch->unk8) != 0) {
            return 1;
        }
    }
    return 0;
}
#line 476 "src/modules/uvvattr_rom.c"

#line 477 "src/modules/uvvattr_rom.c"
/* Strip the high address bit and scan until the original end-list opcode
 * for a vertex-load range containing that address. The low sixteen command
 * bits supply the original range span; the upper endpoint is excluded.
 * RE_ORIGINAL_QUIRK: nested display-list calls are not followed by this scan. */
s32 uvVattrDisplayListLoadsVertexAddress(s32 vertexAddress, Gfx* commands) {
    Gfx* unusedCommands;
    u32 rangeStart;
    u32 opcode;
    u32 address;
    u32 commandWord;

    address = (vertexAddress & 0x7FFFFFFF);
    opcode = (u32) (commands->words.w0 & 0xFF000000) >> 0x18;
    while (opcode != (u8)G_F3DEX_ENDDL) {
        commandWord = commands->words.w0;
        rangeStart = commands->words.w1;
        commands++;
        if (opcode == G_F3DEX_VTX) {
            if ((address >= rangeStart) && (address < (rangeStart + (commandWord & 0xFFFF)))) {
                return 1;
            }
        }
        opcode = (u32) (commands->words.w0 & 0xFF000000) >> 0x18;
    }

    return 0;
}
#line 500 "src/modules/uvvattr_rom.c"

#line 501 "src/modules/uvvattr_rom.c"
/* Decode 10-bit tile/batch and 12-bit triangle indices into three
 * packed contour handles. All-ones reference or unloaded terrain
 * leaves outputs untouched. RE_UNKNOWN: remaining index/output bounds
 * and contour-ID width need original assets, producers and callers. */
void uvVattrGetTerrainTriangleVertexHandles(s32 terrainFileId, u32 triangleReference, s32 *firstVertex, s32 *secondVertex, s32 *thirdVertex) {
    ParsedUVTR *terrain;
    Unk80225FBC_0x28_UnkC *triangle;
    s32 contourFileId;
    Unk80225FBC_0x28 *batch;
    uvUnkTileStruct *tile;

    if (triangleReference == (-1U)) {
        return;
    }
    terrain = uvGetLoadedFile('UVTR', terrainFileId);
    if (terrain == 0) {
        return;
    }
    tile = &terrain->unk28[(triangleReference >> 0x16) & 0x3FF];
    batch = &tile->unk40->unk8[(triangleReference >> 0xC) & 0x3FF];
    triangle = &batch->unk18[triangleReference & 0xFFF];
    contourFileId = tile->unk44;
    *firstVertex = (contourFileId << 0x10) | 0x80000000 | triangle->unk0;
    *secondVertex = (contourFileId << 0x10) | 0x80000000 | triangle->unk2;
    *thirdVertex = (contourFileId << 0x10) | 0x80000000 | triangle->unk4;
}
#line 523 "src/modules/uvvattr_rom.c"
