//###########################################################################
//
// FILE:   emsa_pss.c
//
// TITLE:  EMSA-PSS message encoding and decoding
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

#include "emsa_pss.h"
#include "yarrow.h"
#include "sha256.h"
#include <stdlib.h>
#include <string.h>

//*****************************************************************************
//
// SHA-256 handle
//
//*****************************************************************************
extern SHA256_ObjectByteWise md;

//*****************************************************************************
//
// PKCS1_MGF mask generation using SHA-256
//
//*****************************************************************************
int pkcs_1_mgf(uint16_t *seed, int16_t seedlen, uint16_t *mask, int16_t masklen)
{
    int16_t hLen, x, err;
    uint32_t counter;
    uint16_t *buf;

    if (seed == NULL || mask == NULL)
    {
        return PKCS_STATUS_FAILURE_NULL;
    }

    hLen = HASH_SIZE;
    buf = malloc(hLen * sizeof(uint16_t));

    if (buf == NULL)
    {
        return PKCS_STATUS_FAILURE_MEM;
    }

    counter = 0;

    while (masklen > 0)
    {
        //
        // handle counter
        //
        STORE32H(counter, buf);

        ++counter;

        uint32_t digest[8];
        int i, j;

        if ((err = SHA256_startByteWise(&md)) != SHA256_STATUS_SUCCESS)
        {
            return err;
        }
        if ((err = SHA256_addDataByteWise(&md, (uint16_t *)seed, seedlen)) != SHA256_STATUS_SUCCESS)
        {
            return err;
        }
        if ((err = SHA256_addDataByteWise(&md, (uint16_t *)buf, 4)) != SHA256_STATUS_SUCCESS)
        {
            return err;
        }
        if ((err = SHA256_finalizeByteWise(&md, digest)) != SHA256_STATUS_SUCCESS)
        {
            return err;
        }

        for (i = 0, j = 0; i < (HASH_SIZE/4) && j < HASH_SIZE; i++)
        {
            buf[j++] = (digest[i] >> 24) & 255;
            buf[j++] = (digest[i] >> 16) & 255;
            buf[j++] = (digest[i] >> 8) & 255;
            buf[j++] = (digest[i]) & 255;
        }

        //
        // store it
        //
        for (x = 0; x < hLen && masklen > 0; x++, masklen--)
        {
            *mask++ = buf[x];
        }
    }

    free(buf);

    return PKCS_STATUS_SUCCESS;
}

//*****************************************************************************
//
// EMSA-PSS encode message
//
//*****************************************************************************
int emsa_pss_encode(uint16_t *msghash, uint16_t msghashlen, uint16_t saltlen,
                    uint16_t modulus_bitlen, yarrow_prng *prng,
                    uint16_t *emsa_out, uint16_t emsa_outlen)
{
    uint16_t *DB, *mask, *salt, *hash;
    uint16_t x, y, hLen, modulus_len;
    int err, i ,j;

    if ((msghash == NULL) || (emsa_out == NULL) || (msghashlen <= 0))
    {
        return PKCS_STATUS_FAILURE_NULL;
    }

    hLen = HASH_SIZE;
    modulus_bitlen--;
    modulus_len = (modulus_bitlen >> 3) + (modulus_bitlen & 7 ? 1 : 0);

    //
    // check sizes
    //
    if ((saltlen > modulus_len) || (modulus_len < hLen + saltlen + 2))
    {
        return PKCS_STATUS_FAILURE_SIZE;
    }

    //
    // allocate ram for DB/mask/salt/hash
    //
    DB   = (uint16_t *)malloc((modulus_len - hLen - 1) * sizeof(uint16_t));
    mask = (uint16_t *)malloc((modulus_len - hLen -1) * sizeof(uint16_t));
    salt = (uint16_t *)malloc(saltlen * sizeof(uint16_t));
    hash = (uint16_t *)malloc(hLen * sizeof(uint16_t));

    if (DB == NULL || mask == NULL || salt == NULL || hash == NULL)
    {
        if (DB != NULL)
        {
            free(DB);
        }
        if (mask != NULL)
        {
            free(mask);
        }
        if (salt != NULL)
        {
            free(salt);
        }
        if (hash != NULL)
        {
            free(hash);
        }
        return PKCS_STATUS_FAILURE_MEM;
    }

    if (saltlen > 0)
    {
        //
        // Generate random salt using yarrow PRNG
        //
        if (yarrow_read(prng, (uc *)salt, saltlen) != saltlen)
        {
            return PKCS_STATUS_FAILURE_READ;
        }
    }

    for (i = 0; i < 8; i++)
        DB[i] = '\0';

    uint32_t digest[8];

    //
    // M = (eight) 0x00 || msghash || salt, hash = H(M)
    //
    if ((err = SHA256_startByteWise(&md)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_addDataByteWise(&md, (uint16_t *)DB, 8)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_addDataByteWise(&md, (uint16_t *)msghash, msghashlen)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_addDataByteWise(&md, (uint16_t *)salt, saltlen)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_finalizeByteWise(&md, digest)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }

    for (i = 0, j = 0; i < (HASH_SIZE/4) && j < HASH_SIZE; i++)
    {
        hash[j++] = (digest[i] >> 24) & 255;
        hash[j++] = (digest[i] >> 16) & 255;
        hash[j++] = (digest[i] >> 8) & 255;
        hash[j++] = (digest[i]) & 255;
    }

    //
    // generate DB = PS || 0x01 || salt, PS == modulus_len - saltlen - hLen - 2 zero bytes
    //
    x = 0;

    //
    // memset(DB+x, 0, modulus_len - saltlen - hLen - 2);
    //
    for (x = 0; x < modulus_len - saltlen - hLen - 2; x++)
    {
        DB[x] = 0;
    }

    DB[x++] = 0x01;

    //
    // memcpy(DB + x, salt, saltlen);
    //
    for (i = 0; i < saltlen; i++)
    {
        DB[x++] = salt[i];
    }

    //
    // x += saltlen;
    // generate mask of length modulus_len - hLen - 1 from hash
    //
    if ((err = pkcs_1_mgf(hash, hLen, mask, modulus_len - hLen - 1)) != PKCS_STATUS_SUCCESS)
    {
        return PKCS_STATUS_FAILURE;
    }

    //
    // xor against DB
    //
    for (y = 0; y < (modulus_len - hLen - 1); y++)
    {
        DB[y] ^= mask[y];
    }

    //
    // output is DB || hash || 0xBC
    //
    if (emsa_outlen < modulus_len)
    {
        emsa_outlen = modulus_len;
        err = PKCS_STATUS_FAILURE_MEM;
        return err;
    }

    //
    // DB len = modulus_len - hLen - 1
    //
    y = 0;

    //
    // memcpy(out + y, DB, modulus_len - hLen - 1);
    //
    for (y = 0; y < modulus_len - hLen - 1; y++)
    {
        emsa_out[y] = DB[y];
    }

    //
    // y += modulus_len - hLen - 1;
    // hash: memcpy(out + y, hash, hLen);
    //
    for (i = 0; i < hLen; i++)
    {
        emsa_out[y++] = hash[i];
    }

    //
    // y += hLen;
    // 0xBC
    //
    emsa_out[y] = 0xBC;

    //
    // now clear the 8*modulus_len - modulus_bitlen most significant bits
    //
    emsa_out[0] &= 0xFF >> ((modulus_len << 3) - modulus_bitlen);

    //
    // store output size
    //
    emsa_outlen = modulus_len;
    err = PKCS_STATUS_SUCCESS;

    //
    // Free allocated memory
    //
    free(hash);
    free(salt);
    free(mask);
    free(DB);

    return err;
}

//*****************************************************************************
//
// Function to verify the signature of a data using RSASSA-PSS algorithm
//
//*****************************************************************************
int emsa_pss_decode(uint16_t *sig, uint16_t siglen, uint16_t *msghash, uint16_t msghashlen,
                    uint16_t saltlen, uint16_t modulus_bitlen, int16_t *res)
{
    uint16_t *DB, *mask, *salt, *hash;
    int x, y, hLen, modulus_len, i, j;
    int err;

    *res = -1;

    if ((msghash == NULL) || (sig == NULL))
    {
        return PKCS_STATUS_FAILURE_NULL;
    }

    hLen = HASH_SIZE;
    modulus_bitlen--;
    modulus_len = (modulus_bitlen >> 3) + (modulus_bitlen & 7 ? 1 : 0);

    //
    // check sizes
    //
    if ((saltlen > modulus_len) ||
        (modulus_len < hLen + saltlen + 2))
    {
        return PKCS_STATUS_FAILURE_SIZE;
    }

    //
    // allocate ram for DB/mask/salt/hash
    //
    DB   = (uint16_t *)malloc((modulus_len - hLen - 1) * sizeof(uint16_t));
    mask = (uint16_t *)malloc((modulus_len - hLen -1) * sizeof(uint16_t));
    salt = (uint16_t *)malloc(saltlen * sizeof(uint16_t));
    hash = (uint16_t *)malloc(hLen * sizeof(uint16_t));

    if (DB == NULL || mask == NULL || salt == NULL || hash == NULL)
    {
        if (DB != NULL)
        {
            free(DB);
        }
        if (mask != NULL)
        {
            free(mask);
        }
        if (salt != NULL)
        {
            free(salt);
        }
        if (hash != NULL)
        {
            free(hash);
        }

        return PKCS_STATUS_FAILURE_MEM;
    }

    //
    // ensure the 0xBC byte
    //
    if (sig[siglen - 1] != 0xBC)
    {
        err = PKCS_STATUS_FAILURE;
        *res = 0;
        return err;
    }

    //
    // copy out the DB
    //
    x = 0;

    //
    // memcpy(DB, sig + x, modulus_len - hLen - 1);
    //
    for (x = 0; x < modulus_len - hLen - 1; x++)
    {
        DB[x] = sig[x];
    }

    //
    // x += modulus_len - hLen - 1;
    // copy out the hash
    // memcpy(hash, sig + x, hLen);
    //
    for (i = 0; i < hLen; i++)
    {
        hash[i] = sig[x++];
    }

    //
    // check the MSB
    //
    if ((sig[0] & ~(0xFF >> ((modulus_len << 3) - (modulus_bitlen)))) != 0)
    {
        err = PKCS_STATUS_FAILURE;
        *res = 0;
        return err;
    }

    //
    // generate mask of length modulus_len - hLen - 1 from hash
    //
    if ((err = pkcs_1_mgf(hash, hLen, mask, modulus_len - hLen - 1)) != PKCS_STATUS_SUCCESS)
    {
        return PKCS_STATUS_FAILURE;
    }

    //
    // xor against DB
    //
    for (y = 0; y < (modulus_len - hLen - 1); y++)
    {
        DB[y] ^= mask[y];
    }

    //
    // now clear the first byte [make sure smaller than modulus
    //
    DB[0] &= 0xFF >> ((modulus_len << 3) - (modulus_bitlen));

    for (x = 0; x < modulus_len - saltlen - hLen - 2; x++)
    {
        if (DB[x] != 0x00)
        {
            err = PKCS_STATUS_FAILURE;
            *res = 0;
            return err;
        }
    }

    //
    // check for the 0x01
    //
    if (DB[x++] != 0x01)
    {
        err = PKCS_STATUS_FAILURE;
        *res = 0;
        return err;
    }

    //
    // M = (eight) 0x00 || msghash || salt, mask = H(M)
    //
    uint32_t digest[8];

    if ((err = SHA256_startByteWise(&md)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }

    for (i = 0; i < 8; i++)
    {
        mask[i] = '\0';
    }

    if ((err = SHA256_addDataByteWise(&md, (uint16_t *)mask, 8)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_addDataByteWise(&md, (uint16_t *)msghash, msghashlen)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_addDataByteWise(&md, (uint16_t *)DB + x, saltlen)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }
    if ((err = SHA256_finalizeByteWise(&md, digest)) != SHA256_STATUS_SUCCESS)
    {
        return err;
    }

    for (i = 0, j = 0; i < (HASH_SIZE/4) && j < HASH_SIZE; i++)
    {
        mask[j++] = (digest[i] >> 24) & 255;
        mask[j++] = (digest[i] >> 16) & 255;
        mask[j++] = (digest[i] >> 8) & 255;
        mask[j++] = (digest[i]) & 255;
    }

    for (i = 0; i < hLen; i++)
    {
        if (mask[i] != hash[i])
        {
            err = PK_STATUS_INVALID;
            break;
        }
    }

    if (err != PK_STATUS_INVALID)
    {
        err = PKCS_STATUS_SUCCESS;
        *res = 1;
    }
    else
    {
        *res = 0;
    }

    //
    // Free allocated memory
    //
    free(hash);
    free(salt);
    free(mask);
    free(DB);

    return err;
}
//
// End of file
//
