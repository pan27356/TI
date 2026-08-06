//###########################################################################
//
// FILE:   boot_jump.h
//
// TITLE:  Boot jump to APP (implementation in boot_jump.asm)
//
//###########################################################################

#ifndef BOOT_JUMP_H
#define BOOT_JUMP_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Jump to APP codestart at 0x092000 (change APP_ENTRY_POINT in boot_jump.asm
// if your linker BEGIN address differs). Does not return.
//
// CCS: add common/source/boot_jump.asm to the project (required for link).
//      #include this header in .c files; do not duplicate extern in .c if you
//      already include boot_jump.h.
//
extern void JumpToApp(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_JUMP_H */

