// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "list/list_node.h"

#include "heap.h"

typedef struct ListNodeStruct {
  void* item;
  ListNode next;
} ListNodeStruct;

static ListNode New(const void* item) {
  ListNode self = (ListNode)heap->New(sizeof(ListNodeStruct));
  self->item = (void*)item;
  return self;
}

static void Delete(ListNode* self) { heap->Delete((void**)self); }

static void* GetItem(ListNode self) { return self->item; }

static void SetItem(ListNode self, const void* item) { self->item = (void*)item; }

static ListNode GetNext(ListNode self) { return self->next; }

static void SetNext(ListNode self, ListNode next) { self->next = next; }

static const ListNodeMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .GetItem = GetItem,
    .SetItem = SetItem,
    .GetNext = GetNext,
    .SetNext = SetNext,
};

const ListNodeMethod listNode = &kTheMethod;
