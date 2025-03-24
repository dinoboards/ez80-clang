#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

void vdp_set_super_graphic_2() {
  vdp_set_graphic_7();
  vdp_current_mode   = 18;
  register_31_mirror = 5;
  vdp_reg_write(31, 5);
}
