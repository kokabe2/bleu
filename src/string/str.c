// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "str.h"

#include <string.h>

#include "heap.h"

static Strings New(Strings s) {
  Strings self = (Strings)heap->New(strlen(s) + 1);
  return strncpy((char *)self, s, strlen(s));
}

static void Delete(Strings *self) { heap->Delete((void **)self); }

static int Length(Strings self) { return strlen(self); }

static bool Equals(Strings self, Strings s) {
  int len = strlen(self);
  return len == strlen(s) && strncmp(self, s, len) == 0;
}

static bool Contains(Strings self, Strings s) { return strstr(self, s) != NULL; }

static int Index(Strings self, Strings s) {
  char *p = strstr(self, s);
  return p != NULL ? p - self : -1;
}

static int LastIndex(Strings self, Strings s) {
  int index = 0;
  for (int i = Index(self, s); i != -1; index += i + 1, i = Index(&self[index], s)) continue;
  return index - 1;
}

static int Count(Strings self, Strings s) {
  int index = 0;
  int count = 0;
  for (int i = Index(self, s); i != -1; index += i + 1, i = Index(&self[index], s), ++count) continue;
  return count;
}

static bool HasPrefix(Strings self, Strings s) { return strstr(self, s) == self; }

static bool HasSuffix(Strings self, Strings s) { return strncmp(&self[strlen(self) - strlen(s)], s, strlen(s)) == 0; }

static const StringsMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .Length = Length,
    .Equals = Equals,
    .Contains = Contains,
    .Index = Index,
    .LastIndex = LastIndex,
    .Count = Count,
    .HasPrefix = HasPrefix,
    .HasSuffix = HasSuffix,
};

const StringsMethod strings = &kTheMethod;
