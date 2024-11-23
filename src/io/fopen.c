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
  } else if (strcmp(mode, "r+") == 0) {
    result          = cpm_f_open(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_RDWR;

  } else if (strcmp(mode, "w") == 0) {
    cpm_f_delete(AS_CPM_PTR(file_fcb));
    result          = cpm_f_make(AS_CPM_PTR(file_fcb));
    file_fcb->flags = O_WRONLY;

    // } else if (strcmp(mode, "a") == 0) {
    //   result = cpm_f_open(AS_CPM_PTR(file_fcb));
    //   if (result == 0xFF) {
    //     result = cpm_f_make(AS_CPM_PTR(file_fcb));
    //   }
    //   // Move to the end of the file (simplified)
    //   while (cpm_f_read(AS_CPM_PTR(file_fcb)) != 1);

  } else {
    errno = EINVAL;
    return NULL; // Unsupported mode
  }

  // for w, delete file, then call cpm_f_make
  // for a, check if exists, then open using cpm_f_open and position at end, otherwise create using cpm_f_make

  if (result != CPM_ERR_OK) {
    errno = EIO;
    return NULL; // Error opening/creating file
  }

  claim_fcb(file_fcb);
  return (FILE *)file_fcb; // Return the FCB as FILE pointer
}
