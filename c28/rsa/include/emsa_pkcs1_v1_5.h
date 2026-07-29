//###########################################################################
//
// FILE:   emsa_pkcs1_v1_5.h
//
// TITLE:  EMSA-PKCS message encoding header file
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

#ifndef __EMSA_PKCS1_V1_5_H__
#define __EMSA_PKCS1_V1_5_H__

#include <stdint.h>

//*****************************************************************************
//
// Defines
//
//*****************************************************************************
#define SHA256_HASH_SIZE            32    // 32 byte message digest output for SHA-256
#define SHA384_HASH_SIZE            48    // 48 byte message digest output for SHA-384
#define ASN_1_PAD_SIZE              30
#define PKCS_STATUS_SUCCESS         0
#define PKCS_STATUS_FAILURE         1
#define PKCS_STATUS_FAILURE_SIZE    2
#define PKCS_STATUS_FAILURE_NULL    3
#define PKCS_STATUS_FAILURE_READ    4
#define PKCS_STATUS_FAILURE_MEM     5
#define PKCS_STATUS_FAILURE_LEN     6
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
//! EMSA-PKCS encode message
//!
//! \param emsa_out is the pointer to hold the encoded data
//! \param emsa_outlen is the output length of the encoded data
//! \param digest is the serialized hash data based on the SHA encoding type
//! \param hash_size is the length of the hash
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
int emsa_pkcs1_v1_5_encode(uint16_t* emsa_out, uint16_t* digest, uint16_t hash_size);

//*****************************************************************************
//
//! EMSA-PKCS decode message
//!
//! \param EM_Str is the pointer to the EMSA padding bytes
//! \param hash is the pointer to the hash to be compared (serialized digest)
//! \param hash_size is the size of the hash based on the SHA encoding type
//! \param result is a pointer to the variable to hold the verification result
//!        1  - Verification successful
//!        0  - Incorrect signature. Verification failed
//!       -1  - Verification incomplete
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
int emsa_pkcs1_v1_5_decode(uint16_t* EM_Str, uint16_t *hash, uint16_t hash_size, int16_t* result);

#endif
