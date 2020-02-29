// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "io_data.h"

static void Write8bit(IoAddress offset, IoData data) {
  uint8_t volatile *address = (uint8_t *)offset;
  *address = data;
}

static void Add8bit(IoAddress offset, IoData data) {
  uint8_t volatile *address = (uint8_t *)offset;
  *address |= data;
}

static void Remove8bit(IoAddress offset, IoData data) {
  uint8_t volatile *address = (uint8_t *)offset;
  *address &= ~data;
}

static IoData Read8bit(IoAddress offset) { return *(uint8_t *)offset; }

static const IoInterfaceStruct kImplFor8bit = {
    .Write = Write8bit, .Add = Add8bit, .Remove = Remove8bit, .Read = Read8bit,
};

static void Write16bit(IoAddress offset, IoData data) {
  uint16_t volatile *address = (uint16_t *)offset;
  *address = data;
}

static void Add16bit(IoAddress offset, IoData data) {
  uint16_t volatile *address = (uint16_t *)offset;
  *address |= data;
}

static void Remove16bit(IoAddress offset, IoData data) {
  uint16_t volatile *address = (uint16_t *)offset;
  *address &= ~data;
}

static IoData Read16bit(IoAddress offset) { return *(uint16_t *)offset; }

static const IoInterfaceStruct kImplFor16bit = {
    .Write = Write16bit, .Add = Add16bit, .Remove = Remove16bit, .Read = Read16bit,
};

static void Write32bit(IoAddress offset, IoData data) {
  uint32_t volatile *address = (uint32_t *)offset;
  *address = data;
}

static void Add32bit(IoAddress offset, IoData data) {
  uint32_t volatile *address = (uint32_t *)offset;
  *address |= data;
}

static void Remove32bit(IoAddress offset, IoData data) {
  uint32_t volatile *address = (uint32_t *)offset;
  *address &= ~data;
}

static IoData Read32bit(IoAddress offset) { return *(uint32_t *)offset; }

static const IoInterfaceStruct kImplFor32bit = {
    .Write = Write32bit, .Add = Add32bit, .Remove = Remove32bit, .Read = Read32bit,
};

static const IoDataMethodStruct kTheMethod = {
    .b8 = &kImplFor8bit, .b16 = &kImplFor16bit, .b32 = &kImplFor32bit,
};

const IoDataMethod ioData = &kTheMethod;
