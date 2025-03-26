#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

// 9: 720x240 60Hz
void vdp_set_super_graphic_9() {
  vdp_set_refresh(60);
  vdp_set_graphic_7();
  vdp_current_mode   = 128 + 9;
  register_31_mirror = 7;
  vdp_reg_write(29, 255);
  vdp_reg_write(30, 7); // reset viewport and base addr
  vdp_reg_write(31, register_31_mirror);
}
