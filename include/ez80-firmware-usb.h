#ifndef __EZ80_FIRMWARE_USB_H__
#define __EZ80_FIRMWARE_USB_H__

#include "usb-keyboard.h"
#include <stdint.h>

/* LOW LEVEL USB FUNCTIONS & TYPES */

typedef enum usb_device_e : uint8_t {
  USB_NOT_FOUND       = -1,
  USB_NOT_SUPPORTED   = 0,
  USB_IS_FLOPPY       = 1,
  USB_IS_MASS_STORAGE = 2,
  USB_IS_CDC          = 3,
  USB_IS_KEYBOARD     = 4,
  USB_IS_MOUSE        = 5,
  USB_IS_UNKNOWN      = 6,
  _USB_LAST_DEVICE_TYPE,
  USB_IS_HUB = 15
} usb_device_t;

typedef enum usb_error_e : uint8_t {
  USB_ERR_OK                          = 0,
  USB_ERR_NAK                         = 1,
  USB_ERR_STALL                       = 2,
  USB_ERR_TIMEOUT                     = 3,
  USB_ERR_DATA_ERROR                  = 4,
  USB_ERR_NO_DEVICE                   = 5,
  USB_ERR_PANIC_BUTTON_PRESSED        = 6,
  USB_TOKEN_OUT_OF_SYNC               = 7,
  USB_ERR_UNEXPECTED_STATUS_FROM_HOST = 8,
  USB_ERR_CODE_EXCEPTION              = 9,
  USB_ERR_MEDIA_CHANGED               = 10,
  USB_ERR_MEDIA_NOT_PRESENT           = 11,
  USB_ERR_CH376_BLOCKED               = 12,
  USB_ERR_CH376_TIMEOUT               = 13,
  USB_ERR_FAIL                        = 14,
  USB_ERR_MAX                         = 14,
  USB_ERR_OTHER                       = 15,
  USB_ERR_DISK_READ                   = 0x1D,
  USB_ERR_DISK_WRITE                  = 0x1E,
  USB_FILERR_MIN                      = 0x41,
  USB_ERR_OPEN_DIR                    = 0x41,
  USB_ERR_MISS_FILE                   = 0x42,
  USB_FILERR_MAX                      = 0xB4,
  USB_INT_CONNECT                     = 0x81,
  USB_BAD_ADDRESS                     = 0x82,
  USB_ERR_OUT_OF_MEMORY               = 0x83,
  USB_ERR_BUFF_TO_LARGE               = 0x84,
  USB_ERROR_DEVICE_NOT_FOUND          = 0x85,
} usb_error_t;

typedef struct _device_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t  iManufacturer;
  uint8_t  iProduct;
  uint8_t  iSerialNumber;
  uint8_t  bNumConfigurations;
} device_descriptor_t;

typedef struct _config_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationvalue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
} config_descriptor_t;

typedef struct _interface_descriptor {
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bInterfaceNumber;
  uint8_t bAlternateSetting;
  uint8_t bNumEndpoints;
  uint8_t bInterfaceClass;
  uint8_t bInterfaceSubClass;
  uint8_t bInterfaceProtocol;
  uint8_t iInterface;
} interface_descriptor_t, *p_interface_descriptor_t;

typedef struct _endpoint_descriptor {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bEndpointAddress;
  uint8_t  bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t  bInterval;
} endpoint_descriptor_t;

extern usb_error_t usbtrn_get_descriptor(device_descriptor_t *const buffer);
extern usb_error_t usbtrn_get_descriptor2(device_descriptor_t *const buffer, uint8_t device_address);

extern usb_error_t usbtrn_get_config_descriptor(
    config_descriptor_t *const buffer, uint8_t config_index, uint8_t buffer_size, uint8_t device_address, uint8_t max_packet_size);

extern usb_error_t usbtrn_get_full_config_descriptor(
    uint8_t config_index, uint8_t device_address, uint8_t max_packet_size, uint8_t max_buffer_size, uint8_t *const buffer);

extern usb_error_t usbtrn_set_configuration(uint8_t device_address, uint8_t max_packet_size, uint8_t configuration);

extern usb_error_t usbtrn_set_address(uint8_t device_address);

extern usb_error_t usbtrn_clear_endpoint_halt(uint8_t endpoint_number, uint8_t device_address, uint8_t max_packet_size);

extern usb_error_t usbtrn_get_string(char *const buffer, uint8_t buf_length, uint8_t device_address, uint8_t str_index);

typedef struct _setup_packet {
  uint8_t  bmRequestType;
  uint8_t  bRequest;
  uint8_t  bValue[2];
  uint8_t  bIndex[2];
  uint16_t wLength;
} setup_packet_t;

extern usb_error_t
usb_control_transfer(setup_packet_t *const cmd_packet, void *const buffer, uint8_t device_address, uint8_t max_packet_size);

extern usb_error_t usb_data_in_transfer(
    uint8_t *buffer, uint16_t buffer_size, uint8_t device_address, uint8_t number, uint8_t max_packet_size, uint8_t *toggle);

/* HIGH LEVEL USB FUNCTIONS */

extern usb_device_t ez80_usb_get_device_type(uint8_t dev_index);

extern uint8_t ez80_usb_find_device_index(usb_device_t dev_type);

extern uint8_t ez80_usb_get_device_address(uint8_t dev_index);

extern usb_error_t ez80_usb_get_manufacturer(uint8_t dev_index, char *buffer, uint8_t buffer_size);

extern usb_error_t ez80_usb_get_product(uint8_t dev_index, char *buffer, uint8_t buffer_size);

/* USB KEYBOARD FUNCTIONS */

extern uint8_t ez80_usb_kyb_report(usb_keyboard_report_t *rpt);

typedef struct {
  uint8_t key_ascii; /* ascii char encoding, if applicable */
  uint8_t key_code;  /* Modifier keys state bitmap in high byte, code in low byte */
  uint8_t key_down;  /* true key pressed down event, false, key up event */
} usb_kyb_event_t;

/**
 * @brief Retrieve buffered keyboard key events
 *
 * @param usb_key Pointer to receive the next key event data
 * @return uint8_t Number of events remaining in buffer (including current),
 *         or 0 if buffer is empty
 *
 * @details Processes the USB keyboard state buffer using ez80_usb_kyb_report to extract
 * individual key press and release events. Returns immediately if no events are
 * available.
 *
 * @note Modifier keys (Ctrl, Shift, Alt, etc.) are mapped to special key codes
 * ranging from E0-E7, corresponding to USB_KEY_LCTRL through to USB_KEY_RMETA
 */
extern uint8_t usb_kyb_event(usb_kyb_event_t *key);

/* USB MOUSE FUNCTIONS */

extern uint8_t ez80_usb_mse_init(uint8_t dev_index);

typedef struct {
  uint8_t buttons;
  int24_t x;
  int24_t y;
} ez80_usb_mse_report_ex_t;

extern uint8_t ez80_usb_mse_read(ez80_usb_mse_report_ex_t *rpt);

extern uint8_t ez80_usb_mse_state(ez80_usb_mse_report_ex_t *rpt);

#endif
