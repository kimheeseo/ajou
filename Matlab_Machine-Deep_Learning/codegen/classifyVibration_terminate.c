/*
 * classifyVibration_terminate.c
 *
 * Code generation for function 'classifyVibration_terminate'
 *
 */

/* Include files */
#include "classifyVibration_terminate.h"
#include "_coder_classifyVibration_mex.h"
#include "classifyVibration_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void classifyVibration_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void classifyVibration_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (classifyVibration_terminate.c) */
