// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_IO_INTERFACE_H_
#define V1_IO_INTERFACE_H_

#include <stdint.h>

typedef uintptr_t IoAddress;
typedef uint32_t IoData;

typedef struct {
  void (*Write)(IoAddress offset, IoData data);
  void (*Add)(IoAddress offset, IoData data);
  void (*Remove)(IoAddress offset, IoData data);
  IoData (*Read)(IoAddress offset);
} IoInterfaceStruct;
typedef const IoInterfaceStruct* IoInterface;

#endif  // V1_IO_INTERFACE_H_
