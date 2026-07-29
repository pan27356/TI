//#############################################################################
//
// FILE:   aes_ex2_cbc.c
//
// TITLE:  AES CBC
//
//! \addtogroup library_example_c28x_list
//! <h1>AES CBC Example</h1>
//!
//! This example encrypts block cipher-text using AES in CBC mode.
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

  .keyArray = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
               0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c},

  .initVector = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},

  .dataLength = 4U,

  .plainText  = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
                 0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
                 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
                 0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
                 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
                 0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
                 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10},

  .cipherText = {0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46,
                 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
                 0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee,
                 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
                 0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b,
                 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
                 0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09,
                 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7}
 },

 //
 // Test Case #2
 //
 {
  .keySize = AES_128,

  .opMode = AES_OPMODE_DECRYPT,

  .keyArray = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
               0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c},

  .initVector = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},

  .dataLength = 4U,

  .plainText  = {0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46,
                 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
                 0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee,
                 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
                 0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b,
                 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
                 0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09,
                 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7},

  .cipherText = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
                 0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
                 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
                 0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
                 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
                 0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
                 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10}
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
        AES_performCBC(plainTextArray, dataLength, keyArray, keySize, opMode,
                       initVector);

        //
        // Check the results
        //
        for(cnt = 0; cnt < (dataLength * 16U); cnt++)
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
