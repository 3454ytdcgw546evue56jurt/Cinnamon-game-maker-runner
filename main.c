#include "gm_data_file.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *data_file_name = NULL;

    //parsing the arumends
    printf("aruments\n");

    for(int i = 0;i<argc;i++)
    {
        //im not sure if this even can be a switch statements
        //either way they are an eye sour for me to read
        if(strcmp(argv[i],"-datafile") == 0)
        {
            printf("setting data file name to: ");
            
            i++;

            printf(argv[i]);

            data_file_name = argv[i];

            printf("\n");
        }

        //printf(argv[i]);
        printf("\n");
    }

    if(data_file_name == NULL)
    {
        printf("Data file not specified \n");
        return -1;
    }

    int loading_dt_file_result = parse_gm_data_file(data_file_name);

    if(loading_dt_file_result != 0)
    {
        printf("Error parsing the data file");
        return -2;
    }

    return 0;
}