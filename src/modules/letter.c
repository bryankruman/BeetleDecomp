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
    /* 0x3C */ void (*unk3C)(f32, f32, f32, f32);
} UvGfxMgrExp_00400420;
extern UvGfxMgrExp_00400420 *gUvGfxMgrExports;
typedef struct {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
} TableEntry_00400420; /* stride 0x14 */

typedef struct {
    /* 0x00 */ char unk0[0x8];
    /* 0x08 */ u8 unk8;
    /* 0x09 */ char unk9[0x17];
    /* 0x20 */ f32 unk20;
} LetterObj_00400420;
extern char D_letter_00400480[];
void func_letter_00400230(s32 descriptorIndex, Vec3F *position);
void *letterGetDescriptorOrDefault(s32 index);
#line 45 "src/modules/letter.c"
/* Install the three letter exports, load four models and four textures in
 * their original order, then allocate twenty 36-byte entries. Initialize only
 * each entry active byte and object handle; leave all other bytes untouched.
 * RE_UNKNOWN: asset roles, remaining entry fields, shared word 0x00400518 and
 * external ownership/lifetime of loaded assets and created objects.
 * RE_ORIGINAL_QUIRK: allocation is unchecked. */
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
/* Release nonnegative object handles from all twenty 36-byte entries,
 * free the shared entry array, then unload the four models and four textures
 * in their original order. Preserve shared-pointer reloads around releases. */
/* Keep the setup and loop opening grouped: the original IDO compiler
 * schedules the shared-pointer loads differently when these lines split. */
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
/* Return descriptor zero for an index outside zero through five;
 * otherwise return the original twenty-byte descriptor at that index. */
void *letterGetDescriptorOrDefault(s32 index) {
    if (index < 0 || index >= 6) {
        return D_letter_00400480;
    }
    return D_letter_00400480 + index * 0x14;
}
#line 63 "src/modules/letter.c"

/* Forward the indexed descriptor scalars and object alpha through graphics slot 0x3C. */
#line 65 "src/modules/letter.c"
/* Select the twenty-byte descriptor using the object byte index and
 * set its RGB components with the object alpha through graphics export 0x3C.
 * RE_UNKNOWN: index bound; trace original index producers and descriptor extent. */
void letterSetDescriptorPrimitiveColor(LetterObj_00400420 *object) {
    TableEntry_00400420 *descriptor;

    descriptor = (TableEntry_00400420 *)(D_letter_00400480 + object->unk8 * 0x14);
    gUvGfxMgrExports->unk3C(descriptor->unk8, descriptor->unkC, descriptor->unk10, object->unk20);
}
#line 71 "src/modules/letter.c"

