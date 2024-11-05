#ifndef __V9958
#define __V9958

#include <ez80.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define PAL  1
#define NTSC 2

typedef struct {
  uint8_t red;
  uint8_t blue;
  uint8_t green;
} RGB;

#define VDP_DATA PORT_IO(0xFF98)
#define VDP_ADDR PORT_IO(0xFF99)
#define VDP_PALT PORT_IO(0xFF9A)
#define VDP_REGS PORT_IO(0xFF9B)

#define vdp_out_cmd(v)      port_out(VDP_ADDR, v)
#define vdp_out_dat(v)      port_out(VDP_DATA, v)
#define vdp_out_pal(v)      port_out(VDP_PALT, v)
#define vdp_out_reg_byte(v) port_out(VDP_REGS, v)

extern void vdp_clear_all_memory(void);
extern void vdp_set_palette(RGB *);
extern void vdp_set_mode(const uint8_t mode, const uint8_t lines, const uint8_t refresh_rate);
extern void vdp_set_page(const uint8_t page);

extern void vdp_erase_bank0(uint8_t color);
extern void vdp_erase_bank1(uint8_t color);
extern void _vdp_reg_write(uint16_t rd);
extern void vdp_out_reg_int16(uint16_t b);

extern uint8_t vdp_get_status(uint8_t r);

#define vdp_reg_write(a, b) _vdp_reg_write((a)*256 + (b))

#define REGISTER_COUNT 12

#define CMD_VDP_TO_VRAM 0xC0
#define CMD_LINE(op)    (0x70 | op)
#define CMD_PSET(op)    (0x50 | op)
#define CMD_LOGIC_IMP   0x00
#define CMD_LOGIC_AND   0x01

extern void vdp_cmd(void);
extern void vdp_cmd_wait_completion(void);

extern uint16_t vdp_cmdp_r36;
extern uint16_t vdp_cmdp_r38;
extern uint16_t vdp_cmdp_r40;
extern uint16_t vdp_cmdp_r42;
extern uint8_t  vdp_cmdp_r44;
extern uint8_t  vdp_cmdp_r45;
extern uint8_t  vdp_cmdp_r46;

#define vdp_cmdp_dx        vdp_cmdp_r36
#define vdp_cmdp_dy        vdp_cmdp_r38
#define vdp_cmdp_nx        vdp_cmdp_r40
#define vdp_cmdp_ny        vdp_cmdp_r42
#define vdp_cmdp_color     vdp_cmdp_r44
#define vdp_cmdp_dir       vdp_cmdp_r45
#define vdp_cmdp_operation vdp_cmdp_r46

#define vdp_cmdp_maj vdp_cmdp_r40
#define vdp_cmdp_min vdp_cmdp_r42

#define vdp_cmd_vdp_to_vram(from_x, from_y, to_dx, to_dy, colour, direction)                                                       \
  vdp_cmdp_dx        = (from_x);                                                                                                   \
  vdp_cmdp_dy        = (from_y);                                                                                                   \
  vdp_cmdp_nx        = (to_dx);                                                                                                    \
  vdp_cmdp_ny        = (to_dy);                                                                                                    \
  vdp_cmdp_color     = (colour);                                                                                                   \
  vdp_cmdp_dir       = (direction);                                                                                                \
  vdp_cmdp_operation = CMD_VDP_TO_VRAM;                                                                                            \
  vdp_cmd_wait_completion();                                                                                                       \
  vdp_cmd()

#define vdp_draw_line(fromX, fromY, toX, toY, color, operation)                                                                    \
  vdp_cmdp_dx        = (fromX);                                                                                                    \
  vdp_cmdp_dy        = (fromY);                                                                                                    \
  vdp_cmdp_color     = (color);                                                                                                    \
  vdp_cmdp_operation = CMD_LINE((operation));                                                                                      \
  _vdp_draw_line(toX, toY)

extern void _vdp_draw_line(uint16_t toX, uint16_t toY);

#define pointSet(x, y, color, operation)                                                                                           \
  vdp_cmdp_dx        = (x);                                                                                                        \
  vdp_cmdp_dy        = (y);                                                                                                        \
  vdp_cmdp_color     = (color);                                                                                                    \
  vdp_cmdp_operation = CMD_PSET((operation));                                                                                      \
  vdp_cmd()

#endif
