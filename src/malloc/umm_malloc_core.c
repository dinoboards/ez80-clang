/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include "include/umm_malloc.h"

/* ------------------------------------------------------------------------ */

void *umm_malloc_core(size_t size) {
  uint16_t blocks;
  uint16_t blockSize = 0;

  uint16_t bestSize;
  uint16_t bestBlock;

  uint16_t cf;

  blocks = umm_blocks(size);

  /*
   * Now we can scan through the free list until we find a space that's big
   * enough to hold the number of blocks we need.
   *
   * This part may be customized to be a best-fit, worst-fit, or first-fit
   * algorithm
   */

  cf = UMM_NFREE(0);

  bestBlock = UMM_NFREE(0);
  bestSize  = 0x7FFF;

  while (cf) {
    blockSize = (UMM_NBLOCK(cf) & UMM_BLOCKNO_MASK) - cf;

    DBGLOG_TRACE("Looking at block %i size %i\r\n", cf, blockSize);

#if defined UMM_BEST_FIT
    if ((blockSize >= blocks) && (blockSize < bestSize)) {
      bestBlock = cf;
      bestSize  = blockSize;
    }
#elif defined UMM_FIRST_FIT
    /* This is the first block that fits! */
    if ((blockSize >= blocks)) {
      break;
    }
#else
#error "No UMM_*_FIT is defined"
#endif

    cf = UMM_NFREE(cf);
  }

  if (0x7FFF != bestSize) {
    cf        = bestBlock;
    blockSize = bestSize;
  }

  if (UMM_NBLOCK(cf) & UMM_BLOCKNO_MASK && blockSize >= blocks) {

    /*
     * This is an existing block in the memory heap, we just need to split off
     * what we need, unlink it from the free list and mark it as in use, and
     * link the rest of the block back into the freelist as if it was a new
     * block on the free list...
     */

    if (blockSize == blocks) {
      /* It's an exact fit and we don't neet to split off a block. */
      DBGLOG_DEBUG("Allocating %i blocks starting at %i - exact\r\n", blocks, cf);

      /* Disconnect this block from the FREE list */

      umm_disconnect_from_free_list(cf);
    } else {

      /* It's not an exact fit and we need to split off a block. */
      DBGLOG_DEBUG("Allocating %i blocks starting at %i - existing\r\n", blocks, cf);

      /*
       * split current free block `cf` into two blocks. The first one will be
       * returned to user, so it's not free, and the second one will be free.
       */
      umm_split_block(cf, blocks, UMM_FREELIST_MASK /*new block is free*/);

      /*
       * `umm_split_block()` does not update the free pointers (it affects
       * only free flags), but effectively we've just moved beginning of the
       * free block from `cf` to `cf + blocks`. So we have to adjust pointers
       * to and from adjacent free blocks.
       */

      /* previous free block */
      UMM_NFREE(UMM_PFREE(cf)) = cf + blocks;
      UMM_PFREE(cf + blocks)   = UMM_PFREE(cf);

      /* next free block */
      UMM_PFREE(UMM_NFREE(cf)) = cf + blocks;
      UMM_NFREE(cf + blocks)   = UMM_NFREE(cf);
    }

  } else {
    /* Out of memory */

    DBGLOG_DEBUG("Can't allocate %5i blocks\r\n", blocks);

    return (void *)NULL;
  }

  return (void *)&UMM_DATA(cf);
}
