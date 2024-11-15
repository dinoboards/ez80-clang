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
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__sshrs

__sshrs:
; Suboptimal for large shift amounts
; CC: if C!=0: C*(7*r(PC)+1)+7*r(PC)+(ADL?6*r(SPL)+3*w(SPL):4*r(SPS)+2*w(SPS))+1
;     if C==0: 4*r(PC)+(ADL?3*r(SPL):2*r(SPS))+2
	inc	c
	dec	c
	ret	z
	push	bc
	ld	b, c
.loop:
	sra	h
	rr	l
	djnz	.loop
	pop	bc
	ret
