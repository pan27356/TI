//###########################################################################
//
// FILE:   aes_cmac.c
//
// TITLE:  Implementation of the AES CMAC mode.
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

#include "aes_cmac.h"

//*****************************************************************************
//
// Array to store the generated Message Authentication Code
//
//*****************************************************************************
#ifndef MEM_PACKED_SPEED_OPT
uint16_t CMAC_Tag[16];
#else
uint16_t CMAC_Tag[8];
#endif

//*****************************************************************************
//
// CMAC_splitText - Split text into 128 bit blocks based on blockNumber
//
//*****************************************************************************
void CMAC_splitText(uint16_t *text, uint16_t *output, uint16_t blockNumber)
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
// CMAC_perform128bitXOR - Perform XOR operation on two 16 byte arrays
//
//*****************************************************************************
void CMAC_perform128bitXOR(uint16_t *input1, uint16_t *input2)
{
    int16_t i;

    #ifndef MEM_PACKED_SPEED_OPT
    for(i = 0U; i < 16U; i++)
    #else
    for(i = 0U; i < 8U; i++)
    #endif
    {
        input1[i] ^= input2[i];
    }
}

//*****************************************************************************
//
// CMAC_performOneBitLeftshift - Perform left shift on 16 byte array
//
//*****************************************************************************
void CMAC_performOneBitLeftshift(uint16_t *input, uint16_t *output)
{
    int16_t i;
    uint16_t overflow = 0U;

    #ifndef MEM_PACKED_SPEED_OPT
    for(i = 15; i >= 0; i--)
    {
        output[i] = (input[i] << 1U) & 0xFFU;
        output[i] |= overflow;
        overflow = (input[i] & 0x80U)?1U:0U;
    }
    #else
    for(i = 7; i >= 0; i--)
    {
        output[i] = (input[i] << 1U) & 0xFFFFU;
        output[i] |= overflow;
        overflow = (input[i] & 0x8000U)?1U:0U;
    }
    #endif
}

//*****************************************************************************
//
// CMAC_memset - Copy of compiler memset to quickly clear arrays
//
//*****************************************************************************
void CMAC_memset(void *mem, int16_t ch, uint32_t length)
{
    char *m = (char *)mem;

    while(length--)
    {
        *m++ = ch;
    }
}

//*****************************************************************************
//
// CMAC_move128bitArray - Move input array into output array
//
//*****************************************************************************
void CMAC_move128bitArray(uint16_t *input, uint16_t *output)
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
// AES256_performCMAC
//
//*****************************************************************************
#ifndef MEM_PACKED_SPEED_OPT
uint16_t *AES_performCMAC(uint16_t *text, uint16_t length, uint16_t *key,
                          AES_KeySize keysize)
{
    //
    // Setup local variables for calculation
    //
    int16_t i = 0;
    uint16_t k0[16];
    uint16_t k1[16];
    uint16_t CMAC_AES_CONSTANT[16];
    uint16_t currentMessage[16];

    //
    // Key expansion
    //
    AES_expandKey(key, keysize);

    //
    // Set arrays to zero
    //
    CMAC_memset(currentMessage, 0, sizeof(currentMessage));
    CMAC_memset(CMAC_Tag, 0, sizeof(CMAC_Tag));
    CMAC_memset(CMAC_AES_CONSTANT, 0, sizeof(CMAC_AES_CONSTANT));

    //
    // Configure AES Constant
    //
    CMAC_AES_CONSTANT[15] = 0x87U;

    //
    // Begin CMAC Algorithm
    //

    //
    // Calculate k0 with encryption of 0
    //
    AES_perform(currentMessage, AES_OPMODE_ENCRYPT);

    //
    // Move ciphertext into k0 for future use
    //
    CMAC_move128bitArray(currentMessage, k0);

    //
    // Generate k1
    // Note: Not generating k2 since plain text length is in multiple of
    //       128-bits
    // No padding will be required or performed.
    //
    if((k0[0] & 0x80U) == 0U)
    {
        //
        // Left shift k0 by 1 to calculate k1
        //
        CMAC_performOneBitLeftshift(k0, k1);
    }
    else
    {
        //
        // Left shift k0 by 1 to calculate temporary k1. Then XOR temporary k1
        // by the AES-256bit constant to calculate k1.
        //
        CMAC_performOneBitLeftshift(k0, k1);
        CMAC_perform128bitXOR(k1, CMAC_AES_CONSTANT);
    }

    //
    // Perform message block cipher encryption on all blocks except last one
    //
    for(i = 0; i < length - 1; i++)
    {
        //
        // Get 128 bit block of plaintext from array passed in
        //
        CMAC_splitText(text, currentMessage, i);

        //
        // XOR initialization vector/previousCiphertext with new plaintext
        //
        CMAC_perform128bitXOR(CMAC_Tag,currentMessage);

        //
        // Perform AES encryption on CMAC_TAG
        //
        AES_perform(CMAC_Tag, AES_OPMODE_ENCRYPT);

    }

    //
    // Get 128 bit block of plaintext from array passed in
    //
    CMAC_splitText(text, currentMessage, i);

    //
    // XOR last message with k1
    //
    CMAC_perform128bitXOR(currentMessage, k1);

    //
    // Generate final tag - XOR CMAC_TAG and CMAC_LAST_MESSAGE.
    //                      Encrypt CMAC_TAG.
    //
    CMAC_perform128bitXOR(CMAC_Tag, currentMessage);
    AES_perform(CMAC_Tag, AES_OPMODE_ENCRYPT);

    return(CMAC_Tag);
}
#endif

//*****************************************************************************
//
// AES perform fast CMAC
//
//*****************************************************************************
uint16_t *AES_performCMACFast(uint16_t *text, uint16_t length, uint16_t *key,
                              AES_KeySize keysize)
{
    //
    // Setup local variables for calculation
    //
    int16_t i = 0;

    #ifndef MEM_PACKED_SPEED_OPT
    uint16_t k0[16];
    #else
    uint16_t k0[8];
    #endif

    #ifndef MEM_PACKED_SPEED_OPT
    uint16_t k1[16];
    #else
    uint16_t k1[8];
    #endif

    #ifndef MEM_PACKED_SPEED_OPT
    uint16_t CMAC_AES_CONSTANT[16];
    #else
    uint16_t CMAC_AES_CONSTANT[8];
    #endif

    #ifndef MEM_PACKED_SPEED_OPT
    uint16_t currentMessage[16];
    #else
    uint16_t currentMessage[8];
    #endif

    //
    // Key expansion
    //
    AES_expandKeyFast(key, keysize, AES_OPMODE_ENCRYPT);

    //
    // Set arrays to zero
    //
    CMAC_memset(currentMessage, 0, sizeof(currentMessage));
    CMAC_memset(CMAC_Tag, 0, sizeof(CMAC_Tag));
    CMAC_memset(CMAC_AES_CONSTANT, 0, sizeof(CMAC_AES_CONSTANT));

    //
    // Configure AES Constant
    //
    #ifndef MEM_PACKED_SPEED_OPT
    CMAC_AES_CONSTANT[15] = 0x87U;
    #else
    CMAC_AES_CONSTANT[7] = 0x87U;
    #endif

    //
    // Begin CMAC Algorithm
    //

    //
    // Calculate k0 with fast encryption of 0
    //
    AES_performFast(currentMessage, AES_OPMODE_ENCRYPT);

    //
    // Move ciphertext into k0 for future use
    //
    CMAC_move128bitArray(currentMessage, k0);

    //
    // Generate k1
    // Not generating k2 since plain text length is in multiple of 128-bits
    // No padding will be required or performed.
    //
    #ifndef MEM_PACKED_SPEED_OPT
    if((k0[0] & 0x80U) == 0U)
    #else
    if((k0[0] & 0x8000U) == 0U)
    #endif
    {
        //
        // Left shift k0 by 1 to calculate k1
        //
        CMAC_performOneBitLeftshift(k0, k1);
    }
    else
    {
        //
        // Left shift k0 by 1 to calculate temporary k1. Then XOR temporary k1
        // by the AES-256bit constant to calculate k1.
        //
        CMAC_performOneBitLeftshift(k0, k1);
        CMAC_perform128bitXOR(k1, CMAC_AES_CONSTANT);
    }

    //
    // Perform message block cipher encryption on all blocks except last one
    //
    for(i = 0; i < length - 1; i++)
    {
        //
        // Get 128 bit block of plaintext from array passed in
        //
        CMAC_splitText(text, currentMessage, i);

        //
        // XOR initialization vector/previousCiphertext with new plaintext
        //
        CMAC_perform128bitXOR(CMAC_Tag, currentMessage);

        //
        // Perform AES fast encryption on CMAC_TAG
        //
        AES_performFast(CMAC_Tag, AES_OPMODE_ENCRYPT);

    }

    //
    // Get 128 bit block of plaintext from array passed in
    //
    CMAC_splitText(text, currentMessage, i);

    //
    // XOR last message with k1
    //
    CMAC_perform128bitXOR(currentMessage, k1);

    //
    // Generate final CMAC_Tag - XOR CMAC_TAG and CMAC_LAST_MESSAGE.
    //                      Encrypt CMAC_TAG.
    //
    CMAC_perform128bitXOR(CMAC_Tag, currentMessage);
    AES_performFast(CMAC_Tag, AES_OPMODE_ENCRYPT);

    return(CMAC_Tag);
}

//
// End of File
//

