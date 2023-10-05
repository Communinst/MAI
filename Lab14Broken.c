
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "Procedure.h"



void usage () 
{

    printf("\n./[name_of_exe] [- or /][n option][key] input_file.txt [output_file.txt]\n");
    printf("                             Key list:\n");
    printf("           n in key allows you to determinate output file\n");
    printf("          i - will count all latin letter for a single line\n");
    printf("             s - will count all signs for a single line\n");
    printf("a - will replace every symbol except of digits with it's ASCII hex code\n");


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
    char *filename;
    FILE* output = NULL;
    if (*step == 'n') 
    {
        
        if (argc != 4) {
            return INVALID;
        }
        output = fopen(argv[3], "w");
        step++;
    }
    else  
    {
        if (argc != 3)
        {
            return INVALID;
        }
        
        path_handling(argv[2], &filename);
        char out_name[strlen(filename) + 4];
        strcpy (out_name, "out_");
        output = fopen(strcat(out_name, filename), "w");
    }
    fprintf(output, "%s", "nggr");
    if (!output)
    {
        return NO_FILE;
    }

    if (flag_handling(step, input, output) != OK) 
    {   
        return INVALID;
    }

    free(filename);
    fclose(input);
    fclose(output);
    return OK;

}


EXIT_CODE file_check(char *argv, FILE** in) 
{
    
    if (strlen(argv) < 5)
    {
        return INVALID;
    }

    if (strchr(argv, '/') || strchr(argv, '?') || strchr(argv, '<')|| strchr(argv, '>') || strchr(argv, '|'))
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

EXIT_CODE path_handling (char *argv, char **result)
{

    if (strchr(argv, 92))
    {
        char *final_name = (char*)malloc(sizeof(char) * 1);
        if (!final_name) 
        {
            return BAD_ALLOC;
        }
        final_name[0] = '\0';
        int amount = 1;
        char *step = argv + strlen(argv) - 1;
        while (*step != '\\')
        {
            if (amount == strlen(final_name))
            {
                char *temp = (char*)realloc(final_name, sizeof(char) * (amount * 2));
                if (!temp)
                {
                    return BAD_ALLOC;
                }
                final_name = temp;
                free(temp);
            }
            final_name[amount - 1] = *step;
            final_name[amount] = '\0';
            amount++;
            step = argv + strlen(argv) - amount;

        }
        *result = strrev(final_name);
    }
    else 
    {
        *result = argv;
    }
    return OK;

}


EXIT_CODE flag_handling (char *c, FILE *in, FILE *out) 
{

    fseek(in, 0, SEEK_SET);
    fseek(out, 0, SEEK_SET);
    fprintf(out,"%s", "moron");
    switch (*c)
    {

        case 'i':
            return i_func(in, out);

        case 's':
            return s_func(in, out);
        
        case 'a':
            return a_func(in, out);

        default:
            printf("Sorry, entered flag isn't supported!");
            return INVALID;
    }

}




EXIT_CODE i_func (FILE *in, FILE *out)
{
    int latin = 0;
    char c;
    while ((c = fgetc(in)) != EOF) 
    {
        printf("%c", c);
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
    if (argc < 3) 
    {
        usage();
       return 1;
    }
    switch (input_check(argc, argv))
    {
        case OK:
            printf("SUCCESS!");
            break;
        
        case INVALID:
            printf("Invalid input\n");
            usage();
            break;
        case BAD_ALLOC:
            printf("Memory fault!");
            break;

        case NO_FILE:
            printf("Sorry, file can't be located. Be certain if it exists");
            break;
        default:
            break;
    }
    return 0;
}