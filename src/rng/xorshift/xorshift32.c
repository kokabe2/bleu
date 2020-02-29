// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift32.h"

#include "xorshift_protected.h"

static const uint32_t kDefaultSeeds[] = {2463534242};

static uint32_t Generate(Xorshift self) {
  uint32_t *x = self->state;
  *x ^= *x << 13;
  *x ^= *x >> 17;
  *x ^= *x << 5;
  return self->state[0];
}

static const XorshiftAbstractMethodStruct kConcreteMethod = {
    .Generate = Generate,
};

static Xorshift New(void) {
  Xorshift self = _xorshift->New(sizeof(kDefaultSeeds), &kConcreteMethod);
  xorshift->Give(self, kDefaultSeeds);
  return self;
}

static const Xorshift32MethodStruct kTheMethod = {
    .New = New,
};

const Xorshift32Method xorshift32 = &kTheMethod;
