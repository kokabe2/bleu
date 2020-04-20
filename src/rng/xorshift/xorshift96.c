// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift96.h"

#include "rng/xorshift/xorshift_protected.h"

static const uint32_t kDefaultSeeds[] = {123456789, 362436069, 521288629};

static uint32_t Generate(Xorshift self) {
  uint32_t t = (self->state[0] ^ (self->state[0] << 3)) ^ (self->state[1] ^ (self->state[1] >> 19)) ^
               (self->state[2] ^ (self->state[2] << 6));
  self->state[0] = self->state[1];
  self->state[1] = self->state[2];
  return self->state[2] = t;
}

static const XorshiftAbstractMethodStruct kConcreteMethod = {
    .Generate = Generate,
};

static Xorshift New(void) {
  Xorshift self = _xorshift->New(sizeof(kDefaultSeeds), &kConcreteMethod);
  xorshift->Give(self, kDefaultSeeds);
  return self;
}

static const Xorshift96MethodStruct kTheMethod = {
    .New = New,
};

const Xorshift96Method xorshift96 = &kTheMethod;
