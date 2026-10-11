    // SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void __entrypoint_func_uvufileld_rom_400000(UvuFileLd_Rom_Exports *exports);
void uvuFileldStub(void);
u8 *uvFileCopy(u8 *arg0);
void uvFreeFilePtr(void *arg0);
void uvSetCopyFileDataFlag(s32 arg0);

extern s32 sCopyFileDataFlag;

/* Publish file-copy, stub, release and copy-flag setter exports, then reset the
 * shared copy-data flag to FALSE. No existing file pointer is released here.
 * RE_UNKNOWN: loader export storage, flag meaning and copied/borrowed resource
 * ownership require the later copy/release paths; preserve the post-publication reset. */
#line 13 "src/modules/uvufileld_rom.c"
void __entrypoint_func_uvufileld_rom_400000(UvuFileLd_Rom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvFileCopy = uvFileCopy;
    exports->uvuFileldStub = uvuFileldStub;
    exports->uvFreeFilePtr = uvFreeFilePtr;
    exports->uvSetCopyFileDataFlag = uvSetCopyFileDataFlag;
    sCopyFileDataFlag = FALSE;
}
#line 21 "src/modules/uvufileld_rom.c"

void uvuFileldStub(void) {
}

/*
 * Open the file and obtain its size. For UVRW header type, search COMM entry
 * zero to replace the data pointer/size, preserving the ignored search result.
 * With the shared flag zero, allocate with argument 8 and copy the bytes;
 * otherwise return the existing data pointer. Release the file handle first.
 * RE_ORIGINAL_QUIRK: A nonzero flag selects the borrowed-pointer path despite
 * the flag name. The separate free operation always calls the allocator.
 * RE_UNKNOWN: Failed search outputs, input extent, allocation success and
 * borrowed-pointer lifetime/free protocol require provider and caller proof.
 */
#line 25 "src/modules/uvufileld_rom.c"
u8 *uvFileCopy(u8 *inputData) {
    u8 *resultData;
    s32 fileId;
    s32 fileSize;
    fileId = uvFileReadHeader(inputData);
    fileSize = uvFileGetSize(fileId);

    if (uvFileGetPadType(fileId) == 'UVRW') { /* Header type, not FORM0 category. RE_UNKNOWN: runtime IDs reaching this COMM branch; docs/evidence/us-block-header-boundary.json. */
        uvFileSearchTag(fileId, (u32 *) &fileSize, (void **) &inputData, 'COMM', 0);
    }

    if (!sCopyFileDataFlag) {
        resultData = _uvMemAlloc(fileSize, 8);
        _uvMediaCopy(resultData, inputData, fileSize);
    } else {
        resultData = inputData;
    }
    uvFileFree(fileId);
    return resultData;
}

/*
 * Pass the supplied pointer directly to the existing allocator free routine.
 * RE_ORIGINAL_QUIRK: There is no ownership or shared-flag check even though
 * uvFileCopy can return an existing input/entry pointer instead of a new copy.
 * RE_UNKNOWN: Callers must establish which pointers may be released; NULL
 * handling and the borrowed-pointer protocol are not proved by this wrapper.
 */
#line 46 "src/modules/uvufileld_rom.c"
void uvFreeFilePtr(void *allocation) {
    _uvMemFree(allocation);
}

/*
 * Store the caller word unchanged in the shared file-data mode flag.
 * RE_ORIGINAL_QUIRK: Zero selects allocation/copy in uvFileCopy; any nonzero
 * value selects its existing-pointer path. The flag is not normalized here.
 * RE_UNKNOWN: Coordination with outstanding borrowed/copied results and
 * concurrent loaders requires the flag-setting and destruction callers.
 */
#line 50 "src/modules/uvufileld_rom.c"
void uvSetCopyFileDataFlag(s32 modeFlag) {
    sCopyFileDataFlag = modeFlag;
}
