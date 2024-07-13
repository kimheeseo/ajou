/*
 * classifyVibration_types.h
 *
 * Code generation for function 'classifyVibration'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_char_T_1x8
#define struct_emxArray_char_T_1x8

struct emxArray_char_T_1x8
{
  char_T data[8];
  int32_T size[2];
};

#endif                                 /*struct_emxArray_char_T_1x8*/

#ifndef typedef_emxArray_char_T_1x8
#define typedef_emxArray_char_T_1x8

typedef struct emxArray_char_T_1x8 emxArray_char_T_1x8;

#endif                                 /*typedef_emxArray_char_T_1x8*/

#ifndef typedef_cell_wrap_0
#define typedef_cell_wrap_0

typedef struct {
  emxArray_char_T_1x8 f1;
} cell_wrap_0;

#endif                                 /*typedef_cell_wrap_0*/

/* End of code generation (classifyVibration_types.h) */
