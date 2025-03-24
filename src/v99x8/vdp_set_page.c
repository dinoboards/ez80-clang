#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

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
  }
}
