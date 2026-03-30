#ifndef _NCLR_INCLUDE
#define _NCLR_INCLUDE

#include <cstdint>
#include <nds.h>

#include <stdio.h>
#include <string.h>

#include "libntr/fmt/Common.h"
#include "libntr/fmt/vram.h"
#include "libntr/fs/binaryFile.h"
#include "libntr/gfx/palette.h"

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
  Color color;
} Data;

typedef struct NCLR {
  Palette *palette;

  Data *data;
} NCLR;

static inline void getNCLRsize(NCLR nclr) {
  iprintf("NCLR size: %i", sizeof(nclr));
}

#endif // #ifndef _NCLR_INCLUDE
