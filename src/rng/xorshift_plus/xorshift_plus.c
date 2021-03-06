// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift_plus.h"

#include <stdbool.h>
#include <string.h>

#include "heap.h"
#include "rng/xorshift_plus/xorshift_plus_protected.h"

static XorshiftPlus New(int state_size, XorshiftPlusAbstractMethod impl) {
  XorshiftPlus self = (XorshiftPlus)heap->New(sizeof(XorshiftPlusStruct));
  self->state_size = state_size;
  self->state = (uint64_t*)heap->New(state_size);
  self->impl = impl;
  return self;
}

static const XorshiftPlusProtectedMethodStruct kProtectedMethod = {
    .New = New,
};

const XorshiftPlusProtectedMethod _xorshiftPlus = &kProtectedMethod;

static void Delete(XorshiftPlus* self) {
  heap->Delete((void**)&(*self)->state);
  heap->Delete((void**)self);
}

static bool IsNotAllZero(XorshiftPlus self, const uint64_t* seeds) {
  for (int i = 0; i < self->state_size / sizeof(uint64_t); ++i)
    if (seeds[i] != 0) return true;
  return false;
}

static void Give(XorshiftPlus self, const uint64_t* seeds) {
  if (IsNotAllZero(self, seeds)) memcpy(self->state, seeds, self->state_size);
}

static uint64_t Generate(XorshiftPlus self) { return self->impl->Generate(self); }

static const XorshiftPlusAbstractMethodStruct kTheMethod = {
    .Delete = Delete,
    .Give = Give,
    .Generate = Generate,
};

const XorshiftPlusAbstractMethod xorshiftPlus = &kTheMethod;
