nonmatching __osTimerServicesInit, 0x8C

glabel __osTimerServicesInit
    /* 95C0 800089C0 3C018003 */  lui        $at, %hi(__osCurrentTime + 0x4)
    /* 95C4 800089C4 240E0000 */  addiu      $t6, $zero, 0x0
    /* 95C8 800089C8 240F0000 */  addiu      $t7, $zero, 0x0
    /* 95CC 800089CC AC2F22C4 */  sw         $t7, %lo(__osCurrentTime + 0x4)($at)
    /* 95D0 800089D0 AC2E22C0 */  sw         $t6, %lo(__osCurrentTime)($at)
    /* 95D4 800089D4 3C018003 */  lui        $at, %hi(__osBaseCounter)
    /* 95D8 800089D8 3C188002 */  lui        $t8, %hi(D_80020AF0)
    /* 95DC 800089DC 8F180AF0 */  lw         $t8, %lo(D_80020AF0)($t8)
    /* 95E0 800089E0 AC2022C8 */  sw         $zero, %lo(__osBaseCounter)($at)
    /* 95E4 800089E4 3C018003 */  lui        $at, %hi(__osViIntrCount)
    /* 95E8 800089E8 AC2022CC */  sw         $zero, %lo(__osViIntrCount)($at)
    /* 95EC 800089EC 3C198002 */  lui        $t9, %hi(D_80020AF0)
    /* 95F0 800089F0 AF180004 */  sw         $t8, 0x4($t8)
    /* 95F4 800089F4 8F390AF0 */  lw         $t9, %lo(D_80020AF0)($t9)
    /* 95F8 800089F8 3C098002 */  lui        $t1, %hi(D_80020AF0)
    /* 95FC 800089FC 240A0000 */  addiu      $t2, $zero, 0x0
    /* 9600 80008A00 8F280004 */  lw         $t0, 0x4($t9)
    /* 9604 80008A04 240B0000 */  addiu      $t3, $zero, 0x0
    /* 9608 80008A08 3C0C8002 */  lui        $t4, %hi(D_80020AF0)
    /* 960C 80008A0C AF280000 */  sw         $t0, 0x0($t9)
    /* 9610 80008A10 8D290AF0 */  lw         $t1, %lo(D_80020AF0)($t1)
    /* 9614 80008A14 3C0D8002 */  lui        $t5, %hi(D_80020AF0)
    /* 9618 80008A18 3C188002 */  lui        $t8, %hi(D_80020AF0)
    /* 961C 80008A1C AD2A0010 */  sw         $t2, 0x10($t1)
    /* 9620 80008A20 AD2B0014 */  sw         $t3, 0x14($t1)
    /* 9624 80008A24 8D8C0AF0 */  lw         $t4, %lo(D_80020AF0)($t4)
    /* 9628 80008A28 8D8E0010 */  lw         $t6, 0x10($t4)
    /* 962C 80008A2C 8D8F0014 */  lw         $t7, 0x14($t4)
    /* 9630 80008A30 AD8E0008 */  sw         $t6, 0x8($t4)
    /* 9634 80008A34 AD8F000C */  sw         $t7, 0xC($t4)
    /* 9638 80008A38 8DAD0AF0 */  lw         $t5, %lo(D_80020AF0)($t5)
    /* 963C 80008A3C ADA00018 */  sw         $zero, 0x18($t5)
    /* 9640 80008A40 8F180AF0 */  lw         $t8, %lo(D_80020AF0)($t8)
    /* 9644 80008A44 03E00008 */  jr         $ra
    /* 9648 80008A48 AF00001C */   sw        $zero, 0x1C($t8)
endlabel __osTimerServicesInit
