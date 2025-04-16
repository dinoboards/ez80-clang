#ifndef __USB_KEYBOARD
#define __USB_KEYBOARD

#include <stdint.h>

/**
 * @brief USB HID Keyboard scan codes
 *
 * @notes Follows typical us keyboard assignments
 *
 * @see https://usb.org/sites/default/files/hut1_21.pdf
 *
 */

/* Special keys */
#define USB_KEY_NONE          0x00
#define USB_KEY_ERR_ROLLOVER  0x01
#define USB_KEY_POST_FAIL     0x02
#define USB_KEY_ERR_UNDEFINED 0x03

/* Letters */
#define USB_KEY_A 0x04
#define USB_KEY_B 0x05
#define USB_KEY_C 0x06
#define USB_KEY_D 0x07
#define USB_KEY_E 0x08
#define USB_KEY_F 0x09
#define USB_KEY_G 0x0A
#define USB_KEY_H 0x0B
#define USB_KEY_I 0x0C
#define USB_KEY_J 0x0D
#define USB_KEY_K 0x0E
#define USB_KEY_L 0x0F
#define USB_KEY_M 0x10
#define USB_KEY_N 0x11
#define USB_KEY_O 0x12
#define USB_KEY_P 0x13
#define USB_KEY_Q 0x14
#define USB_KEY_R 0x15
#define USB_KEY_S 0x16
#define USB_KEY_T 0x17
#define USB_KEY_U 0x18
#define USB_KEY_V 0x19
#define USB_KEY_W 0x1A
#define USB_KEY_X 0x1B
#define USB_KEY_Y 0x1C
#define USB_KEY_Z 0x1D

/* Numbers */
#define USB_KEY_1 0x1E
#define USB_KEY_2 0x1F
#define USB_KEY_3 0x20
#define USB_KEY_4 0x21
#define USB_KEY_5 0x22
#define USB_KEY_6 0x23
#define USB_KEY_7 0x24
#define USB_KEY_8 0x25
#define USB_KEY_9 0x26
#define USB_KEY_0 0x27

/* Control keys */
#define USB_KEY_ENTER     0x28
#define USB_KEY_ESCAPE    0x29
#define USB_KEY_BACKSPACE 0x2A
#define USB_KEY_TAB       0x2B
#define USB_KEY_SPACE     0x2C

/* Punctuation */
#define USB_KEY_MINUS     0x2D
#define USB_KEY_EQUAL     0x2E
#define USB_KEY_LBRACKET  0x2F
#define USB_KEY_RBRACKET  0x30
#define USB_KEY_BACKSLASH 0x31
#define USB_KEY_SEMICOLON 0x33
#define USB_KEY_QUOTE     0x34
#define USB_KEY_GRAVE     0x35
#define USB_KEY_COMMA     0x36
#define USB_KEY_PERIOD    0x37
#define USB_KEY_SLASH     0x38

/* Function keys */
#define USB_KEY_CAPSLOCK 0x39
#define USB_KEY_F1       0x3A
#define USB_KEY_F2       0x3B
#define USB_KEY_F3       0x3C
#define USB_KEY_F4       0x3D
#define USB_KEY_F5       0x3E
#define USB_KEY_F6       0x3F
#define USB_KEY_F7       0x40
#define USB_KEY_F8       0x41
#define USB_KEY_F9       0x42
#define USB_KEY_F10      0x43
#define USB_KEY_F11      0x44
#define USB_KEY_F12      0x45

/* Navigation cluster */
#define USB_KEY_PRINTSCREEN 0x46
#define USB_KEY_SCROLLLOCK  0x47
#define USB_KEY_PAUSE       0x48
#define USB_KEY_INSERT      0x49
#define USB_KEY_HOME        0x4A
#define USB_KEY_PAGEUP      0x4B
#define USB_KEY_DELETE      0x4C
#define USB_KEY_END         0x4D
#define USB_KEY_PAGEDOWN    0x4E
#define USB_KEY_RIGHT       0x4F
#define USB_KEY_LEFT        0x50
#define USB_KEY_DOWN        0x51
#define USB_KEY_UP          0x52

/* Keypad */
#define USB_KEY_NUMLOCK     0x53
#define USB_KEY_KP_SLASH    0x54
#define USB_KEY_KP_ASTERISK 0x55
#define USB_KEY_KP_MINUS    0x56
#define USB_KEY_KP_PLUS     0x57
#define USB_KEY_KP_ENTER    0x58
#define USB_KEY_KP_1        0x59
#define USB_KEY_KP_2        0x5A
#define USB_KEY_KP_3        0x5B
#define USB_KEY_KP_4        0x5C
#define USB_KEY_KP_5        0x5D
#define USB_KEY_KP_6        0x5E
#define USB_KEY_KP_7        0x5F
#define USB_KEY_KP_8        0x60
#define USB_KEY_KP_9        0x61
#define USB_KEY_KP_0        0x62
#define USB_KEY_KP_DOT      0x63
#define USB_KEY_KP_EQUAL    0x67

/* Extended Function Keys */
#define USB_KEY_F13 0x68
#define USB_KEY_F14 0x69
#define USB_KEY_F15 0x6A
#define USB_KEY_F16 0x6B
#define USB_KEY_F17 0x6C
#define USB_KEY_F18 0x6D
#define USB_KEY_F19 0x6E
#define USB_KEY_F20 0x6F
#define USB_KEY_F21 0x70
#define USB_KEY_F22 0x71
#define USB_KEY_F23 0x72
#define USB_KEY_F24 0x73

/* Additional Control Keys */
#define USB_KEY_EXECUTE 0x74
#define USB_KEY_HELP    0x75
#define USB_KEY_MENU    0x76
#define USB_KEY_SELECT  0x77
#define USB_KEY_STOP    0x78
#define USB_KEY_AGAIN   0x79
#define USB_KEY_UNDO    0x7A
#define USB_KEY_CUT     0x7B
#define USB_KEY_COPY    0x7C
#define USB_KEY_PASTE   0x7D
#define USB_KEY_FIND    0x7E

/* Media Keys */
#define USB_KEY_MUTE        0x7F
#define USB_KEY_VOLUME_UP   0x80
#define USB_KEY_VOLUME_DOWN 0x81

/* Extended Keypad */
#define USB_KEY_KP_00          0xB0
#define USB_KEY_KP_000         0xB1
#define USB_KEY_KP_LPAREN      0xB6
#define USB_KEY_KP_RPAREN      0xB7
#define USB_KEY_KP_LBRACE      0xB8
#define USB_KEY_KP_RBRACE      0xB9
#define USB_KEY_KP_TAB         0xBA
#define USB_KEY_KP_BACKSPACE   0xBB
#define USB_KEY_KP_XOR         0xC2
#define USB_KEY_KP_CARET       0xC3
#define USB_KEY_KP_PERCENT     0xC4
#define USB_KEY_KP_LESS        0xC5
#define USB_KEY_KP_GREATER     0xC6
#define USB_KEY_KP_AMPERSAND   0xC7
#define USB_KEY_KP_LOGICAL_AND 0xC8
#define USB_KEY_KP_PIPE        0xC9
#define USB_KEY_KP_LOGICAL_OR  0xCA
#define USB_KEY_KP_COLON       0xCB
#define USB_KEY_KP_HASH        0xCC
#define USB_KEY_KP_SPACE       0xCD
#define USB_KEY_KP_AT          0xCE
#define USB_KEY_KP_EXCLAIM     0xCF

/* Memory Keys */
#define USB_KEY_KP_MEM_STORE   0xD0
#define USB_KEY_KP_MEM_RECALL  0xD1
#define USB_KEY_KP_MEM_CLEAR   0xD2
#define USB_KEY_KP_MEM_ADD     0xD3
#define USB_KEY_KP_MEM_SUB     0xD4
#define USB_KEY_KP_MEM_MULT    0xD5
#define USB_KEY_KP_MEM_DIV     0xD6
#define USB_KEY_KP_PLUSMINUS   0xD7
#define USB_KEY_KP_CLEAR       0xD8
#define USB_KEY_KP_CLEAR_ENTRY 0xD9
#define USB_KEY_KP_BINARY      0xDA
#define USB_KEY_KP_OCTAL       0xDB
#define USB_KEY_KP_DECIMAL     0xDC
#define USB_KEY_KP_HEX         0xDD

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
#define USB_KEY_MOD_LCTRL  0x01 /* Left Control key */
#define USB_KEY_MOD_LSHIFT 0x02 /* Left Shift key */
#define USB_KEY_MOD_LALT   0x04 /* Left Alt key */
#define USB_KEY_MOD_LMETA  0x08 /* Left Meta/Windows key */
#define USB_KEY_MOD_RCTRL  0x10 /* Right Control key */
#define USB_KEY_MOD_RSHIFT 0x20 /* Right Shift key */
#define USB_KEY_MOD_RALT   0x40 /* Right Alt key */
#define USB_KEY_MOD_RMETA  0x80 /* Right Meta/Windows key */

#endif
