#include <cpm.h>
#include <stdint.h>

// ___fbuffer must be allocated within the first 64k segment
uint8_t ___fbuffer[SECSIZE] __attribute__((section(".bss_z80")));
