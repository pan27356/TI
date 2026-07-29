//#############################################################################
//
// FILE:   sha_256_ex9_wordwise.c
//
// TITLE:  SHA-256 word-wise
//
//! \addtogroup library_example_c28x_list
//! <h1>SHA256 wordwise Example</h1>
//!
//! This example hashes message and produces message digest using SHA256 
//! algorithm by taking in the message to be hashed wordwise.
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
#include <sha256.h>
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
// SHA-256 word-wise handle
//
SHA256_ObjectWordWise SHA256_Obj;
SHA256_HandleWordWise handle = &SHA256_Obj;

//
// Structure for SHA-256 tests
//
typedef struct
{
    uint16_t dataLength;
    uint32_t plainText[16];
    uint32_t digest[8];
} testVectorSHA256;


//
// Test Cases
//
testVectorSHA256 testVectorSHA256Array[] =
{
 //
 // Test Case #1
 //
 {
  .dataLength = 4U,

  //
  // String "abcd"
  //
  .plainText  = {0x61626364},

  .digest = { 0x88d4266f, 0xd4e6338d, 0x13b845fc,
              0xf289579d, 0x209c8978, 0x23b9217d,
              0xa3e16193, 0x6f031589 }
 },

 //
 // Test Case #2
 //
 {
  .dataLength = 56U,

  .plainText  = {0x61626364, 0x62636465, 0x63646566, 0x64656667,
                 0x65666768, 0x66676869, 0x6768696a, 0x68696a6b,
                 0x696a6b6c, 0x6a6b6c6d, 0x6b6c6d6e, 0x6c6d6e6f,
                 0x6d6e6f70, 0x6e6f7071},

  .digest = { 0x248D6A61, 0xD20638B8, 0xE5C02693,
              0x0C3E6039, 0xA33CE459, 0x64FF2167,
              0xF6ECEDD4, 0x19DB06C1 }
 }
};

void main(void)
{
    uint16_t errCountLocal, cnt;
    uint16_t dataLength;
    uint32_t *expDigest, *plainTextArray;
    uint16_t vectorCnt;
    uint32_t digest[8];

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
        (vectorCnt < (sizeof(testVectorSHA256Array) /
         sizeof(testVectorSHA256Array[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        dataLength         = testVectorSHA256Array[vectorCnt].dataLength;
        plainTextArray     = testVectorSHA256Array[vectorCnt].plainText;
        expDigest = testVectorSHA256Array[vectorCnt].digest;

        //
        // Perform SHA-256
        // Note : For wordwise implementation, dataLength should always 
        // be a multiple of 4
        //
        uint16_t retval = SHA256_hashWordWise(handle,
                                              (uint32_t *)plainTextArray,
                                              dataLength, digest);

        //
        // Check the results
        //
        for(cnt = 0; cnt < 8U; cnt++)
        {
            if(digest[cnt] != expDigest[cnt])
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
