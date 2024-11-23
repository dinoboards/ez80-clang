	include	"src/cpm/cpm.inc"

	.assume	adl=1

	.section	.text, "ax", @progbits
	.global	cpm_f_status_03
	.global	cpm_f_status_00
	.extern	cpm_bdos_adl

	; expect bdos to return A=0 to 3 for success,
	; A=FF, error and H is the additional error code
cpm_f_status_03:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	call	cpm_bdos_adl

	; IF A >=0 && A <= 3 THEN, NO ERROR
	; hardware error code may be in H

	and	$FC
	jr	z, .no_error

.extended_error:
	ld	a, 128
	add	a, h
	cp	128
	jr	z, .general_error

.no_error:
	pop	ix
	ret

.general_error:
	ld	a, 255
	jr	.no_error

	; expect bdos to return A=0 to 3 for success,
	; non-zero maps to an error code
	; A=FF, error and H is the additional error code
cpm_f_status_00:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	call	cpm_bdos_adl

	; a equals error code between 0 OK, between 1 and 11 or 255
	cp	255
	jr	z, .extended_error

	; a equals OK or error code between 1 and 11
	; so return with that value
	jr	.no_error



