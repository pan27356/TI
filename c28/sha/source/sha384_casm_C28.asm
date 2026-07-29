;;//*****************************************************************************
;;// Title:   CASM Version Of Functions:
;;//          void SHA384_processBlockByteWise(uint64_t digest[8],  uint16_t Ws[128])
;;//          void SHA384_processBlockWordWise(uint64_t digest[8],  uint64_t Ws[16])
;;//
;;// Call:    void SHA384_processBlockByteWise_casm_C28(uint64_t digest[8],  uint16_t Ws[128])
;;//          void SHA384_processBlockWordWise_casm_C28(uint64_t digest[8],  uint64_t Ws[16])
;;//
;;// Version: 3
;;//
;;// Cycles:  Byte Wise:   30,821 (running from RAM)
;;//          Word Wise:   26,709 (running from RAM)
;;//          SHA384_K[80] const table located in RAM
;;//
;// $TI Release: C2000 AES Software v2.00.00.00 $
;// $Release Date: Tue Oct 29 00:56:51 IST 2024 $
;// $Copyright:
;// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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

temp_var	.usect	".bss",64,64,6
			.asg	"(temp_var+0)",temp3_l32
			.asg	"(temp_var+2)",temp3_h32

			.asg	"(temp_var+4)",temp4_l32
			.asg	"(temp_var+6)",temp4_h32

			.asg	"(temp_var+8)",temp5_l32
			.asg	"(temp_var+10)",temp5_h32

			.asg	"(temp_var+12)",temp6_l32
			.asg	"(temp_var+14)",temp6_h32

			.asg	"(temp_var+16)",temp7_l32
			.asg	"(temp_var+18)",temp7_h32

			.asg	"(temp_var+20)",temp8_l32
			.asg	"(temp_var+22)",temp8_h32

			.asg	"(temp_var+24)",temp9_l32
			.asg	"(temp_var+26)",temp9_h32

			.asg	"(temp_var+28)",temp10_l32
			.asg	"(temp_var+28)",temp10_w0
			.asg	"(temp_var+29)",temp10_w1
			.asg	"(temp_var+30)",temp10_h32
			.asg	"(temp_var+30)",temp10_w2
			.asg	"(temp_var+31)",temp10_w3

			.asg	"(temp_var+32)",temp11_l32
			.asg	"(temp_var+32)",temp11_w0
			.asg	"(temp_var+33)",temp11_w1
			.asg	"(temp_var+34)",temp11_h32
			.asg	"(temp_var+34)",temp11_w2
			.asg	"(temp_var+35)",temp11_w3

			.asg	"(temp_var+36)",temp12_l32
			.asg	"(temp_var+36)",temp12_w0
			.asg	"(temp_var+37)",temp12_w1
			.asg	"(temp_var+38)",temp12_h32
			.asg	"(temp_var+38)",temp12_w2
			.asg	"(temp_var+39)",temp12_w3

			.asg	"(temp_var+40)",save_XAR0
			.asg	"(temp_var+42)",save_XAR1
			.asg	"(temp_var+44)",save_XAR2
			.asg	"(temp_var+46)",save_XAR3
			.asg	"(temp_var+48)",save_XAR6
			.asg	"(temp_var+50)",save_XAR7

SP_size			.set	54
SP_a_offset		.set	54
		.asg	"-SP[54]",SP_a
		.asg	"-SP[54]",SP_a_l32
		.asg	"-SP[54]",SP_a_w0
		.asg	"-SP[53]",SP_a_w1
		.asg	"-SP[52]",SP_a_h32
		.asg	"-SP[52]",SP_a_w2
		.asg	"-SP[51]",SP_a_w3

		.asg	"-SP[50]",SP_b
		.asg	"-SP[50]",SP_b_l32
		.asg	"-SP[50]",SP_b_w0
		.asg	"-SP[49]",SP_b_w1
		.asg	"-SP[48]",SP_b_h32
		.asg	"-SP[48]",SP_b_w2
		.asg	"-SP[47]",SP_b_w3

		.asg	"-SP[46]",SP_c
		.asg	"-SP[46]",SP_c_l32
		.asg	"-SP[46]",SP_c_w0
		.asg	"-SP[45]",SP_c_w1
		.asg	"-SP[44]",SP_c_h32
		.asg	"-SP[44]",SP_c_w2
		.asg	"-SP[43]",SP_c_w3

		.asg	"-SP[42]",SP_d
		.asg	"-SP[42]",SP_d_l32
		.asg	"-SP[42]",SP_d_w0
		.asg	"-SP[41]",SP_d_w1
		.asg	"-SP[40]",SP_d_h32
		.asg	"-SP[40]",SP_d_w2
		.asg	"-SP[39]",SP_d_w3

		.asg	"-SP[38]",SP_e
		.asg	"-SP[38]",SP_e_l32
		.asg	"-SP[38]",SP_e_w0
		.asg	"-SP[37]",SP_e_w1
		.asg	"-SP[36]",SP_e_h32
		.asg	"-SP[36]",SP_e_w2
		.asg	"-SP[35]",SP_e_w3

		.asg	"-SP[34]",SP_f
		.asg	"-SP[34]",SP_f_l32
		.asg	"-SP[34]",SP_f_w0
		.asg	"-SP[33]",SP_f_w1
		.asg	"-SP[32]",SP_f_h32
		.asg	"-SP[32]",SP_f_w2
		.asg	"-SP[31]",SP_f_w3

		.asg	"-SP[30]",SP_g
		.asg	"-SP[30]",SP_g_l32
		.asg	"-SP[30]",SP_g_w0
		.asg	"-SP[29]",SP_g_w1
		.asg	"-SP[28]",SP_g_h32
		.asg	"-SP[28]",SP_g_w2
		.asg	"-SP[27]",SP_g_w3

		.asg	"-SP[26]",SP_h
		.asg	"-SP[26]",SP_h_l32
		.asg	"-SP[26]",SP_h_w0
		.asg	"-SP[25]",SP_h_w1
		.asg	"-SP[24]",SP_h_h32
		.asg	"-SP[24]",SP_h_w2
		.asg	"-SP[23]",SP_h_w3

		.asg	"-SP[22]",SP_temp2
		.asg	"-SP[22]",SP_temp2_l32
		.asg	"-SP[20]",SP_temp2_h32

		.asg	"-SP[18]",SP_temp1
		.asg	"-SP[18]",SP_temp1_l32
		.asg	"-SP[16]",SP_temp1_h32

SP_wt_offset	.set	14
		.asg	"-SP[14]",SP_wt
		.asg	"-SP[14]",SP_wt_l32
		.asg	"-SP[12]",SP_wt_h32

		.asg	"-SP[10]",SP_s

		.asg	"-SP[9]",SP_s0

		.asg	"-SP[8]",SP_XAR4
		.asg	"-SP[8]",SP_digest

		.asg	"-SP[6]",SP_XAR5
		.asg	"-SP[6]",SP_Ws

		.asg	"-SP[4]",SP_temp13
		.asg	"-SP[4]",SP_temp13_l32
		.asg	"-SP[2]",SP_temp13_h32

;;=============================================================================
;;#define SHA384_GETU64(plaintext)
M_SHA384_GETU64	.macro		pointer, dest_h32, dest_l32
		MOVB	AH.LSB,*+pointer[2]		; Ws[((s0 + AH) & 0x7F) + 1] << 56U
		MOVB	AH.MSB,*+pointer[0]		; Ws[((s0 + AH) & 0x7F) + 0] << 64U
		MOVB	AL.LSB,*+pointer[6]		; Ws[((s0 + AH) & 0x7F) + 3] << 32U
		MOVB	AL.MSB,*+pointer[4]		; Ws[((s0 + AH) & 0x7F) + 2] << 40U
		ADDB	pointer,#4
		MOVL	dest_h32,ACC			; XAR3 = high value
		MOVB	AH.LSB,*+pointer[2]		; Ws[((s0 + AH) & 0x7F) + 5] << 16U
		MOVB	AH.MSB,*+pointer[0]		; Ws[((s0 + AH) & 0x7F) + 4] << 24U
		MOVB	AL.LSB,*+pointer[6]		; Ws[((s0 + AH) & 0x7F) + 7] << 0U
		MOVB	AL.MSB,*+pointer[4]		; Ws[((s0 + AH) & 0x7F) + 6] << 8U
		MOVL	dest_l32,ACC			; XAR2 = low value
		.endm

;;//*****************************************************************************
;;//
;;// SHA-384 process a block of data
;;// Input message : Byte-wise
;;//
;;//*****************************************************************************
;;void SHA384_processBlockByteWise_casm_c28(uint64_t digest[8],  uint16_t Ws[128])
;;{
;;    uint64_t wt;             // Wt from standard
;;    int16_t s, s0;               // s is the message schedule index
;;    uint64_t temp1;          // T1 from standard
;;    uint64_t temp2;          // T2 from standard
;;
;;    //
;;    // Initialize working variables
;;    //
;;    uint64_t a = digest[0];
;;    uint64_t b = digest[1];
;;    uint64_t c = digest[2];
;;    uint64_t d = digest[3];
;;    uint64_t e = digest[4];
;;    uint64_t f = digest[5];
;;    uint64_t g = digest[6];
;;    uint64_t h = digest[7];
;;
;;    //
;;    // Perform 64 rounds of compression function
;;    //
;;    for(s = 0; s < 80; s++)
;;    {
;;        s0 = s << 3;
;;        if(s >= 16)
;;        {
;;            wt = SHA384_SIGMA1(SHA384_GETU64(&Ws[(s0 + 112) & 0x7F])) +
;;                 SHA384_GETU64(&Ws[(s0 + 72) & 0x7F]) +
;;                 SHA384_SIGMAZ(SHA384_GETU64(&Ws[(s0 + 8) & 0x7F])) +
;;                 SHA384_GETU64(&Ws[s0 & 0x7F]);
;;
;;            SHA384_PUTU64(&Ws[s0 & 0x7F], wt);
;;        }
;;        else
;;        {
;;            wt = SHA384_GETU64(&Ws[s0]);
;;        }
;;
;;        temp1 = h + SHA384_SIG1(e) + SHA384_CH(e, f, g) + SHA384_K[s] + wt;
;;        temp2 = SHA384_SIGZ(a) + SHA384_MAJ(a, b, c);
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
;;//*****************************************************************************

;;void SHA384_processBlockByteWise(uint64_t digest[8],  uint16_t Ws[128])
;;{
;;    uint64_t wt;             // Wt from standard
;;    int16_t s, s0;               // s is the message schedule index
;;    uint64_t temp1;          // T1 from standard
;;    uint64_t temp2;          // T2 from standard
;;
;; On Entry:
;;   XAR4 => digest[0]  uint64_t
;;   XAR5 => Ws[0]      uint16_t
;;
;;		.sect		.text
		.sect		".TI.ramfunc"  ; Call this line to execute from RAM
		.global		_SHA384_processBlockByteWise_casm_C28
_SHA384_processBlockByteWise_casm_C28:
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
;;    uint64_t a = digest[0];
;;    uint64_t b = digest[1];
;;    uint64_t c = digest[2];
;;    uint64_t d = digest[3];
;;    uint64_t e = digest[4];
;;    uint64_t f = digest[5];
;;    uint64_t g = digest[6];
;;    uint64_t h = digest[7];
		MOVL	XAR7,*SP_digest		; XAR7 => digest[0]
		MOVZ	AR6,@SP
		SUBB	XAR6,#SP_a_offset	; XAR6 => a
		MOVL	ACC,*XAR7++			; uint64_t a = digest[0];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t b = digest[1];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t c = digest[2];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t d = digest[3];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t e = digest[4];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t f = digest[5];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t g = digest[6];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t h = digest[7];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC

;;    //
;;    // Perform 64 rounds of compression function
;;    //
;;    for(s = 0; s < 80; s++)
;;    {
;;        s0 = s << 3;
;;        if(s >= 16)
;;        {
;; // SHA384_CALC_PART1:
;;            wt = SHA384_SIGMA1(SHA384_GETU64(&Ws[(s0 + 112) & 0x7F])) +
;;                 SHA384_GETU64(&Ws[(s0 + 72) & 0x7F]) +
;;                 SHA384_SIGMAZ(SHA384_GETU64(&Ws[(s0 + 8) & 0x7F])) +
;;                 SHA384_GETU64(&Ws[s0 & 0x7F]);
;;
;;            SHA384_PUTU64(&Ws[s0 & 0x7F], wt);
;;        }
;;        else
;;        {
;; // SHA384_CALC_PART2:
;;            wt = SHA384_GETU64(&Ws[s0]);
;;        }
;; // SHA384_CALC_PART3:
;;        temp1 = h + SHA384_SIG1(e) + SHA384_CH(e, f, g) + SHA384_K[s] + wt;
;;        temp2 = SHA384_SIGZ(a) + SHA384_MAJ(a, b, c);
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
		LSL		AL,#3				; AL = s << 3
		MOV		*SP_s0,AL			; s0 = s << 3
		CMPB	AL,#128				; if(s >= 16)?
		B		$20,LT

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART1:
;;-----------------------------------------------------------------------------
;; wt = XAR7:XAR6 = SHA384_SIGMA1(temp3 = SHA384_GETU64(&Ws[(s0 + 112) & 0x7F])) +
;;      temp5     = SHA384_GETU64(&Ws[(s0 + 72) & 0x7F]) +
;;      XAR3:XAR2 = SHA384_SIGMAZ(temp6 = SHA384_GETU64(&Ws[(s0 + 8) & 0x7F])) +
;;      temp8     = SHA384_GETU64(&Ws[s0 & 0x7F]);
;;
;; temp3 = SHA384_GETU64(&Ws[(s0 + 112) & 0x7F])
		MOVU	ACC,*SP_s0
		ADDB	ACC,#112
		AND		ACC,#0x007F
		ADDL	ACC,*SP_Ws
		MOVL	XAR0,@ACC

;; temp5 = SHA384_GETU64(&Ws[(s0 + 72) & 0x7F])
		MOVU	ACC,*SP_s0
		ADDB	ACC,#72
		AND		ACC,#0x007F
		ADDL	ACC,*SP_Ws
		MOVL	XAR1,@ACC

;; temp6 = SHA384_GETU64(&Ws[(s0 + 8) & 0x7F])
		MOVU	ACC,*SP_s0
		ADDB	ACC,#8
		AND		ACC,#0x007F
		ADDL	ACC,*SP_Ws
		MOVL	XAR2,@ACC

;; temp8 = SHA384_GETU64(&Ws[s0 & 0x7F])
		MOVU	ACC,*SP_s0
		AND		ACC,#0x007F
		ADDL	ACC,*SP_Ws
		MOVL	XAR3,@ACC

		M_SHA384_GETU64		XAR0, @temp3_h32, @temp3_l32

		M_SHA384_GETU64		XAR1, @temp5_h32, @temp5_l32

		M_SHA384_GETU64		XAR2, @temp6_h32, @temp6_l32

		M_SHA384_GETU64		XAR3, @temp8_h32, @temp8_l32

;; XAR7:XAR6 = SHA384_SIGMA1(temp3 = SHA384_GETU64(&Ws[(s0 + 112) & 0x7F]))
;;
;; x = temp3
;; #define SHA384_SIGMA1(x)     (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 19) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 61) ^ temp12 = SHA384_SHR(x, 6))
;;
		MOVL	P,@temp3_l32			; P   = temp3_l32
		MOVL	ACC,@temp3_h32			; ACC = temp3_h32
		LSR64	ACC:P,#6
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = SHA384_SHR(x, 6)
		LSR64	ACC:P,#(19-6)
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 19
		MOV		T,#(61-19)
		LSR64	ACC:P,T
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 61
		MOVL	P,@temp3_l32			; P   = temp3_l32
		MOVL	ACC,@temp3_h32			; ACC = temp3_h32
		LSL64	ACC:P,#(64-61)
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 61
		MOV		T,#(61-19)
		LSL64	ACC:P,T					; ACC:P = x << 64 - 19
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 19)
		MOVL	P,@temp11_l32
		MOVL	ACC,@temp11_h32
		ADDUL	P,@XAR2
		ADDL	ACC,@XAR3				; ACC:P = SHA384_ROTR64(x, 61)
		XOR		AH,@temp12_w3
		XOR		AL,@temp12_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	XAR7,@ACC
		MOVL	ACC,@P
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	XAR6,@ACC				; XAR7:XAR6 = SHA384_SIGMA1(temp3 = SHA384_GETU64(&Ws[(s0 + 112) & 0x7F]))

;; XAR3:XAR2 = SHA384_SIGMAZ(temp6 = SHA384_GETU64(&Ws[(s0 + 8) & 0x7F]))
;;
;; x = temp6
;; #define SHA384_SIGMAZ(x)     (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 1) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 8) ^ temp12 = SHA384_SHR(x, 7))
;;
		MOVL	P,@temp6_l32			; P   = temp3_l32
		MOVL	ACC,@temp6_h32			; ACC = temp3_h32
		LSR64	ACC:P,#1
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 1
		LSR64	ACC:P,#(7-1)
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = SHA384_SHR(x, 7)
		LSR64	ACC:P,#(8-7)
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 8
		MOVL	P,@temp6_l32			; P   = temp3_l32
		MOVL	ACC,@temp6_h32			; ACC = temp3_h32
		MOV		T,#(64-8)
		LSL64	ACC:P,T
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 8
		LSL64	ACC:P,#(8-1)			; ACC:P = x << 64 - 1
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 1)
		MOVL	P,@temp11_l32
		MOVL	ACC,@temp11_h32
		ADDUL	P,@XAR2
		ADDL	ACC,@XAR3				; ACC:P = SHA384_ROTR64(x, 8)
		XOR		AH,@temp12_w3
		XOR		AL,@temp12_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	@XAR3,ACC
		MOVL	ACC,@P
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	@XAR2,ACC				; XAR3:XAR2 = SHA384_SIGMAZ(temp6 = SHA384_GETU64(&Ws[(s0 + 8) & 0x7F]))

;; wt = XAR7:XAR6 + temp5 + XAR3:XAR2 + temp8
		MOVL	P,@XAR6
		MOVL	ACC,@XAR7
		ADDUL	P,@temp5_l32
		ADDCL	ACC,@temp5_h32
		ADDUL	P,@XAR2
		ADDCL	ACC,@XAR3
		ADDUL	P,@temp8_l32
		ADDCL	ACC,@temp8_h32
		MOVL	*SP_wt_l32,P
		MOVL	*SP_wt_h32,ACC

;; #define SHA384_PUTU64(ciphertext, st) \
;;        { (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 56U) & 0x00FFU); \
;;          (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 48U) & 0x00FFU); \
;;          (ciphertext)[2] = (uint16_t)((uint16_t)((st) >> 40U) & 0x00FFU); \
;;          (ciphertext)[3] = (uint16_t)((uint16_t)((st) >> 32U) & 0x00FFU); \
;;          (ciphertext)[4] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU); \
;;          (ciphertext)[5] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU); \
;;          (ciphertext)[6] = (uint16_t)((uint16_t)((st) >> 8U) & 0x00FFU); \
;;          (ciphertext)[7] = (uint16_t)((uint16_t)(st) & 0x00FFU); }
;;
;; SHA384_PUTU64(&Ws[s0 & 0x7F], wt)
		MOVZ	AR0,@SP					; XAR0 => SP top of stack
		MOVU	ACC,*SP_s0
		AND		ACC,#0x007F
		ADDL	ACC,*SP_Ws
		MOVL	XAR1,@ACC				; XAR1 = &Ws[s0 & 0x7F]
		SUBB	XAR0,#SP_wt_offset-2	; XAR0 => &wt-2 on stack (point to high 32)
		NOP
		NOP
		MOVB	AL.LSB,*+XAR0[3]
		MOV		*XAR1++,AL				; (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 56U) & 0x00FFU)
		MOVB	AL.LSB,*+XAR0[2]
		MOV		*XAR1++,AL				; (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 48U) & 0x00FFU)
		MOVB	AL.LSB,*+XAR0[1]
		MOV		*XAR1++,AL				; (ciphertext)[2] = (uint16_t)((uint16_t)((st) >> 40U) & 0x00FFU)
		MOVB	AL.LSB,*+XAR0[0]
		MOV		*XAR1++,AL				; (ciphertext)[3] = (uint16_t)((uint16_t)((st) >> 32U) & 0x00FFU)
		SUBB	XAR0,#2
		MOVB	AL.LSB,*+XAR0[3]		; (ciphertext)[0] = (uint16_t)((uint16_t)((st) >> 24U) & 0x00FFU)
		MOV		*XAR1++,AL
		MOVB	AL.LSB,*+XAR0[2]		; (ciphertext)[1] = (uint16_t)((uint16_t)((st) >> 16U) & 0x00FFU)
		MOV		*XAR1++,AL
		MOVB	AL.LSB,*+XAR0[1]		; (ciphertext)[2] = (uint16_t)((uint16_t)((st) >> 8U) & 0x00FFU)
		MOV		*XAR1++,AL
		MOVB	AL.LSB,*+XAR0[0]		; (ciphertext)[3] = (uint16_t)((uint16_t)(st) & 0x00FFU)
		MOV		*XAR1,AL

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART1: end
;;-----------------------------------------------------------------------------

		B		$30,UNC
$20:

;;=============================================================================
;; // SHA384_CALC_PART2:
;;
;; wt = SHA384_GETU64(&Ws[s0])
;;-----------------------------------------------------------------------------
;; ACC = s0
		MOVB	AH,#0
		ADDL	ACC,*SP_Ws
		MOVL	XAR0,@ACC
		M_SHA384_GETU64		XAR0,*SP_wt_h32, *SP_wt_l32

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART2: end
;;-----------------------------------------------------------------------------

$30:

;;=============================================================================
;; // SHA384_CALC_PART3:
;;        temp1 = h + temp13 = SHA384_SIG1(e) + temp4 = SHA384_CH(e, f, g) + temp5 = SHA384_K[s] + wt;
;;        temp2 = ACC:P = SHA384_SIGZ(a) + temp7 = SHA384_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;-----------------------------------------------------------------------------
;;
;; #define SHA384_SIG1(x)       (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 14) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 18) ^ temp12 = XAR7:XAR6 = SHA384_ROTR64(x, 41))
;; x = e
;; temp13 = SHA384_SIG1(e)
		MOVL	P,*SP_e_l32				; P   = e_l32
		MOVL	ACC,*SP_e_h32			; ACC = e_h32
		LSR64	ACC:P,#14
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 14
		LSR64	ACC:P,#(18-14)
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 18
		MOV		T,#(41-18)
		LSR64	ACC:P,T
		MOVL	XAR6,@P
		MOVL	XAR7,@ACC				; XAR7:XAR6 = x >> 41
		MOVL	P,*SP_e_l32				; P   = e_l32
		MOVL	ACC,*SP_e_h32			; ACC = e_h32
		MOV		T,#(64-41)
		LSL64	ACC:P,T
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = x << 64 - 41
		MOV		T,#(41-18)
		LSL64	ACC:P,T
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 18
		LSL64	ACC:P,#(18-14)			; ACC:P  = x << 64 - 14
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 14)
		MOVL	P,@XAR2
		MOVL	ACC,@XAR3
		ADDUL	P,@temp11_l32
		ADDL	ACC,@temp11_h32
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = SHA384_ROTR64(x, 18)
		MOVL	P,@XAR6
		MOVL	ACC,@XAR7
		ADDUL	P,@temp12_l32
		ADDL	ACC,@temp12_h32			; ACC:P = SHA384_ROTR64(x, 41)
		XOR		AH,@temp11_w3
		XOR		AL,@temp11_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	*SP_temp13_h32,ACC
		MOVL	ACC,@P
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	*SP_temp13_l32,ACC		; temp13 = SHA384_SIG1(e)

		.global	SHA384_K
		MOV		AL,*SP_s
		LSL		AL,#2
		MOVZ	AR0,@AL
		MOVL	XAR1,#SHA384_K			; XAR1 = &SHA384_K[s]

;; #define SHA384_CH(x, y, z)   (((x) & ((y) ^ (z))) ^ (z))
;;
;; temp4 = SHA384_CH(e, f, g)
;;
;; temp4 = ((f ^ g) & e) ^ g
		MOVL	ACC,*SP_f_l32
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		AND		AL,*SP_e_w0
		AND		AH,*SP_e_w1
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		MOVL	@temp4_l32,ACC

		MOVL	ACC,*SP_f_h32
		XOR		AL,*SP_g_w2
		XOR		AH,*SP_g_w3
		AND		AL,*SP_e_w2
		AND		AH,*SP_e_w3
		XOR		AL,*SP_g_w2
		XOR		AH,*SP_g_w3
		MOVL	@temp4_h32,ACC

;; temp5 = SHA384_K[s]
		MOVL	ACC,*+XAR1[AR0]
		MOVL	@temp5_l32,ACC
		ADDB	XAR0,#2
		MOVL	ACC,*+XAR1[AR0]
		MOVL	@temp5_h32,ACC

;; #define SHA384_MAJ(x, y, z)  ((((y)^(z)) & (x)) ^ ((y) & (z)))
;;
;; temp7 = SHA384_MAJ(a, b, c)
;;
;; temp7 = ((b ^ c) & a) ^ (b & c)
		MOVL	ACC,*SP_b_l32
		XOR		AL,*SP_c_w0
		XOR		AH,*SP_c_w1
		AND		AL,*SP_a_w0
		AND		AH,*SP_a_w1
		MOVL	P,@ACC
		MOVL	ACC,*SP_b_l32
		AND		AL,*SP_c_w0
		AND		AH,*SP_c_w1
		XOR		AL,@PL
		XOR		AH,@PH
		MOVL	@temp7_l32,ACC

		MOVL	ACC,*SP_b_h32
		XOR		AL,*SP_c_w2
		XOR		AH,*SP_c_w3
		AND		AL,*SP_a_w2
		AND		AH,*SP_a_w3
		MOVL	P,@ACC
		MOVL	ACC,*SP_b_h32
		AND		AL,*SP_c_w2
		AND		AH,*SP_c_w3
		XOR		AL,@PL
		XOR		AH,@PH
		MOVL	@temp7_h32,ACC

;; #define SHA384_SIGZ(x)       (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 28) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 34) ^ temp12 = XAR7:XAR6 = SHA384_ROTR64(x, 39))
;; x = a
;; ACC:P = SHA384_SIGZ(a)
		MOVL	P,*SP_a_l32				; P   = a_l32
		MOVL	ACC,*SP_a_h32			; ACC = a_h32
		MOV		T,#28
		LSR64	ACC:P,T
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 28
		LSR64	ACC:P,#(34-28)
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 34
		LSR64	ACC:P,#(39-34)
		MOVL	XAR6,@P
		MOVL	XAR7,@ACC				; XAR7:XAR6 = x >> 39
		MOVL	P,*SP_a_l32				; P   = a_l32
		MOVL	ACC,*SP_a_h32			; ACC = a_h32
		MOV		T,#(64-39)
		LSL64	ACC:P,T
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = x << 64 - 39
		LSL64	ACC:P,#(39-34)
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 34
		LSL64	ACC:P,#(34-28)			; ACC:P  = x << 64 - 28
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 28)
		MOVL	P,@XAR2
		MOVL	ACC,@XAR3
		ADDUL	P,@temp11_l32
		ADDL	ACC,@temp11_h32
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = SHA384_ROTR64(x, 34)
		MOVL	P,@XAR6
		MOVL	ACC,@XAR7
		ADDUL	P,@temp12_l32
		ADDL	ACC,@temp12_h32			; ACC:P = SHA384_ROTR64(x, 39)
		XOR		AH,@temp11_w3
		XOR		AL,@temp11_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	XAR0,ACC
		MOVL	ACC,@P
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	P,@ACC
		MOVL	ACC,@XAR0				; ACC:P = SHA384_SIGZ(a)

;; temp2 = ACC:P = SHA384_SIGZ(a) + temp7 = SHA384_MAJ(a, b, c);
;;
;; XAR3:XAR2 = temp2 = ACC:P + temp7
		ADDUL	P,@temp7_l32
		MOVL	XAR2,@P
		ADDCL	ACC,@temp7_h32
		MOVL	XAR3,@ACC

;; temp1 = h + temp13 = SHA384_SIG1(e) + temp4 = SHA384_CH(e, f, g) + temp5 = SHA384_K[s] + wt;
;;
;; XAR1:XAR0 = temp1 = h + temp13 + temp4 + temp5 + wt
		MOVL	P,@temp4_l32
		MOVL	ACC,@temp4_h32
		ADDUL	P,@temp5_l32
		ADDCL	ACC,@temp5_h32
		ADDUL	P,*SP_h_l32
		ADDCL	ACC,*SP_h_h32
		ADDUL	P,*SP_temp13_l32
		ADDCL	ACC,*SP_temp13_h32
		ADDUL	P,*SP_wt_l32
		ADDCL	ACC,*SP_wt_h32
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC

;; h = g;
;; g = f;
;; f = e;
;; e = d + temp1;
;; d = c;
;; c = b;
;; b = a;
;; a = temp1 + temp2;
		MOVL	ACC,*SP_g_l32
		MOVL	*SP_h_l32,ACC
		MOVL	ACC,*SP_g_h32
		MOVL	*SP_h_h32,ACC			; h = g

		MOVL	ACC,*SP_f_l32
		MOVL	*SP_g_l32,ACC
		MOVL	ACC,*SP_f_h32
		MOVL	*SP_g_h32,ACC			; g = f

		MOVL	ACC,*SP_e_l32
		MOVL	*SP_f_l32,ACC
		MOVL	ACC,*SP_e_h32
		MOVL	*SP_f_h32,ACC			; f = e

		MOVL	P,@XAR0
		MOVL	ACC,@XAR1
		ADDUL	P,*SP_d_l32
		MOVL	*SP_e_l32,P
		ADDCL	ACC,*SP_d_h32
		MOVL	*SP_e_h32,ACC			; e = d + temp1

		MOVL	ACC,*SP_c_l32
		MOVL	*SP_d_l32,ACC
		MOVL	ACC,*SP_c_h32
		MOVL	*SP_d_h32,ACC			; d = c

		MOVL	ACC,*SP_b_l32
		MOVL	*SP_c_l32,ACC
		MOVL	ACC,*SP_b_h32
		MOVL	*SP_c_h32,ACC			; c = b

		MOVL	ACC,*SP_a_l32
		MOVL	*SP_b_l32,ACC
		MOVL	ACC,*SP_a_h32
		MOVL	*SP_b_h32,ACC			; b = a

		MOVL	P,@XAR0
		MOVL	ACC,@XAR1
		ADDUL	P,@XAR2
		ADDCL	ACC,@XAR3
		MOVL	*SP_a_l32,P
		MOVL	*SP_a_h32,ACC			; a = temp1 + temp2

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART3: end
;;-----------------------------------------------------------------------------

		MOVU	ACC,*SP_s			; AL = s, AH = 0
		ADD		AL,#1				; AL = s++
		CMPB	AL,#80				; if(s < 80)?
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
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[0] += uint64_t a;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[1] += uint64_t b;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[2] += uint64_t c;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[3] += uint64_t d;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[4] += uint64_t e;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[5] += uint64_t f;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[6] += uint64_t g;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[7] += uint64_t h;

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
;;// SHA-384 process a block of data
;;// Input message : Word-wise
;;//
;;//*****************************************************************************
;;void SHA384_processBlockWordWise_casm_c28(uint64_t digest[8], uint64_t Ws[16])
;;{
;;    uint64_t wt;             // Wt from standard
;;    int16_t s;               // s is the message schedule index
;;    uint64_t temp1;          // T1 from standard
;;    uint64_t temp2;          // T2 from standard
;;
;;    //
;;    // Initialize working variables
;;    //
;;    uint64_t a = digest[0];
;;    uint64_t b = digest[1];
;;    uint64_t c = digest[2];
;;    uint64_t d = digest[3];
;;    uint64_t e = digest[4];
;;    uint64_t f = digest[5];
;;    uint64_t g = digest[6];
;;    uint64_t h = digest[7];
;;
;;    //
;;    // Perform 80 rounds of compression function
;;    //
;;    for(s = 0; s < 80; s++)
;;    {
;;        if(s >= 16)
;;        {
;;           Ws[s & 0xF] += SHA384_SIGMA1(Ws[(s + 14) & 0xF]) +
;;                           Ws[(s + 9) & 0xF] +
;;                           SHA384_SIGMAZ(Ws[(s + 1) & 0xF]);
;;        }
;;        else
;;        {
;;            Ws[s] = ((uint64_t)(Ws[s] << 32) | (uint64_t)(Ws[s] >> 32));
;;        }
;;
;;        wt = Ws[s & 0xF];
;;        temp1 = h + SHA384_SIG1(e) + SHA384_CH(e, f, g) + SHA384_K[s] + wt;
;;        temp2 = SHA384_SIGZ(a) + SHA384_MAJ(a, b, c);
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
;;//*****************************************************************************

;;void SHA384_processBlockWordWise(uint64_t digest[8], uint64_t Ws[16])
;;{
;;    uint64_t wt;             // Wt from standard
;;    int16_t s;               // s is the message schedule index
;;    uint64_t temp1;          // T1 from standard
;;    uint64_t temp2;          // T2 from standard
;;
;; On Entry:
;;   XAR4 => digest[0]  uint64_t
;;   XAR5 => Ws[0]      uint64_t
;;
;;		.sect		.text
		.sect		".TI.ramfunc"  ; Call this line to execute from RAM
		.global		_SHA384_processBlockWordWise_casm_C28
_SHA384_processBlockWordWise_casm_C28:
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
;;    uint64_t a = digest[0];
;;    uint64_t b = digest[1];
;;    uint64_t c = digest[2];
;;    uint64_t d = digest[3];
;;    uint64_t e = digest[4];
;;    uint64_t f = digest[5];
;;    uint64_t g = digest[6];
;;    uint64_t h = digest[7];
		MOVL	XAR7,*SP_digest		; XAR7 => digest[0]
		MOVZ	AR6,@SP
		SUBB	XAR6,#SP_a_offset	; XAR6 => a
		MOVL	ACC,*XAR7++			; uint64_t a = digest[0];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t b = digest[1];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t c = digest[2];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t d = digest[3];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t e = digest[4];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t f = digest[5];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t g = digest[6];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++			; uint64_t h = digest[7];
		MOVL	*XAR6++,ACC
		MOVL	ACC,*XAR7++
		MOVL	*XAR6++,ACC

;;    //
;;    // Perform 80 rounds of compression function
;;    //
;;    for(s = 0; s < 80; s++)
;;    {
;;        if(s >= 16)
;;        {
;;
;; // SHA384_CALC_PART1:
;;           Ws[s & 0xF] += SHA384_SIGMA1(Ws[(s + 14) & 0xF]) +
;;                           Ws[(s + 9) & 0xF] +
;;                           SHA384_SIGMAZ(Ws[(s + 1) & 0xF]);
;;        }
;;        else
;;        {
;; // SHA384_CALC_PART2:
;;            Ws[s] = ((uint64_t)(Ws[s] << 32) | (uint64_t)(Ws[s] >> 32));
;;        }
;;
;; // SHA384_CALC_PART3:
;;        wt = Ws[s & 0xF];
;;        temp1 = h + SHA384_SIG1(e) + SHA384_CH(e, f, g) + SHA384_K[s] + wt;
;;        temp2 = SHA384_SIGZ(a) + SHA384_MAJ(a, b, c);
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
		LSL		ACC,#2
		ADDL	ACC,*SP_Ws
		MOVL	XAR5,@ACC			; XAR5 => Ws[s & 0xF]
		MOV		AL,*SP_s			; AL = s
		CMPB	AL,#16				; if(s >= 16)?
		B		WORD_$20,LT

;;=============================================================================
;; // SHA384_CALC_PART1:
;;-----------------------------------------------------------------------------
;;           Ws[s & 0xF] += XAR7:XAR6 = SHA384_SIGMA1(temp3 = Ws[(s + 14) & 0xF]) +
;;                          temp5     = Ws[(s + 9) & 0xF] +
;;                          XAR3:XAR2 = SHA384_SIGMAZ(temp6 = Ws[(s + 1) & 0xF]);
;;-----------------------------------------------------------------------------

		; temp 3 = Ws[(s + 14) & 0xF]
		MOVU	ACC,*SP_s
		ADDB	ACC,#14
		AND		ACC,#0x000F
		LSL		ACC,#2
		ADDL	ACC,*SP_Ws
		MOVL	XAR0,@ACC

		;temp5   = Ws[(s + 9) & 0xF]
		MOVU	ACC,*SP_s
		ADDB	ACC,#9
		AND		ACC,#0x000F
		LSL		ACC,#2
		ADDL	ACC,*SP_Ws
		MOVL	XAR1,@ACC

		; temp6 = Ws[(s + 1) & 0xF]
		MOVU	ACC,*SP_s
		ADDB	ACC,#1
		AND		ACC,#0x000F
		LSL		ACC,#2
		ADDL	ACC,*SP_Ws
		MOVL	XAR2,@ACC

		MOVL	P,*XAR1++
		MOVL	ACC,*XAR1
		MOVL	@temp5_l32,P
		MOVL	@temp5_h32,ACC

		MOVL	P,*XAR2++
		MOVL	ACC,*XAR2
		MOVL	@temp6_l32,P
		MOVL	@temp6_h32,ACC

		MOVL	P,*XAR0++
		MOVL	ACC,*XAR0
		MOVL	@temp3_l32,P
		MOVL	@temp3_h32,ACC

;; XAR7:XAR6 = SHA384_SIGMA1(temp3 = Ws[(s + 14) & 0xF])
;;
;; x = temp3
;; #define SHA384_SIGMA1(x)     (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 19) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 61) ^ temp12 = SHA384_SHR(x, 6))
;;
		; P   = temp3_l32
		; ACC = temp3_h32
		LSR64	ACC:P,#6
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = SHA384_SHR(x, 6)
		LSR64	ACC:P,#(19-6)
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 19
		MOV		T,#(61-19)
		LSR64	ACC:P,T
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 61
		MOVL	P,@temp3_l32			; P   = temp3_l32
		MOVL	ACC,@temp3_h32			; ACC = temp3_h32
		LSL64	ACC:P,#(64-61)
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 61
		MOV		T,#(61-19)
		LSL64	ACC:P,T					; ACC:P = x << 64 - 19
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 19)
		MOVL	P,@temp11_l32
		MOVL	ACC,@temp11_h32
		ADDUL	P,@XAR2
		ADDL	ACC,@XAR3				; ACC:P = SHA384_ROTR64(x, 61)
		XOR		AH,@temp12_w3
		XOR		AL,@temp12_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	XAR7,@ACC
		MOVL	ACC,@P
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	XAR6,@ACC				; XAR7:XAR6 = SHA384_SIGMA1(temp3 = SHA384_GETU64(&Ws[(s0 + 112) & 0x7F]))

;; XAR3:XAR2 = SHA384_SIGMAZ(temp6 = Ws[(s + 1) & 0xF])
;;
;; x = temp6
;; #define SHA384_SIGMAZ(x)     (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 1) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 8) ^ temp12 = SHA384_SHR(x, 7))
;;
		MOVL	P,@temp6_l32			; P   = temp3_l32
		MOVL	ACC,@temp6_h32			; ACC = temp3_h32
		LSR64	ACC:P,#1
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 1
		LSR64	ACC:P,#(7-1)
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = SHA384_SHR(x, 7)
		LSR64	ACC:P,#(8-7)
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 8
		MOVL	P,@temp6_l32			; P   = temp3_l32
		MOVL	ACC,@temp6_h32			; ACC = temp3_h32
		MOV		T,#(64-8)
		LSL64	ACC:P,T
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 8
		LSL64	ACC:P,#(8-1)			; ACC:P = x << 64 - 1
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 1)
		MOVL	P,@temp11_l32
		MOVL	ACC,@temp11_h32
		ADDUL	P,@XAR2
		ADDL	ACC,@XAR3				; ACC:P = SHA384_ROTR64(x, 8)
		XOR		AH,@temp12_w3
		XOR		AL,@temp12_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	@XAR3,ACC
		MOVL	ACC,@P
		XOR		AH,@temp12_w1
		XOR		AL,@temp12_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	@XAR2,ACC				; XAR3:XAR2 = SHA384_SIGMAZ(temp6 = SHA384_GETU64(&Ws[(s0 + 8) & 0x7F]))

;; Ws[s & 0xF] += XAR7:XAR6 + temp5 + XAR3:XAR2
		MOVL	P,@XAR6
		MOVL	ACC,@XAR7
		ADDUL	P,@temp5_l32
		ADDCL	ACC,@temp5_h32
		ADDUL	P,@XAR2
		ADDCL	ACC,@XAR3
		ADDUL	P,*XAR5
		ADDCL	ACC,*+XAR5[2]
		MOVL	*XAR5,P
		MOVL	*+XAR5[2],ACC

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART1: end
;;-----------------------------------------------------------------------------

		B		WORD_$30,UNC
WORD_$20:

;;=============================================================================
;; // SHA384_CALC_PART2:
;;-----------------------------------------------------------------------------
;;            Ws[s] = ((uint64_t)(Ws[s] << 32) | (uint64_t)(Ws[s] >> 32));
;;-----------------------------------------------------------------------------
		; XAR0 => Ws[s]
		MOVL	ACC,*XAR5		; ACC   = (uint64_t)(Ws[s] << 32)
		MOVL	P,*+XAR5[2]		; P     = (uint64_t)(Ws[s] >> 32)
		MOVL	*XAR5,P
		MOVL	*+XAR5[2],ACC	; Ws[s] = ((uint64_t)(Ws[s] << 32) | (uint64_t)(Ws[s] >> 32))

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART2: end
;;-----------------------------------------------------------------------------

WORD_$30:

;;=============================================================================
;; // SHA384_CALC_PART3:
;;-----------------------------------------------------------------------------
;;        wt = Ws[s & 0xF];
;;        temp1 = h + temp13 = SHA384_SIG1(e) + temp4 = SHA384_CH(e, f, g) + temp5 = SHA384_K[s] + wt;
;;        temp2 = ACC:P = SHA384_SIGZ(a) + temp7 = SHA384_MAJ(a, b, c);
;;
;;        h = g;
;;        g = f;
;;        f = e;
;;        e = d + temp1;
;;        d = c;
;;        c = b;
;;        b = a;
;;        a = temp1 + temp2;
;;-----------------------------------------------------------------------------
;;
;; #define SHA384_SIG1(x)       (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 14) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 18) ^ temp12 = XAR7:XAR6 = SHA384_ROTR64(x, 41))
;; x = e
;; temp13 = SHA384_SIG1(e)
		MOVL	P,*SP_e_l32				; P   = e_l32
		MOVL	ACC,*SP_e_h32			; ACC = e_h32
		LSR64	ACC:P,#14
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 14
		LSR64	ACC:P,#(18-14)
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 18
		MOV		T,#(41-18)
		LSR64	ACC:P,T
		MOVL	XAR6,@P
		MOVL	XAR7,@ACC				; XAR7:XAR6 = x >> 41
		MOVL	P,*SP_e_l32				; P   = e_l32
		MOVL	ACC,*SP_e_h32			; ACC = e_h32
		MOV		T,#(64-41)
		LSL64	ACC:P,T
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = x << 64 - 41
		MOV		T,#(41-18)
		LSL64	ACC:P,T
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 18
		LSL64	ACC:P,#(18-14)			; ACC:P  = x << 64 - 14
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 14)
		MOVL	P,@XAR2
		MOVL	ACC,@XAR3
		ADDUL	P,@temp11_l32
		ADDL	ACC,@temp11_h32
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = SHA384_ROTR64(x, 18)
		MOVL	P,@XAR6
		MOVL	ACC,@XAR7
		ADDUL	P,@temp12_l32
		ADDL	ACC,@temp12_h32			; ACC:P = SHA384_ROTR64(x, 41)
		XOR		AH,@temp11_w3
		XOR		AL,@temp11_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	*SP_temp13_h32,ACC
		MOVL	ACC,@P
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	*SP_temp13_l32,ACC		; temp13 = SHA384_SIG1(e)

		.global	SHA384_K
		MOV		AL,*SP_s
		LSL		AL,#2
		MOVZ	AR0,@AL
		MOVL	XAR1,#SHA384_K			; XAR1 = &SHA384_K[s]

;; #define SHA384_CH(x, y, z)   (((x) & ((y) ^ (z))) ^ (z))
;;
;; temp4 = SHA384_CH(e, f, g)
;;
;; temp4 = ((f ^ g) & e) ^ g
		MOVL	ACC,*SP_f_l32
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		AND		AL,*SP_e_w0
		AND		AH,*SP_e_w1
		XOR		AL,*SP_g_w0
		XOR		AH,*SP_g_w1
		MOVL	@temp4_l32,ACC

		MOVL	ACC,*SP_f_h32
		XOR		AL,*SP_g_w2
		XOR		AH,*SP_g_w3
		AND		AL,*SP_e_w2
		AND		AH,*SP_e_w3
		XOR		AL,*SP_g_w2
		XOR		AH,*SP_g_w3
		MOVL	@temp4_h32,ACC

;; temp5 = SHA384_K[s]
		MOVL	ACC,*+XAR1[AR0]
		MOVL	@temp5_l32,ACC
		ADDB	XAR0,#2
		MOVL	ACC,*+XAR1[AR0]
		MOVL	@temp5_h32,ACC

;; #define SHA384_MAJ(x, y, z)  ((((y)^(z)) & (x)) ^ ((y) & (z)))
;;
;; temp7 = SHA384_MAJ(a, b, c)
;;
;; temp7 = ((b ^ c) & a) ^ (b & c)
		MOVL	ACC,*SP_b_l32
		XOR		AL,*SP_c_w0
		XOR		AH,*SP_c_w1
		AND		AL,*SP_a_w0
		AND		AH,*SP_a_w1
		MOVL	P,@ACC
		MOVL	ACC,*SP_b_l32
		AND		AL,*SP_c_w0
		AND		AH,*SP_c_w1
		XOR		AL,@PL
		XOR		AH,@PH
		MOVL	@temp7_l32,ACC

		MOVL	ACC,*SP_b_h32
		XOR		AL,*SP_c_w2
		XOR		AH,*SP_c_w3
		AND		AL,*SP_a_w2
		AND		AH,*SP_a_w3
		MOVL	P,@ACC
		MOVL	ACC,*SP_b_h32
		AND		AL,*SP_c_w2
		AND		AH,*SP_c_w3
		XOR		AL,@PL
		XOR		AH,@PH
		MOVL	@temp7_h32,ACC

;; #define SHA384_SIGZ(x)       (temp10 = XAR1:XAR0 = SHA384_ROTR64(x, 28) ^ temp11 = XAR3:XAR2 = SHA384_ROTR64(x, 34) ^ temp12 = XAR7:XAR6 = SHA384_ROTR64(x, 39))
;; x = a
;; ACC:P = SHA384_SIGZ(a)
		MOVL	P,*SP_a_l32				; P   = a_l32
		MOVL	ACC,*SP_a_h32			; ACC = a_h32
		MOV		T,#28
		LSR64	ACC:P,T
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC				; XAR1:XAR0 = x >> 28
		LSR64	ACC:P,#(34-28)
		MOVL	XAR2,@P
		MOVL	XAR3,@ACC				; XAR3:XAR2 = x >> 34
		LSR64	ACC:P,#(39-34)
		MOVL	XAR6,@P
		MOVL	XAR7,@ACC				; XAR7:XAR6 = x >> 39
		MOVL	P,*SP_a_l32				; P   = a_l32
		MOVL	ACC,*SP_a_h32			; ACC = a_h32
		MOV		T,#(64-39)
		LSL64	ACC:P,T
		MOVL	@temp12_l32,P
		MOVL	@temp12_h32,ACC			; temp12 = x << 64 - 39
		LSL64	ACC:P,#(39-34)
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = x << 64 - 34
		LSL64	ACC:P,#(34-28)			; ACC:P  = x << 64 - 28
		ADDUL	P,@XAR0
		ADDL	ACC,@XAR1
		MOVL	@temp10_l32,P
		MOVL	@temp10_h32,ACC			; temp10 = SHA384_ROTR64(x, 28)
		MOVL	P,@XAR2
		MOVL	ACC,@XAR3
		ADDUL	P,@temp11_l32
		ADDL	ACC,@temp11_h32
		MOVL	@temp11_l32,P
		MOVL	@temp11_h32,ACC			; temp11 = SHA384_ROTR64(x, 34)
		MOVL	P,@XAR6
		MOVL	ACC,@XAR7
		ADDUL	P,@temp12_l32
		ADDL	ACC,@temp12_h32			; ACC:P = SHA384_ROTR64(x, 39)
		XOR		AH,@temp11_w3
		XOR		AL,@temp11_w2
		XOR		AH,@temp10_w3
		XOR		AL,@temp10_w2
		MOVL	XAR0,ACC
		MOVL	ACC,@P
		XOR		AH,@temp11_w1
		XOR		AL,@temp11_w0
		XOR		AH,@temp10_w1
		XOR		AL,@temp10_w0
		MOVL	P,@ACC
		MOVL	ACC,@XAR0				; ACC:P = SHA384_SIGZ(a)

;; temp2 = ACC:P = SHA384_SIGZ(a) + temp7 = SHA384_MAJ(a, b, c);
;;
;; XAR3:XAR2 = temp2 = ACC:P + temp7
		ADDUL	P,@temp7_l32
		MOVL	XAR2,@P
		ADDCL	ACC,@temp7_h32
		MOVL	XAR3,@ACC

;; wt = Ws[s & 0xF];
;; temp1 = h + temp13 = SHA384_SIG1(e) + temp4 = SHA384_CH(e, f, g) + temp5 = SHA384_K[s] + wt;
;;
;; XAR1:XAR0 = temp1 = h + temp13 + temp4 + temp5 + wt
		MOVL	P,@temp4_l32
		MOVL	ACC,@temp4_h32
		ADDUL	P,@temp5_l32
		ADDCL	ACC,@temp5_h32
		ADDUL	P,*SP_h_l32
		ADDCL	ACC,*SP_h_h32
		ADDUL	P,*SP_temp13_l32
		ADDCL	ACC,*SP_temp13_h32
		ADDUL	P,*XAR5				; wt_l32 = Ws[s & 0xF]_l32
		ADDCL	ACC,*+XAR5[2]		; wt_h32 = Ws[s & 0xF]_h32
		MOVL	XAR0,@P
		MOVL	XAR1,@ACC

;; h = g;
;; g = f;
;; f = e;
;; e = d + temp1;
;; d = c;
;; c = b;
;; b = a;
;; a = temp1 + temp2;
		MOVL	ACC,*SP_g_l32
		MOVL	*SP_h_l32,ACC
		MOVL	ACC,*SP_g_h32
		MOVL	*SP_h_h32,ACC			; h = g

		MOVL	ACC,*SP_f_l32
		MOVL	*SP_g_l32,ACC
		MOVL	ACC,*SP_f_h32
		MOVL	*SP_g_h32,ACC			; g = f

		MOVL	ACC,*SP_e_l32
		MOVL	*SP_f_l32,ACC
		MOVL	ACC,*SP_e_h32
		MOVL	*SP_f_h32,ACC			; f = e

		MOVL	P,@XAR0
		MOVL	ACC,@XAR1
		ADDUL	P,*SP_d_l32
		MOVL	*SP_e_l32,P
		ADDCL	ACC,*SP_d_h32
		MOVL	*SP_e_h32,ACC			; e = d + temp1

		MOVL	ACC,*SP_c_l32
		MOVL	*SP_d_l32,ACC
		MOVL	ACC,*SP_c_h32
		MOVL	*SP_d_h32,ACC			; d = c

		MOVL	ACC,*SP_b_l32
		MOVL	*SP_c_l32,ACC
		MOVL	ACC,*SP_b_h32
		MOVL	*SP_c_h32,ACC			; c = b

		MOVL	ACC,*SP_a_l32
		MOVL	*SP_b_l32,ACC
		MOVL	ACC,*SP_a_h32
		MOVL	*SP_b_h32,ACC			; b = a

		MOVL	P,@XAR0
		MOVL	ACC,@XAR1
		ADDUL	P,@XAR2
		ADDCL	ACC,@XAR3
		MOVL	*SP_a_l32,P
		MOVL	*SP_a_h32,ACC			; a = temp1 + temp2

;;-----------------------------------------------------------------------------
;; // SHA384_CALC_PART3: end
;;-----------------------------------------------------------------------------

		MOVU	ACC,*SP_s			; AL = s, AH = 0
		ADD		AL,#1				; AL = s++
		CMPB	AL,#80				; if(s < 80)?
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
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[0] += uint64_t a;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[1] += uint64_t b;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[2] += uint64_t c;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[3] += uint64_t d;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[4] += uint64_t e;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[5] += uint64_t f;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[6] += uint64_t g;

		MOVL	P,*XAR7
		MOVL	ACC,*+XAR7[2]
		ADDUL	P,*XAR6++
		ADDCL	ACC,*XAR6++
		MOVL	*XAR7++,P
		MOVL	*XAR7++,ACC			; digest[7] += uint64_t h;

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
