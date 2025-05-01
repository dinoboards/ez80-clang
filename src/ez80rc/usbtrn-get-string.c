#include "ez80-firmware-usb.h"
#include <stdbool.h>
#include <stdint.h>

const setup_packet_t cmd_get_device_descriptor = {0x80, 6, {0, 1}, {0, 0}, 8};

#define CHECK(fn)                                                                                                                  \
  {                                                                                                                                \
    result = fn;                                                                                                                   \
    if (result != USB_ERR_OK)                                                                                                      \
      goto done;                                                                                                                   \
  }

usb_error_t
usbtrn_get_string(uint8_t *const buffer, const uint8_t buf_length, const uint8_t device_address, const uint8_t str_index) {
  usb_error_t    result;
  uint16_t       lang_id;
  uint8_t        str_length;
  uint8_t        dest;
  uint8_t        src;
  uint8_t        i;
  setup_packet_t cmd;
  cmd = cmd_get_device_descriptor;

  // 1 get first langid
  cmd.wLength   = 4;
  cmd.bValue[1] = 3;
  CHECK(usb_control_transfer(&cmd, (uint8_t *)buffer, device_address, 8));

  lang_id = (uint16_t)buffer[2] + ((uint16_t)buffer[3] << 8);

  // 2 get length of string for langid
  cmd.wLength   = 2;
  cmd.bValue[0] = str_index;
  cmd.bIndex[0] = lang_id & 255;
  cmd.bIndex[1] = lang_id >> 8;
  CHECK(usb_control_transfer(&cmd, (uint8_t *)buffer, device_address, 8));

  str_length = buffer[0];
  if (str_length > buf_length)
    str_length = buf_length;

  // 3 get string
  cmd.wLength = str_length;
  CHECK(usb_control_transfer(&cmd, (uint8_t *)buffer, device_address, 8));

  // 4 convert to ascii
  dest = 0;
  src  = 2;
  for (i = 0; i < str_length - 2; i++) {
    buffer[dest++] = buffer[src++];
    src++;
  }

  buffer[dest] = 0;

done:
  return result;
}
