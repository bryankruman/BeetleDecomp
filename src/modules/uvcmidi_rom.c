// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef struct MidiSettings_s {
    /* 0x00 */ s32 unk0;   /* inferred */
    /* 0x04 */ void *unk4; /* inferred */
    /* 0x08 */ u16 unk8;   /* inferred */
    /* 0x0A */ u16 unkA;   /* inferred */
    /* 0x0C */ u16 unkC;   /* inferred */
    /* 0x0E */ char padE[2];
} MidiSettings; /* size = 0x10 */

void __entrypoint_func_uvcmidi_rom_400000(UvCMidi_Exports *exports);
void uvaCleanup(void);
void uvaLoadBank(s32 arg0);
void uvaSetSeq(s32 seqId);
void uvaSeqPlay(void);
void uvaSeqSetPosition(u32 arg0);
void uvaSeqSetTempo(f32 arg0);
f32 uvaSeqGetTempo(void);
void uvaSeqGetTicks(void);
void func_uvcmidi_rom_00400878(void);
void uvaSeqGetState(void);
void uvaSeqSetVol(f32 arg0);
void uvaSeqStop(void);
void uvaSeqStop(void);
f32 uvaGetChannelPriority(u8 chan);
void uvaSetChannelPriority(u8 chan, u8 priority);
void func_uvcmidi_rom_00400A38(u8 byte, u8 byte2);
f32 func_uvcmidi_rom_00400A84(u8 channel);
void func_uvcmidi_rom_00400AC8(u8 channel, u8 mix);
void func_uvcmidi_rom_00400AFC(u8 byte1, u8 byte2);
f32 func_uvcmidi_rom_00400B48(u8 channel);
void uvaSetChannelPan(u8 channel, s32 pan);
void func_uvcmidi_rom_00400BC0(u8 status, s32 byte2);
f32 func_uvcmidi_rom_00400C0C(u8 arg0);
void func_uvcmidi_rom_00400C3C(u8 channel, s32 program);
void func_uvcmidi_rom_00400C70(u8 arg0, s32 arg1);
f32 uvaGetChannelVolume(u8 channel);
void func_uvcmidi_rom_00400CFC(u8 channel, u8 volume);
void func_uvcmidi_rom_00400D30(u8 arg0, u8 arg1);
void func_uvcmidi_rom_00400D7C(u8 status, u8 byte1, u8 byte2);
void func_uvcmidi_rom_00400DC0(u8 arg0, u8 arg1, u8 arg2);
void func_uvcmidi_rom_00400E10(u8 arg0, u8 arg1, u8 arg2);
void func_uvcmidi_rom_00400E60(u8 *arg0, s32 arg1, s32 *arg2);
ALVoiceState *uvaGetFreeVoiceList(void);
void uvaGetAllocatedVoiceList(ALVoiceState **arg0, ALVoiceState **arg1);
s32 func_uvcmidi_rom_00400EF8(void);
void func_uvcmidi_rom_00400F04(u8 *arg0);
ALSeqPlayer *uvaGetSeqPlayer(void);
s16 uvaGetSeqCount(void);

extern ALSeqPlayer *sAudioSeqPlayer;
extern ALBank *sAudioBank;
extern ALBankFile *sAudioBankFile;
extern ALSeqFile *sAudioSeqFile;
extern void *sAudioSequencesData;
extern u16 D_uvcmidi_rom_004011F8;
extern void *D_uvcmidi_rom_004011F0;
extern ALCSeq sAudioCurrentSequence;
extern UvAudioMgr_Exports *D_uvcmidi_rom_004011FC;
extern f32 D_uvcmidi_rom_00401000;
extern f64 D_uvcmidi_rom_00401008;
extern f32 D_uvcmidi_rom_00401010;
extern f32 D_uvcmidi_rom_00401014;
extern ALSeqpConfig sAudioSeqPlayerConfig;
extern ALVoiceState *D_uvcmidi_rom_004011EC;
extern ALHeap D_uvcmidi_rom_004010B0;
extern MidiSettings *D_uvcmidi_rom_004011E8;
extern s32 D_uvcmidi_rom_004011F4;

void __entrypoint_func_uvcmidi_rom_400000(UvCMidi_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvaLoadBank = uvaLoadBank;
    exports->uvaSetSeq = uvaSetSeq;
    exports->uvaSeqPlay = uvaSeqPlay;
    exports->uvaSeqSetPosition = uvaSeqSetPosition;
    exports->uvaSeqSetTempo = uvaSeqSetTempo;
    exports->uvaSeqGetTempo = uvaSeqGetTempo;
    exports->uvaSeqGetTicks = uvaSeqGetTicks;
    exports->func_uvcmidi_rom_00400878 = func_uvcmidi_rom_00400878;
    exports->uvaSeqGetState = uvaSeqGetState;
    exports->uvaCleanup = uvaCleanup;
    exports->uvaSeqSetVol = uvaSeqSetVol;
    exports->func_uvcmidi_rom_00400BC0 = func_uvcmidi_rom_00400BC0;
    exports->uvaSeqStop = uvaSeqStop;
    exports->func_uvcmidi_rom_00400E60 = func_uvcmidi_rom_00400E60;
    exports->func_uvcmidi_rom_00400C0C = func_uvcmidi_rom_00400C0C;
    exports->uvaGetChannelPriority = uvaGetChannelPriority;
    exports->uvaGetFreeVoiceList = uvaGetFreeVoiceList;
    exports->func_uvcmidi_rom_00400C3C = func_uvcmidi_rom_00400C3C;
    exports->uvaSetChannelPriority = uvaSetChannelPriority;
    exports->uvaGetAllocatedVoiceList = uvaGetAllocatedVoiceList;
    exports->func_uvcmidi_rom_00400C70 = func_uvcmidi_rom_00400C70;
    exports->func_uvcmidi_rom_00400A38 = func_uvcmidi_rom_00400A38;
    exports->func_uvcmidi_rom_00400EF8 = func_uvcmidi_rom_00400EF8;
    exports->uvaGetChannelVolume = uvaGetChannelVolume;
    exports->func_uvcmidi_rom_00400A84 = func_uvcmidi_rom_00400A84;
    exports->func_uvcmidi_rom_00400F04 = func_uvcmidi_rom_00400F04;
    exports->func_uvcmidi_rom_00400CFC = func_uvcmidi_rom_00400CFC;
    exports->func_uvcmidi_rom_00400AC8 = func_uvcmidi_rom_00400AC8;
    exports->uvaGetSeqPlayer = uvaGetSeqPlayer;
    exports->func_uvcmidi_rom_00400D30 = func_uvcmidi_rom_00400D30;
    exports->func_uvcmidi_rom_00400AFC = func_uvcmidi_rom_00400AFC;
    exports->uvaGetSeqCount = uvaGetSeqCount;
    exports->func_uvcmidi_rom_00400D7C = func_uvcmidi_rom_00400D7C;
    exports->func_uvcmidi_rom_00400B48 = func_uvcmidi_rom_00400B48;
    exports->func_uvcmidi_rom_00400DC0 = func_uvcmidi_rom_00400DC0;
    exports->uvaSetChannelPan = uvaSetChannelPan;
    exports->func_uvcmidi_rom_00400E10 = func_uvcmidi_rom_00400E10;
    D_uvcmidi_rom_004011E8 = uvGetSystemProp(3);
    if (D_uvcmidi_rom_004011E8 == NULL) {
        sAudioSeqPlayerConfig.maxVoices = 0x10;
        sAudioSeqPlayerConfig.maxEvents = 0x100;
        sAudioSeqPlayerConfig.maxChannels = 0x10;
        D_uvcmidi_rom_004011F4 = 0;
        D_uvcmidi_rom_004011F0 = NULL;
    } else {
        if (D_uvcmidi_rom_004011E8->unk8 != 0) {
            sAudioSeqPlayerConfig.maxVoices = D_uvcmidi_rom_004011E8->unk8;
        } else {
            sAudioSeqPlayerConfig.maxVoices = 0x10;
        }
        if (D_uvcmidi_rom_004011E8->unkA != 0) {
            sAudioSeqPlayerConfig.maxEvents = D_uvcmidi_rom_004011E8->unkA;
        } else {
            sAudioSeqPlayerConfig.maxEvents = 0x100;
        }
        if (D_uvcmidi_rom_004011E8->unkC != 0) {
            sAudioSeqPlayerConfig.maxChannels = D_uvcmidi_rom_004011E8->unkC;
        } else {
            sAudioSeqPlayerConfig.maxChannels = 0x10;
        }
        D_uvcmidi_rom_004011F4 = D_uvcmidi_rom_004011E8->unk0;
        D_uvcmidi_rom_004011F0 = D_uvcmidi_rom_004011E8->unk4;
    }
    if (D_uvcmidi_rom_004011F4 == 0) {
        D_uvcmidi_rom_004011F4 = (sAudioSeqPlayerConfig.maxVoices * 0x38)
                                 + (sAudioSeqPlayerConfig.maxEvents * 0x1C)
                                 + (sAudioSeqPlayerConfig.maxChannels * 0x10) + 0x12C;
    }

    if (D_uvcmidi_rom_004011F0 == NULL) {
        D_uvcmidi_rom_004011F8 |= 1;
        D_uvcmidi_rom_004011F0 = _uvMemAllocAlign8((u32) D_uvcmidi_rom_004011F4);
    }
    uvMemSet(D_uvcmidi_rom_004011F0, 0U, (u32) D_uvcmidi_rom_004011F4);
    alHeapInit(&D_uvcmidi_rom_004010B0, (u8 *) D_uvcmidi_rom_004011F0, D_uvcmidi_rom_004011F4);
    sAudioSeqPlayerConfig.heap = &D_uvcmidi_rom_004010B0;

    // !@bug: sAudioSeqPlayer needs to be allocated before calling this function
    alCSPNew((ALCSPlayer *) sAudioSeqPlayer, &sAudioSeqPlayerConfig);
    D_uvcmidi_rom_004011EC = sAudioSeqPlayer->vFreeList;
    D_uvcmidi_rom_004011FC = uvLoadModule('AMGR');
}

// Module cleanup
void uvaCleanup(void) {
    if (alSeqpGetState(sAudioSeqPlayer) != 0) {
        uvaSeqStop();
    }
    alSeqpDelete(sAudioSeqPlayer);
    if (D_uvcmidi_rom_004011F8 & 1) {
        _uvMemFree(D_uvcmidi_rom_004011F0);
    }
    if (D_uvcmidi_rom_004011F8 & 2) {
        _uvMemFree(sAudioBankFile);
        _uvMemFree(sAudioSeqFile);
        _uvMemFree(sAudioSequencesData);
    }
    uvUnloadModule('AMGR');
}

void uvaLoadBank(s32 bankId) {
    void *bankData;
    void *tblSize;
    u32 bankSize;
    s32 fileId;
    ALSeqFile sp4C;
    s32 sp48;
    s32 maxSeqLen;
    s32 i;
    void *seqsData;

    fileId = uvFileReadHeader(uvGetFileData('UVMB', bankId));
    uvFileSearchTag(fileId, &bankSize, &bankData, '.CTL', 0);
    uvFileSearchTag(fileId, NULL, &tblSize, '.TBL', 0);
    uvFileFree(fileId);
    D_uvcmidi_rom_004011F8 |= 2;
    sAudioBankFile = malloc16(bankSize);
    _uvMediaCopy(sAudioBankFile, bankData, bankSize);
    alBnkfNew(sAudioBankFile, (u8 *) tblSize);
    sAudioBank = sAudioBankFile->bankArray[0];
    alSeqpSetBank(sAudioSeqPlayer, sAudioBank);
    fileId = uvFileReadHeader(uvGetFileData('UVMS', 0));
    uvFileSearchTag(fileId, NULL, &seqsData, 'SEQS', 0);
    uvFileFree(fileId);
    _uvMediaCopy(&sp4C, seqsData, 4);
    i = sp4C.seqCount;
    sp48 = (i * 8) + 4;
    sAudioSeqFile = malloc16(sp48);
    _uvMediaCopy(sAudioSeqFile, seqsData, sp48);
    alSeqFileNew(sAudioSeqFile, (u8 *) seqsData);
    maxSeqLen = 0;
    for (i = 0; i < sAudioSeqFile->seqCount; i++) {
        if (sAudioSeqFile->seqArray[i].len >= maxSeqLen) {
            maxSeqLen = sAudioSeqFile->seqArray[i].len;
        }
    }

    if (maxSeqLen & 1) {
        maxSeqLen += 1;
    }
    sAudioSequencesData = malloc16((u32) maxSeqLen);
}

void uvaSetSeq(s32 seqId) {
    s32 seqLen;
    s32 seqAlign;

    seqLen = sAudioSeqFile->seqArray[seqId].len;
    seqAlign = seqLen;
    if (seqLen & 1) {
        seqAlign = seqLen + 1;
    }
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        uvaSeqStop();
    }
    _uvMediaCopy(sAudioSequencesData, sAudioSeqFile->seqArray[seqId].offset,
                 (u32) seqAlign);
    alCSeqNew(&sAudioCurrentSequence, (u8 *) sAudioSequencesData);
    alSeqpSetBank(sAudioSeqPlayer, sAudioBank);
    alSeqpSetSeq(sAudioSeqPlayer, (ALSeq*)&sAudioCurrentSequence);
}

void uvaSeqPlay(void) {
    f32 vol;

    D_uvcmidi_rom_004011FC->func_uvaudiomgr_rom_004011D0(&vol);
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        uvaSeqStop();
    }
    alSeqpPlay(sAudioSeqPlayer);
    alSeqpSetVol(sAudioSeqPlayer, (s16) (s32) (vol * D_uvcmidi_rom_00401000));
}

void uvaSeqSetPosition(u32 pos) {
    ALCSeqMarker marker;

    alCSeqNewMarker(&sAudioCurrentSequence, &marker, pos);
    alCSeqSetLoc(&sAudioCurrentSequence, &marker);
}

void uvaSeqSetTempo(f32 arg0) {
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        alSeqpSetTempo(sAudioSeqPlayer, (s32) (D_uvcmidi_rom_00401008 / (f64) arg0));
    }
}

f32 uvaSeqGetTempo(void) {
    s32 temp_v0;

    temp_v0 = alCSPGetTempo((ALCSPlayer *) sAudioSeqPlayer);
    if (temp_v0 == 0) {
        return 0.0f;
    }
    return D_uvcmidi_rom_00401010 / (f32) temp_v0;
}

void uvaSeqGetTicks(void) {
    alCSeqGetTicks(&sAudioCurrentSequence);
}

void func_uvcmidi_rom_00400878(void) {
    s32 sp1C;

    sp1C = alCSeqGetTicks(&sAudioCurrentSequence);
    alCSeqTicksToSec(&sAudioCurrentSequence, sp1C,
                     alCSPGetTempo((ALCSPlayer *) sAudioSeqPlayer));
}

void uvaSeqGetState(void) {
    alSeqpGetState(sAudioSeqPlayer);
}

void uvaSeqSetVol(f32 vol) {
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        alSeqpSetVol(sAudioSeqPlayer, (s16) (s32) (vol * D_uvcmidi_rom_00401014));
    }
}

void uvaSeqStop(void) {
    alSeqpStop(sAudioSeqPlayer);
    uvClkReset(0x6A);
    while (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        if ((uvClkGetSec(0x6A) > 2.0)) {
            return;
        }
    }
}

f32 uvaGetChannelPriority(u8 chan) {
    return alSeqpGetChlPriority(sAudioSeqPlayer, chan);
}

void uvaSetChannelPriority(u8 chan, u8 priority) {
    alSeqpSetChlPriority(sAudioSeqPlayer, chan, priority);
}

void func_uvcmidi_rom_00400A38(u8 byte, u8 byte2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (byte + 0xB0), 0x10U, (u8) (s32) byte2);
}

f32 func_uvcmidi_rom_00400A84(u8 channel) {
    return alSeqpGetChlFXMix(sAudioSeqPlayer, channel);
}

void func_uvcmidi_rom_00400AC8(u8 channel, u8 mix) {
    alSeqpSetChlFXMix(sAudioSeqPlayer, channel, mix);
}

void func_uvcmidi_rom_00400AFC(u8 byte1, u8 byte2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (byte1 + 0xB0), 0x5BU, byte2);
}

f32 func_uvcmidi_rom_00400B48(u8 channel) {
    return alSeqpGetChlPan(sAudioSeqPlayer, channel);
}

void uvaSetChannelPan(u8 channel, s32 pan) {
    alSeqpSetChlPan(sAudioSeqPlayer, channel, pan);
}

void func_uvcmidi_rom_00400BC0(u8 status, s32 byte2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (status + 0xB0), 0xAU, byte2);
}

f32 func_uvcmidi_rom_00400C0C(u8 arg0) {
    return alSeqpGetChlProgram(sAudioSeqPlayer, arg0);
}

void func_uvcmidi_rom_00400C3C(u8 channel, s32 program) {
    alSeqpSetChlProgram(sAudioSeqPlayer, channel, program);
}

void func_uvcmidi_rom_00400C70(u8 arg0, s32 arg1) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (arg0 + 0xC0), arg1, 0U);
}

f32 uvaGetChannelVolume(u8 channel) {
    return alSeqpGetChlVol(sAudioSeqPlayer, channel);
}

void func_uvcmidi_rom_00400CFC(u8 channel, u8 volume) {
    alSeqpSetChlVol(sAudioSeqPlayer, channel, volume);
}

void func_uvcmidi_rom_00400D30(u8 arg0, u8 arg1) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (arg0 + 0xB0), 7U, arg1);
}

void func_uvcmidi_rom_00400D7C(u8 status, u8 byte1, u8 byte2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, status, byte1, byte2);
}

void func_uvcmidi_rom_00400DC0(u8 arg0, u8 arg1, u8 arg2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (arg0 + 0x90), arg1, arg2);
}

void func_uvcmidi_rom_00400E10(u8 arg0, u8 arg1, u8 arg2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (arg0 + 0x80), arg1, arg2);
}

void func_uvcmidi_rom_00400E60(u8 *arg0, s32 arg1, s32 *arg2) {
    ALVoiceState *node;
    s32 nodePos;

    node = sAudioSeqPlayer->vAllocHead;
    nodePos = 0;
    while ((node != NULL) && (node != sAudioSeqPlayer->vAllocTail)) {
        if (nodePos < arg1) {
            arg0[nodePos] = node->envPhase;
        }
        node = node->next;
        nodePos++;
    }

    *arg2 = nodePos;
}

ALVoiceState *uvaGetFreeVoiceList(void) {
    return sAudioSeqPlayer->vFreeList;
}

void uvaGetAllocatedVoiceList(ALVoiceState **head, ALVoiceState **tail) {
    *head = sAudioSeqPlayer->vAllocHead;
    *tail = sAudioSeqPlayer->vAllocTail;
}

s32 func_uvcmidi_rom_00400EF8(void) {
    return D_uvcmidi_rom_004011EC;
}

void func_uvcmidi_rom_00400F04(u8 *arg0) {
    ALVoiceState *tail;
    ALVoiceState *head;
    s32 i;

    ALVoiceState *v0 = D_uvcmidi_rom_004011EC;

    for (i = 0; i < sAudioSeqPlayerConfig.maxVoices; i++) {
        arg0[i] = 0xFF;
    }

    tail = sAudioSeqPlayer->vAllocTail;
    head = sAudioSeqPlayer->vAllocHead;
    while ((head != tail) && (head != NULL)) {
        i = ((u32) v0 - (u32) head) / 56U;
        i = ABS(i);
        if ((s32) i < sAudioSeqPlayerConfig.maxVoices) {
            arg0[i] = head->envPhase;
        }
        head = head->next;
    }
}

ALSeqPlayer *uvaGetSeqPlayer(void) {
    if (sAudioSeqPlayer != NULL) {
        return sAudioSeqPlayer;
    }
    return NULL;
}

s16 uvaGetSeqCount(void) {
    return sAudioSeqFile->seqCount;
}
