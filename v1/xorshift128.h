// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT128_H_
#define V1_XORSHIFT128_H_

#include "xorshift.h"

typedef struct {
  Xorshift (*New)(void);  // Use xorshift::Delete when delete.
} Xorshift128MethodStruct;
typedef const Xorshift128MethodStruct* Xorshift128Method;

extern const Xorshift128Method xorshift128;

#endif  // V1_XORSHIFT128_H_
