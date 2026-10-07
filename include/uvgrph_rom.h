#ifndef UVGRPH_ROM_H
#define UVGRPH_ROM_H

typedef struct UvGrphInnerStruct_s {
   /* unk0 */ f32 unk0;
   /* unk4 */ f32 unk4;
} UvGrphInnerStruct;

typedef struct UvGrphStruct_s {
    /* 0x0 */ s32 count;
    /* 0x4 */ UvGrphInnerStruct arr[1];
} UvGrphStruct;

typedef struct UvGrph_Exports_s {
    /* 0x00 */ void (*uvGrphNoOpModuleCleanup)(void);                      /* inferred */
    /* 0x04 */ f32 (*uvGrphEvaluateLinearCurve)(UvGrphStruct *, f32);    /* inferred */
    /* 0x08 */ void (*uvGrphClampPointCount)(s32, s32 *);            /* inferred */
    /* 0x0C */ s32 (*uvGrphInsertPointAfter)(UvGrphStruct *, s32);    /* inferred */
    /* 0x10 */ s32 (*uvGrphRemovePoint)(UvGrphStruct *, s32);   /* inferred */
    /* 0x14 */ void (*func_uvgrph_rom_0040033C)(UvGrphStruct *, f32);  /* inferred */
    /* 0x18 */ f32 (*uvGrphEvaluateInverseRange)(UvGrphStruct *, f32, f32, f32); /* inferred */
} UvGrph_Exports;                                   /* size = 0x1C */


#endif /* UVGRPH_ROM_H */
