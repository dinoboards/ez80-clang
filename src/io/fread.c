#include "include/io.h"
#include <cpm.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  FCB   *file_fcb    = (FCB *)stream;
  size_t total_bytes = size * nmemb;
  size_t bytes_read  = 0;

  const near_ptr_t safe_fcb = AS_CPM_PTR(file_fcb);

  if (file_fcb == NULL || file_fcb->use == 0) {
    errno = EBADF;
    return 0;
  }

  if (file_fcb->flags == O_WRONLY) {
    errno             = EINVAL;
    file_fcb->errored = true;
    return 0;
  }

  cpm_f_dmaoff(AS_CPM_PTR(___fbuffer));

  while (bytes_read < total_bytes) {
    // Calculate the current record and offset within the record
    uint24_t record_num = file_fcb->rwptr / SECSIZE;
    uint24_t offset     = file_fcb->rwptr % SECSIZE;

    // Read the current record
    file_fcb->cpm_fcb.ranrec = record_num;
    if (cpm_f_readrand(safe_fcb) != 0) {
      errno             = EIO;
      file_fcb->errored = true;
      file_fcb->eof     = true; // probably we just got to eof.  TODO: review (https://www.seasip.info/Cpm/bytelen.html)
      break;                    // Error reading record
    }

    // Calculate the number of bytes to copy from the current record
    size_t bytes_to_copy = SECSIZE - offset;
    if (bytes_to_copy > total_bytes - bytes_read) {
      bytes_to_copy = total_bytes - bytes_read;
    }

    if (file_fcb->mode & _IOTEXT) {
      // In text mode, scan for Ctrl+Z
      void *found = memchr(___fbuffer + offset, __STDIO_EOFMARKER, bytes_to_copy);
      if (found) {
        file_fcb->eof = true;
        bytes_to_copy = (uint8_t *)found - (___fbuffer + offset);
      }
    }

    // Copy the bytes from the ___fbuffer to the destination
    memcpy((uint8_t *)ptr + bytes_read, ___fbuffer + offset, bytes_to_copy);
    bytes_read += bytes_to_copy;
    file_fcb->rwptr += bytes_to_copy;

    if (file_fcb->eof) {
      break; // Exit the read loop if we found CTRL+Z
    }
  }

  return bytes_read / size;
}
