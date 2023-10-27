
#ifndef PROCEDURE_H
#define PROCEDURE_H


typedef enum 
{
    OK = 0,
    INVALID,
    BAD_ALLOC,
} EXIT_CODE;



double machine_EPS ();


EXIT_CODE sum_coef (double* res, int grade, double to_add, double a, int order);


EXIT_CODE decompose (double EPS, double a, double** res, int grade, ...);


#endif