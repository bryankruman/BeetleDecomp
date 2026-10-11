/*__SEEDEXTERNS__*/
extern int D_filmroll_00400A78;
extern float D_filmroll_004009A4;
typedef struct {
    /* 0x00 */ int stateWord;
    /* 0x04 */ int firstSampleInteger;
    /* 0x08 */ int secondSampleInteger;
    /* 0x0C */ int trailingWord;
} FilmrollRandomizedEntry;
typedef struct {
    /* 0x00 */ char pad[0x34];
    /* 0x34 */ float (*randomUnitFloat)(void);
} FilmrollRandomExports;
extern FilmrollRandomExports *gUvMathExports;
// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
#include "uvgfxmgr_rom.h"
#include "uv_scheduler.h"
extern UvGfxMgr_Exports *gUvGfxMgrExports;
/* Access-only sound export prefix, verified against original bindings and
 * target input consumption. The sound-handle object remains opaque here.
 * RE_UNKNOWN: complete handle allocation/lifetime and historical source ABI. */
typedef struct {
    u8 unknown00[0x30];
    void (*updateManagedSounds)(void);
    u8 unknown34[0x14];
    f32 (*getSfxVolumeScale)(void);
    u8 unknown4C[0x14];
    s16 (*startHandleSound)(void *, s16, s32, f32);
    u8 unknown64[0xC];
    void (*releaseHandle)(void *);
    u8 unknown74[0x58];
    void (*initializeHandle)(void *);
} FilmrollSoundExports;
extern FilmrollSoundExports *gSndExports;
/* Only the first two address words are accessed; this declaration supplies
 * no total allocation extent or inferred framebuffer ownership.
 * RE_UNKNOWN: original range producers, bounds, alignment and lifetime. */
extern u32 D_filmroll_004009C8[];
extern u8 D_filmroll_004009D0[];
extern f32 D_filmroll_004009A0;
void func_filmroll_00400060(void);
void func_filmroll_00400068(s32);
void filmrollSwapBufferRangeAndClearSwapSuppression(void);
void filmrollSwapBufferRangeWithAlternatingBlack(void);
void func_filmroll_00400720(void);
/* Initializer storage view: original 32-bit callback addresses only.
 * RE_UNKNOWN: callback-facing roles and intended historical declarations;
 * trace export consumers before introducing a callable interface. */
typedef struct FilmrollExportAddresses {
    u32 emptyCallbackAddress;
    u32 callback04Address;
    u32 callback08Address;
    u32 callback0CAddress;
    u32 callback10Address;
} FilmrollExportAddresses;
#line 33 "src/modules/filmroll.c"
/*
 * Update the allocation pointer and publish the five original code addresses
 * at offsets 0x00 through 0x10. Preserve the separate empty callback and both
 * swap callbacks; publishing the table does not perform a buffer swap.
 * RE_UNKNOWN: Export-storage lifetime and opaque callback signatures at 0x04
 * and 0x10 require their original implementations and consumers.
 */
#line 39 "src/modules/filmroll.c"
void __entrypoint_func_filmrollInitializeModuleExports(FilmrollExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32)func_filmroll_00400060;
    exports->callback04Address = (u32)func_filmroll_00400068;
    exports->callback08Address = (u32)filmrollSwapBufferRangeAndClearSwapSuppression;
    exports->callback0CAddress = (u32)filmrollSwapBufferRangeWithAlternatingBlack;
    exports->callback10Address = (u32)func_filmroll_00400720;
}
#line 34 "src/modules/filmroll.c"

#line 18 "src/modules/filmroll.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_filmroll_00400060(void) {
}
#line 20 "src/modules/filmroll.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400068.s")

#line 23 "src/modules/filmroll.c"
/* Advance the original unsigned buffer-address cursor toward the shared
 * target in signed 3,840-byte steps, preserving the sound update, graphics
 * begin/end, video-interface swap and requested wait on each iteration.
 * After the loop, swap to a freshly loaded target, wait, copy framebuffer
 * direction 1, clear scheduler swap suppression, update sound and begin
 * graphics again. The otherwise unused phase toggle is original behavior.
 * RE_UNKNOWN: valid address window/alignment, target mutation, cursor wrap
 * and loop termination, and intended visual effect require original range
 * setup/callers and display consumers. Accesses establish neither complete
 * buffer storage nor ownership. The unused phase's intended source role
 * requires original source or a corresponding transition implementation. */
void filmrollSwapBufferRangeAndClearSwapSuppression(void) {
    u32 cursor;
    s32 step;
    s32 direction;
    s32 phase;

    cursor = D_filmroll_004009C8[0];
    phase = 0;
    gUvGfxMgrExports->uvGfxEnd();
    gUvGfxMgrExports->uvGfxWaitIfRequested();
    if (cursor < D_filmroll_004009C8[1]) {
        direction = 1;
    } else {
        direction = -1;
    }
    while ((direction == -1 && D_filmroll_004009C8[1] < cursor)
           || (direction == 1 && cursor < D_filmroll_004009C8[1])) {
        step = direction * 3840;
        gSndExports->updateManagedSounds();
        gUvGfxMgrExports->uvGfxBegin();
        gUvGfxMgrExports->uvGfxEnd();
        osViSwapBuffer((void *)cursor);
        gUvGfxMgrExports->uvGfxWaitIfRequested();
        cursor += step;
        /* RE_ORIGINAL_QUIRK: the original toggles this local every step,
         * but no later operation reads its final value. Its source role
         * remains unknown; retain the observed arithmetic. */
        phase = 1 - phase;
    }
    gSndExports->updateManagedSounds();
    gUvGfxMgrExports->uvGfxBegin();
    gUvGfxMgrExports->uvGfxEnd();
    osViSwapBuffer((void *)D_filmroll_004009C8[1]);
    gUvGfxMgrExports->uvGfxWaitIfRequested();
    gUvGfxMgrExports->uvCopyFrameBuf(1);
    uvScSetBufferSwapSuppressed(0);
    gSndExports->updateManagedSounds();
    gUvGfxMgrExports->uvGfxBegin();
}
#line 24 "src/modules/filmroll.c"

#line 25 "src/modules/filmroll.c"
/* Advance the original unsigned buffer-address cursor toward the shared
 * target in signed 4,480-byte steps. Preserve each sound update, graphics
 * begin/end, video-interface swap and requested wait in their original order;
 * alternate video black state after each step, then restore visible output.
 * Initialize the shared sound handle, start sound 0x59 with flags 0x1F40 and
 * the getter result times the original scalar, and release it after the loop.
 * Copy the final framebuffer according to the phase, then begin graphics.
 * RE_UNKNOWN: range producers, valid byte window/alignment, target mutation
 * and cursor wrap/termination guarantees, sound-handle lifetime and intended
 * visual effect require original setup/callers and display consumers. No
 * remaining range or framebuffer ownership is inferred from these accesses. */
void filmrollSwapBufferRangeWithAlternatingBlack(void) {
    u32 cursor;
    s32 step;
    s32 direction;
    s32 phase;
    f32 volumeScale;

    cursor = D_filmroll_004009C8[0];
    phase = 0;
    gUvGfxMgrExports->uvGfxEnd();
    gUvGfxMgrExports->uvGfxWaitIfRequested();
    if (cursor < D_filmroll_004009C8[1]) {
        direction = 1;
    } else {
        direction = -1;
    }
    gSndExports->initializeHandle(D_filmroll_004009D0);
    volumeScale = gSndExports->getSfxVolumeScale();
    gSndExports->startHandleSound(D_filmroll_004009D0, 0x59, 0x1F40,
                                volumeScale * D_filmroll_004009A0);
    while ((direction == -1 && D_filmroll_004009C8[1] < cursor)
           || (direction == 1 && cursor < D_filmroll_004009C8[1])) {
        step = direction * 4480;
        gSndExports->updateManagedSounds();
        gUvGfxMgrExports->uvGfxBegin();
        gUvGfxMgrExports->uvGfxEnd();
        osViSwapBuffer((void *)cursor);
        gUvGfxMgrExports->uvGfxWaitIfRequested();
        cursor += step;
        if (phase != 0) {
            osViBlack(0);
        } else {
            osViBlack(1);
        }
        phase = 1 - phase;
    }
    osViBlack(0);
    gSndExports->releaseHandle(D_filmroll_004009D0);
    gUvGfxMgrExports->uvCopyFrameBuf(phase);
    gUvGfxMgrExports->uvGfxBegin();
}
#line 26 "src/modules/filmroll.c"

/* RE_UNKNOWN: four entry-word roles, incremented shared word and scale units
 * need original entry draw/update consumers and state/scale producers; names
 * describe observed writes/sampling only, not position/size or activation. */
#line 28 "src/modules/filmroll.c"
#line 28 "src/modules/filmroll.c"
/* Increment the shared word, store1 and fill two integer fields from separate
 * random samples, then clear the trailing word. Preserve both calls, store
 * order and the original float-to-integer truncation; unknown roles noted above. */
void filmrollInitializeRandomizedEntry(FilmrollRandomizedEntry *entry) {
    float secondSample;

    D_filmroll_00400A78 += 1;
    entry->stateWord = 1;
    entry->firstSampleInteger = (int) (gUvMathExports->randomUnitFloat() * D_filmroll_004009A4);
    secondSample = gUvMathExports->randomUnitFloat() * 239.0f;
    entry->trailingWord = 0;
    entry->secondSampleInteger = (int) secondSample;
}
#line 41 "src/modules/filmroll.c"
#line 38 "src/modules/filmroll.c"

#line 39 "src/modules/filmroll.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_filmroll_0040062C(void) {
}
#line 41 "src/modules/filmroll.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400720.s")

