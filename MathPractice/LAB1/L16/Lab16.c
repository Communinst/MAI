
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Procedure.h"




void warning ()
{
    printf("The smallest permissible EPS value - 1e-6");
}


void usage () 
{

    printf("\n./[name_of_exe] [- or /][n option][key] input_file.txt [output_file.txt]\n");
    printf("                             Key list:\n");
    printf("           n in key allows you to determinate output file\n");
    printf("                  d - rid of every arabic numbers            ");
    printf("          i - will count all latin letter for a single line\n");
    printf("             s - will count all signs for a single line\n");
    printf("a - will replace every symbol except of digits with it's ASCII hex code\n");

}


EXIT_CODE double_check (char *argv, double *value)
{
    char *endptr;

    *value = strtod (argv, &endptr);

    if (endptr != argv + strlen(argv))
    {
        return INVALID;
    }
    return OK;
}




EXIT_CODE input_control (char *str_EPS) 
{

    double EPS = 0;
    if (double_check (str_EPS, &EPS)) 
    {
        return INVALID;
    }

    if (EPS <= 0)
    {
        return INAPPROPRIATE;
    }


    double answer = 0;
    if (a_right_rectangle(0, 1, EPS, &answer) != OK)
    {
        return INAPPROPRIATE;
    }
    printf("a: %llf\n", answer);

    if (b_right_rectangle(0, 1, EPS, &answer) != OK)
    {
        return INAPPROPRIATE;
    }
    printf("b: %llf\n", answer);

     if (c_left_rectangle(0, 1, EPS, &answer) != OK)
    {
        return INAPPROPRIATE;
    }
    printf("c: %llf\n", answer);

     if (d_right_rectangle(0, 1, EPS, &answer) != OK)
    {
        return INAPPROPRIATE;
    }
    printf("d: %llf\n", answer);

    return OK;

}



EXIT_CODE a_right_rectangle (int a, int b, double EPS, double *result) 
{
    if (EPS < 1e-6) 
    {
        printf("Please enter the EPS > 1e-6\n");
        return INAPPROPRIATE;
    }
    double prev_result = 0;
    int amount = 1;
    do
    {   
        double step = (1.0) * (b - a) / amount;
        prev_result = *result;  
        *result = 0;
        for (double x = b; x > (a + EPS); x -= step)
        {

            *result += (step * (log(1.0 + x) / x));

        }
        amount++;

    } while (fabsl(*result - prev_result) > EPS);



    return OK;

}



EXIT_CODE b_right_rectangle (int a, int b, double EPS, double *result) 
{
    double prev_result = 0;
    int amount = 1;
    do
    {   
        double step = (1.0) * (b - a) / amount;
        prev_result = *result;  
        *result = 0;
        for (double x = b; x > (a + EPS); x -= step)
        {

            *result += (step * sqrt(exp(x * x)));

        }
        amount++;

    } while (fabsl(*result - prev_result) > EPS);



    return OK;

}



EXIT_CODE c_left_rectangle (int a, int b, double EPS, double *result) 
{
    double prev_result = 0;
    int amount = 1;
    do
    {   
        double step = (1.0) * (b - a) / amount;
        prev_result = *result;  
        *result = 0;
        for (double x = a; x < (b - EPS); x += step)
        {

            *result += (step * log(1.0 / (1.0 - x)));

        }
        amount++;

    } while (fabsl(*result - prev_result) > EPS);

    return OK;

}



EXIT_CODE d_right_rectangle (int a, int b, double EPS, double *result) 
{
    double prev_result = 0;
    int amount = 1;
    do
    {   
        double step = (1.0) * (b - a) / amount;
        prev_result = *result;  
        *result = 0;
        for (double x = b; x > (a + EPS); x -= step)
        {

            *result += (step * pow(x, x));

        }
        amount++;

    } while (fabsl(*result - prev_result) > EPS);



    return OK;

}

int main (int argc, char **argv) 
{

    warning();

    if (argc != 2)
    {

        usage();
        return 1;

    }

    switch (input_control(argv[1]))
    {
        case OK:
            printf("SUCCESS!");
            break;
        
        case INVALID:
            printf("Invalid input\n");
            usage();
            break;
        case INAPPROPRIATE:
            printf("ERROR: Inappropriate EPS!\n Enter EPS in [1e-6 -> inf]");
            break;
        default:
            break;
    }
    return 0;
}