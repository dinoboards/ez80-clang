#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

uint24_t vdp_get_screen_width() {
  switch (vdp_current_mode) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 7:
    return 256;

  case 5:
  case 6:
    return 512;

  case 128 + 1:
    return 320;

  case 128 + 2:
    return 320;

  case 128 + 3:
    return 360;

  case 128 + 4:
    return 360;

  case 128 + 5:
    return 640;

  case 128 + 6:
    return 640;

  case 128 + 7:
    return 720;

  case 128 + 8:
    return 720;

  case 128 + 9:
    return 720;

  case 128 + 10:
    return 720;

  default:
    return 256;
  }
}
