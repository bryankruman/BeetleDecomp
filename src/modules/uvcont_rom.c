// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef enum ContPeriphState {
    CONT_PERIPH_STATE_NONE = 0, // No peripheral inserted
    CONT_PERIPH_STATE_CONT_PAK = 1, // Controller pak initalized
    CONT_PERIPH_STATE_RUMBLE_PAK = 2, // Rumble pak initialized
    CONT_PERIPH_STATE_DEVICE_ERROR = 4, // No peripheral
} ContPeriphState;

typedef struct Controller_s {
    /* 0x00 */ u8 stickX;
    /* 0x01 */ u8 stickY;
    /* 0x02 */ char unused[2];
    /* 0x04 */ f32 stickAxes[3];
    /* 0x10 */ u16 button;     // Just pressed
    /* 0x12 */ u16 prevButton; // Pressed the last frame
    /* 0x14 */ u16 prevStatus;
    /* 0x16 */ u8 periphState; // Peripheral state
    /* 0x17 */ u8 prevErrno;
} Controller; /* size = 0x18 */

/* src/modules/uvcont_rom.c */
void __entrypoint_func_uvcont_rom_400000(UvCont_Exports *exports);
void func_uvcont_rom_004002B8(void);
s32 uvIOUpdate(void);
s32 uvControllerPlugged(s32 arg0);
f32 uvControllerGetStick(s32 arg0, s32 arg1);
s32 uvControllerHasButtons(s32 arg0, s32 arg1);
u16 uvControllerGetButton(s32 arg0);
s32 uvControllerButtonPress(s32 arg0, s32 arg1);
s32 uvControllerButtonRelease(s32 arg0, s32 arg1);
void uvControllerSetNormalizedState(s32 arg0, u16 arg1, u16 arg2, f32 arg3, f32 arg4);
void uvControllerGetRawState(s32 arg0, u16 *arg1, u8 *arg2, u8 *arg3);
void uvControllerSetRawState(s32 arg0, u16 arg1, u16 arg2, s8 arg3, s8 arg4);
u8 uvControllerGetPeriphState(s32 arg0);
void uvControllerSetPakStateCallback(void (*arg0)(s32, u16, u8));
void uvSetContStatusCallback(void (*arg0)(s32, u8));
u8 func_uvcont_rom_00400834(u8 arg0);
u8 func_uvcont_rom_00400974(u8 arg0);
void uvControllerInit(s32 arg0);
void uvControllerUpdate(s32 arg0);
void uvContNormalizeStick(s8 stickX, s8 stickY, f32 *outX, f32 *outY);
s32 uvControllerRepairPfs(s32 arg0);
void uvControllerSetPakIdentity(s32 arg0, s32 arg1);
s32 func_uvcont_rom_00400D5C(s32 arg0, s32 arg1, UvPfsState *arg2);
s32 uvControllerFindPakFile(s32 arg0, s32 arg1, s32 arg2);
void uvControllerAllocatePakFile(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 *arg4);
s32 uvControllerGetPakFileCounts(s32 arg0, s32 *arg1, s32 *arg2);
s32 uvControllerGetPakFreeBytes(s32 arg0, s32 *arg1);
s32 func_uvcont_rom_00401024(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4);
s32 uvControllerWritePakAligned(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4);
s32 uvControllerPakDeleteFile(s32 arg0, s32 arg1);
void uvControllerInitPak(s32 arg0);
void uvControllerEncodePakName(u8 *arg0, u8 *arg1, s32 arg2);
void func_uvcont_rom_00401478(u8 *arg0, u8 *arg1, s32 arg2);
void func_uvcont_rom_00401518(s32 arg0);
s32 uvControllerStartRumblePak(s32 arg0);
s32 uvControllerStopRumblePak(s32 arg0);
s32 uvControllerReinitializeAndStopRumble(s32 arg0);
void uvControllerReinitializeAndStopAllRumble(void);
void uvControllerRumbleInit(s32 arg0);
void func_uvcont_rom_0040183C(s32 arg0);

// private libultra function
extern s32 __osMotorAccess(OSPfs *pfs, s32 flag);

// .bss
extern Controller sControllers[MAXCONTROLLERS + 1];
extern OSPfs sControllersPfs[MAXCONTROLLERS];
extern s32 D_uvcont_rom_00401880;
extern OSContPad sContPads[];
extern OSContStatus *D_uvcont_rom_00401AD8;
extern OSMesgQueue *sPfsMQ;
extern void *D_uvcont_rom_00401AE0;
extern u8 sContBitPattern;
extern void (*sContStatusCallback)(s32, u8);
extern void (*sPakStateCallback)(s32, u16, u8);
extern s32 D_uvcont_rom_00401B10;
extern OSPfs sControllersPfs[];
extern s16 D_uvcont_rom_00401B08;
extern s32 D_uvcont_rom_00401B0C;
extern OSPfsState D_uvcont_rom_00401AB8;
extern u8 D_uvcont_rom_00401AF0;
extern u8 D_uvcont_rom_00401B00;

// from kernel/main.c
extern s32 gNmiAsserted;

void uvControllerReinitializeAndStopAllRumble(void);

void __entrypoint_func_uvcont_rom_400000(UvCont_Exports *exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->uvIOUpdate = uvIOUpdate;
    exports->uvControllerPlugged = uvControllerPlugged;
    exports->uvControllerGetStick = uvControllerGetStick;
    exports->uvControllerHasButtons = uvControllerHasButtons;
    exports->uvControllerGetButton = uvControllerGetButton;
    exports->uvControllerButtonPress = uvControllerButtonPress;
    exports->uvControllerButtonRelease = uvControllerButtonRelease;
    exports->uvControllerSetNormalizedState = uvControllerSetNormalizedState;
    exports->uvControllerGetRawState = uvControllerGetRawState;
    exports->func_uvcont_rom_004002B8 = func_uvcont_rom_004002B8;
    exports->uvControllerSetRawState = uvControllerSetRawState;
    exports->uvControllerGetPakFreeBytes = uvControllerGetPakFreeBytes;
    exports->uvControllerGetPeriphState = uvControllerGetPeriphState;
    exports->func_uvcont_rom_00401024 = func_uvcont_rom_00401024;
    exports->uvControllerSetPakStateCallback = uvControllerSetPakStateCallback;
    exports->uvControllerWritePakAligned = uvControllerWritePakAligned;
    exports->uvSetContStatusCallback = uvSetContStatusCallback;
    exports->uvControllerPakDeleteFile = uvControllerPakDeleteFile;
    exports->uvControllerRepairPfs = uvControllerRepairPfs;
    exports->uvControllerStartRumblePak = uvControllerStartRumblePak;
    exports->uvControllerSetPakIdentity = uvControllerSetPakIdentity;
    exports->uvControllerStopRumblePak = uvControllerStopRumblePak;
    exports->func_uvcont_rom_00400D5C = func_uvcont_rom_00400D5C;
    exports->uvControllerReinitializeAndStopRumble = uvControllerReinitializeAndStopRumble;
    exports->uvControllerFindPakFile = uvControllerFindPakFile;
    exports->uvControllerReinitializeAndStopAllRumble = uvControllerReinitializeAndStopAllRumble;
    exports->uvControllerAllocatePakFile = uvControllerAllocatePakFile;
    exports->uvControllerGetPakFileCounts = uvControllerGetPakFileCounts;
#ifdef __sgi
#line 1
#endif
    sContBitPattern = uvContMesgInit(&sPfsMQ, &D_uvcont_rom_00401AD8);
    osContStartQuery(sPfsMQ);
    osRecvMesg(sPfsMQ, &D_uvcont_rom_00401AE0, 1);
    osContGetQuery(D_uvcont_rom_00401AD8);

    for (i = 0; i < 4; i++) {
        if (D_uvcont_rom_00401AD8[i].errno == 0) {
            sContBitPattern |= 1 << i;
            goto success; // this confused m2c
        } else {
            sContBitPattern &= ~(1 << i);
            sControllers[i].periphState = 0;
            continue;
        }

    success:
        D_uvcont_rom_00401B10 = i;
        uvControllerInit(i);
        if (D_uvcont_rom_00401AD8[i].status & 1) {
            uvControllerInitPak(i);
            uvControllerRumbleInit(i);
        }
    }

    osContSetCh(4);
}

void func_uvcont_rom_004002B8(void) {
    uvControllerReinitializeAndStopAllRumble();
}

s32 uvIOUpdate(void) {
    s32 i;
    u8 temp_s1;
    static s32 D_uvcont_rom_00401880 = 0;

    if (osContStartReadData(sPfsMQ) != 0) {
        return 1;
    }

    osRecvMesg(sPfsMQ, &D_uvcont_rom_00401AE0, 1);
    osContGetReadData(sContPads);
    D_uvcont_rom_00401880--;
    if ((D_uvcont_rom_00401880 < 0) || (gNmiAsserted != 0)) {
        osContStartQuery(sPfsMQ);
        osRecvMesg(sPfsMQ, &D_uvcont_rom_00401AE0, 1);
        osContGetQuery(D_uvcont_rom_00401AD8);
        D_uvcont_rom_00401880 = 0x1E;
    }
    if (gNmiAsserted != 0) {
        uvControllerReinitializeAndStopAllRumble();
    }
    for (i = 0; i < (D_uvcont_rom_00401B10 + 1); i++) {
        if (D_uvcont_rom_00401AD8[i].errno != sControllers[i].prevErrno) {
            if (D_uvcont_rom_00401AD8[i].errno == 0) {
                sContBitPattern |= (1 << i);
                uvControllerInit(i);
                uvControllerInitPak(i);
                uvControllerRumbleInit(i);
            } else {
                sContBitPattern &= ~(1 << i);
                sControllers[i].periphState = 0U;
            }
            if (sContStatusCallback != NULL) {
                sContStatusCallback(i, (sContBitPattern >> i) & 1);
            }
            sControllers[i].prevErrno = D_uvcont_rom_00401AD8[i].errno;
        }
        if (!((sContBitPattern >> i) & 1)) {
            continue;
        }
        if (D_uvcont_rom_00401AD8[i].status != sControllers[i].prevStatus) {
            temp_s1 = sControllers[i].periphState;
            switch (D_uvcont_rom_00401AD8[i].status) { /* irregular */
                case CONT_CARD_ON:                     // Device has been inserted
                    uvControllerInitPak(i);
                    uvControllerRumbleInit(i);
                    if (sPakStateCallback != NULL) {
                        sPakStateCallback(i, temp_s1, sControllers[i].periphState);
                    }
                    break;
                case CONT_CARD_PULL: // Device has been removed
                    sControllers[i].periphState = 0U;
                    if (sPakStateCallback != NULL) {
                        sPakStateCallback(i, temp_s1, 0U);
                    }
                    break;
            }
        }
        uvControllerUpdate(i);
        if (!(D_uvcont_rom_00401AD8[i].type & 4)) {
            continue;
        } else if (!(D_uvcont_rom_00401AD8[i].status & 1)) {
            continue;
        } else {
            if (((u32) sControllers[i].periphState) && !(sControllers[i].periphState & 8)) {
                if (sControllers[i].periphState & CONT_PERIPH_STATE_CONT_PAK) {
                    func_uvcont_rom_00401518(i);
                }
                if (sControllers[i].periphState & CONT_PERIPH_STATE_RUMBLE_PAK) {
                    func_uvcont_rom_0040183C(i);
                }
            }
        }
    }
    return 1;
}

s32 uvControllerPlugged(s32 contNo) {
    return ((s32) sContBitPattern >> contNo) & 1;
}

f32 uvControllerGetStick(s32 contNo, s32 axis) {
    return sControllers[contNo].stickAxes[axis];
}

#line 118 "src/modules/uvcont_rom.c"
/* Return whether any requested controller-button bit is currently held.
 * Controller bounds retain the original caller contract. */
s32 uvControllerHasButtons(s32 controller, s32 mask) {
    return sControllers[controller].button & mask ? TRUE : FALSE;
}
#line 121 "src/modules/uvcont_rom.c"

u16 uvControllerGetButton(s32 contNo) {
    return sControllers[contNo].button;
}

s32 uvControllerButtonPress(s32 contNo, s32 button) {
    if ((sControllers[contNo].button & button) && !(sControllers[contNo].prevButton & button)) {
        return TRUE;
    }
    return FALSE;
}

s32 uvControllerButtonRelease(s32 contNo, s32 button) {
    if (!(sControllers[contNo].button & button) && (sControllers[contNo].prevButton & button)) {
        return TRUE;
    }
    return FALSE;
}

#line 140 "src/modules/uvcont_rom.c"
/* Store previous/current button words and already normalized stick axes.
 * Raw stick-byte fields are intentionally unchanged. */
void uvControllerSetNormalizedState(s32 contNo, u16 prevButton, u16 button, f32 x, f32 y) {
    sControllers[contNo].prevButton = prevButton;
    sControllers[contNo].button = button;
    sControllers[contNo].stickAxes[0] = x;
    sControllers[contNo].stickAxes[1] = y;
}
#line 146 "src/modules/uvcont_rom.c"

#line 147 "src/modules/uvcont_rom.c"
/* Copy raw stick bytes and current buttons to the caller outputs.
 * Preserve the raw byte representations and original output order. */
void uvControllerGetRawState(s32 contNo, u16 *button, u8 *stickX, u8 *stickY) {
    *stickX = sControllers[contNo].stickX;
    *stickY = sControllers[contNo].stickY;
    *button = sControllers[contNo].button;
}
#line 152 "src/modules/uvcont_rom.c"

#line 153 "src/modules/uvcont_rom.c"
/* Store previous/current buttons and normalize supplied signed stick bytes
 * into the two shared stick axes. Preserve other controller fields. */
void uvControllerSetRawState(s32 controller, u16 previousButtons, u16 buttons, s8 stickX, s8 stickY) {
    sControllers[controller].prevButton = previousButtons;
    sControllers[controller].button = buttons;
    uvContNormalizeStick(stickX, stickY, sControllers[controller].stickAxes, &sControllers[controller].stickAxes[1]);
}
#line 158 "src/modules/uvcont_rom.c"

u8 uvControllerGetPeriphState(s32 arg0) {
    return sControllers[arg0].periphState;
}

void uvControllerSetPakStateCallback(void (*pakStateCallback)(s32, u16, u8)) {
    sPakStateCallback = pakStateCallback;
}

void uvSetContStatusCallback(void (*contStatusCallback)(s32, u8)) {
    sContStatusCallback = contStatusCallback;
}

u8 D_uvcont_rom_00401884[15] = {
    0x21, 0x22, 0x23, 0x27, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x3A, 0x3D, 0x3F, 0x40, 0,
};

u8 func_uvcont_rom_00400834(u8 arg0) {
    s32 i;

    if (arg0 < 0x20) {
        return 0;
    }
    if (arg0 == 0x20) {
        return 0xF;
    }
    if (arg0 < 0x30) {
        for (i = 0; i < 14; i++) {
            if (arg0 == D_uvcont_rom_00401884[i]) {
                return D_uvcont_rom_00401884[i] + 0x34;
            }
        }
        return 0x20;
    }
    if (arg0 < 0x3A) {
        return arg0 - 0x20;
    }
    if (arg0 < 0x5B) {
        return arg0 - 0x27;
    }
    return 0x3B;
}

u8 func_uvcont_rom_00400974(u8 arg0) {
    if (arg0 < 15) {
        return 0x2DU;
    }
    if (arg0 == 15) {
        return 0x20U;
    }
    if (arg0 < 0x1A) {
        return (arg0 + 0x20);
    }
    if (arg0 < 0x34) {
        return (arg0 + 0x27);
    }
    if (arg0 < 0x42) {
        return D_uvcont_rom_00401884[arg0 - 0x34];
    }
    return 0x2D;
}

void uvControllerInit(s32 contNo) {
    s32 i;

    for (i = 0; i < 3; i++) {
        sControllers[contNo].stickAxes[i] = 0.0f;
    }

    sControllers[contNo].button = 0;
    sControllers[contNo].prevButton = 0;
    sControllers[contNo].periphState = 0;
    sControllers[contNo].prevStatus = D_uvcont_rom_00401AD8[contNo].status;
    sControllers[contNo].prevErrno = D_uvcont_rom_00401AD8[contNo].errno;
    sContPads[contNo].button = 0;
    sContPads[contNo].stick_x = 0;
    sContPads[contNo].stick_y = 0;
    sContPads[contNo].errno = 0;
}

void uvControllerUpdate(s32 contNo) {
    Controller *controller;
    controller = &sControllers[contNo];
    uvContNormalizeStick(sContPads[contNo].stick_x, sContPads[contNo].stick_y,
                         &controller->stickAxes[0], &controller->stickAxes[1]);

    controller->prevButton = controller->button;
    controller->button = sContPads[contNo].button;
    controller->stickX = sContPads[contNo].stick_x;
    controller->stickY = sContPads[contNo].stick_y;
    controller->prevStatus = D_uvcont_rom_00401AD8[contNo].status;
    controller->prevErrno = D_uvcont_rom_00401AD8[contNo].errno;
}

void uvContNormalizeStick(s8 stickX, s8 stickY, f32 *outX, f32 *outY) {
    if (stickX < 0) {
        if (stickX < -68) {
            stickX = -68;
        } else if (stickX >= -6) {
            stickX = -7;
        }
        *outX = (stickX + 7) / 61.0f;
    } else {
        if (stickX >= 0x45) {
            stickX = 68;
        } else if (stickX < 7) {
            stickX = 7;
        }
        *outX = (stickX - 7) / 61.0f;
    }
    if (stickY < 0) {
        if (stickY < -70) {
            stickY = -70;
        } else if (stickY >= -6) {
            stickY = -7;
        }
        *outY = (stickY + 7) / 63.0f;
    } else {
        if (stickY >= 71) {
            stickY = 70;
        } else if (stickY < 7) {
            stickY = 7;
        }
        *outY = (stickY - 7) / 63.0f;
    }
}

s32 uvControllerRepairPfs(s32 contNo) {
    Controller *controller;

    controller = &sControllers[contNo];
    if (!(controller->periphState & CONT_PERIPH_STATE_CONT_PAK)) {
        return FALSE;
    }
    osPfsInitPak(sPfsMQ, &sControllersPfs[contNo], contNo);
    if (osPfsRepairId(&sControllersPfs[contNo]) == 0) {
        osPfsInitPak(sPfsMQ, &sControllersPfs[contNo], contNo);
        controller->periphState = CONT_PERIPH_STATE_CONT_PAK;
        return TRUE;
    }
    return FALSE;
}

#line 301 "src/modules/uvcont_rom.c"
/* Set the shared company/game identity used by later Controller Pak file
 * operations. Narrowing to the SDK company-code width occurs in those callers. */
void uvControllerSetPakIdentity(s32 companyCode, s32 gameCode) {
    D_uvcont_rom_00401B08 = companyCode;
    D_uvcont_rom_00401B0C = gameCode;
}
#line 305 "src/modules/uvcont_rom.c"

s32 func_uvcont_rom_00400D5C(s32 arg0, s32 arg1, UvPfsState *arg2) {
    if (!(sControllers[arg0].periphState & CONT_PERIPH_STATE_CONT_PAK)) {
        return FALSE;
    }
    if (sControllers[arg0].periphState & 8) {
        return FALSE;
    }
    if (osPfsFileState(&sControllersPfs[arg0], arg1, &D_uvcont_rom_00401AB8) == 0) {
        arg2->companyCode = D_uvcont_rom_00401AB8.company_code;
        arg2->gameCode = D_uvcont_rom_00401AB8.game_code;
        arg2->fileSize = D_uvcont_rom_00401AB8.file_size;
        func_uvcont_rom_00401478(&arg2->gameName[1], D_uvcont_rom_00401AB8.game_name, 0x10);
        func_uvcont_rom_00401478(arg2->extName, D_uvcont_rom_00401AB8.ext_name, 4);
        arg2->gameName[17] = 0;
        arg2->gameName[0] = 0;
        return TRUE;
    }
    return FALSE;
}

#line 326 "src/modules/uvcont_rom.c"
/* Encode the game/extension names and locate the matching Pak file using
 * the shared company/game identity. Return its file number or -1 on SDK error. */
s32 uvControllerFindPakFile(s32 controller, s32 gameName, s32 extensionName) {
    s32 fileNumber;

    uvControllerEncodePakName(&D_uvcont_rom_00401AF0, gameName, 0x10);
    uvControllerEncodePakName(&D_uvcont_rom_00401B00, extensionName, 4);
    if (osPfsFindFile(&sControllersPfs[controller], (u16) D_uvcont_rom_00401B08,
                      (u32) D_uvcont_rom_00401B0C, &D_uvcont_rom_00401AF0, &D_uvcont_rom_00401B00,
                      &fileNumber)
        == 0) {
        return fileNumber;
    }
    return -1;
}
#line 339 "src/modules/uvcont_rom.c"

#line 340 "src/modules/uvcont_rom.c"
/* Encode fixed-width game and extension names, then request SDK Pak allocation.
 * Preserve the original void interface: SDK errors are not returned here. */
void uvControllerAllocatePakFile(s32 controller, u8 *gameName, u8 *extensionName, s32 byteCount, s32 *fileNumber) {
    uvControllerEncodePakName(&D_uvcont_rom_00401AF0, gameName, 0x10);
    uvControllerEncodePakName(&D_uvcont_rom_00401B00, extensionName, 4);
    osPfsAllocateFile(&sControllersPfs[controller], (u16) D_uvcont_rom_00401B08,
                      (u32) D_uvcont_rom_00401B0C, &D_uvcont_rom_00401AF0, &D_uvcont_rom_00401B00, byteCount,
                      fileNumber);
}
#line 347 "src/modules/uvcont_rom.c"

#line 348 "src/modules/uvcont_rom.c"
/* Return one when the SDK fills the maximum/used file counts successfully.
 * Preserve the SDK output contract and original zero-on-error behavior. */
s32 uvControllerGetPakFileCounts(s32 controller, s32 *maximumFiles, s32 *usedFiles) {
    if (osPfsNumFiles(&sControllersPfs[controller], maximumFiles, usedFiles) == 0) {
        return TRUE;
    }
    return FALSE;
}
#line 354 "src/modules/uvcont_rom.c"

#line 355 "src/modules/uvcont_rom.c"
/* Return one when the SDK reports free Controller Pak bytes successfully,
 * or zero on error. Output contents on error remain SDK-defined. */
s32 uvControllerGetPakFreeBytes(s32 controller, s32 *freeBytes) {
    if (osPfsFreeBlocks(&sControllersPfs[controller], freeBytes) == 0) {
        return TRUE;
    }
    return FALSE;
}
#line 361 "src/modules/uvcont_rom.c"

s32 func_uvcont_rom_00401024(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    s32 var_s2;
    s32 temp_v0;
    u8 *var_s0;

    if (arg3 % 32) {
        var_s2 = ((arg3 / 32) << 5) + 0x20;
    } else {
        var_s2 = arg3;
    }
    arg2 = (arg2 / 32) << 5;
    if (var_s2 != arg3) {
        var_s0 = _uvMemAllocAlign8((u32) var_s2);
    } else {
        var_s0 = arg4;
    }
    temp_v0 = osPfsReadWriteFile(&sControllersPfs[arg0], arg1, 0U, arg2, arg3, var_s0);
    if ((temp_v0 == 0) && (var_s0 != NULL) && (var_s2 != arg3)) {
        _uvMediaCopy(arg4, var_s0, (u32) arg3);
    }
    if ((var_s2 != arg3) && (var_s0 != NULL)) {
        _uvMemFree(var_s0);
    }
    return temp_v0;
}

/* Write the aligned Controller Pak range and preserve the SDK status that
 * original callers inspect (zero means success). */
#line 390 "src/modules/uvcont_rom.c"
/* Align the offset down and round the byte count up to 32-byte Pak blocks.
 * Return the SDK write status; the caller must provide the rounded buffer size. */
s32 uvControllerWritePakAligned(s32 controller, s32 fileNumber, s32 offset, s32 byteCount, u8 *data) {
    if (byteCount % 32) {
        byteCount = ((byteCount / 32) << 5) + 0x20;
    }
    offset = (offset / 32) << 5;
    return osPfsReadWriteFile(&sControllersPfs[controller], fileNumber, 1U, offset, byteCount, data);
}
#line 397 "src/modules/uvcont_rom.c"

s32 uvControllerPakDeleteFile(s32 arg0, s32 arg1) {
    UvPfsState uvPfsState;

    if (func_uvcont_rom_00400D5C(arg0, arg1, &uvPfsState) == 0) {
        return FALSE;
    }
    if (osPfsDeleteFile(&sControllersPfs[arg0], D_uvcont_rom_00401AB8.company_code,
                        D_uvcont_rom_00401AB8.game_code, D_uvcont_rom_00401AB8.game_name,
                        D_uvcont_rom_00401AB8.ext_name)
        == 0) {
        return TRUE;
    }
    return FALSE;
}

void uvControllerInitPak(s32 arg0) {
    u32 ret;

    osContStartQuery(sPfsMQ);
    osRecvMesg(sPfsMQ, &D_uvcont_rom_00401AE0, 1);
    osContGetQuery(D_uvcont_rom_00401AD8);
    ret = osPfsInitPak(sPfsMQ, &sControllersPfs[arg0], arg0);
    switch (ret) {
        case 0: // success
            sControllers[arg0].periphState = CONT_PERIPH_STATE_CONT_PAK;
            break;
        case PFS_ERR_NOPACK:
            sControllers[arg0].periphState = CONT_PERIPH_STATE_NONE;
            break;
        case PFS_ERR_DEVICE:
            sControllers[arg0].periphState = CONT_PERIPH_STATE_DEVICE_ERROR;
            break;
        case PFS_ERR_ID_FATAL:
            sControllers[arg0].periphState = 9;
            break;
        case PFS_ERR_CONTRFAIL:
            sControllers[arg0].periphState = 0x20;
            break;
        case PFS_ERR_NEW_PACK:
            sControllers[arg0].periphState = 0x11;
        default:
            break;
    }
}

#line 443 "src/modules/uvcont_rom.c"
/* Encode a fixed-width Pak name, zero-filling from the first input terminator.
 * Preserve the original character conversion and caller-owned buffer lengths. */
void uvControllerEncodePakName(u8 *output, u8 *input, s32 length) {
    s32 nullTerminate;
    s32 i;

    nullTerminate = FALSE;
    for (i = 0; i < length; i++) {
        if (input[i] == 0) {
            nullTerminate = TRUE;
        }
        if (nullTerminate) {
            output[i] = '\0';
        } else {
            output[i] = func_uvcont_rom_00400834(input[i]);
        }
    }
}
#line 459 "src/modules/uvcont_rom.c"

void func_uvcont_rom_00401478(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 nullTerminate;
    s32 i;

    nullTerminate = FALSE;
    for (i = 0; i < arg2; i++) {
        if (arg1[i] == 0) {
            nullTerminate = TRUE;
        }
        if (nullTerminate) {
            arg0[i] = '\0';
        } else {
            arg0[i] = func_uvcont_rom_00400974(arg1[i]);
        }
    }

    arg0[arg2] = '\0';
}

void func_uvcont_rom_00401518(s32 arg0) {
}

s32 uvControllerStartRumblePak(s32 contNo) {
    if (!(sControllers[contNo].periphState & CONT_PERIPH_STATE_RUMBLE_PAK)) {
        return FALSE;
    }
    if (sControllers[contNo].periphState & 8) {
        return FALSE;
    }
    if (gNmiAsserted != 0) {
        return FALSE;
    }

    // Start the motor
    if (__osMotorAccess(&sControllersPfs[contNo], 1) == 0) {
        return TRUE;
    }
    sControllers[contNo].periphState |= 8;
    return FALSE;
}

s32 uvControllerStopRumblePak(s32 contNo) {
    if (!(sControllers[contNo].periphState & CONT_PERIPH_STATE_RUMBLE_PAK)) {
        return FALSE;
    }
    if (sControllers[contNo].periphState & 8) {
        return FALSE;
    }

    // Stop the motor
    __osMotorAccess(&sControllersPfs[contNo], 0);
    return TRUE;
}

#line 514 "src/modules/uvcont_rom.c"
/* For a rumble peripheral, initialize Pak/motor state and send four stop requests.
 * Return whether a rumble peripheral was selected; SDK statuses remain ignored. */
s32 uvControllerReinitializeAndStopRumble(s32 contNo) {
    if (!(sControllers[contNo].periphState & CONT_PERIPH_STATE_RUMBLE_PAK)) {
        return FALSE;
    }
    osPfsInitPak(sPfsMQ, &sControllersPfs[contNo], contNo);
    osMotorInit(sPfsMQ, &sControllersPfs[contNo], contNo);

    // Why do this four times?
    __osMotorAccess(&sControllersPfs[contNo], 0);
    __osMotorAccess(&sControllersPfs[contNo], 0);
    __osMotorAccess(&sControllersPfs[contNo], 0);
    __osMotorAccess(&sControllersPfs[contNo], 0);
    return TRUE;
}
#line 528 "src/modules/uvcont_rom.c"

#line 529 "src/modules/uvcont_rom.c"
/* Apply the original rumble reinitialization/stop sequence to every controller. */
void uvControllerReinitializeAndStopAllRumble(void) {
    s32 i;
    for (i = 0; i < MAXCONTROLLERS; i++) {
        uvControllerReinitializeAndStopRumble(i);
    }
}
#line 535 "src/modules/uvcont_rom.c"

void uvControllerRumbleInit(s32 arg0) {
    Controller *controller;

    controller = &sControllers[arg0];
    if (!(controller->periphState & CONT_PERIPH_STATE_CONT_PAK) || (controller->periphState & 8)) {
        switch (osMotorInit(sPfsMQ, &sControllersPfs[arg0], arg0)) {
            case 0:
                controller->periphState = CONT_PERIPH_STATE_RUMBLE_PAK;
                return;
            case 1:
                controller->periphState = CONT_PERIPH_STATE_NONE;
                return;
            case 11:
                if (!(controller->periphState & CONT_PERIPH_STATE_CONT_PAK)) {
                    controller->periphState = CONT_PERIPH_STATE_DEVICE_ERROR;
                    return;
                }
                break;
            case 4:
                controller->periphState = 0xA;
                break;
        }
    }
}

void func_uvcont_rom_0040183C(s32 arg0) {
}

// unused
s32 D_uvcont_rom_00401892[3] = { 0x00700000, __entrypoint_func_uvcont_rom_400000, 0 };
