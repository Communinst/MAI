
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>

#include "Procedure.h"


/*---------------------------------Ten-to-any-2^r-(r-in-[1-5])----------------------------*/
EXIT_CODE ten_to_n (long long int tenth, char** result, int pow_of_two)
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

        buff = (tenth & ~(sum_up_by_bits(~(1 << pow_of_two), 1)));
        
        mirror[amount] = (buff > 10) ? sum_up_by_bits(buff, 55) : (buff | 48);

        mirror[++amount] = '\0';

        tenth = tenth >> pow_of_two;

    }

    mirror = strrev(mirror);

    *result = mirror;

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

    char* result;

    ten_to_n(123, &result, 2);

    printf("Result:\t%s\n", result);

    free(result);

    return 0;

}