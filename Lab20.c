
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#include "Procedure.h"


double machine_EPS ()
{

    double machine_eps = 1;

    while (1.0 + machine_eps > 1.0)
    {
        machine_eps /= 2;
    }

    return machine_eps;

}


EXIT_CODE sum_coef (double* res, int grade, double to_add, double a, int order)
{

    int k = 1;
    for (int i = 0; i < grade + 1; i++)
    {

        if (order < 0)
        {

            *res = 0.0;

        }
        else 
        {

            *res += (to_add * pow(a, order) * k);

            k *= order;

            order--;

        }
        res++;
    }

    return OK;

}


EXIT_CODE decompose (double EPS, double a, double** res, int grade, ...)
{

    va_list coefs;
    
    va_start(coefs, grade);


    double* new_coefs = (double*)malloc(sizeof(double) * (grade + 1));

    if (!new_coefs)
    {
        return BAD_ALLOC;
    }


    int order = 0;
    
    double* coef = new_coefs;

    for (int i = 0; i < grade + 1; i++)
    {

        sum_coef(coef, grade, va_arg(coefs, double), a, order);

        order++;

    }

    va_end(coefs);

    *res = new_coefs;

    return OK;

}


int main (int argc, char **argv) 
{

    double machine_eps = machine_EPS();
    double* new_coefs;
    int grade = 3;

    decompose(machine_eps, 1, &new_coefs, grade, (double) 1, (double) 7, (double) 2, (double) -1); //, (double) 0, );

    for (int i = 0; i <= grade; i++)
    {

        printf("(%llf * (x - a)^%d)  ", new_coefs[i], i);

    }

    printf("\n");

    free(new_coefs);

    return 0;
}