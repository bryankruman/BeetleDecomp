// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "os.h"
#include "uv_filesystem.h"

// starts at 0x80036010
typedef struct FormFileEntry_s {
    s32 romPtr; // ROM offset
    s32 ovlPtr; // Dynamic ptr of each module file
    s32 instanceCount;
    s32 pad;
} FormFileEntry;

// starts at 0x80035F38
typedef struct FormTagEntry_s {
    s32 tag;
    u16 moduleCount;
    FormFileEntry *fileEntry;
} FormTagEntry;

typedef struct UnkStruct_8002D9BC_s {
    u16 unk0;
    u16 *unk4;
    u16 *unk8;
} UnkStruct_8002D9BC;

typedef struct UnkStruct_80001BC0_s {
    void (*unk0)(void);
} UnkStruct_80001BC0;

typedef struct UnkStruct_80003520_s {
    s32 unk0;
    void *(*unk4)(s32);
    void *(*unk8)(UnkStruct_80001BC0 *);
} UnkStruct_80003520;

extern s32 D_8002D9A8;
extern s32 D_8002D9AC;
extern u8 *D_8002D9B0;
extern s32 D_8002D9B8;
extern u8 D_FORM1_1[];

void uvMemFree(UnkStruct_80001BC0 *fileId); /* extern */
extern FormTagEntry *gFormFiles;
extern UnkStruct_8002D9BC *D_8002D9BC;
extern FormFileEntry *fileDirectory;
extern u16 sFormFilesCount;

s32 uvCheckValidTag(s32 tag);                /* extern */
s32 uvLoadModuleCode(s32);                   /* extern */
void uvUnloadModule(s32);                    /* extern */
void *func_80001724(s32, s32); /* extern */
s32 uvCheckValidFileId(s32 tag, s32 fileId);
void func_80001BC0(s32 tag, UnkStruct_80001BC0 *fileId);
void func_80001A68(s32 tag, s32 fileId);
#define __FORM0_START main_ROM_END

void uvLoadFormFiles(void) {
    s32 fileId;
    FormFileEntry *formTagsPtr;
    FormTagEntry *var_v0;
    s32 temp_v1;
    u32 size;
    void *data;
    u16 formFilesEntryCount;
    s32 j;
    s32 i;
    u16 var_v1;
    s32 *currentFormTableEntry;

    D_8002D9BC = NULL;
    D_8002D9A8 = UVTS_25_ROM_END - FORM0_ROM_END;
    D_8002D9AC = MODULE_FILES_START - __FORM0_START;
    D_8002D9B0 = UVTS_25_ROM_END;
    fileId = uvFileReadHeader(__FORM0_START);
    sFormFilesCount = 0;
    formFilesEntryCount = 0;

    while (uvFileReadBlock(fileId, &size, &data, FILE_COMPRESSED) != 0) {
        sFormFilesCount++;
        formFilesEntryCount += size / sizeof(int);
    }

    gFormFiles =
        _uvMemAllocAlign8((sFormFilesCount * sizeof(FormTagEntry)) + (formFilesEntryCount * sizeof(FormFileEntry)));
    uvFileSetPadTagStart(fileId);
    formTagsPtr = (FormFileEntry *) &(0, gFormFiles)[sFormFilesCount]; // Fake match
    for (i = 0; i < sFormFilesCount; i++) {
        gFormFiles[i].tag = uvFileReadBlock(fileId, &size, &data, FILE_NOT_COMPRESSED);
        gFormFiles[i].moduleCount = size / sizeof(int);
        gFormFiles[i].fileEntry = formTagsPtr;
        currentFormTableEntry = data;
        for (j = 0; j < gFormFiles[i].moduleCount; currentFormTableEntry++, j++) {
            if (D_8002D9B8) { // Fake match
            }

            // Check for null entries in form0 table
            if (*currentFormTableEntry == -1) {
                formTagsPtr[j].romPtr = 0;
            } else {
                formTagsPtr[j].romPtr = (s32) FORM0_ROM_END + *currentFormTableEntry;
            }
            formTagsPtr[j].ovlPtr = 0;
            formTagsPtr[j].pad = 0;
            formTagsPtr[j].instanceCount = NULL;
        }
        formTagsPtr += gFormFiles[i].moduleCount; // Advance to the next form file
        _uvMemFree(data);
    }

    uvFileFree(fileId);
    if (D_8002D9B8) {
        for (i = 0; i < sFormFilesCount; i++) {
        }
    }
}

u16 func_800015D4(s32 tag, s32 fileId) {
    s32 temp_v0;

    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 == -1) {
        return 0U;
    }
    if (uvCheckValidFileId(temp_v0, fileId) == -1) {
        return 0U;
    }
    return gFormFiles[temp_v0].fileEntry[fileId].instanceCount;
}

s32 uvGetFilesCount(s32 tag) {
    s32 temp_v0;

    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 == -1) {
        return 0U;
    }
    return gFormFiles[temp_v0].moduleCount;
}

s32 uvGetFileData(s32 tag, s32 fileId) {
    s32 temp_v0;

    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 == -1) {
        return 0;
    }
    if (uvCheckValidFileId(temp_v0, fileId) == -1) {
        return 0;
    }
    return gFormFiles[temp_v0].fileEntry[fileId].romPtr;
}

void *func_80001724(s32 tag, s32 fileId) {
    s32 idx;

    idx = uvCheckValidTag(tag);
    if (idx == -1) {
        return NULL;
    }
    if (uvCheckValidFileId(idx, fileId) == -1) {
        return NULL;
    }
    return (void *) gFormFiles[idx].fileEntry[fileId].ovlPtr;
}

s32 func_800017A4(s32 tag, s32 fileId) {
    s32 temp_v0;

    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 == -1) {
        return 0;
    }
    if (uvCheckValidFileId(temp_v0, fileId) == -1) {
        return 0;
    }
    return gFormFiles[temp_v0].fileEntry[fileId].pad;
}

s32 uvLoader(s32 tag, s32 fileId) {
    FormFileEntry *temp_s0;
    s32 temp_v0;
    s32 i;

    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 == -1) {
        return 0;
    }
    temp_s0 = &gFormFiles[temp_v0].fileEntry[fileId];
    if (temp_s0->romPtr == 0) {
        temp_s0->ovlPtr = 0;
        return 0;
    }
    if ((tag == 'UVTX') && (D_8002D9BC != NULL)) {
        for (i = 0; i < D_8002D9BC->unk0; i++) {
            if (fileId == D_8002D9BC->unk4[i]) {
                temp_v0 = func_800019B8('UVTX', D_8002D9BC->unk8[i]);
                temp_s0->ovlPtr = temp_v0;
                return temp_v0;
            }
        }
    }
    if (tag == 'UVMO') {
        fileDirectory = temp_s0;
        temp_s0->ovlPtr = uvLoadModuleCode(temp_s0->romPtr);
        fileDirectory = NULL;

    } else if (gFormFiles[temp_v0].tag != 0xFFFF) {
        UnkStruct_80003520 *call = (UnkStruct_80003520 *) uvLoadModule(gFormFiles[temp_v0].tag);
        temp_s0->ovlPtr = call->unk4(temp_s0->romPtr);
        uvUnloadModule(gFormFiles[temp_v0].tag);
    } else {
        temp_s0->ovlPtr = temp_s0->romPtr;
    }
    return temp_s0->ovlPtr;
}

void uvSetFileDirOvlPtr(s32 ovlPtr) {
    fileDirectory->ovlPtr = ovlPtr;
}

s32 func_800019B8(s32 tag, s32 fileId) {
    FormFileEntry *temp_v1;
    s32 ret;

    ret = uvCheckValidTag(tag);
    if (ret == -1) {
        return 0;
    }
    if (uvCheckValidFileId(ret, fileId) == -1) {
        return 0;
    }
    temp_v1 = &gFormFiles[ret].fileEntry[fileId];
    temp_v1->instanceCount++;
    if (temp_v1->instanceCount == 1) {
        temp_v1->ovlPtr = uvLoader(tag, (s32) fileId);
    }
    return temp_v1->ovlPtr;
}

void func_80001A68(s32 tag, s32 fileId) {
    FormFileEntry *ptr;
    s32 temp_v0;

    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 == -1) {
        return;
    }

    if (uvCheckValidFileId(temp_v0, fileId) == -1) {
        return;
    }

    ptr = &gFormFiles[temp_v0].fileEntry[fileId];
    if (ptr->instanceCount == 0) {
        return;
    }

    if (--gFormFiles[temp_v0].fileEntry[fileId].instanceCount) {
        return;
    }

    if ((tag == 'UVTX')) {
        if (D_8002D9BC != NULL) {
            s32 i;
            for (i = 0; i < D_8002D9BC->unk0; i++) {
                if (fileId == D_8002D9BC->unk4[i]) {
                    func_80001A68('UVTX', D_8002D9BC->unk8[i]);
                    ptr->ovlPtr = 0;
                    ptr->pad = 0;
                    return;
                }
            }
        }
    }

    fileId = ptr->ovlPtr;
    if (fileId != 0) {
        func_80001BC0(tag, fileId);
    }
    ptr->ovlPtr = 0;
    ptr->pad = 0;
}

void func_80001BC0(s32 tag, UnkStruct_80001BC0 *fileId) {
    s32 temp_v0;
    UnkStruct_80003520 *call;
    temp_v0 = uvCheckValidTag(tag);
    if (temp_v0 != -1) {
        if (tag == 'UVMO') {
            fileId->unk0();
            uvMemFree(fileId);
            return;
        }
        call = uvLoadModule(gFormFiles[temp_v0].tag);
        call->unk8(fileId);
        uvUnloadModule(gFormFiles[temp_v0].tag);
    }
}

void func_80001C6C(void) {
    s32 i;
    s32 j;

    for (i = 0; i < sFormFilesCount; i++) {
        for (j = 0; j < gFormFiles[i].moduleCount; j++) {
            gFormFiles[i].fileEntry[j].instanceCount = 0;
        }
    }
}

u32 uvFileReadBlock(s32 fileId, u32 *sizeOut, void **data, s32 decodeFlag) {
    u32 tag;
    u8 *allocPtr;
    u32 size;
    u8 *dst;

    tag = uvFileGetEntryTag(fileId, sizeOut, data);
    if (tag != 0) {
        allocPtr = _uvMemAllocAlign8(*sizeOut);
        _uvMediaCopy(allocPtr, *data, *sizeOut);
        *data = allocPtr;
    }
    if (tag == 'GZIP') {
        tag = (u32) uvMemRead(allocPtr, 4);
        size = (u32) uvMemRead(allocPtr + 4, 4);
        if (!(decodeFlag & 2)) {
            dst = _uvMemAllocAlign8(size);
            mio0Decode(allocPtr + 8, dst);
            _uvMemFree(allocPtr);
            *data = dst;
        }
        *sizeOut = size;
    }
    return tag;
}

void uvConsumeBytes(void *dst, u8 **ptr, u32 size) {
    u64 mem;

    if (size < sizeof(s64) + 1) {
        mem = uvMemRead(*ptr, size);
        *ptr += size;
        switch (size) {
            case sizeof(s8):
                *(s8 *) dst = mem;
                return;
            case sizeof(s16):
                *(s16 *) dst = mem;
                return;
            case sizeof(s32):
                *(s32 *) dst = mem;
                return;
            case sizeof(s64):
                *(s64 *) dst = mem;
                return;
        }
    } else {
        _uvMediaCopy(dst, *ptr, size);
        *ptr += size;
    }
}

s32 uvCheckValidTag(s32 tag) {
    FormTagEntry *ptr;
    static s32 i = 0;

    if (tag == gFormFiles[i].tag) {
        return i;
    }

    for (i = 0; i < sFormFilesCount; i++) {
        if (tag == gFormFiles[i].tag) {
            return i;
        }
    }

    return -1;
}

s32 func_80001F38(s32 arg0) {
    static s32 i = 0;
    FormTagEntry *var_a1;
    s32 var_v1;

    if (arg0 == gFormFiles[i].tag) {
        return i;
    }

    for (i = 0; i < sFormFilesCount; i++) {
        if (arg0 == gFormFiles[i].tag) {
            return i;
        }
    }
    return -1;
}

s32 uvCheckValidFileId(s32 tag, s32 fileId) {
    if ((fileId < 0) || (fileId >= gFormFiles[tag].moduleCount)) {
        return -1;
    }
    return 0;
}

u8 *uvGetModuleRomPtr(s32 arg0) {
    int temp;
    s32 i;
    s32 j;

    for (i = arg0; i < sFormFilesCount; i++) {
        for (j = 0; j < gFormFiles[i].moduleCount; j++) {
            int temp = gFormFiles[i].fileEntry[j].romPtr;
            if (temp) {
                return temp;
            }
        }
    }

    return UVTS_25_ROM_END;
}

void func_80002088(s32 *arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < sFormFilesCount; i++) {
        if (i >= arg3) {
            *arg2 = arg3;
            return;
        }

        arg0[i] = gFormFiles[i].tag;
        arg1[i] = uvGetModuleRomPtr(i + 1) - uvGetModuleRomPtr(i);
    }

    *arg2 = i;
}

void func_8000218C(s32 *arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 j;
    s32 i;

    for (i = 0; i < sFormFilesCount; i++) {
        if (i >= arg3) {
            *arg2 = arg3;
            return;
        }

        arg0[i] = gFormFiles[i].tag;
        for (j = 0, arg1[i] = 0; j < gFormFiles[i].moduleCount; j++) {
            arg1[i] += gFormFiles[i].fileEntry[j].pad;
        }
    }

    *arg2 = i;
}

void func_8000226C(s32 *tagPtr, s32 *arg1, s32 *arg2, u32 arg3) {
    u32 var_v0;
    s32 j;
    s32 i;
    s32 temp_a3;
    s32 var_t4;
    s32 var_t2;
    s32 var_t3;

    var_v0 = 0x80000000;
    for (i = 0; i < sFormFilesCount; i++) {
        for (j = 0; j < gFormFiles[i].moduleCount; j++) {
            temp_a3 = gFormFiles[i].fileEntry[j].ovlPtr;
            if ((temp_a3 < arg3) && (var_v0 < temp_a3)) {
                var_t2 = i;
                var_t3 = j;
                var_v0 = temp_a3;
                var_t4 = arg3 - temp_a3;
            }
        }
    }

    if (var_v0 != 0x80000000) {
        *tagPtr = gFormFiles[var_t2].tag;
        *arg1 = var_t3;
        *arg2 = var_t4;
        return;
    }

    *tagPtr = 'CODE';
    *arg1 = 0;
    *arg2 = arg3 - var_v0;
}

void func_80002390(s32 arg0) {
    if (arg0 == 0xFFFF) {
        D_8002D9BC = 0;
    } else {
        D_8002D9BC = func_80001724('UVTP', arg0);
    }
    if (D_8002D9BC)
        ; // FAKE
}
