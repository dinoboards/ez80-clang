#include "include/mm.h"
#include <stdio.h>

void mem_alloc_dump() {
  meta_ptr b = base;
  while (b) {
    printf("Block: %p, size: %u, free: %d, next: %p, prev: %p, data: %p\r\n", b, b->size, b->free, b->next, b->prev, b->data);
    b = b->next;
  }
}
