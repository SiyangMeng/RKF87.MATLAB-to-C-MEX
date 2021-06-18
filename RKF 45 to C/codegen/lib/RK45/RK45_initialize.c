/*
 * File: RK45_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 20:15:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RK45.h"
#include "wrapRK45.h"
#include "yprime.h"
#include "RK45_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void RK45_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for RK45_initialize.c
 *
 * [EOF]
 */
