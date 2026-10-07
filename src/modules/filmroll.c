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
#include "common.h"
#include "file_manager.h"
void func_filmroll_00400060(void);
void func_filmroll_00400068(s32);
void func_filmroll_00400170(void);
void func_filmroll_0040035C(void);
void func_filmroll_00400720(void);
/* Initializer storage view: original 32-bit callback addresses only.
 * RE_UNKNOWN: callback-facing roles and intended historical declarations;
 * trace export consumers before introducing a callable interface. */
typedef struct FilmrollExportAddresses {
    u32 emptyCallbackAddress;
    u32 callback04Address;
    u32 callback08Address;
    u32 callback0CAddress;
    u32 callback10Address;
} FilmrollExportAddresses;
#line 33 "src/modules/filmroll.c"
/* Set the file allocation pointer and publish the five original callback
 * addresses in their original order. The first callback is the separate
 * empty function; the remaining addresses retain their original identities.
 * RE_UNKNOWN: callback-facing roles, intended historical declarations and
 * loader-provided table lifetime. Trace loader/export consumers before
 * replacing this 20-byte address storage view with a callable interface. */
void __entrypoint_func_filmrollInitializeModuleExports(FilmrollExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32)func_filmroll_00400060;
    exports->callback04Address = (u32)func_filmroll_00400068;
    exports->callback08Address = (u32)func_filmroll_00400170;
    exports->callback0CAddress = (u32)func_filmroll_0040035C;
    exports->callback10Address = (u32)func_filmroll_00400720;
}
#line 34 "src/modules/filmroll.c"

#line 18 "src/modules/filmroll.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_filmroll_00400060(void) {
}
#line 20 "src/modules/filmroll.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400068.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_0040035C.s")

/* RE_UNKNOWN: the two randomized integer fields are not established here
 * as position or size. Resolve their roles through the original entry draw/
 * update consumers before adding physical names or units. */
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

#line 39 "src/modules/filmroll.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_filmroll_0040062C(void) {
}
#line 41 "src/modules/filmroll.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/filmroll/func_filmroll_00400720.s")

