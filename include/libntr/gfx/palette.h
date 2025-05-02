#ifndef _PALETTE_H
#define _PALETTE_H

#include <nds.h>

#include <stdio.h>
//#include <>

typedef struct Color{
    union RGB555{
        u16 rgb;
        struct{
            u16 r :5;
            u16 g :5;
            u16 b :5;
        };
    }data;
}Color;

typedef struct PaletteAlloc{
    u16 nextFree;
    u16 size;
}PaletteAlloc;

typedef struct PaletteState{
    int OffsetStep;
    s16 first_free;
    PaletteAlloc *allocPalette;
    s16 paletteAllocBufferSize;
}PaletteState;

u16* paletteAllocateColors(PaletteState *state, int size);
u16* paletteGetGfxPtr(PaletteState *state, int gfxOffsetIndex);

extern PaletteState pal_state_main;

#endif // #ifndef _PALETTE_H