//#############################################################################
//
// FILE:   sha_384_ex13_wordwise.c
//
// TITLE:  SHA-384 word-wise
//
//! \addtogroup library_example_c28x_list
//! <h1>SHA384 wordwise Example</h1>
//!
//! This example hashes message and produces message digest using SHA384 
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
// SHA-384 word-wise handle
//
SHA384_ObjectWordWise SHA384_Obj;
SHA384_HandleWordWise handle = &SHA384_Obj;

//
// Structure for SHA-384 tests
//
typedef struct
{
    uint16_t dataLength;
    uint32_t plainText[32];
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
  .dataLength = 4U,

  //
  // String "abcd"
  //
  .plainText  = {0x61626364},

  .digest = {0x1165b3406ff0b52a, 0x3d24721f785462ca, 0x2276c9f454a116c2,
             0xb2ba20171a7905ea, 0x5a026682eb659c4d, 0x5f115c363aa3c79b}
 },

 //
 // Test Case #2
 //
 {
  .dataLength = 128U,

  .plainText  = { 0x3bf52cc5, 0xee86b9a0,
                  0x190f390a, 0x5c0366a5,
                  0x60b55700, 0x0dbe5115,
                  0xfd9ee116, 0x30a62769,
                  0x011575f1, 0x5881198f,
                  0x227876e8, 0xfe685a69,
                  0x39bc8b89, 0xfd48a34e,
                  0xc5e71e13, 0x1462b288,
                  0x6794dffa, 0x68ccc6d5,
                  0x64733e67, 0xffef25e6,
                  0x27c6f4b5, 0x460796e3,
                  0xbce67bf5, 0x8ca6e8e5,
                  0x55bc916a, 0x8531697a,
                  0xc948b90d, 0xc8616f25,
                  0x101db90b, 0x50c3d3db,
                  0xc9e21e42, 0xff387187 },

  .digest = { 0x12b6cb35eda92ee3, 0x7356ddee77781a17, 0xb3d90e563824a984,
              0xfaffc6fdd1693bd7, 0x626039635563cfc3, 0xb9a2b00f9c65eefd}
 }
};

void main(void)
{
    uint16_t errCountLocal, cnt;
    uint16_t dataLength;
    uint64_t *expDigest;
    uint32_t *plainTextArray;
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
        plainTextArray     = testVectorSHA384Array[vectorCnt].plainText;
        expDigest = testVectorSHA384Array[vectorCnt].digest;

        //
        // Perform SHA-384
        // Note : For wordwise implementation, dataLength should always 
        // be a multiple of 4
        //
        uint16_t retval = SHA384_hashWordWise(handle,
                                              (uint32_t *)plainTextArray,
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
