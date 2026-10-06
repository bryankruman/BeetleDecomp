#ifndef RUMBLE_H
#define RUMBLE_H

typedef struct Rumble_Exports_s {
    /* 0x0 */ void (*func_rumble_00400048)(void);                       /* inferred */
    /* 0x4 */ void (*func_rumble_00400050)(s32, f32, f32, f32);     /* inferred */
    /* 0x8 */ void (*func_rumble_00400138)(void);                       /* inferred */
} Rumble_Exports;                                   /* size = 0xC */

#endif /* RUMBLE_H */
