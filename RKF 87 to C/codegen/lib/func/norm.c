/*
 * File: norm.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RKF87.h"
#include "Runge_Kutta_Fehlberg_7_8.h"
#include "func.h"
#include "norm.h"

/* Function Definitions */

/*
 * Arguments    : const double x[6]
 * Return Type  : double
 */
double norm(const double x[6])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 6; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * File trailer for norm.c
 *
 * [EOF]
 */
