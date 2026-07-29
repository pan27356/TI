//#############################################################################
//
// FILE:   aes_ex11_cbc_packed.c
//
// TITLE:  AES CBC
//
//! \addtogroup library_example_c28x_list
//! <h1>AES CBC Example</h1>
//!
//! This example encrypts block cipher-text using AES in CBC mode with 16-bit
//! packed input plaintext and key.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b errCountGlobal - Error Counter. It should be zero.
//! - \b testStatusGlobal - Test status. It should be equal to PASS.
//!
//
//#############################################################################
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
//
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
// Included Files
//
#include <aes_cbc.h>
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

//
// Global Variables
//

//
// Global error counter & status
//
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;

//
// Structure for AES CBC tests
//
typedef struct
{
    AES_KeySize keySize;
    AES_OperationMode opMode;
    uint16_t keyArray[32];
    uint16_t initVector[16];
    uint16_t dataLength;
    uint16_t plainText[64];
    uint16_t cipherText[64];
} testVectorCBC;


//
// Test Cases
//
testVectorCBC testVectorCBCArray[] =
{
 //
 // Test Case #1
 //
 {
  .keySize = AES_128,

  .opMode = AES_OPMODE_ENCRYPT,

  .keyArray = {0x2b7e, 0x1516, 0x28ae, 0xd2a6,
               0xabf7, 0x1588, 0x09cf, 0x4f3c},

  .initVector = {0x0001, 0x0203, 0x0405, 0x0607,
                 0x0809, 0x0A0B, 0x0C0D, 0x0E0F},

  .dataLength = 4U,

  .plainText  = {0x6bc1, 0xbee2, 0x2e40, 0x9f96,
                 0xe93d, 0x7e11, 0x7393, 0x172a,
                 0xae2d, 0x8a57, 0x1e03, 0xac9c,
                 0x9eb7, 0x6fac, 0x45af, 0x8e51,
                 0x30c8, 0x1c46, 0xa35c, 0xe411,
                 0xe5fb, 0xc119, 0x1a0a, 0x52ef,
                 0xf69f, 0x2445, 0xdf4f, 0x9b17,
                 0xad2b, 0x417b, 0xe66c, 0x3710},

  .cipherText = {0x7649, 0xabac, 0x8119, 0xb246,
                 0xcee9, 0x8e9b, 0x12e9, 0x197d,
                 0x5086, 0xcb9b, 0x5072, 0x19ee,
                 0x95db, 0x113a, 0x9176, 0x78b2,
                 0x73be, 0xd6b8, 0xe3c1, 0x743b,
                 0x7116, 0xe69e, 0x2222, 0x9516,
                 0x3ff1, 0xcaa1, 0x681f, 0xac09,
                 0x120e, 0xca30, 0x7586, 0xe1a7}
 },

 //
 // Test Case #2
 //
 {
  .keySize = AES_128,

  .opMode = AES_OPMODE_DECRYPT,

  .keyArray = {0x2b7e, 0x1516, 0x28ae, 0xd2a6,
               0xabf7, 0x1588, 0x09cf, 0x4f3c},

  .initVector = {0x0001, 0x0203, 0x0405, 0x0607,
                 0x0809, 0x0A0B, 0x0C0D, 0x0E0F},

  .dataLength = 4U,

  .plainText  = {0x7649, 0xabac, 0x8119, 0xb246,
                 0xcee9, 0x8e9b, 0x12e9, 0x197d,
                 0x5086, 0xcb9b, 0x5072, 0x19ee,
                 0x95db, 0x113a, 0x9176, 0x78b2,
                 0x73be, 0xd6b8, 0xe3c1, 0x743b,
                 0x7116, 0xe69e, 0x2222, 0x9516,
                 0x3ff1, 0xcaa1, 0x681f, 0xac09,
                 0x120e, 0xca30, 0x7586, 0xe1a7},

  .cipherText = {0x6bc1, 0xbee2, 0x2e40, 0x9f96,
                 0xe93d, 0x7e11, 0x7393, 0x172a,
                 0xae2d, 0x8a57, 0x1e03, 0xac9c,
                 0x9eb7, 0x6fac, 0x45af, 0x8e51,
                 0x30c8, 0x1c46, 0xa35c, 0xe411,
                 0xe5fb, 0xc119, 0x1a0a, 0x52ef,
                 0xf69f, 0x2445, 0xdf4f, 0x9b17,
                 0xad2b, 0x417b, 0xe66c, 0x3710}
 }
};

void main(void)
{
    uint16_t errCountLocal, cnt;
    uint16_t *keyArray, *initVector, dataLength;
    uint16_t *expCipherTextArray, *plainTextArray;
    uint16_t vectorCnt;
    AES_KeySize keySize;
    AES_OperationMode opMode;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize local variables.
    //
    errCountLocal = 0;

    //
    // Loop through all the given vectors.
    //
    for(vectorCnt = 0;
        (vectorCnt < (sizeof(testVectorCBCArray) /
         sizeof(testVectorCBCArray[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        keySize  = testVectorCBCArray[vectorCnt].keySize;
        opMode  = testVectorCBCArray[vectorCnt].opMode;
        keyArray  = testVectorCBCArray[vectorCnt].keyArray;
        initVector = testVectorCBCArray[vectorCnt].initVector;
        dataLength         = testVectorCBCArray[vectorCnt].dataLength;
        plainTextArray     = testVectorCBCArray[vectorCnt].plainText;
        expCipherTextArray = testVectorCBCArray[vectorCnt].cipherText;

        //
        // Perform AES-CBC
        //
        AES_performCBCFast(plainTextArray, dataLength, keyArray, keySize, opMode,
                       initVector);

        //
        // Check the results
        //
        for(cnt = 0; cnt < (dataLength * 8U); cnt++)
        {
            if(plainTextArray[cnt] != expCipherTextArray[cnt])
            {
                errCountLocal++;
            }
        }

        //
        // Update the global error counter.
        //
        if(errCountLocal > 0)
        {
            errCountGlobal++;
        }

        //
        // Clear the local error counter.
        //
        errCountLocal = 0;
    }

    //
    // Update test status variable
    //
    if(errCountGlobal == 0)
    {
        testStatusGlobal = TEST_PASS;
    }
    else
    {
        testStatusGlobal = TEST_FAIL;
    }

    //
    // Infinite Loop to keep the core running
    //
    while(1)
    {
    }
}

//
// End of file
//
