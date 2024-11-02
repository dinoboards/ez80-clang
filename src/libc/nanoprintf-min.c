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
   NANOPRINTF_IMPLEMENTATION is defined. In a multi-file library what follows
   would be nanoprintf.c. */

#define NANOPRINTF_IMPLEMENTATION
#include "nanoprintf-min.h"

#define NPF_CLZ(X) ((sizeof(long) * 8) - (size_t)__builtin_clzl(X))

static int npf_bin_len(npf_uint_t u) {
  // Return the length of the binary string format of 'u', preferring
  // intrinsics.
  if (!u) {
    return 1;
  }

  return (int)NPF_CLZ(u);
}

void npf_bufputc_nop(int c, void *ctx) {
  (void)c;
  (void)ctx;
}

void npf_bufputc(int c, void *ctx) {
  npf_bufputc_ctx_t *bpc = (npf_bufputc_ctx_t *)ctx;
  if (bpc->cur < bpc->len) {
    bpc->dst[bpc->cur++] = (char)c;
  }
}

void npf_fputc_std(int c, void *ctx) { fputc(c, (FILE *)ctx); }

enum {
  NPF_MANTISSA_BITS           = 23,
  NPF_EXPONENT_BITS           = 8,
  NPF_EXPONENT_BIAS           = 127,
  NPF_FRACTION_BIN_DIGITS     = 64,
  NPF_MAX_FRACTION_DEC_DIGITS = 8
};

static int npf_fsplit_abs(float f, uint64_t *out_int_part, uint64_t *out_frac_part, int *out_frac_base10_neg_exp) {
  /* conversion algorithm by Wojciech Muła (zdjęcia@garnek.pl)
     http://0x80.pl/notesen/2015-12-29-float-to-string.html
     grisu2 (https://bit.ly/2JgMggX) and ryu (https://bit.ly/2RLXSg0)
     are fast + precise + round, but require large lookup tables. */

  uint32_t f_bits;
  { // union-cast is UB, let compiler optimize byte-copy loop.
    char const *src = (char const *)&f;
    char       *dst = (char *)&f_bits;
    for (unsigned i = 0; i < sizeof(f_bits); ++i) {
      dst[i] = src[i];
    }
  }

  int const exponent =
      ((int)((f_bits >> NPF_MANTISSA_BITS) & ((1u << NPF_EXPONENT_BITS) - 1u)) - NPF_EXPONENT_BIAS) - NPF_MANTISSA_BITS;

  if (exponent >= (64 - NPF_MANTISSA_BITS)) {
    return 0;
  } // value is out of range

  uint32_t const implicit_one  = 1u << NPF_MANTISSA_BITS;
  uint32_t const mantissa      = f_bits & (implicit_one - 1);
  uint32_t const mantissa_norm = mantissa | implicit_one;

  if (exponent > 0) {
    *out_int_part = (uint64_t)mantissa_norm << exponent;
  } else if (exponent < 0) {
    if (-exponent > NPF_MANTISSA_BITS) {
      *out_int_part = 0;
    } else {
      *out_int_part = mantissa_norm >> -exponent;
    }
  } else {
    *out_int_part = mantissa_norm;
  }

  uint64_t frac;
  {
    int const shift = NPF_FRACTION_BIN_DIGITS + exponent - 4;
    if ((shift >= (NPF_FRACTION_BIN_DIGITS - 4)) || (shift < 0)) {
      frac = 0;
    } else {
      frac = ((uint64_t)mantissa_norm) << shift;
    }
    // multiply off the leading one's digit
    frac &= 0x0fffffffffffffffllu;
    frac *= 10;
  }

  { // Count the number of 0s at the beginning of the fractional part.
    int frac_base10_neg_exp = 0;
    while (frac && ((frac >> (NPF_FRACTION_BIN_DIGITS - 4))) == 0) {
      ++frac_base10_neg_exp;
      frac &= 0x0fffffffffffffffllu;
      frac *= 10;
    }
    *out_frac_base10_neg_exp = frac_base10_neg_exp;
  }

  { // Convert the fractional part to base 10.
    uint64_t frac_part = 0;
    for (int i = 0; frac && (i < NPF_MAX_FRACTION_DEC_DIGITS); ++i) {
      frac_part *= 10;
      frac_part += (uint64_t)(frac >> (NPF_FRACTION_BIN_DIGITS - 4));
      frac &= 0x0fffffffffffffffllu;
      frac *= 10;
    }
    *out_frac_part = frac_part;
  }
  return 1;
}

static int npf_ftoa_rev(char *buf, float f, char case_adj, int *out_frac_chars) {
  uint32_t f_bits;
  { // union-cast is UB, let compiler optimize byte-copy loop.
    char const *src = (char const *)&f;
    char       *dst = (char *)&f_bits;
    for (unsigned i = 0; i < sizeof(f_bits); ++i) {
      dst[i] = src[i];
    }
  }

  if ((uint8_t)(f_bits >> 23) == 0xFF) {
    if (f_bits & 0x7fffff) {
      for (int i = 0; i < 3; ++i) {
        *buf++ = (char)("NAN"[i] + case_adj);
      }
    } else {
      for (int i = 0; i < 3; ++i) {
        *buf++ = (char)("FNI"[i] + case_adj);
      }
    }
    return -3;
  }

  uint64_t int_part, frac_part;
  int      frac_base10_neg_exp;
  if (npf_fsplit_abs(f, &int_part, &frac_part, &frac_base10_neg_exp) == 0) {
    for (int i = 0; i < 3; ++i) {
      *buf++ = (char)("ROO"[i] + case_adj);
    }
    return -3;
  }

  char *dst = buf;

  while (frac_part) { // write the fractional digits
    *dst++ = (char)('0' + (frac_part % 10));
    frac_part /= 10;
  }

  // write the 0 digits between the . and the first fractional digit
  while (frac_base10_neg_exp-- > 0) {
    *dst++ = '0';
  }
  *out_frac_chars = (int)(dst - buf);
  *dst++          = '.';

  // write the integer digits
  do {
    *dst++ = (char)('0' + (int_part % 10));
    int_part /= 10;
  } while (int_part);
  return (int)(dst - buf);
}

static int npf_itoa_rev(char *buf, npf_int_t i) {
  int       n    = 0;
  int const sign = (i >= 0) ? 1 : -1;
  do {
    *buf++ = (char)('0' + (sign * (i % 10)));
    i /= 10;
    ++n;
  } while (i);
  return n;
}

static int npf_max(int x, int y) { return (x > y) ? x : y; }

static int npf_min(const int x, const int y) { return (x < y) ? x : y; }
// TODO: replace with !npf_max

static int npf_parse_format_spec(char const *format, npf_format_spec_t *out_spec) {
  char const *cur = format;

  out_spec->case_adjust = 'a' - 'A'; // lowercase
  out_spec->prepend     = 0;
  out_spec->alt_form    = 0;

  while (*++cur) {  // cur points at the leading '%' character
    switch (*cur) { // Optional flags
    case '+':
      out_spec->prepend = '+';
      continue;
    case ' ':
      if (out_spec->prepend == 0) {
        out_spec->prepend = ' ';
      }
      continue;
    case '#':
      out_spec->alt_form = '#';
      continue;
    default:
      break;
    }
    break;
  }

  out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_NONE;
  switch (*cur++) { // Length modifier
  case 'h':
    out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_SHORT;
    if (*cur == 'h') {
      out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_CHAR;
      ++cur;
    }
    break;
  case 'l':
    out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_LONG;
    break;
  default:
    --cur;
    break;
  }

  switch (*cur++) { // Conversion specifier
  case '%':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_PERCENT;
    break;
  case 'c':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_CHAR;
    break;
  case 's':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_STRING;
    break;

  case 'i':
  case 'd':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_SIGNED_INT;
    break;

  case 'o':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_OCTAL;
    break;
  case 'u':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_UNSIGNED_INT;
    break;

  case 'X':
    out_spec->case_adjust = 0;
  case 'x':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_HEX_INT;
    break;

  case 'p':
    out_spec->conv_spec = NPF_FMT_SPEC_CONV_POINTER;
    break;

  default:
    return 0;
  }

  return (int)(cur - format);
}

static void npf_putc_cnt(int c, void *ctx) {
  npf_cnt_putc_ctx_t *pc_cnt = (npf_cnt_putc_ctx_t *)ctx;
  ++pc_cnt->n;
  pc_cnt->pc(c, pc_cnt->ctx); // sibling-call optimization
}

void npf_putc_std(int c, void *ctx) {
  (void)ctx;
  putchar(c);
}

static int npf_utoa_rev(char *buf, npf_uint_t i, unsigned base, unsigned case_adj) {
  int n = 0;
  do {
    unsigned const d = (unsigned)(i % base);
    *buf++           = (char)((d < 10) ? ('0' + d) : ('A' + case_adj + (d - 10)));
    i /= base;
    ++n;
  } while (i);
  return n;
}

int npf_vpprintf(npf_putc pc, void *pc_ctx, char const *format, va_list args) {
  npf_format_spec_t  fs;
  char const        *cur = format;
  npf_cnt_putc_ctx_t pc_cnt;
  pc_cnt.pc  = pc;
  pc_cnt.ctx = pc_ctx;
  pc_cnt.n   = 0;

  while (*cur) {
    int const fs_len = (*cur != '%') ? 0 : npf_parse_format_spec(cur, &fs);
    if (!fs_len) {
      NPF_PUTC(*cur++);
      continue;
    }
    cur += fs_len;

    union {
      char       cbuf_mem[32];
      npf_uint_t binval;
    } u;
    char *cbuf = u.cbuf_mem, sign_c = 0;
    int   cbuf_len = 0, need_0x = 0;

    // Extract and convert the argument to string, point cbuf at the text.
    switch (fs.conv_spec) {
    case NPF_FMT_SPEC_CONV_PERCENT:
      *cbuf = '%';
      ++cbuf_len;
      break;

    case NPF_FMT_SPEC_CONV_CHAR:
      *cbuf = (char)va_arg(args, int);
      ++cbuf_len;
      break;

    case NPF_FMT_SPEC_CONV_STRING: {
      cbuf = va_arg(args, char *);
      for (char const *s = cbuf; *s; ++s, ++cbuf_len)
        ; // strlen
    } break;

    case NPF_FMT_SPEC_CONV_SIGNED_INT: {
      npf_int_t val = 0;
      switch (fs.length_modifier) {
        NPF_EXTRACT(NONE, int, int);
        NPF_EXTRACT(SHORT, short, int);
        NPF_EXTRACT(CHAR, char, int);
        NPF_EXTRACT(LONG, long, long);
      default:
        break;
      }

      sign_c = (val < 0) ? '-' : fs.prepend;

      { cbuf_len = npf_itoa_rev(cbuf, val); }
    } break;

    case NPF_FMT_SPEC_CONV_OCTAL:
    case NPF_FMT_SPEC_CONV_HEX_INT:
    case NPF_FMT_SPEC_CONV_UNSIGNED_INT: {
      npf_uint_t val = 0;

      switch (fs.length_modifier) {
        NPF_EXTRACT(NONE, unsigned, unsigned);
        NPF_EXTRACT(SHORT, unsigned short, unsigned);
        NPF_EXTRACT(CHAR, unsigned char, unsigned);
        NPF_EXTRACT(LONG, unsigned long, unsigned long);
      default:
        break;
      }

      {
        unsigned const base =
            (fs.conv_spec == NPF_FMT_SPEC_CONV_OCTAL) ? 8u : ((fs.conv_spec == NPF_FMT_SPEC_CONV_HEX_INT) ? 16u : 10u);
        cbuf_len = npf_utoa_rev(cbuf, val, base, (unsigned)fs.case_adjust);
      }

      if (val && fs.alt_form && (fs.conv_spec == NPF_FMT_SPEC_CONV_OCTAL)) {
        cbuf[cbuf_len++] = '0'; // OK to add leading octal '0' immediately.
      }

      if (val && fs.alt_form) { // 0x or 0b but can't write it yet.
        if (fs.conv_spec == NPF_FMT_SPEC_CONV_HEX_INT) {
          need_0x = 'X';
        }
        if (need_0x) {
          need_0x += fs.case_adjust;
        }
      }
    } break;

    case NPF_FMT_SPEC_CONV_POINTER: {
      cbuf_len = npf_utoa_rev(cbuf, (npf_uint_t)(uintptr_t)va_arg(args, void *), 16, 'a' - 'A');
      need_0x  = 'x';
    } break;

    default:
      break;
    }

    // Compute the number of bytes to truncate or '0'-pad.
    if (fs.conv_spec != NPF_FMT_SPEC_CONV_STRING) {
    }

    {
      if (need_0x) {
        NPF_PUTC('0');
        NPF_PUTC(need_0x);
      }
    } // no pad, '0x' requested.

    // Write the converted payload
    if (fs.conv_spec == NPF_FMT_SPEC_CONV_STRING) {
      for (int i = 0; i < cbuf_len; ++i) {
        NPF_PUTC(cbuf[i]);
      }
    } else {
      if (sign_c) {
        NPF_PUTC(sign_c);
      }

      {
        while (cbuf_len-- > 0) {
          NPF_PUTC(cbuf[cbuf_len]);
        }
      } // payload is reversed
    }
  }

  return pc_cnt.n;
}
