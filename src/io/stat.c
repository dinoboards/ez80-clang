#include "include/io.h"
#include <cpm.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int stat(const char *path, struct stat *buf) {
  FCB *file_fcb = request_fcb();
  if (file_fcb == NULL) {
    errno = ENOMEM;
    return -1; // No free FCB available
  }

  if (extract_filename_parts(path, file_fcb)) {
    errno = EINVAL;
    return -1;
  }

  uint16_t r = cpm_f_sfirst(AS_NEAR_PTR(file_fcb));

  if (r < 4) {
    memset(buf, 0, sizeof(struct stat));
    return 0;
  } else {
    errno = ENOENT;
    return -1;
  }
}
