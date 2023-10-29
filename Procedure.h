
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{
    OK = 0,
    INVALID,
    BAD_ALLOC,
    DONT_EXIST,

} EXIT_CODE;


double machine_EPS ();

EXIT_CODE get_frac(double* top, double* bottom, double input, double EPS);

int belong_to_base (double top, double bottom, int base, double EPS);

EXIT_CODE does_exist_in_base (int base, int amount, ...);

#endif