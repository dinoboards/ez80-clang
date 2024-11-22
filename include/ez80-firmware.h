#ifndef __EZ80_FIRMWARE_H__
#define __EZ80_FIRMWARE_H__

#include <stdint.h>

/*
  ez80 for RC memory configuration:

  CS3: 64K Main Segmented Memory at <MB>xxxx.  This is the main legacy Z80 segmented memory. For configuration todate, the MB value
  is always 0x03/ CS2: I/O access in the range at $FFxx. CS1: 2nd Extended linear memory - not currently used. CS0: 1st Extended
  linear memory at the address range of $200000 -> $3FFFFF
*/

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

#endif
