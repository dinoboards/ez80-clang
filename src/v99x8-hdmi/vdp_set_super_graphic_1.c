#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8-super.h>

void vdp_set_super_graphic_1() {
  vdp_set_refresh(60);
  vdp_set_graphic_7();
  vdp_current_mode   = 128 + 1;
  register_31_mirror = 3;
  vdp_reg_write(29, 255);
  vdp_reg_write(30, 7);                  // reset VIEW PORT and BASE ADDR
  vdp_reg_write(31, register_31_mirror); // set SUPER_MID mode

  vdp_reg_write(29, 0);
  vdp_reg_write(30, 0x28); // 0:VIEW_PORT_START_X  Low  byte 40 (0x28)
  vdp_reg_write(30, 0x00); // 1:VIEW_PORT_START_X  High byte 40 (0x28)
  vdp_reg_write(30, 0xA8); // 2:VIEW_PORT_END_X    Low  byte 680 (0x2A8)
  vdp_reg_write(30, 0x02); // 3:VIEW_PORT_END_X    High byte 680 (0x2A8)
  vdp_reg_write(30, 0x28); // 4:VIEW_PORT_START_Y  Low  byte 40 (0x28)
  vdp_reg_write(30, 0x00); // 5:VIEW_PORT_START_Y  High byte 40 (0x0)
  vdp_reg_write(30, 0xB8); // 6:VIEW_PORT_END_Y    Low  byte 440 (0x1B0)
  vdp_reg_write(30, 0x01); // 7:VIEW_PORT_END_Y    High byte 440 (0x1B0)
}
