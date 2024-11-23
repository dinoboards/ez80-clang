#include <stdio.h>
#include <unistd.h>

int close(int fd) {
  FILE *__restrict file = (FILE *__restrict)fd;

  return fclose(file);
}
