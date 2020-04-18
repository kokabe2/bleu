// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_PATH_H_
#define V1_PATH_H_

#include "str.h"

typedef struct PathStruct* Path;
typedef struct {
  Path (*New)(Strings s);
  void (*Delete)(Path* self);
  int (*Count)(Path self);
  const char* (*Directory)(Path self, int index);
} PathMethodStruct;
typedef const PathMethodStruct* PathMethod;

extern const PathMethod path;

#endif  // V1_PATH_H_
