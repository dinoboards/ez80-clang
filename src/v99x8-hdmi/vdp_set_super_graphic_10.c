#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

// 10: 720x288 50Hz
void vdp_set_super_graphic_10() {
  vdp_set_refresh(50);
  vdp_set_graphic_7();
  vdp_current_mode   = 128 + 10;
  register_31_mirror = 7;
  vdp_reg_write(29, 255);
  vdp_reg_write(30, 7); // reset viewport and base addr
  vdp_reg_write(31, register_31_mirror);
}
