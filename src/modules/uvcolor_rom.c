// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

extern f32 D_uvcolor_rom_00408820;
extern f32 D_uvcolor_rom_00408824;
extern f32 D_uvcolor_rom_00408828;
extern f32 D_uvcolor_rom_0040882C;
extern f32 D_uvcolor_rom_00408830;
extern f32 D_uvcolor_rom_00408834;
extern s32 D_uvcolor_rom_00408810;
extern f32 D_uvcolor_rom_00408838;
extern f32 D_uvcolor_rom_0040883C;
extern f32 D_uvcolor_rom_00408840;
extern f32 D_uvcolor_rom_00408844;
extern f32 D_uvcolor_rom_00408848;
extern f32 D_uvcolor_rom_0040884C;
extern UvGfxMgr_Exports *D_uvcolor_rom_00408850;

void uvColorModuleCleanup(void);
void uvColorApplyStoredChannelTriple(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void uvColorScaleLoadedAssetColors(s32 arg0);
void uvColorSetStoredChannelTriple(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void uvColorTransformLoadedModelVertices(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void uvColorBlendLoadedAssetColors(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void uvColorScaleVertexRgb(Vtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void uvColorScaleVertexHsv(Vtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void uvColorScaleTextureHsv(s32 arg0, s32 arg1, s32 arg2, void *arg3, f32 arg4, f32 arg5, f32 arg6);
void uvColorScaleTextureRgb(s32 arg0, s32 arg1, s32 arg2, void *arg3, f32 arg4, f32 arg5, f32 arg6);
void uvColorBlendVertexRgbByFlag(Vtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7);
void func_uvcolor_rom_00404C54(s32 arg0, s32 arg1, s32 arg2, void *arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7, f32 arg8, f32 arg9);
void uvColorBlendTextureRgb(s32 arg0, s32 arg1, s32 arg2, void *arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7, f32 arg8, f32 arg9);
void uvColorRgbToHsv(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void uvColorHsvToRgb(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5);
void uvColorBlendVertexHsvByFlag(Vtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7);

void __entrypoint_func_uvcolor_rom_400000(UvColor_Exports *exports);

void __entrypoint_func_uvcolor_rom_400000(UvColor_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvColorModuleCleanup = uvColorModuleCleanup;
    exports->uvColorApplyStoredChannelTriple = uvColorApplyStoredChannelTriple;
    exports->uvColorScaleLoadedAssetColors = uvColorScaleLoadedAssetColors;
    exports->uvColorSetStoredChannelTriple = uvColorSetStoredChannelTriple;
    exports->uvColorTransformLoadedModelVertices = uvColorTransformLoadedModelVertices;
    #line 46
    D_uvcolor_rom_00408850 = uvLoadModule('GMGR');
}

#line 55 "src/modules/uvcolor_rom.c"
/* Unload the original graphics-manager dependency. */
void uvColorModuleCleanup(void) {
    uvUnloadModule('GMGR');
}
#line 58 "src/modules/uvcolor_rom.c"

#line 59 "src/modules/uvcolor_rom.c"
/* Apply the stored three-channel values for selector one or the other
 * selector group, together with the supplied triple. The transformation
 * itself remains in the shared color helper. */
void uvColorApplyStoredChannelTriple(s32 selector, f32 x, f32 y, f32 z) {
    if (selector == 1) {
        uvColorBlendLoadedAssetColors(selector, D_uvcolor_rom_0040882C, D_uvcolor_rom_00408830,
                                  D_uvcolor_rom_00408834, x, y, z);
        return;
    }
    uvColorBlendLoadedAssetColors(selector, D_uvcolor_rom_00408820, D_uvcolor_rom_00408824,
                              D_uvcolor_rom_00408828, x, y, z);
}
#line 68 "src/modules/uvcolor_rom.c"

#line 69 "src/modules/uvcolor_rom.c"
/* Scale loaded terrain, model and texture colors using their per-asset
 * weights and the shared RGB or HSV factors. Wait for graphics first
 * and preserve the original format-specific processing order. */
void uvColorScaleLoadedAssetColors(s32 useHsv) {
    f32 textureWeight;
    s32 filesCount;
    f32 firstScale;
    f32 secondScale;
    f32 thirdScale;
    ParsedUVCT *terrain;
    ParsedUVMD *model;
    ParsedUVTX *texture;
    s32 i;

    D_uvcolor_rom_00408850->uvGfxWaitIfRequested();
    filesCount = uvGetFilesCount('UVCT');
    for (i = 0; i < filesCount; i++) {
        terrain = uvGetLoadedFile('UVCT', i);
        if ((terrain != NULL) && (terrain->unk28 != 0.0f)) {
            if (useHsv == 0) {
                firstScale = 1.0f - ((1.0f - D_uvcolor_rom_00408820) * terrain->unk28);
                secondScale = 1.0f - ((1.0f - D_uvcolor_rom_00408824) * terrain->unk28);
                thirdScale = 1.0f - ((1.0f - D_uvcolor_rom_00408828) * terrain->unk28);

                uvColorScaleVertexRgb(terrain->vtxTable, (s32) terrain->vtxCount, firstScale, secondScale, thirdScale);
            } else {
                firstScale = 1.0f - ((1.0f - D_uvcolor_rom_0040882C) * terrain->unk28);
                secondScale = 1.0f - ((1.0f - D_uvcolor_rom_00408830) * terrain->unk28);
                thirdScale = 1.0f - ((1.0f - D_uvcolor_rom_00408834) * terrain->unk28);
                uvColorScaleVertexHsv((s32) terrain->vtxTable, (s32) terrain->vtxCount, firstScale, secondScale,
                                          thirdScale);
            }
        }
    }

    filesCount = uvGetFilesCount('UVMD');
    for (i = 0; i < filesCount; i++) {
        model = uvGetLoadedFile('UVMD', i);
        if ((model != NULL) && (model->unk14 != 0.0f)) {
            if (useHsv == 0) {
                firstScale = 1.0f - ((1.0f - D_uvcolor_rom_00408820) * model->unk14);
                secondScale = 1.0f - ((1.0f - D_uvcolor_rom_00408824) * model->unk14);
                thirdScale = 1.0f - ((1.0f - D_uvcolor_rom_00408828) * model->unk14);
                uvColorScaleVertexRgb(model->vtxTable, (s32) model->vtxCount, firstScale, secondScale, thirdScale);
            } else {
                firstScale = 1.0f - ((1.0f - D_uvcolor_rom_0040882C) * model->unk14);
                secondScale = 1.0f - ((1.0f - D_uvcolor_rom_00408830) * model->unk14);
                thirdScale = 1.0f - ((1.0f - D_uvcolor_rom_00408834) * model->unk14);
                uvColorScaleVertexHsv((s32) model->vtxTable, (s32) model->vtxCount, firstScale, secondScale,
                                          thirdScale);
            }
        }
    }

    filesCount = uvGetFilesCount('UVTX');
    for (i = 0; i < filesCount; i++) {
        texture = uvGetLoadedFile('UVTX', i);
        if ((texture != NULL) && (texture->unk28 != 0.0f)) {
            if (useHsv == 0) {
                firstScale = 1.0f - ((1.0f - D_uvcolor_rom_00408820) * texture->unk28);
                secondScale = 1.0f - ((1.0f - D_uvcolor_rom_00408824) * texture->unk28);
                thirdScale = 1.0f - ((1.0f - D_uvcolor_rom_00408828) * texture->unk28);
                uvColorScaleTextureRgb(texture->unk22, (u8)texture->data.bytes[1], texture->as_u16,
                                          texture->unk2C, firstScale, secondScale, thirdScale);
            } else {
                textureWeight = texture->unk28;
                firstScale = 1.0f - ((1.0f - D_uvcolor_rom_0040882C) * texture->unk28);
                secondScale = 1.0f - ((1.0f - D_uvcolor_rom_00408830) * texture->unk28);
                thirdScale = 1.0f - ((1.0f - D_uvcolor_rom_00408834) * texture->unk28);
                uvColorScaleTextureHsv(texture->unk22, (u8)texture->data.bytes[1], texture->as_u16,
                                          texture->unk2C, firstScale, secondScale, thirdScale);
            }
        }
    }
}
#line 141 "src/modules/uvcolor_rom.c"

#line 142 "src/modules/uvcolor_rom.c"
/* Store the three-channel values in selector group one or the default
 * group. Other selector values intentionally share the default group. */
void uvColorSetStoredChannelTriple(s32 selector, f32 x, f32 y, f32 z) {
    if (selector == 1) {
        D_uvcolor_rom_0040882C = x;
        D_uvcolor_rom_00408830 = y;
        D_uvcolor_rom_00408834 = z;
        return;
    }
    D_uvcolor_rom_00408820 = x;
    D_uvcolor_rom_00408824 = y;
    D_uvcolor_rom_00408828 = z;
}
#line 153 "src/modules/uvcolor_rom.c"

#line 154 "src/modules/uvcolor_rom.c"
/* When the model is already loaded, wait for requested graphics work
 * and apply the original vertex-color transform using the repeated scalar
 * for its final three arguments. Missing models are ignored. */
void uvColorTransformLoadedModelVertices(s32 modelId, f32 x, f32 y, f32 z, f32 scale) {
    ParsedUVMD *model;

    model = uvGetLoadedFile('UVMD', modelId);
    if (model != NULL) {
        D_uvcolor_rom_00408850->uvGfxWaitIfRequested();
        uvColorBlendVertexRgbByFlag(model->vtxTable, (s32) model->vtxCount, x, y, z, scale,
                                  scale, scale);
    }
}
#line 164 "src/modules/uvcolor_rom.c"

#line 165 "src/modules/uvcolor_rom.c"
/* Store the shared target color and per-channel blend amounts, wait for
 * graphics, then blend weighted terrain, model and texture colors in
 * RGB or HSV space using the existing specialized helpers. */
void uvColorBlendLoadedAssetColors(s32 useHsv, f32 targetFirst, f32 targetSecond, f32 targetThird, f32 firstBlendAmount, f32 secondBlendAmount, f32 thirdBlendAmount) {
    f32 secondRetainedWeight;
    f32 thirdRetainedWeight;
    f32 firstRetainedWeight;
    ParsedUVCT *terrain;
    ParsedUVMD *model;
    ParsedUVTX *texture;
    s32 filesCount;
    s32 i;

    D_uvcolor_rom_00408838 = targetFirst;
    D_uvcolor_rom_0040883C = targetSecond;
    D_uvcolor_rom_00408840 = targetThird;
    D_uvcolor_rom_00408844 = firstBlendAmount;
    D_uvcolor_rom_00408848 = secondBlendAmount;
    D_uvcolor_rom_0040884C = thirdBlendAmount;
    D_uvcolor_rom_00408810 = 0;
    D_uvcolor_rom_00408850->uvGfxWaitIfRequested();

    filesCount = uvGetFilesCount('UVCT');
    for (i = 0; i < filesCount; i++) {
        terrain = uvGetLoadedFile('UVCT', i);
        if (terrain != NULL) {
            if (terrain->unk28 != 0.0f) {
                firstRetainedWeight = 1.0f - (terrain->unk28 * firstBlendAmount);
                secondRetainedWeight = 1.0f - (terrain->unk28 * secondBlendAmount);
                thirdRetainedWeight = 1.0f - (terrain->unk28 * thirdBlendAmount);
                if (useHsv == 0) {
                    uvColorBlendVertexRgbByFlag(terrain->vtxTable, (s32) terrain->vtxCount, targetFirst, targetSecond, targetThird,
                                              firstRetainedWeight, secondRetainedWeight, thirdRetainedWeight);
                } else {
                    uvColorBlendVertexHsvByFlag(terrain->vtxTable, (s32) terrain->vtxCount, targetFirst, targetSecond, targetThird,
                                              firstRetainedWeight, secondRetainedWeight, thirdRetainedWeight);
                }
            }
        }
    }

    filesCount = uvGetFilesCount('UVMD');
    for (i = 0; i < filesCount; i++) {
        model = uvGetLoadedFile('UVMD', i);
        if (model != NULL) {
            if (model->unk14 != 0.0f) {
                firstRetainedWeight = 1.0f - (model->unk14 * firstBlendAmount);
                secondRetainedWeight = 1.0f - (model->unk14 * secondBlendAmount);
                thirdRetainedWeight = 1.0f - (model->unk14 * thirdBlendAmount);
                if (useHsv == 0) {
                    uvColorBlendVertexRgbByFlag(model->vtxTable, (s32) model->vtxCount, targetFirst, targetSecond, targetThird,
                                              firstRetainedWeight, secondRetainedWeight, thirdRetainedWeight);
                } else {
                    uvColorBlendVertexHsvByFlag(model->vtxTable, (s32) model->vtxCount, targetFirst, targetSecond, targetThird,
                                              firstRetainedWeight, secondRetainedWeight, thirdRetainedWeight);
                }
            }
        }
    }

    filesCount = uvGetFilesCount('UVTX');
    for (i = 0; i < filesCount; i++) {
        texture = uvGetLoadedFile('UVTX', i);
        if (texture != NULL) {
            if (texture->unk28 != 0.0f) {
                firstRetainedWeight = 1.0f - (texture->unk28 * firstBlendAmount);
                secondRetainedWeight = 1.0f - (texture->unk28 * secondBlendAmount);
                thirdRetainedWeight = 1.0f - (texture->unk28 * thirdBlendAmount);
                if (useHsv == 0) {
                    uvColorBlendTextureRgb((s32) texture->unk22, (s32) texture->data.bytes[1], (s32) texture->as_u16,
                                              texture->unk2C, targetFirst, targetSecond, targetThird, firstRetainedWeight, secondRetainedWeight,
                                              thirdRetainedWeight);
                } else {
                    func_uvcolor_rom_00404C54((s32) texture->unk22, (s32) texture->data.bytes[1], (s32) texture->as_u16,
                                              texture->unk2C, targetFirst, targetSecond, targetThird, firstRetainedWeight, secondRetainedWeight,
                                              thirdRetainedWeight);
                }
            }
        }
    }
}
#line 243 "src/modules/uvcolor_rom.c"

#line 244 "src/modules/uvcolor_rom.c"
/* Scale vertex RGB bytes, using a linear factor for flagged vertices
 * and the cubed factor otherwise. Preserve conversion/narrowing and
 * floating evaluation order; no new clamping is introduced. */
void uvColorScaleVertexRgb(Vtx *vertices, s32 count, f32 redScale, f32 greenScale, f32 blueScale) {
    s32 i;
    f32 channel;
    f32 scaled;

    for (i = 0; i < count; i++) {
        Vtx *v = &vertices[i];
        channel = v->v.cn[0];
        scaled = v->v.flag ? redScale * channel : CUBE(redScale) * channel;
        v->v.cn[0] = scaled;
        channel = v->v.cn[1];
        scaled = v->v.flag ? greenScale * channel : CUBE(greenScale) * channel;
        v->v.cn[1] = scaled;
        channel = v->v.cn[2];
        scaled = v->v.flag ? blueScale * channel : CUBE(blueScale) * channel;
        v->v.cn[2] = scaled;
    }
}
#line 262 "src/modules/uvcolor_rom.c"

#line 263 "src/modules/uvcolor_rom.c"
/* Convert each RGB vertex color to normalized hue/saturation/value,
 * scale those components and convert back. Unflagged vertices cube the
 * value factor only; preserve original unsigned byte conversion. */
void uvColorScaleVertexHsv(Vtx *vertices, s32 count, f32 hueScale, f32 saturationScale, f32 valueScale) {
    f32 scaledValue;

    f32 scaledHue;

    f32 hue;
    f32 saturation;
    f32 value;
    f32 scaledSaturation;
    s32 i;
    Vtx *vertex;
    f32 red;
    f32 green;
    f32 blue;

    for (i = 0; i < count; i++) {
        vertex = vertices + i;

        uvColorRgbToHsv((f32) (u32) vertex->v.cn[0] / 255.0f, (f32) (u32) vertex->v.cn[1] / 255.0f,
                                  (f32) (u32) vertex->v.cn[2] / 255.0f, &hue, &saturation, &value);

        if (vertex->v.flag != 0) {
            scaledHue = hueScale * hue;
            scaledSaturation = saturationScale * saturation;
            scaledValue = valueScale * value;
        } else {
            scaledHue = hueScale * hue;
            scaledSaturation = saturationScale * saturation;
            scaledValue = valueScale * valueScale * valueScale * value;
        }

        uvColorHsvToRgb(scaledHue, scaledSaturation, scaledValue, &red, &green, &blue);

        vertex->v.cn[0] = (u8) (u32) (red * 255.0f);
        vertex->v.cn[1] = (u8) (u32) (green * 255.0f);
        vertex->v.cn[2] = (u8) (u32) (blue * 255.0f);
    }
}
#line 301 "src/modules/uvcolor_rom.c"

#line 302 "src/modules/uvcolor_rom.c"
/* Scale hue, saturation and value for packed color texels; scale only
 * intensity for the supported intensity/alpha formats. Preserve alpha
 * bits, original format codes, narrowing and byte-count semantics. */
void uvColorScaleTextureHsv(s32 format, s32 bitsPerTexel, s32 byteCount, void *texels, f32 hueScale, f32 saturationScale, f32 valueScale) {
    s32 i;
    f32 hue;
    f32 saturation;
    f32 value;
    u16 *texels16;
    u8 *texels8;
    f32 temp_fv1;
    f32 intensity;
    s32 pad;
    f32 red;
    f32 green;
    f32 blue;
    s32 pad2[2];

    switch (format) {
        case 4:
            texels16 = texels;
            for (i = 0; i < byteCount / 2; i++) {
                uvColorRgbToHsv(((s32) (texels16[i] & 0xF800) >> 0xB) / 31.0f,
                                          ((s32) (texels16[i] & 0x7C0) >> 6) / 31.0f,
                                          ((s32) (texels16[i] & 0x3E) >> 1) / 31.0f, &hue, &saturation, &value);
                uvColorHsvToRgb(hueScale * hue, saturationScale * saturation, valueScale * value, &red, &green, &blue);
                red *= 31.0f;
                green *= 31.0f;
                blue *= 31.0f;
                texels16[i] =
                    ((s32) red << 11) | ((s32) green << 6) | ((s32) blue << 1) | (texels16[i] & 1);
            }
            break;
        case 2:
            switch (bitsPerTexel) {
                case 4:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = (texels8[i] & 0xE) >> 1;
                        texels8[i] = (texels8[i] & 0xF1) | (((s32) (valueScale * intensity)) << 1);
                        intensity = (texels8[i] & 0xE0) >> 5;
                        texels8[i] = (((s32) (valueScale * intensity)) << 5) | (texels8[i] & 0x1F);
                    }
                    break;
                case 8:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = (texels8[i] & 0xF0) >> 4;
                        texels8[i] = ((((s32) (valueScale * intensity)) & 0xF) << 4) | (texels8[i] & 0xF);
                    }
                    break;
                case 16:
                    texels16 = texels;
                    for (i = 0; i < byteCount / 2; i++) {
                        intensity = (texels16[i] & 0xFF00) >> 8;
                        texels16[i] = ((((s32) (valueScale * intensity)) & 0xFF) << 8) | (texels16[i] & 0xFF);
                    }
                    break;
            }
            break;
        case 1:
            switch (bitsPerTexel) {
                case 4:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = texels8[i] & 0xF;
                        texels8[i] = (texels8[i] & 0xF0) | (((s32) (valueScale * intensity)) & 0xF);
                        intensity = (texels8[i] & 0xF0) >> 4;
                        texels8[i] = ((((s32) (valueScale * intensity)) & 0xF) << 4) | (texels8[i] & 0xF);
                    }
                    break;
                case 8:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = texels8[i];
                        texels8[i] = valueScale * intensity;
                    }
                    break;
                case 16:
                    texels16 = texels;
                    for (i = 0; i < byteCount / 2; i++) {
                        intensity = texels16[i];
                        texels16[i] = valueScale * intensity;
                    }
                    break;
            }
            break;
    }
}
#line 388 "src/modules/uvcolor_rom.c"

#line 389 "src/modules/uvcolor_rom.c"
/* Scale each packed RGB channel and retain alpha. Intensity formats
 * use the largest caller channel scale; preserve the original nibble
 * masks, unsupported-format no-op behavior and byte-count semantics. */
void uvColorScaleTextureRgb(s32 format, s32 bitsPerTexel, s32 byteCount, void *texels, f32 redScale, f32 greenScale, f32 blueScale) {
    f32 intensityScale;
    u16 *texels16;
    u8 *texels8;
    s32 i;
    f32 r;
    f32 g;
    f32 b;
    f32 intensity;

    if (greenScale < redScale) {
        if (blueScale < redScale) {
            intensityScale = redScale;
        } else {
            intensityScale = blueScale;
        }
    } else {
        if (blueScale < greenScale) {
            intensityScale = greenScale;
        } else {
            intensityScale = blueScale;
        }
    }
    switch (format) {
        case 4:
            texels16 = texels;
            for (i = 0; i < byteCount / 2; i++) {
                r = (texels16[i] & 0xF800) >> 11;
                g = (texels16[i] & 0x7C0) >> 6;
                b = (texels16[i] & 0x3E) >> 1;
                texels16[i] = ((s32) (r * redScale) << 11) | ((s32) (g * greenScale) << 6) | ((s32) (b * blueScale) << 1)
                            | (texels16[i] & 1);
            }
            break;
        case 2:
            switch (bitsPerTexel) {
                case 4:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = (texels8[i] & 0xE) >> 1;
                        texels8[i] = (texels8[i] & 0xF1) | (((s32) (intensityScale * intensity)) << 1);
                        intensity = (texels8[i] & 0xE0) >> 5;
                        texels8[i] = (((s32) (intensityScale * intensity)) << 5) | (texels8[i] & 0x1F);
                    }
                    break;
                case 8:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = (texels8[i] & 0xF0) >> 4;
                        texels8[i] = ((((s32) (intensityScale * intensity)) & 0xF) << 4) | (texels8[i] & 0xF);
                    }
                    break;
                case 16:
                    texels16 = texels;
                    for (i = 0; i < byteCount / 2; i++) {
                        intensity = (texels16[i] & 0xFF00) >> 8;
                        texels16[i] = ((((s32) (intensityScale * intensity)) & 0xFF) << 8) | (texels16[i] & 0xFF);
                    }
                    break;
            }
            break;
        case 1:
            switch (bitsPerTexel) {
                case 4:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = texels8[i] & 0xF;
                        texels8[i] = (texels8[i] & 0xF0) | (((s32) (intensityScale * intensity)) & 0xF);
                        intensity = (texels8[i] & 0xF0) >> 4;
                        texels8[i] = ((((s32) (intensityScale * intensity)) & 0xF) << 4) | (texels8[i] & 0xF);
                    }
                    break;
                case 8:
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = texels8[i];
                        texels8[i] = intensityScale * intensity;
                    }
                    break;
                case 16:
                    texels16 = texels;
                    for (i = 0; i < byteCount / 2; i++) {
                        intensity = texels16[i];
                        texels16[i] = intensityScale * intensity;
                    }
                    break;
            }
            break;
    }
}
#line 479 "src/modules/uvcolor_rom.c"

#line 480 "src/modules/uvcolor_rom.c"
/* Blend vertex RGB toward the caller color using retained weights.
 * Flagged vertices use linear weights; unflagged vertices use their
 * cubes. Alpha and vertex flags remain unchanged. */
void uvColorBlendVertexRgbByFlag(Vtx *vertices, s32 vertexCount, f32 targetRed, f32 targetGreen, f32 targetBlue, f32 redWeight, f32 greenWeight,
                               f32 blueWeight) {
    s32 i;
    f32 redWeightCubed;
    f32 greenWeightCubed;
    f32 blueWeightCubed;
    f32 unflaggedRedOffset;
    f32 unflaggedGreenOffset;
    f32 unflaggedBlueOffset;
    Vtx *vertex;
    f32 channel;
    f32 blendedChannel;

    redWeightCubed = redWeight * redWeight * redWeight;
    greenWeightCubed = greenWeight * greenWeight * greenWeight;
    blueWeightCubed = blueWeight * blueWeight * blueWeight;
    unflaggedRedOffset = (1.0f - redWeightCubed) * 255.0f * targetRed;
    unflaggedGreenOffset = (1.0f - greenWeightCubed) * 255.0f * targetGreen;
    unflaggedBlueOffset = (1.0f - blueWeightCubed) * 255.0f * targetBlue;
    targetRed = targetRed * ((1.0f - redWeight) * 255.0f);
    targetGreen = targetGreen * ((1.0f - greenWeight) * 255.0f);
    targetBlue = targetBlue * ((1.0f - blueWeight) * 255.0f);

    for (i = 0; i < vertexCount; i++) {
        vertex = &vertices[i];
        channel = vertex->v.cn[0];
        if (vertex->v.flag != 0) {
            blendedChannel = (redWeight * channel) + targetRed;
        } else {
            blendedChannel = (redWeightCubed * channel) + unflaggedRedOffset;
        }
        vertex->v.cn[0] = blendedChannel;
        channel = vertex->v.cn[1];
        if (vertex->v.flag != 0) {
            blendedChannel = (greenWeight * channel) + targetGreen;
        } else {
            blendedChannel = (greenWeightCubed * channel) + unflaggedGreenOffset;
        }
        vertex->v.cn[1] = blendedChannel;
        channel = vertex->v.cn[2];
        if (vertex->v.flag != 0) {
            blendedChannel = (blueWeight * channel) + targetBlue;
        } else {
            blendedChannel = (blueWeightCubed * channel) + unflaggedBlueOffset;
        }
        vertex->v.cn[2] = blendedChannel;
    }
}
#line 528 "src/modules/uvcolor_rom.c"

void func_uvcolor_rom_00404C54(s32 arg0, s32 arg1, s32 arg2, void *arg3, f32 arg4, f32 arg5, f32 arg6,
                               f32 arg7, f32 arg8, f32 arg9) {
    s32 i;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    u16 *var_s0;
    u8 *var_v0;
    f32 temp_fv1;
    f32 temp_fa0;
    s32 pad;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    s32 pad2[2];

    switch (arg0) {
        case 4:
            var_s0 = arg3;
            sp50 = (1.0f - arg7) * arg4;
            sp4C = (1.0f - arg8) * arg5;
            sp48 = (1.0f - arg9) * arg6;
            for (i = 0; i < arg2 / 2; i++) {
                uvColorRgbToHsv((f32) ((s32) (var_s0[i] & 0xF800) >> 0xB) / 31.0f,
                                          (f32) ((s32) (var_s0[i] & 0x7C0) >> 6) / 31.0f,
                                          (f32) ((s32) (var_s0[i] & 0x3E) >> 1) / 31.0f, &spB0, &spAC,
                                          &spA8);
                uvColorHsvToRgb((arg7 * spB0) + sp50, (arg8 * spAC) + sp4C,
                                          (arg9 * spA8) + sp48, &sp80, &sp7C, &sp78);
                sp80 *= 31.0f;
                sp7C *= 31.0f;
                sp78 *= 31.0f;
                var_s0[i] =
                    ((s32) sp80 << 11) | ((s32) sp7C << 6) | ((s32) sp78 << 1) | (var_s0[i] & 1);
            }
            break;
        case 2:
            switch (arg1) {
                case 4:
                    temp_fv1 = (1.0f - arg9) * arg6 * 7.0f;
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_v0[i] & 0xE) >> 1;
                        var_v0[i] = (var_v0[i] & 0xF1) | (((s32) ((arg9 * temp_fa0) + temp_fv1)) << 1);
                        temp_fa0 = (var_v0[i] & 0xE0) >> 5;
                        //! @bug sp84 uninitialised!
                        var_v0[i] = (((s32) ((arg9 * temp_fa0) + sp84)) << 5) | (var_v0[i] & 0x1F);
                    }
                    break;
                case 8:
                    temp_fv1 = (1.0f - arg9) * arg6 * 15.0f;
                    var_v0 = arg3;
                    for (i = 0; i < arg2; i++) {
                        temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                        var_v0[i] =
                            ((((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xF) << 4) | (var_v0[i] & 0xF);
                    }
                    break;
                case 16:
                    temp_fv1 = (1.0f - arg9) * arg6 * 255.0f;
                    var_s0 = arg3;
                    for (i = 0; i < arg2 / 2; i++) {
                        temp_fa0 = (var_s0[i] & 0xFF00) >> 8;
                        var_s0[i] =
                            ((((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xFF) << 8) | (var_s0[i] & 0xFF);
                    }
                    break;

                case 1:
                    switch (arg1) {
                        case 4:
                            temp_fv1 = (1.0f - arg9) * arg6 * 15.0f;
                            var_v0 = arg3;
                            for (i = 0; i < arg2; i++) {
                                temp_fa0 = var_v0[i] & 0xF;
                                var_v0[i] =
                                    (var_v0[i] & 0xF0) | (((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xF);
                                temp_fa0 = (var_v0[i] & 0xF0) >> 4;
                                var_v0[i] = ((((s32) ((arg9 * temp_fa0) + temp_fv1)) & 0xF) << 4)
                                            | (var_v0[i] & 0xF);
                            }
                            break;
                        case 8:
                            temp_fv1 = (1.0f - arg9) * arg6 * 255.0f;
                            var_v0 = arg3;
                            for (i = 0; i < arg2; i++) {
                                temp_fa0 = var_v0[i];
                                var_v0[i] = (arg9 * temp_fa0) + temp_fv1;
                            }
                            break;
                        case 16:
                            temp_fv1 = (1.0f - arg9) * arg6 * 65535.0f;
                            var_s0 = arg3;
                            for (i = 0; i < arg2 / 2; i++) {
                                temp_fa0 = var_s0[i];
                                var_s0[i] = (arg9 * temp_fa0) + temp_fv1;
                            }
                            break;
                    }
            }
            break;
    }
}

#line 637 "src/modules/uvcolor_rom.c"
/* Blend packed RGB toward the supplied target while preserving alpha.
 * For intensity formats, use the largest target channel and that
 * channel retained weight, keeping the original ties and narrowing. */
void uvColorBlendTextureRgb(s32 format, s32 bitsPerTexel, s32 byteCount, void *texels, f32 targetRed, f32 targetGreen, f32 targetBlue,
                               f32 redWeight, f32 greenWeight, f32 blueWeight) {
    u8 *texels8;
    u16 *texels16;
    f32 intensityTarget;
    f32 intensityWeight;
    s32 i;
    f32 intensity;
    f32 r;
    f32 g;
    f32 b;

    if (targetGreen < targetRed) {
        if (targetBlue < targetRed) {
            intensityTarget = targetRed;
            intensityWeight = redWeight;
        } else {
            intensityTarget = targetBlue;
            intensityWeight = blueWeight;
        }
    } else if (targetBlue < targetGreen) {
        intensityTarget = targetGreen;
        intensityWeight = greenWeight;
    } else {
        intensityTarget = targetBlue;
        intensityWeight = blueWeight;
    }

    if (format != 1) {
        if (format != 2) {
            if (format == 4) {
                targetRed *= (1.0f - redWeight) * 31.0f;
                targetGreen *= (1.0f - greenWeight) * 31.0f;
                targetBlue *= (1.0f - blueWeight) * 31.0f;
                texels16 = texels;
                for (i = 0; i < byteCount / 2; i++) {
                    r = ((texels16[i] & 0xF800) >> 11);
                    g = ((texels16[i] & 0x7C0) >> 6);
                    b = ((texels16[i] & 0x3E) >> 1);
                    texels16[i] = ((s32) ((redWeight * r) + targetRed) << 11) | ((s32) ((greenWeight * g) + targetGreen) << 6)
                                | ((s32) ((blueWeight * b) + targetBlue) << 1) | (texels16[i] & 1);
                }
            }
        } else {
            switch (bitsPerTexel) {
                case 4:
                    intensityTarget *= (1.0f - intensityWeight) * 7.0f;
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = (texels8[i] & 0xE) >> 1;
                        texels8[i] = (texels8[i] & 0xF1) | ((s32) ((intensityWeight * intensity) + intensityTarget) << 1);
                        intensity = (texels8[i] & 0xE0) >> 5;
                        texels8[i] = ((s32) ((intensityWeight * intensity) + intensityTarget) << 5) | (texels8[i] & 0x1F);
                    }
                    break;
                case 8:
                    intensityTarget *= (1.0f - intensityWeight) * 15.0f;
                    texels8 = texels;
                    for (i = 0; i < byteCount; i++) {
                        intensity = (texels8[i] & 0xF0) >> 4;
                        texels8[i] =
                            (((s32) ((intensityWeight * intensity) + intensityTarget) & 0xF) << 4) | (texels8[i] & 0xF);
                    }
                    break;
                case 16:
                    intensityTarget *= (1.0f - intensityWeight) * 255.0f;
                    texels16 = texels;
                    for (i = 0; i < byteCount / 2; i++) {
                        intensity = (texels16[i] & 0xFF00) >> 8;
                        texels16[i] =
                            (((s32) ((intensityWeight * intensity) + intensityTarget) & 0xFF) << 8) | (texels16[i] & 0xFF);
                    }
                    break;
            }
        }
    } else {
        switch (bitsPerTexel) {
            case 4:
                intensityTarget *= (1.0f - intensityWeight) * 15.0f;
                texels8 = texels;
                for (i = 0; i < byteCount; i++) {
                    intensity = (texels8[i] & 0xF);
                    texels8[i] = (texels8[i] & 0xF0) | ((s32) ((intensityWeight * intensity) + intensityTarget) & 0xF);
                    intensity = (texels8[i] & 0xF0) >> 4;
                    texels8[i] =
                        (((s32) ((intensityWeight * intensity) + intensityTarget) & 0xF) << 4) | (texels8[i] & 0xF);
                }
                break;
            case 8:
                intensityTarget *= (1.0f - intensityWeight) * 255.0f;
                texels8 = texels;
                for (i = 0; i < byteCount; i++) {
                    intensity = texels8[i];
                    texels8[i] = (intensityWeight * intensity) + intensityTarget;
                }
                break;
            case 16:
                intensityTarget *= (1.0f - intensityWeight) * 65535.0f;
                texels16 = texels;
                for (i = 0; i < byteCount / 2; i++) {
                    intensity = texels16[i];
                    texels16[i] = (intensityWeight * intensity) + intensityTarget;
                }
                break;
        }
    }
}
#line 744 "src/modules/uvcolor_rom.c"

#line 745 "src/modules/uvcolor_rom.c"
/* Convert RGB to hue in turns, saturation and maximum-channel value.
 * Equal channels produce hue -1 and saturation zero. Preserve strict
 * comparisons and the original tie/NaN behavior. */
void uvColorRgbToHsv(f32 red, f32 green, f32 blue, f32 *hue, f32 *saturation, f32 *value) {
    f32 maximum;
    f32 minimum;

    maximum = red;
    minimum = red;
    if (red < green) {
        maximum = green;
    }
    if (green < red) {
        minimum = green;
    }
    if (maximum < blue) {
        maximum = blue;
    }
    if (blue < minimum) {
        minimum = blue;
    }
    *value = maximum;
    if (maximum == minimum) {
        *saturation = 0.0f;
        *hue = -1.0f;
        return;
    }

    *saturation = (maximum - minimum) / maximum;
    if (red == maximum) {
        *hue = ((maximum - blue) / (maximum - minimum)) - ((maximum - green) / (maximum - minimum));
    } else if (green == maximum) {
        *hue =
            ((maximum - red) / (maximum - minimum)) - ((maximum - blue) / (maximum - minimum)) + 2.0f;
    } else if (blue == maximum) {
        *hue =
            ((maximum - green) / (maximum - minimum)) - ((maximum - red) / (maximum - minimum)) + 4.0f;
    }
    *hue *= 60.0f;

    if (*hue < 0.0f) {
        *hue += 360.0f;
    }
    *hue /= 360.0f;
}
#line 787 "src/modules/uvcolor_rom.c"

#line 788 "src/modules/uvcolor_rom.c"
/* Convert normalized HSV through the original six hue sectors. Near-zero
 * saturation produces gray; preserve one-step hue wrapping and the original
 * unchanged-output behavior for sectors outside zero through five. */
void uvColorHsvToRgb(f32 hue, f32 saturation, f32 value, f32 *red, f32 *green, f32 *blue) {
    s32 sector;
    f32 fraction;

    if (saturation <= 0.0001f) {
        *red = value;
        *green = value;
        *blue = value;
        return;
    }
    if (hue < 0.0f) {
        hue += 1.0f;
    }
    if (hue == 1.0f) {
        hue = 0;
    }

    hue *= 6.0f;
    sector = (s32) hue;
    fraction = hue - sector;

    switch (sector) {
        case 0:
            *red = value;
            *green = (1.0f - (saturation * (1.0f - fraction))) * value;
            *blue = (1.0f - saturation) * value;
            break;
        case 1:
            *red = (1.0f - (saturation * fraction)) * value;
            *green = value;
            *blue = (1.0f - saturation) * value;
            break;
        case 2:
            *red = (1.0f - saturation) * value;
            *green = value;
            *blue = (1.0f - (saturation * (1.0f - fraction))) * value;
            break;
        case 3:
            *red = (1.0f - saturation) * value;
            *green = (1.0f - (saturation * fraction)) * value;
            *blue = value;
            break;
        case 4:
            *red = (1.0f - (saturation * (1.0f - fraction))) * value;
            *green = (1.0f - saturation) * value;
            *blue = value;
            break;
        case 5:
            *red = value;
            *green = (1.0f - saturation) * value;
            *blue = (1.0f - (saturation * fraction)) * value;
            break;
        default:
            break;
    }
}
#line 844 "src/modules/uvcolor_rom.c"

#line 845 "src/modules/uvcolor_rom.c"
/* Convert vertex RGB to HSV, blend toward the caller HSV color and
 * convert back. Flagged vertices use linear retained weights; unflagged
 * vertices use cubed value weight only. Preserve alpha and narrowing. */
void uvColorBlendVertexHsvByFlag(Vtx *vertices, s32 vertexCount, f32 targetHue, f32 targetSaturation, f32 targetValue, f32 hueWeight, f32 saturationWeight,
                               f32 valueWeight) {
    s32 i;
    Vtx *vertex;
    f32 hue;
    f32 saturation;
    f32 value;
    f32 blendedHue;
    f32 blendedSaturation;
    f32 blendedValue;
    f32 red;
    f32 green;
    f32 blue;
    f32 unflaggedHueOffset;
    f32 unflaggedValueOffset;
    f32 unflaggedSaturationOffset;
    f32 valueWeightCubed;
    s32 pad;

    valueWeightCubed = valueWeight * valueWeight * valueWeight;
    unflaggedHueOffset = (1.0f - hueWeight) * targetHue;
    unflaggedSaturationOffset = (1.0f - saturationWeight) * targetSaturation;
    unflaggedValueOffset = (1.0f - valueWeightCubed) * targetValue;
    targetHue = (1.0f - hueWeight) * targetHue;
    targetSaturation = (1.0f - saturationWeight) * targetSaturation;
    targetValue = (1.0f - valueWeight) * targetValue;
    for (i = 0; i < vertexCount; i++) {
        vertex = &vertices[i];

        uvColorRgbToHsv(vertex->v.cn[0] / 255.0f, vertex->v.cn[1] / 255.0f,
                                  vertex->v.cn[2] / 255.0f, &hue, &saturation, &value);
        if (vertex->v.flag != 0) {
            blendedHue = (hueWeight * hue) + targetHue;
            blendedSaturation = (saturationWeight * saturation) + targetSaturation;
            blendedValue = (valueWeight * value) + targetValue;
        } else {
            blendedHue = (hueWeight * hue) + unflaggedHueOffset;
            blendedSaturation = (saturationWeight * saturation) + unflaggedSaturationOffset;
            blendedValue = (valueWeightCubed * value) + unflaggedValueOffset;
        }
        uvColorHsvToRgb(blendedHue, blendedSaturation, blendedValue, &red, &green, &blue);
        vertex->v.cn[0] = red * 255.0f;
        vertex->v.cn[1] = green * 255.0f;
        vertex->v.cn[2] = blue * 255.0f;
    }
}
#line 891 "src/modules/uvcolor_rom.c"
