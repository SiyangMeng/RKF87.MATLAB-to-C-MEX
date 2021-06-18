/*
 * File: wrapRK45.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 20:15:39
 */

#ifndef __WRAPRK45_H__
#define __WRAPRK45_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "RK45_types.h"

/* Function Declarations */
extern void wrapRK45(const emxArray_real_T *t0tf, const double yinit[6], const
                     struct1_T *options, const struct0_T *var, emxArray_real_T
                     *tspan, emxArray_real_T *yout, double *tf, double yend[6]);

#endif

/*
 * File trailer for wrapRK45.h
 *
 * [EOF]
 */
