/************************************************************************/
/*									*/
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*									*/
/************************************************************************/
/*
        floating-point arctangent

        atan returns the value of the arctangent of its
        argument in the range [-pi/2,pi/2].

        atan2 returns the arctangent of arg1/arg2
        in the range [-pi,pi].

        there are no error returns.

        coefficients are #5077 from Hart & Cheney. (19.56D)
*/

/*
        atan makes its argument positive and
        calls the inner routine satan.
*/

extern double satan(double);

double atan(double arg) {

  if (arg > 0)
    return (satan(arg));

  return (-satan(-arg));
}

/*
        atan2 discovers what quadrant the angle
        is in and calls atan.
*/
