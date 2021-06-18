/*
 * File: RKF87.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RKF87.h"
#include "Runge_Kutta_Fehlberg_7_8.h"
#include "func.h"

/* Function Definitions */

/*
 * Arguments    : double y[6]
 *                double x0
 *                double h
 *                double out[6]
 * Return Type  : void
 */
void RKF87(double y[6], double x0, double h, double out[6])
{
  double h2_7;
  double b_y[6];
  int i;
  double k2[6];
  double k4[6];
  double k6[6];
  double k7[6];
  double k8[6];
  double k9[6];
  double k10[6];
  double k11[6];
  double k12[6];

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*   Runge_Kutta(func, y, x0, h)                                                */
  /*                                                                              */
  /*   Description:                                                               */
  /*      This routine uses Fehlberg's embedded 7th and 8th order methods to      */
  /*      approximate the solution of the differential equation y'=f(x,y) with    */
  /*      the initial condition y = y0 at x = x0. The value at x + h is returned  */
  /*      in y. The function returns err/h ( the absolute error per step size ).  */
  /*                                                                              */
  /*   Arguments:                                                                 */
  /*      func       function which returns the slope at (x,y) of integral curve  */
  /*  				 of the differential equation y' = f(x,y) which passes      */
  /*                 through the point (x0,y0). 			                        */
  /*      y 		 On input y is the initial value of y at x, on output y is      */
  /*  				 the solution at x + h.                              	    */
  /*      x   		 Initial value of x.                                        */
  /*      h   		 Step size                                                  */
  /*                                                                              */
  /*   Return Values:                                                             */
  /*      This routine returns the err/h.  The solution of y(x) at x + h is       */
  /*      returned in y.                                                          */
  /*                                                                              */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  h2_7 = 0.07407407407407407 * h;
  func(x0, y, out);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h2_7 * out[i];
  }

  func(x0 + h2_7, b_y, k2);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (0.027777777777777776 * out[i] + 0.083333333333333329 *
                         k2[i]);
  }

  func(x0 + 0.1111111111111111 * h, b_y, k2);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (0.041666666666666664 * out[i] + 0.125 * k2[i]);
  }

  func(x0 + 0.16666666666666666 * h, b_y, k4);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * ((0.41666666666666669 * out[i] + -1.5625 * k2[i]) +
                         1.5625 * k4[i]);
  }

  func(x0 + 0.41666666666666669 * h, b_y, k2);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * ((0.05 * out[i] + 0.25 * k4[i]) + 0.2 * k2[i]);
  }

  func(x0 + 0.5 * h, b_y, k6);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (((-0.23148148148148148 * out[i] + 1.1574074074074074 *
      k4[i]) + -2.4074074074074074 * k2[i]) + 2.3148148148148149 * k6[i]);
  }

  func(x0 + 0.83333333333333337 * h, b_y, k7);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (((0.10333333333333333 * out[i] + 0.27111111111111114 *
      k2[i]) + -0.22222222222222221 * k6[i]) + 0.014444444444444444 * k7[i]);
  }

  func(x0 + 0.16666666666666666 * h, b_y, k8);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (((((2.0 * out[i] + -8.8333333333333339 * k4[i]) +
      15.644444444444444 * k2[i]) + -11.888888888888889 * k6[i]) +
                          0.74444444444444446 * k7[i]) + 3.0 * k8[i]);
  }

  func(x0 + 0.66666666666666663 * h, b_y, k9);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * ((((((-0.84259259259259256 * out[i] +
      0.21296296296296297 * k4[i]) + -7.2296296296296294 * k2[i]) +
      5.7592592592592595 * k6[i]) + -0.31666666666666665 * k7[i]) +
                          2.8333333333333335 * k8[i]) + -0.083333333333333329 *
                         k9[i]);
  }

  func(x0 + 0.33333333333333331 * h, b_y, k10);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (((((((0.58121951219512191 * out[i] +
      -2.0792682926829267 * k4[i]) + 4.3863414634146345 * k2[i]) +
      -3.6707317073170733 * k6[i]) + 0.52024390243902441 * k7[i]) +
      0.54878048780487809 * k8[i]) + 0.27439024390243905 * k9[i]) +
                         0.43902439024390244 * k10[i]);
  }

  func(x0 + h, b_y, k11);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * (((((0.014634146341463415 * out[i] +
      -0.14634146341463414 * k6[i]) + -0.014634146341463415 * k7[i]) +
      -0.073170731707317069 * k8[i]) + 0.073170731707317069 * k9[i]) +
                         0.14634146341463414 * k10[i]);
  }

  func(x0, b_y, k12);
  for (i = 0; i < 6; i++) {
    b_y[i] = y[i] + h * ((((((((-0.43341463414634146 * out[i] +
      -2.0792682926829267 * k4[i]) + 4.3863414634146345 * k2[i]) +
      -3.524390243902439 * k6[i]) + 0.53487804878048784 * k7[i]) +
      0.62195121951219512 * k8[i]) + 0.20121951219512196 * k9[i]) +
                          0.29268292682926828 * k10[i]) + k12[i]);
    y[i] += h * (((0.04880952380952381 * (out[i] + k11[i]) + 0.32380952380952382
                   * k6[i]) + 0.25714285714285712 * (k7[i] + k8[i])) +
                 0.03214285714285714 * (k9[i] + k10[i]));
  }

  func(x0 + h, b_y, k2);
  for (i = 0; i < 6; i++) {
    out[i] = -0.04880952380952381 * (((out[i] + k11[i]) - k12[i]) - k2[i]);
  }
}

/*
 * File trailer for RKF87.c
 *
 * [EOF]
 */
