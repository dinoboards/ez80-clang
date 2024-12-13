#include "include/mm.h"

meta_ptr base;

static meta_ptr find_suitable_block(size_t size) {
  meta_ptr b = base;
  while (b) {
    if (b->free && b->size >= size)
      return b;

    b = b->next;
  }

  return NULL;
}

void *malloc(size_t size) {
  meta_ptr block;

  if (!base)
    return NULL;

  block = find_suitable_block(size);
  if (!block)
    return NULL;

  if (block->size - size >= (META_BLOCK_SIZE + 4))
    split_space(block, size);

  block->free = 0;

  return block->data;
}
