// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef struct FontMessage_s {
    s32 x;
    s32 y;
    f32 scaleX;
    f32 scaleY;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s16 str16[50];
    ParsedUVFT *font;
} FontMessage; // size = 0x7C; original queue stride


extern ParsedUVFT *sParsedFont;
extern UvString_Exports *sUvStringExports;
extern UvGfxMgr_Exports *sUvGfxMgrExports_font;
extern UvCback_Exports *sUvCbackExports_font;
extern UvGfxState_Rom_Exports *sUvGfxStateExports;
extern UvSprt_Rom_Exports *sUvSpriteExports;
extern s32 sFontCurWidth; // sFontCurWidth
extern f32 sFontScaleX;   // sFontScaleX
extern f32 sFontScaleY;   // sFontScaleY
extern u8 sFontColorRed;
extern u8 sFontColorGreen;
extern u8 sFontColorBlue;
extern u8 sFontColorAlpha;
extern Sprite sFontSprite;
extern s32 sFontMesgCount;
extern FontMessage sFontMessages[];
extern s32 D_uvfont_rom_00402558;

void uvModuleCleanup(void);
void uvSetFont(s32 id);
void uvFontScale(f64 arg0, f64 arg1);
void uvFontColor(u8 red, u8 green, u8 blue, u8 alpha);
s32 uvFontStrlLen(s32 arg0);
s32 uvFontStr16WidthFont(s32 arg0);
s32 _uvFontStrWidth(ParsedUVFT *font, const char *str);
s32 uvFontWidth(const char *str);
s32 uvFontHeight(void);
s32 uvFontPrintStr16(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvFontPrintStr(s32 x, s32 y, char *str);
s32 _uvFontSpriteWidth(Sprite *sprite, s16 *str16, ParsedUVFT *font);
void uvFontMsgGenDlist(Gfx **gdl, FontMessage *fontMesg);
void uvFontAdvanceResetGate(s32 arg0);
void uvFontGenDList(void);

void __entrypoint_func_uvfont_rom_400000(UvFont_Exports *exports);

/*
 * Publish the font operations, import STRG, GMGR, CBCK, STAT and SPRT in that
 * order, then register the reset-gate callback on graphics callback list 1
 * with two zero arguments. The callback implementation is a separate owner.
 * RE_UNKNOWN: Provider/export-table lifetime, callback scheduling and repeated
 * initialization require the loader and frame callers; imports are unchecked.
 */
#line 55 "src/modules/uvfont_rom.c"
void __entrypoint_func_uvfont_rom_400000(UvFont_Exports *moduleExports) {
    uvUpdateFileAllocPtr(moduleExports);
    moduleExports->uvModuleCleanup = uvModuleCleanup;
    moduleExports->uvFontGenDList = uvFontGenDList;
    moduleExports->uvSetFont = uvSetFont;
    moduleExports->uvFontScale = uvFontScale;
    moduleExports->uvFontColor = uvFontColor;
    moduleExports->uvFontStrlLen = uvFontStrlLen;
    moduleExports->uvFontStr16WidthFont = uvFontStr16WidthFont;
    moduleExports->uvFontWidth = uvFontWidth;
    moduleExports->uvFontHeight = uvFontHeight;
    moduleExports->uvFontPrintStr16 = uvFontPrintStr16;
    moduleExports->uvFontPrintStr = uvFontPrintStr;
#line 59
    sUvStringExports = uvLoadModule('STRG');
    sUvGfxMgrExports_font = uvLoadModule('GMGR');
    sUvCbackExports_font = uvLoadModule('CBCK');
    sUvGfxStateExports = uvLoadModule('STAT');
    sUvSpriteExports = uvLoadModule('SPRT');
    sUvCbackExports_font->uvAddCallback(sUvGfxMgrExports_font->uvGfxGetCallbackList(1),
                                               (s32) uvFontAdvanceResetGate, 0, 0);
}

/*
 * Remove the font reset-gate callback from graphics callback list 1 before
 * unloading STRG, GMGR, CBCK and STAT in that order.
 * RE_ORIGINAL_QUIRK: SPRT is imported by the initializer but is not unloaded
 * here. Preserve that asymmetry instead of inferring dependency ownership.
 * RE_UNKNOWN: Shared reference counts, duplicate cleanup and outstanding
 * queued font messages require the original loader/frame lifecycle.
 */
#line 68 "src/modules/uvfont_rom.c"
void uvModuleCleanup(void) {
    sUvCbackExports_font->uvRemoveCallback(sUvGfxMgrExports_font->uvGfxGetCallbackList(1),
                                               (s32) uvFontAdvanceResetGate);
    uvUnloadModule('STRG');
    uvUnloadModule('GMGR');
    uvUnloadModule('CBCK');
    uvUnloadModule('STAT');
}

#line 77 "src/modules/uvfont_rom.c"
/* Select an already loaded font or load the requested UVFT resource,
 * then take its first bitmap width as the fallback glyph width.
 * RE_ORIGINAL_QUIRK: failed loading leaves the selected font null and
 * does not reset the previous fallback width. */
void uvSetFont(s32 fontId) {
    if (((sParsedFont = uvGetLoadedFile('UVFT', fontId)) != 0)
        || (((sParsedFont = uvLoadFile('UVFT', fontId)) != 0))) {
        sFontCurWidth = sParsedFont->bitmap->width;
    }
}
#line 83 "src/modules/uvfont_rom.c"

void uvFontScale(f64 x, f64 y) {
    sFontScaleX = x;
    sFontScaleY = y;
}

void uvFontColor(u8 red, u8 green, u8 blue, u8 alpha) {
    sFontColorRed = red;
    sFontColorGreen = green;
    sFontColorBlue = blue;
    sFontColorAlpha = alpha;
}

s32 uvFontStrlLen(s32 arg0) {
    return 0;
}

s32 uvFontStr16WidthFont(s32 arg0) {
    return 0;
}

#line 104 "src/modules/uvfont_rom.c"
/* Sum mapped glyph widths, using the current fallback for missing
 * glyphs, and apply the horizontal scale on the normal return path.
 * RE_ORIGINAL_QUIRK: newlines neither add width nor reset the total;
 * the early terminator return bypasses scaling. */
s32 _uvFontStrWidth(ParsedUVFT *font, const char *text) {
    s32 textLength;
    char *glyphCharacter;
    s32 totalWidth;
    s32 charactersVisited;
    s32 textIndex;

    textLength = sUvStringExports->uvStrlen(text);

    totalWidth = 0;
    for (charactersVisited = 0, textIndex = 0; charactersVisited < textLength; charactersVisited++, textIndex++) {
        if (text[textIndex] == 0) {
            return totalWidth;
        }
        if (text[textIndex] == '\n') {
            continue;
        }
        glyphCharacter = sUvStringExports->uvStrChr(font->str, text[textIndex]);
        if (glyphCharacter != 0) {
            totalWidth += font->bitmap[glyphCharacter - font->str].width;
        } else {
            totalWidth += sFontCurWidth;
        }
    }

    return totalWidth * sFontScaleX;
}
#line 131 "src/modules/uvfont_rom.c"

/*
 * Pass the currently selected parsed font and caller text to the existing
 * width helper, returning its result unchanged.
 * RE_UNKNOWN: Selected-font lifetime, text termination and glyph-table
 * coverage are inherited helper/caller preconditions, not checked here.
 */
#line 132 "src/modules/uvfont_rom.c"
s32 uvFontWidth(const char *text) {
    return _uvFontStrWidth(sParsedFont, text);
}

/*
 * Read the selected bitmap signed height, multiply it by the shared vertical
 * scale and convert the result to a signed word with the original truncation.
 * RE_UNKNOWN: Font/bitmap lifetime and finite, representable scaled results
 * require the font selector and scale-setting callers; no clamp is added.
 */
#line 136 "src/modules/uvfont_rom.c"
s32 uvFontHeight(void) {
    return (s32) ((f32) sParsedFont->bitmap->actualHeight * sFontScaleY);
}

s32 uvFontPrintStr16(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#if 0
void uvFontPrintStr(s32 x, s32 y, char *str) {
    char *chrPos;
    s32 i;
    char *s1;
    s32 len;
    UvString_Exports *t1;

    y += (s32) (sParsedFont->bitmap->actualHeight * sFontScaleY);
    y = sUvGfxMgrExports_font->uvGetScreenHeight() - y;
    sFontMessages[sFontMesgCount].x = x;
    sFontMessages[sFontMesgCount].y = y;
    sFontMessages[sFontMesgCount].r = sFontColorRed;
    sFontMessages[sFontMesgCount].g = sFontColorGreen;
    sFontMessages[sFontMesgCount].b = sFontColorBlue;
    sFontMessages[sFontMesgCount].a = sFontColorAlpha;
    sFontMessages[sFontMesgCount].scaleX = sFontScaleX;
    sFontMessages[sFontMesgCount].scaleY = sFontScaleY;
    if (1)
        ;
    len = sUvStringExports->uvStrlen(str);
    if (len > 0x32) {
        str[0x31] = 0;
        len = 0x32;
    }

    for (i = 0; i < len; i++) {
        chrPos = sUvStringExports->uvStrChr(sParsedFont->str, str[i]);
        if (chrPos != NULL) {
            sFontMessages[sFontMesgCount].str16[i] = chrPos - sParsedFont->str;
        } else {
            sFontMessages[sFontMesgCount].str16[i] = -2;
        }
    }

    sFontMessages[sFontMesgCount].str16[len] = -1;
    sFontMessages[sFontMesgCount].font = sParsedFont;
    if (sFontMesgCount < 0x31) {
        sFontMesgCount++;
    }
}
#else
/* Queue a message using the original 124-byte stride and font word at +120.
 * RE_ORIGINAL_QUIRK: when the source length exceeds 50, write source[49] = 0
 * but retain a glyph count of 50. The terminator halfword then writes offset
 * +120, and the following font-pointer store overwrites that same offset.
 * Preserve this original order; this note changes no text or queue behavior.
 * RE_UNKNOWN: mutable-input and caller-length guarantees, actual queue
 * capacity and the glyph consumer's termination contract. Resolve through
 * all print callers, queue allocation/reset writers and glyph consumers;
 * the observed writes alone establish no reachable overflow or player fault. */
#line 186 "src/modules/uvfont_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvfont_rom/uvFontPrintStr.s")
#endif

#line 189 "src/modules/uvfont_rom.c"
/* Copy up to fifty glyph bitmaps into the sprite and return their
 * unscaled total width. The -1 terminator ends the sequence; -2 and -3
 * reserve the first glyph width with a null image pointer.
 * RE_UNKNOWN: other glyph indices require a valid font bitmap range. */
s32 _uvFontSpriteWidth(Sprite *sprite, s16 *glyphIndices, ParsedUVFT *font) {
    s32 totalWidth;
    s32 glyphIndex;
    Bitmap *spriteBitmaps;

    spriteBitmaps = sprite->bitmap;
    for (glyphIndex = 0, totalWidth = 0; glyphIndices[glyphIndex] != -1; glyphIndex++) {
        if (!(glyphIndex < 0x32)) {
            break;
        }
        if ((glyphIndices[glyphIndex] == -2) || (glyphIndices[glyphIndex] == -3)) {
            spriteBitmaps[glyphIndex] = font->bitmap[0];
            spriteBitmaps[glyphIndex].buf = NULL;
            totalWidth += font->bitmap[0].width;
        } else {
            spriteBitmaps[glyphIndex] = font->bitmap[glyphIndices[glyphIndex]];
            totalWidth += font->bitmap[glyphIndices[glyphIndex]].width;
        }
    }
    sprite->nbitmaps = glyphIndex;
    return totalWidth;
}
#line 211 "src/modules/uvfont_rom.c"

#line 212 "src/modules/uvfont_rom.c"
/* Populate the shared font sprite from one queued message, build its
 * glyph bitmap sequence and emit its sprite commands. Preserve the
 * successful-draw adjustment that leaves the caller at the final command. */
void uvFontMsgGenDlist(Gfx **displayList, FontMessage *message) {
    sFontSprite.height = message->font->bitmap->actualHeight;
    sFontSprite.width = _uvFontSpriteWidth(&sFontSprite, message->str16, message->font);
    sFontSprite.bmfmt = message->font->bmfmt;
    sFontSprite.bmsiz = message->font->bmsiz;
    sFontSprite.x = message->x;
    sFontSprite.y = message->y;
    sFontSprite.red = message->r;
    sFontSprite.green = message->g;
    sFontSprite.blue = message->b;
    sFontSprite.alpha = message->a;
    sFontSprite.scalex = message->scaleX;
    sFontSprite.scaley = message->scaleY;
    sFontSprite.rsp_dl = *displayList;
    sFontSprite.rsp_dl_next = NULL;
    if (sUvSpriteExports->uvSpriteDraw(&sFontSprite) != NULL) {
        *displayList = sFontSprite.rsp_dl_next;
        *displayList = *displayList - 1;
    }
}
#line 232 "src/modules/uvfont_rom.c"

#ifdef NEEDS_DATA
extern s32 D_uvfont_rom_004009F0;
extern s32 D_uvfont_rom_00402558;

#line 237 "src/modules/uvfont_rom.c"
/* Increment the static reset gate. When nonzero, restore its sentinel -1
 * and clear the shared font word; the next call advances -1 to zero without
 * clearing. Preserve this alternating behavior and the unused argument. */
void uvFontAdvanceResetGate(s32 unused) {
    static s32 D_uvfont_rom_004009F0;

    D_uvfont_rom_004009F0++;
    if (D_uvfont_rom_004009F0 != 0) {
        D_uvfont_rom_004009F0 = -1;
        D_uvfont_rom_00402558 = 0;
    }
}
#line 246 "src/modules/uvfont_rom.c"
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvfont_rom/uvFontAdvanceResetGate.s")
#endif

#line 250 "src/modules/uvfont_rom.c"
/* Emit the queued font messages inside one sprite drawing scope and
 * clear the queue after advancing the submitted-message total. Preserve
 * the final display-list adjustment and optional shade/combine reset. */
void uvFontGenDList(void) {
    Gfx **displayList;
    s32 messageIndex;

    if (sFontMesgCount == 0) {
        return;
    }

    displayList = sUvGfxMgrExports_font->uvGetDisplayListHead();
    sUvSpriteExports->uvSpriteDrawInit(displayList);
    for (messageIndex = 0; messageIndex < sFontMesgCount; messageIndex++) {
        uvFontMsgGenDlist(displayList, &sFontMessages[messageIndex]);
    }

    sUvSpriteExports->uvSpriteDrawFinish(displayList);
    *displayList -= 1;
    D_uvfont_rom_00402558 += sFontMesgCount;
    sFontMesgCount = 0;
    if (sUvGfxStateExports != NULL) {
        sUvGfxStateExports->uvGfxResetShadeCombineMode();
    }
}
#line 272 "src/modules/uvfont_rom.c"
