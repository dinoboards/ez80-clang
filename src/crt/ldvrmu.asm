	.assume	adl=1

	section	.text,"ax",@progbits
	;;; struct u32div_t {
;;;     uint32_t rem;
;;;     uint32_t quot;
;;; };
;;; u32div_t _ldvrmu(uint32_t dividend, uint32_t divisor) {
	.global	__ldvrmu

__ldvrmu:
; I: EUHL=dividend, AUBC=divisor
; O: a[uhl']=EUHL%AUBC, bcu=0, b=A, c=?, euhl=EUHL/AUBC, eubc'=AUBC, zf=!IEF2

;;;     u32div_t result;
;;;     result.quot = dividend;
					; euhl : result.quot

	push	bc

	ld	c, a			; c = A
	ld	a, i			; a = I
					; pf = IEF2
	di

	ld	a, c			; a = A
	exx
	pop	bc
	ld	e, a			; eubc' : divisor

	push	af

;;;     result.rem = 0;
	xor	a, a
	sbc	hl, hl			; auhl' : result.rem

;;;     int i = 32;
	exx
	ld	b, 32			; b : i

;;;     do {
.loop:

;;;         bool dividendBit = result.quot >> 31;
;;;         result.quot <<= 1;
	add	hl, hl
	rl	e
;;;         result.rem = (result.rem << 1) + dividendBit;
	exx
	adc	hl, hl
	adc	a, a

;;;         bool quotBit = result.rem >= divisor;
;;;         result.rem -= divisor;
	sbc	hl, bc
	sbc	a, e

;;;         if (!quotBit) {
	jr	nc, .restore_skip
;;;             result.rem += divisor;
	add	hl, bc
	adc	a, e
;;;         }
.restore_skip:

;;;         if (quotBit) {
	exx
	jr	c, .1_skip
;;;             result.quot++;
	inc	l
;;;         }
.1_skip:

;;;     } while (--i != 0);
	djnz	.loop

;;;     return result;
	pop	bc
	bit	2, c
	ret
;;; }

