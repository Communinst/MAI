
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
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


EXIT_CODE get_frac(double* top, double* bottom, double input, double EPS)
{

    do
    {

        input *= 10;
        *bottom *= 10;

    } while (fmod(input, 1.0) >= EPS );
    *top = input / 1.0;

}


int belong_to_base (double top, double bottom, int base, double EPS)
{

    double divider = bottom / base;

    //printf("%llf!\n", divider);

    if (fmod(top, divider) <= EPS)
    {
        return 1;
    }
    return 0;

}


EXIT_CODE does_exist_in_base (int base, int amount, ...)
{

    double EPS = machine_EPS();

    //printf("%.20llf", EPS);

    va_list tenth;
    va_start(tenth, amount);

    for (int i = 0; i < amount; i++)
    {


        double temp = va_arg(tenth, double);

        if (temp / 1.0 || temp < 0)
        {
            return INVALID;
        }

        double top = 0;
        double bottom = 1;

        get_frac(&top, &bottom, temp, EPS);

        printf("%llf -> %llf\n", top, bottom);

        if (belong_to_base(top, bottom, base, EPS))
        {
            printf("\n%.8llf exists in %d base\n", temp, base);
        }

    }

    va_end(tenth);

    return OK;

}



int main () 
{

    if (does_exist_in_base(4, 3, 1, 0.75, 0.525) == INVALID)
    {
        printf("Invlaid input!\n");
    }


    return 0;
}