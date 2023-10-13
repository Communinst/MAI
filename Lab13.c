#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"




/*---------------------------------------Basic--------------------------------------------*/

void usage() 
{
    printf("./[exe_name]\tcopied_filename\tcopy_filename");
}


EXIT_CODE input_check (int argc, char** argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    return file_cpy(argv[1], argv[2]);

}


EXIT_CODE file_cpy (char* in_name, char* out_name)
{

    FILE* in = fopen(in_name, "rb");
    FILE *out = fopen(out_name, "wb");

    if (!in || !out)
    {
        return NO_FILE;
    }

    char c;

    

    while (fread(&c, sizeof(char), 1, in))
    {
        fwrite(&c, sizeof(char), 1, out);
    }

    fclose(in);
    fclose(out);


}




int main (int argc, char *argv[]) {
    
    switch(input_check(argc, argv))
    {
        
        case INVALID:
            usage();
            break;

        case NO_FILE:
            printf("Seems, file doesn't exist!");
            break;

        case OK:
            printf("SUCCESS!");
            break;

    }   

    return 0;

    
}