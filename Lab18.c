
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "Procedure.h"



void usage () 
{
    printf("./[name_of_exe]");
}

EXIT_CODE is_str_appropriate (char *str, long int *lint_based, int base)
{

    if (!strlen(str)) 
    {
        return EoF;
    }
    char *step;
    *lint_based = strtol(str, &step, base);

    return (step != str + strlen(str));

}


EXIT_CODE input_check (int argc, char **argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    return write_file(argc, argv);

}


EXIT_CODE write_file (int argc, char **argv)
{

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "wb");

    if (!input && !output)
    {
        return NO_FILE;
    }

    int base = 0;

    while (!feof(input))
    {
        char *str;
        long int based_value = 0;
        aquire_str(input, &str, &base);
        base++;

        EXIT_CODE beam = (is_str_appropriate(str, &based_value, base));
        if (beam == EoF) 
        {
            return OK;
        }
        if (beam != OK)
        {
            return INVALID;
        }
        
        if (base == 10)
        {
            fprintf(output, "%s %d %s\n", str, base, str);

        }
        else 
        {
            fprintf(output, "%s %d %ld\n", str, base, based_value);
        }
        free(str);

    }

    fclose(input);
    fclose(output);

    return OK;

}

EXIT_CODE aquire_str (FILE* f, char **str, int *base)
{

    char *buff = (char*)malloc(sizeof(char) * 1);

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff[0] = '\0';

    int a = fgetc(f);
    skip_dividers(f, &a);
    int amount = 1;
    *base = 2;
    //printf("%d!\n", a);
    do
    {
        
        a = toupper(a);
        if (a < 0)
        {
            break;
        }
        
        if (amount == strlen(buff))
        {
            char *temp = (char*)realloc(buff, sizeof(char) * (amount * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            buff = temp;
            free(temp);
        }

        buff[amount - 1] = a;
        buff[amount] = '\0';
        if (*base < (a - '0')) 
        {
            if (a >= 65 && a <= 90) 
            {
                *base = a - 55;
            }
            else if (a >= 48 && a <= 57)
            {
                *base = a - 48;
            }
        }
        amount++;

    } while (!isspace(a = fgetc(f)));
    
    *str = buff;
    return OK;

}


EXIT_CODE skip_dividers (FILE* f, int *res) 
{

    if (!isspace(*res))
    {
        return OK;
    }
    int a;
    while (isspace(a = fgetc(f)))
    {
        if (a == EOF)
        {
            *res = a;
        }
    }
    *res = a;
    return OK;

}



int main (int argc, char **argv) 
{

    switch (input_check(argc, argv))
    {
        case OK:
            printf("SUCCESS!\n");
            break;
        
        case INVALID:
            printf("Invalid input!\n");
            usage();
            break;

        case BAD_ALLOC:
            printf("Memory fault!");
            break;
        default:
            break;
    }
    return 0;
}