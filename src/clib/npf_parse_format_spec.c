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

int npf_parse_format_spec(char const *format, npf_format_spec_t *out_spec) {
  char const *cur = format;

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
  out_spec->left_justified = 0;
  out_spec->leading_zero_pad = 0;
#endif
  out_spec->case_adjust = 'a'-'A'; // lowercase
  out_spec->prepend = 0;
  out_spec->alt_form = 0;

  while (*++cur) { // cur points at the leading '%' character
    switch (*cur) { // Optional flags
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
      case '-':
        out_spec->left_justified = '-';
        out_spec->leading_zero_pad = 0;
        continue;
      case '0':
        out_spec->leading_zero_pad = !out_spec->left_justified;
        continue;
#endif
      case '+':
        out_spec->prepend = '+';
        continue;
      case ' ':
        if (out_spec->prepend == 0) { out_spec->prepend = ' '; }
        continue;
      case '#':
        out_spec->alt_form = '#';
        continue;
      default: break;
    }
    break;
  }

#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
  out_spec->field_width_opt = NPF_FMT_SPEC_OPT_NONE;
  if (*cur == '*') {
    out_spec->field_width_opt = NPF_FMT_SPEC_OPT_STAR;
    ++cur;
  } else {
    out_spec->field_width = 0;
    while ((*cur >= '0') && (*cur <= '9')) {
      out_spec->field_width_opt = NPF_FMT_SPEC_OPT_LITERAL;
      out_spec->field_width = (out_spec->field_width * 10) + (*cur++ - '0');
    }
  }
#endif

#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
  out_spec->prec = 0;
  out_spec->prec_opt = NPF_FMT_SPEC_OPT_NONE;
  if (*cur == '.') {
    ++cur;
    if (*cur == '*') {
      out_spec->prec_opt = NPF_FMT_SPEC_OPT_STAR;
      ++cur;
    } else {
      if (*cur == '-') {
        ++cur;
        out_spec->prec_opt = NPF_FMT_SPEC_OPT_NONE;
      } else {
        out_spec->prec_opt = NPF_FMT_SPEC_OPT_LITERAL;
      }
      while ((*cur >= '0') && (*cur <= '9')) {
        out_spec->prec = (out_spec->prec * 10) + (*cur++ - '0');
      }
    }
  }
#endif

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
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
      if (*cur == 'l') {
        out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_LARGE_LONG_LONG;
        ++cur;
      }
#endif
      break;
#if NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS == 1
    case 'j':
      out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_LARGE_INTMAX;
      break;
    case 'z':
      out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_LARGE_SIZET;
      break;
    case 't':
      out_spec->length_modifier = NPF_FMT_SPEC_LEN_MOD_LARGE_PTRDIFFT;
      break;
#endif
    default: --cur; break;
  }

  switch (*cur++) { // Conversion specifier
    case '%':
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_PERCENT;
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
      out_spec->prec_opt = NPF_FMT_SPEC_OPT_NONE;
#endif
      break;
    case 'c':
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_CHAR;
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
      out_spec->prec_opt = NPF_FMT_SPEC_OPT_NONE;
#endif
      break;
    case 's':
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_STRING;
#if NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS == 1
      out_spec->leading_zero_pad = 0;
#endif
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

#if NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS == 1
    case 'F':
      out_spec->case_adjust = 0;
    case 'f':
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_FLOAT_DECIMAL;
      if (out_spec->prec_opt == NPF_FMT_SPEC_OPT_NONE) { out_spec->prec = 6; }
      break;
#endif

#if NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS == 1
    case 'n':
      // todo: reject string if flags or width or precision exist
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_WRITEBACK;
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
      out_spec->prec_opt = NPF_FMT_SPEC_OPT_NONE;
#endif
      break;
#endif

    case 'p':
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_POINTER;
#if NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS == 1
      out_spec->prec_opt = NPF_FMT_SPEC_OPT_NONE;
#endif
      break;

#if NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS == 1
    case 'B':
      out_spec->case_adjust = 0;
    case 'b':
      out_spec->conv_spec = NPF_FMT_SPEC_CONV_BINARY;
      break;
#endif

    default: return 0;
  }

  return (int)(cur - format);
}
