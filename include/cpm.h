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

/**
 * @brief Call the BDOS function with specified register values.
 *
 * This function calls the BDOS with register pair BC set to `bc` and DE set to `de`.
 * The value returned in register A is the return value of the function/
 *
 * @param[in] bc The value to set in the BC register pair.
 * @param[in] de The value to set in the DE register pair.
 *
 * @return The value returned in register A.
 */
extern uint8_t bdos(uint16_t bc, uint16_t de);

/**
 * @brief Quit the current program and return to the command prompt.
 */
extern void cpm_term(void);

/**
 * @brief Wait for a character from the keyboard, echo it to the screen, and return it.
 *
 * This function waits for a character input from the keyboard, echoes it to the screen,
 * and then returns the character.
 *
 * @return The character read from the keyboard.
 */
extern uint8_t cpm_c_read(void);

/**
 * @brief Send the character to the screen.
 *
 * This function sends the character `c` to the screen. Tabs are expanded to spaces.
 * Output can be paused with ^S and restarted with ^Q (or any key under versions prior to CP/M 3).
 * While the output is paused, the program can be terminated with ^C.
 *
 * @param[in] c The character to send to the screen.
 */
extern void cpm_c_write(uint8_t c);

/**
 * @brief Wait for a character from the auxiliary reader.
 *
 * This function waits for a character input from the auxiliary reader and returns it.
 *
 * @return The character read from the auxiliary reader.
 */
extern uint8_t cpm_a_read(void);

/**
 * @brief Send the character to the Auxiliary (Punch) output.
 *
 * This function sends the character `c` to the Auxiliary (Punch) output.
 *
 * @param[in] c The character to send to the Auxiliary output.
 */
extern void cpm_a_write(uint8_t c);

/**
 * @brief Send the character to the printer.
 *
 * This function sends the character `c` to the printer.
 *
 * @param[in] c The character to send to the printer.
 */
extern void cpm_l_write(uint8_t c);

/**
 * @brief Return a character without echoing if one is waiting; zero if none is available.
 *
 * This function returns a character if one is waiting in the input buffer without echoing it.
 * If no character is available, it returns zero.
 *
 * @return The character if available, otherwise zero.
 */
extern uint8_t cpm_c_rawio(void);

/**
 * @brief Returns the current IOBYTE.
 *
 * This function returns the current IOBYTE, which is bit mapped as follows:
 *
 *     Bits      Bits 6,7    Bits 4,5    Bits 2,3    Bits 0,1
 *     Device    LIST        PUNCH       READER      CONSOLE
 *
 *     Value
 *       00      TTY:        TTY:        TTY:        TTY:
 *       01      CRT:        PTP:        PTR:        CRT:
 *       10      LPT:        UP1:        UR1:        BAT:
 *       11      UL1:        UP2:        UR2:        UC1:
 *
 * BAT = batch mode. Use the current Reader for console input, and the current List (printer) device as the console output.
 * CRT = Standard console (keyboard and terminal screen).
 * LPT = Standard line printer.
 * PTP = Standard Paper Tape Punch.
 * PTR = Standard Paper Tape Reader.
 * TTY = Teletype device, e.g., a serial port.
 * UC1 = User defined (i.e., implementation dependent) console device.
 * UL1 = User defined (i.e., implementation dependent) printer device.
 * UPn = User defined (i.e., implementation dependent) output device.
 * URn = User defined (i.e., implementation dependent) input device.
 *
 * @return The current IOBYTE.
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

/**
 * @brief Sets the IOBYTE to the specified value.
 *
 * This function sets the IOBYTE to the given value.
 *
 * @param[in] iobyte The value to set the IOBYTE to.
 */
extern void cpm_set_iobyte(uint8_t iobyte);

/**
 * @brief Writes a $ terminated string to the console.
 *
 * This function writes the $ terminated string pointed to by `str` to the console.
 *
 * @param[in] str The near pointer to the $ terminated string to be written.
 */
extern void cpm_c_writestr(near_ptr_t str);

/**
 * @brief Reads a string from the console.
 *
 * This function reads characters from the keyboard into a memory buffer until RETURN is pressed. The Delete key is handled
 * correctly. In later versions of CP/M, more features can be used at this point; ZPM3 includes a full line editor with recall of
 * previous lines typed.
 *
 * If str is NULL, the DMA address is used (CP/M 3 and later) and the buffer already contains data:
 *
 * buffer: DEFB    size
 *         DEFB    len
 *         DEFB    bytes
 *
 * The value at buffer+0 is the amount of bytes available in the buffer. Once the limit has been reached, no more can be added,
 * although the line editor can still be used. If str is NULL the next byte contains the number of bytes already in the buffer;
 * otherwise this is ignored. On return from the function, it contains the number of bytes present in the buffer.
 *
 * The bytes typed then follow. There is no end marker.
 *
 * @param[out] str The near pointer to the buffer where the string and its header will be stored.
 */
extern void cpm_c_readstr(near_ptr_t str);

/**
 * @brief Sets the DMA address for the next file operation.
 *
 * This function sets the DMA address to `addr` for the next file operation.
 *
 * @param[in] addr The near pointer to the DMA address.
 */
extern void cpm_f_dmaoff(near_ptr_t addr);

#endif
