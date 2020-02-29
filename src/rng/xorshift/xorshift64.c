// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift64.h"

#include "xorshift_protected.h"

static const uint32_t kDefaultSeeds[] = {123456789, 362436069};

static uint32_t Generate(Xorshift self) {
  uint64_t *x = (uint64_t *)self->state;
  *x ^= *x << 13;
  *x ^= *x >> 7;
  *x ^= *x << 17;
  return self->state[1];
}

static const XorshiftAbstractMethodStruct kConcreteMethod = {
    .Generate = Generate,
};

static Xorshift New(void) {
  Xorshift self = _xorshift->New(sizeof(kDefaultSeeds), &kConcreteMethod);
  xorshift->Give(self, kDefaultSeeds);
  return self;
}

static const Xorshift64MethodStruct kTheMethod = {
    .New = New,
};

const Xorshift64Method xorshift64 = &kTheMethod;
