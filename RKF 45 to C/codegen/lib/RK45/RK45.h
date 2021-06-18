/*
 * File: RK45.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 20:15:39
 */

#ifndef __RK45_H__
#define __RK45_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "RK45_types.h"

/* Function Declarations */
extern void RK45(double x[6], double t, double dt, const struct0_T *var, double
                 errorEstimate[6]);

#endif

/*
 * File trailer for RK45.h
 *
 * [EOF]
 */
