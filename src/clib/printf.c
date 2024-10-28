#include "nanoprintf-min.h"

#undef NPF_PUTC
#undef NPF_EXTRACT
#undef NPF_WRITEBACK

// printf()

int printf(char const *format, ...) {
  va_list val;
  va_start(val, format);
  int const rv = vprintf(format, val);
  va_end(val);
  return rv;
}
