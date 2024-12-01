/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

/*
        computes a^b.
        uses log and exp
*/

#include <errno.h>
#include <math.h>

double pow(double base, double expnt) {
  long n;

  if (base == 0) {
    if (expnt <= 0)
      goto domain; // 0 to power <= 0
    return 1.0;
  }

  n = expnt;
  if (n == expnt) {
    // Integer exponent, do it with repeat multiplication
    unsigned long bit    = 1;
    double        result = 1.0;
    double        pwr    = base;
    if (n < 0) {
      n   = -n;
      pwr = 1.0 / pwr;
    }

    while (1) {
      if (bit & n)
        result *= pwr;
      bit <<= 1;
      if (bit > (unsigned long)n)
        break;
      pwr = pwr * pwr;
    }
    return result;
  }

  if (base < 0.)
    goto domain; // negative number to non-integer power

  float f = log(base);
  return (exp(expnt * f));

domain:
  errno = EDOM;
  return (0.0);
}
