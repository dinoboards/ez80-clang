#ifndef __HBIOS
#define __HBIOS

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
 * @brief USB HID Keyboard Input Report structure
 *
 * Structure matching the USB HID Keyboard report format as per USB HID specification.
 * See https://wiki.osdev.org/USB_Human_Interface_Devices for details.
 */
typedef struct {
  uint8_t bModifierKeys; /* Modifier keys state bitmap */
  uint8_t bReserved;     /* Reserved byte */
  uint8_t keyCode[6];    /* Array of up to 6 concurrent key codes */
} usb_keyboard_report_t;

/** Modifier key bit masks for bModifierKeys field */
#define KEY_MOD_LCTRL  0x01 /* Left Control key */
#define KEY_MOD_LSHIFT 0x02 /* Left Shift key */
#define KEY_MOD_LALT   0x04 /* Left Alt key */
#define KEY_MOD_LMETA  0x08 /* Left Meta/Windows key */
#define KEY_MOD_RCTRL  0x10 /* Right Control key */
#define KEY_MOD_RSHIFT 0x20 /* Right Shift key */
#define KEY_MOD_RALT   0x40 /* Right Alt key */
#define KEY_MOD_RMETA  0x80 /* Right Meta/Windows key */

/**
 * @brief Gets the current USB keyboard state
 *
 * Extended version of hbios_vda_kst that returns the complete USB keyboard state.
 * This function is only supported by the USB keyboard driver.
 *
 * @param video_unit The video unit number to query
 * @param usb_keyboard_report Pointer to structure to receive the keyboard report
 * @return int8_t Standard HBIOS result code
 *
 * @note This function returns the instantaneous keyboard state independent of
 *       the character input queue.
 */
extern int8_t hbios_vda_kstu(uint8_t video_unit, usb_keyboard_report_t *usb_keyboard_report);

#endif
