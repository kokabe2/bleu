// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_DELETER_INTERFACE_H_
#define V1_DELETER_INTERFACE_H_

typedef struct {
  void (*Delete)(void** x);  // x shall be null if deleted successfully.
} DeleterInterface;

#endif  // V1_DELETER_INTERFACE_H_
