#include "include/io.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int _setmode(int fd, int mode) {
  FILE *__restrict file = (FILE *__restrict)fd;
  FCB *file_fcb         = (FCB *)file;

  if (file_fcb == NULL || file_fcb->use == 0) {
    errno = EBADF;
    return -1; // Invalid file pointer
  }

  uint8_t *stream_mode;

  if (file == stdin)
    stream_mode = &_stdin.mode;

  else if (file == stdout)
    stream_mode = &_stdout.mode;

  else {
    errno = EINVAL;
    return -1; // Invalid.  Only support for stdio
  }

  if (mode == _IOTEXT_TRANSLATION)
    *stream_mode |= _IOTEXT_TRANSLATION; // Enable CRLF translation
  else
    *stream_mode &= ~_IOTEXT_TRANSLATION; // Disable CRLF translation

  return 0;
}
