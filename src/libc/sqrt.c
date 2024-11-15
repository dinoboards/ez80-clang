/************************************************************************/
/*                                                                      */
/*                      Copyright (C)1987-2008 by                       */
/*                              Zilog, Inc.                             */
/*                                                                      */
/*                          San Jose, California                        */
/*                                                                      */
/************************************************************************/

#include <errno.h>
#include <math.h>

// sqrt - Standard C library routine
// sqrt returns the square root of its floating point argument.
//
// Arguments:
//   value     - the floating point argument
//
// Returns:
//   - the square root (or zero if the argument is negative)
//
// Notes:
//   This routine was originally written in C, using Newton's method,
//   which has excellent performance on CPUs with floating point hardware.
//   However, on CPUs without floating point hardware, there is a binary
//   shift algorithm that is much faster.  That algorithm has been
//   separately implemented in assembly language for performance.  For
//   portability and other reasons, this routine calls that routine.
//   This behavior is controlled by the USE_ASM_SQRT symbol (above).
//
double sqrt(double value) {
  if (value < 0.0) {
    errno = EDOM;
    return 0.0;
  }

  return sqrtf(value);
}
