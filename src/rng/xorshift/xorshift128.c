// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift128.h"

#include "rng/xorshift/xorshift_protected.h"

static const uint32_t kDefaultSeeds[] = {123456789, 362436069, 521288629, 88675123};

static uint32_t Generate(Xorshift self) {
  uint32_t t = self->state[3];
  uint32_t s = self->state[0];
  self->state[3] = self->state[2];
  self->state[2] = self->state[1];
  self->state[1] = self->state[0];
  t ^= t << 11;
  t ^= t >> 8;
  return self->state[0] = t ^ s ^ (s >> 19);
}

static const XorshiftAbstractMethodStruct kConcreteMethod = {
    .Generate = Generate,
};

static Xorshift New(void) {
  Xorshift self = _xorshift->New(sizeof(kDefaultSeeds), &kConcreteMethod);
  xorshift->Give(self, kDefaultSeeds);
  return self;
}

static const Xorshift128MethodStruct kTheMethod = {
    .New = New,
};

const Xorshift128Method xorshift128 = &kTheMethod;
