nonmatching func_80009DF0, 0x580

glabel func_80009DF0
    /* A9F0 80009DF0 3C0A8003 */  lui        $t2, %hi(D_80033524)
    /* A9F4 80009DF4 254A3524 */  addiu      $t2, $t2, %lo(D_80033524)
    /* A9F8 80009DF8 8D480000 */  lw         $t0, 0x0($t2)
    /* A9FC 80009DFC 27BDFFC8 */  addiu      $sp, $sp, -0x38
    /* AA00 80009E00 AFBF001C */  sw         $ra, 0x1C($sp)
    /* AA04 80009E04 3C03A460 */  lui        $v1, (0xA4600010 >> 16)
    /* AA08 80009E08 34630010 */  ori        $v1, $v1, (0xA4600010 & 0xFFFF)
    /* AA0C 80009E0C 8C780000 */  lw         $t8, 0x0($v1)
    /* AA10 80009E10 950E001A */  lhu        $t6, 0x1A($t0)
    /* AA14 80009E14 25080014 */  addiu      $t0, $t0, 0x14
    /* AA18 80009E18 AFB80030 */  sw         $t8, 0x30($sp)
    /* AA1C 80009E1C 8FB90030 */  lw         $t9, 0x30($sp)
    /* AA20 80009E20 000E78C0 */  sll        $t7, $t6, 3
    /* AA24 80009E24 01EE7821 */  addu       $t7, $t7, $t6
    /* AA28 80009E28 000F7880 */  sll        $t7, $t7, 2
    /* AA2C 80009E2C 010F4821 */  addu       $t1, $t0, $t7
    /* AA30 80009E30 332C0001 */  andi       $t4, $t9, 0x1
    /* AA34 80009E34 1180000C */  beqz       $t4, .L80009E68
    /* AA38 80009E38 25290018 */   addiu     $t1, $t1, 0x18
    /* AA3C 80009E3C 3C048002 */  lui        $a0, %hi(D_800209E0)
    /* AA40 80009E40 248409E0 */  addiu      $a0, $a0, %lo(D_800209E0)
    /* AA44 80009E44 8C8D0000 */  lw         $t5, 0x0($a0)
    /* AA48 80009E48 2401F7FF */  addiu      $at, $zero, -0x801
    /* AA4C 80009E4C 240F001D */  addiu      $t7, $zero, 0x1D
    /* AA50 80009E50 01A17024 */  and        $t6, $t5, $at
    /* AA54 80009E54 AC8E0000 */  sw         $t6, 0x0($a0)
    /* AA58 80009E58 0C002909 */  jal        kernelDiskPostPiEvent
    /* AA5C 80009E5C AD2F0000 */   sw        $t7, 0x0($t1)
    /* AA60 80009E60 1000013F */  b          .L8000A360
    /* AA64 80009E64 24020001 */   addiu     $v0, $zero, 0x1
  .L80009E68:
    /* AA68 80009E68 8C780000 */  lw         $t8, 0x0($v1)
    /* AA6C 80009E6C 3C04A500 */  lui        $a0, (0xA5000508 >> 16)
    /* AA70 80009E70 34840508 */  ori        $a0, $a0, (0xA5000508 & 0xFFFF)
    /* AA74 80009E74 AFB80030 */  sw         $t8, 0x30($sp)
    /* AA78 80009E78 8FB90030 */  lw         $t9, 0x30($sp)
    /* AA7C 80009E7C 3C010100 */  lui        $at, (0x1000000 >> 16)
    /* AA80 80009E80 332C0003 */  andi       $t4, $t9, 0x3
    /* AA84 80009E84 51800008 */  beql       $t4, $zero, .L80009EA8
    /* AA88 80009E88 8C850000 */   lw        $a1, 0x0($a0)
    /* AA8C 80009E8C 8C6D0000 */  lw         $t5, 0x0($v1)
  .L80009E90:
    /* AA90 80009E90 AFAD0030 */  sw         $t5, 0x30($sp)
    /* AA94 80009E94 8FAE0030 */  lw         $t6, 0x30($sp)
    /* AA98 80009E98 31CF0003 */  andi       $t7, $t6, 0x3
    /* AA9C 80009E9C 55E0FFFC */  bnel       $t7, $zero, .L80009E90
    /* AAA0 80009EA0 8C6D0000 */   lw        $t5, 0x0($v1)
    /* AAA4 80009EA4 8C850000 */  lw         $a1, 0x0($a0)
  .L80009EA8:
    /* AAA8 80009EA8 3C0B0200 */  lui        $t3, (0x2000000 >> 16)
    /* AAAC 80009EAC 0005C180 */  sll        $t8, $a1, 6
    /* AAB0 80009EB0 07030015 */  bgezl      $t8, .L80009F08
    /* AAB4 80009EB4 8D020000 */   lw        $v0, 0x0($t0)
    /* AAB8 80009EB8 8C790000 */  lw         $t9, 0x0($v1)
    /* AABC 80009EBC AFB90030 */  sw         $t9, 0x30($sp)
    /* AAC0 80009EC0 8FAC0030 */  lw         $t4, 0x30($sp)
    /* AAC4 80009EC4 318D0003 */  andi       $t5, $t4, 0x3
    /* AAC8 80009EC8 51A00008 */  beql       $t5, $zero, .L80009EEC
    /* AACC 80009ECC 8D190010 */   lw        $t9, 0x10($t0)
    /* AAD0 80009ED0 8C6E0000 */  lw         $t6, 0x0($v1)
  .L80009ED4:
    /* AAD4 80009ED4 AFAE0030 */  sw         $t6, 0x30($sp)
    /* AAD8 80009ED8 8FAF0030 */  lw         $t7, 0x30($sp)
    /* AADC 80009EDC 31F80003 */  andi       $t8, $t7, 0x3
    /* AAE0 80009EE0 5700FFFC */  bnel       $t8, $zero, .L80009ED4
    /* AAE4 80009EE4 8C6E0000 */   lw        $t6, 0x0($v1)
    /* AAE8 80009EE8 8D190010 */  lw         $t9, 0x10($t0)
  .L80009EEC:
    /* AAEC 80009EEC 3C0DA500 */  lui        $t5, %hi(D_A5000510)
    /* AAF0 80009EF0 00001025 */  or         $v0, $zero, $zero
    /* AAF4 80009EF4 03216025 */  or         $t4, $t9, $at
    /* AAF8 80009EF8 ADAC0510 */  sw         $t4, %lo(D_A5000510)($t5)
    /* AAFC 80009EFC 10000118 */  b          .L8000A360
    /* AB00 80009F00 AD200000 */   sw        $zero, 0x0($t1)
    /* AB04 80009F04 8D020000 */  lw         $v0, 0x0($t0)
  .L80009F08:
    /* AB08 80009F08 24060002 */  addiu      $a2, $zero, 0x2
    /* AB0C 80009F0C 00057100 */  sll        $t6, $a1, 4
    /* AB10 80009F10 14C20003 */  bne        $a2, $v0, .L80009F20
    /* AB14 80009F14 00000000 */   nop
    /* AB18 80009F18 10000111 */  b          .L8000A360
    /* AB1C 80009F1C 24020001 */   addiu     $v0, $zero, 0x1
  .L80009F20:
    /* AB20 80009F20 05C3001F */  bgezl      $t6, .L80009FA0
    /* AB24 80009F24 24010001 */   addiu     $at, $zero, 0x1
    /* AB28 80009F28 8C6F0000 */  lw         $t7, 0x0($v1)
    /* AB2C 80009F2C AFAF0030 */  sw         $t7, 0x30($sp)
    /* AB30 80009F30 8FB80030 */  lw         $t8, 0x30($sp)
    /* AB34 80009F34 240F0016 */  addiu      $t7, $zero, 0x16
    /* AB38 80009F38 33190003 */  andi       $t9, $t8, 0x3
    /* AB3C 80009F3C 53200008 */  beql       $t9, $zero, .L80009F60
    /* AB40 80009F40 8C800000 */   lw        $zero, 0x0($a0)
    /* AB44 80009F44 8C6C0000 */  lw         $t4, 0x0($v1)
  .L80009F48:
    /* AB48 80009F48 AFAC0030 */  sw         $t4, 0x30($sp)
    /* AB4C 80009F4C 8FAD0030 */  lw         $t5, 0x30($sp)
    /* AB50 80009F50 31AE0003 */  andi       $t6, $t5, 0x3
    /* AB54 80009F54 55C0FFFC */  bnel       $t6, $zero, .L80009F48
    /* AB58 80009F58 8C6C0000 */   lw        $t4, 0x0($v1)
    /* AB5C 80009F5C 8C800000 */  lw         $zero, 0x0($a0)
  .L80009F60:
    /* AB60 80009F60 0C002909 */  jal        kernelDiskPostPiEvent
    /* AB64 80009F64 AD2F0000 */   sw        $t7, 0x0($t1)
    /* AB68 80009F68 3C03A460 */  lui        $v1, (0xA4600010 >> 16)
    /* AB6C 80009F6C 34630010 */  ori        $v1, $v1, (0xA4600010 & 0xFFFF)
    /* AB70 80009F70 3C048002 */  lui        $a0, %hi(D_800209E0)
    /* AB74 80009F74 24060002 */  addiu      $a2, $zero, 0x2
    /* AB78 80009F78 248409E0 */  addiu      $a0, $a0, %lo(D_800209E0)
    /* AB7C 80009F7C AC660000 */  sw         $a2, 0x0($v1)
    /* AB80 80009F80 8C980000 */  lw         $t8, 0x0($a0)
    /* AB84 80009F84 3C010010 */  lui        $at, (0x100401 >> 16)
    /* AB88 80009F88 34210401 */  ori        $at, $at, (0x100401 & 0xFFFF)
    /* AB8C 80009F8C 0301C825 */  or         $t9, $t8, $at
    /* AB90 80009F90 AC990000 */  sw         $t9, 0x0($a0)
    /* AB94 80009F94 100000F2 */  b          .L8000A360
    /* AB98 80009F98 24020001 */   addiu     $v0, $zero, 0x1
    /* AB9C 80009F9C 24010001 */  addiu      $at, $zero, 0x1
  .L80009FA0:
    /* ABA0 80009FA0 1441002F */  bne        $v0, $at, .L8000A060
    /* ABA4 80009FA4 00056040 */   sll       $t4, $a1, 1
    /* ABA8 80009FA8 0582001D */  bltzl      $t4, .L8000A020
    /* ABAC 80009FAC 8D2F0004 */   lw        $t7, 0x4($t1)
    /* ABB0 80009FB0 950D0004 */  lhu        $t5, 0x4($t0)
    /* ABB4 80009FB4 8D0F0008 */  lw         $t7, 0x8($t0)
    /* ABB8 80009FB8 3C048002 */  lui        $a0, %hi(D_800209E0)
    /* ABBC 80009FBC 000D7080 */  sll        $t6, $t5, 2
    /* ABC0 80009FC0 01CD7021 */  addu       $t6, $t6, $t5
    /* ABC4 80009FC4 000E7080 */  sll        $t6, $t6, 2
    /* ABC8 80009FC8 01CD7021 */  addu       $t6, $t6, $t5
    /* ABCC 80009FCC 000E7080 */  sll        $t6, $t6, 2
    /* ABD0 80009FD0 01CD7021 */  addu       $t6, $t6, $t5
    /* ABD4 80009FD4 25F80001 */  addiu      $t8, $t7, 0x1
    /* ABD8 80009FD8 11D80006 */  beq        $t6, $t8, .L80009FF4
    /* ABDC 80009FDC 248409E0 */   addiu     $a0, $a0, %lo(D_800209E0)
    /* ABE0 80009FE0 24190018 */  addiu      $t9, $zero, 0x18
    /* ABE4 80009FE4 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* ABE8 80009FE8 AD390000 */   sw        $t9, 0x0($t1)
    /* ABEC 80009FEC 100000DC */  b          .L8000A360
    /* ABF0 80009FF0 24020001 */   addiu     $v0, $zero, 0x1
  .L80009FF4:
    /* ABF4 80009FF4 AC660000 */  sw         $a2, 0x0($v1)
    /* ABF8 80009FF8 8C8C0000 */  lw         $t4, 0x0($a0)
    /* ABFC 80009FFC 3C010010 */  lui        $at, (0x100401 >> 16)
    /* AC00 8000A000 34210401 */  ori        $at, $at, (0x100401 & 0xFFFF)
    /* AC04 8000A004 01816825 */  or         $t5, $t4, $at
    /* AC08 8000A008 AC8D0000 */  sw         $t5, 0x0($a0)
    /* AC0C 8000A00C 0C002909 */  jal        kernelDiskPostPiEvent
    /* AC10 8000A010 AD200000 */   sw        $zero, 0x0($t1)
    /* AC14 8000A014 100000D2 */  b          .L8000A360
    /* AC18 8000A018 24020001 */   addiu     $v0, $zero, 0x1
    /* AC1C 8000A01C 8D2F0004 */  lw         $t7, 0x4($t1)
  .L8000A020:
    /* AC20 8000A020 8D2E000C */  lw         $t6, 0xC($t1)
    /* AC24 8000A024 3C060500 */  lui        $a2, (0x5000400 >> 16)
    /* AC28 8000A028 34C60400 */  ori        $a2, $a2, (0x5000400 & 0xFFFF)
    /* AC2C 8000A02C 01EEC021 */  addu       $t8, $t7, $t6
    /* AC30 8000A030 AD380004 */  sw         $t8, 0x4($t1)
    /* AC34 8000A034 8D190008 */  lw         $t9, 0x8($t0)
    /* AC38 8000A038 24050001 */  addiu      $a1, $zero, 0x1
    /* AC3C 8000A03C 272C0001 */  addiu      $t4, $t9, 0x1
    /* AC40 8000A040 AD0C0008 */  sw         $t4, 0x8($t0)
    /* AC44 8000A044 8D2D000C */  lw         $t5, 0xC($t1)
    /* AC48 8000A048 8D270004 */  lw         $a3, 0x4($t1)
    /* AC4C 8000A04C 8D440000 */  lw         $a0, 0x0($t2)
    /* AC50 8000A050 0C0024EC */  jal        osEPiRawStartDma
    /* AC54 8000A054 AFAD0010 */   sw        $t5, 0x10($sp)
    /* AC58 8000A058 100000C1 */  b          .L8000A360
    /* AC5C 8000A05C 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A060:
    /* AC60 8000A060 144000BC */  bnez       $v0, .L8000A354
    /* AC64 8000A064 240F0004 */   addiu     $t7, $zero, 0x4
    /* AC68 8000A068 950F0004 */  lhu        $t7, 0x4($t0)
    /* AC6C 8000A06C 24070003 */  addiu      $a3, $zero, 0x3
    /* AC70 8000A070 54EF0013 */  bnel       $a3, $t7, .L8000A0C0
    /* AC74 8000A074 8D2F0004 */   lw        $t7, 0x4($t1)
    /* AC78 8000A078 8D380010 */  lw         $t8, 0x10($t1)
    /* AC7C 8000A07C 8D0E0008 */  lw         $t6, 0x8($t0)
    /* AC80 8000A080 00056040 */  sll        $t4, $a1, 1
    /* AC84 8000A084 27190011 */  addiu      $t9, $t8, 0x11
    /* AC88 8000A088 032E082A */  slt        $at, $t9, $t6
    /* AC8C 8000A08C 10200005 */  beqz       $at, .L8000A0A4
    /* AC90 8000A090 00000000 */   nop
    /* AC94 8000A094 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AC98 8000A098 AD200000 */   sw        $zero, 0x0($t1)
    /* AC9C 8000A09C 100000B0 */  b          .L8000A360
    /* ACA0 8000A0A0 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A0A4:
    /* ACA4 8000A0A4 05800009 */  bltz       $t4, .L8000A0CC
    /* ACA8 8000A0A8 240D0017 */   addiu     $t5, $zero, 0x17
    /* ACAC 8000A0AC 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* ACB0 8000A0B0 AD2D0000 */   sw        $t5, 0x0($t1)
    /* ACB4 8000A0B4 100000AA */  b          .L8000A360
    /* ACB8 8000A0B8 24020001 */   addiu     $v0, $zero, 0x1
    /* ACBC 8000A0BC 8D2F0004 */  lw         $t7, 0x4($t1)
  .L8000A0C0:
    /* ACC0 8000A0C0 8D38000C */  lw         $t8, 0xC($t1)
    /* ACC4 8000A0C4 01F87021 */  addu       $t6, $t7, $t8
    /* ACC8 8000A0C8 AD2E0004 */  sw         $t6, 0x4($t1)
  .L8000A0CC:
    /* ACCC 8000A0CC 3C19A500 */  lui        $t9, %hi(D_A5000510)
    /* ACD0 8000A0D0 8F220510 */  lw         $v0, %lo(D_A5000510)($t9)
    /* ACD4 8000A0D4 0005C8C0 */  sll        $t9, $a1, 3
    /* ACD8 8000A0D8 00026280 */  sll        $t4, $v0, 10
    /* ACDC 8000A0DC 05810002 */  bgez       $t4, .L8000A0E8
    /* ACE0 8000A0E0 00026A40 */   sll       $t5, $v0, 9
    /* ACE4 8000A0E4 05A00003 */  bltz       $t5, .L8000A0F4
  .L8000A0E8:
    /* ACE8 8000A0E8 004B7824 */   and       $t7, $v0, $t3
    /* ACEC 8000A0EC 11E00019 */  beqz       $t7, .L8000A154
    /* ACF0 8000A0F0 00000000 */   nop
  .L8000A0F4:
    /* ACF4 8000A0F4 8D240010 */  lw         $a0, 0x10($t1)
    /* ACF8 8000A0F8 2C810004 */  sltiu      $at, $a0, 0x4
    /* ACFC 8000A0FC 5420000E */  bnel       $at, $zero, .L8000A138
    /* AD00 8000A100 8D0C0008 */   lw        $t4, 0x8($t0)
    /* AD04 8000A104 95180004 */  lhu        $t8, 0x4($t0)
    /* AD08 8000A108 54F80006 */  bnel       $a3, $t8, .L8000A124
    /* AD0C 8000A10C 24190017 */   addiu     $t9, $zero, 0x17
    /* AD10 8000A110 8D0E0008 */  lw         $t6, 0x8($t0)
    /* AD14 8000A114 29C10053 */  slti       $at, $t6, 0x53
    /* AD18 8000A118 5420000D */  bnel       $at, $zero, .L8000A150
    /* AD1C 8000A11C 248E0001 */   addiu     $t6, $a0, 0x1
    /* AD20 8000A120 24190017 */  addiu      $t9, $zero, 0x17
  .L8000A124:
    /* AD24 8000A124 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AD28 8000A128 AD390000 */   sw        $t9, 0x0($t1)
    /* AD2C 8000A12C 1000008C */  b          .L8000A360
    /* AD30 8000A130 24020001 */   addiu     $v0, $zero, 0x1
    /* AD34 8000A134 8D0C0008 */  lw         $t4, 0x8($t0)
  .L8000A138:
    /* AD38 8000A138 00047880 */  sll        $t7, $a0, 2
    /* AD3C 8000A13C 012FC021 */  addu       $t8, $t1, $t7
    /* AD40 8000A140 258D0001 */  addiu      $t5, $t4, 0x1
    /* AD44 8000A144 AF0D0014 */  sw         $t5, 0x14($t8)
    /* AD48 8000A148 8D240010 */  lw         $a0, 0x10($t1)
    /* AD4C 8000A14C 248E0001 */  addiu      $t6, $a0, 0x1
  .L8000A150:
    /* AD50 8000A150 AD2E0010 */  sw         $t6, 0x10($t1)
  .L8000A154:
    /* AD54 8000A154 07210034 */  bgez       $t9, .L8000A228
    /* AD58 8000A158 8D020008 */   lw        $v0, 0x8($t0)
    /* AD5C 8000A15C 24010057 */  addiu      $at, $zero, 0x57
    /* AD60 8000A160 1041000C */  beq        $v0, $at, .L8000A194
    /* AD64 8000A164 240C0018 */   addiu     $t4, $zero, 0x18
    /* AD68 8000A168 AD2C0000 */  sw         $t4, 0x0($t1)
    /* AD6C 8000A16C AFA90024 */  sw         $t1, 0x24($sp)
    /* AD70 8000A170 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AD74 8000A174 AFA80028 */   sw        $t0, 0x28($sp)
    /* AD78 8000A178 3C03A460 */  lui        $v1, (0xA4600010 >> 16)
    /* AD7C 8000A17C 3C0A8003 */  lui        $t2, %hi(D_80033524)
    /* AD80 8000A180 254A3524 */  addiu      $t2, $t2, %lo(D_80033524)
    /* AD84 8000A184 34630010 */  ori        $v1, $v1, (0xA4600010 & 0xFFFF)
    /* AD88 8000A188 24060002 */  addiu      $a2, $zero, 0x2
    /* AD8C 8000A18C 8FA80028 */  lw         $t0, 0x28($sp)
    /* AD90 8000A190 8FA90024 */  lw         $t1, 0x24($sp)
  .L8000A194:
    /* AD94 8000A194 950F0004 */  lhu        $t7, 0x4($t0)
    /* AD98 8000A198 24010002 */  addiu      $at, $zero, 0x2
    /* AD9C 8000A19C 3C048002 */  lui        $a0, %hi(D_800209E0)
    /* ADA0 8000A1A0 15E1000F */  bne        $t7, $at, .L8000A1E0
    /* ADA4 8000A1A4 00002825 */   or        $a1, $zero, $zero
    /* ADA8 8000A1A8 950D0006 */  lhu        $t5, 0x6($t0)
    /* ADAC 8000A1AC 24180001 */  addiu      $t8, $zero, 0x1
    /* ADB0 8000A1B0 240EFFFF */  addiu      $t6, $zero, -0x1
    /* ADB4 8000A1B4 15A0000A */  bnez       $t5, .L8000A1E0
    /* ADB8 8000A1B8 00000000 */   nop
    /* ADBC 8000A1BC 8D190040 */  lw         $t9, 0x40($t0)
    /* ADC0 8000A1C0 8D0C0048 */  lw         $t4, 0x48($t0)
    /* ADC4 8000A1C4 A5180006 */  sh         $t8, 0x6($t0)
    /* ADC8 8000A1C8 AD0E0008 */  sw         $t6, 0x8($t0)
    /* ADCC 8000A1CC 032C7823 */  subu       $t7, $t9, $t4
    /* ADD0 8000A1D0 AD0F0040 */  sw         $t7, 0x40($t0)
    /* ADD4 8000A1D4 240D0016 */  addiu      $t5, $zero, 0x16
    /* ADD8 8000A1D8 1000000A */  b          .L8000A204
    /* ADDC 8000A1DC AD2D0000 */   sw        $t5, 0x0($t1)
  .L8000A1E0:
    /* ADE0 8000A1E0 248409E0 */  addiu      $a0, $a0, %lo(D_800209E0)
    /* ADE4 8000A1E4 AC660000 */  sw         $a2, 0x0($v1)
    /* ADE8 8000A1E8 8C980000 */  lw         $t8, 0x0($a0)
    /* ADEC 8000A1EC 3C010010 */  lui        $at, (0x100401 >> 16)
    /* ADF0 8000A1F0 34210401 */  ori        $at, $at, (0x100401 & 0xFFFF)
    /* ADF4 8000A1F4 03017025 */  or         $t6, $t8, $at
    /* ADF8 8000A1F8 AC8E0000 */  sw         $t6, 0x0($a0)
    /* ADFC 8000A1FC AD060000 */  sw         $a2, 0x0($t0)
    /* AE00 8000A200 AD200000 */  sw         $zero, 0x0($t1)
  .L8000A204:
    /* AE04 8000A204 8D39000C */  lw         $t9, 0xC($t1)
    /* AE08 8000A208 8D270008 */  lw         $a3, 0x8($t1)
    /* AE0C 8000A20C 8D440000 */  lw         $a0, 0x0($t2)
    /* AE10 8000A210 00196080 */  sll        $t4, $t9, 2
    /* AE14 8000A214 AFAC0010 */  sw         $t4, 0x10($sp)
    /* AE18 8000A218 0C0024EC */  jal        osEPiRawStartDma
    /* AE1C 8000A21C 3C060500 */   lui       $a2, (0x5000000 >> 16)
    /* AE20 8000A220 1000004F */  b          .L8000A360
    /* AE24 8000A224 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A228:
    /* AE28 8000A228 2401FFFF */  addiu      $at, $zero, -0x1
    /* AE2C 8000A22C 54410027 */  bnel       $v0, $at, .L8000A2CC
    /* AE30 8000A230 244C0001 */   addiu     $t4, $v0, 0x1
    /* AE34 8000A234 950F0004 */  lhu        $t7, 0x4($t0)
    /* AE38 8000A238 24010002 */  addiu      $at, $zero, 0x2
    /* AE3C 8000A23C 55E10023 */  bnel       $t7, $at, .L8000A2CC
    /* AE40 8000A240 244C0001 */   addiu     $t4, $v0, 0x1
    /* AE44 8000A244 950D0006 */  lhu        $t5, 0x6($t0)
    /* AE48 8000A248 24010001 */  addiu      $at, $zero, 0x1
    /* AE4C 8000A24C 55A1001F */  bnel       $t5, $at, .L8000A2CC
    /* AE50 8000A250 244C0001 */   addiu     $t4, $v0, 0x1
    /* AE54 8000A254 8D180028 */  lw         $t8, 0x28($t0)
    /* AE58 8000A258 25030018 */  addiu      $v1, $t0, 0x18
    /* AE5C 8000A25C 57000010 */  bnel       $t8, $zero, .L8000A2A0
    /* AE60 8000A260 AD000018 */   sw        $zero, 0x18($t0)
    /* AE64 8000A264 8C620008 */  lw         $v0, 0x8($v1)
    /* AE68 8000A268 8C4E000C */  lw         $t6, 0xC($v0)
    /* AE6C 8000A26C 8C590000 */  lw         $t9, 0x0($v0)
    /* AE70 8000A270 8C4F0004 */  lw         $t7, 0x4($v0)
    /* AE74 8000A274 8C580008 */  lw         $t8, 0x8($v0)
    /* AE78 8000A278 01D96025 */  or         $t4, $t6, $t9
    /* AE7C 8000A27C 018F6825 */  or         $t5, $t4, $t7
    /* AE80 8000A280 01B87025 */  or         $t6, $t5, $t8
    /* AE84 8000A284 11C00005 */  beqz       $t6, .L8000A29C
    /* AE88 8000A288 24190017 */   addiu     $t9, $zero, 0x17
    /* AE8C 8000A28C 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AE90 8000A290 AC790000 */   sw        $t9, 0x0($v1)
    /* AE94 8000A294 10000032 */  b          .L8000A360
    /* AE98 8000A298 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A29C:
    /* AE9C 8000A29C AD000018 */  sw         $zero, 0x18($t0)
  .L8000A2A0:
    /* AEA0 8000A2A0 AFA90024 */  sw         $t1, 0x24($sp)
    /* AEA4 8000A2A4 AFA80028 */  sw         $t0, 0x28($sp)
    /* AEA8 8000A2A8 0C002909 */  jal        kernelDiskPostPiEvent
    /* AEAC 8000A2AC AFA50034 */   sw        $a1, 0x34($sp)
    /* AEB0 8000A2B0 8FA80028 */  lw         $t0, 0x28($sp)
    /* AEB4 8000A2B4 3C0A8003 */  lui        $t2, %hi(D_80033524)
    /* AEB8 8000A2B8 254A3524 */  addiu      $t2, $t2, %lo(D_80033524)
    /* AEBC 8000A2BC 8FA50034 */  lw         $a1, 0x34($sp)
    /* AEC0 8000A2C0 8FA90024 */  lw         $t1, 0x24($sp)
    /* AEC4 8000A2C4 8D020008 */  lw         $v0, 0x8($t0)
    /* AEC8 8000A2C8 244C0001 */  addiu      $t4, $v0, 0x1
  .L8000A2CC:
    /* AECC 8000A2CC 00057840 */  sll        $t7, $a1, 1
    /* AED0 8000A2D0 05E10015 */  bgez       $t7, .L8000A328
    /* AED4 8000A2D4 AD0C0008 */   sw        $t4, 0x8($t0)
    /* AED8 8000A2D8 29810055 */  slti       $at, $t4, 0x55
    /* AEDC 8000A2DC 14200006 */  bnez       $at, .L8000A2F8
    /* AEE0 8000A2E0 00002825 */   or        $a1, $zero, $zero
    /* AEE4 8000A2E4 24180018 */  addiu      $t8, $zero, 0x18
    /* AEE8 8000A2E8 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AEEC 8000A2EC AD380000 */   sw        $t8, 0x0($t1)
    /* AEF0 8000A2F0 1000001B */  b          .L8000A360
    /* AEF4 8000A2F4 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A2F8:
    /* AEF8 8000A2F8 8D2E000C */  lw         $t6, 0xC($t1)
    /* AEFC 8000A2FC 3C060500 */  lui        $a2, (0x5000400 >> 16)
    /* AF00 8000A300 8D270004 */  lw         $a3, 0x4($t1)
    /* AF04 8000A304 AFA90024 */  sw         $t1, 0x24($sp)
    /* AF08 8000A308 34C60400 */  ori        $a2, $a2, (0x5000400 & 0xFFFF)
    /* AF0C 8000A30C 8D440000 */  lw         $a0, 0x0($t2)
    /* AF10 8000A310 0C0024EC */  jal        osEPiRawStartDma
    /* AF14 8000A314 AFAE0010 */   sw        $t6, 0x10($sp)
    /* AF18 8000A318 8FA90024 */  lw         $t1, 0x24($sp)
    /* AF1C 8000A31C 24020001 */  addiu      $v0, $zero, 0x1
    /* AF20 8000A320 1000000F */  b          .L8000A360
    /* AF24 8000A324 AD200000 */   sw        $zero, 0x0($t1)
  .L8000A328:
    /* AF28 8000A328 8D190008 */  lw         $t9, 0x8($t0)
    /* AF2C 8000A32C 240C0018 */  addiu      $t4, $zero, 0x18
    /* AF30 8000A330 2B210055 */  slti       $at, $t9, 0x55
    /* AF34 8000A334 10200005 */  beqz       $at, .L8000A34C
    /* AF38 8000A338 00000000 */   nop
    /* AF3C 8000A33C 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AF40 8000A340 AD2C0000 */   sw        $t4, 0x0($t1)
    /* AF44 8000A344 10000006 */  b          .L8000A360
    /* AF48 8000A348 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A34C:
    /* AF4C 8000A34C 10000004 */  b          .L8000A360
    /* AF50 8000A350 24020001 */   addiu     $v0, $zero, 0x1
  .L8000A354:
    /* AF54 8000A354 0C0028DC */  jal        kernelDiskResetBufferManagerAndNotify
    /* AF58 8000A358 AD2F0000 */   sw        $t7, 0x0($t1)
    /* AF5C 8000A35C 24020001 */  addiu      $v0, $zero, 0x1
  .L8000A360:
    /* AF60 8000A360 8FBF001C */  lw         $ra, 0x1C($sp)
    /* AF64 8000A364 27BD0038 */  addiu      $sp, $sp, 0x38
    /* AF68 8000A368 03E00008 */  jr         $ra
    /* AF6C 8000A36C 00000000 */   nop
endlabel func_80009DF0

