
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>

#include "Procedure.h"


/*----------------------------------------To-free-every-char*-----------------------------*/
EXIT_CODE free_list (int amount, ...)
{

    va_list dynamics;

    va_start(dynamics, amount);

    for (int i = 0; i < amount; i++)
    {

        free(va_arg(dynamics, char**));

    }

    va_end(dynamics);

}

/*----------------------------------------------------------------------------------------*/


/*--------------------------------------Ten-to's-hub--------------------------------------*/
EXIT_CODE ten_to_grades_of_2 (long long int tenth, char** two, char** four, char** eight, char** sixteen, char** thirty_two)
{

    ten_two(tenth, two);

    ten_four(tenth, four);

    ten_eight(tenth, eight);

    ten_sixteen(tenth, sixteen);

    ten_thirty_two(tenth, thirty_two);

    return OK;

}

/*----------------------------------------------------------------------------------------*/


/*---------------------------------Ten-to-any-2^r-(r-in-[1-5])----------------------------*/
EXIT_CODE ten_two (long long int tenth, char** two)
{

    char* mirror = (char*)malloc(sizeof(char) * 1);
    if (!mirror)
    {
        return BAD_ALLOC;
    }
    mirror[0] = '\0';


    int amount = 0;
    int buff = 0;

    while(tenth)
    {

        if (amount == strlen(mirror))
        {

            char* temp = (char*)realloc(mirror, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            mirror = temp;

        }

        buff = (tenth & 1);

        mirror[amount] = buff | 48;

        mirror[++amount] = '\0';

        tenth = tenth >> 1;

    }

    mirror = strrev(mirror);

    *two = mirror;

    return OK;

}


EXIT_CODE ten_four (long long int tenth, char** four)
{

    char* mirror = (char*)malloc(sizeof(char) * 1);
    if (!mirror)
    {
        return BAD_ALLOC;
    }
    mirror[0] = '\0';


    int amount = 0;
    int buff = 0;

    while(tenth)
    {

        if (amount == strlen(mirror))
        {

            char* temp = (char*)realloc(mirror, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            mirror = temp;

        }

        buff = (tenth & 3);
        mirror[amount] = buff | 48;

        mirror[++amount] = '\0';

        tenth = tenth >> 2;

    }

    mirror = strrev(mirror);

    *four = mirror;

    return OK;

}


EXIT_CODE ten_eight (long long int tenth, char** four)
{

    char* mirror = (char*)malloc(sizeof(char) * 1);
    if (!mirror)
    {
        return BAD_ALLOC;
    }
    mirror[0] = '\0';


    int amount = 0;
    int buff = 0;

    while(tenth)
    {

        if (amount == strlen(mirror))
        {

            char* temp = (char*)realloc(mirror, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            mirror = temp;

        }

        buff = (tenth & 7);

        mirror[amount] = buff | 48;

        mirror[++amount] = '\0';

        tenth = tenth >> 3;

    }

    mirror = strrev(mirror);

    *four = mirror;

    return OK;

}


EXIT_CODE ten_sixteen (long long int tenth, char** four)
{

    char* mirror = (char*)malloc(sizeof(char) * 1);
    if (!mirror)
    {
        return BAD_ALLOC;
    }
    mirror[0] = '\0';


    int amount = 0;
    int buff = 0;

    while(tenth)
    {

        if (amount == strlen(mirror))
        {

            char* temp = (char*)realloc(mirror, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            mirror = temp;

        }

        buff = (tenth & 15);
        
        mirror[amount] = (buff > 10) ? sum_up_by_bits(buff, 55) : (buff | 48);

        mirror[++amount] = '\0';

        tenth = tenth >> 4;

    }

    mirror = strrev(mirror);

    *four = mirror;

    return OK;

}


EXIT_CODE ten_thirty_two (long long int tenth, char** four)
{

    char* mirror = (char*)malloc(sizeof(char) * 1);
    if (!mirror)
    {
        return BAD_ALLOC;
    }
    mirror[0] = '\0';


    int amount = 0;
    int buff = 0;

    while(tenth)
    {

        if (amount == strlen(mirror))
        {

            char* temp = (char*)realloc(mirror, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            mirror = temp;

        }

        buff = (tenth & 31);
        
        mirror[amount] = (buff > 10) ? sum_up_by_bits(buff, 55) : (buff | 48);

        mirror[++amount] = '\0';

        tenth = tenth >> 5;

    }

    mirror = strrev(mirror);

    *four = mirror;

    return OK;

}

/*----------------------------------------------------------------------------------------*/


/*------------------------------'+'-by-means-of-bits--------------------------------------*/
int sum_up_by_bits (int residue, int ascii)
{

    int sum = 0;

    int missed = 0;

    //Get sum, but, we missed all 1+1 = 10 (((, got to catch them with &.
    sum = residue ^ ascii;

    //Catched missed 10. Step to the right will avoid overwriting (1 + 1 = 0 and 1 go futher, so..).
    missed = (residue & ascii) << 1;

    //Add all blinds
    while (missed)
    {

        int temp = sum;

        sum = sum ^ missed;

        //step by step, while missed != [0 0 0 0].
        missed = (temp & missed) << 1;

    }

    return sum;

}

/*----------------------------------------------------------------------------------------*/




int main (int argc, char **argv) 
{

    char* second;
    char* fourth;
    char* eighth;
    char* sixteenth;
    char* thirty_second;

    ten_to_grades_of_2(123, &second, &fourth, &eighth, &sixteenth, &thirty_second);


    printf("%s binary\n%s fourth\n%s octal\n%s hex\n%s thirty-second\n", second, fourth, eighth, sixteenth, thirty_second);
    
    free_list(5, &second, &fourth, &eighth, &sixteenth, &thirty_second);


    return 0;

}