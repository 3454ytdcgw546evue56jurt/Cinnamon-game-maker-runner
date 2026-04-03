#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gm_data_file.h"
#include "GM_Strings.h"

struct Chunk Parse_Chunk(FILE *GmDtFile)
{
    struct Chunk Parsed_Chunk;

    fread(Parsed_Chunk.name, 1, 4, GmDtFile);

    //Null terminating the string.
    Parsed_Chunk.name[4] = '\0';

    fread(&Parsed_Chunk.size, 1, 4, GmDtFile);

    return Parsed_Chunk;
}

//Gm string parser
struct GM_Data_Strings Parse_gm_string(char *Parser_data_buffer, unsigned long Size)
{
    struct GM_Data_Strings Parsed_Gm_Strings;

    Parsed_Gm_Strings.size = Size;

    Parsed_Gm_Strings.String = (struct Gm_string *)malloc(sizeof(struct Gm_string) * Size);

    char Char_read = 0x0;

    int new_string_start_index = 0;
    int new_string_lenght = 0;
    int New_string_index = 0;

    for(int i = 0; i < Size;i++)
    {
        char Char_read = Parser_data_buffer[i];

        if(Char_read == 0x0)
        {
            //printf("\n");
            Parsed_Gm_Strings.String[New_string_index].size = new_string_lenght+1;

            Parsed_Gm_Strings.String[New_string_index].data = (char *)malloc(new_string_lenght+1);

            memcpy(Parsed_Gm_Strings.String[New_string_index].data,Parser_data_buffer+new_string_start_index,new_string_lenght);

            Parsed_Gm_Strings.String[New_string_index].data[new_string_lenght+1] = '\0';
            
            New_string_index++;
            new_string_start_index+=new_string_lenght;
            new_string_lenght=0;
        }
        else
        {
            //printf(" %d ",Char_read);
            new_string_lenght++;
        }
    }

    return Parsed_Gm_Strings;
}

//yes making function edit the conents of arguments is stupid
//but i could think of any other way other than exceptions to report errors
int parse_gm_data_file(char* File_Name,struct GM_Data* GMDATA_ptr)
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

    GMDATA_ptr->Form_chunk = Form_Chunk;

    printf("Form Chunk size %u \n",Form_Chunk.size);

    //loopging through chunks and reading them
    struct Chunk Current_Chunk;

    int ammount_of_data_chunks = 0;

    for(int i = 0;i<Form_Chunk.size;)
    {
        printf("---------------------------\n",Current_Chunk.size);
        Current_Chunk = Parse_Chunk(GmDtFile);
        
        char *Parser_data_buffer = (char *)malloc(Current_Chunk.size);

        //getting the data for the parser to read.
        fread(Parser_data_buffer, 1, Current_Chunk.size, GmDtFile);

        printf("Chunk size %u \n",Current_Chunk.size);
        printf("Chunk name %s \n",Current_Chunk.name);
        printf("Chunk data address %u \n",&Parser_data_buffer);

        i+=Current_Chunk.size;

        //Switch statements don't work swith string
        //so a if else statements it is then
        if(strcmp(Current_Chunk.name,"STRG") == 0)
        {
            GMDATA_ptr->Gm_Strings = Parse_gm_string(Parser_data_buffer,Current_Chunk.size);
        }
        else
        {
            printf("Uniplemented parser for %s \n.",Current_Chunk.name);
        }

        printf("Byte read %u \n",i);
        printf("---------------------------\n",Current_Chunk.size);
        printf("Bytes left loading %u\n",Form_Chunk.size - i);

        ammount_of_data_chunks++;

        free(Parser_data_buffer);

        if(strcmp(Current_Chunk.name,"AUDO") == 0)
        {
            break;
        }
    }
    fclose(GmDtFile);

    printf("Amount of chunks %u \n",ammount_of_data_chunks);

    return 0;
}