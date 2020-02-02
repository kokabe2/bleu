// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RNG_XORSHIFT_PLUS_XORSHIFT_PLUS_PRIVATE_H_
#define SRC_RNG_XORSHIFT_PLUS_XORSHIFT_PLUS_PRIVATE_H_

#include "xorshift_plus.h"

typedef struct XorshiftPlusStruct {
  int state_size;
  uint64_t* state;
  XorshiftPlusAbstractMethod impl;
} XorshiftPlusStruct;

typedef struct {
  XorshiftPlus (*New)(int state_size, XorshiftPlusAbstractMethod impl);
} XorshiftPlusPrivateMethodStruct;
typedef const XorshiftPlusPrivateMethodStruct* XorshiftPlusPrivateMethod;

extern const XorshiftPlusPrivateMethod _xorshiftPlus;

#endif  // SRC_RNG_XORSHIFT_PLUS_XORSHIFT_PLUS_PRIVATE_H_
