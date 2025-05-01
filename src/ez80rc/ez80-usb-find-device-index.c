#include "ez80-firmware-usb.h"
#include <stdbool.h>
#include <stdint.h>

uint8_t ez80_usb_find_device_index(usb_device_t dev_type) {
  uint8_t index = 1;
  while (true) {
    const usb_device_t t = ez80_usb_get_device_type(index);
    if (t == dev_type)
      return index;

    if (t == USB_NOT_FOUND)
      return 0;

    index++;
  }
}
