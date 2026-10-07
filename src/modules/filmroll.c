/*__SEEDEXTERNS__*/
extern int D_filmroll_00400A78;
extern float D_filmroll_004009A4;
typedef struct {
    /* 0x00 */ int unk0;
    /* 0x04 */ int unk4;
    /* 0x08 */ int unk8;
    /* 0x0C */ int unkC;
} Node_00400588;
typedef struct {
    /* 0x00 */ char pad[0x34];
    /* 0x34 */ float (*unk34)(void);
} UvMathExp_00400588;
extern UvMathExp_00400588 *gUvMathExports;
// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/__entrypoint_func_filmroll_400000.s")

void func_filmroll_00400060(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400068.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_0040035C.s")

/* Initialises a filmroll entry: increments global counter, randomises position/size fields, clears one field. */
#line 28 "src/modules/filmroll.c"
/* Count and activate the entry, fill two integer fields from separate
 * random samples, and clear its trailing word. Preserve both random calls
 * and the original float-to-integer truncation. */
void filmrollInitializeRandomizedEntry(Node_00400588 *entry) {
    float secondSample;

    D_filmroll_00400A78 += 1;
    entry->unk0 = 1;
    entry->unk4 = (int) (gUvMathExports->unk34() * D_filmroll_004009A4);
    secondSample = gUvMathExports->unk34() * 239.0f;
    entry->unkC = 0;
    entry->unk8 = (int) secondSample;
}
#line 38 "src/modules/filmroll.c"

void func_filmroll_0040062C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400720.s")

