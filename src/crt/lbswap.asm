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
	.global	__lbswap
__lbswap:
	push	hl			; ...[hlu]hl <- (sp)
	inc	sp			; ...[hlu]h <- (sp)
	ld	h, e			; uhl = [hlu]el
	push	hl			; ...[hlu]h[hlu]el <- (sp)
	inc	sp			; ...[hlu]h[hlu]e <- (sp)
	ld	e, l
	pop	hl			; euhl = lh[hlu]e
					; ...[hlu] <- (sp)
	inc	sp			; ... <- (sp)
	ret
