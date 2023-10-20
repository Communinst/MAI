
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

#include "Procedure.h"


EXIT_CODE geom_mean (double* result, int amount, ...)
{

    *result = 1;

    va_list args;

    va_start(args, amount);

    for (int i = 0; i < amount; i++)
    {

        double temp = va_arg(args, double);
        *result *= temp;

    }

    va_end(args);
    *result = pow(*result, 1.0 / amount);

    return OK;

}

EXIT_CODE quick_pow (double* result, int grade, double num)
{

    int neg = 0;

    if (grade < 0)
    {
        neg = 0; 
        grade = (-1) * grade;
    }

    *result = rec_pow (grade, num);

    if (neg)
    {
        *result = 1.0 / *result;
    }

    return OK;

}

double rec_pow (int grade, double num)
{

    if (!grade)
    {
        return 1;
    }

    if (grade == 1)
    {
        return num;
    }

    if ((grade & 1) == 1)
    {
        return num * rec_pow(grade >> 1, num * num);
    }
    else 
    {
        return rec_pow(grade >> 1, num * num);
    }


}


int main ( ) 
{

    double res = 0;

    geom_mean(&res, 5, (double) 1, (double) 3, (double) 9, (double) 27, (double) 81);
    printf("Geometric average: %llf\n", res);

    quick_pow(&res, 3, 1.5);
    printf("1.5 times 3: %llf\n", res);

    return 0;
}