// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "list.h"

#include <stdbool.h>
#include <stddef.h>

#include "heap.h"
#include "list_node.h"

typedef struct ListStruct {
  ListNode head;
  ListNode tail;
  int count;
  ComparerInterface ci;
  DeleterInterface di;
} ListStruct;

static List New(void) { return (List)heap.New(sizeof(ListStruct)); }
inline static bool IsEmpty(List self) { return self->count == 0; }
inline static ListNode GetFirstNode(List self) { return self->head; }
inline static void SetFirstNode(List self, ListNode ln) { self->head = ln; }
inline static ListNode PopFirstNode(List self) {
  ListNode ln = GetFirstNode(self);
  SetFirstNode(self, listNode.GetNext(ln));
  self->count--;
  return ln;
}
inline static void DeleteItemIfNeeded(List self, ListNode ln) {
  if (!self->di.Delete) return;
  void* item = listNode.GetItem(ln);
  self->di.Delete(&item);
}
static void DeleteAllNodes(List self) {
  while (!IsEmpty(self)) {
    ListNode ln = PopFirstNode(self);
    DeleteItemIfNeeded(self, ln);
    listNode.Delete(&ln);
  }
  self->tail = NULL;
}
static void Delete(List* self) {
  if (!self || !*self) return;
  DeleteAllNodes(*self);
  heap.Delete((void**)self);
}
static int Count(List self) { return self ? self->count : 0; }
static ListNode GetNode(List self, int index) {
  ListNode ln = GetFirstNode(self);
  for (int i = 0; i < index; ++i) ln = listNode.GetNext(ln);
  return ln;
}
static void* Get(List self, int index) {
  ListNode ln =
      self && index >= 0 && index < self->count ? GetNode(self, index) : NULL;
  return listNode.GetItem(ln);
}
inline static void SetLastNode(List self, ListNode ln) {
  listNode.SetNext(self->tail, ln);
}
inline static void AddNode(List self, ListNode ln) {
  if (IsEmpty(self))
    SetFirstNode(self, ln);
  else
    SetLastNode(self, ln);

  self->tail = ln;
  self->count++;
}
static void Add(List self, const void* item) {
  ListNode ln = self ? listNode.New(item) : NULL;
  if (ln) AddNode(self, ln);
}
static void Clear(List self) {
  if (self) DeleteAllNodes(self);
}
inline static bool Equals(List self, const void* item, const void* match) {
  return self->ci.Compare(item, match) == 0;
}
static void* Find(List self, const void* match) {
  if (!self || !self->ci.Compare) return NULL;

  for (ListNode ln = GetFirstNode(self); ln; ln = listNode.GetNext(ln))
    if (Equals(self, listNode.GetItem(ln), match)) return listNode.GetItem(ln);
  return NULL;
}
inline static bool IsFirstNode(int index) { return index == 0; }
inline static ListNode PopNode(List self, int index) {
  if (IsFirstNode(index)) return PopFirstNode(self);

  ListNode pre = GetNode(self, index - 1);
  ListNode ln = listNode.GetNext(pre);
  ListNode next = listNode.GetNext(ln);
  listNode.SetNext(pre, next);

  if (!next) self->tail = pre;
  self->count--;
  return ln;
}
inline static void* PopItem(ListNode ln) {
  void* item = listNode.GetItem(ln);
  listNode.Delete(&ln);
  return item;
}
static void* Pop(List self, int index) {
  ListNode ln =
      self && index >= 0 && index < self->count ? PopNode(self, index) : NULL;
  return PopItem(ln);
}
static void SetItemComparer(List self, const ComparerInterface* ci) {
  if (self && ci) self->ci = *ci;
}
static void SetItemDeleter(List self, const DeleterInterface* di) {
  if (self && di) self->di = *di;
}
const ListInterface list = {
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
