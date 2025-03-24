#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

static void vdp_set_super_graphics_page(const uint8_t page) {
  uint24_t page2_addr = page * (vdp_get_screen_width() * vdp_get_screen_height()) / 4;

  vdp_reg_write(29, 8);
  vdp_reg_write(30, page2_addr & 255);
  vdp_reg_write(30, (page2_addr >> 8) & 255);
  vdp_reg_write(30, (page2_addr >> 16) & 255);
}

void vdp_set_page(const uint8_t page) {
  switch (vdp_current_mode) {
  case 6:
    registers_mirror[2] = page ? 0x3F : 0x1F;
    vdp_reg_write(2, registers_mirror[2]);
    registers_mirror[6] = page ? 0x3E : 0x1E;
    vdp_reg_write(6, registers_mirror[6]);
    registers_mirror[11] = page ? 0x03 : 0x01;
    vdp_reg_write(11, registers_mirror[11]);
    break;

  case 7:
    registers_mirror[2] = page ? 0x3F : 0x1F;
    vdp_reg_write(2, registers_mirror[2]);
    registers_mirror[6] = page ? 0x3E : 0x1E;
    vdp_reg_write(6, registers_mirror[6]);
    registers_mirror[11] = page ? 0x03 : 0x01;
    vdp_reg_write(11, registers_mirror[11]);
    break;

  case 128 + 1:
  case 128 + 2:
  case 128 + 3:
  case 128 + 4:
  case 128 + 5:
  case 128 + 6:
  case 128 + 7:
  case 128 + 8:
    vdp_set_super_graphics_page(page);
    break;
  }
}
