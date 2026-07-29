//###########################################################################
//
// FILE:   yarrow.c
//
// TITLE:  Yarrow PRNG algorithm
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

#include "yarrow.h"

//
// SHA-256 handle
//
SHA256_ObjectByteWise hash;

//*****************************************************************************
//
// Initialize yarrow handle with nounce counter values
//
//*****************************************************************************
int yarrow_init_with_nounce(yarrow_prng *prng, const uc *nounceCounter)
{
    if(prng == NULL || nounceCounter == NULL)
    {
        return YARROW_STATUS_ERROR_NULL;
    }

    uint32_t i = 0;
    while (i < MAXBLOCKSIZE)
    {
        prng->pool[i] = 0;
        i++;
    }

    prng->ready = 0;

    for (i = 0; i < 16U; i++)
    {
        prng->nounceCounter[i] = nounceCounter[i];
    }

    return YARROW_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Initialize yarrow handle with default nounce counter value '0'
//
//*****************************************************************************
int yarrow_init_default_nounce(yarrow_prng *prng)
{
    if(prng == NULL)
    {
        return YARROW_STATUS_ERROR_NULL;
    }

    uint32_t i = 0;
    while (i < MAXBLOCKSIZE)
    {
        prng->pool[i] = 0;
        i++;
    }

    prng->ready = 0;

    for (i = 0; i < 16U; i++)
    {
        prng->nounceCounter[i] = 0;
    }

    return YARROW_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Introduce entropy in the algorithm to generate pseudo-random values
//
//*****************************************************************************
int yarrow_add_entropy(uc *in, const uint32_t inlen, yarrow_prng *prng)
{
    if(prng == NULL || in == NULL || inlen <= 0)
    {
        return YARROW_STATUS_ERROR_NULL;
    }

    uc error_msg;

    //
    // Initialize a hash object
    //
    if ((error_msg = SHA256_startByteWise(&hash)) != SHA256_STATUS_SUCCESS)
    {
        return error_msg;
    }

    //
    // Hash the initial pool
    //
    if ((error_msg = SHA256_addDataByteWise(&hash, (uint16_t*)prng->pool, 32U)) != SHA256_STATUS_SUCCESS)
    {
        return error_msg;
    }

    //
    // Now add the entropy to the pool
    //
    if ((error_msg = SHA256_addDataByteWise(&hash, (uint16_t*)in, inlen)) != SHA256_STATUS_SUCCESS)
    {
        return error_msg;
    }

    //
    // Now shift the data from sha256 handle to a temporary digest
    //
    uint32_t digest[8];
    if ((error_msg = SHA256_finalizeByteWise(&hash, digest)) != SHA256_STATUS_SUCCESS)
    {
        return error_msg;
    }

    //
    // Shift the data from digest to prng->pool
    //
    uint32_t i, j;
    for (i = 0, j = 0; i < 8 && j < 32; i++)
    {
        prng->pool[j++] = (digest[i] >> 24) & 255;
        prng->pool[j++] = (digest[i] >> 16) & 255;
        prng->pool[j++] = (digest[i] >> 8) & 255;
        prng->pool[j++] = (digest[i]) & 255;
    }

    return YARROW_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Prepare the yarrow PRNG handle to generate random values
//
//*****************************************************************************
int yarrow_ready(yarrow_prng *prng)
{
    if(prng == NULL)
    {
        return YARROW_STATUS_ERROR_NULL;
    }

    uint32_t i;
    for (i = 0; i < 32; i++)
    {
        prng->key[i] = prng->pool[i];
    }

    prng->ready = 1;

    return YARROW_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Read random values using yarrow PRNG
//
//*****************************************************************************
int yarrow_read( yarrow_prng *prng, uc *out, uc outlen)
{
    //
    // Check for invalid input parameters
    //
    if(prng == NULL || out == NULL || outlen <= 0)
    {
        return YARROW_STATUS_ERROR_NULL;
    }

    //
    // Check if prng is ready
    //
    if (prng->ready != 1)
    {
        return 0;
    }

    //
    // Initialize the out array to 0
    //
    int i;
    for (i = 0; i < outlen; i++)
    {
        out[i] = 0;
    }

    //
    // Populate the out array with pseudo-random values
    //
    i = 0;
    int len = 0;
    int outlenCopy = outlen;
    while (outlen > 0)
    {
        int currlen = (outlen < 32) ? outlen : 32;
        AES_performCTR((uint16_t*)prng->pool, 2, (uint16_t*)prng->key,\
                       AES_256, AES_OPMODE_ENCRYPT,\
                       (uint16_t*)prng->nounceCounter);
        int ptr;
        for (ptr = 0; ptr < currlen; ptr++)
        {
            out[i++] = prng->pool[ptr];
        }
        outlen -= currlen;
        len += currlen;
    }

    if (outlenCopy == len)
        return len;
    else
        return 0;
}
//
// End of file
//
