#ifndef __MM_H
#define __MM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * malloc implementation derived from: https://github.com/RAGUL1902/Dynamic-Memory-Allocation-in-C/tree/master
 *
 * This implementation of malloc is based on first-fit style.
 * meta_block is a struct to store the meta information about every chuck of memory being allocated.
 * A doubly-linked list is maintained with all the meta_blocks
 * to maintain the space being allocated and deallocated
 * Size of meta_block is considered to be 20 (4 bytes for each of the  variables).
 */

struct meta_block;

typedef struct meta_block *meta_ptr;

/* header block for allocated/free memory blocks */
struct meta_block {
  uint8_t  free;   /* 1 if free, 0 if allocated */
  uint24_t size;   /* size of the data block (excluding meta_block)*/
  meta_ptr next;   /* pointer to next meta_block */
  meta_ptr prev;   /* pointer to previous meta_block */
  uint8_t  data[]; /* start of data block */
};

#define META_BLOCK_SIZE sizeof(struct meta_block)

/* Start of heap for malloc's use */
extern meta_ptr base;

/* size after base for the heap*/
extern size_t _heap_size;

/**
 * @brief Verify if the supplied pointer is a validate allocated data block
 *
 * @param p Pointer to the data block
 * @return bool true if the pointer is valid, false otherwise
 */
extern bool is_addr_valid(void *p);

extern meta_ptr get_block_addr(uint8_t *p);

extern void split_space(meta_ptr block, size_t size);

extern meta_ptr merge_blocks(meta_ptr block);

#endif
