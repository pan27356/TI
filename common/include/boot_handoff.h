//###########################################################################
//
// FILE:   boot_handoff.h
//
// TITLE:  Peripheral handoff helpers for Boot -> APP jump (MCAN/CAN cleanup)
//
//###########################################################################

#ifndef BOOT_HANDOFF_H
#define BOOT_HANDOFF_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Call in Boot immediately before JumpToApp() if Boot used CAN/MCAN.
//
extern void Boot_deinitCanBeforeJump(void);

//
// Call at the very beginning of APP CAN/MCAN driver init (before MCAN_init).
//
extern void Boot_mcanPrepareAppInit(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_HANDOFF_H */
