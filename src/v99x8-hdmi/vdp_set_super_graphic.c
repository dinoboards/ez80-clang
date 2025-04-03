#include <v99x8-super.h>

extern void vdp_set_super_graphic(uint8_t mode) {
  switch (mode) {
  case 1:
    vdp_set_super_graphic_1();
    return;
  case 2:
    vdp_set_super_graphic_2();
    return;
  case 3:
    vdp_set_super_graphic_3();
    return;
  case 4:
    vdp_set_super_graphic_4();
    return;
  case 5:
    vdp_set_super_graphic_5();
    return;
  case 6:
    vdp_set_super_graphic_6();
    return;
  case 7:
    vdp_set_super_graphic_7();
    return;
  case 8:
    vdp_set_super_graphic_8();
    return;

  default:
    return;
  }
}
