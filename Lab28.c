
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include "Procedure.h"


EXIT_CODE string_rev (char** dest, char* src)
{

    char* buff = (char*)malloc(sizeof(char) * strlen(src) + 1);

    for (int i = 0; i < strlen(src); i++)
    {

        if (!isdigit(src[strlen(src) - i - 1]))
        {
            return INVALID;
        }

        buff[i] = src[strlen(src) - i - 1];
    }

    buff[strlen(src)] = '\0';

    *dest = buff;

    return OK;

}

EXIT_CODE last_residue (int value, char** dest)
{

    char* buff = *dest;

    int index = strlen(buff);

    char* temp = (char*)realloc(buff, sizeof(char) * (index + 2));

    if (!temp)
    {
        return BAD_ALLOC;
    }

    buff = temp;

    buff[index] = value + '0';
    buff[index + 1] = '\0';

    *dest = buff;

}

EXIT_CODE sum_up (char** sum, char* adden, int base)
{

    int residue = 0;
    int amount = 0;
    char* buff = *sum;
    char* add_char = adden;

    while (*add_char != '\0')
    {

        if (amount == strlen(buff))
        {

            char* temp = (char*)realloc(buff, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            temp[amount] = '0';
            temp[amount + 1] = '\0';

            buff = temp;

        }
    
        buff[amount] += (((*add_char - '0') + residue) % base);
        residue = (((buff[amount] - '0') + (*add_char - '0') + residue) / base);

        amount++;

        if (amount >= strlen(*sum))
        {
            buff[amount] = '\0';
        }

        add_char++;

    }

    if (residue)
    {
        last_residue(residue, &buff);
    }

    *sum = buff;

}

EXIT_CODE long_str_sum (char** result, int base, int amount, ...)
{

    va_list addings;

    va_start(addings, amount);

    char* buff_rev;
    if (string_rev(&buff_rev, va_arg(addings, char*)) == INVALID)
    {
        return INVALID;
    }

    for (int i = 1; i < amount; i++)
    {

        char* adding = va_arg(addings, char*);

        char* adding_rev;

        if (string_rev(&adding_rev, adding) == INVALID)
        {
            return INVALID;
        }

        sum_up(&buff_rev, adding_rev, base);

        free(adding_rev);

    }

    va_end(addings);

    string_rev(result, buff_rev);

}


int main (int argc, char **argv) 
{

    char* result;

    if (long_str_sum(&result, 4, 3, "211", "1", "40110") != OK)
    {
        printf("Error!\n");
        return 1;
    }
    
    printf("%s", result);

    free(result);

    return 0;
}