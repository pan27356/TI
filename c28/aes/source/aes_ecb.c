//###########################################################################
//
// FILE:   aes_ecb.c
//
// TITLE:  Implementation of the AES ECB mode
//
//###########################################################################
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
//###########################################################################

#include "aes_ecb.h"

//*****************************************************************************
//
// ECB_splitText - Split text into 128 bit blocks based on blockNumber
//
//*****************************************************************************
void ECB_splitText(uint16_t *text, uint16_t *output, uint16_t blockNumber)
{
    int16_t i;

    #ifndef MEM_PACKED_SPEED_OPT
    for(i = 0; i < 16; i++)
    {
        output[i] = text[(16 * blockNumber) + i];
    }
    #else
    for(i = 0; i < 8; i++)
    {
        output[i] = text[(8 * blockNumber) + i];
    }
    #endif
}

//*****************************************************************************
//
// ECB_move128bitArray - Move input array into output array
//
//*****************************************************************************
void ECB_move128bitArray(uint16_t *input, uint16_t *output)
{
    int16_t i;

    #ifndef MEM_PACKED_SPEED_OPT
    for(i = 0; i < 16; i++)
    {
        output[i] = input[i];
    }
    #else
    for(i = 0; i < 8; i++)
    {
        output[i] = input[i];
    }
    #endif
}

//*****************************************************************************
//
// ECB_mergeText - Merge final plaintext/ciphertext into text array
//
//*****************************************************************************
void ECB_mergeText(uint16_t *text, uint16_t *input, uint16_t blockNumber)
{
    int16_t i;

    #ifndef MEM_PACKED_SPEED_OPT
    for(i = 0; i < 16; i++)
    {
        text[(16 * blockNumber) + i]  = input[i];
    }
    #else
    for(i = 0; i < 8; i++)
    {
        text[(8 * blockNumber) + i]  = input[i];
    }
    #endif
}

//*****************************************************************************
//
// AES ECB mode of operation
//
//*****************************************************************************
#ifndef MEM_PACKED_SPEED_OPT
void AES_performECB(uint16_t *text, uint16_t length, uint16_t *key,
                        AES_KeySize keysize, AES_OperationMode mode)
{
    //
    // Initialize local variables
    //
    uint16_t currentText[16];
    uint16_t i;

    //
    // Key expansion
    //
    AES_expandKey(key, keysize);

    //
    // main loop
    //
    for(i = 0; i < length; i++)
    {
        //
        // Get 128 bit block of plaintext from array passed in
        //
        ECB_splitText(text, currentText, i);

        //
        // AES encryption/decryption
        //
        AES_perform(currentText, mode);

        //
        // Move the final plaintext/ciphertext into text
        //
        ECB_mergeText(text, currentText , i);
    }
}
#endif
//*****************************************************************************
//
// AES ECB fast mode of operation
//
//*****************************************************************************
void AES_performECBFast(uint16_t *text, uint16_t length, uint16_t *key,
                        AES_KeySize keysize, AES_OperationMode mode)
{
    //
    // Initialize local variables
    //
    uint16_t currentText[16];
    uint16_t i;

    //
    // Key expansion
    //
    AES_expandKeyFast(key, keysize, mode);

    //
    // Main loop
    //
    for(i = 0; i < length; i++)
    {
        //
        // Get 128 bit block of plaintext from array passed in
        //
        ECB_splitText(text, currentText, i);

        //
        // AES fast encryption/decryption
        //
        AES_performFast(currentText, mode);

        //
        // Move the final plaintext/ciphertext into text
        //
        ECB_mergeText(text, currentText , i);
    }
}
//
// End of File
//




