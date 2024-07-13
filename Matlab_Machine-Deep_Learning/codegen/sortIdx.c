/*
 * sortIdx.c
 *
 * Code generation for function 'sortIdx'
 *
 */

/* Include files */
#include "sortIdx.h"
#include "classifyVibration_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo hb_emlrtRSI = { 561,/* lineNo */
  "merge",                             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo ib_emlrtRSI = { 530,/* lineNo */
  "merge",                             /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

/* Function Definitions */
void merge(const emlrtStack *sp, int32_T idx[193], real_T x[193], int32_T offset,
           int32_T np, int32_T nq, int32_T iwork[193], real_T xwork[193])
{
  emlrtStack b_st;
  emlrtStack st;
  int32_T exitg1;
  int32_T iout;
  int32_T j;
  int32_T n_tmp;
  int32_T p;
  int32_T q;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  if (nq != 0) {
    n_tmp = np + nq;
    st.site = &ib_emlrtRSI;
    if ((1 <= n_tmp) && (n_tmp > 2147483646)) {
      b_st.site = &i_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork[j] = idx[iout];
      xwork[j] = x[iout];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] <= xwork[q]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[q];
        x[iout] = xwork[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          st.site = &hb_emlrtRSI;
          if ((p + 1 <= np) && (np > 2147483646)) {
            b_st.site = &i_emlrtRSI;
            check_forloop_overflow_error(&b_st);
          }

          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx[iout] = iwork[j - 1];
            x[iout] = xwork[j - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/* End of code generation (sortIdx.c) */
