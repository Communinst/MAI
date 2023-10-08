
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


EXIT_CODE input_check (int argc, char **argv)
{

    char *step = argv[1];
    if ((*step != '-' && *step != '/') || (strlen(argv[1]) != 2))
    {
        return INVALID;
    }
    step++;
    return (flag_handling (*step, argc, argv));
    

}

EXIT_CODE flag_handling (char flag, int argc, char **argv)
{
    switch (flag)
    {
        case 'r':
            if (argc != 5)
            {
                return INVALID;
            }
            return r_flag_handling (argv);
        
        case 'a':
            if (argc != 4)
            {
                return INVALID;
            }
            return a_flag_handling (argv);

        default:
            break;
    }
}

EXIT_CODE r_flag_handling (char **argv)
{

    FILE* f1 = fopen (argv[2], "r");
    FILE* f2 = fopen (argv[3], "r");
    if (!f1 || !f2)
    {
        return NO_FILE;
    }
    write_both (f1, f2, argv[4]);
    fclose(f1);
    fclose(f2);
    return OK;
}

EXIT_CODE write_both (FILE *f1, FILE *f2, char *out)
{

    FILE *output = fopen(out, "wb");
    if (!output)
    {
        return NO_FILE;
    }
    int c1 = ' ', c2 = ' ';
    do
    {
        skip_dividers(f1, &c1);
        do 
        {
            if (c1 == EOF)
            {
                break;
            }
            fprintf(output, "%c", c1);

        } while (!isspace(c1 = fgetc(f1)));
        fputc(' ', output);

        skip_dividers(f2, &c2);
        do 
        {

            if (c2 == EOF)
            {
                break;
            }
            fprintf(output, "%c", c2);

        } while (!isspace(c2 = fgetc(f2)));
        fputc(' ', output);

    } while (c1 > 0 && c2 > 0);
    write_the_rest_file (f1, output, c1);
    write_the_rest_file (f2, output, c2);
    fclose(output);
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

EXIT_CODE write_the_rest_file (FILE *f, FILE* out, int carr)
{

    if (carr != EOF) 
    {
        do 
        {
            skip_dividers(f, &carr);
            do 
            {
                if (carr == EOF)
                {
                    break;
                }
                fprintf(out, "%c", carr);

            } while (!isspace(carr = fgetc(f)));
            fputc(' ', out);

        } while ((carr = fgetc(f)) != EOF);
    }
    return OK;

}

EXIT_CODE a_flag_handling (char **argv)
{

    FILE* input = fopen(argv[2], "r");
    if (!input)
    {
        return NO_FILE;
    }
    multiplicity_write(input, argv[3]);
    fclose(input);
    return OK;

}

EXIT_CODE multiplicity_write (FILE* input, char *out)
{

    FILE* output = fopen(out, "wb");
    if (!output)
    {
        return NO_FILE;
    }

    int num = 1;
    int ch = ' ';
    long int res = 0;
    do
    {
        skip_dividers(input, &ch);
        do
        {
            if (ch == EOF)
            {
                break;
            }
            if (num == 10)
            {
                char *result;
                printf("%d -> %d\n", ch, tolower(ch));
                conv_tenth_any(tolower(ch), 4, &result);
                fprintf(output, "%s", result);
                free(result);
            }
            else if (num == 5) 
            {
                char *result;
                conv_tenth_any(ch, 8, &result);
                fprintf(output, "%s", result);
                free(result);
            }
            else if (num == 2)
            {
                fprintf(output, "%c", tolower(ch));
            }
            else 
            {
                fprintf(output, "%c", ch);
            }
        } while (!isspace(ch = fgetc(input)));
        fputc(' ', output);
        if (num == 10)
        {
            num = 0;
        }
        num++;
    } while (ch > 0);
    
    fclose(output);
    return OK;

}



EXIT_CODE conv_tenth_any (long int num, long int base, char **result)
{

    int size = 1;
    long int buff = num;
    do 
    {
        size++;
    } while (buff /= base);

    char *answer = (char*)malloc(sizeof(char) * size);
    answer[size - 1] = '\0';

    for (int i = size - 2; i >= 0; i--)
    {

        int residue = num % base;
        if (residue >= 10)
        {

            answer[i] = (55 + residue);

        }

        else 
        {

            answer[i] = residue + '0';

        }
        num /= base;

    }
    *result = answer;

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