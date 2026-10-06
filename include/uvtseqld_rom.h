// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef UVTSEQLD_ROM_H
#define UVTSEQLD_ROM_H
typedef struct UvtSeqLd_Rom_Exports_s {
    /* 0x00 */ void (*uvTexSeqLd_stub)(void);                      /* inferred */
    /* 0x04 */ void *(*uvParseUVTS)(u8 *);                 /* inferred */
    /* 0x08 */ void (*uvFreeUVTS)(void *);                /* inferred */
    /* 0x0C */ s32 (*uvGetFirstFrameTexture)(s32);                    /* inferred */
} UvtSeqLd_Rom_Exports;                             /* size = 0x10 */
#endif /* UVTSEQLD_ROM_H */
