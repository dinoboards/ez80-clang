#include <stdio.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  FILE *__restrict file = (FILE *__restrict)fd;

  return fseek(file, offset, whence);
}
