
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include "Procedure.h"



int is_convex_poly(int amount, ...)
{

    if (amount % 2)
    {
        return INVALID;
    }

    va_list coords;

    va_start(coords, amount);

    double x_start = va_arg(coords, double);
    double y_start = va_arg(coords, double);

    double x_prev = x_start;
    double y_prev = y_start;

    double x_curr;
    double y_curr;

    int angle = 2;

    for (int i = 0; i < ((amount - 2) / 2); i++)
    {   

        x_curr = va_arg(coords, double);
        y_curr = va_arg(coords, double);

        printf("%llf - %llf -> %llf - %llf\n", x_prev, y_prev, x_curr, y_curr);

        if (angle == 2)
        {
            angle = (x_prev * y_curr - y_prev * x_curr < 0);
        }

        
        else if ((x_prev * y_curr - y_prev * x_curr < 0) != angle)
        {
            return NO;
        }
        printf("%d\n", angle);
        x_prev = x_curr;
        y_prev = y_curr;
        
    }

    va_end(coords);

    if ((x_prev * y_start - y_prev * x_start < 0) != angle)
    {
        return NO;
    }


    return YES;

}

EXIT_CODE res_in_point (double* res, double root, int level, ...)
{

    double* coefs = (double*)malloc(sizeof(double) * (level + 1));
    if (!coefs)
    {
        return NO;
    }

    va_list input;

    va_start(input, level);

    for (int i = 0; i < level + 1; i++)
    {

        coefs[i] = va_arg(input, double);

    }

    va_end(input);

    double polynomial = 0;
    int root_level = 1;

    for (int i = level; i >= 0; i--)
    {

        
        polynomial += coefs[i] * root_level;

        root_level *= root;

    }

    *res = polynomial;

    free(coefs);

    return YES;

}

int main () 
{

    //Convex - is_convex_poly(8, (double) 0, (double) 0, (double) 0, (double) 1, (double) 1, (double) 2, (double) 1, (double) 0)
    switch(is_convex_poly(8, (double) 0, (double) 0, (double) 1, (double) 1, (double) 0, (double) 1, (double) 1, (double) 0))
    {

        case INVALID:
            printf("Invalid input!\n");
            break;

        case YES:
            printf("Entered poly's convex!\n");
            break;

        case NO:
            printf("Non-convex!\n");
            break;
    }

    double res = 0;
    res_in_point(&res, (double) 2, 2, (double) 3, (double) 1, (double)0);

    printf("%llf\n", res);



    return 0;
}