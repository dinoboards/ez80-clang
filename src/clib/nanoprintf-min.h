#ifndef _NANOPRINTF_H
#define _NANOPRINTF_H

/*
  nanoprintf: a tiny embeddable printf replacement written in C.
  https://github.com/charlesnicholson/nanoprintf
  charles.nicholson+nanoprintf@gmail.com

  LICENSE:
  --------
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org>
*/

/* The implementation of nanoprintf begins here, to be compiled only if
   NANOPRINTF_IMPLEMENTATION is defined. In a multi-file library what follows would
   be nanoprintf.c. */

#ifndef NANOPRINTF_IMPLEMENTATION_INCLUDED
#define NANOPRINTF_IMPLEMENTATION_INCLUDED

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0

#define NANOPRINTF_CLANG 1

#define NANOPRINTF_HAVE_GCC_WARNING_PRAGMAS 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#ifdef __cplusplus
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#pragma GCC diagnostic ignored "-Wcovered-switch-default"

typedef void (*npf_putc)(int c, void *ctx);

typedef enum {
  NPF_FMT_SPEC_LEN_MOD_NONE,
  NPF_FMT_SPEC_LEN_MOD_SHORT,       // 'h'
  NPF_FMT_SPEC_LEN_MOD_CHAR,        // 'hh'
  NPF_FMT_SPEC_LEN_MOD_LONG         // 'l'
} npf_format_spec_length_modifier_t;

typedef enum {
  NPF_FMT_SPEC_CONV_PERCENT,      // '%'
  NPF_FMT_SPEC_CONV_CHAR,         // 'c'
  NPF_FMT_SPEC_CONV_STRING,       // 's'
  NPF_FMT_SPEC_CONV_SIGNED_INT,   // 'i', 'd'
  NPF_FMT_SPEC_CONV_OCTAL,        // 'o'
  NPF_FMT_SPEC_CONV_HEX_INT,      // 'x', 'X'
  NPF_FMT_SPEC_CONV_UNSIGNED_INT, // 'u'
  NPF_FMT_SPEC_CONV_POINTER       // 'p'
} npf_format_spec_conversion_t;

typedef struct {
  char prepend;          // ' ' or '+'
  char alt_form;         // '#'

  npf_format_spec_length_modifier_t length_modifier;
  npf_format_spec_conversion_t conv_spec;
  char case_adjust;
} npf_format_spec_t;

typedef long npf_int_t;
typedef unsigned long npf_uint_t;

typedef struct {
  char *dst;
  size_t len;
  size_t cur;
} npf_bufputc_ctx_t;

static int npf_parse_format_spec(char const *format, npf_format_spec_t *out_spec);
extern void npf_bufputc(int c, void *ctx);
extern void npf_bufputc_nop(int c, void *ctx);
static int npf_itoa_rev(char *buf, npf_int_t i);
static int npf_utoa_rev(char *buf, npf_uint_t i, unsigned base, unsigned case_adjust);

static int npf_fsplit_abs(float f,
                          uint64_t *out_int_part,
                          uint64_t *out_frac_part,
                          int *out_frac_base10_neg_e);
static int npf_ftoa_rev(char *buf, float f, char case_adj, int *out_frac_chars);

#endif

extern void npf_putc_std(int c, void *ctx);
extern void npf_fputc_std(int c, void *ctx);

typedef struct npf_cnt_putc_ctx {
  npf_putc pc;
  void *ctx;
  int n;
} npf_cnt_putc_ctx_t;

#define NPF_PUTC(VAL) do { npf_putc_cnt((int)(VAL), &pc_cnt); } while (0)

#define NPF_EXTRACT(MOD, CAST_TO, EXTRACT_AS) \
  case NPF_FMT_SPEC_LEN_MOD_##MOD: val = (CAST_TO)va_arg(args, EXTRACT_AS); break

#define NPF_WRITEBACK(MOD, TYPE) \
  case NPF_FMT_SPEC_LEN_MOD_##MOD: *(va_arg(args, TYPE *)) = (TYPE)pc_cnt.n; break

extern int npf_vpprintf(npf_putc pc, void *pc_ctx, char const *format, va_list args);

#endif

