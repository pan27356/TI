//###########################################################################
//
// FILE:   boot_jump.h
//
// TITLE:  Boot chain jump interface (PBL -> SBL -> APP)
//
//###########################################################################

#ifndef BOOT_JUMP_H
#define BOOT_JUMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//
// Entry addresses — must match common/cmd/f28003x_boot_chain_lnk.cmd
//
#define BOOT_SBL_ENTRY_POINT    0x008000U
#define BOOT_APP_ENTRY_POINT    0x092000U

//
// Disable interrupts and clear pending flags before a non-returning jump.
//
extern void Boot_jumpPrepare(void);

//
// Long-branch (LB) to codestart at entryPoint. Does not return.
// entryPoint must be the target image BEGIN / code_start address.
//
extern void Boot_jumpTo(uint32_t entryPoint);

//
// Jump to SBL (RAM, 0x008000) or APP (Flash, 0x092000).
//
extern void Boot_jumpToSbl(void);
extern void Boot_jumpToApp(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_JUMP_H */
