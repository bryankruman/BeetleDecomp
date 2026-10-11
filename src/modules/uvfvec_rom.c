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

/*
 * Publish the existing two- and three-component vector operations and cleanup
 * entry, preserving the separate length-squared export aliases. Import MATH
 * after filling the export slots; no vector storage is allocated here.
 * RE_UNKNOWN: Writable export-table extent, MATH lifetime and repeated module
 * initialization require the loader; imported provider failure is unchecked.
 */
#line 63 "src/modules/uvfvec_rom.c"
void __entrypoint_func_uvfvec_rom_400000(UvFVec_Rom_Exports* moduleExports) {
    uvUpdateFileAllocPtr(moduleExports);
    moduleExports->uvVec3FSet = uvVec3FSet;
    moduleExports->uvVec3FNormalize = uvVec3FNormalize;
    moduleExports->uvVec3FLen = uvVec3FLen;
    moduleExports->uvVec3FLenSquared = uvVec3FLengthSquared;
    moduleExports->uvVec3FDistance = uvVec3FDistance;
    moduleExports->uvVec3FDot = uvVec3FDot;
    moduleExports->uvVec3FCopy = uvVec3FCopy;
    moduleExports->uvVec3FScalarProj = uvVec3FScalarProj;
    moduleExports->uvVec3FCross = uvVec3FCross;
    moduleExports->uvFvecModuleCleanup = uvFvecModuleCleanup;
    moduleExports->uvVec3FAdd = uvVec3FAdd;
    moduleExports->uvVec2FNormalize = uvVec2FNormalize;
    moduleExports->uvVec3FMult = uvVec3FMult;
    moduleExports->uvVec2FIsZero = uvVec2FIsZero;
    moduleExports->uvVec2FLen = uvVec2FLen;
    moduleExports->uvVec3FAddScaled = uvVec3FAddScaled;
    moduleExports->uvVec2FNegate = uvVec2FNegate;
    moduleExports->uvVec2FLenSquared = uvVec2FLengthSquared;
    moduleExports->uvVec3FSub = uvVec3FSub;
    moduleExports->uvVec2FReflect = uvVec2FReflect;
    moduleExports->uvVec2FDot = uvVec2FDot;
    moduleExports->uvVec3FScale = uvVec3FScale;
    moduleExports->uvVec2FCopy = uvVec2FCopy;
    moduleExports->uvVec3FSphereAngles = uvVec3FSphereAngles;
    moduleExports->uvVec2FScalarProj = uvVec2FScalarProj;
    moduleExports->uvVec3FFromSpherical = uvVec3fFromSpherical;
    moduleExports->uvVec2FAdd = uvVec2FAdd;
    moduleExports->uvVec3FIsZero = uvVec3FIsZero;
    moduleExports->uvVec2FAddScaled = uvVec2FAddScaled;
    moduleExports->uvVec3FNegate = uvVec3FNegate;
    moduleExports->uvVec2FSub = uvVec2FSub;
    moduleExports->uvVec2FSet = uvVec2FSet;
    moduleExports->uvVec2FScale = uvVec2FScale;
    #line 2
    sUvMathRomExports = uvLoadModule('MATH');
}
/* Unload the MATH module. The stored math-provider pointer is not cleared here.  * RE_UNKNOWN: loader reference ownership and outstanding vector operations must  * be coordinated by callers; this body performs no vector-storage cleanup. */
void uvFvecModuleCleanup(void) {
    uvUnloadModule('MATH'); // Unload math module
}

void uvVec3FSet(Vec3F *destination, f32 x, f32 y, f32 z) {
    destination->x = x; /* Store supplied f32 components in x/y/z order. */
    destination->y = y;
    destination->z = z; /* RE_UNKNOWN: destination extent/alias/lifetime need caller/allocation evidence. */
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

f32 uvVec3FLen(Vec3F *vector) { /* RE_UNKNOWN: storage/FP and MATH lifetime need caller/loader/kernel evidence. */
    return sUvMathRomExports->uvSqrtf(uvVec3FLengthSquared(vector)); /* Squared length, then live MATH slot04. */
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

f32 uvVec3FDot(Vec3F* first, Vec3F* second) { /* RE_UNKNOWN: storage/lifetime and FP contracts need caller/FP evidence. */
    return (first->x * second->x) + (first->y * second->y) + (first->z * second->z); /* Retain (x product + y product) + z product. */
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

s32 uvVec3FIsZero(Vec3F *vector) { /* Exact x/y/z zero test; retain short circuit and f64 promotion. */
    if ((vector->x == 0.0) && (vector->y == 0.0) && (vector->z == 0.0)) {
        return TRUE;
    }
    return FALSE; /* RE_UNKNOWN: storage/lifetime and FP traps need caller/FP evidence. */
}

void uvVec3FNegate(Vec3F* destination, Vec3F *source) {
    destination->x = -source->x; /* Retain unary f32 negation and component store order. */
    destination->y = -source->y;
    destination->z = -source->z; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
}

void uvVec2FSet(Vec2F *destination, f32 x, f32 y) {
    destination->x = x; /* Store supplied f32 components in x/y order. */
    destination->y = y; /* RE_UNKNOWN: destination extent/alias/lifetime need caller/allocation evidence. */
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

f32 uvVec2FLen(Vec2F *vector) { /* RE_UNKNOWN: storage/FP and MATH lifetime need caller/loader/kernel evidence. */
    return sUvMathRomExports->uvSqrtf(uvVec2FLengthSquared(vector)); /* Squared length, then live MATH slot04. */
}

#line 300 "src/modules/uvfvec_rom.c"

f32 uvVec2FLengthSquared(Vec2F *vector) {
    return SQ(vector->x) + SQ(vector->y);
}
#line 303 "src/modules/uvfvec_rom.c"

f32 uvVec2FDot(Vec2F *first, Vec2F *second) {
    return (first->x * second->x) + (first->y * second->y); /* Keep f32 product grouping. RE_UNKNOWN: caller storage/lifetime and FP contracts. */
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

void uvVec2FAdd(Vec2F *destination, Vec2F *first, Vec2F *second) {
    destination->x = first->x + second->x; /* Component-wise f32 sum; retain operand/store order. */
    destination->y = first->y + second->y; /* RE_UNKNOWN: caller alias/storage/lifetime and FP contracts remain unproved. */
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

s32 uvVec2FIsZero(Vec2F *vector) { /* Exact x/y zero test; retain short circuit and f64 promotion. */
    if ((vector->x == 0.0) && (vector->y == 0.0)) {
        return TRUE;
    }
    return FALSE; /* RE_UNKNOWN: storage/lifetime and FP traps need caller/FP evidence. */
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
