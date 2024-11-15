/************************************************************************/
/*                                                                      */
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

#include "../crt/include/ieee754.h"
#include <math.h>

// frexp - Standard C library routine
// frexp returns the exponent and mantissa of its floating point
// argument.
//
// Arguments:
//   value     - the floating point argument
//   pExponent - pointer to the returned exponent
//
// Returns:
//   - a floating point number between 0.5 and 1.0 (or zero if
//     the input argument is zero)
//
double frexp(double value, int *pExponent) {
  Ieee754 floating;
  long    exponentBits = 0;

  floating.value = value;
  if (value != 0.0) {
    exponentBits = (floating.bits & ((unsigned long)exponent_mask << exponent_shift)) - ((exponent_base - 1L) << exponent_shift);
    floating.bits -= exponentBits; // adjust exponent
  }
  if (pExponent != 0) {
    *pExponent = exponentBits >> exponent_shift;
  }
  return floating.value;
}
