#include <cpm.h>
#include <errno.h>
#include <stdio.h>

int fseek(FILE *stream, long int offset, int origin) {
  FCB *file_fcb = (FCB *)stream;

  if (file_fcb == NULL || file_fcb->use == 0) {
    errno = EBADF;
    return 0;
  }

  switch (origin) {
  case SEEK_SET:
    file_fcb->rwptr = offset;
    file_fcb->eof   = false;  //TODO: check if we are at the end of the file
    break;

  case SEEK_CUR:
    file_fcb->rwptr += offset;
    file_fcb->eof = false; //TODO: check if we are at the end of the file
    break;

  case SEEK_END:
    return -1;
    // find end of file, and calculate position
    break;
  }

  return 0;
}
