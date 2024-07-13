/*
 * pdist2.c
 *
 * Code generation for function 'pdist2'
 *
 */

/* Include files */
#include "pdist2.h"
#include "rt_nonfinite.h"
#include "scanfornan.h"
#include "sort.h"
#include "mwmathutil.h"
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo t_emlrtRSI = { 459, /* lineNo */
  "pdist2",                            /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\stats\\eml\\pdist2.m"/* pathName */
};

static emlrtRSInfo u_emlrtRSI = { 743, /* lineNo */
  "partialSort",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\stats\\eml\\pdist2.m"/* pathName */
};

static emlrtRSInfo v_emlrtRSI = { 27,  /* lineNo */
  "sort",                              /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\eml\\lib\\matlab\\datafun\\sort.m"/* pathName */
};

static emlrtRSInfo qb_emlrtRSI = { 362,/* lineNo */
  "pdist2",                            /* fcnName */
  "C:\\Program Files\\MATLAB\\R2020b\\toolbox\\stats\\eml\\pdist2.m"/* pathName */
};

/* Function Definitions */
void pdist2(const emlrtStack *sp, const real_T Xin[2509], const real_T Yin[13],
            real_T *D, real_T *b_I)
{
  jmp_buf b_emlrtJBEnviron;
  jmp_buf * volatile emlrtJBStack;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  real_T X[2509];
  real_T d[193];
  real_T Y[13];
  real_T tempSum;
  int32_T iidx[193];
  int32_T b_i;
  int32_T i;
  int32_T ii;
  int32_T jj;
  boolean_T logIndX[193];
  boolean_T emlrtHadParallelError = false;
  boolean_T logIndY;
  st.prev = sp;
  st.tls = sp->tls;
  for (ii = 0; ii < 193; ii++) {
    for (i = 0; i < 13; i++) {
      X[i + 13 * ii] = Xin[ii + 193 * i];
    }
  }

  memcpy(&Y[0], &Yin[0], 13U * sizeof(real_T));
  scanfornan(logIndX);
  st.site = &qb_emlrtRSI;
  logIndY = b_scanfornan(&st, Yin);
  emlrtEnterParallelRegion(sp, omp_in_parallel());
  emlrtPushJmpBuf(sp, &emlrtJBStack);

#pragma omp parallel \
 num_threads(emlrtAllocRegionTLSs(sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(tempSum,d,b_emlrtJBEnviron,e_st,b_i,jj,iidx) \
 firstprivate(b_st,c_st,d_st,emlrtHadParallelError)

  {
    if (setjmp(b_emlrtJBEnviron) == 0) {
      b_st.prev = sp;
      b_st.tls = emlrtAllocTLS(sp, omp_get_thread_num());
      b_st.site = NULL;
      emlrtSetJmpBuf(&b_st, &b_emlrtJBEnviron);
      c_st.prev = &b_st;
      c_st.tls = b_st.tls;
      d_st.prev = &c_st;
      d_st.tls = c_st.tls;
      e_st.prev = &d_st;
      e_st.tls = d_st.tls;
    } else {
      emlrtHadParallelError = true;
    }

#pragma omp for nowait

    for (ii = 0; ii < 1; ii++) {
      if (emlrtHadParallelError)
        continue;
      if (setjmp(b_emlrtJBEnviron) == 0) {
        for (b_i = 0; b_i < 193; b_i++) {
          d[b_i] = rtNaN;
        }

        if (logIndY) {
          for (b_i = 0; b_i < 193; b_i++) {
            if (logIndX[b_i]) {
              tempSum = 0.0;
              for (jj = 0; jj < 13; jj++) {
                tempSum += muDoubleScalarAbs(X[jj + 13 * b_i] - Y[jj]);
              }

              d[b_i] = tempSum;
            }
          }
        }

        c_st.site = &t_emlrtRSI;
        d_st.site = &u_emlrtRSI;
        e_st.site = &v_emlrtRSI;
        sort(&e_st, d, iidx);
        *D = d[0];
        *b_I = iidx[0];
      } else {
        emlrtHadParallelError = true;
      }
    }
  }

  emlrtPopJmpBuf(sp, &emlrtJBStack);
  emlrtExitParallelRegion(sp, omp_in_parallel());
}

/* End of code generation (pdist2.c) */
