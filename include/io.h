#ifndef __IO_H
#define __IO_H

#include <fcntl.h>
#include <io.h>

/* Translate CRLF to LF on input/output */
/* default for console */
/* Not supported for file i/o */
#define _IOTEXT_TRANSLATION 1

/* remove/insert trailing CTR+Z chars*/
#define _IOTEXT 2

/* Write 0 at end of files, no CRLF translation */
/* File IO default */
#define _IOBINARY 4

int _setmode(int fd, int mode);

#endif
