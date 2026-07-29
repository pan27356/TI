//###########################################################################
//
// FILE:   emsa_pkcs1_v1_5.c
//
// TITLE:  EMSA-PKCS message encoding and decoding
//
//###########################################################################

#include "emsa_pkcs1_v1_5.h"
#include <stdlib.h>
#include <string.h>

//*****************************************************************************
//
//ASN.1 defines
//
//*****************************************************************************
#define ASN_1_ENCODING              0x20
#define ASN_1_TYPE_BIT_STR          0x03
#define ASN_1_TYPE_OCTET_STR        0x04
#define ASN_1_TYPE_NULL             0x05
#define ASN_1_TYPE_OBJ_ID           0x06
#define ASN_1_TYPE_SEQ              0x10

//*****************************************************************************
//
//SHA256 related data for padding
//
//*****************************************************************************
#define SHA256_DIGEST_SIZE          0x20

//*****************************************************************************
//
//SHA384 related data for padding
//
//*****************************************************************************
#define SHA384_DIGEST_SIZE          0x30

//*****************************************************************************
//
//SHA384 digest size (384 bits = 32 bytes)
//
//*****************************************************************************
#define SHA256_DIGEST_SIZE          0x20

//*****************************************************************************
//
//SHA256 with ASN.1 padding
//
//*****************************************************************************
const uint16_t SHA256_ASN_1_PADDING[ASN_1_PAD_SIZE]  = \
{                           \
    0x00, 0x01,             \
    0xFF, 0xFF, 0xFF, 0xFF, \
    0xFF, 0xFF, 0xFF, 0xFF, \
    0x00,                   \
    0x30, 0x31, 0x30, 0x0D, \
    0x06, 0x09, 0x60, 0x86, \
    0x48, 0x01, 0x65, 0x03, \
    0x04, 0x02, 0x01, 0x05, \
    0x00, 0x04, 0x20
};

//*****************************************************************************
//
//SHA384 with ASN.1 padding
//
//*****************************************************************************
const uint16_t SHA384_ASN_1_PADDING[ASN_1_PAD_SIZE]  = \
{                           \
    0x00, 0x01,             \
    0xFF, 0xFF, 0xFF, 0xFF, \
    0xFF, 0xFF, 0xFF, 0xFF, \
    0x00,                   \
    0x30, 0x41, 0x30, 0x0D, \
    0x06, 0x09, 0x60, 0x86, \
    0x48, 0x01, 0x65, 0x03, \
    0x04, 0x02, 0x02, 0x05, \
    0x00, 0x04, 0x30
};

//*****************************************************************************
//
// EMSA-PKCS1 encode message
//
//*****************************************************************************
int emsa_pkcs1_v1_5_encode(uint16_t* emsa_out, uint16_t* hash, uint16_t hash_size)
{
    const uint16_t* shaPadding = NULL;

    if(emsa_out == NULL)
    {
        return PKCS_STATUS_FAILURE_MEM;
    }

    if(hash_size == SHA256_HASH_SIZE)
    {
        shaPadding = SHA256_ASN_1_PADDING;
    }
    else if(hash_size == SHA384_HASH_SIZE)
    {
        shaPadding = SHA384_ASN_1_PADDING;
    }

    // Pad the sequence as EM = 0x00 || 0x01 || PS || 0x00 || T
    memcpy(emsa_out, shaPadding, ASN_1_PAD_SIZE);

    //Append the hash value
    memcpy(emsa_out + ASN_1_PAD_SIZE, hash, hash_size);

    return PKCS_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Function to verify the signature of a data using RSASSA-PKCS algorithm
//
//*****************************************************************************
int emsa_pkcs1_v1_5_decode(uint16_t* EM_Str, uint16_t *hash, uint16_t hash_size, int16_t* result)
{
    int err = 0;
    const uint16_t* shaPadding = NULL;

    if ((EM_Str == NULL) || (result == NULL))
    {
        *result = -1;
        return PKCS_STATUS_FAILURE_NULL;
    }

    *result = -1;

    //Check signature length is more than the length of 0x00 || 0x01 || PS || 0x00 || T
    if(hash_size == SHA256_HASH_SIZE)
    {
        shaPadding = SHA256_ASN_1_PADDING;
    }
    else if(hash_size == SHA384_HASH_SIZE)
    {
        shaPadding = SHA384_ASN_1_PADDING;
    }


    //
    // Check Padding
    //
    if(memcmp(EM_Str, shaPadding, ASN_1_PAD_SIZE) != 0)
    {
        *result = 0;
        return PKCS_STATUS_FAILURE;
    }

    // Compare expected hash vs computed hash
    if(memcmp(EM_Str + ASN_1_PAD_SIZE, hash, hash_size) != 0)
    {
        *result = 0;
        return PKCS_STATUS_FAILURE;
    }

    *result = 1;

    return err;
}
//
// End of file
//
