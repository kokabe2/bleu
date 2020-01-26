// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_IO_DATA_H_
#define V1_IO_DATA_H_

#include <stdint.h>

typedef uintptr_t IoAddress;

typedef struct {
  struct {
    void (*Write)(IoAddress offset, uint8_t data);
    void (*Add)(IoAddress offset, uint8_t data);
    void (*Remove)(IoAddress offset, uint8_t data);
    uint8_t (*Read)(IoAddress offset);
  } b8;
  struct {
    void (*Write)(IoAddress offset, uint16_t data);
    void (*Add)(IoAddress offset, uint16_t data);
    void (*Remove)(IoAddress offset, uint16_t data);
    uint16_t (*Read)(IoAddress offset);
  } b16;
  struct {
    void (*Write)(IoAddress offset, uint32_t data);
    void (*Add)(IoAddress offset, uint32_t data);
    void (*Remove)(IoAddress offset, uint32_t data);
    uint32_t (*Read)(IoAddress offset);
  } b32;
} IoDataMethod;

extern const IoDataMethod ioData;

#endif  // V1_IO_DATA_H_
