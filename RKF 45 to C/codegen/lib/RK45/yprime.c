/*
 * File: yprime.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 20:15:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RK45.h"
#include "wrapRK45.h"
#include "yprime.h"
#include "norm.h"
#include "RK45_rtwutil.h"

/* Function Definitions */

/*
 * State vector derivative
 * Arguments    : double t
 *                const double y[6]
 *                const struct0_T *var
 *                double yp[6]
 * Return Type  : void
 */
void yprime(double t, const double y[6], const struct0_T *var, double yp[6])
{
  double a;
  int i;
  (void)t;

  /* ------------------------------------------------------------------------------ */
  /*  */
  /*  deriv.m :Computes the derivative of the state vector for the normalized */
  /*           (GM=var.mu) Kepler's problem in three dimensions */
  /*  */
  /*  Inputs: */
  /*    t : time(s) */
  /*    y : state vector(x,y,z,vx,vy,vz) */
  /*  */
  /*  Outputs: */
  /*    yp : derivative of the state vector(vx,vy,vz,ax,ay,az) */
  /*  */
  /*  Last modified:   2018/01/27   M. Mahooti */
  /* ------------------------------------------------------------------------------ */
  a = norm(*(double (*)[3])&y[0]);
  a = rt_powd_snf(a, 3.0);
  for (i = 0; i < 3; i++) {
    yp[i] = y[i + 3];
    yp[i + 3] = -var->mu * y[i] / a;
  }
}

/*
 * File trailer for yprime.c
 *
 * [EOF]
 */
