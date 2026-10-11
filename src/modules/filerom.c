// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_filerom_00400624;
void fileRomNoOpModuleCleanup(void);
s32 fileRomReturnZeroForWrite(u8, u8, u8);
s32 func_filerom_0040007C(s32, u8 *, s32);
s32 func_filerom_00400364(u8 *, s32, s32);
s32 fileRomClearSharedSourceAddress(s32);
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
/* Publish the five original ROM-file exports after the allocation-pointer hook:
 * shutdown, write, read, open and close in their existing order. Publishing these
 * addresses does not open a file or reset the shared source address.
 * RE_UNKNOWN: writable export storage, loader lifetime and the opaque open/read
 * contracts remain caller obligations; the write export is a zero-return stub. */
#line 25 "src/modules/filerom.c"
void __entrypoint_func_filerom_400000(FileromExports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->shutdown = fileRomNoOpModuleCleanup;
    exports->write = fileRomReturnZeroForWrite;
    exports->read = func_filerom_0040007C;
    exports->open = func_filerom_00400364;
    exports->close = fileRomClearSharedSourceAddress;
}
#line 33 "src/modules/filerom.c"
#line 23 "src/modules/filerom.c"

#line 24 "src/modules/filerom.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void fileRomNoOpModuleCleanup(void) {
}
#line 26 "src/modules/filerom.c"

/* Original ROM write-slot implementation returns zero without processing
 * the inputs. Preserve the three existing u8 formal widths and return ABI.
 * RE_UNKNOWN: historical input declarations/roles and write behavior require
 * original write callers and module-selection paths; no host write inferred. */
#line 27 "src/modules/filerom.c"
s32 fileRomReturnZeroForWrite(u8 unusedFirstByte, u8 unusedSecondByte, u8 unusedThirdByte) {
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/func_filerom_0040007C.s")

#line 21 "src/modules/filerom.c"
/* Scan unsigned bytes through the first NUL and return the byte after the last
 * matching delimiter, or the original pointer when none matches. Delimiter zero
 * cannot match because the loop stops before testing the terminator.
 * RE_UNKNOWN: the caller must provide a readable NUL-terminated byte sequence;
 * there is no NULL, length or capacity check. */
#line 25 "src/modules/filerom.c"
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
#line 37 "src/modules/filerom.c"
#line 22 "src/modules/filerom.c"

#line 23 "src/modules/filerom.c"
/* Compare the suffix after the last dot against TED, AIPATH and REPLAY using
 * the string provider's case-sensitive uvStrcmp; return the first index 0..2
 * or -1. With no dot, compare the whole input.
 * RE_UNKNOWN: path validity and provider/table lifetime need callers. Preserve
 * the unchecked NUL-terminated scan and original table order. */
#line 26 "src/modules/filerom.c"
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
#line 37 "src/modules/filerom.c"
#line 24 "src/modules/filerom.c"

#line 25 "src/modules/filerom.c"
/* Use the bytes after the last slash. Require a dot at byte four, then combine
 * bytes zero through three in big-endian order; otherwise return -1.
 * RE_ORIGINAL_QUIRK: byte four is read without checking the component length.
 * RE_UNKNOWN: callers must supply sufficient readable storage and a terminated
 * path. Preserve the original signed shift expression and unchecked short names. */
#line 29 "src/modules/filerom.c"
s32 fileromGetFilenameFourCC(u8 *path) {
    u8 *name;
    name = fileromFindAfterLastDelimiter(path, '/');
    if (name[4] != '.') {
        return -1;
    }
    return (name[0] << 24) | (name[1] << 16) | (name[2] << 8) | name[3];
}
#line 37 "src/modules/filerom.c"
#line 26 "src/modules/filerom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filerom/func_filerom_00400364.s")

#line 29 "src/modules/filerom.c"
/* Clear the shared read-source address, returning 0; return -1 if already zero.
 * RE_UNKNOWN: extent/ownership/lifetime need original assets and load callers; keep unused word ABI. */
s32 fileRomClearSharedSourceAddress(s32 unused) {
    if (D_filerom_00400624 == 0) {
        return -1;
    }
    D_filerom_00400624 = 0;
    return 0;
}
#line 36 "src/modules/filerom.c"

