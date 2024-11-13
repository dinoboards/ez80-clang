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
/*
 * Split the block `c` into two blocks: `c` and `c + blocks`.
 *
 * - `new_freemask` should be `0` if `c + blocks` used, or `UMM_FREELIST_MASK`
 *   otherwise.
 *
 * Note that free pointers are NOT modified by this function.
 */

void umm_split_block(uint16_t c, uint16_t blocks, uint16_t new_freemask) {

  UMM_NBLOCK(c + blocks) = (UMM_NBLOCK(c) & UMM_BLOCKNO_MASK) | new_freemask;
  UMM_PBLOCK(c + blocks) = c;

  UMM_PBLOCK(UMM_NBLOCK(c) & UMM_BLOCKNO_MASK) = (c + blocks);
  UMM_NBLOCK(c)                                = (c + blocks);
}
