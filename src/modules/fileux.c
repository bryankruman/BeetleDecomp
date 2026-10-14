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

/*
 * Initialize the module allocation pointer and publish five exports: the
 * empty cleanup entry plus file write, read, open and close wrappers.
 * RE_UNKNOWN: Export-object extent and lifetime are loader obligations.
 * This initializer does not establish a working host transport or initialize
 * the shared response storage and per-descriptor state array.
 */
#line 55 "src/modules/fileux.c"
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

/* Return one: fileuxHostRequest bypasses its zero-result branch and ignores
 * seven later results. RE_UNKNOWN: intended protocol/status meaning. */
#line 98 "src/modules/fileux.c"
s32 func_fileux_00400144(void) {
    return 1;
}
#line 101 "src/modules/fileux.c"

/*
 * Call GMGR slot 0x74, fill a 256-byte ascending probe, then scan the shared
 * response for a descending probe. Serialize the mode word and mode-specific
 * arguments: O appends path/NUL/flags and an optional word for flag 0x100;
 * R copies response chunks of at most 256 bytes; W rounds payload length up
 * to an 8-byte boundary; C sends a descriptor; L sends it and two opaque words.
 * Return the first response word for O/W/C/L, requested bytes for R, or -1
 * for unsupported modes. Preserve each hook/handshake call in its exact order.
 * RE_ORIGINAL_QUIRK: The original buffer hook is empty and handshake returns
 * 1. Keep the unused probe result and inherited empty/address-test compiler
 * scaffolding; an inherited empty test reads an uninitialized response local.
 * Preserve the varargs handling and signed rounding.
 * RE_UNKNOWN: A functioning host transport, path/request bounds, varargs ABI,
 * valid lengths/addresses and response storage freshness are not proved.
 */
#line 102 "src/modules/fileux.c"
s32 fileuxHostRequest(s32 mode, ...) {
    u8 request[0x100];
    u8 *writeCursor;
    u8 *path;
    s32 bufferAddress;
    s32 descriptor;
    s32 i; // a3
    s32 remainingBytes;
    s32 openFlags;
    s32 chunkBytes;
    s32 requestedBytes;
    s32 modeLWord0;
    s32 modeLWord1;
    s32 readOptionWord;
    va_list args;
    s32 responseWord;

    gUvGfxMgrExports->uvGfxWaitIfRequested();
    writeCursor = request;
    for (i = 0; i < 0x100; i++) {
        request[i] = i;
    }

    fileuxNoOpHostBufferHook(writeCursor, 0x100);
    if (func_fileux_00400144() == 0) {
        return -1;
    }

    i = 0;
    do {
    } while ((D_fileux_00400CF8[i] == (0xFF - i)) && (++i < 0x100));
    if (i) {
    }

    _uvMediaCopy(request, &mode, sizeof(int));
    writeCursor += 4;
    va_start(args, mode);
    switch (mode) {
        case 'O':
            path = va_arg(args, u8 *);
            openFlags = va_arg(args, s32);
            fileuxStrcpy(&writeCursor, path, fileuxStrlen(path));
            *writeCursor = '\0';
            writeCursor += 1;
            fileuxStrcpy(&writeCursor, (u8*)&openFlags, 4);
            if (openFlags & 0x100) {
                i = va_arg(args, s32);
                fileuxStrcpy(&writeCursor, (u8 *) &i, 4);
            } else {
                i = 0;
            }
            fileuxNoOpHostBufferHook(request, 0x100);
            func_fileux_00400144();
            responseWord = ((s32 *) D_fileux_00400CF8)[0];
            return responseWord;
        case 'R':
            descriptor = va_arg(args, s32);
            bufferAddress = va_arg(args, s32);
            requestedBytes = va_arg(args, s32);
            readOptionWord = va_arg(args, s32);
            fileuxStrcpy(&writeCursor, (u8*)&descriptor, 4);
            fileuxStrcpy(&writeCursor, (u8*)&requestedBytes, 4);
            fileuxNoOpHostBufferHook(request, 0x100);
            func_fileux_00400144();

            if (readOptionWord != 0) {
                // FAKE
                if (&readOptionWord) {
                }
                if (&readOptionWord) {
                }
            }
            request[0] = 6;
            fileuxNoOpHostBufferHook(request, 0x100);
            for (i = 0; i < requestedBytes;) {
                remainingBytes = requestedBytes - i;
                if (remainingBytes < 0x100) {
                    chunkBytes = remainingBytes;
                } else {
                    chunkBytes = 0x100;
                }
                func_fileux_00400144();
                _uvMediaCopy(bufferAddress + i, D_fileux_00400CF8, chunkBytes);
                i += chunkBytes;
            }

            // FAKE
            if ((responseWord && responseWord) && responseWord) {
            }
            return requestedBytes;
        case 'W':
            descriptor = va_arg(args, s32);
            bufferAddress = va_arg(args, s32);
            requestedBytes = va_arg(args, s32);
            fileuxStrcpy(&writeCursor, (u8 *) &descriptor, 4);
            fileuxStrcpy(&writeCursor, (u8 *) &requestedBytes, 4);
            fileuxNoOpHostBufferHook(request, 0x100);
            func_fileux_00400144();
            i = requestedBytes;
            if (requestedBytes & 7) {
                i = (requestedBytes - (requestedBytes % 8)) + 8;
            }
            fileuxNoOpHostBufferHook(bufferAddress, i);
            func_fileux_00400144();
            responseWord = ((s32 *) D_fileux_00400CF8)[0];
            return responseWord;
        case 'C':
            descriptor = va_arg(args, s32);
            fileuxStrcpy(&writeCursor, (u8 *) &descriptor, 4);
            fileuxNoOpHostBufferHook(request, 0x100);
            func_fileux_00400144();
            responseWord = ((s32 *) D_fileux_00400CF8)[0];
            return responseWord;
        case 'L':
            descriptor = va_arg(args, s32);
            modeLWord0 = va_arg(args, s32);
            modeLWord1 = va_arg(args, s32);
            fileuxStrcpy(&writeCursor, (u8*)&descriptor, 4);
            fileuxStrcpy(&writeCursor, (u8*)&modeLWord0, 4);
            fileuxStrcpy(&writeCursor, (u8*)&modeLWord1, 4);
            fileuxNoOpHostBufferHook(request, 0x100);
            func_fileux_00400144();
            responseWord = ((s32 *) D_fileux_00400CF8)[0];
            return responseWord;
        default:
            return -1;
    }
}

/* Write through descriptor state when its buffered mode permits; otherwise
 * send W requests in chunks of at most 256 bytes. A final buffered chunk of
 * at most 256 bytes is retained rather than sent immediately.
 * RE_ORIGINAL_QUIRK: retain 0/1 status returns and discard the full-buffer
 * flush response before clearing its pending count.
 * RE_UNKNOWN: valid counts, state ownership, host status and progress on
 * short/failed requests; this wrapper proves no completed host transfer. */
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
/* Consume retained descriptor bytes or issue R requests of at most 256
 * bytes. A buffered refill requests 256 bytes, copies the requested remainder
 * and tracks any surplus with the existing count and read cursor.
 * RE_ORIGINAL_QUIRK: retain 0/1 status returns; the refill count and requested
 * cursor are stored before the short-refill test. Preserve this state on error.
 * RE_UNKNOWN: valid counts, state ownership, host status and progress on
 * short/failed requests; no positive-progress guard is added. */
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

/*
 * Send an O request with path, flags and mode. Preserve any negative result.
 * For a returned descriptor below 20, allocate 0x10C bytes of state and clear
 * only its first word when allocation succeeds; return the descriptor anyway.
 * RE_ORIGINAL_QUIRK: The declared 21-slot array uses a strict below-20 gate.
 * Allocation failure and descriptors at or above 20 still return unchanged.
 * RE_UNKNOWN: Descriptor range/uniqueness, replacement of existing state,
 * remaining state-word initialization and real host availability need proof.
 */
#line 356 "src/modules/fileux.c"
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

/*
 * Reject negative descriptors. Below 20, inspect optional descriptor state;
 * when its first word is nonzero and word 8 is zero, send a W request before
 * freeing the state and clearing its slot. Then send C for every nonnegative
 * descriptor, returning -1 for a negative response and zero otherwise.
 * RE_ORIGINAL_QUIRK: Ignore the W response and free state before checking C;
 * descriptors at or above 20 bypass the state array but still reach C.
 * RE_UNKNOWN: State-field meanings, flush success, concurrent users and
 * descriptor/host lifetime remain unproved; no error rollback is introduced.
 */
#line 371 "src/modules/fileux.c"
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
