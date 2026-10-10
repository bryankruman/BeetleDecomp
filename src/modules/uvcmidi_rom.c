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

void __entrypoint_func_uvcmidi_rom_400000(UvCMidi_Exports *exports) { /* Publish 37 callbacks, read property 3 and choose nonzero limits or defaults 16, 256 and 16. Establish and clear heap storage, initialize the heap and player, save the initial free-list pointer and load AMGR. */
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
/* RE_UNKNOWN: Settings layout and limits, player storage, failed allocation and repeated initialization remain unproved. Preserve the inherited player-allocation warning, ownership flags and all reads and stores. */ }

// Module cleanup
void uvaCleanup(void) { /* Call the stop wrapper when the state result is nonzero, delete the player, free the heap buffer for flag bit 1 and three bank or sequence buffers for bit 2, then unload AMGR. */
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
/* RE_UNKNOWN: Ownership and repeated teardown are unproved. Preserve the flag reread after the first free; this body clears no global pointer or flag. */ }

void uvaLoadBank(s32 bankId) { /* Read UVMB control and table blocks, copy the control block and install its bank. Read UVMS file 0, copy the signed-count sequence table, scan its lengths and allocate scratch space rounded up to an even byte count. */
    void *controlData;
    void *tableBlockData;
    u32 controlBytes;
    s32 fileHandle;
    ALSeqFile sequenceFileHeader;
    s32 sequenceTableBytes;
    s32 maximumSequenceBytes;
    s32 sequenceCountOrIndex;
    void *sequenceBlockData;

    fileHandle = uvFileReadHeader(uvGetFileData('UVMB', bankId));
    uvFileSearchTag(fileHandle, &controlBytes, &controlData, '.CTL', 0);
    uvFileSearchTag(fileHandle, NULL, &tableBlockData, '.TBL', 0);
    uvFileFree(fileHandle);
    D_uvcmidi_rom_004011F8 |= 2;
    sAudioBankFile = malloc16(controlBytes);
    _uvMediaCopy(sAudioBankFile, controlData, controlBytes);
    alBnkfNew(sAudioBankFile, (u8 *) tableBlockData);
    sAudioBank = sAudioBankFile->bankArray[0];
    alSeqpSetBank(sAudioSeqPlayer, sAudioBank);
    fileHandle = uvFileReadHeader(uvGetFileData('UVMS', 0));
    uvFileSearchTag(fileHandle, NULL, &sequenceBlockData, 'SEQS', 0);
    uvFileFree(fileHandle);
    _uvMediaCopy(&sequenceFileHeader, sequenceBlockData, 4);
    sequenceCountOrIndex = sequenceFileHeader.seqCount;
    sequenceTableBytes = (sequenceCountOrIndex * 8) + 4;
    sAudioSeqFile = malloc16(sequenceTableBytes);
    _uvMediaCopy(sAudioSeqFile, sequenceBlockData, sequenceTableBytes);
    alSeqFileNew(sAudioSeqFile, (u8 *) sequenceBlockData);
    maximumSequenceBytes = 0;
    for (sequenceCountOrIndex = 0; sequenceCountOrIndex < sAudioSeqFile->seqCount; sequenceCountOrIndex++) {
        if (sAudioSeqFile->seqArray[sequenceCountOrIndex].len >= maximumSequenceBytes) {
            maximumSequenceBytes = sAudioSeqFile->seqArray[sequenceCountOrIndex].len;
        }
    }

    if (maximumSequenceBytes & 1) {
        maximumSequenceBytes += 1;
    }
    sAudioSequencesData = malloc16((u32) maximumSequenceBytes);
/* RE_UNKNOWN: Missing blocks, signed counts and lengths, allocation failures and replacement ownership are unproved. Keep both file-release points, the table pointer argument, signed scan and even-byte rounding; no bounds or failure checks are added. */ }

void uvaSetSeq(s32 sequenceIndex) { /* Capture the selected length and round it to an even byte count before querying state. Stop on a nonzero state, copy from the freshly read sequence table, then initialize the compressed sequence and install its bank and sequence. */
    s32 sequenceBytes;
    s32 alignedSequenceBytes;

    sequenceBytes = sAudioSeqFile->seqArray[sequenceIndex].len;
    alignedSequenceBytes = sequenceBytes;
    if (sequenceBytes & 1) {
        alignedSequenceBytes = sequenceBytes + 1;
    }
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        uvaSeqStop();
    }
    _uvMediaCopy(sAudioSequencesData, sAudioSeqFile->seqArray[sequenceIndex].offset,
                 (u32) alignedSequenceBytes);
    alCSeqNew(&sAudioCurrentSequence, (u8 *) sAudioSequencesData);
    alSeqpSetBank(sAudioSeqPlayer, sAudioBank);
    alSeqpSetSeq(sAudioSeqPlayer, (ALSeq*)&sAudioCurrentSequence);
/* RE_UNKNOWN: Index, scratch capacity and the extra source byte for odd lengths are unproved. Preserve the captured length across stop and the later table and source-pointer reads. */ }

void uvaSeqPlay(void) { /* Call AMGR slot 0x20 with a float output address, stop on a nonzero state and invoke playback. Then scale the output by the existing constant and convert through signed word and halfword for the volume setter. */
    f32 volumeOutput;

    D_uvcmidi_rom_004011FC->uvAudioMgrGetSequenceVolume(&volumeOutput);
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        uvaSeqStop();
    }
    alSeqpPlay(sAudioSeqPlayer);
    alSeqpSetVol(sAudioSeqPlayer, (s16) (s32) (volumeOutput * D_uvcmidi_rom_00401000));
/* RE_UNKNOWN: Callback output initialization, volume range and player lifetime are unproved. Preserve the callback before state sampling and the conversion sequence. */ }

void uvaSeqSetPosition(u32 sequencePosition) { /* Create a marker for the supplied sequence position, then pass the same local marker to the location setter. */
    ALCSeqMarker positionMarker;

    alCSeqNewMarker(&sAudioCurrentSequence, &positionMarker, sequencePosition);
    alCSeqSetLoc(&sAudioCurrentSequence, &positionMarker);
/* RE_UNKNOWN: Position units, stream bounds and marker validity are unproved. Preserve the unsigned input, real local storage and call order. */ }

void uvaSeqSetTempo(f32 tempoInput) { /* Only for a nonzero state result, divide the existing double constant by the promoted float input and truncate the quotient to a signed word for the tempo setter. */
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        alSeqpSetTempo(sAudioSeqPlayer, (s32) (D_uvcmidi_rom_00401008 / (f64) tempoInput));
    }
/* RE_UNKNOWN: Input units, zero, negative or nonfinite values and conversion range are unproved. Preserve the state gate and double-precision arithmetic. */ }

f32 uvaSeqGetTempo(void) { /* Return zero for a zero integer tempo result; otherwise divide the existing float constant by the signed-word result converted to float. */
    s32 playerTempo;

    playerTempo = alCSPGetTempo((ALCSPlayer *) sAudioSeqPlayer);
    if (playerTempo == 0) {
        return 0.0f;
    }
    return D_uvcmidi_rom_00401010 / (f32) playerTempo;
/* RE_UNKNOWN: Constant units and player validity are unproved. Preserve the explicit zero gate and single-precision division. */ }

void uvaSeqGetTicks(void) { /* Call the compressed-sequence tick query through the current void wrapper. */
    alCSeqGetTicks(&sAudioCurrentSequence);
/* RE_UNKNOWN: Native V0 is not overwritten after the call. Historical return ABI and caller use remain unproved; the current void interface is retained. */ }

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

void uvaSeqGetState(void) { /* Call the current player state query through the current void wrapper. */
    alSeqpGetState(sAudioSeqPlayer);
/* RE_UNKNOWN: Native V0 is not overwritten after the call. Historical return ABI and caller use remain unproved; the current void interface is retained. */ }

void uvaSeqSetVol(f32 volume) { /* Only for a nonzero state result, multiply the input by the existing float constant and convert through signed word and halfword for the volume setter. */
    if (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        alSeqpSetVol(sAudioSeqPlayer, (s16) (s32) (volume * D_uvcmidi_rom_00401014));
    }
/* RE_UNKNOWN: Input range, scale units and exceptional conversion behavior are unproved. Preserve the state gate, player reread and both conversions. */ }

void uvaSeqStop(void) { /* Request stop, reset clock 106 and poll state. Return when the state becomes zero or the clock result is strictly greater than 2.0. */
    alSeqpStop(sAudioSeqPlayer);
    uvClkReset(0x6A);
    while (alSeqpGetState(sAudioSeqPlayer) != AL_STOPPED) {
        if ((uvClkGetSec(0x6A) > 2.0)) {
            return;
        }
    }
/* RE_UNKNOWN: Clock units, asynchronous completion and termination guarantees are unproved. Preserve the state and clock call order and ordered double comparison. */ }

f32 uvaGetChannelPriority(u8 channel) { /* Pass the channel byte to the priority query and convert its returned unsigned word to float. */
    return alSeqpGetChlPriority(sAudioSeqPlayer, channel);
/* RE_UNKNOWN: Valid channel and result domains are unproved. Preserve the native unsigned-word conversion and current float return interface. */ }

void uvaSetChannelPriority(u8 channel, u8 priority) { /* Pass the channel and priority bytes to the current player priority setter. */
    alSeqpSetChlPriority(sAudioSeqPlayer, channel, priority);
/* RE_UNKNOWN: Valid channel and priority domains and player lifetime are unproved; retain both byte arguments and the call. */ }

#line 311 "src/modules/uvcmidi_rom.c"
/* Send immediate MIDI control change 0x10 on the supplied channel. RE_UNKNOWN:
 * permitted channel domain needs the original MIDI consumer/callers; preserve byte narrowing. */
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

void uvaSetChannelPan(u8 channel, s32 pan) { /* Pass the channel byte and low byte of the signed pan argument to the current player pan setter. */
    alSeqpSetChlPan(sAudioSeqPlayer, channel, pan);
/* RE_UNKNOWN: Permitted channel and pan domains are unproved. Preserve the current signed formal type and native narrowing at the call boundary. */ }

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

f32 uvaGetChannelVolume(u8 channel) { /* Pass the channel byte to the volume query and convert its returned unsigned word to float. */
    return alSeqpGetChlVol(sAudioSeqPlayer, channel);
/* RE_UNKNOWN: Valid channel and result domains are unproved. Preserve the native unsigned-word conversion and current float return interface. */ }

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

ALVoiceState *uvaGetFreeVoiceList(void) { /* Return the pointer read from the current player free-list field at offset 0x6C. */
    return sAudioSeqPlayer->vFreeList;
/* RE_UNKNOWN: Player validity and list ownership are unproved; no traversal, allocation or snapshot is added. */ }

void uvaGetAllocatedVoiceList(ALVoiceState **head, ALVoiceState **tail) { /* Write the allocated-list head to the first output, read the player pointer again, then write the tail to the second output. */
    *head = sAudioSeqPlayer->vAllocHead;
    *tail = sAudioSeqPlayer->vAllocTail;
/* RE_UNKNOWN: Output aliasing and player or list mutation are unproved. Preserve the two player reads and ordered output stores. */ }

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

ALSeqPlayer *uvaGetSeqPlayer(void) { /* Return the captured current player pointer through the existing explicit null branch. */
    if (sAudioSeqPlayer != NULL) {
        return sAudioSeqPlayer;
    }
    return NULL;
/* RE_UNKNOWN: Player allocation and lifetime are unproved; preserve the branch and pointer result. */ }

s16 uvaGetSeqCount(void) { /* Return the sequence-file count with the native signed-halfword load. */
    return sAudioSeqFile->seqCount;
/* RE_UNKNOWN: Sequence-file validity and count domain are unproved. The 16-byte function ends before a separate four-byte unassigned zero tail; its historical alignment purpose is unknown. */ }
