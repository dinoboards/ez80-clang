#include <ez80-firmware.h>
#include <stdint.h>

void wait_sync_ms(int24_t future) {
  while ((future - (int24_t)ez80_timers_ticks_get()) > 0)
    ;
}
