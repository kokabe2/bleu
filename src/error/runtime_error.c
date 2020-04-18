// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "runtime_error.h"

#include "heap.h"
#include "string_builder.h"

typedef struct RuntimeErrorStruct {
  RuntimeErrors category;
  Strings cause;
  int parameter;
  Strings message;
} RuntimeErrorStruct;

static RuntimeError New(RuntimeErrors category, const char *message, int parameter) {
  RuntimeError self = (RuntimeError)heap->New(sizeof(RuntimeErrorStruct));
  self->category = category;
  self->cause = strings->New(message);
  self->parameter = parameter;
  self->message = strings->New(message);
  return self;
}

static void Delete(RuntimeError *self) {
  strings->Delete(&(*self)->cause);
  strings->Delete(&(*self)->message);
  heap->Delete((void **)self);
}

static void Wrap(RuntimeError self, const char *message) {
  StringBuilder sb = stringBuilder->New();
  stringBuilder->Append(sb, message)->Append(sb, ": ")->Append(sb, self->message);
  strings->Delete(&self->message);
  self->message = stringBuilder->ToString(sb);
}

static RuntimeErrors Category(RuntimeError self) { return self->category; }

static const char *Message(RuntimeError self) { return self->message; }

static int Parameter(RuntimeError self) { return self->parameter; }

static const char *Cause(RuntimeError self) { return self->cause; }

static const RuntimeErrorMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .Wrap = Wrap,
    .Category = Category,
    .Message = Message,
    .Parameter = Parameter,
    .Cause = Cause,
};

const RuntimeErrorMethod runtimeError = &kTheMethod;
