//###########################################################################
//
// FILE:   boot_handoff.c
//
// TITLE:  Clear CAN/MCAN state left by Boot before APP runs
//
//###########################################################################

#include "boot_handoff.h"

#include "driverlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#define BOOT_MCAN_MEM_INIT_TIMEOUT   1000000U

#pragma CODE_SECTION(Boot_deinitCanBeforeJump, ".TI.ramfunc")
#pragma CODE_SECTION(Boot_mcanPrepareAppInit, ".TI.ramfunc")

//
// Boot_deinitCanBeforeJump - Stop CAN traffic and reset peripherals before jump.
//
void Boot_deinitCanBeforeJump(void)
{
    Interrupt_disable(INT_MCANA_0);
    Interrupt_disable(INT_MCANA_1);
    Interrupt_disable(INT_MCANA_WAKE);
    Interrupt_disable(INT_MCANA_ECC);
    Interrupt_disable(INT_CANA0);
    Interrupt_disable(INT_CANA1);

    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_MCANA);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CANA);
}

//
// Boot_mcanPrepareAppInit - Soft-reset MCAN and wait for message RAM init in APP.
//
void Boot_mcanPrepareAppInit(void)
{
    uint32_t timeout = BOOT_MCAN_MEM_INIT_TIMEOUT;

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANA);

    if(SysCtl_isMCANWakeStatusSet())
    {
        SysCtl_clearMCANWakeStatus();
    }

    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_MCANA);

    while((MCAN_isMemInitDone(MCANA_DRIVER_BASE) == 0U) && (timeout > 0U))
    {
        timeout--;
        SysCtl_delay(1U);
    }
}
