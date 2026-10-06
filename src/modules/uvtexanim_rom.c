// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

void __entrypoint_func_uvtexanim_rom_400000(UvTexAnim_Exports* exports);
void func_uvtexanim_rom_004000DC(void);
void func_uvtexanim_rom_00400118(void);
void func_uvtexanim_rom_004002A0(void);
void func_uvtexanim_rom_004002DC(s32 arg0);
void func_uvtexanim_rom_00400640(UnkUVTX_1C *arg0, ...);

UvGfxMgr_Exports* D_uvtexanim_rom_00400980;
UvCback_Exports* D_uvtexanim_rom_00400984;
void* D_uvtexanim_rom_00400988;
UnkUVTX_1C** D_uvtexanim_rom_0040098C;
s32 D_uvtexanim_rom_00400990;
u8 D_uvtexanim_rom_00400994;

s32 D_uvtexanim_rom_00400970[] = {0x00100000, __entrypoint_func_uvtexanim_rom_400000, 0, 0};

void __entrypoint_func_uvtexanim_rom_400000(UvTexAnim_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->func_uvtexanim_rom_004000DC = func_uvtexanim_rom_004000DC;
    exports->func_uvtexanim_rom_00400118 = func_uvtexanim_rom_00400118;
    exports->func_uvtexanim_rom_004002A0 = func_uvtexanim_rom_004002A0;
    exports->func_uvtexanim_rom_00400640 = func_uvtexanim_rom_00400640;
#ifdef __sgi
    #line 24
#endif
    D_uvtexanim_rom_00400980 = uvLoadModule('GMGR');
    D_uvtexanim_rom_00400984 = uvLoadModule('CBCK');
    D_uvtexanim_rom_00400988 = uvLoadModule('TEXT');
    D_uvtexanim_rom_0040098C = NULL;
    D_uvtexanim_rom_00400990 = 0;
    D_uvtexanim_rom_00400984->uvAddCallback(D_uvtexanim_rom_00400980->func_uvgfxmgr_rom_00400AB8(1), (s32) func_uvtexanim_rom_004002DC, 0, 0);
}

void func_uvtexanim_rom_004000DC(void) {
    uvUnloadModule('GMGR');
    uvUnloadModule('CBCK');
    uvUnloadModule('TEXT');
}

void func_uvtexanim_rom_00400118(void) {
    s32 filesCount;
    s32 i;
    ParsedUVTX* uvtx;

    if (D_uvtexanim_rom_0040098C != NULL) {
        return;
    }
        
    filesCount = uvGetFilesCount('UVTX');
    D_uvtexanim_rom_00400990 = 0;
    for (i = 0; i < filesCount; i++) {
        if (uvGetFileInstanceCount('UVTX', i) != 0) {
            uvtx = uvGetLoadedFile('UVTX', i);
            if (uvtx != NULL) {
                if (uvtx->unk4 != 0) {
                    D_uvtexanim_rom_00400990++;
                }
                if (uvtx->size.as_s32 != 0) {
                    D_uvtexanim_rom_00400990++;
                }
            }
        }
    }
    if (D_uvtexanim_rom_00400990 == 0) {
        return;
    }
           
    D_uvtexanim_rom_0040098C = _uvMemAllocAlign8(D_uvtexanim_rom_00400990 * 4);
    D_uvtexanim_rom_00400990 = 0;
    
    for (i = 0; i < filesCount; i++) {
        if (uvGetFileInstanceCount('UVTX', i) != 0) {
            uvtx = uvGetLoadedFile('UVTX', i);
            if (uvtx != NULL) {
                if (uvtx->unk4 != 0) {
                    // TODO: What's happening here?
                    D_uvtexanim_rom_0040098C[D_uvtexanim_rom_00400990] = (void*)uvtx->unk4;
                    D_uvtexanim_rom_00400990 += 1;
                }
                if (uvtx->size.as_s32 != 0) {
                    D_uvtexanim_rom_0040098C[D_uvtexanim_rom_00400990] = (void*)uvtx->size.as_s32;
                    D_uvtexanim_rom_00400990 += 1;
                }
            }
        }
    }
    D_uvtexanim_rom_00400994 = 0;
}

void func_uvtexanim_rom_004002A0(void) {
    if (D_uvtexanim_rom_0040098C != NULL) {
        _uvMemFree(D_uvtexanim_rom_0040098C);
    }
    D_uvtexanim_rom_0040098C = NULL;
    D_uvtexanim_rom_00400990 = 0;
}

void func_uvtexanim_rom_004002DC(s32 arg0) {
    f32 temp_fv0;
    s32 i;
    UnkUVTX_1C *temp_v0;

    temp_fv0 = D_uvtexanim_rom_00400980->func_uvgfxmgr_rom_00401004();
    if ((u8) D_uvtexanim_rom_00400994 == 1) {
        return;
    }

    for (i = 0; i < D_uvtexanim_rom_00400990; i++) {
        temp_v0 = D_uvtexanim_rom_0040098C[i];
        if (temp_v0->unk1A == 0) {
            continue;
        }
        if (temp_v0->unk18 != 3) {
            temp_v0->unk10 += (temp_v0->unk8 * temp_fv0);
        }
        if (temp_v0->unk18 == 0) {
            if (temp_v0->unk8 > 0.0f) {
                if (temp_v0->unk10 >= 1.0f) {
                    temp_v0->unk10 -= 1.0f;
                }
            }
            if (temp_v0->unk8 < 0.0f) {
                if (temp_v0->unk10 <= 0) {
                    temp_v0->unk10 += 1.0f;
                }
            }
        } else if (temp_v0->unk18 == 2) {
            if (temp_v0->unk10 >= 1.0f) {
                temp_v0->unk10 = 0.999f;
                temp_v0->unk8 =  -temp_v0->unk8;
            } else if (temp_v0->unk10 <= 0) {
                temp_v0->unk10 = 0.001f;
                temp_v0->unk8 = -temp_v0->unk8;
            }
        } else if (temp_v0->unk18 == 1) {
            if ((temp_v0->unk8 > 0.0f) && (temp_v0->unk10 >= 1.0f)) {
                temp_v0->unk10 = 1.0f;
                temp_v0->unk1A = 0U;
            }
            if ((temp_v0->unk8 < 0.0f) && (temp_v0->unk10 <= 0)) {
                temp_v0->unk10 = 0;
                temp_v0->unk1A = 0U;
            }
        }
        if (temp_v0->unk19 != 3) {
            temp_v0->unk14 += temp_v0->unkC * temp_fv0;
        }
        if (temp_v0->unk19 == 0) {
            if (temp_v0->unkC > 0.0f) {
                if (temp_v0->unk14 >= 1.0f) {
                    temp_v0->unk14 -= 1.0f;
                }
            }
            if (temp_v0->unkC < 0.0f) {
                if (temp_v0->unk14 <= 0) {
                    temp_v0->unk14 += 1.0f;
                }
            }
        } else if (temp_v0->unk19 == 2) {
            if (temp_v0->unk14 >= 1.0f) {
                temp_v0->unk14 = 0.999f;
                temp_v0->unkC =  -temp_v0->unkC;
            } else if (temp_v0->unk14 <= 0) {
                temp_v0->unk14 =  0.001f;
                temp_v0->unkC = -temp_v0->unkC;
            }
        } else if (temp_v0->unk19 == 1) {
            if ((temp_v0->unkC > 0.0f) && (temp_v0->unk14 >= 1.0f)) {
                temp_v0->unk14 = 1.0f;
                temp_v0->unk1A = 0U;
            }
            if ((temp_v0->unkC < 0.0f) && (temp_v0->unk14 <= 0)) {
                temp_v0->unk14 = 0;
                temp_v0->unk1A = 0U;
            }
        }
    }
}

void func_uvtexanim_rom_00400640(UnkUVTX_1C *arg0, ...) {
    s32 var_a2;
    s16 temp_a0;
    va_list args;
    UnkUVTX_1C* v0;

    v0 = arg0;

    va_start(args, arg0);
    while (TRUE) {
        temp_a0 = va_arg(args, u16*);
        switch (temp_a0) {
            default:
                return;
            case 1:
                D_uvtexanim_rom_00400994 = (s16)va_arg(args, s32);
                break;
            case 2:
                v0->unk0 = va_arg(args, f64);
                v0->unk4 = va_arg(args, f64);
                break;
            case 3:
                v0->unk8 = va_arg(args, f64);
                v0->unkC = va_arg(args, f64);
                break;
            case 5:
                var_a2 = FALSE;
                v0->unk10 = va_arg(args, f64);
                v0->unk14 = va_arg(args, f64);
                if (v0->unk10 > 1.0f) {
                    v0->unk10 = 1.0f;
                    var_a2 = TRUE;
                }
                if (v0->unk10 < 0.0f) {
                    var_a2 = TRUE;
                    v0->unk10 = 0.0f;
                }
                if (v0->unk14 > 1.0f) {
                    v0->unk14 = 1.0f;
                    var_a2 = TRUE;
                }
                if (v0->unk14 < 0.0f) {
                    var_a2 = TRUE;
                    v0->unk14 = 0.0f;
                }
                if (var_a2) {
                    break;
                }
                break;
            case 4:
                v0->unk1A = va_arg(args, s32);
                break;
            case 6:
                v0->unk18 = va_arg(args, s32);
                v0->unk19 = va_arg(args, s32);
                break;
            case 0:
                return;
        }
    }
}