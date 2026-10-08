#ifndef UVTEXANIM_ROM_H
#define UVTEXANIM_ROM_H


typedef struct UvTexAnim_Exports_s {
    /* 0x00 */ void (*uvTexAnimModuleCleanup)(void);                      /* inferred */
    /* 0x04 */ void (*uvTexAnimCollectLoadedAnimationRecords)(void);                      /* inferred */
    /* 0x08 */ void (*uvTexAnimReleaseSharedArray)(void);                      /* inferred */
    /* 0x0C */ void (*uvTexAnimSetTaggedProperties)(UnkUVTX_1C*, ...);      /* inferred */
} UvTexAnim_Exports;                                /* size = 0x10 */


#endif /* UVTEXANIM_ROM_H */
