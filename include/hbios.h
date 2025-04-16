#ifndef __HBIOS
#define __HBIOS

#include "usb-keyboard.h"
#include <stdint.h>

/* HBIOS standard result codes */
#define HBIOS_SUCCESS              0   /* Function succeeded */
#define HBIOS_ERROR_UNDEFINED      -1  /* Undefined error */
#define HBIOS_ERROR_NOTIMPLEMENTED -2  /* Function not implemented */
#define HBIOS_ERROR_INVALIDFUNC    -3  /* Invalid function */
#define HBIOS_ERROR_INVALIDUNIT    -4  /* Invalid unit number */
#define HBIOS_ERROR_NOMEM          -5  /* Out of memory */
#define HBIOS_ERROR_RANGE          -6  /* Parameter out of range */
#define HBIOS_ERROR_NOMEDIA        -7  /* Media not present */
#define HBIOS_ERROR_NOHARDWARE     -8  /* Hardware not present */
#define HBIOS_ERROR_IO             -9  /* I/O error */
#define HBIOS_ERROR_READONLY       -10 /* Write request to read-only media */
#define HBIOS_ERROR_TIMEOUT        -11 /* Device timeout */
#define HBIOS_ERROR_CONFIG         -12 /* Invalid configuration */

/**
 * @brief Marshalling function to invoke HBIOS CIOOUT
 *
 * @param ce Combined parameter where:
 *           - High byte: character unit
 *           - Low byte: character to be sent
 * @return int8_t Standard HBIOS result code
 */
extern int8_t _hbios_cio_out(uint16_t ce);

/**
 * @brief Sends a character via the specified Character Video Unit
 *
 * @param video_unit The video unit to send the character to
 * @param ch The character to be sent
 * @return int8_t Standard HBIOS result code
 * @note If there is no space available in the unit's output buffer,
 *       the function will wait indefinitely
 */
static inline int8_t hbios_cio_out(uint8_t video_unit, uint8_t ch) { return _hbios_cio_out(((uint16_t)(video_unit)) << 8 | (ch)); }

/**
 * @brief Structure containing information about a specific video unit
 */
typedef struct {
  uint8_t  video_mode; /* Current video mode (driver specific value) */
  uint8_t  rows;       /* Number of character rows in current mode */
  uint8_t  columns;    /* Number of character columns in current mode */
  uint8_t *font_map;   /* Pointer to font bitmap data, or NULL if not available */
} vda_info_t;

/**
 * @brief Queries information about a specific video unit
 *
 * @param video_unit The video unit to query
 * @param new_font_map Pointer to buffer in upper 32K of MBASE to store font bitmap data.
 *                     Must be set to NULL if not used to avoid memory corruption.
 * @param info Pointer to vda_info_t structure to receive the query results
 *
 * @return Standard HBIOS result code
 *
 * @details Returns current video mode and display dimensions (rows/columns) for the
 *          specified video unit. The rows and columns values represent the total count,
 *          not the maximum index values.
 *
 * @note If new_font_map is provided, it must point to a suitably sized buffer in the
 *       upper 32K of MBASE address space. The buffer will be filled with the current
 *       character bitmap data if supported by the video driver. If bitmap retrieval
 *       is not supported, the font_map field in info will be set to zero.
 */
extern int8_t hbios_vda_qry(uint8_t video_unit, uint8_t *new_font_map, vda_info_t *info);

/**
 * @brief Structure containing keyboard input data from a video unit
 */
typedef struct {
  uint8_t scan_code; /* Raw PS/2 scan code (set 2) from keyboard */
  uint8_t key_state; /* Modifier and lock state flags (shift, ctrl, etc.) */
  uint8_t key_code;  /* ASCII value or special code for function/arrow keys */
} vda_keyrd_info_t;

/**
 * @brief Reads keyboard input from a specified video unit
 *
 * @param video_unit The video unit to read keyboard input from
 * @param info Pointer to vda_keyrd_info_t structure to receive the key data
 * @return Standard HBIOS result code
 *
 * @details Returns the next available key data from the keyboard buffer.
 *          If no key data is available, blocks indefinitely until a key is pressed.
 *
 * The returned data includes:
 * - scan_code: Raw PS/2 scancode (set 2 standard)
 * - key_state: Modifier and lock state bitmap:
 *   - Bit 7: Numpad key indicator
 *   - Bit 6: Caps Lock state
 *   - Bit 5: Num Lock state
 *   - Bit 4: Scroll Lock state
 *   - Bit 3: Windows key state
 *   - Bit 2: Alt key state
 *   - Bit 1: Control key state
 *   - Bit 0: Shift key state
 * - key_code: ASCII value for standard keys, special codes for function/arrow keys
 *
 * @note Keyboard driver compatibility varies. Refer to specific driver documentation
 *       in the RomWBW HBIOS source code for detailed behavior.
 */
extern int8_t hbios_vda_krd(uint8_t video_unit, vda_keyrd_info_t *info);

/**
 * @brief Gets the number of pending keystrokes in the keyboard buffer
 *
 * @param video_unit The video unit to check for pending keystrokes
 * @return int8_t Number of pending keystrokes (≥0) or HBIOS error code (<0)
 *
 * @details If the exact count cannot be determined, returns 1 to indicate keys
 * are available or 0 if the buffer is empty. Negative return values indicate
 * HBIOS errors (bit 7 set).
 */
extern int8_t hbios_vda_kst(uint8_t video_unit);

/**
 * @brief Query USB keyboard state and retrieve buffered report
 *
 * @param video_unit The video unit number to query
 * @param usb_keyboard_report Pointer to receive the USB keyboard report data
 * @return int16_t Combined status where:
 *         - Low byte: Standard HBIOS result code
 *         - High byte: Number of remaining reports in buffer (including current)
 *
 * @details This function extends hbios_vda_kst to provide full USB keyboard state
 * information. It retrieves and removes one buffered report from the keyboard queue.
 * Only the USB keyboard driver supports this functionality.
 *
 * The function maintains a separate queue from hbios_vda_krd and only stores state
 * changes. This means reading infrequently may return older state transitions that
 * were buffered.
 *
 * @note A return value with high byte ≥1 indicates valid report data was written
 * to usb_keyboard_report. A high byte of 0 means no reports are available.
 */
extern int16_t hbios_vda_kstu(uint8_t video_unit, usb_keyboard_report_t *usb_keyboard_report);

#endif
