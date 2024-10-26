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

#define NANOPRINTF_IMPLEMENTATION

#ifdef NANOPRINTF_IMPLEMENTATION

#ifndef NANOPRINTF_IMPLEMENTATION_INCLUDED
#define NANOPRINTF_IMPLEMENTATION_INCLUDED

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Pick reasonable defaults if nothing's been configured.
#if !defined(NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS) && \
    !defined(NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS) && \
    !defined(NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS) && \
    !defined(NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS) && \
    !defined(NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS) && \
    !defined(NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS)
  #define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 0
  #define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 0
  #define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
  #define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 0
  #define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 0
  #define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#endif

// If anything's been configured, everything must be configured.
#ifndef NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS
  #error NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS must be #defined to 0 or 1
#endif
#ifndef NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS
  #error NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS must be #defined to 0 or 1
#endif
#ifndef NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS
  #error NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS must be #defined to 0 or 1
#endif
#ifndef NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS
  #error NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS must be #defined to 0 or 1
#endif
#ifndef NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS
  #error NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS must be #defined to 0 or 1
#endif
#ifndef NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS
  #error NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS must be #defined to 0 or 1
#endif

// Ensure flags are compatible.
#if (NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1) && \
    (NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 0)
  #error Precision format specifiers must be enabled if float support is enabled.
#endif

#if defined(NANOPRINTF_SNPRINTF_SAFE_EMPTY_STRING_ON_OVERFLOW) && \
    defined(NANOPRINTF_SNPRINTF_SAFE_TRIM_STRING_ON_OVERFLOW)
  #error snprintf safety flags are mutually exclusive.
#endif

// intmax_t / uintmax_t require stdint from c99 / c++11
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
  #ifndef _MSC_VER
    #ifdef __cplusplus
      #if __cplusplus < 201103L
        #error large format specifier support requires C++11 or later.
      #endif
    #else
      #if __STDC_VERSION__ < 199409L
        #error nanoprintf requires C99 or later.
      #endif
    #endif
  #endif
#endif

// Figure out if we can disable warnings with pragmas.
#ifdef __clang__
  #define NANOPRINTF_CLANG 1
  #define NANOPRINTF_GCC_PAST_4_6 0
#else
  #define NANOPRINTF_CLANG 0
  #if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 6)))
    #define NANOPRINTF_GCC_PAST_4_6 1
  #else
    #define NANOPRINTF_GCC_PAST_4_6 0
  #endif
#endif

#if NANOPRINTF_CLANG || NANOPRINTF_GCC_PAST_4_6
  #define NANOPRINTF_HAVE_GCC_WARNING_PRAGMAS 1
#else
  #define NANOPRINTF_HAVE_GCC_WARNING_PRAGMAS 0
#endif

#if NANOPRINTF_HAVE_GCC_WARNING_PRAGMAS
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-function"
  #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
  #ifdef __cplusplus
    #pragma GCC diagnostic ignored "-Wold-style-cast"
  #endif
  #pragma GCC diagnostic ignored "-Wpadded"
  #pragma GCC diagnostic ignored "-Wfloat-equal"
  #if NANOPRINTF_CLANG
    #pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
    #pragma GCC diagnostic ignored "-Wcovered-switch-default"
  #elif NANOPRINTF_GCC_PAST_4_6
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
  #endif
#endif

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable:4514) // unreferenced inline function removed
  #pragma warning(disable:4505) // unreferenced function removed
  #pragma warning(disable:4820) // padding after data member
  #pragma warning(disable:5039) // extern "C" throw
  #pragma warning(disable:5045) // spectre mitigation
  #pragma warning(disable:4701) // possibly uninitialized
  #pragma warning(disable:4706) // assignment in conditional
  #pragma warning(disable:4710) // not inlined
  #pragma warning(disable:4711) // selected for inline
#endif

typedef void (*npf_putc)(int c, void *ctx);

#if (NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1) || \
    (NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1)
typedef enum {
  NPF_FMT_SPEC_OPT_NONE,
  NPF_FMT_SPEC_OPT_LITERAL,
  NPF_FMT_SPEC_OPT_STAR,
} npf_fmt_spec_opt_t;
#endif

typedef enum {
  NPF_FMT_SPEC_LEN_MOD_NONE,
  NPF_FMT_SPEC_LEN_MOD_SHORT,       // 'h'
  NPF_FMT_SPEC_LEN_MOD_CHAR,        // 'hh'
  NPF_FMT_SPEC_LEN_MOD_LONG         // 'l'
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
  ,
  NPF_FMT_SPEC_LEN_MOD_LARGE_LONG_LONG, // 'll'
  NPF_FMT_SPEC_LEN_MOD_LARGE_INTMAX,    // 'j'
  NPF_FMT_SPEC_LEN_MOD_LARGE_SIZET,     // 'z'
  NPF_FMT_SPEC_LEN_MOD_LARGE_PTRDIFFT   // 't'
#endif
} npf_format_spec_length_modifier_t;

typedef enum {
  NPF_FMT_SPEC_CONV_PERCENT,      // '%'
  NPF_FMT_SPEC_CONV_CHAR,         // 'c'
  NPF_FMT_SPEC_CONV_STRING,       // 's'
  NPF_FMT_SPEC_CONV_SIGNED_INT,   // 'i', 'd'
#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
  NPF_FMT_SPEC_CONV_BINARY,       // 'b'
#endif
  NPF_FMT_SPEC_CONV_OCTAL,        // 'o'
  NPF_FMT_SPEC_CONV_HEX_INT,      // 'x', 'X'
  NPF_FMT_SPEC_CONV_UNSIGNED_INT, // 'u'
  NPF_FMT_SPEC_CONV_POINTER       // 'p'
#if NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS == 1
  , NPF_FMT_SPEC_CONV_WRITEBACK   // 'n'
#endif
#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
  , NPF_FMT_SPEC_CONV_FLOAT_DECIMAL // 'f', 'F'
#endif
} npf_format_spec_conversion_t;

typedef struct {
  char prepend;          // ' ' or '+'
  char alt_form;         // '#'

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
  npf_fmt_spec_opt_t field_width_opt;
  int field_width;
  char left_justified;   // '-'
  char leading_zero_pad; // '0'
#endif

#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
  npf_fmt_spec_opt_t prec_opt;
  int prec;
#endif

  npf_format_spec_length_modifier_t length_modifier;
  npf_format_spec_conversion_t conv_spec;
  char case_adjust;
} npf_format_spec_t;

#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 0
  typedef long npf_int_t;
  typedef unsigned long npf_uint_t;
#else
  typedef intmax_t npf_int_t;
  typedef uintmax_t npf_uint_t;
#endif

typedef struct {
  char *dst;
  size_t len;
  size_t cur;
} npf_bufputc_ctx_t;

extern int npf_parse_format_spec(char const *format, npf_format_spec_t *out_spec);
extern void npf_bufputc(int c, void *ctx);
extern void npf_bufputc_nop(int c, void *ctx);
extern int npf_itoa_rev(char *buf, npf_int_t i);
extern int npf_utoa_rev(char *buf, npf_uint_t i, unsigned base, unsigned case_adjust);

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
extern int npf_fsplit_abs(float f,
                          uint64_t *out_int_part,
                          uint64_t *out_frac_part,
                          int *out_frac_base10_neg_e);
extern int npf_ftoa_rev(char *buf, float f, char case_adj, int *out_frac_chars);
#endif

#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
extern int npf_bin_len(npf_uint_t i);
#endif

#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
typedef size_t ssize_t;
#endif

#ifdef _MSC_VER
  #include <intrin.h>
#endif

#endif
#endif

extern int npf_min(int x, int y);
extern int npf_max(int x, int y);
extern void npf_putc_std(int c, void *ctx);
extern void npf_fputc_std(int c, void *ctx);
extern void npf_putc_cnt(int c, void *ctx);

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

