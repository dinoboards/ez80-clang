#include "include/io.h"
#include <cpm.h>
#include <stdio.h>
#include <stdlib.h>

int fclose(FILE *stream) {
  FCB *file_fcb = (FCB *)stream;

  if (file_fcb == NULL || file_fcb->use == 0) {
    return EOF; // Invalid file pointer or file not open
  }

  const cpm_f_error_t result = cpm_f_close(AS_CPM_PTR(file_fcb));

  if (result != 0) {
    return -1; // Error closing file
  }

  free_fcb(file_fcb);
  return 0; // Success
}
