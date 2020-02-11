// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_LIST_LIST_NODE_H_
#define SRC_LIST_LIST_NODE_H_

typedef struct ListNodeStruct* ListNode;
typedef struct {
  ListNode (*New)(const void* item);
  void (*Delete)(ListNode* self);
  void* (*GetItem)(ListNode self);
  void (*SetItem)(ListNode self, const void* item);
  ListNode (*GetNext)(ListNode self);
  void (*SetNext)(ListNode self, ListNode node);
} ListNodeMethodStruct;
typedef const ListNodeMethodStruct* ListNodeMethod;

extern const ListNodeMethod listNode;

#endif  // SRC_LIST_LIST_NODE_H_
