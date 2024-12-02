#include "include/umm_malloc.h"
#include <ez80.h>
#include <stddef.h>

void malloc_init(size_t heap_size) { umm_init_heap(_heap, heap_size); }
