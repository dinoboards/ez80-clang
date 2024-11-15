/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                              Zilog, Inc.                             */
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/
#include "include/ieee754.h"
#include <errno.h>
#include <math.h>

// ldexp - Standard C library routine
// ldexp returns the argument multiplied by an integral (positive or
// negative) power of two.
//
// Arguments:
//   value - the floating point argument
//   power - the power of two to be used
//
// Returns:
//   - the argument multiplied by an integral power of two
//
float ldexpf(float value, int power) {
  Ieee754 floating;
  int     exponent;
  int     powerplusexponent;

  if (value == 0.0 || !isfinite(value))
    return value;

  floating.value    = value;
  exponent          = (floating.bits >> exponent_shift) & exponent_mask;
  powerplusexponent = power + exponent;

  if (powerplusexponent > exponent_max) {
    errno = ERANGE;
    return (floating.bits & (1L << sign_shift)) == 0 ? HUGE_VALF : -HUGE_VALF;
  }
  if (powerplusexponent <= exponent_min) // CR 3964
  {
    errno = ERANGE;
    return 0.0;
  }
  floating.bits += (long)power << exponent_shift; // adjust exponent
  return floating.value;
}

double ldexp(double, int) __attribute__((alias("ldexpf")));
