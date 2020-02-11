// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_XORSHIFT_PLUS_H_
#define V1_XORSHIFT_PLUS_H_

#include <stdint.h>

typedef struct XorshiftPlusStruct* XorshiftPlus;
typedef struct {
  void (*Delete)(XorshiftPlus* self);
  void (*Give)(XorshiftPlus self, const uint64_t* seeds);
  uint64_t (*Generate)(XorshiftPlus self);  // Abstract method
} XorshiftPlusAbstractMethodStruct;
typedef const XorshiftPlusAbstractMethodStruct* XorshiftPlusAbstractMethod;

extern const XorshiftPlusAbstractMethod xorshiftPlus;

#endif  // V1_XORSHIFT_PLUS_H_
