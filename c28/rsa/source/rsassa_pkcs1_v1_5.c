//###########################################################################
//
// FILE:   rsassa_pkcs1_v1_5.c
//
// TITLE:  RSASSA-PKCS algorithm to generate and verify digital signature
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

#include "rsassa_pkcs1_v1_5.h"
#include "emsa_pkcs1_v1_5.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


rsa_err rsassa_pkcs1_v1_5_sign(rsa_PrivateKey* key_pvt, rsa_Modulus* modulus,
    rsa_Signature* sign, uint16_t *hash, uint16_t hash_size)
{
    //Array to hold the padding string
    uint16_t EM_str[256];

    //Padding length
    uint16_t EM_len = ASN_1_PAD_SIZE + hash_size;

    //
    // Multiple precision integer to hold the encoded message
    //
    mp_int EM;

    //
    // EMSA-PKCS1 encoding of the message hash
    //
    if(PKCS_STATUS_SUCCESS != emsa_pkcs1_v1_5_encode(EM_str, hash, hash_size))
    {
        return -1;
    }

    if(0 != mp_init(&EM))
    {
        return -1;
    }

    if(0 != mp_read_from_mem(&EM, EM_str, EM_len))
    {
        mp_clear(&EM);
        return -1;
    }

    //
    // Modular exponentiation to generate signature
    //

    if(0 != mp_exptmod(&EM, key_pvt, modulus, sign))
    {
        mp_clear(&EM);
        mp_clear(sign);
        return -1;
    }

    mp_clear(&EM);

    return 0;
}

rsa_err rsassa_pkcs1_v1_5_verify(rsa_Signature* sign, uint16_t* hash, uint16_t hash_size,
    uint16_t mod_len, rsa_PublicKey* key_pub,
    rsa_Modulus* modulus,
    int16_t* result)
{
    rsa_err rErr = 0;

    //
    // Array to hold the PKCS encoding of the message
    //
    uint16_t *EM_str = NULL;

    //
    // Multiple precision integer to hold the encoded message
    //
    mp_int EM;

    if(mp_init(&EM) != 0)
    {
        *result = -1;
        return -1;
    }

    //
    // Modular exponentiation to generate the message encoding from the signature
    //
    if(mp_exptmod(sign, key_pub, modulus, &EM) != 0)
    {
        *result = -1;
        mp_clear(&EM);
        return -1;
    }

    EM_str = (uint16_t *)malloc(mod_len);

    if(EM_str == NULL)
    {
        *result = -1;
        return -1;
    }

    if(mp_to_mem(&EM, EM_str, mod_len) != 0)
    {
        *result = -1;
        free(EM_str);
        mp_clear(&EM);
        return -1;
    }

    rErr = emsa_pkcs1_v1_5_decode(EM_str, hash, hash_size, result);

    if(EM_str)
    {
        free(EM_str);
    }

    mp_clear(&EM);

    return rErr;
}
