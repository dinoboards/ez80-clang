#include "include/io.h"
#include <cpm.h>
#include <errno.h>
#include <stdio.h>

#define __STDIO_EOFMARKER 26

int fseek(FILE *stream, long offset, int origin) {
  FCB *file_fcb = (FCB *)stream;

  if (file_fcb == NULL || file_fcb->use == 0) {
    errno = EBADF;
    return 0;
  }

  switch (origin) {
  case SEEK_SET:
    file_fcb->rwptr = offset;
    file_fcb->eof   = false; // TODO: check if we are at the end of the file
    break;

  case SEEK_CUR:
    file_fcb->rwptr += offset;
    file_fcb->eof = false; // TODO: check if we are at the end of the file
    break;

  case SEEK_END:
    file_fcb->cpm_fcb.ranrec = 0;
    cpm_f_size(AS_CPM_PTR(file_fcb));

    file_fcb->eof   = false;
    file_fcb->rwptr = (file_fcb->cpm_fcb.ranrec * 128);

    if ((file_fcb->mode & _IOTEXT) && (file_fcb->rwptr >= 0)) {
      cpm_f_dmaoff(AS_CPM_PTR(buffer));

      file_fcb->cpm_fcb.ranrec--;
      if (cpm_f_readrand(AS_CPM_PTR(file_fcb)) != 0) {
        errno             = EIO;
        file_fcb->errored = true;
        return -1;
      }

      int cnt = 127;
      while (cnt > 0 && buffer[cnt] == __STDIO_EOFMARKER)
        cnt--;

      cnt = 127 - cnt;

      file_fcb->rwptr -= cnt;
    }

    break;
  }

  return 0;
}
