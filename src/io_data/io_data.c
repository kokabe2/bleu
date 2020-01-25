// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "io_data.h"

static void Write8bit(IoAddress offset, uint8_t data) {
  uint8_t volatile *address = (uint8_t *)offset;
  *address = data;
}
static void Add8bit(IoAddress offset, uint8_t data) {
  uint8_t volatile *address = (uint8_t *)offset;
  *address |= data;
}
static void Remove8bit(IoAddress offset, uint8_t data) {
  uint8_t volatile *address = (uint8_t *)offset;
  *address &= ~data;
}
static uint8_t Read8bit(IoAddress offset) { return *(uint8_t *)offset; }
static void Write16bit(IoAddress offset, uint16_t data) {
  uint16_t volatile *address = (uint16_t *)offset;
  *address = data;
}
static void Add16bit(IoAddress offset, uint16_t data) {
  uint16_t volatile *address = (uint16_t *)offset;
  *address |= data;
}
static void Remove16bit(IoAddress offset, uint16_t data) {
  uint16_t volatile *address = (uint16_t *)offset;
  *address &= ~data;
}
static uint16_t Read16bit(IoAddress offset) { return *(uint16_t *)offset; }
static void Write32bit(IoAddress offset, uint32_t data) {
  uint32_t volatile *address = (uint32_t *)offset;
  *address = data;
}
static void Add32bit(IoAddress offset, uint32_t data) {
  uint32_t volatile *address = (uint32_t *)offset;
  *address |= data;
}
static void Remove32bit(IoAddress offset, uint32_t data) {
  uint32_t volatile *address = (uint32_t *)offset;
  *address &= ~data;
}
static uint32_t Read32bit(IoAddress offset) { return *(uint32_t *)offset; }
const IoDataInterface ioData = {
    .b8 =
        {
            .Write = Write8bit,
            .Add = Add8bit,
            .Remove = Remove8bit,
            .Read = Read8bit,
        },
    .b16 =
        {
            .Write = Write16bit,
            .Add = Add16bit,
            .Remove = Remove16bit,
            .Read = Read16bit,
        },
    .b32 =
        {
            .Write = Write32bit,
            .Add = Add32bit,
            .Remove = Remove32bit,
            .Read = Read32bit,
        },
};
