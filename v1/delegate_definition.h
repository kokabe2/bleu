// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_DELEGATE_DEFINITION_H_
#define V1_DELEGATE_DEFINITION_H_

typedef int (*CompareDelegate)(
    const void* x,
    const void* y);  // Returns less than 0 if x is less than y, 0 if x equals y, greater than 0 if x is greater than y.
typedef void (*DeleteDelegate)(void** x);  // x shall be null if deleted successfully.

#endif  // V1_DELEGATE_DEFINITION_H_
