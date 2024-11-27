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
  if (strcmp(mode, "r") == 0) {
    result          = cpm_f_open(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_RDONLY;
    file_fcb->mode  = _IOTEXT;

  } else if (strcmp(mode, "r+") == 0) {
    result          = cpm_f_open(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_RDWR;
    file_fcb->mode  = _IOTEXT;

  } else if (strcmp(mode, "w") == 0) {
    cpm_f_delete(AS_CPM_PTR(file_fcb));
    result          = cpm_f_make(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_WRONLY;
    file_fcb->mode  = _IOTEXT;

  } else if (strcmp(mode, "wb") == 0) {
    cpm_f_delete(AS_CPM_PTR(file_fcb));
    result          = cpm_f_make(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_WRONLY;
    file_fcb->mode  = 0;

  } else if (strcmp(mode, "rb") == 0) {
    result          = cpm_f_open(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_RDONLY;
    file_fcb->mode  = 0;

  } else {
    errno = EINVAL;
    return NULL; // Unsupported mode
  }

  if (result != CPM_ERR_OK) {
    errno = EIO;
    return NULL; // Error opening/creating file
  }

  claim_fcb(file_fcb);
  return (FILE *)file_fcb; // Return the FCB as FILE pointer
}
