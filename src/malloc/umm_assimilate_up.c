/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include "include/umm_malloc.h"

/* ------------------------------------------------------------------------
 * The umm_assimilate_up() function does not assume that UMM_NBLOCK(c)
 * has the UMM_FREELIST_MASK bit set. It only assimilates up if the
 * next block is free.
 */

void umm_assimilate_up(uint16_t c) {

  if (UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_FREELIST_MASK) {

    /*
     * The next block is a free block, so assimilate up and remove it from
     * the free list
     */

    DBGLOG_DEBUG("Assimilate up to next block, which is FREE\r\n");

    /* Disconnect the next block from the FREE list */

    umm_disconnect_from_free_list(UMM_NBLOCK(c));

    /* Assimilate the next block with this one */

    UMM_PBLOCK(UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_BLOCKNO_MASK) = c;
    UMM_NBLOCK(c)                                            = UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_BLOCKNO_MASK;
  }
}
