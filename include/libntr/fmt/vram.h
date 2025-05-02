#ifndef _VRAM_H
#define _VRAM_H

#include <nds.h>

static inline
void vramTransfer(const void *src, void *dest, u32 size)
{
    while (dmaBusy(3));

    DC_FlushRange(src, size);

    dmaCopyHalfWords(3, src, dest, size);

    DC_InvalidateRange(dest, size);
}

#endif // #ifndef _VRAM_H