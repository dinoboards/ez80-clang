#ifndef __V9958_SUPER
#define __V9958_SUPER

#include "v99x8.h"

/**
 * @brief Assign LED strip pixel read/write zero based index
 *
 * Assign to this port the index of an RGB pixel you wish to write,
 * or read the discrete RGB values. Values are exchanged with the
 * `WS2812_LEDVAL` port.
 *
 * > Writable only
 *
 */
#define WS2812_LEDIDX PORT_IO(0xFF30)

/**
 * @brief Read or Write the 3 separate RGB values for current pixel
 *
 * After assigning the index with port `WS2812_LEDIDX`, three bytes
 * are expected to be written or read on this port.
 *
 * The three bytes represent the current pixel's Red, Green and Blue 8 bit values.
 *
 * After the 3 bytes are exchanged, the index is auto incremented.
 *
 * > Readable and Writable
 *
 */
#define WS2812_LEDVAL PORT_IO(0xFF31)

/**
 * @brief Define the current maximum number of pixels available on the attached strip.
 *
 *  When auto indexing reaches the end (as per this setting), the index is automatically reset back to 0.
 *
 * > Writable only
 */
#define WS2812_LEDCNT PORT_IO(0xFF32)

/**
 * @brief Set a specific WS2812 LED strip pixel's RGB colour
 *
 * @param index index of pixel
 * @param rgb the red, green, and blue components of the LEDs
 */
static inline void ws2812_set_pixel(const uint8_t index, const RGB rgb) {
  WS2812_LEDIDX = index;

  WS2812_LEDVAL = rgb.red;
  WS2812_LEDVAL = rgb.green;
  WS2812_LEDVAL = rgb.blue;
}

extern uint8_t register_31_mirror;

/**
 * @brief Sets the base VRAM page for VDP command operations
 *
 * Defines the base VRAM address (page) that will be used for all VDP command
 * operations (vdp_cmd_XXXX functions). This allows command operations to target
 * different VRAM pages without changing the display page.
 *
 * @param page The VRAM page number to used.
 *
 * @note This feature is only available with the Super HDMI Tang Nano FPGA module
 * @note Does not change which page is being displayed
 * @see vdp_set_page
 */
extern void vdp_set_command_page(const uint8_t page);

/**
 * @brief Sets the VDP extended palette registers
 *
 * Updates all 256 palette registers with new RGB color values. Each color component
 * (red, green, blue) can have a value from 0-255.
 *
 * Extended Palette features:
 * - 256 palette entries total
 * - Each entry contains RGB values
 * - Used by super graphics modes
 *
 * @param pPalette Pointer to an array of 256 RGB structures containing the new palette colors
 *
 * @note This feature is only available with the Super HDMI Tang Nano FPGA module
 */
extern void vdp_set_extended_palette(RGB *pPalette);

/**
 * @brief Sets a single entry in the VDP extended palette
 *
 * Updates a single palette register with new RGB color values in the 256-color
 * extended palette. Each color component (red, green, blue) can have a value
 * from 0-255.
 *
 * @param index The palette entry to update (0-255)
 * @param palette_entry RGB structure containing the new color values
 *
 * @note This feature is only available with the Super HDMI Tang Nano FPGA module
 * @see vdp_set_extended_palette
 */
extern void vdp_set_extended_palette_entry(uint8_t index, RGB palette_entry);

/*
  Super Graphics Modes:
   1: 320x200 @ 60hz
   2: 320x240 @ 50hz
   3: 360x240 @ 60hz
   4: 360x288 @ 50hz
   5: 640x400 @ 60hz
   6: 640x480 @ 50hz
   7: 720x480 @ 60Hz
   8: 720x576 @ 50Hz
   9: 720x240 @ 60Hz
  10: 720x288 @ 50Hz

  //TODO MODES
  11: 640x240 @ 60hz (720-80)*(480/2)
  12: 640x256 @ 50hz (720-80)*(576/2-32)
*/

/**
 * @brief Sets the VDP to Super Graphics Mode 1
 *
 * Super Graphics Mode 1 characteristics:
 * - Resolution: 320 x 200 pixels @ 60Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 64,000 bytes
 * - This mode has a small border around the main view
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 * - Border colour as per Register #7
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_1();

/**
 * @brief Sets the VDP to Super Graphics Mode 2
 *
 * Super Graphics Mode 2 characteristics:
 * - Resolution: 320 x 240 pixels @ 60Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 76,800 bytes
 * - This mode has a small border around the main view
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 * - Border colour as per Register #7
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_2();

/**
 * @brief Sets the VDP to Super Graphics Mode 3
 *
 * Super Graphics Mode 3 characteristics:
 * - Resolution: 360 x 240 @ 60Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 86,400
 * - This mode will fill the entire screen space
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_3();

/**
 * @brief Sets the VDP to Super Graphics Mode 4
 *
 * Super Graphics Mode 4 characteristics:
 * - Resolution: 360 x 288 @ 50Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 103,680
 * - This mode will fill the entire screen space
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_4();

/**
 * @brief Sets the VDP to Super Graphics Mode 5
 *
 * Super Graphics Mode 5 characteristics:
 * - Resolution: 640 x 400 @ 60Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 256,000
 * - This mode has a small border around the main view
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 * - Border colour as per Register #7
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_5();

/**
 * @brief Sets the VDP to Super Graphics Mode 6
 *
 * Super Graphics Mode 6 characteristics:
 * - Resolution: 640 x 480 @ 50Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 307,200
 * - This mode has a small border around the main view
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 * - Border colour as per Register #7
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_6();

/**
 * @brief Sets the VDP to Super Graphics Mode 7
 *
 * Super Graphics Mode 7 characteristics:
 * - Resolution: 720 x 480 @ 60Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 345,600
 * - This mode will fill the entire screen space
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_7();

/**
 * @brief Sets the VDP to Super Graphics Mode 8
 *
 * Super Graphics Mode 8 characteristics:
 * - Resolution: 720 x 576 @ 50Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 414,720
 * - This mode will fill the entire screen space
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_8();

/**
 * @brief Sets the VDP to Super Graphics Mode 9
 *
 * Super Graphics Mode 9 characteristics:
 * - Resolution: 640 x 512 @ 50Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 327, 680 bytes
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_9();

/**
 * @brief Sets the VDP to Super Graphics Mode 9
 *
 * Super Graphics Mode 10 characteristics:
 * - Resolution: 640 x 256 @ 50Hz
 * - Colors: Uses 256 palette colors
 * - VRAM Usage:  bytes
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * > Only supported on the Super HDMI Tang Nano 20K
 * > custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_10();

extern void vdp_set_super_graphic(uint8_t mode);
#endif
