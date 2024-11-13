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

uint16_t umm_blocks(size_t size) {

  /*
   * The calculation of the block size is not too difficult, but there are
   * a few little things that we need to be mindful of.
   *
   * When a block removed from the free list, the space used by the free
   * pointers is available for data. That's what the first calculation
   * of size is doing.
   *
   * We don't check for the special case of (size == 0) here as this needs
   * special handling in the caller depending on context. For example when we
   * realloc() a block to size 0 it should simply be freed.
   *
   * We do NOT need to check for allocating more blocks than the heap can
   * possibly hold - the allocator figures this out for us.
   *
   * There are only two cases left to consider:
   *
   * 1. (size <= body)  Obviously this is just one block
   * 2. (blocks > (2^15)) This should return ((2^15)) to force a
   *                      failure when the allocator runs
   *
   * If the requested size is greater that 32677-2 blocks (max block index
   * minus the overhead of the top and bottom bookkeeping blocks) then we
   * will return an incorrectly truncated value when the result is cast to
   * a uint16_t.
   */

  if (size <= (sizeof(((umm_block *)0)->body))) {
    return 1;
  }

  /*
   * If it's for more than that, then we need to figure out the number of
   * additional whole blocks the size of an umm_block are required, so
   * reduce the size request by the number of bytes in the body of the
   * first block.
   */

  size -= (sizeof(((umm_block *)0)->body));

  /* NOTE WELL that we take advantage of the fact that INT16_MAX is the
   * number of blocks that we can index in 15 bits :-)
   *
   * The below expression looks wierd, but it's right. Assuming body
   * size of 4 bytes and a block size of 8 bytes:
   *
   * BYTES (BYTES-BODY) (BYTES-BODY-1)/BLOCKSIZE BLOCKS
   *     1        n/a                        n/a      1
   *     5          1                          0      2
   *    12          8                          0      2
   *    13          9                          1      3
   */

  size_t blocks = (2 + ((size - 1) / (UMM_BLOCKSIZE)));

  if (blocks > (INT16_MAX)) {
    blocks = INT16_MAX;
  }

  return (uint16_t)blocks;
}
