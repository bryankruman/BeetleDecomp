// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void uvUnloadModule(s32 tag);                                 /* extern */

void uvFvecModuleCleanup(void);
void uvVec2FAdd(Vec2F *vdst, Vec2F *va, Vec2F *vb);
void uvVec2FAdd(Vec2F *vdst, Vec2F *va, Vec2F *vb);
void uvVec2FAddScaled(Vec2F *vdst, Vec2F *va, f32 sb, Vec2F *vb);
void uvVec2FAddScaled(Vec2F *vdst, Vec2F *va, f32 sb, Vec2F *vb);
void uvVec2FCopy(Vec2F *va, Vec2F *vb);
void uvVec2FCopy(Vec2F *va, Vec2F *vb);
f32 uvVec2FDot(Vec2F *va, Vec2F *vb);
f32 uvVec2FDot(Vec2F *va, Vec2F *vb);
s32 uvVec2FIsZero(Vec2F *v);
f32 uvVec2FLen(Vec2F *v);
f32 uvVec2FLengthSquared(Vec2F *v);
f32 uvVec2FLengthSquared(Vec2F *arg0);
void uvVec2FNegate(Vec2F *vdst, Vec2F *vsrc);
s32 uvVec2FNormalize(Vec2F *va, Vec2F *vb);
void uvVec2FReflect(Vec2F *va, Vec2F *vb, Vec2F *vc, f32 factor);
f32 uvVec2FScalarProj(Vec2F *arg0, Vec2F *arg1);
void uvVec2FScale(Vec2F *vdst, Vec2F *va, f32 sb);
void uvVec2FScale(Vec2F *vdst, Vec2F *va, f32 sb);
void uvVec2FSet(Vec2F *vd, f32 x, f32 y);
void uvVec2FSub(Vec2F *vdst, Vec2F *va, Vec2F *vb);
void uvVec2FSub(Vec2F *vdst, Vec2F *va, Vec2F *vb);
void uvVec3FAdd(Vec3F *vdst, Vec3F *va, Vec3F *vb);
void uvVec3FAdd(Vec3F *vdst, Vec3F *va, Vec3F *vb);
void uvVec3FAddScaled(Vec3F *vdst, Vec3F *va, f32 sb, Vec3F *vb);
void uvVec3FAddScaled(Vec3F *vdst, Vec3F *va, f32 sb, Vec3F *vb);
void uvVec3FCopy(Vec3F *vdst, Vec3F *vsrc);
void uvVec3FCross(Vec3F *vd, Vec3F *va, Vec3F *vb);
void uvVec3FCross(Vec3F *arg0, Vec3F *arg1, Vec3F *arg2);
f32 uvVec3FDistance(Vec3F *va, Vec3F *vb);
f32 uvVec3FDistance(Vec3F *arg0, Vec3F *arg1);
f32 uvVec3FDot(Vec3F *va, Vec3F *vb);
s32 uvVec3FIsZero(Vec3F *v);
f32 uvVec3FLen(Vec3F *v);
f32 uvVec3FLengthSquared(Vec3F *v);
f32 uvVec3FLengthSquared(Vec3F *vec);
void uvVec3FMult(Vec3F *vdst, Vec3F *va, Vec3F *vb);
void uvVec3FMult(Vec3F *vdst, Vec3F *va, Vec3F *vb);
void uvVec3FNegate(Vec3F *va, Vec3F *vb);
s32 uvVec3FNormalize(Vec3F *vd, Vec3F *vs);
s32 uvVec3FNormalize(Vec3F *vd, Vec3F *vs);
f32 uvVec3FScalarProj(Vec3F *arg0, Vec3F *arg1);
void uvVec3FScale(Vec3F *vdst, Vec3F *va, f32 scale);
void uvVec3FSet(Vec3F *vec, f32 x, f32 y, f32 z);
void uvVec3FSphereAngles(f32 *azimuth, f32 *elevation, Vec3F *v);
void uvVec3FSub(Vec3F *vdst, Vec3F *va, Vec3F *vb);
void uvVec3FSub(Vec3F *vdst, Vec3F *va, Vec3F *vb);
void uvVec3fFromSpherical(Vec3F *arg0, f32 arg1, f32 arg2);

void __entrypoint_func_uvfvec_rom_400000(UvFVec_Rom_Exports* exports);

// .bss
static UvMath_Exports* sUvMathRomExports;

s32 D_uvfvec_rom_00400BB0[] = {0x00840000, __entrypoint_func_uvfvec_rom_400000, 0, 0};

void __entrypoint_func_uvfvec_rom_400000(UvFVec_Rom_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvVec3FSet = uvVec3FSet;
    exports->uvVec3FNormalize = uvVec3FNormalize;
    exports->uvVec3FLen = uvVec3FLen;
    exports->uvVec3FLenSquared = uvVec3FLengthSquared;
    exports->uvVec3FDistance = uvVec3FDistance;
    exports->uvVec3FDot = uvVec3FDot;
    exports->uvVec3FCopy = uvVec3FCopy;
    exports->uvVec3FScalarProj = uvVec3FScalarProj;
    exports->uvVec3FCross = uvVec3FCross;
    exports->uvFvecModuleCleanup = uvFvecModuleCleanup;
    exports->uvVec3FAdd = uvVec3FAdd;
    exports->uvVec2FNormalize = uvVec2FNormalize;
    exports->uvVec3FMult = uvVec3FMult;
    exports->uvVec2FIsZero = uvVec2FIsZero;
    exports->uvVec2FLen = uvVec2FLen;
    exports->uvVec3FAddScaled = uvVec3FAddScaled;
    exports->uvVec2FNegate = uvVec2FNegate;
    exports->uvVec2FLenSquared = uvVec2FLengthSquared;
    exports->uvVec3FSub = uvVec3FSub;
    exports->uvVec2FReflect = uvVec2FReflect;
    exports->uvVec2FDot = uvVec2FDot;
    exports->uvVec3FScale = uvVec3FScale;
    exports->uvVec2FCopy = uvVec2FCopy;
    exports->uvVec3FSphereAngles = uvVec3FSphereAngles;
    exports->uvVec2FScalarProj = uvVec2FScalarProj;
    exports->uvVec3FFromSpherical = uvVec3fFromSpherical;
    exports->uvVec2FAdd = uvVec2FAdd;
    exports->uvVec3FIsZero = uvVec3FIsZero;
    exports->uvVec2FAddScaled = uvVec2FAddScaled;
    exports->uvVec3FNegate = uvVec3FNegate;
    exports->uvVec2FSub = uvVec2FSub;
    exports->uvVec2FSet = uvVec2FSet;
    exports->uvVec2FScale = uvVec2FScale;
    #line 2
    sUvMathRomExports = uvLoadModule('MATH');
}

void uvFvecModuleCleanup(void) {
    uvUnloadModule('MATH'); // Unload math module
}

void uvVec3FSet(Vec3F *vec, f32 x, f32 y, f32 z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

#line 112 "src/modules/uvfvec_rom.c"
/* Normalize the source into destination and report success. A zero
 * source leaves destination untouched. Cache source coordinates before
 * writes so an in-place request retains the original behavior. */
s32 uvVec3FNormalize(Vec3F* destination, Vec3F* source) {
    f32 sourceX;
    f32 sourceY;
    f32 sourceZ;
    f32 lengthOrReciprocal;

    sourceX = source->x;
    sourceY = source->y;
    sourceZ = source->z;
    lengthOrReciprocal = sUvMathRomExports->uvSqrtf(SQ(sourceX) + SQ(sourceY) + SQ(sourceZ));
    if (lengthOrReciprocal == 0.0f) {
        return FALSE;
    }
    lengthOrReciprocal = 1.0f / lengthOrReciprocal;
    destination->x = sourceX * lengthOrReciprocal;
    destination->y = sourceY * lengthOrReciprocal;
    destination->z = sourceZ * lengthOrReciprocal;
    return TRUE;
}
#line 131 "src/modules/uvfvec_rom.c"

f32 uvVec3FLen(Vec3F *v) {
    return sUvMathRomExports->uvSqrtf(uvVec3FLengthSquared(v));
}

#line 136 "src/modules/uvfvec_rom.c"

f32 uvVec3FLengthSquared(Vec3F* vector) {
    return SQ(vector->x) + SQ(vector->y) + SQ(vector->z);
}
#line 139 "src/modules/uvfvec_rom.c"

f32 uvVec3FDistance(Vec3F *first, Vec3F *second) {
    Vec3F difference; /* RE_UNKNOWN: caller storage/alias/FP contracts and historical MATH/kernel declarations need further evidence. */

    uvVec3FSub(&difference, first, second);
    return sUvMathRomExports->uvSqrtf(uvVec3FLengthSquared(&difference)); /* Preserve Sub, length-squared, then live MATH slot 4 dispatch. */
}

f32 uvVec3FDot(Vec3F* va, Vec3F* vb) {
    return (va->x * vb->x) + (va->y * vb->y) + (va->z * vb->z);
}

void uvVec3FCopy(Vec3F *destination, Vec3F *source) {
    destination->x = source->x; /* Retain each source load before its destination store. */
    destination->y = source->y;
    destination->z = source->z; /* RE_UNKNOWN: caller storage, overlap and lifetime need caller/allocation evidence. */
}

#line 157 "src/modules/uvfvec_rom.c"
/* Return the dot product divided by both vector lengths: the cosine
 * of their angle for nonzero vectors. Keep the established export name.
 * RE_ORIGINAL_QUIRK: zero-length vectors are not guarded. */
f32 uvVec3FScalarProj(Vec3F* first, Vec3F* second) {
    f32 firstLength;
    f32 dotProduct;

    dotProduct = uvVec3FDot(first, second);
    firstLength = uvVec3FLen(first);
    return dotProduct / (uvVec3FLen(second) * firstLength);
}
#line 165 "src/modules/uvfvec_rom.c"

#line 166 "src/modules/uvfvec_rom.c"
/* Compute the first vector cross the second vector. Cache all six
 * source components before storing so either source may be destination. */
void uvVec3FCross(Vec3F* destination, Vec3F* first, Vec3F* second) {
    f32 ax = first->x, ay = first->y, az = first->z;
    f32 bx = second->x, by = second->y, bz = second->z;

    destination->x = ((ay * bz) - (az * by));
    destination->y = -((ax * bz) - (az * bx));
    destination->z = ((ax * by) - (ay * bx));
}
#line 174 "src/modules/uvfvec_rom.c"

void uvVec3FAdd(Vec3F *destination, Vec3F *first, Vec3F *second) {
    destination->x = first->x + second->x; /* Component-wise f32 sum; retain operand/store order. */
    destination->y = first->y + second->y;
    destination->z = first->z + second->z; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

void uvVec3FMult(Vec3F *destination, Vec3F *first, Vec3F *second) {
    destination->x = first->x * second->x; /* Component-wise product; retain interleaved reads/stores. */
    destination->y = first->y * second->y;
    destination->z = first->z * second->z; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

#line 187 "src/modules/uvfvec_rom.c"
/* Add the first vector to scale times the second vector component by
 * component, preserving evaluation order and in-place destination support. */
void uvVec3FAddScaled(Vec3F *destination, Vec3F *first, f32 scale, Vec3F *second) {
    destination->x = first->x + (scale * second->x);
    destination->y = first->y + (scale * second->y);
    destination->z = first->z + (scale * second->z);
}
#line 192 "src/modules/uvfvec_rom.c"

void uvVec3FSub(Vec3F *destination, Vec3F *first, Vec3F *second) {
    s32 pad; /* RE_UNKNOWN: historical purpose of this unused local needs original source. */
    destination->x = first->x - second->x;
    destination->y = first->y - second->y;
    destination->z = first->z - second->z; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved; retain interleaving. */
}

void uvVec3FScale(Vec3F *destination, Vec3F *source, f32 scale) {
    destination->x = source->x * scale; /* Retain f32 products and component store order. */
    destination->y = source->y * scale;
    destination->z = source->z * scale; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

#line 206 "src/modules/uvfvec_rom.c"
/* Normalize the caller vector in place, then compute azimuth from
 * atan2(-X, Y) and elevation from arcsine(Z), in radians. Preserve the
 * original ignored normalization result for a zero input vector. */
void uvVec3FSphereAngles(f32 *azimuth, f32 *elevation, Vec3F *vector) {
    uvVec3FNormalize(vector, vector);
    *azimuth = sUvMathRomExports->uvAtan2F(-vector->x, vector->y);
    *elevation = sUvMathRomExports->uvArcSinF(vector->z);
}
#line 211 "src/modules/uvfvec_rom.c"

#line 212 "src/modules/uvfvec_rom.c"
/* Build a unit direction from azimuth and elevation in radians using
 * the original -sin(azimuth), cos(azimuth) XY convention. Preserve angle
 * wrapping, hemisphere handling and exact-pole branches. */
void uvVec3fFromSpherical(Vec3F* destination, f32 azimuth, f32 elevation) {
    f32 x;
    f32 y;
    s32 pad1C;
    f32 cosineElevation;
    f32 absoluteElevation;
    f32 z;

    if (elevation > 0.0f) {
        absoluteElevation = elevation;
    } else {
        absoluteElevation = -elevation;
    }
    if (absoluteElevation < 1.5707963f) {
        cosineElevation = sUvMathRomExports->uvCosF(elevation);
        x = -sUvMathRomExports->uvSinF(azimuth) * cosineElevation;
        y = sUvMathRomExports->uvCosF(azimuth) * cosineElevation;
        z = sUvMathRomExports->uvSinF(elevation);
    } else if (1.5707963f < absoluteElevation) {
        while (elevation > 3.1415927f) {
            elevation -= 6.2831855f;
        }

        while (elevation < -3.1415927f) {
            elevation += 6.2831855f;
        }

        if (1.5707963f < elevation) {
            elevation = 1.5707963f - elevation;
        }
        if (elevation < -1.5707963f) {
            elevation = -1.5707963f - elevation;
        }

        cosineElevation = sUvMathRomExports->uvCosF(elevation);
        x = sUvMathRomExports->uvSinF(azimuth) * cosineElevation;
        y = -sUvMathRomExports->uvCosF(azimuth) * cosineElevation;
        z = sUvMathRomExports->uvSinF(elevation);
    } else {
        y = 0;
        x = 0;
        if (elevation > 0) {
            z = 1.0f;
        } else {
            z = -1.0f;
        }
    }
    uvVec3FSet(destination, x, y, z);
}
#line 261 "src/modules/uvfvec_rom.c"

s32 uvVec3FIsZero(Vec3F *v) {
    if ((v->x == 0.0) && (v->y == 0.0) && (v->z == 0.0)) {
        return TRUE;
    }
    return FALSE;
}

void uvVec3FNegate(Vec3F* va, Vec3F *vb) {
    va->x = -vb->x;
    va->y = -vb->y;
    va->z = -vb->z;
}

void uvVec2FSet(Vec2F *vd, f32 x, f32 y) {
    vd->x = x;
    vd->y = y;
}

#line 280 "src/modules/uvfvec_rom.c"
/* Normalize the two source components into destination using direct
 * division by their length. A zero source leaves destination untouched
 * and returns false; cached components support an in-place request. */
s32 uvVec2FNormalize(Vec2F* destination, Vec2F* source) {
    f32 sourceX;
    f32 sourceY;
    f32 length;

    sourceX = source->x;
    sourceY = source->y;
    length = sUvMathRomExports->uvSqrtf(SQ(sourceX) + SQ(sourceY));
    if (length == 0.0f) {
        return FALSE;
    }
    destination->x = sourceX / length;
    destination->y = sourceY / length;
    return TRUE;
}
#line 295 "src/modules/uvfvec_rom.c"

f32 uvVec2FLen(Vec2F *v) {
    return sUvMathRomExports->uvSqrtf(uvVec2FLengthSquared(v));
}

#line 300 "src/modules/uvfvec_rom.c"

f32 uvVec2FLengthSquared(Vec2F *vector) {
    return SQ(vector->x) + SQ(vector->y);
}
#line 303 "src/modules/uvfvec_rom.c"

f32 uvVec2FDot(Vec2F *va, Vec2F *vb) {
    return (va->x * vb->x) + (va->y * vb->y);
}

void uvVec2FCopy(Vec2F *destination, Vec2F *source) {
    destination->x = source->x; /* Preserve the first store before reading source->y. */
    destination->y = source->y; /* RE_UNKNOWN: caller partial-overlap and storage/lifetime contracts remain unproved. */
}

#line 313 "src/modules/uvfvec_rom.c"
/* Return the dot product divided by both vector lengths: the cosine
 * of their angle for nonzero vectors. Keep the established export name.
 * RE_ORIGINAL_QUIRK: zero-length vectors are not guarded. */
f32 uvVec2FScalarProj(Vec2F* first, Vec2F* second) {
    f32 firstLength;
    f32 dotProduct;

    dotProduct = uvVec2FDot(first, second);
    firstLength = uvVec2FLen(first);
    return dotProduct / (uvVec2FLen(second) * firstLength);
}
#line 321 "src/modules/uvfvec_rom.c"

void uvVec2FAdd(Vec2F *vdst, Vec2F *va, Vec2F *vb) {
    vdst->x = va->x + vb->x;
    vdst->y = va->y + vb->y;
}

#line 327 "src/modules/uvfvec_rom.c"
/* Add the first vector to scale times the second vector component by
 * component, preserving evaluation order and in-place destination support. */
void uvVec2FAddScaled(Vec2F *destination, Vec2F *first, f32 scale, Vec2F *second) {
    destination->x = first->x + (scale * second->x);
    destination->y = first->y + (scale * second->y);
}
#line 331 "src/modules/uvfvec_rom.c"

void uvVec2FSub(Vec2F *destination, Vec2F *first, Vec2F *second) {
    destination->x = first->x - second->x; /* Component-wise first minus second; retain operand order. */
    destination->y = first->y - second->y; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

void uvVec2FScale(Vec2F *destination, Vec2F *source, f32 scale) {
    destination->x = source->x * scale; /* Retain f32 products and interleaved reads/stores. */
    destination->y = source->y * scale; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

s32 uvVec2FIsZero(Vec2F *v) {
    if ((v->x == 0.0) && (v->y == 0.0)) {
        return TRUE;
    }
    return FALSE;
}

void uvVec2FNegate(Vec2F *destination, Vec2F *source) {
    destination->x = -source->x; /* Retain unary f32 negation and component store order. */
    destination->y = -source->y; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

#line 354 "src/modules/uvfvec_rom.c"
/* Subtract normal * dot(normal, incident) * (1 + factor) from incident.
 * The supplied normal is not normalized here; factor one gives the
 * usual reflection for a unit normal. Preserve the temporary for aliasing. */
void uvVec2FReflect(Vec2F* destination, Vec2F* normal, Vec2F* incident, f32 factor) {
    UNUSED s32 pad;
    Vec2F normalComponent;

    uvVec2FScale(&normalComponent, normal, uvVec2FDot(normal, incident) * (1.0f + factor));
    uvVec2FSub(destination, incident, &normalComponent);
}
#line 361 "src/modules/uvfvec_rom.c"
