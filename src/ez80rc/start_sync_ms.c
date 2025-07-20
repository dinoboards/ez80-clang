#include <ez80-firmware.h>
#include <stdint.h>

int24_t start_sync_ms(uint24_t period) {
  const uint8_t freq = ez80_timers_freq_tick_get();

  int24_t adjusted_period = freq * period / 1000;
  return (int24_t)ez80_timers_ticks_get() + adjusted_period;
}
