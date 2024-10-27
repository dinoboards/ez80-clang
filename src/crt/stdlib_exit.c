#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ATEXIT_FUNCS 32

static void (*atexit_funcs[MAX_ATEXIT_FUNCS])(void);
static int atexit_count = 0;

int atexit(void (*fn)(void)) {
  if (atexit_count >= MAX_ATEXIT_FUNCS)
    return EXIT_FAILURE; // Too many functions registered

  atexit_funcs[atexit_count++] = fn;
  return 0;
}

void run_atexit_funcs(void) {
  for (int i = atexit_count - 1; i >= 0; i--)
    atexit_funcs[i]();
}
