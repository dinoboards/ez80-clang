#ifndef __IO_H
#define __IO_H

#include <fcntl.h>
#include <io.h>

/* Do not translate CRLF to LF on input/output */
#define _O_BINARY 0

/* Translate CRLF to LF on input/output */
#define _O_TEXT 1

/* For managing CP/M DMABUF fills. For text files remove/insert trailing CTR+Z chars*/
#define _IOTEXT 64

/*  For managing CP/M DMABUF fills. Write 0 at end of files */
#define _IOBINARY 128

int _setmode(int fd, int mode);

#endif
