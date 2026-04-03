#pragma once
#include <stdint.h>
#include <string.h>
#include "GM_Strings.h"

struct Chunk
{
    char name [5];
    unsigned long size;
};

struct GM_Data_Strings
{
    unsigned long size;
    struct Gm_string *String;
};

struct GM_Data
{
    struct Chunk Form_chunk;
    struct GM_Data_Strings Gm_Strings;
};

int parse_gm_data_file(char* File_Name,struct GM_Data* GMDATA_ptr);