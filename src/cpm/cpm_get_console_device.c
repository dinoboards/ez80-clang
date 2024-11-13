#include "include/cpm.h"
#include <stddef.h>
#include <stdint.h>

const char *cpm_get_console_device() {
  const uint8_t iobyte = cpm_get_iobyte();

  switch (CPM_IOBYTE_GET_CONSOLE(iobyte)) {
  case 0:
    return __TTY;
  case 1:
    return __CRT;
  case 2:
    return __BAT;
  case 3:
    return __UC1;
  }

  return NULL;
}
