// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"
#include <PR/sp.h>
#include "uvasset_types.h"

#define MY_K0 (175 & 0x1ff)
#define MY_K1 (-43 & 0x1ff)
#define MY_K2 (-89 & 0x1ff)
#define MY_K3 (222 & 0x1ff)
#define MY_K4 (114 & 0x1ff)
#define MY_K5 (42 & 0x1ff)
#define SPRITE_SURF G_RM_TEX_EDGE
#define SPRITE_SURF2 G_RM_TEX_EDGE2

typedef struct uvSprite_s {
    /* 00 */ u8 unk0; // Flag to draw the sprite
    /* 01 */ u8 unk1;
    /* 02 */ u8 unk2; // Another flag to draw the sprite?
    /* 04 */ s16 height;
    /* 06 */ s16 unk6;
    /* 08 */ u16 textureId;
    /* 0A */ u16 unkA;
    /* 0xC */ Bitmap *bitmap;
    /* 10 */ Sprite sprite;
} uvSprite_t; // size 0x54

/* STAT export 0x58 is uvGfxResetShadeCombineMode(void), with no result. */
typedef struct UnkStruct_uvsprt_rom_004033CC_s {
    char pad[0x58];
    void (*resetShadeCombineMode)(void);
} UnkStruct_uvsprt_rom_004033CC;

void __entrypoint_func_uvsprt_rom_400298(UvSprt_Rom_Exports* exports);
void uvSpriteFromBitmap(uvSprite_t *sprite, ParsedUVTX *uvtx);
void uvSpriteInitializeFromTextureOrDefaults(uvSprite_t *sprite, ParsedUVTX *uvtx);
s32 uvSpriteAllocateFirstFree(void);
void uvSpriteClearStateBytes(s32 arg0);
void uvSprtModuleCleanup(void);
void uvSpriteDisplayList(Gfx **gdlh, uvSprite_t *sp);
void uvSpriteDrawAll(void);
void uvSpriteRender(s32 arg0);
void uvSpriteSetBlit(uvSprite_t *sprite, s32 blitId);
s16 uvGetSpriteWidth(s32 arg0);
s16 uvGetSpriteHeight(s32 arg0);
void uvSprtProps(s32 arg0, ...);
void uvDrawBitmap(Gfx **gdl, Sprite *s, Bitmap *b, s32 x, s32 y, s32 xx, s32 yy, s32 fs,
                              s32 ft, s32 sx, s32 sy);
void uvSpriteDrawInit(Gfx **glistp);
Gfx* uvSpriteDraw(Sprite* sp);
void uvSpriteDrawFinish(Gfx **glistp);

// .data
s32 *sPrevBitmapBuf = NULL;
u16 sSpriteAttribute = 0;

s32 sUnkModuleInfo[] = {0x002C0000, &__entrypoint_func_uvsprt_rom_400298};

// .bss
extern s32 sScissorXmax;
extern s32 sScissorYmax;
extern s32 sScissorXmin;
extern s32 sScissorYmin;
extern UvGfxMgr_Exports *sUvGfxMgrExports_uvsprt;
extern UnkStruct_uvsprt_rom_004033CC *sUvGfxStateExports_uvsprt;
extern uvSprite_t *sSprites;
extern s32 sMaxSprites;

void uvSpriteFromBitmap(uvSprite_t *spriteRecord, ParsedUVTX *textureConfig) {
    Bitmap *bitmapStorage;
    /* RE_ORIGINAL_QUIRK: allocator result is used without a local null check. RE_UNKNOWN: allocation success, backing, aliases and lifetimes need original allocator, producer and caller proof. */
    if ((u16) spriteRecord->textureId == 0xFFFF) {
        spriteRecord->bitmap = NULL;
    }
    bitmapStorage = spriteRecord->bitmap;
    if (bitmapStorage == NULL) {
        bitmapStorage = _uvMemAllocAlign8(sizeof(Bitmap));
        spriteRecord->bitmap = bitmapStorage;
    }
    bitmapStorage->width = textureConfig->width - 1;
    spriteRecord->bitmap->width_img = (s16) textureConfig->width;
    spriteRecord->bitmap->s = 0;
    spriteRecord->bitmap->t = 0;
    spriteRecord->bitmap->buf = textureConfig->data.pointer; // RE_UNKNOWN: copied texture-data extent, ownership and lifetime need original producer/consumer proof.
    spriteRecord->bitmap->actualHeight = (s16) textureConfig->height;
    spriteRecord->bitmap->LUToffset = 0;
}

#line 89 "src/modules/uvsprt_rom.c"
/* Initialize a sprite from available texture dimensions, format and
 * transparency metadata, then set the original white color, bitmap
 * storage and drawing defaults. A null texture leaves dimension and
 * format fields untouched. */
void uvSpriteInitializeFromTextureOrDefaults(uvSprite_t *sprite, ParsedUVTX *texture) {
    Sprite *nativeSprite = &sprite->sprite;

    if (texture != NULL) {
        nativeSprite->width = texture->width - 1;
        nativeSprite->height = texture->height - 1;
        nativeSprite->bmheight = texture->height - 1;
        nativeSprite->bmHreal = (s16) texture->height;
        nativeSprite->bmfmt = G_IM_FMT_RGBA;
        nativeSprite->bmsiz = G_IM_SIZ_16b;
        nativeSprite->attr = 0x200;

        if (texture->unk21 != 1) {
            nativeSprite->attr |= SP_TRANSPARENT;
        }
        if (texture->unk21 == 1) {
            nativeSprite->bmfmt = G_IM_FMT_I;
        } else if (texture->unk21 == 2) {
            nativeSprite->bmfmt = G_IM_FMT_IA;
        } else {
            nativeSprite->bmfmt = 0;
        }
        if (texture->unk24 == 4) {
            nativeSprite->bmsiz = G_IM_SIZ_4b;
        } else if (texture->unk24 == 8) {
            nativeSprite->bmsiz = G_IM_SIZ_8b;
        } else {
            nativeSprite->bmsiz = G_IM_SIZ_16b;
        }
        nativeSprite->scalex = 1.0f;
        nativeSprite->scaley = 1.0f;
    }

    nativeSprite->expx = 0;
    nativeSprite->expy = 0;
    nativeSprite->zdepth = 0x1234;
    nativeSprite->red = 0xFF;
    nativeSprite->green = 0xFF;
    nativeSprite->blue = 0xFF;
    nativeSprite->alpha = 0xFF;
    nativeSprite->startTLUT = 0;
    nativeSprite->nTLUT = 0;
    nativeSprite->LUT = NULL;
    nativeSprite->istart = 0;
    nativeSprite->istep = 1;
    nativeSprite->nbitmaps = 1;
    nativeSprite->ndisplist = 0x24;
    nativeSprite->scalex = 1.0f;
    nativeSprite->scaley = 1.0f;
    nativeSprite->bitmap = sprite->bitmap;
    nativeSprite->frac_s = 0;
    nativeSprite->frac_t = 0;
}
#line 142 "src/modules/uvsprt_rom.c"

#line 143 "src/modules/uvsprt_rom.c"
/* Mark and return the first sprite whose allocation byte is zero;
 * return -1 when all configured sprite entries are occupied. */
s32 uvSpriteAllocateFirstFree(void) {
    s32 index;

    for (index = 0; index < sMaxSprites; index++) {
        if (sSprites[index].unk1 == 0) {
            sSprites[index].unk1 = 1;
            return index;
        }
    }

    return -1;
}
#line 155 "src/modules/uvsprt_rom.c"

#line 156 "src/modules/uvsprt_rom.c"
/* Clear both leading bytes in the selected sprite. RE_UNKNOWN: sprite
 * index/backing validity need original pool, ID producers and callers. */
void uvSpriteClearStateBytes(s32 spriteId) {
    sSprites[spriteId].unk0 = 0;
    sSprites[spriteId].unk1 = 0;
}
#line 160 "src/modules/uvsprt_rom.c"

void uvSprtModuleCleanup(void) {
    uvUnloadModule('GMGR');
}

void __entrypoint_func_uvsprt_rom_400298(UvSprt_Rom_Exports* exports) {
    s32 *configuredCount;
    uvSprite_t *spriteRecord;
    s32 spriteIndex;
    /* RE_UNKNOWN: count domain, allocation/module success and pool lifetime need original property producers, allocators and callers. */
    uvUpdateFileAllocPtr(exports);
    exports->uvSprtModuleCleanup = uvSprtModuleCleanup;
    exports->uvSpriteDrawFinish = uvSpriteDrawFinish;
    exports->uvSpriteAllocateFirstFree = uvSpriteAllocateFirstFree;
    exports->uvSpriteClearStateBytes = uvSpriteClearStateBytes;
    exports->uvSpriteDrawAll = uvSpriteDrawAll;
    exports->uvSpriteRender = uvSpriteRender;
    exports->uvGetSpriteWidth = uvGetSpriteWidth;
    exports->uvGetSpriteHeight = uvGetSpriteHeight;
    exports->uvSprtProps = uvSprtProps;
    exports->uvSpriteDrawInit = uvSpriteDrawInit;
    exports->uvSpriteDraw = uvSpriteDraw;
    configuredCount = uvGetSystemProp(SYSTEM_PROPID_MAX_SPRITES);
    if (configuredCount == NULL) {
        sMaxSprites = 20;
    } else {
        if (*configuredCount != 0) {
            sMaxSprites = *configuredCount;
        } else {
            sMaxSprites = 20;
        }
    }
    sUvGfxMgrExports_uvsprt = uvLoadModule('GMGR');
    sUvGfxStateExports_uvsprt = uvLoadModule('STAT');
    sSprites = _uvMemAllocAlign8(sMaxSprites * sizeof(uvSprite_t));
    uvMemSet(sSprites, 0, sMaxSprites * sizeof(uvSprite_t));

    for (spriteIndex = 0; spriteIndex < sMaxSprites; spriteIndex++) {
        spriteRecord = spriteIndex + sSprites;
        spriteRecord->unk0 = 0;
        spriteRecord->unk1 = 0;
        spriteRecord->unk2 = 0;
        spriteRecord->sprite.red = spriteRecord->sprite.green = spriteRecord->sprite.blue = spriteRecord->sprite.alpha = 255;
        spriteRecord->textureId = 0xFFF;
        spriteRecord->bitmap = NULL;
    }
}

void uvSpriteDisplayList(Gfx **displayListCursor, uvSprite_t *spriteRecord) {
    Sprite *spriteState = &spriteRecord->sprite;
    /* RE_UNKNOWN: cursor/sprite backing, writable capacity, aliases and lifetimes need original caller/producer proof. */
    spriteState->rsp_dl = *displayListCursor;
    spriteState->attr &= 0xFFDF;
    spriteState->rsp_dl_next = NULL;
    /* Preserve both cursor assignments when the drawing provider returns a nonzero start pointer. */
    if (uvSpriteDraw(spriteState) != NULL) {
        *displayListCursor = spriteState->rsp_dl_next;
        *displayListCursor = *displayListCursor - 1;
    }
}

void uvSpriteDrawAll(void) {
    Gfx** gdlh;
    s32 i;
    uvSprite_t* temp_a1;

    gdlh = sUvGfxMgrExports_uvsprt->uvGetDisplayListHead();
    uvSpriteDrawInit(gdlh);
    for (i = 0; i < sMaxSprites; i++) {
        temp_a1 = sSprites + i;
        if ((temp_a1->unk0 == 0) || (temp_a1->unk2 == 0)) {
            continue;
        } else if (temp_a1->textureId == 0xFFF) {
            continue;
        }
        uvSpriteDisplayList(gdlh, temp_a1);
    }

    uvSpriteDrawFinish(gdlh);
    *gdlh -= 1;
    if (sUvGfxStateExports_uvsprt != NULL) {
        sUvGfxStateExports_uvsprt->resetShadeCombineMode();
    }
}

void uvSpriteRender(s32 arg0) {
    uvSprite_t *uvSprite;
    Gfx **gdlh;

    if (arg0 < sMaxSprites) {
        uvSprite = &sSprites[arg0];
        if ((u16) uvSprite->textureId != 0xFFF) {
            gdlh = sUvGfxMgrExports_uvsprt->uvGetDisplayListHead();
            uvSpriteDrawInit(gdlh);
            uvSpriteDisplayList(gdlh, uvSprite);
            uvSpriteDrawFinish(gdlh);
            *gdlh -= 1;
            sUvGfxStateExports_uvsprt->resetShadeCombineMode();
        }
    }
}

void uvSpriteSetBlit(uvSprite_t *spriteRecord, s32 bitmapResourceId) {
    ParsedUVBT *bitmapConfig;
    Sprite *spriteState = &spriteRecord->sprite;
    s16 unusedHalfwordA;
    s16 unusedHalfwordB;
    // RE_UNKNOWN: asset extents, aliasing, ownership and historical declarations need original producer/caller proof.
    bitmapConfig = uvGetLoadedFile('UVBT', bitmapResourceId);
    if ((bitmapConfig != NULL) || (bitmapConfig = uvLoadFile('UVBT', bitmapResourceId), (bitmapConfig != NULL))) {
        spriteRecord->sprite.bitmap = bitmapConfig->bitmap;
        spriteRecord->textureId = -1;
        spriteRecord->sprite.width = bitmapConfig->width;
        spriteRecord->sprite.height = bitmapConfig->height;
        spriteRecord->sprite.bitmap = bitmapConfig->bitmap;
        spriteRecord->sprite.nbitmaps = bitmapConfig->nbitmaps;
        spriteRecord->sprite.ndisplist = (bitmapConfig->nbitmaps * 0xC) + 0x18;
        spriteRecord->sprite.bmheight = bitmapConfig->texelHeight;
        spriteRecord->sprite.bmHreal = bitmapConfig->texelHeight;
        spriteRecord->sprite.bmfmt = (u8) bitmapConfig->bmfmt;
        switch (bitmapConfig->bitdepth) { /* Other bit depths retain bmsiz. */
            case 4:
                spriteRecord->sprite.bmsiz = 0;
                break;
            case 8:
                spriteRecord->sprite.bmsiz = 1;
                break;
            case 16:
                spriteRecord->sprite.bmsiz = 2;
                break;
            case 32:
                spriteRecord->sprite.bmsiz = 3;
                break;
        }
        spriteRecord->sprite.istart = 0;
        spriteRecord->sprite.istep = 1;
        switch (bitmapConfig->bmfmt) {
            case G_IM_FMT_RGBA:
                if (bitmapConfig->bitdepth == 16) {
                    spriteState->attr = SP_TEXSHUF;
                } else {
                    spriteState->attr = 0; // Preserve zero attributes for other RGBA bit depths.
                }
                break;
            case G_IM_FMT_IA:
            case G_IM_FMT_I:
                spriteState->attr = SP_TEXSHUF;
                break;
            default:
                // RE_UNKNOWN: unsupported formats retain attributes; asset validity and resource lifetime need producer proof.
                break;
        }
        spriteState->expx = 0;
        spriteState->expy = 0;
        spriteState->zdepth = 0x1234;
        spriteState->red = 0xFF;
        spriteState->green = 0xFF;
        spriteState->blue = 0xFF;
        spriteState->alpha = 0xFF;
        spriteState->startTLUT = 0;
        spriteState->nTLUT = 0;
        spriteState->LUT = NULL;
        spriteState->frac_s = 0;
        spriteState->frac_t = 0;
        spriteState->scalex = 1.0f;
        spriteState->scaley = 1.0f;
    }
}

s16 uvGetSpriteWidth(s32 spriteId) {
    if (spriteId >= sMaxSprites) {
        return 0;
    }
    return sSprites[spriteId].sprite.width;
}

s16 uvGetSpriteHeight(s32 spriteId) {
    if (spriteId >= sMaxSprites) {
        return 0;
    }
    return sSprites[spriteId].sprite.height;
}

void uvSprtProps(s32 spriteId, ...) {
    ParsedUVTX* textureConfig;
    Sprite* spriteState;
    s32 requestedHeight;
    s32 requestedWidth;
    s32 propertyCode;
    uvSprite_t* spriteRecord;
    va_list propertyArgs;
    // RE_UNKNOWN: lower index bound, argument-stream extents, asset validity and lifetimes need original caller/producer proof.
    if (spriteId >= sMaxSprites) {
        return;
    }

    va_start(propertyArgs, spriteId);

    spriteRecord = &sSprites[spriteId];
    spriteState = &spriteRecord->sprite;

    while (TRUE) {
        propertyCode = va_arg(propertyArgs, s32);
        switch (propertyCode) {
            case 0:
                return;
            case 1:
                requestedWidth = va_arg(propertyArgs, s32);
                if (requestedWidth <= 0) {
                    requestedWidth = 1;
                }

                requestedHeight = va_arg(propertyArgs, s32);
                if (requestedHeight <= 0) {
                    requestedHeight = 1;
                }

                if (spriteState->width > 0) {
                    spriteState->scalex = requestedWidth / (f32)spriteState->width;
                }

                if (spriteState->height > 0) {
                    spriteState->scaley = requestedHeight / (f32)spriteState->height;
                }
                if ((spriteState->scalex == 1.0f) && (spriteState->scaley == 1.0f)) {
                    spriteState->attr &= ~SP_SCALE;
                } else {
                    spriteState->attr |= SP_SCALE;
                }
                break;
            case 13: // RE_UNKNOWN: native reads two f32 words; original variadic declarations and caller packing need proof.
                spriteState->scalex = va_arg(propertyArgs, f32);
                spriteState->scaley = va_arg(propertyArgs, f32);
                if ((spriteState->scalex == 1.0f) && (spriteState->scaley == 1.0f)) {
                    spriteState->attr &= ~SP_SCALE;
                } else {
                    spriteState->attr |= SP_SCALE;
                }
                break;
            case 2:
                spriteState->x = va_arg(propertyArgs, s32);
                spriteState->y = (sUvGfxMgrExports_uvsprt->uvGetScreenHeight() - va_arg(propertyArgs, s32)) - spriteState->height;
                break;
            case 7:
                spriteState->red = va_arg(propertyArgs, s32);
                spriteState->green = va_arg(propertyArgs, s32);
                spriteState->blue = va_arg(propertyArgs, s32);
                spriteState->alpha = va_arg(propertyArgs, s32);
                break;
            case 3:
                spriteRecord->unk0 = va_arg(propertyArgs, s32);
                break;
            case 6:
                spriteRecord->unk2 = va_arg(propertyArgs, s32);
                break;
            case 9:
                uvSpriteSetBlit(spriteRecord, va_arg(propertyArgs, s32));
                break;
            case 10:
                spriteRecord->textureId = va_arg(propertyArgs, s32);
                if (spriteRecord->textureId != 0xFFF) {
                    textureConfig = uvGetLoadedFile('UVTX', spriteRecord->textureId);
                    if (textureConfig == NULL) {
                        spriteRecord->textureId = 0xFFF;
                    } else {
                        uvSpriteFromBitmap(spriteRecord, textureConfig);
                        uvSpriteInitializeFromTextureOrDefaults(spriteRecord, textureConfig);
                    }
                }
                break;
            case 11:
                if (va_arg(propertyArgs, s32) == 0) {
                    spriteState->attr &= ~SP_TRANSPARENT;
                } else {
                    spriteState->attr |= SP_TRANSPARENT;
                }
                break;
            case 12:
                if (va_arg(propertyArgs, s32) == 0) {
                    spriteState->attr &= ~SP_CUTOUT;
                } else {
                    spriteState->attr |= SP_CUTOUT;
                }
                break;
            case 14:
                if (va_arg(propertyArgs, s32) == 0) {
                    spriteState->attr &= ~SP_EXTERN;
                } else {
                    spriteState->attr |= SP_EXTERN;
                }
                break;
            default:
                break;
        }
    }
}

void uvDrawBitmap(Gfx **gdl, Sprite *s, Bitmap *b, s32 x, s32 y, s32 xx, s32 yy, s32 fs,
                              s32 ft, s32 sx, s32 sy) {
    s32 rs, rt;
    s32 rxh, ryh;
    s32 rxl, ryl;
    Gfx *gdlh;
    s32 tex_width, tex_height;
    Gtexrect gt, *g;
    s32 s_clamp, t_clamp, s_mask, t_mask, s_lod, t_lod;

    g = &gt;

    tex_width = b->width_img;
    tex_height = s->bmHreal;

    gdlh = *gdl;

    /* Scissoring */
    if ((x >= sScissorXmax) || (y >= sScissorYmax)) {
        return;
    }

    if ((xx < sScissorXmin) || (yy < sScissorYmin)) {
        return;
    }

    if (x < sScissorXmin) {
        rxh = sScissorXmin * 4;
        rs = (b->s << 5) + fs + (((sScissorXmin - x) * sx) >> 5);
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Left Edge (%d) not in range (%d,%d)\n", x, sScissorXmin,
                 sScissorXmax);
#endif
    } else {
        rxh = x * 4;
        rs = (b->s << 5) + fs;
    };

    if (y < sScissorYmin) {
        ryh = sScissorYmin * 4;
        rt = (b->t << 5) + ft + (((sScissorYmin - y) * sy) >> 5);
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Top Edge (%d) not in range (%d,%d)\n", y, sScissorYmin,
                 sScissorYmax);
#endif
    } else {
        ryh = y * 4;
        rt = (b->t << 5) + ft;
    }

    if (xx >= sScissorXmax) {
        rxl = sScissorXmax * 4;
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Right Edge (%d) not in range (%d,%d)\n", xx, sScissorXmin,
                 sScissorXmax);
#endif
    } else {
        rxl = xx * 4;
    };

    if (yy >= sScissorYmax) {
        ryl = sScissorYmax * 4;
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Bottom Edge (%d) not in range (%d,%d)\n", yy, sScissorYmin,
                 sScissorYmax);
#endif
    } else {
        ryl = yy * 4;
    };

    s_clamp = G_TX_CLAMP;
    t_clamp = G_TX_CLAMP;
    s_mask = G_TX_NOMASK;
    t_mask = G_TX_NOMASK;
    s_lod = G_TX_NOLOD;
    t_lod = G_TX_NOLOD;

#define LOAD_TEX

#ifdef LOAD_TEX
    if (b->buf != sPrevBitmapBuf) {
        switch (s->bmsiz) {
            case G_IM_SIZ_4b:
                if (s->attr & SP_TEXSHUF) {
                    gDPLoadTextureBlock_4bS(gdlh++, b->buf, s->bmfmt, tex_width, tex_height, 0, s_clamp,
                                            t_clamp, s_mask, t_mask, s_lod, t_lod);
                } else {
                    gDPLoadTextureBlock_4b(gdlh++, b->buf, s->bmfmt, tex_width, tex_height, 0, s_clamp,
                                           t_clamp, s_mask, t_mask, s_lod, t_lod);
                };
                break;

            case G_IM_SIZ_8b:
                if (s->attr & SP_TEXSHUF) {
                    gDPLoadTextureBlockS(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_8b, tex_width, tex_height, 0,
                                         s_clamp, t_clamp, s_mask, t_mask, s_lod, t_lod);
                } else {
                    gDPLoadTextureBlock(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_8b, tex_width, tex_height, 0,
                                        s_clamp, t_clamp, s_mask, t_mask, s_lod, t_lod);
                };
                break;
            case G_IM_SIZ_16b:
                if (s->bmfmt == G_IM_FMT_YUV) {
                    if (s->attr & SP_TEXSHUF) {
                        gDPLoadTextureBlockYuvS(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_16b, tex_width,
                                                tex_height, 0, s_clamp, t_clamp, s_mask, t_mask, s_lod,
                                                t_lod);
                    } else {
                        if (b->LUToffset != 0) { /* Split Y and UV areas */
                            unsigned char *uv, *addr;
                            int j;
                            s32 tmem, siz;

                            gDPSetTextureImage(gdlh++, G_IM_FMT_I, G_IM_SIZ_8b, 1, b->buf);
                            gDPSetTile(gdlh++, G_IM_FMT_I, G_IM_SIZ_8b, 0, 256, G_TX_LOADTILE, 0, t_clamp,
                                       t_mask, t_lod, s_clamp, s_mask, s_lod);
                            gDPLoadSync(gdlh++);
                            gDPLoadBlock(gdlh++, G_TX_LOADTILE, 0, 0, tex_width * tex_height - 1,
                                         CALC_DXT(tex_width, 1));
                            gDPLoadSync(gdlh++);

                            uv = ((unsigned char *) b->buf)
                                 + ((tex_width * tex_height) / 2) * b->LUToffset;

                            for (j = 0; j <= (tex_height / 2); j++) {
                                addr = uv + ((tex_height / 2) - 2 - j) * tex_width;
                                siz = 3 * tex_width;
                                tmem = (tex_width / 8) * (tex_height - 2 - 2 * j);
                                if (tmem < 0) {
                                    addr += (-tmem) * 8;
                                    siz -= (-tmem) * 8;
                                    tmem = 0;
                                };
                                if (j == 0)
                                    siz = 2 * tex_width;

                                gDPSetTextureImage(gdlh++, G_IM_FMT_I, G_IM_SIZ_8b, 1, addr);
                                gDPSetTile(gdlh++, G_IM_FMT_I, G_IM_SIZ_8b, 0, tmem, G_TX_LOADTILE, 0,
                                           t_clamp, t_mask, t_lod, s_clamp, s_mask, s_lod);
                                gDPLoadSync(gdlh++);
                                gDPLoadBlock(gdlh++, G_TX_LOADTILE, 0, 0, siz - 1,
                                             CALC_DXT(tex_width, 1));
                                gDPLoadSync(gdlh++);
                            };

                            gDPSetTile(gdlh++, s->bmfmt, G_IM_SIZ_16b, (((tex_width) * 1) + 7) >> 3, 0,
                                       G_TX_RENDERTILE, 0, t_clamp, t_mask, t_lod, s_clamp, s_mask,
                                       s_lod);
                            gDPSetTileSize(gdlh++, G_TX_RENDERTILE, 0, 0,
                                           ((tex_width) -1) << G_TEXTURE_IMAGE_FRAC,
                                           ((tex_height) -1) << G_TEXTURE_IMAGE_FRAC);

                        } else {
                            gDPLoadTextureBlockYuv(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_16b, tex_width,
                                                   tex_height, 0, s_clamp, t_clamp, s_mask, t_mask,
                                                   s_lod, t_lod);
                        };
                    };
                } else {
                    if (s->attr & SP_TEXSHUF) {
                        gDPLoadTextureBlockS(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_16b, tex_width,
                                             tex_height, 0, s_clamp, t_clamp, s_mask, t_mask, s_lod,
                                             t_lod);
                    } else {
                        gDPLoadTextureBlock(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_16b, tex_width, tex_height,
                                            0, s_clamp, t_clamp, s_mask, t_mask, s_lod, t_lod);
                    };
                };
                break;
            case G_IM_SIZ_32b:
                if (s->attr & SP_TEXSHUF) {
                    gDPLoadTextureBlockS(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_32b, tex_width, tex_height, 0,
                                         s_clamp, t_clamp, s_mask, t_mask, s_lod, t_lod);
                } else {
                    gDPLoadTextureBlock(gdlh++, b->buf, s->bmfmt, G_IM_SIZ_32b, tex_width, tex_height, 0,
                                        s_clamp, t_clamp, s_mask, t_mask, s_lod, t_lod);
                };
                break;
        }
        sPrevBitmapBuf = b->buf;
    }
#endif /* LOAD_TEX */

    g->cmd = G_TEXRECT;
    g->tile = 0;

    g->xh = rxh;
    g->xl = rxl;
    g->yh = ryh;
    g->yl = ryl;

    g->s = rs;
    g->t = rt;

    if ((s->attr & SP_FASTCOPY) && (s->bmfmt != G_IM_FMT_YUV))
        g->dsdx = sx * 4;
    else
        g->dsdx = sx;

    g->dtdy = sy;

    gSPTextureRectangle(gdlh++, g->xh, g->yh, g->xl, g->yl, g->tile, g->s, g->t, g->dsdx, g->dtdy);

    gDPPipeSync(gdlh++);

    *gdl = gdlh;
}

void uvSpriteDrawInit(Gfx **outDisplayList) {
    Gfx *displayListCursor;

    displayListCursor = *outDisplayList;
    sSpriteAttribute = 0;
    sScissorXmin = 0;
    sScissorYmin = 0;
    sScissorXmax = SCREEN_WIDTH;
    sScissorYmax = SCREEN_HEIGHT;
    // RE_UNKNOWN: display-list capacity, aliasing, resource lifetime and shared-state call ordering need caller proof.
    gDPPipeSync(displayListCursor++);
    gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);
    gSPTexture(displayListCursor++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetAlphaCompare(displayListCursor++, G_AC_NONE);
    gDPSetTexturePersp(displayListCursor++, G_TP_NONE);
    gDPSetTextureFilter(displayListCursor++, G_TF_BILERP);
    gDPSetTextureConvert(displayListCursor++, G_TC_FILT);
    gDPSetTextureDetail(displayListCursor++, G_TD_CLAMP);
    gDPSetTextureLOD(displayListCursor++, G_TL_TILE);
    gDPSetTextureLUT(displayListCursor++, G_TT_NONE);

    gDPSetRenderMode(displayListCursor++, SPRITE_SURF, SPRITE_SURF2);
    *outDisplayList = displayListCursor;
}

Gfx* uvSpriteDraw(Sprite* inputSprite) {
    int bitmapIndex;
    s32 x, y;
    float scaleX, scaleY;
    Bitmap* bitmapCursor;
    Gfx* displayListCursor;
    Gfx* displayListStart;
    s32 isx, isy;
    s32 tx, ty;
    s32 tx2, ty2;
    s32 x2, y2;
    float ftx, fty;
    s32 fs, ft;
    s32 ex, ey;
    Sprite* spriteState = inputSprite;
    /* RE_UNKNOWN: sprite/bitmap backing, display-list capacity, aliases, numeric domains and shared-state lifetimes need original producers/callers and runtime-format proof. */
    if (spriteState->attr & SP_HIDDEN) {
        return NULL;
    }

    sPrevBitmapBuf = NULL;

    displayListCursor = spriteState->rsp_dl_next;
    if (displayListCursor == NULL) {
        displayListCursor = spriteState->rsp_dl;
    }
    displayListStart = displayListCursor;

    bitmapCursor = spriteState->bitmap;
    ex = 0;
    ey = 0;

    if (sSpriteAttribute & SP_EXTERN) { /* previous attr was extern? */
        sSpriteAttribute = ~spriteState->attr;  /* Assume previous modes are all different from new ones */
    }


    if (spriteState->attr & SP_EXTERN) { /* current attr is extern? */
        sSpriteAttribute = spriteState->attr;   /* Assume all settings should remain the same */
    }

    if (spriteState->attr != sSpriteAttribute) {
        if ((spriteState->attr & SP_TRANSPARENT) && !(sSpriteAttribute & SP_TRANSPARENT)) {
            gDPSetRenderMode(displayListCursor++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        } else if (!(spriteState->attr & SP_TRANSPARENT) && (sSpriteAttribute & SP_TRANSPARENT)) {
            gDPSetRenderMode(displayListCursor++, SPRITE_SURF, SPRITE_SURF2);
        }

        if ((spriteState->attr & SP_CUTOUT) && !(sSpriteAttribute & SP_CUTOUT)) {
            gDPSetBlendColor(displayListCursor++, 0xff, 0xff, 0xff, 0x01);
            gDPSetAlphaCompare(displayListCursor++, G_AC_THRESHOLD);
        } else if (!(spriteState->attr & SP_CUTOUT) && (sSpriteAttribute & SP_CUTOUT)) {
            gDPSetAlphaCompare(displayListCursor++, G_AC_NONE);
        }

        if ((spriteState->attr & SP_TEXSHIFT) && !(sSpriteAttribute & SP_TEXSHIFT)) {
            gDPSetTextureFilter(displayListCursor++, G_TF_AVERAGE);
        } else if (!(spriteState->attr & SP_TEXSHIFT) && (sSpriteAttribute & SP_TEXSHIFT)) {
            gDPSetTextureFilter(displayListCursor++, G_TF_BILERP);
        }
    }

    sSpriteAttribute = spriteState->attr;

    if (sSpriteAttribute & SP_Z) {
        gDPSetPrimDepth(displayListCursor++, spriteState->zdepth, 0);
    };

    gDPSetPrimColor(displayListCursor++, 0, 0, spriteState->red, spriteState->green, spriteState->blue, spriteState->alpha);

    if (spriteState->bmfmt == G_IM_FMT_IA) { /* RE_UNKNOWN: duplicated IA combine arms retain current C; historical source intent needs original source/compiler proof. */
        if (spriteState->alpha == 0xFF) {
            gDPSetCombineMode(displayListCursor++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        } else {
            gDPSetCombineMode(displayListCursor++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        }
    } else if (spriteState->bmfmt == G_IM_FMT_I) { // @diff to PW64
        gDPSetCombineMode(displayListCursor++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    } else {
        if (spriteState->alpha == 0xFF) {
            gDPSetCombineMode(displayListCursor++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
        } else {
            gDPSetCombineMode(displayListCursor++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        }
    }

    if (spriteState->bmfmt == G_IM_FMT_CI) {
        gDPSetTextureLUT(displayListCursor++, G_TT_RGBA16);
        gDPLoadTLUT(displayListCursor++, spriteState->nTLUT, 256 + spriteState->startTLUT, spriteState->LUT);
        gDPLoadSync(displayListCursor++);
    };


    if ((spriteState->bmfmt == G_IM_FMT_YUV) && (spriteState->attr & SP_FASTCOPY)) {
        gDPSetTextureConvert(displayListCursor++, G_TC_CONV);
        gDPSetTextureFilter(displayListCursor++, G_TF_POINT);
        gDPSetCombineMode(displayListCursor++, G_CC_1CYUV2RGB, G_CC_1CYUV2RGB);
        gDPSetConvert(displayListCursor++, MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5);
    } else if (spriteState->bmfmt == G_IM_FMT_YUV) {
        gDPSetCycleType(displayListCursor++, G_CYC_2CYCLE);
        gDPSetTextureFilter(displayListCursor++, G_TF_BILERP);
        gDPSetTextureConvert(displayListCursor++, G_TC_FILTCONV);
        gDPSetConvert(displayListCursor++, MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5);
        gDPSetCombineMode(displayListCursor++, G_CC_YUV2RGB, G_CC_PASS2);
    }

    if (spriteState->attr & SP_SCALE) {
        scaleX = spriteState->scalex;
        scaleY = spriteState->scaley;
    } else {
        scaleX = 1.0F;
        scaleY = 1.0F;
    }

    isx = (int)((1 << 10) / scaleX + 0.5F);
    isy = (int)((1 << 10) / scaleY + 0.5F);

    if (bitmapCursor) {
        if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
            gDPSetCycleType(displayListCursor++, G_CYC_COPY);

        x = 0.0F;
        y = 0.0F;

        fty = spriteState->y + y * scaleY;
        ty = (int)(fty + 0.99999F);
        ft = (int)(isy * (ty - fty));
        ft = (ft + 16) >> 5;
        if (spriteState->attr & SP_TEXSHIFT)
            ft += 16; /* 1/2 Texel for AntiAliasing */

        if (spriteState->attr & SP_FRACPOS)
            ft += spriteState->frac_t; /* Micro-positioning */

        y2 = y + spriteState->bmheight;
        ty2 = (int)(spriteState->y + y2 * scaleY + 0.99999F);

        if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
            ty2--;

        //rmonPrintf("\tiscale=(%d,%d), %d bitmaps, sprite_size=(%d,%d)\n", isx, isy, s->nbitmaps, s->width, s->height);

        for (bitmapIndex = 0; (bitmapIndex < spriteState->nbitmaps) && (bitmapCursor->width > 0); bitmapIndex++, bitmapCursor++) {
            if ((x + bitmapCursor->width) > spriteState->width) { /* Next bitmap hits edge? */
                int bh;

                x = 0;
                fs = 0;
                ex = 0;
                ey += spriteState->expy;
                y += spriteState->bmheight;     /* Wrap to next line */
                y2 = y + spriteState->bmheight; /* Wrap to next line */

                fty = spriteState->y + y * scaleY;
                ty = (int)(fty + 0.9999F);
                ft = (int)(isy * (ty - fty));
                ft = (ft + 16) >> 5;
                if (spriteState->attr & SP_TEXSHIFT)
                    ft += 16; /* 1/2 Texel for AntiAliasing */

                if (spriteState->attr & SP_FRACPOS)
                    ft += spriteState->frac_t; /* Micro-positioning */

                ty2 = (int)(spriteState->y + y2 * scaleY + 0.9999F);

                ty += ey;
                ty2 += ey;

                if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
                    ty2--;

                /* Fill out to rect. bdy? */

                if ((bitmapCursor->actualHeight != 0))
                    bh = bitmapCursor->actualHeight;
                else
                    bh = spriteState->bmheight;

                if ((y + bh) > spriteState->height) /* Can't wrap any more? */
                    break;
            };

            //rmonPrintf("bm# %d, x,y=(%d,%d) width=%d \n", i, x, y, bitmap->width);

            ftx = spriteState->x + x * scaleX;
            tx = (s32)(ftx + 0.9999F);
            fs = (s32)(isx * (tx - ftx));
            fs = (fs + 16) >> 5;
            if (spriteState->attr & SP_TEXSHIFT)
                fs += 16; /* 1/2 Texel for AntiAliasing */

            if (spriteState->attr & SP_FRACPOS)
                fs += spriteState->frac_s; /* Micro-positioning */

            x2 = x + bitmapCursor->width;
            tx2 = (int)(spriteState->x + x2 * scaleX + 0.9999F);

            if ((bitmapCursor->actualHeight != 0)) {
                y2 = y + bitmapCursor->actualHeight;
                ty2 = (s32)(spriteState->y + y2 * scaleY + 0.9999F);
                ty2 += ey;

                if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
                    ty2--;
            }

            //rmonPrintf("\tfull(%g,%g) = int(%d,%d) + frac(%d,%d)\n", ftx, fty, tx, ty, fs, ft);

            tx += ex;
            tx2 += ex;
            if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
                tx2--;

            if (bitmapCursor->buf != NULL) { /* Skip over null bitmaps (blanks) */
                uvDrawBitmap(&displayListCursor, spriteState, bitmapCursor, tx, ty, tx2, ty2, fs, ft, isx, isy);
            }

            x += bitmapCursor->width;
            ex += spriteState->expx;
        }

        if (spriteState->attr & SP_FASTCOPY)
            gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);

        if (spriteState->bmfmt == G_IM_FMT_YUV) {
            gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);
            gDPSetTextureFilter(displayListCursor++, G_TF_BILERP);
            gDPSetTextureConvert(displayListCursor++, G_TC_FILT);
        };

    } else {
        int rgba;

        x = (s32)spriteState->x;
        y = (s32)spriteState->y;
        x2 = spriteState->x + (spriteState->width * scaleX) - 1;
        y2 = spriteState->y + (spriteState->height * scaleY) - 1;

        if ((x >= sScissorXmax) || (y >= sScissorYmax)) {
            //emPrintf("Sprite Scissoring: FILL Upper Left corner (%d,%d) beyond range (%d,%d)\n", x, y, scissor_xmax, scissor_ymax);
        } else if ((x2 < sScissorXmin) || (y2 < sScissorYmin)) {
            //emPrintf("Sprite Scissoring: FILL Lower Right corner (%d,%d) below range (%d,%d)\n", x2, y2, scissor_xmin, scissor_ymin);
        } else {
            if (x < sScissorXmin) {
                x = sScissorXmin;
            }

            if (x2 >= sScissorXmax) {
                x2 = sScissorXmax - 1;
            }

            if (y < sScissorYmin) {
                y = sScissorYmin;
            }

            if (y2 >= sScissorYmax) {
                y2 = sScissorYmax - 1;
            }

            rgba = GPACK_RGBA5551((spriteState->red), (spriteState->green), (spriteState->blue), (spriteState->alpha >> 7));

            gSPTexture(displayListCursor++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
            gDPSetCycleType(displayListCursor++, G_CYC_FILL);
            gDPSetFillColor(displayListCursor++, (rgba << 16) | (rgba));

            gDPFillRectangle(displayListCursor++, x, y, x2, y2);
            gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);
            gSPTexture(displayListCursor++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        }
    }

    if (spriteState->bmfmt == G_IM_FMT_CI) {
        gDPSetTextureLUT(displayListCursor++, G_TT_NONE);
    };

    gSPEndDisplayList(displayListCursor++);

    spriteState->rsp_dl_next = displayListCursor;
    return (displayListStart);
}

void uvSpriteDrawFinish(Gfx **outDisplayList) {
    Gfx *displayListCursor;

    displayListCursor = *outDisplayList;

    // RE_UNKNOWN: display-list capacity, aliasing, resource lifetime and shared-state call ordering need caller proof.
    gSPTexture(displayListCursor++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(displayListCursor++, G_CC_SHADE, G_CC_SHADE);

    if (sSpriteAttribute & SP_TRANSPARENT) {
        // Select opaque surface rendering when the current attribute requests it.
        gDPSetRenderMode(displayListCursor++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    }

    if (sSpriteAttribute & SP_CUTOUT) {
        // Disable alpha comparison when the current cutout attribute is set.
        gDPSetAlphaCompare(displayListCursor++, G_AC_NONE);
    }

    gSPEndDisplayList(displayListCursor++);

    *outDisplayList = displayListCursor;
}
