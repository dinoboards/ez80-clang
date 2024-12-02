#include "include/io.h"
#include <cpm.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  FCB   *file_fcb      = (FCB *)stream;
  size_t total_bytes   = size * nmemb;
  size_t bytes_written = 0;

  if (file_fcb == NULL || file_fcb->use == 0) {
    errno = EBADF;
    return 0;
  }

  if (file_fcb->flags == O_RDONLY)
    return 0;

  cpm_f_dmaoff(AS_CPM_PTR(___fbuffer));

  while (bytes_written < total_bytes) {
    // Calculate the current record and offset within the record
    unsigned long record_num = file_fcb->rwptr / SECSIZE;
    unsigned long offset     = file_fcb->rwptr % SECSIZE;

    memset(___fbuffer, file_fcb->mode & _IOTEXT ? __STDIO_EOFMARKER : 0, SECSIZE);

    // Read the current record if it's not aligned to the start
    if (offset != 0 || bytes_written == 0) {
      file_fcb->cpm_fcb.ranrec = record_num;
      cpm_f_readrand(AS_CPM_PTR(file_fcb));
    }

    // Calculate the number of bytes to copy to the current record
    size_t bytes_to_copy = SECSIZE - offset;
    if (bytes_to_copy > total_bytes - bytes_written) {
      bytes_to_copy = total_bytes - bytes_written;
    }

    // Copy the bytes from the source to the ___fbuffer
    memcpy(___fbuffer + offset, (const uint8_t *)ptr + bytes_written, bytes_to_copy);

    // Write the current record
    file_fcb->cpm_fcb.ranrec = record_num;
    if (cpm_f_writerand(AS_CPM_PTR(file_fcb)) != 0) {
      errno             = EIO;
      file_fcb->errored = true;
      break; // Error writing record
    }

    bytes_written += bytes_to_copy;
    file_fcb->rwptr += bytes_to_copy;
  }

  return bytes_written / size;
}
