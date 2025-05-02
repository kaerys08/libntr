#ifndef _COMMON_H
#define _COMMON_H

#include <nds.h>

#include <stdio.h>

#define NCLR_MAGIC          0x4E434C52 // 0x524C434E in little Endian

#define HEADER_SIZE sizeof(Header)
#define COMMON_SIZE sizeof(CommonBlock)
#define PALETTE_SIZE sizeof(Palette)

#define COLOR_DEPHT_16    ((u32)0x00000003)
#define COLOR_DEPHT_256   ((u32)0x00000004)

#define SET_BG_COLOR_MODE(x, id)    setPaletteModeOnBG(x, id)

typedef struct Header{
    u32 magic;
    u16 endianess;
    u16 version;
    u32 file_size;
    u16 header_size;
    u16 blocks;
}Header;

typedef struct CommonBlock{
    u32 magic;
    u32 blocksize;
}CommonBlock;

typedef enum binaryValidFiles{
    NCLR,
    NCGR,
    NCSR,
}ValidFiles;

static inline
void setPaletteModeOnBG(u32 mode, int id){
    switch(mode){
        case COLOR_DEPHT_256:{
            iprintf("Color 256\n");
            BGCTRL[id] |= BG_COLOR_256;
            break;
        }
        case COLOR_DEPHT_16:{
            iprintf("Color 16\n");
            BGCTRL[id] |= BG_COLOR_16;
            break;
        }
    }
}

#endif // #ifndef _COMMON_H