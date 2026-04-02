#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gm_data_file.h"

struct Chunk Parse_Chunk(FILE *GmDtFile)
{
    struct Chunk Parsed_Chunk;

    fread(Parsed_Chunk.name, 1, 4, GmDtFile);

    Parsed_Chunk.name[4] = '\0';

    fread(&Parsed_Chunk.size, 1, 4, GmDtFile);

    return Parsed_Chunk;
}

//yes making function edit the conents of arguments is stupid
//but i could think of any other way other than exceptions to report errors
int parse_gm_data_file(char* File_Name)
{
    printf("Parsing file %s \n", File_Name);

    FILE *GmDtFile;

    GmDtFile = fopen(File_Name, "rb");

    if(GmDtFile == NULL)
    {
        printf("File not found \n");
        return -1;
    }
    struct Chunk Form_Chunk;

    Form_Chunk = Parse_Chunk(GmDtFile);

    printf("Form Chunk size %u \n",Form_Chunk.size);

    fseek(GmDtFile, 8, SEEK_SET);

    //loopging through chunks and reading them
    struct Chunk Current_Chunk;

    int ammount_of_data_chunks = 0;

    for(int i = 0;i<Form_Chunk.size;)
    {
        printf("---------------------------\n",Current_Chunk.size);
        Current_Chunk = Parse_Chunk(GmDtFile);

        printf("Chunk size %u \n",Current_Chunk.size);
        printf("Chunk name %s \n",Current_Chunk.name);

        i+=Current_Chunk.size;

        printf("Byte read %u \n",i);
        printf("---------------------------\n",Current_Chunk.size);
        printf("Bytes left loading %u\n",Form_Chunk.size - i);

        ammount_of_data_chunks++;

        if(strcmp(Current_Chunk.name,"AUDO") == 0)
        {
            break;
        }
        
        fseek(GmDtFile, Current_Chunk.size, SEEK_CUR);
    }
    fclose(GmDtFile);

    printf("Amount of chunks %u \n",ammount_of_data_chunks);

    return 0;
}