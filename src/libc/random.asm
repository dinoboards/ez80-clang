;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;
;  Original file source: https://github.com/CE-Programming/toolchain
;  License: https://github.com/CE-Programming/toolchain?tab=LGPL-3.0-1-ov-file
;
; Modified to comply with GNU AS assembler (ez80-none-elf-as) syntax
;
;--------------------------------------------------------------

; ---
; uint32_t random(void)
; ---
	.assume	adl=1

; https://github.com/MersenneTwister-Lab/XSadd/blob/master/xsadd.h#L75
; using shift parameters (19, 21, 8) instead of (15, 18, 11)

; uint32_t xsadd(uint32_t state[static 4])
; {
;	uint32_t s0, s1, s2, t0, t1, t2, t3, z, result;
;	t0 = state[0];
;	state[0] = state[1]; state[1] = state[2]; state[2] = state[3];
;	s0 = t0 << 19;
;	t1 = t0 ^ s0;
;	s1 = t1 >> 21;
;	t2 = t1 ^ s1;
;	z = state[3];
;	s2 = z << 8;
;	t3 = t2 ^ s2;
;	state[3] = t3;
;	result = t3 + state[2];
;	return result;
; }

	section	.text,"ax",@progbits
	.global	_random
_random:
; Read state[0] and perform state shifting.
	ld	iy,__state		; iy = &state[0]
	ld	hl,(iy+0*4+0)		; hl = hl(state[0])
	push	hl
	ld	hl,(iy+0*4+2)		; hl = eu(state[0])
	push	hl
	lea	hl,iy+1*4		; hl = &state[1]
	lea	de,iy+0*4		; de = &state[0]
	ld	bc,3*4
	ldir				; state[0] = state[1]
					; state[1] = state[2]
					; state[2] = state[3]
	pop	bc
	pop	de			; bcde = state[0] == t0
;
; s0 = t0 << 19 ==> s0h == 0  ==> t1h = t0h
;		    s0l == 0  ==> t1l = t0l
;
; s1 = t1 >> 21 ==> s1e == 0  ==> t2e = t1e
;		    s1u == 0  ==> t2u = t1u
;
; s2 = z << 8   ==> s2e == zu ==> t3e == t2e ^ s2e == t1e ^ s2e == t0e ^ s0e ^ s2e
;		    s2u == zh ==> t3u == t2u ^ s2u == t1u ^ s2u == t0u ^ s0u ^ s2u
;		    s2h == zl ==> t3h == t2h ^ s2h == t1h ^ s1h ^ s2h == t0h ^ s1h ^ s2h
;		    s2l == 0  ==> t3l == t2l == t1l ^ s1l == t0l ^ s1l
;
; Calculate s0.
	ld	h,d
	ld	l,e			; hl = t0hl == t0 << 16
	add	hl,hl
	add	hl,hl
	add	hl,hl			; hl = t0 << 19 = s0eu
					; h = s0e
					; l = s0u
; Calculate t1e and t3e.
	ld	a,b			; a = t0e
	xor	a,h			; a = t0e ^ s0e == t1e
	ld	h,a			; h = t1e
	xor	a,(iy+3*4+2)		; a = t1e ^ zu == t2e ^ s2e == t3e
	ld	(iy+3*4+3),a		; e(state[3]) = t3e
	ld	b,a			; b = t3e
; Calculate t1u and t3u.
	ld	a,c			; a = t0u
	xor	a,l			; a = t0u ^ s0u == t1u
	ld	l,a			; l = t1u
					; hl = t1eu == t1 >> 16
	xor	a,(iy+3*4+1)		; a = t1u ^ zh == t2u ^ s2u == t3u
	ld	(iy+3*4+2),a		; u(state[3]) = t3u
; Calculate s1.
	xor	a,a			; a = 0
	add.s	hl,hl
	adc	a,a
	add.s	hl,hl
	adc	a,a
	add.s	hl,hl
	adc	a,a			; ahl = (t1 >> 16) << 3
					; ah = ((t1 >> 16) << 3) >> 8 == t1 >> 21 == s1hl
					; a = s1h
					; h = s1l
; Calculate t3h.
	xor	a,d			; a = s1h ^ t0h === s1h ^ t1h == t2h
	xor	a,(iy+3*4+0)		; a = t2h ^ zl == t2h ^ s2h == t3h
	ld	(iy+3*4+1),a		; h(state[3]) = t3h
; Calculate t3l.
	ld	a,e			; a = t0l == t1l
	xor	a,h			; a = t1l ^ s1l == t2l == t3l
	ld	(iy+3*4+0),a		; l(state[3]) = t3l
; Calculate result.
	ld	hl,(iy+3*4)
	ld	a,b			; auhl = t3
	ld	de,(iy+2*4)
	ld	c,(iy+2*4+3)		; cude = state[2]
	add	hl,de
	adc	a,c			; auhl = t3 + state[2] = result
	ld	e,a			; euhl = result
	ret

; ---
; void srandom(uint32_t seed)
; ---

	section	.text,"ax",@progbits
	.global	_srandom
_srandom:
	pop	bc
	pop	de
	ex	(sp),hl			; lude = seed
	push	de
	push	bc
	ex	de,hl
	ld	a,e			; auhl = seed
	.global	__setstate
__setstate:
	ld	(__state),hl
	ld	hl,__state+3
	ld	(hl),a
	ld	b,12
__setstateloop:
	inc	hl
	ld	(hl),b
	djnz	__setstateloop
	ret

	section	.data,"aw",@progbits
	.global	__state
__state:
	d32	0d0e0f10h,090a0b0ch,05060708h,01020304h
