/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "include/umm_malloc.h"

/* ------------------------------------------------------------------------ */

void *malloc(const size_t size) {
  /*
   * the very first thing we do is figure out if we're being asked to allocate
   * a size of 0 - and if we are we'll simply return a null pointer. if not
   * then reduce the size by 1 byte so that the subsequent calculations on
   * the number of blocks to allocate are easier...
   */

  if (0 == size) {
    DBGLOG_DEBUG("malloc a block of 0 bytes -> do nothing\n");

    return NULL;
  }

  return umm_malloc_core(size);
}
