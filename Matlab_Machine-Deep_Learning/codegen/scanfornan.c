/*
 * scanfornan.c
 *
 * Code generation for function 'scanfornan'
 *
 */

/* Include files */
#include "scanfornan.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
boolean_T b_scanfornan(const emlrtStack *sp, const real_T X[13])
{
  jmp_buf * volatile emlrtJBStack;
  int32_T jj;
  int32_T qq;
  boolean_T exitg1;
  boolean_T nanflag;
  boolean_T nanobs;
  nanobs = true;
  emlrtEnterParallelRegion(sp, omp_in_parallel());
  emlrtPushJmpBuf(sp, &emlrtJBStack);

#pragma omp parallel for \
 num_threads(emlrtAllocRegionTLSs(sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(nanflag,jj,exitg1)

  for (qq = 0; qq < 1; qq++) {
    nanflag = false;
    jj = 0;
    exitg1 = false;
    while ((!exitg1) && (jj < 13)) {
      if (muDoubleScalarIsNaN(X[jj])) {
        nanflag = true;
        exitg1 = true;
      } else {
        jj++;
      }
    }

    nanobs = ((!nanflag) && nanobs);
  }

  emlrtPopJmpBuf(sp, &emlrtJBStack);
  emlrtExitParallelRegion(sp, omp_in_parallel());
  return nanobs;
}

void scanfornan(boolean_T nanobs[193])
{
  int32_T i;
  for (i = 0; i < 193; i++) {
    nanobs[i] = true;
  }
}

/* End of code generation (scanfornan.c) */
