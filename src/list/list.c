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
  ComparerInterfaceStruct cis;
  DeleterInterfaceStruct dis;
} ListStruct;

inline static void SetItemComparer(List self, ComparerInterface cis) { self->cis = *cis; }

inline static void SetItemDeleter(List self, DeleterInterface dis) { self->dis = *dis; }

static List New(void) {
  List self = (List)heap->New(sizeof(ListStruct));
  SetItemComparer(self, NullComparer);
  SetItemDeleter(self, NullDeleter);
  return self;
}

inline static bool IsEmpty(List self) { return self->count == 0; }

inline static ListNode GetFirstNode(List self) { return self->head; }

inline static void SetFirstNode(List self, ListNode ln) { self->head = ln; }

inline static ListNode PopFirstNode(List self) {
  ListNode ln = GetFirstNode(self);
  SetFirstNode(self, listNode->GetNext(ln));
  self->count--;
  return ln;
}

inline static void DeleteNode(List self, ListNode ln) {
  void* item = listNode->GetItem(ln);
  self->dis.Delete(&item);
  listNode->Delete(&ln);
}

static void DeleteAllNodes(List self) {
  while (!IsEmpty(self)) {
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
  ListNode ln = Validate(self, index) ? GetNode(self, index) : NULL;
  return ln ? listNode->GetItem(ln) : NULL;
}

inline static void AddToLastNode(List self, ListNode ln) { listNode->SetNext(self->tail, ln); }

inline static void SetLastNode(List self, ListNode ln) { self->tail = ln; }

inline static void AddNode(List self, ListNode ln) {
  if (IsEmpty(self))
    SetFirstNode(self, ln);
  else
    AddToLastNode(self, ln);

  SetLastNode(self, ln);
  self->count++;
}

static void Add(List self, const void* item) {
  ListNode ln = listNode->New(item);
  AddNode(self, ln);
}

static void Clear(List self) { DeleteAllNodes(self); }

inline static bool Equals(List self, const void* item, const void* match) {
  return self->cis.Compare(item, match) == 0;
}

static void* Find(List self, const void* match) {
  for (ListNode ln = GetFirstNode(self); ln; ln = listNode->GetNext(ln))
    if (Equals(self, listNode->GetItem(ln), match)) return listNode->GetItem(ln);
  return NULL;
}

inline static bool IsFirstNode(int index) { return index == 0; }

inline static ListNode PopNode(List self, int index) {
  if (IsFirstNode(index)) return PopFirstNode(self);

  ListNode pre = GetNode(self, index - 1);
  ListNode ln = listNode->GetNext(pre);
  ListNode next = listNode->GetNext(ln);
  listNode->SetNext(pre, next);

  if (!next) SetLastNode(self, pre);
  self->count--;
  return ln;
}

inline static void* PopItem(ListNode ln) {
  void* item = listNode->GetItem(ln);
  listNode->Delete(&ln);
  return item;
}

static void* Pop(List self, int index) {
  if (Validate(self, index)) {
    ListNode ln = PopNode(self, index);
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
