/*
 * File: func.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RKF87.h"
#include "Runge_Kutta_Fehlberg_7_8.h"
#include "func.h"
#include "func_rtwutil.h"

/* Function Definitions */

/*
 * State vector derivative
 * Arguments    : double t
 *                const double y[6]
 *                double yp[6]
 * Return Type  : void
 */
void func(double t, const double y[6], double yp[6])
{
  double b_y;
  double scale;
  int k;
  double absxk;
  double b_t;
  (void)t;

  /* ------------------------------------------------------------------------------ */
  /*  */
  /*  deriv.m :Computes the derivative of the state vector for the normalized */
  /*           (GM=1) Kepler's problem in three dimensions */
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
  b_y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 3; k++) {
    absxk = fabs(y[k]);
    if (absxk > scale) {
      b_t = scale / absxk;
      b_y = 1.0 + b_y * b_t * b_t;
      scale = absxk;
    } else {
      b_t = absxk / scale;
      b_y += b_t * b_t;
    }

    yp[k] = y[k + 3];
  }

  b_y = scale * sqrt(b_y);
  b_y = rt_powd_snf(b_y, 3.0);
  for (k = 0; k < 3; k++) {
    yp[k + 3] = -y[k] / b_y;
  }
}

/*
 * File trailer for func.c
 *
 * [EOF]
 */
