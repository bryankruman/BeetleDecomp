// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
/* All three export slots from the original module initializer. */
typedef struct {
    void (*cleanup)(void);
    void (*createObject)(s32, Vec3F *);
    void *(*getDescriptor)(s32);
} LetterInitializerExports;
/* Only this eight-byte prefix is used here; original record stride is 0x24. */
typedef struct {
    u8 active;
    u8 unknown01[3];
    s32 objectHandle;
} LetterInitializerEntryPrefix;
extern s32 D_letter_00400518;
void letterReleaseObjectsAndMedia(void);
#include "module.h"
/*__SEEDEXTERNS__*/
void _uvMemFree(void *ptr);
void uvUnloadFile(s32 formFileTag, s32 fileId);
extern UvDobj_Exports *gUvDobjExports;
extern void *D_letter_00400504;
typedef struct {
    /* 0x00 */ char pad[0x3C];
    /* 0x3C */ void (*setPrimitiveColor)(f32, f32, f32, f32);
} LetterPrimitiveColorExports;
extern LetterPrimitiveColorExports *gUvGfxMgrExports;
typedef struct {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ f32 red;
    /* 0x0C */ f32 green;
    /* 0x10 */ f32 blue;
} LetterPrimitiveColorDescriptor; /* stride 0x14 */

typedef struct {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ u8 descriptorIndex;
    /* 0x09 */ char unk9[0x17];
    /* 0x20 */ f32 alpha;
} LetterPrimitiveColorObjectView;
extern char D_letter_00400480[];
void func_letter_00400230(s32 descriptorIndex, Vec3F *position);
void *letterGetDescriptorOrDefault(s32 index);
#line 45 "src/modules/letter.c"
/* Publish three exports; load models 0x101/0x102/0x104/0x103, then textures
 * 0x3E8/0x3E9/0x3FE/0x3FC. Allocate twenty 36-byte entries (720 bytes), set
 * only each handle to -1 and active byte to zero, then clear shared word
 * 0x00400518. RE_ORIGINAL_QUIRK: allocation is unchecked; traversal adds byte
 * offsets to a 32-bit base address. Preserve the initialization order.
 * RE_UNKNOWN: asset/shared-word roles, remaining entry fields, allocation or
 * import failure, repeated initialization, and resource/pool/object ownership
 * and lifetime require creator, cleanup and provider evidence. */
#line 51 "src/modules/letter.c"
void __entrypoint_func_letterInitializeModuleAndObjectPool(LetterInitializerExports *exports) {
    s32 entryOffset;
    LetterInitializerEntryPrefix *entry;

    uvUpdateFileAllocPtr(exports);
    exports->cleanup = letterReleaseObjectsAndMedia;
    exports->createObject = func_letter_00400230;
    exports->getDescriptor = letterGetDescriptorOrDefault;
    uvLoadFile(0x55564D44, 0x101);
    uvLoadFile(0x55564D44, 0x102);
    uvLoadFile(0x55564D44, 0x104);
    uvLoadFile(0x55564D44, 0x103);
    uvLoadFile(0x55565458, 0x3E8);
    uvLoadFile(0x55565458, 0x3E9);
    uvLoadFile(0x55565458, 0x3FE);
    uvLoadFile(0x55565458, 0x3FC);
    D_letter_00400504 = _uvMemAllocAlign8(0x2D0);
    entryOffset = 0;
    do {
        /* The N64 module stores a 32-bit base address; entryOffset is in bytes. */
        entry = (LetterInitializerEntryPrefix *)(entryOffset + (u32)D_letter_00400504);
        entry->objectHandle = -1;
        entry->active = 0;
        entryOffset += 0x24;
    } while (entryOffset != 0x2D0);
    D_letter_00400518 = 0;
}
#line 46 "src/modules/letter.c"

#line 32 "src/modules/letter.c"
/* Release nonnegative handles in all twenty 36-byte entries, free the final
 * reloaded pool pointer, then unload models and textures in their original order.
 * RE_ORIGINAL_QUIRK: active bytes are ignored; handles and the shared pool
 * pointer are not cleared here. Preserve pointer reloads and the grouped setup/
 * loop opening: splitting those lines changes the original IDO scheduling.
 * RE_UNKNOWN: callback effects on the pool, partial-initialization entry and
 * repeated-cleanup safety require loader/caller and provider evidence. */
#line 37 "src/modules/letter.c"
void letterReleaseObjectsAndMedia(void) {
    void *entries;
    s32 objectHandle;
    s32 entryOffset;

    entries = D_letter_00400504; entryOffset = 0; do {
        objectHandle = *((s32 *) ((((u8 *) entries) + entryOffset) + 0x4));
        if (objectHandle >= 0) {
            gUvDobjExports->uvDobjClearModelAndStateByte(objectHandle);
            entries = D_letter_00400504;
        }
        entries = D_letter_00400504;
        entryOffset += 0x24;
    } while (entryOffset != 0x2D0);
    _uvMemFree(entries);
    uvUnloadFile(0x55564D44, 0x101);
    uvUnloadFile(0x55564D44, 0x102);
    uvUnloadFile(0x55564D44, 0x104);
    uvUnloadFile(0x55564D44, 0x103);
    uvUnloadFile(0x55565458, 0x3E8);
    uvUnloadFile(0x55565458, 0x3E9);
    uvUnloadFile(0x55565458, 0x3FE);
    uvUnloadFile(0x55565458, 0x3FC);
}
#line 54 "src/modules/letter.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/letter/func_letter_00400230.s")

#line 57 "src/modules/letter.c"
/* Return the 20-byte descriptor for index 0..5, or descriptor zero otherwise.
 * This selects a return pointer without validating or rewriting an object's
 * stored index; see letterSetDescriptorPrimitiveColor's separate contract. */
#line 59 "src/modules/letter.c"
void *letterGetDescriptorOrDefault(s32 index) {
    if (index < 0 || index >= 6) {
        return D_letter_00400480;
    }
    return D_letter_00400480 + index * 0x14;
}
#line 63 "src/modules/letter.c"

/* Select a 20-byte descriptor with the object's unsigned index byte and pass
 * its RGB plus the object's alpha through graphics export 0x3C.
 * RE_ORIGINAL_QUIRK: indexing is direct, without the getter's fallback.
 * RE_UNKNOWN: producer index bounds and full descriptor storage extent; the
 * getter's 0..5 check proves neither a six-entry allocation nor a reachable
 * invalid access here. Trace index writers and descriptor storage producers. */
#line 69 "src/modules/letter.c"
void letterSetDescriptorPrimitiveColor(LetterPrimitiveColorObjectView *object) {
    LetterPrimitiveColorDescriptor *descriptor;

    descriptor = (LetterPrimitiveColorDescriptor *)(D_letter_00400480 + object->descriptorIndex * 0x14);
    gUvGfxMgrExports->setPrimitiveColor(descriptor->red, descriptor->green, descriptor->blue, object->alpha);
}
#line 74 "src/modules/letter.c"
#line 71 "src/modules/letter.c"

