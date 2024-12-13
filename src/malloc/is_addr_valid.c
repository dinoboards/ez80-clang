#include "include/mm.h"

/*
 * This function checks if the given pointer address is indeed created by invoking malloc() or not.
 * We use the field ptr in the meta_block() to check if the passed address is same as the one present in the meta_block()
 */
bool is_addr_valid(void *p) {
  if (base) {
    const void *low  = (void *)base->data;
    const void *high = (void *)(base + _heap_size);
    if (p >= low && p < high) {
      meta_ptr block = get_block_addr(p);
      uint8_t *pData = block->data;
      return (p == pData);
    }
  }
  return false;
}
