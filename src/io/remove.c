#include "include/io.h"
#include <cpm.h>
#include <errno.h>
#include <stdio.h>

int remove(const char *filename) {
  FCB *file_fcb = request_fcb();
  if (file_fcb == NULL) {
    errno = EMFILE;
    return -1; // No free FCB available
  }

  if (extract_filename_parts(filename, file_fcb)) {
    errno = EINVAL;
    return -1;
  }

  cpm_f_error_t result;
  result = cpm_f_delete(AS_CPM_PTR(file_fcb));
  if (result != CPM_ERR_OK) {
    errno = EIO;
    return -1; // Error deleting file
  }

  return 0; // Success
}
