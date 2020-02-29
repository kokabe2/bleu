// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "list.h"

#include <stdbool.h>
#include <stddef.h>

#include "heap.h"
#include "list_node.h"
#include "null_comparer.h"
#include "null_deleter.h"

typedef struct ListStruct {
  ListNode head;
  ListNode tail;
  int count;
  ComparerInterfaceStruct comparer;
  DeleterInterfaceStruct deleter;
} ListStruct;

inline static void SetItemComparer(List self, ComparerInterface comparer) { self->comparer = *comparer; }

inline static void SetItemDeleter(List self, DeleterInterface deleter) { self->deleter = *deleter; }

static List New(void) {
  List self = (List)heap->New(sizeof(ListStruct));
  SetItemComparer(self, NullComparer);
  SetItemDeleter(self, NullDeleter);
  return self;
}

inline static ListNode GetFirstNode(List self) { return self->head; }

inline static void SetFirstNode(List self, ListNode ln) { self->head = ln; }

inline static ListNode PopFirstNode(List self) {
  ListNode ln = GetFirstNode(self);
  SetFirstNode(self, listNode->GetNext(ln));
  return ln;
}

inline static void DeleteNode(List self, ListNode ln) {
  void* item = listNode->GetItem(ln);
  self->deleter.Delete(&item);
  listNode->Delete(&ln);
}

static void DeleteAllNodes(List self) {
  for (; self->count > 0; --self->count) {
    ListNode ln = PopFirstNode(self);
    DeleteNode(self, ln);
  }
}

static void Delete(List* self) {
  DeleteAllNodes(*self);
  heap->Delete((void**)self);
}

static int Count(List self) { return self->count; }

inline static bool Validate(List self, int index) { return index < self->count; }

static ListNode GetNode(List self, int index) {
  ListNode ln = GetFirstNode(self);
  for (int i = 0; i < index; ++i) ln = listNode->GetNext(ln);
  return ln;
}

static void* Get(List self, int index) {
  if (Validate(self, index)) {
    ListNode ln = GetNode(self, index);
    return listNode->GetItem(ln);
  } else {
    return NULL;
  }
}

inline static bool IsEmpty(List self) { return self->count == 0; }

inline static void AddToLastNode(List self, ListNode ln) { listNode->SetNext(self->tail, ln); }

inline static void SetLastNode(List self, ListNode ln) { self->tail = ln; }

inline static void AddNode(List self, ListNode ln) {
  if (IsEmpty(self))
    SetFirstNode(self, ln);
  else
    AddToLastNode(self, ln);

  SetLastNode(self, ln);
}

static void Add(List self, const void* item) {
  ListNode ln = listNode->New(item);
  AddNode(self, ln);
  ++self->count;
}

static void Clear(List self) { DeleteAllNodes(self); }

inline static bool Equals(List self, const void* item, const void* match) {
  return self->comparer.Compare(item, match) == 0;
}

static void* Find(List self, const void* match) {
  for (ListNode ln = GetFirstNode(self); ln; ln = listNode->GetNext(ln))
    if (Equals(self, listNode->GetItem(ln), match)) return listNode->GetItem(ln);
  return NULL;
}

inline static bool IsFirstNode(int index) { return index == 0; }

inline static ListNode PopNodeOtherThanFirst(List self, int index) {
  ListNode pre = GetNode(self, index - 1);
  ListNode ln = listNode->GetNext(pre);
  ListNode next = listNode->GetNext(ln);

  listNode->SetNext(pre, next);
  if (next == NULL) SetLastNode(self, pre);

  return ln;
}

inline static ListNode PopNode(List self, int index) {
  if (IsFirstNode(index))
    return PopFirstNode(self);
  else
    return PopNodeOtherThanFirst(self, index);
}

inline static void* PopItem(ListNode ln) {
  void* item = listNode->GetItem(ln);
  listNode->Delete(&ln);
  return item;
}

static void* Pop(List self, int index) {
  if (Validate(self, index)) {
    ListNode ln = PopNode(self, index);
    --self->count;
    return PopItem(ln);
  } else {
    return NULL;
  }
}

static const ListMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .Count = Count,
    .Get = Get,
    .Add = Add,
    .Clear = Clear,
    .Find = Find,
    .Pop = Pop,
    .SetItemComparer = SetItemComparer,
    .SetItemDeleter = SetItemDeleter,
};

const ListMethod list = &kTheMethod;
