/*
 * File: func_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RKF87.h"
#include "Runge_Kutta_Fehlberg_7_8.h"
#include "func.h"
#include "func_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void func_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for func_initialize.c
 *
 * [EOF]
 */
