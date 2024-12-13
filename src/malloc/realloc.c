#include "include/mm.h"
#include <stdlib.h>
#include <string.h>

static void copy_data(meta_ptr src, meta_ptr dest) {
  size_t min_size = src->size < dest->size ? src->size : dest->size;
  memcpy(dest->data, src->data, min_size);
}

void *realloc(void *p, size_t size) {
  meta_ptr new_block, old_block;
  void    *new_ptr;

  if (!p)
    return malloc(size);

  if (!is_addr_valid(p))
    return NULL;

  old_block = get_block_addr(p);

  if (old_block->size >= size) {
    if (old_block->size >= (META_BLOCK_SIZE + 4))
      split_space(old_block, size);

    return p;
  }

  if (old_block->next && old_block->next->free && (old_block->size + old_block->next->size + META_BLOCK_SIZE) >= size) {
    merge_blocks(old_block);
    if ((uint24_t)(old_block - size) >= (META_BLOCK_SIZE + 4))
      split_space(old_block, size);

    return p;
  }

  new_ptr = malloc(size);

  if (!new_ptr)
    return NULL;

  new_block = get_block_addr(new_ptr);
  copy_data(old_block, new_block);

  free(p);
  return new_ptr;
}
