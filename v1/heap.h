// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_HEAP_H_
#define V1_HEAP_H_

#define Delete(x) Del((void**) & x)

typedef struct {
  void* (*New)(int size);
  void (*Del)(void** memory);
  void (*SetUsageWarning)(int size, void (*func)(int usage));
} HeapInterface;

extern const HeapInterface heap;

#endif  // V1_HEAP_H_
