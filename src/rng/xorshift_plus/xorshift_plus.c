// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "xorshift_plus.h"

#include <stdbool.h>
#include <string.h>

#include "heap.h"
#include "xorshift_plus_private.h"

static XorshiftPlus New(int state_size, XorshiftPlusAbstractMethod impl) {
  XorshiftPlus self = (XorshiftPlus)heap->New(sizeof(XorshiftPlusStruct));
  if (!self) return NULL;
  self->state_size = state_size;
  self->impl = impl;
  self->state = (uint64_t*)heap->New(state_size);
  if (!self->state) heap->Delete((void**)&self);
  return self;
}
static const XorshiftPlusPrivateMethodStruct kPrivateMethod = {
    .New = New,
};
const XorshiftPlusPrivateMethod _xorshiftPlus = &kPrivateMethod;

static void Delete(XorshiftPlus* self) {
  if (!self || !*self) return;
  heap->Delete((void**)&(*self)->state);
  heap->Delete((void**)self);
}
static bool IsAllZero(XorshiftPlus self, const uint64_t* seeds) {
  for (int i = 0; i < self->state_size / sizeof(uint64_t); ++i)
    if (seeds[i]) return false;
  return true;
}
static void Give(XorshiftPlus self, const uint64_t* seeds) {
  if (self && seeds && !IsAllZero(self, seeds))
    memcpy(self->state, seeds, self->state_size);
}
static uint64_t Generate(XorshiftPlus self) {
  return self ? self->impl->Generate(self) : 0;
}
static const XorshiftPlusAbstractMethodStruct kTheMethod = {
    .Delete = Delete, .Give = Give, .Generate = Generate,
};
const XorshiftPlusAbstractMethod xorshiftPlus = &kTheMethod;
