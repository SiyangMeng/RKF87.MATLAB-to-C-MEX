/*
 * File: _coder_func_api.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 10:47:42
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_func_api.h"
#include "_coder_func_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true, false, 131419U, NULL, "func", NULL,
  false, { 2045744189U, 2170104910U, 2743257031U, 4284093946U }, NULL };

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void b_emlrt_marshallOut(const real_T u[6], const mxArray *y);
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *y, const
  char_T *identifier))[6];
static const mxArray *c_emlrt_marshallOut(const real_T u);
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[6];
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *t, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u[6]);
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[6];

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[6]
 *                const mxArray *y
 * Return Type  : void
 */
static void b_emlrt_marshallOut(const real_T u[6], const mxArray *y)
{
  static const int32_T iv2[1] = { 6 };

  mxSetData((mxArray *)y, (void *)u);
  emlrtSetDimensions((mxArray *)y, iv2, 1);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *y
 *                const char_T *identifier
 * Return Type  : real_T (*)[6]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *y, const
  char_T *identifier))[6]
{
  real_T (*b_y)[6];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_y = d_emlrt_marshallIn(sp, emlrtAlias(y), &thisId);
  emlrtDestroyArray(&y);
  return b_y;
}
/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
  static const mxArray *c_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[6]
 */
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[6]
{
  real_T (*y)[6];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
  static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *t
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *t, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(t), &thisId);
  emlrtDestroyArray(&t);
  return y;
}

/*
 * Arguments    : const real_T u[6]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u[6])
{
  const mxArray *y;
  static const int32_T iv0[1] = { 0 };

  const mxArray *m0;
  static const int32_T iv1[1] = { 6 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u);
  emlrtSetDimensions((mxArray *)m0, iv1, 1);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[6]
 */
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[6]
{
  real_T (*ret)[6];
  static const int32_T dims[1] = { 6 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[6])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const mxArray *prhs[3]
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
  void RKF87_api(const mxArray *prhs[3], const mxArray *plhs[2])
{
  real_T (*out)[6];
  real_T (*y)[6];
  real_T x0;
  real_T h;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  out = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, true, -1);

  /* Marshall function inputs */
  y = c_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "y");
  x0 = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "x0");
  h = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "h");

  /* Invoke the target function */
  RKF87(*y, x0, h, *out);

  /* Marshall function outputs */
  b_emlrt_marshallOut(*y, prhs[0]);
  plhs[0] = prhs[0];
  plhs[1] = emlrt_marshallOut(*out);
}

/*
 * Arguments    : const mxArray *prhs[5]
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void Runge_Kutta_Fehlberg_7_8_api(const mxArray *prhs[5], const mxArray *plhs[3])
{
  real_T (*y)[6];
  real_T (*b_y0)[6];
  real_T x;
  real_T h;
  real_T xmax;
  real_T tolerance;
  real_T h_next;
  real_T out;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  y = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  b_y0 = c_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "y0");
  x = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "x");
  h = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "h");
  xmax = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "xmax");
  tolerance = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "tolerance");

  /* Invoke the target function */
  Runge_Kutta_Fehlberg_7_8(*b_y0, x, h, xmax, tolerance, *y, &out, &h_next);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*y);
  plhs[1] = c_emlrt_marshallOut(out);
  plhs[2] = c_emlrt_marshallOut(h_next);
}

/*
 * Arguments    : const mxArray *prhs[2]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void func_api(const mxArray *prhs[2], const mxArray *plhs[1])
{
  real_T (*yp)[6];
  real_T t;
  real_T (*y)[6];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  yp = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);

  /* Marshall function inputs */
  t = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "t");
  y = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "y");

  /* Invoke the target function */
  func(t, *y, *yp);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*yp);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void func_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  func_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void func_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void func_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_func_api.c
 *
 * [EOF]
 */
