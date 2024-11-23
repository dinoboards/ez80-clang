#include <cpm.h>
#include <stdint.h>

// buffer must be allocated within the first 64k segment
uint8_t buffer[SECSIZE] __attribute__((section(".bss_z80")));
