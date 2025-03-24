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

  case 16:
    return 180;

  case 17:
    return 360;

  case 18:
    return 720;

  default:
    return 256;
  }
}
