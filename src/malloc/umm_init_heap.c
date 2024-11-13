/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include "include/umm_malloc.h"
#include <string.h>

/* ------------------------------------------------------------------------- */

struct umm_heap_config umm_heap_current; // The global heap for single-heap use

void umm_init_heap(void *ptr, size_t size) {
  /* init heap pointer and size, and memset it to 0 */
  umm_heap_current.pheap     = ptr;
  umm_heap_current.heap_size = size;
  umm_heap_current.numblocks = (size / UMM_BLOCKSIZE);
  memset(umm_heap_current.pheap, 0x00, size);

  /* Set up umm_block[0], which just points to umm_block[1] */
  UMM_NBLOCK(0) = 1;
  UMM_NFREE(0)  = 1;
  UMM_PFREE(0)  = 1;

  /*
   * Now, we need to set the whole heap space as a huge free block. We should
   * not touch umm_block[0], since it's special: umm_block[0] is the head of
   * the free block list. It's a part of the heap invariant.
   *
   * See the detailed explanation at the beginning of the file.
   *
   * umm_block[1] has pointers:
   *
   * - next `umm_block`: the last one umm_block[n]
   * - prev `umm_block`: umm_block[0]
   *
   * Plus, it's a free `umm_block`, so we need to apply `UMM_FREELIST_MASK`
   *
   * And it's the last free block, so the next free block is 0 which marks
   * the end of the list. The previous block and free block pointer are 0
   * too, there is no need to initialize these values due to the init code
   * that memsets the entire umm_ space to 0.
   */
  UMM_NBLOCK(1) = UMM_BLOCK_LAST | UMM_FREELIST_MASK;

  /*
   * Last umm_block[n] has the next block index at 0, meaning it's
   * the end of the list, and the previous block is umm_block[1].
   *
   * The last block is a special block and can never be part of the
   * free list, so its pointers are left at 0 too.
   */

  UMM_PBLOCK(UMM_BLOCK_LAST) = 1;

  // DBGLOG_FORCE(true, "nblock(0) %04x pblock(0) %04x nfree(0) %04x pfree(0) %04x\r\n", UMM_NBLOCK(0) & UMM_BLOCKNO_MASK,
  // UMM_PBLOCK(0), UMM_NFREE(0), UMM_PFREE(0)); DBGLOG_FORCE(true, "nblock(1) %04x pblock(1) %04x nfree(1) %04x pfree(1) %04x\r\n",
  // UMM_NBLOCK(1) & UMM_BLOCKNO_MASK, UMM_PBLOCK(1), UMM_NFREE(1), UMM_PFREE(1));
}
