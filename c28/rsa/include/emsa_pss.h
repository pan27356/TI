//###########################################################################
//
// FILE:   emsa_pss.h
//
// TITLE:  EMSA-PSS message encoding header file
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

#ifndef EMSA_PSS_H_
#define EMSA_PSS_H_

#include <stdint.h>
#include "yarrow.h"

//*****************************************************************************
//
// Defines
//
//*****************************************************************************
#define HASH_SIZE       32    // 32 byte message digest output for SHA-256
#define PKCS_STATUS_SUCCESS 0
#define PKCS_STATUS_FAILURE 1
#define PKCS_STATUS_FAILURE_SIZE 2
#define PKCS_STATUS_FAILURE_NULL 3
#define PKCS_STATUS_FAILURE_READ 4
#define PKCS_STATUS_FAILURE_MEM 5
#define PK_STATUS_INVALID 6
#define STORE32H(x, y)                               \
    do                                               \
    {                                                \
        (y)[0] = (unsigned char)(((x) >> 24) & 255); \
        (y)[1] = (unsigned char)(((x) >> 16) & 255); \
        (y)[2] = (unsigned char)(((x) >> 8) & 255);  \
        (y)[3] = (unsigned char)((x)&255);           \
    } while (0)

//*****************************************************************************
//
//! PKCS1_MGF mask generation using SHA-256
//!
//! \param seed is the pointer to the input seed
//! \param seedlen is the length of the seed in bytes
//! \param mask is the pointer to the output mask
//! \param masklen is the length of the output mask in bytes
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
int pkcs_1_mgf(uint16_t *seed, int16_t seedlen, uint16_t *mask, int16_t masklen);

//*****************************************************************************
//
//! EMSA-PSS encode message
//!
//! \param msghash is the pointer to the bytewise hash digest of the message
//! \param hashlen is the length of the hash digest of the message in bytes
//! \param saltlen is the length of the random salt in bytes
//! \param modulus_bitlen is the length of the RSA modulus in bits (not bytes)
//! \param prng is the pointer to the yarrow prng handler to generate
//!        random salt
//! \param emsa_out is the pointer to hold the encoded data
//! \param emsa_outlen is the output length of the encoded data
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
int emsa_pss_encode(uint16_t *msghash, uint16_t msghashlen, uint16_t saltlen,
                    uint16_t modulus_bitlen, yarrow_prng *prng,
                    uint16_t *emsa_out, uint16_t emsa_outlen);

//*****************************************************************************
//
//! EMSA-PSS decode message
//!
//! \param sig is the pointer to the message encoding to be decoded
//! \param siglen is the length in bytes of the message encoding to be decoded
//! \param msghash is the pointer to the bytewise hash digest of the message
//! \param hashlen is the length of the hash digest of the message in bytes
//! \param saltlen is the length of the random salt in bytes
//! \param modulus_bitlen is the length of the RSA modulus in bits (not bytes)
//! \param res is a pointer to the variable to hold the verification result
//!        1  - Verification successful
//!        0  - Incorrect signature. Verification failed
//!        -1 - Verification incomplete
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
int emsa_pss_decode(uint16_t *sig, uint16_t siglen, uint16_t *msghash, uint16_t msghashlen,
                    uint16_t saltlen, uint16_t modulus_bitlen, int16_t *res);

#endif /* EMSA_PSS_H_ */
