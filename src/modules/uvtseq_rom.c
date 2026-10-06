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
f32 func_uvtseq_rom_00400A10(s32 arg0);
void __entrypoint_func_uvtseq_rom_400000(UvTSeq_Exports *exports);

extern s32 D_uvtseq_rom_00400A88;

void __entrypoint_func_uvtseq_rom_400000(UvTSeq_Exports *exports) {
    s32 i;
    TexSequenceSettings *settings;

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
    exports->func_uvtseq_rom_00400A10 = func_uvtseq_rom_00400A10;
    settings = uvGetSystemProp(SYSTEM_PROPID_TEX_SEQ_SETTINGS);
    if (settings == NULL) {
        sTextureSequencesCount = TEXTURE_SEQUENCE_POOL_COUNT_DEFAULT;
        D_uvtseq_rom_00400A88 = 0x10;
    } else {
        if (settings->texSeqCount != 0) {
            sTextureSequencesCount = settings->texSeqCount;
        } else {
            sTextureSequencesCount = TEXTURE_SEQUENCE_POOL_COUNT_DEFAULT;
        }
        if (settings->unk_4 != 0) {
            D_uvtseq_rom_00400A88 = settings->unk_4;
        } else {
            D_uvtseq_rom_00400A88 = 0x10;
        }
    }
    D_uvtseq_rom_00400A90 = uvLoadModule('GMGR');
    D_uvtseq_rom_00400A94 = uvLoadModule('CBCK');
    sTextureSequencePool =
        _uvMemAllocAlign8(sTextureSequencesCount * sizeof(TextureSequence));
    uvMemSet(sTextureSequencePool, 0, sTextureSequencesCount * sizeof(TextureSequence));

    for (i = 0; i < sTextureSequencesCount; i++) {
        sTextureSequencePool[i].active = FALSE;
        sTextureSequencePool[i].used = 0;
        sTextureSequencePool[i].curFrame = 0;
        sTextureSequencePool[i].frameTime = 0.0f;
        sTextureSequencePool[i].uvts.frameCount = 0;
        sTextureSequencePool[i].uvts.frameTable = NULL;
        sTextureSequencePool[i].uvts.mode = 1;
        sTextureSequencePool[i].uvts.reverse = 0;
        sTextureSequencePool[i].uvts.frameRate = 1.0f;
    }

    D_uvtseq_rom_00400A94->uvAddCallback(
        D_uvtseq_rom_00400A90->func_uvgfxmgr_rom_00400AB8(1), (s32) uvTexSeqCallBack, 0, 0);
    sUpdateTexSequencesFlag = 0;
}

void uvTexSeqDestroy(void) {
    s32 var_s0;
    s32 var_s1;
    s32 i;

    D_uvtseq_rom_00400A94->uvRemoveCallback(
        D_uvtseq_rom_00400A90->func_uvgfxmgr_rom_00400AB8(1), (s32) uvTexSeqCallBack);

    for (i = 0; i < sTextureSequencesCount; i++) {
        _uvMemFree(sTextureSequencePool[i].uvts.frameTable);
    }

    _uvMemFree(sTextureSequencePool);
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('MATH');
    uvUnloadModule('MODL');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
}

void uvTexSeqModel(s32 texSeq, s32 uvts) {
    TextureSequence *texSequence;
    ParsedUVTS *vts;

    texSequence = &sTextureSequencePool[texSeq];
    if (uvts == 0xFF) {
        texSequence->active = FALSE;
        return;
    }
    vts = uvGetLoadedFile('UVTS', uvts);
    if ((vts != NULL) || (((vts = uvLoadFile('UVTS', uvts)) != NULL))) {
        texSequence->active = TRUE;

        if (vts->reverse == 1) {
            texSequence->curFrame = vts->frameCount - 1;
        } else {
            texSequence->curFrame = 0;
        }

        if (vts->frameCount != 0) {
            texSequence->frameTime = vts->frameTable[texSequence->curFrame].frameTime;
        }

        _uvMediaCopy(&texSequence->uvts, vts, sizeof(ParsedUVTS));
    }
}

void uvTexSeqProps(s32 texSeq, ...) {
    ParsedUVTS *uvts;
    TextureSequence *texSequence;
    int prop;
    va_list args;

    texSequence = &sTextureSequencePool[texSeq];
    uvts = &texSequence->uvts;
    if (texSequence == NULL) {
        return;
    }
    va_start(args, texSeq);
    if (uvts == NULL) {
        return;
    }

    while (TRUE) {
        prop = va_arg(args, s32);
        switch (prop) {
            case TSEQ_PROPID_ACTIVE:
                texSequence->active = va_arg(args, s32);
                break;
            case TSEQ_PROPID_CURR_FRAME:
                prop = va_arg(args, s32);
                if (prop < uvts->frameCount) {
                    texSequence->curFrame = prop;
                }
                break;
            case TSEQ_PROPID_MODE:
                uvts->mode = va_arg(args, s32);
                break;
            case TSEQ_PROPID_REVERSE:
                uvts->reverse = va_arg(args, s32);
                texSequence->curFrame = uvts->frameCount - 1;
                break;
            case TSEQ_PROPID_FRAMERATE:
                uvts->frameRate = va_arg(args, f64);
                break;
            case TSEQ_PROPID_UPDATE:
                sUpdateTexSequencesFlag = va_arg(args, s32);
                break;
            case TSEQ_PROPID_END:
                return;
        }
    }
}

s32 uvTexSeqFindFree(void) {
    s32 i;

    for (i = 0; i < sTextureSequencesCount; i++) {
        if (!sTextureSequencePool[i].used) {
            sTextureSequencePool[i].used = TRUE;
            sTextureSequencePool[i].active = TRUE;
            return i;
        }
    }
    return 0xFF;
}

void uvTexSeqFree(s32 texSeq) {
    if ((texSeq >= 0) && (texSeq < sTextureSequencesCount)) {
        sTextureSequencePool[texSeq].active = FALSE;
        sTextureSequencePool[texSeq].used = FALSE;
    }
}

void uvTexSeqCallBack(s32 arg0) {
    uvTexSeqUpdateAll();
}

void uvTexSeqUpdateAll(void) {
    s32 i;

    if (sUpdateTexSequencesFlag == 1) {
        return;
    }

    for (i = 0; i < sTextureSequencesCount; i++) {
        if (sTextureSequencePool[i].active) {
            uvTexSeqUpdate(i);
        }
    }
}

void uvTexSeqUpdate(s32 texSeq) {
    TextureSequence *texSequence;
    ParsedUVTS *uvts;

    texSequence = &sTextureSequencePool[texSeq];
    uvts = &texSequence->uvts;
    texSequence->frameTime -= uvts->frameRate * D_uvtseq_rom_00400A90->func_uvgfxmgr_rom_00401004();

    if (!(texSequence->frameTime > 0.0f) && (texSequence->frameTime <= 0.0f)) {
        while (TRUE) {
            switch (uvts->mode) { /* irregular */
                case UVTSEQ_MODE_ONESHOT:
                    if (uvts->reverse == 0) {
                        texSequence->curFrame = ((texSequence->curFrame + 1) % uvts->frameCount);
                    } else {
                        texSequence->curFrame =
                            (u8) ((s32) ((texSequence->curFrame + uvts->frameCount) - 1) % (s32) uvts->frameCount);
                    }
                    break;
                case UVTSEQ_MODE_REPEAT:
                    if (uvts->reverse == 0) {
                        texSequence->curFrame++;
                        if ((texSequence->curFrame + 1) == uvts->frameCount) {
                            texSequence->active = 0;
                            return;
                        }
                    } else {
                        if (texSequence->curFrame == 0) {
                            texSequence->active = 0;
                            return;
                        }
                        texSequence->curFrame--;
                    }
                    break;
                case UVTSEQ_MODE_STROBE:
                    if (uvts->reverse == 0) {
                        texSequence->curFrame++;
                        if ((texSequence->curFrame + 1) == uvts->frameCount) {
                            uvts->reverse = 1;
                        }
                    } else {
                        texSequence->curFrame--;
                        if (texSequence->curFrame == 0) {
                            uvts->reverse = 0;
                        }
                    }
                    break;
            }

            texSequence->frameTime += uvts->frameTable[texSequence->curFrame].frameTime;
            if (!(texSequence->frameTime <= 0.0f)) {
                return;
            }
        }
    }
}

u16 uvTexSeqGetCurFrameTexture(s32 texSeq) {
    TextureSequence *textureSequence;

    textureSequence = &sTextureSequencePool[texSeq];
    return textureSequence->uvts.frameTable[textureSequence->curFrame].texture;
}

u8 uvTexSeqGetFrameCount(s32 arg0) {
    TextureSequence *textureSequence;

    textureSequence = &sTextureSequencePool[arg0];
    return textureSequence->uvts.frameCount;
}

u16 uvTexSeqGetFrameTexture(s32 texSeq, s32 frame) {
    TextureSequence *textureSequence;

    textureSequence = &sTextureSequencePool[texSeq];
    frame = (s32) (textureSequence->curFrame + frame) % (s32) textureSequence->uvts.frameCount;
    return textureSequence->uvts.frameTable[frame].texture;
}

u8 uvTexSeqGetActive(s32 texSeq) {
    TextureSequence *textureSequence;

    textureSequence = &sTextureSequencePool[texSeq];
    return textureSequence->active;
}

f32 func_uvtseq_rom_00400A10(s32 texSeq) {
    TextureSequence *textureSequence;

    textureSequence = &sTextureSequencePool[texSeq];
    return textureSequence->frameTime / textureSequence->uvts.frameTable[textureSequence->curFrame].frameTime;
}
