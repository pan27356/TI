//###########################################################################
//
// FILE:   boot_jump.c
//
// TITLE:  Boot chain jump interface
//
//###########################################################################

#include "boot_jump.h"

#include "f28003x_device.h"

#pragma CODE_SECTION(Boot_jumpPrepare, ".TI.ramfunc")

//
// Boot_jumpPrepare - Disable interrupts before handing off to next stage.
//
void Boot_jumpPrepare(void)
{
    DINT;
    IER = 0U;
    IFR = 0U;
}

#pragma CODE_SECTION(Boot_jumpToSbl, ".TI.ramfunc")
#pragma CODE_SECTION(Boot_jumpToApp, ".TI.ramfunc")

//
// Boot_jumpToSbl - Jump to SBL codestart in RAM.
//
void Boot_jumpToSbl(void)
{
    Boot_jumpPrepare();
    Boot_jumpTo(BOOT_SBL_ENTRY_POINT);
}

//
// Boot_jumpToApp - Jump to APP codestart in Flash.
//
void Boot_jumpToApp(void)
{
    Boot_jumpPrepare();
    Boot_jumpTo(BOOT_APP_ENTRY_POINT);
}
