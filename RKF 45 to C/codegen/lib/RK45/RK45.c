/*
 * File: RK45.c
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
 * REFERENCE1: https://github.com/recalon/rkf_calon/rkf_calon.cpp
 *  REFERENCE2: https://github.com/lcsamaro/rkf45/blob/master/main.cpp
 *  const Real tableau[8][7]{
 *    {       0.0,           0.0,            0.0,            0.0,             0.0,        0.0,      0.0 },
 *    {   1.0/4.0,       1.0/4.0,            0.0,            0.0,             0.0,        0.0,      0.0 },
 *    {   3.0/8.0,      3.0/32.0,       9.0/32.0,            0.0,             0.0,        0.0,      0.0 },
 *    { 12.0/13.0, 1932.0/2197.0, -7200.0/2197.0,  7296.0/2197.0,             0.0,        0.0,      0.0 },
 *    {       1.0,   439.0/216.0,           -8.0,   3680.0/513.0,   -845.0/4104.0,        0.0,      0.0 },
 *    {   1.0/2.0,     -8.0/27.0,            2.0, -3544.0/2565.0,   1859.0/4104.0, -11.0/40.0,      0.0 },
 *    {       0.0,    16.0/135.0,            0.0, 6656.0/12825.0, 28561.0/56430.0,  -9.0/50.0, 2.0/55.0 },
 *    {       0.0,    25.0/216.0,            0.0,  1408.0/2565.0,   2197.0/4104.0,   -1.0/5.0,      0.0 }
 *  };
 * Arguments    : double x[6]
 *                double t
 *                double dt
 *                const struct0_T *var
 *                double errorEstimate[6]
 * Return Type  : void
 */
void RK45(double x[6], double t, double dt, const struct0_T *var, double
          errorEstimate[6])
{
  double a;
  int i;
  double k1[6];
  double y[6];
  double k2[6];
  double b_a;
  double k3[6];
  double c_a;
  double k4[6];
  double d_a;
  double k5[6];
  double e_a;
  double b_k2;
  (void)t;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*   RK4(yprime, y, x0, h)                                                */
  /*                                                                              */
  /*   Description:                                                               */
  /*      This routine uses Fehlberg's embedded 7th and 8th order methods to      */
  /*      approximate the solution of the differential equation y'=f(x,y) with    */
  /*      the initial condition y = y0 at x = x0. The value at x + h is returned  */
  /*      in y. The function returns err/h ( the absolute error per step size ).  */
  /*                                                                              */
  /*   Arguments:                                                                 */
  /*      yprime	function handle which returns the slope at (x,y) of integral  */
  /*            curve of the differential equation y' = f(x,y) which passes     */
  /*            through the point (x0,y0). 			                        */
  /*      y     On input y is the initial value of y at x, on output y is      */
  /*                the solution at x + h.                              	    */
  /*      x     Initial value of x.                                        */
  /*      h     Step size                                                  */
  /*                                                                              */
  /*   Return Values:                                                             */
  /*      This routine returns the err/h.  The solution of y(x) at x + h is       */
  /*      returned in y.                                                          */
  /*                                                                              */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  State vector derivative */
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
  a = norm(*(double (*)[3])&x[0]);
  a = rt_powd_snf(a, 3.0);
  for (i = 0; i < 3; i++) {
    k1[i] = x[i + 3];
    k1[i + 3] = -var->mu * x[i] / a;
  }

  for (i = 0; i < 6; i++) {
    y[i] = x[i] + dt * k1[i] / 4.0;
  }

  /*  State vector derivative */
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
    k2[i] = y[i + 3];
    k2[i + 3] = -var->mu * y[i] / a;
  }

  a = 3.0 * dt;
  b_a = 9.0 * dt;
  for (i = 0; i < 6; i++) {
    y[i] = (x[i] + a * k1[i] / 32.0) + b_a * k2[i] / 32.0;
  }

  /*  State vector derivative */
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
    k3[i] = y[i + 3];
    k3[i + 3] = -var->mu * y[i] / a;
  }

  a = 1932.0 * dt;
  b_a = 7200.0 * dt;
  c_a = 7296.0 * dt;
  for (i = 0; i < 6; i++) {
    y[i] = ((x[i] + a * k1[i] / 2197.0) - b_a * k2[i] / 2197.0) + c_a * k3[i] /
      2197.0;
  }

  /*  State vector derivative */
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
    k4[i] = y[i + 3];
    k4[i + 3] = -var->mu * y[i] / a;
  }

  a = 439.0 * dt;
  b_a = 8.0 * dt;
  c_a = 3680.0 * dt;
  d_a = 845.0 * dt;
  for (i = 0; i < 6; i++) {
    y[i] = (((x[i] + a * k1[i] / 216.0) - b_a * k2[i]) + c_a * k3[i] / 513.0) -
      d_a * k4[i] / 4104.0;
  }

  /*  State vector derivative */
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
    k5[i] = y[i + 3];
    k5[i + 3] = -var->mu * y[i] / a;
  }

  a = 8.0 * dt;
  b_a = 2.0 * dt;
  c_a = 3544.0 * dt;
  d_a = 1859.0 * dt;
  e_a = 11.0 * dt;

  /*  State vector derivative */
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
  for (i = 0; i < 6; i++) {
    b_k2 = ((((x[i] - a * k1[i] / 27.0) + b_a * k2[i]) - c_a * k3[i] / 2565.0) +
            d_a * k4[i] / 4104.0) - e_a * k5[i] / 40.0;
    x[i] += dt * (((k1[i] * 25.0 / 216.0 + k3[i] * 1408.0 / 2565.0) + k4[i] *
                   2197.0 / 4104.0) - k5[i] / 5.0);
    k2[i] = b_k2;
  }

  a = norm(*(double (*)[3])&k2[0]);
  a = rt_powd_snf(a, 3.0);
  for (i = 0; i < 3; i++) {
    errorEstimate[i] = ((((16.0 * k1[i] / 135.0 + 6656.0 * k3[i] / 12825.0) +
                          28561.0 * k4[i] / 56430.0) - 9.0 * k5[i] / 50.0) + 2.0
                        * k2[i + 3] / 55.0) - (((25.0 * k1[i] / 216.0 + 1408.0 *
      k3[i] / 2565.0) + 2197.0 * k4[i] / 4104.0) - k5[i] / 5.0);
    errorEstimate[i + 3] = ((((16.0 * k1[i + 3] / 135.0 + 6656.0 * k3[i + 3] /
      12825.0) + 28561.0 * k4[i + 3] / 56430.0) - 9.0 * k5[i + 3] / 50.0) + 2.0 *
      (-var->mu * k2[i] / a) / 55.0) - (((25.0 * k1[i + 3] / 216.0 + 1408.0 *
      k3[i + 3] / 2565.0) + 2197.0 * k4[i + 3] / 4104.0) - k5[i + 3] / 5.0);
  }

  /*  errorEstimate = k1/360 - k3*128/4275 - k4*2197/75240 + k5/50 + k6*2/55; */
}

/*
 * File trailer for RK45.c
 *
 * [EOF]
 */
