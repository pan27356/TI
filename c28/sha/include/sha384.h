//###########################################################################
//
// FILE:   sha384.h
//
// TITLE:  SHA-384 header file
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

#ifndef SHA384_H_
#define SHA384_H_
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
//! \addtogroup sha384_api SHA384 API
//! @{
//
//*****************************************************************************
#include <stddef.h>
#include <stdint.h>

//*****************************************************************************
//
// SHA-384 object
//
//*****************************************************************************
typedef struct {
     uint32_t  bitsProcessed;   // Only 2^32 bits (512 MiBytes) are supported
     int16_t   offsetWb;        // Byte offset into Ws, used to load message
     uint64_t  digest[8];      // Holds intermediate/final digest
     uint32_t  Ws[32];
} SHA384_ObjectWordWise;

typedef struct {
     uint32_t  bitsProcessed;   // Only 2^32 bits (512 MiBytes) are supported
     int16_t   offsetWb;        // Byte offset into Ws, used to load message
     uint64_t  digest[8];      // Holds intermediate/final digest
     uint16_t  Ws[128];
} SHA384_ObjectByteWise;

//*****************************************************************************
//
// Handle to the SHA-384 object
//
//*****************************************************************************
typedef SHA384_ObjectWordWise* SHA384_HandleWordWise;
typedef SHA384_ObjectByteWise* SHA384_HandleByteWise;

//*****************************************************************************
//
// Define Macros
//
//*****************************************************************************
/** SHA384-  NULL input error */
#define SHA384_STATUS_NULL_INPUT       (uint16_t)0x0000
/** SHA384 operation successful */
#define SHA384_STATUS_SUCCESS          (uint16_t)0xABCD
/** SHA384-  length of input too large */
#define SHA384_STATUS_LENGTH_TOO_LARGE (uint16_t)0xBADA
/** SHA384-  input not aligned */
#define SHA384_STATUS_NOT_ALIGNED      (uint16_t)0x0BAD

#define SHA384_GETU32(plaintext) (((uint32_t)(plaintext)[0] << 24U) ^ \
                                  ((uint32_t)(plaintext)[1] << 16U) ^ \
                                  ((uint32_t)(plaintext)[2] <<  8U) ^ \
                                  ((uint32_t)(plaintext)[3]))
#define SHA384_GETU64(plaintext) (((uint64_t)(plaintext)[0] << 56U) ^ \
                                  ((uint64_t)(plaintext)[1] << 48U) ^ \
                                  ((uint64_t)(plaintext)[2] << 40U) ^ \
                                  ((uint64_t)(plaintext)[3] << 32U) ^ \
                                  ((uint64_t)(plaintext)[4] << 24U) ^ \
                                  ((uint64_t)(plaintext)[5] << 16U) ^ \
                                  ((uint64_t)(plaintext)[6] << 8U) ^ \
                                  ((uint64_t)(plaintext)[7]))
#define SHA384_PUTU64(ciphertext, st) \
        { (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 56U) & 0x00FFU); \
          (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 48U) & 0x00FFU); \
          (ciphertext)[2] = (uint16_t)((uint16_t)((st) >> 40U) & 0x00FFU); \
          (ciphertext)[3] = (uint16_t)((uint16_t)((st) >> 32U) & 0x00FFU); \
          (ciphertext)[4] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU); \
          (ciphertext)[5] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU); \
          (ciphertext)[6] = (uint16_t)((uint16_t)((st) >> 8U) & 0x00FFU); \
          (ciphertext)[7] = (uint16_t)((uint16_t)(st) & 0x00FFU); }
#define SHA384_PUTU32(ciphertext, st) \
        { (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU); \
          (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU); \
          (ciphertext)[2] = (uint16_t)((uint16_t)((st) >>  8U) & 0x00FFU); \
          (ciphertext)[3] = (uint16_t)((uint16_t)(st) & 0x00FFU); }

#define SHA384_SHR(x, a)      ((x) >> (a))
#define SHA384_ROTR32(x, n)   (( SHA384_SHR(x, n) ) ^ ( (x) << (32 - (n)) ))
#define SHA384_ROTR64(x, n)   (( SHA384_SHR(x, n) ) ^ ( (x) << (64 - (n)) ))

//*****************************************************************************
//
// SHA384_CH function from NIST FIPS 180-4, Eq 4.8.
// Implementation is refactored for efficiency.
//
//*****************************************************************************
#define SHA384_CH(x, y, z)   (((x) & ((y) ^ (z))) ^ (z))

//*****************************************************************************
//
// SHA384_MAJ function from NIST FIPS 180-4, Eq 4.9.
// Implementation is refactored for efficiency.
//
//*****************************************************************************
#define SHA384_MAJ(x, y, z)  ((((y)^(z)) & (x)) ^ ((y) & (z)))

//*****************************************************************************
//
// Big Sigma 0-512 function from NIST FIPS 180-4, Eq 4.10.
//
//*****************************************************************************
#define SHA384_SIGZ(x)       (SHA384_ROTR64(x, 28) ^ SHA384_ROTR64(x, 34) ^ \
                              SHA384_ROTR64(x, 39))

//*****************************************************************************
//
// Big Sigma 1-512 function from NIST FIPS 180-4, Eq 4.11.
//
//*****************************************************************************
#define SHA384_SIG1(x)       (SHA384_ROTR64(x, 14) ^ SHA384_ROTR64(x, 18) ^ \
                              SHA384_ROTR64(x, 41))

//*****************************************************************************
//
// Little Sigma 0-512 function from NIST FIPS 180-4, Eq 4.12.
//
//*****************************************************************************
#define SHA384_SIGMAZ(x)     (SHA384_ROTR64(x, 1) ^ SHA384_ROTR64(x, 8) ^ \
                              SHA384_SHR(x, 7))

//*****************************************************************************
//
// Little Sigma 1-512 function from NIST FIPS 180-4, Eq 4.13.
//
//*****************************************************************************
#define SHA384_SIGMA1(x)     (SHA384_ROTR64(x, 19) ^ SHA384_ROTR64(x, 61) ^ \
                              SHA384_SHR(x, 6))

//*****************************************************************************
//
//! Perform a complete hash operation when input is supplied as 32-bit words,
//! producing a final digest for the data.
//!   - This function wraps #SHA384_startWordWise(), #SHA384_addDataWordWise(),
//!     and #SHA384_finalizeWordWise().
//!   - There is no need to call #SHA384_startWordWise() prior to calling
//!     this function.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.)
//!
//! \param handle  A 'SHA384_HandleWordWise' handle
//! \param data    32-bit pointer pointing to the starting memory location of
//!                the data to be hashed
//! \param length  Length of the data (in number of bytes) to be hashed.
//!                Note that for word-wise input, length of the data should be
//!                a multiple of 4.
//! \param digest  Output location for the final digest
//!
//! \return #SHA384_STATUS_SUCCESS           The hash operation succeeded.
//!                                          #SHA384_STATUS_LENGTH_TOO_LARGE -
//!                                          The requested length of data to
//!                                          hash is more than the
//!                                          implementation supports.
//!                                          #SHA384_STATUS_NULL_INPUT - One or
//!                                          more of the pointer inputs is NULL.
//!                                          #SHA384_STATUS_NOT_ALIGNED - Length.
//!                                          is not a multiple of 4
//
//*****************************************************************************
uint16_t SHA384_hashWordWise(SHA384_HandleWordWise handle, uint32_t *data,
                             size_t length, uint64_t digest[6]);

//*****************************************************************************
//
//! Perform a complete hash operation when input is supplied byte-wise,
//! producing a final digest for the data.
//!   - This function wraps #SHA384_startByteWise(), #SHA384_addDataByteWise(),
//!     and #SHA384_finalizeByteWise().
//!   - There is no need to call #SHA384_startByteWise() prior to calling
//!     this function.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.)
//!
//! \param handle  A 'SHA384_HandleByteWise' handle
//! \param data    16-bit pointer pointing to the memory location of the
//!                starting byte the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed.
//! \param digest  Output location for the final digest
//!
//! \return #SHA384_STATUS_SUCCESS           The hash operation succeeded.
//! \return #SHA384_STATUS_LENGTH_TOO_LARGE  The requested length of data to
//!                                          hash is more than the
//!                                          implementation supports.
//! \return #SHA384_STATUS_NULL_INPUT        One or more of the pointer inputs
//!                                          is NULL.
//
//*****************************************************************************
uint16_t SHA384_hashByteWise(SHA384_HandleByteWise handle, uint16_t *data,
                             size_t length, uint64_t digest[6]);

//*****************************************************************************
//
//! Initialize a 'SHA384SW_HandleWordWise' handle, preparing for hashing data.
//!
//! \param handle  A 'SHA384_HandleWordWise' handle
//!
//! \return #SHA384_STATUS_SUCCESS           The hash operation succeeded.
//! \return #SHA384_STATUS_NULL_INPUT        One or more of the pointer inputs
//!                                          is NULL.
//
//*****************************************************************************
uint16_t SHA384_startWordWise(SHA384_HandleWordWise handle);

//*****************************************************************************
//
//! Initialize a 'SHA384SW_HandleByteWise' handle, preparing for hashing data.
//!
//! \param handle  A 'SHA384_HandleByteWise' handle
//!
//! \return #SHA384_STATUS_SUCCESS           The hash operation succeeded.
//! \return #SHA384_STATUS_NULL_INPUT        One or more of the pointer inputs
//!                                          is NULL.
//
//*****************************************************************************
uint16_t SHA384_startByteWise(SHA384_HandleByteWise handle);

//*****************************************************************************
//
//! Add data to SHA384 operation when inputs are supplied as 32-bit words
//!   - Adds data to a hash operation. The @c handle must have been
//!     initialized by a call to SHA384_startWordWise first.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.).
//!   - After passing in all data to be hashed, call #SHA384_finalizeWordWise()
//!     to obtain the final digest.
//!
//! \param handle  A 'SHA384_HandleWordWise' handle.
//! \param data    32-bit pointer pointing to the starting memory location of
//!                the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed
//!                Note that for word-wise input, length of the data should
//!                be a multiple of 4.
//!
//! \return #SHA384_STATUS_SUCCESS            The hash operation succeeded.
//! \return #SHA384_STATUS_LENGTH_TOO_LARGE   The requested length of data to
//!                                           hash is more than the
//!                                           implementation supports.
//! \return #SHA384_STATUS_NULL_INPUT         One or more of the pointer inputs
//!                                           is NULL.
//! \return #SHA384_STATUS_NOT_ALIGNED        Length is not a multiple of 4
//
//*****************************************************************************
uint16_t SHA384_addDataWordWise(SHA384_HandleWordWise handle, uint32_t *data,
                                size_t length);

//*****************************************************************************
//
//! Add data to SHA384 operation when inputs are supplied byte-wise
//!   - Adds data to a hash operation. The @c handle must have been
//!     initialized by a call to SHA384_startByteWise first.
//!   - The total length of data that can be hashed by this implementation
//!     is 512MiB (0x20000000 bytes.).
//!   - After passing in all data to be hashed, call #SHA384_finalizeWordWise()
//!     to obtain the final digest.
//!
//! \param handle  A 'SHA384_HandleByteWise' handle.
//! \param data    16-bit pointer pointing to the memory location of the
//!                starting byte the data to be hashed.
//! \param length  Length of the data (in number of bytes) to be hashed
//!
//! \return #SHA384_STATUS_SUCCESS            hash operation succeeded.
//!                                           #SHA384_STATUS_LENGTH_TOO_LARGE -
//!                                           requested length of data to
//!                                           hash is more than supported length.
//!                                           #SHA384_STATUS_NULL_INPUT- One or
//!                                           more of the pointer inputs is NULL
//
//*****************************************************************************
uint16_t SHA384_addDataByteWise(SHA384_HandleByteWise handle, uint16_t *data,
                                size_t length);

//*****************************************************************************
//
//! Finalize the SHA384 operation when input is supplied as 32-bit words,
//! creating the final digest.
//!   - After calling this function, @c handle should not be used again
//!     until it has been reinitialized via a call to #SHA384_startWordWise().
//!
//! \param handle  A 'SHA384_HandleWordWise' handle
//! \param digest  Output location for the final digest
//!
//! \return #SHA384_STATUS_SUCCESS          The hash operation succeeded.
//! \return #SHA384_STATUS_NULL_INPUT       One or more of the pointer inputs
//!                                         is NULL.
//
//*****************************************************************************
uint16_t SHA384_finalizeWordWise(SHA384_HandleWordWise handle,
                                 uint64_t digest[6]);

//*****************************************************************************
//
//! Finalize the SHA384 operation when input is supplied byte-wise,
//! creating the final digest.
//!   - After calling this function, @c handle should not be used again
//!     until it has been reinitialized via a call to #SHA384_startByteWise().
//!
//! \param handle  A 'SHA384_HandleByteWise' handle
//! \param digest  Output location for the final digest
//!
//! \return #SHA384_STATUS_SUCCESS          The hash operation succeeded.
//! \return #SHA384_STATUS_NULL_INPUT       One or more of the pointer inputs
//!                                         is NULL.
//
//*****************************************************************************
uint16_t SHA384_finalizeByteWise(SHA384_HandleByteWise handle,
                                 uint64_t digest[6]);

//*****************************************************************************
//
//! Cancels SHA384 operation by clearing intermediate
//! data stored in the 'SHA384_HandleWordWise' handle.
//!   - The handle will not be ready for a new operation until after
//!     #SHA384_startWordWise() is called on the handle.
//!
//! \param handle  A 'SHA384_HandleWordWise' handle
//!
//
//*****************************************************************************
void SHA384_cancelWordWise(SHA384_HandleWordWise handle);

//*****************************************************************************
//
//! Cancels SHA384 operation by clearing intermediate
//! data stored in the 'SHA384_HandleByteWise' handle.
//!   - The handle will not be ready for a new operation until after
//!     #SHA384_startByteWise() is called on the handle.
//!
//! \param handle  A 'SHA384_HandleByteWise' handle
//!
//
//*****************************************************************************
void SHA384_cancelByteWise(SHA384_HandleByteWise handle);

//*****************************************************************************
//
//! Performs core SHA2-384 algorithm on one 1024 bit block of data when input
//! is supplied as 32-bit words.
//!   - object->digest will contain the updated digest resulting from
//!     hashing the block.
//!
//! \param digest  pre-loaded with previous block's digest (or initial
//!                digest if call is to process first block)
//!                On function return digest will hold the updated digest.
//! \param Ws      loaded with data block, including padding as specified by
//!                the SHA384 standard.
//
//*****************************************************************************
void SHA384_processBlockWordWise(uint64_t digest[8], uint64_t Ws[16]);
extern void _SHA384_processBlockWordWise_casm_C28(uint64_t digest[8], uint64_t Ws[16]);

//*****************************************************************************
//
//! Performs core SHA2-384 algorithm on one 1024 bit block of data when input
//! is supplied byte-wise.
//!   - object->digest will contain the updated digest resulting from
//!     hashing the block.
//!
//! \param digest  pre-loaded with previous block's digest (or initial
//!                digest if call is to process first block)
//!                On function return digest will hold the updated digest.
//! \param Ws      loaded with data block, including padding as specified by
//!                the SHA384 standard.
//
//*****************************************************************************
void SHA384_processBlockByteWise(uint64_t digest[8], uint16_t Ws[128]);

extern void _SHA384_processBlockByteWise_casm_C28(uint64_t digest[8], uint16_t Ws[128]);


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
#endif /* SHA384_H_ */
