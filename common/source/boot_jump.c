//###########################################################################
//
// FILE:   boot_jump.c
//
// TITLE:  Boot jump to APP (single C function)
//
// Note: TI inline asm does not allow LB/LCR/RET. Use SETC OBJMODE + call.
//
//###########################################################################

#include "boot_jump.h"

#include "f28003x_device.h"

#define APP_ENTRY_POINT    0x092000U

#pragma CODE_SECTION(JumpToApp, ".TI.ramfunc")

void JumpToApp(void)
{
    void (*appEntry)(void);

    DINT;
    IER = 0U;
    IFR = 0U;

    __asm(" SETC OBJMODE");
    __asm(" NOP");

    appEntry = (void (*)(void))APP_ENTRY_POINT;
    appEntry();
}
