// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_filerom_00400624;
#include "uvstring_rom.h"
extern UvString_Exports *gUvStringExports;
extern char *D_filerom_004004F0[3];
u8 *fileromFindAfterLastDelimiter(u8 *, u8);
s32 fileromGetFilenameExtensionIndex(u8 *);
s32 fileromGetFilenameFourCC(u8 *);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/__entrypoint_func_filerom_400000.s")

void func_filerom_00400060(void) {
}

s32 func_filerom_00400068(u8 a0, u8 a1, u8 a2) {
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/func_filerom_0040007C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/fileromFindAfterLastDelimiter.s")

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

