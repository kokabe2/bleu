// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_STR_H_
#define V1_STR_H_

#include <stdbool.h>

typedef const char* Strings;
typedef struct {
  Strings (*New)(Strings s);
  void (*Delete)(Strings* self);
  int (*Length)(Strings self);
  bool (*Equals)(Strings self, Strings s);
  bool (*Contains)(Strings self, Strings s);
  int (*Index)(Strings self, Strings s);
  int (*LastIndex)(Strings self, Strings s);
  int (*Count)(Strings self, Strings s);
  bool (*HasPrefix)(Strings self, Strings s);
  bool (*HasSuffix)(Strings self, Strings s);
} StringsMethodStruct;
typedef const StringsMethodStruct* StringsMethod;

extern const StringsMethod strings;

#endif  // V1_STR_H_
