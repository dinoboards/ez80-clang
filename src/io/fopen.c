#include "include/io.h"
#include <cpm.h>
#include <stdio.h>
#include <string.h>

#define MAX_OPEN_FILES 8

/**
 * @brief Opens a file.
 *
 * @details The `fopen` function opens the file whose name is the string pointed to by `filename` and associates a stream with it.
 *
 * The `mode` argument is a string that indicates the type of access requested for the file. The allowed modes are:
 * - `"r"` : Open text file for reading. The stream is positioned at the beginning of the file.
 * - `"w"` : Truncate to zero length or create text file for writing. The stream is positioned at the beginning of the file.
 * - `"a"` : Open for writing. The file is created if it does not exist. The stream is positioned at the end of the file.
 * - `"r+"`: Open for reading and writing. The stream is positioned at the beginning of the file.
 * - `"w+"`: Truncate to zero length or create text file for reading and writing. The stream is positioned at the beginning of the
 * file.
 * - `"a+"`: Open for reading and writing. The file is created if it does not exist. The stream is positioned at the end of the
 * file.
 * - `"rb"`: Open binary file for reading. The stream is positioned at the beginning of the file.
 * - `"wb"`: Truncate to zero length or create binary file for writing. The stream is positioned at the beginning of the file.
 * - `"ab"`: Open binary file for writing. The file is created if it does not exist. The stream is positioned at the end of the
 * file.
 * - `"r+b"` or `"rb+"`: Open binary file for reading and writing. The stream is positioned at the beginning of the file.
 * - `"w+b"` or `"wb+"`: Truncate to zero length or create binary file for reading and writing. The stream is positioned at the
 * beginning of the file.
 * - `"a+b"` or `"ab+"`: Open binary file for reading and writing. The file is created if it does not exist. The stream is
 * positioned at the end of the file.
 *
 * The `fopen` function returns a pointer to a `FILE` object that can be used to identify the stream in subsequent operations. If
 * the file cannot be opened, a `NULL` pointer is returned.
 *
 * @param[in] filename The name of the file to be opened.
 * @param[in] mode The mode in which to open the file.
 *
 * @return A pointer to a `FILE` object on success, or `NULL` on failure.
 */
FILE *fopen(const char *filename, const char *mode) {
  FCB *file_fcb = request_fcb();
  if (file_fcb == NULL)
    return NULL; // No free FCB available

  if (extract_filename_parts(filename, file_fcb)) {
    return NULL;
  }

  cpm_f_error_t result;
  if (strcmp(mode, "r") == 0) {
    result = cpm_f_open(AS_CPM_PTR(file_fcb));
  }

  // for w, delete file, then call cpm_f_make
  // for a, check if exists, then open using cpm_f_open and position at end, otherwise create using cpm_f_make

  // } else if (strcmp(mode, "w") == 0) {
  //     result = cpm_f_make((near_ptr_t)file_fcb);
  // } else if (strcmp(mode, "a") == 0) {
  //     result = cpm_f_open((near_ptr_t)file_fcb);
  //     if (result == 0xFF) {
  //         result = cpm_f_make((near_ptr_t)file_fcb);
  //     }
  //     // Move to the end of the file (simplified)
  //     while (cpm_f_read((near_ptr_t)file_fcb) != 1);
  // }
  else {
    return NULL; // Unsupported mode
  }

  if (result == 0xFF) {
    return NULL; // Error opening/creating file
  }

  claim_fcb(file_fcb);
  return (FILE *)file_fcb; // Return the FCB as FILE pointer
}
