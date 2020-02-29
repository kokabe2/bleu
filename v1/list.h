// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_LIST_H_
#define V1_LIST_H_

#include "comparer_interface.h"
#include "deleter_interface.h"

typedef struct ListStruct* List;
typedef struct {
  List (*New)(void);
  void (*Delete)(List* self);
  int (*Count)(List self);
  void* (*Get)(List self, int index);
  void (*Add)(List self, const void* item);
  void (*Clear)(List self);
  void* (*Find)(List self, const void* match);
  void* (*Pop)(List self, int index);
  void (*SetItemComparer)(List self, ComparerInterface comparer);
  void (*SetItemDeleter)(List self, DeleterInterface di);
} ListMethodStruct;
typedef const ListMethodStruct* ListMethod;

extern const ListMethod list;

#endif  // V1_LIST_H_
