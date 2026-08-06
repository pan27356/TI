/*****************************************************************************
 * F28003x unified linker command file for PBL / SBL / APP
 *
 * Based on 28003x_generic_flash_lnk.cmd. Select image at build time:
 *
 *   PBL : -DBUILD_PBL  -D_FLASH   (72KB flash @ 0x00080000)
 *   SBL : -DBUILD_SBL              (48KB RAM  @ 0x00008000, no _FLASH)
 *   APP : -DBUILD_APP  -D_FLASH   (flash @ 0x00092000, up to ~120KB on-chip)
 *
 * Upgrade flow: PBL (flash) -> load SBL to RAM -> SBL upgrades APP (flash)
 *
 * Shared addresses: 28003x_boot_memmap_shared.h
 *****************************************************************************/

#if !defined(BUILD_PBL) && !defined(BUILD_SBL) && !defined(BUILD_APP)
#error "Define exactly one of BUILD_PBL, BUILD_SBL, or BUILD_APP"
#endif

MEMORY
{
#if defined(BUILD_SBL)
   PAGE 0:
   BEGIN            : origin = 0x00008000, length = 0x00000002

   /* 48KB SBL pool: LS0..LS7 (16KB) + GS0..GS2 (12KB) + GS3 code (4KB-8B) */
   SBL_RAM_LS0       : origin = 0x00008000, length = 0x00000800
   SBL_RAM_LS1       : origin = 0x00008800, length = 0x00000800
   SBL_RAM_LS2       : origin = 0x00009000, length = 0x00000800
   SBL_RAM_LS3       : origin = 0x00009800, length = 0x00000800
   SBL_RAM_LS4       : origin = 0x0000A000, length = 0x00000800
   SBL_RAM_LS5       : origin = 0x0000A800, length = 0x00000800
   SBL_RAM_LS6       : origin = 0x0000B000, length = 0x00000800
   SBL_RAM_LS7       : origin = 0x0000B800, length = 0x00000800
   SBL_RAM_GS0       : origin = 0x0000C000, length = 0x00001000
   SBL_RAM_GS1       : origin = 0x0000D000, length = 0x00001000
   SBL_RAM_GS2       : origin = 0x0000E000, length = 0x00001000
   SBL_RAM_GS3       : origin = 0x0000F000, length = 0x00000FF0

   PAGE 1:
   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8

   RESET            : origin = 0x003FFFC0, length = 0x00000002

#else /* BUILD_PBL or BUILD_APP */
#if defined(BUILD_PBL)
   BEGIN            : origin = 0x00080000, length = 0x00000002
#else /* BUILD_APP */
   BEGIN            : origin = 0x00092000, length = 0x00000002
#endif
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8

   /* 0x8000 is SBL load/run address; PBL/APP use LS4+ for ramfunc RUN */
   RAMLS4           : origin = 0x0000A000, length = 0x00000800
   RAMLS5           : origin = 0x0000A800, length = 0x00000800
   RAMLS6           : origin = 0x0000B000, length = 0x00000800
   RAMLS7           : origin = 0x0000B800, length = 0x00000800

   RAMLS_RAMFUNC    : origin = 0x0000A000, length = 0x00002000
   RAMLS2           : origin = 0x00009000, length = 0x00000800
   RAMLS3           : origin = 0x00009800, length = 0x00000800

   RAMGS0           : origin = 0x0000C000, length = 0x00001000
   RAMGS1           : origin = 0x0000D000, length = 0x00001000
   RAMGS2           : origin = 0x0000E000, length = 0x00001000
   RAMGS3           : origin = 0x0000F000, length = 0x00000FF0
   PERSIST_RAM      : origin = 0x0000FFF0, length = 0x00000008

   BOOTROM          : origin = 0x003F8000, length = 0x00007FC0
   SECURE_ROM       : origin = 0x003F2000, length = 0x00006000
   RESET            : origin = 0x003FFFC0, length = 0x00000002

#if defined(BUILD_PBL)
   /* PBL: 72KB = Bank0 SEC0..SEC15 + Bank1 SEC0..SEC1 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000
   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000
   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000
   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000
   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000
   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000
   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000
#else /* BUILD_APP */
   /* APP: remaining on-chip flash (~120KB) = Bank1 SEC2..SEC15 + Bank2 */
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x001000
   FLASH_BANK2_SEC0  : origin = 0x0A0000, length = 0x001000
   FLASH_BANK2_SEC1  : origin = 0x0A1000, length = 0x001000
   FLASH_BANK2_SEC2  : origin = 0x0A2000, length = 0x001000
   FLASH_BANK2_SEC3  : origin = 0x0A3000, length = 0x001000
   FLASH_BANK2_SEC4  : origin = 0x0A4000, length = 0x001000
   FLASH_BANK2_SEC5  : origin = 0x0A5000, length = 0x001000
   FLASH_BANK2_SEC6  : origin = 0x0A6000, length = 0x001000
   FLASH_BANK2_SEC7  : origin = 0x0A7000, length = 0x001000
   FLASH_BANK2_SEC8  : origin = 0x0A8000, length = 0x001000
   FLASH_BANK2_SEC9  : origin = 0x0A9000, length = 0x001000
   FLASH_BANK2_SEC10 : origin = 0x0AA000, length = 0x001000
   FLASH_BANK2_SEC11 : origin = 0x0AB000, length = 0x001000
   FLASH_BANK2_SEC12 : origin = 0x0AC000, length = 0x001000
   FLASH_BANK2_SEC13 : origin = 0x0AD000, length = 0x001000
   FLASH_BANK2_SEC14 : origin = 0x0AE000, length = 0x001000
   FLASH_BANK2_SEC15 : origin = 0x0AF000, length = 0x000FF0
#endif
#endif
}

SECTIONS
{
#if defined(BUILD_SBL)
   codestart        : > BEGIN, PAGE = 0, ALIGN(8)

   .TI.ramfunc      : >> SBL_RAM_LS0 | SBL_RAM_LS1, PAGE = 0, ALIGN(8)
   .text            : >> SBL_RAM_LS2 | SBL_RAM_LS3 | SBL_RAM_LS4 |
                        SBL_RAM_LS5 | SBL_RAM_LS6 | SBL_RAM_LS7 |
                        SBL_RAM_GS0 | SBL_RAM_GS1 | SBL_RAM_GS2 |
                        SBL_RAM_GS3, PAGE = 0, ALIGN(8)
   .cinit           : > SBL_RAM_LS0, PAGE = 0, ALIGN(8)
   .switch          : > SBL_RAM_LS0, PAGE = 0, ALIGN(8)
   .reset           : > RESET, PAGE = 0, TYPE = DSECT

   .stack           : > RAMM1, PAGE = 1

#if defined(__TI_EABI__)
   .init_array      : > SBL_RAM_LS1, PAGE = 0, ALIGN(8)
   .bss             : > SBL_RAM_GS2, PAGE = 0
   .bss:output      : > SBL_RAM_GS2, PAGE = 0
   .bss:cio         : > SBL_RAM_GS1, PAGE = 0
   .data            : > SBL_RAM_GS2, PAGE = 0
   .sysmem          : > SBL_RAM_GS1, PAGE = 0
   .const           : > SBL_RAM_GS3, PAGE = 0, ALIGN(8)
#else
   .pinit           : > SBL_RAM_LS1, PAGE = 0, ALIGN(8)
   .ebss            : > SBL_RAM_GS2, PAGE = 0
   .esysmem         : > SBL_RAM_GS1, PAGE = 0
   .cio             : > SBL_RAM_GS1, PAGE = 0
   .econst          : > SBL_RAM_GS3, PAGE = 0, ALIGN(8)
#endif

   IQmath           : > SBL_RAM_GS0, PAGE = 0, ALIGN(8)
   IQmathTables     : > SBL_RAM_GS0, PAGE = 0, ALIGN(8)

#else /* BUILD_PBL or BUILD_APP */
   codestart        : > BEGIN, ALIGN(8)

#if defined(BUILD_PBL)
   .text            : >> FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4 |
                        FLASH_BANK0_SEC5 | FLASH_BANK0_SEC6 | FLASH_BANK0_SEC7 |
                        FLASH_BANK0_SEC8 | FLASH_BANK0_SEC9 | FLASH_BANK0_SEC10 |
                        FLASH_BANK0_SEC11 | FLASH_BANK0_SEC12 | FLASH_BANK0_SEC13 |
                        FLASH_BANK0_SEC14 | FLASH_BANK0_SEC15 |
                        FLASH_BANK1_SEC0 | FLASH_BANK1_SEC1, ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .switch          : > FLASH_BANK0_SEC1,  ALIGN(8)
#else /* BUILD_APP */
   .text            : >> FLASH_BANK1_SEC3 | FLASH_BANK1_SEC4 | FLASH_BANK1_SEC5 |
                        FLASH_BANK1_SEC6 | FLASH_BANK1_SEC7 | FLASH_BANK1_SEC8 |
                        FLASH_BANK1_SEC9 | FLASH_BANK1_SEC10 | FLASH_BANK1_SEC11 |
                        FLASH_BANK1_SEC12 | FLASH_BANK1_SEC13 | FLASH_BANK1_SEC14 |
                        FLASH_BANK1_SEC15 |
                        FLASH_BANK2_SEC0 | FLASH_BANK2_SEC1 | FLASH_BANK2_SEC2 |
                        FLASH_BANK2_SEC3 | FLASH_BANK2_SEC4 | FLASH_BANK2_SEC5 |
                        FLASH_BANK2_SEC6 | FLASH_BANK2_SEC7 | FLASH_BANK2_SEC8 |
                        FLASH_BANK2_SEC9 | FLASH_BANK2_SEC10 | FLASH_BANK2_SEC11 |
                        FLASH_BANK2_SEC12 | FLASH_BANK2_SEC13 | FLASH_BANK2_SEC14 |
                        FLASH_BANK2_SEC15, ALIGN(8)
   .cinit           : > FLASH_BANK1_SEC2,  ALIGN(8)
   .switch          : > FLASH_BANK1_SEC2,  ALIGN(8)
#endif

   .reset           : > RESET, TYPE = DSECT
   .stack           : > RAMM1

#if defined(__TI_EABI__)
#if defined(BUILD_PBL)
   .init_array      : > FLASH_BANK0_SEC1,  ALIGN(8)
   .const           : > FLASH_BANK0_SEC4,  ALIGN(8)
#else
   .init_array      : > FLASH_BANK1_SEC2,  ALIGN(8)
   .const           : > FLASH_BANK2_SEC0,  ALIGN(8)
#endif
   .bss             : > RAMLS5
   .bss:output      : > RAMLS3
   .bss:cio         : > RAMLS2
   .data            : > RAMLS5
   .sysmem          : > RAMGS2
#else
#if defined(BUILD_PBL)
   .pinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .econst          : > FLASH_BANK0_SEC4,  ALIGN(8)
#else
   .pinit           : > FLASH_BANK1_SEC2,  ALIGN(8)
   .econst          : > FLASH_BANK2_SEC0,  ALIGN(8)
#endif
   .ebss            : > RAMLS5
   .esysmem         : > RAMGS2
   .cio             : > RAMLS2
#endif

#if defined(BUILD_PBL)
   IQmath           : > FLASH_BANK0_SEC1, ALIGN(8)
   IQmathTables     : > FLASH_BANK0_SEC2, ALIGN(8)

   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS_RAMFUNC,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)
#else /* BUILD_APP */
   IQmath           : > FLASH_BANK1_SEC2, ALIGN(8)
   IQmathTables     : > FLASH_BANK1_SEC3, ALIGN(8)

   .TI.ramfunc      : LOAD = FLASH_BANK1_SEC2,
                      RUN = RAMLS_RAMFUNC,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)

   .persist         : type = NOINIT > PERSIST_RAM
#endif
#endif
}
