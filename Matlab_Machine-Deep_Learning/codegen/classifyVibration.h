/*
 * classifyVibration.h
 *
 * Code generation for function 'classifyVibration'
 *
 */

#pragma once

/* Include files */
#include "classifyVibration_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void classifyVibration(const emlrtStack *sp, const real_T features[13],
  cell_wrap_0 label[1]);
emlrtCTX emlrtGetRootTLSGlobal(void);
void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX aTLS,
  void *aData);

/* End of code generation (classifyVibration.h) */
