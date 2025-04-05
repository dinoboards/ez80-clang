#include "include/io.h"
#include <cpm.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

FILE *fopen(const char *filename, const char *mode) {
  FCB *file_fcb = request_fcb();
  if (file_fcb == NULL) {
    errno = EMFILE;
    return NULL; // No free FCB available
  }

  if (extract_filename_parts(filename, file_fcb)) {
    errno = EINVAL;
    return NULL;
  }

  cpm_f_error_t result;
  uint8_t       has_read = 0, has_write = 0, has_plus = 0, has_text = 0;
  const char   *p;

  for (p = mode; *p; p++) {
    switch (*p) {
    case 'r':
      has_read = 1;
      break;
    case 'w':
      has_write = 1;
      break;
    case '+':
      has_plus = 1;
      break;
    case 't':
      has_text = 1;
      break;
    case 'b':
      has_text = 0;
      break;
    default:
      errno = EINVAL;
      return NULL;
    }
  }

  if (has_read && has_write) {
    errno = EINVAL;
    return NULL;
  }

  if (!has_read && !has_write) {
    errno = EINVAL;
    return NULL;
  }

  if (has_write) {
    cpm_f_delete(AS_CPM_PTR(file_fcb));
    result          = cpm_f_make(AS_CPM_PTR(file_fcb));
    file_fcb->flags = has_plus ? O_RDWR : O_WRONLY;
  } else { // has_read
    result          = cpm_f_open(AS_CPM_PTR(file_fcb));
    file_fcb->flags = has_plus ? O_RDWR : O_RDONLY;
  }

  file_fcb->mode = has_text ? _IOTEXT : _IOBINARY;

  if (result != CPM_ERR_OK) {
    errno = EIO;
    return NULL; // Error opening/creating file
  }

  claim_fcb(file_fcb);
  return (FILE *)file_fcb; // Return the FCB as FILE pointer
}
