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

/* Unload GMGR without clearing the stored provider pointer or freeing sprite
 * records in this body. RE_UNKNOWN: module reference ownership, outstanding
 * callbacks and repeated cleanup remain caller/loader lifecycle obligations. */
#line 161 "src/modules/uvsprt_rom.c"
void uvSprtModuleCleanup(void) {
    uvUnloadModule('GMGR');
}
#line 164 "src/modules/uvsprt_rom.c"

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

/*
 * Start drawing from the caller cursor, clear sprite attribute bit 0x20,
 * and clear the next-list pointer before calling uvSpriteDraw. A nonzero
 * return publishes the sprite next pointer minus one Gfx command.
 * RE_UNKNOWN: Writable cursor capacity, sprite backing and aliases, and
 * drawing-provider ownership and lifetime require caller/provider proof.
 */
#line 208 "src/modules/uvsprt_rom.c"
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

/*
 * Find the loaded UVBT resource or load it; leave the sprite unchanged if both
 * attempts fail. On success copy bitmap geometry/format, map bit depths
 * 4/8/16/32 to size codes 0/1/2/3, choose the existing texture-shuffle attribute
 * for RGBA16 or IA/I, then reset color, depth, scale and lookup-table fields.
 * RE_ORIGINAL_QUIRK: Keep the duplicate bitmap store. Other bit depths retain
 * the old size code, and unsupported formats retain the old attributes.
 * RE_UNKNOWN: Asset dimensions/extents, display-list capacity, borrowed bitmap
 * lifetime and resource aliasing require the asset/provider and render paths.
 */
#line 262 "src/modules/uvsprt_rom.c"
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

/* Return zero when spriteId is at least the configured count; otherwise return
 * the signed width halfword from the 0x54-stride sprite record. Negative
 * indices remain unchecked. RE_UNKNOWN: sprite storage lifetime, count
 * consistency and nonnegative indices require callers and pool initialization. */
#line 329 "src/modules/uvsprt_rom.c"
s16 uvGetSpriteWidth(s32 spriteId) {
    if (spriteId >= sMaxSprites) {
        return 0;
    }
    return sSprites[spriteId].sprite.width;
}
#line 335 "src/modules/uvsprt_rom.c"

/* Return zero when spriteId is at least the configured count; otherwise return
 * the signed height halfword from the 0x54-stride sprite record. Negative
 * indices remain unchecked. RE_UNKNOWN: sprite storage lifetime, count
 * consistency and nonnegative indices require callers and pool initialization. */
#line 336 "src/modules/uvsprt_rom.c"
s16 uvGetSpriteHeight(s32 spriteId) {
    if (spriteId >= sMaxSprites) {
        return 0;
    }
    return sSprites[spriteId].sprite.height;
}
#line 342 "src/modules/uvsprt_rom.c"

/*
 * Consume sprite property codes through code zero. Set dimensions/scales,
 * position, RGBA, record bytes and attribute bits; a texture selection
 * looks up UVTX and runs both existing bitmap/initialization calls in order.
 * RE_ORIGINAL_QUIRK: Only the upper sprite-index bound is checked. Unknown
 * codes consume no payload; case 13 reads f32 directly from the va_list.
 * RE_UNKNOWN: Negative indices, variadic caller packing/stream bounds,
 * asset validity and old/new texture lifetimes are not proved here.
 */
#line 343 "src/modules/uvsprt_rom.c"
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

/* Clip the bitmap rectangle to the shared scissor, advancing S/T for the
 * clipped left/top edges. Load the selected texture format only when its
 * buffer address changes, then emit the rectangle and publish the cursor.
 * RE_UNKNOWN: Command/backing capacities, signed arithmetic domains and
 * cache validity require original allocators, asset producers and callers.
 * The split-YUV inclusive row loop and unknown-size cache update remain
 * unchanged; these paths do not establish valid resource domains. */
#line 457 "src/modules/uvsprt_rom.c"
void uvDrawBitmap(Gfx **outDisplayList, Sprite *spriteState, Bitmap *bitmapState, s32 startX, s32 startY, s32 endX, s32 endY, s32 textureOffsetS,
                              s32 textureOffsetT, s32 textureStepS, s32 textureStepT) {
    s32 clippedS, clippedT;
    s32 rectangleLeftQ2, rectangleTopQ2;
    s32 rectangleRightQ2, rectangleBottomQ2;
    Gfx *displayListCursor;
    s32 textureWidth, textureHeight;
    Gtexrect rectangleFields, *rectangleFieldView;
    s32 clampS, clampT, maskS, maskT, lodS, lodT;

    rectangleFieldView = &rectangleFields;

    textureWidth = bitmapState->width_img;
    textureHeight = spriteState->bmHreal; /* Snapshot bitmap width and sprite real height before either scissor early return. */

    displayListCursor = *outDisplayList;
    /* RE_UNKNOWN: writable command capacity, backing extents, aliases and lifetimes need original allocators/producers and full caller contracts; macro overhead estimates are not bounds. */
    /* Clip endpoints and adjust texture coordinates. RE_UNKNOWN: valid signed ranges and packed truncation intent need original callers/assets and command-format evidence. */
    if ((startX >= sScissorXmax) || (startY >= sScissorYmax)) {
        return;
    }

    if ((endX < sScissorXmin) || (endY < sScissorYmin)) {
        return;
    }

    if (startX < sScissorXmin) {
        rectangleLeftQ2 = sScissorXmin * 4;
        clippedS = (bitmapState->s << 5) + textureOffsetS + (((sScissorXmin - startX) * textureStepS) >> 5);
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Left Edge (%d) not in range (%d,%d)\n", startX, sScissorXmin,
                 sScissorXmax);
#endif
    } else {
        rectangleLeftQ2 = startX * 4;
        clippedS = (bitmapState->s << 5) + textureOffsetS;
    };

    if (startY < sScissorYmin) {
        rectangleTopQ2 = sScissorYmin * 4;
        clippedT = (bitmapState->t << 5) + textureOffsetT + (((sScissorYmin - startY) * textureStepT) >> 5);
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Top Edge (%d) not in range (%d,%d)\n", startY, sScissorYmin,
                 sScissorYmax);
#endif
    } else {
        rectangleTopQ2 = startY * 4;
        clippedT = (bitmapState->t << 5) + textureOffsetT;
    }

    if (endX >= sScissorXmax) {
        rectangleRightQ2 = sScissorXmax * 4;
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Right Edge (%d) not in range (%d,%d)\n", endX, sScissorXmin,
                 sScissorXmax);
#endif
    } else {
        rectangleRightQ2 = endX * 4;
    };

    if (endY >= sScissorYmax) {
        rectangleBottomQ2 = sScissorYmax * 4;
#ifdef DEBUG_SCISSOR
        emPrintf("Sprite Scissoring: Bottom Edge (%d) not in range (%d,%d)\n", endY, sScissorYmin,
                 sScissorYmax);
#endif
    } else {
        rectangleBottomQ2 = endY * 4;
    };

    clampS = G_TX_CLAMP;
    clampT = G_TX_CLAMP;
    maskS = G_TX_NOMASK;
    maskT = G_TX_NOMASK;
    lodS = G_TX_NOLOD;
    lodT = G_TX_NOLOD;

#define LOAD_TEX

#ifdef LOAD_TEX
    if (bitmapState->buf != sPrevBitmapBuf) { /* The native cache key compares only the buffer word; format and dimensions are not separate keys. */
        switch (spriteState->bmsiz) {
            case G_IM_SIZ_4b:
                if (spriteState->attr & SP_TEXSHUF) {
                    gDPLoadTextureBlock_4bS(displayListCursor++, bitmapState->buf, spriteState->bmfmt, textureWidth, textureHeight, 0, clampS,
                                            clampT, maskS, maskT, lodS, lodT);
                } else {
                    gDPLoadTextureBlock_4b(displayListCursor++, bitmapState->buf, spriteState->bmfmt, textureWidth, textureHeight, 0, clampS,
                                           clampT, maskS, maskT, lodS, lodT);
                };
                break;

            case G_IM_SIZ_8b:
                if (spriteState->attr & SP_TEXSHUF) {
                    gDPLoadTextureBlockS(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                                         clampS, clampT, maskS, maskT, lodS, lodT);
                } else {
                    gDPLoadTextureBlock(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                                        clampS, clampT, maskS, maskT, lodS, lodT);
                };
                break;
            case G_IM_SIZ_16b:
                if (spriteState->bmfmt == G_IM_FMT_YUV) {
                    if (spriteState->attr & SP_TEXSHUF) {
                        gDPLoadTextureBlockYuvS(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_16b, textureWidth,
                                                textureHeight, 0, clampS, clampT, maskS, maskT, lodS,
                                                lodT);
                    } else {
                        if (bitmapState->LUToffset != 0) { /* Preserve native split-load addressing and inclusive row loop. RE_UNKNOWN: split-data layout and readable extent need original resource producers. */
                            unsigned char *splitDataBase, *rowDataAddress;
                            int rowIndex;
                            s32 tileMemoryOffset, loadCount;

                            gDPSetTextureImage(displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 1, bitmapState->buf);
                            gDPSetTile(displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 0, 256, G_TX_LOADTILE, 0, clampT,
                                       maskT, lodT, clampS, maskS, lodS);
                            gDPLoadSync(displayListCursor++);
                            gDPLoadBlock(displayListCursor++, G_TX_LOADTILE, 0, 0, textureWidth * textureHeight - 1,
                                         CALC_DXT(textureWidth, 1));
                            gDPLoadSync(displayListCursor++);

                            splitDataBase = ((unsigned char *) bitmapState->buf)
                                 + ((textureWidth * textureHeight) / 2) * bitmapState->LUToffset;

                            for (rowIndex = 0; rowIndex <= (textureHeight / 2); rowIndex++) {
                                rowDataAddress = splitDataBase + ((textureHeight / 2) - 2 - rowIndex) * textureWidth;
                                loadCount = 3 * textureWidth;
                                tileMemoryOffset = (textureWidth / 8) * (textureHeight - 2 - 2 * rowIndex);
                                if (tileMemoryOffset < 0) {
                                    rowDataAddress += (-tileMemoryOffset) * 8;
                                    loadCount -= (-tileMemoryOffset) * 8;
                                    tileMemoryOffset = 0;
                                };
                                if (rowIndex == 0)
                                    loadCount = 2 * textureWidth;

                                gDPSetTextureImage(displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 1, rowDataAddress);
                                gDPSetTile(displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 0, tileMemoryOffset, G_TX_LOADTILE, 0,
                                           clampT, maskT, lodT, clampS, maskS, lodS);
                                gDPLoadSync(displayListCursor++);
                                gDPLoadBlock(displayListCursor++, G_TX_LOADTILE, 0, 0, loadCount - 1,
                                             CALC_DXT(textureWidth, 1));
                                gDPLoadSync(displayListCursor++);
                            };

                            gDPSetTile(displayListCursor++, spriteState->bmfmt, G_IM_SIZ_16b, (((textureWidth) * 1) + 7) >> 3, 0,
                                       G_TX_RENDERTILE, 0, clampT, maskT, lodT, clampS, maskS,
                                       lodS);
                            gDPSetTileSize(displayListCursor++, G_TX_RENDERTILE, 0, 0,
                                           ((textureWidth) -1) << G_TEXTURE_IMAGE_FRAC,
                                           ((textureHeight) -1) << G_TEXTURE_IMAGE_FRAC);

                        } else {
                            gDPLoadTextureBlockYuv(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_16b, textureWidth,
                                                   textureHeight, 0, clampS, clampT, maskS, maskT,
                                                   lodS, lodT);
                        };
                    };
                } else {
                    if (spriteState->attr & SP_TEXSHUF) {
                        gDPLoadTextureBlockS(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_16b, textureWidth,
                                             textureHeight, 0, clampS, clampT, maskS, maskT, lodS,
                                             lodT);
                    } else {
                        gDPLoadTextureBlock(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_16b, textureWidth, textureHeight,
                                            0, clampS, clampT, maskS, maskT, lodS, lodT);
                    };
                };
                break;
            case G_IM_SIZ_32b:
                if (spriteState->attr & SP_TEXSHUF) {
                    gDPLoadTextureBlockS(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_32b, textureWidth, textureHeight, 0,
                                         clampS, clampT, maskS, maskT, lodS, lodT);
                } else {
                    gDPLoadTextureBlock(displayListCursor++, bitmapState->buf, spriteState->bmfmt, G_IM_SIZ_32b, textureWidth, textureHeight, 0,
                                        clampS, clampT, maskS, maskT, lodS, lodT);
                };
                break;
        }
        sPrevBitmapBuf = bitmapState->buf; /* RE_ORIGINAL_QUIRK: native publishes buf to the cache even when bmsiz is outside 0..3 and no load case runs; caller reachability remains unknown. */
    }
#endif /* LOAD_TEX */
    /* RE_UNKNOWN: buffer-address cache validity across data/format changes needs original resource lifetimes and render-order proof. */
    rectangleFieldView->cmd = G_TEXRECT;
    rectangleFieldView->tile = 0; /* Rectangle coordinates retain the original multiply-by-four and packed-field conversions. */

    rectangleFieldView->xh = rectangleLeftQ2;
    rectangleFieldView->xl = rectangleRightQ2;
    rectangleFieldView->yh = rectangleTopQ2;
    rectangleFieldView->yl = rectangleBottomQ2;

    rectangleFieldView->s = clippedS;
    rectangleFieldView->t = clippedT;

    if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
        rectangleFieldView->dsdx = textureStepS * 4;
    else
        rectangleFieldView->dsdx = textureStepS;

    rectangleFieldView->dtdy = textureStepT;

    gSPTextureRectangle(displayListCursor++, rectangleFieldView->xh, rectangleFieldView->yh, rectangleFieldView->xl, rectangleFieldView->yl, rectangleFieldView->tile, rectangleFieldView->s, rectangleFieldView->t, rectangleFieldView->dsdx, rectangleFieldView->dtdy);

    gDPPipeSync(displayListCursor++);

    *outDisplayList = displayListCursor;
}
#line 664 "src/modules/uvsprt_rom.c"

/*
 * Reset shared sprite attributes and the 320-by-240 scissor limits, then
 * emit the existing sprite drawing setup commands and advance the caller
 * cursor. Preserve command order and the exact texture/render-mode values.
 * RE_UNKNOWN: Output capacity, cursor aliases and legal ordering with
 * other drawing users require caller proof; no prior GPU state is saved.
 */
#line 665 "src/modules/uvsprt_rom.c"
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

/* Return NULL for hidden sprites. Otherwise emit attribute/color state,
 * walk bitmap segments with row wrapping and expansion offsets, or draw
 * a clipped solid fill when the bitmap pointer is null. Finish the list,
 * publish its next cursor and return its captured start.
 * RE_UNKNOWN: Bitmap/list capacities, scale/conversion domains, aliases
 * and shared render-state lifetimes require producers and all callers.
 * Preserve fresh field reads and the differing initial/wrapped Y biases;
 * null bitmap buffers still advance geometry without emitting a tile. */
#line 690 "src/modules/uvsprt_rom.c"
Gfx* uvSpriteDraw(Sprite* inputSprite) {
    int bitmapIndex;
    s32 bitmapX, bitmapY;
    float scaleX, scaleY;
    Bitmap* bitmapCursor;
    Gfx* displayListCursor;
    Gfx* displayListStart;
    s32 textureStepS, textureStepT;
    s32 screenLeft, screenTop;
    s32 screenRight, screenBottom;
    s32 bitmapRight, bitmapBottom;
    float scaledLeft, scaledTop;
    s32 fractionS, fractionT;
    s32 extraX, extraY;
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
    extraX = 0;
    extraY = 0;

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

    textureStepS = (int)((1 << 10) / scaleX + 0.5F); /* RE_UNKNOWN: Zero, negative or nonfinite scale and integer-conversion range are not checked here. */
    textureStepT = (int)((1 << 10) / scaleY + 0.5F);

    if (bitmapCursor) {
        if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
            gDPSetCycleType(displayListCursor++, G_CYC_COPY);

        bitmapX = 0.0F;
        bitmapY = 0.0F;

        scaledTop = spriteState->y + bitmapY * scaleY;
        screenTop = (int)(scaledTop + 0.99999F); /* RE_ORIGINAL_QUIRK: Initial Y uses0.99999F; later wrapped rows use0.9999F. Preserve both literals. */
        fractionT = (int)(textureStepT * (screenTop - scaledTop));
        fractionT = (fractionT + 16) >> 5;
        if (spriteState->attr & SP_TEXSHIFT)
            fractionT += 16; /* 1/2 Texel for AntiAliasing */

        if (spriteState->attr & SP_FRACPOS)
            fractionT += spriteState->frac_t; /* Micro-positioning */

        bitmapBottom = bitmapY + spriteState->bmheight;
        screenBottom = (int)(spriteState->y + bitmapBottom * scaleY + 0.99999F);

        if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
            screenBottom--;

        //rmonPrintf("\tiscale=(%d,%d), %d bitmaps, sprite_size=(%d,%d)\n", isx, isy, s->nbitmaps, s->width, s->height);

        for (bitmapIndex = 0; (bitmapIndex < spriteState->nbitmaps) && (bitmapCursor->width > 0); bitmapIndex++, bitmapCursor++) {
            if ((bitmapX + bitmapCursor->width) > spriteState->width) { /* Next bitmap hits edge? */
                int rowBitmapHeight;

                bitmapX = 0;
                fractionS = 0;
                extraX = 0;
                extraY += spriteState->expy;
                bitmapY += spriteState->bmheight;     /* Wrap to next line */
                bitmapBottom = bitmapY + spriteState->bmheight; /* Wrap to next line */

                scaledTop = spriteState->y + bitmapY * scaleY;
                screenTop = (int)(scaledTop + 0.9999F);
                fractionT = (int)(textureStepT * (screenTop - scaledTop));
                fractionT = (fractionT + 16) >> 5;
                if (spriteState->attr & SP_TEXSHIFT)
                    fractionT += 16; /* 1/2 Texel for AntiAliasing */

                if (spriteState->attr & SP_FRACPOS)
                    fractionT += spriteState->frac_t; /* Micro-positioning */

                screenBottom = (int)(spriteState->y + bitmapBottom * scaleY + 0.9999F);

                screenTop += extraY;
                screenBottom += extraY;

                if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
                    screenBottom--;

                /* Fill out to rect. bdy? */

                if ((bitmapCursor->actualHeight != 0))
                    rowBitmapHeight = bitmapCursor->actualHeight;
                else
                    rowBitmapHeight = spriteState->bmheight;

                if ((bitmapY + rowBitmapHeight) > spriteState->height) /* Can't wrap any more? */
                    break;
            };

            //rmonPrintf("bm# %d, x,y=(%d,%d) width=%d \n", i, x, y, bitmap->width);

            scaledLeft = spriteState->x + bitmapX * scaleX;
            screenLeft = (s32)(scaledLeft + 0.9999F);
            fractionS = (s32)(textureStepS * (screenLeft - scaledLeft));
            fractionS = (fractionS + 16) >> 5;
            if (spriteState->attr & SP_TEXSHIFT)
                fractionS += 16; /* 1/2 Texel for AntiAliasing */

            if (spriteState->attr & SP_FRACPOS)
                fractionS += spriteState->frac_s; /* Micro-positioning */

            bitmapRight = bitmapX + bitmapCursor->width;
            screenRight = (int)(spriteState->x + bitmapRight * scaleX + 0.9999F);

            if ((bitmapCursor->actualHeight != 0)) {
                bitmapBottom = bitmapY + bitmapCursor->actualHeight;
                screenBottom = (s32)(spriteState->y + bitmapBottom * scaleY + 0.9999F);
                screenBottom += extraY;

                if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
                    screenBottom--;
            }

            //rmonPrintf("\tfull(%g,%g) = int(%d,%d) + frac(%d,%d)\n", ftx, fty, tx, ty, fs, ft);

            screenLeft += extraX;
            screenRight += extraX;
            if ((spriteState->attr & SP_FASTCOPY) && (spriteState->bmfmt != G_IM_FMT_YUV))
                screenRight--;

            if (bitmapCursor->buf != NULL) { /* Skip over null bitmaps (blanks) */
                uvDrawBitmap(&displayListCursor, spriteState, bitmapCursor, screenLeft, screenTop, screenRight, screenBottom, fractionS, fractionT, textureStepS, textureStepT);
            }

            bitmapX += bitmapCursor->width; /* Advance geometry even when a null bitmap buffer skipped the draw call. */
            extraX += spriteState->expx;
        }

        if (spriteState->attr & SP_FASTCOPY)
            gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);

        if (spriteState->bmfmt == G_IM_FMT_YUV) {
            gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);
            gDPSetTextureFilter(displayListCursor++, G_TF_BILERP);
            gDPSetTextureConvert(displayListCursor++, G_TC_FILT);
        };

    } else {
        int fillColorRgba5551;

        bitmapX = (s32)spriteState->x;
        bitmapY = (s32)spriteState->y;
        bitmapRight = spriteState->x + (spriteState->width * scaleX) - 1;
        bitmapBottom = spriteState->y + (spriteState->height * scaleY) - 1;

        if ((bitmapX >= sScissorXmax) || (bitmapY >= sScissorYmax)) {
            //emPrintf("Sprite Scissoring: FILL Upper Left corner (%d,%d) beyond range (%d,%d)\n", x, y, scissor_xmax, scissor_ymax);
        } else if ((bitmapRight < sScissorXmin) || (bitmapBottom < sScissorYmin)) {
            //emPrintf("Sprite Scissoring: FILL Lower Right corner (%d,%d) below range (%d,%d)\n", x2, y2, scissor_xmin, scissor_ymin);
        } else {
            if (bitmapX < sScissorXmin) {
                bitmapX = sScissorXmin;
            }

            if (bitmapRight >= sScissorXmax) {
                bitmapRight = sScissorXmax - 1;
            }

            if (bitmapY < sScissorYmin) {
                bitmapY = sScissorYmin;
            }

            if (bitmapBottom >= sScissorYmax) {
                bitmapBottom = sScissorYmax - 1;
            }

            fillColorRgba5551 = GPACK_RGBA5551((spriteState->red), (spriteState->green), (spriteState->blue), (spriteState->alpha >> 7));

            gSPTexture(displayListCursor++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
            gDPSetCycleType(displayListCursor++, G_CYC_FILL);
            gDPSetFillColor(displayListCursor++, (fillColorRgba5551 << 16) | (fillColorRgba5551));

            gDPFillRectangle(displayListCursor++, bitmapX, bitmapY, bitmapRight, bitmapBottom);
            gDPSetCycleType(displayListCursor++, G_CYC_1CYCLE);
            gSPTexture(displayListCursor++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        }
    }

    if (spriteState->bmfmt == G_IM_FMT_CI) {
        gDPSetTextureLUT(displayListCursor++, G_TT_NONE);
    };

    gSPEndDisplayList(displayListCursor++);

    spriteState->rsp_dl_next = displayListCursor; /* Publish the cursor after the end command; the returned pointer is the earlier list start. */
    return (displayListStart);
}
#line 970 "src/modules/uvsprt_rom.c"

/*
 * Disable texturing and select shade combining. SP_TRANSPARENT selects
 * opaque surface mode; SP_CUTOUT disables alpha comparison. Append the
 * end command and publish the advanced cursor in this exact order.
 * RE_UNKNOWN: Cursor capacity/aliases and shared drawing-state ordering
 * require caller proof. This writes selected states without saving or
 * restoring a complete earlier GPU state.
 */
#line 971 "src/modules/uvsprt_rom.c"
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
