#include <cpm.h>
#include <stdio.h>

int getchar(void) {
  unsigned char c;
  do {
    c = cpm_rawio();
  } while (c == 0);

  return c;
}
