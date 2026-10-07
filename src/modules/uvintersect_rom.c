// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

static UvMath_Exports *sUvMathExports;
static UvFVec_Rom_Exports *sUvFvecExports;

void __entrypoint_func_uvintersect_rom_400000(UvIntersect_Exports *exports);
void uvIntersectModuleCleanup(void);
s32 uvIntersectSegmentSphereFraction(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 *arg10);
s32 uvIntersectPointInsideSphere(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
s32 uvIntersectSpheresOverlap(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
s32 func_uvintersect_rom_00400530(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10);
void uvIntersectGetSegmentSphereNormal(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, Vec3F *arg10);
s32 uvIntersectGetScaledTriangleNormal(Vtx *arg0, s32 arg1, s32 arg2, s32 arg3, Vec3F *arg4, f32 arg5);
s32 uvIntersectClassifySphereTriangleContact(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, Vec3F *arg14, f32 *arg15);
s32 uvIntersectPointInPositiveWindingTriangle2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
s32 uvIntersectPointInNegativeWindingTriangle2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);
s32 uvIntersectPointInOrientedTriangle3D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, f32 arg14);
s32 uvIntersectSegmentScaledTriangle(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, f32 arg14, f32 arg15, f32 arg16, f32 *arg17, Vec3F *arg18);
s32 uvIntersectSegmentBoundsOverlapRectangle(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void uvIntersectClipSegmentToRectangleBounds(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void uvIntersectClipSegmentDepthToRectangleBounds(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void func_uvintersect_rom_004020A0(Mtx4F *arg0, s16 arg1, Vec3F *arg2);
s32 uvIntersectSegmentTriangleWithNormal(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, f32 arg14, f32 *arg15, Vec3F *arg16);

s32 D_uvintersect_rom_00402660[] = {0x00440000, __entrypoint_func_uvintersect_rom_400000, 0, 0};

void __entrypoint_func_uvintersect_rom_400000(UvIntersect_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvIntersectModuleCleanup = uvIntersectModuleCleanup;
    exports->uvIntersectPointInOrientedTriangle3D = uvIntersectPointInOrientedTriangle3D;
    exports->uvIntersectSegmentSphereFraction = uvIntersectSegmentSphereFraction;
    exports->uvIntersectSegmentScaledTriangle = uvIntersectSegmentScaledTriangle;
    exports->uvIntersectPointInsideSphere = uvIntersectPointInsideSphere;
    exports->uvIntersectSegmentBoundsOverlapRectangle = uvIntersectSegmentBoundsOverlapRectangle;
    exports->uvIntersectSpheresOverlap = uvIntersectSpheresOverlap;
    exports->uvIntersectClipSegmentToRectangleBounds = uvIntersectClipSegmentToRectangleBounds;
    exports->func_uvintersect_rom_00400530 = func_uvintersect_rom_00400530;
    exports->uvIntersectClipSegmentDepthToRectangleBounds = uvIntersectClipSegmentDepthToRectangleBounds;
    exports->uvIntersectGetSegmentSphereNormal = uvIntersectGetSegmentSphereNormal;
    exports->func_uvintersect_rom_004020A0 = func_uvintersect_rom_004020A0;
    exports->uvIntersectGetScaledTriangleNormal = uvIntersectGetScaledTriangleNormal;
    exports->uvIntersectSegmentTriangleWithNormal = uvIntersectSegmentTriangleWithNormal;
    exports->uvIntersectClassifySphereTriangleContact = uvIntersectClassifySphereTriangleContact;
    exports->uvIntersectPointInPositiveWindingTriangle2D = uvIntersectPointInPositiveWindingTriangle2D;
    exports->uvIntersectPointInNegativeWindingTriangle2D = uvIntersectPointInNegativeWindingTriangle2D;
    #ifdef __sgi
    #line 1
    #endif
    sUvMathExports = uvLoadModule('MATH');
    sUvFvecExports = uvLoadModule('FVEC');
}

#line 55 "src/modules/uvintersect_rom.c"
/* Unload MATH and FVEC dependencies in their original order. */
void uvIntersectModuleCleanup(void) {
    uvUnloadModule('MATH');
    uvUnloadModule('FVEC');
}
#line 59 "src/modules/uvintersect_rom.c"

#line 60 "src/modules/uvintersect_rom.c"
/* Solve the segment/sphere quadratic and return the first root within
 * zero through one. A zero-length segment uses the inclusive point test; two
 * strictly interior endpoints return fraction zero. Misses leave output alone.
 * Scratch values are reused across endpoint tests and quadratic evaluation. */
s32 uvIntersectSegmentSphereFraction(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 centerX,
                                  f32 centerY, f32 centerZ, f32 radius, f32 *fraction) {
    f32 lengthSquared;
    f32 linearCoefficient;
    f32 constantCoefficient;
    f32 unusedStartOffsetZ;
    f32 unusedScalar0;
    f32 unusedScalar1;
    f32 firstRootOrOffsetZ;
    f32 secondRoot;
    s32 intersects;
    f32 scratch0;
    s32 firstValid;
    f32 scratch1;
    s32 secondRootValid;

    lengthSquared = SQ(endX - startX) + SQ(endY - startY) + SQ(endZ - startZ);
    if (lengthSquared == 0.0f) {
        intersects = uvIntersectPointInsideSphere(startX, startY, startZ, centerX, centerY, centerZ, radius);
        if (intersects) {
            *fraction = 0.0f;
        }
        return intersects;
    }
    scratch0 = startX - centerX;
    scratch1 = startY - centerY;
    unusedStartOffsetZ = startZ - centerZ;
    linearCoefficient = 2.0f
           * (((endX - startX) * (startX - centerX)) + ((endY - startY) * (startY - centerY))
              + ((endZ - startZ) * (startZ - centerZ)));
    constantCoefficient = (SQ(startX - centerX) + SQ(startY - centerY) + SQ(startZ - centerZ)) - SQ(radius);
    firstValid = 0;
    if (sUvMathExports->uvSqrtf(SQ(startX - centerX) + SQ(startY - centerY) + SQ(startZ - centerZ))
        < radius) {
        firstValid = 1;
    }
    scratch0 = endX - centerX;
    scratch1 = endY - centerY;
    firstRootOrOffsetZ = endZ - centerZ;
    if ((sUvMathExports->uvSqrtf(SQ(scratch0) + SQ(scratch1) + SQ(firstRootOrOffsetZ)) < radius)
        && (firstValid != 0)) {
        *fraction = 0.0f;
        return 1;
    }
    scratch0 = linearCoefficient * linearCoefficient;
    scratch1 = 4.0f * lengthSquared * constantCoefficient;
    if (scratch0 < scratch1) {
        return 0;
    }
    scratch0 = sUvMathExports->uvSqrtf(scratch0 - scratch1);
    firstRootOrOffsetZ = ((-linearCoefficient) - scratch0) / (2.0f * lengthSquared);
    secondRoot = ((-linearCoefficient) + scratch0) / (2.0f * lengthSquared);
    firstValid = 0;
    secondRootValid = 0;

    if ((firstRootOrOffsetZ >= 0.0f) && (firstRootOrOffsetZ <= 1.0f)) {
        firstValid = 1;
    }
    if ((secondRoot >= 0.0f) && (secondRoot <= 1.0f)) {
        secondRootValid = 1;
    }
    if ((firstValid != 0) && (secondRootValid != 0)) {
        if (firstRootOrOffsetZ < secondRoot) {
            *fraction = firstRootOrOffsetZ;
        } else {
            *fraction = secondRoot;
        }
        return 1;
    }
    if (firstValid != 0) {
        *fraction = firstRootOrOffsetZ;
        return 1;
    }
    if (secondRootValid != 0) {
        *fraction = secondRoot;
        return TRUE;
    }
    return FALSE;
}
#line 139 "src/modules/uvintersect_rom.c"

#line 140 "src/modules/uvintersect_rom.c"
/* Test squared point-to-center distance against squared radius, including
 * the boundary. Preserve the original squared-radius behavior for signed radii
 * and the original floating comparisons. */
s32 uvIntersectPointInsideSphere(f32 pointX, f32 pointY, f32 pointZ, f32 centerX, f32 centerY, f32 centerZ,
                                  f32 radius) {
    f32 dz;
    f32 dx;
    f32 dy;

    dx = pointX - centerX;
    dy = pointY - centerY;
    dz = pointZ - centerZ;
    if ((SQ(dx) + SQ(dy) + SQ(dz)) <= SQ(radius)) {
        return TRUE;
    }
    return FALSE;
}
#line 154 "src/modules/uvintersect_rom.c"

#line 155 "src/modules/uvintersect_rom.c"
/* Test center distance against the square of the summed radii.
 * Touching spheres are accepted; signed radii and unordered comparisons retain
 * their original behavior. */
s32 uvIntersectSpheresOverlap(f32 firstX, f32 firstY, f32 firstZ, f32 firstRadius, f32 secondX, f32 secondY, f32 secondZ,
                                  f32 secondRadius) {
    f32 dz;
    f32 radiusSum;
    f32 dx;
    f32 dy;

    dx = firstX - secondX;
    dy = firstY - secondY;
    dz = firstZ - secondZ;
    radiusSum = secondRadius + firstRadius;

    if ((SQ(dx) + SQ(dy) + SQ(dz)) <= SQ(radiusSum)) {
        return TRUE;
    }
    return FALSE;
}
#line 172 "src/modules/uvintersect_rom.c"

s32 func_uvintersect_rom_00400530(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                                  f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    f32 sp24;
    f32 sp50;
    f32 temp_fv0;
    Vec3F sp40;
    Vec3F sp34;
    Vec3F sp28;

    sp24 = SQ(arg3 + arg10);
    sp40.x = arg4 - arg0;
    sp40.y = arg5 - arg1;
    sp40.z = arg6 - arg2;
    sp50 = SQ(sp40.x) + SQ(sp40.y) + SQ(sp40.z);
    if (sp50 <= sp24) {
        return 1;
    }
    sp28.x = arg7 - arg4;
    sp28.y = arg8 - arg5;
    sp28.z = arg9 - arg6;

    temp_fv0 = sUvFvecExports->uvVec3FDot(&sp40, &sp28);
    sp50 *= 1.0f - SQ(temp_fv0);
    if (sp24 < sp50) {
        return 0;
    }
    sp34.x = arg7 - arg0;
    sp34.y = arg8 - arg1;
    sp34.z = arg9 - arg2;
    sp50 = SQ(sp34.x) + SQ(sp34.y) + SQ(sp34.z);
    if (sp50 <= sp24) {
        return 1;
    }
    if (temp_fv0 > 0.0f) {
        return 0;
    }
    if (sUvFvecExports->uvVec3FDot(&sp34, &sp28) < 0.0f) {
        return FALSE;
    }
    return TRUE;
}

#line 215 "src/modules/uvintersect_rom.c"
/* Interpolate the segment at the caller fraction and normalize the
 * displacement from the center. A zero displacement returns positive Z as
 * the original fallback normal; the fraction is not clamped. */
void uvIntersectGetSegmentSphereNormal(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 fraction,
                                   f32 centerX, f32 centerY, f32 centerZ, Vec3F *normal) {
    f32 distance;
    f32 normalX;
    f32 normalZ;
    f32 normalY;

    distance = sUvMathExports->uvSqrtf(SQ(((((endX - startX) * fraction) + startX) - centerX))
                                                   + SQ(((((endY - startY) * fraction) + startY) - centerY))
                                                   + SQ(((((endZ - startZ) * fraction) + startZ) - centerZ)));
    if (distance != 0.0f) {
        normalX = ((((endX - startX) * fraction) + startX) - centerX) / distance;
        normalY = ((((endY - startY) * fraction) + startY) - centerY) / distance;
        normalZ = ((((endZ - startZ) * fraction) + startZ) - centerZ) / distance;
    } else {
        normalX = 0.0f;
        normalZ = 1.0f;
        normalY = 0.0f;
    }
    normal->x = normalX;
    normal->y = normalY;
    normal->z = normalZ;
}
#line 238 "src/modules/uvintersect_rom.c"

#line 239 "src/modules/uvintersect_rom.c"
/* Build two indexed triangle edges, scale their Z components and
 * normalize their cross product. Return zero when normalization reports a
 * degenerate triangle; vertex indices remain caller-owned.
 * RE_UNKNOWN: physical units of the caller Z scale remain unproven. */
s32 uvIntersectGetScaledTriangleNormal(Vtx *vertices, s32 firstIndex, s32 secondIndex, s32 thirdIndex, Vec3F *normal, f32 zScale) {
    Vec3F firstEdge;
    Vec3F secondEdge;
    f32 firstZ;
    f32 unusedScalar;
    f32 firstX;
    f32 firstY;

    firstX = vertices[firstIndex].v.ob[0];
    firstY = vertices[firstIndex].v.ob[1];
    firstZ = vertices[firstIndex].v.ob[2];
    firstEdge.x = vertices[secondIndex].v.ob[0] - firstX;
    firstEdge.y = vertices[secondIndex].v.ob[1] - firstY;
    firstEdge.z = vertices[secondIndex].v.ob[2] - firstZ;
    secondEdge.x = vertices[thirdIndex].v.ob[0] - firstX;
    secondEdge.y = vertices[thirdIndex].v.ob[1] - firstY;
    secondEdge.z = vertices[thirdIndex].v.ob[2] - firstZ;
    firstEdge.z *= zScale;
    secondEdge.z *= zScale;
    sUvFvecExports->uvVec3FCross(normal, &firstEdge, &secondEdge);
    if (sUvFvecExports->uvVec3FNormalize(normal, normal) == 0) {
        return 0;
    }
    return 1;
}
#line 264 "src/modules/uvintersect_rom.c"

#line 265 "src/modules/uvintersect_rom.c"
/* Test a Z-scaled triangle plane and its inward edge distances against
 * the sphere. Return zero for rejection, one for a face classification and
 * two when a negative edge distance contributes to the reported distance.
 * RE_ORIGINAL_QUIRK: both accepted classifications output the face normal;
 * the separately selected edge normal is not copied to the caller.
 * RE_UNKNOWN: physical units and intended contact-classification semantics
 * beyond these observed return conditions remain unproven. */
s32 uvIntersectClassifySphereTriangleContact(f32 centerX, f32 centerY, f32 centerZ, f32 radius, f32 zScale, f32 firstX, f32 firstY,
                                  f32 firstZ, f32 secondX, f32 secondY, f32 secondZ, f32 thirdX, f32 thirdY,
                                  f32 thirdZ, Vec3F *normal, f32 *distance) {
    Vec3F faceNormal;
    Vec3F secondEdge;
    Vec3F firstEdge;
    Vec3F centerOffset;
    Vec3F inwardEdgeNormal;
    Vec3F edge;
    Vec3F selectedEdgeNormal;
    f32 planeCircleRadius;
    f32 planeDistance;
    f32 edgeDistance;
    s32 classification;
    f32 minimumNegativeEdgeDistance;

    firstEdge.x = secondX - firstX;
    firstEdge.y = secondY - firstY;
    firstEdge.z = secondZ - firstZ;
    firstEdge.z *= zScale;
    secondEdge.x = thirdX - firstX;
    secondEdge.y = thirdY - firstY;
    secondEdge.z = thirdZ - firstZ;
    secondEdge.z *= zScale;
    sUvFvecExports->uvVec3FCross(&faceNormal, &firstEdge, &secondEdge);
    if (sUvFvecExports->uvVec3FNormalize(&faceNormal, &faceNormal) == 0) {
        return 0;
    }
    centerOffset.x = centerX - firstX;
    centerOffset.y = centerY - firstY;
    centerOffset.z = centerZ - firstZ;
    centerOffset.z = centerOffset.z * zScale;
    planeDistance = sUvFvecExports->uvVec3FDot((Vec3F *) &centerOffset, &faceNormal);
    if (radius < FABS(planeDistance)) {
        return 0;
    }

    planeCircleRadius = sUvMathExports->uvSqrtf(SQ(radius) - SQ(planeDistance));
    minimumNegativeEdgeDistance = 10000000000.0f;


    sUvFvecExports->uvVec3FCross(&inwardEdgeNormal, &faceNormal, (Vec3F *) &firstEdge);
    sUvFvecExports->uvVec3FNormalize(&inwardEdgeNormal, &inwardEdgeNormal);
    edgeDistance = sUvFvecExports->uvVec3FDot((Vec3F *) &centerOffset, &inwardEdgeNormal);
    if (edgeDistance < 0) {
        minimumNegativeEdgeDistance = edgeDistance;
        sUvFvecExports->uvVec3FCopy(&selectedEdgeNormal, &inwardEdgeNormal);
    }
    if (edgeDistance < -planeCircleRadius) {
        return 0;
    }

    edge.x = thirdX - secondX;
    edge.y = thirdY - secondY;
    edge.z = thirdZ - secondZ;
    centerOffset.x = centerX - secondX;
    centerOffset.y = centerY - secondY;
    centerOffset.z = centerZ - secondZ;
    centerOffset.z *= zScale;
    edge.z *= zScale;
    sUvFvecExports->uvVec3FCross(&inwardEdgeNormal, &faceNormal, (Vec3F *) &edge);
    sUvFvecExports->uvVec3FNormalize(&inwardEdgeNormal, &inwardEdgeNormal);
    edgeDistance = sUvFvecExports->uvVec3FDot((Vec3F *) &centerOffset, &inwardEdgeNormal);
    if ((edgeDistance < minimumNegativeEdgeDistance) && (edgeDistance < 0)) {
        minimumNegativeEdgeDistance = edgeDistance;
        sUvFvecExports->uvVec3FCopy(&selectedEdgeNormal, &inwardEdgeNormal);
    }
    if (edgeDistance < -planeCircleRadius) {
        return 0;
    }
    edge.x = firstX - thirdX;
    edge.y = firstY - thirdY;
    edge.z = firstZ - thirdZ;
    centerOffset.x = centerX - thirdX;
    centerOffset.y = centerY - thirdY;
    centerOffset.z = centerZ - thirdZ;
    centerOffset.z *= zScale;
    edge.z *= zScale;

    sUvFvecExports->uvVec3FCross(&inwardEdgeNormal, &faceNormal, &edge);
    sUvFvecExports->uvVec3FNormalize(&inwardEdgeNormal, &inwardEdgeNormal);
    edgeDistance = sUvFvecExports->uvVec3FDot(&centerOffset, &inwardEdgeNormal);
    if ((edgeDistance < minimumNegativeEdgeDistance) && (edgeDistance < 0)) {
        minimumNegativeEdgeDistance = edgeDistance;
        sUvFvecExports->uvVec3FCopy(&selectedEdgeNormal, &inwardEdgeNormal);
    }
    if (edgeDistance < -planeCircleRadius) {
        return 0;
    }
    if (minimumNegativeEdgeDistance < 0) {
        *distance = sUvMathExports->uvSqrtf(SQ(planeDistance) + SQ(minimumNegativeEdgeDistance));
        classification = 2;
    } else {
        *distance = planeDistance;
        classification = 1;
    }
    normal->x = faceNormal.x;
    normal->y = faceNormal.y;
    normal->z = faceNormal.z;
    return classification;
}
#line 366 "src/modules/uvintersect_rom.c"

#line 367 "src/modules/uvintersect_rom.c"
/* Divide triangle XY coordinates by the caller scale when it is not
 * one, then test the three nonnegative directed-edge cross products.
 * Boundary points are accepted; preserve the original degenerate, zero-scale
 * and unordered-value behavior. */
s32 uvIntersectPointInPositiveWindingTriangle2D(f32 pointX, f32 pointY, f32 firstX, f32 firstY, f32 secondX, f32 secondY, f32 thirdX,
                                  f32 thirdY, f32 triangleScale) {
    f32 inverseScale;
    f32 unusedScalar0;
    f32 unusedScalar1;
    s32 unusedWord;

    if (triangleScale != 1.0f) {
        inverseScale = 1.0f / triangleScale;
        firstX *= inverseScale;
        firstY *= inverseScale;
        secondX *= inverseScale;
        secondY *= inverseScale;
        thirdX *= inverseScale;
        thirdY *= inverseScale;
    }
    if (((pointY - firstY) * (secondX - firstX)) < ((pointX - firstX) * (secondY - firstY))) {
        return FALSE;
    }
    if (((pointY - secondY) * (thirdX - secondX)) < ((pointX - secondX) * (thirdY - secondY))) {
        return FALSE;
    }
    if (((pointY - thirdY) * (firstX - thirdX)) < ((pointX - thirdX) * (firstY - thirdY))) {
        return FALSE;
    }
    return TRUE;
}
#line 394 "src/modules/uvintersect_rom.c"

#line 395 "src/modules/uvintersect_rom.c"
/* Divide triangle XY coordinates by the caller scale when it is not
 * one, then test the three nonpositive directed-edge cross products.
 * Boundary points are accepted; preserve the original degenerate, zero-scale
 * and unordered-value behavior. */
s32 uvIntersectPointInNegativeWindingTriangle2D(f32 pointX, f32 pointY, f32 firstX, f32 firstY, f32 secondX, f32 secondY, f32 thirdX, f32 thirdY, f32 triangleScale) {
    f32 inverseScale;

    if (triangleScale != 1.0f) {
        inverseScale = 1.0f / triangleScale;
        firstX *= inverseScale;
        firstY *= inverseScale;
        secondX *= inverseScale;
        secondY *= inverseScale;
        thirdX *= inverseScale;
        thirdY *= inverseScale;
    }
    if (((pointX - firstX) * (secondY - firstY)) < ((pointY - firstY) * (secondX - firstX))) {
        return FALSE;
    }
    if (((pointX - secondX) * (thirdY - secondY)) < ((pointY - secondY) * (thirdX - secondX))) {
        return FALSE;
    }
    if (((pointX - thirdX) * (firstY - thirdY)) < ((pointY - thirdY) * (firstX - thirdX))) {
        return FALSE;
    }
    return TRUE;
}
#line 418 "src/modules/uvintersect_rom.c"

#line 419 "src/modules/uvintersect_rom.c"
/* Test the point against all three triangle edges using the caller
 * normal to orient each cross product. A positive oriented edge expression
 * rejects the point; boundary and degenerate cases keep the original behavior. */
s32 uvIntersectPointInOrientedTriangle3D(f32 pointX, f32 pointY, f32 pointZ, f32 normalX, f32 normalY, f32 normalZ, f32 firstX, f32 firstY, f32 firstZ, f32 secondX, f32 secondY, f32 secondZ, f32 thirdX,
                  f32 thirdY, f32 thirdZ) {
    s32 unusedWord;
    f32 offsetZ;
    f32 edgeX;
    f32 edgeY;
    f32 edgeZ;
    f32 offsetX;
    f32 offsetY;

    offsetX = pointX - firstX;
    offsetY = pointY - firstY;
    offsetZ = pointZ - firstZ;
    edgeX = secondX - firstX;
    edgeY = secondY - firstY;
    edgeZ = secondZ - firstZ;
    if ((((((offsetY * edgeZ) - (offsetZ * edgeY)) * normalX) - (((offsetX * edgeZ) - (offsetZ * edgeX)) * normalY)) +
         (((offsetX * edgeY) - (offsetY * edgeX)) * normalZ)) > 0.0f) {
        return 0;
    }

    offsetX = pointX - secondX;
    offsetY = pointY - secondY;
    offsetZ = pointZ - secondZ;
    edgeX = thirdX - secondX;
    edgeY = thirdY - secondY;
    edgeZ = thirdZ - secondZ;
    if ((((((offsetY * edgeZ) - (offsetZ * edgeY)) * normalX) - (((offsetX * edgeZ) - (offsetZ * edgeX)) * normalY)) +
         (((offsetX * edgeY) - (offsetY * edgeX)) * normalZ)) > 0.0f) {
        return 0;
    }

    offsetX = pointX - thirdX;
    offsetY = pointY - thirdY;
    offsetZ = pointZ - thirdZ;
    edgeX = firstX - thirdX;
    edgeY = firstY - thirdY;
    edgeZ = firstZ - thirdZ;
    if ((((((offsetY * edgeZ) - (offsetZ * edgeY)) * normalX) - (((offsetX * edgeZ) - (offsetZ * edgeX)) * normalY)) +
         (((offsetX * edgeY) - (offsetY * edgeX)) * normalZ)) > 0.0f) {
        return 0;
    }

    return 1;
}
#line 464 "src/modules/uvintersect_rom.c"

#line 465 "src/modules/uvintersect_rom.c"
/* Scale triangle coordinates, reject separated segment/triangle bounds,
 * compute the triangle normal and intersect the segment with its plane. Test
 * the resulting point using XY winding or the full oriented-edge helper.
 * RE_ORIGINAL_QUIRK: rejection paths write outputs differently; the normal
 * may already be written, while the fraction is cleared only on some misses.
 * RE_UNKNOWN: physical units of the XY and Z scale divisors remain unproven. */
s32 uvIntersectSegmentScaledTriangle(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 firstX, f32 firstY, f32 firstZ, f32 secondX, f32 secondY, f32 secondZ, f32 thirdX, f32 thirdY, f32 thirdZ, f32 xyScale, f32 zScale, f32* fraction, Vec3F* normal) {
    f32 planeDenominator;
    f32 unusedScalar;
    f32 minY;
    f32 maxY;
    f32 planeNumerator;
    f32 minX;
    f32 maxX;
    Vec3F firstEdge;
    Vec3F secondEdge;
    f32 minZ;
    f32 maxZ;
    f32 scratch0;
    f32 scratch1;
    s32 unusedWords[2];

    if ((xyScale != 1.0f) || (zScale != 1.0f)) {
        scratch0 = 1.0f / xyScale;
        scratch1 = 1.0f / zScale;
        firstX *= scratch0;
        firstY *= scratch0;
        firstZ *= scratch1;
        secondX *= scratch0;
        secondY *= scratch0;
        secondZ *= scratch1;
        thirdX *= scratch0;
        thirdY *= scratch0;
        thirdZ *= scratch1;
    }
    maxX = startX;
    maxY = startY;
    maxZ = startZ;
    minX = startX;
    minY = startY;
    minZ = startZ;
    if (endX < minX) {
        minX = endX;
    } else {
        maxX = endX;
    }
    if (endY < startY) {
        minY = endY;
    } else {
        maxY = endY;
    }
    if (endZ < startZ) {
        minZ = endZ;
    } else {
        maxZ = endZ;
    }
    if (((firstZ < minZ) && (secondZ < minZ) && (thirdZ < minZ)) || ((maxZ < firstZ) && (maxZ < secondZ) && (maxZ < thirdZ)) || ((firstY < minY) && (secondY < minY) && (thirdY < minY)) || ((maxY < firstY) && (maxY < secondY) && (maxY < thirdY)) || ((firstX < minX) && (secondX < minX) && (thirdX < minX)) || ((maxX < firstX) && (maxX < secondX) && (maxX < thirdX))) {
        return 0;
    }
    firstEdge.x = secondX - firstX;
    secondEdge.x = thirdX - firstX;
    firstEdge.y = secondY - firstY;
    secondEdge.y = thirdY - firstY;
    firstEdge.z = secondZ - firstZ;
    secondEdge.z = thirdZ - firstZ;
    sUvFvecExports->uvVec3FCross(normal, &firstEdge, &secondEdge);
    sUvFvecExports->uvVec3FNormalize(normal, normal);
    planeNumerator = ((firstX - startX) * normal->x) + ((firstY - startY) * normal->y) + ((firstZ - startZ) * normal->z);
    planeDenominator = ((endX - startX) * normal->x) + ((endY - startY) * normal->y) + ((endZ - startZ) * normal->z);
    if (planeDenominator != 0.0f) {
        scratch0 = planeNumerator / planeDenominator;
    } else {
        return 0;
    }
    if ((scratch0 < 0.0f) || (scratch0 > 1.0f)) {
        return 0;
    }
    if (FABS(normal->z) < 0.1f) {
        if (uvIntersectPointInOrientedTriangle3D(((endX - startX) * scratch0) + startX,
                                          ((endY - startY) * scratch0) + startY,
                                          ((endZ - startZ) * scratch0) + startZ,
                                          normal->x, normal->y, normal->z,
                                          firstX, firstY, firstZ, secondX,
                                          secondY, secondZ, thirdX, thirdY, thirdZ) != 0) {
            *fraction = scratch0;
            return 1;
        }
        *fraction = 0.0f;
        return 0;
    }
    if (normal->z > 0.0f) {
        if (uvIntersectPointInPositiveWindingTriangle2D(((endX - startX) * scratch0) + startX, ((endY - startY) * scratch0) + startY,
                                          firstX, firstY, secondX,
                                          secondY, thirdX, thirdY, 1.0f) != 0) {
            *fraction = scratch0;
            return 1;
        }
        *fraction = 0.0f;
        return 0;
    }
    if (uvIntersectPointInNegativeWindingTriangle2D(((endX - startX) * scratch0) + startX, ((endY - startY) * scratch0) + startY,
                                      firstX, firstY, secondX, secondY,
                                      thirdX, thirdY, 1.0f) != 0) {
        *fraction = scratch0;
        return 1;
    }
    *fraction = 0.0f;
    return 0;
}
#line 568 "src/modules/uvintersect_rom.c"


#line 570 "src/modules/uvintersect_rom.c"
/* Test whether the segment XY bounds overlap the caller rectangle.
 * Endpoints may be in either order and touching bounds count as overlap.
 * This bounds test does not prove the line itself crosses the rectangle. */
s32 uvIntersectSegmentBoundsOverlapRectangle(f32 startX, f32 startY, f32 endX, f32 endY, f32 minX, f32 maxX, f32 minY, f32 maxY) {
    if (startX < endX) {
        if (endX < minX) {
            return FALSE;
        }
        if (maxX < startX) {
            return FALSE;
        }
    } else {
        if (startX < minX) {
            return FALSE;
        }
        if (maxX < endX) {
            return FALSE;
        }
    }
    if (startY < endY) {
        if (endY < minY) {
            return FALSE;
        }
        if (maxY < startY) {
            return FALSE;
        }
    } else {
        if (startY < minY) {
            return FALSE;
        }
        if (maxY < endY) {
            return FALSE;
        }
    }
    return TRUE;
}
#line 603 "src/modules/uvintersect_rom.c"

#line 604 "src/modules/uvintersect_rom.c"
/* Adjust both XY endpoints to the rectangle using the original slope
 * and intercept arithmetic, with a separate vertical-segment path. Preserve
 * store order and pointer aliasing; the routine returns no rejection status. */
void uvIntersectClipSegmentToRectangleBounds(f32* startX, f32* startY, f32* endX, f32* endY, f32 minX, f32 maxX, f32 minY, f32 maxY) {
    f32 slope;
    f32 intercept;
    f32 x1;
    f32 y1;
    f32 x0;
    f32 y0;

    x0 = *startX;
    y0 = *startY;
    x1 = *endX;
    y1 = *endY;
    if (x1 == x0) {
        if (x0 < minX) {
            x1 = minX;
            x0 = minX;
        } else if (maxX < x0) {
            x1 = maxX;
            x0 = maxX;
        }
        if (y0 < minY) {
            y0 = minY;
        } else if (maxY < y0) {
            y0 = maxY;
        }
        if (y1 < minY) {
            y1 = minY;
        } else if (maxY < y1) {
            y1 = maxY;
        }
        *startX = x0;
        *startY = y0;
        *endX = x1;
        *endY = y1;
    } else {
        slope = (y1 - y0) / (x1 - x0);
        intercept = y1 - (slope * x1);
        if (x0 < minX) {
            y0 = (slope * minX) + intercept;
            x0 = minX;
        } else if (maxX < x0) {
            y0 = (slope * maxX) + intercept;
            x0 = maxX;
        }
        if (y0 < minY) {
            y0 = minY;
            if (slope != 0.0f) {
                x0 = (minY - intercept) / slope;
            }
        } else if (maxY < y0) {
            y0 = maxY;
            if (slope != 0.0f) {
                x0 = (maxY - intercept) / slope;
            }
        }
        if (x1 < minX) {
            x1 = minX;
            y1 = (slope * minX) + intercept;
        } else if (maxX < x1) {
            x1 = maxX;
            y1 = (slope * maxX) + intercept;
        }
        if (y1 < minY) {
            y1 = minY;
            if (slope != 0.0f) {
                x1 = (minY - intercept) / slope;
            }
        } else if (maxY < y1) {
            y1 = maxY;
            if (slope != 0.0f) {
                x1 = (maxY - intercept) / slope;
            }
        }
        *startX = x0;
        *startY = y0;
        *endX = x1;
        *endY = y1;
    }
}
#line 683 "src/modules/uvintersect_rom.c"

#line 684 "src/modules/uvintersect_rom.c"
/* Clip XY endpoints using the original line arithmetic and interpolate
 * their Z values from the original deltas when the line is nonvertical.
 * RE_ORIGINAL_QUIRK: the vertical path writes only XY, leaving both caller
 * Z values untouched. Preserve original aliasing and interpolation precedence. */
void uvIntersectClipSegmentDepthToRectangleBounds(f32* startX, f32* startY, f32* startZ, f32* endX, f32* endY, f32* endZ, f32 minX, f32 maxX, f32 minY, f32 maxY) {
    f32 intercept;
    f32 slope;
    f32 x0;
    f32 x1;
    f32 y0;
    f32 y1;
    f32 z0;
    f32 z1;
    f32 dx;
    f32 dy;
    f32 dz;

    // clang-format off
    x0 = *startX; \
    y0 = *startY; \
    z0 = *startZ;    \
    x1 = *endX; \
    y1 = *endY; \
    z1 = *endZ;
    // clang-format on

    dx = x1 - x0;
    dy = y1 - y0;
    dz = z1 - z0;

    if (x1 == x0) {
        if (x0 < minX) {
            x1 = minX;
            x0 = minX;
        } else if (maxX < x0) {
            x1 = maxX;
            x0 = maxX;
        }
        if (y0 < minY) {
            y0 = minY;
        } else if (maxY < y0) {
            y0 = maxY;
        }
        if (y1 < minY) {
            y1 = minY;
        } else if (maxY < y1) {
            y1 = maxY;
        }
        *startX = x0;
        *startY = y0;
        *endX = x1;
        *endY = y1;
    } else {
        slope = (y1 - y0) / (x1 - x0);
        intercept = y1 - (slope * x1);
        if (x0 < minX) {
            y0 = (slope * minX) + intercept;
            x0 = minX;
        } else if (maxX < x0) {
            y0 = (slope * maxX) + intercept;
            x0 = maxX;
        }
        if (y0 < minY) {
            y0 = minY;
            if (slope != 0.0f) {
                x0 = (minY - intercept) / slope;
            }
        } else if (maxY < y0) {
            y0 = maxY;
            if (slope != 0.0f) {
                x0 = (maxY - intercept) / slope;
            }
        }
        if (x1 < minX) {
            y1 = (slope * minX) + intercept;
            x1 = minX;
        } else if (maxX < x1) {
            y1 = (slope * maxX) + intercept;
            x1 = maxX;
        }
        if (y1 < minY) {
            y1 = minY;
            if (slope != 0.0f) {
                x1 = (minY - intercept) / slope;
            }
        } else if (maxY < y1) {
            y1 = maxY;
            if (slope != 0.0f) {
                x1 = (maxY - intercept) / slope;
            }
        }

        if ((x0 != *startX) && (dx != 0.0f)) {
            z0 += dz * ((x0 - *startX) / dx);
        } else if ((y0 != *startY) && (dy != 0.0f)) {
            z0 += dz * ((y0 - *startY) / dy);
        }
        if ((x1 != *endX) && (dx != 0.0f)) {
            z1 += dz * ((x1 - *endX) / dx);
        } else if ((y1 != *endY) && (dy != 0.0f)) {
            z1 += dz * ((y1 - *endY) / dy);
        }
        *startX = x0;
        *startY = y0;
        *startZ = z0;
        *endX = x1;
        *endY = y1;
        *endZ = z1;
    }
}
#line 790 "src/modules/uvintersect_rom.c"

void func_uvintersect_rom_004020A0(Mtx4F *arg0, s16 arg1, Vec3F *arg2) {
    s32 c = (s32) arg1;
    switch (c) {
        case -1:
            arg2->x = -arg0->m[0][0];
            arg2->y = -arg0->m[0][1];
            arg2->z = -arg0->m[0][2];
            break;

        case 1:
            arg2->x = arg0->m[0][0];
            arg2->y = arg0->m[0][1];
            arg2->z = arg0->m[0][2];
            break;

        case -2:
            arg1++; // FAKE
            arg1--;
            arg2->x = -arg0->m[1][0];
            arg2->y = -arg0->m[1][1];
            arg2->z = -arg0->m[1][2];
            break;

        case 2:
            arg2->x = arg0->m[1][0];
            arg2->y = arg0->m[1][1];
            arg2->z = arg0->m[1][2];
            break;

        case -3:
            arg2->x = -arg0->m[2][0];
            arg2->y = -arg0->m[2][1];
            arg2->z = -arg0->m[2][2];
            break;

        case 3:
            arg2->x = arg0->m[2][0];
            arg2->y = arg0->m[2][1];
            arg2->z = arg0->m[2][2];
            break;

        default:
            break;
    }
}

#line 837 "src/modules/uvintersect_rom.c"
/* Reject separated segment/triangle bounds, intersect the segment
 * with the caller-supplied plane normal and test the point against triangle
 * edges. XY winding is used unless the normal is nearly horizontal.
 * RE_ORIGINAL_QUIRK: the plane fraction is stored before range and triangle
 * tests, so rejected hits may still update the fraction. */
s32 uvIntersectSegmentTriangleWithNormal(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 firstX, f32 firstY, f32 firstZ, f32 secondX, f32 secondY, f32 secondZ, f32 thirdX, f32 thirdY, f32 thirdZ, f32* fraction, Vec3F* normal) {
    f32 planeDenominator;
    f32 lowerBound;
    f32 planeFraction;
    f32 upperBound;
    f32 planeNumerator;
    s32 unusedWords[7];

    if (startX < endX) {
        lowerBound = startX;
        upperBound = endX;
    } else {
        lowerBound = endX;
        upperBound = startX;
    }
    if (((firstX < lowerBound) &&
         (secondX < lowerBound) && (thirdX < lowerBound)) ||
        ((upperBound < firstX) && (upperBound < secondX) &&
         (upperBound < thirdX))) {
        return 0;
    }
    if (startY < endY) {
        lowerBound = startY;
        upperBound = endY;
    } else {
        lowerBound = endY;
        upperBound = startY;
    }
    if (((firstY < lowerBound) && (secondY < lowerBound) &&
         (thirdY < lowerBound)) || ((upperBound < firstY) &&
        (upperBound < secondY) && (upperBound < thirdY))) {
        return 0;
    }
    if (startZ < endZ) {
        lowerBound = startZ;
        upperBound = endZ;
    } else {
        lowerBound = endZ;
        upperBound = startZ;
    }
    if (((firstZ < lowerBound) && (secondZ < lowerBound) && (thirdZ < lowerBound)) ||
        ((upperBound < firstZ) && (upperBound < secondZ) && (upperBound < thirdZ))) {
        return 0;
    }

    planeNumerator = ((firstX - startX) * normal->x) + ((firstY - startY) * normal->y) + ((firstZ - startZ) * normal->z);
    planeDenominator = ((endX - startX) * normal->x) + ((endY - startY) * normal->y) + ((endZ - startZ) * normal->z);
    if (planeDenominator == 0.0f) {
        return 0;
    }
    planeFraction = planeNumerator / planeDenominator;
    *fraction = planeFraction;

    if ((planeFraction < 0.0f) || (planeFraction > 1.0f)) {
        return 0;
    }

    if ((ABS_2(normal->z) < 0.1f)) {
        if (uvIntersectPointInOrientedTriangle3D(((endX - startX) * planeFraction) + startX, ((endY - startY) * planeFraction) + startY,
                                          ((endZ - startZ) * planeFraction) + startZ, normal->x, normal->y,
                                          normal->z, firstX, firstY, firstZ, secondX, secondY,
                                          secondZ, thirdX, thirdY, thirdZ) != 0) {
            return 1;
        }
        return 0;
    }
    if (normal->z > 0.0f) {
        if (uvIntersectPointInPositiveWindingTriangle2D(((endX - startX) * planeFraction) + startX, ((endY - startY) * planeFraction) + startY,
                                          firstX, firstY, secondX, secondY, thirdX, thirdY, 1.0f) != 0) {
            return 1;
        }
        return 0;
    }
    if (uvIntersectPointInNegativeWindingTriangle2D(((endX - startX) * planeFraction) + startX, ((endY - startY) * planeFraction) + startY, firstX,
                                      firstY, secondX, secondY, thirdX, thirdY, 1.0f) != 0) {
        return 1;
    }
    return 0;
}
#line 916 "src/modules/uvintersect_rom.c"

