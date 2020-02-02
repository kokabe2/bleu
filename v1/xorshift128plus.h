// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT128PLUS_H_
#define V1_XORSHIFT128PLUS_H_

#include "xorshift_plus.h"

typedef struct {
  XorshiftPlus (*New)(void);  // Use xorshiftPlus::Delete when delete.
} XorshiftPlus128MethodStruct;
typedef const XorshiftPlus128MethodStruct* XorshiftPlus128Method;

extern const XorshiftPlus128Method xorshift128plus;

#endif  // V1_XORSHIFT128PLUS_H_
