// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[0x24]; f32 selected; } SceneTrackChoice;
typedef struct { u8 unk00[8]; s32 value08; u8 unk0C[0x90]; } SceneTrackRecord;
typedef struct { u8 unk00[0xC4]; void (*select)(SceneTrackChoice *, s32); } SceneGuiSelectionExports;
/*__SEEDEXTERNS__*/
extern s32 D_scene_00402D14;
extern f32 D_scene_00401814;
extern f32 D_scene_00401818;
extern f32 D_scene_0040181C;
extern f32 D_scene_00401820;
extern f32 D_scene_00401824;
extern f32 D_scene_00401828;
extern f32 D_scene_0040182C;
extern f32 D_scene_00401830;
extern f32 D_scene_00401834;
extern s32 D_8002CB8C;
extern s32 D_8002CC64;
extern s32 D_8002D1A8;
extern s32 D_scene_00402CFC;
extern s32 D_scene_00402DA0;
extern s32 D_scene_00402DB8;
extern s32 gCurrentGameState;
extern s8 D_scene_00402E00;
extern s8 D_scene_00402E01;
extern u8 D_scene_00401754;
extern u8 D_scene_0040175C;
extern u8 D_scene_00401764;
extern u8 D_scene_0040176C;
extern u8 D_scene_00401778;
extern u8 D_scene_004017A4;
extern u8 D_scene_004017AC;
extern u8 D_scene_004017B8;
extern u8 D_scene_004017C0;
extern u8 D_scene_004017CC;
extern u8 D_scene_004017D4;
extern u8 D_scene_004017E0;
extern u8 D_scene_004017EC;
extern u8 D_scene_004017F4;
extern u8 D_scene_004017FC;
extern u8 D_scene_00401804;
extern u8 D_scene_00401840;
extern u8 D_scene_00401D3C;
extern u8 D_scene_00402CF0;
extern u8 D_scene_00402DD8;
extern u8 D_scene_00402DF8;
extern u8 D_scene_00402E20;
extern u8 D_scene_00402E4C;
extern u8 D_scene_00402ED0;
extern u8 D_scene_00402ED4;
extern u8 D_scene_00402ED8;
extern u8 D_scene_00402EDC;
extern u8 D_scene_00402EE0;
extern u8 D_scene_00402EE4;
extern u8 D_scene_00402EE8;
extern u8 gCheatTrackMusic;
extern u8 gCurrentTrack;
extern u8 gTrackWeather;
extern void *D_scene_00402EF0;
extern void *gGlareExports;
extern void *gLightExports;
extern void *gRainExports;
extern void *gScrnExports;
extern void *gSndExports;
extern void *gUvCmidiExports;
extern void *gUvDobjExports;
extern void *gUvEnvExports;
extern void *gUvGuiExports;
extern void *gUvIsectExports;
extern void *gUvLightExports;
extern void *gUvMathExports;
extern void *gUvTerraExports;
extern s32 D_scene_00402CF8;
extern s32 D_scene_00402D10;
extern s32 D_scene_00402D34;
extern s32 D_scene_00402D40;
s32 func_scene_00400000();
s32 func_scene_00400030();
void func_scene_00400060();
void func_scene_00400188();
void func_scene_004002A8(void);
void sceneRefreshLoadedModelsWithFlags(void);
void sceneRefreshLoadedModelsWithData(void);
void func_scene_004003F4();
void sceneUpdateSharedEffectState(void);
void func_scene_00400CB8();
void func_scene_00400EC8();
void func_scene_00401254(s32 arg0);
void sceneApplySelectedTrack(SceneTrackChoice *choice);
void func_scene_00401324();
void sceneCopyEightWordRecord();
void func_scene_00401438();
s32 func_scene_00400000(s32 a0) {
    if (a0 >= 6) {
        a0 = 5;
    } else if (a0 < 0) {
        a0 = 0;
    }
    return (&D_scene_00402CF8)[a0];
}

s32 func_scene_00400030(s32 a0) {
    if (a0 >= 9) {
        a0 = 8;
    } else if (a0 < 0) {
        a0 = 0;
    }
    return (&D_scene_00402D10)[a0];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400060.s")

s32 func_scene_004000FC(s32 arg0) {
    s32 *var_v0;
    s32 var_v1;

    if (arg0 == D_scene_00402D10) {
        return 0;
    }
    var_v0 = &D_scene_00402D14;
    var_v1 = 1;
loop_3:
    if (arg0 == var_v0[0]) {
        return var_v1;
    }
    if (arg0 == var_v0[1]) {
        return var_v1 + 1;
    }
    if (arg0 == var_v0[2]) {
        return var_v1 + 2;
    }
    if (arg0 == var_v0[3]) {
        return var_v1 + 3;
    }
    var_v1 += 4;
    var_v0 += 4;
    if (var_v1 != 9) {
        goto loop_3;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400188.s")

void func_scene_004002A8(void)
{
 do { s32 *p = &D_scene_00402D34; if (1) { do { func_scene_00400188(*p); p++; } while (p != (&D_scene_00402D40)); } } while (0);
}

#line 150 "src/modules/scene.c"
/* Visit loaded model IDs and refresh those whose byte-five flags include
 * any bit in mask 0x70. Preserve the original file-count snapshot. */
void sceneRefreshLoadedModelsWithFlags(void) {
    s32 count;
    s32 index;
    void *file;

    count = uvGetFilesCount(0x55564D44);
    index = 0;
    if (count > 0) {
        do {
            file = uvGetLoadedFile(0x55564D44, index);
            if ((file != 0) && (*(u8 *)((u8 *)file + 0x5) & 0x70)) {
                func_scene_00400188(index);
            }
            index += 1;
        } while (index < count);
    }
}
#line 167 "src/modules/scene.c"

#line 168 "src/modules/scene.c"
/* Visit loaded model IDs and refresh those with a nonzero word at 0x20.
 * Preserve the original file-count snapshot and loaded-file null check. */
void sceneRefreshLoadedModelsWithData(void) {
    s32 count;
    s32 index;
    void *file;

    count = uvGetFilesCount(0x55564D44);
    index = 0;
    if (count > 0) {
        do {
            file = uvGetLoadedFile(0x55564D44, index);
            if ((file != 0) && (*(s32 *)((u8 *)file + 0x20) != 0)) {
                func_scene_00400188(index);
            }
            index = index + 1;
        } while (index < count);
    }
}
#line 185 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004003F4.s")

void func_scene_00400C58(void) {
}

#line 191 "src/modules/scene.c"
/* Run the optional scene export update, then clear the two shared scalars
 * at 0xE8/0xEC when the shared enable word at 0xD8 is zero. */
void sceneUpdateSharedEffectState(void) {
    void *exports;

    exports = D_scene_00402EF0;
    if (exports != 0) {
        (*(void (**)(void))((u8 *)exports + 0x4))();
    }
    if (*(s32 *)((u8 *)&D_scene_00402DF8 + 0xD8) == 0) {
        *(f32 *)((u8 *)&D_scene_00402DF8 + 0xE8) = 0.0f;
        *(f32 *)((u8 *)&D_scene_00402DF8 + 0xEC) = 0.0f;
    }
}
#line 203 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/__entrypoint_func_scene_400e0c.s")

void func_scene_00400EC0(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400EC8.s")

void func_scene_00401254(s32 arg0)
{
  s32 var_v0;
  s32 var_a1;
  void *var_v1;
  void *temp_a0;
  *((s32 *) (((u8 *) (&arg0)) + 0x0)) = arg0;
  var_v0 = 0;
  var_v1 = *((void **) (((u8 *) gScrnExports) + 0x18));
  var_a1 = 0;
  if ((*((s16 *) (((u8 *) (*((void **) (((u8 *) gScrnExports) + 0x18)))) + 0x10))) > 0)
  {
    do
    {
      temp_a0 = *((void **) (((u8 *) var_v1) + var_a1));
      var_v0 += 1;
      var_a1 += 4;
      *((s32 *) (((u8 *) temp_a0) + 0x21C)) = 1;
      var_v1 = *((void **) (((u8 *) gScrnExports) + 0x18));
    }
    while (var_v0 < (*((s16 *) (((u8 *) var_v1) + 0x10))));
  }
}

void func_scene_004012B0(s32 a0) {
}

#line 240 "src/modules/scene.c"
/* Truncate the floating selection into the current track, then forward the
 * corresponding 0x9C-byte record value to GUI export 0xC4. Preserve the
 * original unchecked index and use the stored track for record selection. */
void sceneApplySelectedTrack(SceneTrackChoice *choice) {

    SceneTrackRecord *record;
    gGameSettings->currentTrack = (s32)choice->selected;
    record = &((SceneTrackRecord *)&D_scene_00401840)[gGameSettings->currentTrack];
    ((SceneGuiSelectionExports *)gUvGuiExports)->select(choice, record->value08);
}
#line 241 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00401324.s")

#line 244 "src/modules/scene.c"
/* Copy the original leading integer and seven floating words in their
 * original order. Preserve explicit scalar copies and the source address ABI. */
void sceneCopyEightWordRecord(void *destination, s32 sourceAddress) {
    *(s32 *)((u8 *)destination + 0x0) = *(s32 *)((u8 *)sourceAddress + 0x0);
    *(f32 *)((u8 *)destination + 0x4) = *(f32 *)((u8 *)sourceAddress + 0x4);
    *(f32 *)((u8 *)destination + 0x8) = *(f32 *)((u8 *)sourceAddress + 0x8);
    *(f32 *)((u8 *)destination + 0xC) = *(f32 *)((u8 *)sourceAddress + 0xC);
    *(f32 *)((u8 *)destination + 0x10) = *(f32 *)((u8 *)sourceAddress + 0x10);
    *(f32 *)((u8 *)destination + 0x14) = *(f32 *)((u8 *)sourceAddress + 0x14);
    *(f32 *)((u8 *)destination + 0x18) = *(f32 *)((u8 *)sourceAddress + 0x18);
    *(f32 *)((u8 *)destination + 0x1C) = *(f32 *)((u8 *)sourceAddress + 0x1C);
}
#line 254 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00401438.s")

