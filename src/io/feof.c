#include <cpm.h>
#include <errno.h>
#include <stdio.h>

int feof(FILE *stream) {
  FCB *file_fcb = (FCB *)stream;

  if (file_fcb == NULL || file_fcb->use == 0) {
    errno = EBADF;
    return 0;
  }

  return file_fcb->eof;
}
