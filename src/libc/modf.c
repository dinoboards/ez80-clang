/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                              Zilog, Inc.                             */
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

#include "../crt/include/ieee754.h"
#include <math.h>

// modf - Standard C library routine
// modf returns the integral and fractional components of its
// floating point argument.
//
// Arguments:
//   value     - the floating point argument
//   pIntegral - pointer to the returned integral component
//
// Returns:
//   - the fractional component
//
double modf(double value, double *pIntegral) {
  Ieee754 integral;
  int     exponent;

  integral.value = value;
  frexp(value, &exponent);
  if (exponent <= 0) { // set integral portion to zero
    integral.bits = 0;
  } else if (exponent <= mastissa_bits) { // mask out fractional portion
    integral.bits &= -1L << (mastissa_bits - exponent + 1);
  }
  if (pIntegral != 0) {
    *pIntegral = integral.value;
  }
  return value - integral.value;
}
