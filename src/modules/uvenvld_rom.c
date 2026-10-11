// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

typedef struct UnkUvEnvLd_Exports_s {
    char pad0[4];
    void (*unk4)(f32, f32, s32, s32);
} UnkUvEnvLd_Exports;

void __entrypoint_func_uvenvld_rom_400000(UvEnvLd_Exports *exports);
void uvEnvironmentLoaderReservedCallback(void);
ParsedUVEN *uvParseUVEN(u8 *data);
ParsedUVEN *_uvParseUVEN(void *arg0);
void uvEnvLdCleanup(ParsedUVEN *parsedUvEnv);

// .data
s32 D_uvenvld_rom_00400320[] = {0x000C0000, __entrypoint_func_uvenvld_rom_400000, 0, 0};

/* Publish environment parse, reserved-callback and cleanup exports after the
 * allocation hook. No environment is parsed and no shared environment data is
 * reset here. RE_UNKNOWN: export storage and parsed-resource lifetime remain
 * contracts of the loader and later parse/cleanup callers. */
#line 20 "src/modules/uvenvld_rom.c"
void __entrypoint_func_uvenvld_rom_400000(UvEnvLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVEN = uvParseUVEN;
    exports->uvEnvironmentLoaderReservedCallback = uvEnvironmentLoaderReservedCallback;
    exports->uvEnvLdCleanup = uvEnvLdCleanup;
}
#line 26 "src/modules/uvenvld_rom.c"

// stub
#line 28 "src/modules/uvenvld_rom.c"
/* Original empty environment-loader callback; retain its entry point. */
void uvEnvironmentLoaderReservedCallback(void) {
}
#line 30 "src/modules/uvenvld_rom.c"

/*
 * Open the environment file and visit blocks with decode flag 1. For each
 * COMM block, parse its bytes and free that block before continuing; release
 * the file handle at the end and return the last parsed environment or NULL.
 * RE_ORIGINAL_QUIRK: Repeated COMM blocks replace the result without releasing
 * the previous environment. Other block tags have no local free here.
 * RE_UNKNOWN: Accepted block sequence, decoded extents and ownership of ignored
 * blocks require the file provider and asset callers; no validation is added.
 */
#line 31 "src/modules/uvenvld_rom.c"
ParsedUVEN *uvParseUVEN(u8 *fileData) {
    s32 fileId;
    ParsedUVEN *environment;
    u32 blockSize;
    void *blockData;
    u32 tag;
    void *commBlock;

    environment = NULL;
    fileId = uvFileReadHeader(fileData);
    tag = uvFileReadBlock(fileId, &blockSize, &blockData, FILE_NOT_COMPRESSED);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                commBlock = blockData;
                environment = _uvParseUVEN(commBlock);
                _uvMemFree(commBlock);
                break;
            default:
                break;
        }
        tag = uvFileReadBlock(fileId, &blockSize, &blockData, FILE_NOT_COMPRESSED);
    }
    uvFileFree(fileId);
    return environment;
}

// uvParseUVEN internal
/*
 * Copy the 0x60-byte environment record, clear its two callback fields and
 * allocate a model table for the byte-sized model count. For each entry, read
 * the model ID, load UVMD, then read its flag. When field 0x1D is nonzero,
 * load UENV, allocate the 0x200-byte lookup, call export 0x04 and unload UENV.
 * RE_ORIGINAL_QUIRK: The inherited provider declaration passes the lookup and
 * environment pointers through s32 parameters; preserve that ABI expression.
 * RE_UNKNOWN: Input extent, allocation/import failure and model/lookup lifetime
 * are unchecked. The copied record fields retain their original layout.
 */
#line 59 "src/modules/uvenvld_rom.c"
ParsedUVEN *_uvParseUVEN(void *inputCursor) {
    s32 modelIndex;
    UnkUvEnvLd_Exports *environmentProvider;
    ParsedUVEN *environmentRecord;

    environmentRecord = malloc8(sizeof(ParsedUVEN));
    uvConsumeBytes(environmentRecord, (u8 **) &inputCursor, sizeof(ParsedUVEN));
    environmentRecord->unk38 = 0;
    environmentRecord->unk5C = 0;
    if (environmentRecord->modelCount > 0) {
        environmentRecord->modelTable = malloc8(environmentRecord->modelCount * sizeof(uvEnvModel));
    } else {
        environmentRecord->modelTable = NULL;
    }
    for (modelIndex = 0; modelIndex < environmentRecord->modelCount; modelIndex++) {
        uvConsumeBytes(&environmentRecord->modelTable[modelIndex].modelId, (u8 **) &inputCursor, sizeof(u16));
        uvLoadFile('UVMD', environmentRecord->modelTable[modelIndex].modelId);
        uvConsumeBytes(&environmentRecord->modelTable[modelIndex].flag, (u8 **) &inputCursor, sizeof(u8));
    }
    if (environmentRecord->unk1D == 0) {
        environmentRecord->unk44 = NULL;
    } else {
        environmentProvider = uvLoadModule('UENV');
        environmentRecord->unk44 = _uvMemAlloc(0x200, 8);
        /* UENV export 0x04 builds this environment's 256-entry fog lookup. */
        environmentProvider->unk4(environmentRecord->unk3C, environmentRecord->unk40, environmentRecord->unk44, environmentRecord);
        uvUnloadModule('UENV');
    }
    return environmentRecord;
}

/*
 * Free the optional field-0x44 lookup, unload each referenced UVMD in table
 * order when the byte-sized model count is nonzero, then free the table and
 * environment record. A zero count skips the table free entirely.
 * RE_UNKNOWN: The record must still own the lookup/table and loaded model
 * references. Partial initialization, aliases and repeated cleanup are not
 * checked here; preserve the unused local and original release order.
 */
#line 90 "src/modules/uvenvld_rom.c"
void uvEnvLdCleanup(ParsedUVEN *environmentRecord) {
    void *lookupStorage;
    s32 modelIndex;
    s32 unusedWord;
    ParsedUVEN *environment = environmentRecord;

    lookupStorage = environment->unk44;
    if (lookupStorage != NULL) {
        _uvMemFree(lookupStorage);
    }
    if (environment->modelCount != 0) {
        for (modelIndex = 0; modelIndex < environment->modelCount; modelIndex++) {
            uvUnloadFile('UVMD', environment->modelTable[modelIndex].modelId);
        }
        _uvMemFree(environment->modelTable);
    }
    _uvMemFree(environment);
}
