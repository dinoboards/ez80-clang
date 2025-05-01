#include "ez80-firmware-usb.h"
#include "include/ez80rc.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

usb_error_t ez80_usb_get_product(const uint8_t dev_index, char *const buffer, const uint8_t buffer_size) {
  usb_error_t         result;
  device_descriptor_t my_device_descriptor;
  memset(&my_device_descriptor, 0, sizeof(device_descriptor_t));

  memset(buffer, 0, buffer_size);

  const uint8_t device_address = ez80_usb_get_device_address(dev_index);
  CHECK(usbtrn_get_descriptor2(&my_device_descriptor, device_address));

  return usbtrn_get_string(buffer, buffer_size, device_address, my_device_descriptor.iProduct);

done:
  return result;
}
