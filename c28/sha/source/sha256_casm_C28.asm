;;//*****************************************************************************
;;// Title:   CASM Version Of Functions:
;;//          void SHA256_processBlockByteWise(uint32_t digest[8],  unsigned char Ws[64])
;;//          void SHA256_processBlockWordWise(uint32_t digest[8],  uint32_t Ws[16])
;;//
;;// Call:    void SHA256_processBlockByteWise_casm_C28(uint32_t digest[8],  unsigned char Ws[64])
;;//          void SHA256_processBlockWordWise_casm_C28(uint32_t digest[8],  uint32_t Ws[16])
;;//
;;// Version: 1
;;//
;;// Cycles:  Byte Wise:   13,798 (running from RAM)
;;//          Word Wise:   12,098 (running from RAM)
;;//          SHA256_K[64] const table located in RAM
;;//
;// $TI Release: C2000 AES Software v2.00.00.00 $
;// $Release Date: Tue Oct 29 00:56:51 IST 2024 $
;// $Copyright:
;// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;;//*****************************************************************************

temp_var	.usect	".bss",32,32,6
			.asg	"(temp_var+0)",temp3

			.asg	"(temp_var+2)",temp4

			.asg	"(temp_var+4)",temp5

			.asg	"(temp_var+6)",temp6

			.asg	"(temp_var+8)",temp7

			.asg	"(temp_var+10)",temp8

			.asg	"(temp_var+12)",temp9

			.asg	"(temp_var+14)",temp10
			.asg	"(temp_var+14)",temp10_w0
			.asg	"(temp_var+15)",temp10_w1

			.asg	"(temp_var+16)",temp11
			.asg	"(temp_var+16)",temp11_w0
			.asg	"(temp_var+17)",temp11_w1

			.asg	"(temp_var+18)",temp12
			.asg	"(temp_var+18)",temp12_w0
			.asg	"(temp_var+19)",temp12_w1

			.asg	"(temp_var+20)",save_XAR0
			.asg	"(temp_var+22)",save_XAR1
			.asg	"(temp_var+24)",save_XAR2
			.asg	"(temp_var+26)",save_XAR3
			.asg	"(temp_var+28)",save_XAR6
			.asg	"(temp_var+30)",save_XAR7

SP_size			.set	30
SP_a_offset		.set	30
		.asg	"-SP[30]",SP_a
		.asg	"-SP[30]",SP_a_w0
		.asg	"-SP[29]",SP_a_w1

		.asg	"-SP[28]",SP_b
		.asg	"-SP[28]",SP_b_w0
		.asg	"-SP[27]",SP_b_w1

		.asg	"-SP[26]",SP_c
		.asg	"-SP[26]",SP_c_w0
		.asg	"-SP[25]",SP_c_w1

		.asg	"-SP[24]",SP_d
		.asg	"-SP[24]",SP_d_w0
		.asg	"-SP[23]",SP_d_w1

		.asg	"-SP[22]",SP_e
		.asg	"-SP[22]",SP_e_w0
		.asg	"-SP[21]",SP_e_w1

		.asg	"-SP[20]",SP_f
		.asg	"-SP[20]",SP_f_w0
		.asg	"-SP[19]",SP_f_w1

		.asg	"-SP[18]",SP_g
		.asg	"-SP[18]",SP_g_w0
		.asg	"-SP[17]",SP_g_w1

		.asg	"-SP[16]",SP_h
		.asg	"-SP[16]",SP_h_w0
		.asg	"-SP[15]",SP_h_w1

		.asg	"-SP[14]",SP_temp2

		.asg	"-SP[12]",SP_temp1

SP_wt_offset	.set	10
		.asg	"-SP[10]",SP_wt

		.asg	"-SP[8]",SP_s

		.asg	"-SP[7]",SP_s0

		.asg	"-SP[6]",SP_XAR4
		.asg	"-SP[6]",SP_digest

		.asg	"-SP[4]",SP_XAR5
		.asg	"-SP[4]",SP_Ws

		.asg	"-SP[2]",SP_temp13

;;=============================================================================
;;#define SHA256_GETU32(plaintext) (((uint32_t)(plaintext)[0] << 24U) ^ \
;;                                  ((uint32_t)(plaintext)[1] << 16U) ^ \
;;                                  ((uint32_t)(plaintext)[2] <<  8U) ^ \
;;                                  ((uint32_t)(plaintext)[3]))
;;
M_SHA256_GETU32	.macro		pointer, dest
		MOVB	AH.LSB,*+pointer[2]		; Ws[((s0 + AH) & 0x3F) + 1] << 16U
		MOVB	AH.MSB,*+pointer[0]		; Ws[((s0 + AH) & 0x3F) + 0] << 24U
		MOVB	AL.LSB,*+pointer[6]		; Ws[((s0 + AH) & 0x3F) + 3] << 0U
		MOVB	AL.MSB,*+pointer[4]		; Ws[((s0 + AH) & 0x3F) + 2] << 8U
		MOVL	dest,ACC
		.endm

;;//*****************************************************************************
;;//
;;// SHA-256 process a block of data
;;// Input message : Byte-wise
;;//
;;//*****************************************************************************
;;void SHA256_processBlockByteWise(uint32_t digest[8], unsigned char Ws[64])
;;{
;;    uint32_t wt;             // Wt from standard
;;    int16_t s, s0;               // s is the message schedule index
;;    uint32_t temp1;          // T1 from standard
;;    uint32_t temp2;          // T2 from standard
;;
;;    //
;;    // Initialize working variables
;;    //
;;    uint32_t a = digest[0];
;;    uint32_t b = digest[1];
;;    uint32_t c = digest[2];
;;    uint32_t d = digest[3];
;;    uint32_t e = digest[4];
;;    uint32_t f = digest[5];
;;    uint32_t g = digest[6];
;;    uint32_t h = digest[7];
;;
;;    //
;;    // Perform 64 rounds of compression function
;;    //
;;    for(s = 0; s < 64; s++)
;;    {
;;        s0 = s << 2;
;;        if(s0 >= 64)
;;        {
;;            wt = SHA256_SIGMA1(SHA256_GETU32(&Ws[(s0-8) & 0x3F])) +
;;                 SHA256_GETU32(&Ws[(s0-28) & 0x3F]) +
;;                 SHA256_SIGMAZ(SHA256_GETU32(&Ws[(s0-60) & 0x3F])) +
;;                 SHA256_GETU32(&Ws[(s0-64) & 0x3F]);
;;
;;            SHA256_PUTU32(&Ws[s0 & 0x3F], wt);
;;        }
;;        else
;;        {
;;            wt = SHA256_GETU32(&Ws[s0]);
;;        }
;;
;;        temp1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + SHA256_K[s] + wt;
;;        temp2 = SHA256_SIGZ(a) + SHA256_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;    }
;;
;;    //
;;    // Intermediate digest value
;;    //
;;    digest[0] += a;
;;    digest[1] += b;
;;    digest[2] += c;
;;    digest[3] += d;
;;    digest[4] += e;
;;    digest[5] += f;
;;    digest[6] += g;
;;    digest[7] += h;
;;}

;;void SHA256_processBlockByteWise(uint32_t digest[8], unsigned char Ws[64])
;;{
;;    uint32_t wt;             // Wt from standard
;;    int16_t s, s0;               // s is the message schedule index
;;    uint32_t temp1;          // T1 from standard
;;    uint32_t temp2;          // T2 from standard
;;
;; On Entry:
;;    XAR4 => digest[0]  uint32_t
;;    XAR5 => Ws[0]      uint16_t
;;
;;		.sect		.text
		.sect		".TI.ramfunc"  ; Call this line to execute from RAM
		.global		_SHA256_processBlockByteWise_casm_C28
_SHA256_processBlockByteWise_casm_C28:
		MOVW	DP,#temp_var
		ADDB	SP,#SP_size
		MOVL	*SP_XAR4,XAR4
		MOVL	*SP_XAR5,XAR5
		MOVL	@save_XAR0,XAR0
		MOVL	@save_XAR1,XAR1
		MOVL	@save_XAR2,XAR2
		MOVL	@save_XAR3,XAR3
		MOVL	@save_XAR6,XAR6
		MOVL	@save_XAR7,XAR7

;;    //
;;    // Initialize working variables
;;    //
;;    uint32_t a = digest[0];
;;    uint32_t b = digest[1];
;;    uint32_t c = digest[2];
;;    uint32_t d = digest[3];
;;    uint32_t e = digest[4];
;;    uint32_t f = digest[5];
;;    uint32_t g = digest[6];
;;    uint32_t h = digest[7];
		MOVL	XAR7,*SP_digest		; XAR7 => digest[0]
		MOVZ	AR6,@SP
		SUBB	XAR6,#SP_a_offset	; XAR6 => a
		MOVL	ACC,*XAR7++			; uint32_t a = digest[0];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t b = digest[1];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t c = digest[2];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t d = digest[3];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t e = digest[4];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t f = digest[5];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t g = digest[6];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t h = digest[7];
		MOVL	*XAR6++,ACC

;;    //
;;    // Perform 64 rounds of compression function
;;    //
;;    for(s = 0; s < 64; s++)
;;    {
;;        s0 = s << 2;
;;        if(s0 >= 64)
;;        {
;; // SHA256_CALC_PART1:
;;            wt = SHA256_SIGMA1(SHA256_GETU32(&Ws[(s0-8) & 0x3F])) +
;;                 SHA256_GETU32(&Ws[(s0-28) & 0x3F]) +
;;                 SHA256_SIGMAZ(SHA256_GETU32(&Ws[(s0-60) & 0x3F])) +
;;                 SHA256_GETU32(&Ws[(s0-64) & 0x3F]);
;;
;;            SHA256_PUTU32(&Ws[s0 & 0x3F], wt);
;;        }
;;        else
;;        {
;; // SHA256_CALC_PART2:
;;            wt = SHA256_GETU32(&Ws[s0]);
;;        }
;;
;; // SHA256_CALC_PART3:
;;        temp1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + SHA256_K[s] + wt;
;;        temp2 = SHA256_SIGZ(a) + SHA256_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;    }

		MOVB	AL,#0
$10:
		MOV		*SP_s,AL			; s  = AL
		LSL		AL,#2				; AL = s << 2
		MOV		*SP_s0,AL			; s0 = s << 2
		CMPB	AL,#64				; if(s0 >= 64)?
		B		$20,LT

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART1:
;;-----------------------------------------------------------------------------
;; wt = XAR6      = SHA256_SIGMA1(temp3 = SHA256_GETU32(&Ws[(s0-8) & 0x3F])) +
;;      temp5     = SHA256_GETU32(&Ws[(s0-28) & 0x3F]) +
;;      XAR2      = SHA256_SIGMAZ(temp6 = SHA256_GETU32(&Ws[(s0-60) & 0x3F])) +
;;      temp8     = SHA256_GETU32(&Ws[(s0-64) & 0x3F]);
;;
;; temp3 = SHA256_GETU32(&Ws[(s0-8) & 0x3F])
		MOVU	ACC,*SP_s0
		SUBB	ACC,#8
		AND		ACC,#0x003F
		ADDL	ACC,*SP_Ws
		MOVL	XAR0,@ACC

;; temp5 = SHA256_GETU32(&Ws[(s0-28) & 0x3F])
		MOVU	ACC,*SP_s0
		SUBB	ACC,#28
		AND		ACC,#0x003F
		ADDL	ACC,*SP_Ws
		MOVL	XAR1,@ACC

;; temp6 = SHA256_GETU32(&Ws[(s0-60) & 0x3F])
		MOVU	ACC,*SP_s0
		SUBB	ACC,#60
		AND		ACC,#0x003F
		ADDL	ACC,*SP_Ws
		MOVL	XAR2,@ACC

;; temp8 = SHA256_GETU32(&Ws[(s0-64) & 0x3F])
		MOVU	ACC,*SP_s0
		SUBB	ACC,#64
		AND		ACC,#0x003F
		ADDL	ACC,*SP_Ws
		MOVL	XAR3,@ACC

		M_SHA256_GETU32		XAR0, @temp3

		M_SHA256_GETU32		XAR1, @temp5

		M_SHA256_GETU32		XAR2, @temp6

		M_SHA256_GETU32		XAR3, @temp8

;; XAR6 = SHA256_SIGMA1(temp3 = SHA256_GETU32(&Ws[(s0-8) & 0x3F]))
;;
;; x = temp3
;; #define SHA256_SIGMA1(x)     (temp10 = XAR0 = SHA256_ROTR32(x, 17) ^ temp11 = XAR2 = SHA256_ROTR32(x, 19) ^ temp12 = SHA256_SHR(x, 10))
;;
		MOVL	ACC,@temp3				; ACC = temp3
		LSR64	ACC:P,#10
		MOVL	@temp12,ACC				; temp12 = SHA256_SHR(x, 10)
		LSR64	ACC:P,#(17-10)
		MOVL	XAR0,@ACC				; XAR0 = x >> 17
		LSR64	ACC:P,#(19-17)
		MOVL	XAR2,@ACC				; XAR2 = x >> 19
		ZAPA
		MOVL	ACC,@temp3				; ACC = temp3
		LSL64	ACC:P,#(32-19)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 19
		LSL64	ACC:P,#(19-17)			; ACC    = x << 32 - 17
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 17)
		MOVL	ACC,@temp11
		ADDL	ACC,@XAR2				; ACC    = SHA256_ROTR32(x, 19)
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	XAR6,@ACC				; XAR6 = SHA256_SIGMA1(temp3 = SHA256_GETU32(&Ws[(s0-8) & 0x3F]))

;; XAR2 = SHA256_SIGMAZ(temp6 = SHA256_GETU32(&Ws[(s0-60) & 0x3F]))
;;
;; x = temp6
;; #define SHA256_SIGMAZ(x)     (temp10 = XAR0 = SHA256_ROTR32(x, 7) ^ temp11 = XAR2 = SHA256_ROTR32(x, 18) ^ temp12 = SHA256_SHR(x, 3))
;;
		MOVL	ACC,@temp6				; ACC = temp6
		LSR64	ACC:P,#3
		MOVL	@temp12,ACC				; temp12 = SHA256_SHR(x, 3)
		LSR64	ACC:P,#(7-3)
		MOVL	@XAR0,ACC				; XAR0   = x >> 7
		LSR64	ACC:P,#(18-7)
		MOVL	XAR2,@ACC				; XAR2   = x >> 18
		ZAPA
		MOVL	ACC,@temp6				; ACC = temp6
		LSL64	ACC:P,#(32-18)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 18
		LSL64	ACC:P,#(18-7)				; ACC    = x << 32 - 7
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 7)
		MOVL	ACC,@temp11
		ADDL	ACC,@XAR2				; ACC    = SHA256_ROTR32(x, 18)
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	@XAR2,ACC				; XAR2 = SHA256_SIGMAZ(temp6 = SHA256_GETU32(&Ws[(s0-60) & 0x3F]))

;; wt = XAR6 + temp5 + XAR2 + temp8
		MOVL	P,@XAR6
		ADDUL	P,@temp5
		ADDUL	P,@XAR2
		ADDUL	P,@temp8
		MOVL	*SP_wt,P

;; #define SHA256_PUTU32(ciphertext, st) \
;;        { (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU); \
;;          (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU); \
;;          (ciphertext)[2] = (uint16_t)((uint16_t)((st) >>  8U) & 0x00FFU); \
;;          (ciphertext)[3] = (uint16_t)((uint16_t)(st) & 0x00FFU); }
;;
;; SHA256_PUTU32(&Ws[s0 & 0x3F], wt);
		MOVZ	AR0,@SP					; XAR0 => SP top of stack
		MOVU	ACC,*SP_s0
		AND		ACC,#0x003F
		ADDL	ACC,*SP_Ws
		MOVL	XAR1,@ACC				; XAR1 = &Ws[s0 & 0x3F]
		SUBB	XAR0,#SP_wt_offset		; XAR0 => &wt on stack
		NOP
		NOP
		MOVB	AL.LSB,*+XAR0[3]		; (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU)
		MOV		*XAR1++,AL
		MOVB	AL.LSB,*+XAR0[2]		; (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU)
		MOV		*XAR1++,AL
		MOVB	AL.LSB,*+XAR0[1]		; (ciphertext)[2] = (uint16_t)((uint16_t)((st) >> 8U) & 0x00FFU)
		MOV		*XAR1++,AL
		MOVB	AL.LSB,*+XAR0[0]		; (ciphertext)[3] = (uint16_t)((uint16_t)(st) & 0x00FFU)
		MOV		*XAR1,AL

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART1: end
;;-----------------------------------------------------------------------------

		B		$30,UNC
$20:

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART2:
;;-----------------------------------------------------------------------------
;; wt = SHA256_GETU32(&Ws[s0])
;;-----------------------------------------------------------------------------
		MOVU	ACC,*SP_s0
		ADDL	ACC,*SP_Ws
		MOVL	XAR0,@ACC
		M_SHA256_GETU32		XAR0,*SP_wt

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART2: end
;;-----------------------------------------------------------------------------

$30:

;;=============================================================================
;; // SHA256_CALC_PART3:
;;
;;        temp1 = h + temp13 = SHA256_SIG1(e) + temp4 = SHA256_CH(e, f, g) + temp5 = SHA256_K[s] + wt;
;;        temp2 = ACC = SHA256_SIGZ(a) + temp7 = SHA256_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;
;;-----------------------------------------------------------------------------
;;
;; #define SHA256_SIG1(x)       (temp10 = XAR0 = SHA256_ROTR32(x, 6) ^ temp11 = XAR2 = SHA256_ROTR32(x, 11) ^ temp12 = XAR6 = SHA256_ROTR32(x, 25))
;;
;; x = e
;; temp13 = SHA256_SIG1(e)
		MOVL	ACC,*SP_e				; ACC = e
		LSR64	ACC:P,#6
		MOVL	XAR0,@ACC				; XAR0 = x >> 6
		LSR64	ACC:P,#(11-6)
		MOVL	XAR2,@ACC				; XAR2 = x >> 11
		LSR64	ACC:P,#(25-11)
		MOVL	XAR6,@ACC				; XAR6 = x >> 25
		ZAPA
		MOVL	ACC,*SP_e				; ACC = e
		LSL64	ACC:P,#(32-25)
		MOVL	@temp12,ACC				; temp12 = x << 32 - 25
		LSL64	ACC:P,#(25-11)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 11
		LSL64	ACC:P,#(11-6)			; ACC    = x << 32 - 6
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 6)
		MOVL	ACC,@XAR2
		ADDL	ACC,@temp11
		MOVL	@temp11,ACC				; temp11 = SHA256_ROTR32(x, 11)
		MOVL	ACC,@XAR6
		ADDL	ACC,@temp12				; ACC    = SHA256_ROTR32(x, 25)
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	*SP_temp13,ACC			; temp13 = SHA256_SIG1(e)

		.global	SHA256_K
		MOV		AL,*SP_s
		LSL		AL,#1
		MOVZ	AR0,@AL
		MOVL	XAR1,#SHA256_K			; XAR1 = &SHA256_K[s]

;; #define SHA256_CH(x, y, z)   (((x) & ((y) ^ (z))) ^ (z))
;;
;; temp4 = SHA256_CH(e, f, g)
;;
;; temp4 = ((f ^ g) & e) ^ g
		MOVL	ACC,*SP_f
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		AND		AL,*SP_e_w0
		AND		AH,*SP_e_w1
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		MOVL	@temp4,ACC

;; temp5 = SHA256_K[s]
		MOVL	ACC,*+XAR1[AR0]
		MOVL	@temp5,ACC

;; #define SHA256_MAJ(x, y, z)  ((((y)^(z)) & (x)) ^ ((y) & (z)))
;;
;; temp7 = SHA256_MAJ(a, b, c)
;;
;; temp7 = ((b ^ c) & a) ^ (b & c)
		MOVL	ACC,*SP_b
		XOR		AL,*SP_c_w0
		XOR		AH,*SP_c_w1
		AND		AL,*SP_a_w0
		AND		AH,*SP_a_w1
		MOVL	P,@ACC
		MOVL	ACC,*SP_b
		AND		AL,*SP_c_w0
		AND		AH,*SP_c_w1
		XOR		AL,@PL
		XOR		AH,@PH
		MOVL	@temp7,ACC

;; #define SHA256_SIGZ(x)       (temp10 = XAR0 = SHA256_ROTR32(x, 2) ^ temp11 = XAR2 = SHA256_ROTR32(x, 13) ^ temp12 = XAR6 = SHA256_ROTR32(x, 22))
;;
;; x = a
;; ACC = SHA256_SIGZ(a)
		MOVL	ACC,*SP_a				; ACC = a
		LSR64	ACC:P,#2
		MOVL	XAR0,@ACC				; XAR0 = x >> 2
		LSR64	ACC:P,#(13-2)
		MOVL	XAR2,@ACC				; XAR2 = x >> 13
		LSR64	ACC:P,#(22-13)
		MOVL	XAR6,@ACC				; XAR6 = x >> 22
		ZAPA
		MOVL	ACC,*SP_a				; ACC = a
		LSL64	ACC:P,#(32-22)
		MOVL	@temp12,ACC				; temp12 = x << 32 - 22
		LSL64	ACC:P,#(22-13)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 13
		LSL64	ACC:P,#(13-2)				; ACC    = x << 32 - 2
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 2)
		MOVL	ACC,@XAR2
		ADDL	ACC,@temp11
		MOVL	@temp11,ACC				; temp11 = SHA256_ROTR32(x, 13)
		MOVL	ACC,@XAR6
		ADDL	ACC,@temp12				; ACC    = SHA256_ROTR32(x, 22)
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0			; ACC    = SHA256_SIGZ(a)

;; temp2 = ACC = SHA256_SIGZ(a) + temp7 = SHA256_MAJ(a, b, c);
;;
;; XAR2 = temp2 = ACC + temp7
		ADDL	ACC,@temp7
		MOVL	XAR2,@ACC

;; temp1 = h + temp13 = SHA256_SIG1(e) + temp4 = SHA256_CH(e, f, g) + temp5 = SHA256_K[s] + wt;
;;
;; temp1 = h + temp13 = SHA384_SIG1(e) + temp4 = SHA384_CH(e, f, g) + temp5 = SHA384_K[s] + wt;
;;
;; XAR0 = temp1 = h + temp13 + temp4 + temp5 + wt
		MOVL	ACC,@temp4
		ADDL	ACC,@temp5
		ADDL	ACC,*SP_h
		ADDL	ACC,*SP_temp13
		ADDL	ACC,*SP_wt
		MOVL	XAR0,@ACC

;; h = g;
;; g = f;
;; f = e;
;; e = d + temp1;
;; d = c;
;; c = b;
;; b = a;
;; a = temp1 + temp2;
		MOVL	ACC,*SP_g
		MOVL	*SP_h,ACC				; h = g

		MOVL	ACC,*SP_f
		MOVL	*SP_g,ACC				; g = f

		MOVL	ACC,*SP_e
		MOVL	*SP_f,ACC				; f = e

		MOVL	ACC,@XAR0
		ADDL	ACC,*SP_d
		MOVL	*SP_e,ACC				; e = d + temp1

		MOVL	ACC,*SP_c
		MOVL	*SP_d,ACC				; d = c

		MOVL	ACC,*SP_b
		MOVL	*SP_c,ACC				; c = b

		MOVL	ACC,*SP_a
		MOVL	*SP_b,ACC				; b = a

		MOVL	ACC,@XAR0
		ADDL	ACC,@XAR2
		MOVL	*SP_a,ACC				; a = temp1 + temp2

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART3: end
;;-----------------------------------------------------------------------------

		MOVU	ACC,*SP_s			; AL = s, AH = 0
		ADD		AL,#1				; AL = s++
		CMPB	AL,#64				; if(s < 64)?
		B		$10,LT

;;    //
;;    // Intermediate digest value
;;    //
;;    digest[0] += a;
;;    digest[1] += b;
;;    digest[2] += c;
;;    digest[3] += d;
;;    digest[4] += e;
;;    digest[5] += f;
;;    digest[6] += g;
;;    digest[7] += h;
		MOVL	XAR7,*SP_digest		; XAR7 => digest[0]
		MOVL	XAR6,#0
		MOV		AR6,@SP
		SUBB	XAR6,#SP_a_offset	; XAR6 => a

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[0] += uint32_t a;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[1] += uint32_t b;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[2] += uint32_t c;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[3] += uint32_t d;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[4] += uint32_t e;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[5] += uint32_t f;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[6] += uint32_t g;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[7] += uint32_t h;

		MOVL	XAR7,@save_XAR7
		MOVL	XAR6,@save_XAR6
		MOVL	XAR3,@save_XAR3
		MOVL	XAR2,@save_XAR2
		MOVL	XAR1,@save_XAR1
		MOVL	XAR0,@save_XAR0
		MOVL	XAR5,*SP_XAR5
		MOVL	XAR4,*SP_XAR4
		SUBB	SP,#SP_size
		LRETR

;;//*****************************************************************************
;;//
;;// SHA-256 process a block of data
;;// Input message : Word-wise
;;//
;;//*****************************************************************************
;;void SHA256_processBlockWordWise(uint32_t digest[8], uint32_t Ws[16])
;;{
;;    uint32_t wt;             // Wt from standard
;;    int16_t s;               // s is the message schedule index
;;    uint32_t temp1;          // T1 from standard
;;    uint32_t temp2;          // T2 from standard
;;
;;    //
;;    // Initialize working variables
;;    //
;;    uint32_t a = digest[0];
;;    uint32_t b = digest[1];
;;    uint32_t c = digest[2];
;;    uint32_t d = digest[3];
;;    uint32_t e = digest[4];
;;    uint32_t f = digest[5];
;;    uint32_t g = digest[6];
;;    uint32_t h = digest[7];
;;
;;    //
;;    // Perform 64 rounds of compression function
;;    //
;;    for(s = 0; s < 64; s++)
;;    {
;;        if(s >= 16)
;;        {
;;            Ws[s & 0xF] += SHA256_SIGMA1(Ws[(s + 14) & 0xF]) +
;;                           Ws[(s + 9) & 0xF] +
;;                           SHA256_SIGMAZ(Ws[(s + 1) & 0xF]);
;;        }
;;
;;        wt = Ws[s & 0xF];
;;        temp1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + SHA256_K[s] + wt;
;;        temp2 = SHA256_SIGZ(a) + SHA256_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;    }
;;
;;    //
;;    // Intermediate digest value
;;    //
;;    digest[0] += a;
;;    digest[1] += b;
;;    digest[2] += c;
;;    digest[3] += d;
;;    digest[4] += e;
;;    digest[5] += f;
;;    digest[6] += g;
;;    digest[7] += h;
;;}

;;void SHA256_processBlockWordWise(uint32_t digest[8], uint32_t Ws[16])
;;{
;;    uint32_t wt;             // Wt from standard
;;    int16_t s;               // s is the message schedule index
;;    uint32_t temp1;          // T1 from standard
;;    uint32_t temp2;          // T2 from standard
;;
;; On Entry:
;;   XAR4 => digest[0]  uint32_t
;;   XAR5 => Ws[0]      uint32_t
;;
;;		.sect		.text
		.sect		".TI.ramfunc"  ; Call this line to execute from RAM
		.global		_SHA256_processBlockWordWise_casm_C28
_SHA256_processBlockWordWise_casm_C28:
		MOVW	DP,#temp_var
		ADDB	SP,#SP_size
		MOVL	*SP_XAR4,XAR4
		MOVL	*SP_XAR5,XAR5
		MOVL	@save_XAR0,XAR0
		MOVL	@save_XAR1,XAR1
		MOVL	@save_XAR2,XAR2
		MOVL	@save_XAR3,XAR3
		MOVL	@save_XAR6,XAR6
		MOVL	@save_XAR7,XAR7

;;    //
;;    // Initialize working variables
;;    //
;;    uint32_t a = digest[0];
;;    uint32_t b = digest[1];
;;    uint32_t c = digest[2];
;;    uint32_t d = digest[3];
;;    uint32_t e = digest[4];
;;    uint32_t f = digest[5];
;;    uint32_t g = digest[6];
;;    uint32_t h = digest[7];
		MOVL	XAR7,*SP_digest		; XAR7 => digest[0]
		MOVZ	AR6,@SP
		SUBB	XAR6,#SP_a_offset	; XAR6 => a
		MOVL	ACC,*XAR7++			; uint32_t a = digest[0];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t b = digest[1];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t c = digest[2];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t d = digest[3];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t e = digest[4];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t f = digest[5];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t g = digest[6];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint32_t h = digest[7];
		MOVL	*XAR6++,ACC

;;    //
;;    // Perform 64 rounds of compression function
;;    //
;;    for(s = 0; s < 64; s++)
;;    {
;;        if(s >= 16)
;;        {
;; // SHA256_CALC_PART1:
;;            Ws[s & 0xF] += SHA256_SIGMA1(Ws[(s + 14) & 0xF]) + Ws[(s + 9) & 0xF] + SHA256_SIGMAZ(Ws[(s + 1) & 0xF]);
;;        }
;;
;; // SHA256_CALC_PART2:
;;        wt = Ws[s & 0xF];
;;        temp1 = h + SHA256_SIG1(e) + SHA256_CH(e, f, g) + SHA256_K[s] + wt;
;;        temp2 = SHA256_SIGZ(a) + SHA256_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;    }

		MOVB	AL,#0
WORD_$10:
		MOV		*SP_s,AL			; s  = AL
		MOVU	ACC,@AL
		AND		ACC,#0x000F
		LSL		ACC,#1
		ADDL	ACC,*SP_Ws
		MOVL	XAR5,@ACC			; XAR5 => Ws[s & 0xF]
		MOV		AL,*SP_s			; AL = s
		CMPB	AL,#16				; if(s >= 16)?
		B		WORD_$20,LT

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART1:
;;-----------------------------------------------------------------------------
;;       Ws[s & 0xF] += XAR6  = SHA256_SIGMA1(temp3 = Ws[(s + 14) & 0xF]) +
;;                      temp5 = Ws[(s + 9) & 0xF] +
;;                      XAR2  = SHA256_SIGMAZ(temp6 = Ws[(s + 1) & 0xF]);
;;-----------------------------------------------------------------------------

		; temp 3 = Ws[(s + 14) & 0xF]
		MOVU	ACC,*SP_s
		ADDB	ACC,#14
		AND		ACC,#0x000F
		LSL		ACC,#1
		ADDL	ACC,*SP_Ws
		MOVL	XAR0,@ACC

		;temp5   = Ws[(s + 9) & 0xF]
		MOVU	ACC,*SP_s
		ADDB	ACC,#9
		AND		ACC,#0x000F
		LSL		ACC,#1
		ADDL	ACC,*SP_Ws
		MOVL	XAR1,@ACC

		; temp6 = Ws[(s + 1) & 0xF]
		MOVU	ACC,*SP_s
		ADDB	ACC,#1
		AND		ACC,#0x000F
		LSL		ACC,#1
		ADDL	ACC,*SP_Ws
		MOVL	XAR2,@ACC

		MOVL	ACC,*XAR0
		MOVL	@temp3,ACC

		MOVL	ACC,*XAR1
		MOVL	@temp5,ACC

		MOVL	ACC,*XAR2
		MOVL	@temp6,ACC

;; XAR6  = SHA256_SIGMA1(temp3 = Ws[(s + 14) & 0xF])
;;
;; x = temp3
;; #define SHA256_SIGMA1(x)     (temp10 = XAR0 = SHA256_ROTR32(x, 17) ^ temp11 = XAR2 = SHA256_ROTR32(x, 19) ^ temp12 = SHA256_SHR(x, 10))

		MOVL	ACC,@temp3				; ACC = temp3
		LSR64	ACC:P,#10
		MOVL	@temp12,ACC				; temp12 = SHA256_SHR(x, 10)
		LSR64	ACC:P,#(17-10)
		MOVL	XAR0,@ACC				; XAR0 = x >> 17
		LSR64	ACC:P,#(19-17)
		MOVL	XAR2,@ACC				; XAR2 = x >> 19
		ZAPA
		MOVL	ACC,@temp3				; ACC = temp3
		LSL64	ACC:P,#(32-19)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 19
		LSL64	ACC:P,#(19-17)			; ACC    = x << 32 - 17
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 17)
		MOVL	ACC,@temp11
		ADDL	ACC,@XAR2				; ACC    = SHA256_ROTR32(x, 19)
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	XAR6,@ACC				; XAR6  = SHA256_SIGMA1(temp3 = Ws[(s + 14) & 0xF])

;; XAR2  = SHA256_SIGMAZ(temp6 = Ws[(s + 1) & 0xF]);
;;
;; x = temp6
;; #define SHA256_SIGMAZ(x)     (temp10 = XAR0 = SHA256_ROTR32(x, 7) ^ temp11 = XAR2 = SHA256_ROTR32(x, 18) ^ temp12 = SHA256_SHR(x, 3))

		MOVL	ACC,@temp6				; ACC = temp6
		LSR64	ACC:P,#3
		MOVL	@temp12,ACC				; temp12 = SHA256_SHR(x, 3)
		LSR64	ACC:P,#(7-3)
		MOVL	@XAR0,ACC				; XAR0   = x >> 7
		LSR64	ACC:P,#(18-7)
		MOVL	XAR2,@ACC				; XAR2   = x >> 18
		ZAPA
		MOVL	ACC,@temp6				; ACC = temp6
		LSL64	ACC:P,#(32-18)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 18
		LSL64	ACC:P,#(18-7)				; ACC    = x << 32 - 7
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 7)
		MOVL	ACC,@temp11
		ADDL	ACC,@XAR2				; ACC    = SHA256_ROTR32(x, 18)
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	@XAR2,ACC				; XAR2  = SHA256_SIGMAZ(temp6 = Ws[(s + 1) & 0xF])

;; Ws[s & 0xF] += XAR6  + temp5 + XAR2
;;
;; XAR5 => Ws[s & 0xF]
		MOVL	P,@XAR6
		ADDUL	P,@temp5
		ADDUL	P,@XAR2
		ADDUL	P,*XAR5
		MOVL	*XAR5,P

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART1: end
;;-----------------------------------------------------------------------------

WORD_$20:

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART2:
;;-----------------------------------------------------------------------------
;;        wt = Ws[s & 0xF];
;;        temp1 = h + temp13 = SHA256_SIG1(e) + temp4 = SHA256_CH(e, f, g) + temp5 = SHA256_K[s] + wt;
;;        temp2 = ACC = SHA256_SIGZ(a) + temp7 = SHA256_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;


;; #define SHA256_SIG1(x)       (temp10 = XAR0 = SHA256_ROTR32(x, 6) ^ temp11 = XAR2 = SHA256_ROTR32(x, 11) ^ temp12 = XAR6 = SHA256_ROTR32(x, 25))
;;
;; x = e
;; temp13 = SHA256_SIG1(e)
		MOVL	ACC,*SP_e				; ACC = e
		LSR64	ACC:P,#6
		MOVL	XAR0,@ACC				; XAR0 = x >> 6
		LSR64	ACC:P,#(11-6)
		MOVL	XAR2,@ACC				; XAR2 = x >> 11
		LSR64	ACC:P,#(25-11)
		MOVL	XAR6,@ACC				; XAR6 = x >> 25
		ZAPA
		MOVL	ACC,*SP_e				; ACC = e
		LSL64	ACC:P,#(32-25)
		MOVL	@temp12,ACC				; temp12 = x << 32 - 25
		LSL64	ACC:P,#(25-11)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 11
		LSL64	ACC:P,#(11-6)			; ACC    = x << 32 - 6
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 6)
		MOVL	ACC,@XAR2
		ADDL	ACC,@temp11
		MOVL	@temp11,ACC				; temp11 = SHA256_ROTR32(x, 11)
		MOVL	ACC,@XAR6
		ADDL	ACC,@temp12				; ACC    = SHA256_ROTR32(x, 25)
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	*SP_temp13,ACC			; temp13 = SHA256_SIG1(e)

		.global	SHA256_K
		MOV		AL,*SP_s
		LSL		AL,#1
		MOVZ	AR0,@AL
		MOVL	XAR1,#SHA256_K			; XAR1 = &SHA256_K[s]

;; #define SHA256_CH(x, y, z)   (((x) & ((y) ^ (z))) ^ (z))
;;
;; temp4 = SHA256_CH(e, f, g)
;;
;; temp4 = ((f ^ g) & e) ^ g
		MOVL	ACC,*SP_f
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		AND		AL,*SP_e_w0
		AND		AH,*SP_e_w1
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		MOVL	@temp4,ACC

;; temp5 = SHA256_K[s]
		MOVL	ACC,*+XAR1[AR0]
		MOVL	@temp5,ACC

;; #define SHA256_MAJ(x, y, z)  ((((y)^(z)) & (x)) ^ ((y) & (z)))
;;
;; temp7 = SHA256_MAJ(a, b, c)
;;
;; temp7 = ((b ^ c) & a) ^ (b & c)
		MOVL	ACC,*SP_b
		XOR		AL,*SP_c_w0
		XOR		AH,*SP_c_w1
		AND		AL,*SP_a_w0
		AND		AH,*SP_a_w1
		MOVL	P,@ACC
		MOVL	ACC,*SP_b
		AND		AL,*SP_c_w0
		AND		AH,*SP_c_w1
		XOR		AL,@PL
		XOR		AH,@PH
		MOVL	@temp7,ACC

;; #define SHA256_SIGZ(x)       (temp10 = XAR0 = SHA256_ROTR32(x, 2) ^ temp11 = XAR2 = SHA256_ROTR32(x, 13) ^ temp12 = XAR6 = SHA256_ROTR32(x, 22))
;;
;; x = a
;; ACC = SHA256_SIGZ(a)
		MOVL	ACC,*SP_a				; ACC = a
		LSR64	ACC:P,#2
		MOVL	XAR0,@ACC				; XAR0 = x >> 2
		LSR64	ACC:P,#(13-2)
		MOVL	XAR2,@ACC				; XAR2 = x >> 13
		LSR64	ACC:P,#(22-13)
		MOVL	XAR6,@ACC				; XAR6 = x >> 22
		ZAPA
		MOVL	ACC,*SP_a				; ACC = a
		LSL64	ACC:P,#(32-22)
		MOVL	@temp12,ACC				; temp12 = x << 32 - 22
		LSL64	ACC:P,#(22-13)
		MOVL	@temp11,ACC				; temp11 = x << 32 - 13
		LSL64	ACC:P,#(13-2)				; ACC    = x << 32 - 2
		ADDL	ACC,@XAR0
		MOVL	@temp10,ACC				; temp10 = SHA256_ROTR32(x, 2)
		MOVL	ACC,@XAR2
		ADDL	ACC,@temp11
		MOVL	@temp11,ACC				; temp11 = SHA256_ROTR32(x, 13)
		MOVL	ACC,@XAR6
		ADDL	ACC,@temp12				; ACC    = SHA256_ROTR32(x, 22)
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0			; ACC    = SHA256_SIGZ(a)

;; temp2 = ACC = SHA256_SIGZ(a) + temp7 = SHA256_MAJ(a, b, c);
;;
;; XAR2 = temp2 = ACC + temp7
		ADDL	ACC,@temp7
		MOVL	XAR2,@ACC

;; wt = XAR5 => Ws[s & 0xF];
;;
;; temp1 = h + temp13 = SHA256_SIG1(e) + temp4 = SHA256_CH(e, f, g) + temp5 = SHA256_K[s] + wt;
;;
;; temp1 = h + temp13 = SHA384_SIG1(e) + temp4 = SHA384_CH(e, f, g) + temp5 = SHA384_K[s] + wt;
;;
;; XAR0 = temp1 = h + temp13 + temp4 + temp5 + wt
		MOVL	ACC,@temp4
		ADDL	ACC,@temp5
		ADDL	ACC,*SP_h
		ADDL	ACC,*SP_temp13
		ADDL	ACC,*XAR5
		MOVL	XAR0,@ACC

;; h = g;
;; g = f;
;; f = e;
;; e = d + temp1;
;; d = c;
;; c = b;
;; b = a;
;; a = temp1 + temp2;

		MOVL	ACC,*SP_g
		MOVL	*SP_h,ACC				; h = g

		MOVL	ACC,*SP_f
		MOVL	*SP_g,ACC				; g = f

		MOVL	ACC,*SP_e
		MOVL	*SP_f,ACC				; f = e

		MOVL	ACC,@XAR0
		ADDL	ACC,*SP_d
		MOVL	*SP_e,ACC				; e = d + temp1

		MOVL	ACC,*SP_c
		MOVL	*SP_d,ACC				; d = c

		MOVL	ACC,*SP_b
		MOVL	*SP_c,ACC				; c = b

		MOVL	ACC,*SP_a
		MOVL	*SP_b,ACC				; b = a

		MOVL	ACC,@XAR0
		ADDL	ACC,@XAR2
		MOVL	*SP_a,ACC				; a = temp1 + temp2

;;-----------------------------------------------------------------------------
;; // SHA256_CALC_PART2: end
;;-----------------------------------------------------------------------------

		MOVU	ACC,*SP_s			; AL = s, AH = 0
		ADD		AL,#1				; AL = s++
		CMPB	AL,#64				; if(s < 64)?
		B		WORD_$10,LT

;;    //
;;    // Intermediate digest value
;;    //
;;    digest[0] += a;
;;    digest[1] += b;
;;    digest[2] += c;
;;    digest[3] += d;
;;    digest[4] += e;
;;    digest[5] += f;
;;    digest[6] += g;
;;    digest[7] += h;
		MOVL	XAR7,*SP_digest		; XAR7 => digest[0]
		MOVL	XAR6,#0
		MOV		AR6,@SP
		SUBB	XAR6,#SP_a_offset	; XAR6 => a

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[0] += uint32_t a;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[1] += uint32_t b;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[2] += uint32_t c;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[3] += uint32_t d;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[4] += uint32_t e;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[5] += uint32_t f;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[6] += uint32_t g;

		MOVL	P,*XAR7
		ADDUL	P,*XAR6++
		MOVL	*XAR7++,P			; digest[7] += uint32_t h;

		MOVL	XAR7,@save_XAR7
		MOVL	XAR6,@save_XAR6
		MOVL	XAR3,@save_XAR3
		MOVL	XAR2,@save_XAR2
		MOVL	XAR1,@save_XAR1
		MOVL	XAR0,@save_XAR0
		MOVL	XAR5,*SP_XAR5
		MOVL	XAR4,*SP_XAR4
		SUBB	SP,#SP_size
		LRETR

;;
;; File End.
;;
