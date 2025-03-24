#ifndef __V9958_SUPER
#define __V9958_SUPER

#include "v99x8.h"

extern uint8_t register_31_mirror;

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

/**
 * @brief Sets the VDP to Super Graphics Mode 1 (Mid Resolution)
 *
 * Super Graphics Mode 1 characteristics:
 * - Resolution: 360 x 288 pixels (50Hz) or 360 x 240 pixels (60Hz)
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 103,680 bytes (50Hz) or 86,400 bytes (60Hz)
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * @note Only supported on the Super HDMI Tang Nano 20K
 *       custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_1();

/**
 * @brief Sets the VDP to Super Graphics Mode 2 (High Resolution)
 *
 * Super Graphics Mode 2 characteristics:
 * - Resolution: 720 x 576 pixels (50Hz) or 720 x 480 pixels (60Hz)
 * - Colors: Uses 256 palette colors
 * - VRAM Usage: 414,720 bytes (50Hz) or 345,600 bytes (60Hz)
 *
 * Memory organization:
 * - Each pixel uses one byte to specify its color
 * - Colors are selected from palette registers
 *
 * @note Only supported on the Super HDMI Tang Nano 20K
 *       custom kit with the SUPER_RES extensions enabled.
 */
extern void vdp_set_super_graphic_2();

#endif
