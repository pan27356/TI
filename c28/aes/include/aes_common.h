//###########################################################################
//
// FILE:   aes_common.h
//
// TITLE:  AES algorithm header file
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

#ifndef AES_H
#define AES_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
//! Modes that can be used in the encryption/decryption functions
//
//*****************************************************************************
typedef enum
{
     AES_OPMODE_ENCRYPT,   //!< Encryption mode
     AES_OPMODE_DECRYPT    //!< Decryption mode
} AES_OperationMode;

//*****************************************************************************
//
//! Key sizes that can be used in the AES algorithm
//
//*****************************************************************************
typedef enum
{
     AES_128,   //!< AES 128 bit key size
     AES_256    //!< AES 128 bit key size
} AES_KeySize;

#ifndef MEM_PACKED_SPEED_OPT
//*****************************************************************************
//
//! Perform AES Encryption/Decryption
//!
//! \param text is the input plaintext or ciphertext and once operation is
//!        complete, this parameter contains the output plaintext or ciphertext
//! \param mode is the AES operation mode of encryption or decryption
//!
//! This function performs AES encryption/decryption algorithm
//! with 128-bit/256-bit key sizes
//!
//! \return None.
//
//*****************************************************************************
void AES_perform(uint16_t *text, AES_OperationMode mode);

//*****************************************************************************
//
//! Perform AES key expansion
//!
//! \param key is the AES key
//! \param keysize is the size of the AES key
//!
//! This function performs AES key expansion algorithm for 128/256 bit keys
//!
//! \return None.
//
//*****************************************************************************
void AES_expandKey(uint16_t *key, AES_KeySize keysize);
#endif

//*****************************************************************************
//
//! Perform AES fast Encryption/Decryption
//!
//! \param text is the input plaintext or ciphertext and once operation is
//!        complete, this parameter contains the output plaintext or ciphertext
//! \param mode is the AES operation mode of encryption or decryption
//!
//! This function performs AES fast encryption/decryption algorithm
//! with 128-bit/256-bit key sizes
//!
//! \return None.
//
//*****************************************************************************
void AES_performFast(uint16_t *text, AES_OperationMode mode);

//*****************************************************************************
//
//! Perform AES key expansion
//!
//! \param key is the AES key
//! \param keysize is the size of the AES key
//! \param mode is operation mode encryption or decryption
//!
//! This function performs AES key expansion algorithm for 128/256 bit keys
//!
//! \return None.
//
//*****************************************************************************
void AES_expandKeyFast(uint16_t *key, AES_KeySize keysize,
                       AES_OperationMode mode);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* AES_AES */
