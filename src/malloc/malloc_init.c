#include "include/umm_malloc.h"
#include <ez80.h>
#include <stddef.h>

void malloc_init(size_t stack_reserved) {
  void  *sps  = _get_sps();
  size_t size = ((unsigned int)sps - stack_reserved) - (unsigned int)(void *)_heap;
  umm_init_heap(_heap, size);
}
