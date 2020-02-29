// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_COMPARER_INTERFACE_H_
#define V1_COMPARER_INTERFACE_H_

typedef struct {
  int (*Compare)(const void* x, const void* y);  // Returns less than 0 if x is less than y, 0 if x equals y, greater
                                                 // than 0 if x is greater than y.
} ComparerInterfaceStruct;
typedef const ComparerInterfaceStruct* ComparerInterface;

#endif  // V1_COMPARER_INTERFACE_H_
