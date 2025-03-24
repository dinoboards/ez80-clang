#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

void vdp_set_command_page(const uint8_t page) {
  uint24_t page2_addr = page * (vdp_get_screen_width() * vdp_get_screen_height()) / 4;

  vdp_reg_write(29, 11);
  vdp_reg_write(30, page2_addr & 255);
  vdp_reg_write(30, (page2_addr >> 8) & 255);
  vdp_reg_write(30, (page2_addr >> 16) & 255);
}
