
	.global	cpm_bdos_adl

;//must point to a function in the 64k seg
;//that
; cpm_bdos_z80:
; 	call	BDOS
; 	RET.L

; 	.assume	adl=1
; 	section	.text, "ax", @progbits
; 	.global	cpm_bdos_adl

; cpm_bdos_adl:
; 	CALL.sis cpm_bdos_z80 & 0xFFFF
; 	RET


cpm_bdos_adl	equ	0x200005
