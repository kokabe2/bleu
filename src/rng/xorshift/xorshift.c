// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift.h"

#include <stdbool.h>
#include <string.h>

#include "heap.h"
#include "xorshift_protected.h"

static Xorshift New(int state_size, XorshiftAbstractMethod impl) {
  Xorshift self = (Xorshift)heap->New(sizeof(XorshiftStruct));
  if (!self) return self;
  self->state_size = state_size;
  self->impl = impl;
  self->state = (uint32_t*)heap->New(state_size);
  if (!self->state) heap->Delete((void**)&self);
  return self;
}
static const XorshiftProtectedMethodStruct kProtectedMethod = {
    .New = New,
};
const XorshiftProtectedMethod _xorshift = &kProtectedMethod;

static void Delete(Xorshift* self) {
  if (!self || !*self) return;
  heap->Delete((void**)&(*self)->state);
  heap->Delete((void**)self);
}
static bool IsAllZero(Xorshift self, const uint32_t* seeds) {
  for (int i = 0; i < self->state_size / sizeof(uint32_t); ++i)
    if (seeds[i]) return false;
  return true;
}
static void Give(Xorshift self, const uint32_t* seeds) {
  if (self && seeds && !IsAllZero(self, seeds))
    memcpy(self->state, seeds, self->state_size);
}
static uint32_t Generate(Xorshift self) {
  return self ? self->impl->Generate(self) : 0;
}
static const XorshiftAbstractMethodStruct kTheMethod = {
    .Delete = Delete, .Give = Give, .Generate = Generate,
};
const XorshiftAbstractMethod xorshift = &kTheMethod;
