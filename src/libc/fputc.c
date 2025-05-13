#include <stdio.h>

int fputc(int c, FILE *stream) {
  if (stream == stderr || stream == stdout) {
    putchar(c);
    return c;
  }

  if (fwrite(&c, 1, 1, stream) != 1)
    return EOF;
  return c;
}
