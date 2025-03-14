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
  uint8_t green;
  uint8_t blue;
} RGB;

extern uint16_t VDP_IO_DATA;
extern uint16_t VDP_IO_ADDR;
extern uint16_t VDP_IO_STAT;
extern uint16_t VDP_IO_PALT;
extern uint16_t VDP_IO_REGS;

#define VDP_DATA PORT_IO(VDP_IO_DATA)
#define VDP_ADDR PORT_IO(VDP_IO_ADDR)
#define VDP_PALT PORT_IO(VDP_IO_PALT)
#define VDP_REGS PORT_IO(VDP_IO_REGS)

#define vdp_out_cmd(v)      port_out(VDP_IO_ADDR, v)
#define vdp_out_dat(v)      port_out(VDP_IO_DATA, v)
#define vdp_out_pal(v)      port_out(VDP_IO_PALT, v)
#define vdp_out_reg_byte(v) port_out(VDP_IO_REGS, v)

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

extern uint24_t vdp_get_screen_width();
extern uint24_t vdp_get_screen_height();

/**
 * @brief copy data from CPU to VRAM
 *
 * @param source the byte data to be copied
 * @param vdp_address to destination address in VRAM
 * @param length the number of bytes to be copied
 */
extern void vdp_cpu_to_vram(const uint8_t *const source, uint24_t vdp_address, uint16_t length);

/**
 * @brief copy data from CPU to VRAM address 0x000000
 *
 *
 * @param source the byte data to be copied
 * @param length the number of bytes to be copied
 */
extern void vdp_cpu_to_vram0(const uint8_t *const source, uint16_t length);

#define DIX_RIGHT 0
#define DIX_LEFT  4
#define DIY_DOWN  0
#define DIY_UP    8

/**
 * @brief VDP command 'High-speed move VDP to VRAM'
 *
 * Command Code: CMD_HMMV 0xC0
 *
 * The HMMV command is used to paint in a specified rectangular area of the VRAM or the expansion RAM.
 * Since the data to be transferred is done in units of one byte, there is a limitation due to the display mode, on the value for x.
 *
 * @note that in the G4 and G6 modes, the lower one bit, and in the G5 mode, the lower two bits of x and width, are lost.
 *
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param colour the colour code to be painted (as per the current graphics mode)
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 */
extern void vdp_cmd_vdp_to_vram(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t colour, uint8_t direction);

/**
 * @brief VDP command 'High-speed move CPU to VRAM'
 *
 * Command Code: CMD_HMMC 0xF0
 *
 * The HMMC command is used to transfer data from the CPU to the VRAM or the expansion RAM.
 * Since the data to be transferred is done in units of one byte, there is a limitation due to the display mode, on the value for x.
 *
 * @note that in the G4 and G6 modes, the lower one bit, and in the G5 mode, the lower two bits of x and width, are lost.
 *
 * @param source the byte data to be copied to the VDP's VRAM
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param length the number of bytes to be copied (width * height)
 */
extern void vdp_cmd_move_cpu_to_vram(
    const uint8_t *source, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, uint24_t length);

/**
 * @brief Prepare VDP command 'High-speed move CPU to VRAM'
 *
 * This function issues the same command as vdp_cmd_move_cpu_to_vram. The difference is that it expects
 * the data to be sent via the vdp_cmd_send_byte function.
 *
 * @param first_byte the first data byte to be sent to the VDP
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param length the number of bytes to be copied (width * height)
 */
extern void vdp_cmd_move_data_to_vram(
    uint8_t first_byte, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, uint24_t length);

/**
 * @brief transmit the next data byte to the VDP for the current pending command
 *
 * @param next_byte the data to be sent to the VDP
 */
static inline void vdp_cmd_send_byte(uint8_t next_byte) { VDP_REGS = next_byte; }

/**
 * @brief VDP command 'High-speed move VRAM to VRAM, y only'
 *
 * Command Code: CMD_YMMM 0xE0
 *
 * The YMMM command transfers data from the area specified by x, y, to_y, height and the right (or left) edge of the Video RAM, in
 * the y-direction.
 *
 * @param x the starting x-coordinate of the rectangle
 * @param from_y the starting y-coordinate of the rectangle
 * @param to_y the y-coordinate of the top-left corner of the destination rectangle
 * @param height the number of pixels to be copied in the y-direction
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 */
extern void vdp_cmd_move_vram_to_vram_y(uint16_t x, uint16_t from_y, uint16_t to_y, uint16_t height, uint8_t direction);

/**
 * @brief VDP command 'High-speed move VRAM to VRAM'
 *
 * Command Code: CMD_HMMM 0xD0
 *
 * The HMMM command transfers data in a specified rectangular area from the VRAM or the expansion RAM to the VRAM or the expansion
 * RAM. Since the data to be transferred is done in units of one byte, there is a limitation due to the display mode, on the value
 * for x.
 *
 * @param x the starting x-coordinate of the source rectangle
 * @param y the starting y-coordinate of the source rectangle
 * @param to_x the starting x-coordinate of the destination rectangle
 * @param to_y the starting y-coordinate of the destination rectangle
 * @param width the width of the rectangle in pixels to be copied
 * @param height the height of the rectangle in pixels to be copied
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 */
extern void
vdp_cmd_move_vram_to_vram(uint16_t x, uint16_t y, uint16_t to_x, uint16_t to_y, uint16_t width, uint16_t height, uint8_t direction);

/**
 * @brief VDP Command 'Logical Move CPU to VRAM'
 *
 * Command Code: CMD_LMMC 0xB0
 *
 * The LMMC command transfers data from the CPU to the Video or expansion RAM in a specified rectangular area (in x-y coordinates).
 *
 * @param source the byte data to be copied to the VDP's VRAM
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param length the number of bytes to be copied (width * height)
 * @param operation the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)
 */
extern void vdp_cmd_logical_move_cpu_to_vram(const uint8_t *source,
                                             uint16_t       x,
                                             uint16_t       y,
                                             uint16_t       width,
                                             uint16_t       height,
                                             uint8_t        direction,
                                             uint24_t       length,
                                             uint8_t        operation);

/**
 * @brief VDP Command 'Logical Move VRAM to CPU'
 *
 * Command Code: CMD_LMCM 0xA0
 *
 * The LMCM command transfers data from the Video or expansion RAM to the CPU in a specified rectangular area (in x-y coordinates).
 *
 * @param destination the location to store the retrieve data from VRAM
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param length the number of bytes to be copied (width * height)
 */
extern void vdp_cmd_logical_move_vram_to_cpu(
    uint8_t *destination, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, uint24_t length);

/**
 * @brief VDP Command 'Logical Move VRAM to VRAM'
 *
 * Command Code: CMD_LMMM 0x90
 *
 * The LMMM command transfers data in a specified rectangular area from the VRAM or the expansion RAM to the VRAM or the expansion.
 * Since the data to be transferred is done in units of dots, logical operations may be done on the destination data.
 *
 * @param x the starting x-coordinate of the source rectangle
 * @param y the starting y-coordinate of the source rectangle
 * @param to_x the starting x-coordinate of the destination rectangle
 * @param to_y the starting y-coordinate of the destination rectangle
 * @param width the width of the rectangle in pixels to be copied
 * @param height the height of the rectangle in pixels to be copied
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param operation the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)
 */
extern void vdp_cmd_logical_move_vram_to_vram(
    uint16_t x, uint16_t y, uint16_t to_x, uint16_t to_y, uint16_t width, uint16_t height, uint8_t direction, uint8_t operation);

/**
 * @brief VDP Command 'Logical Move VDP to VRAM'
 *
 * Command Code: CMD_LMMV 0x80
 *
 * The LMMV command paints in a specified rectangular area of the Video or Expansion RAM according to a specified color code.
 * The data is transferred in units of one dot, and a logical operation may be done on the destination data.
 *
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param colour the colour code to be painted
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param operation the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)
 */
extern void vdp_cmd_logical_move_vdp_to_vram(
    uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t colour, uint8_t direction, uint8_t operation);

/**
 * @brief VDP LINE drawing command
 *
 * The LINE command draws a straight line in the Video or Expansion RAM. The line drawn is the hypotenuse that results after the
 * long and short sides of a triangle are defined. The two sides are defined as distances from a single point.
 *
 * @param x the starting x-coordinate of the rectangle
 * @param y the starting y-coordinate of the rectangle
 * @param long_length the number of pixels on the long side
 * @param short_length the number of pixels on the short side
 * @param colour the colour code to be painted
 * @param direction the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
 * @param operation the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)
 */
extern void vdp_cmd_line(
    uint16_t x, uint16_t y, uint16_t long_length, uint16_t short_length, uint8_t direction, uint8_t colour, uint8_t operation);

extern int16_t vdp_cmd_search(uint16_t x, uint16_t y, uint8_t colour, uint8_t operation);

extern void vdp_cmd_pset(uint16_t x, uint16_t y, uint8_t colour, uint8_t operation);

extern uint8_t vdp_cmd_point(uint16_t x, uint16_t y);

#define REGISTER_COUNT 12

#define CMD_POINT 0x40
#define CMD_PSET  0x50
#define CMD_SRCH  0x60
#define _CMD_LINE 0x70
#define CMD_LMMV  0x80
#define CMD_LMMM  0x90
#define CMD_LMCM  0xA0
#define CMD_LMMC  0xB0
#define CMD_HMMV  0xC0
#define CMD_HMMM  0xD0
#define CMD_YMMM  0xE0
#define CMD_HMMC  0xF0

#define CMD_LOGIC_IMP 0x00
#define CMD_LOGIC_AND 0x01

// deprecated
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

extern void vdp_draw_line(uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint8_t colour, uint8_t operation);

// dprecated
#define pointSet(x, y, color, operation)                                                                                           \
  vdp_cmdp_dx        = (x);                                                                                                        \
  vdp_cmdp_dy        = (y);                                                                                                        \
  vdp_cmdp_color     = (color);                                                                                                    \
  vdp_cmdp_operation = CMD_PSET((operation));                                                                                      \
  vdp_cmd()

#endif

extern void vdp_set_lines(const uint8_t lines);
extern void vdp_set_refresh(const uint8_t refresh_rate);

/**
 * @brief Sets the VDP to Graphics Mode 7 (G7)
 *
 * Graphics Mode 7 characteristics:
 * - Resolution: 256 x 212 pixels (50Hz) or 256 x 192 pixels (60Hz)
 * - Colors: 256 colors per screen from a fixed color space
 * - VRAM Usage: 128KB (supports two screens)
 * - Sprite Mode: 2
 *
 * Color encoding:
 * Each pixel is represented by 1 byte with the following bit layout:
 * - Bits 7-6: Green (2 bits)
 * - Bits 5-3: Red (3 bits)
 * - Bits 2-0: Blue (3 bits)
 *
 * The pattern name table contains one byte per pixel that directly
 * specifies its color (not a palette index).
 *
 * Controls
 * - Graphics - VRAN pattern name table
 * - Background color: Set by low-order four bits of Register 7
 * - Sprites: Uses VRAM sprite attribute table and sprite pattern table
 *
 */
extern void vdp_set_graphic_7();

/**
 * @brief Sets the VDP to Graphics Mode 6 (G6)
 *
 * Graphics Mode 6 characteristics:
 * - Resolution: 512 x 212 pixels (50Hz) or 512 x 192 pixels (60Hz)
 * - Colors: 16 colors per screen from a palette of 512 colors
 * - VRAM Usage: 128KB (supports two screens)
 * - Sprite Mode: 2
 *
 * Pattern name table characteristics:
 * - One byte represents two horizontal pixels
 * - Each pixel can be assigned one of 16 colors
 * - Colors are selected from a palette of 512 possible colors
 *
 * Controls:
 * - Background color: Set by low-order four bits of Register 7
 * - Sprites: Uses VRAM sprite attribute table and sprite pattern table
 */
extern void vdp_set_graphic_6();

/**
 * @brief Sets the VDP to Graphics Mode 5 (G5)
 *
 * Graphics Mode 5 characteristics:
 * - Resolution: 512 x 212 pixels (50Hz) or 512 x 192 pixels (60Hz)
 * - Colors: 4 colors per screen from a palette of 512 colors
 * - VRAM Usage: 32KB per screen
 * - Sprite Mode: 2
 *
 * Pattern name table characteristics:
 * - One byte represents four horizontal pixels
 * - Each pixel can be assigned one of 4 colors
 * - Colors are selected from a palette of 512 possible colors
 *
 * Hardware tiling features:
 * - Separate color control for even/odd dots
 * - Higher-order two bits specify even dot colors
 * - Lower-order two bits specify odd dot colors
 * - Applies to both sprite and background colors
 * - Sprite dots can display two colors when using tiling
 *
 * Controls:
 * - Background color: Set by low-order four bits of Register 7
 * - Sprite attributes: Set in Register 5 and Register 11
 * - Sprite patterns: Set in Register 6
 * - Sprites: Uses VRAM sprite attribute table and pattern table
 *
 * @note Sprites in this mode are twice the width of graphics dots but can
 *       show two colors per dot when using the tiling function
 */
extern void vdp_set_graphic_5();

/**
 * @brief Sets the VDP to Graphics Mode 4 (G4)
 *
 * Graphics Mode 4 characteristics:
 * - Resolution: 256 x 212 pixels (50Hz) or 256 x 192 pixels (60Hz)
 * - Colors: 16 colors per screen from a palette of 512 colors
 * - VRAM Usage: 32KB per screen
 * - Sprite Mode: 2
 *
 * Pattern name table characteristics:
 * - One byte represents two horizontal pixels
 * - Each pixel can be assigned one of 16 colors
 * - Colors are selected from a palette of 512 possible colors
 *
 * Controls:
 * - Background color: Set by low-order four bits of Register 7
 * - Sprite attributes: Set in Register 5 and Register 11
 * - Sprite patterns: Set in Register 6
 * - Sprites: Uses VRAM sprite attribute table and pattern table
 *
 * @note This is a bit-mapped graphics mode with direct color specification
 *       for each pixel pair
 */
extern void vdp_set_graphic_4();

extern void vdp_set_super_graphic_1();
extern void vdp_set_super_graphic_2();
extern void vdp_set_super_graphic_3();

extern void vdp_set_super_colour(RGB rgb);
