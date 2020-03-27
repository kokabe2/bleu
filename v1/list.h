// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_LIST_H_
#define V1_LIST_H_

typedef int (*CompareDelegate)(
    const void* x,
    const void* y);  // Returns less than 0 if x is less than y, 0 if x equals y, greater than 0 if x is greater than y.
typedef void (*DeleteDelegate)(void** x);  // x shall be null if deleted successfully.
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
  void (*SetItemComparer)(List self, CompareDelegate delegate);
  void (*SetItemDeleter)(List self, DeleteDelegate delegate);
} ListMethodStruct;
typedef const ListMethodStruct* ListMethod;

extern const ListMethod list;

#endif  // V1_LIST_H_
