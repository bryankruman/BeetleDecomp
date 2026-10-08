#ifndef RUMBLE_H
#define RUMBLE_H

typedef struct Rumble_Exports_s {
    /* 0x0 */ void (*rumbleNoOpModuleCleanup)(void);                       /* inferred */
    /* 0x4 */ void (*rumbleMergeQuantizedPatternValues)(s32, f32, f32, f32);     /* inferred */
    /* 0x8 */ void (*rumbleUpdateControllerPatterns)(void);                       /* inferred */
} Rumble_Exports;                                   /* size = 0xC */

#endif /* RUMBLE_H */
