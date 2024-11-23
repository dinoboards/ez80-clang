#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count) {
  FILE *__restrict file = (FILE *__restrict)fd;

  size_t written = fwrite((const void *__restrict)buf, 1, count, file);
  if (written < count) {
    if (ferror(file)) {
      errno = EIO;
      return -1;
    }
  }

  return (ssize_t)written;
}
