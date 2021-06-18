/*
 * File: wrapRK45.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-Jun-2021 20:15:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "RK45.h"
#include "wrapRK45.h"
#include "yprime.h"
#include "RK45_emxutil.h"
#include "norm.h"
#include "RK45_rtwutil.h"

/* Function Declarations */
static void eml_null_assignment(emxArray_real_T *x, const emxArray_real_T *idx);
static void multiStepRK45(double x0[6], double t0, double dt, double tf, double
  RelTol, const struct0_T var, double *out, double *h_next);

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 *                const emxArray_real_T *idx
 * Return Type  : void
 */
static void eml_null_assignment(emxArray_real_T *x, const emxArray_real_T *idx)
{
  int nxin;
  int nrowx;
  int k;
  int nxout;
  emxArray_real_T *b_x;
  int k0;
  emxArray_boolean_T *b;
  nxin = x->size[0] - 1;
  nrowx = x->size[0];
  if (idx->size[1] == 1) {
    for (k = (int)idx->data[0]; k <= nxin; k++) {
      x->data[k - 1] = x->data[k];
    }

    if (nrowx != 1) {
      if (1 > nxin) {
        nxout = 0;
      } else {
        nxout = nxin;
      }

      emxInit_real_T1(&b_x, 1);
      k0 = b_x->size[0];
      b_x->size[0] = nxout;
      emxEnsureCapacity((emxArray__common *)b_x, k0, (int)sizeof(double));
      for (k0 = 0; k0 < nxout; k0++) {
        b_x->data[k0] = x->data[k0];
      }

      k0 = x->size[0];
      x->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)x, k0, (int)sizeof(double));
      nxout = b_x->size[0];
      for (k0 = 0; k0 < nxout; k0++) {
        x->data[k0] = b_x->data[k0];
      }

      emxFree_real_T(&b_x);
    } else {
      if (1 > nxin) {
        nxout = 0;
      } else {
        nxout = nxin;
      }

      emxInit_real_T1(&b_x, 1);
      k0 = b_x->size[0];
      b_x->size[0] = nxout;
      emxEnsureCapacity((emxArray__common *)b_x, k0, (int)sizeof(double));
      for (k0 = 0; k0 < nxout; k0++) {
        b_x->data[k0] = x->data[k0];
      }

      k0 = x->size[0];
      x->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)x, k0, (int)sizeof(double));
      nxout = b_x->size[0];
      for (k0 = 0; k0 < nxout; k0++) {
        x->data[k0] = b_x->data[k0];
      }

      emxFree_real_T(&b_x);
    }
  } else {
    emxInit_boolean_T(&b, 2);
    k0 = b->size[0] * b->size[1];
    b->size[0] = 1;
    b->size[1] = x->size[0];
    emxEnsureCapacity((emxArray__common *)b, k0, (int)sizeof(boolean_T));
    nxout = x->size[0];
    for (k0 = 0; k0 < nxout; k0++) {
      b->data[k0] = false;
    }

    for (k = 1; k <= idx->size[1]; k++) {
      b->data[(int)idx->data[k - 1] - 1] = true;
    }

    k0 = 0;
    for (k = 1; k <= b->size[1]; k++) {
      k0 += b->data[k - 1];
    }

    nxout = x->size[0] - k0;
    k0 = -1;
    for (k = 1; k <= nxin + 1; k++) {
      if ((k > b->size[1]) || (!b->data[k - 1])) {
        k0++;
        x->data[k0] = x->data[k - 1];
      }
    }

    emxFree_boolean_T(&b);
    if (nrowx != 1) {
      if (1 > nxout) {
        nxout = 0;
      }

      emxInit_real_T1(&b_x, 1);
      k0 = b_x->size[0];
      b_x->size[0] = nxout;
      emxEnsureCapacity((emxArray__common *)b_x, k0, (int)sizeof(double));
      for (k0 = 0; k0 < nxout; k0++) {
        b_x->data[k0] = x->data[k0];
      }

      k0 = x->size[0];
      x->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)x, k0, (int)sizeof(double));
      nxout = b_x->size[0];
      for (k0 = 0; k0 < nxout; k0++) {
        x->data[k0] = b_x->data[k0];
      }

      emxFree_real_T(&b_x);
    } else {
      if (1 > nxout) {
        nxout = 0;
      }

      emxInit_real_T1(&b_x, 1);
      k0 = b_x->size[0];
      b_x->size[0] = nxout;
      emxEnsureCapacity((emxArray__common *)b_x, k0, (int)sizeof(double));
      for (k0 = 0; k0 < nxout; k0++) {
        b_x->data[k0] = x->data[k0];
      }

      k0 = x->size[0];
      x->size[0] = b_x->size[0];
      emxEnsureCapacity((emxArray__common *)x, k0, (int)sizeof(double));
      nxout = b_x->size[0];
      for (k0 = 0; k0 < nxout; k0++) {
        x->data[k0] = b_x->data[k0];
      }

      emxFree_real_T(&b_x);
    }
  }
}

/*
 * Arguments    : double x0[6]
 *                double t0
 *                double dt
 *                double tf
 *                double RelTol
 *                const struct0_T var
 *                double *out
 *                double *h_next
 * Return Type  : void
 */
static void multiStepRK45(double x0[6], double t0, double dt, double tf, double
  RelTol, const struct0_T var, double *out, double *h_next)
{
  int last_interval;
  double temp_x0[6];
  int i;
  boolean_T guard1 = false;
  int exitg1;
  double scale;
  int b_i;
  boolean_T exitg2;
  double temp_x[6];
  int c_i;
  double err[6];
  double b_err;
  double yy;
  double maxval;
  last_interval = 0;

  /*  Verify that the step size is positive and that the upper endpoint % */
  /*  of integration is greater than the initial enpoint.               % */
  if ((tf < t0) || (dt <= 0.0)) {
    *out = -2.0;
    *h_next = dt;
  } else {
    /*  If the upper endpoint of the independent variable agrees with the % */
    /*  initial value of the independent variable.  Set the value of the  % */
    /*  dependent variable and return success.                            % */
    *h_next = dt;
    if (tf == t0) {
      *out = 0.0;
    } else {
      /*  Insure that the step size h is not larger than the length of the % */
      /*  integration interval.                                            % */
      if (dt > tf - t0) {
        dt = tf - t0;
        last_interval = 1;
      }

      /*  Redefine the error tolerance to an error tolerance per unit    % */
      /*  length of the integration interval.                            % */
      RelTol /= tf - t0;

      /*  Integrate the diff eq x'=f(t,x) from t=t0 to t=tf trying to  % */
      /*  maintain an error less than tolerance * (tf-t0) using an     % */
      /*  initial step size of h and initial value: x = x[0]            % */
      for (i = 0; i < 6; i++) {
        temp_x0[i] = x0[i];
      }

      guard1 = false;
      do {
        exitg1 = 0;
        if (t0 < tf) {
          scale = 1.0;
          i = 1;
          b_i = 0;
          exitg2 = false;
          while ((!exitg2) && (b_i < 12)) {
            i = b_i + 1;
            for (c_i = 0; c_i < 6; c_i++) {
              temp_x[c_i] = temp_x0[c_i];
            }

            RK45(temp_x, t0, dt, &var, err);
            b_err = b_norm(err);
            if (b_err == 0.0) {
              scale = 4.0;
              exitg2 = true;
            } else {
              if (b_norm(temp_x0) == 0.0) {
                yy = RelTol;
              } else {
                yy = b_norm(temp_x0);
              }

              scale = 0.84 * rt_powd_snf(RelTol * yy / b_err, 0.25);
              if (scale >= 0.125) {
                maxval = scale;
              } else {
                maxval = 0.125;
              }

              if (maxval <= 4.0) {
                scale = maxval;
              } else {
                scale = 4.0;
              }

              if (b_err < RelTol * yy) {
                exitg2 = true;
              } else {
                dt *= scale;
                if (t0 + dt > tf) {
                  dt = tf - t0;
                } else {
                  if ((t0 + dt) + 0.5 * dt > tf) {
                    dt *= 0.5;
                  }
                }

                b_i++;
              }
            }
          }

          if (i >= 12) {
            *h_next = dt * scale;
            *out = -1.0;
            exitg1 = 1;
          } else {
            for (i = 0; i < 6; i++) {
              temp_x0[i] = temp_x[i];
            }

            t0 += dt;
            dt *= scale;
            *h_next = dt;
            if (last_interval != 0) {
              guard1 = true;
              exitg1 = 1;
            } else {
              if (t0 + dt > tf) {
                last_interval = 1;
                dt = tf - t0;
              } else {
                if ((t0 + dt) + 0.5 * dt > tf) {
                  dt *= 0.5;
                }
              }

              guard1 = false;
            }
          }
        } else {
          guard1 = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      if (guard1) {
        for (i = 0; i < 6; i++) {
          x0[i] = temp_x0[i];
        }

        *out = 0.0;
      }
    }
  }
}

/*
 * this function is slightly Differentfrom the format of MATLAB
 *  [T,Y,TE,YE,IE] = solver(odefun,tspan,y0,options)
 *  options = odeset('RelTol',1e-13,'AbsTol',1e-13,...);
 * Arguments    : const emxArray_real_T *t0tf
 *                const double yinit[6]
 *                const struct1_T *options
 *                const struct0_T *var
 *                emxArray_real_T *tspan
 *                emxArray_real_T *yout
 *                double *tf
 *                double yend[6]
 * Return Type  : void
 */
void wrapRK45(const emxArray_real_T *t0tf, const double yinit[6], const
              struct1_T *options, const struct0_T *var, emxArray_real_T *tspan,
              emxArray_real_T *yout, double *tf, double yend[6])
{
  double tolerance;
  emxArray_real_T *y;
  int i;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  int j;
  int nm1d2;
  int k;
  boolean_T variableStepOutPut;
  unsigned int num;
  double dt;
  double tnext;
  unsigned int ii;
  emxArray_real_T *b_yout;
  double dtAttemptVar;
  emxArray_real_T *b_ii;
  int nrowx;
  emxArray_boolean_T *b;
  emxArray_real_T *c_yout;
  int c_ii;
  double x[6];

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*   Description: */
  /*      The Runge-Kutta-Fehlberg method is an adaptive procedure for approxi- */
  /*      mating the solution of the differential equation y'(x) = f(x,y) with */
  /*      initial condition y(x0) = c.  This implementation evaluates f(x,y) */
  /*      thirteen times per step using embedded seventh order and eight order */
  /*      Runge-Kutta estimates to estimate the not only the solution but also */
  /*      the error. */
  /*      The next step size is then calculated using the preassigned tolerance */
  /*      and error estimate. */
  /*      For step i+1, */
  /*         y[i+1] = y[i] +  h * (41/840 * k1 + 34/105 * k6 + 9/35 * k7 */
  /*                         + 9/35 * k8 + 9/280 * k9 + 9/280 k10 + 41/840 k11 ) */
  /*      where */
  /*      k1 = f( x[i],y[i],var ), */
  /*      k2 = f( x[i]+h/2, y[i] + k1*dt/2,var), */
  /*      k3 = f( x[i]+h/2, y[i]+k2*dt/2 ,var), */
  /*      k4 = f( x[i]+h, y[i]+k3*dt/2 ,var), */
  /*      x[i+1] = x[i] + h. */
  /*  */
  /*      The error is estimated to be */
  /*         err = -41/840 * h * ( k1 + k11 - k12 - k13) */
  /*      The step size h is then scaled by the scale factor */
  /*          scale = 0.8 * | epsilon * y[i] / [err * (xmax - x[0])] | ^ 1/7 */
  /*      The scale factor is further constrained 0.125 < scale < 4.0. */
  /*      The new step size is h := scale * h. */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  *tf = t0tf->data[t0tf->size[0] - 1];

  /*  as the length of tspan is not known, it is allocated by the biggest */
  /*  stepsize, and the more lengths will be deleted */
  tolerance = options->RelTol;
  emxInit_real_T(&y, 2);
  if (t0tf->size[0] == 2) {
    if (rtIsNaN(t0tf->data[0]) || rtIsNaN(options->MaxStep) || rtIsNaN
        (t0tf->data[1])) {
      i = 1;
      anew = rtNaN;
      apnd = t0tf->data[1];
    } else if ((options->MaxStep == 0.0) || ((t0tf->data[0] < t0tf->data[1]) &&
                (options->MaxStep < 0.0)) || ((t0tf->data[1] < t0tf->data[0]) &&
                (options->MaxStep > 0.0))) {
      i = 0;
      anew = t0tf->data[0];
      apnd = t0tf->data[1];
    } else if (rtIsInf(t0tf->data[0]) || rtIsInf(t0tf->data[1])) {
      i = 1;
      anew = rtNaN;
      apnd = t0tf->data[1];
    } else if (rtIsInf(options->MaxStep)) {
      i = 1;
      anew = t0tf->data[0];
      apnd = t0tf->data[1];
    } else {
      anew = t0tf->data[0];
      ndbl = floor((t0tf->data[1] - t0tf->data[0]) / options->MaxStep + 0.5);
      apnd = t0tf->data[0] + ndbl * options->MaxStep;
      if (options->MaxStep > 0.0) {
        cdiff = apnd - t0tf->data[1];
      } else {
        cdiff = t0tf->data[1] - apnd;
      }

      absa = fabs(t0tf->data[0]);
      absb = fabs(t0tf->data[1]);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = t0tf->data[1];
      } else if (cdiff > 0.0) {
        apnd = t0tf->data[0] + (ndbl - 1.0) * options->MaxStep;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        i = (int)ndbl;
      } else {
        i = 0;
      }
    }

    j = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = i;
    emxEnsureCapacity((emxArray__common *)y, j, (int)sizeof(double));
    if (i > 0) {
      y->data[0] = anew;
      if (i > 1) {
        y->data[i - 1] = apnd;
        j = i - 1;
        nm1d2 = j / 2;
        for (k = 1; k < nm1d2; k++) {
          ndbl = (double)k * options->MaxStep;
          y->data[k] = anew + ndbl;
          y->data[(i - k) - 1] = apnd - ndbl;
        }

        if (nm1d2 << 1 == i - 1) {
          y->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          ndbl = (double)nm1d2 * options->MaxStep;
          y->data[nm1d2] = anew + ndbl;
          y->data[nm1d2 + 1] = apnd - ndbl;
        }
      }
    }

    j = tspan->size[0];
    tspan->size[0] = y->size[1];
    emxEnsureCapacity((emxArray__common *)tspan, j, (int)sizeof(double));
    i = y->size[1];
    for (j = 0; j < i; j++) {
      tspan->data[j] = y->data[y->size[0] * j];
    }

    if (tspan->data[tspan->size[0] - 1] < t0tf->data[1]) {
      nm1d2 = tspan->size[0];
      j = tspan->size[0];
      tspan->size[0] = nm1d2 + 1;
      emxEnsureCapacity((emxArray__common *)tspan, j, (int)sizeof(double));
      tspan->data[nm1d2] = t0tf->data[1];
    }

    variableStepOutPut = true;
  } else {
    j = tspan->size[0];
    tspan->size[0] = t0tf->size[0];
    emxEnsureCapacity((emxArray__common *)tspan, j, (int)sizeof(double));
    i = t0tf->size[0];
    for (j = 0; j < i; j++) {
      tspan->data[j] = t0tf->data[j];
    }

    variableStepOutPut = false;
  }

  /*  Integration from t=t0 to t=tf */
  num = (unsigned int)tspan->size[0];
  j = yout->size[0] * yout->size[1];
  yout->size[0] = tspan->size[0];
  yout->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)yout, j, (int)sizeof(double));
  i = tspan->size[0] * 6;
  for (j = 0; j < i; j++) {
    yout->data[j] = 0.0;
  }

  for (j = 0; j < 6; j++) {
    yout->data[yout->size[0] * j] = yinit[j];
  }

  for (k = 0; k < 6; k++) {
    yend[k] = yinit[k];
  }

  /*  to column vector */
  /*  to row vector */
  if (variableStepOutPut) {
    /*  variable stepsize and multiple step in a horizon */
    dt = options->MaxStep;
    tnext = t0tf->data[0] + options->MaxStep;
    ii = 1U;
    emxInit_real_T(&b_yout, 2);
    while (tspan->data[(int)ii - 1] < *tf) {
      multiStepRK45(yend, tspan->data[(int)ii - 1], dt, tnext, tolerance, *var,
                    &cdiff, &dtAttemptVar);
      dt = dtAttemptVar;
      ii++;
      if (ii > num) {
        nm1d2 = tspan->size[0];
        j = tspan->size[0];
        tspan->size[0] = nm1d2 + 1;
        emxEnsureCapacity((emxArray__common *)tspan, j, (int)sizeof(double));
        tspan->data[nm1d2] = tnext;
        j = b_yout->size[0] * b_yout->size[1];
        b_yout->size[0] = yout->size[0] + 1;
        b_yout->size[1] = 6;
        emxEnsureCapacity((emxArray__common *)b_yout, j, (int)sizeof(double));
        for (j = 0; j < 6; j++) {
          i = yout->size[0];
          for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
            b_yout->data[nm1d2 + b_yout->size[0] * j] = yout->data[nm1d2 +
              yout->size[0] * j];
          }
        }

        for (j = 0; j < 6; j++) {
          b_yout->data[yout->size[0] + b_yout->size[0] * j] = yend[j];
        }

        j = yout->size[0] * yout->size[1];
        yout->size[0] = b_yout->size[0];
        yout->size[1] = 6;
        emxEnsureCapacity((emxArray__common *)yout, j, (int)sizeof(double));
        for (j = 0; j < 6; j++) {
          i = b_yout->size[0];
          for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
            yout->data[nm1d2 + yout->size[0] * j] = b_yout->data[nm1d2 +
              b_yout->size[0] * j];
          }
        }

        num++;
      } else {
        tspan->data[(int)ii - 1] = tnext;
        for (j = 0; j < 6; j++) {
          yout->data[((int)ii + yout->size[0] * j) - 1] = yend[j];
        }
      }

      tnext += dtAttemptVar;
      if (tnext > *tf) {
        tnext = *tf;
        dt = *tf - tspan->data[(int)ii - 1];
      }
    }

    emxFree_real_T(&b_yout);
    if (ii < num) {
      emxInit_real_T(&b_ii, 2);
      j = b_ii->size[0] * b_ii->size[1];
      b_ii->size[0] = 1;
      b_ii->size[1] = (int)((double)num - ((double)ii + 1.0)) + 1;
      emxEnsureCapacity((emxArray__common *)b_ii, j, (int)sizeof(double));
      i = (int)((double)num - ((double)ii + 1.0));
      for (j = 0; j <= i; j++) {
        b_ii->data[b_ii->size[0] * j] = ((double)ii + 1.0) + (double)j;
      }

      eml_null_assignment(tspan, b_ii);
      j = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = (int)((double)num - ((double)ii + 1.0)) + 1;
      emxEnsureCapacity((emxArray__common *)y, j, (int)sizeof(double));
      i = (int)((double)num - ((double)ii + 1.0));
      emxFree_real_T(&b_ii);
      for (j = 0; j <= i; j++) {
        y->data[y->size[0] * j] = ((double)ii + 1.0) + (double)j;
      }

      nrowx = yout->size[0];
      if (y->size[1] == 1) {
        nm1d2 = yout->size[0] - 1;
        for (j = 0; j < 6; j++) {
          for (i = (int)y->data[0]; i < nrowx; i++) {
            yout->data[(i + yout->size[0] * j) - 1] = yout->data[i + yout->size
              [0] * j];
          }
        }
      } else {
        emxInit_boolean_T(&b, 2);
        j = b->size[0] * b->size[1];
        b->size[0] = 1;
        b->size[1] = yout->size[0];
        emxEnsureCapacity((emxArray__common *)b, j, (int)sizeof(boolean_T));
        i = yout->size[0];
        for (j = 0; j < i; j++) {
          b->data[j] = false;
        }

        for (k = 1; k <= y->size[1]; k++) {
          b->data[(int)y->data[k - 1] - 1] = true;
        }

        i = 0;
        for (k = 1; k <= b->size[1]; k++) {
          i += b->data[k - 1];
        }

        nm1d2 = yout->size[0] - i;
        i = 0;
        for (k = 1; k <= nrowx; k++) {
          if ((k > b->size[1]) || (!b->data[k - 1])) {
            for (j = 0; j < 6; j++) {
              yout->data[i + yout->size[0] * j] = yout->data[(k + yout->size[0] *
                j) - 1];
            }

            i++;
          }
        }

        emxFree_boolean_T(&b);
      }

      if (1 > nm1d2) {
        i = 0;
      } else {
        i = nm1d2;
      }

      emxInit_real_T(&c_yout, 2);
      j = c_yout->size[0] * c_yout->size[1];
      c_yout->size[0] = i;
      c_yout->size[1] = 6;
      emxEnsureCapacity((emxArray__common *)c_yout, j, (int)sizeof(double));
      for (j = 0; j < 6; j++) {
        for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
          c_yout->data[nm1d2 + c_yout->size[0] * j] = yout->data[nm1d2 +
            yout->size[0] * j];
        }
      }

      j = yout->size[0] * yout->size[1];
      yout->size[0] = c_yout->size[0];
      yout->size[1] = 6;
      emxEnsureCapacity((emxArray__common *)yout, j, (int)sizeof(double));
      for (j = 0; j < 6; j++) {
        i = c_yout->size[0];
        for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
          yout->data[nm1d2 + yout->size[0] * j] = c_yout->data[nm1d2 +
            c_yout->size[0] * j];
        }
      }

      emxFree_real_T(&c_yout);
    }
  } else {
    /*  variable stepsize and multiple step in a horizon */
    dtAttemptVar = options->MaxStep;
    for (c_ii = 0; c_ii <= tspan->size[0] - 2; c_ii++) {
      multiStepRK45(yend, tspan->data[c_ii], dtAttemptVar, tspan->data[c_ii + 1],
                    tolerance, *var, &cdiff, &ndbl);
      dtAttemptVar = ndbl;
      for (j = 0; j < 6; j++) {
        yout->data[(c_ii + yout->size[0] * j) + 1] = yend[j];
      }
    }
  }

  emxFree_real_T(&y);
  for (i = 0; i < 6; i++) {
    x[i] = yend[i];
  }

  for (k = 0; k < 6; k++) {
    yend[k] = x[k];
  }

  /*  to the same size as yinit */
}

/*
 * File trailer for wrapRK45.c
 *
 * [EOF]
 */
