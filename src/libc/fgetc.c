#include <stdio.h>

// Implementation of fgetc that delegates based on the stream type
int fgetc(FILE *stream) {
  if (stream == stdin)
    return getchar();

  // TODO
  return EOF;
}
