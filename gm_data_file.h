#pragma once
#include <stdint.h>
#include <string.h>

struct Chunk {
    char name [5];
    unsigned long size;
};


int parse_gm_data_file(char* File_Name);