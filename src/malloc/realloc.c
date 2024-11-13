/*
 * This file and function was extracted from the project umm_malloc.
 *
 * umm_malloc: https://github.com/rhempel/umm_malloc
 * Included in this project as a subtree at external/umm_malloc.
 *
 * License and copyrights are per the umm_malloc project.
 */

#include "include/umm_malloc.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------ */

void *realloc(void *ptr, size_t size) {
  uint16_t blocks;
  uint16_t blockSize;
  uint16_t prevBlockSize = 0;
  uint16_t nextBlockSize = 0;

  uint16_t c;

  size_t curSize;

  /*
   * This code looks after the case of a NULL value for ptr. The ANSI C
   * standard says that if ptr is NULL and size is non-zero, then we've
   * got to work the same a malloc(). If size is also 0, then our version
   * of malloc() returns a NULL pointer, which is OK as far as the ANSI C
   * standard is concerned.
   */

  if (((void *)NULL == ptr)) {
    DBGLOG_DEBUG("realloc the NULL pointer - call malloc()\r\n");

    return malloc(size);
  }

  /*
   * Now we're sure that we have a non_NULL ptr, but we're not sure what
   * we should do with it. If the size is 0, then the ANSI C standard says that
   * we should operate the same as free.
   */

  if (0 == size) {
    DBGLOG_DEBUG("realloc to 0 size, just free the block\r\n");

    free(ptr);

    return (void *)NULL;
  }

  /*
   * Otherwise we need to actually do a reallocation. A naive approach
   * would be to malloc() a new block of the correct size, copy the old data
   * to the new block, and then free the old block.
   *
   * While this will work, we end up doing a lot of possibly unnecessary
   * copying. So first, let's figure out how many blocks we'll need.
   */

  blocks = umm_blocks(size);

  /* Figure out which block we're in. Note the use of truncated division... */

  c = (((uint8_t *)ptr) - (uint8_t *)(&(UMM_HEAP[0]))) / UMM_BLOCKSIZE;

  /* Figure out how big this block is ... the free bit is not set :-) */

  blockSize = (UMM_NBLOCK(c) - c);

  /* Figure out how many bytes are in this block */

  curSize = (blockSize * UMM_BLOCKSIZE) - (sizeof(((umm_block *)0)->header));

  /* Now figure out if the previous and/or next blocks are free as well as
   * their sizes - this will help us to minimize special code later when we
   * decide if it's possible to use the adjacent blocks.
   *
   * We set prevBlockSize and nextBlockSize to non-zero values ONLY if they
   * are free!
   */

  if ((UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_FREELIST_MASK)) {
    nextBlockSize = (UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_BLOCKNO_MASK) - UMM_NBLOCK(c);
  }

  if ((UMM_NBLOCK(UMM_PBLOCK(c)) & UMM_FREELIST_MASK)) {
    prevBlockSize = (c - UMM_PBLOCK(c));
  }

  DBGLOG_DEBUG("realloc blocks %i blockSize %i nextBlockSize %i prevBlockSize %i\r\n", blocks, blockSize, nextBlockSize,
               prevBlockSize);

  /*
   * Ok, now that we're here we know how many blocks we want and the current
   * blockSize. The prevBlockSize and nextBlockSize are set and we can figure
   * out the best strategy for the new allocation as follows:
   *
   * 1. If the new block is the same size or smaller than the current block do
   *    nothing.
   * 2. If the next block is free and adding it to the current block gives us
   *    EXACTLY enough memory, assimilate the next block. This avoids unwanted
   *    fragmentation of free memory.
   *
   * The following cases may be better handled with memory copies to reduce
   * fragmentation
   *
   * 3. If the previous block is NOT free and the next block is free and
   *    adding it to the current block gives us enough memory, assimilate
   *    the next block. This may introduce a bit of fragmentation.
   * 4. If the prev block is free and adding it to the current block gives us
   *    enough memory, remove the previous block from the free list, assimilate
   *    it, copy to the new block.
   * 5. If the prev and next blocks are free and adding them to the current
   *    block gives us enough memory, assimilate the next block, remove the
   *    previous block from the free list, assimilate it, copy to the new block.
   * 6. Otherwise try to allocate an entirely new block of memory. If the
   *    allocation works free the old block and return the new pointer. If
   *    the allocation fails, return NULL and leave the old block intact.
   *
   * TODO: Add some conditional code to optimise for less fragmentation
   *       by simply allocating new memory if we need to copy anyways.
   *
   * All that's left to do is decide if the fit was exact or not. If the fit
   * was not exact, then split the memory block so that we use only the requested
   * number of blocks and add what's left to the free list.
   */

  //  Case 1 - block is same size or smaller
  if (blockSize >= blocks) {
    DBGLOG_DEBUG("realloc the same or smaller size block - %i, do nothing\r\n", blocks);
    /* This space intentionally left blank */

    //  Case 2 - block + next block fits EXACTLY
  } else if ((blockSize + nextBlockSize) == blocks) {
    DBGLOG_DEBUG("exact realloc using next block - %i\r\n", blocks);
    umm_assimilate_up(c);
    blockSize += nextBlockSize;

    //  Case 3 - prev block NOT free and block + next block fits
  } else if ((0 == prevBlockSize) && (blockSize + nextBlockSize) >= blocks) {
    DBGLOG_DEBUG("realloc using next block - %i\r\n", blocks);
    umm_assimilate_up(c);
    blockSize += nextBlockSize;

    //  Case 4 - prev block + block fits
  } else if ((prevBlockSize + blockSize) >= blocks) {
    DBGLOG_DEBUG("realloc using prev block - %i\r\n", blocks);
    umm_disconnect_from_free_list(UMM_PBLOCK(c));
    c = umm_assimilate_down(c, 0);
    memmove((void *)&UMM_DATA(c), ptr, curSize);
    ptr = (void *)&UMM_DATA(c);
    blockSize += prevBlockSize;

    //  Case 5 - prev block + block + next block fits
  } else if ((prevBlockSize + blockSize + nextBlockSize) >= blocks) {
    DBGLOG_DEBUG("realloc using prev and next block - %i\r\n", blocks);
    umm_assimilate_up(c);
    umm_disconnect_from_free_list(UMM_PBLOCK(c));
    c = umm_assimilate_down(c, 0);
    memmove((void *)&UMM_DATA(c), ptr, curSize);
    ptr = (void *)&UMM_DATA(c);
    blockSize += (prevBlockSize + nextBlockSize);

    //  Case 6 - default is we need to realloc a new block
  } else {
    DBGLOG_DEBUG("realloc a completely new block %i\r\n", blocks);
    void *oldptr = ptr;
    if ((ptr = umm_malloc_core(size))) {
      DBGLOG_DEBUG("realloc %i to a bigger block %i, copy, and free the old\r\n", blockSize, blocks);
      memcpy(ptr, oldptr, curSize);
      umm_free_core(oldptr);
    } else {
      DBGLOG_DEBUG("realloc %i to a bigger block %i failed - return NULL and leave the old block!\r\n", blockSize, blocks);
      /* This space intentionally left blnk */
    }
    blockSize = blocks;
  }

  /* Now all we need to do is figure out if the block fit exactly or if we
   * need to split and free ...
   */

  if (blockSize > blocks) {
    DBGLOG_DEBUG("split and free %i blocks from %i\r\n", blocks, blockSize);
    umm_split_block(c, blocks, 0);
    umm_free_core((void *)&UMM_DATA(c + blocks));
  }

  return ptr;
}
