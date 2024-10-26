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

int npf_vpprintf(npf_putc pc, void *pc_ctx, char const *format, va_list args) {
  npf_format_spec_t fs;
  char const *cur = format;
  npf_cnt_putc_ctx_t pc_cnt;
  pc_cnt.pc = pc;
  pc_cnt.ctx = pc_ctx;
  pc_cnt.n = 0;

  while (*cur) {
    int const fs_len = (*cur != '%') ? 0 : npf_parse_format_spec(cur, &fs);
    if (!fs_len) { NPF_PUTC(*cur++); continue; }
    cur += fs_len;

    // Extract star-args immediately
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    if (fs.field_width_opt == NPF_FMT_SPEC_OPT_STAR) {
      fs.field_width_opt = NPF_FMT_SPEC_OPT_LITERAL;
      fs.field_width = va_arg(args, int);
      if (fs.field_width < 0) {
        fs.field_width = -fs.field_width;
        fs.left_justified = 1;
      }
    }
#endif
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
    if (fs.prec_opt == NPF_FMT_SPEC_OPT_STAR) {
      fs.prec_opt = NPF_FMT_SPEC_OPT_NONE;
      fs.prec = va_arg(args, int);
      if (fs.prec >= 0) { fs.prec_opt = NPF_FMT_SPEC_OPT_LITERAL; }
    }
#endif

    union { char cbuf_mem[32]; npf_uint_t binval; } u;
    char *cbuf = u.cbuf_mem, sign_c = 0;
    int cbuf_len = 0, need_0x = 0;
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    int field_pad = 0;
    char pad_c = 0;
#endif
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
    int prec_pad = 0;
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    int zero = 0;
#endif
#endif
#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
    int frac_chars = 0, inf_or_nan = 0;
#endif

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
        for (char const *s = cbuf; *s; ++s, ++cbuf_len); // strlen
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
        if (fs.prec_opt == NPF_FMT_SPEC_OPT_LITERAL) {
          cbuf_len = npf_min(fs.prec, cbuf_len); // prec truncates strings
        }
#endif
      } break;

      case NPF_FMT_SPEC_CONV_SIGNED_INT: {
        npf_int_t val = 0;
        switch (fs.length_modifier) {
          NPF_EXTRACT(NONE, int, int);
          NPF_EXTRACT(SHORT, short, int);
          NPF_EXTRACT(CHAR, char, int);
          NPF_EXTRACT(LONG, long, long);
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
          NPF_EXTRACT(LARGE_LONG_LONG, long long, long long);
          NPF_EXTRACT(LARGE_INTMAX, intmax_t, intmax_t);
          NPF_EXTRACT(LARGE_SIZET, ssize_t, ssize_t);
          NPF_EXTRACT(LARGE_PTRDIFFT, ptrdiff_t, ptrdiff_t);
#endif
          default: break;
        }

        sign_c = (val < 0) ? '-' : fs.prepend;

#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
        zero = !val;
#endif
        // special case, if prec and value are 0, skip
        if (!val && (fs.prec_opt == NPF_FMT_SPEC_OPT_LITERAL) && !fs.prec) {
          cbuf_len = 0;
        } else
#endif
        { cbuf_len = npf_itoa_rev(cbuf, val); }
      } break;

#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
      case NPF_FMT_SPEC_CONV_BINARY:
#endif
      case NPF_FMT_SPEC_CONV_OCTAL:
      case NPF_FMT_SPEC_CONV_HEX_INT:
      case NPF_FMT_SPEC_CONV_UNSIGNED_INT: {
        npf_uint_t val = 0;

        switch (fs.length_modifier) {
          NPF_EXTRACT(NONE, unsigned, unsigned);
          NPF_EXTRACT(SHORT, unsigned short, unsigned);
          NPF_EXTRACT(CHAR, unsigned char, unsigned);
          NPF_EXTRACT(LONG, unsigned long, unsigned long);
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
          NPF_EXTRACT(LARGE_LONG_LONG, unsigned long long, unsigned long long);
          NPF_EXTRACT(LARGE_INTMAX, uintmax_t, uintmax_t);
          NPF_EXTRACT(LARGE_SIZET, size_t, size_t);
          NPF_EXTRACT(LARGE_PTRDIFFT, size_t, size_t);
#endif
          default: break;
        }

#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
        zero = !val;
#endif
        if (!val && (fs.prec_opt == NPF_FMT_SPEC_OPT_LITERAL) && !fs.prec) {
          // Zero value and explicitly-requested zero precision means "print nothing".
          if ((fs.conv_spec == NPF_FMT_SPEC_CONV_OCTAL) && fs.alt_form) {
            fs.prec = 1; // octal special case, print a single '0'
          }
        } else
#endif
#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
        if (fs.conv_spec == NPF_FMT_SPEC_CONV_BINARY) {
          cbuf_len = npf_bin_len(val); u.binval = val;
        } else
#endif
        {
          unsigned const base = (fs.conv_spec == NPF_FMT_SPEC_CONV_OCTAL) ?
            8u : ((fs.conv_spec == NPF_FMT_SPEC_CONV_HEX_INT) ? 16u : 10u);
          cbuf_len = npf_utoa_rev(cbuf, val, base, (unsigned)fs.case_adjust);
        }

        if (val && fs.alt_form && (fs.conv_spec == NPF_FMT_SPEC_CONV_OCTAL)) {
          cbuf[cbuf_len++] = '0'; // OK to add leading octal '0' immediately.
        }

        if (val && fs.alt_form) { // 0x or 0b but can't write it yet.
          if (fs.conv_spec == NPF_FMT_SPEC_CONV_HEX_INT) { need_0x = 'X'; }
#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
          else if (fs.conv_spec == NPF_FMT_SPEC_CONV_BINARY) { need_0x = 'B'; }
#endif
          if (need_0x) { need_0x += fs.case_adjust; }
        }
      } break;

      case NPF_FMT_SPEC_CONV_POINTER: {
        cbuf_len =
          npf_utoa_rev(cbuf, (npf_uint_t)(uintptr_t)va_arg(args, void *), 16, 'a'-'A');
        need_0x = 'x';
      } break;

#if NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS == 1
      case NPF_FMT_SPEC_CONV_WRITEBACK:
        switch (fs.length_modifier) {
          NPF_WRITEBACK(NONE, int);
          NPF_WRITEBACK(SHORT, short);
          NPF_WRITEBACK(LONG, long);
          NPF_WRITEBACK(CHAR, signed char);
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
          NPF_WRITEBACK(LARGE_LONG_LONG, long long);
          NPF_WRITEBACK(LARGE_INTMAX, intmax_t);
          NPF_WRITEBACK(LARGE_SIZET, size_t);
          NPF_WRITEBACK(LARGE_PTRDIFFT, ptrdiff_t);
#endif
          default: break;
        } break;
#endif

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
      case NPF_FMT_SPEC_CONV_FLOAT_DECIMAL: {
        float val;
        val = (float)va_arg(args, double);

        sign_c = (val < 0.f) ? '-' : fs.prepend;
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
        zero = (val == 0.f);
#endif
        cbuf_len = npf_ftoa_rev(cbuf, val, fs.case_adjust, &frac_chars);

        if (cbuf_len < 0) {
          cbuf_len = -cbuf_len;
          inf_or_nan = 1;
        } else {
          int const prec_adj = npf_max(0, frac_chars - fs.prec);
          cbuf += prec_adj;
          cbuf_len -= prec_adj;
        }
      } break;
#endif
      default: break;
    }

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    // Compute the field width pad character
    if (fs.field_width_opt == NPF_FMT_SPEC_OPT_LITERAL) {
      if (fs.leading_zero_pad) { // '0' flag is only legal with numeric types
        if ((fs.conv_spec != NPF_FMT_SPEC_CONV_STRING) &&
            (fs.conv_spec != NPF_FMT_SPEC_CONV_CHAR) &&
            (fs.conv_spec != NPF_FMT_SPEC_CONV_PERCENT)) {
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
          if ((fs.prec_opt == NPF_FMT_SPEC_OPT_LITERAL) && !fs.prec && zero) {
            pad_c = ' ';
          } else
#endif
          { pad_c = '0'; }
        }
      } else { pad_c = ' '; }
    }
#endif

    // Compute the number of bytes to truncate or '0'-pad.
    if (fs.conv_spec != NPF_FMT_SPEC_CONV_STRING) {
#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
      if (!inf_or_nan) { // float precision is after the decimal point
        int const prec_start =
          (fs.conv_spec == NPF_FMT_SPEC_CONV_FLOAT_DECIMAL) ? frac_chars : cbuf_len;
        prec_pad = npf_max(0, fs.prec - prec_start);
      }
#elif NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
      prec_pad = npf_max(0, fs.prec - cbuf_len);
#endif
    }

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    // Given the full converted length, how many pad bytes?
    field_pad = fs.field_width - cbuf_len - !!sign_c;
    if (need_0x) { field_pad -= 2; }

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
    if ((fs.conv_spec == NPF_FMT_SPEC_CONV_FLOAT_DECIMAL) && !fs.prec && !fs.alt_form) {
      ++field_pad; // 0-pad, no decimal point.
    }
#endif
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
    field_pad -= prec_pad;
#endif
    field_pad = npf_max(0, field_pad);
#endif // NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    // Apply right-justified field width if requested
    if (!fs.left_justified && pad_c) { // If leading zeros pad, sign goes first.
      if (pad_c == '0') {
        if (sign_c) { NPF_PUTC(sign_c); sign_c = 0; }
        // Pad byte is '0', write '0x' before '0' pad chars.
        if (need_0x) { NPF_PUTC('0'); NPF_PUTC(need_0x); }
      }
      while (field_pad-- > 0) { NPF_PUTC(pad_c); }
      // Pad byte is ' ', write '0x' after ' ' pad chars but before number.
      if ((pad_c != '0') && need_0x) { NPF_PUTC('0'); NPF_PUTC(need_0x); }
    } else
#endif
    { if (need_0x) { NPF_PUTC('0'); NPF_PUTC(need_0x); } } // no pad, '0x' requested.

    // Write the converted payload
    if (fs.conv_spec == NPF_FMT_SPEC_CONV_STRING) {
      for (int i = 0; i < cbuf_len; ++i) { NPF_PUTC(cbuf[i]); }
    } else {
      if (sign_c) { NPF_PUTC(sign_c); }
#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
      if (fs.conv_spec != NPF_FMT_SPEC_CONV_FLOAT_DECIMAL) {
#endif

#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
        while (prec_pad-- > 0) { NPF_PUTC('0'); } // int precision leads.
#endif

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
      } else {
        // if 0 precision, skip the fractional part and '.'
        // if 0 prec + alternative form, keep the '.'
        if (!fs.prec && !fs.alt_form) { ++cbuf; --cbuf_len; }
      }
#endif

#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
      if (fs.conv_spec == NPF_FMT_SPEC_CONV_BINARY) {
        while (cbuf_len) { NPF_PUTC('0' + ((u.binval >> --cbuf_len) & 1)); }
      } else
#endif
      { while (cbuf_len-- > 0) { NPF_PUTC(cbuf[cbuf_len]); } } // payload is reversed

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
      // real precision comes after the number.
      if ((fs.conv_spec == NPF_FMT_SPEC_CONV_FLOAT_DECIMAL) && !inf_or_nan) {
        while (prec_pad-- > 0) { NPF_PUTC('0'); }
      }
#endif
    }

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
    if (fs.left_justified && pad_c) { // Apply left-justified field width
      while (field_pad-- > 0) { NPF_PUTC(pad_c); }
    }
#endif
  }

  return pc_cnt.n;
}

