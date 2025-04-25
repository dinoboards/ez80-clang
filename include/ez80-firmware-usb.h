#ifndef __EZ80_FIRMWARE_USB_H__
#define __EZ80_FIRMWARE_USB_H__

#include "usb-keyboard.h"
#include <stdint.h>

typedef uint8_t usb_error_t;
enum {
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
};

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
extern usb_error_t usbtrn_get_descriptor2(device_descriptor_t *const buffer, const uint8_t device_address);

extern usb_error_t usbtrn_get_config_descriptor(config_descriptor_t *const buffer,
                                                const uint8_t              config_index,
                                                const uint8_t              buffer_size,
                                                const uint8_t              device_address,
                                                const uint8_t              max_packet_size);

extern usb_error_t usbtrn_gfull_cfg_desc(const uint8_t  config_index,
                                         const uint8_t  device_address,
                                         const uint8_t  max_packet_size,
                                         const uint8_t  max_buffer_size,
                                         uint8_t *const buffer);

extern usb_error_t
usbtrn_set_configuration(const uint8_t device_address, const uint8_t max_packet_size, const uint8_t configuration);

extern usb_error_t usbtrn_set_address(const uint8_t device_address);

extern usb_error_t
usbtrn_clear_endpoint_halt(const uint8_t endpoint_number, const uint8_t device_address, const uint8_t max_packet_size);

#endif
