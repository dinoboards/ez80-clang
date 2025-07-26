#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

uint24_t vdp_get_screen_max_unique_colours() {
  switch (vdp_current_mode) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 6:
  case 128 + 11:
    return 16;

  case 5:
    return 4;

  case 7:
  case 128 + 1:
  case 128 + 2:
  case 128 + 3:
  case 128 + 4:
  case 128 + 5:
  case 128 + 6:
  case 128 + 7:
  case 128 + 8:
  case 128 + 9:
  case 128 + 10:
    return 256;

  default:
    return 0;
  }
}
