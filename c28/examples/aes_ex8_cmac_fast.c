//#############################################################################
//
// FILE:   aes_ex8_cmac_fast.c
//
// TITLE:  AES CMAC_fast
//
//! \addtogroup library_example_c28x_list
//! <h1>AES CMAC fast Example</h1>
//!
//! This example encrypts block cipher-text using AES fast implementation in 
//! CMAC mode to generate a message authentication code.
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
#include <aes_cmac.h>
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
// Structure for AES CMAC tests
//
typedef struct
{
    AES_KeySize keySize;
    uint16_t keyArray[32];
    uint16_t dataLength;
    uint16_t plainText[64];
    uint16_t tag[16];
} testVectorCMAC;


//
// Test Cases
//
testVectorCMAC testVectorCMACArray[] =
{
 //
 // Test Case #1
 //
 {
  .keySize = AES_128,

  .keyArray = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
               0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c},

  .dataLength = 4U,

  .plainText  = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
                 0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
                 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
                 0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
                 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
                 0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
                 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10},

  .tag = {0x51, 0xf0, 0xbe, 0xbf, 0x7e, 0x3b, 0x9d, 0x92,
          0xfc, 0x49, 0x74, 0x17, 0x79, 0x36, 0x3c, 0xfe}
 },

 //
 // Test Case #1
 //
 {
  .keySize = AES_256,

  .keyArray = {0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
               0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
               0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
               0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4},

  .dataLength = 4U,

  .plainText  = {0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
                 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                 0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
                 0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                 0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11,
                 0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
                 0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17,
                 0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10},

  .tag = {0xe1, 0x99, 0x21, 0x90, 0x54, 0x9f, 0x6e, 0xd5,
          0x69, 0x6a, 0x2c, 0x05, 0x6c, 0x31, 0x54, 0x10}
 }
};

void main(void)
{
    uint16_t errCountLocal, cnt;
    uint16_t *keyArray, dataLength;
    uint16_t *expTag, *plainTextArray;
    uint16_t vectorCnt;
    AES_KeySize keySize;

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
        (vectorCnt < (sizeof(testVectorCMACArray) /
         sizeof(testVectorCMACArray[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        keySize  = testVectorCMACArray[vectorCnt].keySize;
        keyArray  = testVectorCMACArray[vectorCnt].keyArray;
        dataLength         = testVectorCMACArray[vectorCnt].dataLength;
        plainTextArray     = testVectorCMACArray[vectorCnt].plainText;
        expTag = testVectorCMACArray[vectorCnt].tag;

        //
        // Perform AES-CMAC fast
        //
        uint16_t *tag = AES_performCMACFast(plainTextArray, dataLength,
                                            keyArray,keySize);

        //
        // Check the results
        //
        for(cnt = 0; cnt < 16U; cnt++)
        {
            if(tag[cnt] != expTag[cnt])
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
