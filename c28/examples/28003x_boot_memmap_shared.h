//#############################################################################
//
// FILE:   28003x_boot_memmap_shared.h
//
// TITLE:  Shared flash/RAM addresses for PBL / SBL / APP (F28003x).
//
// Upgrade flow: PBL (flash) -> SBL (RAM) -> APP (flash)
//
// Linker: use 28003x_boot_lnk.cmd with BUILD_PBL / BUILD_SBL / BUILD_APP.
//
//#############################################################################

#ifndef BOOT_MEMMAP_SHARED_H
#define BOOT_MEMMAP_SHARED_H

//
// PBL: 72KB in flash, entry @ BEGIN (codestart).
//
#define PBL_FLASH_START           0x00080000UL
#define PBL_FLASH_SIZE            0x00012000UL   // 72KB
#define PBL_FLASH_END             (PBL_FLASH_START + PBL_FLASH_SIZE - 1UL)

//
// APP: logical 200KB partition; on F28003x on-chip flash after PBL is ~120KB.
//
#define APP_FLASH_START           (PBL_FLASH_START + PBL_FLASH_SIZE)   // 0x00092000
#define APP_FLASH_SIZE            0x00032000UL   // 200KB (logical budget)
#define APP_FLASH_ONCHIP_SIZE     0x0001E000UL   // ~120KB physical on F28003x
#define APP_FLASH_END             (APP_FLASH_START + APP_FLASH_ONCHIP_SIZE - 1UL)

//
// SBL: 48KB budget, loaded and executed from 0x00008000 by PBL.
// On-chip LS+GS RAM is 32KB (0x8000..0xFFEF); keep linked SBL <= 32KB unless
// your part provides additional RAM.
//
#define SBL_RAM_START             0x00008000UL
#define SBL_RAM_SIZE              0x0000C000UL   // 48KB (design budget)
#define SBL_RAM_ONCHIP_SIZE       0x00008000UL   // 32KB linkable on F28003x
#define SBL_RAM_END               (SBL_RAM_START + SBL_RAM_ONCHIP_SIZE - 1UL)

#define SBL_ENTRY_POINT           SBL_RAM_START

#endif // BOOT_MEMMAP_SHARED_H
