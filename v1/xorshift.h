// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT_H_
#define V1_XORSHIFT_H_

#include <stdint.h>

typedef struct XorshiftStruct* Xorshift;
typedef struct {
  void (*Delete)(Xorshift* self);
  void (*Give)(Xorshift self, const uint32_t* seeds);
  uint32_t (*Generate)(Xorshift self);  // Abstract method
} XorshiftAbstractMethodStruct;
typedef const XorshiftAbstractMethodStruct* XorshiftAbstractMethod;

extern const XorshiftAbstractMethod xorshift;

#endif  // V1_XORSHIFT_H_
