#ifndef UVINTERSECT_ROM_H
#define UVINTERSECT_ROM_H


typedef struct UvIntersect_Exports_s {
    /* 0x00 */ void (*uvIntersectModuleCleanup)();                      /* inferred */
    /* 0x04 */ s32 (*uvIntersectSegmentSphereFraction)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *); /* inferred */
    /* 0x08 */ s32 (*uvIntersectPointInsideSphere)(f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x0C */ s32 (*uvIntersectSpheresOverlap)(f32, f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x10 */ s32 (*func_uvintersect_rom_00400530)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x14 */ void (*uvIntersectGetSegmentSphereNormal)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, Vec3F *); /* inferred */
    /* 0x18 */ s32 (*uvIntersectGetScaledTriangleNormal)(Vtx *, s32, s32, s32, Vec3F *, f32); /* inferred */
    /* 0x1C */ s32 (*uvIntersectClassifySphereTriangleContact)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, Vec3F *, f32 *); /* inferred */
    /* 0x20 */ s32 (*uvIntersectPointInPositiveWindingTriangle2D)(f32, f32, f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x24 */ s32 (*uvIntersectPointInNegativeWindingTriangle2D)(f32, f32, f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x28 */ s32 (*uvIntersectPointInOrientedTriangle3D)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x2C */ s32 (*uvIntersectSegmentScaledTriangle)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, Vec3F *); /* inferred */
    /* 0x30 */ s32 (*uvIntersectSegmentBoundsOverlapRectangle)(f32, f32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x34 */ void (*uvIntersectClipSegmentToRectangleBounds)(f32 *, f32 *, f32 *, f32 *, f32, f32, f32, f32); /* inferred */
    /* 0x38 */ void (*uvIntersectClipSegmentDepthToRectangleBounds)(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32, f32, f32, f32); /* inferred */
    /* 0x3C */ void (*func_uvintersect_rom_004020A0)(Mtx4F *, s16, Vec3F *); /* inferred */
    /* 0x40 */ s32 (*uvIntersectSegmentTriangleWithNormal)(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, Vec3F *); /* inferred */
} UvIntersect_Exports;                              /* size = 0x44 */


#endif /* UVINTERSECT_ROM_H */
