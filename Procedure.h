
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
} EXIT_CODE;


EXIT_CODE geom_mean (double* result, int amount, ...);

EXIT_CODE quick_pow (double* result, int grade, double num);

double rec_pow (int grade, double num);



#endif