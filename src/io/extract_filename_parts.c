#include "include/io.h"
#include <cpm.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int extract_filename_parts(const char *input, FCB *fcb) {
  // Initialize output buffers
  fcb->drive = '\0';
  memset(fcb->name, ' ', 8 + 3); // includes ext

  const char *ptr      = input;
  int         name_len = 0;
  int         ext_len  = 0;

  // Check for drive designation
  if (isalpha(ptr[0]) && ptr[1] == ':') {
    fcb->drive = toupper(ptr[0]) - 'A' + 1;
    ptr += 2;
  }

  // Extract filename
  while (*ptr && *ptr != '.' && name_len < 8) {
    if (!isalnum(*ptr))
      return -1; // Invalid character
    fcb->name[name_len++] = toupper(*ptr);
    ptr++;
  }

  // Skip the dot if present
  if (*ptr == '.')
    ptr++;

  // Extract extension
  while (*ptr && ext_len < 3) {
    if (!isalnum(*ptr))
      return -1; // Invalid character
    fcb->ext[ext_len++] = toupper(*ptr);
    ptr++;
  }

  return 0; // Success
}
