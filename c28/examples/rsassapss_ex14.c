//###########################################################################
//
// FILE:   rsassapss_ex14.c
//
// TITLE:  RSASSA-PSS Example
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

#include "emsa_pss.h"
#include "rsassa_pss.h"
#include "sha256.h"
#include "yarrow.h"
#include <time.h>
#include "driverlib.h"
#include "device.h"
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE       32

void runTest(void);

//*****************************************************************************
//
// SHA-256 object for hashing the message
//
//*****************************************************************************
SHA256_ObjectByteWise md;

//*****************************************************************************
//
// RSA-SSA PSS Parameters
//
//*****************************************************************************
#ifdef RSA_2048
unsigned char n[] = "c5062b58d8539c765e1e5dbaf14cf75dd56c2e13105fecfd1a930bbb5948ff328f126abe779359ca59bca752c308d281573bc6178b6c0fef7dc445e4f826430437b9f9d790581de5749c2cb9cb26d42b2fee15b6b26f09c99670336423b86bc5bec71113157be2d944d7ff3eebffb28413143ea36755db0ae62ff5b724eecb3d316b6bac67e89cacd8171937e2ab19bd353a89acea8c36f81c89a620d5fd2effea896601c7f9daca7f033f635a3a943331d1b1b4f5288790b53af352f1121ca1bef205f40dc012c412b40bdd27585b946466d75f7ee0a7f9d549b4bece6f43ac3ee65fe7fd37123359d9f1a850ad450aaf5c94eb11dea3fc0fc6e9856b1805ef";
unsigned char e[] = "86c94f";
unsigned char d[] = "49e5786bb4d332f94586327bde088875379b75d128488f08e574ab4715302a87eea52d4c4a23d8b97af7944804337c5f55e16ba9ffafc0c9fd9b88eca443f39b7967170ddb8ce7ddb93c6087c8066c4a95538a441b9dc80dc9f7810054fd1e5c9d0250c978bb2d748abe1e9465d71a8165d3126dce5db2adacc003e9062ba37a54b63e5f49a4eafebd7e4bf5b0a796c2b3a950fa09c798d3fa3e86c4b62c33ba9365eda054e5fe74a41f21b595026acf1093c90a8c71722f91af1ed29a41a2449a320fc7ba3120e3e8c3e4240c04925cc698ecd66c7c906bdf240adad972b4dff4869d400b5d13e33eeba38e075e872b0ed3e91cc9c283867a4ffc3901d2069f";
unsigned char msg[] = "dfc22604b95d15328059745c6c98eb9dfb347cf9f170aff19deeec555f22285a6706c4ecbf0fb1458c60d9bf913fbae6f4c554d245d946b4bc5f34aec2ac6be8b33dc8e0e3a9d601dfd53678f5674443f67df78a3a9e0933e5f158b169ac8d1c4cd0fb872c14ca8e001e542ea0f9cfda88c42dcad8a74097a00c22055b0bd41f";
#endif

#ifdef RSA_3072
unsigned char n[] = "a7a1882a7fb896786034d07fb1b9f6327c27bdd7ce6fe39c285ae3b6c34259adc0dc4f7b9c7dec3ca4a20d3407339eedd7a12a421da18f5954673cac2ff059156ecc73c6861ec761e6a0f2a5a033a6768c6a42d8b459e1b4932349e84efd92df59b45935f3d0e30817c66201aa99d07ae36c5d74f408d69cc08f044151ff4960e531360cb19077833adf7bce77ecfaa133c0ccc63c93b856814569e0b9884ee554061b9a20ab46c38263c094dae791aa61a17f8d16f0e85b7e5ce3b067ece89e20bc4e8f1ae814b276d234e04f4e766f501da74ea7e3817c24ea35d016676cece652b823b051625573ca92757fc720d254ecf1dcbbfd21d98307561ecaab545480c7c52ad7e9fa6b597f5fe550559c2fe923205ac1761a99737ca02d7b19822e008a8969349c87fb874c81620e38f613c8521f0381fe5ba55b74827dad3e1cf2aa29c6933629f2b286ad11be88fa6436e7e3f64a75e3595290dc0d1cd5eee7aaac54959cc53bd5a934a365e72dd81a2bd4fb9a67821bffedf2ef2bd94913de8b";
unsigned char e[] = "1415a7";
unsigned char d[] = "073a5fc4cd642f6113dffc4f84035cee3a2b8acc549703751a1d6a5eaa13487229a58ef7d7a522bb9f4f25510f1aa0f74c6a8fc8a5c5be8b91a674ede50e92f7e34a90a3c9da999fffb1d695e4588f451256c163484c151350cb9c7825a7d910845ee5cf826fecf9a7c0fbbbba22bb4a531c131d2e7761ba898f002ebef8ab87218511f81d3266e1ec07a7ca8622514c6dfdc86c67679a2c8f5f031de9a0c22b5a88060b46ee0c64d3b9af3c0a379bcd9c6a1b51cf6480456d3fd6def94cd2a6c171dd3f010e3c9d662bc857208248c94ebcb9fd997b9ff4a7e5fd95558569906525e741d78344f6f6cfdbd59d4faa52ee3fa964fb7cccb2d6be1935d211fe1498217716273939a946081fd8509913fd47747c5c2f03efd4d6fc9c6fcfd8402e9f40a0a5b3de3ca2b3c0fac9456938faa6cf2c20e3912e5981c9876d8ca1ff29b87a15eeae0ccce3f8a8f1e405091c083b98bcc5fe0d0deaae33c67c0394437f0eccb385b7efb17aeebba8afaecca30a2f63eac8f0ac8f1eacad85bbcaf3960b";
unsigned char msg[] = "3b8a68da11b61b5fee1c2ca00a6aa35bbfdbdd42855b284320ec8d0c1848edcf6ac850427d8479eb57bcbe9a11771637886974bd561a5387014592cb717e8364a8183fd4ad463c89c980215ff629d867956ee5e75f71f7a19ea7bd589d7efb915d44dd9789448bc1ac32fdf7a2c911734db2dbc589a83c1a61dab6bd83907ede";
#endif

//*****************************************************************************
//
// Data structures to work with
//
//*****************************************************************************
rsa_PublicKey key_pub;
rsa_PrivateKey key_pvt;
rsa_Modulus modulus;
rsa_Signature sign;
int16_t verified = -1;

//*****************************************************************************
//
// Main function
//
//*****************************************************************************
void main(void)
{
    //
    // Device initialize
    //
    Device_init();

    uint16_t i, j;

    //
    // Yarrow PRNG handler to generate random salt
    //
    yarrow_prng prng;

    //
    // Initialize RSASSA-PSS parameters
    //
    rsa_init_pvtkey(&key_pvt);
    rsa_init_pubkey(&key_pub);
    rsa_init_modulus(&modulus);

    //
    // Set RSASSA-PSS parameters with values from hex strings
    //
    rsa_set_pvtkey_from_hex(&key_pvt, d);
    rsa_set_pubkey_from_hex(&key_pub, e);
    rsa_set_modulus_from_hex(&modulus, n);

    //
    // Place the message for which the signature has to be generated
    // in memory
    //
    uint16_t datalen = strlen((char *)msg)/2;
    uint16_t *msg_data = (uint16_t *)malloc(datalen);
    rsa_hex_to_data(msg, msg_data);

    //
    // Hashing the message
    //
    uint32_t digest[8];
    SHA256_hashByteWise(&md, msg_data, datalen, digest);
    uint16_t hash[40];
    for (i = 0, j = 0; i < 8 && j < 32; i++)
    {
        hash[j++] = (digest[i] >> 24) & 255;
        hash[j++] = (digest[i] >> 16) & 255;
        hash[j++] = (digest[i] >> 8) & 255;
        hash[j++] = (digest[i]) & 255;
    }

    //
    // Free the memory used up for holding the message. It is not needed anymore
    //
    free(msg_data);

    //
    // Initialize the Yarrow PRNG handler
    //
    uc nounce[16] = {0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
                     0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};
    yarrow_init_with_nounce(&prng, nounce);
    yarrow_add_entropy("abcd", 4U, &prng);
    yarrow_ready(&prng);

    //
    // Generate the signature
    //
    int mod_len = strlen((char *)n)*4;
    int saltlen = 20; /* Desired random salt length */
    rsassa_pss_sign(hash, HASH_SIZE, saltlen, &key_pvt, &modulus, mod_len, &prng, &sign);

    //
    // Extract the generated signature into a byte string
    //
    uint16_t sign_len = strlen((char *)n)/2;
    uint16_t *sign_str = (uint16_t *)malloc(sign_len);
    rsa_signature_to_mem(&sign, sign_str, sign_len);

    //
    //
    // Verify the generated signature
    // if verified == 1,  then successful
    // if verified == 0,  then signature incorrect
    // if verified == -1, then verification incomplete
    //
    rsassa_pss_verify(&sign, hash, HASH_SIZE, saltlen, &key_pub, &modulus, mod_len, &verified);

    while(1);
}
//
// End of file
//
