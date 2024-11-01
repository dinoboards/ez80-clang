#include <stdio.h>

int fputc(int c, FILE *stream) {
  if (stream == stdout) {
    putchar(c);
    return c;
  }
  return EOF;
}
