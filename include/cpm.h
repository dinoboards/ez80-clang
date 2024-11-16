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
 * If `str` is NULL, the DMA address is used (CP/M 3 and later) and the buffer already contains data:
 *
 * buffer: DEFB    size
 *         DEFB    len
 *         DEFB    bytes
 *
 * The value at buffer+0 is the amount of bytes available in the buffer. Once the limit has been reached, no more can be added,
 * although the line editor can still be used. If `str` is NULL the next byte contains the number of bytes already in the buffer;
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

/**
 * @brief Returns 0 if no characters are waiting, nonzero if a character is waiting.
 *
 * @return The console status
 */
extern uint8_t cpm_c_stat(void);

/**
 * @brief Returns the BDOS version.
 *
 * This function returns the BDOS version.
 *
 * @return The BDOS version.
 */
extern uint8_t cpm_s_bdosver(void);

/**
 * @brief Resets all disk drives and logs out all disks.
 *
 * This function resets all disk drives, logs out all disks, and empties disk buffers. It sets the currently selected drive to A:.
 * Any drives set to Read-Only in software* become Read-Write; replacement BDOS implementations may leave them Read-Only.
 *
 * In CP/M versions 1 and 2, it logs in drive A: and returns 0xFF if there is a file present whose name begins with a `$`, otherwise
 * it returns 0. Replacement BDOS* implementations may modify this behavior.
 *
 * In multitasking versions, it returns 0 if succeeded, or 0xFF if other processes have files open on removable or read-only drives.
 *
 * When the Digital Research CP/M 2 BDOS is started from cold, it is not properly initialized until this function is called; disk
 * operations may fail or crash.  Normally, this is done by the CCP and other programs don't need to worry, but if you are writing
 * an alternative CCP or a program that runs instead of the CCP, it's something to bear in mind.
 *
 * @return 0 if succeeded, or 0xFF if there are issues.
 */
extern uint8_t cpm_drv_allreset(void);

/**
 * @brief Sets the currently selected drive.
 *
 * This function sets the currently selected drive to the specified drive number and logs in the disk. The drive number passed to
 * this routine is 0 for A:, 1 for B:, up to 15 for P:.
 *
 * CP/M 1975 and 1.3 are limited to two drives. CP/M 1.4 is limited to four drives.
 *
 * @param[in] drive The drive number to set (0 for A:, 1 for B:, ..., 15 for P:).
 *
 * @return 0 if successful, or 0xFF if there is an error. Under MP/M II and later versions, H can contain a physical error number.
 */
extern uint8_t cpm_drv_set(uint8_t drive);

/**
 * @brief Returns the currently selected drive.
 *
 * Returns currently selected drive. 0 => A:, 1 => B: etc.
 *
 * @return The currently selected drive.
 */
extern uint8_t cpm_drv_get(void);

/**
 * @brief Opens a file for reading or reading/writing.
 *
 * This function opens a file for reading or reading/writing using the File Control Block (FCB). The FCB is a 36-byte data
 * structure, most of which is maintained by CP/M.
 *
 * The FCB should have its DR, Fn, and Tn fields filled in, and the four fields EX, S1, S2, and RC set to zero. Under CP/M 3 and
 * later, if CR is set to 0xFF, then on return CR will contain the last record byte count.  Note that CR should normally be reset to
 * zero if sequential access is to be used.
 *
 * Under MP/M II, the file is normally opened exclusively - no other process can access it.
 * Two bits in the FCB control the mode the file is opened in:
 * - F5': Set to 1 for "unlocked" mode - other programs can use the file.
 * - F6': Set to 1 to open the file in read-only mode - other programs can use the file read-only.
 *   If both F6' and F5' are set, F6' wins.
 * If the file is opened in "unlocked" mode, the file's identifier (used for record locking) will be returned at FCB+21h.
 *
 * Under MP/M II and later versions, a password can be supplied to this function by pointing the DMA address at the password.
 *
 * On return from this function, A is 0xFF for error, or 0-3 for success. Some versions (including CP/M 3) always return zero;
 * others return 0-3 to indicate that an image of the directory entry is to be found at (80h+20h*A).
 *
 * If result is 0xFF, CP/M 3 returns a hardware error (stored in errno). It also sets some bits in the FCB:
 * - F7': Set if the file is read-only because writing is password protected and no password was supplied.
 * - F8': Set if the file is read-only because it is a User 0 system file opened from another user area.
 *
 * @param[in] fcb The near pointer to the File Control Block (FCB).
 *
 * @return 0-3 for success, or 0xFF for error.
 */
extern uint16_t cpm_f_open(near_ptr_t fcb);

/**
 * @brief Write a record to the previously specified DMA address.
 *
 * @details The record is normally 128 bytes, but can be a multiple of 128 bytes.
 * Update byte returned values are:
 * - 0: OK
 * - 1: Directory full
 * - 2: Disc full
 * - 8: (MP/M) Record locked by another process
 * - 9: Invalid FCB
 * - 10: (CP/M) Media changed; (MP/M) FCB checksum error
 * - 11: (MP/M) Unlocked file verification error
 * - 0xFF: Hardware error??
 *
 * Lower byte, contains the number of 128-byte records written, before any error (CP/M 3 only).
 *
 * @param[in] fcb The near pointer to the File Control Block (FCB).
 *
 * @return 0 for success, or an error code as described above.
 */
extern uint16_t cpm_f_write(near_ptr_t fcb);

/**
 * @brief Creates the file specified by the FCB.
 *
 * @details Returns error codes in BA and HL.
 *
 * If the directory is full, the function return an upper byte of 0xFF.
 *
 * If the file already exists, the default action is to return to the command prompt. However, CP/M 3 may return a hardware error in
 * the lower byte
 *
 * Under MP/M II, set F5' to open the file in "unlocked" mode.
 *
 * Under MP/M II and later versions, set F6' to create the file with a password; the DMA address should point at a 9-byte buffer:
 *
 * @code
 * DEFS    8   ;Password
 * DEFB    1   ;Password mode
 * @endcode
 *
 * @param[in] fcb The near pointer to the File Control Block (FCB).
 *
 * @return 0 for success, or an error code as described above.
 */
extern uint16_t cpm_f_make(near_ptr_t fcb);

/* Size of CPM Sector */
#define SECSIZE 128

/* Flags for fcp->use */
#define U_READ  1 /* file open for reading */
#define U_WRITE 2 /* file open for writing */
#define U_RDWR  3 /* open for read and write */
#define U_CON   4 /* device is console */
#define U_RDR   5 /* device is reader */
#define U_PUN   6 /* device is punch */
#define U_LST   7 /* list device */

#define __STDIO_EOFMARKER 26 /* End of file marker (^Z) */
#define __STDIO_BINARY    1  /* We should consider binary/text differences */
#define __STDIO_CRLF      1  /* Automatically convert between CR and CRLF */

typedef struct fcb {
  // 36 bytes of standard FCB
  uint8_t  drive;       /* drive code */
  char     name[8];     /* file name */
  char     ext[3];      /* file type */
  uint8_t  extent;      /* file extent */
  char     filler[2];   /* not used */
  char     records;     /* number of records in present extent */
  char     discmap[16]; /* CP/M disc map */
  char     next_record; /* next record to read or write */
  uint24_t ranrec;      /* random record number (24 bit no. ) */

  /* Below here is used by the library */
  // 7 bytes used by the library
  unsigned long rwptr; /* read/write pointer in bytes */
  uint8_t       use;   /* use flag */
  uint8_t       uid;   /* user id belonging to this file */
  uint8_t       mode;  /* TEXT/BINARY discrimination */

  // 133 bytes used for caching
  unsigned long cached_record; /* Record number that we have cached */
  uint8_t       dirty;         /* Set if the buffer is dirty and needs writing to disc */
  uint8_t       buffer[SECSIZE];
} FCB;

#endif
