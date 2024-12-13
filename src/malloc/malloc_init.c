#include "include/mm.h"
#include <ez80.h>
#include <stddef.h>

size_t _heap_size;

void malloc_init_2(void *heap_start, size_t heap_size);

void malloc_init(size_t heap_size) { malloc_init_2(_heap, heap_size); }

void malloc_init_2(void *heap_start, size_t heap_size) {
  base       = heap_start;
  _heap_size = heap_size;

  base->size = heap_size - META_BLOCK_SIZE;
  base->free = 1;
  base->next = NULL;
  base->prev = NULL;
}
