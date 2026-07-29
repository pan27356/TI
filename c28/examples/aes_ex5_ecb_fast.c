//#############################################################################
//
// FILE:   aes_ex5_ecb_fast.c
//
// TITLE:  AES ECB fast
//
//! \addtogroup library_example_c28x_list
//! <h1>AES ECB fast Example</h1>
//!
//! This example encrypts block cipher-text using AES fast implementation in 
//! ECB mode.
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
#include <aes_ecb.h>
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
// Structure for AES ECB tests
//
typedef struct
{
    AES_KeySize keySize;
    AES_OperationMode opMode;
    uint16_t keyArray[32];
    uint16_t dataLength;
    uint16_t plainText[64];
    uint16_t cipherText[64];
} testVectorECB;


//
// Test Cases
//
testVectorECB testVectorECBArray[] =
{
 //
 // Test Case #1
 //
 {
  .keySize = AES_128,

  .opMode = AES_OPMODE_ENCRYPT,

  .keyArray = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
               0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c},

  .dataLength = 4U,

  .plainText  = {0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
                 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                 0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
                 0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                 0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11,
                 0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
                 0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17,
                 0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10},

  .cipherText = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
                 0xf5, 0xd3, 0xd5, 0x85, 0x03, 0xb9, 0x69, 0x9d,
                 0xe7, 0x85, 0x89, 0x5a, 0x96, 0xfd, 0xba, 0xaf,
                 0x43, 0xb1, 0xcd, 0x7f, 0x59, 0x8e, 0xce, 0x23,
                 0x88, 0x1b, 0x00, 0xe3, 0xed, 0x03, 0x06, 0x88,
                 0x7b, 0x0c, 0x78, 0x5e, 0x27, 0xe8, 0xad, 0x3f,
                 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5d, 0xd4}
 },

 //
 // Test Case #2
 //
 {
  .keySize = AES_128,

  .opMode = AES_OPMODE_DECRYPT,

  .keyArray = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
               0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c},

  .dataLength = 4U,

  .plainText  = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
                 0xf5, 0xd3, 0xd5, 0x85, 0x03, 0xb9, 0x69, 0x9d,
                 0xe7, 0x85, 0x89, 0x5a, 0x96, 0xfd, 0xba, 0xaf,
                 0x43, 0xb1, 0xcd, 0x7f, 0x59, 0x8e, 0xce, 0x23,
                 0x88, 0x1b, 0x00, 0xe3, 0xed, 0x03, 0x06, 0x88,
                 0x7b, 0x0c, 0x78, 0x5e, 0x27, 0xe8, 0xad, 0x3f,
                 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5d, 0xd4},

  .cipherText = {0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
                 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                 0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
                 0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                 0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11,
                 0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
                 0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17,
                 0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10}
 }
};

void main(void)
{
    uint16_t errCountLocal, cnt;
    uint16_t *keyArray, dataLength;
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
        (vectorCnt < (sizeof(testVectorECBArray) /
         sizeof(testVectorECBArray[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        keySize  = testVectorECBArray[vectorCnt].keySize;
        opMode  = testVectorECBArray[vectorCnt].opMode;
        keyArray  = testVectorECBArray[vectorCnt].keyArray;
        dataLength         = testVectorECBArray[vectorCnt].dataLength;
        plainTextArray     = testVectorECBArray[vectorCnt].plainText;
        expCipherTextArray = testVectorECBArray[vectorCnt].cipherText;

        //
        // Perform AES-ECB fast
        //
        AES_performECBFast(plainTextArray, dataLength, keyArray,
                           keySize, opMode);

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
