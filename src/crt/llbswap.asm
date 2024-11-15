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
	.global	__llbswap
__llbswap:
	push	af
	ld	a, b			; a = b
	ld	b, l			; bcudeuhl = lc[deu]de[hlu]hl
	ld	l, d			; bcudeuhl = lc[deu]de[hlu]hd
	ld	d, c			; bcudeuhl = lc[deu]ce[hlu]hd
	ld	c, h			; bcudeuhl = lh[deu]ce[hlu]hd
	ld	h, e			; bcudeuhl = lh[deu]ce[hlu]ed
	ld	e, a			; bcudeuhl = lh[deu]cb[hlu]ed
	ex	de, hl			; bcudeuhl = lh[hlu]ed[deu]cb
	pop	af
	ret
