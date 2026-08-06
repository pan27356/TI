/*****************************************************************************
 * SBL (boot2) wrapper - RAM execution @ 0x00008000.
 * CCS: use this file OR 28003x_boot_lnk.cmd with -DBUILD_SBL (no _FLASH)
 *****************************************************************************/
#define BUILD_SBL
#include "28003x_boot_lnk.cmd"
