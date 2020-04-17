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
  Strings (*Directory)(Path self, int hierarchy);
} PathMethodStruct;
typedef const PathMethodStruct* PathMethod;

extern const PathMethod path;

#endif  // V1_PATH_H_
