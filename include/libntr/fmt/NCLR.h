#ifndef _NCLR_INCLUDE
#define _NCLR_INCLUDE

#include <nds.h>

#include <stdio.h>
#include <string.h>

#include "libntr/fmt/Common.h"
#include "libntr/fmt/vram.h"
#include "libntr/fs/binaryFile.h"
#include "libntr/gfx/palette.h"

typedef struct Palette{
    u32 magic;
    u32 palette_size;
    u32 bit_depht;
    bool  extended_palette;
    u8 padding[3];
    u32 unk;
    u32 colors_by_palette;
}Palette;

typedef union Data{
    u16 data;
    Color color;
}Data;

typedef struct NCLR{
    Palette *palette;

    Data *data;
}NCLR;

static inline
void getNCLRsize(NCLR nclr){
    iprintf("NCLR size: %i", sizeof(nclr));
}

#endif // #ifndef _NCLR_INCLUDE