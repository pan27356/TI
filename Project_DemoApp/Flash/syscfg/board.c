/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	CPUTIMER_init();
	GPIO_init();
	MCAN_SYSCFG_init();
	WATCHDOG_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	// GPIO29 -> CAN_SLP Pinmux
	GPIO_setPinConfig(GPIO_29_GPIO29);
	//
	// MCAN -> MCAN_COM Pinmux
	//
	GPIO_setPinConfig(MCAN_COM_MCANRX_PIN_CONFIG);
	GPIO_setPadConfig(MCAN_COM_MCANRX_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MCAN_COM_MCANRX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(MCAN_COM_MCANTX_PIN_CONFIG);
	GPIO_setPadConfig(MCAN_COM_MCANTX_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(MCAN_COM_MCANTX_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	myCPUTIMER0_init();
}

void myCPUTIMER0_init(){
	CPUTimer_setEmulationMode(myCPUTIMER0_BASE, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
	CPUTimer_setPreScaler(myCPUTIMER0_BASE, 0U);
	CPUTimer_setPeriod(myCPUTIMER0_BASE, 120000U);
	CPUTimer_enableInterrupt(myCPUTIMER0_BASE);
	CPUTimer_stopTimer(myCPUTIMER0_BASE);

	CPUTimer_reloadTimerCounter(myCPUTIMER0_BASE);
	CPUTimer_startTimer(myCPUTIMER0_BASE);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	CAN_SLP_init();
}

void CAN_SLP_init(){
	GPIO_writePin(CAN_SLP, 1);
	GPIO_setPadConfig(CAN_SLP, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(CAN_SLP, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(CAN_SLP, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(CAN_SLP, GPIO_CORE_CPU1);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Settings for INT_myCPUTIMER0
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_myCPUTIMER0, &INT_myCPUTIMER0_ISR);
	Interrupt_enable(INT_myCPUTIMER0);
	
	// Interrupt Settings for INT_MCAN_COM_0
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_MCAN_COM_0, &mcanISR);
	Interrupt_enable(INT_MCAN_COM_0);
}
//*****************************************************************************
//
// MCAN Configurations
//
//*****************************************************************************
void MCAN_SYSCFG_init(){
    MCAN_COM_init();
}

void MCAN_COM_init(){
    MCAN_RevisionId revid_MCAN_COM;
    MCAN_InitParams initParams_MCAN_COM;
    MCAN_ConfigParams configParams_MCAN_COM;
    MCAN_StdMsgIDFilterElement stdFiltelem_MCAN_COM;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams_MCAN_COM;
    MCAN_BitTimingParams       bitTimes_MCAN_COM;
    //
    // Initialize MCAN Init parameters.
    //
    initParams_MCAN_COM.fdMode            = true;
    initParams_MCAN_COM.brsEnable         = true;
    initParams_MCAN_COM.txpEnable         = false;
    initParams_MCAN_COM.efbi              = false;
    initParams_MCAN_COM.pxhddisable       = true;
    initParams_MCAN_COM.darEnable         = false;
    initParams_MCAN_COM.wkupReqEnable     = true;
    initParams_MCAN_COM.autoWkupEnable    = true;
    initParams_MCAN_COM.emulationEnable   = false;
    initParams_MCAN_COM.tdcEnable         = true;
    initParams_MCAN_COM.wdcPreload        = 0;
    //
    // Transmitter Delay Compensation parameters.
    //
    initParams_MCAN_COM.tdcConfig.tdcf    = 10;
    initParams_MCAN_COM.tdcConfig.tdco    = 6;
    //
    // Initialize MCAN Config parameters.
    //
    configParams_MCAN_COM.monEnable         = false;
    configParams_MCAN_COM.asmEnable         = false;
    configParams_MCAN_COM.tsPrescalar       = 15;
    configParams_MCAN_COM.tsSelect          = 0;
    configParams_MCAN_COM.timeoutSelect     = MCAN_TIMEOUT_SELECT_CONT;
    configParams_MCAN_COM.timeoutPreload    = 65535;
    configParams_MCAN_COM.timeoutCntEnable  = false;
    configParams_MCAN_COM.filterConfig.rrfs = false;
    configParams_MCAN_COM.filterConfig.rrfe = true;
    configParams_MCAN_COM.filterConfig.anfe = 0;
    configParams_MCAN_COM.filterConfig.anfs = 0;
    //
    // Initialize Message RAM Sections Configuration Parameters.
    //
    msgRAMConfigParams_MCAN_COM.flssa                = MCAN_COM_MCAN_STD_ID_FILT_START_ADDR;
    //
    // Standard ID Filter List Start Address.
    //
    msgRAMConfigParams_MCAN_COM.lss                  = MCAN_COM_MCAN_STD_ID_FILTER_NUM;
    //
    // List Size: Standard ID.
    //
    msgRAMConfigParams_MCAN_COM.flesa                = MCAN_COM_MCAN_EXT_ID_FILT_START_ADDR;
    //
    // Extended ID Filter List Start Address.
    //
    msgRAMConfigParams_MCAN_COM.lse                  = MCAN_COM_MCAN_EXT_ID_FILTER_NUM;
    //
    // List Size: Extended ID.
    //
    msgRAMConfigParams_MCAN_COM.txStartAddr          = MCAN_COM_MCAN_TX_BUFF_START_ADDR;
    //
    // Tx Buffers Start Address.
    //
    msgRAMConfigParams_MCAN_COM.txBufNum             = MCAN_COM_MCAN_TX_BUFF_SIZE;
    //
    // Number of Dedicated Transmit Buffers.
    //
    msgRAMConfigParams_MCAN_COM.txFIFOSize           = 0;
    msgRAMConfigParams_MCAN_COM.txBufMode            = 0;
    msgRAMConfigParams_MCAN_COM.txBufElemSize        = 7;
    //
    // Tx Buffer Element Size.
    //
    msgRAMConfigParams_MCAN_COM.txEventFIFOStartAddr = MCAN_COM_MCAN_TX_EVENT_START_ADDR;
    //
    // Tx Event FIFO Start Address.
    //
    msgRAMConfigParams_MCAN_COM.txEventFIFOSize      = MCAN_COM_MCAN_TX_EVENT_SIZE;
    //
    // Event FIFO Size.
    //
    msgRAMConfigParams_MCAN_COM.txEventFIFOWaterMark = 0;
    //
    // Level for Tx Event FIFO watermark interrupt.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO0startAddr     = MCAN_COM_MCAN_FIFO_0_START_ADDR;
    //
    // Rx FIFO0 Start Address.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO0size          = MCAN_COM_MCAN_FIFO_0_NUM;
    //
    // Number of Rx FIFO elements.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO0waterMark     = 0; // Rx FIFO0 Watermark.
    msgRAMConfigParams_MCAN_COM.rxFIFO0OpMode        = 0;
    msgRAMConfigParams_MCAN_COM.rxFIFO1startAddr     = MCAN_COM_MCAN_FIFO_1_START_ADDR;
    //
    // Rx FIFO1 Start Address.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO1size          = MCAN_COM_MCAN_FIFO_1_NUM;
    //
    // Number of Rx FIFO elements.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO1waterMark     = 0; // Level for Rx FIFO 1
                                                  // watermark interrupt.
    msgRAMConfigParams_MCAN_COM.rxFIFO1OpMode        = 0; // FIFO blocking mode.
    msgRAMConfigParams_MCAN_COM.rxBufStartAddr       = MCAN_COM_MCAN_RX_BUFF_START_ADDR;
    //
    // Rx Buffer Start Address.
    //
    msgRAMConfigParams_MCAN_COM.rxBufElemSize        = 7;
    //
    // Rx Buffer Element Size.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO0ElemSize      = 7;
    //
    // Rx FIFO0 Element Size.
    //
    msgRAMConfigParams_MCAN_COM.rxFIFO1ElemSize      = 7;
    //
    // Rx FIFO1 Element Size.
    //
    //
    // Initialize bit timings.
    //
    bitTimes_MCAN_COM.nomRatePrescalar   = 3; // Nominal Baud Rate Pre-scaler.
    bitTimes_MCAN_COM.nomTimeSeg1        = 14; // Nominal Time segment before sample point.
    bitTimes_MCAN_COM.nomTimeSeg2        = 3; // Nominal Time segment after sample point.
    bitTimes_MCAN_COM.nomSynchJumpWidth  = 2; // Nominal (Re)Synchronization Jump Width Range.
    bitTimes_MCAN_COM.dataRatePrescalar  = 0; // Data Baud Rate Pre-scaler.
    bitTimes_MCAN_COM.dataTimeSeg1       = 12; // Data Time segment before sample point.
    bitTimes_MCAN_COM.dataTimeSeg2       = 5; // Data Time segment after sample point.
    bitTimes_MCAN_COM.dataSynchJumpWidth = 4; // Data (Re)Synchronization Jump Width.
    //
    // Get MCANSS Revision ID.
    //
    MCAN_getRevisionId(MCAN_COM_BASE, &revid_MCAN_COM);
    //
    // Wait for Memory initialization to be completed.
    //
    while(0 == MCAN_isMemInitDone(MCAN_COM_BASE));
    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCAN_COM_BASE, MCAN_OPERATION_MODE_SW_INIT);
    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCAN_COM_BASE));
    //
    // Initialize MCAN module.
    //
    MCAN_init(MCAN_COM_BASE, &initParams_MCAN_COM);
    //
    // Configure MCAN module.
    //
    MCAN_config(MCAN_COM_BASE, &configParams_MCAN_COM);
    //
    // Configure Bit timings.
    //
    MCAN_setBitTime(MCAN_COM_BASE, &bitTimes_MCAN_COM);
    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCAN_COM_BASE, &msgRAMConfigParams_MCAN_COM);

    stdFiltelem_MCAN_COM.sft = MCAN_STDFILT_RANGE;
    stdFiltelem_MCAN_COM.sfec = MCAN_STDFILTEC_FIFO1;
    stdFiltelem_MCAN_COM.sfid1 = 0;
    stdFiltelem_MCAN_COM.sfid2 = 0;

    //
    // Configure Standard ID filter element 1
    //
    MCAN_addStdMsgIDFilter(MCAN_COM_BASE, 1U, &stdFiltelem_MCAN_COM);
    //
    // Internal loopback mode
    //
    MCAN_lpbkModeEnable(MCAN_COM_BASE, MCAN_LPBK_MODE_EXTERNAL, false);
    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCAN_COM_BASE, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCAN_COM_BASE));
    //
    // Enable MCAN Interrupts
    //
    MCAN_enableIntr(MCAN_COM_BASE, MCAN_INTR_MASK_ALL, 1U);
    MCAN_selectIntrLine(MCAN_COM_BASE, MCAN_IR_RF0N_MASK, MCAN_INTR_LINE_NUM_0);
    MCAN_enableIntrLine(MCAN_COM_BASE, MCAN_INTR_LINE_NUM_0, 1U);
}

//*****************************************************************************
//
// WATCHDOG Configurations
//
//*****************************************************************************
void WATCHDOG_init(){
	myWATCHDOG0_init();
}

void myWATCHDOG0_init(){
	SysCtl_disableWatchdog();
	SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);
	SysCtl_setWatchdogPredivider(SYSCTL_WD_PREDIV_512);
	SysCtl_setWatchdogPrescaler(SYSCTL_WD_PRESCALE_1);
	SysCtl_setWatchdogWindowValue(0);
	SysCtl_delay(6);
	SysCtl_enableWatchdog();
}

