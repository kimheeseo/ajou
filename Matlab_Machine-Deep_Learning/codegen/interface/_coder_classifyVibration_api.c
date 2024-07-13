/*
 * _coder_classifyVibration_api.c
 *
 * Code generation for function '_coder_classifyVibration_api'
 *
 */

/* Include files */
#include "_coder_classifyVibration_api.h"
#include "classifyVibration.h"
#include "classifyVibration_data.h"
#include "classifyVibration_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[13];
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[13];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *features,
  const char_T *identifier))[13];
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const cell_wrap_0
  u[1]);

/* Function Definitions */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[13]
{
  real_T (*y)[13];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[13]
{
  static const int32_T dims[2] = { 1, 13 };

  real_T (*ret)[13];
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[13])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *features,
  const char_T *identifier))[13]
{
  emlrtMsgIdentifier thisId;
  real_T (*y)[13];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(features), &thisId);
  emlrtDestroyArray(&features);
  return y;
}
  static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const
  cell_wrap_0 u[1])
{
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  int32_T iv1[2];
  int32_T iv[1];
  y = NULL;
  iv[0] = 1;
  emlrtAssign(&y, emlrtCreateCellArrayR2014a(1, iv));
  b_y = NULL;
  iv1[0] = u[0].f1.size[0];
  iv1[1] = u[0].f1.size[1];
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a(sp, u[0].f1.size[1], m, &u[0].f1.data[0]);
  emlrtAssign(&b_y, m);
  emlrtSetCell(y, 0, b_y);
  return y;
}

void classifyVibration_api(const mxArray * const prhs[1], const mxArray *plhs[1])
{
  cell_wrap_0 label[1];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  real_T (*features)[13];
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  features = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "features");

  /* Invoke the target function */
  classifyVibration(&st, *features, label);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, label);
}

/* End of code generation (_coder_classifyVibration_api.c) */
