#include <stdio.h>

// TODO: implement fputc for other streams

int fputc(int c, FILE *stream) {
  if (stream == stdout) {
    putchar(c);
    return c;
  }
  return EOF;
}
