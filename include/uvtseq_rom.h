#ifndef UVTSEQ_ROM_H
#define UVTSEQ_ROM_H


#define TSEQ_PROPID_END          0
#define TSEQ_PROPID_ACTIVE       1 // type:s32
#define TSEQ_PROPID_MODE         2 // type:s32
#define TSEQ_PROPID_CURR_FRAME   3 // type:s32
#define TSEQ_PROPID_FRAMERATE    4 // type:f64
#define TSEQ_PROPID_REVERSE      5 // type:s32
#define TSEQ_PROPID_UPDATE      6 // type:s32

#define TSEQ_PROP_END            TSEQ_PROPID_END
#define TSEQ_PROP_ACTIVE(x)      TSEQ_PROPID_ACTIVE, (x)
#define TSEQ_PROP_MODE(x)        TSEQ_PROPID_MODE, (x)
#define TSEQ_PROP_CURR_FRAME(x)  TSEQ_PROPID_CURR_FRAME, (x)
#define TSEQ_PROP_FRAMERATE(x)   TSEQ_PROPID_FRAMERATE, (x)
#define TSEQ_PROP_REVERSE(x)     TSEQ_PROPID_REVERSE, (x)
#define TSEQ_PROP_UPDATE(x)     TSEQ_PROPID_UPDATE, (x)

typedef struct UvTSeq_Exports_s {
    /* 0x00 */ void (*uvTexSeqDestroy)(void);                      /* inferred */
    /* 0x04 */ void (*uvTexSeqModel)(s32, s32);              /* inferred */
    /* 0x08 */ void (*uvTexSeqProps)(s32, ...);              /* inferred */
    /* 0x0C */ s32 (*uvTexSeqFindFree)(void);                       /* inferred */
    /* 0x10 */ void (*uvTexSeqFree)(s32);                  /* inferred */
    /* 0x14 */ u16 (*uvTexSeqGetCurFrameTexture)(s32);                   /* inferred */
    /* 0x18 */ u8 (*uvTexSeqGetFrameCount)(s32);                    /* inferred */
    /* 0x1C */ u16 (*uvTexSeqGetFrameTexture)(s32, s32);              /* inferred */
    /* 0x20 */ u8 (*uvTexSeqGetActive)(s32);                    /* inferred */
    /* 0x24 */ f32 (*func_uvtseq_rom_00400A10)(s32);                   /* inferred */
} UvTSeq_Exports;                                   /* size = 0x28 */
#endif /* UVTSEQ_ROM_H */
