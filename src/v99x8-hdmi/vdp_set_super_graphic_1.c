#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

void vdp_set_super_graphic_1() {
  vdp_set_graphic_7();
  vdp_current_mode   = 17;
  register_31_mirror = 3;

  vdp_reg_write(29, 255);
  vdp_reg_write(30, 3); // reset VIEW PORT and BASE ADDR
  vdp_reg_write(31, 3);
}
