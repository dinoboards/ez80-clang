/*
    See a thorouhly commented linker file here:
    https://github.com/wntrblm/Castor_and_Pollux/blob/main/firmware/scripts/samd21g18a.ld
*/

START_OF_RAM    = 0x034000;
RAM_SIZE        = 0x003FFF;     /* restrict to a 16k page */

START_OF_2MB_RAM = 0x200000;
RAM_2MB_SIZE = 0x1FFFFF;        /* 2MB for the SRAM Module */

CRT_ORG_CODE = START_OF_2MB_RAM + 0x0400;

EXTERN(__start)

MEMORY
{
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
}

/* int my_bss2_var __attribute__((section(".bss2"))); */
