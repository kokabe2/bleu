// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "path.h"

#include <string.h>

#include "heap.h"
#include "list.h"

typedef struct PathStruct {
  Strings origin;
  List directories;
} PathStruct;

static void DeleteItem(void **item) { strings->Delete((Strings *)item); }

static void MakeDirectories(Path self, Strings s) {
  Strings temp = strings->New(s);
  for (char *tp = strtok((char *)temp, "/"); tp != NULL; tp = strtok(NULL, "/"))
    list->Add(self->directories, strings->New(tp));
  strings->Delete(&temp);
}

static Path New(Strings s) {
  Path self = (Path)heap->New(sizeof(PathStruct));
  self->origin = strings->New(s);
  self->directories = list->New();
  list->SetItemDeleter(self->directories, DeleteItem);
  MakeDirectories(self, s);
  return self;
}

static void Delete(Path *self) {
  strings->Delete(&(*self)->origin);
  list->Delete(&(*self)->directories);
  heap->Delete((void **)self);
}

static int Count(Path self) { return list->Count(self->directories); }

static const char *Directory(Path self, int hierarchy) { return list->Get(self->directories, hierarchy); }

static const PathMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .Count = Count,
    .Directory = Directory,
};

const PathMethod path = &kTheMethod;
