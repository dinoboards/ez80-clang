/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include "include/umm_malloc.h"

void umm_free_core(void *ptr) {

  uint16_t c;

  /*
   * FIXME: At some point it might be a good idea to add a check to make sure
   *        that the pointer we're being asked to free up is actually within
   *        the umm_heap!
   *
   * NOTE:  See the new umm_info() function that you can use to see if a ptr is
   *        on the free list!
   */

  /* Figure out which block we're in. Note the use of truncated division... */

  c = (((uint8_t *)ptr) - (uint8_t *)(&(UMM_HEAP[0]))) / UMM_BLOCKSIZE;

  DBGLOG_DEBUG("Freeing block %i\r\n", c);

  /* Now let's assimilate this block with the next one if possible. */

  umm_assimilate_up(c);

  /* Then assimilate with the previous block if possible */

  if (UMM_NBLOCK(UMM_PBLOCK(c)) & UMM_FREELIST_MASK) {

    DBGLOG_DEBUG("Assimilate down to previous block, which is FREE\r\n");

    c = umm_assimilate_down(c, UMM_FREELIST_MASK);
  } else {
    DBGLOG_DEBUG("Just add to head of free list\r\n");

    UMM_PFREE(UMM_NFREE(0)) = c;
    UMM_NFREE(c)            = UMM_NFREE(0);
    UMM_PFREE(c)            = 0;
    UMM_NFREE(0)            = c;

    UMM_NBLOCK(c) |= UMM_FREELIST_MASK;
  }
}
