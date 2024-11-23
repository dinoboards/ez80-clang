#include <cpm.h>
#include <stdio.h>

int fseek(FILE *stream, long int offset, int origin) {
  FCB *file_fcb = (FCB *)stream;

  switch (origin) {
  case SEEK_SET:
    file_fcb->rwptr = offset;
    break;

  case SEEK_CUR:
    file_fcb->rwptr += offset;
    break;

  case SEEK_END:
    return -1;
    // find end of file, and calculate position
    break;
  }

  return 0;
}
