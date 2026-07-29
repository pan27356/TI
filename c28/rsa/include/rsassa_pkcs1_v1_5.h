//###########################################################################
//
// FILE:   rsassa_pkcs1_v1_5.h
//
// TITLE:  RSASSA-PKCS header file
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

#ifndef __RSASSA_PKCS1_1V_5__
#define __RSASSA_PKCS1_1V_5__

#include "mpi.h"

//*****************************************************************************
//
// RSA Private Key data structure
//
//*****************************************************************************
typedef mp_int rsa_PrivateKey;

//*****************************************************************************
//
// RSA Public Key data structure
//
//*****************************************************************************
typedef mp_int rsa_PublicKey;

//*****************************************************************************
//
// RSA Modulus data structure
//
//*****************************************************************************
typedef mp_int rsa_Modulus;

//*****************************************************************************
//
// RSA Signature data structure
//
//*****************************************************************************
typedef mp_int rsa_Signature;

//*****************************************************************************
//
// RSA error data type
//
//*****************************************************************************
typedef mp_err rsa_err;

//*****************************************************************************
//
//! Initialize RSA Public Key data structure
//!
//! \param pub_key is the pointer to the rsa_PublicKey data structure
//!
//! \return Returns MP_OKAY if successful, MP_MEM if memory could not be
//!         allocated for the structure.
//
//*****************************************************************************
#define rsa_init_pubkey(pub_key)   mp_init(pub_key)

//*****************************************************************************
//
//! Initialize RSA Private Key data structure
//!
//! \param pvt_key is the pointer to the rsa_PrivateKey data structure
//!
//! \return Returns MP_OKAY if successful, MP_MEM if memory could not be
//!         allocated for the structure.
//
//*****************************************************************************
#define rsa_init_pvtkey(pvt_key)   mp_init(pvt_key)

//*****************************************************************************
//
//! Initialize RSA Modulus data structure
//!
//! \param modulus is the pointer to the rsa_Modulus data structure
//!
//! \return Returns MP_OKAY if successful, MP_MEM if memory could not be
//!         allocated for the structure.
//
//*****************************************************************************
#define rsa_init_modulus(modulus)  mp_init(modulus)

//*****************************************************************************
//
//! Initialize RSA signature data structure
//!
//! \param pub_key is the pointer to the rsa_Signature data structure
//!
//! \return Returns MP_OKAY if successful, MP_MEM if memory could not be
//!         allocated for the structure.
//
//*****************************************************************************
#define rsa_init_signature(sign)    mp_init(sign)

//*****************************************************************************
//
//! Set RSA public key value in the data structure from a hex string
//!
//! \param pub_key is the pointer to the rsa_PublicKey data structure
//! \param pub_key_hex is the public key hex string (without the '0x' prefix)
//!
//! \return Returns MP_OKAY if successful. One of the failure macros
//!         defined in mpi.h depending on the type of failure.
//
//*****************************************************************************
#define rsa_set_pubkey_from_hex(pub_key, pub_key_hex) \
        mp_read_hex(pub_key, pub_key_hex)

//*****************************************************************************
//
//! Set RSA private key value in the data structure from a hex string
//!
//! \param pvt_key is the pointer to the rsa_PrivateKey data structure
//! \param pvt_key_hex is the private key hex string (without the '0x' prefix)
//!
//! \return Returns MP_OKAY if successful. One of the failure macros
//!         defined in mpi.h depending on the type of failure.
//
//*****************************************************************************
#define rsa_set_pvtkey_from_hex(pvt_key, pvt_key_hex) \
        mp_read_hex(pvt_key, pvt_key_hex)

//*****************************************************************************
//
//! Set RSA modulus value in the data structure from a hex string
//!
//! \param modulus is the pointer to the rsa_Modulus data structure
//! \param modulus_hex is the modulus hex string (without the '0x' prefix)
//!
//! \return Returns MP_OKAY if successful. One of the failure macros
//!         defined in mpi.h depending on the type of failure.
//
//*****************************************************************************
#define rsa_set_modulus_from_hex(modulus, modulus_hex ) \
        mp_read_hex(modulus, modulus_hex)

//*****************************************************************************
//
//! Extract RSA signature value to a byte array
//!
//! \param sign is the pointer to the rsa_Signature data structure
//! \param sign_str is the pointer to the string where signature has to be
//!        written
//! \param sign_len is the length of the signature in bytes
//!
//! \return Returns MP_OKAY if successful.
//
//*****************************************************************************
#define rsa_signature_to_mem(sign, sign_str, sign_len ) \
        mp_to_mem(sign, sign_str, sign_len);

//*****************************************************************************
//
//! Function to write data represented in a hex string into the memory bytewise
//!
//! \param hex_str is the hex string (without the '0x' prefix)
//! \param data is the pointer to the memory location where the data will be
//!        written
//!
//! \return Returns 0 if successful
//!                 3 if the hex string is invalid
//
//*****************************************************************************
rsa_err rsa_hex_to_data(unsigned char* hex_str, uint16_t* data);

//*****************************************************************************
//
//! Function to generate a signature of the data using RSASSA-PKCS algorithm
//!
//! \param key_pvt is the pointer to the rsa_PrivateKey data structure holding
//!                the RSA private key value
//! \param modulus is the pointer to the rsa_Modulus data structure holding
//!                the RSA modulus value
//! \param sign is the pointer to the rsa_Signature data structure which
//!                will hold the generated the signature
//! \param hash is the pointer to the byte wise hash digest of the message
//! \param hash_size is the size of the hash based on the SHA encoding type
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
rsa_err rsassa_pkcs1_v1_5_sign(rsa_PrivateKey* key_pvt, rsa_Modulus* modulus,
    rsa_Signature* sign, uint16_t *hash, uint16_t hash_size);

//*****************************************************************************
//
//! Function to verify the signature of a data using RSASSA-PKCS algorithm
//!
//! \param sign is the pointer to the rsa_Signature data structure holding
//!             the signature to be verified
//! \param hash is the pointer to the bytewise hash digest of the message
//! \param hashlen is the length of the hash digest of the message in bytes
//! \param key_pub is the pointer to the rsa_PublicKey data structure holding
//!                the RSA public key value
//! \param modulus is the pointer to the rsa_Modulus data structure holding
//!                the RSA modulus value
//! \param result is the pointer to the verification result
//!        1  - Verification successful
//!        0  - Incorrect signature. Verification failed
//!        -1 - Verification incomplete
//!
//! \return Returns PKCS_STATUS_SUCCESS if successful
//
//*****************************************************************************
rsa_err rsassa_pkcs1_v1_5_verify(rsa_Signature* sign, uint16_t* hash, uint16_t hashlen,
    uint16_t mod_len, rsa_PublicKey* key_pub,
    rsa_Modulus* modulus,
    int16_t* result);


#endif
