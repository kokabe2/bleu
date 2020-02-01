// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_IO_DATA_H_
#define V1_IO_DATA_H_

#include <stdint.h>

typedef uintptr_t IoAddress;
typedef uint32_t IoData;

typedef struct {
  struct {
    void (*Write)(IoAddress offset, IoData data);
    void (*Add)(IoAddress offset, IoData data);
    void (*Remove)(IoAddress offset, IoData data);
    IoData (*Read)(IoAddress offset);
  } b8;
  struct {
    void (*Write)(IoAddress offset, IoData data);
    void (*Add)(IoAddress offset, IoData data);
    void (*Remove)(IoAddress offset, IoData data);
    IoData (*Read)(IoAddress offset);
  } b16;
  struct {
    void (*Write)(IoAddress offset, IoData data);
    void (*Add)(IoAddress offset, IoData data);
    void (*Remove)(IoAddress offset, IoData data);
    IoData (*Read)(IoAddress offset);
  } b32;
} IoDataMethodStruct;
typedef const IoDataMethodStruct* IoDataMethod;

extern const IoDataMethod ioData;

#endif  // V1_IO_DATA_H_
