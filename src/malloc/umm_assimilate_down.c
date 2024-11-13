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
 * The umm_assimilate_down() function assumes that UMM_NBLOCK(c) does NOT
 * have the UMM_FREELIST_MASK bit set. In other words, try to assimilate
 * up before assimilating down.
 */

uint16_t umm_assimilate_down(uint16_t c, uint16_t freemask) {
  UMM_NBLOCK(UMM_PBLOCK(c)) = UMM_NBLOCK(c) | freemask;
  UMM_PBLOCK(UMM_NBLOCK(c)) = UMM_PBLOCK(c);

  return UMM_PBLOCK(c);
}
