// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"
#include "global_exports.h"

#define MAX_FILE_DESCRIPTORS 21

typedef struct FileDescriptorState_s {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    char buf[0x100];
} FileDescriptorState;

void __entrypoint_func_fileux_400000(FileUx_Exports *exports);
void fileuxNoOpModuleCleanup(void);
void func_fileux_00400068(void);
s32 fileuxStrlen(u8 *text);
void fileuxStrcpy(u8 **destinationCursor, u8 *source, s32 byteCount);
void fileuxNoOpHostBufferHook(void *arg0, s32 arg1);
s32 func_fileux_00400144(void);
s32 fileuxHostRequest(s32 mode, ...);
s32 fileuxWrite(s32 fd, u8 *sourceBuffer, s32 byteCount);
s32 fileuxRead(s32 fd, u8 *destinationBuffer, s32 byteCount);
s32 fileuxOpen(char *arg0, s32 arg1, s32 arg2);
s32 fileuxClose(s32 arg0);

// .data
s32 D_fileux_00400CE0[] = { 0x140000, __entrypoint_func_fileux_400000, 0, 0 };

// .rodata
static const char sStubbedPrintf[] = { " %02x" };
static const char sStubbedPrintf1[] = { "\n" };
static const char sStubbedPrintf2[] = {
    "=================================================================\n"
};
static const char sStubbedPrintf3[] = { "all synced up\n" };
static const char sStubbedPrintf4[] = { "requesting open [%s] mask [0x%x] cmask [0x%x]\n" };
static const char sStubbedPrintf5[] = { "result fd = %d\n" };
static const char sStubbedPrintf6[] = { "requesting read fd: %d buf: 0x%x  nbytes: %d\n" };
static const char sStubbedPrintf7[] = { "number of bytes read by host: %d\n" };
static const char sStubbedPrintf8[] = { "send acknowledge to host\n" };
static const char sStubbedPrintf9[] = { "reading %d bytes at offset %d\n" };
static const char sStubbedPrintf10[] = { "requesting write of fd: %d  buf: 0x%x nbytes:%d\n" };
static const char sStubbedPrintf11[] = { "sending buffer with %d bytes\n" };
static const char sStubbedPrintf12[] = { "requesting close of fd: %d\n" };
static const char sStubbedPrintf13[] = { "requesting lseek fd: %d  offs: %d  whence: %d\n" };

// .bss
s32 B_fileux_00400CF0[2]; // unreferenced padding
u8 D_fileux_00400CF8[0x200];
FileDescriptorState *sFileDescriptorsState[MAX_FILE_DESCRIPTORS];

void __entrypoint_func_fileux_400000(FileUx_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->fileuxNoOpModuleCleanup = fileuxNoOpModuleCleanup;
    exports->fileuxWrite = fileuxWrite;
    exports->fileuxRead = fileuxRead;
    exports->fileuxOpen = fileuxOpen;
    exports->fileuxClose = fileuxClose;
}

#line 64 "src/modules/fileux.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void fileuxNoOpModuleCleanup(void) {
}
#line 66 "src/modules/fileux.c"

#line 67 "src/modules/fileux.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_fileux_00400068(void) {
}
#line 69 "src/modules/fileux.c"

#line 70 "src/modules/fileux.c"

s32 fileuxStrlen(u8 *text) {
    s32 length;
    u8 *cursor;

    length = 0;
    cursor = text;
    while (*cursor != '\0') {
        length++;
        cursor++;
    }

    return length;
}
#line 83 "src/modules/fileux.c"

#line 84 "src/modules/fileux.c"

void fileuxStrcpy(u8 **destinationCursor, u8 *source, s32 byteCount) {
    s32 byteIndex;
    u8 *sourceBytes = source;

    for (byteIndex = 0; byteIndex < byteCount; byteIndex++) {
        *(*destinationCursor + byteIndex) = sourceBytes[byteIndex];
    }

    *destinationCursor += byteCount;
}
#line 94 "src/modules/fileux.c"

#line 95 "src/modules/fileux.c"
/* Original no-op hook used by fileuxHostRequest with request, handshake,
 * acknowledgement or write-data buffers and their byte counts. This body never
 * accesses the buffer; preserve the original pointer-plus-s32 argument ABI.
 * RE_UNKNOWN: intended protocol operation; callers alone do not establish
 * whether this hook would send, receive, synchronize or inspect the buffer. */
void fileuxNoOpHostBufferHook(void *unusedBuffer, s32 unusedByteCount) {
}
#line 97 "src/modules/fileux.c"

s32 func_fileux_00400144(void) {
    return 1;
}

s32 fileuxHostRequest(s32 mode, ...) {
    u8 sp60[0x100];
    u8 *sp5C;
    u8 *sp58;
    s32 sp54;
    s32 sp50;
    s32 i; // a3
    s32 temp_v0;
    s32 sp44;
    s32 var_s0;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    va_list args;
    s32 a0;

    gUvGfxMgrExports->uvGfxWaitIfRequested();
    sp5C = sp60;
    for (i = 0; i < 0x100; i++) {
        sp60[i] = i;
    }

    fileuxNoOpHostBufferHook(sp5C, 0x100);
    if (func_fileux_00400144() == 0) {
        return -1;
    }

    i = 0;
    do {
    } while ((D_fileux_00400CF8[i] == (0xFF - i)) && (++i < 0x100));
    if (i) {
    }

    _uvMediaCopy(sp60, &mode, sizeof(int));
    sp5C += 4;
    va_start(args, mode);
    switch (mode) {
        case 'O':
            sp58 = va_arg(args, u8 *);
            sp44 = va_arg(args, s32);
            fileuxStrcpy(&sp5C, sp58, fileuxStrlen(sp58));
            *sp5C = '\0';
            sp5C += 1;
            fileuxStrcpy(&sp5C, (u8*)&sp44, 4);
            if (sp44 & 0x100) {
                i = va_arg(args, s32);
                fileuxStrcpy(&sp5C, (u8 *) &i, 4);
            } else {
                i = 0;
            }
            fileuxNoOpHostBufferHook(sp60, 0x100);
            func_fileux_00400144();
            a0 = ((s32 *) D_fileux_00400CF8)[0];
            return a0;
        case 'R':
            sp50 = va_arg(args, s32);
            sp54 = va_arg(args, s32);
            sp3C = va_arg(args, s32);
            sp30 = va_arg(args, s32);
            fileuxStrcpy(&sp5C, (u8*)&sp50, 4);
            fileuxStrcpy(&sp5C, (u8*)&sp3C, 4);
            fileuxNoOpHostBufferHook(sp60, 0x100);
            func_fileux_00400144();

            if (sp30 != 0) {
                // FAKE
                if (&sp30) {
                }
                if (&sp30) {
                }
            }
            sp60[0] = 6;
            fileuxNoOpHostBufferHook(sp60, 0x100);
            for (i = 0; i < sp3C;) {
                temp_v0 = sp3C - i;
                if (temp_v0 < 0x100) {
                    var_s0 = temp_v0;
                } else {
                    var_s0 = 0x100;
                }
                func_fileux_00400144();
                _uvMediaCopy(sp54 + i, D_fileux_00400CF8, var_s0);
                i += var_s0;
            }

            // FAKE
            if ((a0 && a0) && a0) {
            }
            return sp3C;
        case 'W':
            sp50 = va_arg(args, s32);
            sp54 = va_arg(args, s32);
            sp3C = va_arg(args, s32);
            fileuxStrcpy(&sp5C, (u8 *) &sp50, 4);
            fileuxStrcpy(&sp5C, (u8 *) &sp3C, 4);
            fileuxNoOpHostBufferHook(sp60, 0x100);
            func_fileux_00400144();
            i = sp3C;
            if (sp3C & 7) {
                i = (sp3C - (sp3C % 8)) + 8;
            }
            fileuxNoOpHostBufferHook(sp54, i);
            func_fileux_00400144();
            a0 = ((s32 *) D_fileux_00400CF8)[0];
            return a0;
        case 'C':
            sp50 = va_arg(args, s32);
            fileuxStrcpy(&sp5C, (u8 *) &sp50, 4);
            fileuxNoOpHostBufferHook(sp60, 0x100);
            func_fileux_00400144();
            a0 = ((s32 *) D_fileux_00400CF8)[0];
            return a0;
        case 'L':
            sp50 = va_arg(args, s32);
            sp38 = va_arg(args, s32);
            sp34 = va_arg(args, s32);
            fileuxStrcpy(&sp5C, (u8*)&sp50, 4);
            fileuxStrcpy(&sp5C, (u8*)&sp38, 4);
            fileuxStrcpy(&sp5C, (u8*)&sp34, 4);
            fileuxNoOpHostBufferHook(sp60, 0x100);
            func_fileux_00400144();
            a0 = ((s32 *) D_fileux_00400CF8)[0];
            return a0;
        default:
            return -1;
    }
}

#line 231 "src/modules/fileux.c"

s32 fileuxWrite(s32 fd, u8 *sourceBuffer, s32 byteCount) {
    s32 chunkSize;
    s32 bytesProcessed;
    FileDescriptorState *fileDescriptorState;

    bytesProcessed = 0;
    if ((fd < MAX_FILE_DESCRIPTORS - 1) && (fd >= 0)) {
        fileDescriptorState = sFileDescriptorsState[fd];
    } else {
        fileDescriptorState = NULL;
    }
    if ((fileDescriptorState != NULL)
        && (((fileDescriptorState->unk0 == 0)) || (fileDescriptorState->unk8 == 0))) {
        fileDescriptorState->unk8 = 0;
        if (fileDescriptorState->unk0 > 0) {
            if ((0x100 - fileDescriptorState->unk0) < byteCount) {
                bytesProcessed = (0x100 - fileDescriptorState->unk0);
            } else {
                bytesProcessed = byteCount;
            }
            _uvMediaCopy((u8 *) fileDescriptorState + fileDescriptorState->unk0 + 0xC, sourceBuffer, bytesProcessed);
            fileDescriptorState->unk0 += bytesProcessed;
            if (fileDescriptorState->unk0 == 0x100) {
                fileuxHostRequest('W', fd, fileDescriptorState->buf, 0x100);
                fileDescriptorState->unk0 = 0;
            }
        }
        if (bytesProcessed == byteCount) {
            return 0;
        }
        if (fileDescriptorState->unk0 != 0) {
            return 1;
        }
        while (bytesProcessed < byteCount) {
            if ((byteCount - bytesProcessed) >= 0x101) {
                bytesProcessed += fileuxHostRequest('W', fd, sourceBuffer + bytesProcessed, 0x100);
            } else {
                _uvMediaCopy(fileDescriptorState->buf, sourceBuffer + bytesProcessed, (u32) (byteCount - bytesProcessed));
                fileDescriptorState->unk0 = (byteCount - bytesProcessed);
                bytesProcessed = byteCount;
            }
        }
        goto ret;
    }

    while (bytesProcessed < byteCount) {
        if ((byteCount - bytesProcessed) < 0x100) {
            chunkSize = (byteCount - bytesProcessed);
        } else {
            chunkSize = 0x100;
        }
        bytesProcessed += fileuxHostRequest('W', fd, sourceBuffer + bytesProcessed, chunkSize);
    }

    if (bytesProcessed != byteCount) {
        return 1;
    }
ret:
    return 0;
}
#line 291 "src/modules/fileux.c"

#line 292 "src/modules/fileux.c"

s32 fileuxRead(s32 fd, u8 *destinationBuffer, s32 byteCount) {
    FileDescriptorState *fileDescriptorState;
    s32 chunkSize;
    s32 bytesProcessed;
    s32 bufferedReadCount;

    bytesProcessed = 0;
    if ((fd < MAX_FILE_DESCRIPTORS - 1) && (fd >= 0)) {
        fileDescriptorState = sFileDescriptorsState[fd];
    } else {
        fileDescriptorState = NULL;
    }
    if ((fileDescriptorState != NULL)
        && (((fileDescriptorState->unk0 == 0)) || (fileDescriptorState->unk8 != 0))) {
        fileDescriptorState->unk8 = 1;
        if (fileDescriptorState->unk0 != 0) {
            if (byteCount < (fileDescriptorState->unk0 - fileDescriptorState->unk4)) {
                bytesProcessed = byteCount;
            } else {
                bytesProcessed = (fileDescriptorState->unk0 - fileDescriptorState->unk4);
            }
            _uvMediaCopy(destinationBuffer, (u8 *) fileDescriptorState + fileDescriptorState->unk4 + 0xC,
                         (u32) bytesProcessed);
            fileDescriptorState->unk4 += bytesProcessed;
        }
        if (bytesProcessed == byteCount) {
            return 0;
        }
        if ((fileDescriptorState->unk0 != 0)
            && (fileDescriptorState->unk0 != fileDescriptorState->unk4)) {
            return 1;
        }
        while (bytesProcessed < byteCount) {
            if ((byteCount - bytesProcessed) >= 0x101) {
                bytesProcessed += fileuxHostRequest('R', fd, destinationBuffer + bytesProcessed, 0x100, 1);
                continue;
            }
            bufferedReadCount = fileuxHostRequest('R', fd, fileDescriptorState->buf, 0x100, 0);
            fileDescriptorState->unk0 = bufferedReadCount;
            fileDescriptorState->unk4 = (byteCount - bytesProcessed);
            if (bufferedReadCount < (byteCount - bytesProcessed)) {
                return 1;
            }
            _uvMediaCopy(destinationBuffer + bytesProcessed, fileDescriptorState->buf, (u32) fileDescriptorState->unk4);
            bytesProcessed += fileDescriptorState->unk4;
        }

        goto ret;
    }
    while (bytesProcessed < byteCount) {
        if ((byteCount - bytesProcessed) < 0x100) {
            chunkSize = (byteCount - bytesProcessed);
        } else {
            chunkSize = 0x100;
        }
        bytesProcessed += fileuxHostRequest('R', fd, destinationBuffer + bytesProcessed, chunkSize, 1);
    }
    if (bytesProcessed != byteCount) {
        return 1;
    }
ret:
    return 0;
}
#line 355 "src/modules/fileux.c"

s32 fileuxOpen(char *path, s32 flags, s32 mode) {
    s32 fd;

    fd = fileuxHostRequest('O', path, flags, mode);
    if (fd < 0) {
        return fd;
    } else if (fd < MAX_FILE_DESCRIPTORS - 1) {
        sFileDescriptorsState[fd] = malloc8(0x10C);
        if (sFileDescriptorsState[fd] != NULL) {
            sFileDescriptorsState[fd]->unk0 = 0;
        }
    }
    return fd;
}

s32 fileuxClose(s32 fd) {
    FileDescriptorState *fileDescriptorState;

    if (fd < 0) {
        return -1;
    }
    if (fd < MAX_FILE_DESCRIPTORS - 1) {
        fileDescriptorState = sFileDescriptorsState[fd];
        if (fileDescriptorState != NULL) {
            if ((fileDescriptorState->unk0 != 0) && (fileDescriptorState->unk8 == 0)) {
                fileuxHostRequest('W', fd, fileDescriptorState->buf, fileDescriptorState->unk0);
            }
            _uvMemFree(fileDescriptorState);
            sFileDescriptorsState[fd] = NULL;
        }
    }
    if (fileuxHostRequest('C', fd) < 0) {
        return -1;
    }
    return 0;
}
