/*
 * File: Runge_Kutta_Fehlberg_7_8.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

#ifndef __RUNGE_KUTTA_FEHLBERG_7_8_H__
#define __RUNGE_KUTTA_FEHLBERG_7_8_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "func_types.h"

/* Function Declarations */
extern void Runge_Kutta_Fehlberg_7_8(const double b_y0[6], double x, double h,
  double xmax, double tolerance, double y[6], double *out, double *h_next);

#endif

/*
 * File trailer for Runge_Kutta_Fehlberg_7_8.h
 *
 * [EOF]
 */
