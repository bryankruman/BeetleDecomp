/*__SEEDEXTERNS__*/
extern int D_filmroll_00400A78;
extern float D_filmroll_004009A4;
typedef struct {
    /* 0x00 */ int unk0;
    /* 0x04 */ int unk4;
    /* 0x08 */ int unk8;
    /* 0x0C */ int unkC;
} Node_00400588;
typedef struct {
    /* 0x00 */ char pad[0x34];
    /* 0x34 */ float (*unk34)(void);
} UvMathExp_00400588;
extern UvMathExp_00400588 *gUvMathExports;
// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
#include "uvgfxmgr_rom.h"
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
void func_filmroll_00400170(void);
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
/* Set the file allocation pointer and publish the five original callback
 * addresses in their original order. The first callback is the separate
 * empty function; the remaining addresses retain their original identities.
 * RE_UNKNOWN: callback-facing roles, intended historical declarations and
 * loader-provided table lifetime. Trace loader/export consumers before
 * replacing this 20-byte address storage view with a callable interface. */
void __entrypoint_func_filmrollInitializeModuleExports(FilmrollExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32)func_filmroll_00400060;
    exports->callback04Address = (u32)func_filmroll_00400068;
    exports->callback08Address = (u32)func_filmroll_00400170;
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400170.s")

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

/* RE_UNKNOWN: the two randomized integer fields are not established here
 * as position or size. Resolve their roles through the original entry draw/
 * update consumers before adding physical names or units. */
#line 28 "src/modules/filmroll.c"
/* Count and activate the entry, fill two integer fields from separate
 * random samples, and clear its trailing word. Preserve both random calls
 * and the original float-to-integer truncation. */
void filmrollInitializeRandomizedEntry(Node_00400588 *entry) {
    float secondSample;

    D_filmroll_00400A78 += 1;
    entry->unk0 = 1;
    entry->unk4 = (int) (gUvMathExports->unk34() * D_filmroll_004009A4);
    secondSample = gUvMathExports->unk34() * 239.0f;
    entry->unkC = 0;
    entry->unk8 = (int) secondSample;
}
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

