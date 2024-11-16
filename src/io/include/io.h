#ifndef __IO_H
#define __IO_H

#include <cpm.h>

#define MAX_OPEN_FILES 8

// extern FCB __fcb[MAX_OPEN_FILES];

extern int extract_filename_parts(const char *input, FCB *fcb);

extern FCB        *request_fcb();
extern void        free_fcb(FCB *fcb);
static inline void claim_fcb(FCB *fcb) { fcb->use = 1; }

#endif
