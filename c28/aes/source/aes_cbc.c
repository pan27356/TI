//###########################################################################
//
// FILE:   aes_cbc.c
//
// TITLE:  Implementation of the AES CBC mode
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

#include "aes_cbc.h"

//*****************************************************************************
//
// CBC_splitText - Split text into 128 bit blocks based on blockNumber
//
//*****************************************************************************
void CBC_splitText(uint16_t *text, uint16_t *output, uint16_t blockNumber)
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
// CBC_perform128bitXOR - Perform XOR operation on two 16 byte arrays
//
//*****************************************************************************
void CBC_perform128bitXOR(uint16_t *input1, uint16_t *input2, uint16_t *out)
{
    int16_t i;

    #ifndef MEM_PACKED_SPEED_OPT
    for(i = 0U; i < 16U; i++)
    #else
    for(i = 0U; i < 8U; i++)
    #endif
    {
        out[i] = input1[i] ^ input2[i];
    }
}

//*****************************************************************************
//
// CBC_move128bitArray - Move input array into output array
//
//*****************************************************************************
void CBC_move128bitArray(uint16_t *input, uint16_t *output)
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
// CBC_mergeText - Merge final plaintext/ciphertext into text array
//
//*****************************************************************************
void CBC_mergeText(uint16_t *text, uint16_t *input, uint16_t blockNumber)
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
// AES CBC mode of operation
//
//*****************************************************************************
#ifndef MEM_PACKED_SPEED_OPT
void AES_performCBC(uint16_t *text, uint16_t length, uint16_t *key,
                    AES_KeySize keysize, AES_OperationMode mode, uint16_t *iv)
{
    //
    // Initialize local variables
    //
    uint16_t previousCiphertext[16];
    uint16_t currentCiphertext[16];
    uint16_t decryptionCiphertext[16];
    uint16_t i;
    
    //
    // Key expansion
    //
    AES_expandKey(key, keysize);

    //
    // set previousCiphertext equal to the initialization vector
    //
    CBC_move128bitArray(iv, previousCiphertext);
    
    //
    // main loop
    // Encryption order of operations: XOR plaintext with previousCiphertext, 
    //                                   encrypt plaintext, save result for next
    //                                 round
    // Decryption order of operations: save ciphertext for next round, decrypt
    //                                 ciphertext, XOR ciphertext with
    //                                 previousCiphertext
    //
    for(i = 0; i < length; i++)
    {    
        if(mode == AES_OPMODE_ENCRYPT)
        {
            //
            // Get 128 bit block of plaintext from array passed in
            //
            CBC_splitText(text, currentCiphertext, i);

            //
            // XOR initialization vector/previousCiphertext with new plaintext
            //
            CBC_perform128bitXOR(currentCiphertext, previousCiphertext,
                                 currentCiphertext);

            //
            // AES encryption
            //
            AES_perform(currentCiphertext, mode);

            //
            // move result to previousCiphertext for use in next round
            //
            CBC_move128bitArray(currentCiphertext, previousCiphertext);
        }
        else
        {
            //
            // Get 128 bit block of ciphertext from array passed in
            //
            CBC_splitText(text, currentCiphertext, i);

            //
            // Copy ciphertext into temporary variable so it can be moved into
            // previousCiphertext later on
            //
            CBC_move128bitArray(currentCiphertext, decryptionCiphertext);

            //
            // AES decryption
            //
            AES_perform(currentCiphertext, mode);

            //
            // XOR initialization vector/previousCiphertext with new ciphertext
            //
            CBC_perform128bitXOR(currentCiphertext, previousCiphertext,  
                                 currentCiphertext);

            //
            // Move temporary ciphertext array into previousCiphertext
            //
            CBC_move128bitArray(decryptionCiphertext, previousCiphertext);
        }

        //
        // Move the final plaintext/ciphertext into text
        //
        CBC_mergeText(text, currentCiphertext , i);
    }
}
#endif

//*****************************************************************************
//
// AES CBC fast mode of operation
//
//*****************************************************************************
void AES_performCBCFast(uint16_t *text, uint16_t length, uint16_t *key,
                        AES_KeySize keysize, AES_OperationMode mode,
                        uint16_t *iv)
{
    //
    // Initialize local variables
    //
    #ifndef MEM_PACKED_SPEED_OPT
    uint16_t previousCiphertext[16];
    #else
    uint16_t previousCiphertext[8];
    #endif

    #ifndef MEM_PACKED_SPEED_OPT
        uint16_t currentCiphertext[16];
    #else
        uint16_t currentCiphertext[8];
    #endif

    #ifndef MEM_PACKED_SPEED_OPT
        uint16_t decryptionCiphertext[16];
    #else
        uint16_t decryptionCiphertext[8];
    #endif

    uint16_t i;

    //
    // Key expansion
    //
    AES_expandKeyFast(key, keysize, mode);

    //
    // set previousCiphertext equal to the initialization vector
    //
    CBC_move128bitArray(iv, previousCiphertext);

    //
    // Main loop
    // Encryption order of operations: XOR plaintext with previousCiphertext,
    //                                 encrypt plaintext, save result for next
    //                                 round
    // Decryption order of operations: save ciphertext for next round, decrypt
    //                                 ciphertext, XOR ciphertext with
    //                                 previousCiphertext
    //
    for(i = 0; i < length; i++)
    {
        if(mode == AES_OPMODE_ENCRYPT)
        {
            //
            // Get 128 bit block of plaintext from array passed in
            //
            CBC_splitText(text, currentCiphertext, i);

            //
            // XOR initialization vector/previousCiphertext with new plaintext
            //
            CBC_perform128bitXOR(currentCiphertext, previousCiphertext,
                                 currentCiphertext);

            //
            // AES fast encryption
            //
            AES_performFast(currentCiphertext, mode);

            //
            // move result to previousCiphertext for use in next round
            //
            CBC_move128bitArray(currentCiphertext, previousCiphertext);
        }
        else
        {
            //
            // Get 128 bit block of ciphertext from array passed in
            //
            CBC_splitText(text, currentCiphertext, i);

            //
            // Copy ciphertext into temporary variable so it can be moved into
            // previousCiphertext later on
            //
            CBC_move128bitArray(currentCiphertext, decryptionCiphertext);

            //
            // AES fast decryption
            //
            AES_performFast(currentCiphertext, mode);

            //
            // XOR initialization vector/previousCiphertext with new ciphertext
            //
            CBC_perform128bitXOR(currentCiphertext, previousCiphertext,
                                 currentCiphertext);

            //
            // Move temporary ciphertext array into previousCiphertext
            //
            CBC_move128bitArray(decryptionCiphertext, previousCiphertext);
        }

        //
        // Move the final plaintext/ciphertext into text
        //
        CBC_mergeText(text, currentCiphertext , i);
    }
}
//
// End of File
//
