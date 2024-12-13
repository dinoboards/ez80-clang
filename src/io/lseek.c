#include <errno.h>
#include <stdio.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  FILE *__restrict file = (FILE *__restrict)fd;

  int r = fseek(file, offset, whence);

  if (r == 0) {
    return ftell(file);
  } else {
    errno = EBADF;
    return -1;
  }
}
