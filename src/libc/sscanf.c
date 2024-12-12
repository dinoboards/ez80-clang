/************************************************************************/
/*                                                                      */
/*      Copyright (C)1987-2008 by                                       */
/*                Zilog, Inc.                                           */
/*                                                                      */
/*            San Jose, California                                      */
/*                                                                      */
/************************************************************************/
#include <format.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

int sscanf(const char *string, const char *fmt, ...) {
  va_list ap;

  if (string == NULL)
    return EOF;

  va_start(ap, fmt);
  return _u_scan((FILE *)NULL, string, fmt, ap);
}
