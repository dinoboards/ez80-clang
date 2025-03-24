#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

/**
 * deprecated
 */
void vdp_set_mode(const uint8_t mode, const uint8_t lines, const uint8_t refresh_rate) {
  vdp_set_lines(lines);
  vdp_set_refresh(refresh_rate);

  switch (mode) {
  case 4:
    vdp_set_graphic_4();
    break;
  case 6:
    vdp_set_graphic_6();
    break;
  case 7:
    vdp_set_graphic_7();
    break;
  }
}
