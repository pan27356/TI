//###########################################################################
//
// FILE:   aes_cmac.h
//
// TITLE:  AES CMAC mode header file
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

#ifndef AES_CMAC_H
#define AES_CMAC_H

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
//
//! \addtogroup aes_cmac_api AES CMAC API
//! @{
//
//*****************************************************************************
//*****************************************************************************
#include <stdint.h>
#include "aes_common.h"

#ifndef MEM_PACKED_SPEED_OPT
//*****************************************************************************
//
//! Perform AES CMAC to generate Message Authentication Code (MAC)
//!
//! \param text is the input plaintext or ciphertext and once operation is
//!        complete, this parameter contains the output plaintext or ciphertext
//! \param length is the length of the input data in blocks (block size is
//!        128-bits)
//! \param key is the AES key
//! \param keysize is the size of the AES key
//!
//! This function performs AES Cipher-based Message Authentication
//! (CMAC) on the requested number of 128-bit input plain text blocks.
//! The calculated Message Authentication Code(MAC) is returned.
//!
//! - \b Note: Size of the plain text must be a multiple of 128-bits
//!
//! \return MAC Starting address of a 128 element array
//!         containing the MAC(128-bits)
//
//*****************************************************************************
extern uint16_t *AES_performCMAC(uint16_t *text, uint16_t length,
                                 uint16_t *key, AES_KeySize keysize);
#endif

//*****************************************************************************
//
//! Perform AES fast CMAC to generate Message Authentication Code (MAC)
//!
//! \param text is the input plaintext or ciphertext and once operation is
//!        complete, this parameter contains the output plaintext or ciphertext
//! \param length is the length of the input data in blocks (block size is
//!        128-bits)
//! \param key is the AES key
//! \param keysize is the size of the AES key
//!
//! This function performs AES fast Cipher-based Message Authentication
//! (CMAC) on the requested number of 128-bit input plain text blocks.
//! The calculated Message Authentication Code(MAC) is returned.
//!
//! - \b Note: Size of the plain text must be a multiple of 128-bits
//!
//! \return MAC Starting address of a 128 element array
//!         containing the MAC(128-bits)
//
//*****************************************************************************
extern uint16_t *AES_performCMACFast(uint16_t *text, uint16_t length,
                                     uint16_t *key, AES_KeySize keysize);

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

#endif //AES_CMAC_H
