/*
 * scanfornan.h
 *
 * Code generation for function 'scanfornan'
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
boolean_T b_scanfornan(const emlrtStack *sp, const real_T X[13]);
void scanfornan(boolean_T nanobs[193]);

/* End of code generation (scanfornan.h) */
