// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "list_node.h"

#include <stddef.h>

#include "heap.h"

typedef struct ListNodeStruct {
  void* item;
  ListNode next;
} ListNodeStruct;

static ListNode New(const void* item) {
  ListNode self = (ListNode)heap->New(sizeof(ListNodeStruct));
  if (self) self->item = (void*)item;
  return self;
}

static void Delete(ListNode* self) {
  if (self) heap->Delete((void**)self);
}

static void* GetItem(ListNode self) { return self ? self->item : NULL; }

static void SetItem(ListNode self, const void* item) {
  if (self) self->item = (void*)item;
}

static ListNode GetNext(ListNode self) { return self ? self->next : NULL; }

static void SetNext(ListNode self, ListNode next) {
  if (self) self->next = next;
}

static const ListNodeMethodStruct kTheMethod = {
    .New = New, .Delete = Delete, .GetItem = GetItem, .SetItem = SetItem, .GetNext = GetNext, .SetNext = SetNext,
};

const ListNodeMethod listNode = &kTheMethod;
