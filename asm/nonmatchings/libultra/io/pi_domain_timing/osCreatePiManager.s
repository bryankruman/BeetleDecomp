nonmatching osCreatePiManager, 0x17C

glabel osCreatePiManager
    /* 7D90 80007190 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 7D94 80007194 AFB00020 */  sw         $s0, 0x20($sp)
    /* 7D98 80007198 3C108002 */  lui        $s0, %hi(D_800209F0)
    /* 7D9C 8000719C 261009F0 */  addiu      $s0, $s0, %lo(D_800209F0)
    /* 7DA0 800071A0 8E0E0000 */  lw         $t6, 0x0($s0)
    /* 7DA4 800071A4 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 7DA8 800071A8 AFA40030 */  sw         $a0, 0x30($sp)
    /* 7DAC 800071AC AFA50034 */  sw         $a1, 0x34($sp)
    /* 7DB0 800071B0 AFA60038 */  sw         $a2, 0x38($sp)
    /* 7DB4 800071B4 15C00050 */  bnez       $t6, .L800072F8
    /* 7DB8 800071B8 AFA7003C */   sw        $a3, 0x3C($sp)
    /* 7DBC 800071BC 0C001CC3 */  jal        func_8000730C
    /* 7DC0 800071C0 00000000 */   nop
    /* 7DC4 800071C4 8FA40034 */  lw         $a0, 0x34($sp)
    /* 7DC8 800071C8 8FA50038 */  lw         $a1, 0x38($sp)
    /* 7DCC 800071CC 0C0016E4 */  jal        osCreateMesgQueue
    /* 7DD0 800071D0 8FA6003C */   lw        $a2, 0x3C($sp)
    /* 7DD4 800071D4 3C048003 */  lui        $a0, %hi(D_800321D0)
    /* 7DD8 800071D8 3C058003 */  lui        $a1, %hi(D_800321E8)
    /* 7DDC 800071DC 24A521E8 */  addiu      $a1, $a1, %lo(D_800321E8)
    /* 7DE0 800071E0 248421D0 */  addiu      $a0, $a0, %lo(D_800321D0)
    /* 7DE4 800071E4 0C0016E4 */  jal        osCreateMesgQueue
    /* 7DE8 800071E8 24060001 */   addiu     $a2, $zero, 0x1
    /* 7DEC 800071EC 3C0F8002 */  lui        $t7, %hi(D_80020A30)
    /* 7DF0 800071F0 8DEF0A30 */  lw         $t7, %lo(D_80020A30)($t7)
    /* 7DF4 800071F4 15E00003 */  bnez       $t7, .L80007204
    /* 7DF8 800071F8 00000000 */   nop
    /* 7DFC 800071FC 0C001E64 */  jal        func_80007990
    /* 7E00 80007200 00000000 */   nop
  .L80007204:
    /* 7E04 80007204 3C058003 */  lui        $a1, %hi(D_800321D0)
    /* 7E08 80007208 3C062222 */  lui        $a2, (0x22222222 >> 16)
    /* 7E0C 8000720C 34C62222 */  ori        $a2, $a2, (0x22222222 & 0xFFFF)
    /* 7E10 80007210 24A521D0 */  addiu      $a1, $a1, %lo(D_800321D0)
    /* 7E14 80007214 0C001A14 */  jal        osSetEventMesg
    /* 7E18 80007218 24040008 */   addiu     $a0, $zero, 0x8
    /* 7E1C 8000721C 2418FFFF */  addiu      $t8, $zero, -0x1
    /* 7E20 80007220 AFB80028 */  sw         $t8, 0x28($sp)
    /* 7E24 80007224 0C002370 */  jal        osGetThreadPri
    /* 7E28 80007228 00002025 */   or        $a0, $zero, $zero
    /* 7E2C 8000722C 8FB90030 */  lw         $t9, 0x30($sp)
    /* 7E30 80007230 00002025 */  or         $a0, $zero, $zero
    /* 7E34 80007234 0059082A */  slt        $at, $v0, $t9
    /* 7E38 80007238 10200003 */  beqz       $at, .L80007248
    /* 7E3C 8000723C 03202825 */   or        $a1, $t9, $zero
    /* 7E40 80007240 0C001CE0 */  jal        osSetThreadPri
    /* 7E44 80007244 AFA20028 */   sw        $v0, 0x28($sp)
  .L80007248:
    /* 7E48 80007248 0C001EA4 */  jal        __osDisableInt
    /* 7E4C 8000724C 00000000 */   nop
    /* 7E50 80007250 8FA90034 */  lw         $t1, 0x34($sp)
    /* 7E54 80007254 8FAF0030 */  lw         $t7, 0x30($sp)
    /* 7E58 80007258 3C048003 */  lui        $a0, %hi(D_80031020)
    /* 7E5C 8000725C 3C0A8003 */  lui        $t2, %hi(D_800321D0)
    /* 7E60 80007260 3C0B8003 */  lui        $t3, %hi(D_80032288)
    /* 7E64 80007264 3C0C8001 */  lui        $t4, %hi(osPiRawStartDma)
    /* 7E68 80007268 3C0D8001 */  lui        $t5, %hi(osEPiRawStartDma)
    /* 7E6C 8000726C 3C0E8003 */  lui        $t6, %hi(D_800321D0)
    /* 7E70 80007270 24841020 */  addiu      $a0, $a0, %lo(D_80031020)
    /* 7E74 80007274 24080001 */  addiu      $t0, $zero, 0x1
    /* 7E78 80007278 254A21D0 */  addiu      $t2, $t2, %lo(D_800321D0)
    /* 7E7C 8000727C 256B2288 */  addiu      $t3, $t3, %lo(D_80032288)
    /* 7E80 80007280 258C92D0 */  addiu      $t4, $t4, %lo(osPiRawStartDma)
    /* 7E84 80007284 25AD93B0 */  addiu      $t5, $t5, %lo(osEPiRawStartDma)
    /* 7E88 80007288 25CE21D0 */  addiu      $t6, $t6, %lo(D_800321D0)
    /* 7E8C 8000728C 3C068001 */  lui        $a2, %hi(__osDevMgrMain)
    /* 7E90 80007290 AFA2002C */  sw         $v0, 0x2C($sp)
    /* 7E94 80007294 AE080000 */  sw         $t0, 0x0($s0)
    /* 7E98 80007298 AE040004 */  sw         $a0, 0x4($s0)
    /* 7E9C 8000729C AE0A000C */  sw         $t2, 0xC($s0)
    /* 7EA0 800072A0 AE0B0010 */  sw         $t3, 0x10($s0)
    /* 7EA4 800072A4 AE0C0014 */  sw         $t4, 0x14($s0)
    /* 7EA8 800072A8 AE0D0018 */  sw         $t5, 0x18($s0)
    /* 7EAC 800072AC 24C695E0 */  addiu      $a2, $a2, %lo(__osDevMgrMain)
    /* 7EB0 800072B0 AFAE0010 */  sw         $t6, 0x10($sp)
    /* 7EB4 800072B4 00002825 */  or         $a1, $zero, $zero
    /* 7EB8 800072B8 02003825 */  or         $a3, $s0, $zero
    /* 7EBC 800072BC AE090008 */  sw         $t1, 0x8($s0)
    /* 7EC0 800072C0 0C001A4C */  jal        osCreateThread
    /* 7EC4 800072C4 AFAF0014 */   sw        $t7, 0x14($sp)
    /* 7EC8 800072C8 3C048003 */  lui        $a0, %hi(D_80031020)
    /* 7ECC 800072CC 0C001AA0 */  jal        osStartThread
    /* 7ED0 800072D0 24841020 */   addiu     $a0, $a0, %lo(D_80031020)
    /* 7ED4 800072D4 0C001EAC */  jal        __osRestoreInt
    /* 7ED8 800072D8 8FA4002C */   lw        $a0, 0x2C($sp)
    /* 7EDC 800072DC 8FB80028 */  lw         $t8, 0x28($sp)
    /* 7EE0 800072E0 2401FFFF */  addiu      $at, $zero, -0x1
    /* 7EE4 800072E4 00002025 */  or         $a0, $zero, $zero
    /* 7EE8 800072E8 53010004 */  beql       $t8, $at, .L800072FC
    /* 7EEC 800072EC 8FBF0024 */   lw        $ra, 0x24($sp)
    /* 7EF0 800072F0 0C001CE0 */  jal        osSetThreadPri
    /* 7EF4 800072F4 03002825 */   or        $a1, $t8, $zero
  .L800072F8:
    /* 7EF8 800072F8 8FBF0024 */  lw         $ra, 0x24($sp)
  .L800072FC:
    /* 7EFC 800072FC 8FB00020 */  lw         $s0, 0x20($sp)
    /* 7F00 80007300 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 7F04 80007304 03E00008 */  jr         $ra
    /* 7F08 80007308 00000000 */   nop
endlabel osCreatePiManager

