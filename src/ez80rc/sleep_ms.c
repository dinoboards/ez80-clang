#include <ez80-firmware.h>
#include <stdint.h>

void sleep_ms(uint24_t period) {
  const int24_t future = start_sync_ms(period);
  wait_sync_ms(future);
}
