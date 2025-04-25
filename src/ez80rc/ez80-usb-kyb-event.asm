
	.assume	adl=1

	section	.text, "ax", @progbits

KEYBOARD_BUFFER_SIZE_MASK      EQU     15
KEYBOARD_BUFFER_SIZE           EQU     16

	.global	_ez80_usb_kyb_event

;  static void _usb_kyb_put_up(uint8_t key_code)
__usb_kyb_put_up:
       ld      iy, 0
       add     iy, sp

       ; if (key_code == 0)
       ;   return;
       ld      a, (iy+3)
       or      a
       ret     z

       ld      e, a

       ; uint8_t next_write_index = (write_index + 1) & KEYBOARD_BUFFER_SIZE_MASK
       ld      a, (_write_index)
       ld      b, a
       inc     a
       and     a, KEYBOARD_BUFFER_SIZE_MASK
       ld      d, a

       ; if (next_write_index == read_index)
       ;   return
       ld      a, (_read_index)
       ld      c, a
       ld      a, d
       cp      c
       ret     z

       ; hl = &buffer[write_index]
       or      a, a
       sbc     hl, hl
       ld      l, b
       add     hl, hl
       ld      bc, _buffer
       add     hl, bc

       ; buffer[write_index].key_code = key_code
       ld      (hl), e

       ; buffer[write_index].key_down = false
       inc     hl
       ld      (hl), 0
       ld      a, d
       ld      (_write_index), a

       ret

;	static void _usb_kyb_put_down(uint8_t key_code)
__usb_kyb_put_down:
	ld	iy, 0
	add	iy, sp

	; if (key_code == 0)
	;	return;
	ld	a, (iy+3)
	or	a
	ret	z

	ld	e, a

	; uint8_t next_write_index = (write_index + 1) & KEYBOARD_BUFFER_SIZE_MASK
	ld	a, (_write_index)
	ld	b, a
	inc	a
	and	a, KEYBOARD_BUFFER_SIZE_MASK
	ld	d, a

	; if (next_write_index == read_index)
	;	return
	ld	a, (_read_index)
	ld	c, a
	ld	a, d
	cp	c
	ret	z

	; hl = &buffer[write_index]
	or	a, a
	sbc	hl, hl
	ld	l, b
	add	hl, hl
	ld	bc, _buffer
	add	hl, bc

	; buffer[write_index].key_code = key_code
	ld	(hl), e

	; buffer[write_index].key_down = true
	inc	hl
	ld	(hl), 1
	ld	a, d
	ld	(_write_index), a

	ret

; extern void inject_modified_bits();
_inject_modified_bits:
	push	ix
	ld	iy, _previous_report
	ld	ix, _report

	ld	l, $E0
	ld	e, (iy+0)
	ld	d, (ix+0)
.loop1:
	rrc	e				; previous bit
	jr	c, .previous_mod_bit_set

.previous_mod_bit_not_set:
	rrc	d				; test current bit
	jr	nc, .skip			; previous 0 current 0

	; previous 0, current 1
	push	hl
	exx
	call	__usb_kyb_put_down
	exx
	pop	hl
	jr	.skip

.previous_mod_bit_set:
	rrc	d				; test current bit
	jr	c, .skip			; previous 1 current 1

	; previous 1, current 0
	push	hl
	exx
	call	__usb_kyb_put_up
	exx
	pop	hl

.skip:
	inc	l
	ld	a, $E8
	cp	l
	jr	nz, .loop1

	pop	ix
	ret

; void inject_codes()
_inject_codes:
	ld	b, 6

	ld	hl, _previous_report+2
	ld	de, _report+2
.loop2:
	ld	a, (de)
	cp	(hl)
	jr	z, .next

	ld	c, (hl)
	push	bc
	exx
	ex	af, af'
	call	__usb_kyb_put_up
	ex	af, af'
	exx
	pop	bc

	or	a
	jr	z, .next

	ld	c, a
	push	bc
	exx
	call	__usb_kyb_put_down
	exx
	pop	bc

.next:
	inc	hl
	inc	de
	djnz	.loop2

	ret

_inject:
	; uint16_t r = ez80_usb_kyb_report(&report);
	ld	hl, _report
	push	hl
	call	_ez80_usb_kyb_report
	pop	de

	; if (a == 0) return
	or	a
	ret	z

	call	_inject_modified_bits
	call	_inject_codes

	ld	de, _previous_report
	ld	hl, _report
	ld	bc, 8	; sizeof(usb_keyboard_report_t)
	ldir

	ret

_ez80_usb_kyb_event:
	push	ix
	ld	ix, 0
	add	ix, sp

	call	_inject

	; get current queue size
	; if (write_index >= read_index)
	;	return write_index	read_index;
	; else
	;	return KEYBOARD_BUFFER_SIZE	read_index + write_index;
	ld	c, 0
	ld	a, (_write_index)
	ld	l, a
	ld	a, (_read_index)
	ld	e, a
	ld	a, l
	cp	a, e
	jr	nc, .no_overflow
	ld	c, KEYBOARD_BUFFER_SIZE
.no_overflow:
	ld	a, l
	sub	a, e
	add	a, c
	; current queue size in A

	ld	e, a
	or	a, a
	jr	z, BB0_2

	ld	iy, _buffer
	ld	a, (_read_index)
	or	a, a
	sbc	hl, hl
	ld	l, a
	add	hl, hl
	push	hl
	pop	bc
	add	iy, bc

	ld	hl, (iy)
	ld	iy, (ix + 6)
	ld	(iy), l
	ld	(iy + 1), h
	inc	a
	and	a, KEYBOARD_BUFFER_SIZE_MASK
	ld	(_read_index), a
BB0_2:
	ld	a, e
	pop	ix
	ret

	section .bss,"aw",@nobits
; usb_keyboard_report_t previous_report = {0};
_previous_report:
	ds	8
; uint8_t write_index = 0;
_write_index:
	ds	1
; uint8_t read_index = 0;
_read_index:
	ds	1
; usb_keyboard_key_t buffer[KEYBOARD_BUFFER_SIZE];
_buffer:
	ds	32
; usb_keyboard_report_t report;
_report:
	ds	8
