#ifndef __IO_H
#define __IO_H

#include <cpm.h>

#define MAX_OPEN_FILES 8

typedef struct {
  CPM_FCB cpm_fcb; // Base FCB structure

  /* Below here is used by the library */
  // 7 bytes used by the library
  unsigned long rwptr; /* read/write pointer in bytes */
  uint8_t       use;   /* use flag */
  // uint8_t       uid;     /* user id belonging to this file */
  uint8_t mode;    /* TEXT/BINARY discrimination */
  uint8_t flags;   /* access flags O_RDONLY | O_WRONLY | O_RDWR */
  bool    errored; /* error number */
  bool    eof;     /* end of file */
} FCB;

extern int extract_filename_parts(const char *input, FCB *fcb);

extern FCB        *request_fcb();
extern void        free_fcb(FCB *fcb);
static inline void claim_fcb(FCB *fcb) { fcb->use = 1; }

#define _IOUSE    1
#define _IOREAD   2
#define _IOWRITE  4
#define _IOEOF    8
#define _IOSYSTEM 16
#define _IOEXTRA  32
#define _IOTEXT   64
#define _IOSTRING 128

extern uint8_t buffer[SECSIZE];

#endif
