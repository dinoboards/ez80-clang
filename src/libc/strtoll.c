/************************************************************************/
/*                                    */
/*            Copyright (C)1987-2008 by                */
/*                    Zilog, Inc.                       */
/*                                    */
/*                San Jose, California                 */
/*                                    */
/************************************************************************/
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*************************************************
 *
 * strtoll - string to long long conversion
 *
 * Inputs:
 *    cp - pointer to the character string
 *    endptr - place to put ptr to first invalid character
 *    base - radix
 *
 * Returns:
 *    the value of the number
 *
 *************************************************/
long long strtoll(const char *__restrict nptr, char **__restrict endptr, int base) {
  long long sum, psum;
  char      sign;
  int       radix = base;
  char     *cp    = (char *)nptr;
  char      digit;

  while (isspace(*cp))
    ++cp;

  sign = 0;
  if (*cp == (char)'-') {
    sign = 1;
    ++cp;
  } else if (*cp == (char)'+')
    ++cp;

  if (base == 0) {
    radix = 10;
    if (*cp == (char)'0') {
      if (cp[1] == (char)'x' || cp[1] == (char)'X') {
        radix = 16;
      } else {
        radix = 8;
      }
    }
  }

  if (base == 16 && *cp == (char)'0' && (cp[1] == (char)'x' || cp[1] == (char)'X'))
    cp += 2;

  sum = 0;
  for (;;) {
    digit = toupper(*(cp++));
    if (digit >= (char)'A')
      digit = (digit - (char)'A') + (char)10;
    else
      digit -= (char)'0';
    if (digit < (char)0 || digit >= (char)radix)
      break;
    psum = sum;
    sum *= radix;
    sum += digit;
    if (sum < psum) { /* overflow */
      sum   = sign ? LLONG_MIN : LLONG_MAX;
      errno = ERANGE;
      break;
    }
  }

  if (endptr) {
    --cp;
    if (base == 0) {
      while (*cp == (char)'h' || *cp == (char)'u' || *cp == (char)'l' || *cp == (char)'L')
        ++cp;
    }
    *endptr = (char *)cp;
  }
  return (sign ? -sum : sum);
}
