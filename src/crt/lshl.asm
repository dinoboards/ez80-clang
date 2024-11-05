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

	section	.text,"ax",@progbits
	.global	__lshl

__lshl:
; Suboptimal for large shift amounts
; CC: if L!=0: L*(5*r(PC)+1)+9*r(PC)+(ADL?12*r(SPL)+9*w(SPL):8*r(SPS)+6*w(SPS))+1
;     if L==0: 4*r(PC)+(ADL?3*r(SPL):2*r(SPS))+2
	inc	l
	dec	l
	ret	z
	push	bc
	ld	b, l
	ex	(sp), hl
.loop:
	add	hl, hl
	rla
	djnz	.loop
	ex	(sp), hl
	pop	bc
	ret
