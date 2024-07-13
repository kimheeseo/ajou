/*
 * sortIdx.h
 *
 * Code generation for function 'sortIdx'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void merge(const emlrtStack *sp, int32_T idx[193], real_T x[193], int32_T offset,
           int32_T np, int32_T nq, int32_T iwork[193], real_T xwork[193]);

/* End of code generation (sortIdx.h) */
