#include "include/cpm.h"
#include <stddef.h>
#include <stdint.h>

const char *cpm_get_reader_device() {
  const uint8_t iobyte = cpm_get_iobyte();

  switch (CPM_IOBYTE_GET_READER(iobyte)) {
  case 0:
    return __TTY;
  case 1:
    return __PTR;
  case 2:
    return __UR1;
  case 3:
    return __UR2;
  }

  return NULL;
}
