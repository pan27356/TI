//###########################################################################
//
// FILE:   yarrow.h
//
// TITLE:  Yarrow PRNG algorithm header file
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

#ifndef YARROW_H_
#define YARROW_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "aes_ctr.h"
#include "sha256.h"

typedef unsigned char uc;

#define MAXBLOCKSIZE 144
#define YARROW_STATUS_SUCCESS 1
#define YARROW_STATUS_ERROR_NULL -1

//*****************************************************************************
//
//  Data structure to handle Yarrow PRNG algortithm
//
//*****************************************************************************
typedef struct yarrow_prng
{
    uc pool[MAXBLOCKSIZE];
    uc ready;
    uc nounceCounter[16];
    uc key[32];
} yarrow_prng;

//*****************************************************************************
//
//! Initialize yarrow handle with nounce counter values
//!
//! \param prng is the pointer to the yarrow PRNG handle
//! \param nounceCounter is the pointer to the array which contains the counter
//!        values to be initialized with
//!
//! \return Returns YARROW_STATUS_SUCCESS if successful.
//
//*****************************************************************************
int yarrow_init_with_nounce(yarrow_prng *prng, const uc *nounceCounter);

//*****************************************************************************
//
//! Initialize yarrow handle with default nounce counter value '0'
//!
//! \param prng is the pointer to the yarrow PRNG handle
//!
//! \return Returns YARROW_STATUS_SUCCESS if successful.
//
//*****************************************************************************
int yarrow_init_default_nounce(yarrow_prng *prng);

//*****************************************************************************
//
//! Introduce entropy in the algorithm to generate pseudo-random values
//!
//! \param in is the random input string which will be used to introduce entropy
//! \param inlen is the length of the random input string
//! \param prng is the pointer to the yarrow PRNG handle
//!
//! \return Returns YARROW_STATUS_SUCCESS if successful.
//
//*****************************************************************************
int yarrow_add_entropy(uc *in, const uint32_t inlen, yarrow_prng *prng);

//*****************************************************************************
//
//! Prepare the yarrow PRNG handle to generate random values
//!
//! \param prng is the pointer to the yarrow PRNG handle
//!
//! \return Returns YARROW_STATUS_SUCCESS if successful.
//
//*****************************************************************************
int yarrow_ready(yarrow_prng *prng);

//*****************************************************************************
//
//! Read random values using yarrow PRNG
//!
//! \param prng is the pointer to the yarrow PRNG handle
//! \param out is the output string of random values
//! \param outlen is the length of the output string of random values
//!
//! \return Returns outlen if successful.
//
//*****************************************************************************
int yarrow_read(yarrow_prng *prng, uc *out, uc outlen);

#ifdef __cplusplus
}
#endif

#endif /* YARROW_H_ */
