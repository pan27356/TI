//#############################################################################
//
// FILE:   cancom_util_main.c
//
// This application is intended to be run on a LaunchPad with an on-board
// CAN-FD transceiver such as the LAUNCHXL-F280039C to communicate with another
// device running the tidm_02012_ecompressor project built with CMD_CAN_EN
// turned on.
//
// Watch Variables
// - Use the CCS Expressions view Import option to import
//   solutions\tidm_02012_ecompressor\common\debug\tidm_02012_cancom_util.txt
// - Use flagEnableCmd to enable or disable updates to the transmitted message
// - Use flagCmdRun to update flagEnableRunAndIdentify on the other device
// - Use speedSet_Hz to update speedRef_Hz on the other device
//
////#############################################################################
// $Copyright:
// Copyright (C) 2017-2025 Texas Instruments Incorporated - http://www.ti.com/
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// include the related header files
//
#include "board.h"
#include "device.h"

//
// Defines
//
#define CANCOM_TX_MSG_OBJ_ID            5U
#define CANCOM_BUFFER_NUM               0U
#define CAN_DIAG_FUNCTION_ID            0X7FF
#define CAN_DIAG_PHYSICAL_ID            0X754
#define CAN_DIAG_RESPONSE_ID            0X654

// Globals
//
uint16_t writeBuffer[16] = {100, 101, 102, 103, 104, 105, 106, 107};
uint16_t readBuffer[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
bool flag_write_test = false;
bool flag_read_test = false;
//
// Opcodes for the EEPROM (8-bit)
//
#define RDSR                        0x0500
#define READ                        0x0300
#define WRITE                       0x0200
#define WREN                        0x0606
#define WRDI                        0x0400
#define WRSR                        0x0100
#define EEPROM_ADDRESS              0x000

//
// Function Prototypes
//

uint16_t readStatusRegister(uint16_t statusRegister);
void writeData(uint16_t address, uint16_t *data, uint16_t NumByteToWrite, uint16_t txdly);
void readData(uint16_t address, uint16_t *pBuffer, uint16_t NumByteToRead, uint16_t txdly);
void enableWrite(void);

//
// Typedefs
//
typedef struct _CANCOM_Obj_
{

    uint16_t    txMsgCount;       // for debug
    uint16_t    rxMsgCount;       // for debug
    uint16_t    errorFlag;        // for debug

    uint16_t    waitTimeCnt;
    uint16_t    waitTimeDelay;

    bool    flagRxDone;
    bool    flagTxDone;

    bool    flagCmdTxRun;

    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxBufElement rxMsg_FUNCTION;


}CANCOM_Obj;

//
// Globals
//
volatile CANCOM_Obj canComVars;

float32_t speedSet_Hz = 40.0f;
bool flagEnableCmd = true;
bool flagCmdRun = false;

//
// Function Prototypes
//
__interrupt void mcanISR(void);
__interrupt void INT_myCPUTIMER0_ISR(void);
void CANCOM_init(void);
void CANCOM_updateCANCmdFreq(void);

uint16_t counter_ISR_timer0 = 0;
//
// Main
//
void main(void)
{
    //uint32_t loopCount = 0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANCLK_DIV_3);

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board initialization
    //
    Board_init();

    //
    // initialize the CANCOM object
    //
    CANCOM_init();

    //
    // Enable transmit buffer interrupt
    //
    MCAN_txBufTransIntrEnable(MCAN_COM_BASE, CANCOM_BUFFER_NUM, 1U);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(true)
    {
        SysCtl_serviceWatchdog();
        //
        // Update data to be sent
        //
        CANCOM_updateCANCmdFreq();

        if(flagEnableCmd == true)
        {
            canComVars.flagCmdTxRun = flagCmdRun;
        }

        if(flag_write_test){
            SysCtl_disableWatchdog();
            writeData(EEPROM_ADDRESS,&writeBuffer[0],16,0);
            SysCtl_enableWatchdog();
            flag_write_test = false;
        }

        if(flag_read_test){
            SysCtl_disableWatchdog();
            readData(EEPROM_ADDRESS,&readBuffer[0],16,0);
            SysCtl_enableWatchdog();
            flag_read_test = false;
        }

        //
        // Blink an LED to indicate this loop is running
        //
/*        if(loopCount == 300000)
        {
            //GPIO_togglePin(LED4_GPIO);
            loopCount = 0;
        }
        else
        {
            loopCount++;
        }*/
    }

}

//! \brief      Initializes CAN
//! \param[in]  N/A
void CANCOM_init(void)
{

    canComVars.txMsgCount = 0;                // for debug
    canComVars.rxMsgCount = 0;                // for debug

    canComVars.waitTimeCnt = 1000;            // 1s/1000ms
    canComVars.waitTimeDelay = 2;             // 2ms

    canComVars.flagTxDone = true;             // To enable CAN
    canComVars.flagRxDone = false;

    canComVars.flagCmdTxRun = false;
    //
    // Initialize transmit message element
    //
    canComVars.txMsg.id = ((uint32_t)(CAN_DIAG_RESPONSE_ID) << 18);
    canComVars.txMsg.rtr = 0U;
    canComVars.txMsg.xtd = 0U;  // Standard 11-bit identifier
    canComVars.txMsg.esi = 0U;
    canComVars.txMsg.dlc = 15U;  // 64 bytes
    canComVars.txMsg.brs = 1U;  // Bit-rate switching enabled
    canComVars.txMsg.fdf = 1U;  // Frame transmitted in CAN FD format
    canComVars.txMsg.efc = 1U;
    canComVars.txMsg.mm = 0xAAU;

    //
    // Initialize receive message element
    //
    canComVars.rxMsg.id = 0U;
    canComVars.rxMsg.rtr = 0U;
    canComVars.rxMsg.xtd = 0U;
    canComVars.rxMsg.esi = 0U;
    canComVars.rxMsg.rxts = 0U; // Rx Timestamp
    canComVars.rxMsg.dlc = 0U;
    canComVars.rxMsg.brs = 0U;
    canComVars.rxMsg.fdf = 0U;
    canComVars.rxMsg.fidx = 0U; // Filter Index
                                // (of matching Rx acceptance filter element)
    canComVars.rxMsg.anmf = 0U; // Accepted Non-matching Frame

    return;
} // end of HAL_initCANInt() function

void CANCOM_updateCANCmdFreq(void)
{

    if(canComVars.flagRxDone == true)
    {
        canComVars.flagTxDone = true;
        canComVars.flagRxDone = false;
    }

/*    if((canComVars.flagTxDone == true) && (canComVars.waitTimeCnt == 0))
    {

        //
        // Write message to Message RAM.
        //
        MCAN_writeMsgRam(MCAN_COM_BASE, MCAN_MEM_TYPE_BUF,
             CANCOM_BUFFER_NUM, (const MCAN_TxBufElement *)&canComVars.txMsg);

        //
        // Add transmission request for Tx buffer 0
        //
        MCAN_txBufAddReq(MCAN_COM_BASE, CANCOM_BUFFER_NUM);

        canComVars.waitTimeCnt = canComVars.waitTimeDelay;
        canComVars.flagTxDone = false;
    }*/

    if(canComVars.waitTimeCnt > 0)
    {
        canComVars.waitTimeCnt--;
    }

    return;
}

__interrupt void mcanISR(void)
{
    uint32_t status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    status = MCAN_getIntrStatus(MCAN_COM_BASE);

    //
    // Interrupt was caused by completed transmission
    //
    if((status & MCAN_INTR_SRC_TRANS_COMPLETE) != 0U)
    {
        // Increment a counter to keep track of how many messages have been
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        canComVars.txMsgCount++;

        // Since the message was sent, clear any error flags.
        canComVars.errorFlag = 0;
    }
    //
    // Interrupt was caused by a new message in the Rx FIFO
    //
    else if((status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) != 0U)
    //else if((status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO0_NEW_MSG)

    {
        // Get the received message
        MCAN_readMsgRam(MCAN_COM_BASE, MCAN_MEM_TYPE_FIFO, 0U, MCAN_RX_FIFO_NUM_0,
                        (MCAN_RxBufElement *)&canComVars.rxMsg);
        MCAN_writeRxFIFOAck(MCAN_COM_BASE, MCAN_RX_FIFO_NUM_0, 0);

        canComVars.rxMsgCount++;
        canComVars.flagRxDone = true;

        // Since the message was received, clear any error flags.
        canComVars.errorFlag = 0;
    }
    //
    // If something unexpected caused the interrupt, this would handle it.
    //
    else
    {
        // Spurious interrupt handling can go here.
        canComVars.errorFlag++;
    }

    //
    // Clear the interrupt flags for the MCAN interrupt line
    //
    MCAN_clearIntrStatus(MCAN_COM_BASE, status);
    MCAN_extTSWriteEOI(MCAN_COM_BASE);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    return;
}

// send CANFD message every 100ms
__interrupt void INT_myCPUTIMER0_ISR(void)
{
    counter_ISR_timer0++;

    if(counter_ISR_timer0 >= 100)
    {
        //
        // Write message to Message RAM.
        //
        MCAN_writeMsgRam(MCAN_COM_BASE, MCAN_MEM_TYPE_BUF,
             CANCOM_BUFFER_NUM, (const MCAN_TxBufElement *)&canComVars.txMsg);

        //
        // Add transmission request for Tx buffer 0
        //
        MCAN_txBufAddReq(MCAN_COM_BASE, CANCOM_BUFFER_NUM);

        counter_ISR_timer0 = 0;
    }

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
    ;
}

//
// Function to send RDSR opcode and return the status of the EEPROM
//
uint16_t readStatusRegister(uint16_t statusRegister)
{
    ;
}

//
// Function to send the WREN opcode
//
void enableWrite(void)
{
    uint32_t base = SPIA_BASE;
    uint16_t n = 0;

    // reset the Rx fifo pointer to zero
    SPI_resetRxFIFO(base);
    SPI_enableFIFO(base);

    // wait for registers to update
    for(n = 0; n < 0x0FF; n++)
    {
        __asm(" NOP");
    }

    // write the command
    SPI_writeDataNonBlocking(base, WREN);


    // wait for registers to update
    for(n = 0; n < 0x0FF; n++)
    {
        __asm(" NOP");
    }

    return;
}

//
// Function to write data to the EEPROM
// - address is the byte address of the EEPROM
// - data is a pointer to an array of data being sent
// - length is the number of characters in the array to send
//
void writeData(uint16_t address, uint16_t *data, uint16_t NumByteToWrite, uint16_t txdly)
{
    uint32_t base = SPIA_BASE;

    uint16_t i,n = 0;

    // Send the write enable opcode
    enableWrite();

    // Send the WRITE opcode + address MSB(8bit)
    SPI_writeDataNonBlocking(base, (WRITE|((address&0xFF00)>>8)));
    // Send the WRITE address LSB(8bit) + first data
    SPI_writeDataNonBlocking(base, ((address&0xFF)<< 8)|(data[0]&0xFF));

    for(i=0;i<((NumByteToWrite-1)>>1);i++)
    {
        SPI_writeDataNonBlocking(base, ((data[i*2+1]&0xFF)<<8)|(data[i*2+2]&0xFF));
    }

    if((NumByteToWrite-1)%2 == 0x01u)
    {
        SPI_writeDataNonBlocking(base, ((data[NumByteToWrite-1]&0xFF)<< 8));

    }

    // wait for registers to update
     for(n = 0; n < 0x0FF; n++)
     {
         __asm(" NOP");
     }

}

//
// Function to read data from the EEPROM
// - address is the byte address of the EEPROM
// - data is a pointer to an array of data being received
// - length is the number of characters in the array to receive
//
void readData(uint16_t address, uint16_t *pBuffer, uint16_t NumByteToRead, uint16_t txdly)
{
    uint32_t base = SPIA_BASE;

    uint16_t i;
    uint16_t n;

    uint16_t writetimes=0;
    uint16_t readdata=0;

    volatile uint16_t WaitTimeOut = 0;
    volatile SPI_RxFIFOLevel RxFifoCnt = SPI_FIFO_RXEMPTY;

    writetimes = (NumByteToRead-1)>>1;

    // reset the Rx fifo pointer to zero
    SPI_resetRxFIFO(base);
    SPI_enableFIFO(base);

    // wait for registers to update
    for(n = 0; n < 0x06; n++)
    {
        __asm(" NOP");
    }

    // disable global interrupts
    //
    //Interrupt_disableMaster();

    // write the command
    SPI_writeDataNonBlocking(base, (READ|((address&0xFF00)>>8)));

    // write the address
    // SPI_writeDataNonBlocking(obj->spiHandle, (ReadAddr&0xFF00));
    SPI_writeDataNonBlocking(base, ((address&0xFF) << 8));


    for(i=0;i<writetimes;i++)
    {
        SPI_writeDataNonBlocking(base, 0x0000);
    }

    if((NumByteToRead-1)%2 == 0x01u)
    {
        SPI_writeDataNonBlocking(base, 0x0000);
    }

    // enable global interrupts
    //
    //Interrupt_enableMaster();

    SPI_readDataBlockingFIFO(base);
    pBuffer[0] = SPI_readDataBlockingFIFO(base)&0xFF;

    for(i=0;i<writetimes;i++)
    {
        readdata = SPI_readDataBlockingFIFO(base);
        pBuffer[i*2+1] = ((readdata&0xFF00)>>8);
        pBuffer[i*2+2] = (readdata&0xFF);
    }

    if((NumByteToRead-1)%2 == 0x01u)
    {
        pBuffer[NumByteToRead-1] = (SPI_readDataBlockingFIFO(base)&0xFF00)>>8;
    }

    for(n = 0; n < 0x03FF; n++)
    {
        __asm(" NOP");
    }

}

//
//-- end of this file ----------------------------------------------------------
//
