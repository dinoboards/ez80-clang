#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

// TODO: interlaced double line not applied in result
uint24_t vdp_get_screen_height() {
  switch (vdp_current_mode) {
  case 128 + 1:
    return 200;

  case 128 + 2:
    return 240;

  case 128 + 3:
    return 240;

  case 128 + 4:
    return 288;

  case 128 + 5:
    return 400;

  case 128 + 6:
    return 480;

  case 128 + 7:
    return 480;

  case 128 + 8:
    return 576;

  case 128 + 9:
    return 240;

  case 128 + 10:
    return 288;

  case 128 + 11:
    return 240;

  default:
    return (registers_mirror[9] & 0x80) ? 212 : 192;
  }
}
