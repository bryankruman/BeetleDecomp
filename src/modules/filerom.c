// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_filerom_00400624;
void func_filerom_00400060(void);
s32 func_filerom_00400068(u8, u8, u8);
s32 func_filerom_0040007C(s32, u8 *, s32);
s32 func_filerom_00400364(u8 *, s32, s32);
s32 func_filerom_00400494(s32);
typedef struct {
    void (*shutdown)(void);
    s32 (*write)(u8, u8, u8);
    s32 (*read)(s32, u8 *, s32);
    s32 (*open)(u8 *, s32, s32);
    s32 (*close)(s32);
} FileromExports;
#include "uvstring_rom.h"
extern UvString_Exports *gUvStringExports;
extern char *D_filerom_004004F0[3];
u8 *fileromFindAfterLastDelimiter(u8 *, u8);
s32 fileromGetFilenameExtensionIndex(u8 *);
s32 fileromGetFilenameFourCC(u8 *);
#line 22 "src/modules/filerom.c"
/* Register the ROM-file module's five original callbacks after updating
 * the loader's allocation pointer. Keep the shutdown and write callbacks'
 * original inactive implementations; no new file behavior is introduced. */
void __entrypoint_func_filerom_400000(FileromExports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->shutdown = func_filerom_00400060;
    exports->write = func_filerom_00400068;
    exports->read = func_filerom_0040007C;
    exports->open = func_filerom_00400364;
    exports->close = func_filerom_00400494;
}
#line 23 "src/modules/filerom.c"

void func_filerom_00400060(void) {
}

s32 func_filerom_00400068(u8 a0, u8 a1, u8 a2) {
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/func_filerom_0040007C.s")

#line 21 "src/modules/filerom.c"
/* Return the byte after the last matching non-NUL delimiter, or the
 * original text when no delimiter occurs. The terminator is never matched.
 * A zero XOR expresses byte equality while retaining IDO's original branch
 * operand order; the indexed loop reproduces the original register allocation. */
u8 *fileromFindAfterLastDelimiter(u8 *text, u8 delimiter) {
    u8 *afterLast;
    s32 index;
    s32 character;
    afterLast = text;
    for (index = 0; (character = text[index]) != 0; index++) {
        if ((delimiter ^ character) == 0) {
            afterLast = &text[index + 1];
        }
    }
    return afterLast;
}
#line 22 "src/modules/filerom.c"

#line 23 "src/modules/filerom.c"
/* Compare the text after the last period against the three original
 * extensions (TED, AIPATH and REPLAY), returning its table index or -1.
 * Matching is case sensitive; no period means the complete path is compared. */
s32 fileromGetFilenameExtensionIndex(u8 *path) {
    s32 index;
    u8 *extension;
    extension = fileromFindAfterLastDelimiter(path, '.');
    for (index = 0; index < 3; index++) {
        if (gUvStringExports->uvStrcmp(D_filerom_004004F0[index], (char *)extension) == 0) {
            return index;
        }
    }
    return -1;
}
#line 24 "src/modules/filerom.c"

#line 25 "src/modules/filerom.c"
/* Select the basename after the last slash and pack its first four bytes
 * as a big-endian four-character asset name, provided the fifth byte is a
 * period. Preserve the original valid-path/minimum-storage preconditions and
 * return -1 when that period test fails; this does not scan for a shorter name. */
s32 fileromGetFilenameFourCC(u8 *path) {
    u8 *name;
    name = fileromFindAfterLastDelimiter(path, '/');
    if (name[4] != '.') {
        return -1;
    }
    return (name[0] << 24) | (name[1] << 16) | (name[2] << 8) | name[3];
}
#line 26 "src/modules/filerom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/func_filerom_00400364.s")

s32 func_filerom_00400494(s32 arg0) {
    if (D_filerom_00400624 == 0) {
        return -1;
    }
    D_filerom_00400624 = 0;
    return 0;
}

