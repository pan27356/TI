/*****************************************************************************
 * FILE:    f28003x_boot_chain_lnk.cmd
 * TITLE:   Shared linker for PBL + SBL + APP boot chain (F28003x)
 *
 * Layout:
 *   PBL (Flash) : 0x080000 - 0x091FFF  (72 KB, 18 x 4KB sectors)
 *   APP (Flash) : 0x092000 - 0x0C3FFF  (200 KB, 50 x 4KB sectors)
 *   SBL (RAM)   : 0x008000 - 0x013FFF  (48 KB run / load region)
 *
 * Boot flow: PBL -> SBL (RAM) -> APP
 *
 * CCS usage — add ONE define in Project Properties -> Build -> Linker -> Advanced Options -> Command File Preprocessing:
 *   PBL project : --define=BUILD_PBL
 *   SBL project : --define=BUILD_SBL
 *   APP project : --define=BUILD_APP
 *
 * All projects:
 *   - Link f28003x_codestartbranch.asm
 *   - Linker entry : -e code_start
 *
 * Jump addresses (for C code):
 *   SBL entry : 0x008000  (after PBL loads SBL image into RAM)
 *   APP entry : 0x092000  (APP codestart / BEGIN)
 *****************************************************************************/

#if !defined(BUILD_PBL) && !defined(BUILD_SBL) && !defined(BUILD_APP)
--error "Define exactly one of: BUILD_PBL, BUILD_SBL, BUILD_APP"
#endif

#if defined(BUILD_PBL)
#define BEGIN_ORIGIN            0x00080000
#elif defined(BUILD_APP)
#define BEGIN_ORIGIN            0x00092000
#endif

/* Exported constants for boot source code */
SBL_RUN_START   = 0x008000;
SBL_RUN_SIZE    = 0x00C000;
APP_RUN_START   = 0x092000;
APP_RUN_SIZE    = 0x032000;
PBL_FLASH_START = 0x080000;
PBL_FLASH_SIZE  = 0x012000;

MEMORY
{
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8

   /* SBL run region (48 KB). PBL must not use 0x8000-0x13FFF when loading SBL. */
   SBL_RAM          : origin = 0x00008000, length = 0x0000C000

#if !defined(BUILD_SBL)
   BEGIN            : origin = BEGIN_ORIGIN, length = 0x00000002
#endif

   /* Remaining on-chip RAM (for PBL / APP; not used by SBL link map) */
   RAMLS5           : origin = 0x0000A800, length = 0x00000800
   RAMLS6           : origin = 0x0000B000, length = 0x00000800
   RAMLS7           : origin = 0x0000B800, length = 0x00000800
   RAMGS0           : origin = 0x0000C000, length = 0x00001000
   RAMGS1           : origin = 0x0000D000, length = 0x00001000
   RAMGS2           : origin = 0x0000E000, length = 0x00001000
   RAMGS3           : origin = 0x0000F000, length = 0x00000FF8

   BOOTROM          : origin = 0x003F8000, length = 0x00007FC0
   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* -------- PBL Flash: 72 KB (0x080000 - 0x091FFF) -------- */
   FLASH_PBL_SEC0   : origin = 0x080002, length = 0x000FFE
   FLASH_PBL_SEC1   : origin = 0x081000, length = 0x001000
   FLASH_PBL_SEC2   : origin = 0x082000, length = 0x001000
   FLASH_PBL_SEC3   : origin = 0x083000, length = 0x001000
   FLASH_PBL_SEC4   : origin = 0x084000, length = 0x001000
   FLASH_PBL_SEC5   : origin = 0x085000, length = 0x001000
   FLASH_PBL_SEC6   : origin = 0x086000, length = 0x001000
   FLASH_PBL_SEC7   : origin = 0x087000, length = 0x001000
   FLASH_PBL_SEC8   : origin = 0x088000, length = 0x001000
   FLASH_PBL_SEC9   : origin = 0x089000, length = 0x001000
   FLASH_PBL_SEC10  : origin = 0x08A000, length = 0x001000
   FLASH_PBL_SEC11  : origin = 0x08B000, length = 0x001000
   FLASH_PBL_SEC12  : origin = 0x08C000, length = 0x001000
   FLASH_PBL_SEC13  : origin = 0x08D000, length = 0x001000
   FLASH_PBL_SEC14  : origin = 0x08E000, length = 0x001000
   FLASH_PBL_SEC15  : origin = 0x08F000, length = 0x001000
   FLASH_PBL_SEC16  : origin = 0x090000, length = 0x001000
   FLASH_PBL_SEC17  : origin = 0x091000, length = 0x001000

   /* -------- APP Flash: 200 KB (0x092000 - 0x0C3FFF) -------- */
   FLASH_APP_SEC0   : origin = 0x092002, length = 0x000FFE
   FLASH_APP_SEC1   : origin = 0x093000, length = 0x001000
   FLASH_APP_SEC2   : origin = 0x094000, length = 0x001000
   FLASH_APP_SEC3   : origin = 0x095000, length = 0x001000
   FLASH_APP_SEC4   : origin = 0x096000, length = 0x001000
   FLASH_APP_SEC5   : origin = 0x097000, length = 0x001000
   FLASH_APP_SEC6   : origin = 0x098000, length = 0x001000
   FLASH_APP_SEC7   : origin = 0x099000, length = 0x001000
   FLASH_APP_SEC8   : origin = 0x09A000, length = 0x001000
   FLASH_APP_SEC9   : origin = 0x09B000, length = 0x001000
   FLASH_APP_SEC10  : origin = 0x09C000, length = 0x001000
   FLASH_APP_SEC11  : origin = 0x09D000, length = 0x001000
   FLASH_APP_SEC12  : origin = 0x09E000, length = 0x001000
   FLASH_APP_SEC13  : origin = 0x09F000, length = 0x001000
   FLASH_APP_SEC14  : origin = 0x0A0000, length = 0x001000
   FLASH_APP_SEC15  : origin = 0x0A1000, length = 0x001000
   FLASH_APP_SEC16  : origin = 0x0A2000, length = 0x001000
   FLASH_APP_SEC17  : origin = 0x0A3000, length = 0x001000
   FLASH_APP_SEC18  : origin = 0x0A4000, length = 0x001000
   FLASH_APP_SEC19  : origin = 0x0A5000, length = 0x001000
   FLASH_APP_SEC20  : origin = 0x0A6000, length = 0x001000
   FLASH_APP_SEC21  : origin = 0x0A7000, length = 0x001000
   FLASH_APP_SEC22  : origin = 0x0A8000, length = 0x001000
   FLASH_APP_SEC23  : origin = 0x0A9000, length = 0x001000
   FLASH_APP_SEC24  : origin = 0x0AA000, length = 0x001000
   FLASH_APP_SEC25  : origin = 0x0AB000, length = 0x001000
   FLASH_APP_SEC26  : origin = 0x0AC000, length = 0x001000
   FLASH_APP_SEC27  : origin = 0x0AD000, length = 0x001000
   FLASH_APP_SEC28  : origin = 0x0AE000, length = 0x001000
   FLASH_APP_SEC29  : origin = 0x0AF000, length = 0x000FF0
   /* Bank3 — confirm sector map on your specific F28003x part */
   FLASH_APP_SEC30  : origin = 0x0B0000, length = 0x001000
   FLASH_APP_SEC31  : origin = 0x0B1000, length = 0x001000
   FLASH_APP_SEC32  : origin = 0x0B2000, length = 0x001000
   FLASH_APP_SEC33  : origin = 0x0B3000, length = 0x001000
   FLASH_APP_SEC34  : origin = 0x0B4000, length = 0x001000
   FLASH_APP_SEC35  : origin = 0x0B5000, length = 0x001000
   FLASH_APP_SEC36  : origin = 0x0B6000, length = 0x001000
   FLASH_APP_SEC37  : origin = 0x0B7000, length = 0x001000
   FLASH_APP_SEC38  : origin = 0x0B8000, length = 0x001000
   FLASH_APP_SEC39  : origin = 0x0B9000, length = 0x001000
   FLASH_APP_SEC40  : origin = 0x0BA000, length = 0x001000
   FLASH_APP_SEC41  : origin = 0x0BB000, length = 0x001000
   FLASH_APP_SEC42  : origin = 0x0BC000, length = 0x001000
   FLASH_APP_SEC43  : origin = 0x0BD000, length = 0x001000
   FLASH_APP_SEC44  : origin = 0x0BE000, length = 0x001000
   FLASH_APP_SEC45  : origin = 0x0BF000, length = 0x001000
   FLASH_APP_SEC46  : origin = 0x0C0000, length = 0x001000
   FLASH_APP_SEC47  : origin = 0x0C1000, length = 0x001000
   FLASH_APP_SEC48  : origin = 0x0C2000, length = 0x001000
   FLASH_APP_SEC49  : origin = 0x0C3000, length = 0x001000
}

#if defined(BUILD_PBL)

SECTIONS
{
   codestart        : > BEGIN, ALIGN(8)
   .text            : >> FLASH_PBL_SEC2 | FLASH_PBL_SEC3 | FLASH_PBL_SEC4 |
                       FLASH_PBL_SEC5 | FLASH_PBL_SEC6 | FLASH_PBL_SEC7 |
                       FLASH_PBL_SEC8 | FLASH_PBL_SEC9 | FLASH_PBL_SEC10 |
                       FLASH_PBL_SEC11 | FLASH_PBL_SEC12 | FLASH_PBL_SEC13 |
                       FLASH_PBL_SEC14 | FLASH_PBL_SEC15 | FLASH_PBL_SEC16 |
                       FLASH_PBL_SEC17, ALIGN(8)
   .cinit           : > FLASH_PBL_SEC1,  ALIGN(8)
   .switch          : > FLASH_PBL_SEC1,  ALIGN(8)
   .reset           : > RESET, TYPE = DSECT

   /* Keep 0x8000-0x13FFF free for SBL download */
   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_PBL_SEC1,  ALIGN(8)
   .bss             : > RAMGS0
   .bss:output      : > RAMGS1
   .bss:cio         : > RAMGS2
   .data            : > RAMGS0
   .sysmem          : > RAMGS0
   .const           : > FLASH_PBL_SEC4,  ALIGN(8)
#else
   .pinit           : > FLASH_PBL_SEC1,  ALIGN(8)
   .ebss            : > RAMGS0
   .esysmem         : > RAMGS0
   .cio             : > RAMGS2
   .econst          : > FLASH_PBL_SEC4,  ALIGN(8)
#endif

   .TI.ramfunc      : LOAD = FLASH_PBL_SEC1,
                      RUN = RAMGS3,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)
}

#elif defined(BUILD_SBL)

SECTIONS
{
   codestart        : > SBL_RAM, ALIGN(8)
   .text            : >> SBL_RAM, ALIGN(8)
   .cinit           : > SBL_RAM, ALIGN(8)
   .switch          : > SBL_RAM, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > SBL_RAM, ALIGN(8)
   .bss             : > SBL_RAM
   .bss:output      : > SBL_RAM
   .bss:cio         : > SBL_RAM
   .data            : > SBL_RAM
   .sysmem          : > SBL_RAM
   .const           : > SBL_RAM, ALIGN(8)
#else
   .pinit           : > SBL_RAM, ALIGN(8)
   .ebss            : > SBL_RAM
   .esysmem         : > SBL_RAM
   .cio             : > SBL_RAM
   .econst          : > SBL_RAM, ALIGN(8)
#endif
}

#elif defined(BUILD_APP)

SECTIONS
{
   codestart        : > BEGIN, ALIGN(8)
   .text            : >> FLASH_APP_SEC2 | FLASH_APP_SEC3 | FLASH_APP_SEC4 |
                       FLASH_APP_SEC5 | FLASH_APP_SEC6 | FLASH_APP_SEC7 |
                       FLASH_APP_SEC8 | FLASH_APP_SEC9 | FLASH_APP_SEC10 |
                       FLASH_APP_SEC11 | FLASH_APP_SEC12 | FLASH_APP_SEC13 |
                       FLASH_APP_SEC14 | FLASH_APP_SEC15 | FLASH_APP_SEC16 |
                       FLASH_APP_SEC17 | FLASH_APP_SEC18 | FLASH_APP_SEC19 |
                       FLASH_APP_SEC20 | FLASH_APP_SEC21 | FLASH_APP_SEC22 |
                       FLASH_APP_SEC23 | FLASH_APP_SEC24 | FLASH_APP_SEC25 |
                       FLASH_APP_SEC26 | FLASH_APP_SEC27 | FLASH_APP_SEC28 |
                       FLASH_APP_SEC29 | FLASH_APP_SEC30 | FLASH_APP_SEC31 |
                       FLASH_APP_SEC32 | FLASH_APP_SEC33 | FLASH_APP_SEC34 |
                       FLASH_APP_SEC35 | FLASH_APP_SEC36 | FLASH_APP_SEC37 |
                       FLASH_APP_SEC38 | FLASH_APP_SEC39 | FLASH_APP_SEC40 |
                       FLASH_APP_SEC41 | FLASH_APP_SEC42 | FLASH_APP_SEC43 |
                       FLASH_APP_SEC44 | FLASH_APP_SEC45 | FLASH_APP_SEC46 |
                       FLASH_APP_SEC47 | FLASH_APP_SEC48 | FLASH_APP_SEC49, ALIGN(8)
   .cinit           : > FLASH_APP_SEC1,  ALIGN(8)
   .switch          : > FLASH_APP_SEC1,  ALIGN(8)
   .reset           : > RESET, TYPE = DSECT

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_APP_SEC1,  ALIGN(8)
   .bss             : > RAMLS5
   .bss:output      : > RAMLS6
   .bss:cio         : > RAMLS7
   .data            : > RAMLS5
   .sysmem          : > RAMLS5
   .const           : > FLASH_APP_SEC4,  ALIGN(8)
#else
   .pinit           : > FLASH_APP_SEC1,  ALIGN(8)
   .ebss            : > RAMLS5
   .esysmem         : > RAMLS5
   .cio             : > RAMLS7
   .econst          : > FLASH_APP_SEC4,  ALIGN(8)
#endif

   .TI.ramfunc      : LOAD = FLASH_APP_SEC1,
                      RUN = SBL_RAM,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)
}

#endif
