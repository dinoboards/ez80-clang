#ifndef __CPMCALLS
#define __CPMCALLS

#include <ez80.h>
#include <stdint.h>

#define MBASE_CONST_VARIABLE(T, c) (*(T)(((uint24_t)cpm_mbase | c)))

typedef char (*CPM_FCB_t)[];
#define CPM_FCB    MBASE_CONST_VARIABLE(CPM_FCB_t, 0x005C)
#define CPM_DMABUF MBASE_CONST_VARIABLE(CPM_FCB_t, 0x0080) /* Default DMA buffer address */

// assigned to the start of the 64k CPM page (0x030000)
extern void const *const cpm_mbase;

#define __MBASE (((uint8_t *)&cpm_mbase)[2])

#define AS_CPM_PTR(a) as_near_ptr_safe(a, __MBASE, __FILE__, __LINE__)

/* Call the bdos with register pair BC set to bc and DE set
to de. The value returned in register A is the return
value. */
extern uint8_t bdos(uint16_t bc, uint16_t de);

/* Quit the current program, return to command prompt. */
extern void cpm_term(void);

/* Wait for a character from the keyboard; then echo it to the screen and return it. */
extern uint8_t cpm_c_read(void);

/*
Send the character c to the screen. Tabs are expanded to spaces. Output can be paused with ^S and restarted with ^Q (or any key
under versions prior to CP/M 3). While the output is paused, the program can be terminated with ^C.
*/
extern void cpm_c_write(uint8_t c);

/* Wait for a character from the auxiliary reader */
extern uint8_t cpm_a_read(void);

/* Send the character c to the Auxiliary (Punch) output */
extern void cpm_a_write(uint8_t c);

/* Send the character c to the printer */
extern void cpm_l_write(uint8_t c);

/* Return a character without echoing if one is waiting; zero if none is
 * available. */
extern uint8_t cpm_c_rawio(void);

/* Returns the current IOBYTE
The value is bit mapped:

     Bits      Bits 6,7    Bits 4,5    Bits 2,3    Bits 0,1
     Device    LIST        PUNCH       READER      CONSOLE

     Value
       00      TTY:        TTY:        TTY:        TTY:
       01      CRT:        PTP:        PTR:        CRT:
       10      LPT:        UP1:        UR1:        BAT:
       11      UL1:        UP2:        UR2:        UC1:

BAT = batch mode. Use the current Reader for console input, and he current List (printer) device as the console output.
CRT = Standard console (keyboard and terminal screen).
LPT = Standard line printer.
PTP = Standard Paper Tape Punch.
PTR = Standard Paper Tape Reader.
TTY = Teletype device, eg a serial port.
UC1 = User defined (ie implementation dependent) console device.
UL1 = User defined (ie implementation dependent) printer device.
UPn = User defined (ie implementation dependent) output device.
URn = User defined (ie implementation dependent) input device.
*/
extern uint8_t cpm_get_iobyte(void);

// Bit masks for each device in the iobyte
#define CPM_IOBYTE_CONSOLE_MASK ((uint8_t)0x03) // 00000011
#define CPM_IOBYTE_READER_MASK  ((uint8_t)0x0C) // 00001100
#define CPM_IOBYTE_PUNCH_MASK   ((uint8_t)0x30) // 00110000
#define CPM_IOBYTE_LIST_MASK    ((uint8_t)0xC0) // 11000000

// Bit shift values for each device in the iobyte
#define CPM_IOBYTE_CONSOLE_SHIFT 0
#define CPM_IOBYTE_READER_SHIFT  2
#define CPM_IOBYTE_PUNCH_SHIFT   4
#define CPM_IOBYTE_LIST_SHIFT    6

// Macros to extract each device from the iobyte
#define CPM_IOBYTE_GET_CONSOLE(iobyte) ((iobyte & CPM_IOBYTE_CONSOLE_MASK) >> CPM_IOBYTE_CONSOLE_SHIFT)
#define CPM_IOBYTE_GET_READER(iobyte)  ((iobyte & CPM_IOBYTE_READER_MASK) >> CPM_IOBYTE_READER_SHIFT)
#define CPM_IOBYTE_GET_PUNCH(iobyte)   ((iobyte & CPM_IOBYTE_PUNCH_MASK) >> CPM_IOBYTE_PUNCH_SHIFT)
#define CPM_IOBYTE_GET_LIST(iobyte)    ((iobyte & CPM_IOBYTE_LIST_MASK) >> CPM_IOBYTE_LIST_SHIFT)

// Macros to set each device in the iobyte
#define CPM_IOBYTE_SET_CONSOLE(iobyte, value)                                                                                      \
  (iobyte = (iobyte & ~CPM_IOBYTE_CONSOLE_MASK) | ((value << CPM_IOBYTE_CONSOLE_SHIFT) & CPM_IOBYTE_CONSOLE_MASK))
#define CPM_IOBYTE_SET_READER(iobyte, value)                                                                                       \
  (iobyte = (iobyte & ~CPM_IOBYTE_READER_MASK) | ((value << CPM_IOBYTE_READER_SHIFT) & CPM_IOBYTE_READER_MASK))
#define CPM_IOBYTE_SET_PUNCH(iobyte, value)                                                                                        \
  (iobyte = (iobyte & ~CPM_IOBYTE_PUNCH_MASK) | ((value << CPM_IOBYTE_PUNCH_SHIFT) & CPM_IOBYTE_PUNCH_MASK))
#define CPM_IOBYTE_SET_LIST(iobyte, value)                                                                                         \
  (iobyte = (iobyte & ~CPM_IOBYTE_LIST_MASK) | ((value << CPM_IOBYTE_LIST_SHIFT) & CPM_IOBYTE_LIST_MASK))

extern const char *cpm_get_console_device();
extern const char *cpm_get_reader_device();
extern const char *cpm_get_punch_device();
extern const char *cpm_get_list_device();

/* Set the IOBYTE to the value iobyte */
extern void cpm_set_iobyte(uint8_t iobyte);

extern void cpm_c_writestr(near_ptr_t str);

extern void cpm_c_readstr(near_ptr_t str);

extern void cpm_f_dmaoff(near_ptr_t addr);

#endif
