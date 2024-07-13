/*
 * pdist2.h
 *
 * Code generation for function 'pdist2'
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
void pdist2(const emlrtStack *sp, const real_T Xin[2509], const real_T Yin[13],
            real_T *D, real_T *b_I);

/* End of code generation (pdist2.h) */
