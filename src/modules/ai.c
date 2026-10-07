// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[0x9C]; s32 value; u8 unkA0[0x14]; s16 active; u8 unkB6[0x132]; } AiIndexedRecord; /* Original stride 0x1E8. */
typedef struct { u8 unk00[0x1D]; u8 excluded; } AiRankActor;
typedef struct { AiRankActor *actor; } AiRankSource;
typedef struct AiRankNode { u8 unk00[0xC]; struct AiRankNode *next; u8 unk10[4]; AiRankSource *source; } AiRankNode;
#include "module.h"
extern UvFVec_Rom_Exports *gUvFvecExports;
/*__SEEDEXTERNS__*/
extern f32 D_ai_0040810C;
extern s32 D_ai_00407EA0;
extern void *D_ai_00408E40;
extern void *D_ai_00407FF4;
extern s32 D_ai_00408E48;
extern s32 D_ai_00408E4C;
extern s32 D_ai_00408008;
void func_ai_00400000();
void func_ai_0040019C();
void func_ai_0040089C();
void func_ai_00400A24();
void aiBuildOrthonormalBasisFromX(Mtx4F *basis, Vec3F *direction);
void func_ai_00400F18();
void func_ai_00400FF0();
void func_ai_004017A4();
void func_ai_004019EC();
void func_ai_00401C84();
void func_ai_00401EF0();
void func_ai_00402028();
void func_ai_004021E0();
void func_ai_004022A4();
void func_ai_00402858();
void func_ai_00402974();
void func_ai_00402A10();
void func_ai_00402AE0();
void func_ai_00402C2C();
void func_ai_00402E4C();
void func_ai_004030BC();
void func_ai_00403288();
void func_ai_00403448();
void func_ai_004037B4();
void func_ai_00403994();
void func_ai_00403C80();
void func_ai_00403F4C(s32 arg0);
void func_ai_00403F54();
void func_ai_00404064();
void func_ai_00404150(void *arg0, void *arg1);
void func_ai_00404194();
void func_ai_0040428C();
void func_ai_004042A4();
void func_ai_004044F0();
s32 func_ai_0040462C(Mtx4F *, Mtx4F *);
s32 aiTestBoundsContainmentEitherOrder(Mtx4F *first, Mtx4F *second);
void func_ai_0040490C();
void func_ai_00404E10();
void func_ai_004051A4();
void func_ai_00405324();
void func_ai_004053A8();
void func_ai_004057C0();
void func_ai_00405AC4();
void func_ai_00405B4C();
void func_ai_00405C8C();
void func_ai_00405D18();
void func_ai_00405D50();

void func_ai_00405EF4();
s32 aiGetEligibleListRank(AiRankNode *target);
void func_ai_0040617C();
void func_ai_00406400();
void func_ai_004068A8();
void func_ai_004069CC();
void func_ai_00406D84();
void func_ai_00407054();
s32 func_ai_0040757C();
void func_ai_004075B8();
s32 aiGetActiveRecordValue9C(u16 index);
extern s32 D_ai_00408E44;
extern s32 D_ai_00407FFC;
extern s32 D_ai_00408000;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040019C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040089C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/__entrypoint_func_ai_400bbc.s")

void func_ai_00400E38(void) {
}

#line 88 "src/modules/ai.c"
/* Set the X axis from direction, derive Z = X cross Y and Y = Z cross X,
 * then normalize all three axes. Leave matrix translation and W values intact. */
void aiBuildOrthonormalBasisFromX(Mtx4F *basis, Vec3F *direction) {
    Vec3F *axisZ;
    Vec3F *axisY;

    gUvFvecExports->uvVec3FCopy((Vec3F *)&basis->m[0][0], direction);
    axisZ = (Vec3F *)&basis->m[2][0];
    axisY = (Vec3F *)&basis->m[1][0];
    gUvFvecExports->uvVec3FCross(axisZ, direction, axisY);
    gUvFvecExports->uvVec3FCross(axisY, axisZ, direction);
    gUvFvecExports->uvVec3FNormalize((Vec3F *)&basis->m[0][0], (Vec3F *)&basis->m[0][0]);
    gUvFvecExports->uvVec3FNormalize(axisY, axisY);
    gUvFvecExports->uvVec3FNormalize(axisZ, axisZ);
}
#line 89 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00400FF0.s")

void func_ai_0040179C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004017A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004019EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00401C84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00401EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402028.s")

void func_ai_004021D8(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004021E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004022A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00402E4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004030BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403288.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403448.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004037B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403994.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403C80.s")

void func_ai_00403F44(void) {
}

void func_ai_00403F4C(s32 arg0) {

}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00403F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00404064.s")

void func_ai_00404150(void *arg0, void *arg1) {
    s32 idx = D_ai_00407EA0;
    if (idx != -1) {
        *(f32 *)arg0 = *(f32 *)((u8 *)&D_ai_0040810C + idx * 0x1E8);
        *(f32 *)arg1 = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00404194.s")

void func_ai_0040428C(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0xC2) = 0x1;
    *(f32 *)((u8 *)arg0 + 0x84) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xB0) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004042A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004044F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040462C.s")

#line 171 "src/modules/ai.c"
/* Run the original transformed nine-point bounds-containment test in each
 * order. Short-circuit after the first hit; boundary rules belong to that test. */
s32 aiTestBoundsContainmentEitherOrder(Mtx4F *first, Mtx4F *second) {
    if (func_ai_0040462C(first, second) || func_ai_0040462C(second, first)) {
        return 1;
    }
    return 0;
}
#line 172 "src/modules/ai.c"

void func_ai_00404904(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040490C.s")

void func_ai_00404DE8(void) {
}

void func_ai_00404DF0(void *a0, s16 a1) {
    if (D_ai_00407FFC) {
        *(s16 *)((u8 *)a0 + 0xA) = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00404E10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004051A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004053A8.s")

extern void *D_ai_00408E58;

void func_ai_00405754(s32 arg0)
{
  s32 new_var;
  new_var = arg0;
 goto dummy_label_975647; dummy_label_975647: ;
  (*((void (**)(s32, s32, s32, s32, f64, s32)) (((u8 *) D_ai_00408E58) + 0x14)))(*((s32 *) (new_var + 0x1DC)), 0x11, ((0, new_var)) + 0x100, 0xE, (f64) (*((f32 *) (new_var + 0x104))), 0);
  (*((void (**)(s32)) (((u8 *) D_ai_00408E58) + 0x10)))(*((s32 *) (new_var + 0x1DC)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004057C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405AC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405B4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405C8C.s")

void func_ai_00405D18(void *a0, void *a1, void *a2) {
    *(s32 *)((u8 *)a0 + 0x10) = (s32)a2;
    *(s32 *)((u8 *)a0 + 0xC) = (s32)a1;
    if (a1 == NULL) {
        D_ai_00408E40 = a0;
    } else {
        *(s32 *)((u8 *)a1 + 0x10) = (s32)a0;
    }
    if (a2 == NULL) {
        D_ai_00408E44 = (s32)a0;
        return;
    }
    *(s32 *)((u8 *)a2 + 0xC) = (s32)a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405D50.s")

#line 229 "src/modules/ai.c"
/* Find the first active AI record with this key, or return -1.
 * The record stride and field offsets come from the original lookup code. */
typedef struct {
    u8 pad0[0x9C];
    s32 key;
    u8 padA0[0x14];
    s16 active;
    u8 padB6[0x132];
} AiLookupRecord;
s32 aiFindActiveRecordByKey(s32 value) {
    s32 index;
    for (index = 0; index < D_ai_00408E4C; index = (index + 1) & 0xFFFF) {
        AiLookupRecord *record = &((AiLookupRecord *)&D_ai_00408008)[index];
        if (record->active != 0 && value == record->key) return index;
    }
    return -1;
}
#line 230 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00405EF4.s")

#line 233 "src/modules/ai.c"
/* Return one plus the number of eligible predecessors, or zero if absent.
 * A predecessor counts when its source actor is absent or its exclusion byte
 * is zero; the target itself is not filtered by that byte. */
s32 aiGetEligibleListRank(AiRankNode *target) {
    AiRankNode *node = (AiRankNode *)D_ai_00408E44;
    AiRankActor *actor;
    s32 rank = 1;
    while (node != NULL) {
        if (node == target) {
            break;
        }
        actor = node->source->actor;
        if (actor == NULL || actor->excluded == 0) {
            rank++;
        }
        node = node->next;
    }
    if (node == NULL) {
        rank = 0;
    }
    return rank;
}
#line 234 "src/modules/ai.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_0040617C.s")

s32 func_ai_004063B4(void) {
    s32 count;
    void *node;

    node = D_ai_00408E44;
    count = 1;
    if (node != NULL) {
loop:
        if (*(s32 *)((u8 *)node + 0x8) != 0) {
            node = *(void **)((u8 *)node + 0xC);
            count += 1;
            if (node != NULL) {
                goto loop;
            }
        }
    }
    if (node == NULL) {
        count = 1;
    }
    D_ai_00407FF4 = node;
    return count;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00406400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004068A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004069CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00406D84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_00407054.s")

s32 func_ai_00407564(void) {
    return D_ai_00408E44;
}

void func_ai_00407570(s32 a0) {
    D_ai_00407FFC = a0;
}

s32 func_ai_0040757C(void *arg0) {
    D_ai_00408E48 = 0;
    if (*(s32 *)((u8 *)arg0 + 0xC) != 0) {
        do {
            D_ai_00408E48++;
            arg0 = *(void **)((u8 *)arg0 + 0xC);
        } while (*(s32 *)((u8 *)arg0 + 0xC) != 0);
    }
    return D_ai_00408E48;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ai/func_ai_004075B8.s")

void func_ai_00407718(s32 a0) {
    D_ai_00408000 = a0;
}

#line 295 "src/modules/ai.c"
/* Return field 0x9C for an active indexed 0x1E8-byte AI record, otherwise -1.
 * Preserve the original unsigned-16 index conversion and signed count check. */
s32 aiGetActiveRecordValue9C(u16 index) {
    AiIndexedRecord *record;
    if (index < D_ai_00408E4C) {
        record = &((AiIndexedRecord *)&D_ai_00408008)[index];
        if (record->active != 0) {
            return record->value;
        }
    }
    return -1;
}
#line 296 "src/modules/ai.c"

