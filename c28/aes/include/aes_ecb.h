//###########################################################################
//
// FILE:   aes_ecb.h
//
// TITLE:  AES ECB mode header file
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

#ifndef AES_ECB_H_
#define AES_ECB_H_

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
#include "aes_common.h"

#ifndef MEM_PACKED_SPEED_OPT
//*****************************************************************************
//
//! Perform AES ECB Encryption/Decryption
//!
//! \param text is the input plaintext or ciphertext and once operation is
//!        complete, this parameter contains the output plaintext or ciphertext
//! \param length is the length of the input data in blocks (block size is
//!        128-bits)
//! \param key is the AES key
//! \param keysize is the size of the AES key
//! \param mode is the AES operation mode of encryption or decryption
//!
//! This function performs AES Electronic Code Book (ECB) mode
//! encryption or decryption on the requested number of 128-bit input blocks.
//!
//! \return None.
//
//*****************************************************************************
extern void AES_performECB(uint16_t *text, uint16_t length, uint16_t *key,
                           AES_KeySize keysize, AES_OperationMode mode);
#endif

//*****************************************************************************
//
//! Perform AES ECB fast Encryption/Decryption
//!
//! \param text is the input plaintext or ciphertext and once operation is
//!        complete, this parameter contains the output plaintext or ciphertext
//! \param length is the length of the input data in blocks (block size is
//!        128-bits)
//! \param key is the AES key
//! \param keysize is the size of the AES key
//! \param mode is the AES operation mode of encryption or decryption
//!
//! This function performs AES Electronic Code Book (ECB) mode fast
//! encryption or decryption on the requested number of 128-bit input blocks.
//!
//! \return None.
//
//*****************************************************************************
extern void AES_performECBFast(uint16_t *text, uint16_t length, uint16_t *key,
                               AES_KeySize keysize, AES_OperationMode mode);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* AES_ECB_H_ */
