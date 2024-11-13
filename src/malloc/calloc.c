/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include "include/umm_malloc.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------ */

void *calloc(size_t num, size_t item_size) {
  void *ret;

  ret = malloc((size_t)(item_size * num));

  if (ret) {
    memset(ret, 0x00, (size_t)(item_size * num));
  }

  return ret;
}
