// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RNG_XORSHIFT_PLUS_XORSHIFT_PLUS_PROTECTED_H_
#define SRC_RNG_XORSHIFT_PLUS_XORSHIFT_PLUS_PROTECTED_H_

#include "xorshift_plus.h"

typedef struct XorshiftPlusStruct {
  int state_size;
  uint64_t* state;
  XorshiftPlusAbstractMethod impl;
} XorshiftPlusStruct;
typedef struct {
  XorshiftPlus (*New)(int state_size, XorshiftPlusAbstractMethod impl);
} XorshiftPlusProtectedMethodStruct;
typedef const XorshiftPlusProtectedMethodStruct* XorshiftPlusProtectedMethod;

extern const XorshiftPlusProtectedMethod _xorshiftPlus;

#endif  // SRC_RNG_XORSHIFT_PLUS_XORSHIFT_PLUS_PROTECTED_H_
