//###########################################################################
//
// FILE:   sha256.h
//
// TITLE:  SHA-256 header file
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

#ifndef SHA256_H_
#define SHA256_H_
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
//! \addtogroup sha256_api SHA256 API
//! @{
//
//*****************************************************************************
#include <stddef.h>
#include <stdint.h>

//*****************************************************************************
//
// SHA-256 object
//
//*****************************************************************************
typedef struct {
     uint32_t  bitsProcessed;  // Only 2^32 bits (512 MiBytes) are supported
     int16_t   offsetWb;       // Byte offset into Ws, used to load message
     uint32_t  digest[8];      // Holds intermediate/final digest
     uint32_t  Ws[16];
} SHA256_ObjectWordWise;

typedef struct {
     uint32_t  bitsProcessed;  // Only 2^32 bits (512 MiBytes) are supported
     int16_t   offsetWb;       // Byte offset into Ws, used to load message
     uint32_t  digest[8];      // Holds intermediate/final digest
     uint16_t  Ws[64];
} SHA256_ObjectByteWise;

//*****************************************************************************
//
// Handle to the SHA-256 object
//
//*****************************************************************************
typedef SHA256_ObjectWordWise* SHA256_HandleWordWise;
typedef SHA256_ObjectByteWise* SHA256_HandleByteWise;

//*****************************************************************************
//
// Define Macros
//
//*****************************************************************************
/** SHA256-  NULL input error */
#define SHA256_STATUS_NULL_INPUT       (uint16_t)0x0000
/** SHA256 operation successfull */
#define SHA256_STATUS_SUCCESS          (uint16_t)0xABCD
/** SHA256-  length of input too large */
#define SHA256_STATUS_LENGTH_TOO_LARGE (uint16_t)0xBADA
/** SHA256-  input not aligned */
#define SHA256_STATUS_NOT_ALIGNED      (uint16_t)0x0BAD

#define SHA256_GETU32(plaintext) (((uint32_t)(plaintext)[0] << 24U) ^ \
                                  ((uint32_t)(plaintext)[1] << 16U) ^ \
                                  ((uint32_t)(plaintext)[2] <<  8U) ^ \
                                  ((uint32_t)(plaintext)[3]))
#define SHA256_PUTU32(ciphertext, st) \
        { (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU); \
          (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU); \
          (ciphertext)[2] = (uint16_t)((uint16_t)((st) >>  8U) & 0x00FFU); \
          (ciphertext)[3] = (uint16_t)((uint16_t)(st) & 0x00FFU); }

#define SHA256_SHR(x, a)      ((x) >> (a))
#define SHA256_ROTR32(x, n)   (( SHA256_SHR(x, n) ) ^ ( (x) << (32 - (n)) ))

//*****************************************************************************
//
// SHA256_CH function from NIST FIPS 180-4, Eq 4.2.
// Implementation is refactored for efficiency.
//
//*****************************************************************************
#define SHA256_CH(x, y, z)   (((x) & ((y) ^ (z))) ^ (z))

//*****************************************************************************
//
// SHA256_MAJ function from NIST FIPS 180-4, Eq 4.3.
// Implementation is refactored for efficiency.
//
//*****************************************************************************
#define SHA256_MAJ(x, y, z)  ((((y)^(z)) & (x)) ^ ((y) & (z)))

//*****************************************************************************
//
// Big Sigma 0-512 function from NIST FIPS 180-4, Eq 4.4.
//
//*****************************************************************************
#define SHA256_SIGZ(x)       (SHA256_ROTR32(x, 2) ^ SHA256_ROTR32(x, 13) ^ \
                              SHA256_ROTR32(x, 22))

//*****************************************************************************
//
// Big Sigma 1-512 function from NIST FIPS 180-4, Eq 4.5.
//
//*****************************************************************************
#define SHA256_SIG1(x)       (SHA256_ROTR32(x, 6) ^ SHA256_ROTR32(x, 11) ^ \
                              SHA256_ROTR32(x, 25))

//*****************************************************************************
//
// Little Sigma 0-512 function from NIST FIPS 180-4, Eq 4.6.
//
//*****************************************************************************
#define SHA256_SIGMAZ(x)     (SHA256_ROTR32(x, 7) ^ SHA256_ROTR32(x, 18) ^ \
                              SHA256_SHR(x, 3))

//*****************************************************************************
//
// Little Sigma 1-512 function from NIST FIPS 180-4, Eq 4.7.
//
//*****************************************************************************
#define SHA256_SIGMA1(x)     (SHA256_ROTR32(x, 17) ^ SHA256_ROTR32(x, 19) ^ \
                              SHA256_SHR(x, 10))

//*****************************************************************************
//
//! Perform a complete hash operation when input is supplied as 32-bit words,
//! producing a final digest for the data.
//!   - This function wraps #SHA256_startWordWise(), #SHA256_addDataWordWise(),
//!     and #SHA256_finalizeWordWise().
//!   - There is no need to call #SHA256_startWordWise() prior to calling
//!     this function.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.)
//!
//! \param handle  A 'SHA256_HandleWordWise' handle
//! \param data    32-bit pointer pointing to the starting memory location of
//!                the data to be hashed
//! \param length  Length of the data (in number of bytes) to be hashed.
//!                Note that for word-wise input, length of the data should be
//!                a multiple of 4.
//! \param digest  Output location for the final digest
//!
//! \return #SHA256_STATUS_SUCCESS           The hash operation succeeded.
//!                                          #SHA256_STATUS_LENGTH_TOO_LARGE -
//!                                          The requested length of data to
//!                                          hash is more than the
//!                                          implementation supports.
//!                                          #SHA256_STATUS_NULL_INPUT - One or
//!                                          more of the pointer inputs is NULL.
//!                                          #SHA256_STATUS_NOT_ALIGNED - Length.
//!                                          is not a multiple of 4
//
//*****************************************************************************
uint16_t SHA256_hashWordWise(SHA256_HandleWordWise handle, uint32_t *data,
                             size_t length, uint32_t digest[8]);

//*****************************************************************************
//
//! Perform a complete hash operation when input is supplied as 32-bit words,
//! with High-Low words Swapped,
//! producing a final digest for the data.
//!   - This function wraps #SHA256_startWordWise(), #SHA256_addDataWordWiseSwapped(),
//!     and #SHA256_finalizeWordWise().
//!   - There is no need to call #SHA256_startWordWise() prior to calling
//!     this function.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.)
//!
//! \param handle  A 'SHA256_HandleWordWise' handle
//! \param data    32-bit pointer pointing to the starting memory location of
//!                the data to be hashed
//! \param length  Length of the data (in number of bytes) to be hashed.
//!                Note that for word-wise input, length of the data should be
//!                a multiple of 4.
//! \param digest  Output location for the final digest
//!
//! \return #SHA256_STATUS_SUCCESS           The hash operation succeeded.
//!                                          #SHA256_STATUS_LENGTH_TOO_LARGE -
//!                                          The requested length of data to
//!                                          hash is more than the
//!                                          implementation supports.
//!                                          #SHA256_STATUS_NULL_INPUT - One or
//!                                          more of the pointer inputs is NULL.
//!                                          #SHA256_STATUS_NOT_ALIGNED - Length.
//!                                          is not a multiple of 4
//
//*****************************************************************************
uint16_t SHA256_hashWordWiseSwapped(SHA256_HandleWordWise handle, uint32_t *data,
                             size_t length, uint32_t digest[8]);

//*****************************************************************************
//
//! Perform a complete hash operation when input is supplied byte-wise,
//! producing a final digest for the data.
//!   - This function wraps #SHA256_startByteWise(), #SHA256_addDataByteWise(),
//!     and #SHA256_finalizeByteWise().
//!   - There is no need to call #SHA256_startByteWise() prior to calling
//!     this function.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.)
//!
//! \param handle  A 'SHA256_HandleByteWise' handle
//! \param data    16-bit pointer pointing to the memory location of the
//!                starting byte the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed.
//! \param digest  Output location for the final digest
//!
//! \return #SHA256_STATUS_SUCCESS           The hash operation succeeded.
//! \return #SHA256_STATUS_LENGTH_TOO_LARGE  The requested length of data to
//!                                          hash is more than the
//!                                          implementation supports.
//! \return #SHA256_STATUS_NULL_INPUT        One or more of the pointer inputs
//!                                          is NULL.
//
//*****************************************************************************
uint16_t SHA256_hashByteWise(SHA256_HandleByteWise handle, uint16_t *data,
                             size_t length, uint32_t digest[8]);

//*****************************************************************************
//
//! Initialize a 'SHA256SW_HandleWordWise' handle, preparing for hashing data.
//!
//! \param handle  A 'SHA256_HandleWordWise' handle
//!
//! \return #SHA256_STATUS_SUCCESS           The hash operation succeeded.
//! \return #SHA256_STATUS_NULL_INPUT        One or more of the pointer inputs
//!                                          is NULL.
//
//*****************************************************************************
uint16_t SHA256_startWordWise(SHA256_HandleWordWise handle);

//*****************************************************************************
//
//! Initialize a 'SHA256SW_HandleByteWise' handle, preparing for hashing data.
//!
//! \param handle  A 'SHA256_HandleByteWise' handle
//!
//! \return #SHA256_STATUS_SUCCESS           The hash operation succeeded.
//! \return #SHA256_STATUS_NULL_INPUT        One or more of the pointer inputs
//!                                          is NULL.
//
//*****************************************************************************
uint16_t SHA256_startByteWise(SHA256_HandleByteWise handle);

//*****************************************************************************
//
//! Add data to SHA256 operation when inputs are supplied as 32-bit words
//!   - Adds data to a hash operation. The @c handle must have been
//!     initialized by a call to SHA256_startWordWise first.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.).
//!   - After passing in all data to be hashed, call #SHA256_finalizeWordWise()
//!     to obtain the final digest.
//!
//! \param handle  A 'SHA256_HandleWordWise' handle.
//! \param data    32-bit pointer pointing to the starting memory location of
//!                the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed
//!                Note that for word-wise input, length of the data should
//!                be a multiple of 4.
//!
//! \return #SHA256_STATUS_SUCCESS            The hash operation succeeded.
//! \return #SHA256_STATUS_LENGTH_TOO_LARGE   The requested length of data to
//!                                           hash is more than the
//!                                           implementation supports.
//! \return #SHA256_STATUS_NULL_INPUT         One or more of the pointer inputs
//!                                           is NULL.
//! \return #SHA256_STATUS_NOT_ALIGNED        Length is not a multiple of 4
//
//*****************************************************************************
uint16_t SHA256_addDataWordWise(SHA256_HandleWordWise handle, uint32_t *data,
                                size_t length);

//*****************************************************************************
//
//! Add data to SHA256 operation when inputs are supplied as 32-bit words
//!   - Input words are Swapped High-Low
//!   - Adds data to a hash operation. The @c handle must have been
//!     initialized by a call to SHA256_startWordWise first.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.).
//!   - After passing in all data to be hashed, call #SHA256_finalizeWordWise()
//!     to obtain the final digest.
//!
//! \param handle  A 'SHA256_HandleWordWise' handle.
//! \param data    32-bit pointer pointing to the starting memory location of
//!                the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed
//!                Note that for word-wise input, length of the data should
//!                be a multiple of 4.
//!
//! \return #SHA256_STATUS_SUCCESS            The hash operation succeeded.
//! \return #SHA256_STATUS_LENGTH_TOO_LARGE   The requested length of data to
//!                                           hash is more than the
//!                                           implementation supports.
//! \return #SHA256_STATUS_NULL_INPUT         One or more of the pointer inputs
//!                                           is NULL.
//! \return #SHA256_STATUS_NOT_ALIGNED        Length is not a multiple of 4
//
//*****************************************************************************
uint16_t SHA256_addDataWordWiseSwapped(SHA256_HandleWordWise handle, uint32_t *data,
                                size_t length);

//*****************************************************************************
//
//! Add data to SHA256 operation when inputs are supplied byte-wise
//!   - Adds data to a hash operation. The @c handle must have been
//!     initialized by a call to SHA256_startByteWise first.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.).
//!   - After passing in all data to be hashed, call #SHA256_finalizeWordWise()
//!     to obtain the final digest.
//!
//! \param handle  A 'SHA256_HandleByteWise' handle.
//! \param data    16-bit pointer pointing to the memory location of the
//!                starting byte the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed
//!
//! \return #SHA256_STATUS_SUCCESS            hash operation succeeded.
//!                                           #SHA256_STATUS_LENGTH_TOO_LARGE -
//!                                           requested length of data to
//!                                           hash is more than supported length.
//!                                           #SHA256_STATUS_NULL_INPUT- One or
//!                                           more of the pointer inputs is NULL
//
//*****************************************************************************
uint16_t SHA256_addDataByteWise(SHA256_HandleByteWise handle, uint16_t *data,
                                size_t length);

//*****************************************************************************
//
//! Finalize the SHA256 operation when input is supplied as 32-bit words,
//! creating the final digest.
//!   - After calling this function, @c handle should not be used again
//!     until it has been reinitialized via a call to #SHA256_startWordWise().
//!
//! \param handle  A 'SHA256_HandleWordWise' handle
//! \param digest  Output location for the final digest
//! \param digest  Output location for the final digest

//!
//! \return #SHA256_STATUS_SUCCESS          The hash operation succeeded.
//! \return #SHA256_STATUS_NULL_INPUT       One or more of the pointer inputs
//!                                         is NULL.
//
//*****************************************************************************
uint16_t SHA256_finalizeWordWise(SHA256_HandleWordWise handle,
                                 uint32_t digest[8]);

//*****************************************************************************
//
//! Finalize the SHA256 operation when input is supplied byte-wise,
//! creating the final digest.
//!   - After calling this function, @c handle should not be used again
//!     until it has been reinitialized via a call to #SHA256_startByteWise().
//!
//! \param handle  A 'SHA256_HandleByteWise' handle
//! \param digest  Output location for the final digest
//!
//! \return #SHA256_STATUS_SUCCESS          The hash operation succeeded.
//! \return #SHA256_STATUS_NULL_INPUT       One or more of the pointer inputs
//!                                         is NULL.
//
//*****************************************************************************
uint16_t SHA256_finalizeByteWise(SHA256_HandleByteWise handle,
                                 uint32_t digest[8]);

//*****************************************************************************
//
//! Cancels SHA256 operation by clearing intermediate
//! data stored in the 'SHA256_HandleWordWise' handle.
//!   - The handle will not be ready for a new operation until after
//!     #SHA256_startWordWise() is called on the handle.
//!
//! \param handle  A 'SHA256_HandleWordWise' handle
//!
//
//*****************************************************************************
void SHA256_cancelWordWise(SHA256_HandleWordWise handle);

//*****************************************************************************
//
//! Cancels SHA256 operation by clearing intermediate
//! data stored in the 'SHA256_HandleByteWise' handle.
//!   - The handle will not be ready for a new operation until after
//!     #SHA256_startByteWise() is called on the handle.
//!
//! \param handle  A 'SHA256_HandleByteWise' handle
//!
//
//*****************************************************************************
void SHA256_cancelByteWise(SHA256_HandleByteWise handle);

//*****************************************************************************
//
//! Performs core SHA2-256 algorithm on one 512 bit block of data when input
//! is supplied as 32-bit words.
//!   - object->digest will contain the updated digest resulting from
//!     hashing the block.
//!
//! \param digest  pre-loaded with previous block's digest (or initial
//!                digest if call is to process first block)
//!                On function return digest will hold the updated digest.
//! \param Ws      loaded with data block, including padding as specified by
//!                the SHA256 standard.
//
//*****************************************************************************
void SHA256_processBlockWordWise(uint32_t digest[8], uint32_t Ws[16]);
extern void _SHA256_processBlockWordWise_casm_C28(uint32_t digest[8], uint32_t Ws[16]);

//*****************************************************************************
//
//! Performs core SHA2-256 algorithm on one 512 bit block of data when input
//! is supplied byte-wise.
//!   - object->digest will contain the updated digest resulting from
//!     hashing the block.
//!
//! \param digest  pre-loaded with previous block's digest (or initial
//!                digest if call is to process first block)
//!                On function return digest will hold the updated digest.
//! \param Ws      loaded with data block, including padding as specified by
//!                the SHA256 standard.
//
//*****************************************************************************
void SHA256_processBlockByteWise(uint32_t digest[8], uint16_t Ws[64]);
extern void _SHA256_processBlockByteWise_casm_C28(uint32_t digest[8], uint16_t Ws[64]);


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
#endif /* SHA256_H_ */
