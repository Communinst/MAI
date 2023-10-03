
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "Procedure.h"



void usage () 
{

    printf("error");

}

EXIT_CODE input_check(int argc, char **argv)
{
    
    char *step = argv[1];
    
    if (*step != '-' && *step != '/') 
    {
        return INVALID;
    }
    FILE* input = NULL;

    if (file_check(argv[2], &input) != OK) 
    {
        return INVALID;
    }
    step++;
    
    FILE* output = NULL;
    if (*step == 'n') 
    {
        
        if (argc != 4) {
            return INVALID;
        }
        output = fopen(argv[3], "w");
        step++;
    }
    else if (argc != 3) 
    {
        return INVALID;
    }

    char out_name[strlen(argv[2]) + 4];
    strcpy (out_name, "out_");
    output = fopen(strcat(out_name, argv[2]), "w");

    if (flag_handling(step, input, output) != OK) 
    {   
        return INVALID;
    }
    fclose(input);
    return OK;

}


EXIT_CODE file_check(char *argv, FILE** in) 
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

    *in = fopen(argv, "r");
    if (in == NULL) 
    {
        return INVALID;
    }
    return OK;
}

EXIT_CODE extention_check (char *argv) 
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

EXIT_CODE flag_handling (char *c, FILE* in, FILE* out) 
{

    switch (*c)
    {

        case 'i':
            return i_func(in, out);
            break;

        case 's':
            return s_func(in, out);
            break;
        
        case 'a':
            return a_func(in, out);
            break;

        default:
            break;

    }

}


EXIT_CODE i_func (FILE *in, FILE *out)
{

    fseek(in, 0, SEEK_SET);
    fseek(out, 0, SEEK_SET);
    int latin = 0;
    char c;
    while ((c = fgetc(in)) != EOF) {
        
        if (c == '\n')
        {
            fprintf(out, " %d", latin);
            latin = 0;
        }
        
        else if (toupper(c) >= 65 && toupper(c) <= 90)
        {
            latin++;
        }

        fputc(c, out);

    }
    fprintf(out, " %d", latin);
    return OK;
}


EXIT_CODE s_func (FILE *in, FILE *out)
{

    fseek(in, 0, SEEK_SET);
    fseek(out, 0, SEEK_SET);
    int latin = 0;
    char c;
    while ((c = fgetc(in)) != EOF) {
        
        if (c == '\n')
        {
            fprintf(out, " %d", latin);
            latin = 0;
        }
        
        else if ((toupper(c) < 65 || toupper(c) > 90) && (c < '0' || c > '9') && (c != ' '))
        {
            latin++;
        }

        fputc(c, out);

    }
    fprintf(out, " %d", latin);
    return OK;    
    
}

EXIT_CODE a_func (FILE *in, FILE *out) 
{

    fseek(in, 0, SEEK_SET);
    fseek(out, 0, SEEK_SET);
    char c;
    while ((c = fgetc(in)) != EOF) 
    {
        if ((c < '0' || c > '9') && (c != '\n'))
        {
            fprintf(out, "%X", c);
        }
        else 
        {
            fputc(c, out);
        }
    }
    return OK;    
    
}


int main (int argc, char **argv) {

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
    return 0;
}
