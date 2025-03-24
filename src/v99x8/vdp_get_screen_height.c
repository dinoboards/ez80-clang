#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

// TODO: interlaced double line not applied in result
uint24_t vdp_get_screen_height() {
  switch (vdp_current_mode) {
  case 16:
    return (registers_mirror[9] & 0x02) ? 144 : 120;

  case 17:
    return (registers_mirror[9] & 0x02) ? 288 : 240;

  case 18:
    return (registers_mirror[9] & 0x02) ? 576 : 480;

  default:
    return (registers_mirror[9] & 0x80) ? 212 : 192;
  }
}
