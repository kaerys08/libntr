#include "libntr/fs/binaryFile.h"

#define AS_NCLR_PALETTE(x)      ((Palette *)(x))

#define PALETTE                    AS_NCLR_PALETTE(bf.block)

bool ReadFile(const char *path, bool on_vram){
    BinaryFile bf;
    FILE *file = NULL;

    if(!OpenBinaryFile(path, &file)){
        return 0;
    }

    bf.header = malloc(HEADER_SIZE);
    if(bf.header == NULL){
        free(bf.header);
        CloseBinaryFile(&file);
        return 0;
    }

    if(!ReadBinaryFile(bf.header, HEADER_SIZE, &file)){
        free(bf.header);
        CloseBinaryFile(&file);
        return 0;
    }

    bf.common = malloc(COMMON_SIZE);
    if(bf.common == NULL){
        free(bf.header);
        free(bf.common);
        CloseBinaryFile(&file);
        return 0;
    }

    if(!ReadBinaryFile(bf.common, COMMON_SIZE_SIZE, &file)){
        free(bf.header);
        free(bf.common);
        CloseBinaryFile(&file);
        return 0;
    }

    /*if(!DetectBinaryFile(&bf)){
        free(bf.header);
        free(bf.common);
        free(bf.block);
        CloseBinaryFile(&file);
        return 0;
    }*/
    ValidFiles valid = DetectBinaryFile(&bf);
    switch(valid){
        case ValidFiles.NCLR:{
            NCLR nclr;
            nclr.Palette = malloc(sizeof(Palette));
            if(!ReadBinaryFile(bf.block, PALETTE_SIZE, &file)){
                free(bf.header);
                free(bf.common);
                free(bf.block);
                CloseBinaryFile(&file);
                return 0;
            }
        }
        default:{
            iprintf("Nope\n");
        }
    }

    if(bf.block == NULL){
        free(bf.header);
        free(bf.common);
        free(bf.block);
        CloseBinaryFile(&file);
        return 0;
    }
    
    if(!ReadBinaryFile(bf.block, PALETTE_SIZE, &file)){
        free(bf.header);
        free(bf.common);
        free(bf.block);
        CloseBinaryFile(&file);
        return 0;
    }

    SET_BG_COLOR_MODE(PALETTE->bit_depht, 0);
    
    //iprintf("Palette Magic: %08lX", PALETTE->magic);
    /*
    nclr.data = (Data *)malloc(sizeof(Data) * DATA_VALUE_U16(nclr));
    if(nclr.data == NULL){
        free(nclr.header);
        free(nclr.palette);
        free(nclr.data);
        CloseBinaryFile(&file);
        return 0;
    }
    if(!ReadBinaryFile(nclr.data, DATA_VALUE_U16(nclr), &file)){
        free(nclr.header);
        free(nclr.palette);
        free(nclr.data);
        CloseBinaryFile(&file);
        return 0;
    }

    iprintf("Data: 0x%04X 0x%04X\n", nclr.data[1], nclr.data[2]);
    */
    if(!CloseBinaryFile(&file)){
        free(bf.header);
        free(bf.common);
        free(bf.block);
        //free(nclr.palette);
        //free(nclr.data);
        return 0;
    }

    //vramTransfer(nclr.data, paletteAllocateColors(&pal_state_main, DATA_VALUE_U16(nclr)), DATA_VALUE_U16(nclr));
    
    free(bf.header);
    free(bf.common);
    free(bf.block);
    //free(nclr.palette);
    //free(nclr.data);
    return 1;
}

bool OpenBinaryFile(const char *path, FILE **file){
    *file = fopen(path, "rb");
    return *file != NULL;
}

ValidFiles DetectBinaryFile(BinaryFile *bf){
    switch((*bf).header->magic){
        case NCLR_MAGIC:{
            //(*bf).block = malloc(PALETTE_SIZE);
            return ValidFiles.NCLR;
            break;
        }
        default:{
            iprintf("None type detected");
            return 0;
            break;
        }
    }
    return 0;
}

bool ReadBinaryFile(void *read_buf, size_t read_size, FILE **file){
    iprintf("enter\n");
    return fread(read_buf, 1, read_size, *file) == read_size;
}

bool CloseBinaryFile(FILE **file){
    return fclose(*file) == 0;
}