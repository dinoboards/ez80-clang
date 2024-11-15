/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
/*
        sinh(arg) returns the hyperbolic sine of its floating-
        point argument.

        The exponential function is called for arguments
        greater in magnitude than 0.5.

        A series is used for arguments smaller in magnitude than 0.5.
        The coefficients are #2029 from Hart & Cheney. (20.36D)

        cosh(arg) is computed from the exponential function for
        all arguments.
*/

#include <math.h>

double cosh(double arg) {
  double val;

  if (arg < 0)
    arg = -arg;
  if (arg > 21.) {
    return (exp(arg) / 2);
  }

  val = exp(arg);
  val += exp(-arg);
  val /= 2;
  return (val);
}
