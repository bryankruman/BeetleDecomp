// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
typedef struct { u8 unk00[0xC0]; u32 phase; u8 unkC4[8]; f32 time; u8 unkD0; u8 flagD1; } SprayEffectState;
extern f32 D_80025D6C;
extern Snd_Exports *gSndExports;
extern UnkStruct_004005C8 D_spray_00401768;
extern s32 D_spray_004010B0;
void uvUnloadFile(s32 formFileTag, s32 fileId);
typedef struct UnkCbckExports_s { char pad[0x10]; void (*unk10)(s32, void *, s32, s32); } UnkCbckExports;
typedef struct UnkChanExports_s { char pad[0x4]; void (*unk4)(s32, s32, void *, s32); } UnkChanExports;
extern UnkCbckExports *gUvCbckExports;
extern UnkChanExports *gUvChanExports;
void func_spray_0040055C(s32 arg0);
void sprayModuleCleanup();
void sprayRegisterChannelCallback();
void func_spray_00400138();
void spraySetActivationState(SprayEffectState *state, u8 enabled);
#include "uvfvec_rom.h"
#include "uvmath_rom.h"
#include "uvtexture_rom.h"

/* RE_UNKNOWN: these are access views of observed offsets, not allocation or
 * lifetime declarations. The companion vector's physical meaning is unresolved. */
typedef struct {
    Vec3F position;
    Vec3F companion;
    s16 textureCoordinate;
    u8 unknown1A[2];
    f32 segmentLength;
} SprayStripPoint;

typedef struct {
    SprayStripPoint points[6];
    u32 pointCount;
    u32 retiredPointIndex;
    f32 accumulatedLength;
    u8 unknownCC[4];
    u8 reverseTextureCoordinate;
} SprayStripWriteView;

extern UvMath_Exports *gUvMathExports;
extern UvTexture_Exports *gUvTextureExports;
extern f32 D_spray_00401054;
extern f32 D_spray_00401058;
extern f32 D_spray_0040105C;

#line 19 "src/modules/spray.c"
s32 sprayAppendStripPoint(SprayStripWriteView *, Vec3F *, Vec3F *);
void func_spray_0040055C();
void func_spray_0040064C();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/__entrypoint_func_spray_400000.s")

#line 24 "src/modules/spray.c"
/* Unload the two original spray textures, 0x7C followed by 0x7B. */
void sprayModuleCleanup(void) {
    uvUnloadFile(0x55565458, 0x7C);
    uvUnloadFile(0x55565458, 0x7B);
}
#line 28 "src/modules/spray.c"

#line 29 "src/modules/spray.c"
/* Find channel property six and register the original spray callback
 * with no insert-before callback and priority 0xC8. */
void sprayRegisterChannelCallback(s32 channel) {
    s32 callbackList;
    gUvChanExports->unk4(channel, 6, &callbackList, 0);
    gUvCbckExports->unk10(callbackList, func_spray_0040055C, 0, 0xC8);
}
#line 34 "src/modules/spray.c"

/* Acquire the first zero-D1 record in the native eight-step, 0xD4-stride walk;
 * return null at the adjacent shared sound-state label. Reset the original
 * fields, store the selector low byte, then optionally initialize that sound
 * handle, read SND48's scalar and call SND08 with sound44, priority7FFF,
 * the returned scalar times D1050 and pitch0.5. Clear the setup request after
 * that callback returns, regardless of its result; retain record identity.
 * RE_UNKNOWN: selector/field policies, record/shared-handle reuse, ownership,
 * callback mutation and lifetime guarantees need original writers, consumers
 * and teardown. The fixed native walk does not establish all caller domains.
 * A readable draft is 252 versus 264 native bytes, with 65 differing words.
 * Frame 48 becomes 40 and the preserved record home moves 32 to 36; the compiler
 * reuses the endpoint address for the first handle call instead of reloading
 * its original label. All observed field resets, call inputs/order and flag
 * store remain represented, but 22/18 complete relocation records differ.
 * Historical source declarations/local organization remain unknown; keep
 * original assembly until every instruction and relocation matches. */
#line 35 "src/modules/spray.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_00400138.s")

#line 37 "src/modules/spray.c"
/*
 * When the low enabled byte is nonzero and the unsigned phase is at least 2,
 * copy the shared time into state offset 0xCC; otherwise clear byte 0xD1.
 * Always release the shared sound handle next and finally store 1 to the
 * shared word. The successful branch retains byte 0xD1 rather than setting it.
 * RE_UNKNOWN: The phase protocol and shared word/flag meanings remain opaque.
 */
#line 40 "src/modules/spray.c"
void spraySetActivationState(SprayEffectState *state, u8 enabled) {
    if (enabled && state->phase >= 2U) {
        state->time = D_80025D6C;
    } else {
        state->flagD1 = 0;
    }
    gSndExports->sndReleaseHandle(&D_spray_00401768);
    D_spray_004010B0 = 1;
}
#line 38 "src/modules/spray.c"

#line 39 "src/modules/spray.c"
/* Append a position and companion vector to the six-point spray strip.
 * Measure the new segment, advance the signed texture coordinate with the
 * original single direction reversal, and retire the overwritten length.
 * RE_ORIGINAL_QUIRK: a segment below the stored threshold returns zero after
 * copying both vectors and writing its length; the count is not advanced.
 * Texture property one can return without writing outputs; retain that caller
 * assumption, the signed conversion, and the original floating comparisons.
 * RE_UNKNOWN: companion-vector meaning, texture-field units, count wrap,
 * ownership and provider/caller alias guarantees remain unresolved. */
s32 sprayAppendStripPoint(SprayStripWriteView *strip, Vec3F *position,
                       Vec3F *companion) {
    s32 textureFirstValue;
    s32 textureSecondValue;
    SprayStripPoint *retired;
    f32 dx;
    f32 dy;
    f32 dz;
    SprayStripPoint *point;
    SprayStripPoint *previous;
    f32 coordinateStep;
    f32 textureCoordinate;

    if (strip == NULL) {
        return 0;
    }

    point = &strip->points[strip->pointCount % 6U];
    point->position.x = position->x;
    point->position.y = position->y;
    point->position.z = position->z;
    point->companion.x = companion->x;
    point->companion.y = companion->y;
    point->companion.z = companion->z;
    if (strip->pointCount == 0U) {
        point->textureCoordinate = 0;
        point->segmentLength = 0.0f;
        strip->pointCount++;
        return 1;
    }

    previous = &strip->points[(strip->pointCount - 1U) % 6U];
    dx = position->x - previous->position.x;
    dy = position->y - previous->position.y;
    dz = position->z - previous->position.z;
    point->segmentLength = gUvMathExports->uvSqrtf((dx * dx + dy * dy) + dz * dz);
    if (point->segmentLength < D_spray_00401054) {
        return 0;
    }

    gUvTextureExports->uvTextureGetProps(0x7C, 1, &textureFirstValue,
                                       &textureSecondValue, 0);
    coordinateStep = (point->segmentLength / 2.5f) * (f32)textureSecondValue;
    if (strip->reverseTextureCoordinate == 0) {
        textureCoordinate = (f32)previous->textureCoordinate + coordinateStep;
        if (D_spray_00401058 < textureCoordinate) {
            strip->reverseTextureCoordinate = 1;
            coordinateStep = -coordinateStep;
            textureCoordinate = (f32)previous->textureCoordinate + coordinateStep;
        }
    } else if ((f32)previous->textureCoordinate - coordinateStep < D_spray_0040105C) {
        strip->reverseTextureCoordinate = 0;
        textureCoordinate = (f32)previous->textureCoordinate + coordinateStep;
    } else {
        coordinateStep = -coordinateStep;
        textureCoordinate = (f32)previous->textureCoordinate + coordinateStep;
    }
    point->textureCoordinate = (s16)(s32)textureCoordinate;

    strip->pointCount++;
    strip->accumulatedLength += point->segmentLength;
    if (strip->pointCount >= 7U) {
        strip->retiredPointIndex++;
        retired = &strip->points[strip->retiredPointIndex % 6U];
        strip->accumulatedLength -= retired->segmentLength;
        retired->segmentLength = 0.0f;
    }
    return 1;
}
#line 40 "src/modules/spray.c"
/* RE_UNKNOWN: complete spray record layout, byte D1/state C0 meaning, initialization, storage bounds, callback/resource lifetime and historical local storage. Original callback saves/restores fog around a fixed-stride pointer walk ending at the adjacent sound-state label; trace original initializer, record writers, registration and drawing helper before strengthening semantic names, bounds or safety guarantees. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_0040055C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_0040064C.s")

