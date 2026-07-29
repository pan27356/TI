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

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************
//
// GPIO29 - GPIO Settings
//
#define CAN_SLP_GPIO_PIN_CONFIG GPIO_29_GPIO29

//
// MCAN -> MCAN_COM Pinmux
//
//
// MCAN_RX - GPIO Settings
//
#define GPIO_PIN_MCAN_RX 5
#define MCAN_COM_MCANRX_GPIO 5
#define MCAN_COM_MCANRX_PIN_CONFIG GPIO_5_MCAN_RX
//
// MCAN_TX - GPIO Settings
//
#define GPIO_PIN_MCAN_TX 4
#define MCAN_COM_MCANTX_GPIO 4
#define MCAN_COM_MCANTX_PIN_CONFIG GPIO_4_MCAN_TX

//
// SPIA -> EEPROM_SPI Pinmux
//
//
// SPIA_PICO - GPIO Settings
//
#define GPIO_PIN_SPIA_PICO 8
#define EEPROM_SPI_SPIPICO_GPIO 8
#define EEPROM_SPI_SPIPICO_PIN_CONFIG GPIO_8_SPIA_SIMO
//
// SPIA_POCI - GPIO Settings
//
#define GPIO_PIN_SPIA_POCI 10
#define EEPROM_SPI_SPIPOCI_GPIO 10
#define EEPROM_SPI_SPIPOCI_PIN_CONFIG GPIO_10_SPIA_SOMI
//
// SPIA_CLK - GPIO Settings
//
#define GPIO_PIN_SPIA_CLK 9
#define EEPROM_SPI_SPICLK_GPIO 9
#define EEPROM_SPI_SPICLK_PIN_CONFIG GPIO_9_SPIA_CLK
//
// SPIA_PTE - GPIO Settings
//
#define GPIO_PIN_SPIA_PTE 11
#define EEPROM_SPI_SPIPTE_GPIO 11
#define EEPROM_SPI_SPIPTE_PIN_CONFIG GPIO_11_SPIA_STE

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define myCPUTIMER0_BASE CPUTIMER0_BASE
void myCPUTIMER0_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define CAN_SLP 29
void CAN_SLP_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myCPUTIMER0
// ISR need to be defined for the registered interrupts
#define INT_myCPUTIMER0 INT_TIMER0
#define INT_myCPUTIMER0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_myCPUTIMER0_ISR(void);

// Interrupt Settings for INT_MCAN_COM_0
// ISR need to be defined for the registered interrupts
#define INT_MCAN_COM_0 INT_MCANA_0
#define INT_MCAN_COM_0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void mcanISR(void);

//*****************************************************************************
//
// MCAN Configurations
//
//*****************************************************************************
#define MCAN_COM_BASE MCANA_DRIVER_BASE
//
// Defines
//
#define MCAN_COM_MCAN_STD_ID_FILTER_NUM          (1)
#define MCAN_COM_MCAN_EXT_ID_FILTER_NUM          (0)
#define MCAN_COM_MCAN_FIFO_0_NUM                 (1)
#define MCAN_COM_MCAN_FIFO_1_NUM                 (0)
#define MCAN_COM_MCAN_TX_BUFF_SIZE               (1)
#define MCAN_COM_MCAN_TX_EVENT_SIZE              (0)

#define MCAN_COM_MCAN_STD_ID_FILT_START_ADDR     (0)
#define MCAN_COM_MCAN_EXT_ID_FILT_START_ADDR     (4)
#define MCAN_COM_MCAN_FIFO_0_START_ADDR          (4)
#define MCAN_COM_MCAN_FIFO_1_START_ADDR          (76)
#define MCAN_COM_MCAN_RX_BUFF_START_ADDR         (76)
#define MCAN_COM_MCAN_TX_BUFF_START_ADDR         (76)
#define MCAN_COM_MCAN_TX_EVENT_START_ADDR        (148)

#define MCAN_COM_MCAN_INTR_LINE_NUM_0_INT (MCAN_IR_RF0N_MASK)
void MCAN_COM_init();

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
#define EEPROM_SPI_BASE SPIA_BASE
#define EEPROM_SPI_BITRATE 1000000
#define EEPROM_SPI_DATAWIDTH 16
void EEPROM_SPI_init();

//*****************************************************************************
//
// WATCHDOG Configurations
//
//*****************************************************************************
#define myWATCHDOG0_PREDIVIDER SYSCTL_WD_PREDIV_512
#define myWATCHDOG0_PRESCALAR SYSCTL_WD_PRESCALE_1
void myWATCHDOG0_init();

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	CPUTIMER_init();
void	GPIO_init();
void	INTERRUPT_init();
void	MCAN_SYSCFG_init();
void	SPI_init();
void	WATCHDOG_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
