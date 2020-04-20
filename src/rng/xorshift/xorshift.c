// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift.h"

#include <stdbool.h>
#include <string.h>

#include "heap.h"
#include "rng/xorshift/xorshift_protected.h"

static Xorshift New(int state_size, XorshiftAbstractMethod impl) {
  Xorshift self = (Xorshift)heap->New(sizeof(XorshiftStruct));
  self->state_size = state_size;
  self->state = (uint32_t*)heap->New(state_size);
  self->impl = impl;
  return self;
}

static const XorshiftProtectedMethodStruct kProtectedMethod = {
    .New = New,
};

const XorshiftProtectedMethod _xorshift = &kProtectedMethod;

static void Delete(Xorshift* self) {
  heap->Delete((void**)&(*self)->state);
  heap->Delete((void**)self);
}

static bool IsNotAllZero(Xorshift self, const uint32_t* seeds) {
  for (int i = 0; i < self->state_size / sizeof(uint32_t); ++i)
    if (seeds[i] != 0) return true;
  return false;
}

static void Give(Xorshift self, const uint32_t* seeds) {
  if (IsNotAllZero(self, seeds)) memcpy(self->state, seeds, self->state_size);
}

static uint32_t Generate(Xorshift self) { return self->impl->Generate(self); }

static const XorshiftAbstractMethodStruct kTheMethod = {
    .Delete = Delete,
    .Give = Give,
    .Generate = Generate,
};

const XorshiftAbstractMethod xorshift = &kTheMethod;
