#ifndef _BINARYFILE_H
#define _BINARYFILE_H

#include <nds.h>

#include <stdio.h>

#include "libntr/fmt/Common.h"
#include "libntr/fmt/NCLR.h"

typedef struct BinaryFile{
    Header *header;
    CommonBlock *common;
    void *block;
}BinaryFile;

bool ReadFile(const char *nclr_path, bool on_vram);

bool OpenBinaryFile(const char *path, FILE **file);
bool DetectBinaryFile(BinaryFile *bf);
bool ReadBinaryFile(void *read_buf, size_t read_size, FILE **file);
bool CloseBinaryFile(FILE **file);

#endif // #ifndef _BINARYFILE_H