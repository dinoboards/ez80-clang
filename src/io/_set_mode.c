#include "include/io.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define TRANSLATION_FLAGS (_O_BINARY | _O_TEXT)

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

  else
    stream_mode = &file_fcb->mode;

  if (mode == _O_BINARY) {
    *stream_mode &= ~_O_TEXT; // Disable CRLF translation
  } else if (mode == _O_TEXT) {
    *stream_mode |= _O_TEXT; // Enable CRLF translation
  } else {
    errno = EINVAL;
    return -1; // Invalid mode
  }

  return 0;
}
