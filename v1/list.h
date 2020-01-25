// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_LIST_H_
#define V1_LIST_H_

#include "comparer.h"
#include "deleter.h"

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
  void (*SetItemComparer)(List self, const ComparerInterface* ci);
  void (*SetItemDeleter)(List self, const DeleterInterface* di);
} ListInterface;

extern const ListInterface list;

#endif  // V1_LIST_H_
