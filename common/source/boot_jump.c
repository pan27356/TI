//###########################################################################
//
// FILE:   boot_jump.c
//
// TITLE:  Boot jump to APP (single function)
//
//###########################################################################

#include "boot_jump.h"

#include "f28003x_device.h"

#define APP_ENTRY_POINT    0x092000U

#pragma CODE_SECTION(JumpToApp, ".TI.ramfunc")

void JumpToApp(void)
{
    DINT;
    IER = 0U;
    IFR = 0U;

    asm(" SETC  OBJMODE");
    asm(" NOP");
    asm(" MOVL  XAR7, #0x92000");
    asm(" LB    *XAR7");
}
