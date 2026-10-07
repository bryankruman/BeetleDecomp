#ifndef UVDGEOM_ROM_H
#define UVDGEOM_ROM_H

typedef struct UvDGeom_Rom_Exports_s {
    /* 0x00 */ void (*uvDgeomModuleCleanup)(void);                      /* inferred */
    /* 0x04 */ s16 (*uvVtx)(s32, s32, s32, s32, s32, s32, s32, s32, s32); /* inferred */
    /* 0x08 */ void (*uvDgeomSetVertexRange)(s32, s32);              /* inferred */
    /* 0x0C */ void (*uvVtxBeginPoly)(void);                      /* inferred */
    /* 0x10 */ void (*uvBeginGrid)(void);                     /* inferred */
    /* 0x14 */ void (*uvBeginTmesh)(void);                     /* inferred */
    /* 0x18 */ void (*uvDgeomEndTriangleMesh)(void);                     /* inferred */
    /* 0x1C */ void (*uvDgeomEndGrid)(s32, s32, s32, s32);   /* inferred */
    /* 0x20 */ void (*uvVtxEndPoly)(void);                     /* inferred */
    /* 0x24 */ s16 (*uvVtxDup)(s32, s32, s32, s32, s32, s32, s32, s32, s32); /* inferred */
} UvDGeom_Rom_Exports;                              /* size = 0x28 */

#endif /* UVDEGEOM_ROM_H */
