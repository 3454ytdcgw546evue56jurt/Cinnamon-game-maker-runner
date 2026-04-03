#include "gm_data_file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *data_file_name = NULL;

    //parsing the arumends
    printf("aruments\n");

    bool print_string = false;

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
        else if(strcmp(argv[i],"-PrintStrings") == 0)
        {
            print_string = true;
        }

        //printf(argv[i]);
        printf("\n");
    }

    if(data_file_name == NULL)
    {
        printf("Data file not specified \n");
        return -1;
    }

    //alocating the Gm data struct
    struct GM_Data *GM_Data = (struct GM_Data *)malloc(sizeof(struct GM_Data));

    if(GM_Data == NULL)
    {
        printf("Unable to alocare memory for struct GM_Data exiting...");
        return 0;
    }

    //Parsin the gm file
    int loading_dt_file_result = parse_gm_data_file(data_file_name,GM_Data);

    if(loading_dt_file_result != 0)
    {
        printf("Error parsing the data file");
        return -2;
    }
    
    if(print_string)
    {
        for(int i = 0; i < GM_Data->Gm_Strings.size;i++)
        {
            printf("%s\n",GM_Data->Gm_Strings.String[i].data);
        }
    }

    free(GM_Data);

    return 0;
}