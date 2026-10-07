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
void uvaVisitSequenceElapsedSeconds(void);
void uvaSeqGetState(void);
void uvaSeqSetVol(f32 arg0);
void uvaSeqStop(void);
void uvaSeqStop(void);
f32 uvaGetChannelPriority(u8 chan);
void uvaSetChannelPriority(u8 chan, u8 priority);
void uvaSendChannelController10(u8 byte, u8 byte2);
f32 uvaGetChannelEffectsMix(u8 channel);
void uvaSetChannelEffectsMix(u8 channel, u8 mix);
void uvaSendChannelEffectsMix(u8 byte1, u8 byte2);
f32 uvaGetChannelPan(u8 channel);
void uvaSetChannelPan(u8 channel, s32 pan);
void uvaSendChannelPan(u8 status, s32 byte2);
f32 uvaGetChannelProgram(u8 arg0);
void uvaSetChannelProgram(u8 channel, s32 program);
void uvaSendChannelProgram(u8 arg0, s32 arg1);
f32 uvaGetChannelVolume(u8 channel);
void uvaSetChannelVolume(u8 channel, u8 volume);
void uvaSendChannelVolume(u8 arg0, u8 arg1);
void uvaSendMidiMessage(u8 status, u8 byte1, u8 byte2);
void uvaSendNoteOn(u8 arg0, u8 arg1, u8 arg2);
void uvaSendNoteOff(u8 arg0, u8 arg1, u8 arg2);
void uvaCollectAllocatedVoicePhases(u8 *arg0, s32 arg1, s32 *arg2);
ALVoiceState *uvaGetFreeVoiceList(void);
void uvaGetAllocatedVoiceList(ALVoiceState **arg0, ALVoiceState **arg1);
s32 uvaGetInitialVoicePoolAddress(void);
void uvaCollectVoicePoolPhases(u8 *arg0);
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
    exports->uvaVisitSequenceElapsedSeconds = uvaVisitSequenceElapsedSeconds;
    exports->uvaSeqGetState = uvaSeqGetState;
    exports->uvaCleanup = uvaCleanup;
    exports->uvaSeqSetVol = uvaSeqSetVol;
    exports->uvaSendChannelPan = uvaSendChannelPan;
    exports->uvaSeqStop = uvaSeqStop;
    exports->uvaCollectAllocatedVoicePhases = uvaCollectAllocatedVoicePhases;
    exports->uvaGetChannelProgram = uvaGetChannelProgram;
    exports->uvaGetChannelPriority = uvaGetChannelPriority;
    exports->uvaGetFreeVoiceList = uvaGetFreeVoiceList;
    exports->uvaSetChannelProgram = uvaSetChannelProgram;
    exports->uvaSetChannelPriority = uvaSetChannelPriority;
    exports->uvaGetAllocatedVoiceList = uvaGetAllocatedVoiceList;
    exports->uvaSendChannelProgram = uvaSendChannelProgram;
    exports->uvaSendChannelController10 = uvaSendChannelController10;
    exports->uvaGetInitialVoicePoolAddress = uvaGetInitialVoicePoolAddress;
    exports->uvaGetChannelVolume = uvaGetChannelVolume;
    exports->uvaGetChannelEffectsMix = uvaGetChannelEffectsMix;
    exports->uvaCollectVoicePoolPhases = uvaCollectVoicePoolPhases;
    exports->uvaSetChannelVolume = uvaSetChannelVolume;
    exports->uvaSetChannelEffectsMix = uvaSetChannelEffectsMix;
    exports->uvaGetSeqPlayer = uvaGetSeqPlayer;
    exports->uvaSendChannelVolume = uvaSendChannelVolume;
    exports->uvaSendChannelEffectsMix = uvaSendChannelEffectsMix;
    exports->uvaGetSeqCount = uvaGetSeqCount;
    exports->uvaSendMidiMessage = uvaSendMidiMessage;
    exports->uvaGetChannelPan = uvaGetChannelPan;
    exports->uvaSendNoteOn = uvaSendNoteOn;
    exports->uvaSetChannelPan = uvaSetChannelPan;
    exports->uvaSendNoteOff = uvaSendNoteOff;
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

    D_uvcmidi_rom_004011FC->uvAudioMgrGetSequenceVolume(&vol);
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

#line 275 "src/modules/uvcmidi_rom.c"
/* Convert the current compressed-sequence tick position to seconds using
 * its current tempo. Preserve the original discarded conversion result. */
void uvaVisitSequenceElapsedSeconds(void) {
    s32 ticks;

    ticks = alCSeqGetTicks(&sAudioCurrentSequence);
    alCSeqTicksToSec(&sAudioCurrentSequence, ticks,
                     alCSPGetTempo((ALCSPlayer *) sAudioSeqPlayer));
}
#line 282 "src/modules/uvcmidi_rom.c"

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

#line 311 "src/modules/uvcmidi_rom.c"
/* Send immediate MIDI control change 0x10 on the supplied channel.
 * Retain the original byte narrowing and caller-owned channel bounds. */
void uvaSendChannelController10(u8 channel, u8 value) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0xB0), 0x10U, (u8) (s32) value);
}
#line 314 "src/modules/uvcmidi_rom.c"

#line 315 "src/modules/uvcmidi_rom.c"
/* Return the sequence channel effects-mix value through the original float ABI. */
f32 uvaGetChannelEffectsMix(u8 channel) {
    return alSeqpGetChlFXMix(sAudioSeqPlayer, channel);
}
#line 318 "src/modules/uvcmidi_rom.c"

#line 319 "src/modules/uvcmidi_rom.c"
/* Set the sequence channel effects mix through the player API. */
void uvaSetChannelEffectsMix(u8 channel, u8 mix) {
    alSeqpSetChlFXMix(sAudioSeqPlayer, channel, mix);
}
#line 322 "src/modules/uvcmidi_rom.c"

#line 323 "src/modules/uvcmidi_rom.c"
/* Send immediate MIDI control change 0x5B on the supplied channel. */
void uvaSendChannelEffectsMix(u8 channel, u8 mix) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0xB0), 0x5BU, mix);
}
#line 326 "src/modules/uvcmidi_rom.c"

#line 327 "src/modules/uvcmidi_rom.c"
/* Return the sequence channel pan through the original float ABI. */
f32 uvaGetChannelPan(u8 channel) {
    return alSeqpGetChlPan(sAudioSeqPlayer, channel);
}
#line 330 "src/modules/uvcmidi_rom.c"

void uvaSetChannelPan(u8 channel, s32 pan) {
    alSeqpSetChlPan(sAudioSeqPlayer, channel, pan);
}

#line 335 "src/modules/uvcmidi_rom.c"
/* Send immediate MIDI control change 0x0A on the supplied channel. */
void uvaSendChannelPan(u8 channel, s32 pan) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0xB0), 0xAU, pan);
}
#line 338 "src/modules/uvcmidi_rom.c"

#line 339 "src/modules/uvcmidi_rom.c"
/* Return the sequence channel program through the original float ABI. */
f32 uvaGetChannelProgram(u8 channel) {
    return alSeqpGetChlProgram(sAudioSeqPlayer, channel);
}
#line 342 "src/modules/uvcmidi_rom.c"

#line 343 "src/modules/uvcmidi_rom.c"
/* Set the sequence channel program through the player API. */
void uvaSetChannelProgram(u8 channel, s32 program) {
    alSeqpSetChlProgram(sAudioSeqPlayer, channel, program);
}
#line 346 "src/modules/uvcmidi_rom.c"

#line 347 "src/modules/uvcmidi_rom.c"
/* Send an immediate MIDI program-change message. */
void uvaSendChannelProgram(u8 channel, s32 program) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0xC0), program, 0U);
}
#line 350 "src/modules/uvcmidi_rom.c"

f32 uvaGetChannelVolume(u8 channel) {
    return alSeqpGetChlVol(sAudioSeqPlayer, channel);
}

#line 355 "src/modules/uvcmidi_rom.c"
/* Set the sequence channel volume through the player API. */
void uvaSetChannelVolume(u8 channel, u8 volume) {
    alSeqpSetChlVol(sAudioSeqPlayer, channel, volume);
}
#line 358 "src/modules/uvcmidi_rom.c"

#line 359 "src/modules/uvcmidi_rom.c"
/* Send immediate MIDI control change seven on the supplied channel. */
void uvaSendChannelVolume(u8 channel, u8 volume) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0xB0), 7U, volume);
}
#line 362 "src/modules/uvcmidi_rom.c"

#line 363 "src/modules/uvcmidi_rom.c"
/* Send the supplied MIDI status and two data bytes with zero delay. */
void uvaSendMidiMessage(u8 status, u8 byte1, u8 byte2) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, status, byte1, byte2);
}
#line 366 "src/modules/uvcmidi_rom.c"

#line 367 "src/modules/uvcmidi_rom.c"
/* Send an immediate MIDI note-on message. */
void uvaSendNoteOn(u8 channel, u8 key, u8 velocity) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0x90), key, velocity);
}
#line 370 "src/modules/uvcmidi_rom.c"

#line 371 "src/modules/uvcmidi_rom.c"
/* Send an immediate MIDI note-off message. */
void uvaSendNoteOff(u8 channel, u8 key, u8 velocity) {
    alSeqpSendMidi(sAudioSeqPlayer, 0, (channel + 0x80), key, velocity);
}
#line 374 "src/modules/uvcmidi_rom.c"

#line 375 "src/modules/uvcmidi_rom.c"
/* Copy at most capacity allocated voice envelope phases and report the full
 * visited count. Preserve the original exclusive allocated-tail sentinel. */
void uvaCollectAllocatedVoicePhases(u8 *phases, s32 capacity, s32 *count) {
    ALVoiceState *node;
    s32 voiceIndex;

    node = sAudioSeqPlayer->vAllocHead;
    voiceIndex = 0;
    while ((node != NULL) && (node != sAudioSeqPlayer->vAllocTail)) {
        if (voiceIndex < capacity) {
            phases[voiceIndex] = node->envPhase;
        }
        node = node->next;
        voiceIndex++;
    }

    *count = voiceIndex;
}
#line 391 "src/modules/uvcmidi_rom.c"

ALVoiceState *uvaGetFreeVoiceList(void) {
    return sAudioSeqPlayer->vFreeList;
}

void uvaGetAllocatedVoiceList(ALVoiceState **head, ALVoiceState **tail) {
    *head = sAudioSeqPlayer->vAllocHead;
    *tail = sAudioSeqPlayer->vAllocTail;
}

#line 401 "src/modules/uvcmidi_rom.c"
/* Return the initial free-voice-list address through the original word ABI. */
s32 uvaGetInitialVoicePoolAddress(void) {
    return D_uvcmidi_rom_004011EC;
}
#line 404 "src/modules/uvcmidi_rom.c"

#line 405 "src/modules/uvcmidi_rom.c"
/* Initialize one phase byte per configured voice to 255, then fill allocated
 * phases by the original unsigned pointer-distance calculation. Tail is exclusive. */
void uvaCollectVoicePoolPhases(u8 *phases) {
    ALVoiceState *tail;
    ALVoiceState *head;
    s32 voiceIndex;

    ALVoiceState *voicePoolBase = D_uvcmidi_rom_004011EC;

    for (voiceIndex = 0; voiceIndex < sAudioSeqPlayerConfig.maxVoices; voiceIndex++) {
        phases[voiceIndex] = 0xFF;
    }

    tail = sAudioSeqPlayer->vAllocTail;
    head = sAudioSeqPlayer->vAllocHead;
    while ((head != tail) && (head != NULL)) {
        voiceIndex = ((u32) voicePoolBase - (u32) head) / 56U;
        voiceIndex = ABS(voiceIndex);
        if ((s32) voiceIndex < sAudioSeqPlayerConfig.maxVoices) {
            phases[voiceIndex] = head->envPhase;
        }
        head = head->next;
    }
}
#line 427 "src/modules/uvcmidi_rom.c"

ALSeqPlayer *uvaGetSeqPlayer(void) {
    if (sAudioSeqPlayer != NULL) {
        return sAudioSeqPlayer;
    }
    return NULL;
}

s16 uvaGetSeqCount(void) {
    return sAudioSeqFile->seqCount;
}
