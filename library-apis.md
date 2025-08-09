# eZ80 Clang

The ez80 clang compiler, is a customised version of clang with ez80 support.  It includes support libraries and other facilities to build .COM and .EXE files for the `eZ80 for RC` platform.

### Table of Contents

- Libraries
  - [Memory Models](#memory-models)
  - [Library v99x8](#library-v99x8)
    - [Functions](#v99x8-functions)
    - [Types](#v99x8-types)
  - [Library v99x8-super](#library-v99x8-super)
    - [Functions](#v99x8-super-functions)
  - [Library CP/M](#library-cpm)
    - [Functions](#cpm-functions)
    - [Types](#cpm-types)
  - [Library HBIOS](#library-hbios)
  - [Library eZ80](#library-ez80)
  - [Library eZ80 Firmware](#library-ez80-firmware)

## Memory Models

The compiler can build one of two different binaries for executing on your system.  Both binary types assume the code will be run on a eZ80 CPU with the CP/M operating system running
in the eZ80's compatibility mode.

The type of binary is selected by specifying the required memory model on the `ez80-cc`'s commmand line with the `mem-model` argument.

```
--mem-model type  Specify the memory model: 64KB (default) or 2MB.
```

### COM - 64K Memory

In this mode, the binary must be less than 64K as per a standard `.COM` binary for CP/M.  But unlike standard Z80 .COM binaries, this compiler will include a specific piece of startup code, to switch the CPU to the eZ80's ADL mode -- allowing for full use of the CPU's instruction set.

When your program exits, the code will automatically switch the CPU back to Z80 compatibility mode.

If your program makes any CP/M (or HBIOS) calls, the libraries will ensure the CPU is in Z80 mode whilst executing the CP/M function.

### EXE - 2MB Memory

> This mode requires your ***eZ80 for RC*** have access to a extended linear memory module.

The binary produced, by this mode, will have a .EXE extension and can be larger than 64K.  To execute such a binary, you need to use the `EXE.COM` loader (available within the releases of the [ez80-for-rc](https://github.com/dinoboards/ez80-for-rc/releases) project)

Like the COM version, any calls to CP/M (or HBIOS) will be correctly managed and marhsalled with the CPU's Z80 compatibility mode.

One important point to note for the EXE model, is that any pointers passed to CP/M (or HBIOS) functions must exist within the 64K segement used by CP/M.

You can use the `__attribute((section))` directive to make the c compiler allocate variables
within the required section.

```c
uint8_t buffer[512] __attribute__((section(".bss_z80")));
```


### The available memory sections

The linker configuration used by both memory models provide the following sections:

| Section | 64K .COM Model | 2MB .EXE Model |
| ------------ | --- | --- |
|**.text**         | ADL code | ADL code allocated within extended linear memory, typically starting at $200400 |
|**.rodata**     | read only data | read only data allocated to the extended memory range |
|**.data**    | writable data | writable data allocated to the extended memory range |
|**.bss**   | uninitialised data | uninitialised data allocated to the extended memory range |
|**.bss_z80**   | uninitialised data | uninitialised data allocated within the Z80 compatible segment - typically 0x03xxxx |
|**.text_on_chip**    | for function to be executed from the eZ80 onboard fast RAM | for function to be executed from the eZ80 onboard fast RAM
|**.data_on_chip**    | initialised data copied to the eZ80's onboard fast RAM | initialised data copied to the eZ80's onboard fast RAM |
|**.bss_on_chip**   |uninitialised data allocated within eZ80's onboard fast RAM | uninitialised data allocated within eZ80's onboard fast RAM |

---

## Library V99X8

*Functions and supporting structures to access the V9958/V9938 on-chip functions.*

The V9958 and V9938 Video Display Process from YAMAHA has many on chip features.  It
is recommended you familiarise yourself with the V9958/V9938 spec docs from YAMAHA.

* [V9938 Datasheet](https://github.com/dinoboards/yellow-msx-series-for-rc2014/blob/main/datasheets/yamaha_v9938.pdf)
* [V9938 Datasheet](https://github.com/dinoboards/yellow-msx-series-for-rc2014/blob/main/datasheets/yamaha_v9958.pdf)


### V99X8 Functions



#### vdp_out_cmd

*Write byte to the VDP's COMMAND port*

```cpp
void vdp_out_cmd(const uint8_t v)
```



**Params:**

- `v` - byte to be sent to the COMMAND port


---



#### vdp_init

*Discover version of VDP and initialise its internal registers*

```cpp
uint8_t vdp_init()
```


> does not enable any specific graphics mode

> should be called before any vdp operations


---



#### vdp_set_palette

*Sets the VDP palette registers*

```cpp
void vdp_set_palette(RGB *palette)
```


Updates all 16 palette registers with new RGB color values. Each color component
(red, green, blue) can have a value from 0-7, giving 512 possible colors.

Palette organization:
- 16 palette entries total
- Each entry contains RGB values
- Used by graphics modes 4-6



**Params:**

- `palette` - Pointer to an array of 16 RGB structures containing the new palette colors

> For Graphics Mode 7, the palette is fixed and cannot be changed


---



#### vdp_set_extended_palette

*Sets the VDP extended palette registers*

```cpp
void vdp_set_extended_palette(RGB *pPalette)
```


Updates all 256 palette registers with new RGB color values. Each color component
(red, green, blue) can have a value from 0-255.

Extended Palette features:
- 256 palette entries total
- Each entry contains RGB values
- Used by super graphics modes



**Params:**

- `pPalette` - Pointer to an array of 256 RGB structures containing the new palette colors

> This feature is only available with the Super HDMI Tang Nano FPGA module


---



#### vdp_set_extended_palette_entry

*Sets a single entry in the VDP extended palette*

```cpp
void vdp_set_extended_palette_entry(uint8_t index, RGB palette_entry)
```


Updates a single palette register with new RGB color values in the 256-color
extended palette. Each color component (red, green, blue) can have a value
from 0-255.



**See also:**

* [vdp_set_extended_palette](#vdp_set_extended_palette)

**Params:**

- `index` - The palette entry to update (0-255)
- `palette_entry` - RGB structure containing the new color values

> This feature is only available with the Super HDMI Tang Nano FPGA module


---



#### vdp_set_page

*Switches between VRAM pages in supported graphics modes*

```cpp
void vdp_set_page(const uint8_t page)
```



Changes the active VRAM page for graphics modes that support page flipping (G6 and G7).
Each page represents a complete screen buffer of 128KB. Switching pages allows for
double-buffering techniques.

The number of pages available are dependant on the available memory and the mode selected


**Params:**

- `page` - The VRAM page number to be used.

> Only works in Graphics modes 6 and 7 and (super graphics modes if available)


---



#### vdp_get_screen_width

*Get the current screen width*

```cpp
screen_size_t vdp_get_screen_width()
```


Returns the width in pixels of the current video mode:
- Standard modes: 256 or 512 pixels
- Super Graphics Mode 1: 360 pixels
- Super Graphics Mode 2: 720 pixels

**Returns:**

- uint24_t The current screen width in pixels

---



#### vdp_get_screen_height

*Get the current screen height*

```cpp
screen_size_t vdp_get_screen_height()
```


Returns the height in pixels of the current video mode:
- Standard modes: 192 (60Hz) or 212 (50Hz) lines
- Super Graphics Mode 1: 240 (60Hz) or 288 (50Hz) lines
- Super Graphics Mode 2: 480 (60Hz) or 576 (50Hz) lines

**Returns:**

- uint24_t The current screen height in pixels

---



#### vdp_get_screen_max_unique_colours

*Return current maximum number of unique colours that can be displayed*

```cpp
uint16_t vdp_get_screen_max_unique_colours()
```


For all modes other than Graphics Mode 7, return the palette depth look up - typically
256, 16 or 4 unique colours

For Graphics mode 7, return 256

**Returns:**

- uint24_t the max number of unique colours

---



#### vdp_cpu_to_vram

*copy data from CPU to VRAM*

```cpp
void vdp_cpu_to_vram(const uint8_t *const source, screen_addr_t vdp_address, uint16_t length)
```



**Params:**

- `source` - the byte data to be copied
- `vdp_address` - to destination address in VRAM
- `length` - the number of bytes to be copied


---



#### vdp_cpu_to_vram0

*copy data from CPU to VRAM address 0x000000*

```cpp
void vdp_cpu_to_vram0(const uint8_t *const source, uint16_t length)
```




**Params:**

- `source` - the byte data to be copied
- `length` - the number of bytes to be copied


---



#### vdp_cmd_vdp_to_vram

*VDP command 'High-speed move VDP to VRAM'*

```cpp
void vdp_cmd_vdp_to_vram(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t colour, uint8_t direction)
```


Command Code: CMD_HMMV 0xC0

The HMMV command is used to paint in a specified rectangular area of the VRAM or the expansion RAM.
Since the data to be transferred is done in units of one byte, there is a limitation due to the display mode, on the value for x.



**Params:**

- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `colour` - the colour code to be painted (as per the current graphics mode)
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)

> that in the G4 and G6 modes, the lower one bit, and in the G5 mode, the lower two bits of x and width, are lost.


---



#### vdp_cmd_move_cpu_to_vram

*VDP command 'High-speed move CPU to VRAM'*

```cpp
void vdp_cmd_move_cpu_to_vram(const uint8_t *source, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, screen_addr_t length)
```


Command Code: CMD_HMMC 0xF0

The HMMC command is used to transfer data from the CPU to the VRAM or the expansion RAM.
Since the data to be transferred is done in units of one byte, there is a limitation due to the display mode, on the value for x.



**Params:**

- `source` - the byte data to be copied to the VDP's VRAM
- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `length` - the number of bytes to be copied (width * height)

> that in the G4 and G6 modes, the lower one bit, and in the G5 mode, the lower two bits of x and width, are lost.


---



#### vdp_cmd_move_data_to_vram

*Prepare VDP command 'High-speed move CPU to VRAM'*

```cpp
void vdp_cmd_move_data_to_vram(uint8_t first_byte, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction)
```


This function issues the same command as vdp_cmd_move_cpu_to_vram. The difference is that it expects
the data to be sent via the vdp_cmd_send_byte function.

Interrupts are recommended to be disabled before starting the data transfer
After data transfer with vdp_cmd_send_byte is completed you must call vdp_reset_status_reg and then re-enable
interrupts


**Params:**

- `first_byte` - the first data byte to be sent to the VDP
- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)


---



#### vdp_reset_status_reg

*Restore the current select status register to S#0*

```cpp
void vdp_reset_status_reg()
```


Interrupt handlers will typically expect the status register to
be 0 for detecting the interrupt flag

If the selected status register is changed, it must be done while interrupts
are disabled, and before re-enabling interrupts, this function should be called.

---



#### vdp_cmd_send_byte

*transmit the next data byte to the VDP for the current pending command*

```cpp
bool vdp_cmd_send_byte(const uint8_t next_byte)
```



**Params:**

- `next_byte` - the data to be sent to the VDP

**Returns:**

- false timeout waiting for VDP to accept bye

---



#### vdp_cmd_move_vram_to_vram_y

*VDP command 'High-speed move VRAM to VRAM, y only'*

```cpp
void vdp_cmd_move_vram_to_vram_y(uint16_t x, uint16_t from_y, uint16_t to_y, uint16_t height, uint8_t direction)
```


Command Code: CMD_YMMM 0xE0

The YMMM command transfers data from the area specified by x, y, to_y, height and the right (or left) edge of the Video RAM, in
the y-direction.


**Params:**

- `x` - the starting x-coordinate of the rectangle
- `from_y` - the starting y-coordinate of the rectangle
- `to_y` - the y-coordinate of the top-left corner of the destination rectangle
- `height` - the number of pixels to be copied in the y-direction
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)


---



#### vdp_cmd_move_vram_to_vram

*VDP command 'High-speed move VRAM to VRAM'*

```cpp
void vdp_cmd_move_vram_to_vram(uint16_t x, uint16_t y, uint16_t to_x, uint16_t to_y, uint16_t width, uint16_t height, uint8_t direction)
```


Command Code: CMD_HMMM 0xD0

The HMMM command transfers data in a specified rectangular area from the VRAM or the expansion RAM to the VRAM or the expansion
RAM. Since the data to be transferred is done in units of one byte, there is a limitation due to the display mode, on the value
for x.


**Params:**

- `x` - the starting x-coordinate of the source rectangle
- `y` - the starting y-coordinate of the source rectangle
- `to_x` - the starting x-coordinate of the destination rectangle
- `to_y` - the starting y-coordinate of the destination rectangle
- `width` - the width of the rectangle in pixels to be copied
- `height` - the height of the rectangle in pixels to be copied
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)


---



#### vdp_cmd_logical_move_cpu_to_vram

*VDP Command 'Logical Move CPU to VRAM'*

```cpp
void vdp_cmd_logical_move_cpu_to_vram(const uint8_t *const source, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, screen_addr_t length, uint8_t operation)
```


Command Code: CMD_LMMC 0xB0

The LMMC command transfers data from the CPU to the Video or expansion RAM in a specified rectangular area (in x-y coordinates).


**Params:**

- `source` - the byte data to be copied to the VDP's VRAM
- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `length` - the number of bytes to be copied (width * height)
- `operation` - the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)


---



#### vdp_cmd_logical_move_data_to_vram

*Prepare VDP command 'Logical Move CPU to VRAM'*

```cpp
void vdp_cmd_logical_move_data_to_vram(uint8_t first_byte, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, uint8_t operation)
```


Command Code: CMD_LMMC 0xB0

This function issues the same command as vdp_cmd_move_vram_to_vram. The difference is that it expects
the data to be sent via the vdp_cmd_send_byte function.

Interrupts are recommended to be disabled before starting the data transfer
After data transfer with vdp_cmd_send_byte is completed, you must call vdp_reset_status_reg and then re-enable
interrupts


**Params:**

- `first_byte` - the first data byte to be sent to the VDP
- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `operation` - the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)


---



#### vdp_cmd_logical_move_vram_to_cpu

*VDP Command 'Logical Move VRAM to CPU'*

```cpp
void vdp_cmd_logical_move_vram_to_cpu(uint8_t *destination, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, screen_addr_t length)
```


Command Code: CMD_LMCM 0xA0

The LMCM command transfers data from the Video or expansion RAM to the CPU in a specified rectangular area (in x-y coordinates).


**Params:**

- `destination` - the location to store the retrieve data from VRAM
- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `length` - the number of bytes to be copied (width * height)


---



#### vdp_cmd_logical_move_vram_to_vram

*VDP Command 'Logical Move VRAM to VRAM'*

```cpp
void vdp_cmd_logical_move_vram_to_vram(uint16_t x, uint16_t y, uint16_t to_x, uint16_t to_y, uint16_t width, uint16_t height, uint8_t direction, uint8_t operation)
```


Command Code: CMD_LMMM 0x90

The LMMM command transfers data in a specified rectangular area from the VRAM or the expansion RAM to the VRAM or the expansion.
Since the data to be transferred is done in units of dots, logical operations may be done on the destination data.


**Params:**

- `x` - the starting x-coordinate of the source rectangle
- `y` - the starting y-coordinate of the source rectangle
- `to_x` - the starting x-coordinate of the destination rectangle
- `to_y` - the starting y-coordinate of the destination rectangle
- `width` - the width of the rectangle in pixels to be copied
- `height` - the height of the rectangle in pixels to be copied
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `operation` - the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)


---



#### vdp_cmd_logical_move_vdp_to_vram

*VDP Command 'Logical Move VDP to VRAM'*

```cpp
void vdp_cmd_logical_move_vdp_to_vram(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t colour, uint8_t direction, uint8_t operation)
```


Command Code: CMD_LMMV 0x80

The LMMV command paints in a specified rectangular area of the Video or Expansion RAM according to a specified color code.
The data is transferred in units of one dot, and a logical operation may be done on the destination data.


**Params:**

- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `width` - the width of the rectangle in pixels
- `height` - the height of the rectangle in pixels
- `colour` - the colour code to be painted
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `operation` - the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)


---



#### vdp_cmd_line

*VDP LINE drawing command*

```cpp
void vdp_cmd_line(uint16_t x, uint16_t y, uint16_t long_length, uint16_t short_length, uint8_t direction, uint8_t colour, uint8_t operation)
```


The LINE command draws a straight line in the Video or Expansion RAM. The line drawn is the hypotenuse that results after the
long and short sides of a triangle are defined. The two sides are defined as distances from a single point.


**Params:**

- `x` - the starting x-coordinate of the rectangle
- `y` - the starting y-coordinate of the rectangle
- `long_length` - the number of pixels on the long side
- `short_length` - the number of pixels on the short side
- `colour` - the colour code to be painted
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `operation` - the logical operation to be performed (CMD_LOGIC_IMP, CMD_LOGIC_AND, ...)


---



#### vdp_cmd_wait_completion

*wait for any pending command to complete*

```cpp
void vdp_cmd_wait_completion()
```


Will eventually time out (conducts upto status $100000 tests, before timing out)

---



#### vdp_set_refresh

*Set the refresh rate of the display output*

```cpp
void vdp_set_refresh(const uint8_t refresh_rate)
```


Refresh can be set to 50Hz or 60Hz

Apply this setting before setting a standard graphics mode

This function is not applicable for super res modes as
each super graphics mode already configures a specific refresh
rate

Possible values are:
`PAL` or 50 to select 50Hz, and `NTSC` or 60 to select 60Hz


**Params:**

- `refresh_rate` - to be applied


---



#### vdp_get_refresh

*Return the current refresh rate*

```cpp
uint8_t vdp_get_refresh()
```




**Params:**

- `refresh_rate` - the actual refresh rate

> the return value is one of 50 or 60

> will never equate to PAL or NTSC


---



#### vdp_set_graphic_7

*Sets the VDP to Graphics Mode 7 (G7)*

```cpp
void vdp_set_graphic_7()
```


Graphics Mode 7 characteristics:
- Resolution: 256 x 212 pixels (50Hz) or 256 x 192 pixels (60Hz)
- Colors: 256 colors per screen from a fixed color space
- VRAM Usage: 128KB (supports two screens)
- Sprite Mode: 2

Color encoding:
Each pixel is represented by 1 byte with the following bit layout:
- Bits 7-6: Green (2 bits)
- Bits 5-3: Red (3 bits)
- Bits 2-0: Blue (3 bits)

The pattern name table contains one byte per pixel that directly
specifies its color (not a palette index).

Controls
- Graphics - VRAN pattern name table
- Background color: Set by low-order four bits of Register 7
- Sprites: Uses VRAM sprite attribute table and sprite pattern table


---



#### vdp_set_graphic_6

*Sets the VDP to Graphics Mode 6 (G6)*

```cpp
void vdp_set_graphic_6()
```


Graphics Mode 6 characteristics:
- Resolution: 512 x 212 pixels (50Hz) or 512 x 192 pixels (60Hz)
- Colors: 16 colors per screen from a palette of 512 colors
- VRAM Usage: 128KB (supports two screens)
- Sprite Mode: 2

Pattern name table characteristics:
- One byte represents two horizontal pixels
- Each pixel can be assigned one of 16 colors
- Colors are selected from a palette of 512 possible colors

Controls:
- Background color: Set by low-order four bits of Register 7
- Sprites: Uses VRAM sprite attribute table and sprite pattern table

---



#### vdp_set_graphic_5

*Sets the VDP to Graphics Mode 5 (G5)*

```cpp
void vdp_set_graphic_5()
```


Graphics Mode 5 characteristics:
- Resolution: 512 x 212 pixels (50Hz) or 512 x 192 pixels (60Hz)
- Colors: 4 colors per screen from a palette of 512 colors
- VRAM Usage: 32KB per screen
- Sprite Mode: 2

Pattern name table characteristics:
- One byte represents four horizontal pixels
- Each pixel can be assigned one of 4 colors
- Colors are selected from a palette of 512 possible colors

Hardware tiling features:
- Separate color control for even/odd dots
- Higher-order two bits specify even dot colors
- Lower-order two bits specify odd dot colors
- Applies to both sprite and background colors
- Sprite dots can display two colors when using tiling

Controls:
- Background color: Set by low-order four bits of Register 7
- Sprite attributes: Set in Register 5 and Register 11
- Sprite patterns: Set in Register 6
- Sprites: Uses VRAM sprite attribute table and pattern table

      show two colors per dot when using the tiling function
> Sprites in this mode are twice the width of graphics dots but can


---



#### vdp_set_graphic_4

*Sets the VDP to Graphics Mode 4 (G4)*

```cpp
void vdp_set_graphic_4()
```


Graphics Mode 4 characteristics:
- Resolution: 256 x 212 pixels (50Hz) or 256 x 192 pixels (60Hz)
- Colors: 16 colors per screen from a palette of 512 colors
- VRAM Usage: 32KB per screen
- Sprite Mode: 2

Pattern name table characteristics:
- One byte represents two horizontal pixels
- Each pixel can be assigned one of 16 colors
- Colors are selected from a palette of 512 possible colors

Controls:
- Background color: Set by low-order four bits of Register 7
- Sprite attributes: Set in Register 5 and Register 11
- Sprite patterns: Set in Register 6
- Sprites: Uses VRAM sprite attribute table and pattern table

      for each pixel pair
> This is a bit-mapped graphics mode with direct color specification


---



#### vdp_get_graphic_mode

*Retrieve the current activated graphics mode*

```cpp
uint8_t vdp_get_graphic_mode()
```


Super graphics mode are indicated with high bit set

**Returns:**

- uint8_t the current graphics mode

---



#### vdp_set_graphic_mode

*Set the graphics or super graphics mode*

```cpp
void vdp_set_graphic_mode(uint8_t mode)
```


If high bit set, then a super graphics mode is selected

> Super graphics modes are only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.


**Params:**

- `mode` - the graphic mode to enable


---



### V99X8 Types



#### RGB

*an 8Bit per color RGB colour code*

```cpp
typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} RGB;
```



---


## Library V99X8-SUPER

*Functions to support extended feature beyond stock V9958 interface of the HDMI for RC kit*

The HDMI for RC kit supports, if flashed with appropriate firmware, it will support extended graphics modes
and the ability to manage a WS8212 LED strip.

**Extended Graphics**

The *HDMI for RC* offers three base graphics modes, with modifiers for viewport sizing, colour palette depth and refresh rate.

The 3 base modes are as follows:

| Base Mode | Native HDMI Resolution | Rendered Resolution | Refresh Rate |
| :-------: | :--------:             | :-----------------: | :----------: |
|   Half    |   720x480              | 720x240             |      60Hz    |
|   Half    |   720x576              | 720x288             |      50Hz    |
|   Mid     |   720x480              | 360x240             |      60Hz    |
|   Mid     |   720x576              | 360x288             |      50Hz    |
|   High    |   720x480              | 720x480             |      60Hz    |
|   High    |   720x576              | 720x576             |      50Hz    |

Each of the above base modes can be adjusted to have a border applied, reducing the effective rendered resolution.
Modes with lower resolutions have reduced memory needs and offer faster command processing.

**Super Graphics Modes**

One of the following pre-configured Super Graphics Modes can be selected by invoking the appropriate library
function: `vdp_set_super_graphic_XX` or  `vdp_set_super_graphic(mode)`.


| Super Mode | Resolution | Memory Size (bytes) | Refresh Rate | Palette Size | Base Mode | Full/Bordered |
| :--------: | :--------: | :-----------------: | :----------: | :----------: | :-------: | :-----------: |
|  1  (0x01)   | 320x200    | 64000             |     60Hz     |     256      |   mid     |   Bordered    |
|  2  (0x02)   | 320x240    | 76800             |     50Hz     |     256      |   mid     |   Bordered    |
|  3  (0x03)   | 360x240    | 86400             |     60Hz     |     256      |   mid     |  Full screen  |
|  4  (0x04)   | 360x288    | 103780            |     50Hz     |     256      |   mid     |  Full Screen  |
|  5  (0x05)   | 640x400    | 256000            |     60Hz     |     256      |   high    |   Bordered    |
|  6  (0x06)   | 640x480    | 307200            |     50Hz     |     256      |   high    |   Bordered    |
|  7  (0x07)   | 720x480    | 345600            |     60Hz     |     256      |   high    |  Full Screen  |
|  8  (0x08)   | 720x576    | 414720            |     50Hz     |     256      |   high    |  Full Screen  |
|  9  (0x09)   | 640x512    | 327680            |     50Hz     |     256      |   high    |   Bordered    |
|  10 (0x0A)   | 640x256    | 163840            |     50Hz     |     256      |   half    |   Bordered    |
|  11 (0x0B)   | 720x240    | 172800            |     60Hz     |     256      |   half    |  Full Screen  |
|  12 (0x0C)   | 720x288    | 207360            |     50Hz     |     256      |   half    |  Full Screen  |
|  21 (0x15)   | 640x400    | 128000            |     60Hz     |      16      |   high    |   Bordered    |
|  22 (0x16)   | 640x480    | 153600            |     50Hz     |      16      |   high    |   Bordered    |
|  23 (0x17)   | 720x480    | 172800            |     60Hz     |      16      |   high    |  Full Screen  |
|  24 (0x18)   | 720x576    | 207360            |     50Hz     |      16      |   high    |  Full Screen  |
|  25 (0x19)   | 640x512    | 163840            |     50Hz     |      16      |   high    |   Bordered    |
|  26 (0x1A)   | 640x256    | 81920             |     50Hz     |      16      |   half    |   Bordered    |
|  27 (0x1B)   | 720x240    | 86400             |     60Hz     |      16      |   half    |  Full Screen  |
|  28 (0x1C)   | 720x288    | 103680            |     50Hz     |      16      |   half    |  Full Screen  |


### V99X8-SUPER Functions



#### WS2812_LEDIDX

*Assign LED strip pixel read/write zero based index*

```cpp
#define WS2812_LEDIDX PORT_IO(0xFF30)
```


Assign to this port the index of an RGB pixel you wish to write,
or read the discrete RGB values. Values are exchanged with the
`WS2812_LEDVAL` port.

> Writable only


---



#### WS2812_LEDVAL

*Read or Write the 3 separate RGB values for current pixel*

```cpp
#define WS2812_LEDVAL PORT_IO(0xFF31)
```


After assigning the index with port `WS2812_LEDIDX`, three bytes
are expected to be written or read on this port.

The three bytes represent the current pixel's Red, Green and Blue 8 bit values.

After the 3 bytes are exchanged, the index is auto incremented.

> Readable and Writable


---



#### WS2812_LEDCNT

*Define the current maximum number of pixels available on the attached strip.*

```cpp
#define WS2812_LEDCNT PORT_IO(0xFF32)
```


 When auto indexing reaches the end (as per this setting), the index is automatically reset back to 0.

> Writable only

---



#### ws2812_set_pixel

*Set a specific WS2812 LED strip pixel's RGB colour*

```cpp
void ws2812_set_pixel(const uint8_t index, const RGB rgb)
```



**Params:**

- `index` - index of pixel
- `rgb` - the red, green, and blue components of the LEDs


---



#### vdp_set_command_page

*Sets the base VRAM page for VDP command operations*

```cpp
void vdp_set_command_page(const uint8_t page)
```


Defines the base VRAM address (page) that will be used for all VDP command
operations (vdp_cmd_XXXX functions). This allows command operations to target
different VRAM pages without changing the display page.



**See also:**

* [vdp_set_page](#vdp_set_page)

**Params:**

- `page` - The VRAM page number to used.

> This feature is only available with the Super HDMI Tang Nano FPGA module

> Does not change which page is being displayed


---



#### vdp_set_extended_palette

*Sets the VDP extended palette registers*

```cpp
void vdp_set_extended_palette(RGB *pPalette)
```


Updates all 256 palette registers with new RGB color values. Each color component
(red, green, blue) can have a value from 0-255.

Extended Palette features:
- 256 palette entries total
- Each entry contains RGB values
- Used by super graphics modes



**Params:**

- `pPalette` - Pointer to an array of 256 RGB structures containing the new palette colors

> This feature is only available with the Super HDMI Tang Nano FPGA module


---



#### vdp_set_extended_palette_entry

*Sets a single entry in the VDP extended palette*

```cpp
void vdp_set_extended_palette_entry(uint8_t index, RGB palette_entry)
```


Updates a single palette register with new RGB color values in the 256-color
extended palette. Each color component (red, green, blue) can have a value
from 0-255.



**See also:**

* [vdp_set_extended_palette](#vdp_set_extended_palette)

**Params:**

- `index` - The palette entry to update (0-255)
- `palette_entry` - RGB structure containing the new color values

> This feature is only available with the Super HDMI Tang Nano FPGA module


---



#### vdp_set_super_graphic_1

*Sets the VDP to Super Graphics Mode 1*

```cpp
void vdp_set_super_graphic_1()
```


Super Graphics Mode 1 characteristics:
- Resolution: 320 x 200 pixels @ 60Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 64,000 bytes
- This mode has a small border around the main view

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers
- Border colour as per Register #7

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_2

*Sets the VDP to Super Graphics Mode 2*

```cpp
void vdp_set_super_graphic_2()
```


Super Graphics Mode 2 characteristics:
- Resolution: 320 x 240 pixels @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 76,800 bytes
- This mode has a small border around the main view

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers
- Border colour as per Register #7

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_3

*Sets the VDP to Super Graphics Mode 3*

```cpp
void vdp_set_super_graphic_3()
```


Super Graphics Mode 3 characteristics:
- Resolution: 360 x 240 @ 60Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 86,400
- This mode will fill the entire screen space

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_4

*Sets the VDP to Super Graphics Mode 4*

```cpp
void vdp_set_super_graphic_4()
```


Super Graphics Mode 4 characteristics:
- Resolution: 360 x 288 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 103,680
- This mode will fill the entire screen space

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_5

*Sets the VDP to Super Graphics Mode 5*

```cpp
void vdp_set_super_graphic_5()
```


Super Graphics Mode 5 characteristics:
- Resolution: 640 x 400 @ 60Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 256,000
- This mode has a small border around the main view

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers
- Border colour as per Register #7

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_6

*Sets the VDP to Super Graphics Mode 6*

```cpp
void vdp_set_super_graphic_6()
```


Super Graphics Mode 6 characteristics:
- Resolution: 640 x 480 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 307,200
- This mode has a small border around the main view

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers
- Border colour as per Register #7

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_7

*Sets the VDP to Super Graphics Mode 7*

```cpp
void vdp_set_super_graphic_7()
```


Super Graphics Mode 7 characteristics:
- Resolution: 720 x 480 @ 60Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 345,600
- This mode will fill the entire screen space

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_8

*Sets the VDP to Super Graphics Mode 8*

```cpp
void vdp_set_super_graphic_8()
```


Super Graphics Mode 8 characteristics:
- Resolution: 720 x 576 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 414,720
- This mode will fill the entire screen space

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_9

*Sets the VDP to Super Graphics Mode 9*

```cpp
void vdp_set_super_graphic_9()
```


Super Graphics Mode 9 characteristics:
- Resolution: 640 x 512 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 327, 680 bytes

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_10

*Sets the VDP to Super Graphics Mode 10*

```cpp
void vdp_set_super_graphic_10()
```


Super Graphics Mode 10 characteristics:
- Resolution: 640 x 256 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 163,840 bytes

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_11

*Sets the VDP to Super Graphics Mode 11*

```cpp
void vdp_set_super_graphic_11()
```


Super Graphics Mode 11 characteristics:
- Resolution: 720 x 240 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 172,800 bytes

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_12

*Sets the VDP to Super Graphics Mode 12*

```cpp
void vdp_set_super_graphic_12()
```


Super Graphics Mode 12 characteristics:
- Resolution: 720 x 288 @ 60Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 207,360 bytes

Memory organization:
- Each pixel uses one byte to specify its color
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_21

*Sets the VDP to Super Graphics Mode 21*

```cpp
void vdp_set_super_graphic_21()
```


Same as Super Graphics Mode 5, but with reduced colour palette size

Super Graphics Mode 21 characteristics:
- Resolution: 640 x 400 @ 60Hz
- Colors: Uses 16 palette colors
- VRAM Usage: 128,000
- This mode has a small border around the main view

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers
- Border colour as per Register #7

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_22

*Sets the VDP to Super Graphics Mode 22*

```cpp
void vdp_set_super_graphic_22()
```


Super Graphics Mode 22 characteristics:
- Resolution: 640 x 480 @ 50Hz
- Colors: Uses 16 palette colors
- VRAM Usage: 153,600
- This mode has a small border around the main view

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers
- Border colour as per Register #7

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_23

*Sets the VDP to Super Graphics Mode 23*

```cpp
void vdp_set_super_graphic_23()
```


Same as Super Graphics Mode 7, but with reduced colour palette size

Super Graphics Mode 23 characteristics:
- Resolution: 720 x 480 @ 60Hz
- Colors: Uses 16 palette colors
- VRAM Usage: 172,800
- This mode will fill the entire screen space

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_24

*Sets the VDP to Super Graphics Mode 24*

```cpp
void vdp_set_super_graphic_24()
```


Super Graphics Mode 24 characteristics:
- Resolution: 720 x 576 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 207,360
- This mode will fill the entire screen space

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_25

*Sets the VDP to Super Graphics Mode 25*

```cpp
void vdp_set_super_graphic_25()
```


Super Graphics Mode 25 characteristics:
- Resolution: 640 x 512 @ 50Hz
- Colors: Uses 256 palette colors
- VRAM Usage: 163,840 bytes

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_26

*Sets the VDP to Super Graphics Mode 26*

```cpp
void vdp_set_super_graphic_26()
```


Super Graphics Mode 26 characteristics:
- Resolution: 640 x 256 @ 50Hz
- Colors: Uses 16 palette colors
- VRAM Usage: 81,920 bytes

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_27

*Sets the VDP to Super Graphics Mode 27*

```cpp
void vdp_set_super_graphic_27()
```


Super Graphics Mode 27 characteristics:
- Resolution: 720 x 240 @ 60Hz
- Colors: Uses 16 palette colors
- VRAM Usage: 86,400 bytes

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_set_super_graphic_28

*Sets the VDP to Super Graphics Mode 28*

```cpp
void vdp_set_super_graphic_28()
```


Super Graphics Mode 28 characteristics:
- Resolution: 720 x 288 @ 50Hz
- Colors: Uses 16 palette colors
- VRAM Usage: 103,680 bytes

Memory organization:
- Each pixel uses 4 bits to specify its color - 2 pixels per byte
- Most significant 4 bits of each byte represent the left most pixel
- Colors are selected from the palette registers

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.

---



#### vdp_get_super_graphic_mode

*Retrieve the current activated super graphics mode*

```cpp
uint8_t vdp_get_super_graphic_mode()
```


If a super graphics mode is not enabled, return 0

**Returns:**

- uint8_t the current super graphics mode (1 based)

---



#### vdp_set_super_graphic_mode

*Set the super graphics mode*

```cpp
void vdp_set_super_graphic_mode(uint8_t mode)
```


Delegated to one of the vdp_set_super_graphics_xx function.
Should not have the high bit set

> Only supported on the Super HDMI Tang Nano 20K
> custom kit with the SUPER_RES extensions enabled.


**Params:**

- `mode` - super graphics mode to select (1 base)


---



#### vdp_set_remap

*Configures the colours applied for logical CMD_LOGIC_REMAP operation*

```cpp
void vdp_set_remap(uint8_t remap_background_colour, uint8_t remap_foreground_colour)
```




**See also:**

* [vdp_cmd_move_linear_to_xy](#vdp_cmd_move_linear_to_xy)

**Params:**

- `remap_background_colour` - the palette index for background (zero) colour
- `remap_foreground_colour` - the palette index for foreground (non zero) colour


---



#### vdp_cmd_move_linear_to_xy

*VDP command 'Byte move to X, Y from Linear'*

```cpp
void vdp_cmd_move_linear_to_xy(screen_addr_t src_addr, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction, uint8_t operation)
```


Command Code: CMD_BMXL 0x30

The BMXL command transfers data in a specified rectangular area from the linear address in VRAM to the rectangular area.

This command is similar to `vdp_cmd_logical_move_vram_to_vram` function, but instead of using a data source of a bounded
rectangle, the `vdp_cmd_move_linear_to_xy` function retrieves its source data from the linear address space starting at
`src_addr` within the VRAM.

When used with logical operation other than `CMD_LOGIC_REMAP`, the function will read a byte for each destination pixel,
regardless of the pixel depths of the destination.  As such, if used on a destination that only support a 4 bit pixel depth, only
the lower 4 bits of each byte are applied to the logical operation.

When used with logical operation `CMD_LOGIC_REMAP`, the individual bits of the source data are maps to the individual destination
pixels.  As such, the first byte at `src_addr` will be mapped to the first 8 bytes of the destination rectangle.  If the bit is
0, the `remap_background_colour` is applied to the pixel and if the bit is a 1, then the `remap_foreground_colour` value is
applied.

> This function is only available with the Super HDMI Tang Nano FPGA module





**See also:**

* [vdp_set_remap](#vdp_set_remap)
* [vdp_cmd_logical_move_vram_to_vram](#vdp_cmd_logical_move_vram_to_vram)

**Params:**

- `src_addr` - the source address in VRAM of bytes to be transferred
- `x` - the starting x-coordinate of the destination rectangle
- `y` - the starting y-coordinate of the destination rectangle
- `width` - the width of the rectangle in pixels to be copied
- `height` - the height of the rectangle in pixels to be copied
- `direction` - the direction of the painting (DIX_RIGHT, DIX_LEFT, DIY_DOWN, DIY_UP)
- `operation` - the logical operation to be performed (CMD_LOGIC_IMP or CMD_LOGIC_REMAP)


---



### V99X8-SUPER Types


## Library CPM

*CP/M system calls and data structures.*

The cpm library provides structures, constants, and function declarations for
interacting with the CP/M operating system on the eZ80 platform. It includes
definitions for the File Control Block (FCB), BDOS calls, IOBYTE handling,
and various CP/M error codes and macros.

All functions will be marshalled from eZ80's ADL execution environment to
the Z80 compatibility environment.  All pointers supplied to functions must reference
an address within the Z80 compatibility segement - for the `eZ80 for RC` module
this is typically at address range: 0x03XXXX.

To ensure any structure if within this segment, you can allocate variables/arrays within
the `bss_z80` segment.


### CPM Functions



#### bdos

*Call the BDOS function with specified register values.*

```cpp
uint8_t bdos(uint16_t bc, uint16_t de)
```


This function calls the BDOS with register pair BC set to `bc` and DE set to `de`.
The value returned in register A is the return value of the function



**Params:**

- `bc` - The value to set in the BC register pair.
- `de` - The value to set in the DE register pair.

**Returns:**

- The value returned in register A.

---



#### cpm_term

*Quit the current program and return to the command prompt.*

```cpp
void cpm_term()
```


---



#### cpm_c_read

*Wait for a character from the keyboard, echo it to the screen, and return it.*

```cpp
uint8_t cpm_c_read()
```


This function waits for a character input from the keyboard, echoes it to the screen,
and then returns the character.

**Returns:**

- The character read from the keyboard.

---



#### cpm_c_write

*Send the character to the screen.*

```cpp
void cpm_c_write(uint8_t c)
```


This function sends the character `c` to the screen. Tabs are expanded to spaces.
Output can be paused with ^S and restarted with ^Q (or any key under versions prior to CP/M 3).
While the output is paused, the program can be terminated with ^C.


**Params:**

- `c` - n] c The character to send to the screen.


---



#### cpm_a_read

*Wait for a character from the auxiliary reader.*

```cpp
uint8_t cpm_a_read()
```


This function waits for a character input from the auxiliary reader and returns it.

**Returns:**

- The character read from the auxiliary reader.

---



#### cpm_a_write

*Send the character to the Auxiliary (Punch) output.*

```cpp
void cpm_a_write(uint8_t c)
```


This function sends the character `c` to the Auxiliary (Punch) output.


**Params:**

- `c` - n] c The character to send to the Auxiliary output.


---



#### cpm_l_write

*Send the character to the printer.*

```cpp
void cpm_l_write(uint8_t c)
```


This function sends the character `c` to the printer.


**Params:**

- `c` - n] c The character to send to the printer.


---



#### cpm_c_rawio

*Return a character without echoing if one is waiting; zero if none is available.*

```cpp
uint8_t cpm_c_rawio()
```


This function returns a character if one is waiting in the input buffer without echoing it.
If no character is available, it returns zero.

**Returns:**

- The character if available, otherwise zero.

---



#### cpm_get_iobyte

*Returns the current IOBYTE.*

```cpp
uint8_t cpm_get_iobyte()
```


This function returns the current IOBYTE, which is bit mapped as follows:

    Bits      Bits 6,7    Bits 4,5    Bits 2,3    Bits 0,1
    Device    LIST        PUNCH       READER      CONSOLE

    Value
      00      TTY:        TTY:        TTY:        TTY:
      01      CRT:        PTP:        PTR:        CRT:
      10      LPT:        UP1:        UR1:        BAT:
      11      UL1:        UP2:        UR2:        UC1:

BAT = batch mode. Use the current Reader for console input, and the current List (printer) device as the console output.
CRT = Standard console (keyboard and terminal screen).
LPT = Standard line printer.
PTP = Standard Paper Tape Punch.
PTR = Standard Paper Tape Reader.
TTY = Teletype device, e.g., a serial port.
UC1 = User defined (i.e., implementation dependent) console device.
UL1 = User defined (i.e., implementation dependent) printer device.
UPn = User defined (i.e., implementation dependent) output device.
URn = User defined (i.e., implementation dependent) input device.

**Returns:**

- The current IOBYTE.

---



#### cpm_set_iobyte

*Sets the IOBYTE to the specified value.*

```cpp
void cpm_set_iobyte(uint8_t iobyte)
```


This function sets the IOBYTE to the given value.


**Params:**

- `iobyte` - byte The value to set the IOBYTE to.


---



#### cpm_c_writestr

*Writes a $ terminated string to the console.*

```cpp
void cpm_c_writestr(near_ptr_t str)
```


This function writes the $ terminated string pointed to by `str` to the console.


**Params:**

- `str` - str The near pointer to the $ terminated string to be written.


---



#### cpm_c_readstr

*Reads a string from the console.*

```cpp
void cpm_c_readstr(near_ptr_t str)
```


This function reads characters from the keyboard into a memory buffer until RETURN is pressed. The Delete key is handled
correctly. In later versions of CP/M, more features can be used at this point; ZPM3 includes a full line editor with recall of
previous lines typed.

If `str` is NULL, the DMA address is used (CP/M 3 and later) and the buffer already contains data:

buffer: DEFB    size
        DEFB    len
        DEFB    bytes

The value at buffer+0 is the amount of bytes available in the buffer. Once the limit has been reached, no more can be added,
although the line editor can still be used. If `str` is NULL the next byte contains the number of bytes already in the buffer;
otherwise this is ignored. On return from the function, it contains the number of bytes present in the buffer.

The bytes typed then follow. There is no end marker.


**Params:**

- `str` - ] str The near pointer to the buffer where the string and its header will be stored.


---



#### cpm_f_dmaoff

*Sets the DMA address for the next file operation.*

```cpp
void cpm_f_dmaoff(near_ptr_t addr)
```


This function sets the DMA address to `addr` for the next file operation.


**Params:**

- `addr` - addr The near pointer to the DMA address.


---



#### cpm_c_stat

*Returns 0 if no characters are waiting, nonzero if a character is waiting.*

```cpp
uint8_t cpm_c_stat()
```


**Returns:**

- The console status

---



#### cpm_s_bdosver

*Returns the BDOS version.*

```cpp
uint16_t cpm_s_bdosver()
```


This function returns the BDOS version.

**Returns:**

- The BDOS version.

---



#### cpm_drv_allreset

*Resets all disk drives and logs out all disks.*

```cpp
uint8_t cpm_drv_allreset()
```


This function resets all disk drives, logs out all disks, and empties disk buffers. It sets the currently selected drive to A:.
Any drives set to Read-Only in software* become Read-Write; replacement BDOS implementations may leave them Read-Only.

In CP/M versions 1 and 2, it logs in drive A: and returns 0xFF if there is a file present whose name begins with a `$`, otherwise
it returns 0. Replacement BDOS* implementations may modify this behavior.

In multitasking versions, it returns 0 if succeeded, or 0xFF if other processes have files open on removable or read-only drives.

When the Digital Research CP/M 2 BDOS is started from cold, it is not properly initialized until this function is called; disk
operations may fail or crash.  Normally, this is done by the CCP and other programs don't need to worry, but if you are writing
an alternative CCP or a program that runs instead of the CCP, it's something to bear in mind.

**Returns:**

- 0 if succeeded, or 0xFF if there are issues.

---



#### cpm_drv_set

*Sets the currently selected drive.*

```cpp
uint8_t cpm_drv_set(uint8_t drive)
```


This function sets the currently selected drive to the specified drive number and logs in the disk. The drive number passed to
this routine is 0 for A:, 1 for B:, up to 15 for P:.

CP/M 1975 and 1.3 are limited to two drives. CP/M 1.4 is limited to four drives.



**Params:**

- `drive` - rive The drive number to set (0 for A:, 1 for B:, ..., 15 for P:).

**Returns:**

- 0 if successful, or 0xFF if there is an error. Under MP/M II and later versions, H can contain a physical error number.

---



#### cpm_drv_get

*Returns the currently selected drive.*

```cpp
uint8_t cpm_drv_get()
```


Returns currently selected drive. 0 => A:, 1 => B: etc.

**Returns:**

- The currently selected drive.

---



#### cpm_f_open

*Opens a file for reading or reading/writing.*

```cpp
cpm_f_error_t cpm_f_open(near_ptr_t fcb)
```


This function opens a file for reading or reading/writing using the File Control Block (FCB). The FCB is a 36-byte data
structure, most of which is maintained by CP/M.

The FCB should have its DR, Fn, and Tn fields filled in, and the four fields EX, S1, S2, and RC set to zero. Under CP/M 3 and
later, if CR is set to 0xFF, then on return CR will contain the last record byte count.  Note that CR should normally be reset to
zero if sequential access is to be used.

Under MP/M II, the file is normally opened exclusively - no other process can access it.
Two bits in the FCB control the mode the file is opened in:
- F5': Set to 1 for "unlocked" mode - other programs can use the file.
- F6': Set to 1 to open the file in read-only mode - other programs can use the file read-only.
  If both F6' and F5' are set, F6' wins.
If the file is opened in "unlocked" mode, the file's identifier (used for record locking) will be returned at FCB+21h.

Under MP/M II and later versions, a password can be supplied to this function by pointing the DMA address at the password.

On return from this function, A is 0xFF for error, or 0-3 for success. Some versions (including CP/M 3) always return zero;
others return 0-3 to indicate that an image of the directory entry is to be found at (80h+20h*A).

If result is 0xFF, CP/M 3 returns a hardware error (stored in errno). It also sets some bits in the FCB:
- F7': Set if the file is read-only because writing is password protected and no password was supplied.
- F8': Set if the file is read-only because it is a User 0 system file opened from another user area.



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0-3 for success, or 0xFF for error.

---



#### cpm_f_write

*Write a record to the previously specified DMA address.*

```cpp
cpm_f_error_t cpm_f_write(near_ptr_t fcb)
```


The record is normally 128 bytes, but can be a multiple of 128 bytes.
Update byte returned values are:
- 0: OK
- 1: Directory full
- 2: Disc full
- 8: (MP/M) Record locked by another process
- 9: Invalid FCB
- 10: (CP/M) Media changed; (MP/M) FCB checksum error
- 11: (MP/M) Unlocked file verification error
- 0xFF: Hardware error??

Lower byte, contains the number of 128-byte records written, before any error (CP/M 3 only).



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0 for success, or an error code as described above.

---



#### cpm_f_make

*Creates the file specified by the FCB.*

```cpp
cpm_f_error_t cpm_f_make(near_ptr_t fcb)
```


Returns error codes in BA and HL.

If the directory is full, the function return an upper byte of 0xFF.

If the file already exists, the default action is to return to the command prompt. However, CP/M 3 may return a hardware error in
the lower byte

Under MP/M II, set F5' to open the file in "unlocked" mode.

Under MP/M II and later versions, set F6' to create the file with a password; the DMA address should point at a 9-byte buffer:

@code
DEFS    8   ;Password
DEFB    1   ;Password mode
@endcode



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0 for success, or an error code as described above.

---



#### cpm_f_usernum

*Set or retrieve the current user number.*

```cpp
uint8_t cpm_f_usernum(const uint8_t number)
```


If number=0xFF, returns the current user number.

Set the current user number. number should be 0-15, or 255 to retrieve the current user number. Some versions can use user areas
16-31, but these should be avoided for compatibility reasons.



**Params:**

- `number` - mber The user number to set (0-15) or 255 to retrieve the current user number.

**Returns:**

- The current user number if number is 255, otherwise the number set.

---



#### cpm_f_close

*Close a file and write any pending data.*

```cpp
cpm_f_error_t cpm_f_close(near_ptr_t fcb)
```


This function closes a file and writes any pending data. It should always be used when a file has been written to.

On return from this function, A is 0xFF for error, or 0-3 for success. Some versions always return zero; others return 0-3 to
indicate that an image of the directory entry is to be found at (80h+20h*A).

Under CP/M 3, if F5' is set to 1, the pending data are written and the file is made consistent, but it remains open.

If A=0xFF, CP/M 3 returns a hardware error in H and B.



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0-3 for success, or 0xFF for error.

---



#### cpm_f_sfirst

*Search for the first occurrence of the specified file.*

```cpp
cpm_f_error_t cpm_f_sfirst(near_ptr_t fcb)
```


BDOS function 17 (F_SFIRST) - search for first
Supported by: All versions

Searches for the first occurrence of the specified file. The filename should be stored in the supplied FCB.  The filename can
include '?' marks, which match any character on the disk. If the first byte of the FCB is '?',  then any directory entry
(including disk labels, date stamps, etc.) will match. The EX byte is also checked; normally it should be set to zero, but if it
is set to '?', then all suitable extents are matched.


Returns 0xFF in the upper byte if an error occurs (CP/M 3 returns a hardware error in lower byte), or A=0-3 un upper byte if
successful.

Under CP/M-86 v4, if the first byte of the FCB is '?' or bit 7 of the byte is set, subdirectories as well as files will be
returned by this search.

**Params:**

- `fcb` - The address of the FCB.

**Returns:**

- cpm_f_error_t Error codes in BA and HL.

---



#### cpm_f_snext

*Search for the next occurrence of the specified file.*

```cpp
cpm_f_error_t cpm_f_snext(near_ptr_t fcb)
```


BDOS function 18 (F_SNEXT) - search for next
Supported by: All versions
Entered with C=0x12, DE=address of FCB. Returns error codes in BA and HL.

This function should only be executed immediately after function 17 or another invocation of function 18.  No other disk access
functions should have been used.

Function 18 behaves exactly as function 17, but finds the next occurrence of the specified file after the one returned last time.
The FCB parameter is not documented, but Jim Lopushinsky states in LD301.DOC:

  In none of the official Programmer's Guides for any version of CP/M does it say that an FCB is required for Search Next
  (function 18). However, if the FCB passed to Search First contains an unambiguous file reference (i.e. no question marks), then
  the Search Next function requires an FCB passed in reg DE (for CP/M-80) or DX (for CP/M-86).


**Params:**

- `fcb` - The address of the FCB.

**Returns:**

- cpm_f_error_t Error codes in BA and HL.

---



#### cpm_f_delete

*Deletes a file.*

```cpp
cpm_f_error_t cpm_f_delete(near_ptr_t fcb)
```


BDOS function 19 (F_DELETE) - delete file.
Supported by: All versions.


Deletes all directory entries matching the specified filename. The name can contain '?' marks.
Returns 0xFF in the upper byte if an error occurs (CP/M 3 returns a hardware error in lower byte), or 0-3 in upper byte if
successful.

Under CP/M 3, if bit F5' is set to 1, the file remains but any password protection is removed.
If the file has any password protection at all, the DMA address must be pointing at the password when this function is called.

**Params:**

- `fcb` - Address of the FCB.

**Returns:**

- Error codes in BA and HL.

---



#### cpm_f_read

*Load a record at the previously specified DMA address.*

```cpp
cpm_f_error_t cpm_f_read(near_ptr_t fcb)
```


Loads a record (normally 128 bytes, but under CP/M 3 this can be a multiple of 128 bytes) at the previously specified
DMA address.

BDOS function 20 (F_READ) read record
Supported by all versions.

Values returned in upper byte are:
- 0: OK
- 1: End of file
- 9: Invalid FCB
- 10: (CP/M) Media changed; (MP/M) FCB checksum error
- 11: (MP/M) Unlocked file verification error
- 0xFF: Hardware error

If on return upper byte is not 0xFF, the lower byte contains the number of 128-byte records read before the error (MP/M II and
later).



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0 for success, or an error code as described above.

---



#### cpm_f_rename

*Rename a file.*

```cpp
cpm_f_error_t cpm_f_rename(near_ptr_t fcb)
```


BDOS function 23 (F_RENAME) - Supported by all versions.

Renames the file specified to the new name, stored at FCB+16. This function cannot rename across drives, so the "drive" bytes of
both filenames should be identical. Returns A=0-3 if successful; A=0xFF if error. Under CP/M 3, if H is zero then the file could
not be found; if it is nonzero it contains a hardware error number.

Under Concurrent CP/M, set F5' if an extended lock on the file should be held through the rename. Otherwise, the lock will be
released.



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0-3 for success, or 0xFF for error.

---



#### cpm_f_attrib

*Set file attributes.*

```cpp
cpm_f_error_t cpm_f_attrib(near_ptr_t fcb)
```


BDOS function 30 (F_ATTRIB) - Supported by CP/M 2 and later.

Sets and resets the bits required. Standard CP/M versions allow the bits F1', F2', F3', F4', T1' (read-only), T2' (system), and
T3' (archive) to be changed. Some alternative BDOS versions allow F5', F6', F7', and F8' to be set, but this is not encouraged
since setting these bits can cause CP/M 3 to behave differently.

Under Concurrent CP/M, if the F5' bit is not set and the file has an extended file lock, the lock will be released when the
attributes are set. If F5' is set, the lock stays.

Under CP/M 3, the Last Record Byte Count is set by storing the required value at FCB+32 (FCB+20h) and setting the F6' bit.

The code returned in A is 0-3 if the operation was successful, or 0xFF if there was an error. Under CP/M 3, if A is 0xFF and H is
nonzero, H contains a hardware error.



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0-3 for success, or 0xFF for error.

---



#### cpm_f_readrand

*Random access read record.*

```cpp
cpm_f_error_t cpm_f_readrand(near_ptr_t fcb)
```


BDOS function 33 (F_READRAND) - Supported by CP/M 2 and later.

Reads the record specified in the random record count area of the FCB, at the DMA address. The pointers in the FCB will be
updated so that the next record to read using the sequential I/O calls will be the record just read.

Error numbers returned are:
- 0: OK
- 1: Reading unwritten data
- 4: Reading unwritten extent (a 16k portion of file does not exist)
- 6: Record number out of range
- 9: Invalid FCB
- 10: Media changed (CP/M); FCB checksum error (MP/M)
- 11: Unlocked file verification error (MP/M)
- 0xFF: [MP/M II, CP/M 3] Hardware error in H.



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0 for success, or an error code as described above.

---



#### cpm_f_writerand

*Random access write record.*

```cpp
cpm_f_error_t cpm_f_writerand(near_ptr_t fcb)
```


BDOS function 34 (F_WRITERAND) - Supported by CP/M 2 and later.

Writes the record specified in the random record count area of the FCB, at the DMA address. The pointers in the FCB will be
updated so that the next record to write using the sequential I/O calls will be the record just written.

Error numbers returned are:
- 0: OK
- 2: Disc full
- 3: Cannot close extent
- 5: Directory full
- 6: Record number out of range
- 8: Record is locked by another process (MP/M)
- 9: Invalid FCB
- 10: Media changed (CP/M); FCB checksum error (MP/M)
- 11: Unlocked file verification error (MP/M)
- 0xFF: [MP/M II, CP/M 3] Hardware error in H.

If the record indicated is beyond the end of the file, the record will be written and the file may contain a gap; attempting to
read this gap may give "reading unwritten data" errors, or nonsense.



**Params:**

- `fcb` - fcb The near pointer to the File Control Block (FCB).

**Returns:**

- 0 for success, or an error code as described above.

---



#### cpm_f_size

*Compute the size of a file.*

```cpp
cpm_f_error_t cpm_f_size(near_ptr_t fcb)
```


BDOS function 35 (F_SIZE) - Supported by CP/M 2 and later.

Computes the size of a file by setting the random record count bytes of the FCB to the number of 128-byte records in the file.

the function does not distinguish between a zero-length file and one that does not exist at all.
Under CP/M 3, returns 0xFF if there is an error (file not found, or CP/M 3 hardware error);
otherwise, returns A=0.




**Params:**

- `fcb` - fcb A pointer to the File Control Block (FCB).

**Returns:**

- @return 0 for success, or an error code as described above.
> Under CP/M 2, the value returned has no meaning;


---



### CPM Types



#### CPM_FCB

*CP/M's File Control Block structure*

```cpp
typedef struct cpm_fcb {
  // 36 bytes of standard FCB
  uint8_t  drive;       /* drive code 0*/
  char     name[8];     /* file name 1*/
  char     ext[3];      /* file type 9*/
  uint8_t  extent;      /* file extent 12*/
  char     filler[2];   /* not used 14*/
  char     records;     /* number of records in present extent 15*/
  char     discmap[16]; /* CP/M disc map 16 */
  char     next_record; /* next record to read or write 32*/
  uint24_t ranrec;      /* random record number (24 bit no. ) */
} CPM_FCB;
```



---


## Library HBIOS



### HBIOS Functions



#### hbios_cio_out

*Sends a character via the specified Character Video Unit*

```cpp
int8_t hbios_cio_out(uint8_t video_unit, uint8_t ch)
```



**Params:**

- `video_unit` - The video unit to send the character to
- `ch` - The character to be sent

**Returns:**

- Standard HBIOS result code
> If there is no space available in the unit's output buffer, the function will wait indefinitely


---



#### hbios_vda_qry

*Queries information about a specific video unit*

```cpp
int8_t hbios_vda_qry(uint8_t video_unit, uint8_t *new_font_map, vda_info_t *info)
```




Returns current video mode and display dimensions (rows/columns) for the
specified video unit. The rows and columns values represent the total count,
not the maximum index values.

> ***new_font_map*** must be set to NULL if not used, to avoid memory corruption.
> If ***new_font_map*** is provided, it must point to a suitably sized buffer in the
> upper 32K of MBASE address space. The buffer will be filled with the current
> character bitmap data if supported by the video driver. If bitmap retrieval
> is not supported, the font_map field in info will be set to zero.

**Params:**

- `video_unit` - The video unit to query
- `new_font_map` - Pointer to buffer in upper 32K of MBASE to store font bitmap data.
- `info` - Pointer to vda_info_t structure to receive the query results

**Returns:**

- Standard HBIOS result code

---



#### hbios_vda_krd

*Reads keyboard input from a specified video unit*

```cpp
int8_t hbios_vda_krd(uint8_t video_unit, vda_keyrd_info_t *info)
```



Returns the next available key data from the keyboard buffer.
If no key data is available, blocks indefinitely until a key is pressed.

The returned data includes:
- scan_code: Raw PS/2 scancode (set 2 standard)
- key_state: Modifier and lock state bitmap:
  - Bit 7: Numpad key indicator
  - Bit 6: Caps Lock state
  - Bit 5: Num Lock state
  - Bit 4: Scroll Lock state
  - Bit 3: Windows key state
  - Bit 2: Alt key state
  - Bit 1: Control key state
  - Bit 0: Shift key state
- key_code: ASCII value for standard keys, special codes for function/arrow keys

> Keyboard driver compatibility varies. Refer to specific driver documentation
> in the RomWBW HBIOS source code for detailed behavior.

**Params:**

- `video_unit` - The video unit to read keyboard input from
- `info` - Pointer to vda_keyrd_info_t structure to receive the key data

**Returns:**

- Standard HBIOS result code

---



#### hbios_vda_kst

*Gets the number of pending keystrokes in the keyboard buffer*

```cpp
int8_t hbios_vda_kst(uint8_t video_unit)
```



If the exact count cannot be determined, returns 1 to indicate keys
are available or 0 if the buffer is empty. Negative return values indicate
HBIOS errors (bit 7 set).

**Params:**

- `video_unit` - The video unit to check for pending keystrokes

**Returns:**

- the number of pending keystrokes (>=0) or HBIOS error code (<0)

---



### HBIOS Types



#### vda_info_t

*Structure containing information about a specific video unit*

```cpp
typedef struct {
  uint8_t  video_mode; /* Current video mode (driver specific value) */
  uint8_t  rows;       /* Number of character rows in current mode */
  uint8_t  columns;    /* Number of character columns in current mode */
  uint8_t *font_map;   /* Pointer to font bitmap data, or NULL if not available */
} vda_info_t;
```


---



#### vda_keyrd_info_t

*Structure containing keyboard input data from a video unit*

```cpp
typedef struct {
  uint8_t scan_code; /* Raw PS/2 scan code (set 2) from keyboard */
  uint8_t key_state; /* Modifier and lock state flags (shift, ctrl, etc.) */
  uint8_t key_code;  /* ASCII value or special code for function/arrow keys */
} vda_keyrd_info_t;
```


---


## Library EZ80



### EZ80 Functions



#### PORT_IO(c)

*Helper to define clang compliant ez80 I/O PORT access*

```cpp
#define PORT_IO(c) (*((volatile uint8_t IO_SPACE *)((uint24_t)c)))
```


The `PORT_IO` helper defines a `uint8_t` constant such that reads/writes will be
translated to appropriate eZ80 in/out instructions.

example:
> ```c
>   #define FRONT_PANEL_LEDS PORT_IO(0xFF00)
>
>   FRONT_PANEL_LEDS = 0x80;  ; Send 0x80 to IO port @ 0xFF00
> ```

---



#### as_near_ptr_safe

*Extracts the near 16-bit pointer from the 24-bit address.*

```cpp
near_ptr_t as_near_ptr_safe(const void *address, const uint8_t mbase, const char *file, const int line)
```


This function extracts the near 16-bit pointer from the given 24-bit address.
It checks if the 24-bit address is within the same 64k page as the MBASE.
If not, it prints an error message and aborts.



**Params:**

- `address` - ress The 24-bit address to be used.
- `mbase` - base The base address of the 64k page.
- `file` - file The name of the file where the function is called from.
- `line` - line The line number in the file where the function is called from.

**Returns:**

- The near 16-bit pointer extracted from the 24-bit address.

---



#### get_memory_start

*Get the application's allocated memory*

```cpp
uint8_t *get_memory_start()
```


For a standard COM application, the address returned is the MBASE address (eg: 0x030000)
For an EXE application, the start extended memory address the application was loaded into. (eg: 0x200000)

**Returns:**

- uint8_t* The starting address allocated to the application.

---



#### get_memory_end

*Get the the first address after the application's allocated memory*

```cpp
uint8_t *get_memory_end()
```


For standard COM application, the address returned is the MBASE+1 address (eg: 0x040000)
For an EXE application, the address returned is the first byte address beyond the allocated memory. eg (0x400000)

For EXE, the top of memory is free for use.
For COM, the top of memory is used by CPM.

**Returns:**

- uint8_t* the end address allocated to the application.

---



### EZ80 Types


## Library EZ80-FIRMWARE



### EZ80-FIRMWARE Functions



#### ez80_timers_ticks_get

*Retrieve the current timer tick count value*

```cpp
uint24_t ez80_timers_ticks_get()
```


Invokes firmware function A=2, B=0 SYSTMR_TICKS_GET

**Returns:**

- uint24_t the current timer tick count value

---



#### ez80_timers_ticks_set

*Set the current timer tick count value*

```cpp
void ez80_timers_ticks_set(const uint24_t ticks)
```


Invokes firmware function A=2, B=2 SYSTMR_TICKS_SET


**Params:**

- `ticks` - the new tick count value


---



#### ez80_timers_freq_tick_get

*Retrieve the current timer tick frequency*

```cpp
uint8_t ez80_timers_freq_tick_get()
```


Invokes firmware function A=2, B=4 SYSTMR_FREQTICK_GET

**Returns:**

- uint8_t the current timer tick frequency in ticks/second (typically 50 or 60)

---



#### ez80_timers_freq_tick_set

*Set the timer tick frequency*

```cpp
void ez80_timers_freq_tick_set(const uint8_t freq)
```


Invokes firmware function A=2, B=3 SYSTMR_FREQTICK_SET


**Params:**

- `freq` - new tick frequency in ticks/second (typically 50 or 60)


---



#### ez80_cpu_freq_get

*Retrieve the eZ80 CPU frequency*

```cpp
uint32_t ez80_cpu_freq_get()
```


Invokes firmware function A=0, B=5 SYSUTL_CPU_FREQ_GET

**Returns:**

- uint32_t the CPU frequency in Hz

---



#### ez80_mem_bus_cycles_get

*Retrieve the eZ80 memory configuration/timing*

```cpp
uint24_t ez80_mem_bus_cycles_get()
```


Invokes firmware function A=0, B=10 SYSUTL_MEMTM_GET

For each byte in the result, the top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of
cycles or wait states.

**Returns:**

- uint24_t each byte contains the memory configuration for CS3 (low byte), CS0 (middle byte), CS1 (high byte)

---



#### ez80_io_bus_cycles_get

*Retrieve the eZ80 memory configuration/timing for IO access (CS1)*

```cpp
uint8_t ez80_io_bus_cycles_get()
```


Invokes firmware function A=0, B=11 SYSUTL_IOTM_GET

The return byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
states.

**Returns:**

- uint8_t the memory configuration for CS2

---



#### ez80_mem_bus_cycles_set

*Configure the eZ80 for RC's main segmented memory bus configuration and timing (CS3)*

```cpp
void ez80_mem_bus_cycles_set(const uint8_t cycles)
```


Invokes firmware function A=0, B=8 SYSUTL_MEMTM_SET

The cycle byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
states.


**Params:**

- `cycles` - the number of cycles or wait states to set


---



#### ez80_io_bus_cycles_set

*Configure the eZ80 for RC's IO access bus configuration and timing (CS2)*

```cpp
void ez80_io_bus_cycles_set(const uint8_t cycles)
```


Invokes firmware function A=0, B=9 SYSUTL_IOTM_SET


**Params:**

- `cycles` - the number of cycles or wait states to set


---



#### ez80_mem0_bus_cycles_set

*Configure the eZ80 for RC's 1st extended linear memory bus configuration and timing (CS0)*

```cpp
void ez80_mem0_bus_cycles_set(const uint8_t cycles)
```


Invokes firmware function A=0, B=1 SYSUTL_MEM0TM_SET

The cycle byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
states.


**Params:**

- `cycles` - the number of cycles or wait states to set


---



#### ez80_mem1_bus_cycles_set

*Configure the eZ80 for RC's 1st extended linear memory bus configuration and timing (CS1)*

```cpp
void ez80_mem1_bus_cycles_set(const uint8_t cycles)
```


Invokes firmware function A=0, B=2 SYSUTL_MEM1TM_SET

The cycle byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
states.


**Params:**

- `cycles` - the number of cycles or wait states to set


---



#### ez80_flash_wait_cycles_get

*Retrieve the eZ80 memory configuration/timing*

```cpp
uint8_t ez80_flash_wait_cycles_get()
```


Invokes firmware function A=0, B=15 SYSUTL_FLASHWS_GET

Return the number (0-7) of wait states for the on-chip flash rom.

**Returns:**

- uint8_t the number of wait states for the on-chip flash rom

---



#### ez80_uart_out

*sends character to the eZ80's uart*

```cpp
void ez80_uart_out(const char ch)
```


Invokes firmware function A=3, B=1 UART_OUT


**Params:**

- `ch` - the character to be sent


---



#### ez80_uart_in

*reads the next character received on the eZ80's uart*

```cpp
uint8_t ez80_uart_in()
```


Invokes firmware function A=3, B=0 UART_IN


**Returns:**

- uint8_t the received character
> blocks until a character is received


---



#### start_sync_ms

*calculate a future timer tick point*

```cpp
int24_t start_sync_ms(uint24_t period_ms)
```


Supply the return value of this function to the `wait_sync_ms` function,
to block `period_ms` milliseconds after the invocation of this call.

> function will handle timer tick wrap around


> The effective resolution of this wait period is limited
> by the timer tick's frequency



**See also:**

* [ez80_timers_freq_tick_get](#ez80_timers_freq_tick_get)

**Params:**

- `period_ms` - number of milliseconds in the future to apply to current timer tick

**Returns:**

- `int24_t` of the future timer tick

---



#### wait_sync_ms

*block and wait until future time has arrived*

```cpp
void wait_sync_ms(int24_t future)
```


Retrieve the future time from the `start_sync_ms` function.

> function will handle timer tick wrap around


> The effective resolution of this wait period is limited
> by the timer tick's frequency


**See also:**

* [ez80_timers_freq_tick_get](#ez80_timers_freq_tick_get)

**Params:**

- `future` - the future time to wait


---



#### sleep_ms

*Wait for a number of milliseconds*

```cpp
void sleep_ms(uint24_t period_ms)
```


Function blocks for the specified number of milliseconds.


> The effective resolution of this wait period is limited
> by the timer tick's frequency


**See also:**

* [ez80_timers_freq_tick_get](#ez80_timers_freq_tick_get)

**Params:**

- `period_ms` - number of milliseconds to wait


---



### EZ80-FIRMWARE Types

