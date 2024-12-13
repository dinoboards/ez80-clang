#include "include/mm.h"

/*
 * The split_space function splits the given block if it contains space greater than the requested space.
 * Creates a new block of the free space and adds it in the linked list
 */
void split_space(meta_ptr block, size_t size) {
  const meta_ptr new_block  = (meta_ptr)(block->data + size);
  const size_t   total_size = (size + META_BLOCK_SIZE);
  const size_t   new_size   = block->size - total_size;
  new_block->size           = new_size;
  new_block->next           = block->next;
  new_block->free           = 1;
  new_block->prev           = block;

  block->next = new_block;
  block->size = size;
  if (new_block->next)
    new_block->next->prev = new_block;
}
