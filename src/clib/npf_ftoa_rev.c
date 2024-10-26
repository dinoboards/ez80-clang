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

#include "nanoprintf.h"

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1

int npf_ftoa_rev(char *buf, float f, char case_adj, int *out_frac_chars) {
  uint32_t f_bits; { // union-cast is UB, let compiler optimize byte-copy loop.
    char const *src = (char const *)&f;
    char *dst = (char *)&f_bits;
    for (unsigned i = 0; i < sizeof(f_bits); ++i) { dst[i] = src[i]; }
  }

  if ((uint8_t)(f_bits >> 23) == 0xFF) {
    if (f_bits & 0x7fffff) {
      for (int i = 0; i < 3; ++i) { *buf++ = (char)("NAN"[i] + case_adj); }
    } else {
      for (int i = 0; i < 3; ++i) { *buf++ = (char)("FNI"[i] + case_adj); }
    }
    return -3;
  }

  uint64_t int_part, frac_part;
  int frac_base10_neg_exp;
  if (npf_fsplit_abs(f, &int_part, &frac_part, &frac_base10_neg_exp) == 0) {
    for (int i = 0; i < 3; ++i) { *buf++ = (char)("ROO"[i] + case_adj); }
    return -3;
  }

  char *dst = buf;

  while (frac_part) { // write the fractional digits
    *dst++ = (char)('0' + (frac_part % 10));
    frac_part /= 10;
  }

  // write the 0 digits between the . and the first fractional digit
  while (frac_base10_neg_exp-- > 0) { *dst++ = '0'; }
  *out_frac_chars = (int)(dst - buf);
  *dst++ = '.';

  // write the integer digits
  do { *dst++ = (char)('0' + (int_part % 10)); int_part /= 10; } while (int_part);
  return (int)(dst - buf);
}

#endif // NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS
