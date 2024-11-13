#include <cpm.h>
#include <stdio.h>

int getchar(void) {
  unsigned char c = cpm_c_read();

  return c;
}
