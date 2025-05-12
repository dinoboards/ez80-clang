#ifndef __EZ80_FIRMWARE_H__
#define __EZ80_FIRMWARE_H__

#include "usb-keyboard.h"
#include <stdint.h>

/*
  ez80 for RC memory configuration:

  CS3: 64K Main Segmented Memory at <MB>xxxx.  This is the main legacy Z80 segmented memory. For configuration todate, the MB value
  is always 0x03/ CS2: I/O access in the range at $FFxx. CS1: 2nd Extended linear memory - not currently used. CS0: 1st Extended
  linear memory at the address range of $200000 -> $3FFFFF
*/

/**
 * @brief Retrieve the current timer tick count value
 *
 * Invokes firmware function A=2, B=0 SYSTMR_TICKS_GET
 *
 * @return uint24_t the current timer tick count value
 */
extern uint24_t ez80_timers_ticks_get(void);

/**
 * @brief Set the current timer tick count value
 *
 * Invokes firmware function A=2, B=2 SYSTMR_TICKS_SET
 *
 * @param ticks the new tick count value
 */
extern void ez80_timers_ticks_set(const uint24_t ticks);

/**
 * @brief Retrieve the current timer tick frequency
 *
 * Invokes firmware function A=2, B=4 SYSTMR_FREQTICK_GET
 *
 * @return uint8_t the current timer tick frequency in ticks/second (typically 50 or 60)
 */
extern uint8_t ez80_timers_freq_tick_get(void);

/**
 * @brief Set the timer tick frequency
 *
 * Invokes firmware function A=2, B=3 SYSTMR_FREQTICK_SET
 *
 * @param freq new tick frequency in ticks/second (typically 50 or 60)
 */
extern void ez80_timers_freq_tick_set(const uint8_t freq);

/**
 * @brief Retrieve the eZ80 CPU frequency
 *
 * Invokes firmware function A=0, B=5 SYSUTL_CPU_FREQ_GET
 *
 * @return uint32_t the CPU frequency in Hz
 */
extern uint32_t ez80_cpu_freq_get(void);

/**
 * @brief Retrieve the eZ80 memory configuration/timing
 *
 * Invokes firmware function A=0, B=10 SYSUTL_MEMTM_GET
 *
 * For each byte in the result, the top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of
 * cycles or wait states.
 *
 * @return uint24_t each byte contains the memory configuration for CS3 (low byte), CS0 (middle byte), CS1 (high byte)
 */
extern uint24_t ez80_mem_bus_cycles_get(void);

/**
 * @brief Retrieve the eZ80 memory configuration/timing for IO access (CS1)
 *
 * Invokes firmware function A=0, B=11 SYSUTL_IOTM_GET
 *
 * The return byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
 * states.
 *
 * @return uint8_t the memory configuration for CS2
 */
extern uint8_t ez80_io_bus_cycles_get(void);

/**
 * @brief Configure the eZ80 for RC's main segmented memory bus configuration and timing (CS3)
 *
 * Invokes firmware function A=0, B=8 SYSUTL_MEMTM_SET
 *
 * The cycle byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
 * states.
 *
 * @param cycles the number of cycles or wait states to set
 */
extern void ez80_mem_bus_cycles_set(const uint8_t cycles);

/**
 * @brief Configure the eZ80 for RC's IO access bus configuration and timing (CS2)
 *
 * Invokes firmware function A=0, B=9 SYSUTL_IOTM_SET
 *
 * @param cycles the number of cycles or wait states to set
 */
extern void ez80_io_bus_cycles_set(const uint8_t cycles);

/**
 * @brief Configure the eZ80 for RC's 1st extended linear memory bus configuration and timing (CS0)
 *
 * Invokes firmware function A=0, B=1 SYSUTL_MEM0TM_SET
 *
 * The cycle byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
 * states.
 *
 * @param cycles the number of cycles or wait states to set
 */
extern void ez80_mem0_bus_cycles_set(const uint8_t cycles);

/**
 * @brief Configure the eZ80 for RC's 1st extended linear memory bus configuration and timing (CS1)
 *
 * Invokes firmware function A=0, B=2 SYSUTL_MEM1TM_SET
 *
 * The cycle byte's top bit represents the bus mode (0 = eZ80, 1 = Z80) and the lower 3 bits represent the number of cycles or wait
 * states.
 *
 * @param cycles the number of cycles or wait states to set
 */
extern void ez80_mem1_bus_cycles_set(const uint8_t cycles);

/**
 * @brief Retrieve the eZ80 memory configuration/timing
 *
 * Invokes firmware function A=0, B=15 SYSUTL_FLASHWS_GET
 *
 * Return the number (0-7) of wait states for the on-chip flash rom.
 *
 * @return uint8_t the number of wait states for the on-chip flash rom
 */
extern uint8_t ez80_flash_wait_cycles_get(void);

/*
 * @brief Configure the eZ80 for RC's on-chip flash rom bus configuration and timing
 *
 * Invokes firmware function A=0, B=14 SYSUTL_FLASHWS_SET
 *
 * @param cycles the number of wait states to set
 */
extern void ez80_flash_wait_cycles_set(const uint8_t cycles);

extern uint8_t ez80_uart_out(const char ch);

extern uint8_t ez80_uart_in();

typedef struct {
  uint8_t key_ascii; /* ascii char encoding, if applicable */
  uint8_t key_code;  /* Modifier keys state bitmap in high byte, code in low byte */
  uint8_t key_down;  /* true key pressed down event, false, key up event */
} usb_kyb_event_t;

/**
 * @brief Retrieve buffered keyboard key events
 *
 * @param usb_key Pointer to receive the next key event data
 * @return uint8_t Number of events remaining in buffer (including current),
 *         or 0 if buffer is empty
 *
 * @details Processes the USB keyboard state buffer using ez80_usb_kyb_report to extract
 * individual key press and release events. Returns immediately if no events are
 * available.
 *
 * @note Modifier keys (Ctrl, Shift, Alt, etc.) are mapped to special key codes
 * ranging from E0-E7, corresponding to USB_KEY_LCTRL through to USB_KEY_RMETA
 */
extern uint8_t usb_kyb_event(usb_kyb_event_t *key);

#endif
