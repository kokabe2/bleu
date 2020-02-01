// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_IO_DATA_H_
#define V1_IO_DATA_H_

#include "io_interface.h"

typedef struct {
  IoInterface b8;
  IoInterface b16;
  IoInterface b32;
} IoDataMethodStruct;
typedef const IoDataMethodStruct* IoDataMethod;

extern const IoDataMethod ioData;

#endif  // V1_IO_DATA_H_
