#include "include/io.h"
#include <cpm.h>
#include <stdbool.h>
#include <string.h>

static FCB __fcb[MAX_OPEN_FILES] __attribute__((section(".startup_z80")));
;

FCB *request_fcb() {
  for (int i = 0; i < MAX_OPEN_FILES; i++) {
    if (!__fcb[i].use) {
      memset(&__fcb[i], 0, sizeof(FCB));
      return &__fcb[i];
    }
  }
  return NULL; // No free FCB available
}

void free_fcb(FCB *fcb) {
  if (fcb) {
    memset(fcb, 0, sizeof(FCB));
  }
}
