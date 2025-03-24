#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

void vdp_set_extended_palette_entry(uint8_t index, RGB palette_entry) {
  DI;
  register_31_mirror |= 0x08;
  vdp_reg_write(31, register_31_mirror);

  vdp_reg_write(16, index);
  vdp_out_pal(palette_entry.red);
  vdp_out_pal(palette_entry.green);
  vdp_out_pal(palette_entry.blue);

  register_31_mirror &= ~0x08;
  vdp_reg_write(31, register_31_mirror);

  EI;
}
