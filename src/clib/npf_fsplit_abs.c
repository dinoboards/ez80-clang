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
enum {
  NPF_MANTISSA_BITS = 23,
  NPF_EXPONENT_BITS = 8,
  NPF_EXPONENT_BIAS = 127,
  NPF_FRACTION_BIN_DIGITS = 64,
  NPF_MAX_FRACTION_DEC_DIGITS = 8
};

int npf_fsplit_abs(float f, uint64_t *out_int_part, uint64_t *out_frac_part,
                   int *out_frac_base10_neg_exp) {
  /* conversion algorithm by Wojciech Muła (zdjęcia@garnek.pl)
     http://0x80.pl/notesen/2015-12-29-float-to-string.html
     grisu2 (https://bit.ly/2JgMggX) and ryu (https://bit.ly/2RLXSg0)
     are fast + precise + round, but require large lookup tables. */

  uint32_t f_bits; { // union-cast is UB, let compiler optimize byte-copy loop.
    char const *src = (char const *)&f;
    char *dst = (char *)&f_bits;
    for (unsigned i = 0; i < sizeof(f_bits); ++i) { dst[i] = src[i]; }
  }

  int const exponent =
    ((int)((f_bits >> NPF_MANTISSA_BITS) & ((1u << NPF_EXPONENT_BITS) - 1u)) -
      NPF_EXPONENT_BIAS) - NPF_MANTISSA_BITS;

  if (exponent >= (64 - NPF_MANTISSA_BITS)) { return 0; } // value is out of range

  uint32_t const implicit_one = 1u << NPF_MANTISSA_BITS;
  uint32_t const mantissa = f_bits & (implicit_one - 1);
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

  uint64_t frac; {
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

#endif
