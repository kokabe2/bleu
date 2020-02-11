// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_QUEUE_H_
#define V1_QUEUE_H_

#include <stdint.h>

typedef struct QueueStruct* Queue;
typedef struct {
  Queue (*New)(int capacity);
  void (*Delete)(Queue* self);
  void (*Enqueue)(Queue self, uint8_t data);
  uint8_t (*Dequeue)(Queue self);
  void (*Add)(Queue self, int size, const void* data);
  void (*Pop)(Queue self, int size, void* data);
  void (*Clear)(Queue self);
  int (*UsedSize)(Queue self);
  int (*AvailableSize)(Queue self);
} QueueMethodStruct;
typedef const QueueMethodStruct* QueueMethod;

extern const QueueMethod queue;

#endif  // V1_QUEUE_H_
