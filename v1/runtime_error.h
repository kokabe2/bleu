// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_RUNTIME_ERROR_H_
#define V1_RUNTIME_ERROR_H_

#include <stddef.h>

typedef enum {
  kAssertionError = 1,
  kIllegalArgumentError,
  kIndexError,
  kInternalError,
  kIoError,
  kNullPointerError,
  kOsError,
  kOutOfMemoryError,
  kUnsupportedOperationError,
} RuntimeErrors;

typedef struct RuntimeErrorStruct* RuntimeError;
typedef struct {
  RuntimeError (*New)(RuntimeErrors category, const char* message, int parameter);
  void (*Delete)(RuntimeError* self);
  void (*Wrap)(RuntimeError self, const char* message);
  RuntimeErrors (*Category)(RuntimeError self);
  const char* (*Message)(RuntimeError self);
  int (*Parameter)(RuntimeError self);
  const char* (*Cause)(RuntimeError self);
} RuntimeErrorMethodStruct;
typedef const RuntimeErrorMethodStruct* RuntimeErrorMethod;

extern const RuntimeErrorMethod runtimeError;

#endif  // V1_RUNTIME_ERROR_H_
