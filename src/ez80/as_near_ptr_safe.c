#include <ez80.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

near_ptr_t as_near_ptr_safe(const void *address, const uint8_t mbase, const char *file, const int line) {
  uint24_t x = (uint24_t)address;

  if (x >> 16 != mbase) {
    printf("%s:%d: Not a near address %X. Current MBASE is %XXXXX\r\n", file, line, x, mbase);
    abort();
  }

  return (uint16_t)x;
}
