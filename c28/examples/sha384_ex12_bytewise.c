//#############################################################################
//
// FILE:   sha_384_ex12_bytewise.c
//
// TITLE:  SHA-384 bytewise
//
//! \addtogroup library_example_c28x_list
//! <h1>SHA384 bytewise Example</h1>
//!
//! This example hashes message and produces message digest using SHA384 
//! algorithm by taking in the message to be hashed bytewise.
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
#include <sha384.h>
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
// SHA-384 byte-wise handle
//
SHA384_ObjectByteWise SHA384_Obj;
SHA384_HandleByteWise handle = &SHA384_Obj;

//
// Structure for SHA-384 tests
//
typedef struct
{
    uint16_t dataLength;
    char plainText[128];
    uint64_t digest[6];
} testVectorSHA384;


//
// Test Cases
//
testVectorSHA384 testVectorSHA384Array[] =
{
 //
 // Test Case #1
 //
 {
  .dataLength = 3U,

  .plainText  = "abc",

  .digest = {0xCB00753F45A35E8B, 0xB5A03D699AC65007, 0x272C32AB0EDED163,
             0x1A8B605A43FF5BED, 0x8086072BA1E7CC23, 0x58BAECA134C825A7}
 },

 //
 // Test Case #2
 //
 {
  .dataLength = 128U,

  .plainText  = { 0x3b, 0xf5, 0x2c, 0xc5, 0xee, 0x86, 0xb9, 0xa0,
                  0x19, 0x0f, 0x39, 0x0a, 0x5c, 0x03, 0x66, 0xa5,
                  0x60, 0xb5, 0x57, 0x00, 0x0d, 0xbe, 0x51, 0x15,
                  0xfd, 0x9e, 0xe1, 0x16, 0x30, 0xa6, 0x27, 0x69,
                  0x01, 0x15, 0x75, 0xf1, 0x58, 0x81, 0x19, 0x8f,
                  0x22, 0x78, 0x76, 0xe8, 0xfe, 0x68, 0x5a, 0x69,
                  0x39, 0xbc, 0x8b, 0x89, 0xfd, 0x48, 0xa3, 0x4e,
                  0xc5, 0xe7, 0x1e, 0x13, 0x14, 0x62, 0xb2, 0x88,
                  0x67, 0x94, 0xdf, 0xfa, 0x68, 0xcc, 0xc6, 0xd5,
                  0x64, 0x73, 0x3e, 0x67, 0xff, 0xef, 0x25, 0xe6,
                  0x27, 0xc6, 0xf4, 0xb5, 0x46, 0x07, 0x96, 0xe3,
                  0xbc, 0xe6, 0x7b, 0xf5, 0x8c, 0xa6, 0xe8, 0xe5,
                  0x55, 0xbc, 0x91, 0x6a, 0x85, 0x31, 0x69, 0x7a,
                  0xc9, 0x48, 0xb9, 0x0d, 0xc8, 0x61, 0x6f, 0x25,
                  0x10, 0x1d, 0xb9, 0x0b, 0x50, 0xc3, 0xd3, 0xdb,
                  0xc9, 0xe2, 0x1e, 0x42, 0xff, 0x38, 0x71, 0x87 },

  .digest = { 0x12b6cb35eda92ee3, 0x7356ddee77781a17, 0xb3d90e563824a984,
              0xfaffc6fdd1693bd7, 0x626039635563cfc3, 0xb9a2b00f9c65eefd }
 }
};

void main(void)
{
    uint16_t errCountLocal, cnt;
    uint16_t dataLength;
    uint64_t *expDigest;
    uint16_t *plainTextArray;
    uint16_t vectorCnt;
    uint64_t digest[6];

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
        (vectorCnt < (sizeof(testVectorSHA384Array) /
         sizeof(testVectorSHA384Array[0]))); vectorCnt++)
    {
        //
        // Get the current vector's data members.
        //
        dataLength         = testVectorSHA384Array[vectorCnt].dataLength;
        plainTextArray     = (uint16_t *)testVectorSHA384Array[vectorCnt].plainText;
        expDigest = testVectorSHA384Array[vectorCnt].digest;

        //
        // Perform SHA-384
        //
        uint16_t retval = SHA384_hashByteWise(handle,
                                              (uint16_t *)plainTextArray,
                                              dataLength, digest);

        //
        // Check the results
        //
        for(cnt = 0; cnt < 6U; cnt++)
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
