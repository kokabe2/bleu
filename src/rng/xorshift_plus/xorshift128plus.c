// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift128plus.h"

#include "xorshift_plus_protected.h"

static const uint64_t kDefaultSeeds[] = {3141592653589793, 2718281828459045};

static uint64_t Generate(XorshiftPlus self) {
  uint64_t s1 = self->state[0];
  uint64_t s0 = self->state[1];
  self->state[0] = s0;
  s1 ^= s1 << 23;
  s1 ^= s1 >> 17;
  s1 ^= s0;
  s1 ^= s0 >> 26;
  self->state[1] = s1;
  return self->state[0] + self->state[1];
}

static const XorshiftPlusAbstractMethodStruct kConcreteMethod = {
    .Generate = Generate,
};

static XorshiftPlus New(void) {
  XorshiftPlus self = _xorshiftPlus->New(sizeof(kDefaultSeeds), &kConcreteMethod);
  xorshiftPlus->Give(self, kDefaultSeeds);
  return self;
}

static const XorshiftPlus128MethodStruct kTheMethod = {
    .New = New,
};

const XorshiftPlus128Method xorshift128plus = &kTheMethod;
