/*
 * sort.c
 *
 * Code generation for function 'sort'
 *
 */

/* Include files */
#include "sort.h"
#include "classifyVibration_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "mwmathutil.h"
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo w_emlrtRSI = { 72,  /* lineNo */
  "sort",                              /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sort.m"/* pathName */
};

static emlrtRSInfo x_emlrtRSI = { 105, /* lineNo */
  "sortIdx",                           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo y_emlrtRSI = { 308, /* lineNo */
  "block_merge_sort",                  /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo ab_emlrtRSI = { 333,/* lineNo */
  "block_merge_sort",                  /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo bb_emlrtRSI = { 420,/* lineNo */
  "initialize_vector_sort",            /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo cb_emlrtRSI = { 427,/* lineNo */
  "initialize_vector_sort",            /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo db_emlrtRSI = { 499,/* lineNo */
  "merge_block",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo eb_emlrtRSI = { 506,/* lineNo */
  "merge_block",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo fb_emlrtRSI = { 507,/* lineNo */
  "merge_block",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

static emlrtRSInfo gb_emlrtRSI = { 514,/* lineNo */
  "merge_block",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\eml\\+coder\\+internal\\sortIdx.m"/* pathName */
};

/* Function Definitions */
void sort(const emlrtStack *sp, real_T x[193], int32_T idx[193])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  real_T xwork[193];
  real_T x4[4];
  real_T d;
  real_T d1;
  int32_T iwork[193];
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T ib;
  int32_T k;
  int32_T nNaNs;
  int8_T perm[4];
  uint8_T idx4[4];
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &w_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  memset(&idx[0], 0, 193U * sizeof(int32_T));
  b_st.site = &x_emlrtRSI;
  c_st.site = &y_emlrtRSI;
  x4[0] = 0.0;
  idx4[0] = 0U;
  x4[1] = 0.0;
  idx4[1] = 0U;
  x4[2] = 0.0;
  idx4[2] = 0U;
  x4[3] = 0.0;
  idx4[3] = 0U;
  memset(&xwork[0], 0, 193U * sizeof(real_T));
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 193; k++) {
    if (muDoubleScalarIsNaN(x[k])) {
      idx[192 - nNaNs] = k + 1;
      xwork[192 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (uint8_T)(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        ib = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }

        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[i2 - 1];
          if (d <= d1) {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i2;
            perm[2] = (int8_T)i3;
            perm[3] = (int8_T)i4;
          } else if (d <= x4[i4 - 1]) {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i1;
              perm[2] = (int8_T)i2;
              perm[3] = (int8_T)i4;
            } else {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i1;
              perm[2] = (int8_T)i4;
              perm[3] = (int8_T)i2;
            }
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)i4;
            perm[2] = (int8_T)i1;
            perm[3] = (int8_T)i2;
          }
        }

        idx[ib - 3] = idx4[perm[0] - 1];
        idx[ib - 2] = idx4[perm[1] - 1];
        idx[ib - 1] = idx4[perm[2] - 1];
        idx[ib] = idx4[perm[3] - 1];
        x[ib - 3] = x4[perm[0] - 1];
        x[ib - 2] = x4[perm[1] - 1];
        x[ib - 1] = x4[perm[2] - 1];
        x[ib] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }

  if (ib > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }

    d_st.site = &bb_emlrtRSI;
    if (ib > 2147483646) {
      e_st.site = &i_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }

    for (k = 0; k < ib; k++) {
      i2 = perm[k] - 1;
      i1 = ((k - nNaNs) - ib) + 193;
      idx[i1] = idx4[i2];
      x[i1] = x4[i2];
    }
  }

  ib = (nNaNs >> 1) + 193;
  d_st.site = &cb_emlrtRSI;
  for (k = 0; k <= ib - 194; k++) {
    i2 = (k - nNaNs) + 193;
    i1 = idx[i2];
    idx[i2] = idx[192 - k];
    idx[192 - k] = i1;
    x[i2] = xwork[192 - k];
    x[192 - k] = xwork[i2];
  }

  if ((nNaNs & 1) != 0) {
    ib -= nNaNs;
    x[ib] = xwork[ib];
  }

  if (193 - nNaNs > 1) {
    c_st.site = &ab_emlrtRSI;
    memset(&iwork[0], 0, 193U * sizeof(int32_T));
    i3 = (193 - nNaNs) >> 2;
    i1 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        ib = i1 * i3;
        i2 = 193 - (nNaNs + ib);
        if (i2 > i1) {
          d_st.site = &db_emlrtRSI;
          merge(&d_st, idx, x, ib, i1, i2 - i1, iwork, xwork);
        }
      }

      ib = i1 << 1;
      i3 >>= 1;
      d_st.site = &eb_emlrtRSI;
      for (k = 0; k < i3; k++) {
        d_st.site = &fb_emlrtRSI;
        merge(&d_st, idx, x, k * ib, i1, i1, iwork, xwork);
      }

      i1 = ib;
    }

    if (193 - nNaNs > i1) {
      d_st.site = &gb_emlrtRSI;
      merge(&d_st, idx, x, 0, i1, 193 - (nNaNs + i1), iwork, xwork);
    }
  }
}

/* End of code generation (sort.c) */
