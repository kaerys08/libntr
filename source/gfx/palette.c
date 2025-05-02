#include "libntr/gfx/palette.h"

#define PH(id) getPaletteAlloc(state, id)

PaletteState pal_state_main = {
    5,
    0,
    NULL,
    64,
};

static PaletteAlloc* getPaletteAlloc(PaletteState *state, int index){
    /*if(index >= paletteAllocBuffer){

    }*/

    return &state->allocPalette[index];
}

static void PaletteAllocPrepare(PaletteState *state){
    if(state->allocPalette == NULL){
        state->allocPalette = (PaletteAlloc *)malloc(sizeof(PaletteAlloc) * state->paletteAllocBufferSize);
        PH(0)->nextFree = 256;
        PH(0)->size = 256;
    }
}

static int simplePaletteAlloc(PaletteState *state, int size){
    iprintf("Size %i\n", size);
    PaletteAllocPrepare(state);

    u16 CurOffset = state->first_free;

    if(state->first_free >= 256 || state->first_free == -1){
        state->first_free = -1;
        return -1;
    }

    int misalignment = CurOffset & (size - 1);

    if(misalignment)
		misalignment = size - misalignment;

    int next = state->first_free;
    int last = next;

    if(CurOffset == state->first_free){
        if(PH(next)->size == size)
		{
			state->first_free = PH(next)->nextFree;
		}
		else
		{
            iprintf("Enter \n");
			state->first_free = CurOffset + size;
			PH(state->first_free)->nextFree = PH(next)->nextFree;
			PH(state->first_free)->size = PH(next)->size - size;
            iprintf("first_Free: %i\n",state->first_free);
            iprintf("nextFree: %04X size: %04X\n", PH(state->first_free)->nextFree, PH(state->first_free)->size);
		}
    }

    return CurOffset;

}

u16* paletteAllocateColors(PaletteState *state, int size){
    int offset = simplePaletteAlloc(state, size);

    iprintf("Offset: %i\n", offset);

    return paletteGetGfxPtr(state, offset);
}

//---------------------------------------------------------------------------------
u16* paletteGetGfxPtr(PaletteState *state, int gfxOffsetIndex) {
//---------------------------------------------------------------------------------
    if(gfxOffsetIndex < 0) return NULL;
    
    if(state == &pal_state_main) {
        return &BG_PALETTE[gfxOffsetIndex];
    } else {
        return &BG_PALETTE_SUB[gfxOffsetIndex];
    }
}
