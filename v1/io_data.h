// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_IO_DATA_H_
#define V1_IO_DATA_H_

#include "io_reader_writer.h"

typedef struct {
  IoReaderWriter b8;
  IoReaderWriter b16;
  IoReaderWriter b32;
} IoDataMethodStruct;
typedef const IoDataMethodStruct* IoDataMethod;

extern const IoDataMethod ioData;

#endif  // V1_IO_DATA_H_
