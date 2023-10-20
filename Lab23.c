
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include "Procedure.h"


void warning ()
{
    printf("\nWarning: EOF'll terminate executing process immediately.\n\n");
}


void usage () 
{
    printf("IDIOT!\n");
}


EXIT_CODE paths_handling (const char* substr, int amount, ...)
{

    va_list paths;

    va_start(paths, amount);

    for (int i = 0; i < amount; i++)
    {

        const char* path = va_arg(paths, const char*);
        printf("%s", path);
        str_str(substr, path);

    }

    va_end(paths);

    return OK;

}



EXIT_CODE str_str (const char* substr, const char* file_name)
{

    FILE* in = fopen(file_name, "r");

    if (!in)
    {
        return NO_FILE;
    }

    int c = fgetc(in);

    while (c > 0)
    {

        if (c == substr[0])
        {

        }
        else 
        {
            c = fgetc(in);
        }
        

    } 

    fclose(in);


}


char if_substr (const char* ss, FILE* in)
{





}




int main () 
{

    const char* substr = "idiot";

    if (paths_handling(substr, 3, "a.txt", "b.txt", "c.txt") != OK)
    {
        return NO_FILE;
    }


    return 0;
}