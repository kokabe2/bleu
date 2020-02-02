// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT96_H_
#define V1_XORSHIFT96_H_

#include "xorshift.h"

typedef struct {
  Xorshift (*New)(void);  // Use xorshift::Delete when delete.
} Xorshift96MethodStruct;
typedef const Xorshift96MethodStruct* Xorshift96Method;

extern const Xorshift96Method xorshift96;

#endif  // V1_XORSHIFT96_H_
