//###########################################################################
//
// FILE:   sha384.c
//
// TITLE:  Implementation of the SHA-384 algorithm
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

#include <sha384.h>

// Uncomment line when copying constants from FLASH to RAM
#pragma DATA_SECTION(SHA384_K, ".TI.ramfunc");  // map the TX data to memory


//*****************************************************************************
//
// SHA-384 round constants
//
//*****************************************************************************
const uint64_t SHA384_K[80] = { 0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                                0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                                0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
                                0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
                                0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
                                0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                                0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
                                0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
                                0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
                                0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
                                0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
                                0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
                                0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
                                0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
                                0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
                                0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
                                0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
                                0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
                                0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
                                0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

//*****************************************************************************
//
// SHA-384 single call hash function
// Input message : Word-wise
//
//*****************************************************************************
uint16_t SHA384_hashWordWise(SHA384_HandleWordWise handle, uint32_t *data,
                             size_t length, uint64_t digest[6])
{
    uint16_t result;

    //
    // Initialize the SHA384 handle
    //
    result = SHA384_startWordWise(handle);

    //
    // Add data block by block
    //
    if(result == SHA384_STATUS_SUCCESS) {
        result = SHA384_addDataWordWise(handle, data, length);
    }

    //
    // Finalize SHA-384 hashing
    //
    if(result == SHA384_STATUS_SUCCESS) {
        result = SHA384_finalizeWordWise(handle, digest);
    }

    return(result);
}

//*****************************************************************************
//
// SHA-384 single call hash function
// Input message : Byte-wise
//
//*****************************************************************************
uint16_t SHA384_hashByteWise(SHA384_HandleByteWise handle, uint16_t *data,
                             size_t length, uint64_t digest[6])
{
    uint16_t result;

    //
    // Initialize the SHA256 handle
    //
    result = SHA384_startByteWise(handle);

    //
    // Add data block by block
    //
    if(result == SHA384_STATUS_SUCCESS) {
        result = SHA384_addDataByteWise(handle, data, length);
    }

    //
    // Finalize SHA-384 hashing
    //
    if(result == SHA384_STATUS_SUCCESS) {
        result = SHA384_finalizeByteWise(handle, digest);
    }

    return(result);
}

//*****************************************************************************
//
// SHA-384 start function
// Input type : Word-wise
//
//*****************************************************************************
uint16_t SHA384_startWordWise(SHA384_HandleWordWise handle)
{
    uint16_t result = SHA384_STATUS_SUCCESS;

    if(handle == NULL)
    {
        result = SHA384_STATUS_NULL_INPUT;
        return(result);
    }

    //
    // Initialize handle with starting values
    //
    handle->bitsProcessed = 0;
    handle->offsetWb = 0;

    handle->digest[0] = 0xcbbb9d5dc1059ed8;
    handle->digest[1] = 0x629a292a367cd507;
    handle->digest[2] = 0x9159015a3070dd17;
    handle->digest[3] = 0x152fecd8f70e5939;
    handle->digest[4] = 0x67332667ffc00b31;
    handle->digest[5] = 0x8eb44a8768581511;
    handle->digest[6] = 0xdb0c2e0d64f98fa7;
    handle->digest[7] = 0x47b5481dbefa4fa4;

    return(result);
}

//*****************************************************************************
//
// SHA-384 start function
// Input type : Byte-wise
//
//*****************************************************************************
uint16_t SHA384_startByteWise(SHA384_HandleByteWise handle)
{
    uint16_t result = SHA384_STATUS_SUCCESS;

    if(handle == NULL)
    {
        result = SHA384_STATUS_NULL_INPUT;
        return(result);
    }

    //
    // Initialize handle with starting values
    //
    handle->bitsProcessed = 0;
    handle->offsetWb = 0;

    handle->digest[0] = 0xcbbb9d5dc1059ed8;
    handle->digest[1] = 0x629a292a367cd507;
    handle->digest[2] = 0x9159015a3070dd17;
    handle->digest[3] = 0x152fecd8f70e5939;
    handle->digest[4] = 0x67332667ffc00b31;
    handle->digest[5] = 0x8eb44a8768581511;
    handle->digest[6] = 0xdb0c2e0d64f98fa7;
    handle->digest[7] = 0x47b5481dbefa4fa4;

    return(result);
}

//*****************************************************************************
//
// SHA-384 add data block function
// Input data : Word-wise
//
//*****************************************************************************
uint16_t SHA384_addDataWordWise(SHA384_HandleWordWise handle, uint32_t *data,
                                size_t length)
{
    int16_t i;
    size_t dataOffset;
    uint16_t result = SHA384_STATUS_SUCCESS;

    if((handle == NULL) || (data == NULL))
    {
        result = SHA384_STATUS_NULL_INPUT;
        return(result);
    }

    if(length >= 0x20000000U)
    {
        result = SHA384_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if(((length << 3u) + handle->bitsProcessed) < handle->bitsProcessed)
    {
        result = SHA384_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if((length & 0x3U) != 0)
    {
        result = SHA384_STATUS_NOT_ALIGNED;
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
        while((i < 32) && (dataOffset < length))
        {
            handle->Ws[i] = data[dataOffset];
            i++;
            dataOffset++;
        }

        handle->offsetWb = (int16_t) i;

        //
        // After loading a block completely, process it
        //
        if(handle->offsetWb >= 32)
        {
            _SHA384_processBlockWordWise_casm_C28(handle->digest, (uint64_t *)handle->Ws);
            handle->offsetWb = 0;
        }
    }

    handle->bitsProcessed += length << 5;

    return(result);
}

//*****************************************************************************
//
// SHA-384 add data block function
// Input data : Byte-wise
//
//*****************************************************************************
uint16_t SHA384_addDataByteWise(SHA384_HandleByteWise handle, uint16_t *data,
                                size_t length)
{
    int16_t i;
    size_t dataOffset;
    uint16_t result = SHA384_STATUS_SUCCESS;

    if((handle == NULL) || (data == NULL))
    {
        result = SHA384_STATUS_NULL_INPUT;
        return(result);
    }

    if(length >= 0x20000000U)
    {
        result = SHA384_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    if(((length << 3u) + handle->bitsProcessed) < handle->bitsProcessed)
    {
        result = SHA384_STATUS_LENGTH_TOO_LARGE;
        return(result);
    }

    dataOffset = 0;
    while(dataOffset < length)
    {
        i = (int16_t) handle->offsetWb;

        //
        // Load data block into the handle
        //
        while((i < 128) && (dataOffset < length))
        {
            handle->Ws[i] = data[dataOffset];
            i++;
            dataOffset++;
        }

        handle->offsetWb = (int16_t) i;

        //
        // After loading a block completely, process it
        //
        if(handle->offsetWb >= 128)
        {
            // C-based implementation
//            SHA384_processBlockByteWise(handle->digest, handle->Ws);

            // ASM implementation
            _SHA384_processBlockByteWise_casm_C28(handle->digest, handle->Ws);
            handle->offsetWb = 0;
        }
    }

    handle->bitsProcessed += length << 3;

    return(result);
}

//*****************************************************************************
//
// SHA-384 finalize hash function
// Input message : Word-wise
//
//*****************************************************************************
uint16_t SHA384_finalizeWordWise(SHA384_HandleWordWise handle,
                                 uint64_t digest[6])
{
    int16_t i;
    uint16_t paddedBlocks;
    uint16_t result = SHA384_STATUS_SUCCESS;

    if((handle == NULL) || (digest == NULL))
    {
        result = SHA384_STATUS_NULL_INPUT;
        return(result);
    }

    i = handle->offsetWb;

    //
    // '1' pad bit
    //
    handle->Ws[i] = 0x80000000;
    i++;

    //
    // If fewer than 16 bytes (128 bits) remain in current
    // block, must pad out the current block and then pad out
    // another block. (Need space to store 128 bit value
    // of bits processed in the end of the last block.)
    //
    if(handle->offsetWb >= 28)
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
        while(i < 31)
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
        _SHA384_processBlockWordWise_casm_C28(handle->digest, (uint64_t *)handle->Ws);
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

    //
    // For security - clear data held by handle
    //
    SHA384_cancelWordWise(handle);

    return(result);
}

//*****************************************************************************
//
// SHA-256 finalize hash function
//
//*****************************************************************************
uint16_t SHA384_finalizeByteWise(SHA384_HandleByteWise handle,
                                 uint64_t digest[6])
{
    int16_t i;
    uint16_t paddedBlocks;
    uint16_t result = SHA384_STATUS_SUCCESS;

    if((handle == NULL) || (digest == NULL))
    {
        result = SHA384_STATUS_NULL_INPUT;
        return(result);
    }

    i = handle->offsetWb;

    //
    // '1' pad bit
    //
    handle->Ws[i] = 0x80;
    i++;

    //
    // If fewer than 16 bytes (128 bits) remain in current
    // block, must pad out the current block and then pad out
    // another block. (Need space to store 128 bit value
    // of bits processed in the end of the last block.)
    //
    if(handle->offsetWb >= 112)
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
        while(i < 128)
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
            SHA384_PUTU32(&handle->Ws[124], handle->bitsProcessed)
        }

        //
        // Process the final block
        //

        // C base implementation
//        SHA384_processBlockByteWise(handle->digest, handle->Ws);

        // ASM implementation
        _SHA384_processBlockByteWise_casm_C28(handle->digest, handle->Ws);

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

    //
    // For security - clear data held by handle
    //
    SHA384_cancelByteWise(handle);

    return(result);
}

//*****************************************************************************
//
// SHA-384 clear handle
// Input message : Word-wise
//
//*****************************************************************************
void SHA384_cancelWordWise(SHA384_HandleWordWise handle)
{
    int16_t i, j;
    uint16_t * objAsBytes;
    j = sizeof(SHA384_ObjectWordWise);

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
// SHA-384 clear handle
// Input message : Byte-wise
//
//*****************************************************************************
void SHA384_cancelByteWise(SHA384_HandleByteWise handle)
{
    int16_t i, j;
    uint16_t * objAsBytes;
    j = sizeof(SHA384_ObjectByteWise);

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
// SHA-384 process a block of data
// Input message : Word-wise
//
//*****************************************************************************
void SHA384_processBlockWordWise(uint64_t digest[8], uint64_t Ws[16])
{
    uint64_t wt;             // Wt from standard
    int16_t s;               // s is the message schedule index
    uint64_t temp1;          // T1 from standard
    uint64_t temp2;          // T2 from standard

    //
    // Initialize working variables
    //
    uint64_t a = digest[0];
    uint64_t b = digest[1];
    uint64_t c = digest[2];
    uint64_t d = digest[3];
    uint64_t e = digest[4];
    uint64_t f = digest[5];
    uint64_t g = digest[6];
    uint64_t h = digest[7];

    //
    // Perform 80 rounds of compression function
    //
    for(s = 0; s < 80; s++)
    {
        if(s >= 16)
        {
            Ws[s & 0xF] += SHA384_SIGMA1(Ws[(s + 14) & 0xF]) +
                           Ws[(s + 9) & 0xF] +
                           SHA384_SIGMAZ(Ws[(s + 1) & 0xF]);
        }
        else
        {
            Ws[s] = ((uint64_t)(Ws[s] << 32) | (uint64_t)(Ws[s] >> 32));
        }

        wt = Ws[s & 0xF];
        temp1 = h + SHA384_SIG1(e) + SHA384_CH(e, f, g) + SHA384_K[s] + wt;
        temp2 = SHA384_SIGZ(a) + SHA384_MAJ(a, b, c);

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
// SHA-384 process a block of data
// Input message : Byte-wise
//
//*****************************************************************************

void SHA384_processBlockByteWise(uint64_t digest[8],  uint16_t Ws[128])
{
    uint64_t wt;             // Wt from standard
    int16_t s, s0;               // s is the message schedule index
    uint64_t temp1;          // T1 from standard
    uint64_t temp2;          // T2 from standard

    //
    // Initialize working variables
    //
    uint64_t a = digest[0];
    uint64_t b = digest[1];
    uint64_t c = digest[2];
    uint64_t d = digest[3];
    uint64_t e = digest[4];
    uint64_t f = digest[5];
    uint64_t g = digest[6];
    uint64_t h = digest[7];

    //
    // Perform 64 rounds of compression function
    //
    for(s = 0; s < 80; s++)
    {
        s0 = s << 3;
        if(s >= 16)
        {
            wt = SHA384_SIGMA1(SHA384_GETU64(&Ws[(s0 + 112) & 0x7F])) +
                 SHA384_GETU64(&Ws[(s0 + 72) & 0x7F]) +
                 SHA384_SIGMAZ(SHA384_GETU64(&Ws[(s0 + 8) & 0x7F])) +
                 SHA384_GETU64(&Ws[s0 & 0x7F]);

            SHA384_PUTU64(&Ws[s0 & 0x7F], wt);
        }
        else
        {
            wt = SHA384_GETU64(&Ws[s0]);
        }

        temp1 = h + SHA384_SIG1(e) + SHA384_CH(e, f, g) + SHA384_K[s] + wt;
        temp2 = SHA384_SIGZ(a) + SHA384_MAJ(a, b, c);

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
