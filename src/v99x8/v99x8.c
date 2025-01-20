#include <ez80.h>
#include <stdbool.h>
#include <stdlib.h>
#include <v99x8.h>

static uint8_t registers_mirror[REGISTER_COUNT] = {
    0x0E, // R0 - M5 = 1, M4 = 1, M3 = 1
    0x40, // R1 - ENABLE SCREEN, DISABLE INTERRUPTS, M1 = 0, M2 = 0
    0x1F, // R2 - PATTERN NAME TABLE := 0, A16 = 0
    0x00, // R3 - NO COLOR TABLE
    0x00, // R4 - N/A???
    0xF7, // R5 - SPRITE ATTRIBUTE TABLE -> FA00
    0x1E, // R6 - SPRITE PATTERN => F000
    0x00, // R7 - a background colour?
    0x8A, // R8 - COLOUR BUS INPUT, DRAM 64K, DISABLE SPRITE
    0x00, // R9 LN = 1(212 lines), S1, S0 = 0, IL = 0, EO = 0, NT = 1 (PAL), DC
          // = 0
    0x00, // R10 - color table - n/a
    0x01  // R11 - SPRITE ATTRIBUTE TABLE -> FA00
};

static void set_base_registers() {
  DI;
  uint8_t *pReg = registers_mirror;

  for (uint8_t i = 0; i < REGISTER_COUNT; i++) {
    vdp_reg_write(i, *pReg); // if we inline the increment, the compiler (with -Oz seems to pre-increment the pointer)
    pReg++;
  }

  EI;
}

static uint8_t vdp_current_mode = 255;

void vdp_set_lines(const uint8_t lines) {
  switch (lines) {
  case 212:
    registers_mirror[9] |= 0x80;
    break;

  case 192:
    registers_mirror[9] &= ~0x80;
    break;
  }
}

void vdp_set_refresh(const uint8_t refresh_rate) {
  switch (refresh_rate) {
  case PAL:
    registers_mirror[9] |= 0x02;
    break;

  case NTSC:
    registers_mirror[9] &= ~0x02;
    break;
  }
}

void vdp_set_graphic_7() {
  uint8_t *r = registers_mirror;

  *r++ = 0x0E; // R0 - M5 = 1, M4 = 1, M3 = 1
  r++;         // 0x40 R1 - ENABLE SCREEN, DISABLE INTERRUPTS, M1 = 0, M2 = 0
  *r++ = 0x1F; // R2 - PATTERN NAME TABLE := 0, A16 = 0
  *r++ = 0x00; // R3 - NO COLOR TABLE
  *r++ = 0x00; // R4 - N/A???
  *r++ = 0xF7; // R5 - SPRITE ATTRIBUTE TABLE -> FA00
  *r++ = 0x1E; // R6 - SPRITE PATTERN => F000
  r++;         // 0x00 R7 - background colour?
  r++;         // 0x8A R8 - COLOUR BUS INPUT, DRAM 64K, DISABLE SPRITE
  r++;         // 0x00 R9 LN = 1(212 lines), S1, S0 = 0, IL = 0, EO = 0, NT = 1 (PAL), DC = 0
  r++;         // 0x00 R10 - color table - n/a
  *r = 0x01;   // R11 - SPRITE ATTRIBUTE TABLE -> FA00

  set_base_registers();
  vdp_current_mode = 7;
}

void vdp_set_graphic_6() {
  uint8_t *r = registers_mirror;

  *r++ = 0x0A; // R0 - M5 = 1, M4 = 0, M3 = 1
  r++;         // 0x40 R1 - ENABLE SCREEN, DISABLE INTERRUPTS, M1 = 0, M2 = 0
  *r++ = 0x1F; // R2 - PATTERN NAME TABLE := 0, A16 = 0
  *r++ = 0x00; // R3 - NO COLOR TABLE
  *r++ = 0x00; // R4 - N/A???
  *r++ = 0xF7; // R5 - SPRITE ATTRIBUTE TABLE -> FA00
  *r++ = 0x1E; // R6 - SPRITE PATTERN => F000
  r++;         // 0x00 R7 - a background colour?
  r++;         // 0x8A R8 - COLOUR BUS INPUT, DRAM 64K, DISABLE SPRITE
  r++;         // 0x00 R9 LN = 1(212 lines), S1, S0 = 0, IL = 0, EO = 0, NT = 1 (PAL), DC = 0
  r++;         // 0x00 R10 - color table - n/a
  *r++ = 0x01; // R11 - SPRITE ATTRIBUTE TABLE -> FA00

  set_base_registers();
  vdp_current_mode = 6;
}

/**
 * deprecated
 */
void vdp_set_mode(const uint8_t mode, const uint8_t lines, const uint8_t refresh_rate) {
  vdp_set_lines(lines);
  vdp_set_refresh(refresh_rate);

  switch (mode) {
  case 6:
    vdp_set_graphic_6();
    break;
  case 7:
    vdp_set_graphic_7();
    break;
  }
}

void vdp_set_page(const uint8_t page) {
  switch (vdp_current_mode) {
  case 6:
    registers_mirror[2] = page ? 0x3F : 0x1F;
    vdp_reg_write(2, registers_mirror[2]); // Set Indirect register Access
    registers_mirror[6] = page ? 0x3E : 0x1E;
    vdp_reg_write(6, registers_mirror[6]); // Set Indirect register Access
    registers_mirror[11] = page ? 0x03 : 0x01;
    vdp_reg_write(11, registers_mirror[11]); // Set Indirect register Access
    break;

  case 7:
    registers_mirror[2] = page ? 0x3F : 0x1F;
    vdp_reg_write(2, registers_mirror[2]); // Set Indirect register Access
    registers_mirror[6] = page ? 0x3E : 0x1E;
    vdp_reg_write(6, registers_mirror[6]); // Set Indirect register Access
    registers_mirror[11] = page ? 0x03 : 0x01;
    vdp_reg_write(11, registers_mirror[11]); // Set Indirect register Access
    break;
  }
}

void vdp_set_palette(RGB *pPalette) {
  DI;
  vdp_reg_write(16, 0);
  for (uint8_t c = 0; c < 16; c++) {
    vdp_out_pal(pPalette->red * 16 + pPalette->blue);
    vdp_out_pal(pPalette->green);
    pPalette++;
  }
  EI;
}

void vdp_clear_all_memory(void) {
  DI;
  vdp_reg_write(14, 0);
  vdp_out_cmd(0);
  vdp_out_cmd(0x40);
  for (int i = 0; i < 0x20000; i++)
    vdp_out_dat(0);
  EI;
}

extern void delay(void);

void vdp_erase_bank0(uint8_t color) {
  vdp_cmd_wait_completion();

  DI;
  // Clear bitmap data from 0x0000 to 0x3FFF

  vdp_reg_write(17, 36);                // Set Indirect register Access
  vdp_out_reg_int16(0);                 // DX
  vdp_out_reg_int16(0);                 // DY
  vdp_out_reg_int16(512);               // NX
  vdp_out_reg_int16(212);               // NY
  vdp_out_reg_byte(color * 16 + color); // COLOUR for both pixels (assuming G7 mode)
  vdp_out_reg_byte(0);                  // Direction: VRAM, Right, Down
  vdp_out_reg_byte(CMD_VDP_TO_VRAM);
  EI;
}

void vdp_erase_bank1(uint8_t color) {
  vdp_cmd_wait_completion();

  DI;
  // Clear bitmap data from 0x0000 to 0x3FFF

  vdp_reg_write(17, 36);                // Set Indirect register Access
  vdp_out_reg_int16(0);                 // DX
  vdp_out_reg_int16(256);               // DY
  vdp_out_reg_int16(512);               // NX
  vdp_out_reg_int16(212);               // NY
  vdp_out_reg_byte(color * 16 + color); // COLOUR for both pixels (assuming G7 mode)
  vdp_out_reg_byte(0x0);                // Direction: ExpVRAM, Right, Down
  vdp_out_reg_byte(CMD_VDP_TO_VRAM);
  EI;
}

void _vdp_cmd_vdp_to_vram() {}

void _vdp_draw_line(uint16_t toX, uint16_t toY) {

  const uint16_t number_on_x_side = abs(toX - vdp_cmdp_dx);
  const uint16_t number_on_y_side = abs(toY - vdp_cmdp_dy);

  const bool major_direction_is_y = number_on_y_side >= number_on_x_side;

  vdp_cmdp_maj = major_direction_is_y ? number_on_y_side : number_on_x_side;
  vdp_cmdp_min = major_direction_is_y ? number_on_x_side : number_on_y_side;

  const bool diy = toY < vdp_cmdp_dy;
  const bool dix = toX < vdp_cmdp_dx;

  vdp_cmdp_dir = (major_direction_is_y ? 1 : 0) + (dix ? 4 : 0) + (diy ? 8 : 0);

  vdp_cmd_wait_completion();
  vdp_cmd();
}
