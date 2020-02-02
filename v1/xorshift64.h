// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT64_H_
#define V1_XORSHIFT64_H_

#include "xorshift.h"

typedef struct {
  Xorshift (*New)(void);  // Use xorshift::Delete when delete.
} Xorshift64MethodStruct;
typedef const Xorshift64MethodStruct* Xorshift64Method;

extern const Xorshift64Method xorshift64;

#endif  // V1_XORSHIFT64_H_
