
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include "Procedure.h"



void usage () 
{

    printf("moron");

}

EXIT_CODE input_check(int argc, char **argv)
{

    char *step = argv[1];
    
    if (*step != '-' && *step != '/') 
    {
        return INVALID;
    }

    FILE* input = NULL;

    if (file_check(argv[2], input) != OK) 
    {
        return INVALID;
    }

    *step++;
    if (step == 'n') {

    }

    

    fclose(input);
    return OK;

}


EXIT_CODE file_check(char *argv, FILE* in) 
{
    
    if (strlen(argv) < 5)
    {
        return INVALID;
    }

    if (strchr(argv, '/') || strchr(argv, '?') || strchr(argv, '\\') || strchr(argv, ':') || strchr(argv, '"') || strchr(argv, '<')|| strchr(argv, '>') || strchr(argv, '|'))
    {
        return INVALID;
    }

    if (extention_check(argv) != OK) 
    {   
        return INVALID;
    }

    in = fopen(argv, "r");
    if (in == NULL) 
    {
        return INVALID;
    }
    return OK;
}

EXIT_CODE extention_check(char *argv) 
{

    if (argv[strlen(argv) - 4] != '.') 
    {
        return INVALID;
    }

    char buff[4] = {'\0'};
    for (int i = 1; i <= 3; i++) 
    {
        buff[i - 1] = argv[strlen(argv) - i];
    }

    return (strcmp(buff, "txt"));
}




EXIT_CODE main (int argc, char **argv) {

    if (argc < 3) {
        usage();
        return INVALID;
    }
    switch (input_check(argc, argv))
    {
    case OK:
        printf("cool");
        break;
    
    case INVALID:
        printf("IDIOT!");
        break;

    default:
        break;
    }

}