// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void uvGrphNoOpModuleCleanup(void);
f32 uvGrphEvaluateLinearCurve(UvGrphStruct *arg0, f32 arg1);
void uvGrphClampPointCount(s32 arg0, s32 *arg1);
s32 uvGrphInsertPointAfter(UvGrphStruct *grph, s32 arg1);
s32 uvGrphRemovePoint(UvGrphStruct *grph, s32 arg1);
void func_uvgrph_rom_0040033C(UvGrphStruct *arg0, f32 arg1);
f32 uvGrphEvaluateInverseRange(UvGrphStruct *arg0, f32 arg1, f32 arg2, f32 arg3);
void __entrypoint_func_uvgrph_rom_400000(UvGrph_Exports *exports);

s32 D_uvgrph_rom_004006C0[] = {0x1C0000, __entrypoint_func_uvgrph_rom_400000, 0};

/* Update the allocation pointer, then publish seven graph callbacks in their
 * original slot order. RE_UNKNOWN: export-table lifetime, graph ownership and
 * repeated initialization require module consumers. */
#line 16 "src/modules/uvgrph_rom.c"
void __entrypoint_func_uvgrph_rom_400000(UvGrph_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->func_uvgrph_rom_0040033C = func_uvgrph_rom_0040033C;
    exports->uvGrphNoOpModuleCleanup = uvGrphNoOpModuleCleanup;
    exports->uvGrphEvaluateInverseRange = uvGrphEvaluateInverseRange;
    exports->uvGrphEvaluateLinearCurve = uvGrphEvaluateLinearCurve;
    exports->uvGrphClampPointCount = uvGrphClampPointCount;
    exports->uvGrphInsertPointAfter = uvGrphInsertPointAfter;
    exports->uvGrphRemovePoint = uvGrphRemovePoint;
}
#line 26 "src/modules/uvgrph_rom.c"

#line 27 "src/modules/uvgrph_rom.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void uvGrphNoOpModuleCleanup(void) {
}
#line 29 "src/modules/uvgrph_rom.c"

#line 30 "src/modules/uvgrph_rom.c"
/* Evaluate the piecewise linear curve with endpoint clamps and
 * original arithmetic order. RE_UNKNOWN: nonempty/ordered points and
 * nonzero neighboring X differences need original curve producers and callers. */
f32 uvGrphEvaluateLinearCurve(UvGrphStruct *curve, f32 x) {
    f32 fraction;
    s32 index;

    if (x <= curve->arr->unk0) {
        return curve->arr->unk4;
    }

    if (curve->arr[curve->count - 1].unk0 <= x) {
        return curve->arr[curve->count - 1].unk4;
    }

    for (index = 1; index < curve->count - 1; index++) {
        if ((x < curve->arr[index].unk0)) {
            break;
        }
    }

    fraction = (x - curve->arr[index - 1].unk0) / (curve->arr[index].unk0 - curve->arr[index - 1].unk0);
    return (curve->arr[index].unk4 * fraction) + (curve->arr[index - 1].unk4 * (1.0f - fraction));
}
#line 51 "src/modules/uvgrph_rom.c"

#line 52 "src/modules/uvgrph_rom.c"
/* Clamp the supplied count to zero through twenty, then retain the
 * original count-only walk. The first argument is intentionally unused. */
void uvGrphClampPointCount(s32 unused, s32 *count) {
    s32 index;

    if (*count < 0) {
        *count = 0;
    } else if (*count >= 0x15) {
        *count = 0x14;
    }
    // Retain the original count-only walk and its generated instructions.
    index = 0;
    while (index < *count) {
        index++;
    }
}
#line 66 "src/modules/uvgrph_rom.c"

#line 67 "src/modules/uvgrph_rom.c"
/* Insert after the selected point, retaining the twenty-point count
 * limit and returned selection. Append extends the previous X
 * interval; interior insertion averages neighbors. RE_UNKNOWN:
 * selected/count/backing and predecessor bounds need original producers/callers. */
s32 uvGrphInsertPointAfter(UvGrphStruct *grph, s32 selected) {
    s32 inserted;
    s32 index;
    UvGrphStruct *unusedCurve;
    f32 interval;
    UvGrphInnerStruct *unusedPoint;
    if (selected < 0) {
        return selected;
    }
    if (grph->count > 0x13) {
        return selected;
    } else {
        grph->count++;
    }

    inserted = selected + 1;

    for (index = grph->count - 1; index > inserted; index--) {
        grph->arr[index].unk0 = grph->arr[index - 1].unk0;
        grph->arr[index].unk4 = grph->arr[index - 1].unk4;
    }

    if (inserted == grph->count - 1) {
        interval = grph->arr[selected].unk0 - grph->arr[selected - 1].unk0;
        grph->arr[inserted].unk0 = grph->arr[inserted - 1].unk0 + interval;
        grph->arr[inserted].unk4 = grph->arr[inserted - 1].unk4;
    } else {
        grph->arr[inserted].unk0 = (grph->arr[selected].unk0 + grph->arr[selected + 2].unk0) * 0.5f;
        grph->arr[inserted].unk4 = (grph->arr[selected].unk4 + grph->arr[selected + 2].unk4) * 0.5f;
    }
    selected++;
    if (grph->count - 1 < selected) {
        selected = grph->count - 1;
    }
    return selected;
}
#line 103 "src/modules/uvgrph_rom.c"

#line 104 "src/modules/uvgrph_rom.c"
/* Remove a valid selected point only when at least three points exist.
 * Shift later pairs left and select the previous point, clamping at zero.
 * Invalid selections return unchanged without changing the curve. */
s32 uvGrphRemovePoint(UvGrphStruct *grph, s32 selected) {
    s32 index;

    if (grph->count < 3) {
        return selected;
    }

    if ((selected < 0) || ((grph->count - 1) < selected)) {
        return selected;
    }
    for (index = selected; index < grph->count - 1; index++) {
        grph->arr[index].unk0 = grph->arr[index + 1].unk0;
        grph->arr[index].unk4 = grph->arr[index + 1].unk4;
    }

    selected--;
    grph->count = grph->count - 1;
    if (selected < 0) {
        selected = 0;
    }

    return selected;
}
#line 127 "src/modules/uvgrph_rom.c"

/* Call uvGrphEvaluateInverseRange with the graph and input plus two zero bounds.
 * RE_UNKNOWN: the zero-bound convention and graph validity require that provider. */
#line 128 "src/modules/uvgrph_rom.c"
void func_uvgrph_rom_0040033C(UvGrphStruct *arg0, f32 arg1) {
    uvGrphEvaluateInverseRange(arg0, arg1, 0.0f, 0.0f);
}
#line 131 "src/modules/uvgrph_rom.c"

#line 132 "src/modules/uvgrph_rom.c"
/* Find X for Y on the original ascending/descending branch; equal range edges
 * select the full curve. RE_UNKNOWN: nonempty/suitable points, range and
 * denominator domains need original producers/callers. Retained C can leave
 * last unassigned when no point is below the upper edge; original
 * invalid-domain reachability needs native/caller proof. Preserve endpoint/arithmetic order. */
f32 uvGrphEvaluateInverseRange(UvGrphStruct *curve, f32 y, f32 rangeStart, f32 rangeEnd) {
    UvGrphInnerStruct *first;
    UvGrphInnerStruct *second;
    f32 fraction;
    f32 maximum;
    f32 minimum;
    s32 maximumIndex;
    s32 last;
    s32 minimumIndex;
    s32 start;
    s32 index;

    start = -1;
    if (rangeStart == rangeEnd) {
        start = 0;
        last = curve->count - 1;
    } else {
        start = -1;
        for (index = 0; index < curve->count; index++) {
            if ((start == -1) && (rangeStart < curve->arr[index].unk0)) {
                start = index;
            }
            if (curve->arr[index].unk0 < rangeEnd) {
                last = index;
            }
        }
    }

    if ((start == -1) || ((last - start) < 0)) {
        return 0.0f;
    }

    maximum = curve->arr[start].unk4;
    maximumIndex = start;
    minimumIndex = start;
    minimum = maximum;

    for (index = start + 1; index <= last; index++) {
        if (curve->arr[index].unk4 < minimum) {
            minimum = curve->arr[index].unk4;
            minimumIndex = index;
        }
        if (maximum < curve->arr[index].unk4) {
            maximum = curve->arr[index].unk4;
            maximumIndex = index;
        }
    }

    if (maximum <= y) {
        return curve->arr[maximumIndex].unk0;
    }
    if (y <= minimum) {
        return curve->arr[minimumIndex].unk0;
    }

    if (minimumIndex < maximumIndex) {
        for (index = start + 1; index <= last - 1; index++) {
            if ((y < curve->arr[index].unk4)) {
                break;
            }
        }
        first = &curve->arr[index - 1];
        second = &curve->arr[index];
    } else {
        for (index = start + 1; index <= last - 1; index++) {
            if ((curve->arr[index].unk4 < y)) {
                break;
            }
        }
        first = &curve->arr[index];
        second = &curve->arr[index - 1];
    }
    fraction = (y - first->unk4) / (second->unk4 - first->unk4);
    return (first->unk0 * (1.0f - fraction)) + (second->unk0 * fraction);
}
#line 207 "src/modules/uvgrph_rom.c"
