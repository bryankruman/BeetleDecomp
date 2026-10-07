#ifndef UVQUAT_ROM_H
#define UVQUAT_ROM_H

typedef struct Quat_s {
    /* 0x00 */ f32 x;                /* inferred */
    /* 0x04 */ f32 y;                /* inferred */
    /* 0x08 */ f32 z;                /* inferred */
    /* 0x0C */ f32 w;                /* inferred */
} Quat; /* size = 0x10 */

typedef struct UvQuat_Exports_s {
    /* 0x00 */ void (*uvQuatModuleCleanup)(void);                      /* inferred */
    /* 0x04 */ void (*uvQuatFromRotationMatrix)(Quat*, Mtx4F*); /* inferred */
    /* 0x08 */ void (*uvQuatFromEuler)(Quat*, f32, f32, f32); /* inferred */
    /* 0x0C */ void (*uvQuatToAdjustedRotationMatrix)(Mtx4F*, Quat*); /* inferred */
    /* 0x10 */ void (*uvQuatComputeAngularDerivative)(Quat*, Quat*, f32, f32, f32, f32); /* inferred */
    /* 0x14 */ void (*uvQuatMultiply)(Quat*, Quat*, Quat*); /* inferred */
    /* 0x18 */ void (*uvQuatCopy)(Quat*, Quat*); /* inferred */
    /* 0x1C */ void (*uvQuatBlendNormalized)(Quat*, Quat*, Quat*, f32); /* inferred */
} UvQuat_Exports;                                   /* size = 0x20 */

#endif /* UVQUAT_ROM_H */
