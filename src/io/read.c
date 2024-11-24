#include <errno.h>
#include <stdio.h>
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count) {
  FILE *__restrict file = (FILE *__restrict)fd;

  size_t read = fread(buf, 1, count, file);
  if (read < count) {
    if (feof(file)) {
      errno = 0;
    } else if (ferror(file)) {
      errno = EIO;
      return -1;
    }
  }

  return (ssize_t)read;
}
