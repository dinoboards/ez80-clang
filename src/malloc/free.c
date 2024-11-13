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
#include <string.h>

/* ------------------------------------------------------------------------ */

void free(void *ptr) {
  /* If we're being asked to free a NULL pointer, well that's just silly! */

  if ((void *)0 == ptr) {
    DBGLOG_DEBUG("free a null pointer -> do nothing\n");

    return;
  }

  /* If we're being asked to free an out of range pointer - do nothing */
  /* TODO: remove the check for NULL pointer later */

  if ((ptr < umm_heap_current.pheap) || ((size_t)ptr >= (size_t)umm_heap_current.pheap + umm_heap_current.heap_size)) {
    DBGLOG_DEBUG("free an out of range pointer -> do nothing\n");

    return;
  }

  umm_free_core(ptr);
}
