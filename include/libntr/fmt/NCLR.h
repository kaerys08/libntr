#ifndef NCLR_H
#define NCLR_H

#include <nds.h>

#include <stdio.h>
#include <string.h>

#include "fmt/Common.h"
#include "fs/binaryFile.h"
#include "gfx/palette.h"

typedef struct Palette {
  uint32_t magic;
  uint32_t palette_size;
  uint32_t bit_depht;
  bool extended_palette;
  uint8_t padding[3];
  uint32_t unk;
  uint32_t colors_by_palette;
} Palette;

typedef union Data {
  u16 data;
} Data;

typedef struct NCLR {
  Palette *palette;

  Data *data;
} NCLR;

static inline void getNCLRsize(NCLR nclr) {
  iprintf("NCLR size: %i", sizeof(nclr));
}

#endif // #ifndef NCLR_H
