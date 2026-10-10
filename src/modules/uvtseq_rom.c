// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"
#include "stdarg.h"

typedef struct TextureSequence_s {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 used;
    /* 0x02 */ u8 curFrame;
    /* 0x03 */ char pad3[1];
    /* 0x04 */ f32 frameTime;
    /* 0x08 */ ParsedUVTS uvts;
} TextureSequence;

typedef struct TexSequenceSettings_s {
    s32 texSeqCount;
    s32 unk_4;
} TexSequenceSettings;

#define TEXTURE_SEQUENCE_POOL_COUNT_DEFAULT 20
#define UVTSEQ_MODE_REPEAT    0
#define UVTSEQ_MODE_ONESHOT   1
#define UVTSEQ_MODE_STROBE    2

extern TextureSequence *sTextureSequencePool;
extern UvGfxMgr_Exports *D_uvtseq_rom_00400A90;
extern UvCback_Exports *D_uvtseq_rom_00400A94;
extern s32 sTextureSequencesCount;
extern u8 sUpdateTexSequencesFlag;

void uvTexSeqDestroy(void);
void uvTexSeqModel(s32 arg0, s32 arg1);
void uvTexSeqProps(s32 arg0, ...);
s32 uvTexSeqFindFree(void);
void uvTexSeqFree(s32 arg0);
void uvTexSeqCallBack(s32 arg0);
void uvTexSeqUpdateAll(void);
void uvTexSeqUpdate(s32 arg0);
u16 uvTexSeqGetCurFrameTexture(s32 arg0);
u8 uvTexSeqGetFrameCount(s32 arg0);
u16 uvTexSeqGetFrameTexture(s32 arg0, s32 arg1);
u8 uvTexSeqGetActive(s32 arg0);
f32 uvTexSeqGetCurrentFrameProgress(s32 arg0);
void __entrypoint_func_uvtseq_rom_400000(UvTSeq_Exports *exports);

extern s32 D_uvtseq_rom_00400A88;

void __entrypoint_func_uvtseq_rom_400000(UvTSeq_Exports *exports) { /* Publish ten callbacks, choose nonzero settings or defaults 20 and 16, load GMGR and CBCK, allocate and clear the sequence pool, initialize its records, register the update callback and clear the update flag. */
    s32 sequenceIndex;
    TexSequenceSettings *sequenceSettings;

    uvUpdateFileAllocPtr(exports);
    exports->uvTexSeqDestroy = uvTexSeqDestroy;
    exports->uvTexSeqModel = uvTexSeqModel;
    exports->uvTexSeqProps = uvTexSeqProps;
    exports->uvTexSeqFindFree = uvTexSeqFindFree;
    exports->uvTexSeqFree = uvTexSeqFree;
    exports->uvTexSeqGetCurFrameTexture = uvTexSeqGetCurFrameTexture;
    exports->uvTexSeqGetFrameCount = uvTexSeqGetFrameCount;
    exports->uvTexSeqGetFrameTexture = uvTexSeqGetFrameTexture;
    exports->uvTexSeqGetActive = uvTexSeqGetActive;
    exports->uvTexSeqGetCurrentFrameProgress = uvTexSeqGetCurrentFrameProgress;
    sequenceSettings = uvGetSystemProp(SYSTEM_PROPID_TEX_SEQ_SETTINGS);
    if (sequenceSettings == NULL) {
        sTextureSequencesCount = TEXTURE_SEQUENCE_POOL_COUNT_DEFAULT;
        D_uvtseq_rom_00400A88 = 0x10;
    } else {
        if (sequenceSettings->texSeqCount != 0) {
            sTextureSequencesCount = sequenceSettings->texSeqCount;
        } else {
            sTextureSequencesCount = TEXTURE_SEQUENCE_POOL_COUNT_DEFAULT;
        }
        if (sequenceSettings->unk_4 != 0) {
            D_uvtseq_rom_00400A88 = sequenceSettings->unk_4;
        } else {
            D_uvtseq_rom_00400A88 = 0x10;
        }
    }
    D_uvtseq_rom_00400A90 = uvLoadModule('GMGR');
    D_uvtseq_rom_00400A94 = uvLoadModule('CBCK');
    sTextureSequencePool =
        _uvMemAllocAlign8(sTextureSequencesCount * sizeof(TextureSequence));
    uvMemSet(sTextureSequencePool, 0, sTextureSequencesCount * sizeof(TextureSequence));

    for (sequenceIndex = 0; sequenceIndex < sTextureSequencesCount; sequenceIndex++) {
        sTextureSequencePool[sequenceIndex].active = FALSE;
        sTextureSequencePool[sequenceIndex].used = 0;
        sTextureSequencePool[sequenceIndex].curFrame = 0;
        sTextureSequencePool[sequenceIndex].frameTime = 0.0f;
        sTextureSequencePool[sequenceIndex].uvts.frameCount = 0;
        sTextureSequencePool[sequenceIndex].uvts.frameTable = NULL;
        sTextureSequencePool[sequenceIndex].uvts.mode = 1;
        sTextureSequencePool[sequenceIndex].uvts.reverse = 0;
        sTextureSequencePool[sequenceIndex].uvts.frameRate = 1.0f;
    }

    D_uvtseq_rom_00400A94->uvAddCallback(
        D_uvtseq_rom_00400A90->uvGfxGetCallbackList(1), (s32) uvTexSeqCallBack, 0, 0);
    sUpdateTexSequencesFlag = 0;
/* RE_UNKNOWN: Allocation failure, settings limits and repeated initialization are unproved. Preserve both setting defaults, the pool-pointer rereads and live count reads during record initialization. */ }

void uvTexSeqDestroy(void) {


    s32 sequenceIndex;

    D_uvtseq_rom_00400A94->uvRemoveCallback(
        D_uvtseq_rom_00400A90->uvGfxGetCallbackList(1), (s32) uvTexSeqCallBack);

    for (sequenceIndex = 0; sequenceIndex < sTextureSequencesCount; sequenceIndex++) {
        _uvMemFree(sTextureSequencePool[sequenceIndex].uvts.frameTable);
    }

    _uvMemFree(sTextureSequencePool);
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('MATH');
    uvUnloadModule('MODL');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
}

void uvTexSeqModel(s32 sequenceIndex, s32 sequenceFileId) { /* File ID 255 only disables the selected sequence. Otherwise try the loaded file before loading it, set the direction-dependent current frame, copy its duration only for a nonzero frame count, then copy the 16-byte parsed sequence record. */
    TextureSequence *sequence;
    ParsedUVTS *loadedSequence;

    sequence = &sTextureSequencePool[sequenceIndex];
    if (sequenceFileId == 0xFF) {
        sequence->active = FALSE;
        return;
    }
    loadedSequence = uvGetLoadedFile('UVTS', sequenceFileId);
    if ((loadedSequence != NULL) || (((loadedSequence = uvLoadFile('UVTS', sequenceFileId)) != NULL))) {
        sequence->active = TRUE;

        if (loadedSequence->reverse == 1) {
            sequence->curFrame = loadedSequence->frameCount - 1;
        } else {
            sequence->curFrame = 0;
        }

        if (loadedSequence->frameCount != 0) {
            sequence->frameTime = loadedSequence->frameTable[sequence->curFrame].frameTime;
        }

        _uvMediaCopy(&sequence->uvts, loadedSequence, sizeof(ParsedUVTS));
    }
/* RE_UNKNOWN: Sequence and file ID bounds, failed-load state, frame-table ownership and zero frame counts are unproved. The copied frame-table pointer is shared; no deep copy or additional reset is performed. */ }

void uvTexSeqProps(s32 sequenceIndex, ...) { /* Consume tagged values for active state, current frame, mode, reverse, rate and the global update flag until the end tag. The frame case reuses the selector word as the index; setting reverse always selects frameCount minus one. */
    ParsedUVTS *sequenceData;
    TextureSequence *sequence;
    int propertyOrFrameIndex;
    va_list arguments;

    sequence = &sTextureSequencePool[sequenceIndex];
    sequenceData = &sequence->uvts;
    if (sequence == NULL) {
        return;
    }
    va_start(arguments, sequenceIndex);
    if (sequenceData == NULL) {
        return;
    }

    while (TRUE) {
        propertyOrFrameIndex = va_arg(arguments, s32);
        switch (propertyOrFrameIndex) {
            case TSEQ_PROPID_ACTIVE:
                sequence->active = va_arg(arguments, s32);
                break;
            case TSEQ_PROPID_CURR_FRAME:
                propertyOrFrameIndex = va_arg(arguments, s32);
                if (propertyOrFrameIndex < sequenceData->frameCount) {
                    sequence->curFrame = propertyOrFrameIndex;
                }
                break;
            case TSEQ_PROPID_MODE:
                sequenceData->mode = va_arg(arguments, s32);
                break;
            case TSEQ_PROPID_REVERSE:
                sequenceData->reverse = va_arg(arguments, s32);
                sequence->curFrame = sequenceData->frameCount - 1;
                break;
            case TSEQ_PROPID_FRAMERATE:
                sequenceData->frameRate = va_arg(arguments, f64);
                break;
            case TSEQ_PROPID_UPDATE:
                sUpdateTexSequencesFlag = va_arg(arguments, s32);
                break;
            case TSEQ_PROPID_END:
                return;
        }
    }
/* RE_UNKNOWN: Index and vararg domains remain unproved. Preserve the signed upper-bound-only frame check, double rate argument, byte truncations, existing null tests and continued scanning after unsupported tags. */ }

s32 uvTexSeqFindFree(void) { /* Scan the captured count for the first unused sequence, mark it used and active, and return its index; return 255 if none is found. No frame or parsed-data fields are reset. */
    s32 sequenceIndex;

    for (sequenceIndex = 0; sequenceIndex < sTextureSequencesCount; sequenceIndex++) {
        if (!sTextureSequencePool[sequenceIndex].used) {
            sTextureSequencePool[sequenceIndex].used = TRUE;
            sTextureSequencePool[sequenceIndex].active = TRUE;
            return sequenceIndex;
        }
    }
    return 0xFF;
/* RE_UNKNOWN: Pool validity and the configured count domain are unproved. Preserve the separate pool-pointer read before marking the selected sequence active. */ }

void uvTexSeqFree(s32 sequenceIndex) { /* For a nonnegative index below the current count, clear active and used; leave all parsed data and frame state untouched. */
    if ((sequenceIndex >= 0) && (sequenceIndex < sTextureSequencesCount)) {
        sTextureSequencePool[sequenceIndex].active = FALSE;
        sTextureSequencePool[sequenceIndex].used = FALSE;
    }
/* RE_UNKNOWN: External ownership of the parsed frame table and reuse/reset ordering remain unproved. */ }

void uvTexSeqCallBack(s32 callbackArgument) { /* Call the sequence update-all routine without inspecting the callback argument. */
    uvTexSeqUpdateAll();
/* RE_UNKNOWN: The historical callback argument contract is unproved. Preserve the current formal type and unconditional call. */ }

void uvTexSeqUpdateAll(void) { /* Skip updates only when the global flag equals 1; otherwise visit active sequences. Reload the count after each update call and read the current pool pointer for the next sequence. */
    s32 sequenceIndex;

    if (sUpdateTexSequencesFlag == 1) {
        return;
    }

    for (sequenceIndex = 0; sequenceIndex < sTextureSequencesCount; sequenceIndex++) {
        if (sTextureSequencePool[sequenceIndex].active) {
            uvTexSeqUpdate(sequenceIndex);
        }
    }
/* RE_UNKNOWN: Mutation of the pool, count or active fields during an update is unproved. Preserve the count reloads and exact flag equality gate. */ }

void uvTexSeqUpdate(s32 sequenceIndex) { /* Subtract the frame rate times the GMGR scalar result. For expired frames, numeric mode 1 wraps by signed remainder, mode 0 may deactivate playback, and mode 2 changes direction; then add the selected frame duration and repeat while time remains nonpositive. */
    TextureSequence *sequence;
    ParsedUVTS *sequenceData;

    sequence = &sTextureSequencePool[sequenceIndex];
    sequenceData = &sequence->uvts;
    sequence->frameTime -= sequenceData->frameRate * D_uvtseq_rom_00400A90->uvGfxMgrGetScalarOverrideOrCurrent();

    if (!(sequence->frameTime > 0.0f) && (sequence->frameTime <= 0.0f)) {
        while (TRUE) {
            switch (sequenceData->mode) { /* irregular */
                case UVTSEQ_MODE_ONESHOT:
                    if (sequenceData->reverse == 0) {
                        sequence->curFrame = ((sequence->curFrame + 1) % sequenceData->frameCount);
                    } else {
                        sequence->curFrame =
                            (u8) ((s32) ((sequence->curFrame + sequenceData->frameCount) - 1) % (s32) sequenceData->frameCount);
                    }
                    break;
                case UVTSEQ_MODE_REPEAT:
                    if (sequenceData->reverse == 0) {
                        sequence->curFrame++;
                        if ((sequence->curFrame + 1) == sequenceData->frameCount) {
                            sequence->active = 0;
                            return;
                        }
                    } else {
                        if (sequence->curFrame == 0) {
                            sequence->active = 0;
                            return;
                        }
                        sequence->curFrame--;
                    }
                    break;
                case UVTSEQ_MODE_STROBE:
                    if (sequenceData->reverse == 0) {
                        sequence->curFrame++;
                        if ((sequence->curFrame + 1) == sequenceData->frameCount) {
                            sequenceData->reverse = 1;
                        }
                    } else {
                        sequence->curFrame--;
                        if (sequence->curFrame == 0) {
                            sequenceData->reverse = 0;
                        }
                    }
                    break;
            }

            sequence->frameTime += sequenceData->frameTable[sequence->curFrame].frameTime;
            if (!(sequence->frameTime <= 0.0f)) {
                return;
            }
        }
    }
/* RE_UNKNOWN: Historical mode intent, valid sequence/frame bounds and termination with zero or negative durations are unproved. Keep the inherited mode labels, byte wrapping, off-by-one tests, modulo traps and ordered floating-point tests, including NaN behavior. */ }

u16 uvTexSeqGetCurFrameTexture(s32 sequenceIndex) { /* Return the texture halfword from the selected sequence current frame. */
    TextureSequence *sequence;

    sequence = &sTextureSequencePool[sequenceIndex];
    return sequence->uvts.frameTable[sequence->curFrame].texture;
/* RE_UNKNOWN: Sequence index, current frame and frame-table validity are unchecked; their caller guarantees are unproved. */ }

u8 uvTexSeqGetFrameCount(s32 sequenceIndex) { /* Return the selected sequence frame-count byte. */
    TextureSequence *sequence;

    sequence = &sTextureSequencePool[sequenceIndex];
    return sequence->uvts.frameCount;
/* RE_UNKNOWN: Sequence-index and pool validity are unproved; retain the unchecked access and byte result. */ }

u16 uvTexSeqGetFrameTexture(s32 sequenceIndex, s32 frameOffsetOrIndex) { /* Add the requested frame offset to the current frame, take signed remainder by the frame count and return that frame texture. */
    TextureSequence *sequence;

    sequence = &sTextureSequencePool[sequenceIndex];
    frameOffsetOrIndex = (s32) (sequence->curFrame + frameOffsetOrIndex) % (s32) sequence->uvts.frameCount;
    return sequence->uvts.frameTable[frameOffsetOrIndex].texture;
/* RE_UNKNOWN: Negative offsets, zero frame counts and resulting frame-table bounds are unproved. Preserve signed remainder and the lack of a normalization or validity gate. */ }

u8 uvTexSeqGetActive(s32 sequenceIndex) { /* Return the selected sequence active byte without consulting its used flag. */
    TextureSequence *sequence;

    sequence = &sTextureSequencePool[sequenceIndex];
    return sequence->active;
/* RE_UNKNOWN: Sequence-index and pool validity remain unproved; do not add a used-state gate. */ }

#line 322 "src/modules/uvtseq_rom.c"
/* Return elapsed time divided by the current texture-frame duration.
 * Preserve the original unchecked sequence index and zero-duration
 * behavior; this accessor does not advance the sequence. */
f32 uvTexSeqGetCurrentFrameProgress(s32 sequenceId) {
    TextureSequence *sequence;

    sequence = &sTextureSequencePool[sequenceId];
    return sequence->frameTime / sequence->uvts.frameTable[sequence->curFrame].frameTime;
}
#line 328 "src/modules/uvtseq_rom.c"
