
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Procedure.h"



EXIT_CODE dichotomy (double* res, double l_board, double r_board, double EPS, double (*func)(double))
{

    if (l_board > r_board)
    {
        return INVALID;
    }

    if (EPS < 0)
    {
        return INVALID;
    }

    double mid;
    double func_mid;
    do
    {

        mid = (r_board + l_board) / 2;
        func_mid = func(mid);

        if (func_mid * func(l_board) > 0)
        {
            l_board = mid;
        }
        if (func_mid * func(r_board) > 0)
        {
            r_board = mid;
        }

    } while (fabs(func_mid) > EPS);

    *res = mid;

}


int main (int argc, char **argv) 
{

    double res = 0;

    if (dichotomy(&res, 0, 3.14, 0.000001, sin) == INVALID)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("%llf", res);

    return 0;
}