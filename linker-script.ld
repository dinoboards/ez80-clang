/*
    See a thorouhly commented linker file here:
    https://github.com/wntrblm/Castor_and_Pollux/blob/main/firmware/scripts/samd21g18a.ld
*/

START_OF_RAM    = 0x000000;
RAM_SIZE        = 0x200000;     /* 2Mb, 2.097.152 bytes */
FLASH_SIZE      = 0x800000;     /* 8Mb, 8.388.608 bytes */

SECTIONS
{
    . = 0x000000;
    start_of_reset = . ;
    .reset : { *(.reset) }
    end_of_reset = . ;

    . = 0x000100;
    start_of_ivects = . ;
    .ivects : { *(.ivects) }
    end_of_ivects = . ;

    start_of_startup = . ;
    .startup : { *(.startup) }
    end_of_startup = . ;

    start_of_text = . ;
    .text : { *(.text) }
    end_of_text = . ;

    start_of_data = . ;
    .data : { *(.data) }
    end_of_data = . ;

    start_of_bss = . ;
    .bss : { *(.bss) }
    end_of_bss = . ;
}

/* These values are taken from the ZDS II linkcmd file */
__low_romdata       = start_of_data;
__low_data          = start_of_data;
__len_data          = end_of_data - __low_data;
__low_bss           = start_of_bss;
__len_bss           = end_of_bss - __low_bss;
__stack             = START_OF_RAM + RAM_SIZE;
/* __heaptop = highaddr of RAM
__heapbot = top of RAM + 1 */
__low_romcode       = start_of_text;
__low_code          = start_of_text;
__len_code          = end_of_text - __low_code;
__copy_code_to_ram  = 0;
/*__crtl = 1 */

/* on CWS 1: CS0 = Flash 8 Mb */
__CS0_LBR_INIT_PARAM = 0x20;
__CS0_UBR_INIT_PARAM = 0x2f;
__CS0_CTL_INIT_PARAM = 0x88;
__CS0_BMC_INIT_PARAM = 0x01;
/* on CWS 1: CS1 = SRAM 2 Mb */
__CS1_LBR_INIT_PARAM = 0x00;
__CS1_UBR_INIT_PARAM = 0x1f;
__CS1_CTL_INIT_PARAM = 0x08;
__CS1_BMC_INIT_PARAM = 0x01;
/* on CWS 1: CS2 = Not Used */
__CS2_LBR_INIT_PARAM = 0x80;
__CS2_UBR_INIT_PARAM = 0xbf;
__CS2_CTL_INIT_PARAM = 0x28;
__CS2_BMC_INIT_PARAM = 0x01;
/* on CWS 1: CS3 = Not Used */
__CS3_LBR_INIT_PARAM = 0x03;
__CS3_UBR_INIT_PARAM = 0x03;
__CS3_CTL_INIT_PARAM = 0x18;
__CS3_BMC_INIT_PARAM = 0x84;

_SYS_CLK_FREQ = 20000000;
