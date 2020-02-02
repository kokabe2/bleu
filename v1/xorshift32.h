// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT32_H_
#define V1_XORSHIFT32_H_

#include "xorshift.h"

typedef struct {
  Xorshift (*New)(void);  // Use xorshift::Delete when delete.
} Xorshift32MethodStruct;
typedef const Xorshift32MethodStruct* Xorshift32Method;

extern const Xorshift32Method xorshift32;

#endif  // V1_XORSHIFT32_H_
