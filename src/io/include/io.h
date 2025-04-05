#ifndef __INTERNAL_IO_H
#define __INTERNAL_IO_H

#include <cpm.h>
#include <io.h>

#define MAX_OPEN_FILES 8

typedef struct {
  CPM_FCB cpm_fcb; // Base FCB structure

  /* Below here is used by the library */
  // 7 bytes used by the library
  unsigned long rwptr;   /* read/write pointer in bytes */
  uint8_t       use;     /* use flag */
  uint8_t       mode;    /* TEXT/BINARY discrimination */
  uint8_t       flags;   /* access flags O_RDONLY | O_WRONLY | O_RDWR */
  bool          errored; /* error number */
  bool          eof;     /* end of file */
} FCB;

typedef struct {
  uint8_t mode; /* mode of the stream */
} stdio_config_t;

extern stdio_config_t _stdin;
extern stdio_config_t _stdout;
#define _stderr _stdout

extern int extract_filename_parts(const char *input, FCB *fcb);

extern FCB        *request_fcb();
extern void        free_fcb(FCB *fcb);
static inline void claim_fcb(FCB *fcb) { fcb->use = 1; }

extern uint8_t ___fbuffer[SECSIZE];

#endif
