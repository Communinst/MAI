
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{
    OK = 0,
    INVALID,
    BAD_ALLOC,

} EXIT_CODE;

EXIT_CODE dichotomy (double* res, double l_board, double r_board, double EPS, double (*func)(double));

#endif