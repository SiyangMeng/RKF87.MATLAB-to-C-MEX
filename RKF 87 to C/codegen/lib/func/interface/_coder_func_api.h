/*
 * File: _coder_func_api.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

#ifndef ___CODER_FUNC_API_H__
#define ___CODER_FUNC_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_func_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void RKF87(real_T y[6], real_T x0, real_T h, real_T out[6]);
extern void RKF87_api(const mxArray *prhs[3], const mxArray *plhs[2]);
extern void Runge_Kutta_Fehlberg_7_8(real_T b_y0[6], real_T x, real_T h, real_T
  xmax, real_T tolerance, real_T y[6], real_T *out, real_T *h_next);
extern void Runge_Kutta_Fehlberg_7_8_api(const mxArray *prhs[5], const mxArray
  *plhs[3]);
extern void func(real_T t, real_T y[6], real_T yp[6]);
extern void func_api(const mxArray *prhs[2], const mxArray *plhs[1]);
extern void func_atexit(void);
extern void func_initialize(void);
extern void func_terminate(void);
extern void func_xil_terminate(void);

#endif

/*
 * File trailer for _coder_func_api.h
 *
 * [EOF]
 */
