/*
    See a thoroughly commented linker file here:
    https://github.com/wntrblm/Castor_and_Pollux/blob/main/firmware/scripts/samd21g18a.ld
*/

START_OF_ONCHIP_RAM = 0x02E100;
ONCHIP_RAM_SIZE = 0x1B00;      /* reserve just 6192 bytes for the on-chip RAM  (low 256 reserved for firmware and last 1k for stack)*/

START_OF_RAM    = 0x034000;
RAM_SIZE        = 0x003FFF;     /* restrict to a 16k page */

START_OF_2MB_RAM = 0x200000;
RAM_2MB_SIZE = 0x1FFFFF;        /* 2MB for the SRAM Module */

CRT_ORG_CODE = START_OF_2MB_RAM + 0x0400;

EXTERN(__start)

MEMORY
{
    RAMONCHIP (rwx) : ORIGIN = START_OF_ONCHIP_RAM, LENGTH = ONCHIP_RAM_SIZE
    RAM64K (rwx) : ORIGIN = START_OF_RAM, LENGTH = RAM_SIZE
    RAM2MB (rwx) : ORIGIN = START_OF_2MB_RAM, LENGTH = RAM_2MB_SIZE
}

SECTIONS
{
     /* PROVIDE(my_symbol = 0x038000); */

    start_of_header = . ;
    .header 0x200400  : AT(0x200400) { *(.header_adl) } > RAM2MB
    end_of_header = . ;

    start_of_startup = . ;
    .startup  : {
        *(.startup_adl)
        *(code_crt_init)
        *(code_crt_init_exit)
        *(code_crt_exit)
        *(code_crt_exit_exit)
    } > RAM2MB
    end_of_startup = . ;

    start_of_text = . ;
    .text : {
        *(.text)
        *(.text.*)
    } > RAM2MB
    end_of_text = . ;

    start_of_rodata = . ;
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > RAM2MB
    end_of_rodata = . ;

    start_of_data = . ;
    .data : {
        *(.data)
        *(.data.*)
    } > RAM2MB
    end_of_data = . ;

    _start_of_bss = . ;
    .bss(NOLOAD) : {
        *(bss_crt)
        *(.bss)
        *(.bss.*)
    } > RAM2MB
    _end_of_bss = . ;
    __heap = ALIGN(4);
    _length_of_bss = _end_of_bss - _start_of_bss;

    .bss64K(NOLOAD) : {
    _start_of_bss_z80 = . ;
        KEEP(*(.bss64k))
        KEEP(*(.bss_z80))
    } > RAM64K
    _end_of_bss_z80 = . ;
    _length_of_bss_z80 = _end_of_bss_z80 - _start_of_bss_z80;

    .comment(NOLOAD) : { *(.comment) }

    /* Define the VMA and LMA addresses */
    VMA_ADDR = ORIGIN(RAMONCHIP);
    LMA_ADDR = LOADADDR(.data) + SIZEOF(.data);

    _on_chip_source = LMA_ADDR;

    /* New section for code to be placed in RAMONCHIP */
    .textOnChip VMA_ADDR : AT(LMA_ADDR) {
        _start_of_on_chip = . ;
        *(.text_on_chip)
        *(.text_on_chip.*)
        __end_of_on_text_chip = . ;
    } > RAMONCHIP

    LMA_DATA_ADDR = LOADADDR(.textOnChip) + SIZEOF(.textOnChip);

    .dataOnChip : AT(LMA_DATA_ADDR) {
        *(.data_on_chip)
        *(.data_on_chip.*)
        _end_of_on_chip = . ;
    } > RAMONCHIP
    _length_of_on_chip = _end_of_on_chip - _start_of_on_chip;

    .bssOnChip(NOLOAD) : {
        _start_of_bss_on_chip = . ;
        KEEP(*(.bss_on_chip))
    } > RAMONCHIP
    _end_of_bss_on_chip = . ;
    _length_of_bss_on_chip = _end_of_bss_on_chip - _start_of_bss_on_chip;
}
