/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#ifndef FORMAT_H
#define FORMAT_H

#include <stdarg.h>
#include <stdio.h>

#ifndef _PTR_
#define _PTR_ *
#endif

/* Note: 24 bits times log(2) is 7.224 decimal digits.
   We only need 14 if and when we support doubles. <THH> */
#define MAXDIGITS         10
#define MINEXP            -4
#define DEFAULT_PRECISION 6

/* format status codes */
#define FMT_OK        0
#define FMT_ERR       1
#define FMT_PASS_THRU 2

/* format flags */
#define FMT_FLAG_MINUS     0x01
#define FMT_FLAG_PLUS      0x02
#define FMT_FLAG_SPACE     0x04
#define FMT_FLAG_POUND     0x08
#define FMT_FLAG_IGNORE    0x10 // scanf only.
#define FMT_FLAG_PRECISION 0x10 // Only needed for %s, as 0 is valid precision
#define FMT_FLAG_UPPERCASE 0x20 // Added. <THH>
#define FMT_FLAG_PAD_ZERO  0x40
#define FMT_FLAG_STRIP     0x80 // Output only. <THH>
#define FMT_FLAG_SET                                                                                                               \
  0x80 // Input only; maybe not needed if
       // set_begin != 0 is used instead. <THH>

struct fmt_type {
  unsigned char    status;      /* status, OK, ERR, or PASS_THRU */
  unsigned char    flags;       /* flags bit mask */
  char             size;        /* size character h,l or L */
  char             chr;         /* pass thru character */
  char             type;        /* type of argument d,i,o,u,x ... */
  unsigned char    field_width; /* field width */
  char             precision;   /* precision */
  const char _PTR_ set_begin;   /* pointer to first char in set */
  const char _PTR_ set_end;     /* pointer to last char in set */
  unsigned char    pad_whole;
  unsigned char    pad_pre_fract;
  unsigned char    pad_post_fract;
  char _PTR_       pad_at;
};

/* info flags */
#define FLT_INFO_SIGN (1 << 0)
#define FLT_INFO_INF  (1 << 1)
#define FLT_INFO_NAN  (1 << 2)

extern int _u_scan(FILE _PTR_ fp, const char _PTR_ src, const char _PTR_ fmt, va_list ap);

extern const char _PTR_ _u_sscan(const char _PTR_ fmt, struct fmt_type _PTR_ str);

#endif
