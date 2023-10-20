
#include <stdlib.h>
#include <stdio.h>
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
        printf("Inclusions in %s: \n", path);
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

    int beginning = 0;
    int str_num = 1;

    int c;

    while ((c = fgetc(in)) > 0)
    {
        if (substr[0] == c)
        {
            int passed = 0;
            int exit = if_substr(substr, in, c, &passed);
            if (!exit)
            {
                printf("\tString number %d: %d pos\n", str_num, beginning);
            }
            if (exit == 2)
            {
                break;
            }
            fseek(in, passed, SEEK_CUR);
        }
        beginning++;
        if (c == '\n')
        {
            beginning = 0;
            str_num++;
        }
        

    }

    fclose(in);


}


size_t string_length (const char* str)
{

    size_t size = 0;

    while (str[size] != '\0')
    {
        size++;
    }

    return size;

}


int if_substr (const char* ss, FILE* in, int current, int* passed)
{

    

    for (int i = 1; i < string_length(ss); i++)
    {

        current = fgetc(in);
        *passed -= 1;
        if (current < 0)
        {
            return 2;
        }
        if (current != ss[i])
        {
            return 1;
        }
    }

    return 0;

}




int main () 
{

    const char* substr = "\n";

    if (paths_handling(substr, 3, "a.txt", "b.txt", "c.txt") != OK)
    {
        return NO_FILE;
    }


    return 0;
}