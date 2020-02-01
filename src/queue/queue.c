// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "queue.h"

#include <stdbool.h>
#include <string.h>

#include "heap.h"

typedef struct QueueStruct {
  uint8_t* buffer;
  int capacity;
  int used;
  int head;
  int tail;
} QueueStruct;

static Queue New(int capacity) {
  Queue self = (Queue)heap->New(sizeof(QueueStruct));
  if (!self) return self;
  self->capacity = capacity;
  self->buffer = (uint8_t*)heap->New(capacity);
  if (!self->buffer) heap->Delete((void**)&self);
  return self;
}
static void Delete(Queue* self) {
  if (!self || !*self) return;
  heap->Delete((void**)&(*self)->buffer);
  heap->Delete((void**)self);
}
inline static bool IsBufferFull(Queue self) {
  return self->capacity == self->used;
}
static void Enqueue(Queue self, uint8_t data) {
  if (!self || IsBufferFull(self)) return;
  self->buffer[self->head++] = data;
  if (self->head == self->capacity) self->head = 0;
  self->used++;
}
inline static bool IsBufferEmpty(Queue self) { return self->used == 0; }
static uint8_t Dequeue(Queue self) {
  if (!self || IsBufferEmpty(self)) return 0;
  uint8_t data = self->buffer[self->tail++];
  if (self->tail == self->capacity) self->tail = 0;
  self->used--;
  return data;
}
inline static int available_size(Queue self) {
  return self->capacity - self->used;
}
static void Add(Queue self, int size, const void* data) {
  if (!self || !data) return;
  int copy_size = size <= available_size(self) ? size : available_size(self);
  int size_to_buffer_end = self->capacity - self->head;
  if (copy_size <= size_to_buffer_end) {
    memcpy(&self->buffer[self->head], data, copy_size);
    self->head += copy_size;
  } else {
    memcpy(&self->buffer[self->head], data, size_to_buffer_end);
    memcpy(self->buffer, (void*)((uintptr_t)data + size_to_buffer_end),
           copy_size - size_to_buffer_end);
    self->head = copy_size - size_to_buffer_end;
  }
  self->used += copy_size;
}
static void Pop(Queue self, int size, void* data) {
  if (!self || !data) return;
  int copy_size = size <= self->used ? size : self->used;
  int size_to_buffer_end = self->capacity - self->tail;
  if (copy_size <= size_to_buffer_end) {
    memcpy(data, &self->buffer[self->tail], copy_size);
    self->tail += copy_size;
  } else {
    memcpy(data, &self->buffer[self->tail], size_to_buffer_end);
    memcpy((void*)((uintptr_t)data + size_to_buffer_end), self->buffer,
           copy_size - size_to_buffer_end);
    self->tail = copy_size - size_to_buffer_end;
  }
  self->used -= copy_size;
}
static void Clear(Queue self) {
  if (!self) return;
  self->used = 0;
  self->head = 0;
  self->tail = 0;
}
static int UsedSize(Queue self) { return self ? self->used : 0; }
static int AvailableSize(Queue self) {
  return self ? self->capacity - self->used : 0;
}
static const QueueMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .Enqueue = Enqueue,
    .Dequeue = Dequeue,
    .Add = Add,
    .Pop = Pop,
    .Clear = Clear,
    .UsedSize = UsedSize,
    .AvailableSize = AvailableSize,
};
const QueueMethod queue = &kTheMethod;
