// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "string_builder.h"

#include <stdio.h>
#include <string.h>

#include "heap.h"

typedef struct StringBuilderStruct {
  Strings str;
} StringBuilderStruct;

static StringBuilder New(void) {
  StringBuilder self = heap->New(sizeof(StringBuilderStruct));
  self->str = strings->New("");
  return self;
}

inline static void Delete(StringBuilder *self) { heap->Delete((void **)self); }

static StringBuilderMethod Append(StringBuilder self, Strings s) {
  int new_length = strlen(self->str) + strlen(s) + 1;
  Strings old_str = self->str;
  self->str = heap->New(new_length);
  snprintf((char *)self->str, new_length, "%s%s", old_str, s);
  strings->Delete(&old_str);
  return stringBuilder;
}

static Strings ToString(StringBuilder self) {
  Strings s = self->str;
  Delete(&self);
  return s;
}

static const StringBuilderMethodStruct kTheMethod = {
    .New = New,
    .Append = Append,
    .ToString = ToString,
};

const StringBuilderMethod stringBuilder = &kTheMethod;
