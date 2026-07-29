//###########################################################################
//
// FILE:   sha256.c
//
// TITLE:  Implementation of the SHA-256 algorithm
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

#include <sha256.h>

// Uncomment line when copying constants from FLASH to RAM
#pragma DATA_SECTION(SHA256_K, ".TI.ramfunc");  // map the TX data to memory


//*****************************************************************************
//
// SHA-256 round constants
//
//*****************************************************************************
const uint32_t SHA256_K[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
                                0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                                0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
                                0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                                0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
                                0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                                0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
                                0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                                0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
                                0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                                0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
                                0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                                0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
                                0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                                0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
                                0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

//*****************************************************************************
//
// SHA-256 single call hash function
// Input message : Word-wise
//
//*****************************************************************************
uint16_t SHA256_hashWordWise(SHA256_HandleWordWise handle, uint32_t *data,
                             size_t length, uint32_t digest[8])
{
    uint16_t result;

    //
    // Initialize the SHA256 handle
    //
    result = SHA256_startWordWise(handle);

    //
    // Add data block by block
    //
    if(result == SHA256_STATUS_SUCCESS) {
        result = SHA256_addDataWordWise(handle, data, length);
    }

    //
    // Finalize SHA-256 hashing
    //
    if(result == SHA256_STATUS_SUCCESS) {
        result = SHA256_finalizeWordWise(handle, digest);
    }

    return(result);
}

//*****************************************************************************
//
// SHA-256 single call hash function
// Input message : Word-wise, High-Low words Swapped
//
//*****************************************************************************
uint16_t SHA256_hashWordWiseSwapped(SHA256_HandleWordWise handle, uint32_t *data,
                             size_t length, uint32_t digest[8])
{
    uint16_t result;

    //
    // Initialize the SHA256 handle
    //
    result = SHA256_startWordWise(handle);

    //
    // Add data block by block
    //
    if(result == SHA256_STATUS_SUCCESS) {
        result = SHA256_addDataWordWiseSwapped(handle, data, length);
    }

    //
    // Finalize SHA-256 hashing
    //
    if(result == SHA256_STATUS_SUCCESS) {
        result = SHA256_finalizeWordWise(handle, digest);
    }

    return(result);
}

//*****************************************************************************
//
// SHA-256 single call hash function
// Input message : Byte-wise
//
//*****************************************************************************
uint16_t SHA256_hashByteWise(SHA256_HandleByteWise handle, uint16_t *data,
                             size_t length, uint32_t digest[8])
{
    uint16_t result;

    //
    // Initialize the SHA256 handle
    //
    result = SHA256_startByteWise(handle);

    //
    // Add data block by block
    //
    if(result == SHA256_STATUS_SUCCESS) {
        result = SHA256_addDataByteWise(handle, data, length);
    }

    //
    // Finalize SHA-256 hashing
    //
    if(result == SHA256_STATUS_SUCCESS) {
        result = SHA256_finalizeByteWise(handle, digest);
    }

    return(result);
}

//*****************************************************************************
//
// SHA-256 start function
// Input type : Word-wise
//
//*****************************************************************************
uint16_t SHA256_startWordWise(SHA256_HandleWordWise handle)
{
    uint16_t result = SHA256_STATUS_SUCCESS;

    if(handle == NULL)
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    //
    // Initialize handle with starting values
    //
    handle->bitsProcessed = 0;
    handle->offsetWb = 0;

    handle->digest[0] = 0x6A09E667;
    handle->digest[1] = 0xBB67AE85;
    handle->digest[2] = 0x3C6EF372;
    handle->digest[3] = 0xA54FF53A;
    handle->digest[4] = 0x510E527F;
    handle->digest[5] = 0x9B05688C;
    handle->digest[6] = 0x1F83D9AB;
    handle->digest[7] = 0x5BE0CD19;

    return(result);
}

//*****************************************************************************
//
// SHA-256 start function
// Input type : Byte-wise
//
//*****************************************************************************
uint16_t SHA256_startByteWise(SHA256_HandleByteWise handle)
{
    uint16_t result = SHA256_STATUS_SUCCESS;

    if(handle == NULL)
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    //
    // Initialize handle with starting values
    //
    handle->bitsProcessed = 0;
    handle->offsetWb = 0;

    handle->digest[0] = 0x6A09E667;
    handle->digest[1] = 0xBB67AE85;
    handle->digest[2] = 0x3C6EF372;
    handle->digest[3] = 0xA54FF53A;
    handle->digest[4] = 0x510E527F;
    handle->digest[5] = 0x9B05688C;
    handle->digest[6] = 0x1F83D9AB;
    handle->digest[7] = 0x5BE0CD19;

    return(result);
}

//*****************************************************************************
//
// SHA-256 add data block function
// Input data : Word-wise
//
//*****************************************************************************
uint16_t SHA256_addDataWordWise(SHA256_HandleWordWise handle, uint32_t *data,
                                size_t length)
{
    int16_t i;
    size_t dataOffset;
    uint16_t result = SHA256_STATUS_SUCCESS;

    if((handle == NULL) || (data == NULL))
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    if(length >= 0x20000000U)
    {
        result = SHA256_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if(((length << 3u) + handle->bitsProcessed) < handle->bitsProcessed)
    {
        result = SHA256_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if((length & 0x3U) != 0)
    {
        result = SHA256_STATUS_NOT_ALIGNED;
        return(result);
    }

    dataOffset = 0;
    length = length >> 2;
    while(dataOffset < length)
    {
        i = (int16_t) handle->offsetWb;

        //
        // Load data block into the handle
        //
        while((i < 16) && (dataOffset < length))
        {
            handle->Ws[i] = data[dataOffset];
            i++;
            dataOffset++;
        }

        handle->offsetWb = (int16_t) i;

        //
        // After loading a block completely, process it
        //
        if(handle->offsetWb >= 16)
        {
            _SHA256_processBlockWordWise_casm_C28(handle->digest, handle->Ws);
            handle->offsetWb = 0;
        }
    }

    handle->bitsProcessed += length << 5;

    return(result);
}

//*****************************************************************************
//
// SHA-256 add data block function
// Input data : Word-wise , High-Low words Swapped
//
//*****************************************************************************
uint16_t SHA256_addDataWordWiseSwapped(SHA256_HandleWordWise handle, uint32_t *data,
                                size_t length)
{
    int16_t i;
    size_t dataOffset;
    uint16_t result = SHA256_STATUS_SUCCESS;

    if((handle == NULL) || (data == NULL))
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    if(length >= 0x20000000U)
    {
        result = SHA256_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if(((length << 3u) + handle->bitsProcessed) < handle->bitsProcessed)
    {
        result = SHA256_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if((length & 0x3U) != 0)
    {
        result = SHA256_STATUS_NOT_ALIGNED;
        return(result);
    }

    dataOffset = 0;
    length = length >> 2;
    while(dataOffset < length)
    {
        i = (int16_t) handle->offsetWb;

        //
        // Load data block into the handle
        //
        while((i < 16) && (dataOffset < length))
        {
            //
            // Flip High-Low words
            //
            uint32_t low_word_32 = (data[dataOffset] & 0xFFFF0000) >> 16;
            uint32_t high_word_32 = (data[dataOffset] & 0x0000FFFF) << 16;
            handle->Ws[i] = high_word_32 | low_word_32;
            i++;
            dataOffset++;
        }

        handle->offsetWb = (int16_t) i;

        //
        // After loading a block completely, process it
        //
        if(handle->offsetWb >= 16)
        {
            _SHA256_processBlockWordWise_casm_C28(handle->digest, handle->Ws);
            handle->offsetWb = 0;
        }
    }

    handle->bitsProcessed += length << 5;

    return(result);
}

//*****************************************************************************
//
// SHA-256 add data block function
// Input data : Byte-wise
//
//*****************************************************************************
uint16_t SHA256_addDataByteWise(SHA256_HandleByteWise handle, uint16_t *data,
                                size_t length)
{
    int16_t i;
    size_t dataOffset;
    uint16_t result = SHA256_STATUS_SUCCESS;

    if((handle == NULL) || (data == NULL))
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    if(length >= 0x20000000U)
    {
        result = SHA256_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if(((length << 3u) + handle->bitsProcessed) < handle->bitsProcessed)
    {
        result = SHA256_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    dataOffset = 0;
    while(dataOffset < length)
    {
        i = (int16_t) handle->offsetWb;

        //
        // Load data block into the handle
        //
        while((i < 64) && (dataOffset < length))
        {
            handle->Ws[i] = data[dataOffset];
            i++;
            dataOffset++;
        }

        handle->offsetWb = (int16_t) i;

        //
        // After loading a block completely, process it
        //
        if(handle->offsetWb >= 64)
        {
            _SHA256_processBlockByteWise_casm_C28(handle->digest, handle->Ws);
            handle->offsetWb = 0;
        }
    }

    handle->bitsProcessed += length << 3;

    return(result);
}

//*****************************************************************************
//
// SHA-256 finalize hash function
// Input message : Word-wise
//
//*****************************************************************************
uint16_t SHA256_finalizeWordWise(SHA256_HandleWordWise handle,
                                 uint32_t digest[8])
{
    int16_t i;
    uint16_t paddedBlocks;
    uint16_t result = SHA256_STATUS_SUCCESS;

    if((handle == NULL) || (digest == NULL))
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    i = handle->offsetWb;

    //
    // '1' pad bit
    //
    handle->Ws[i] = 0x80000000;
    i++;

    //
    // If fewer than 8 bytes (64 bits) remain in current
    // block, must pad out the current block and then pad out
    // another block. (Need space to store 64 bit value
    // of bits processed in the end of the last block.)
    //
    if(handle->offsetWb >= 14)
    {
        paddedBlocks = 2;
    }
    else
    {
        paddedBlocks = 1;
    }

    //
    // Perform padding
    //
    do
    {
        //
        // Finish out block with 0 pad.
        //
        while(i < 15)
        {
            handle->Ws[i] = 0;
            i++;
        }

        //
        // Write bitsProcessed into last block of padding.
        // Note: implementation only supports 2^32 bits of input.
        //
        if(paddedBlocks == 1)
        {
            handle->Ws[i] = handle->bitsProcessed;
        }
        else
        {
            handle->Ws[i] = 0;
        }

        //
        // Process the final block
        //
        _SHA256_processBlockWordWise_casm_C28(handle->digest, handle->Ws);
        i = 0;

    } while(--paddedBlocks > 0);

    //
    // Copy out final digest
    //
    digest[0] = handle->digest[0];
    digest[1] = handle->digest[1];
    digest[2] = handle->digest[2];
    digest[3] = handle->digest[3];
    digest[4] = handle->digest[4];
    digest[5] = handle->digest[5];
    digest[6] = handle->digest[6];
    digest[7] = handle->digest[7];

    //
    // For security - clear data held by handle
    //
    SHA256_cancelWordWise(handle);

    return(result);
}

//*****************************************************************************
//
// SHA-256 finalize hash function
//
//*****************************************************************************
uint16_t SHA256_finalizeByteWise(SHA256_HandleByteWise handle,
                                 uint32_t digest[8])
{
    int16_t i;
    uint16_t paddedBlocks;
    uint16_t result = SHA256_STATUS_SUCCESS;

    if((handle == NULL) || (digest == NULL))
    {
        result = SHA256_STATUS_NULL_INPUT;
        return(result);
    }

    i = handle->offsetWb;

    //
    // '1' pad bit
    //
    handle->Ws[i] = 0x80;
    i++;

    //
    // If fewer than 8 bytes (64 bits) remain in current
    // block, must pad out the current block and then pad out
    // another block. (Need space to store 64 bit value
    // of bits processed in the end of the last block.)
    //
    if(handle->offsetWb >= 56)
    {
        paddedBlocks = 2;
    }
    else
    {
        paddedBlocks = 1;
    }

    //
    // Perform padding
    //
    do
    {
        //
        // Finish out block with 0 pad.
        //
        while(i < 64)
        {
            handle->Ws[i] = 0;
            i++;
        }

        //
        // Write bitsProcessed into last block of padding.
        // Note: implementation only supports 2^32 bits of input.
        //
        if(paddedBlocks == 1)
        {
            SHA256_PUTU32(&handle->Ws[60], handle->bitsProcessed)
        }

        //
        // Process the final block
        //
        _SHA256_processBlockByteWise_casm_C28(handle->digest, handle->Ws);
        i = 0;

    } while(--paddedBlocks > 0);

    //
    // Copy out final digest
    //
    digest[0] = handle->digest[0];
    digest[1] = handle->digest[1];
    digest[2] = handle->digest[2];
    digest[3] = handle->digest[3];
    digest[4] = handle->digest[4];
    digest[5] = handle->digest[5];
    digest[6] = handle->digest[6];
    digest[7] = handle->digest[7];

    //
    // For security - clear data held by handle
    //
    SHA256_cancelByteWise(handle);

    return(result);
}

//*****************************************************************************
//
// SHA-256 clear handle
// Input message : Word-wise
//
//*****************************************************************************
void SHA256_cancelWordWise(SHA256_HandleWordWise handle)
{
    int16_t i, j;
    uint16_t * objAsBytes;
    j = sizeof(SHA256_ObjectWordWise);

    if(handle != NULL)
    {
        objAsBytes = (uint16_t *) handle;

        for (i = 0; i < j; i++)
        {
            objAsBytes[i] = 0x0;
        }

    }

    return;
}

//*****************************************************************************
//
// SHA-256 clear handle
// Input message : Byte-wise
//
//*****************************************************************************
void SHA256_cancelByteWise(SHA256_HandleByteWise handle)
{
    int16_t i, j;
    uint16_t * objAsBytes;
    j = sizeof(SHA256_ObjectByteWise);

    if(handle != NULL)
    {
        objAsBytes = (uint16_t *) handle;

        for (i = 0; i < j; i++)
        {
            objAsBytes[i] = 0x0;
        }

    }

    return;
}

//*****************************************************************************
//
// SHA-256 process a block of data
// Input message : Word-wise
//
//*****************************************************************************
void SHA256_processBlockWordWise(uint32_t digest[8], uint32_t Ws[64])
{
    uint32_t wt;             // Wt from standard
    int16_t s;               // s is the message schedule index
    uint32_t temp1;          // T1 from standard
    uint32_t temp2;          // T2 from standard

    //
    // Initialize working variables
    //
    uint32_t a = digest[0];
    uint32_t b = digest[1];
    uint32_t c = digest[2];
    uint32_t d = digest[3];
    uint32_t e = digest[4];
    uint32_t f = digest[5];
    uint32_t g = digest[6];
    uint32_t h = digest[7];

    //
    // Perform 64 rounds of compression function
    //
    for(s = 0; s < 64; s++)
    {
        if(s >= 16)
        {
            Ws[s & 0xF] += SHA256_SIGMA1(Ws[(s + 14) & 0xF]) +
                           Ws[(s + 9) & 0xF] +
                           SHA256_SIGMAZ(Ws[(s + 1) & 0xF]);
        }

        wt = Ws[s & 0xF];
        temp1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + SHA256_K[s] + wt;
        temp2 = SHA256_SIGZ(a) + SHA256_MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    //
    // Intermediate digest value
    //
    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;
    digest[5] += f;
    digest[6] += g;
    digest[7] += h;
}

//*****************************************************************************
//
// SHA-256 process a block of data
// Input message : Byte-wise
//
//*****************************************************************************
void SHA256_processBlockByteWise(uint32_t digest[8], uint16_t Ws[64])
{
    uint32_t wt;             // Wt from standard
    int16_t s, s0;               // s is the message schedule index
    uint32_t temp1;          // T1 from standard
    uint32_t temp2;          // T2 from standard

    //
    // Initialize working variables
    //
    uint32_t a = digest[0];
    uint32_t b = digest[1];
    uint32_t c = digest[2];
    uint32_t d = digest[3];
    uint32_t e = digest[4];
    uint32_t f = digest[5];
    uint32_t g = digest[6];
    uint32_t h = digest[7];

    //
    // Perform 64 rounds of compression function
    //
    for(s = 0; s < 64; s++)
    {
        s0 = s << 2;
        if(s0 >= 64)
        {
            wt = SHA256_SIGMA1(SHA256_GETU32(&Ws[(s0-8) & 0x3F])) +
                 SHA256_GETU32(&Ws[(s0-28) & 0x3F]) +
                 SHA256_SIGMAZ(SHA256_GETU32(&Ws[(s0-60) & 0x3F])) +
                 SHA256_GETU32(&Ws[(s0-64) & 0x3F]);

            SHA256_PUTU32(&Ws[s0 & 0x3F], wt);
        }
        else
        {
            wt = SHA256_GETU32(&Ws[s0]);
        }

        temp1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + SHA256_K[s] + wt;
        temp2 = SHA256_SIGZ(a) + SHA256_MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    //
    // Intermediate digest value
    //
    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;
    digest[5] += f;
    digest[6] += g;
    digest[7] += h;
}

//
// End of file
//
