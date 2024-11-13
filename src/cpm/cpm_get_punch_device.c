#include "include/cpm.h"
#include <stddef.h>
#include <stdint.h>

const char *cpm_get_punch_device() {
  const uint8_t iobyte = cpm_get_iobyte();

  switch (CPM_IOBYTE_GET_PUNCH(iobyte)) {
  case 0:
    return __TTY;
  case 1:
    return __PTP;
  case 2:
    return __UP1;
  case 3:
    return __UP2;
  }

  return NULL;
}
