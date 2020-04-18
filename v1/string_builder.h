// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_STRING_BUILDER_H_
#define V1_STRING_BUILDER_H_

#include "str.h"

typedef struct StringBuilderStruct* StringBuilder;
typedef const struct StringBuilderMethodStruct* StringBuilderMethod;
typedef struct StringBuilderMethodStruct {
  StringBuilder (*New)(void);
  StringBuilderMethod (*Append)(StringBuilder self, Strings s);
  Strings (*ToString)(StringBuilder self);  // The StringBuilder instance will be automatically destroyed.
} StringBuilderMethodStruct;

extern const StringBuilderMethod stringBuilder;

#endif  // V1_STRING_BUILDER_H_
