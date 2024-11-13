/* ----------------------------------------------------------------------------
 * umm_malloc.h - a memory allocator for embedded systems (microcontrollers)
 *
 * See copyright notice in LICENSE.TXT
 * ----------------------------------------------------------------------------

 * There are a number of defines you can set at compile time that affect how
 * the memory allocator will operate.
 *
 * You should NOT edit this file, it may be changed from time to time in
 * the upstream project. Instead, you can do one of the following (in order
 * of priority
 *
 * 1. Pass in the override values on the command line using -D UMM_xxx
 * 2. Pass in the filename holding override values using -D UMM_CFGFILE
 * 3. Set up defaults in a file called umm_malloc_cfgport.h
 *
 * NOTE WELL: For the command line -D options to take highest priority, your
 *            project level override file must check that the UMM_xxx
 *            value is not already defined before overriding
 *
 * Unless otherwise noted, the default state of these values is #undef-ined!
 *
 * As this is the top level configuration file, it is responsible for making
 * sure that the configuration makes sense. For example the UMM_BLOCK_BODY_SIZE
 * is a minimum of 8 and a multiple of 4.
 *
 * UMM_BLOCK_BODY_SIZE
 *
 * Defines the umm_block[].body size - it is 8 by default
 *
 * This assumes umm_ptr is a pair of uint16_t values
 * which is 4 bytes plus the data[] array which is another 4 bytes
 * for a total of 8.
 *
 * NOTE WELL that the umm_block[].body size must be multiple of
 *           the natural access size of the host machine to ensure
 *           that accesses are efficient.
 *
 *           We have not verified the checks below for 64 bit machines
 *           because this library is targeted for 32 bit machines.
 *
 * UMM_BEST_FIT (default)
 *
 * Set this if you want to use a best-fit algorithm for allocating new blocks.
 * On by default, turned off by UMM_FIRST_FIT
 *
 * UMM_FIRST_FIT
 *
 * Set this if you want to use a first-fit algorithm for allocating new blocks.
 * Faster than UMM_BEST_FIT but can result in higher fragmentation.
 *
 * ----------------------------------------------------------------------------
 */

/* ----------------------------------------------------------------------------
 *
 * See LICENSE for copyright notice
 * See README.md for acknowledgements and description of internals
 * ----------------------------------------------------------------------------
 *
 * R.Hempel 2007-09-22 - Original
 * R.Hempel 2008-12-11 - Added MIT License biolerplate
 *                     - realloc() now looks to see if previous block is free
 *                     - made common operations functions
 * R.Hempel 2009-03-02 - Added macros to disable tasking
 *                     - Added function to dump heap and check for valid free
 *                        pointer
 * R.Hempel 2009-03-09 - Changed name to umm_malloc to avoid conflicts with
 *                        the mm_malloc() library functions
 *                     - Added some test code to assimilate a free block
 *                        with the very block if possible. Complicated and
 *                        not worth the grief.
 * D.Frank 2014-04-02  - Fixed heap configuration when UMM_TEST_MAIN is NOT set,
 *                        added user-dependent configuration file umm_malloc_cfg.h
 * R.Hempel 2016-12-04 - Add support for Unity test framework
 *                     - Reorganize source files to avoid redundant content
 *                     - Move integrity and poison checking to separate file
 * R.Hempel 2017-12-29 - Fix bug in realloc when requesting a new block that
 *                        results in OOM error - see Issue 11
 * R.Hempel 2019-09-07 - Separate the malloc() and free() functionality into
 *                        wrappers that use critical section protection macros
 *                        and static core functions that assume they are
 *                        running in a protected con text. Thanks @devyte
 * R.Hempel 2020-01-07 - Add support for Fragmentation metric - See Issue 14
 * R.Hempel 2020-01-12 - Use explicitly sized values from stdint.h - See Issue 15
 * R.Hempel 2020-01-20 - Move metric functions back to umm_info - See Issue 29
 * R.Hempel 2020-02-01 - Macro functions are uppercased - See Issue 34
 * R.Hempel 2020-06-20 - Support alternate body size - See Issue 42
 * R.Hempel 2021-05-02 - Support explicit memory umm_init_heap() - See Issue 53
 * K.Whitlock 2023-07-06 - Add support for multiple heaps
 * ----------------------------------------------------------------------------
 */

#ifndef UMM_MALLOC_H
#define UMM_MALLOC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A couple of macros to make packing structures less compiler dependent */

#define UMM_H_ATTPACKPRE
#define UMM_H_ATTPACKSUF __attribute__((__packed__))

/* -------------------------------------------------------------------------- */

#define UMM_BLOCK_BODY_SIZE (8)

#if ((UMM_BLOCK_BODY_SIZE % 4) != 0)
#error UMM_BLOCK_BODY_SIZE must be multiple of 4!
#endif

/* -------------------------------------------------------------------------- */

#ifdef UMM_BEST_FIT
#ifdef UMM_FIRST_FIT
#error Both UMM_BEST_FIT and UMM_FIRST_FIT are defined - pick one!
#endif
#else /* UMM_BEST_FIT is not defined */
#ifndef UMM_FIRST_FIT
#define UMM_BEST_FIT
#endif
#endif

/* -------------------------------------------------------------------------- */
/*
 * Add blank macros for DBGLOG_xxx() - if you want to override these on
 * a per-source module basis, you must define DBGLOG_LEVEL and then
 * #include "dbglog.h"
 */

#define DBGLOG_TRACE(format, ...)
#define DBGLOG_DEBUG(format, ...)
// printf(format, ##__VA_ARGS__);
#define DBGLOG_CRITICAL(format, ...)
#define DBGLOG_ERROR(format, ...)
#define DBGLOG_WARNING(format, ...)
#define DBGLOG_INFO(format, ...)
#define DBGLOG_FORCE(format, ...)

/* ------------------------------------------------------------------------ */

typedef struct umm_heap_config {
  void    *pheap;
  size_t   heap_size;
  uint16_t numblocks;
} umm_heap;

extern struct umm_heap_config umm_heap_current;

/* ------------------------------------------------------------------------ */

extern void umm_init_heap(void *ptr, size_t size);
extern void umm_init(void);

// extern void *malloc(size_t size);
// extern void *calloc(size_t num, size_t size);
// extern void *realloc(void *ptr, size_t size);
// extern void  free(void *ptr);

/* ------------------------------------------------------------------------ */

extern void    *umm_malloc_core(size_t size);
extern void     umm_free_core(void *ptr);
extern uint16_t umm_blocks(size_t size);
extern void     umm_split_block(uint16_t c, uint16_t blocks, uint16_t new_freemask);
extern void     umm_disconnect_from_free_list(uint16_t c);
extern void     umm_assimilate_up(uint16_t c);
extern uint16_t umm_assimilate_down(uint16_t c, uint16_t freemask);

UMM_H_ATTPACKPRE typedef struct umm_ptr_t {
  uint16_t next;
  uint16_t prev;
} UMM_H_ATTPACKSUF umm_ptr;

UMM_H_ATTPACKPRE typedef struct umm_block_t {
  union {
    umm_ptr used;
  } header;
  union {
    umm_ptr free;
    uint8_t data[UMM_BLOCK_BODY_SIZE - sizeof(struct umm_ptr_t)];
  } body;
} UMM_H_ATTPACKSUF umm_block;

#define UMM_FREELIST_MASK ((uint16_t)(0x8000))
#define UMM_BLOCKNO_MASK  ((uint16_t)(0x7FFF))

/* ------------------------------------------------------------------------- */

#define UMM_HEAP      ((umm_block *)umm_heap_current.pheap)
#define UMM_HEAPSIZE  (umm_heap_current.heap_size)
#define UMM_NUMBLOCKS (umm_heap_current.numblocks)

#define UMM_BLOCKSIZE  (sizeof(umm_block))
#define UMM_BLOCK_LAST (UMM_NUMBLOCKS - 1)

/* -------------------------------------------------------------------------
 * These macros evaluate to the address of the block and data respectively
 */

#define UMM_BLOCK(b) (UMM_HEAP[b])
#define UMM_DATA(b)  (UMM_BLOCK(b).body.data)

/* -------------------------------------------------------------------------
 * These macros evaluate to the index of the block - NOT the address!!!
 */

#define UMM_NBLOCK(b) (UMM_BLOCK(b).header.used.next)
#define UMM_PBLOCK(b) (UMM_BLOCK(b).header.used.prev)
#define UMM_NFREE(b)  (UMM_BLOCK(b).body.free.next)
#define UMM_PFREE(b)  (UMM_BLOCK(b).body.free.prev)

#ifdef __cplusplus
}
#endif

#endif /* UMM_MALLOC_H */
