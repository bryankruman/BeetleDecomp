// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

extern void func_level1_0040003C(void);
extern void func_level1_00400044(void);

void __entrypoint_func_level1_400000(Level1_Exports* arg0) {
    uvUpdateFileAllocPtr(arg0);
    arg0->func_level1_0040003C = &func_level1_0040003C;
    arg0->func_level1_00400044 = &func_level1_00400044;
}


void func_level1_0040003C(void) {

}


void func_level1_00400044(void) {

}


