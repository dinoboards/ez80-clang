#include <cpm.h>
#include <stdio.h>

int ferror(FILE *stream) {
  FCB *file_fcb = (FCB *)stream;

  if (file_fcb == NULL || file_fcb->use == 0) {
    return 1;
  }

  return file_fcb->errored;
}
