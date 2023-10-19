
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "Procedure.h"



void usage () 
{

    printf("./[name_of_exe] double_EPS double_x");

}


EXIT_CODE double_check (char *argv, double *value)
{
    char *endptr;
    *value = strtod (argv, &endptr);
    return (endptr != argv + strlen(argv));
}

EXIT_CODE input_check (int argc, char **argv)
{

    if (argc != 3) 
    {
        return INVALID;
    }

    double EPS = 0;
    double x = 0;

    if (double_check(argv[1], &EPS) != OK || (EPS <= 0)) 
    {
        return INVALID;
    }

    if (double_check(argv[2], &x) != OK) 
    {
        return INVALID;
    } 

    double result = 0;
    if (a_func(EPS, x, &result) != OK)
    {
        return INVALID;
    }
    printf("a: %llf\n", result);
    if (b_func(EPS, x, &result) != OK)
    {
        return INVALID;
    }
    printf("b: %llf\n", result);
    if (c_func(EPS, x, &result) != OK)
    {
        return INVALID;
    }
    printf("c: %llf\n", result);
    if (d_func(EPS, x, &result) != OK)
    {
        return INVALID;
    }
    printf("d: %llf\n", result);
}


EXIT_CODE a_func (double EPS, double x, double *result) 
{

    *result = 1.0;
    double prev_sum = 0;
    double add = 1;
    int num = 0;
    do 
    {
        prev_sum = *result;
        add *= (x / (num + 1.0));
        *result += add;
        num++;

    } while (fabsl(prev_sum - *result) > EPS);
    
    return OK;
}

EXIT_CODE b_func (double EPS, double x, double *result)
{

    *result = 1;
    double prev_sum = 0;
    double add = 1;
    int num = 0;

    do
    {

        prev_sum = *result;
        add *= (((-1.0) * (pow(x, 2))) / (num * 2.0 + 1.0) / (num * 2.0 + 2.0));
        *result += add;
        num++;


    } while (fabsl(prev_sum - *result) > EPS);
    
    return OK;
}

EXIT_CODE c_func (double EPS, double x, double *result)
{


    if (x >= 1)
    {
        return INVALID;
    }
    *result = 1;
    double prev_sum = 0;
    double add = 1;
    int num = 0;

    do
    {

        prev_sum = *result;
        add *= (9.0 * x * x * pow((num + 1.0), 2) / (num * 3.0 + 1.0) / (num * 3.0 + 2.0));
        *result += add;
        num++;


    } while (fabsl(prev_sum - *result) > EPS);

    return OK;
}

EXIT_CODE d_func (double EPS, double x, double *result)
{


    if (x >= 1)
    {
        return INVALID;
    }

    
    double prev_sum = 0;
    double add = ((-1.0) * x * x / 2.0);
    *result = add;
    int num = 1;

    do
    {

        prev_sum = *result;
        add *= ((-1.0) * x * x * (2.0 * num + 1.0) / (2.0 * num + 2.0));
        *result += add;
        num++;


    } while (fabsl(prev_sum - *result) > EPS);

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

        default:
            break;
    }
    return 0;
}