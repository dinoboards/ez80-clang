#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

void vdp_set_super_graphic_11() {
  vdp_set_refresh(60);
  vdp_set_graphic_7();
  vdp_current_mode = 128 + 11;

  // set extended register 255
  vdp_reg_write(29, 255);
  vdp_reg_write(30, 255); // reset VIEW PORT and BASE ADDR and PALETTE_DEPTH

  register_31_mirror = 4; // super high res
  vdp_reg_write(31, register_31_mirror);

  vdp_reg_write(29, 14); // select extended register PALETTE_DEPTH
  vdp_reg_write(30, 1);  // 2 pixels per byte aka 4 bits per pixel, 16 colours
}
