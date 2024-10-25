/*
    See a thorouhly commented linker file here:
    https://github.com/wntrblm/Castor_and_Pollux/blob/main/firmware/scripts/samd21g18a.ld
*/

START_OF_RAM    = 0x020000;
RAM_SIZE        = 0x00FFFF;     /* 64K for CP/M limit */

/* Check if the environment variable is set, otherwise use the default value */
CRT_ORG_CODE = START_OF_RAM + 0x0100;

MEMORY
{
    RAM (rwx) : ORIGIN = START_OF_RAM, LENGTH = RAM_SIZE
}

SECTIONS
{
    start_of_header = . ;
    .header 0x020100  : AT(0x020100) { *(.header) } > RAM
    end_of_header = . ;

    start_of_startup = . ;
    .startup  : {
        *(.startup)
        *(code_crt_init)
        *(code_crt_init_exit)
        *(code_crt_exit)
        *(code_crt_exit_exit)
    } > RAM
    end_of_startup = . ;

    start_of_text = . ;
    .text : { *(.text) } > RAM
    end_of_text = . ;

    start_of_rodata = . ;
    .rodata : { *(.rodata) } > RAM
    end_of_rodata = . ;

    start_of_data = . ;
    .data : { *(.data) } > RAM
    end_of_data = . ;

    start_of_bss = . ;
    .bss(NOLOAD) : {
        *(bss_crt)
        *(.bss)
    }
    end_of_bss = . ;

    .comment(NOLOAD) : { *(.comment) }
}


/*ez80-ld -T linker-script.ld -Map=main.map ./crt.o ./main.o --oformat binary -o main.com*/
