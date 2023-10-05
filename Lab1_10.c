
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



EXIT_CODE double_check (char *argv, long int *value, int base)
{
    char *endptr;
    *value = strtol (argv, &endptr, base);
    return (endptr != argv + strlen(argv));
}

EXIT_CODE input_control ()
{

    long int base = 0;
    bool run = true;

    switch (proper_start_nd_base(&base))
    {

        case STOP:
            run = false;
            break;

        case BAD_ALLOC:
            return BAD_ALLOC;
            break;

        case INVALID:
            return INVALID;
            break;

        default:
            break;
    }

    if (base < 2 || base > 36) 
    {
        return INVALID;
    }

    long int num = 0;
    char *unit;
    long int max = 0;

    switch (string_analysis (&unit))
    {
        case STOP:
            run = false;
            break;

        case BAD_ALLOC:
            return BAD_ALLOC;
            break;

        case INVALID:
            return INVALID;
            break;

        default:
            break;
    }

    do
    {
        if (double_check (unit, &num, base))
        {
            return INVALID;
        }

        if (max < num) 
        {
            max = num;
        }
        free(unit);

        switch (string_analysis (&unit))
        {
            case STOP:
                run = false;
                break;

            case BAD_ALLOC:
                return BAD_ALLOC;
                break;
            case INVALID:
                return INVALID;
                break;

            default:
                break;
        }
    
    } while (run);

    free(unit);
    
    char *result;
    printf("%d\n", max);
    conv_tenth_any(max, 9, &result);
    printf("%s\n", result);
    free(result);
    conv_tenth_any(max, 18, &result);
    printf("%s\n", result);
    free(result);
    conv_tenth_any(max, 27, &result);
    printf("%s\n", result);
    free(result);
    conv_tenth_any(max, 36, &result);
    printf("%s\n", result);
    free(result);


    return OK;

}

EXIT_CODE proper_start_nd_base(long int *base)
{

    char *str_base = NULL;
    if (acquire_string(&str_base) != OK)
    {
        return BAD_ALLOC;
    }
    if (!strcmp(str_base, "Stop")) 
    {
        return STOP;
    }
    EXIT_CODE temp = double_check(str_base, base, 10);
    free(str_base);
    return temp;

}

EXIT_CODE string_analysis (char **result)
{

    char *str_base;
    switch (acquire_string(&str_base))
    {
        case BAD_ALLOC:
            return BAD_ALLOC;
            break;
        case INVALID:
            return INVALID;
            break;
        default:
            break;
    }
    if (!strcmp(str_base, "Stop")) 
    {
        return STOP;
    }
    *result = str_base;
    free(str_base);
    return OK;

}

EXIT_CODE acquire_string (char **result)
{

    
    char *input = (char*)malloc(sizeof(char) * 1);

    if (!input)
    {
        return BAD_ALLOC;
    }

    input[0] = '\0';

    char c;
    int amount = 1;
    while ((c = getchar()) != '\n')
    {
        if (c == '-') {
            return INVALID;
        }
        if (c == EOF) 
        {
            break;
        }
        if ((strlen(input)) == amount)
        {

            char *temp = (char*)realloc(input, sizeof(char) * (amount * 2 + 1));
            
            if (!temp)
            {
                return BAD_ALLOC;
            }
            input = temp;
            free(temp);

        }
        input[amount - 1] = c;
        input[amount] = '\0';
        amount++;
    }
    *result = input;
    free(input);
    return OK;
    
}

EXIT_CODE conv_tenth_any (long int num, long int base, char **result)
{


    char *final_str = (char*)malloc(sizeof(char) * 1);
    if (!final_str)
    {
        return BAD_ALLOC;
    }
    final_str[0] = '\0';

    
    int amount = 1;

    do
    {   
        if (strlen(final_str) == amount)
        {

            char *temp = (char*)realloc(final_str, sizeof(char) * (amount * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            final_str = temp;
            free(temp);

        }

        int residue = num % base;
        if (residue >= 10)
        {
            final_str[amount - 1] = (55 + residue);
        }
        else {
            final_str[amount - 1] = residue + '0';
        }
        final_str[amount] = '\0';
        amount++;

    } while (num /= base);

    *result = strrev(final_str);
    free(final_str);
    return OK;
}


int main () 
{

    switch (input_control())
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