//###########################################################################
//
// FILE:   rsassa_pss.c
//
// TITLE:  RSASSA-PSS algorithm to generate and verify digital signature
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

#include "rsassa_pss.h"
#include "emsa_pss.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

//*****************************************************************************
//
// Function to write data represented in a hex string into the memory bytewise
//
//*****************************************************************************
rsa_err rsa_hex_to_data(unsigned char *hex_str, uint16_t *data)
{
    rsa_err err = 0;
    uint16_t i = 0, j = 0;

    while(i < strlen((char *)hex_str))
    {
        if (((uint16_t)hex_str[i] >= 48) && ((uint16_t)hex_str[i] <= 57))
            data[j] = (uint16_t)hex_str[i] - 48;
        else if (((uint16_t)hex_str[i] >= 65) && ((uint16_t)hex_str[i] <= 70))
            data[j] = (uint16_t)hex_str[i] - 55;
        else if (((uint16_t)hex_str[i] >= 97) && ((uint16_t)hex_str[i] <= 102))
            data[j] = (uint16_t)hex_str[i] - 87;
        else
        {
            err = 3;
            return err;
        }

        if(++i >= strlen((char *)hex_str))
            break;

        data[j] <<= 4;
        if (((uint16_t)hex_str[i] >= 48) && ((uint16_t)hex_str[i] <= 57))
            data[j] |= ((uint16_t)hex_str[i] - 48);
        else if (((uint16_t)hex_str[i] >= 65) && ((uint16_t)hex_str[i] <= 70))
            data[j] |= ((uint16_t)hex_str[i] - 55);
        else if (((uint16_t)hex_str[i] >= 97) && ((uint16_t)hex_str[i] <= 102))
            data[j] |= ((uint16_t)hex_str[i] - 87);
        else
        {
            err = 3;
            return err;
        }

        i++;
        j++;

    }

    return err;
}

//*****************************************************************************
//
// Function to generate a signature of the data using RSASSA-PSS algorithm
//
//*****************************************************************************
rsa_err rsassa_pss_sign(uint16_t *hash, uint16_t hashlen, uint16_t saltlen,
                        rsa_PrivateKey *key_pvt, rsa_Modulus *modulus,
                        uint16_t modulus_bitlen, yarrow_prng *prng,
                        rsa_Signature *sign)
{
   rsa_err err;

   uint16_t EM_len = modulus_bitlen/8;

   //
   // Array to hold the pss encoding of the message
   //
   uint16_t *EM_str = (uint16_t *)malloc(EM_len);

   //
   // Multiple precision integer to hold the encoded message
   //
   mp_int EM;

   //
   // EMSA-PSS encoding of the message hash
   //
   err = emsa_pss_encode(hash, hashlen, saltlen, modulus_bitlen, prng, \
                         EM_str, EM_len);

   mp_init(&EM);
   mp_read_from_mem(&EM, EM_str, EM_len);
   mp_init(sign);

   //
   // Modular exponentiation to generate signature
   //
   mp_exptmod(&EM, key_pvt, modulus, sign);

   return err;
}

//*****************************************************************************
//
// Function to verify the signature of a data using RSASSA-PSS algorithm
//
//
//*****************************************************************************
rsa_err rsassa_pss_verify( rsa_Signature *sign, uint16_t *hash, uint16_t hashlen,
                          uint16_t saltlen, rsa_PublicKey *key_pub,
                          rsa_Modulus *modulus, uint16_t modulus_bitlen,
                          int16_t *result)
{
   rsa_err err;

   uint16_t EM_len = modulus_bitlen/8;

   //
   // Array to hold the pss encoding of the message
   //
   uint16_t *EM_str = (uint16_t *)malloc(EM_len);

   //
   // Multiple precision integer to hold the encoded message
   //
   mp_int EM;

   mp_init(&EM);

   //
   // Modular exponentiation to generate the message encoding from the signature
   //
   mp_exptmod(sign, key_pub, modulus, &EM);

   mp_to_mem(&EM, EM_str, EM_len);

   //
   // EMSA-PSS decoding to verify the message encoding
   //
   err = emsa_pss_decode(EM_str, EM_len, hash, hashlen, saltlen, modulus_bitlen, result);

   return err;
}
//
// End of file
//
