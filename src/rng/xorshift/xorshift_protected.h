// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RNG_XORSHIFT_XORSHIFT_PROTECTED_H_
#define SRC_RNG_XORSHIFT_XORSHIFT_PROTECTED_H_

#include "xorshift.h"

typedef struct XorshiftStruct {
  int state_size;
  uint32_t* state;
  XorshiftAbstractMethod impl;
} XorshiftStruct;
typedef struct {
  Xorshift (*New)(int state_size, XorshiftAbstractMethod impl);  //
} XorshiftProtectedMethodStruct;
typedef const XorshiftProtectedMethodStruct* XorshiftProtectedMethod;

extern const XorshiftProtectedMethod _xorshift;

#endif  // SRC_RNG_XORSHIFT_XORSHIFT_PROTECTED_H_
