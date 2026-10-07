// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00; u8 first; u8 unk02; u8 second; } CarAudioVoiceIds;
typedef struct { u8 unk00[8]; CarAudioVoiceIds *voices; } CarAudioDualVoice;
extern f32 D_caraudio_00403EF4;
#include "module.h"
extern Snd_Exports *gSndExports;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
#include "module.h"
#include "global_exports.h"
/*__SEEDEXTERNS__*/
extern f32 D_caraudio_004040C0[];
extern f32 D_caraudio_00404254;
void func_caraudio_00400314();
void func_caraudio_004003B0();
void func_caraudio_00400550();
void func_caraudio_00400758();
void func_caraudio_0040090C();
void func_caraudio_00400DB4();
void func_caraudio_004010A4();
void func_caraudio_004015B8();
void func_caraudio_00401698();
void func_caraudio_0040171C();
void func_caraudio_00401A08();
void func_caraudio_00401F24();
void carAudioSetEmitterPropertiesAndScalar(UnkStruct_004005C8 *emitter, UnkStruct_uvemitter_rom_004008CC *properties, f32 scalar);
void func_caraudio_00402044();
void func_caraudio_00402070();
void func_caraudio_0040218C();
void func_caraudio_004022BC();
void func_caraudio_004027A8();
void func_caraudio_004029F8();
void func_caraudio_00402B20();
void caraudioUpdateDualEmitterScalar(CarAudioDualVoice *state);
void func_caraudio_00402CA4();
void func_caraudio_00402E00();
void carAudioStartFixedPositionSound(s32 arg0);
void func_caraudio_004031E0();
void func_caraudio_0040336C();
void func_caraudio_0040397C();
extern u8 D_caraudio_004041E0[];
extern s32 gCurrentTrack;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/__entrypoint_func_caraudio_400000.s")

void func_caraudio_00400314(void) {
    gSndExports->func_snd_00401650();
    uvUnloadModule('motn');
}

void *func_caraudio_0040034C(s32 arg0, s32 arg1)
{
  void *obj = _uvMemAllocAlign8(0x50);
  (*((void (**)(void *)) (((u8 *) gUvFmtxExports) + 0x1C)))(((u8 *) obj) + 0x10);
  *((s16 *) (((u8 *) obj) + 0x6)) = 0x1C;
  *((s32 *) (((u8 *) obj) + 0xC)) = arg0;
  *((s16 *) (((u8 *) obj) + 0x6)) = 0x1C;
  func_caraudio_004003B0(obj, arg1);
  return obj;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004003B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00400550.s")

void func_caraudio_00400708(void *arg0) {
    D_caraudio_00404254 = D_caraudio_004040C0[*(s32 *)(*(s32 *)((u8 *)arg0 + 0xC) + 0x1EC)];
    func_caraudio_00402B20(*(s32 *)((u8 *)arg0 + 0x14), arg0);
    caraudioUpdateDualEmitterScalar(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00400758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040090C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00400DB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004010A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004015B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00401698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040171C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00401A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00401F24.s")

#line 86 "src/modules/caraudio.c"
/* Apply emitter properties through sound slot 0x80, then the scalar through
 * slot 0x88. The sound implementation owns scalar clamping and emitter validity. */
void carAudioSetEmitterPropertiesAndScalar(UnkStruct_004005C8 *emitter, UnkStruct_uvemitter_rom_004008CC *properties, f32 scalar) {
    gSndExports->func_snd_00401E08(emitter, properties);
    gSndExports->func_snd_00401EB8(emitter, scalar);
}
#line 87 "src/modules/caraudio.c"

/* Forward the caller's emitter to sound export slot 0x70. */
void func_caraudio_00402044(UnkStruct_004005C8 *emitter) {
    gSndExports->func_snd_00401CDC(emitter);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402070.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040218C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004022BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004027A8.s")

s32 func_caraudio_00402994(void *arg0) {
    s32 *slots;

    slots = (s32 *)((u8 *)*(s32 **)((u8 *)arg0 + 0x4) + 0x2D0);
    if (slots[0] != 0) {
        return 1;
    }
    if (slots[1] != 0) {
        return 1;
    }
    if (slots[2] != 0) {
        return 1;
    }
    if (slots[3] != 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004029F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402B20.s")

void func_caraudio_00402C08(void) {
}

#line 127 "src/modules/caraudio.c"
/* Apply the original shared sound scalar to both emitter IDs stored in the
 * car audio record. Keep multiplication order and the two update calls. */
void caraudioUpdateDualEmitterScalar(CarAudioDualVoice *state) {
    f32 scalar = gSndExports->func_snd_004014B4() * (D_caraudio_00404254 * D_caraudio_00403EF4);
    gUvEmitterExports->func_uvemitter_rom_00400BE8(state->voices->first, scalar);
    gUvEmitterExports->func_uvemitter_rom_00400BE8(state->voices->second, scalar);
}
#line 128 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402CA4.s")

void func_caraudio_00402DE4(s32 a0) {
    D_caraudio_004041E0[a0] = 0;
}

s32 func_caraudio_00402DF4(void) {
    return gCurrentTrack;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402E00.s")

#line 141 "src/modules/caraudio.c"
/* Start sound 0x1D at the original fixed XYZ position, if an emitter is available.
 * Preserve its original playback parameters and unused argument; the sound's
 * gameplay identity is not yet established. */
extern f32 D_caraudio_00403F00;
extern f32 D_caraudio_00403F04;
extern f32 D_caraudio_00403F08;
extern UnkStruct_004005C8 D_caraudio_00404300;

void carAudioStartFixedPositionSound(s32 unused) {
    u8 soundId;
    Mtx4F soundTransform;

    gUvFmtxExports->uvMat4SetIdentity(&soundTransform);
    soundTransform.m[3][0] = D_caraudio_00403F00;
    soundTransform.m[3][1] = D_caraudio_00403F04;
    soundTransform.m[3][2] = 284.0f;
    soundId = gSndExports->func_snd_00401AA8(&D_caraudio_00404300, 0x1D, 0xBB8, 0);
    if (soundId != 0xFF) {
        gSndExports->func_snd_00401D54(&D_caraudio_00404300, 0U);
        gSndExports->func_snd_00401E08(&D_caraudio_00404300, (UnkStruct_uvemitter_rom_004008CC *) &soundTransform);
        gSndExports->func_snd_00401E70(&D_caraudio_00404300, gSndExports->func_snd_004014B4() * D_caraudio_00403F08);
        gSndExports->func_snd_00401EB8(&D_caraudio_00404300, 0.5f);
        gSndExports->func_snd_00401D14(&D_caraudio_00404300);
    }
}
#line 142 "src/modules/caraudio.c"

extern void *D_caraudio_00404228;

void func_caraudio_00403170(s32 arg0, s32 arg1, s32 arg2, unsigned char arg3, f32 arg4)
{
  volatile long pad;
  s32 *node = (0, _uvMemAllocAlign8(0x1C));
  node[0] = 0;
  node[1] = arg0;
  node[2] = arg1;
  node[3] = arg2;
  *((u8 *) (((u8 *) node) + (0x10 ^ 0))) = arg3;
  *((f32 *) (((u8 *) node) + 0x14)) = arg4;
  *((s32 *) (((u8 *) node) + 0x18)) = (s32) D_caraudio_00404228;
  D_caraudio_00404228 = node;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004031E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040336C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040397C.s")

extern u8 D_caraudio_00404230[];

void func_caraudio_00403A2C(void *arg0, s32 arg1)
{
  s32 *entry;
  s32 emitter;
  emitter = 8;
  if (arg1 < 4)
  {
    entry = (s32 *) (&D_caraudio_00404230[arg1 * emitter]);
    emitter = ((((((((((((*((s32 *) (((u8 *) arg0) + 0x8))) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF;
 entry[1] = arg1; entry[0] = emitter;
    (*((void (**)(s32, s32)) (((u8 *) gUvFmtxExports) + 0xC)))(emitter + 0x10, (*((s32 *) (((u8 *) arg0) + 0xC))) + 0x1A8);
  }
}

