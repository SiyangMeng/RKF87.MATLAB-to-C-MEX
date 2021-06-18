/*
 * File: _coder_func_mex.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

/* Include Files */
#include "_coder_func_api.h"
#include "_coder_func_mex.h"

/* Variable Definitions */
static const char * emlrtEntryPoints[3] = { "func", "RKF87",
  "Runge_Kutta_Fehlberg_7_8" };

/* Function Declarations */
static void RKF87_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs,
  const mxArray *prhs[3]);
static void c_Runge_Kutta_Fehlberg_7_8_mexF(int32_T nlhs, mxArray *plhs[3],
  int32_T nrhs, const mxArray *prhs[5]);
static void func_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[2]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[2]
 *                int32_T nrhs
 *                const mxArray *prhs[3]
 * Return Type  : void
 */
static void RKF87_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs,
  const mxArray *prhs[3])
{
  int32_T n;
  const mxArray *inputs[3];
  const mxArray *outputs[2];
  int32_T b_nlhs;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4, 5,
                        "RKF87");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 5,
                        "RKF87");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  RKF87_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  func_terminate();
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[3]
 *                int32_T nrhs
 *                const mxArray *prhs[5]
 * Return Type  : void
 */
static void c_Runge_Kutta_Fehlberg_7_8_mexF(int32_T nlhs, mxArray *plhs[3],
  int32_T nrhs, const mxArray *prhs[5])
{
  int32_T n;
  const mxArray *inputs[5];
  const mxArray *outputs[3];
  int32_T b_nlhs;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 5, 4,
                        24, "Runge_Kutta_Fehlberg_7_8");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 24,
                        "Runge_Kutta_Fehlberg_7_8");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  Runge_Kutta_Fehlberg_7_8_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  func_terminate();
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[1]
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
static void func_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs, const
  mxArray *prhs[2])
{
  int32_T n;
  const mxArray *inputs[2];
  const mxArray *outputs[1];
  int32_T b_nlhs;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4, 4,
                        "func");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 4,
                        "func");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  func_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  func_terminate();
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(func_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  func_initialize();

  /* Dispatch the entry-point. */
  switch (emlrtGetEntryPointIndex(nrhs, prhs, emlrtEntryPoints, 3)) {
   case 0:
    func_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
    break;

   case 1:
    RKF87_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
    break;

   case 2:
    c_Runge_Kutta_Fehlberg_7_8_mexF(nlhs, plhs, nrhs - 1, &prhs[1]);
    break;
  }
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_func_mex.c
 *
 * [EOF]
 */
