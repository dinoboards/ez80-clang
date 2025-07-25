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

/**
 * @brief sends character to the eZ80's uart
 *
 * Invokes firmware function A=3, B=1 UART_OUT
 *
 * @param ch the character to be sent
 */
extern void ez80_uart_out(const char ch);

/**
 * @brief reads the next character received on the eZ80's uart
 *
 * Invokes firmware function A=3, B=0 UART_IN
 *
 * @return uint8_t the received character
 *
 * @note blocks until a character is received
 */
extern uint8_t ez80_uart_in();

/**
 * @brief calculate a future timer tick point
 *
 * Supply the return value of this function to the `wait_sync_ms` function,
 * to block `period_ms` milliseconds after the invocation of this call.
 *
 * > function will handle timer tick wrap around
 *
 * @see ez80_timers_freq_tick_get
 *
 * > The effective resolution of this wait period is limited
 * > by the timer tick's frequency
 *
 * @param period_ms number of milliseconds in the future to apply to current timer tick
 * @return `int24_t` of the future timer tick
 *
 */
int24_t start_sync_ms(uint24_t period_ms);

/**
 * @brief block and wait until future time has arrived
 *
 * Retrieve the future time from the `start_sync_ms` function.
 *
 * > function will handle timer tick wrap around
 *
 * @see ez80_timers_freq_tick_get
 *
 * > The effective resolution of this wait period is limited
 * > by the timer tick's frequency
 *
 * @param future the future time to wait
 */
void wait_sync_ms(int24_t future);

/**
 * @brief Wait for a number of milliseconds
 *
 * Function blocks for the specified number of milliseconds.
 *
 * @see ez80_timers_freq_tick_get
 *
 * > The effective resolution of this wait period is limited
 * > by the timer tick's frequency
 *
 * @param period_ms number of milliseconds to wait
 */
void sleep_ms(uint24_t period_ms);

#endif
